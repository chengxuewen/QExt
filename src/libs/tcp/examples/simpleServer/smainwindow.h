#ifndef SMAINWINDOW_H
#define SMAINWINDOW_H

#include <QMainWindow>
#include <qextglobal.h>
#include <qextTcpServer.h>



namespace Ui {
class SMainWindow;
}

class SMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SMainWindow(QWidget *parent = QEXT_DECL_NULLPTR);
    ~SMainWindow();


private slots:
    void onSocketError(const QSharedPointer<QEXTTcpSocket> &socket, const QAbstractSocket::SocketError &error);
    void onServerMessageReceived(const QString &msg);
    void onSocketConnected(const QSharedPointer<QEXTTcpSocket> &socket);
    void onSocketDisConected(const QSharedPointer<QEXTTcpSocket> &socket);

    void on_pushButton_ctrl_clicked();

    void on_pushButton_clearReceivedMsg_clicked();

private:
    Ui::SMainWindow *ui;
    QScopedPointer<QEXTTcpServer> m_tcpServer;
};

#endif // SMAINWINDOW_H
