#ifndef _QEXTTCPPACKETHEADER_P_H
#define _QEXTTCPPACKETHEADER_P_H

#include <qextTcpPacketHeader.h>

#include <QMutex>
#include <QVector>
#include <QPair>

class QEXT_TCP_API QEXTTcpPacketHeaderPrivate
{
public:
    explicit QEXTTcpPacketHeaderPrivate(QEXTTcpPacketHeader *q);
    virtual ~QEXTTcpPacketHeaderPrivate();

    QEXTTcpPacketHeader * const q_ptr;

    void initHeaderData(const QEXTTcpPacketHeader::DataInfoVector &dataInfoVector);
    void updateHeaderSize();

    quint16 m_headerSize;
    quint16 m_contentSize;

    mutable QMutex m_mutex;
    QVector<QPair<quint8, QString> > m_dataInfoVector;
    QMap<QString, QEXTTcpPacketVariant> m_dataMap;
    QMap<QString, quint8> m_typeMap;

private:
    Q_DECLARE_PUBLIC(QEXTTcpPacketHeader)
    Q_DISABLE_COPY(QEXTTcpPacketHeaderPrivate)
};



#endif // _QEXTTCPPACKETHEADER_P_H
