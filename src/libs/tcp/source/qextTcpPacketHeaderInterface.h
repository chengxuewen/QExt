#ifndef _QEXTTCPPACKETHEADERINTERFACE_H
#define _QEXTTCPPACKETHEADERINTERFACE_H

#include <qextTcpGlobal.h>
#include <qextTcpPacketVariant.h>

#include <QSharedPointer>

class QEXT_TCP_API QExtTcpPacketHeaderInterface
{
public:
    virtual ~QExtTcpPacketHeaderInterface() {}

    virtual quint16 headerSize() const = 0;
    virtual quint16 contentSize() const = 0;
    virtual void setContentSize(const quint16 &size) = 0;

    virtual QByteArray stream() const = 0;
    virtual bool setStream(const QByteArray &stream) = 0;

    virtual bool isHeaderDataExist(const QString &name) const = 0;
    virtual QList<QString> headerList() const = 0;
    virtual QExtTcpPacketVariant headerData(const QString &name) const = 0;
    virtual bool setHeaderData(const QString &name, const QExtTcpPacketVariant &data) = 0;
};

#endif // _QEXTTCPPACKETHEADERINTERFACE_H
