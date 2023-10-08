#ifndef _QEXTTCPPACKETPARSER_P_H
#define _QEXTTCPPACKETPARSER_P_H

#include <qextId.h>
#include <qextTcpPacketParser.h>
#include <qextTcpPacketHeader.h>

#include <QHash>
#include <QMutex>



class QEXTTcpPacketInterface;
class QEXTTcpPacketParser;
class QEXT_TCP_API QEXTTcpPacketParserPrivate
{
public:
    explicit QEXTTcpPacketParserPrivate(QEXTTcpPacketParser *q);
    virtual ~QEXTTcpPacketParserPrivate();

    QEXTTcpPacketParser * const q_ptr;

    QString m_errorString;
    QEXTTcpPacketHeader::DataInfoVector m_headerDataPairVector;
    QEXTTcpPacketHeader::DataInfoVector m_extraHeaderDataPairVector;

    mutable QMutex m_mutex;
    QHash<QEXTId, QSharedPointer<QEXTTcpPacketInterface> > m_packetIdMap;
    static quint32 sm_id;

private:
    Q_DECLARE_PUBLIC(QEXTTcpPacketParser)
    Q_DISABLE_COPY(QEXTTcpPacketParserPrivate)
};



#endif // _QEXTTCPPACKETPARSER_P_H
