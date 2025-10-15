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
#include <qextQmlInitializer.h>
#include <qextQmlConstant.h>
#include <qextQmlConfig.h>
#include <qextQmlSizeInfo.h>
#include <qextQmlBorderInfo.h>
#include <qextQmlPaddingInfo.h>
#include <qextQmlIconInfo.h>
#include <qextQmlTextInfo.h>
#include <qextQmlPalette.h>
#include <qextQmlRectangleInfo.h>
#include <qextQmlBackgroundInfo.h>

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
    QQuickWindow *mRootWindow{nullptr};
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
}

QString QExtQml::stateToString(int state) const
{
    switch (state)
    {
    case StateNormal:
        return QExtQmlConstant::kStateNormal;
    case StateHovered:
        return QExtQmlConstant::kStateHovered;
    case StatePressed:
        return QExtQmlConstant::kStatePressed;
    case StateChecked:
        return QExtQmlConstant::kStateChecked;
    default:
        break;
    }
    return "";
}

int QExtQml::stateToEnum(const QString &state) const
{
    if (state == QExtQmlConstant::kStateNormal)
    {
        return StateNormal;
    }
    else if (state == QExtQmlConstant::kStateHovered)
    {
        return StateHovered;
    }
    else if (state == QExtQmlConstant::kStatePressed)
    {
        return StatePressed;
    }
    else if (state == QExtQmlConstant::kStateChecked)
    {
        return StateChecked;
    }
    else
    {
        return -1;
    }
}

QString QExtQml::qtVersion() const
{
    return QT_VERSION_STR;
}

int QExtQml::qtVersionMajor() const
{
    return QT_VERSION_MAJOR;
}

int QExtQml::qtVersionMinor() const
{
    return QT_VERSION_MINOR;
}

int QExtQml::qtVersionPatch() const
{
    return QT_VERSION_PATCH;
}

QQuickWindow *QExtQml::rootWindow() const
{
    Q_D(const QExtQml);
    return d->mRootWindow;
}

void QExtQml::setRootWindow(QQuickWindow *window)
{
    Q_D(QExtQml);
    if (window != d->mRootWindow)
    {
        d->mRootWindow = window;
        emit this->rootWindowChanged(window);
    }
}

int QExtQml::svgIconVersion() const
{
#ifdef Q_OS_ANDROID
    return 0;
#else
    return (QT_VERSION_MAJOR > 5) ? 1 : 2;
#endif
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
    static QExtOnceFlag onceFlag;
    if (onceFlag.enter())
    {
        Q_INIT_RESOURCE(qextQml);
        const int major = QEXT_VERSION_MAJOR;
        const int minor = QEXT_VERSION_MINOR;

        qmlRegisterSingletonType<QExtQml>(QEXT_QML_MODULE_URI, major, minor, "QExtQml", QExtQml::create);

        qmlRegisterType<QExtQmlPalette>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlPalette");
        qmlRegisterType<QExtQmlInitializer>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlInitializer");

        qmlRegisterType<QExtQmlSizeInfo>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlSizeInfo");
        qmlRegisterType<QExtQmlTextInfo>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlTextInfo");
        qmlRegisterType<QExtQmlIconInfo>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlIconInfo");
        qmlRegisterType<QExtQmlBorderInfo>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlBorderInfo");
        qmlRegisterType<QExtQmlPaddingInfo>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlPaddingInfo");
        qmlRegisterType<QExtQmlRectangleInfo>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlRectangleInfo");
        qmlRegisterType<QExtQmlBackgroundInfo>(QEXT_QML_MODULE_URI, major, minor, "QExtQmlBackgroundInfo");

        qmlRegisterType(QUrl("qrc:/QExtQml/qml/QExtQmlObject.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQmlObject");
        onceFlag.leave();
    }
}

void QExtQml::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri)
    Q_D(QExtQml);
    d->mQmlEngine = engine;
}
