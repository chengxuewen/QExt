#include <qextQuick.h>
#include <qextQuick_p.h>

#include <QFontDatabase>
#include <QMutex>
#include <QMutexLocker>
#include <QFontDatabase>
#include <QQmlContext>
#include <QDebug>

inline void initMyResource() { Q_INIT_RESOURCE(QEXTQuick); }

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



static QEXTQuick *sg_instance = QEXT_DECL_NULLPTR;

QEXTQuick::QEXTQuick(QObject *parent)
    : QObject(parent), d_ptr(new QEXTQuickPrivate(this))
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
    if (nullptr == sg_instance) {
        sg_instance = new QEXTQuick;
    }
    return sg_instance;
}

QEXTQuick::~QEXTQuick()
{

}

QString QEXTQuick::version() const
{
    return QString("%1.%2").arg(QEXTQUICK_VERSION_MAJOR).arg(QEXTQUICK_VERSION_MINOR);
}

QString QEXTQuick::stateToString(int state) const
{
    Q_UNUSED(state);
    //    switch (state) {
    //    case State_None: return "";
    //    case State_Normal: return "Normal";
    //    case State_Hovered: return "Hovered";
    //    case State_Pressed: return "Pressed";
    //    case State_Checked: return "Checked";
    //    case State_Unchecked: return "Unchecked";
    //    case State_PartiallyChecked: return "PartiallyChecked";
    //    default: break;
    //    }
    return "";
}

int QEXTQuick::stateToEnum(const QString &state) const
{
    Q_UNUSED(state);
    //    if (state == "") {
    //        return State_None;
    //    } else if (state == "Normal") {
    //        return State_Normal;
    //    } else if (state == "Hovered") {
    //        return State_Hovered;
    //    } else if (state == "Pressed") {
    //        return State_Pressed;
    //    } else if (state == "Checked") {
    //        return State_Checked;
    //    } else if (state == "Unchecked") {
    //        return State_Unchecked;
    //    } else if (state == "PartiallyChecked") {
    //        return State_PartiallyChecked;
    //    } else {
    //        return -1;
    //    }
    return -1;
}

void QEXTQuick::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String(QEXTQUICK_NAME));
    //    Q_INIT_RESOURCE(QEXTQuick);
    MyNamespace::myFunction();

    int major = QEXTQUICK_VERSION_MAJOR;
    int minor = QEXTQUICK_VERSION_MINOR;

    qmlRegisterSingletonType<QEXTQuick>(uri, major, minor, "QEXTQuick", QEXTQuick::qmlSingletonTypeProvider);

    qmlRegisterType<QEXTQuickWorld>( uri, major, minor, "QEXTQuickWorld");

}

void QEXTQuick::initQmlEngine(QQmlEngine *engine, const char *uri)
{
    Q_D(QEXTQuick);
    Q_UNUSED(uri)
    d->m_qmlEngine = engine;
    //    QFontDatabase::addApplicationFont(":/QEXTQuick/font/fontawesome-webfont.ttf");
    d->m_qmlEngine->rootContext()->setContextProperty("qextRootWindow", QEXT_DECL_NULLPTR);
}

void QEXTQuick::initQuickRoot(QQuickWindow *rootWindow)
{
    Q_D(QEXTQuick);
    if (!d->m_rootWindow.isNull()) {
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
