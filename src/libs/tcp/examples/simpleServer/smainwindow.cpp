#include "smainwindow.h"
#include "ui_smainwindow.h"
#include "ssocketmsgbrowser.h"

#include <QNetworkInterface>
#include <QHostAddress>
#include <QMessageBox>
#include <QDateTime>
#include <QDebug>
#include <QThread>

#include <qextTcpPacketParser.h>

SMainWindow::SMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SMainWindow)
{
    ui->setupUi(this);

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

    QEXTTcpPacketHeader::DataInfoVector headerDataInfoVector;
    headerDataInfoVector.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 16, "src"));
    headerDataInfoVector.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 8, "des"));
    m_tcpServer.reset(new QEXTTcpServer);
    m_tcpServer->setPacketParser(QSharedPointer<QEXTTcpPacketParser>(new QEXTTcpPacketParser(headerDataInfoVector)));
    m_tcpServer->setPacketDispatcherFactory(QSharedPointer<QEXTTcpPacketDispatcherFactory>(new QEXTTcpPacketDispatcherFactory));
    connect(m_tcpServer.data(), SIGNAL(socketError(QWeakPointer<QEXTTcpSocket>,QAbstractSocket::SocketError)),
            this, SLOT(onSocketError(QWeakPointer<QEXTTcpSocket>,QAbstractSocket::SocketError)));
    connect(m_tcpServer.data(), SIGNAL(serverMessage(QString)), this, SLOT(onServerMessageReceived(QString)));
    connect(m_tcpServer.data(), SIGNAL(socketConnected(QWeakPointer<QEXTTcpSocket>)), this, SLOT(onSocketConnected(QWeakPointer<QEXTTcpSocket>)));
    connect(m_tcpServer.data(), SIGNAL(socketDisconnected(QWeakPointer<QEXTTcpSocket>)), this, SLOT(onSocketDisCnnected(QWeakPointer<QEXTTcpSocket>)));
}

SMainWindow::~SMainWindow()
{
    delete ui;
}

void SMainWindow::onSocketError(const QWeakPointer<QEXTTcpSocket> &socket, const QAbstractSocket::SocketError &error)
{
    QSharedPointer<QEXTTcpSocket> sharedSocker(socket);
    qDebug() << "SMainWindow::onSocketError():" << sharedSocker->errorString();
}

void SMainWindow::onServerMessageReceived(const QString &msg)
{
    ui->textEditServerMsg->append("onServerMessageReceived:" + QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss:zzz"));
    ui->textEditServerMsg->append(msg);
}

void SMainWindow::onSocketConnected(const QWeakPointer<QEXTTcpSocket> &socket)
{
    QSharedPointer<QEXTTcpSocket> sharedSocket(socket);
    SSocketMsgBrowser *msgBrowser = new SSocketMsgBrowser(ui->tabWidgetSocket);
    connect(sharedSocket.data(), SIGNAL(newPacketReceived(QString)), msgBrowser, SLOT(onNewPacketReceived(QString)));
    connect(sharedSocket.data(), SIGNAL(newPacketSend(QString)), msgBrowser, SLOT(onNewPacketSend(QString)));
    connect(sharedSocket.data(), SIGNAL(transferErrorString(QString)), msgBrowser, SLOT(onTransferErrorString(QString)));
    connect(sharedSocket.data(), SIGNAL(disconnected()), msgBrowser, SLOT(deleteLater()));
    ui->tabWidgetSocket->addTab(msgBrowser, sharedSocket->identityId().toString());
}

void SMainWindow::onSocketDisCnnected(const QWeakPointer<QEXTTcpSocket> &socket)
{

}

void SMainWindow::on_pushButton_ctrl_clicked()
{
    if (m_tcpServer->isListening()) {
        m_tcpServer->close();
        ui->pushButton_ctrl->setText("Start Listen");
        QString closeMsg = QString("Server close listen!");
        ui->textEditServerMsg->append(closeMsg);
    } else {
        bool ret = m_tcpServer->listen(QHostAddress::Any, ui->lineEdit_serverPort->text().toInt());
        if (!ret) {
            ui->pushButton_ctrl->setText("Start Listen");
            QMessageBox::warning(this, "tcp server listen!",
                                 QString("tcp server listen failed for %1").arg(m_tcpServer->errorString()),
                                 QMessageBox::Ok);
        } else {
            ui->pushButton_ctrl->setText("Stop Listen");
            QString listenMsg = QString("Server start listen:IP %1, Port %2")
                    .arg(m_tcpServer->serverAddress().toString()).arg(m_tcpServer->serverPort());
            ui->textEditServerMsg->append(listenMsg);
            QMessageBox::information(this, "tcp server listen!",
                                     QString("tcp server listen success"),
                                     QMessageBox::Ok);
        }
    }
}

void SMainWindow::on_pushButton_clearReceivedMsg_clicked()
{
    ui->textEditServerMsg->clear();
}

