/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2025 ChengXueWen.
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

// QExtSvgColorImageProvider 单测（设计文档 §14.8 / T5）。
// 量化表与 QML 外壳（QExtQuickSvgIcon.qml 的 bucketPx/bucketDpr）为双实现，本文件的桶断言即对拍锚点：
// 改一处必改另一处，否则 bucketsSnapToLadder 失败。

#include <qextSvgColorImageProvider.h>

#include <QColor>
#include <QDir>
#include <QFile>
#include <QImage>
#include <QTemporaryDir>
#include <QUrl>
#include <QtTest>

namespace {

// urlFor 产出的完整 URL → requestImage 收到的 id（去掉 "image://qextsvg/" 前缀）
static QString idFromUrl(const QString &url)
{
    return url.section(QLatin1Char('/'), 3); // f0=image: f1='' f2=qextsvg → 其余为 id
}

} // namespace

class TstSvgColorProvider : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();

    void urlForEncodesAllParams();
    void parseRoundTrip();
    void bucketsSnapToLadder();
    void dprClampsInParseId();
    void tintKeepsAlphaAndReplacesRgb();
    void respectsDevicePixelRatio();
    void invalidSourceReturnsNull();
    void sourceContractNormalizesAndFails();
    void qrcSchemeRenders();
    void cacheHitOnSameUrl();

private:
    QTemporaryDir mTempDir;
    QString mSvgPath; // 100x100 viewBox、中心 60x60 黑色方块的单色图标
};

void TstSvgColorProvider::initTestCase()
{
    QVERIFY(mTempDir.isValid());
    mSvgPath = mTempDir.filePath(QStringLiteral("square.svg"));

    QFile f(mSvgPath);
    QVERIFY(f.open(QIODevice::WriteOnly | QIODevice::Truncate));
    const QByteArray svg =
        "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100\" height=\"100\" viewBox=\"0 0 100 100\">"
        "<rect x=\"20\" y=\"20\" width=\"60\" height=\"60\" fill=\"black\"/></svg>";
    QCOMPARE(f.write(svg), svg.size());
    f.close();
}

void TstSvgColorProvider::urlForEncodesAllParams()
{
    const QColor tint(QColor(QStringLiteral("#ff8000"))); // 不透明
    const QString url = QExtSvgColorImageProvider::urlFor(
        QStringLiteral("qrc:/QExtQuickControls/resources/image/arrow.svg"), tint, 16, 16, 1.0);

    QVERIFY(url.startsWith(QStringLiteral("image://qextsvg/16/16/100/ffff8000/")));
    // source 段为百分号编码（':' 与 '/' 均被编码，段内不含裸 '/'）
    const QString sourceSeg = url.section(QLatin1Char('/'), 7);
    QCOMPARE(sourceSeg, QString::fromLatin1(
        QUrl::toPercentEncoding(QStringLiteral("qrc:/QExtQuickControls/resources/image/arrow.svg"))));
    QCOMPARE(sourceSeg.count(QLatin1Char('/')), 0);

    // 空参数 → 空串
    QVERIFY(QExtSvgColorImageProvider::urlFor(QString(), tint, 16, 16, 1.0).isEmpty());
    QVERIFY(QExtSvgColorImageProvider::urlFor(QStringLiteral("a.svg"), tint, 0, 16, 1.0).isEmpty());
}

void TstSvgColorProvider::parseRoundTrip()
{
    const QColor tint(12, 34, 56, 78);
    const QString source = QStringLiteral("qrc:/x y/图标.svg"); // 含空格/非 ASCII，往返必须无损
    const QString url = QExtSvgColorImageProvider::urlFor(source, tint, 21, 40, 2.35);
    QVERIFY(!url.isEmpty());

    QString outSource; QColor outColor; qreal w = 0, h = 0, dpr = 0;
    QVERIFY(QExtSvgColorImageProvider::parseId(idFromUrl(url), &outSource, &outColor, &w, &h, &dpr));
    QCOMPARE(outSource, source);                       // 21→24 桶、2.35→3 档（量化后回解）
    QCOMPARE(w, 24.0);
    QCOMPARE(h, 48.0);
    QCOMPARE(dpr, 3.0);
    QCOMPARE(outColor.name(QColor::HexArgb), tint.name(QColor::HexArgb)); // aarrggbb 无损
}

void TstSvgColorProvider::bucketsSnapToLadder()
{
    // 与 QML 外壳 bucketPx/bucketDpr 同一张表（§14.2/§14.4 双实现对拍锚点）
    struct { qreal w; const char *seg; } cases[] = {
        { 1, "8" }, { 8, "8" }, { 9, "12" }, { 21, "24" }, { 33, "48" },
        { 48, "48" }, { 49, "64" }, { 96, "96" }, { 200, "256" }, { 256, "256" },
        { 257, "512" }, { 300, "512" },
    };
    for (const auto &c : cases) {
        const QString url = QExtSvgColorImageProvider::urlFor(
            QStringLiteral("a.svg"), QColor(Qt::black), c.w, c.w, 1.0);
        const QStringList seg = url.section(QLatin1Char('/'), 3).split(QLatin1Char('/'));
        QVERIFY2(seg.at(0) == QLatin1String(c.seg),
                 qPrintable(QStringLiteral("w=%1 got=%2 want=%3").arg(c.w).arg(seg.at(0), c.seg)));
    }

    struct { qreal dpr; int seg; } dprCases[] = {
        { 0.1, 50 }, { 0.5, 50 }, { 0.6, 100 }, { 1.0, 100 }, { 1.2, 150 },
        { 2.35, 300 }, { 3.5, 400 }, { 99.0, 400 }, // 上限钳制（R-2）
    };
    for (const auto &c : dprCases) {
        const QString url = QExtSvgColorImageProvider::urlFor(
            QStringLiteral("a.svg"), QColor(Qt::black), 16, 16, c.dpr);
        const QStringList seg = url.section(QLatin1Char('/'), 3).split(QLatin1Char('/'));
        QVERIFY2(seg.at(2).toInt() == c.seg,
                 qPrintable(QStringLiteral("dpr=%1 got=%2 want=%3").arg(c.dpr).arg(seg.at(2)).arg(c.seg)));
    }
}

void TstSvgColorProvider::dprClampsInParseId()
{
    QString src; QColor col; qreal w = 0, h = 0, dpr = 0;
    const QString tail = QStringLiteral("/ffff0000/a.svg");

    QVERIFY(QExtSvgColorImageProvider::parseId(
        QStringLiteral("16/16/999900") + tail, &src, &col, &w, &h, &dpr));
    QCOMPARE(dpr, 4.0); // 畸形大 dpr → 上钳（防巨量分配）

    QVERIFY(QExtSvgColorImageProvider::parseId(
        QStringLiteral("16/16/1") + tail, &src, &col, &w, &h, &dpr));
    QCOMPARE(dpr, 0.5); // 畸形小 dpr → 下钳

    QVERIFY(!QExtSvgColorImageProvider::parseId(
        QStringLiteral("16/16/100/notahex/"), &src, &col, &w, &h, &dpr)); // 非法颜色段
    QVERIFY(!QExtSvgColorImageProvider::parseId(
        QStringLiteral("16/16"), &src, &col, &w, &h, &dpr)); // 段数不足
}

void TstSvgColorProvider::tintKeepsAlphaAndReplacesRgb()
{
    QExtSvgColorImageProvider provider;
    QSize size;
    const QColor tint(255, 0, 0, 255);
    const QString url = QExtSvgColorImageProvider::urlFor(mSvgPath, tint, 24, 24, 1.0);

    const QImage img = provider.requestImage(idFromUrl(url), &size, QSize());
    QVERIFY(!img.isNull());
    QCOMPARE(img.format(), QImage::Format_ARGB32_Premultiplied);
    QCOMPARE(size, img.size());

    const QColor corner = img.pixelColor(0, 0);       // 源 alpha=0 → 保持透明
    QCOMPARE(corner.alpha(), 0);
    const QColor center = img.pixelColor(img.width() / 2, img.height() / 2); // 源不透明 → 换色
    QCOMPARE(center.red(), 255);
    QCOMPARE(center.green(), 0);
    QCOMPARE(center.blue(), 0);
    QCOMPARE(center.alpha(), 255);

    // 半透明染色：预乘往返有量化误差，分量用 ±2 容差
    const QColor halfTint(0, 128, 255, 128);
    const QString url2 = QExtSvgColorImageProvider::urlFor(mSvgPath, halfTint, 24, 24, 1.0);
    const QImage img2 = provider.requestImage(idFromUrl(url2), &size, QSize());
    const QColor center2 = img2.pixelColor(img2.width() / 2, img2.height() / 2);
    QVERIFY(qAbs(center2.red() - 0) <= 2);
    QVERIFY(qAbs(center2.green() - 128) <= 2);
    QVERIFY(qAbs(center2.blue() - 255) <= 2);
    QVERIFY(qAbs(center2.alpha() - 128) <= 2);
}

void TstSvgColorProvider::respectsDevicePixelRatio()
{
    QExtSvgColorImageProvider provider;
    QSize size;
    const QString url = QExtSvgColorImageProvider::urlFor(mSvgPath, QColor(Qt::black), 48, 48, 2.0);
    const QImage img = provider.requestImage(idFromUrl(url), &size, QSize());

    QVERIFY(!img.isNull());
    QCOMPARE(img.devicePixelRatio(), 2.0);
    QCOMPARE(img.size(), QSize(96, 96)); // 48 桶 × dpr2（方形自然比例）
    QCOMPARE(size, QSize(96, 96));
}

void TstSvgColorProvider::invalidSourceReturnsNull()
{
    QExtSvgColorImageProvider provider;
    QSize size;

    QVERIFY(provider.requestImage(QStringLiteral("nonsense"), &size, QSize()).isNull());
    QVERIFY(provider.requestImage(QStringLiteral("16/16/100/zzzzzzzz/a.svg"), &size, QSize()).isNull());

    const QString missing = QExtSvgColorImageProvider::urlFor(
        mTempDir.filePath(QStringLiteral("nope.svg")), QColor(Qt::black), 16, 16, 1.0);
    QVERIFY(provider.requestImage(idFromUrl(missing), &size, QSize()).isNull()); // 文件不存在
}

void TstSvgColorProvider::sourceContractNormalizesAndFails()
{
    QExtSvgColorImageProvider provider;
    QSize size;

    // file:// 归一（QFile 不认前缀，R-9）→ 与裸路径等效出图
    const QString fileUrl = QUrl::fromLocalFile(mSvgPath).toString(); // file:///...
    QVERIFY(fileUrl.startsWith(QStringLiteral("file:")));
    const QString urlFile = QExtSvgColorImageProvider::urlFor(fileUrl, QColor(Qt::red), 24, 24, 1.0);
    QVERIFY(!provider.requestImage(idFromUrl(urlFile), &size, QSize()).isNull());

    // 非 SVG（PNG）→ QSvgRenderer 无效 → 空图（Image 进 Error 态，不静默降级）
    const QString pngPath = mTempDir.filePath(QStringLiteral("fake.svg"));
    QFile pf(pngPath);
    QVERIFY(pf.open(QIODevice::WriteOnly));
    pf.write(QByteArray::fromHex("89504e470d0a1a0a0000000d49484452000000010000000108060000001f15c48"));
    pf.close();
    const QString urlPng = QExtSvgColorImageProvider::urlFor(pngPath, QColor(Qt::red), 24, 24, 1.0);
    QVERIFY(provider.requestImage(idFromUrl(urlPng), &size, QSize()).isNull());
}

void TstSvgColorProvider::qrcSchemeRenders()
{
    // qrc: scheme 前缀归一（冒烟实证：QSvgRenderer/QFile 不认 "qrc:"，须剥为 ":/"；R-9）
    // 资源由 testdata.qrc 经 AUTORCC 编入测试二进制
    QExtSvgColorImageProvider provider;
    QSize size;
    const QString url = QExtSvgColorImageProvider::urlFor(
        QStringLiteral("qrc:/svgcolor-test/square.svg"), QColor(Qt::blue), 24, 24, 1.0);
    const QImage img = provider.requestImage(idFromUrl(url), &size, QSize());
    QVERIFY2(!img.isNull(), qPrintable(QStringLiteral("qrc: 前缀应归一后成功出图 id=%1").arg(idFromUrl(url))));
    QCOMPARE(img.pixelColor(img.width() / 2, img.height() / 2).blue(), 255);
}

void TstSvgColorProvider::cacheHitOnSameUrl()
{
    QExtSvgColorImageProvider provider;
    QSize size1, size2;
    const QString url = QExtSvgColorImageProvider::urlFor(mSvgPath, QColor(Qt::darkGreen), 32, 32, 1.0);
    const QString id = idFromUrl(url);

    const QImage first = provider.requestImage(id, &size1, QSize());   // 首访：光栅 + 入缓存
    const QImage second = provider.requestImage(id, &size2, QSize());  // 次访：缓存命中
    QVERIFY(!first.isNull());
    QCOMPARE(second, first);
    QCOMPARE(size2, size1);
}

QTEST_GUILESS_MAIN(TstSvgColorProvider)

#include <tst_svgcolorprovider.moc>
