#include <qextQmlQuick.h>
#include <qextQmlQuick_p.h>
#include <qextQmlQuickWorld.h>
#include <qextQmlQuickGlobal.h>
#include <qextQmlQuickTextGadget.h>
#include <qextQmlQuickBorderGadget.h>
#include <qextQmlQuickBackgroundGadget.h>
#include <qextQmlQuickIconGadget.h>
#include <qextQmlQuickItemGadget.h>
#include <qextQmlQuickPalette.h>
#include <qextQmlQuickFontAwesome.h>

#include <qextQuickConfig.h>
#include <qextGlobal.h>

#include <QMutex>
#include <QMutexLocker>
#include <QFontDatabase>
#include <QQmlContext>
#include <QDebug>

inline void initMyResource()
{
    Q_INIT_RESOURCE(QEXTQmlQuick);
}

namespace MyNamespace
{
    void myFunction()
    {
        initMyResource();
    }
}




QEXTQmlQuickPrivate::QEXTQmlQuickPrivate(QEXTQmlQuick *q)
    : q_ptr(q)
{
    m_mouseAreaCurrsor = Qt::ArrowCursor;
}

QEXTQmlQuickPrivate::~QEXTQmlQuickPrivate()
{

}



static QEXTQmlQuick *sg_instance = nullptr;

QEXTQmlQuick::QEXTQmlQuick(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QEXTQmlQuickPrivate(this))
{

}

QEXTQmlQuick::~QEXTQmlQuick()
{

}

QObject *QEXTQmlQuick::qmlSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return QEXTQmlQuick::instance();
}

QEXTQmlQuick *QEXTQmlQuick::instance()
{
    static QMutex mutex;
    QMutexLocker mutexLocker(&mutex);
    if (nullptr == sg_instance)
    {
        sg_instance = new QEXTQmlQuick;
    }
    return sg_instance;
}

QString QEXTQmlQuick::version() const
{
    return QString("%1.%2").arg(QEXT_QUICK_PLUGIN_VERSION_MAJOR).arg(QEXT_QUICK_PLUGIN_VERSION_MINOR);
}

QString QEXTQmlQuick::stateToString(int state) const
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

int QEXTQmlQuick::stateToEnum(const QString &state) const
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

void QEXTQmlQuick::registerTypes(const char *url)
{
    Q_ASSERT(url == QLatin1String(QEXT_QUICK_PLUGIN_NAME));
    Q_INIT_RESOURCE(QEXTQmlQuick);
//    MyNamespace::myFunction();

    int major = QEXT_QUICK_PLUGIN_VERSION_MAJOR;
    int minor = QEXT_QUICK_PLUGIN_VERSION_MINOR;

    qmlRegisterSingletonType<QEXTQmlQuick>(url, major, minor, "QEXTQmlQuick", QEXTQmlQuick::qmlSingletonTypeProvider);
    qmlRegisterSingletonType<QEXTQmlQuickFontAwesome>(url, major, minor, "QEXTQmlQuickFontAwesome", QEXTQmlQuickFontAwesome::qmlSingletonTypeProvider);
    qmlRegisterSingletonType<QEXTQmlQuickPalette>(url, major, minor, "QEXTQmlQuickPalette", QEXTQmlQuickPalette::qmlSingletonTypeProvider);

    qmlRegisterType<QEXTQmlQuickTextGadget>(url, major, minor, "QEXTQmlQuickTextGadget");
    qmlRegisterType<QEXTQmlQuickBorderGadget>(url, major, minor, "QEXTQmlQuickBorderGadget");
    qmlRegisterType<QEXTQmlQuickBackgroundGadget>(url, major, minor, "QEXTQmlQuickBackgroundGadget");
    qmlRegisterType<QEXTQmlQuickIconGadget>(url, major, minor, "QEXTQmlQuickIconGadget");
    qmlRegisterType<QEXTQmlQuickItemGadget>(url, major, minor, "QEXTQmlQuickItemGadget");
    qmlRegisterType<QEXTQmlQuickWorld>( url, major, minor, "QEXTQmlQuickWorld");

    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickAvatar.qml"), url, major, minor, "QEXTQmlQuickAvatar");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickAwesomeIcon.qml"), url, major, minor, "QEXTQmlQuickAwesomeIcon");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickBadge.qml"), url, major, minor, "QEXTQmlQuickBadge");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickBusyIndicator.qml"), url, major, minor, "QEXTQmlQuickBusyIndicator");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickButton.qml"), url, major, minor, "QEXTQmlQuickButton");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickCarousel.qml"), url, major, minor, "QEXTQmlQuickCarousel");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickCarouselElement.qml"), url, major, minor, "QEXTQmlQuickCarouselElement");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickCheckBox.qml"), url, major, minor, "QEXTQmlQuickCheckBox");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickCircularProgressBar.qml"), url, major, minor, "QEXTQmlQuickCircularProgressBar");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickCollapse.qml"), url, major, minor, "QEXTQmlQuickCollapse");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickCollapseElement.qml"), url, major, minor, "QEXTQmlQuickCollapseElement");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickDialog.qml"), url, major, minor, "QEXTQmlQuickDialog");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickDialogButton.qml"), url, major, minor, "QEXTQmlQuickDialogButton");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickDividerLine.qml"), url, major, minor, "QEXTQmlQuickDividerLine");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickFpsMonitor.qml"), url, major, minor, "QEXTQmlQuickFpsMonitor");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickIcon.qml"), url, major, minor, "QEXTQmlQuickIcon");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickIconButton.qml"), url, major, minor, "QEXTQmlQuickIconButton");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickInputField.qml"), url, major, minor, "QEXTQmlQuickInputField");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickMask.qml"), url, major, minor, "QEXTQmlQuickMask");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickMoveArea.qml"), url, major, minor, "QEXTQmlQuickMoveArea");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickNavigationBar.qml"), url, major, minor, "QEXTQmlQuickNavigationBar");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickNavigationElement.qml"), url, major, minor, "QEXTQmlQuickNavigationElement");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickObject.qml"), url, major, minor, "QEXTQmlQuickObject");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickPagination.qml"), url, major, minor, "QEXTQmlQuickPagination");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickProgressBar.qml"), url, major, minor, "QEXTQmlQuickProgressBar");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickRadioButton.qml"), url, major, minor, "QEXTQmlQuickRadioButton");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickResizeArea.qml"), url, major, minor, "QEXTQmlQuickResizeArea");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickRoundRectangle.qml"), url, major, minor, "QEXTQmlQuickRoundRectangle");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickScrollbarH.qml"), url, major, minor, "QEXTQmlQuickScrollbarH");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickScrollbarV.qml"), url, major, minor, "QEXTQmlQuickScrollbarV");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickSplitView.qml"), url, major, minor, "QEXTQmlQuickSplitView");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickSVGIcon.qml"), url, major, minor, "QEXTQmlQuickSVGIcon");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickSwitch.qml"), url, major, minor, "QEXTQmlQuickSwitch");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickTag.qml"), url, major, minor, "QEXTQmlQuickTag");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickWindow.qml"), url, major, minor, "QEXTQmlQuickWindow");
    qmlRegisterType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickWindowTitleBar.qml"), url, major, minor, "QEXTQmlQuickWindowTitleBar");

    qmlRegisterSingletonType(QUrl("qrc:/QEXTQmlQuick/control/QEXTQmlQuickToast.qml"), url, major, minor, "QEXTQmlQuickToast");
}

void QEXTQmlQuick::initQmlEngine(QQmlEngine *engine, const char *uri)
{
    Q_D(QEXTQmlQuick);
    Q_UNUSED(uri)
    d->m_qmlEngine = engine;
    QFontDatabase::addApplicationFont(":/QEXTQmlQuick/font/fontawesome-webfont.ttf");
    d->m_qmlEngine->rootContext()->setContextProperty("qextRootWindow", QEXT_DECL_NULLPTR);
}

void QEXTQmlQuick::initQuickRoot(QQuickWindow *rootWindow)
{
    Q_D(QEXTQmlQuick);
    if (!d->m_rootWindow.isNull())
    {
        return;
    }
    d->m_rootWindow = rootWindow;
    d->m_qmlEngine->rootContext()->setContextProperty("qextRootWindow", rootWindow);
}

void QEXTQmlQuick::initWorld(QEXTQmlQuickWorld *world)
{
    Q_D(QEXTQmlQuick);
    d->m_quickWorld = world;
}

int QEXTQmlQuick::mouseAreaCursorShape() const
{
    Q_D(const QEXTQmlQuick);
    return (int)d->m_mouseAreaCurrsor;
}

void QEXTQmlQuick::setMouseAreaCursorShape(const Qt::CursorShape &cursor)
{
    Q_D(QEXTQmlQuick);
    d->m_mouseAreaCurrsor = cursor;
}
