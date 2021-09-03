#ifndef QEXTTCPPACKETINTERFACE_H
#define QEXTTCPPACKETINTERFACE_H

#include <qextTcpGlobal.h>
#include <qextTcpPacketHeaderInterface.h>

#include <qextid.h>

#include <QSharedPointer>

class QEXT_TCP_API QEXTTcpPacketInterface
{
public:
    virtual ~QEXTTcpPacketInterface() {}

    virtual QDateTime timestamp() const = 0;
    virtual bool isValid() const = 0;

    virtual QByteArray stream() const = 0;

    virtual QSharedPointer<QEXTTcpPacketHeaderInterface> header() const = 0;
    virtual bool setHeader(const QSharedPointer<QEXTTcpPacketHeaderInterface> &header) = 0;

    virtual QByteArray content() const = 0;
    virtual bool setContent(const QByteArray &content) = 0;

    virtual qint64 nextBlockSize() const = 0;
    virtual bool setNextBlockSize(qint64 size) = 0;
};


#endif // QEXTTCPPACKETINTERFACE_H
