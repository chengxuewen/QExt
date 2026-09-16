/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021 ChengXueWen.
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

#include <qextQuickControls.h>
#include <qextQuickControlsConfig.h>
#include <qextQuickControlsConstant.h>
#include <qextQuickTriangleItem.h>
#include <qextSvgColorImageProvider.h>
#include <qextQuickIpcWidgetItem.h>
#include <qextQuickWidgetItem.h>
#include <qextQuickWorld.h>

#include <qextOnceFlag.h>

#include <QDebug>
#include <QMutex>
#include <QPointer>
#include <QQmlEngine>
#include <QQmlContext>
#include <QMutexLocker>
#include <QQuickWindow>

class QExtQuickWorld;
class QExtQuickControlsPrivate
{
    QExtQuickControls * const q_ptr;
    Q_DECLARE_PUBLIC(QExtQuickControls)
    Q_DISABLE_COPY(QExtQuickControlsPrivate)
public:
    explicit QExtQuickControlsPrivate(QExtQuickControls *q);
    virtual ~QExtQuickControlsPrivate();

    QPointer<QQmlEngine> mQmlEngine;
    QPointer<QQuickWindow> mRootWindow;
    QPointer<QExtQuickWorld> mQuickWorld;
    Qt::CursorShape mMouseAreaCurrsor = Qt::ArrowCursor;
};

QExtQuickControlsPrivate::QExtQuickControlsPrivate(QExtQuickControls *q)
    : q_ptr(q)
{
    mMouseAreaCurrsor = Qt::ArrowCursor;
}

QExtQuickControlsPrivate::~QExtQuickControlsPrivate()
{

}

QExtQuickControls::QExtQuickControls()
    : dd_ptr(new QExtQuickControlsPrivate(this))
{
}

QExtQuickControls::~QExtQuickControls()
{
}

QQuickWindow *QExtQuickControls::rootWindow() const
{
    Q_D(const QExtQuickControls);
    return d->mRootWindow.data();
}

void QExtQuickControls::initQuickRoot(QQuickWindow *rootWindow)
{
    Q_D(QExtQuickControls);
    if (d->mRootWindow.isNull())
    {
        d->mRootWindow = rootWindow;
        d->mQmlEngine->rootContext()->setContextProperty("QExtQuickRootWindow", rootWindow);
        emit this->rootWindowChanged(rootWindow);
    }
}

void QExtQuickControls::initWorld(QExtQuickWorld *world)
{
    Q_D(QExtQuickControls);
    d->mQuickWorld = world;
}

int QExtQuickControls::mouseAreaCursorShape() const
{
    Q_D(const QExtQuickControls);
    return (int)d->mMouseAreaCurrsor;
}

void QExtQuickControls::setMouseAreaCursorShape(const Qt::CursorShape &cursor)
{
    Q_D(QExtQuickControls);
    d->mMouseAreaCurrsor = cursor;
}

QString QExtQuickControls::version() const
{
    return QString("%1.%2").arg(QEXT_VERSION_MAJOR).arg(QEXT_VERSION_MINOR);
}

void QExtQuickControls::registerTypes(const char *url)
{
    // qDebug() << QString("QExtQuickControls::registerTypes(%1)").arg(QEXT_QML_MODULE_URI);
    if (url)
    {
        Q_ASSERT(url == QLatin1String(QEXT_QML_MODULE_URI));
    }
    static QExtOnceFlag onceFlag;
    if (onceFlag.enter())
    {
        Q_INIT_RESOURCE(qextQuickControls);

        const int major = QEXT_VERSION_MAJOR;
        const int minor = QEXT_VERSION_MINOR;

        qmlRegisterSingletonType<QExtQuickControls>(QEXT_QML_MODULE_URI, major, minor, "QExtQuickControls",
                                                    QExtQuickControls::create);

        qmlRegisterType<QExtQuickIpcWidgetItem>(QEXT_QML_MODULE_URI, major, minor, "QExtQuickIpcWidgetItem");
        qmlRegisterType<QExtQuickWidgetItem>(QEXT_QML_MODULE_URI, major, minor, "QExtQuickWidgetItem");
        qmlRegisterType<QExtQuickTriangle>(QEXT_QML_MODULE_URI, major, minor, "QExtQuickTriangle");

        qmlRegisterType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickButton.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQuickButton");
        qmlRegisterType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickButtonArea.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQuickButtonArea");
        qmlRegisterType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickCheckBox.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQuickCheckBox");
        qmlRegisterType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickCollapse.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQuickCollapse");
        qmlRegisterType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickCollapseElement.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQuickCollapseElement");
        qmlRegisterType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickDividerLine.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQuickDividerLine");
        qmlRegisterType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickFontIcon.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQuickFontIcon");
        qmlRegisterType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickIcon.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQuickIcon");
        qmlRegisterType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickIconButton.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQuickIconButton");
        qmlRegisterType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickInputField.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQuickInputField");
        qmlRegisterType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickRadioBox.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQuickRadioBox");
        qmlRegisterType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickRadioBoxGroup.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQuickRadioBoxGroup");
        qmlRegisterType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickRectangle.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQuickRectangle");
        qmlRegisterType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickRoundedShap.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQuickRoundedShap");
        qmlRegisterType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickSvgIcon.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQuickSvgIcon");
        qmlRegisterType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickSwitch.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQuickSwitch");
        qmlRegisterType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickText.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQuickText");
        qmlRegisterType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickToast.qml"),
                        QEXT_QML_MODULE_URI, major, minor, "QExtQuickToast");

        qmlRegisterSingletonType(QUrl("qrc:/QExtQuickControls/qml/QExtQuickGlobalToast.qml"),
                                 QEXT_QML_MODULE_URI, major, minor, "QExtQuickGlobalToast");

        onceFlag.leave();
    }
}

void QExtQuickControls::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri)
    Q_D(QExtQuickControls);
    d->mQmlEngine = engine;
    d->mQmlEngine->rootContext()->setContextProperty("QExtQuickRootWindow", QEXT_NULLPTR);
    // 引导 linked-in/Android 无插件部署：Qt<6.4 引擎默认不扫 ":/" 资源根，而 android rcc bundle
    // 里各 QExt 模块的 qmldir+qml 恰挂在 ":/<Module>/..."（≥6.4 改挂 ":/qt/qml/..." 且引擎默认搜索）。
    // addImportPath 为追加（全局最低优先级），仅兼底；重复添加会被引擎去重，桌面插件模式无感知。
    engine->addImportPath(QStringLiteral(":/"));

    // D5: 每个引擎新建实例，所有权交给 engine（addImageProvider 会接管）。
    // 注：linked-in（Android link-target）解析下插件的 initializeEngine 可能不被调用，
    //     消费方（例子/主程序）须在 engine.load() 前显式调用本函数（幂等守卫防重复）。
    if (engine->imageProvider(QExtSvgColorImageProvider::kId) == QEXT_NULLPTR)
        engine->addImageProvider(QExtSvgColorImageProvider::kId, new QExtSvgColorImageProvider);
}
