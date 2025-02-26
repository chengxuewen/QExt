#ifndef _QEXTTCPTASK_H
#define _QEXTTCPTASK_H

#include <qextTcpGlobal.h>
#include <qextTcpPacketParserInterface.h>
#include <qextTcpPacketTransceiver.h>
#include <qextTcpPacketDispatcher.h>
#include <qextTcpSocket.h>

#include <QRunnable>

class QExtTcpTaskPrivate;
class QEXT_TCP_API QExtTcpTask : public QObject, public QRunnable
{
    Q_OBJECT
    Q_DISABLE_COPY(QExtTcpTask)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtTcpTask)
public:
    QExtTcpTask(const QSharedPointer<QExtTcpPacketTransceiver> &transceiver);
    QExtTcpTask(const QSharedPointer<QExtTcpPacketTransceiver> &transceiver,
                const QSharedPointer<QExtTcpPacketInterface> &packet);
    QExtTcpTask(QExtTcpTaskPrivate *d,
                const QSharedPointer<QExtTcpPacketTransceiver> &transceiver);
    QExtTcpTask(QExtTcpTaskPrivate *d,
                const QSharedPointer<QExtTcpPacketTransceiver> &transceiver,
                const QSharedPointer<QExtTcpPacketInterface> &packet);
    ~QExtTcpTask();

    QSharedPointer<QExtTcpPacketInterface> receivedPacket() const;
    QSharedPointer<QExtTcpPacketTransceiver> packetTransceiver() const;
    QDateTime timestamp() const;

    quint64 id() const;
    QExtTag identityId() const;

    bool isFinished() const;
    bool isErrored() const;
    QString errorString() const;

    virtual QExtTag typeId() const;
    void run() QEXT_OVERRIDE;

Q_SIGNALS:
    void aboutToBeDelete(quint64 id);
    void error(const QString &err);

protected:
    void setErrorString(const QString &string);

    QScopedPointer<QExtTcpTaskPrivate> dd_ptr;
};


class QEXT_TCP_API QExtTcpPostBackTask : public QExtTcpTask
{
public:
    QExtTcpPostBackTask(const QSharedPointer<QExtTcpPacketTransceiver> &transceiver, const QSharedPointer<QExtTcpPacketInterface> &packet);
    QExtTcpPostBackTask(QExtTcpTaskPrivate *d, const QSharedPointer<QExtTcpPacketTransceiver> &transceiver, const QSharedPointer<QExtTcpPacketInterface> &packet);
    ~QExtTcpPostBackTask();

    QExtTag typeId() const QEXT_OVERRIDE;
    void run() QEXT_OVERRIDE;
};

#endif // _QEXTTCPTASK_H
