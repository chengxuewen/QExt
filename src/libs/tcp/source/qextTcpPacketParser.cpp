#include <qextTcpPacketParser.h>
#include <qextTcpPacketParser_p.h>
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

quint32 QEXTTcpPacketParserPrivate::sm_id = 0;

QEXTTcpPacketParserPrivate::QEXTTcpPacketParserPrivate(QEXTTcpPacketParser *q)
    : q_ptr(q)
{

}

QEXTTcpPacketParserPrivate::~QEXTTcpPacketParserPrivate()
{

}



QEXTTcpPacketParser::QEXTTcpPacketParser(const QEXTTcpPacketHeader::DataInfoVector &extraHeaderDataInfo)
    : dd_ptr(new QEXTTcpPacketParserPrivate(this))
{
    Q_D(QEXTTcpPacketParser);
    QEXTTcpPacketHeader::DataInfoVector infoVector;
    infoVector.prepend(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 8, QEXT_TCP_PACKET_KEY_TYPE));
    infoVector.prepend(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 32, QEXT_TCP_PACKET_KEY_TIME));
    infoVector.prepend(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_uint64, QEXT_TCP_PACKET_KEY_ID));
    d->m_headerDataPairVector = infoVector + extraHeaderDataInfo;
    d->m_extraHeaderDataPairVector = extraHeaderDataInfo;
}

QEXTTcpPacketParser::QEXTTcpPacketParser(QEXTTcpPacketParserPrivate *d)
    : dd_ptr(d)
{

}

QEXTTcpPacketParser::~QEXTTcpPacketParser()
{

}

QString QEXTTcpPacketParser::name() const
{
    return "QEXTTcpPacketParser";
}

QString QEXTTcpPacketParser::errorString() const
{
    Q_D(const QEXTTcpPacketParser);
    return d->m_errorString;
}

bool QEXTTcpPacketParser::comparePacket(const QSharedPointer<QEXTTcpPacketInterface> &lpacket,
                                        const QSharedPointer<QEXTTcpPacketInterface> &rpacket) const
{
    Q_D(const QEXTTcpPacketParser);
    if (lpacket != rpacket)
    {
        QEXTTcpPacketHeader::DataInfoVector::const_iterator iter;
        for (iter = d->m_headerDataPairVector.begin(); iter != d->m_headerDataPairVector.end(); ++iter)
        {
            QEXTTcpPacketHeader::DataInfoPair pair = *iter;
            if (lpacket->header()->headerData(pair.second) != rpacket->header()->headerData(pair.second))
            {
                return false;
            }
        }
        return lpacket->content() == rpacket->content();
    }
    return true;
}

bool QEXTTcpPacketParser::checkIsSyncReplyPacket(const QSharedPointer<QEXTTcpPacketInterface> &send,
                                                 const QSharedPointer<QEXTTcpPacketInterface> &rcv) const
{
    Q_D(const QEXTTcpPacketParser);
    if (this->isRequestPacket(send) && this->isReplyPacket(rcv) && send != rcv)
    {
        if (send->header()->headerData(QEXT_TCP_PACKET_KEY_ID).toUint64() == rcv->header()->headerData(QEXT_TCP_PACKET_KEY_ID).toUint64())
        {
            return true;
        }
    }
    return false;
}

quint64 QEXTTcpPacketParser::packetId(const QSharedPointer<QEXTTcpPacketInterface> &packet) const
{
    Q_D(const QEXTTcpPacketParser);
    if (!packet.isNull())
    {
        return packet->header()->headerData(QEXT_TCP_PACKET_KEY_ID).toUint64();
    }
    return 0;
}

bool QEXTTcpPacketParser::isRequestPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet) const
{
    if (!packet.isNull())
    {
        return packet->header()->headerData(QEXT_TCP_PACKET_KEY_TYPE).toHostString() == QEXT_TCP_PACKET_TYPE_REQUEST;
    }
    return false;
}

bool QEXTTcpPacketParser::setRequestPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet)
{
    Q_D(QEXTTcpPacketParser);
    if (!packet.isNull())
    {
        bool success = packet->header()->setHeaderData(QEXT_TCP_PACKET_KEY_TYPE, QEXTTcpPacketVariant(QEXT_TCP_PACKET_TYPE_REQUEST));
        success = packet->header()->setHeaderData(QEXT_TCP_PACKET_KEY_TIME, QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss:zzz")) && success;
        return packet->header()->setHeaderData(QEXT_TCP_PACKET_KEY_ID, (quint64)++d->sm_id) && success;
    }
    return false;
}

bool QEXTTcpPacketParser::isReplyPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet) const
{
    if (!packet.isNull())
    {
        return packet->header()->headerData(QEXT_TCP_PACKET_KEY_TYPE).toHostString() == QEXT_TCP_PACKET_TYPE_REPLY;
    }
    return false;
}

bool QEXTTcpPacketParser::setReplyPacket(const QSharedPointer<QEXTTcpPacketInterface> &send,
                                         const QSharedPointer<QEXTTcpPacketInterface> &rcv)
{
    Q_D(QEXTTcpPacketParser);
    if (!send.isNull() && !rcv.isNull() && send != rcv)
    {
        bool success = send->header()->setHeaderData(QEXT_TCP_PACKET_KEY_TYPE, QEXTTcpPacketVariant(QEXT_TCP_PACKET_TYPE_REPLY));
        success = send->header()->setHeaderData(QEXT_TCP_PACKET_KEY_TIME, QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss:zzz")) && success;
        return send->header()->setHeaderData(QEXT_TCP_PACKET_KEY_ID, rcv->header()->headerData(QEXT_TCP_PACKET_KEY_ID).toUint64()) && success;
    }
    return false;
}

bool QEXTTcpPacketParser::isNotifyPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet) const
{
    if (!packet.isNull())
    {
        return packet->header()->headerData(QEXT_TCP_PACKET_KEY_TYPE).toHostString() == QEXT_TCP_PACKET_TYPE_NOTIFY;
    }
    return false;
}

bool QEXTTcpPacketParser::setNotifyPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet)
{
    Q_D(QEXTTcpPacketParser);
    if (!packet.isNull())
    {
        bool success = packet->header()->setHeaderData(QEXT_TCP_PACKET_KEY_TYPE, QEXTTcpPacketVariant(QEXT_TCP_PACKET_TYPE_NOTIFY));
        success = packet->header()->setHeaderData(QEXT_TCP_PACKET_KEY_TIME, QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss:zzz")) && success;
        return packet->header()->setHeaderData(QEXT_TCP_PACKET_KEY_ID, (quint64)++d->sm_id) && success;
    }
    return false;
}

QSharedPointer<QEXTTcpPacketHeaderInterface> QEXTTcpPacketParser::createHeader() const
{
    Q_D(const QEXTTcpPacketParser);
    return QSharedPointer<QEXTTcpPacketHeaderInterface>(new QEXTTcpPacketHeader(d->m_headerDataPairVector));
}

QSharedPointer<QEXTTcpPacketInterface> QEXTTcpPacketParser::createPacket() const
{
    Q_D(const QEXTTcpPacketParser);
    return QSharedPointer<QEXTTcpPacketInterface>(new QEXTTcpPacket(this->createHeader()));
}

QSharedPointer<QEXTTcpPacketInterface> QEXTTcpPacketParser::clonePacket(const QSharedPointer<QEXTTcpPacketInterface> &packet) const
{
    Q_D(const QEXTTcpPacketParser);
    QSharedPointer<QEXTTcpPacketInterface> clonePacket;
    if (!packet.isNull())
    {
        clonePacket = this->createPacket();
        QEXTTcpPacketHeader::DataInfoVector::const_iterator iter;
        for (iter = d->m_headerDataPairVector.begin(); iter != d->m_headerDataPairVector.end(); ++iter)
        {
            QEXTTcpPacketHeader::DataInfoPair pair = *iter;
            clonePacket->header()->setHeaderData(pair.second, packet->header()->headerData(pair.second));
        }
        clonePacket->setContent(packet->content());
    }
    return clonePacket;
}

QSharedPointer<QEXTTcpPacketInterface> QEXTTcpPacketParser::createReplyPacket(const QSharedPointer<QEXTTcpPacketInterface> &rcv) const
{
    if (!rcv.isNull())
    {
        QSharedPointer<QEXTTcpPacketInterface> packet = this->createPacket();
        packet->header()->setHeaderData(QEXT_TCP_PACKET_KEY_TYPE, QEXTTcpPacketVariant(QEXT_TCP_PACKET_TYPE_REPLY));
        packet->header()->setHeaderData(QEXT_TCP_PACKET_KEY_TIME, QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss:zzz"));
        packet->header()->setHeaderData(QEXT_TCP_PACKET_KEY_ID, rcv->header()->headerData(QEXT_TCP_PACKET_KEY_ID));
        return packet;
    }
    return QSharedPointer<QEXTTcpPacketInterface>();
}

QSharedPointer<QEXTTcpPacketParserInterface> QEXTTcpPacketParser::clonePacketParser() const
{
    Q_D(const QEXTTcpPacketParser);
    return QSharedPointer<QEXTTcpPacketParserInterface>(new QEXTTcpPacketParser(d->m_extraHeaderDataPairVector));
}

QSharedPointer<QEXTTcpPacketInterface> QEXTTcpPacketParser::readData(QEXTTcpSocket *socket, bool &success)
{
    Q_D(QEXTTcpPacketParser);
    QMutexLocker mutexLocker(&d->m_mutex);

    success = true;
    QEXTId socketId = socket->identityId();
    QSharedPointer<QEXTTcpPacketInterface> packet = d->m_packetIdMap.value(socketId);
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
            return QSharedPointer<QEXTTcpPacketInterface>(); // next readData call
        }

        char *header = new char[headerSize];
        if (QEXT_DECL_NULLPTR == header)
        {
            socket->readAll(); // give up socket data
            d->m_errorString = "malloc header memory failed";
            success = false;
            return QSharedPointer<QEXTTcpPacketInterface>(); // readData as packet error for malloc failed
        }
        memset(header, 0, headerSize);
        socket->read(header, headerSize);
        if (!packet->header()->setStream(QByteArray(header, headerSize)))
        {
            free(header);
            d->m_errorString = "parse header data failed";
            success = false;
            return QSharedPointer<QEXTTcpPacketInterface>(); // readData as packet error for parse header failed
        }
        packet->setNextBlockSize(packet->header()->contentSize());
        delete []header;   // readData as packet header success
    }

    if (socket->bytesAvailable() < packet->nextBlockSize())
    {
        return QSharedPointer<QEXTTcpPacketInterface>(); // next readData call
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

qint64 QEXTTcpPacketParser::writeData(QEXTTcpSocket *socket, const QSharedPointer<QEXTTcpPacketInterface> &packet)
{
    Q_D(QEXTTcpPacketParser);
    QMutexLocker mutexLocker(&d->m_mutex);
    QByteArray stream = packet->stream();
    return socket->write(stream.data(), stream.size());
}


