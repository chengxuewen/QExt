#ifndef _QEXTTCPPACKETPARSER_P_H
#define _QEXTTCPPACKETPARSER_P_H

#include <qextTag.h>
#include <qextTcpPacketParser.h>
#include <qextTcpPacketHeader.h>

#include <QHash>
#include <QMutex>



class QExtTcpPacketInterface;
class QExtTcpPacketParser;
class QEXT_TCP_API QExtTcpPacketParserPrivate
{
public:
    explicit QExtTcpPacketParserPrivate(QExtTcpPacketParser *q);
    virtual ~QExtTcpPacketParserPrivate();

    QExtTcpPacketParser * const q_ptr;

    QString m_errorString;
    QExtTcpPacketHeader::DataInfoVector m_headerDataPairVector;
    QExtTcpPacketHeader::DataInfoVector m_extraHeaderDataPairVector;

    mutable QMutex m_mutex;
    QHash<QExtTag, QSharedPointer<QExtTcpPacketInterface> > m_packetIdMap;
    static quint32 sm_id;

private:
    Q_DECLARE_PUBLIC(QExtTcpPacketParser)
    Q_DISABLE_COPY(QExtTcpPacketParserPrivate)
};



#endif // _QEXTTCPPACKETPARSER_P_H
