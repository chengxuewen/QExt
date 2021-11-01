#include "qtkealogtracker_p.h"

#include <QDateTime>

QTKEALogTracker::QTKEALogTracker(QTKPluginContext *pContext, QIODevice *pOut)
    : QTKServiceTracker<QTKLogService *>(pContext),
      m_outTextStream(pOut),
      m_iLogLevel(std::numeric_limits<int>::max())
{

}

int QTKEALogTracker::getLogLevel() const
{
    QMutexLocker lock(&m_mutex);
    return m_iLogLevel;
}

QTKLogService *QTKEALogTracker::addingService(const QTKServiceReference &serviceRef)
{
    QTKLogService *pService = this->getService(serviceRef);

    QMutexLocker lock(&m_mutex);
    if (m_iLogLevel == std::numeric_limits<int>::max() || pService->getLogLevel() > m_iLogLevel) {
        m_iLogLevel = pService->getLogLevel();
    }
    return pService;
}

void QTKEALogTracker::removedService(const QTKServiceReference &serviceRef, QTKLogService *pService)
{
    int iNewLogLevel = std::numeric_limits<int>::max();

    QList<QTKLogService *> listServices = this->getServices();
    foreach (QTKLogService *pLocalService, listServices) {
        if (pService == pLocalService) {
            continue;
        }
        if (iNewLogLevel == std::numeric_limits<int>::max() || pService->getLogLevel() > iNewLogLevel) {
            iNewLogLevel = pService->getLogLevel();
        }
    }

    {
        QMutexLocker lock(&m_mutex);
        m_iLogLevel = iNewLogLevel;
    }

    QTKServiceTracker<QTKLogService *>::removedService(serviceRef, pService);
}

void QTKEALogTracker::log(int iLevel, const QString &strMessage, const std::exception *pException,
                          const char *pFile, const char *pFunction, int iLine)
{
    this->logToAll(QTKServiceReference(), iLevel, strMessage, pException, pFile, pFunction, iLine);
}

void QTKEALogTracker::log(const QTKServiceReference &serviceRef, int iLevel, const QString &strMessage,
                          const std::exception *pException, const char *pFile, const char *pFunction, int iLine)
{
    this->logToAll(serviceRef, iLevel, strMessage, pException, pFile, pFunction, iLine);
}

void QTKEALogTracker::logToAll(const QTKServiceReference &serviceRef, int iLevel, const QString &strMessage,
                               const std::exception *pException, const char *pFile, const char *pFunction, int iLine)
{
    QList<QTKServiceReference> listReferences = getServiceReferences();

    if (!listReferences.isEmpty()) {
        foreach (QTKServiceReference ref, listReferences) {
            QTKLogService *pService = this->getService(ref);
            if (nullptr != pService) {
                try {
                    pService->log(serviceRef, iLevel, strMessage, pException, pFile, pFunction, iLine);
                } catch (...) {
                    // TODO: consider printing to System Error
                }
            }
        }
        return;
    }

    this->noLogService(serviceRef, iLevel, strMessage, pException, pFile, pFunction, iLine);
}

void QTKEALogTracker::noLogService(const QTKServiceReference &serviceRef, int iLevel, const QString &strMessage,
                                   const std::exception *pException, const char *pFile, const char *pFunction, int iLine)
{
    Q_UNUSED(serviceRef)

    QMutexLocker lock(&m_mutex);
    QString strTimestamp = QDateTime::currentDateTime().toString();

    m_outTextStream << strTimestamp;

    if (iLevel == QTKLogService::LOG_DEBUG) {
        m_outTextStream << " Debug";
    } else if (iLevel == LOG_INFO) {
        m_outTextStream << " Info";
    } else if (iLevel == LOG_WARNING) {
        m_outTextStream << " Warning";
    } else if (iLevel == LOG_ERROR) {
        m_outTextStream << " Error";
    } else {
        m_outTextStream << "[Unknown Log Level]";
    }

    m_outTextStream << ": " << strMessage << '\n';

    if (serviceRef) {
        m_outTextStream << serviceRef << '\n';
    }

    if (pException) {
        m_outTextStream << pException->what() << '\n';
    }

    if (pFile || pFunction) {
        m_outTextStream << "in " << pFunction << ", " << pFile << ":" << iLine << '\n';
    }

    m_outTextStream.flush();
}
