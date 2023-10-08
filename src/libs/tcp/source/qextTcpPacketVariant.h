#ifndef _QEXTTCPPACKETVARIANT_H
#define _QEXTTCPPACKETVARIANT_H

#include <qextTcpGlobal.h>

#include <qextNetworkUtils.h>

#include <QByteArray>
#include <QMap>

class QEXT_TCP_API QEXTTcpPacketVariant
{
public:
    enum DataType {
        Data_int8 = 0,
        Data_uint8,
        Data_int16,
        Data_uint16,
        Data_int32,
        Data_uint32,
        Data_int64,
        Data_uint64,
        Data_chars // Data_chars1 = Data_chars + 1 ...
    };
    union IntData {
        qint8 int8;
        quint8 uint8;
        qint16 int16;
        quint16 uint16;
        qint32 int32;
        quint32 uint32;
        qint64 int64;
        quint64 uint64;
    };

    QEXTTcpPacketVariant();
    QEXTTcpPacketVariant(const qint8 &data);
    QEXTTcpPacketVariant(const quint8 &data);
    QEXTTcpPacketVariant(const qint16 &data);
    QEXTTcpPacketVariant(const quint16 &data);
    QEXTTcpPacketVariant(const qint32 &data);
    QEXTTcpPacketVariant(const quint32 &data);
    QEXTTcpPacketVariant(const qint64 &data);
    QEXTTcpPacketVariant(const quint64 &data);
    QEXTTcpPacketVariant(const QByteArray &data);
    QEXTTcpPacketVariant(const QString &data);
    QEXTTcpPacketVariant(const char *data);
    QEXTTcpPacketVariant(const QVariant &data, const quint8 &type);
    QEXTTcpPacketVariant(const QByteArray &stream, const quint8 &type);
    QEXTTcpPacketVariant(const QEXTTcpPacketVariant &variant);
    virtual ~QEXTTcpPacketVariant() {}

    QEXTTcpPacketVariant &operator=(const QEXTTcpPacketVariant &variant);
    bool operator==(const QEXTTcpPacketVariant &variant) const;
    bool operator!=(const QEXTTcpPacketVariant &variant) const;

    qint8 toInt8() const { return m_intData.int8; }
    quint8 toUint8() const { return m_intData.uint8; }
    qint16 toInt16() const { return m_intData.int16; }
    quint16 toUint16() const { return m_intData.uint16; }
    qint32 toInt32() const { return m_intData.int32; }
    quint32 toUint32() const { return m_intData.uint32; }
    qint64 toInt64() const { return m_intData.int64; }
    quint64 toUint64() const { return m_intData.uint64; }
    QByteArray toChars(bool trimmed = true) const;
    QByteArray toStream() const { return m_stream; }
    QByteArray toHostByteArray() const;
    QString toHostString() const;

    void setData(const qint8 &data);
    void setData(const quint8 &data);
    void setData(const qint16 &data);
    void setData(const quint16 &data);
    void setData(const qint32 &data);
    void setData(const quint32 &data);
    void setData(const qint64 &data);
    void setData(const quint64 &data);
    void setData(const QByteArray &data);
    void setData(const QString &data);
    void setData(const char *data);
    void setData(const QVariant &data);
    void setStream(const QByteArray &stream);

    quint8 size() const;
    quint8 dataType() const { return m_dataType; }
    static quint8 dataTypeSize(const quint8 &type);
    static bool isChartsDataType(const quint8 &type);

    bool isValid() const { return m_valid; }
    QString errorString() const { return m_errorString; }

protected:
    IntData m_intData;
    QByteArray m_charsData;
    QByteArray m_stream;
    bool m_valid;
    QString m_errorString;
    quint8 m_dataType;
};

#endif // _QEXTTCPPACKETVARIANT_H
