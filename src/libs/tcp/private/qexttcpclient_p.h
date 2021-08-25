#ifndef QEXTTCPCLIENT_P_H
#define QEXTTCPCLIENT_P_H

#include <qextobject_p.h>

#include <qexttcpglobal.h>
#include <qexttcpclientproxy_p.h>
#include <qexttcpclientsocket.h>

#include <QScopedPointer>
#include <QSharedPointer>
#include <QThread>
#include <QMutex>
#include <QMap>



class QEXTTcpClientProxy;
class QEXTTcpAbstractPacketDispatcher;
class QEXTTcpAbstractTaskPool;
class QEXTTcpAbstractPacketParser;
class QEXTTcpClient;
class QEXT_TCP_API QEXTTcpClientPrivate : public QEXTTcpClientProxyPrivate
{
public:
    QEXTTcpClientPrivate(QEXTTcpClient *qq);
    ~QEXTTcpClientPrivate();

    void initClient(QEXTTcpClient *client);
    void handleProxyConnect(QEXTTcpClientProxy *proxy, bool connect);

    QScopedPointer<QThread> m_socketThread;
    QMap<QString, QEXTTcpClientProxy *> m_proxyNameMap;
    QScopedPointer<QEXTTcpAbstractPacketDispatcher> m_packetDispatcher;
    QScopedPointer<QThread> m_packetDispatcherThread;

private:
    QEXT_DECL_PUBLIC(QEXTTcpClient)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpClientPrivate)
};



#endif // QEXTTCPCLIENT_P_H
