#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <qextGlobal.h>
#include <QMainWindow>

#include <qextTcpClient.h>

namespace Ui {
class CMainWindow;
}



class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = QEXT_NULLPTR);
    ~CMainWindow();

private slots:
    void onSocketError(QAbstractSocket::SocketError socketError);
    void onTransferError(const QExtTcpSocket::TransferErrorType &error);

    void onSocketConnected();
    void onSocketDisconnected();
    void onNewPacketSend(const QString &data);
    void onNewPacketReceived(const QString &data);

    void receiveReplyPacket();

    void on_pushButton_ctrl_clicked();

    void on_pushButton_send_clicked();

private:
    Ui::CMainWindow *ui;

    QScopedPointer<QExtTcpClient> m_tcpClient;
    QThread *m_thread;
};

#endif // CMAINWINDOW_H
