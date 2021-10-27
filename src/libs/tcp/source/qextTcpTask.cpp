#include <qextTcpTask.h>
#include <qextTcpTask_p.h>
#include <qextTcpPacketTransceiver.h>
#include <qextTcpPacketDispatcher.h>
#include <qextTcpUtils.h>

#include <qextDateTimeUtils.h>

#include <QDebug>

quint64 QEXTTcpTaskPrivate::sm_id = 0;

QEXTTcpTaskPrivate::QEXTTcpTaskPrivate(QEXTTcpTask *q)
    : q_ptr(q),
      m_timestamp(QDateTime::currentDateTime())
{
    m_id = ++sm_id;
    m_finished = false;
}

QEXTTcpTaskPrivate::~QEXTTcpTaskPrivate()
{

}



QEXTTcpTask::QEXTTcpTask(const QSharedPointer<QEXTTcpPacketTransceiver> &transceiver)
    : QObject(QEXT_DECL_NULLPTR), d_ptr(new QEXTTcpTaskPrivate(this))
{
    d_ptr->m_packetTransceiver = transceiver;
}

QEXTTcpTask::QEXTTcpTask(const QSharedPointer<QEXTTcpPacketTransceiver> &transceiver,
                         const QSharedPointer<QEXTTcpPacketInterface> &packet)
    : QObject(QEXT_DECL_NULLPTR), d_ptr(new QEXTTcpTaskPrivate(this))
{
    d_ptr->m_packetTransceiver = transceiver;
    d_ptr->m_receivedPacket = packet;
}

QEXTTcpTask::QEXTTcpTask(QEXTTcpTaskPrivate *d,
                         const QSharedPointer<QEXTTcpPacketTransceiver> &transceiver)
    : QObject(QEXT_DECL_NULLPTR), d_ptr(d)
{
    d_ptr->m_packetTransceiver = transceiver;
}

QEXTTcpTask::QEXTTcpTask(QEXTTcpTaskPrivate *d,
                         const QSharedPointer<QEXTTcpPacketTransceiver> &transceiver,
                         const QSharedPointer<QEXTTcpPacketInterface> &packet)
    : QObject(QEXT_DECL_NULLPTR), d_ptr(d)
{
    d_ptr->m_packetTransceiver = transceiver;
    d_ptr->m_receivedPacket = packet;
}

QEXTTcpTask::~QEXTTcpTask()
{
    emit this->aboutToBeDelete(d_ptr->m_id);
}

QSharedPointer<QEXTTcpPacketInterface> QEXTTcpTask::receivedPacket() const
{
    QEXT_DECL_DC(QEXTTcpTask);
    return d->m_receivedPacket;
}

QSharedPointer<QEXTTcpPacketTransceiver> QEXTTcpTask::packetTransceiver() const
{
    QEXT_DECL_DC(QEXTTcpTask);
    return d->m_packetTransceiver;
}

quint64 QEXTTcpTask::id() const
{
    QEXT_DECL_DC(QEXTTcpTask);
    return d->m_id;
}

QEXTId QEXTTcpTask::identityId() const
{
    QEXT_DECL_DC(QEXTTcpTask);
    return QString("%1-%3:%4")
            .arg(this->packetTransceiver()->identityId().toString())
            .arg(this->typeId().toString()).arg(d->m_id);
}

QDateTime QEXTTcpTask::timestamp() const
{
    QEXT_DECL_DC(QEXTTcpTask);
    return d->m_timestamp;
}

bool QEXTTcpTask::isFinished() const
{
    QEXT_DECL_DC(QEXTTcpTask);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_finished;
}

bool QEXTTcpTask::isErrored() const
{
    QEXT_DECL_DC(QEXTTcpTask);
    QMutexLocker mutexLocker(&d->m_mutex);
    return !d->m_errorString.isEmpty();
}

QString QEXTTcpTask::errorString() const
{
    QEXT_DECL_DC(QEXTTcpTask);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_errorString;
}

QEXTId QEXTTcpTask::typeId() const
{
    return "QEXTTcpTask";
}

void QEXTTcpTask::run()
{
    qDebug() << "QEXTTcpTask::run(): do nothing";
}

void QEXTTcpTask::setErrorString(const QString &string)
{
    QEXT_DECL_D(QEXTTcpTask);
    QMutexLocker mutexLocker(&d->m_mutex);
    d->m_errorString = string;
    emit this->error(string);
}



QEXTTcpPostBackTask::QEXTTcpPostBackTask(const QSharedPointer<QEXTTcpPacketTransceiver> &transceiver,
                                         const QSharedPointer<QEXTTcpPacketInterface> &packet)
    : QEXTTcpTask(transceiver, packet)
{

}

QEXTTcpPostBackTask::QEXTTcpPostBackTask(QEXTTcpTaskPrivate *d,
                                         const QSharedPointer<QEXTTcpPacketTransceiver> &transceiver,
                                         const QSharedPointer<QEXTTcpPacketInterface> &packet)
    : QEXTTcpTask(d, transceiver, packet)
{

}

QEXTTcpPostBackTask::~QEXTTcpPostBackTask()
{

}

QEXTId QEXTTcpPostBackTask::typeId() const
{
    return "QEXTTcpPostBackTask";
}

void QEXTTcpPostBackTask::run()
{
    qDebug() << "QEXTTcpPostBackTask::run()-------------------------";
    QEXTTcpUtils::printPacket(this->receivedPacket());
    QSharedPointer<QEXTTcpPacketInterface> receivedPacket = this->receivedPacket();
    QSharedPointer<QEXTTcpPacketParserInterface> packetParser = this->packetTransceiver()->packetParser();
    QSharedPointer<QEXTTcpPacketInterface> packet = packetParser->clonePacket(receivedPacket);
    this->packetTransceiver()->send(packet);
}
