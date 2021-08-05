#ifndef QEXTTCPCLIENTPROXY_P_H
#define QEXTTCPCLIENTPROXY_P_H

#include <qextobject_p.h>

#include <qexttcpglobal.h>

#include <QMutex>
#include <QWaitCondition>
#include <QQueue>
#include <QHash>
#include <QPointer>



class QEXTTcpClientSocket;
class QEXTTcpAbstractPacketParser;
class QEXTTcpAbstractPacket;
class QEXTTcpClientProxy;
class QEXT_TCP_API QEXTTcpClientProxyPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpClientProxyPrivate(QEXTTcpClientProxy *qq);
    ~QEXTTcpClientProxyPrivate();

    bool waitForReply(int msecs);
    void setRequestFlag(QEXTTcpAbstractPacket *send);
    void setSyncRequestReplyFlag(QEXTTcpAbstractPacket *reply);

    QString m_name;
    QPointer<QEXTTcpClientSocket> m_socket;
    mutable QMutex m_mutex;
    QWaitCondition m_syncRequestWaitCondition;
    bool m_syncRequestReplyReceived;
    bool m_syncRequestWaitCancelled;
    QScopedPointer<QEXTTcpAbstractPacket> m_sendPacket;
    QEXTTcpAbstractPacket *m_syncRequestReplyPacket;
    QScopedPointer<QEXTTcpAbstractPacketParser> m_packetParser;

    mutable QMutex m_packetQueueMutex;
    QQueue<QEXTTcpAbstractPacket *> m_receivedPacketQueue;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpClientProxy)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpClientProxyPrivate)
};



#endif // QEXTTCPCLIENTPROXY_P_H
