#ifndef QTKEVENTBUSIMPL_H
#define QTKEVENTBUSIMPL_H

#include "qtkeventadminbus.h"
#include "qtkeventbusmanager.h"

#include <QList>
#include <QHash>
#include <QSet>

class QTKEventHandlerWrapper;

class QTKEventBusImpl : public QObject, public QTKEventAdminBus
{
    Q_OBJECT
    Q_INTERFACES(QTKEventAdminBus)

public:
    QTKEventBusImpl();

    void postEvent(const QTKEvent &event) Q_DECL_OVERRIDE;

    void sendEvent(const QTKEvent &event) Q_DECL_OVERRIDE;

    void publishSignal(const QObject *pPublisher, const char *pSignal,
                       const QString &strTopic,
                       Qt::ConnectionType eType = Qt::QueuedConnection) Q_DECL_OVERRIDE;

    void unpublishSignal(const QObject *pPublisher, const char *pSignal = 0,
                         const QString &strTopic = "") Q_DECL_OVERRIDE;

    qlonglong subscribeSlot(const QObject *pSubscriber, const char *pMember,
                            const QTKDictionary &properties,
                            Qt::ConnectionType eType = Qt::AutoConnection) Q_DECL_OVERRIDE;

    void unsubscribeSlot(qlonglong llSubscriptionId) Q_DECL_OVERRIDE;

    bool updateProperties(qlonglong llSubsriptionId, const QTKDictionary &properties) Q_DECL_OVERRIDE;

    bool createServer(const QString &strCommunicationProtocol, unsigned int ulListenPort) Q_DECL_OVERRIDE;
    void startListen() Q_DECL_OVERRIDE;
    bool createClient(const QString &strCommunicationProtocol, const QString &strServerHost, unsigned int uiPort) Q_DECL_OVERRIDE;

protected:
    void dispatchEvent(const QTKEvent &event, bool bIsAsync);

private:
    qtkeventbus::QTKEventBusManager *m_pEventBusManager;
};

#endif // QTKEVENTBUSIMPL_H
