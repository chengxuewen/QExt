#include <qextTcpPacketVariant.h>

#include <qextNetworkUtils.h>

#include <QDebug>

QExtTcpPacketVariant::QExtTcpPacketVariant()
    : m_dataType(Data_int8)
{
    m_intData.uint64 = 0;
    m_valid = false;
}

QExtTcpPacketVariant::QExtTcpPacketVariant(const quint8 &data)
    : m_dataType(Data_uint8)
{
    m_valid = true;
    m_intData.uint8 = data;
    m_stream.append(data);
}

QExtTcpPacketVariant::QExtTcpPacketVariant(const qint16 &data)
    : m_dataType(Data_int16)
{
    m_valid = true;
    m_intData.int16 = data;
    m_stream = QExtNetworkUtils::qint16HostToNet(data);
}

QExtTcpPacketVariant::QExtTcpPacketVariant(const quint16 &data)
    : m_dataType(Data_uint16)
{
    m_valid = true;
    m_intData.uint16 = data;
    m_stream = QExtNetworkUtils::quint16HostToNet(data);
}

QExtTcpPacketVariant::QExtTcpPacketVariant(const qint32 &data)
    : m_dataType(Data_int32)
{
    m_valid = true;
    m_intData.int32 = data;
    m_stream = QExtNetworkUtils::qint32HostToNet(data);
}

QExtTcpPacketVariant::QExtTcpPacketVariant(const quint32 &data)
    : m_dataType(Data_uint32)
{
    m_valid = true;
    m_intData.uint32 = data;
    m_stream = QExtNetworkUtils::quint32HostToNet(data);
}

QExtTcpPacketVariant::QExtTcpPacketVariant(const qint64 &data)
    : m_dataType(Data_int64)
{
    m_valid = true;
    m_intData.int64 = data;
    m_stream = QExtNetworkUtils::qint64HostToNet(data);
}

QExtTcpPacketVariant::QExtTcpPacketVariant(const quint64 &data)
    : m_dataType(Data_uint64)
{
    m_valid = true;
    m_intData.uint64 = data;
    m_stream = QExtNetworkUtils::quint64HostToNet(data);
}

QExtTcpPacketVariant::QExtTcpPacketVariant(const QByteArray &data)
    : m_dataType(Data_chars + data.size())
{
    m_intData.uint64 = 0;
    m_valid = true;
    m_charsData = data;
    m_stream = data;
}

QExtTcpPacketVariant::QExtTcpPacketVariant(const QString &data)
    : m_dataType(Data_chars + data.toLatin1().size())
{
    m_intData.uint64 = 0;
    m_valid = true;
    m_charsData = data.toLatin1();
    m_stream = m_charsData;
}

QExtTcpPacketVariant::QExtTcpPacketVariant(const char *data)
    : m_dataType(Data_chars + strlen(data))
{
    m_intData.uint64 = 0;
    m_valid = true;
    m_charsData = QByteArray(data, strlen(data));
    m_stream = m_charsData;
}

QExtTcpPacketVariant::QExtTcpPacketVariant(const QVariant &data, const quint8 &type)
    : m_dataType(type)
{
    m_intData.uint64 = 0;
    m_valid = true;
    this->setData(data);
}

QExtTcpPacketVariant::QExtTcpPacketVariant(const QByteArray &stream, const quint8 &type)
    : m_dataType(type)
{
    m_intData.uint64 = 0;
    m_valid = true;
    this->setStream(stream);
}

QExtTcpPacketVariant::QExtTcpPacketVariant(const QExtTcpPacketVariant &variant)
    : m_dataType(variant.m_dataType)
{
    m_intData = variant.m_intData;
    m_charsData = variant.m_charsData;
    m_stream = variant.m_stream;
    m_valid = variant.m_valid;
    m_errorString = variant.m_errorString;
}

QExtTcpPacketVariant &QExtTcpPacketVariant::operator=(const QExtTcpPacketVariant &variant)
{
    m_intData = variant.m_intData;
    m_charsData = variant.m_charsData;
    m_stream = variant.m_stream;
    m_valid = variant.m_valid;
    m_errorString = variant.m_errorString;
    return *this;
}

bool QExtTcpPacketVariant::operator==(const QExtTcpPacketVariant &variant) const
{
    if (m_intData.uint64 != variant.m_intData.uint64) {
        return false;
    }
    if (m_charsData != variant.m_charsData) {
        return false;
    }
    if (m_stream != variant.m_stream) {
        return false;
    }
    if (m_valid != variant.m_valid) {
        return false;
    }
    if (m_errorString != variant.m_errorString) {
        return false;
    }
    return true;
}

bool QExtTcpPacketVariant::operator!=(const QExtTcpPacketVariant &variant) const
{
    return !(*this == variant);
}

QByteArray QExtTcpPacketVariant::toChars(bool trimmed) const
{
    if (trimmed) {
        int index = m_charsData.lastIndexOf('\0');
        return m_charsData.mid(index + 1);
    }
    return m_charsData;
}

QByteArray QExtTcpPacketVariant::toHostByteArray() const
{
    return this->toHostString().toLatin1();
}

QString QExtTcpPacketVariant::toHostString() const
{
    switch (m_dataType) {
    case Data_int8:
        return QString::number(m_intData.int8);
    case Data_uint8:
        return QString::number(m_intData.uint8);
    case Data_int16:
        return QString::number(m_intData.int16);
    case Data_uint16:
        return QString::number(m_intData.uint16);
    case Data_int32:
        return QString::number(m_intData.int32);
    case Data_uint32:
        return QString::number(m_intData.uint32);
    case Data_int64:
        return QString::number(m_intData.int64);
    case Data_uint64:
        return QString::number(m_intData.uint64);
    default:
        return QString(this->toChars().data());
    }
}

void QExtTcpPacketVariant::setData(const qint8 &data)
{
    m_intData.int8 = data;
}

void QExtTcpPacketVariant::setData(const quint8 &data)
{
    m_intData.uint8 = data;
}

void QExtTcpPacketVariant::setData(const qint16 &data)
{
    m_intData.int16 = data;
}

void QExtTcpPacketVariant::setData(const quint16 &data)
{
    m_intData.uint16 = data;
}

void QExtTcpPacketVariant::setData(const qint32 &data)
{
    m_intData.int32 = data;
}

void QExtTcpPacketVariant::setData(const quint32 &data)
{
    m_intData.uint32 = data;
}

void QExtTcpPacketVariant::setData(const qint64 &data)
{
    m_intData.int64 = data;
}

void QExtTcpPacketVariant::setData(const quint64 &data)
{
    m_intData.uint64 = data;
}

void QExtTcpPacketVariant::setData(const QByteArray &data)
{
    m_charsData = data;
}

void QExtTcpPacketVariant::setData(const QString &data)
{
    m_charsData = data.toLatin1();
}

void QExtTcpPacketVariant::setData(const char *data)
{
    m_charsData = QByteArray(data, strlen(data));
}

void QExtTcpPacketVariant::setData(const QVariant &data)
{
    switch (m_dataType) {
    case Data_int8:
        m_intData.int8 = (qint8)data.toLongLong(&m_valid);
        break;
    case Data_uint8:
        m_intData.uint8 = (quint8)data.toULongLong(&m_valid);
        break;
    case Data_int16:
        m_intData.int16 = (qint16)data.toLongLong(&m_valid);
        break;
    case Data_uint16:
        m_intData.uint16 = (quint16)data.toULongLong(&m_valid);
        break;
    case Data_int32:
        m_intData.int32 = (qint32)data.toLongLong(&m_valid);
        break;
    case Data_uint32:
        m_intData.uint32 = (quint32)data.toULongLong(&m_valid);
        break;
    case Data_int64:
        m_intData.int64 = (qint64)data.toLongLong(&m_valid);
        break;
    case Data_uint64:
        m_intData.uint64 = (quint64)data.toULongLong(&m_valid);
        break;
    default:
        if (m_dataType >= Data_chars) {
            m_charsData = data.toByteArray();
        }
        break;
    }
    if (!m_valid) {
        m_errorString = "stream.size() must be 1";
    }
}

void QExtTcpPacketVariant::setStream(const QByteArray &stream)
{
    m_stream = stream;
    switch (m_dataType) {
    case Data_int8:
        if (1 == stream.size()) {
            m_intData.int8 = stream.at(0);
        } else {
            m_valid = false;
            m_errorString = "stream.size() must be 1";
        }
        break;
    case Data_uint8:
        if (1 == stream.size()) {
            m_intData.uint8 = stream.at(0);
        } else {
            m_valid = false;
            m_errorString = "stream.size() must be 1";
        }
        break;
    case Data_int16:
        if (2 == stream.size()) {
            m_intData.int16 = QExtNetworkUtils::qint16NetToHost(stream);
        } else {
            m_valid = false;
            m_errorString = "stream.size() must be 2";
        }
        break;
    case Data_uint16:
        if (2 == stream.size()) {
            m_intData.uint16 = QExtNetworkUtils::quint16NetToHost(stream);
        } else {
            m_valid = false;
            m_errorString = "stream.size() must be 2";
        }
        break;
    case Data_int32:
        if (4 == stream.size()) {
            m_intData.int32 = QExtNetworkUtils::qint32NetToHost(stream);
        } else {
            m_valid = false;
            m_errorString = "stream.size() must be 4";
        }
        break;
    case Data_uint32:
        if (4 == stream.size()) {
            m_intData.uint32 = QExtNetworkUtils::quint32NetToHost(stream);
        } else {
            m_valid = false;
            m_errorString = "stream.size() must be 4";
        }
        break;
    case Data_int64:
        if (8 == stream.size()) {
            m_intData.int64 = QExtNetworkUtils::qint64NetToHost(stream);
        } else {
            m_valid = false;
            m_errorString = "stream.size() must be 8";
        }
        break;
    case Data_uint64:
        if (8 == stream.size()) {
            m_intData.uint64 = QExtNetworkUtils::quint64NetToHost(stream);
        } else {
            m_valid = false;
            m_errorString = "stream.size() must be 8";
        }
        break;
    default:
        if (m_dataType >= Data_chars) {
            m_charsData = stream;
        }
        break;
    }
}

quint8 QExtTcpPacketVariant::size() const
{
    return this->dataTypeSize(m_dataType);
}

quint8 QExtTcpPacketVariant::dataTypeSize(const quint8 &type)
{
    switch (type) {
    case Data_int8:
    case Data_uint8:
        return 1;
    case Data_int16:
    case Data_uint16:
        return 2;
    case Data_int32:
    case Data_uint32:
        return 4;
    case Data_int64:
    case Data_uint64:
        return 8;
    case Data_chars:
        return 0;
    default:
        if (type > Data_chars) {
            return type - Data_chars;
        }
        break;
    }
    return 0;
}

bool QExtTcpPacketVariant::isChartsDataType(const quint8 &type)
{
    return type >= Data_chars;
}
