#ifndef QEXTTCPCLIENT_P_H
#define QEXTTCPCLIENT_P_H

#include <qextobject_p.h>

#include <qextnetworkglobal.h>
#include <qexttcpclientproxy_p.h>
#include <qexttcpclientsocket.h>

#include <QScopedPointer>
#include <QSharedPointer>
#include <QThread>
#include <QMutex>
#include <QMap>

class QEXTTcpClientProxy;
class QEXTTcpPacketDispatcherBase;
class QEXTTcpTaskPoolBase;
class QEXTTcpPacketParserBase;
class QEXTTcpClient;
class QEXT_NETWORK_API QEXTTcpClientPrivate : public QEXTTcpClientProxyPrivate
{
public:
    QEXTTcpClientPrivate(QEXTTcpClient *qq);
    ~QEXTTcpClientPrivate();

    void initClient(QEXTTcpClient *client);
    void handleProxyConnect(QEXTTcpClientProxy *proxy, bool connect);

    QScopedPointer<QThread> m_socketThread;
    QMap<QString, QEXTTcpClientProxy *> m_proxyNameMap;
    QScopedPointer<QEXTTcpPacketDispatcherBase> m_packetDispatcher;
    QScopedPointer<QThread> m_packetDispatcherThread;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpClient)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpClientPrivate)
};

#endif // QEXTTCPCLIENT_P_H
