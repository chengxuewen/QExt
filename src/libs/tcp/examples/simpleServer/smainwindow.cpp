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
#include <qextTcpFactory.h>

struct STcpFactory : public QEXTTcpFactory
{
    QSharedPointer<QEXTTcpPacketDispatcher> createPacketDispatcher(const QSharedPointer<QEXTTcpSocket> &socket);
    QSharedPointer<QEXTTcpPacketParserInterface> createPacketParser();

    QEXTTcpTask *createTask(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher, int function);
    QEXTTcpTask *createTask(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher, const QSharedPointer<QEXTTcpPacketInterface> &packet);

    QSharedPointer<QEXTTcpFactory> clone();
};


QSharedPointer<QEXTTcpPacketDispatcher> STcpFactory::createPacketDispatcher(const QSharedPointer<QEXTTcpSocket> &socket)
{

}

QSharedPointer<QEXTTcpPacketParserInterface> STcpFactory::createPacketParser()
{
    QEXTTcpPacketHeader::DataInfoVector headerDataInfoVector;
    headerDataInfoVector.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 16, "src"));
    headerDataInfoVector.append(QEXTTcpPacketHeader::DataInfoPair(QEXTTcpPacketVariant::Data_chars + 8, "des"));
    return QSharedPointer<QEXTTcpPacketParserInterface>(new QEXTTcpPacketParser(headerDataInfoVector));
}

QEXTTcpTask *STcpFactory::createTask(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher, int function)
{

}

QEXTTcpTask *STcpFactory::createTask(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher, const QSharedPointer<QEXTTcpPacketInterface> &packet)
{

}

QSharedPointer<QEXTTcpFactory> STcpFactory::clone()
{
    return QSharedPointer<QEXTTcpFactory>(new STcpFactory);
}




SMainWindow::SMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SMainWindow)
{
    ui->setupUi(this);

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

    m_tcpServer.reset(new QEXTTcpServer);
    m_tcpServer->setTcpFactory(QSharedPointer<QEXTTcpFactory>(new STcpFactory));
    connect(m_tcpServer.data(), SIGNAL(socketError(QSharedPointer<QEXTTcpSocket>, QAbstractSocket::SocketError)),
            this, SLOT(onSocketError(QSharedPointer<QEXTTcpSocket>, QAbstractSocket::SocketError)));
    connect(m_tcpServer.data(), SIGNAL(serverMessage(QString)),
            this, SLOT(onServerMessageReceived(QString)));
    connect(m_tcpServer.data(), SIGNAL(socketConnected(QSharedPointer<QEXTTcpSocket>)),
            this, SLOT(onSocketConnected(QSharedPointer<QEXTTcpSocket>)));
    connect(m_tcpServer.data(), SIGNAL(socketDisconnected(QSharedPointer<QEXTTcpSocket>)),
            this, SLOT(onSocketDisConected(QSharedPointer<QEXTTcpSocket>)));
}

SMainWindow::~SMainWindow()
{
    delete ui;
}

void SMainWindow::onSocketError(const QSharedPointer<QEXTTcpSocket> &socket, const QAbstractSocket::SocketError &error)
{
    qDebug() << "SMainWindow::onSocketError():" << socket->errorString();
}

void SMainWindow::onServerMessageReceived(const QString &msg)
{
    ui->textEditServerMsg->append("onServerMessageReceived:" + QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss:zzz"));
    ui->textEditServerMsg->append(msg);
}

void SMainWindow::onSocketConnected(const QSharedPointer<QEXTTcpSocket> &socket)
{
    SSocketMsgBrowser *msgBrowser = new SSocketMsgBrowser(ui->tabWidgetSocket);
    connect(socket.data(), SIGNAL(newPacketReceived(QString)), msgBrowser, SLOT(onNewPacketReceived(QString)));
    connect(socket.data(), SIGNAL(newPacketSend(QString)), msgBrowser, SLOT(onNewPacketSend(QString)));
    connect(socket.data(), SIGNAL(transferErrorString(QString)), msgBrowser, SLOT(onTransferErrorString(QString)));
    connect(socket.data(), SIGNAL(disconnected()), msgBrowser, SLOT(deleteLater()));
    ui->tabWidgetSocket->addTab(msgBrowser, socket->identityId().toString());
}

void SMainWindow::onSocketDisConected(const QSharedPointer<QEXTTcpSocket> &socket)
{

}

void SMainWindow::on_pushButton_ctrl_clicked()
{
    if (m_tcpServer->isListening())
    {
        m_tcpServer->close();
        ui->pushButton_ctrl->setText("Start Listen");
        QString closeMsg = QString("Server close listen!");
        ui->textEditServerMsg->append(closeMsg);
    }
    else
    {
        bool ret = m_tcpServer->listen(QHostAddress::Any, ui->lineEdit_serverPort->text().toInt());
        if (!ret)
        {
            ui->pushButton_ctrl->setText("Start Listen");
            QMessageBox::warning(this, "tcp server listen!",
                                 QString("tcp server listen failed for %1").arg(m_tcpServer->errorString()),
                                 QMessageBox::Ok);
        }
        else
        {
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

