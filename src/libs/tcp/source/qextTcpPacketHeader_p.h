#ifndef _QEXTTCPPACKETHEADER_P_H
#define _QEXTTCPPACKETHEADER_P_H

#include <qextTcpPacketHeader.h>

#include <QMutex>
#include <QVector>
#include <QPair>

class QEXT_TCP_API QExtTcpPacketHeaderPrivate
{
public:
    explicit QExtTcpPacketHeaderPrivate(QExtTcpPacketHeader *q);
    virtual ~QExtTcpPacketHeaderPrivate();

    QExtTcpPacketHeader * const q_ptr;

    void initHeaderData(const QExtTcpPacketHeader::DataInfoVector &dataInfoVector);
    void updateHeaderSize();

    quint16 m_headerSize;
    quint16 m_contentSize;

    mutable QMutex m_mutex;
    QVector<QPair<quint8, QString> > m_dataInfoVector;
    QMap<QString, QExtTcpPacketVariant> m_dataMap;
    QMap<QString, quint8> m_typeMap;

private:
    Q_DECLARE_PUBLIC(QExtTcpPacketHeader)
    Q_DISABLE_COPY(QExtTcpPacketHeaderPrivate)
};



#endif // _QEXTTCPPACKETHEADER_P_H
