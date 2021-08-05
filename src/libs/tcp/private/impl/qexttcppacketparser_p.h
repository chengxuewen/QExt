#ifndef QEXTTCPPACKETPARSER_P_H
#define QEXTTCPPACKETPARSER_P_H

#include <qextobject_p.h>
#include <qextid.h>

#include <qexttcpglobal.h>
#include <qexttcppacketheader.h>

#include <QHash>
#include <QMutex>



class QEXTTcpAbstractPacket;
class QEXTTcpPacketParser;
class QEXT_TCP_API QEXTTcpPacketParserPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTTcpPacketParserPrivate(QEXTTcpPacketParser *qq);
    ~QEXTTcpPacketParserPrivate();

    QString m_errorString;
    QEXTTcpPacketHeader::DataInfoVector m_headerDataPairVector;
    QEXTTcpPacketHeader::DataInfoVector m_extraHeaderDataPairVector;

    mutable QMutex m_mutex;
    QHash<QEXTId, QEXTTcpAbstractPacket *> m_packetIdMap;
    static quint32 sm_id;

private:
    QEXT_DECLARE_PUBLIC(QEXTTcpPacketParser)
    QEXT_DISABLE_COPY_MOVE(QEXTTcpPacketParserPrivate)
};



#endif // QEXTTCPPACKETPARSER_P_H
