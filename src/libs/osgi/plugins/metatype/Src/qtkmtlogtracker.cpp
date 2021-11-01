#include "qtkmtlogtracker_p.h"

#include <QDateTime>

QTKMTLogTracker::QTKMTLogTracker(QTKPluginContext* context, QIODevice* out)
    : QTKServiceTracker<QTKLogService*>(context), out(out), logLevel(std::numeric_limits<int>::max())
{

}

int QTKMTLogTracker::getLogLevel() const
{
    QMutexLocker lock(&mutex);
    return logLevel;
}

QTKLogService* QTKMTLogTracker::addingService(const QTKServiceReference& reference)
{
    QTKLogService* service = getService(reference);

    QMutexLocker lock(&mutex);
    if (logLevel == std::numeric_limits<int>::max() ||
            service->getLogLevel() > logLevel)
    {
        logLevel = service->getLogLevel();
    }
    return service;
}

void QTKMTLogTracker::removedService(const QTKServiceReference& reference, QTKLogService* service)
{
    int newLogLevel = std::numeric_limits<int>::max();

    QList<QTKLogService*> services = getServices();
    foreach (QTKLogService* s, services)
    {
        if (s == service) continue;
        if (newLogLevel == std::numeric_limits<int>::max() ||
                s->getLogLevel() > newLogLevel)
        {
            newLogLevel = s->getLogLevel();
        }
    }

    {
        QMutexLocker lock(&mutex);
        logLevel = newLogLevel;
    }

    QTKServiceTracker<QTKLogService*>::removedService(reference, service);
}

void QTKMTLogTracker::log(int level, const QString& message, const std::exception* exception,
                          const char* file, const char* function, int line)
{
    logToAll(QTKServiceReference(), level, message, exception, file, function, line);
}

void QTKMTLogTracker::log(const QTKServiceReference& reference, int level, const QString& message,
                          const std::exception* exception, const char* file, const char* function, int line)
{
    logToAll(reference, level, message, exception, file, function, line);
}

void QTKMTLogTracker::logToAll(const QTKServiceReference& reference, int level, const QString& message,
                               const std::exception* exception, const char* file, const char* function, int line)
{
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

void QTKMTLogTracker::noLogService(const QTKServiceReference& reference, int level, const QString& message,
                                   const std::exception* exc, const char* file, const char* function, int line)
{
    QMutexLocker lock(&mutex);
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
