#ifndef _QEXTTCPTASK_H
#define _QEXTTCPTASK_H

#include <qextTcpGlobal.h>
#include <qextTcpPacketParserInterface.h>
#include <qextTcpPacketTransceiver.h>
#include <qextTcpPacketDispatcher.h>
#include <qextTcpSocket.h>

#include <QRunnable>

class QEXTTcpTaskPrivate;
class QEXT_TCP_API QEXTTcpTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    QEXTTcpTask(const QSharedPointer<QEXTTcpPacketTransceiver> &transceiver);
    QEXTTcpTask(const QSharedPointer<QEXTTcpPacketTransceiver> &transceiver,
                const QSharedPointer<QEXTTcpPacketInterface> &packet);
    QEXTTcpTask(QEXTTcpTaskPrivate *d,
                const QSharedPointer<QEXTTcpPacketTransceiver> &transceiver);
    QEXTTcpTask(QEXTTcpTaskPrivate *d,
                const QSharedPointer<QEXTTcpPacketTransceiver> &transceiver,
                const QSharedPointer<QEXTTcpPacketInterface> &packet);
    ~QEXTTcpTask();

    QSharedPointer<QEXTTcpPacketInterface> receivedPacket() const;
    QSharedPointer<QEXTTcpPacketTransceiver> packetTransceiver() const;
    QDateTime timestamp() const;

    quint64 id() const;
    QEXTId identityId() const;

    bool isFinished() const;
    bool isErrored() const;
    QString errorString() const;

    virtual QEXTId typeId() const;
    void run() QEXT_DECL_OVERRIDE;

Q_SIGNALS:
    void aboutToBeDelete(quint64 id);
    void error(const QString &err);

protected:
    void setErrorString(const QString &string);

    QScopedPointer<QEXTTcpTaskPrivate> d_ptr;

private:
    QEXT_DECL_PRIVATE(QEXTTcpTask)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTask)
};


class QEXT_TCP_API QEXTTcpPostBackTask : public QEXTTcpTask
{
public:
    QEXTTcpPostBackTask(const QSharedPointer<QEXTTcpPacketTransceiver> &transceiver, const QSharedPointer<QEXTTcpPacketInterface> &packet);
    QEXTTcpPostBackTask(QEXTTcpTaskPrivate *d, const QSharedPointer<QEXTTcpPacketTransceiver> &transceiver, const QSharedPointer<QEXTTcpPacketInterface> &packet);
    ~QEXTTcpPostBackTask();

    QEXTId typeId() const QEXT_DECL_OVERRIDE;
    void run() QEXT_DECL_OVERRIDE;
};

#endif // _QEXTTCPTASK_H
