#include <qextTcpTask.h>
#include <qextTcpTask_p.h>
#include <qextTcpPacketTransceiver.h>
#include <qextTcpPacketDispatcher.h>
#include <qextTcpUtils.h>

#include <qextdatetimeutils.h>

#include <QDebug>

quint64 QEXTTcpTaskPrivate::sm_id = 0;

QEXTTcpTaskPrivate::QEXTTcpTaskPrivate(QEXTTcpTask *qq)
    : QEXTObjectPrivate(qq),
      m_timestamp(QDateTime::currentDateTime())
{
    m_id = ++sm_id;
    m_finished = false;
}

QEXTTcpTaskPrivate::~QEXTTcpTaskPrivate()
{

}



QEXTTcpTask::QEXTTcpTask(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher,
                         const QSharedPointer<QEXTTcpPacketInterface> &packet)
    : QObject(), QRunnable(), QEXTObject(*(new QEXTTcpTaskPrivate(this)))
{
    QEXT_DECL_D(QEXTTcpTask);
    d->m_packetDispatcher = dispatcher;
    d->m_packet = packet;
    d->m_packetTransceiver = QSharedPointer<QEXTTcpPacketTransceiver>(new QEXTTcpPacketTransceiver(dispatcher));
}

QEXTTcpTask::QEXTTcpTask(QEXTTcpTaskPrivate &dd,
                         const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher,
                         const QSharedPointer<QEXTTcpPacketInterface> &packet)
    : QObject(), QRunnable(), QEXTObject(dd)
{
    QEXT_DECL_D(QEXTTcpTask);
    d->m_packetDispatcher = dispatcher;
    d->m_packet = packet;
    d->m_packetTransceiver = QSharedPointer<QEXTTcpPacketTransceiver>(new QEXTTcpPacketTransceiver(dispatcher));
}

QEXTTcpTask::~QEXTTcpTask()
{
    QEXT_DECL_DC(QEXTTcpTask);
    emit this->aboutToBeDelete(d->m_id);
}

QSharedPointer<QEXTTcpPacketDispatcher> QEXTTcpTask::dispatcher() const
{
    QEXT_DECL_DC(QEXTTcpTask);
    return d->m_packetDispatcher;
}

QSharedPointer<QEXTTcpPacketInterface> QEXTTcpTask::packet() const
{
    QEXT_DECL_DC(QEXTTcpTask);
    return d->m_packet;
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
            .arg(this->dispatcher()->socket()->identityId().toString())
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



QEXTTcpPostBackTask::QEXTTcpPostBackTask(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher,
                                         const QSharedPointer<QEXTTcpPacketInterface> &packet)
    : QEXTTcpTask(dispatcher, packet)
{

}

QEXTTcpPostBackTask::QEXTTcpPostBackTask(QEXTTcpTaskPrivate &dd,
                                         const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher,
                                         const QSharedPointer<QEXTTcpPacketInterface> &packet)
    : QEXTTcpTask(dd, dispatcher, packet)
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
    QEXTTcpUtils::printPacket(this->packet());
    QSharedPointer<QEXTTcpPacketInterface> receivedPacket = this->packet();
    QSharedPointer<QEXTTcpPacketParserInterface> packetParser = this->dispatcher()->packetParser();
    QSharedPointer<QEXTTcpPacketInterface> packet = packetParser->clonePacket(receivedPacket.data());
    this->packetTransceiver()->send(packet);
}


QEXTTcpTask *QEXTTcpTaskFactory::createTask(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher,
                                            const QSharedPointer<QEXTTcpPacketInterface> &packet)
{
    return new QEXTTcpPostBackTask(dispatcher, packet);
}
