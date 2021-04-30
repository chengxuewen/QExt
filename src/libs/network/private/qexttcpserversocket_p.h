#ifndef QEXTTCPSERVERSOCKET_P_H
#define QEXTTCPSERVERSOCKET_P_H

#include <qexttcpsocket_p.h>

#include <QTimer>

class QEXTTcpServerSocket;
class QEXT_NETWORK_API QEXTTcpServerSocketPrivate : public QEXTTcpSocketPrivate
{
public:
    explicit QEXTTcpServerSocketPrivate(QEXTTcpServerSocket *qq);
    ~QEXTTcpServerSocketPrivate();

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpServerSocket)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpServerSocketPrivate)
};

#endif // QEXTTCPSERVERSOCKET_P_H
