#include <qextTcpUtils.h>
#include <qextTcpPacketInterface.h>

#include <QDebug>

QEXTTcpUtils::QEXTTcpUtils()
{

}

QString QEXTTcpUtils::packetData(const QSharedPointer<QEXTTcpPacketInterface> &packet)
{
    QString packetData;
    if (!packet.isNull())
    {
        QList<QString> dataList = packet->header()->headerList();
        for (int i = 0; i < dataList.size(); ++i) {
            QString name = dataList.at(i);
            packetData.append(QString("Packet-Header:[%1]=%2\n").arg(name).arg(packet->header()->headerData(name).toHostString()));
        }
        packetData.append(QString("Packet-Content:hex=%2\n").arg(packet->content().toHex().data()));
        packetData.append(QString("Packet-Content:string=%2\n").arg(packet->content().data()));
    }
    return packetData;
}

QString QEXTTcpUtils::packetData(QEXTTcpPacketInterface *packet)
{
    QString packetData;
    if (packet)
    {
        QList<QString> dataList = packet->header()->headerList();
        for (int i = 0; i < dataList.size(); ++i) {
            QString name = dataList.at(i);
            packetData.append(QString("Packet-Header:[%1]=%2\n").arg(name).arg(packet->header()->headerData(name).toHostString()));
        }
        packetData.append(QString("Packet-Content:hex=%2\n").arg(packet->content().toHex().data()));
        packetData.append(QString("Packet-Content:string=%2\n").arg(packet->content().data()));
    }
    return packetData;
}

void QEXTTcpUtils::printPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet)
{
    qDebug() << "QEXTTcpUtils::printPacket():-----------------";
    if (!packet.isNull())
    {
        QList<QString> dataList = packet->header()->headerList();
        for (int i = 0; i < dataList.size(); ++i) {
            QString name = dataList.at(i);
            qDebug() << QString("Packet-Header:[%1]=%2").arg(name).arg(packet->header()->headerData(name).toHostString());
        }
        qDebug() << QString("Packet-Content:hex=%2").arg(packet->content().toHex().data());
        qDebug() << QString("Packet-Content:string=%2").arg(packet->content().data());
    }
}

void QEXTTcpUtils::printPacket(QEXTTcpPacketInterface *packet)
{
    qDebug() << "QEXTTcpUtils::printPacket():-----------------";
    if (packet)
    {
        QList<QString> dataList = packet->header()->headerList();
        for (int i = 0; i < dataList.size(); ++i) {
            QString name = dataList.at(i);
            qDebug() << QString("Packet-Header:[%1]=%2").arg(name).arg(packet->header()->headerData(name).toHostString());
        }
        qDebug() << QString("Packet-Content:hex=%2").arg(packet->content().toHex().data());
        qDebug() << QString("Packet-Content:string=%2").arg(packet->content().data());
    }
}
