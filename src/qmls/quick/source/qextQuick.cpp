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

#include <private/qextQuick_p.h>
#include <qextQuickWorld.h>
#include <qextQuickGlobal.h>
#include <qextQuickTextGadget.h>
#include <qextQuickBorderGadget.h>
#include <qextQuickBackgroundGadget.h>
#include <qextQuickIconGadget.h>
#include <qextQuickItemGadget.h>
#include <qextQuickPalette.h>
#include <qextQuickFontAwesome.h>
#include <qextQuickConfig.h>

#include <QDebug>
#include <QMutex>
#include <QMutexLocker>
#include <QFontDatabase>
#include <QQmlContext>

inline void initMyResource()
{
    Q_INIT_RESOURCE(qextQuick);
}

namespace MyNamespace
{
void myFunction()
{
    initMyResource();
}
}


QExtQuickPrivate::QExtQuickPrivate(QExtQuick *q)
    : q_ptr(q)
{
    m_mouseAreaCurrsor = Qt::ArrowCursor;
}

QExtQuickPrivate::~QExtQuickPrivate()
{

}



static QExtQuick *sg_instance = nullptr;

QExtQuick::QExtQuick(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQuickPrivate(this))
{

}

QExtQuick::~QExtQuick()
{

}

QObject *QExtQuick::qmlSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return QExtQuick::instance();
}

QExtQuick *QExtQuick::instance()
{
    static QMutex mutex;
    QMutexLocker mutexLocker(&mutex);
    if (nullptr == sg_instance)
    {
        sg_instance = new QExtQuick;
    }
    return sg_instance;
}

QString QExtQuick::version() const
{
    return QString("%1.%2").arg(QEXT_QUICK_PLUGIN_VERSION_MAJOR).arg(QEXT_QUICK_PLUGIN_VERSION_MINOR);
}

QString QExtQuick::stateToString(int state) const
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

int QExtQuick::stateToEnum(const QString &state) const
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

void QExtQuick::registerTypes(const char *url)
{
    Q_ASSERT(url == QLatin1String(QEXT_QUICK_PLUGIN_NAME));
    Q_INIT_RESOURCE(qextQuick);
    //    MyNamespace::myFunction();

    int major = QEXT_QUICK_PLUGIN_VERSION_MAJOR;
    int minor = QEXT_QUICK_PLUGIN_VERSION_MINOR;

    qmlRegisterSingletonType<QExtQuick>(url, major, minor, "QExtQuick", QExtQuick::qmlSingletonTypeProvider);
    qmlRegisterSingletonType<QExtQuickFontAwesome>(url, major, minor, "QExtQuickFontAwesome", QExtQuickFontAwesome::qmlSingletonTypeProvider);
    qmlRegisterSingletonType<QExtQuickPalette>(url, major, minor, "QExtQuickPalette", QExtQuickPalette::qmlSingletonTypeProvider);

    qmlRegisterType<QExtQuickTextGadget>(url, major, minor, "QExtQuickTextGadget");
    qmlRegisterType<QExtQuickBorderGadget>(url, major, minor, "QExtQuickBorderGadget");
    qmlRegisterType<QExtQuickBackgroundGadget>(url, major, minor, "QExtQuickBackgroundGadget");
    qmlRegisterType<QExtQuickIconGadget>(url, major, minor, "QExtQuickIconGadget");
    qmlRegisterType<QExtQuickItemGadget>(url, major, minor, "QExtQuickItemGadget");
    qmlRegisterType<QExtQuickWorld>( url, major, minor, "QExtQuickWorld");

    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickAvatar.qml"), url, major, minor, "QExtQuickAvatar");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickAwesomeIcon.qml"), url, major, minor, "QExtQuickAwesomeIcon");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickBadge.qml"), url, major, minor, "QExtQuickBadge");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickBusyIndicator.qml"), url, major, minor, "QExtQuickBusyIndicator");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickButton.qml"), url, major, minor, "QExtQuickButton");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickCarousel.qml"), url, major, minor, "QExtQuickCarousel");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickCarouselElement.qml"), url, major, minor, "QExtQuickCarouselElement");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickCheckBox.qml"), url, major, minor, "QExtQuickCheckBox");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickCircularProgressBar.qml"), url, major, minor, "QExtQuickCircularProgressBar");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickCollapse.qml"), url, major, minor, "QExtQuickCollapse");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickCollapseElement.qml"), url, major, minor, "QExtQuickCollapseElement");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickDialog.qml"), url, major, minor, "QExtQuickDialog");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickDialogButton.qml"), url, major, minor, "QExtQuickDialogButton");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickDividerLine.qml"), url, major, minor, "QExtQuickDividerLine");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickFpsMonitor.qml"), url, major, minor, "QExtQuickFpsMonitor");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickIcon.qml"), url, major, minor, "QExtQuickIcon");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickIconButton.qml"), url, major, minor, "QExtQuickIconButton");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickInputField.qml"), url, major, minor, "QExtQuickInputField");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickMask.qml"), url, major, minor, "QExtQuickMask");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickMoveArea.qml"), url, major, minor, "QExtQuickMoveArea");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickNavigationBar.qml"), url, major, minor, "QExtQuickNavigationBar");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickNavigationElement.qml"), url, major, minor, "QExtQuickNavigationElement");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickObject.qml"), url, major, minor, "QExtQuickObject");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickPagination.qml"), url, major, minor, "QExtQuickPagination");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickProgressBar.qml"), url, major, minor, "QExtQuickProgressBar");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickRadioButton.qml"), url, major, minor, "QExtQuickRadioButton");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickResizeArea.qml"), url, major, minor, "QExtQuickResizeArea");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickRoundRectangle.qml"), url, major, minor, "QExtQuickRoundRectangle");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickScrollbarH.qml"), url, major, minor, "QExtQuickScrollbarH");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickScrollbarV.qml"), url, major, minor, "QExtQuickScrollbarV");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickSplitView.qml"), url, major, minor, "QExtQuickSplitView");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickSVGIcon.qml"), url, major, minor, "QExtQuickSVGIcon");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickSwitch.qml"), url, major, minor, "QExtQuickSwitch");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickTag.qml"), url, major, minor, "QExtQuickTag");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickWindow.qml"), url, major, minor, "QExtQuickWindow");
    qmlRegisterType(QUrl("qrc:/QExtQuick/control/QExtQuickWindowTitleBar.qml"), url, major, minor, "QExtQuickWindowTitleBar");

    qmlRegisterSingletonType(QUrl("qrc:/QExtQuick/control/QExtQuickToast.qml"), url, major, minor, "QExtQuickToast");
}

void QExtQuick::initQmlEngine(QQmlEngine *engine, const char *uri)
{
    Q_D(QExtQuick);
    Q_UNUSED(uri)
    d->m_qmlEngine = engine;
    QFontDatabase::addApplicationFont(":/QExtQuick/font/fontawesome-webfont.ttf");
    d->m_qmlEngine->rootContext()->setContextProperty("qextRootWindow", QEXT_NULLPTR);
}

void QExtQuick::initQuickRoot(QQuickWindow *rootWindow)
{
    Q_D(QExtQuick);
    if (!d->m_rootWindow.isNull())
    {
        return;
    }
    d->m_rootWindow = rootWindow;
    d->m_qmlEngine->rootContext()->setContextProperty("qextRootWindow", rootWindow);
}

void QExtQuick::initWorld(QExtQuickWorld *world)
{
    Q_D(QExtQuick);
    d->m_quickWorld = world;
}

int QExtQuick::mouseAreaCursorShape() const
{
    Q_D(const QExtQuick);
    return (int)d->m_mouseAreaCurrsor;
}

void QExtQuick::setMouseAreaCursorShape(const Qt::CursorShape &cursor)
{
    Q_D(QExtQuick);
    d->m_mouseAreaCurrsor = cursor;
}
