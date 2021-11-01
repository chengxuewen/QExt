#ifndef QTKMTLOGTRACKER_P_H
#define QTKMTLOGTRACKER_P_H

#include <QTKPluginFramework/Service/Log/QTKLogService>
#include <QTKPluginFramework/QTKServiceTracker>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

/**
 * This class encapsulates the QTKLogService
 * and handles all issues such as the service coming and going.
 */
class QTKMTLogTracker : public QTKServiceTracker<QTKLogService*>, public QTKLogService
{

public:

    /**
   * Create new QTKMTLogTracker.
   *
   * @param context QTKPluginContext of parent plugin.
   * @param out Default QIODevice to use if QTKLogService is unavailable.
   */
    QTKMTLogTracker(QTKPluginContext* context, QIODevice* out);

    /*
   * ----------------------------------------------------------------------
   *      LogService Interface implementation
   * ----------------------------------------------------------------------
   */

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

    mutable QMutex mutex;

    int logLevel;
};

#endif // QTKMTLOGTRACKER_P_H
