#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <qextglobal.h>
#include <QMainWindow>

#include <qexttcpclient.h>

namespace Ui {
class CMainWindow;
}



class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = QEXT_DECL_NULLPTR);
    ~CMainWindow();

private slots:
    void displaySocketError(QAbstractSocket::SocketError socketError);
    void displayTransferError(const QEXTTcpSocket::TransferErrorType &error);

    void receiveReplyPacket();

    void on_pushButton_ctrl_clicked();

    void on_pushButton_send_clicked();

private:
    Ui::CMainWindow *ui;

    QEXTTcpClient *m_tcpClient;
    QThread *m_thread;
};

#endif // CMAINWINDOW_H
