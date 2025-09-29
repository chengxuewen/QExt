/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2024 ChengXueWen.
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

#include <qextQmlFontIcon.h>
#include <qextQmlFontAwesome.h>
#include <qextOnceFlag.h>

#include <QDebug>
#include <QMutex>
#include <QQmlContext>
#include <QMutexLocker>

class QExtQmlFontIconPrivate
{
public:
    explicit QExtQmlFontIconPrivate(QExtQmlFontIcon *q);
    virtual ~QExtQmlFontIconPrivate();

    QExtQmlFontIcon * const q_ptr;


private:
    QEXT_DECLARE_PUBLIC(QExtQmlFontIcon)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlFontIconPrivate)
};

QExtQmlFontIconPrivate::QExtQmlFontIconPrivate(QExtQmlFontIcon *q)
    : q_ptr(q)
{

}

QExtQmlFontIconPrivate::~QExtQmlFontIconPrivate()
{

}


QExtQmlFontIcon::QExtQmlFontIcon()
    : dd_ptr(new QExtQmlFontIconPrivate(this))
{
}

QExtQmlFontIcon::~QExtQmlFontIcon()
{
}

namespace detail
{
const QString &fontIconUrlHeader()
{
    static const QString urlHeader = "FontIcon:/";
    return urlHeader;
}
}

bool QExtQmlFontIcon::isFontIconUrl(const QString &url)
{
    return 0 == url.indexOf(detail::fontIconUrlHeader());
}

QExtQmlFontIconInfo QExtQmlFontIcon::fontIconInfoFromUrl(const QString &url)
{
    QExtQmlFontIconInfo fontIconInfo;
    if (0 == url.indexOf(detail::fontIconUrlHeader()))
    {
        auto content = url;
        content.remove(detail::fontIconUrlHeader());
        const QStringList contents = content.split("/");
        if (2 == contents.size())
        {
            fontIconInfo.setFamily(contents.at(0).toLower());
            fontIconInfo.setText(contents.at(1));
        }
    }
    return fontIconInfo;
}

bool QExtQmlFontIcon::parseFontIconInfoFromUrl(const QString &url, QExtQmlFontIconInfo *fontIconInfo)
{
    QExtQmlFontIconInfo iconInfo = this->fontIconInfoFromUrl(url);
    fontIconInfo->setFamily(iconInfo.family());
    fontIconInfo->setText(iconInfo.text());
    return true;
}

QString QExtQmlFontIcon::fontIconUrl(const QString &family, const QString &key)
{
    return QString("FontIcon:/%1/%2").arg(family, key);
}

QString QExtQmlFontIcon::version() const
{
    return QString("%1.%2").arg(QEXT_VERSION_MAJOR).arg(QEXT_VERSION_MINOR);
}

void QExtQmlFontIcon::registerTypes(const char *url)
{
    qDebug() << QString("QExtQmlFontIcon::registerTypes(%1)").arg(QEXT_QML_MODULE_URI);
    if (url)
    {
        Q_ASSERT(url == QLatin1String(QEXT_QML_MODULE_URI));
    }
    if (QT_VERSION < QT_VERSION_CHECK(6, 2, 0))
    {
        static QExtOnceFlag onceFlag;
        if (onceFlag.enter())
        {
            Q_INIT_RESOURCE(qextQmlFontIcon);

            const int major = QEXT_VERSION_MAJOR;
            const int minor = QEXT_VERSION_MINOR;

            qmlRegisterType<QExtQmlFontIconInfo>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlFontIconInfo");

            qmlRegisterSingletonType<QExtQmlFontIcon>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlFontIcon",
                                                      QExtQmlFontIcon::create);
            qmlRegisterSingletonType<QExtQmlFontAwesome>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlFontAwesome",
                                                         QExtQmlFontAwesome::create);
            onceFlag.leave();
        }
    }
}

void QExtQmlFontIcon::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(engine)
    Q_UNUSED(uri)
}
