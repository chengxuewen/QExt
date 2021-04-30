#include <qexttcpclient.h>
#include <qexttcpserver.h>
#include <qexttcppacketparser.h>
#include <qexttcppacketdispatcher.h>
#include <qexttcptaskpool.h>

#include <gtest/gtest.h>

#include <QNetworkInterface>
#include <QApplication>
#include <QThread>

class QEXTNetworkTcpGTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        QEXTTcpPacketHeader::DataInfoVector headerDataInfoVector;
        headerDataInfoVector.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 32, "time"));
        headerDataInfoVector.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 16, "src"));
        headerDataInfoVector.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 8, "des"));
        QEXTTcpPacketParser *packetParser = new QEXTTcpPacketParser(headerDataInfoVector);
        QEXTTcpTaskPool *taskPool = new QEXTTcpTaskPool;
        m_tcpServer = new QEXTTcpServer(packetParser, taskPool);
        m_serverThread = new QThread;
        m_tcpServer->moveToThread(m_serverThread);
        m_serverThread->start();

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
        m_tcpClient = new QEXTTcpClient(packetParser->cloneParser(), packetDispatcher);
        m_clientThread = new QThread;
        m_tcpClient->moveToThread(m_clientThread);
        m_clientThread->start();

        m_tcpClient->startConnection(ipAddress, 8080);
    }
    virtual void TearDown()
    {
        m_serverThread->quit();
        m_serverThread->wait();
        m_tcpServer->deleteLater();
        m_serverThread->deleteLater();

        m_clientThread->quit();
        m_clientThread->wait();
        m_tcpClient->deleteLater();
        m_clientThread->deleteLater();
    }
    virtual void TestBody()
    {
        //        ASSERT_TRUE(m_tcpServer->listen(QHostAddress::Any));

        //        QEXTTcpPacketBase *packet = m_tcpClient->packetParser()->createPacket(m_tcpClient->socket()->identityId());
        //        packet->header()->setHeaderData("time", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz"));
        //        packet->header()->setHeaderData("src", QByteArray("Client"));
        //        packet->header()->setHeaderData("des", "Server");
        //        QByteArray data = QString("msg:test").toLatin1();
        //        packet->setContent(data);
        //        QEXTTcpPacketBase *rcv = QEXT_NULLPTR;
        //        ASSERT_TRUE(m_tcpClient->sendSyncRequestPacket(packet, &rcv));
        //        ASSERT_TRUE(rcv);
        //        delete rcv;
    }
    QThread *m_serverThread;
    QThread *m_clientThread;
    QEXTTcpServer *m_tcpServer;
    QEXTTcpClient *m_tcpClient;
};

TEST_F(QEXTNetworkTcpGTest, simpleTcpTest)
{
    ASSERT_TRUE(m_tcpServer->listen(QHostAddress::Any));

    QEXTTcpPacketBase *packet = m_tcpClient->packetParser()->createPacket(m_tcpClient->socket()->identityId());
    packet->header()->setHeaderData("time", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz"));
    packet->header()->setHeaderData("src", QByteArray("Client"));
    packet->header()->setHeaderData("des", "Server");
    QByteArray data = QString("msg:test").toLatin1();
    packet->setContent(data);
    QEXTTcpPacketBase *rcv = QEXT_NULLPTR;
    ASSERT_TRUE(m_tcpClient->sendSyncRequestPacket(packet, &rcv));
    ASSERT_TRUE(rcv);
    delete rcv;
}

int main(int argc,char ** argv)
{
    QApplication app(argc,argv);
    app.processEvents();

    testing::InitGoogleTest(&argc,argv);

    QEXTNetworkTcpGTest qextNetworkTcpGTest;

    return RUN_ALL_TESTS();
}

//GTEST_API_ int main(int argc, char **argv)
//{
//    QApplication app(argc, argv);
//    app.exec();

//    testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}
