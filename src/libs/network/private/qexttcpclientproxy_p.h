#ifndef QEXTTCPCLIENTPROXY_P_H
#define QEXTTCPCLIENTPROXY_P_H

#include <qextobject_p.h>

#include <qextnetworkglobal.h>

#include <QMutex>
#include <QWaitCondition>
#include <QQueue>
#include <QHash>
#include <QPointer>

class QEXTTcpClientSocket;
class QEXTTcpPacketParserBase;
class QEXTTcpPacketBase;
class QEXTTcpClientProxy;
class QEXT_NETWORK_API QEXTTcpClientProxyPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpClientProxyPrivate(QEXTTcpClientProxy *qq);
    ~QEXTTcpClientProxyPrivate();

    bool waitForReply(int msecs);
    void setRequestFlag(QEXTTcpPacketBase *send);
    void setSyncRequestReplyFlag(QEXTTcpPacketBase *reply);

    QString m_name;
    QPointer<QEXTTcpClientSocket> m_socket;
    mutable QMutex m_mutex;
    QWaitCondition m_syncRequestWaitCondition;
    bool m_syncRequestReplyReceived;
    bool m_syncRequestWaitCancelled;
    QScopedPointer<QEXTTcpPacketBase> m_sendPacket;
    QEXTTcpPacketBase *m_syncRequestReplyPacket;
    QScopedPointer<QEXTTcpPacketParserBase> m_packetParser;

    mutable QMutex m_packetQueueMutex;
    QQueue<QEXTTcpPacketBase *> m_receivedPacketQueue;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpClientProxy)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpClientProxyPrivate)
};

#endif // QEXTTCPCLIENTPROXY_P_H
