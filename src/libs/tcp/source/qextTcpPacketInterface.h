#ifndef _QEXTTCPPACKETINTERFACE_H
#define _QEXTTCPPACKETINTERFACE_H

#include <qextTcpGlobal.h>
#include <qextTcpPacketHeaderInterface.h>

#include <qextId.h>

#include <QSharedPointer>

class QEXT_TCP_API QExtTcpPacketInterface
{
public:
    virtual ~QExtTcpPacketInterface() {}

    virtual QDateTime timestamp() const = 0;
    virtual bool isValid() const = 0;

    virtual QByteArray stream() const = 0;

    virtual QSharedPointer<QExtTcpPacketHeaderInterface> header() const = 0;
    virtual bool setHeader(const QSharedPointer<QExtTcpPacketHeaderInterface> &header) = 0;

    virtual QByteArray content() const = 0;
    virtual bool setContent(const QByteArray &content) = 0;

    virtual qint64 nextBlockSize() const = 0;
    virtual bool setNextBlockSize(qint64 size) = 0;
};


#endif // _QEXTTCPPACKETINTERFACE_H
