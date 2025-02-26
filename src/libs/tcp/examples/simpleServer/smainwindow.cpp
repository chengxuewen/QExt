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

struct STcpFactory : public QExtTcpFactory
{
    QSharedPointer<QExtTcpPacketDispatcher> createPacketDispatcher(const QSharedPointer<QExtTcpSocket> &socket);
    QSharedPointer<QExtTcpPacketParserInterface> createPacketParser();

    QExtTcpTask *createTask(const QSharedPointer<QExtTcpPacketDispatcher> &dispatcher, int function);
    QExtTcpTask *createTask(const QSharedPointer<QExtTcpPacketDispatcher> &dispatcher, const QSharedPointer<QExtTcpPacketInterface> &packet);

    QSharedPointer<QExtTcpFactory> clone();
};


QSharedPointer<QExtTcpPacketDispatcher> STcpFactory::createPacketDispatcher(const QSharedPointer<QExtTcpSocket> &socket)
{
    return QExtTcpFactory::createPacketDispatcher(socket);
}

QSharedPointer<QExtTcpPacketParserInterface> STcpFactory::createPacketParser()
{
    QExtTcpPacketHeader::DataInfoVector headerDataInfoVector;
    headerDataInfoVector.append(QExtTcpPacketHeader::DataInfoPair(QExtTcpPacketVariant::Data_chars + 16, "src"));
    headerDataInfoVector.append(QExtTcpPacketHeader::DataInfoPair(QExtTcpPacketVariant::Data_chars + 8, "des"));
    return QSharedPointer<QExtTcpPacketParserInterface>(new QExtTcpPacketParser(headerDataInfoVector));
}

QExtTcpTask *STcpFactory::createTask(const QSharedPointer<QExtTcpPacketDispatcher> &dispatcher, int function)
{
    return QExtTcpFactory::createTask(dispatcher, function);
}

QExtTcpTask *STcpFactory::createTask(const QSharedPointer<QExtTcpPacketDispatcher> &dispatcher,
                                     const QSharedPointer<QExtTcpPacketInterface> &packet)
{
    return QExtTcpFactory::createTask(dispatcher, packet);
}

QSharedPointer<QExtTcpFactory> STcpFactory::clone()
{
    return QSharedPointer<QExtTcpFactory>(new STcpFactory);
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

    m_tcpServer.reset(new QExtTcpServer);
    m_tcpServer->setTcpFactory(QSharedPointer<QExtTcpFactory>(new STcpFactory));
    connect(m_tcpServer.data(), SIGNAL(socketError(QSharedPointer<QExtTcpSocket>, QAbstractSocket::SocketError)),
            this, SLOT(onSocketError(QSharedPointer<QExtTcpSocket>, QAbstractSocket::SocketError)));
    connect(m_tcpServer.data(), SIGNAL(serverMessage(QString)),
            this, SLOT(onServerMessageReceived(QString)));
    connect(m_tcpServer.data(), SIGNAL(socketConnected(QSharedPointer<QExtTcpSocket>)),
            this, SLOT(onSocketConnected(QSharedPointer<QExtTcpSocket>)));
    connect(m_tcpServer.data(), SIGNAL(socketDisconnected(QSharedPointer<QExtTcpSocket>)),
            this, SLOT(onSocketDisConected(QSharedPointer<QExtTcpSocket>)));
}

SMainWindow::~SMainWindow()
{
    delete ui;
}

void SMainWindow::onSocketError(const QSharedPointer<QExtTcpSocket> &socket, const QAbstractSocket::SocketError &error)
{
    qDebug() << "SMainWindow::onSocketError():" << socket->errorString();
}

void SMainWindow::onServerMessageReceived(const QString &msg)
{
    ui->textEditServerMsg->append("onServerMessageReceived:" + QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss:zzz"));
    ui->textEditServerMsg->append(msg);
}

void SMainWindow::onSocketConnected(const QSharedPointer<QExtTcpSocket> &socket)
{
    SSocketMsgBrowser *msgBrowser = new SSocketMsgBrowser(ui->tabWidgetSocket);
    connect(socket.data(), SIGNAL(newPacketReceived(QString)), msgBrowser, SLOT(onNewPacketReceived(QString)));
    connect(socket.data(), SIGNAL(newPacketSend(QString)), msgBrowser, SLOT(onNewPacketSend(QString)));
    connect(socket.data(), SIGNAL(transferErrorString(QString)), msgBrowser, SLOT(onTransferErrorString(QString)));
    connect(socket.data(), SIGNAL(disconnected()), msgBrowser, SLOT(deleteLater()));
    ui->tabWidgetSocket->addTab(msgBrowser, socket->identityId().toString());
}

void SMainWindow::onSocketDisConected(const QSharedPointer<QExtTcpSocket> &socket)
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

