#include <qextTcpUtils.h>
#include <qextTcpPacketInterface.h>

#include <QDebug>

QEXTTcpUtils::QEXTTcpUtils()
{

}

QString QEXTTcpUtils::packetData(const QSharedPointer<QEXTTcpPacketInterface> &packet)
{
    return QEXTTcpUtils::packetData(packet.data());
}

QString QEXTTcpUtils::packetData(QEXTTcpPacketInterface *packet)
{
    QString packetData;
    QList<QString> dataList = packet->header()->headerList();
    for (int i = 0; i < dataList.size(); ++i) {
        QString name = dataList.at(i);
        packetData.append(QString("Packet-Header:[%1]=%2\n").arg(name).arg(packet->header()->headerData(name).toHostString()));
    }
    packetData.append(QString("Packet-Content=%2\n").arg(packet->content().data()));
    return packetData;
}

void QEXTTcpUtils::printPacket(const QSharedPointer<QEXTTcpPacketInterface> &packet)
{
    QEXTTcpUtils::printPacket(packet.data());
}

void QEXTTcpUtils::printPacket(QEXTTcpPacketInterface *packet)
{
    qDebug() << "QEXTTcpUtils::printPacket():-----------------";
    QList<QString> dataList = packet->header()->headerList();
    for (int i = 0; i < dataList.size(); ++i) {
        QString name = dataList.at(i);
        qDebug() << QString("Packet-Header:[%1]=%2").arg(name).arg(packet->header()->headerData(name).toHostString());
    }
    qDebug() << QString("Packet-Content=%2").arg(packet->content().data());
}
