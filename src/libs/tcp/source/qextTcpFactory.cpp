#include <qextTcpFactory.h>
#include <qextTcpPacketParser.h>

QSharedPointer<QEXTTcpPacketDispatcher> QEXTTcpFactory::createPacketDispatcher(const QSharedPointer<QEXTTcpSocket> &socket)
{
    return QSharedPointer<QEXTTcpPacketDispatcher>(new QEXTTcpPacketDispatcher(socket.data(), this->clone()));
}

QSharedPointer<QEXTTcpPacketParserInterface> QEXTTcpFactory::createPacketParser()
{
    return QSharedPointer<QEXTTcpPacketParser>(new QEXTTcpPacketParser);
}

QEXTTcpTask *QEXTTcpFactory::createTask(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher, int function)
{
    Q_UNUSED(dispatcher);
    Q_UNUSED(function);
    return QEXT_DECL_NULLPTR;
}

QEXTTcpTask *QEXTTcpFactory::createTask(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher, const QSharedPointer<QEXTTcpPacketInterface> &packet)
{
    return new QEXTTcpPostBackTask(dispatcher->createPacketTransceiver(), packet);
}

QSharedPointer<QEXTTcpFactory> QEXTTcpFactory::clone()
{
    return QSharedPointer<QEXTTcpFactory>(new QEXTTcpFactory);
}
