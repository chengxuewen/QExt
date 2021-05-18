#ifndef QEXTTCPSERVERSOCKET_H
#define QEXTTCPSERVERSOCKET_H

#include <qexttcpsocket.h>



class QEXTTcpAbstractPacket;
class QEXTTcpServerSocketPrivate;
class QEXT_TCP_API QEXTTcpServerSocket : public QEXTTcpSocket
{
    Q_OBJECT
public:
    QEXTTcpServerSocket();
    ~QEXTTcpServerSocket();

    int expiryTime() const;
    void setExpiryTime(int expiryTime);

    void sendReadyRead();

public Q_SLOTS:
    void updateIdentityId() QEXT_OVERRIDE;

private:
    QEXT_DECLARE_PRIVATE(QEXTTcpServerSocket)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpServerSocket)
};



#endif // QEXTTCPSERVERSOCKET_H
