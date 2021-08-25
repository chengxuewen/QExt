#include <qexttcppacketparser.h>
#include <qexttcppacketparser_p.h>
#include <qexttcppacket.h>
#include <qexttcppacketheader.h>

#include <QDebug>
#include <QByteArray>
#include <QMutexLocker>



static const char *QEXT_TCP_PACKET_TYPE_KEY = "type";
static const char *QEXT_TCP_PACKET_TYPE_REQUEST = "REQUEST";
static const char *QEXT_TCP_PACKET_TYPE_REPLY = "REPLY";
static const char *QEXT_TCP_PACKET_TYPE_NOTIFY = "NOTIFY";

static const char *QEXT_TCP_PACKET_ID_KEY = "id";

quint32 QEXTTcpPacketParserPrivate::sm_id = 0;

QEXTTcpPacketParserPrivate::QEXTTcpPacketParserPrivate(QEXTTcpPacketParser *qq)
    : QEXTObjectPrivate(qq)
{

}

QEXTTcpPacketParserPrivate::~QEXTTcpPacketParserPrivate()
{

}



QEXTTcpPacketParser::QEXTTcpPacketParser(const QEXTTcpPacketHeader::DataInfoVector &extraHeaderDataInfo)
    : QEXTObject(*(new QEXTTcpPacketParserPrivate(this)))
{
    QEXT_DECL_D(QEXTTcpPacketParser);
    QEXTTcpPacketHeader::DataInfoVector infoVector;
    infoVector.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 8, QEXT_TCP_PACKET_TYPE_KEY));
    infoVector.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_uint32, QEXT_TCP_PACKET_ID_KEY));
    d->m_headerDataPairVector = infoVector + extraHeaderDataInfo;
    d->m_extraHeaderDataPairVector = extraHeaderDataInfo;
}

QEXTTcpPacketParser::QEXTTcpPacketParser(QEXTTcpPacketParserPrivate &dd)
    : QEXTObject(dd)
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
    QEXT_DECL_DC(QEXTTcpPacketParser);
    return d->m_errorString;
}

bool QEXTTcpPacketParser::checkIsSyncReplyPacket(QEXTTcpAbstractPacket *send, QEXTTcpAbstractPacket *rcv) const
{
    QEXT_DECL_DC(QEXTTcpPacketParser);
    if (this->isRequestPacket(send) && this->isReplyPacket(rcv)) {
        if (send->header()->headerData(QEXT_TCP_PACKET_ID_KEY).toUint32() ==
                rcv->header()->headerData(QEXT_TCP_PACKET_ID_KEY).toUint32()) {
            return true;
        }
    }
    return false;
}

bool QEXTTcpPacketParser::isRequestPacket(QEXTTcpAbstractPacket *packet) const
{
    if (packet) {
        return packet->header()->headerData(QEXT_TCP_PACKET_TYPE_KEY).toHostString() == QEXT_TCP_PACKET_TYPE_REQUEST;
    }
    return false;
}

bool QEXTTcpPacketParser::setRequestPacket(QEXTTcpAbstractPacket *packet)
{
    QEXT_DECL_D(QEXTTcpPacketParser);
    if (packet) {
        bool success = packet->header()->setHeaderData(QEXT_TCP_PACKET_TYPE_KEY, QEXTTcpPacketVariant(QEXT_TCP_PACKET_TYPE_REQUEST));
        return packet->header()->setHeaderData(QEXT_TCP_PACKET_ID_KEY, (quint32)++d->sm_id) && success;
    }
    return false;
}

bool QEXTTcpPacketParser::isReplyPacket(QEXTTcpAbstractPacket *packet) const
{
    if (packet) {
        return packet->header()->headerData(QEXT_TCP_PACKET_TYPE_KEY).toHostString() == QEXT_TCP_PACKET_TYPE_REPLY;
    }
    return false;
}

bool QEXTTcpPacketParser::setReplyPacket(QEXTTcpAbstractPacket *packet)
{
    QEXT_DECL_D(QEXTTcpPacketParser);
    if (packet) {
        bool success = packet->header()->setHeaderData(QEXT_TCP_PACKET_TYPE_KEY, QEXTTcpPacketVariant(QEXT_TCP_PACKET_TYPE_REPLY));
        return packet->header()->setHeaderData(QEXT_TCP_PACKET_ID_KEY, (quint32)++d->sm_id) && success;
    }
    return false;
}

bool QEXTTcpPacketParser::isNotifyPacket(QEXTTcpAbstractPacket *packet) const
{
    if (packet) {
        return packet->header()->headerData(QEXT_TCP_PACKET_TYPE_KEY).toHostString() == QEXT_TCP_PACKET_TYPE_NOTIFY;
    }
    return false;
}

bool QEXTTcpPacketParser::setNotifyPacket(QEXTTcpAbstractPacket *packet)
{
    QEXT_DECL_D(QEXTTcpPacketParser);
    if (packet) {
        bool success = packet->header()->setHeaderData(QEXT_TCP_PACKET_TYPE_KEY, QEXTTcpPacketVariant(QEXT_TCP_PACKET_TYPE_NOTIFY));
        return packet->header()->setHeaderData(QEXT_TCP_PACKET_ID_KEY, (quint32)++d->sm_id) && success;
    }
    return false;
}

QEXTTcpAbstractPacketHeader *QEXTTcpPacketParser::createHeader() const
{
    QEXT_DECL_DC(QEXTTcpPacketParser);
    return new QEXTTcpPacketHeader(d->m_headerDataPairVector);
}

QEXTTcpAbstractPacket *QEXTTcpPacketParser::createPacket(const QEXTId &socketId) const
{
    QEXT_DECL_DC(QEXTTcpPacketParser);
    return new QEXTTcpPacket(this->createHeader(), socketId);
}

QEXTTcpAbstractPacket *QEXTTcpPacketParser::createReplyPacket(QEXTTcpAbstractPacket *rcv) const
{
    if (rcv) {
        QEXTTcpAbstractPacket *packet = this->createPacket(rcv->socketId());
        packet->header()->setHeaderData(QEXT_TCP_PACKET_TYPE_KEY, QEXTTcpPacketVariant(QEXT_TCP_PACKET_TYPE_REPLY));
        packet->header()->setHeaderData(QEXT_TCP_PACKET_ID_KEY, rcv->header()->headerData(QEXT_TCP_PACKET_ID_KEY));
        return packet;
    }
    return QEXT_DECL_NULLPTR;
}

QEXTTcpAbstractPacketParser *QEXTTcpPacketParser::cloneParser() const
{
    QEXT_DECL_DC(QEXTTcpPacketParser);
    return new QEXTTcpPacketParser(d->m_extraHeaderDataPairVector);
}

QEXTTcpAbstractPacket *QEXTTcpPacketParser::readData(QEXTTcpSocket *socket, bool &success)
{
    QEXT_DECL_D(QEXTTcpPacketParser);
    QMutexLocker mutexLocker(&d->m_mutex);

    success = true;
    QEXTId socketId = socket->identityId();
    QEXTTcpAbstractPacket *packet = d->m_packetIdMap.value(socketId, QEXT_DECL_NULLPTR);
    if (!packet) {
        packet = this->createPacket(socketId);
        d->m_packetIdMap.insert(socketId, packet);
    }

    /*read header data*/
    if (0 == packet->nextBlockSize()) {
        int headerSize = packet->header()->headerSize();
        if (socket->bytesAvailable() < headerSize) {
            return QEXT_DECL_NULLPTR; // next readData call
        }

        char *header = new char[headerSize];
        if (QEXT_DECL_NULLPTR == header) {
            socket->readAll(); // give up socket data
            d->m_errorString = "malloc header memory failed";
            success = false;
            return QEXT_DECL_NULLPTR; // readData as packet error for malloc failed
        }
        memset(header, 0, headerSize);
        socket->read(header, headerSize);
        if (!packet->header()->setStream(QByteArray(header, headerSize))) {
            free(header);
            d->m_errorString = "parse header data failed";
            success = false;
            return QEXT_DECL_NULLPTR; // readData as packet error for parse header failed
        }
        packet->setNextBlockSize(packet->header()->contentSize());
        delete []header;   // readData as packet header success
    }

    if (socket->bytesAvailable() < packet->nextBlockSize()) {
        return QEXT_DECL_NULLPTR; // next readData call
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

qint64 QEXTTcpPacketParser::writeData(QEXTTcpSocket *socket, QEXTTcpAbstractPacket *packet)
{
    QEXT_DECL_D(QEXTTcpPacketParser);
    QMutexLocker mutexLocker(&d->m_mutex);
    QByteArray stream = packet->stream();
    return socket->write(stream.data(), stream.size());
}


