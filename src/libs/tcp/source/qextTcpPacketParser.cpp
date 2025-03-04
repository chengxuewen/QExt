#include <private/qextTcpPacketParser_p.h>
#include <qextTcpPacket.h>
#include <qextTcpPacketVariant.h>
#include <qextTcpPacketHeader.h>
#include <qextTcpUtils.h>

#include <QDebug>
#include <QDateTime>
#include <QByteArray>
#include <QMutexLocker>

static const char *QEXT_TCP_PACKET_KEY_TYPE = "type";
static const char *QEXT_TCP_PACKET_KEY_TIME = "time";
static const char *QEXT_TCP_PACKET_KEY_ID = "id";

static const char *QEXT_TCP_PACKET_TYPE_REQUEST = "REQUEST";
static const char *QEXT_TCP_PACKET_TYPE_NOTIFY = "NOTIFY";
static const char *QEXT_TCP_PACKET_TYPE_REPLY = "REPLY";

quint32 QExtTcpPacketParserPrivate::sm_id = 0;

QExtTcpPacketParserPrivate::QExtTcpPacketParserPrivate(QExtTcpPacketParser *q)
    : q_ptr(q)
{

}

QExtTcpPacketParserPrivate::~QExtTcpPacketParserPrivate()
{

}



QExtTcpPacketParser::QExtTcpPacketParser(const QExtTcpPacketHeader::DataInfoVector &extraHeaderDataInfo)
    : dd_ptr(new QExtTcpPacketParserPrivate(this))
{
    Q_D(QExtTcpPacketParser);
    QExtTcpPacketHeader::DataInfoVector infoVector;
    infoVector.prepend(QExtTcpPacketHeader::DataInfoPair(QExtTcpPacketVariant::Data_chars + 8, QEXT_TCP_PACKET_KEY_TYPE));
    infoVector.prepend(QExtTcpPacketHeader::DataInfoPair(QExtTcpPacketVariant::Data_chars + 32, QEXT_TCP_PACKET_KEY_TIME));
    infoVector.prepend(QExtTcpPacketHeader::DataInfoPair(QExtTcpPacketVariant::Data_uint64, QEXT_TCP_PACKET_KEY_ID));
    d->m_headerDataPairVector = infoVector + extraHeaderDataInfo;
    d->m_extraHeaderDataPairVector = extraHeaderDataInfo;
}

QExtTcpPacketParser::QExtTcpPacketParser(QExtTcpPacketParserPrivate *d)
    : dd_ptr(d)
{

}

QExtTcpPacketParser::~QExtTcpPacketParser()
{

}

QString QExtTcpPacketParser::name() const
{
    return "QExtTcpPacketParser";
}

QString QExtTcpPacketParser::errorString() const
{
    Q_D(const QExtTcpPacketParser);
    return d->m_errorString;
}

bool QExtTcpPacketParser::comparePacket(const QSharedPointer<QExtTcpPacketInterface> &lpacket,
                                        const QSharedPointer<QExtTcpPacketInterface> &rpacket) const
{
    Q_D(const QExtTcpPacketParser);
    if (lpacket != rpacket)
    {
        QExtTcpPacketHeader::DataInfoVector::const_iterator iter;
        for (iter = d->m_headerDataPairVector.begin(); iter != d->m_headerDataPairVector.end(); ++iter)
        {
            QExtTcpPacketHeader::DataInfoPair pair = *iter;
            if (lpacket->header()->headerData(pair.second) != rpacket->header()->headerData(pair.second))
            {
                return false;
            }
        }
        return lpacket->content() == rpacket->content();
    }
    return true;
}

bool QExtTcpPacketParser::checkIsSyncReplyPacket(const QSharedPointer<QExtTcpPacketInterface> &send,
                                                 const QSharedPointer<QExtTcpPacketInterface> &rcv) const
{
    Q_D(const QExtTcpPacketParser);
    if (this->isRequestPacket(send) && this->isReplyPacket(rcv) && send != rcv)
    {
        if (send->header()->headerData(QEXT_TCP_PACKET_KEY_ID).toUint64() == rcv->header()->headerData(QEXT_TCP_PACKET_KEY_ID).toUint64())
        {
            return true;
        }
    }
    return false;
}

quint64 QExtTcpPacketParser::packetId(const QSharedPointer<QExtTcpPacketInterface> &packet) const
{
    Q_D(const QExtTcpPacketParser);
    if (!packet.isNull())
    {
        return packet->header()->headerData(QEXT_TCP_PACKET_KEY_ID).toUint64();
    }
    return 0;
}

bool QExtTcpPacketParser::isRequestPacket(const QSharedPointer<QExtTcpPacketInterface> &packet) const
{
    if (!packet.isNull())
    {
        return packet->header()->headerData(QEXT_TCP_PACKET_KEY_TYPE).toHostString() == QEXT_TCP_PACKET_TYPE_REQUEST;
    }
    return false;
}

bool QExtTcpPacketParser::setRequestPacket(const QSharedPointer<QExtTcpPacketInterface> &packet)
{
    Q_D(QExtTcpPacketParser);
    if (!packet.isNull())
    {
        bool success = packet->header()->setHeaderData(QEXT_TCP_PACKET_KEY_TYPE, QExtTcpPacketVariant(QEXT_TCP_PACKET_TYPE_REQUEST));
        success = packet->header()->setHeaderData(QEXT_TCP_PACKET_KEY_TIME, QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss:zzz")) && success;
        return packet->header()->setHeaderData(QEXT_TCP_PACKET_KEY_ID, (quint64)++d->sm_id) && success;
    }
    return false;
}

bool QExtTcpPacketParser::isReplyPacket(const QSharedPointer<QExtTcpPacketInterface> &packet) const
{
    if (!packet.isNull())
    {
        return packet->header()->headerData(QEXT_TCP_PACKET_KEY_TYPE).toHostString() == QEXT_TCP_PACKET_TYPE_REPLY;
    }
    return false;
}

bool QExtTcpPacketParser::setReplyPacket(const QSharedPointer<QExtTcpPacketInterface> &send,
                                         const QSharedPointer<QExtTcpPacketInterface> &rcv)
{
    Q_D(QExtTcpPacketParser);
    if (!send.isNull() && !rcv.isNull() && send != rcv)
    {
        bool success = send->header()->setHeaderData(QEXT_TCP_PACKET_KEY_TYPE, QExtTcpPacketVariant(QEXT_TCP_PACKET_TYPE_REPLY));
        success = send->header()->setHeaderData(QEXT_TCP_PACKET_KEY_TIME, QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss:zzz")) && success;
        return send->header()->setHeaderData(QEXT_TCP_PACKET_KEY_ID, rcv->header()->headerData(QEXT_TCP_PACKET_KEY_ID).toUint64()) && success;
    }
    return false;
}

bool QExtTcpPacketParser::isNotifyPacket(const QSharedPointer<QExtTcpPacketInterface> &packet) const
{
    if (!packet.isNull())
    {
        return packet->header()->headerData(QEXT_TCP_PACKET_KEY_TYPE).toHostString() == QEXT_TCP_PACKET_TYPE_NOTIFY;
    }
    return false;
}

bool QExtTcpPacketParser::setNotifyPacket(const QSharedPointer<QExtTcpPacketInterface> &packet)
{
    Q_D(QExtTcpPacketParser);
    if (!packet.isNull())
    {
        bool success = packet->header()->setHeaderData(QEXT_TCP_PACKET_KEY_TYPE, QExtTcpPacketVariant(QEXT_TCP_PACKET_TYPE_NOTIFY));
        success = packet->header()->setHeaderData(QEXT_TCP_PACKET_KEY_TIME, QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss:zzz")) && success;
        return packet->header()->setHeaderData(QEXT_TCP_PACKET_KEY_ID, (quint64)++d->sm_id) && success;
    }
    return false;
}

QSharedPointer<QExtTcpPacketHeaderInterface> QExtTcpPacketParser::createHeader() const
{
    Q_D(const QExtTcpPacketParser);
    return QSharedPointer<QExtTcpPacketHeaderInterface>(new QExtTcpPacketHeader(d->m_headerDataPairVector));
}

QSharedPointer<QExtTcpPacketInterface> QExtTcpPacketParser::createPacket() const
{
    Q_D(const QExtTcpPacketParser);
    return QSharedPointer<QExtTcpPacketInterface>(new QExtTcpPacket(this->createHeader()));
}

QSharedPointer<QExtTcpPacketInterface> QExtTcpPacketParser::clonePacket(const QSharedPointer<QExtTcpPacketInterface> &packet) const
{
    Q_D(const QExtTcpPacketParser);
    QSharedPointer<QExtTcpPacketInterface> clonePacket;
    if (!packet.isNull())
    {
        clonePacket = this->createPacket();
        QExtTcpPacketHeader::DataInfoVector::const_iterator iter;
        for (iter = d->m_headerDataPairVector.begin(); iter != d->m_headerDataPairVector.end(); ++iter)
        {
            QExtTcpPacketHeader::DataInfoPair pair = *iter;
            clonePacket->header()->setHeaderData(pair.second, packet->header()->headerData(pair.second));
        }
        clonePacket->setContent(packet->content());
    }
    return clonePacket;
}

QSharedPointer<QExtTcpPacketInterface> QExtTcpPacketParser::createReplyPacket(const QSharedPointer<QExtTcpPacketInterface> &rcv) const
{
    if (!rcv.isNull())
    {
        QSharedPointer<QExtTcpPacketInterface> packet = this->createPacket();
        packet->header()->setHeaderData(QEXT_TCP_PACKET_KEY_TYPE, QExtTcpPacketVariant(QEXT_TCP_PACKET_TYPE_REPLY));
        packet->header()->setHeaderData(QEXT_TCP_PACKET_KEY_TIME, QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss:zzz"));
        packet->header()->setHeaderData(QEXT_TCP_PACKET_KEY_ID, rcv->header()->headerData(QEXT_TCP_PACKET_KEY_ID));
        return packet;
    }
    return QSharedPointer<QExtTcpPacketInterface>();
}

QSharedPointer<QExtTcpPacketParserInterface> QExtTcpPacketParser::clonePacketParser() const
{
    Q_D(const QExtTcpPacketParser);
    return QSharedPointer<QExtTcpPacketParserInterface>(new QExtTcpPacketParser(d->m_extraHeaderDataPairVector));
}

QSharedPointer<QExtTcpPacketInterface> QExtTcpPacketParser::readData(QExtTcpSocket *socket, bool &success)
{
    Q_D(QExtTcpPacketParser);
    QMutexLocker mutexLocker(&d->m_mutex);

    success = true;
    QExtTagId socketId = socket->identityId();
    QSharedPointer<QExtTcpPacketInterface> packet = d->m_packetIdMap.value(socketId);
    if (packet.isNull())
    {
        packet = this->createPacket();
        d->m_packetIdMap.insert(socketId, packet);
    }

    /*read header data*/
    if (0 == packet->nextBlockSize())
    {
        int headerSize = packet->header()->headerSize();
        if (socket->bytesAvailable() < headerSize)
        {
            return QSharedPointer<QExtTcpPacketInterface>(); // next readData call
        }

        char *header = new char[headerSize];
        if (QEXT_NULLPTR == header)
        {
            socket->readAll(); // give up socket data
            d->m_errorString = "malloc header memory failed";
            success = false;
            return QSharedPointer<QExtTcpPacketInterface>(); // readData as packet error for malloc failed
        }
        memset(header, 0, headerSize);
        socket->read(header, headerSize);
        if (!packet->header()->setStream(QByteArray(header, headerSize)))
        {
            free(header);
            d->m_errorString = "parse header data failed";
            success = false;
            return QSharedPointer<QExtTcpPacketInterface>(); // readData as packet error for parse header failed
        }
        packet->setNextBlockSize(packet->header()->contentSize());
        delete []header;   // readData as packet header success
    }

    if (socket->bytesAvailable() < packet->nextBlockSize())
    {
        return QSharedPointer<QExtTcpPacketInterface>(); // next readData call
    }

    int contentSize = packet->header()->contentSize();
    char *content = new char[contentSize];
    socket->read(content, contentSize);
    packet->setContent(QByteArray(content, contentSize));
    d->m_packetIdMap.remove(socketId);
    d->m_errorString = "";
    delete []content;
    return packet; // readData as packet success
}

qint64 QExtTcpPacketParser::writeData(QExtTcpSocket *socket, const QSharedPointer<QExtTcpPacketInterface> &packet)
{
    Q_D(QExtTcpPacketParser);
    QMutexLocker mutexLocker(&d->m_mutex);
    QByteArray stream = packet->stream();
    return socket->write(stream.data(), stream.size());
}


