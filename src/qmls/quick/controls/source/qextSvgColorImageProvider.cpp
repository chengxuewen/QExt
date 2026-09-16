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

#include <qextSvgColorImageProvider.h>

#include <QColor>
#include <QPainter>
#include <QSvgRenderer>
#include <QUrl>
#include <QtMath>

const QString QExtSvgColorImageProvider::kId = QStringLiteral("qextsvg");

QExtSvgColorImageProvider::QExtSvgColorImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Image)
{
    mCache.setMaxCost(kCacheBytes);   // 必须显式设：QCache 默认 maxCost=100
    // QQuickImageProvider::Image 类型 + 同步 requestImage，Qt5.15/Qt6.x 交集 API（D6）
}

static int sizeBucket(qreal v)                      // D7：w/h 量化桶（CSS px，与 QML 侧 bucketPx 同表）
{
    static const int kBuckets[] = {8, 12, 16, 24, 32, 48, 64, 96, 128, 192, 256};
    for (int b : kBuckets)
        if (v <= b)
            return b;
    return qCeil(v / 256.0) * 256;
}

static qreal dprBucket(qreal v)                     // D7：dpr 档位，上限钳制（R-2）
{
    static const qreal kSteps[] = {0.5, 1, 1.5, 2, 3, 4};
    for (qreal s : kSteps)
        if (v <= s)
            return s;
    return 4;
}

QString QExtSvgColorImageProvider::urlFor(const QString &source, const QColor &color,
                                          qreal width, qreal height, qreal devicePixelRatio)
{
    if (source.isEmpty() || width <= 0 || height <= 0)
        return QString();

    return QStringLiteral("image://qextsvg/%1/%2/%3/%4/%5")
            .arg(sizeBucket(width)).arg(sizeBucket(height))                   // D7 尺寸桶
            .arg(qRound(dprBucket(devicePixelRatio) * 100.0))                 // D7 dpr 档位，钳制 [0.5,4]
            .arg(color.name(QColor::HexArgb).mid(1))                          // aarrggbb
            .arg(QString::fromLatin1(QUrl::toPercentEncoding(source)));       // D3/D4: 参数全进 path
}

bool QExtSvgColorImageProvider::parseId(const QString &id, QString *source, QColor *color,
                                        qreal *width, qreal *height, qreal *dpr)
{
    const QStringList head = id.section(QLatin1Char('/'), 0, 3).split(QLatin1Char('/'));
    if (head.size() != 4)
        return false;

    *width  = head.at(0).toDouble();
    *height = head.at(1).toDouble();
    *dpr    = qBound(0.5, head.at(2).toDouble() / 100.0, 4.0);   // 上下限钳制（R-2：防畸形 dpr 巨量分配）

    QColor c;
    c.setNamedColor(QLatin1Char('#') + head.at(3));     // #aarrggbb：Qt 5.2 起支持，单测锁定
    if (!c.isValid())
        return false;
    *color = c;

    // 第 5 段起为 source（百分号编码；解码后段内即便含 '/' 也由 section(4,-1) 原样接回）
    *source = QUrl::fromPercentEncoding(id.section(QLatin1Char('/'), 4, -1).toUtf8());
    return !source->isEmpty();
}

static QSizeF naturalSize(const QSvgRenderer &renderer)
{
    QSizeF size = QSizeF(renderer.defaultSize());
    if (size.width() <= 0 || size.height() <= 0) {    // 无 width/height 属性的图标回退 viewBox()
        const QRectF vb = renderer.viewBox();
        if (vb.width() > 0 && vb.height() > 0)
            size = QSizeF(vb.width(), vb.height());
    }
    return size;
}

static QSizeF fittedSize(const QSizeF &natural, const QSizeF &box)
{
    if (natural.isEmpty() || natural.width() <= 0 || natural.height() <= 0)
        return box;
    const qreal s = qMin(box.width() / natural.width(), box.height() / natural.height());
    return QSizeF(natural.width() * s, natural.height() * s);
}

QImage QExtSvgColorImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(requestedSize)
    QMutexLocker locker(&mMutex);

    if (const QImage *hit = mCache.object(id)) {   // 命中分支也必须填 *size（§14.4 示意遗漏，单测发现）
        if (size)
            *size = hit->size();
        return *hit;                              // id 即键 → 命中即返回
    }

    QString source; QColor color; qreal w = 0, h = 0, dpr = 1.0;
    if (!parseId(id, &source, &color, &w, &h, &dpr))
        return QImage();

    // QString 构造重载；QByteArray 重载会被当作 SVG 文档内容解析。
    // 归一：QFile/QSvgRenderer 不认 scheme 前缀（"file:" 拒、"qrc:" 打不开，冒烟实证；R-9 补充）
    QString path = source;
    if (path.startsWith(QLatin1String("file:")))
        path = QUrl(path).toLocalFile();                // "file://" → 本地路径
    else if (path.startsWith(QLatin1String("qrc:")))
        path.replace(0, 4, QLatin1String(":"));              // "qrc:/x" → ":/x"（QFile 资源形态；"/x" 会被当文件系统绝对路径）
    QSvgRenderer renderer(path);
    if (!renderer.isValid())
        return QImage();

    // 按 SVG 自然比例在 (w x h) 盒内决定分辨率；缩放/裁剪语义留给 QML Image.fillMode
    const QSizeF css = fittedSize(naturalSize(renderer), QSizeF(w, h));
    const QSize px(qMax(1, qCeil(css.width() * dpr)), qMax(1, qCeil(css.height() * dpr)));

    QImage image(px, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    renderer.render(&painter, QRectF(QPointF(0, 0), QSizeF(px)));
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);   // D1: 保 alpha 换 RGB
    painter.fillRect(image.rect(), color);
    painter.end();

    image.setDevicePixelRatio(dpr);                                   // 绘制结束后再设
    mCache.insert(id, new QImage(image), image.sizeInBytes());        // 代价显式传；byteCount() Qt6 已删
    if (size)
        *size = px;
    return image;
}
