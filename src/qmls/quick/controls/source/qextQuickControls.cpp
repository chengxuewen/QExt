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
#include <qextQuickWorld.h>
#include <qextQuickTextGadget.h>
#include <qextQuickBorderGadget.h>
#include <qextQuickBackgroundGadget.h>
#include <qextQuickIconGadget.h>
#include <qextQuickItemGadget.h>
#include <qextQuickPadding.h>
#include <qextQuickPalette.h>
#include <qextQuickControlConfig.h>

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

    QPointer<QQmlEngine> m_qmlEngine;
    QPointer<QQuickWindow> m_rootWindow;
    QPointer<QExtQuickWorld> m_quickWorld;
    Qt::CursorShape m_mouseAreaCurrsor = Qt::ArrowCursor;
};

QExtQuickControlsPrivate::QExtQuickControlsPrivate(QExtQuickControls *q)
    : q_ptr(q)
{
    m_mouseAreaCurrsor = Qt::ArrowCursor;
}

QExtQuickControlsPrivate::~QExtQuickControlsPrivate()
{

}

QExtQuickControls::QExtQuickControls(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQuickControlsPrivate(this))
{

}

QExtQuickControls::~QExtQuickControls()
{

}

QObject *QExtQuickControls::qmlSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return QExtQuickControls::instance();
}

QExtQuickControls *QExtQuickControls::instance()
{
    static QExtOnceFlag onceFlag;
    static QExtQuickControls *instance = QEXT_NULLPTR;
    if (onceFlag.enter())
    {
        instance = new QExtQuickControls;
        onceFlag.leave();
    }
    return instance;
}

QString QExtQuickControls::version() const
{
    return QString("%1.%2").arg(QEXT_VERSION_MAJOR).arg(QEXT_VERSION_MINOR);
}

QString QExtQuickControls::stateToString(int state) const
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

int QExtQuickControls::stateToEnum(const QString &state) const
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

void QExtQuickControls::registerTypes(const char *url)
{
    Q_ASSERT(url == QLatin1String(QEXT_QML_MODULE_URI));
    Q_INIT_RESOURCE(qextQuickControls);

    const int major = QEXT_VERSION_MAJOR;
    const int minor = QEXT_VERSION_MINOR;

    qmlRegisterSingletonType<QExtQuickControls>(QEXT_QML_MODULE_URI, major, minor, "QExtQuickControls",
                                                QExtQuickControls::qmlSingletonTypeProvider);
    qmlRegisterSingletonType<QExtQuickPalette>(QEXT_QML_MODULE_URI, major, minor, "QExtQuickPalette",
                                               QExtQuickPalette::qmlSingletonTypeProvider);

    qmlRegisterType<QExtQuickWorld>( QEXT_QML_MODULE_URI, major, minor, "QExtQuickWorld");
    qmlRegisterType<QExtQuickPadding>(QEXT_QML_MODULE_URI, major, minor, "QExtQuickPadding");
    qmlRegisterType<QExtQuickItemGadget>(QEXT_QML_MODULE_URI, major, minor, "QExtQuickItemGadget");
    qmlRegisterType<QExtQuickTextGadget>(QEXT_QML_MODULE_URI, major, minor, "QExtQuickTextGadget");
    qmlRegisterType<QExtQuickIconGadget>(QEXT_QML_MODULE_URI, major, minor, "QExtQuickIconGadget");
    qmlRegisterType<QExtQuickBorderGadget>(QEXT_QML_MODULE_URI, major, minor, "QExtQuickBorderGadget");
    qmlRegisterType<QExtQuickBackgroundGadget>(QEXT_QML_MODULE_URI, major, minor, "QExtQuickBackgroundGadget");

    qmlRegisterType(QUrl("qrc:/QExtQuickControls/source/qml/QExtQuickAvatar.qml"),
                    QEXT_QML_MODULE_URI, major, minor, "QExtQuickAvatar");
    qmlRegisterType(QUrl("qrc:/QExtQuickControls/source/qml/QExtQuickBadge.qml"),
                    QEXT_QML_MODULE_URI, major, minor, "QExtQuickBadge");
    qmlRegisterType(QUrl("qrc:/QExtQuickControls/source/qml/QExtQuickBusyIndicator.qml"),
                    QEXT_QML_MODULE_URI, major, minor, "QExtQuickBusyIndicator");
    qmlRegisterType(QUrl("qrc:/QExtQuickControls/source/qml/QExtQuickCollapse.qml"),
                    QEXT_QML_MODULE_URI, major, minor, "QExtQuickCollapse");
    qmlRegisterType(QUrl("qrc:/QExtQuickControls/source/qml/QExtQuickCollapseElement.qml"),
                    QEXT_QML_MODULE_URI, major, minor, "QExtQuickCollapseElement");
    qmlRegisterType(QUrl("qrc:/QExtQuickControls/source/qml/QExtQuickDividerLine.qml"),
                    QEXT_QML_MODULE_URI, major, minor, "QExtQuickDividerLine");
    qmlRegisterType(QUrl("qrc:/QExtQuickControls/source/qml/QExtQuickFontImage.qml"),
                    QEXT_QML_MODULE_URI, major, minor, "QExtQuickFontImage");
    qmlRegisterType(QUrl("qrc:/QExtQuickControls/source/qml/QExtQuickFpsMonitor.qml"),
                    QEXT_QML_MODULE_URI, major, minor, "QExtQuickFpsMonitor");
    qmlRegisterType(QUrl("qrc:/QExtQuickControls/source/qml/QExtQuickImage.qml"),
                    QEXT_QML_MODULE_URI, major, minor, "QExtQuickImage");
    qmlRegisterType(QUrl("qrc:/QExtQuickControls/source/qml/QExtQuickInputField.qml"),
                    QEXT_QML_MODULE_URI, major, minor, "QExtQuickInputField");
    qmlRegisterType(QUrl("qrc:/QExtQuickControls/source/qml/QExtQuickMask.qml"),
                    QEXT_QML_MODULE_URI, major, minor, "QExtQuickMask");
    qmlRegisterType(QUrl("qrc:/QExtQuickControls/source/qml/QExtQuickProgressBar.qml"),
                    QEXT_QML_MODULE_URI, major, minor, "QExtQuickProgressBar");
    qmlRegisterType(QUrl("qrc:/QExtQuickControls/source/qml/QExtQuickSvgImage.qml"),
                    QEXT_QML_MODULE_URI, major, minor, "QExtQuickSvgImage");
    qmlRegisterType(QUrl("qrc:/QExtQuickControls/source/qml/QExtQuickTag.qml"),
                    QEXT_QML_MODULE_URI, major, minor, "QExtQuickTag");
    qmlRegisterType(QUrl("qrc:/QExtQuickControls/source/qml/QExtQuickToast.qml"),
                    QEXT_QML_MODULE_URI, major, minor, "QExtQuickToast");

    qmlRegisterSingletonType(QUrl("qrc:/QExtQuickControls/source/qml/QExtQuickGlobalToast.qml"),
                             QEXT_QML_MODULE_URI, major, minor, "QExtQuickGlobalToast");

    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickButton.qml"), url, major, minor, "QExtQuickButton");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickCarousel.qml"), url, major, minor, "QExtQuickCarousel");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickCarouselElement.qml"), url, major, minor, "QExtQuickCarouselElement");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickCheckBox.qml"), url, major, minor, "QExtQuickCheckBox");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickCircularProgressBar.qml"), url, major, minor, "QExtQuickCircularProgressBar");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickDialog.qml"), url, major, minor, "QExtQuickDialog");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickDialogButton.qml"), url, major, minor, "QExtQuickDialogButton");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickIconButton.qml"), url, major, minor, "QExtQuickIconButton");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickMoveArea.qml"), url, major, minor, "QExtQuickMoveArea");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickNavigationBar.qml"), url, major, minor, "QExtQuickNavigationBar");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickNavigationElement.qml"), url, major, minor, "QExtQuickNavigationElement");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickObject.qml"), url, major, minor, "QExtQuickObject");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickPagination.qml"), url, major, minor, "QExtQuickPagination");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickRadioButton.qml"), url, major, minor, "QExtQuickRadioButton");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickResizeArea.qml"), url, major, minor, "QExtQuickResizeArea");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickRoundRectangle.qml"), url, major, minor, "QExtQuickRoundRectangle");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickScrollbarH.qml"), url, major, minor, "QExtQuickScrollbarH");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickScrollbarV.qml"), url, major, minor, "QExtQuickScrollbarV");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickSplitView.qml"), url, major, minor, "QExtQuickSplitView");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickSwitch.qml"), url, major, minor, "QExtQuickSwitch");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickWindow.qml"), url, major, minor, "QExtQuickWindow");
    // qmlRegisterType(QUrl("qrc:/QExtQuickControls/control/QExtQuickWindowTitleBar.qml"), url, major, minor, "QExtQuickWindowTitleBar");

}

void QExtQuickControls::initQmlEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri)
    Q_D(QExtQuickControls);
    d->m_qmlEngine = engine;
    d->m_qmlEngine->rootContext()->setContextProperty("qextRootWindow", QEXT_NULLPTR);
}

void QExtQuickControls::initQuickRoot(QQuickWindow *rootWindow)
{
    Q_D(QExtQuickControls);
    if (d->m_rootWindow.isNull())
    {
        d->m_rootWindow = rootWindow;
        d->m_qmlEngine->rootContext()->setContextProperty("qextRootWindow", rootWindow);
    }
}

void QExtQuickControls::initWorld(QExtQuickWorld *world)
{
    Q_D(QExtQuickControls);
    d->m_quickWorld = world;
}

int QExtQuickControls::mouseAreaCursorShape() const
{
    Q_D(const QExtQuickControls);
    return (int)d->m_mouseAreaCurrsor;
}

void QExtQuickControls::setMouseAreaCursorShape(const Qt::CursorShape &cursor)
{
    Q_D(QExtQuickControls);
    d->m_mouseAreaCurrsor = cursor;
}
