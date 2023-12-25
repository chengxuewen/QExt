#ifndef _QEXTTCPPACKETHEADER_H
#define _QEXTTCPPACKETHEADER_H

#include <qextTcpGlobal.h>
#include <qextTcpPacketHeaderInterface.h>
#include <qextTcpPacketVariant.h>

#include <QVector>
#include <QPair>

class QExtTcpPacketHeaderPrivate;
class QEXT_TCP_API QExtTcpPacketHeader : public QExtTcpPacketHeaderInterface
{
    Q_DISABLE_COPY(QExtTcpPacketHeader)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtTcpPacketHeader)
public:
    typedef QPair<quint8, QString> DataInfoPair;
    typedef QVector<DataInfoPair> DataInfoVector;

    QExtTcpPacketHeader(const DataInfoVector &dataInfoVector);
    QExtTcpPacketHeader(QExtTcpPacketHeaderPrivate *d, const DataInfoVector &dataInfoVector);
    ~QExtTcpPacketHeader();

    quint16 headerSize() const QEXT_OVERRIDE;
    quint16 contentSize() const QEXT_OVERRIDE;
    void setContentSize(const quint16 &size) QEXT_OVERRIDE;

    QByteArray stream() const QEXT_OVERRIDE;
    bool setStream(const QByteArray &stream) QEXT_OVERRIDE;

    bool isHeaderDataExist(const QString &name) const QEXT_OVERRIDE;
    QList<QString> headerList() const QEXT_OVERRIDE;
    QExtTcpPacketVariant headerData(const QString &name) const QEXT_OVERRIDE;
    bool setHeaderData(const QString &name, const QExtTcpPacketVariant &data) QEXT_OVERRIDE;

protected:
    QScopedPointer<QExtTcpPacketHeaderPrivate> dd_ptr;
};

#endif // _QEXTTCPPACKETHEADER_H
