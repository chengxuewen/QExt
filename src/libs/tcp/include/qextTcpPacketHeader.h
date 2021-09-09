#ifndef QEXTTCPPACKETHEADER_H
#define QEXTTCPPACKETHEADER_H

#include <qextTcpGlobal.h>
#include <qextTcpPacketHeaderInterface.h>
#include <qextTcpPacketVariant.h>

#include <qextObject.h>

#include <QVector>
#include <QPair>

class QEXTTcpPacketHeaderPrivate;
class QEXT_TCP_API QEXTTcpPacketHeader : public QEXTTcpPacketHeaderInterface, public QEXTObject
{
public:
    typedef QPair<quint8, QString> DataInfoPair;
    typedef QVector<DataInfoPair> DataInfoVector;

    QEXTTcpPacketHeader(const DataInfoVector &dataInfoVector);
    QEXTTcpPacketHeader(QEXTTcpPacketHeaderPrivate &dd, const DataInfoVector &dataInfoVector);
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

private:
    QEXT_DECL_PRIVATE(QEXTTcpPacketHeader)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketHeader)
};

#endif // QEXTTCPPACKETHEADER_H
