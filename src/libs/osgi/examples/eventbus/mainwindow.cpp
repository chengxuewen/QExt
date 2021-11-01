#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTKEventBus/QTKEventAdminBus>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(QTKEventAdminBus *bus, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_EventBus = bus;
    connectEvents();
}

MainWindow::~MainWindow()
{
    delete handler;
    delete ui;
}

void MainWindow::sendEvent()
{
    QString textToDisplay("Me: ");
    textToDisplay.append(ui->txtParameter->property("plainText").toString());
    ui->textBrowser->append(textToDisplay);

    // event bus starts here

    QVariantList localEventList;
    localEventList.append("QTK/remote/eventBus/comunication/receive/xmlrpc");

    QVariantList dataList;
    dataList.append("myUser");
    dataList.append(ui->txtParameter->property("plainText").toString());

    QTKDictionary dic;

    dic.insert("localEvent",localEventList);
    dic.insert("localData",dataList);

    QString value = "QTK/remote/eventBus/comunication/send/xmlrpc";
    QTKEvent event(value,dic);

    m_EventBus->sendEvent(event);
}

void MainWindow::updateMessage(QString message)
{
    ui->textBrowser->append(message);
}

void MainWindow::connectClient()
{
    bool result, resultClient, resultServer;
    resultClient = m_EventBus->createServer("XMLRPC", ui->portLineEdit->text().toInt());
    m_EventBus->startListen();
    resultServer = m_EventBus->createClient("XMLRPC", ui->hostLineEdit->text(), ui->portLineEdit->text().toInt());
    result = resultClient && resultServer;
    if(result) {
        ui->hostLineEdit->setEnabled(false);
        ui->portLineEdit->setEnabled(false);
        ui->connectButton->setEnabled(false);

        ui->txtParameter->setEnabled(true);
        ui->btnSend->setEnabled(true);
    }
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::connectEvents()
{
    handler = new QTKEventDemo();
    connect(ui->btnSend, SIGNAL(released()), this, SLOT(sendEvent()));
    connect(handler, SIGNAL(updateMessageSignal(QString)), this, SLOT(updateMessage(QString)));
    connect(ui->connectButton, SIGNAL(released()), this, SLOT(connectClient()));

    qDebug() << "connectEvents";
    m_EventBus->publishSignal(handler, "receiveEventSignal(QVariantList)", "QTK/remote/eventBus/comunication/receive/xmlrpc");
    QTKDictionary dic;
    dic.insert("event.topics","QTK/remote/eventBus/comunication/receive/xmlrpc");
    m_EventBus->subscribeSlot(handler, "receiveEvent(QVariantList)", dic);
}


void QTKEventDemo::receiveEvent(QVariantList l)
{
    QString value;
    value.append(l.at(0).toString());
    value.append(": ");
    value.append(l.at(1).toString());
    emit updateMessageSignal(value);
}
