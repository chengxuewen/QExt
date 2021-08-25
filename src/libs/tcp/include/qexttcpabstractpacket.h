#ifndef QEXTTCPABSTRACTPACKET_H
#define QEXTTCPABSTRACTPACKET_H

#include <qextid.h>

#include <qexttcpglobal.h>
#include <qexttcpserversocket.h>
#include <qexttcppacketvariant.h>

#include <QTcpSocket>
#include <QDateTime>



static const int QEXT_TCP_PACKET_HEADER_META_DATA_MAX_NUM = 256;

class QEXT_TCP_API QEXTTcpAbstractPacketHeader
{
public:
    virtual ~QEXTTcpAbstractPacketHeader() {}

    virtual quint16 headerSize() const = 0;
    virtual quint16 contentSize() const = 0;
    virtual void setContentSize(const quint16 &size) = 0;

    virtual QByteArray stream() const = 0;
    virtual bool setStream(const QByteArray &stream) = 0;

    virtual bool isHeaderDataExist(const QString &name) const = 0;
    virtual QList<QString> headerList() const = 0;
    virtual QEXTTcpPacketVariant headerData(const QString &name) const = 0;
    virtual bool setHeaderData(const QString &name, const QEXTTcpPacketVariant &data) = 0;
};



class QEXT_TCP_API QEXTTcpAbstractPacket
{
public:
    virtual ~QEXTTcpAbstractPacket() {}

    virtual QEXTId socketId() const = 0;
    virtual QDateTime timestamp() const = 0;
    virtual bool isValid() const = 0;

    virtual QByteArray stream() const = 0;

    virtual QEXTTcpAbstractPacketHeader *header() const = 0;
    virtual bool setHeader(QEXTTcpAbstractPacketHeader *header) = 0;

    virtual QByteArray content() const = 0;
    virtual bool setContent(const QByteArray &content) = 0;

    virtual qint64 nextBlockSize() const = 0;
    virtual bool setNextBlockSize(qint64 size) = 0;

    static void printPacket(QEXTTcpAbstractPacket *packet) {
        qDebug() << "QEXTTcpAbstractPacket::printPacket():-----------------";
        QList<QString> dataList = packet->header()->headerList();
        for (int i = 0; i < dataList.size(); ++i) {
            QString name = dataList.at(i);
            qDebug() << QString("Packet-Header:[%1]=%2").arg(name).arg(packet->header()->headerData(name).toHostString());
        }
        qDebug() << QString("Packet-Content=%2").arg(packet->content().data());
    }
};



class QEXT_TCP_API QEXTTcpAbstractPacketParser
{
public:
    virtual ~QEXTTcpAbstractPacketParser() {}

    virtual QString name() const = 0;
    virtual QString errorString() const = 0;

    virtual bool checkIsSyncReplyPacket(QEXTTcpAbstractPacket *send, QEXTTcpAbstractPacket *rcv) const = 0;

    virtual bool isRequestPacket(QEXTTcpAbstractPacket *packet) const = 0;
    virtual bool setRequestPacket(QEXTTcpAbstractPacket *packet) = 0;

    virtual bool isReplyPacket(QEXTTcpAbstractPacket *packet) const = 0;
    virtual bool setReplyPacket(QEXTTcpAbstractPacket *packet) = 0;

    virtual bool isNotifyPacket(QEXTTcpAbstractPacket *packet) const = 0;
    virtual bool setNotifyPacket(QEXTTcpAbstractPacket *packet) = 0;

    virtual QEXTTcpAbstractPacketHeader *createHeader() const = 0;
    virtual QEXTTcpAbstractPacket *createPacket(const QEXTId &socketId) const = 0;
    virtual QEXTTcpAbstractPacket *createReplyPacket(QEXTTcpAbstractPacket *rcv) const = 0;
    virtual QEXTTcpAbstractPacketParser *cloneParser() const = 0;

    virtual QEXTTcpAbstractPacket *readData(QEXTTcpSocket *socket, bool &success) = 0;
    virtual qint64 writeData(QEXTTcpSocket *socket, QEXTTcpAbstractPacket *packet) = 0;
};



class QEXTTcpClient;
class QEXTTcpClientProxy;
class QEXT_TCP_API QEXTTcpAbstractPacketDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit QEXTTcpAbstractPacketDispatcher(QObject *parent = QEXT_DECL_NULLPTR) : QObject(parent) {}
    virtual ~QEXTTcpAbstractPacketDispatcher() {}

    virtual QEXTTcpClient *tcpClient() const = 0;
    virtual void setTcpClient(QEXTTcpClient *client) = 0;

    virtual QList<QEXTTcpClientProxy *> allTcpClientProxyList() const = 0;

    virtual QEXTTcpAbstractPacket *dequeuePacket() = 0;
    virtual void enqueuePacket(QEXTTcpAbstractPacket *packet) = 0;
    virtual int packetsCount() const = 0;

protected Q_SLOTS:
    virtual void dispatchPacket() {}
};



#endif // QEXTTCPABSTRACTPACKET_H
