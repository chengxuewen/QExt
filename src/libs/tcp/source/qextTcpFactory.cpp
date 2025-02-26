#include <qextTcpFactory.h>
#include <qextTcpPacketParser.h>

#include <QSharedPointer>

QSharedPointer<QExtTcpPacketDispatcher>
QExtTcpFactory::createPacketDispatcher(const QSharedPointer<QExtTcpSocket> &socket) {
    return QSharedPointer<QExtTcpPacketDispatcher>(new QExtTcpPacketDispatcher(socket.data(), this->clone()));
}

QSharedPointer<QExtTcpPacketParserInterface> QExtTcpFactory::createPacketParser() {
    return QSharedPointer<QExtTcpPacketParser>(new QExtTcpPacketParser);
}

QExtTcpTask *QExtTcpFactory::createTask(const QSharedPointer<QExtTcpPacketDispatcher> &dispatcher, int function) {
    Q_UNUSED(dispatcher);
    Q_UNUSED(function);
    return QEXT_NULLPTR;
}

QExtTcpTask *QExtTcpFactory::createTask(const QSharedPointer<QExtTcpPacketDispatcher> &dispatcher,
                                        const QSharedPointer<QExtTcpPacketInterface> &packet) {
    return new QExtTcpPostBackTask(dispatcher->createPacketTransceiver(), packet);
}

QSharedPointer<QExtTcpFactory> QExtTcpFactory::clone() {
    return QSharedPointer<QExtTcpFactory>(new QExtTcpFactory);
}
