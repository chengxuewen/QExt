#ifndef _QEXTTCPFACTORY_H
#define _QEXTTCPFACTORY_H

#include <qextTcpGlobal.h>
#include <qextTcpPacketDispatcher.h>
#include <qextTcpTask.h>

struct QEXT_TCP_API QExtTcpFactory
{
    virtual ~QExtTcpFactory() {}

    virtual QSharedPointer<QExtTcpPacketDispatcher> createPacketDispatcher(const QSharedPointer<QExtTcpSocket> &socket);
    virtual QSharedPointer<QExtTcpPacketParserInterface> createPacketParser();

    virtual QExtTcpTask *createTask(const QSharedPointer<QExtTcpPacketDispatcher> &dispatcher, int function);
    virtual QExtTcpTask *createTask(const QSharedPointer<QExtTcpPacketDispatcher> &dispatcher, const QSharedPointer<QExtTcpPacketInterface> &packet);

    virtual QSharedPointer<QExtTcpFactory> clone();
};

#endif // _QEXTTCPFACTORY_H
