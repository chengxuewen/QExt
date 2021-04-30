#include "smainwindow.h"
#include "ui_smainwindow.h"

#include <QNetworkInterface>
#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>
#include <QThread>

#include <qexttcppacketparser.h>
#include <qexttcptaskpool.h>

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
    headerDataInfoVector.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 32, "time"));
    headerDataInfoVector.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 16, "src"));
    headerDataInfoVector.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 8, "des"));
    QEXTTcpPacketParser *packetParser = new QEXTTcpPacketParser(headerDataInfoVector);
    QEXTTcpTaskPool *taskPool = new QEXTTcpTaskPool;
    m_tcpServer = new QEXTTcpServer(packetParser, taskPool, this);
    connect(m_tcpServer, SIGNAL(socketError(QEXTId,QAbstractSocket::SocketError)),
            this, SLOT(displaySocketError(QEXTId,QAbstractSocket::SocketError)));
    connect(m_tcpServer, SIGNAL(socketMessage(QEXTId,QString)),
            this, SLOT(displaySocketMessage(QEXTId,QString)));
    connect(m_tcpServer, SIGNAL(transferError(QEXTTcpSocket::TransferErrorType)),
            this, SLOT(displayTransferError(QEXTTcpSocket::TransferErrorType)));
}

SMainWindow::~SMainWindow()
{
    delete ui;
}

void SMainWindow::displayTransferError(const QEXTTcpSocket::TransferErrorType &error)
{
    qDebug() << "SMainWindow::displayTransferError():--------------------";
    qDebug() << "socketError=" << error;
    qDebug() << "errorString=" << QEXTTcpSocket::transferErrorString(error);
}

void SMainWindow::displaySocketError(const QEXTId &socketId, const QAbstractSocket::SocketError &error)
{
    qDebug() << "CMainWindow::displaySocketError():--------------------";
    qDebug() << "socketError=" << error;
    qDebug() << "socketId=" << socketId.toString();
}

void SMainWindow::displaySocketMessage(const QEXTId &socketId, const QString &msg)
{
    qDebug() << "CMainWindow::displaySocketMessage():--------------------";
    qDebug() << "msg=" << msg;
    qDebug() << "socketId=" << socketId.toString();
}

void SMainWindow::on_pushButton_ctrl_clicked()
{
    if (m_tcpServer->isListening()) {
        m_tcpServer->close();
        ui->pushButton_ctrl->setText("Start Listen");
        QString closeMsg = QString("Server close listen!");
        ui->textBrowser_receivedMsg->append(closeMsg);
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
            ui->textBrowser_receivedMsg->append(listenMsg);
            QMessageBox::information(this, "tcp server listen!",
                                     QString("tcp server listen success"),
                                     QMessageBox::Ok);
        }
    }
}

void SMainWindow::on_pushButton_clearReceivedMsg_clicked()
{
    ui->textBrowser_receivedMsg->clear();
}

