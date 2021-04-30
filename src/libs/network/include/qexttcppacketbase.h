#ifndef QEXTTCPPACKETBASE_H
#define QEXTTCPPACKETBASE_H

#include <qextid.h>

#include <qextnetworkglobal.h>
#include <qexttcpserversocket.h>
#include <qexttcppacketvariant.h>

#include <QTcpSocket>
#include <QDateTime>

static const int QEXT_TCP_PACKET_HEADER_META_DATA_MAX_NUM = 256;

class QEXT_NETWORK_API QEXTTcpPacketHeaderBase
{
public:
    virtual ~QEXTTcpPacketHeaderBase() {}

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



class QEXT_NETWORK_API QEXTTcpPacketBase
{
public:
    virtual ~QEXTTcpPacketBase() {}

    virtual QEXTId socketId() const = 0;
    virtual QDateTime timestamp() const = 0;
    virtual bool isValid() const = 0;

    virtual QByteArray stream() const = 0;

    virtual QEXTTcpPacketHeaderBase *header() const = 0;
    virtual bool setHeader(QEXTTcpPacketHeaderBase *header) = 0;

    virtual QByteArray content() const = 0;
    virtual bool setContent(const QByteArray &content) = 0;

    virtual qint64 nextBlockSize() const = 0;
    virtual bool setNextBlockSize(qint64 size) = 0;

    static void printPacket(QEXTTcpPacketBase *packet) {
        qDebug() << "QEXTTcpPacketBase::printPacket():-----------------";
        QList<QString> dataList = packet->header()->headerList();
        for (int i = 0; i < dataList.size(); ++i) {
            QString name = dataList.at(i);
            qDebug() << QString("Packet-Header:[%1]=%2").arg(name).arg(packet->header()->headerData(name).toHostString());
        }
        qDebug() << QString("Packet-Content=%2").arg(packet->content().data());
    }
};



class QEXT_NETWORK_API QEXTTcpPacketParserBase
{
public:
    virtual ~QEXTTcpPacketParserBase() {}

    virtual QString name() const = 0;
    virtual QString errorString() const = 0;

    virtual bool checkIsSyncReplyPacket(QEXTTcpPacketBase *send, QEXTTcpPacketBase *rcv) const = 0;

    virtual bool isRequestPacket(QEXTTcpPacketBase *packet) const = 0;
    virtual bool setRequestPacket(QEXTTcpPacketBase *packet) = 0;

    virtual bool isReplyPacket(QEXTTcpPacketBase *packet) const = 0;
    virtual bool setReplyPacket(QEXTTcpPacketBase *packet) = 0;

    virtual bool isNotifyPacket(QEXTTcpPacketBase *packet) const = 0;
    virtual bool setNotifyPacket(QEXTTcpPacketBase *packet) = 0;

    virtual QEXTTcpPacketHeaderBase *createHeader() const = 0;
    virtual QEXTTcpPacketBase *createPacket(const QEXTId &socketId) const = 0;
    virtual QEXTTcpPacketBase *createReplyPacket(QEXTTcpPacketBase *rcv) const = 0;
    virtual QEXTTcpPacketParserBase *cloneParser() const = 0;

    virtual QEXTTcpPacketBase *readData(QEXTTcpSocket *socket, bool &success) = 0;
    virtual qint64 writeData(QEXTTcpSocket *socket, QEXTTcpPacketBase *packet) = 0;
};



class QEXTTcpClient;
class QEXTTcpClientProxy;
class QEXT_NETWORK_API QEXTTcpPacketDispatcherBase : public QObject
{
    Q_OBJECT
public:
    explicit QEXTTcpPacketDispatcherBase(QObject *parent = QEXT_NULLPTR) : QObject(parent) {}
    virtual ~QEXTTcpPacketDispatcherBase() {}

    virtual QEXTTcpClient *tcpClient() const = 0;
    virtual void setTcpClient(QEXTTcpClient *client) = 0;

    virtual QList<QEXTTcpClientProxy *> allTcpClientProxyList() const = 0;

    virtual QEXTTcpPacketBase *dequeuePacket() = 0;
    virtual void enqueuePacket(QEXTTcpPacketBase *packet) = 0;
    virtual int packetsCount() const = 0;

protected Q_SLOTS:
    virtual void dispatchPacket() {}
};

#endif // QEXTTCPPACKETBASE_H
