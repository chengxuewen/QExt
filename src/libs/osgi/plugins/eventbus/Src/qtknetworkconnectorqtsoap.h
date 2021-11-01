#ifndef QTKNETWORKCONNECTORQTSOAP_H
#define QTKNETWORKCONNECTORQTSOAP_H

#include "qtknetworkconnector.h"

#include <QTKSOAP/QTKSoapType>
#include <QTKSOAP/QTKSoapHttpTransport>
#include <QTKSOAP/QTKSoapMessage>

QTK_SOAP_USE_NAMESPACE

namespace qtkeventbus {

class QTK_EVENTBUS_EXPORT QTKNetworkConnectorQtSoap : public QTKNetworkConnector
{
    Q_OBJECT
public:
    QTKNetworkConnectorQtSoap();
    ~QTKNetworkConnectorQtSoap();

    void createClient(const QString strHostName, const unsigned int uiPort);

    void setWSDL(const QString strWsdlUrl);
    void setAction(const QString strAction);
    void setPath(const QString strPath);
    void registerNamespace(QString strPrefix, QString strNamespaceURI);

    void createServer(const unsigned int uiPort);
    void startListen();
    void send(const QString strMethodName, QTKEventArgumentsList *pArgList);

    QTKSoapType *marshall(const QString strName, const QVariant &parameter);
    QTKSoapType *response();

    void initializeForEventBus();
    virtual QTKNetworkConnector *clone();

Q_SIGNALS:
    void registerMethodsServer(mafRegisterMethodsMap registerMethodsList);

public Q_SLOTS:
    void registerServerMethod(QString strMethodName, QList<QVariant::Type> types);

private Q_SLOTS:
    void retrieveRemoteResponse();

private:
    void stopServer();

    QTKSoapHttpTransport *m_pHttp; ///< variable that represents the soap request from client to server
    QTKSoapMessage m_Request; ///< variable that represents the request
    mafRegisterMethodsMap m_mapRegisterMethods;
    QString m_strWSDLUrl; ///< represents the url of the wsdl
    QString m_strAction; ///< represents the action to put inside transport http
    QString m_strPath; ///< represents the path (for example the endpoint)
    QTKSoapType *m_pResponse;
};

inline void QTKNetworkConnectorQtSoap::setWSDL(const QString strWsdlUrl) {
    m_strWSDLUrl = strWsdlUrl;
}

inline void QTKNetworkConnectorQtSoap::setAction(const QString strAction) {
    m_strAction = strAction;
}

inline void QTKNetworkConnectorQtSoap::setPath(const QString strPath) {
    m_strPath = strPath;
}

inline QTKSoapType *QTKNetworkConnectorQtSoap::response() {
    return m_pResponse;
}

inline void QTKNetworkConnectorQtSoap::registerNamespace(QString strPrefix, QString strNamespaceURI) {
    m_Request.useNamespace(strPrefix, strNamespaceURI);
}

} //namespace qtkeventbus

#endif // QTKNETWORKCONNECTORQTSOAP_H
