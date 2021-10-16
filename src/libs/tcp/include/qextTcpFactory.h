#ifndef _QEXTTCPFACTORY_H
#define _QEXTTCPFACTORY_H

#include <qextTcpGlobal.h>
#include <qextTcpPacketDispatcher.h>
#include <qextTcpTask.h>

struct QEXT_TCP_API QEXTTcpFactory
{
    virtual ~QEXTTcpFactory() {}

    virtual QSharedPointer<QEXTTcpPacketDispatcher> createPacketDispatcher(const QSharedPointer<QEXTTcpSocket> &socket);
    virtual QSharedPointer<QEXTTcpPacketParserInterface> createPacketParser();

    virtual QEXTTcpTask *createTask(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher, int function);
    virtual QEXTTcpTask *createTask(const QSharedPointer<QEXTTcpPacketDispatcher> &dispatcher, const QSharedPointer<QEXTTcpPacketInterface> &packet);

    virtual QSharedPointer<QEXTTcpFactory> clone();
};

#endif // _QEXTTCPFACTORY_H
