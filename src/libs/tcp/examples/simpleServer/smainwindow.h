#ifndef SMAINWINDOW_H
#define SMAINWINDOW_H

#include <QMainWindow>
#include <qextglobal.h>
#include <qexttcpserver.h>



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
    void displayTransferError(const QEXTTcpSocket::TransferErrorType &error);
    void displaySocketError(const QEXTId &socketId, const QAbstractSocket::SocketError &error);
    void displaySocketMessage(const QEXTId &socketId, const QString &msg);

    void on_pushButton_ctrl_clicked();

    void on_pushButton_clearReceivedMsg_clicked();

private:
    Ui::SMainWindow *ui;
    QEXTTcpServer *m_tcpServer;
};

#endif // SMAINWINDOW_H
