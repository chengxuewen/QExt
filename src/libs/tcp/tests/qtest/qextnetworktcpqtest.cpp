#include <qexttcpclient.h>
#include <qexttcpserver.h>
#include <qexttcppacketparser.h>
#include <qexttcppacketdispatcher.h>
#include <qexttcptaskpool.h>

#include <QtTest>
#include <QString>
#include <QNetworkInterface>

class QEXTNetworkTcpQTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void simpleTcpTest();
};

void QEXTNetworkTcpQTest::simpleTcpTest()
{
    QEXTTcpPacketHeader::DataInfoVector headerDataInfoVector;
    headerDataInfoVector.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 32, "time"));
    headerDataInfoVector.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 16, "src"));
    headerDataInfoVector.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 8, "des"));
    QEXTTcpPacketParser *packetParser = new QEXTTcpPacketParser(headerDataInfoVector);
    QEXTTcpTaskPool *taskPool = new QEXTTcpTaskPool;
    QThread *serverThread = new QThread;
    QEXTTcpServer *tcpServer = new QEXTTcpServer(packetParser, taskPool);
    tcpServer->moveToThread(serverThread);
    connect(tcpServer, SIGNAL(destroyed(QObject*)), serverThread, SLOT(deleteLater()));
    serverThread->start();
    QVERIFY(tcpServer->listen(QHostAddress::Any));

    // find out which IP to connect to
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty()) {
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }
    QEXTTcpPacketDispatcher *packetDispatcher = new QEXTTcpPacketDispatcher;
    QThread *clientThread = new QThread;
    QEXTTcpClient *tcpClient = new QEXTTcpClient(packetParser->cloneParser(), packetDispatcher);
    tcpClient->moveToThread(clientThread);
    connect(tcpClient, SIGNAL(destroyed(QObject*)), clientThread, SLOT(deleteLater()));
    clientThread->start();
    tcpClient->startConnection(ipAddress, 8080);

    QEXTTcpPacketBase *packet = tcpClient->packetParser()->createPacket(tcpClient->socket()->identityId());
    packet->header()->setHeaderData("time", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz"));
    packet->header()->setHeaderData("src", QByteArray("Client"));
    packet->header()->setHeaderData("des", "Server");
    QByteArray data = QString("msg:test").toLatin1();
    packet->setContent(data);
    QEXTTcpPacketBase *rcv = QEXT_NULLPTR;
    QVERIFY(tcpClient->sendSyncRequestPacket(packet, &rcv));
    QVERIFY(rcv);
    delete rcv;

    serverThread->quit();
    serverThread->wait();
    tcpServer->deleteLater();

    clientThread->quit();
    clientThread->wait();
    tcpClient->deleteLater();
}

QTEST_APPLESS_MAIN(QEXTNetworkTcpQTest)

#include "qextnetworktcpqtest.moc"
