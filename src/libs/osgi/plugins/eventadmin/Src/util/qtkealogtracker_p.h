#ifndef QTKEALOGTRACKER_P_H
#define QTKEALOGTRACKER_P_H

#include <QTKPluginFramework/Service/Log/QTKLogService>
#include <QTKPluginFramework/QTKServiceTracker>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKEALogTracker : public QTKServiceTracker<QTKLogService*>, public QTKLogService
{
public:
    QTKEALogTracker(QTKPluginContext *pContext, QIODevice *pOut);

    void log(int iLevel, const QString &strMessage, const std::exception *pException = 0,
             const char *pFile = nullptr, const char *pFunction = nullptr, int iLine = -1);

    void log(const QTKServiceReference &serviceRef, int iLevel, const QString &strMessage,
             const std::exception *pException = nullptr,
             const char *pFile = nullptr, const char *pFunction = nullptr, int iLine = -1);

    int getLogLevel() const;

protected:
    QTKLogService *addingService(const QTKServiceReference &serviceRef);
    void removedService(const QTKServiceReference &serviceRef, QTKLogService *pService);

private:
    void logToAll(const QTKServiceReference &serviceRef, int iLevel, const QString &strMessage,
                  const std::exception *pException, const char *pFile, const char *pFunction, int iLine);

    void noLogService(const QTKServiceReference &serviceRef, int iLevel, const QString &strMessage,
                      const std::exception *pException, const char *pFile, const char *pFunction, int iLine);

    /** Output device to use if QTKLogService is unavailable */
    QTextStream m_outTextStream;
    mutable QMutex m_mutex;
    int m_iLogLevel;
};

#endif // QTKEALOGTRACKER_P_H
