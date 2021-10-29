#ifndef _QEXTTCPPACKETHEADER_H
#define _QEXTTCPPACKETHEADER_H

#include <qextTcpGlobal.h>
#include <qextTcpPacketHeaderInterface.h>
#include <qextTcpPacketVariant.h>

#include <QVector>
#include <QPair>

class QEXTTcpPacketHeaderPrivate;
class QEXT_TCP_API QEXTTcpPacketHeader : public QEXTTcpPacketHeaderInterface
{
public:
    typedef QPair<quint8, QString> DataInfoPair;
    typedef QVector<DataInfoPair> DataInfoVector;

    QEXTTcpPacketHeader(const DataInfoVector &dataInfoVector);
    QEXTTcpPacketHeader(QEXTTcpPacketHeaderPrivate *d, const DataInfoVector &dataInfoVector);
    ~QEXTTcpPacketHeader();

    quint16 headerSize() const QEXT_DECL_OVERRIDE;
    quint16 contentSize() const QEXT_DECL_OVERRIDE;
    void setContentSize(const quint16 &size) QEXT_DECL_OVERRIDE;

    QByteArray stream() const QEXT_DECL_OVERRIDE;
    bool setStream(const QByteArray &stream) QEXT_DECL_OVERRIDE;

    bool isHeaderDataExist(const QString &name) const QEXT_DECL_OVERRIDE;
    QList<QString> headerList() const QEXT_DECL_OVERRIDE;
    QEXTTcpPacketVariant headerData(const QString &name) const QEXT_DECL_OVERRIDE;
    bool setHeaderData(const QString &name, const QEXTTcpPacketVariant &data) QEXT_DECL_OVERRIDE;

protected:
    QScopedPointer<QEXTTcpPacketHeaderPrivate> d_ptr;

private:
    QEXT_DECL_PRIVATE(QEXTTcpPacketHeader)
    QEXT_DECL_DISABLE_COPY(QEXTTcpPacketHeader)
};

#endif // _QEXTTCPPACKETHEADER_H
