#include <qextVLC.h>
#include <qextVLCError.h>
#include <qextVLCInstance.h>
#include <qextVLCModuleDescription.h>
#include <qextVLCConfig.h>

#include <QtCore/QDebug>
#include <QtCore/QStringList>

#include <vlc/vlc.h>

#ifdef Q_OS_WIN
#include "compat/asprintf.h"
#endif

void logCallback(void *data,
                 int level,
                 const libvlc_log_t *ctx,
                 const char *fmt,
                 va_list args)
{
    Q_UNUSED(ctx)

    QEXTVLCInstance *instance = static_cast<QEXTVLCInstance *>(data);
    if (instance->logLevel() > level) {
        return;
    }

    char *result;
    if (vasprintf(&result, fmt, args) < 0) {
        return; // LCOV_EXCL_LINE
    }

    QString message(result);
    free(result);
    //    QString message;

    message.prepend("libvlc: ");

    switch (level) {
    case QEXTVLC::LogLevel_Error:
        qCritical(message.toUtf8().data(), NULL);
        break;
    case QEXTVLC::LogLevel_Warning:
        qWarning(message.toUtf8().data(), NULL);
        break;
    case QEXTVLC::LogLevel_Notice:
    case QEXTVLC::LogLevel_Debug:
    default:
        qDebug(message.toUtf8().data(), NULL);
        break;
    }
}


class QEXTVLCInstancePrivate
{
public:
    explicit QEXTVLCInstancePrivate(QEXTVLCInstance *q);
    virtual ~QEXTVLCInstancePrivate();

    QEXTVLCInstance * const q_ptr;

    libvlc_instance_t *m_vlcInstance;
    bool m_status;
    QEXTVLC::LogLevelType m_logLevel;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTVLCInstancePrivate)
    QEXT_DECL_PUBLIC(QEXTVLCInstance)
};

QEXTVLCInstancePrivate::QEXTVLCInstancePrivate(QEXTVLCInstance *q)
    : q_ptr(q)
    , m_vlcInstance(NULL)
    , m_status(false)
    , m_logLevel(QEXTVLC::LogLevel_Error)
{

}

QEXTVLCInstancePrivate::~QEXTVLCInstancePrivate()
{
    if (m_status && m_vlcInstance)
    {
        libvlc_release(m_vlcInstance);
    }
}



QEXTVLCInstance::QEXTVLCInstance(const QStringList &args, QObject *parent)
    : QObject(parent)
    , dd_ptr(new QEXTVLCInstancePrivate(this))
{
    Q_D(QEXTVLCInstance);
    // Convert arguments to required format
#if defined(Q_OS_WIN32) // Will be removed on Windows if confirmed working
    char **argv = (char **)malloc(sizeof(char **) * args.count());
    for (int i = 0; i < args.count(); ++i)
    {
        argv[i] = (char *)qstrdup(args.at(i).toUtf8().data());
    }
#else
    char *argv[args.count()];
    for (int i = 0; i < args.count(); ++i)
    {
        argv[i] = (char *)qstrdup(args.at(i).toUtf8().data());
    }
#endif

    // Create new libvlc instance
    d->m_vlcInstance = libvlc_new(args.count(), argv);

    qRegisterMetaType<QEXTVLC::MetaType>("QEXTVLC::MetaType");
    qRegisterMetaType<QEXTVLC::StateType>("QEXTVLC::StateType");

    QEXTVLCError::showErrMsg();

    // Check if instance is running
    if (d->m_vlcInstance)
    {
        libvlc_log_set(d->m_vlcInstance, logCallback, this);
        d->m_status = true;
        qDebug() << "Using libvlc version:" << this->version();
    } else {
        qCritical() << "VLC-Qt Error: libvlc failed to load!";
    }
}

QEXTVLCInstance::~QEXTVLCInstance()
{

}

libvlc_instance_t *QEXTVLCInstance::core()
{
    Q_D(QEXTVLCInstance);
    return d->m_vlcInstance;
}

bool QEXTVLCInstance::status() const
{
    Q_D(const QEXTVLCInstance);
    return d->m_status;
}

QEXTVLC::LogLevelType QEXTVLCInstance::logLevel() const
{
    Q_D(const QEXTVLCInstance);
    return d->m_logLevel;
}

void QEXTVLCInstance::setLogLevel(QEXTVLC::LogLevelType level)
{
    Q_D(QEXTVLCInstance);
    d->m_logLevel = level;
}

QString QEXTVLCInstance::changeset()
{
    // Returns libvlc changeset
    return QString(libvlc_get_changeset());
}

QString QEXTVLCInstance::compiler()
{
    // Returns libvlc compiler version
    return QString(libvlc_get_compiler());
}

QString QEXTVLCInstance::version()
{
    // Returns libvlc version
    return QString(libvlc_get_version());
}

void QEXTVLCInstance::setUserAgent(const QString &application, const QString &version)
{
    Q_D(QEXTVLCInstance);
    QString applicationOutput = application + " " + version;
    QString httpOutput = application + "/" + version + "/QEXTVLC"; // "AppName/1.2.3/QEXTVLC"
    libvlc_set_user_agent(d->m_vlcInstance, applicationOutput.toUtf8().data(), httpOutput.toUtf8().data());
}

void QEXTVLCInstance::setAppId(const QString &id, const QString &version, const QString &icon)
{
    Q_D(QEXTVLCInstance);
    libvlc_set_app_id(d->m_vlcInstance, id.toUtf8().data(), version.toUtf8().data(), icon.toUtf8().data());
}

QList<QEXTVLCModuleDescription *> QEXTVLCInstance::audioFilterList() const
{
    Q_D(const QEXTVLCInstance);
    libvlc_module_description_t *original = libvlc_audio_filter_list_get(d->m_vlcInstance);
    if (NULL == original)
    {
        return QList<QEXTVLCModuleDescription *>(); // LCOV_EXCL_LINE
    }

    libvlc_module_description_t *list = original;
    QList<QEXTVLCModuleDescription *> audioFilters;
    do {
        QEXTVLCModuleDescription *module = new QEXTVLCModuleDescription(QEXTVLCModuleDescription::AudioFilter, list->psz_name);
        module->setLongName(list->psz_longname);
        module->setShortName(list->psz_shortname);
        module->setHelp(list->psz_help);
        audioFilters << module;

        list = list->p_next;
    } while (list->p_next);

    libvlc_module_description_list_release(original);

    return audioFilters;
}

QList<QEXTVLCModuleDescription *> QEXTVLCInstance::videoFilterList() const
{
    Q_D(const QEXTVLCInstance);
    libvlc_module_description_t *original = libvlc_video_filter_list_get(d->m_vlcInstance);
    if (NULL == original)
    {
        return QList<QEXTVLCModuleDescription *>(); // LCOV_EXCL_LINE
    }

    libvlc_module_description_t *list = original;
    QList<QEXTVLCModuleDescription *> videoFilters;
    do {
        QEXTVLCModuleDescription *module = new QEXTVLCModuleDescription(QEXTVLCModuleDescription::VideoFilter, list->psz_name);
        module->setLongName(list->psz_longname);
        module->setShortName(list->psz_shortname);
        module->setHelp(list->psz_help);
        videoFilters << module;

        list = list->p_next;
    } while (list->p_next);

    libvlc_module_description_list_release(original);

    return videoFilters;
}
