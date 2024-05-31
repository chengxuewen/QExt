#include <private/qextQml_p.h>
#include <qextQmlWorld.h>
#include <qextQmlGlobal.h>
#include <qextQmlConfig.h>

#include <QDebug>
#include <QMutex>
#include <QQmlContext>
#include <QMutexLocker>

inline void initMyResource()
{
    Q_INIT_RESOURCE(qextQml);
}

namespace MyNamespace
{
void myFunction()
{
    initMyResource();
}
}


QExtQmlPrivate::QExtQmlPrivate(QExtQml *q)
    : q_ptr(q)
{
    m_mouseAreaCurrsor = Qt::ArrowCursor;
}

QExtQmlPrivate::~QExtQmlPrivate()
{

}



static QExtQml *sg_instance = nullptr;

QExtQml::QExtQml(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQmlPrivate(this))
{

}

QExtQml::~QExtQml()
{

}

QObject *QExtQml::qmlSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return QExtQml::instance();
}

QExtQml *QExtQml::instance()
{
    static QMutex mutex;
    QMutexLocker mutexLocker(&mutex);
    if (nullptr == sg_instance)
    {
        sg_instance = new QExtQml;
    }
    return sg_instance;
}

QString QExtQml::version() const
{
    return QString("%1.%2").arg(QEXT_QML_PLUGIN_VERSION_MAJOR).arg(QEXT_QML_PLUGIN_VERSION_MINOR);
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

void QExtQml::registerTypes(const char *url)
{
    Q_ASSERT(url == QLatin1String(QEXT_QML_PLUGIN_NAME));
    //    Q_INIT_RESOURCE(qextQml);
    //    MyNamespace::myFunction();

    int major = QEXT_QML_PLUGIN_VERSION_MAJOR;
    int minor = QEXT_QML_PLUGIN_VERSION_MINOR;

    qmlRegisterSingletonType<QExtQml>(url, major, minor, "QExtQml", QExtQml::qmlSingletonTypeProvider);
    qmlRegisterType<QExtQmlWorld>( url, major, minor, "QExtQmlWorld");
}

void QExtQml::initQmlEngine(QQmlEngine *engine, const char *uri)
{
    Q_D(QExtQml);
    Q_UNUSED(uri)
    d->m_qmlEngine = engine;
    QFontDatabase::addApplicationFont(":/QExtQml/font/fontawesome-webfont.ttf");
    d->m_qmlEngine->rootContext()->setContextProperty("qextRootWindow", QEXT_NULLPTR);
}

void QExtQml::initQuickRoot(QQuickWindow *rootWindow)
{
    Q_D(QExtQml);
    if (!d->m_rootWindow.isNull())
    {
        return;
    }
    d->m_rootWindow = rootWindow;
    d->m_qmlEngine->rootContext()->setContextProperty("qextRootWindow", rootWindow);
}

void QExtQml::initWorld(QExtQmlWorld *world)
{
    Q_D(QExtQml);
    d->m_quickWorld = world;
}

int QExtQml::mouseAreaCursorShape() const
{
    Q_D(const QExtQml);
    return (int)d->m_mouseAreaCurrsor;
}

void QExtQml::setMouseAreaCursorShape(const Qt::CursorShape &cursor)
{
    Q_D(QExtQml);
    d->m_mouseAreaCurrsor = cursor;
}
