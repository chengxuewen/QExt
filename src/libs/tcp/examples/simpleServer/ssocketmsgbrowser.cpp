#include "ssocketmsgbrowser.h"
#include "ui_ssocketmsgbrowser.h"

#include <QDateTime>

SSocketMsgBrowser::SSocketMsgBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SSocketMsgBrowser)
{
    ui->setupUi(this);
}

SSocketMsgBrowser::~SSocketMsgBrowser()
{
    delete ui;
}

void SSocketMsgBrowser::onNewPacketReceived(const QString &data)
{
    ui->textBrowserRcv->append("onNewPacketReceived:" + QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss:zzz"));
    ui->textBrowserRcv->append(data);
}

void SSocketMsgBrowser::onNewPacketSend(const QString &data)
{
    ui->textBrowserSend->append("onNewPacketSend:" + QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss:zzz"));
    ui->textBrowserSend->append(data);
}

void SSocketMsgBrowser::onTransferErrorString(const QString &error)
{
    ui->textBrowserError->append("onTransferErrorString:" + QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss:zzz"));
    ui->textBrowserError->append(error);
}
