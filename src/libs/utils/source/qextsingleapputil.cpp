#include "qextsingleapputil.h"
#include "qextsingleapputil_p.h"

#include <QLocalSocket>
#include <QCoreApplication>
#include <QFileInfo>
#include <QDebug>

QEXTSingleAppUtilPrivate::QEXTSingleAppUtilPrivate(QEXTSingleAppUtil *qq)
    : QEXTObjectPrivate(qq)
{
    m_localServerName = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
}

QEXTSingleAppUtilPrivate::~QEXTSingleAppUtilPrivate()
{

}

bool QEXTSingleAppUtilPrivate::initLocalServer()
{
    QEXT_Q(QEXTSingleAppUtil);
    m_localServer.reset(new QLocalServer());
    QObject::connect(m_localServer.data(), &QLocalServer::newConnection, [=](){
        q->newLocalConnectionReceived();
    });
    if(!m_localServer->listen(m_localServerName)) {
        if(QAbstractSocket::AddressInUseError == m_localServer->serverError()) {
            QLocalServer::removeServer(m_localServerName);
            m_localServer->listen(m_localServerName);
        }
    }
    return true;
}



QEXTSingleAppUtil::QEXTSingleAppUtil()
    : QEXTObject(*(new QEXTSingleAppUtilPrivate(this)))
{

}

QEXTSingleAppUtil::QEXTSingleAppUtil(QEXTSingleAppUtilPrivate &dd)
    : QEXTObject(dd)
{

}

QEXTSingleAppUtil::~QEXTSingleAppUtil()
{

}

void QEXTSingleAppUtil::newLocalConnectionReceived()
{
    QEXT_D(QEXTSingleAppUtil);
    QScopedPointer<QLocalSocket> socket(d->m_localServer->nextPendingConnection());
    if (socket.isNull()) {
        return;
    }
    socket->waitForReadyRead(1000);
}

bool QEXTSingleAppUtil::initLocalConnection()
{
    QEXT_D(QEXTSingleAppUtil);
    QLocalSocket socket;
    socket.connectToServer(d->m_localServerName);
    if(socket.waitForConnected(500)) {
        QTextStream stream(&socket);
        QStringList args = QCoreApplication::arguments();
        if (args.count() > 1) {
            stream << args.last();
        } else {
            stream << QString();
        }
        stream.flush();
        socket.waitForBytesWritten();
        return false;
    }
    return d->initLocalServer();
}
