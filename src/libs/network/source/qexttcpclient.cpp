#include <qexttcpclient.h>
#include <qexttcpclient_p.h>
#include <qexttcpclientsocket.h>
#include <qexttcptaskthreadpool.h>
#include <qexttcpclientproxy.h>
#include <qexttcppacketbase.h>

#include <QDebug>
#include <QHostAddress>

QEXTTcpClientPrivate::QEXTTcpClientPrivate(QEXTTcpClient *qq)
    : QEXTTcpClientProxyPrivate(qq)
{
    m_name = "Client";
}

QEXTTcpClientPrivate::~QEXTTcpClientPrivate()
{
    m_socketThread->quit();
    m_socketThread->wait();

    m_packetDispatcherThread->quit();
    m_packetDispatcherThread->wait();

    m_socket->deleteLater();
}

void QEXTTcpClientPrivate::initClient(QEXTTcpClient *client)
{
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
    qRegisterMetaType<QEXTTcpSocket::TransferErrorType>("QEXTTcpSocket::TransferErrorType");

    m_packetDispatcherThread.reset(new QThread);
    m_packetDispatcherThread->start();

    m_socket = new QEXTTcpClientSocket;
    m_socketThread.reset(new QThread);
    m_socket->moveToThread(m_socketThread.data());
    QObject::connect(m_socket.data(), SIGNAL(connected()), client, SIGNAL(socketConnected()), Qt::QueuedConnection);
    QObject::connect(m_socket.data(), SIGNAL(disconnected()), client, SIGNAL(socketDisconnected()), Qt::QueuedConnection);
    QObject::connect(m_socket.data(), SIGNAL(error(QAbstractSocket::SocketError)),
                     client, SIGNAL(socketError(QAbstractSocket::SocketError)), Qt::QueuedConnection);
    QObject::connect(m_socket.data(), SIGNAL(transferError(QEXTTcpSocket::TransferErrorType)),
                     client, SIGNAL(transferError(QEXTTcpSocket::TransferErrorType)), Qt::QueuedConnection);

    QObject::connect(client, SIGNAL(tryToConnect()), m_socket.data(), SLOT(connectToServer()), Qt::QueuedConnection);
    QObject::connect(client, SIGNAL(tryToClose()), m_socket.data(), SLOT(closeSocket()), Qt::QueuedConnection);
    QObject::connect(client, SIGNAL(tryToAbort()), m_socket.data(), SLOT(abortSocket()), Qt::QueuedConnection);
    m_socketThread->start();

    this->handleProxyConnect(client, true);
}

void QEXTTcpClientPrivate::handleProxyConnect(QEXTTcpClientProxy *proxy, bool connect)
{
    if (connect) {
        QObject::connect(proxy, SIGNAL(newSendPacketReady(QEXTTcpPacketBase*)),
                         m_socket.data(), SLOT(enqueueSendPacket(QEXTTcpPacketBase*)));
    } else {
        QObject::disconnect(proxy, SIGNAL(newSendPacketReady(QEXTTcpPacketBase*)),
                            m_socket.data(), SLOT(enqueueSendPacket(QEXTTcpPacketBase*)));
    }
}



QEXTTcpClient::QEXTTcpClient(QObject *parent)
    : QEXTTcpClientProxy(*(new QEXTTcpClientPrivate(this)), parent)
{
    QEXT_D(QEXTTcpClient);
    d->initClient(this);
}

QEXTTcpClient::QEXTTcpClient(QEXTTcpPacketParserBase *packetParser, QObject *parent)
    : QEXTTcpClientProxy(*(new QEXTTcpClientPrivate(this)), parent)
{
    QEXT_D(QEXTTcpClient);
    d->initClient(this);
    this->setPacketParser(packetParser);
}

QEXTTcpClient::QEXTTcpClient(QEXTTcpPacketParserBase *packetParser,
                             QEXTTcpPacketDispatcherBase *packetDispatcher,
                             QObject *parent)
    : QEXTTcpClientProxy(*(new QEXTTcpClientPrivate(this)), parent)
{
    QEXT_D(QEXTTcpClient);
    d->initClient(this);
    this->setPacketParser(packetParser);
    this->setPacketDispatcher(packetDispatcher);
}

QEXTTcpClient::QEXTTcpClient(QEXTTcpClientPrivate &dd, QObject *parent)
    : QEXTTcpClientProxy(dd, parent)
{
    QEXT_D(QEXTTcpClient);
    d->initClient(this);;
}

QEXTTcpClient::QEXTTcpClient(QEXTTcpClientPrivate &dd,
                             QEXTTcpPacketParserBase *packetParser,
                             QObject *parent)
    : QEXTTcpClientProxy(dd, parent)
{
    QEXT_D(QEXTTcpClient);
    d->initClient(this);
    this->setPacketParser(packetParser);
}

QEXTTcpClient::QEXTTcpClient(QEXTTcpClientPrivate &dd,
                             QEXTTcpPacketParserBase *packetParser,
                             QEXTTcpPacketDispatcherBase *packetDispatcher,
                             QObject *parent)
    : QEXTTcpClientProxy(dd, parent)
{
    QEXT_D(QEXTTcpClient);
    d->initClient(this);
    this->setPacketParser(packetParser);
    this->setPacketDispatcher(packetDispatcher);
}

QEXTTcpClient::~QEXTTcpClient()
{

}

bool QEXTTcpClient::isSocketConnected() const
{
    QEXT_DC(QEXTTcpClient);
    return d->m_socket->isOpen();
}

void QEXTTcpClient::startConnection(const QString &ipAddr, quint16 port)
{
    QEXT_D(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_mutex);
    d->m_socket->setServerAddress(ipAddr);
    d->m_socket->setServerPort(port);
    emit this->tryToClose();
    emit this->tryToConnect();
}

void QEXTTcpClient::closeConnection()
{
    emit this->tryToClose();
}

void QEXTTcpClient::abortConnection()
{
    emit this->tryToAbort();
}

QString QEXTTcpClient::serverAddress() const
{
    QEXT_DC(QEXTTcpClient);
    return d->m_socket->serverAddress();
}

quint16 QEXTTcpClient::serverPort() const
{
    QEXT_DC(QEXTTcpClient);
    return d->m_socket->serverPort();
}

QList<QEXTTcpClientProxy *> QEXTTcpClient::allProxies() const
{
    QEXT_DC(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_proxyNameMap.values();
}

QEXTTcpClientProxy *QEXTTcpClient::proxy(const QString &name) const
{
    QEXT_DC(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_proxyNameMap.value(name, QEXT_NULLPTR);
}

bool QEXTTcpClient::addProxy(QEXTTcpClientProxy *proxy)
{
    QEXT_D(QEXTTcpClient);
    if (!proxy) {
        qCritical() << "QEXTTcpClient::addNetworkProxy():proxy can not null";
        return false;
    }

    if (this == proxy) {
        qCritical() << "QEXTTcpClient::addNetworkProxy():proxy can not be QEXTTcpClient";
        return false;
    }

    if (proxy->name().isEmpty()) {
        qCritical() << "QEXTTcpClient::addNetworkProxy():proxy name can not empty";
        return false;
    }

    if (d->m_proxyNameMap.contains(proxy->name()) || proxy->name() == d->m_name) {
        qCritical() << QString("QEXTTcpClient::addNetworkProxy():proxy name %1 already exist")
                       .arg(proxy->name());
        return false;
    }

    QThread *current = QThread::currentThread();
    if (current == proxy->thread()) {
        qCritical() << QString("QEXTTcpClient::addNetworkProxy():proxy %1 can not in client thread")
                       .arg(proxy->name());
        return false;
    }

    QMapIterator<QString, QEXTTcpClientProxy *> iter(d->m_proxyNameMap);
    while (iter.hasNext()) {
        QEXTTcpClientProxy *localProxy = iter.next().value();
        if (proxy->thread() == localProxy->thread()) {
            qCritical() << QString("QEXTTcpClient::addNetworkProxy():proxy %1 can not in proxy %2 thread")
                           .arg(proxy->name()).arg(localProxy->name());
            return false;
        }
    }

    QMutexLocker locker(&d->m_mutex);
    d->m_proxyNameMap.insert(proxy->name(), proxy);
    d->handleProxyConnect(proxy, true);
    proxy->setPacketParser(d->m_packetParser->cloneParser());
    proxy->setSocket(d->m_socket.data());
    return true;
}

int QEXTTcpClient::removeProxy(QEXTTcpClientProxy *proxy)
{
    QEXT_D(QEXTTcpClient);
    if (!proxy) {
        qCritical() << "QEXTTcpClient::removeNetworkProxy():proxy can not null";
        return false;
    }

    QMutexLocker locker(&d->m_mutex);
    if (!d->m_proxyNameMap.contains(proxy->name())) {
        if (!d->m_proxyNameMap.values().contains(proxy)) {
            QString name = d->m_proxyNameMap.key(proxy);
            d->m_proxyNameMap.remove(name);
            qCritical() << QString("QEXTTcpClient::removeNetworkProxy():proxy %1 name not exist but ptr exist")
                           .arg(proxy->name());
            return true;
        }  else {
            qCritical() << QString("QEXTTcpClient::removeNetworkProxy():proxy %1 not exist")
                           .arg(proxy->name());
            return false;
        }
    }

    d->m_proxyNameMap.remove(proxy->name());
    return true;
}

int QEXTTcpClient::removeProxy(const QString &name)
{
    QEXT_D(QEXTTcpClient);
    QMutexLocker locker(&d->m_mutex);
    if (!d->m_proxyNameMap.contains(name)) {
        qCritical() << QString("QEXTTcpClient::removeNetworkProxy():proxy %1 not exist")
                       .arg(name);
        return false;
    }

    d->m_proxyNameMap.remove(name);
    return true;
}

bool QEXTTcpClient::sendProxySyncRequestPacket(QEXTTcpPacketBase *send, QEXTTcpPacketBase **rcv, const QString &proxyName)
{
    QEXT_D(QEXTTcpClient);
    QMutexLocker locker(&d->m_mutex);
    QEXTTcpClientProxy *proxy = d->m_proxyNameMap.value(proxyName, QEXT_NULLPTR);
    if (!proxy) {
        qCritical() << QString("QEXTTcpClient::sendProxySyncRequestPacket():proxy %1 not exist").arg(proxyName);
        return false;
    }
    return proxy->sendSyncRequestPacket(send, rcv);
}

bool QEXTTcpClient::sendProxyRequestPacket(QEXTTcpPacketBase *send, const QString &proxyName)
{
    QEXT_D(QEXTTcpClient);
    QMutexLocker locker(&d->m_mutex);
    QEXTTcpClientProxy *proxy = d->m_proxyNameMap.value(proxyName, QEXT_NULLPTR);
    if (!proxy) {
        qCritical() << QString("QEXTTcpClient::sendProxyRequestPacket():proxy %1 not exist").arg(proxyName);
        return false;
    }
    return proxy->sendRequestPacket(send);
}

bool QEXTTcpClient::sendProxyReplyPacket(QEXTTcpPacketBase *send, const QString &proxyName)
{
    QEXT_D(QEXTTcpClient);
    QMutexLocker locker(&d->m_mutex);
    QEXTTcpClientProxy *proxy = d->m_proxyNameMap.value(proxyName, QEXT_NULLPTR);
    if (!proxy) {
        qCritical() << QString("QEXTTcpClient::sendProxyReplyPacket():proxy %1 not exist").arg(proxyName);
        return false;
    }
    return proxy->sendReplyPacket(send);
}

bool QEXTTcpClient::sendProxyNotifyPacket(QEXTTcpPacketBase *send, const QString &proxyName)
{
    QEXT_D(QEXTTcpClient);
    QMutexLocker locker(&d->m_mutex);
    QEXTTcpClientProxy *proxy = d->m_proxyNameMap.value(proxyName, QEXT_NULLPTR);
    if (!proxy) {
        qCritical() << QString("QEXTTcpClient::sendProxyNotifyPacket():proxy %1 not exist").arg(proxyName);
        return false;
    }
    return proxy->sendNotifyPacket(send);
}

QEXTTcpPacketDispatcherBase *QEXTTcpClient::packetDispatcher() const
{
    QEXT_DC(QEXTTcpClient);
    return d->m_packetDispatcher.data();
}

void QEXTTcpClient::setPacketDispatcher(QEXTTcpPacketDispatcherBase *dispatcher)
{
    QEXT_D(QEXTTcpClient);
    QMutexLocker mutexLocker(&d->m_mutex);
    dispatcher->setParent(QEXT_NULLPTR);
    dispatcher->setTcpClient(this);
    d->m_packetDispatcher.reset(dispatcher);
    d->m_packetDispatcher->moveToThread(d->m_packetDispatcherThread.data());
    d->m_socket->setPacketDispatcher(dispatcher);
}

void QEXTTcpClient::setPacketParser(QEXTTcpPacketParserBase *packetParser)
{
    QEXTTcpClientProxy::setPacketParser(packetParser);
    QEXT_D(QEXTTcpClient);
    d->m_socket->setPacketParser(packetParser->cloneParser());
    QMapIterator<QString, QEXTTcpClientProxy *> iter(d->m_proxyNameMap);
    while (iter.hasNext()) {
        QEXTTcpClientProxy *proxy = iter.next().value();
        if (proxy->packetParser() != packetParser) {
            proxy->setPacketParser(packetParser->cloneParser());
        }
    }
}

