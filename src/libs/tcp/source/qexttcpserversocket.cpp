#include <qexttcpserversocket.h>
#include <qexttcpserversocket_p.h>

#include <QHostAddress>
#include <QDebug>



QEXTTcpServerSocketPrivate::QEXTTcpServerSocketPrivate(QEXTTcpServerSocket *qq)
    : QEXTTcpSocketPrivate(qq)
{

}

QEXTTcpServerSocketPrivate::~QEXTTcpServerSocketPrivate()
{

}



QEXTTcpServerSocket::QEXTTcpServerSocket()
    : QEXTTcpSocket(*(new QEXTTcpServerSocketPrivate(this)))
{
    QEXT_D(QEXTTcpServerSocket);
    connect(this, SIGNAL(connected()), this, SLOT(updateIdentityId()));
}

QEXTTcpServerSocket::~QEXTTcpServerSocket()
{

}

void QEXTTcpServerSocket::updateIdentityId()
{
    QEXT_D(QEXTTcpServerSocket);
    if (!d->m_identityId.isValid()) {
        d->m_identityId = QString("%1:%2:%3").arg(d->sm_id, 5, 10, QLatin1Char('0'))
                .arg(this->peerAddress().toString()).arg(this->peerPort());
    }
}

void QEXTTcpServerSocket::sendReadyRead()
{
    emit this->readyRead();
}
