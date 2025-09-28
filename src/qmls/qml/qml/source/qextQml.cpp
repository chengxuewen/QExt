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

#include <qextQml.h>
#include <qextQmlGlobal.h>
#include <qextQmlConfig.h>
#include <qextQmlSize.h>
#include <qextQmlBorder.h>
#include <qextQmlPadding.h>
#include <qextQmlIconData.h>
#include <qextQmlTextData.h>
#include <qextQmlBackground.h>

#include <qextObject.h>
#include <qextOnceFlag.h>

#include <QDebug>
#include <QMutex>
#include <QPointer>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QMutexLocker>

class QEXT_QML_API QExtQmlPrivate
{
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlPrivate)
    QEXT_DECLARE_PUBLIC(QExtQml)
public:
    explicit QExtQmlPrivate(QExtQml *q);
    virtual ~QExtQmlPrivate();

    QExtQml * const q_ptr;

    QPointer<QQmlEngine> mQmlEngine;
};

QExtQmlPrivate::QExtQmlPrivate(QExtQml *q)
    : q_ptr(q)
{
}

QExtQmlPrivate::~QExtQmlPrivate()
{

}

QExtQml::QExtQml()
    : dd_ptr(new QExtQmlPrivate(this))
{
}

QExtQml::~QExtQml()
{
    int i = 0;
}

QString QExtQml::stateToString(int state) const
{
    switch (state)
    {
    case State_None:
        return "";
    case State_Normal:
        return "Normal";
    case State_Hovered:
        return "Hovered";
    case State_Pressed:
        return "Pressed";
    case State_Checked:
        return "Checked";
    case State_Unchecked:
        return "Unchecked";
    case State_PartiallyChecked:
        return "PartiallyChecked";
    default:
        break;
    }
    return "";
}

int QExtQml::stateToEnum(const QString &state) const
{
    if (state == "")
    {
        return State_None;
    }
    else if (state == "Normal")
    {
        return State_Normal;
    }
    else if (state == "Hovered")
    {
        return State_Hovered;
    }
    else if (state == "Pressed")
    {
        return State_Pressed;
    }
    else if (state == "Checked")
    {
        return State_Checked;
    }
    else if (state == "Unchecked")
    {
        return State_Unchecked;
    }
    else if (state == "PartiallyChecked")
    {
        return State_PartiallyChecked;
    }
    else
    {
        return -1;
    }
}

namespace detail
{
const QString &fontIconUrlHeader()
{
    static const QString urlHeader = "FontIcon:/";
    return urlHeader;
}
}

bool QExtQml::isFontIconUrl(const QString &url)
{
    return 0 == url.indexOf(detail::fontIconUrlHeader());
}

QExtQmlFontIconInfo QExtQml::fontIconInfoFromUrl(const QString &url)
{
    QExtQmlFontIconInfo fontIconInfo;
    if (0 == url.indexOf(detail::fontIconUrlHeader()))
    {
        QStringList contents = url.right(detail::fontIconUrlHeader().size()).split("/");
        if (2 == contents.size())
        {
            fontIconInfo.setFamily(contents.at(0));
            fontIconInfo.setText(contents.at(1));
        }
    }
    return fontIconInfo;
}

bool QExtQml::parseFontIconInfoFromUrl(const QString &url, QExtQmlFontIconInfo *fontIconInfo)
{
    QExtQmlFontIconInfo iconInfo = this->fontIconInfoFromUrl(url);
    fontIconInfo->setFamily(iconInfo.family());
    fontIconInfo->setText(iconInfo.text());
    return true;
}

QString QExtQml::fontIconUrl(const QString &family, const QString &key)
{
    return QString("FontIcon:/%1/%2").arg(family, key);
}

QString QExtQml::version() const
{
    return QString("%1.%2").arg(QEXT_VERSION_MAJOR).arg(QEXT_VERSION_MINOR);
}

void QExtQml::registerTypes(const char *url)
{
    qDebug() << QString("QExtQml::registerTypes(%1)").arg(QEXT_QML_MODULE_URI);
    if (url)
    {
        Q_ASSERT(url == QLatin1String(QEXT_QML_MODULE_URI));
    }
    if (QT_VERSION < QT_VERSION_CHECK(6, 2, 0))
    {
        static QExtOnceFlag onceFlag;
        if (onceFlag.enter())
        {
            Q_INIT_RESOURCE(qextQml);
            const int major = QEXT_VERSION_MAJOR;
            const int minor = QEXT_VERSION_MINOR;

            qmlRegisterSingletonType<QExtQml>(QEXT_QML_MODULE_URI, major, minor, "QExtQml", QExtQml::create);

            qmlRegisterType<QExtQmlSize>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlSize");
            qmlRegisterType<QExtQmlBorder>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlBorder");
            qmlRegisterType<QExtQmlPadding>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlPadding");
            qmlRegisterType<QExtQmlTextData>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlTextData");
            qmlRegisterType<QExtQmlIconData>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlIconData");
            qmlRegisterType<QExtQmlBackground>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlBackground");
            qmlRegisterType<QExtQmlFontIconInfo>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlFontIconInfo");

            qmlRegisterType(QUrl("qrc:/QExtQml/qml/QExtQmlObject.qml"),
                            QEXT_QML_MODULE_URI, major, minor, "QExtQmlObject");
            onceFlag.leave();
        }
    }
}

void QExtQml::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri)
    Q_D(QExtQml);
    d->mQmlEngine = engine;
}
