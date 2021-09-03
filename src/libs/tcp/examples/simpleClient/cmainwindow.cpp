#include "cmainwindow.h"
#include "ui_cmainwindow.h"

#include <qextTcpPacketDispatcher.h>
#include <qextTcpPacketParser.h>
#include <qextTcpClient.h>
#include <qextTcpUtils.h>

#include <qextnetworkutils.h>

#include <QNetworkInterface>
#include <QDataStream>
#include <QMessageBox>
#include <QDateTime>
#include <QMetaEnum>
#include <QDateTime>
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
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address())
        {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
    {
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }
    ui->lineEdit_serverIP->setText(ipAddress);
    ui->lineEdit_serverPort->setText("8080");

    QEXTTcpPacketHeader::DataInfoVector extraHeaderDataInfo;
    extraHeaderDataInfo.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 16, "src"));
    extraHeaderDataInfo.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 8, "des"));
    QSharedPointer<QEXTTcpPacketParserInterface> packetParser(new QEXTTcpPacketParser(extraHeaderDataInfo));
    m_tcpClient.reset(new QEXTTcpClient(packetParser));
    QSharedPointer<QEXTTcpPacketDispatcher> packetDispatcher(new QEXTTcpPacketDispatcher(m_tcpClient->socket()));
    m_tcpClient->setPacketDispatcher(packetDispatcher);
    m_thread = new QThread(this);
    m_tcpClient->moveToThread(m_thread);
    connect(m_tcpClient.data(), SIGNAL(socketError(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    connect(m_tcpClient.data(), SIGNAL(transferError(QEXTTcpSocket::TransferErrorType)), this, SLOT(onTransferError(QEXTTcpSocket::TransferErrorType)));
    connect(m_tcpClient.data(), SIGNAL(packetReady()), this, SLOT(receiveReplyPacket()));
    connect(m_tcpClient->socket().data(), SIGNAL(connected()), this, SLOT(onSocketConnected()));
    connect(m_tcpClient->socket().data(), SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
    connect(m_tcpClient->socket().data(), SIGNAL(newPacketSend(QString)), this, SLOT(onNewPacketSend(QString)));
    connect(m_tcpClient->socket().data(), SIGNAL(newPacketReceived(QString)), this, SLOT(onNewPacketReceived(QString)));
    m_thread->start();
}

CMainWindow::~CMainWindow()
{
    m_thread->quit();
    m_thread->wait();
    delete ui;
}

void CMainWindow::onSocketError(QAbstractSocket::SocketError socketError)
{
    QString text = "SocketError:" + QString::number(socketError) + " " + m_tcpClient->socket()->errorString();
    ui->textBrowserMsg->append(text);
}

void CMainWindow::onTransferError(const QEXTTcpSocket::TransferErrorType &error)
{
    QString text = "TransferError:" + text + " " + QEXTTcpSocket::transferErrorText(error);
    ui->textBrowserMsg->append(text);
}

void CMainWindow::onSocketConnected()
{
    ui->pushButton_ctrl->setText("Disconnect");
    ui->textBrowserMsg->append("Socket connected!");
}

void CMainWindow::onSocketDisconnected()
{
    ui->pushButton_ctrl->setText("Connect");
    ui->textBrowserMsg->append("Socket disconnected!");
}

void CMainWindow::onNewPacketSend(const QString &data)
{
    ui->textBrowserSend->append("onNewPacketSend:" + QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss:zzz"));
    ui->textBrowserSend->append(data);
}

void CMainWindow::onNewPacketReceived(const QString &data)
{
    ui->textBrowserReceive->append("onNewPacketReceived:" + QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss:zzz"));
    ui->textBrowserReceive->append(data);
}

void CMainWindow::receiveReplyPacket()
{
    QSharedPointer<QEXTTcpPacketInterface> packet = m_tcpClient->dequeuePacket();
    if (!packet.isNull())
    {
        qDebug() << "CMainWindow::receiveReplyPacket():--------------------";
        QEXTTcpUtils::printPacket(packet);
    }
}

void CMainWindow::on_pushButton_ctrl_clicked()
{
    if (m_tcpClient->isSocketConnected())
    {
        m_tcpClient->closeConnection();
        ui->pushButton_ctrl->setText("Connect");
    }
    else
    {
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

    QSharedPointer<QEXTTcpPacketInterface> packet = m_tcpClient->packetParser()->createPacket();
    packet->header()->setHeaderData("src", QByteArray("Client"));
    packet->header()->setHeaderData("des", "Server");
    QByteArray data("ssddff");
    data.append(str);
    str += "-";
    packet->setContent(data);
    QSharedPointer<QEXTTcpPacketInterface> rcv;
    qDebug() << m_tcpClient->sendNotify(packet);
//    qDebug() << m_tcpClient->sendRequest(packet);
//    qDebug() << m_tcpClient->sendRequestSync(packet, rcv);
    if (!rcv.isNull())
    {
        QEXTTcpUtils::printPacket(rcv);
    }
//    qDebug() << m_tcpClient->sendReply(packet, packet);
}
