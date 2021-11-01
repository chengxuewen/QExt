#include "qtkcmlogtracker_p.h"

#include <QDateTime>

QTKCMLogTracker::QTKCMLogTracker(QTKPluginContext* context, QIODevice* out)
    : QTKServiceTracker<QTKLogService*>(context), out(out), logLevel(std::numeric_limits<int>::max())
{

}

int QTKCMLogTracker::getLogLevel() const
{
    return logLevel;
}

QTKLogService* QTKCMLogTracker::addingService(const QTKServiceReference& reference)
{
    QTKLogService* service = getService(reference);
    if (logLevel == std::numeric_limits<int>::max() ||
            service->getLogLevel() > logLevel)
    {
        logLevel = service->getLogLevel();
    }
    return service;
}

void QTKCMLogTracker::removedService(const QTKServiceReference& reference, QTKLogService* service)
{
    logLevel = std::numeric_limits<int>::max();

    QList<QTKLogService*> services = getServices();
    foreach (QTKLogService* s, services)
    {
        if (s == service) continue;
        if (logLevel == std::numeric_limits<int>::max() ||
                s->getLogLevel() > logLevel)
        {
            logLevel = s->getLogLevel();
        }
    }

    QTKServiceTracker<QTKLogService*>::removedService(reference, service);
}

void QTKCMLogTracker::log(int level, const QString& message, const std::exception* exception,
                          const char* file, const char* function, int line)
{
    logToAll(QTKServiceReference(), level, message, exception, file, function, line);
}

void QTKCMLogTracker::log(const QTKServiceReference& reference, int level, const QString& message,
                          const std::exception* exception, const char* file, const char* function, int line)
{
    logToAll(reference, level, message, exception, file, function, line);
}

void QTKCMLogTracker::logToAll(const QTKServiceReference& reference, int level, const QString& message,
                               const std::exception* exception, const char* file, const char* function, int line)
{
    QMutexLocker lock(&mutex);
    QList<QTKServiceReference> references = getServiceReferences();

    if (!references.isEmpty())
    {
        foreach (QTKServiceReference ref, references)
        {
            QTKLogService* service = getService(ref);
            if (service != 0)
            {
                try
                {
                    service->log(reference, level, message, exception, file, function, line);
                }
                catch (...)
                {
                    // TODO: consider printing to System Error
                }
            }
        }
        return;
    }

    noLogService(reference, level, message, exception, file, function, line);
}

void QTKCMLogTracker::noLogService(const QTKServiceReference& reference, int level, const QString& message,
                                   const std::exception* exc, const char* file, const char* function, int line)
{
    Q_UNUSED(reference)

    QString timestamp = QDateTime::currentDateTime().toString();

    out << timestamp;

    if (level == QTKLogService::LOG_DEBUG)
    {
        out << " Debug";
    }
    else if (level == LOG_INFO)
    {
        out << " Info";
    }
    else if (level == LOG_WARNING)
    {
        out << " Warning";
    }
    else if (level == LOG_ERROR)
    {
        out << " Error";
    }
    else
    {
        out << "[Unknown Log Level]";
    }

    out << ": " << message << '\n';

    if (reference)
    {
        out << reference << '\n';
    }

    if (exc)
    {
        out << exc->what() << '\n';
    }

    if (file || function)
    {
        out << "in " << function << ", " << file << ":" << line << '\n';
    }

    out.flush();
}
