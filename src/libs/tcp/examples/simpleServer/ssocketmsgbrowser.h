#ifndef SSOCKETMSGBROWSER_H
#define SSOCKETMSGBROWSER_H

#include <QWidget>

namespace Ui {
class SSocketMsgBrowser;
}

class SSocketMsgBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit SSocketMsgBrowser(QWidget *parent = 0);
    ~SSocketMsgBrowser();

public slots:
    void onNewPacketReceived(const QString &data);
    void onNewPacketSend(const QString &data);
    void onTransferErrorString(const QString &error);

private:
    Ui::SSocketMsgBrowser *ui;
};

#endif // SSOCKETMSGBROWSER_H
