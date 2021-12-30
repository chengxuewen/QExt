#include <qextQuick.h>
#include <qextQuick_p.h>
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
#include <qextGlobal.h>

#include <QMutex>
#include <QMutexLocker>
#include <QFontDatabase>
#include <QQmlContext>
#include <QDebug>

inline void initMyResource()
{
    Q_INIT_RESOURCE(QEXTQuick);
}

namespace MyNamespace
{
    void myFunction()
    {
        initMyResource();
    }
}




QEXTQuickPrivate::QEXTQuickPrivate(QEXTQuick *q)
    : q_ptr(q)
{
    m_mouseAreaCurrsor = Qt::ArrowCursor;
}

QEXTQuickPrivate::~QEXTQuickPrivate()
{

}



static QEXTQuick *sg_instance = nullptr;

QEXTQuick::QEXTQuick(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QEXTQuickPrivate(this))
{

}

QEXTQuick::~QEXTQuick()
{

}

QObject *QEXTQuick::qmlSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return QEXTQuick::instance();
}

QEXTQuick *QEXTQuick::instance()
{
    static QMutex mutex;
    QMutexLocker mutexLocker(&mutex);
    if (nullptr == sg_instance)
    {
        sg_instance = new QEXTQuick;
    }
    return sg_instance;
}

QString QEXTQuick::version() const
{
    return QString("%1.%2").arg(QEXT_QUICK_PLUGIN_VERSION_MAJOR).arg(QEXT_QUICK_PLUGIN_VERSION_MINOR);
}

QString QEXTQuick::stateToString(int state) const
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

int QEXTQuick::stateToEnum(const QString &state) const
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

void QEXTQuick::registerTypes(const char *url)
{
    Q_ASSERT(url == QLatin1String(QEXT_QUICK_PLUGIN_NAME));
    Q_INIT_RESOURCE(QEXTQuick);
//    MyNamespace::myFunction();

    int major = QEXT_QUICK_PLUGIN_VERSION_MAJOR;
    int minor = QEXT_QUICK_PLUGIN_VERSION_MINOR;

    qmlRegisterSingletonType<QEXTQuick>(url, major, minor, "QEXTQuick", QEXTQuick::qmlSingletonTypeProvider);
    qmlRegisterSingletonType<QEXTQuickFontAwesome>(url, major, minor, "QEXTQuickFontAwesome", QEXTQuickFontAwesome::qmlSingletonTypeProvider);
    qmlRegisterSingletonType<QEXTQuickPalette>(url, major, minor, "QEXTQuickPalette", QEXTQuickPalette::qmlSingletonTypeProvider);

    qmlRegisterType<QEXTQuickTextGadget>(url, major, minor, "QEXTQuickTextGadget");
    qmlRegisterType<QEXTQuickBorderGadget>(url, major, minor, "QEXTQuickBorderGadget");
    qmlRegisterType<QEXTQuickBackgroundGadget>(url, major, minor, "QEXTQuickBackgroundGadget");
    qmlRegisterType<QEXTQuickIconGadget>(url, major, minor, "QEXTQuickIconGadget");
    qmlRegisterType<QEXTQuickItemGadget>(url, major, minor, "QEXTQuickItemGadget");
    qmlRegisterType<QEXTQuickWorld>( url, major, minor, "QEXTQuickWorld");

    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTAvatar.qml"), url, major, minor, "QEXTAvatar");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTAwesomeIcon.qml"), url, major, minor, "QEXTAwesomeIcon");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTBadge.qml"), url, major, minor, "QEXTBadge");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTBusyIndicator.qml"), url, major, minor, "QEXTBusyIndicator");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTButton.qml"), url, major, minor, "QEXTButton");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTCarousel.qml"), url, major, minor, "QEXTCarousel");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTCarouselElement.qml"), url, major, minor, "QEXTCarouselElement");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTCheckBox.qml"), url, major, minor, "QEXTCheckBox");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTCircularProgressBar.qml"), url, major, minor, "QEXTCircularProgressBar");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTCollapse.qml"), url, major, minor, "QEXTCollapse");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTCollapseElement.qml"), url, major, minor, "QEXTCollapseElement");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTDialog.qml"), url, major, minor, "QEXTDialog");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTDialogButton.qml"), url, major, minor, "QEXTDialogButton");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTDividerLine.qml"), url, major, minor, "QEXTDividerLine");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTFpsMonitor.qml"), url, major, minor, "QEXTFpsMonitor");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTIcon.qml"), url, major, minor, "QEXTIcon");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTIconButton.qml"), url, major, minor, "QEXTIconButton");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTInputField.qml"), url, major, minor, "QEXTInputField");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTMask.qml"), url, major, minor, "QEXTMask");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTMoveArea.qml"), url, major, minor, "QEXTMoveArea");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTNavigationBar.qml"), url, major, minor, "QEXTNavigationBar");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTNavigationElement.qml"), url, major, minor, "QEXTNavigationElement");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTObject.qml"), url, major, minor, "QEXTObject");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTPagination.qml"), url, major, minor, "QEXTPagination");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTProgressBar.qml"), url, major, minor, "QEXTProgressBar");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTRadioButton.qml"), url, major, minor, "QEXTRadioButton");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTResizeArea.qml"), url, major, minor, "QEXTResizeArea");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTRoundRectangle.qml"), url, major, minor, "QEXTRoundRectangle");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTScrollbarH.qml"), url, major, minor, "QEXTScrollbarH");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTScrollbarV.qml"), url, major, minor, "QEXTScrollbarV");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTSplitView.qml"), url, major, minor, "QEXTSplitView");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTSVGIcon.qml"), url, major, minor, "QEXTSVGIcon");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTSwitch.qml"), url, major, minor, "QEXTSwitch");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTTag.qml"), url, major, minor, "QEXTTag");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTWindow.qml"), url, major, minor, "QEXTWindow");
    qmlRegisterType(QUrl("qrc:/QEXTQuick/control/QEXTWindowTitleBar.qml"), url, major, minor, "QEXTWindowTitleBar");

    qmlRegisterSingletonType(QUrl("qrc:/QEXTQuick/control/QEXTToast.qml"), url, major, minor, "QEXTToast");
}

void QEXTQuick::initQmlEngine(QQmlEngine *engine, const char *uri)
{
    Q_D(QEXTQuick);
    Q_UNUSED(uri)
    d->m_qmlEngine = engine;
    QFontDatabase::addApplicationFont(":/QEXTQuick/font/fontawesome-webfont.ttf");
    d->m_qmlEngine->rootContext()->setContextProperty("qextRootWindow", QEXT_DECL_NULLPTR);
}

void QEXTQuick::initQuickRoot(QQuickWindow *rootWindow)
{
    Q_D(QEXTQuick);
    if (!d->m_rootWindow.isNull())
    {
        return;
    }
    d->m_rootWindow = rootWindow;
    d->m_qmlEngine->rootContext()->setContextProperty("qextRootWindow", rootWindow);
}

void QEXTQuick::initWorld(QEXTQuickWorld *world)
{
    Q_D(QEXTQuick);
    d->m_quickWorld = world;
}

int QEXTQuick::mouseAreaCursorShape() const
{
    Q_D(const QEXTQuick);
    return (int)d->m_mouseAreaCurrsor;
}

void QEXTQuick::setMouseAreaCursorShape(const Qt::CursorShape &cursor)
{
    Q_D(QEXTQuick);
    d->m_mouseAreaCurrsor = cursor;
}
