#ifndef QTKLOGQDEBUG_P_H
#define QTKLOGQDEBUG_P_H

#include <QTKPluginFramework/Service/Log/QTKLogService>

#include <QObject>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKLogQDebug : public QObject, public QTKLogService
{

    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKLogService)

public:
    QTKLogQDebug();

    void log(int level, const QString& message, const std::exception* exception = 0,
             const char* file = 0, const char* function = 0, int line = -1);
    void log(const QTKServiceReference& sr, int level, const QString& message,
             const std::exception* exception = 0,
             const char* file = 0, const char* function = 0, int line = -1);
    int getLogLevel() const;

private:

    int logLevel;
};

#endif // QTKLOGQDEBUG_P_H
