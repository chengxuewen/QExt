#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include <qexttcppacketdispatcher.h>
#include <qexttcppacketparser.h>
#include <qexttcpclient.h>
#include <qextnetworkutils.h>

#include <QNetworkInterface>
#include <QDataStream>
#include <QMessageBox>
#include <QDebug>
#include <QThread>

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

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
    ui->lineEdit_serverIP->setText(ipAddress);
    ui->lineEdit_serverPort->setText("8080");

    QEXTTcpPacketHeader::DataInfoVector extraHeaderDataInfo;
    extraHeaderDataInfo.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 32, "time"));
    extraHeaderDataInfo.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 16, "src"));
    extraHeaderDataInfo.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 8, "des"));
    QEXTTcpPacketParser *packetParser = new QEXTTcpPacketParser(extraHeaderDataInfo);
    QEXTTcpPacketDispatcher *packetDispatcher = new QEXTTcpPacketDispatcher;
    m_thread = new QThread(this);
    m_tcpClient = new QEXTTcpClient(packetParser, packetDispatcher);
    m_tcpClient->moveToThread(m_thread);
    connect(m_tcpClient, SIGNAL(socketError(QAbstractSocket::SocketError)),
            this, SLOT(displaySocketError(QAbstractSocket::SocketError)));
    connect(m_tcpClient, SIGNAL(transferError(QEXTTcpSocket::TransferErrorType)),
            this, SLOT(displayTransferError(QEXTTcpSocket::TransferErrorType)));
    connect(m_tcpClient, SIGNAL(newReceivePacketReady()), this, SLOT(receiveReplyPacket()));
    m_thread->start();
}

CMainWindow::~CMainWindow()
{
    m_thread->quit();
    m_thread->wait();
    delete ui;
}

void CMainWindow::displaySocketError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "CMainWindow::displaySocketError():--------------------";
    qDebug() << "socketError=" << socketError;
    qDebug() << "errorString=" << m_tcpClient->socket()->errorString();
}

void CMainWindow::displayTransferError(const QEXTTcpSocket::TransferErrorType &error)
{
    qDebug() << "CMainWindow::displayTransferError():--------------------";
    qDebug() << "transferError=" << error;
    qDebug() << "errorString=" << QEXTTcpSocket::transferErrorString(error);
}

void CMainWindow::receiveReplyPacket()
{
    QEXTTcpPacketBase *packet = m_tcpClient->dequeuePacket();
    if (packet) {
        QEXTTcpPacketBase::printPacket(packet);
    }
}

void CMainWindow::on_pushButton_ctrl_clicked()
{
    if (m_tcpClient->isSocketConnected()) {
        m_tcpClient->closeConnection();
        ui->pushButton_ctrl->setText("Connect");
    } else {
        m_tcpClient->abortConnection();
        m_tcpClient->startConnection(ui->lineEdit_serverIP->text(),
                                     ui->lineEdit_serverPort->text().toInt());
        ui->pushButton_ctrl->setText("Disconnect");
    }
}

void CMainWindow::on_pushButton_send_clicked()
{
    qDebug() << "CMainWindow::on_pushButton_send_clicked()----------------";
    static QString str = "-";

    QEXTTcpPacketBase *packet = m_tcpClient->packetParser()->createPacket(m_tcpClient->socket()->identityId());
    packet->header()->setHeaderData("time", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz"));
    packet->header()->setHeaderData("src", QByteArray("Client"));
    packet->header()->setHeaderData("des", "Server");
    QByteArray data("ssddff");
    data.append(str);
    str += "-";
    packet->setContent(data);
    QEXTTcpPacketBase *rcv = QEXT_NULLPTR;
    qDebug() << m_tcpClient->sendSyncRequestPacket(packet, &rcv);
    if (rcv) {
        QEXTTcpPacketBase::printPacket(rcv);
        delete rcv;
    }

//    for (int i = 0; i < 100; ++i) {
//        QEXTTcpPacketBase *packet = m_tcpClient->packetParser()->createPacket(m_tcpClient->socket()->identityId());
//        packet->header()->setHeaderData("time", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz"));
//        packet->header()->setHeaderData("src", QByteArray("Client"));
//        packet->header()->setHeaderData("des", "Server");
//        QByteArray data = QString("msg:%1").arg(i).toLatin1();
//        packet->setContent(data);
//        qDebug() << m_tcpClient->sendNotifyPacket(packet);
//    }
}
