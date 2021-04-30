#ifndef QEXTTCPCLIENTSOCKET_P_H
#define QEXTTCPCLIENTSOCKET_P_H

#include <qexttcpsocket_p.h>

#include <QMutex>
#include <QQueue>
#include <QPointer>

class QEXTTcpPacketBase;
class QEXTTcpPacketDispatcherBase;
class QEXTTcpPacketParserBase;
class QEXTTcpClientSocket;
class QEXT_NETWORK_API QEXTTcpClientSocketPrivate : public QEXTTcpSocketPrivate
{
public:
    explicit QEXTTcpClientSocketPrivate(QEXTTcpClientSocket *qq);
    ~QEXTTcpClientSocketPrivate();

    mutable QMutex m_socketMutex;
    QString m_serverIpAddr;
    quint16 m_serverPort;

    mutable QMutex m_packetMutex;
    QQueue<QEXTTcpPacketBase *> m_sendPacketQueue;

    mutable QMutex m_packetParserMutex;
    QScopedPointer<QEXTTcpPacketParserBase> m_packetParser;

    mutable QMutex m_packetDispatcherMutex;
    QPointer<QEXTTcpPacketDispatcherBase> m_packetDispatcher;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpClientSocket)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpClientSocketPrivate)
};

#endif // QEXTTCPCLIENTSOCKET_P_H
