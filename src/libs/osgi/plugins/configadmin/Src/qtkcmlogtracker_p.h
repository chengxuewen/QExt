#ifndef QTKCMLOGTRACKER_P_H
#define QTKCMLOGTRACKER_P_H

#include <QTKPluginFramework/QTKServiceTracker>
#include <QTKPluginFramework/Service/Log/QTKLogService>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKCMLogTracker : public QTKServiceTracker<QTKLogService*>, public QTKLogService
{
public:
    QTKCMLogTracker(QTKPluginContext* context, QIODevice* out);

    void log(int level, const QString& message, const std::exception* exception = 0,
             const char* file = 0, const char* function = 0, int line = -1);

    void log(const QTKServiceReference& sr, int level, const QString& message,
             const std::exception* exception = 0,
             const char* file = 0, const char* function = 0, int line = -1);

    int getLogLevel() const;

protected:

    QTKLogService* addingService(const QTKServiceReference& reference);

    void removedService(const QTKServiceReference& reference, QTKLogService* service);

private:

    void logToAll(const QTKServiceReference& reference, int level, const QString& message,
                  const std::exception* exception, const char* file, const char* function, int line);

    /**
   * The QTKLogService is not available so we write the message to a QTextStream.
   *
   * @param reference QTKServiceReference associated with message or a default constructed one if none.
   * @param level Logging level.
   * @param message Log message.
   * @param exc Log exception or null if none.
   * @param file The file name where the log message came from.
   * @param function The function where the log message came from.
   * @param The line number where the log message came from.
   */
    void noLogService(const QTKServiceReference& reference, int level, const QString& message,
                      const std::exception* exc, const char* file, const char* function, int line);

    /** Output device to use if QTKLogService is unavailable */
    QTextStream out;

    QMutex mutex;

    int logLevel;
};

#endif // QTKCMLOGTRACKER_P_H
