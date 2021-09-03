#ifndef QEXTTCPTASK_H
#define QEXTTCPTASK_H

#include <qextTcpGlobal.h>
#include <qextTcpPacketParserInterface.h>
#include <qextTcpPacketTransceiver.h>
#include <qextTcpPacketDispatcher.h>
#include <qextTcpSocket.h>

#include <QRunnable>

class QEXTTcpTaskPrivate;
class QEXT_TCP_API QEXTTcpTask : public QObject, public QRunnable, public QEXTObject
{
    Q_OBJECT
public:
    QEXTTcpTask(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher,
                const QSharedPointer<QEXTTcpPacketInterface> &packet);
    QEXTTcpTask(QEXTTcpTaskPrivate &dd,
                const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher,
                const QSharedPointer<QEXTTcpPacketInterface> &packet);
    ~QEXTTcpTask();

    QSharedPointer<QEXTTcpPacketDispatcher> dispatcher() const;
    QSharedPointer<QEXTTcpPacketInterface> packet() const;
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

private:
    QEXT_DECL_PRIVATE(QEXTTcpTask)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpTask)
};


class QEXT_TCP_API QEXTTcpPostBackTask : public QEXTTcpTask
{
public:
    QEXTTcpPostBackTask(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher, const QSharedPointer<QEXTTcpPacketInterface> &packet);
    QEXTTcpPostBackTask(QEXTTcpTaskPrivate &dd, const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher, const QSharedPointer<QEXTTcpPacketInterface> &packet);
    ~QEXTTcpPostBackTask();

    QEXTId typeId() const QEXT_DECL_OVERRIDE;
    void run() QEXT_DECL_OVERRIDE;
};


class QEXT_TCP_API QEXTTcpTaskFactory
{
public:
    QEXTTcpTaskFactory() {}
    virtual ~QEXTTcpTaskFactory() {}

    virtual QEXTTcpTask *createTask(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher,
                                    const QSharedPointer<QEXTTcpPacketInterface> &packet);
};


#endif // QEXTTCPTASK_H
