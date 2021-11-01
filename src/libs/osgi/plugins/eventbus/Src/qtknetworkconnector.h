#ifndef QTKNETWORKCONNECTOR_H
#define QTKNETWORKCONNECTOR_H

#include "qtkeventdefinitions.h"

namespace qtkeventbus {

class QTK_EVENTBUS_EXPORT QTKNetworkConnector : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString protocol READ protocol)

public:
    QTKNetworkConnector();

    virtual void createClient(const QString strHostName, const unsigned int uiPort) = 0;
    virtual void createServer(const unsigned int uiPort) = 0;
    virtual void startListen() = 0;
    virtual void send(const QString strEventId, QTKEventArgumentsList *pArgList) = 0;
    virtual QTKNetworkConnector *clone() = 0;
    virtual void initializeForEventBus() = 0;

    QString protocol();

Q_SIGNALS:
    void remoteCommunication(const QString strEventId, QTKEventArgumentsList *pArgList);

protected:
    QString m_strProtocol; ///< define the protocol of the connector (xmlrpc, soap, etc...)
};

} //namespace QTKEventBus

#endif // QTKNETWORKCONNECTOR_H
