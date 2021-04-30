#ifndef QEXTTCPTRANSFERTHREAD_P_H
#define QEXTTCPTRANSFERTHREAD_P_H

#include <qexttcpthreadbase_p.h>
#include <qextid.h>

#include <qextnetworkglobal.h>
#include <qexttcpserversocket.h>
#include <qexttcptransferthread.h>

#include <QDateTime>
#include <QPointer>
#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QSet>
#include <QMap>

class QEXTTcpPacketParserBase;
class QEXTTcpTransferThreadPool;
class QEXT_NETWORK_API QEXTTcpTransferThreadPrivate : public QEXTTcpThreadBasePrivate
{
public:
    explicit QEXTTcpTransferThreadPrivate(QEXTTcpTransferThread *qq);
    ~QEXTTcpTransferThreadPrivate();

    void handleSocketConnect(QEXTTcpServerSocket *socket, bool connect);

    mutable QMutex m_socketMutex;
    QSet<QEXTTcpServerSocket *> m_socketSet;
    QHash<QEXTId, QEXTTcpServerSocket *> m_socketHashMap;

    mutable QMutex m_packetMutex;
    QQueue<QEXTTcpPacketBase *> m_sendPacketQueue;

    static QMap<int, QString> sm_errorStringMap;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpTransferThread)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTransferThreadPrivate)
};

#endif // QEXTTCPTRANSFERTHREAD_P_H
