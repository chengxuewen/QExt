#include <qexttcptask.h>
#include <qexttcptask_p.h>

#include <qextdatetimeutils.h>

#include <QDebug>
#include <QThread>
#include <QDateTime>

QEXTTcpTaskPrivate::QEXTTcpTaskPrivate(QEXTTcpTask *qq)
    : QEXTTcpTaskBasePrivate(qq)
{

}

QEXTTcpTaskPrivate::~QEXTTcpTaskPrivate()
{

}



QEXTTcpTask::QEXTTcpTask(QEXTTcpPacketBase *packet, QEXTTcpTaskPoolBase *taskPool)
    : QEXTTcpTaskBase(*(new QEXTTcpTaskPrivate(this)), taskPool)
{
    QEXT_D(QEXTTcpTask);
    d->m_packet.reset(packet);
}

QEXTTcpTask::~QEXTTcpTask()
{

}

bool QEXTTcpTask::run()
{
    qDebug() << "QEXTTcpTask::run():--------------------";
    QEXT_D(QEXTTcpTask);
    QEXTTcpPacketBase::printPacket(d->m_packet.data());
    if (!d->m_taskPool.isNull()) {
        QEXTDateTimeUtils::mSleep(1000);
        QEXTTcpPacketParserBase *packetParser = d->m_taskPool->packetParser();
        QEXTTcpPacketBase *notifyPacket = packetParser->createPacket(d->m_packet->socketId());
        notifyPacket->setContent(QByteArray("notify"));
        packetParser->setNotifyPacket(notifyPacket);
        this->taskPool()->sendPacket(notifyPacket);

        if (packetParser->isRequestPacket(d->m_packet.data())) {
            qDebug() << "QEXTTcpTask::run():isRequestPacket";
            QEXTTcpPacketBase *replyPacket = packetParser->createReplyPacket(d->m_packet.data());
            replyPacket->setContent(QByteArray("success"));
            this->taskPool()->sendPacket(replyPacket);
        }
    }
    this->setFinished(true);
    qDebug() << "QEXTTcpTask::run():finish";
    return true;
}

