#ifndef QEXTTCPPACKETHEADER_P_H
#define QEXTTCPPACKETHEADER_P_H

#include <qextobject_p.h>

#include <qexttcpglobal.h>
#include <qexttcppacketheader.h>

#include <QMutex>
#include <QVector>
#include <QPair>



class QEXT_TCP_API QEXTTcpPacketHeaderPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpPacketHeaderPrivate(QEXTTcpPacketHeader *qq);
    ~QEXTTcpPacketHeaderPrivate();

    void initHeaderData(const QEXTTcpPacketHeader::DataInfoVector &dataInfoVector);
    void updateHeaderSize();

    quint16 m_headerSize;
    quint16 m_contentSize;

    mutable QMutex m_mutex;
    QVector<QPair<quint8, QString> > m_dataInfoVector;
    QMap<QString, QEXTTcpPacketVariant> m_dataMap;
    QMap<QString, quint8> m_typeMap;

private:
    QEXT_DECL_PUBLIC(QEXTTcpPacketHeader)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketHeaderPrivate)
};



#endif // QEXTTCPPACKETHEADER_P_H
