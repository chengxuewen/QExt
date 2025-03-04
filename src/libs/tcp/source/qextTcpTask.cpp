#include <private/qextTcpTask_p.h>
#include <qextTcpPacketTransceiver.h>
#include <qextTcpPacketDispatcher.h>
#include <qextTcpUtils.h>

#include <qextDateTimeUtils.h>

#include <QDebug>

quint64 QExtTcpTaskPrivate::sm_id = 0;

QExtTcpTaskPrivate::QExtTcpTaskPrivate(QExtTcpTask *q)
    : q_ptr(q),
      m_timestamp(QDateTime::currentDateTime())
{
    m_id = ++sm_id;
    m_finished = false;
}

QExtTcpTaskPrivate::~QExtTcpTaskPrivate()
{

}



QExtTcpTask::QExtTcpTask(const QSharedPointer<QExtTcpPacketTransceiver> &transceiver)
    : QObject(QEXT_NULLPTR), dd_ptr(new QExtTcpTaskPrivate(this))
{
    dd_ptr->m_packetTransceiver = transceiver;
}

QExtTcpTask::QExtTcpTask(const QSharedPointer<QExtTcpPacketTransceiver> &transceiver,
                         const QSharedPointer<QExtTcpPacketInterface> &packet)
    : QObject(QEXT_NULLPTR), dd_ptr(new QExtTcpTaskPrivate(this))
{
    dd_ptr->m_packetTransceiver = transceiver;
    dd_ptr->m_receivedPacket = packet;
}

QExtTcpTask::QExtTcpTask(QExtTcpTaskPrivate *d,
                         const QSharedPointer<QExtTcpPacketTransceiver> &transceiver)
    : QObject(QEXT_NULLPTR), dd_ptr(d)
{
    dd_ptr->m_packetTransceiver = transceiver;
}

QExtTcpTask::QExtTcpTask(QExtTcpTaskPrivate *d,
                         const QSharedPointer<QExtTcpPacketTransceiver> &transceiver,
                         const QSharedPointer<QExtTcpPacketInterface> &packet)
    : QObject(QEXT_NULLPTR), dd_ptr(d)
{
    dd_ptr->m_packetTransceiver = transceiver;
    dd_ptr->m_receivedPacket = packet;
}

QExtTcpTask::~QExtTcpTask()
{
    emit this->aboutToBeDelete(dd_ptr->m_id);
}

QSharedPointer<QExtTcpPacketInterface> QExtTcpTask::receivedPacket() const
{
    Q_D(const QExtTcpTask);
    return d->m_receivedPacket;
}

QSharedPointer<QExtTcpPacketTransceiver> QExtTcpTask::packetTransceiver() const
{
    Q_D(const QExtTcpTask);
    return d->m_packetTransceiver;
}

quint64 QExtTcpTask::id() const
{
    Q_D(const QExtTcpTask);
    return d->m_id;
}

QExtTagId QExtTcpTask::identityId() const
{
    Q_D(const QExtTcpTask);
    return QString("%1-%3:%4")
            .arg(this->packetTransceiver()->identityId().toString())
            .arg(this->typeId().toString()).arg(d->m_id);
}

QDateTime QExtTcpTask::timestamp() const
{
    Q_D(const QExtTcpTask);
    return d->m_timestamp;
}

bool QExtTcpTask::isFinished() const
{
    Q_D(const QExtTcpTask);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_finished;
}

bool QExtTcpTask::isErrored() const
{
    Q_D(const QExtTcpTask);
    QMutexLocker mutexLocker(&d->m_mutex);
    return !d->m_errorString.isEmpty();
}

QString QExtTcpTask::errorString() const
{
    Q_D(const QExtTcpTask);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_errorString;
}

QExtTagId QExtTcpTask::typeId() const
{
    return "QExtTcpTask";
}

void QExtTcpTask::run()
{
    qDebug() << "QExtTcpTask::run(): do nothing";
}

void QExtTcpTask::setErrorString(const QString &string)
{
    Q_D(QExtTcpTask);
    QMutexLocker mutexLocker(&d->m_mutex);
    d->m_errorString = string;
    emit this->error(string);
}



QExtTcpPostBackTask::QExtTcpPostBackTask(const QSharedPointer<QExtTcpPacketTransceiver> &transceiver,
                                         const QSharedPointer<QExtTcpPacketInterface> &packet)
    : QExtTcpTask(transceiver, packet)
{

}

QExtTcpPostBackTask::QExtTcpPostBackTask(QExtTcpTaskPrivate *d,
                                         const QSharedPointer<QExtTcpPacketTransceiver> &transceiver,
                                         const QSharedPointer<QExtTcpPacketInterface> &packet)
    : QExtTcpTask(d, transceiver, packet)
{

}

QExtTcpPostBackTask::~QExtTcpPostBackTask()
{

}

QExtTagId QExtTcpPostBackTask::typeId() const
{
    return "QExtTcpPostBackTask";
}

void QExtTcpPostBackTask::run()
{
    qDebug() << "QExtTcpPostBackTask::run()-------------------------";
    QExtTcpUtils::printPacket(this->receivedPacket());
    QSharedPointer<QExtTcpPacketInterface> receivedPacket = this->receivedPacket();
    QSharedPointer<QExtTcpPacketParserInterface> packetParser = this->packetTransceiver()->packetParser();
    QSharedPointer<QExtTcpPacketInterface> packet = packetParser->clonePacket(receivedPacket);
    this->packetTransceiver()->send(packet);
}
