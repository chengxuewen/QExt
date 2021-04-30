#include <qexttcppacketheader.h>
#include <qexttcppacketheader_p.h>
#include <qextnetworkutils.h>

QEXTTcpPacketHeaderPrivate::QEXTTcpPacketHeaderPrivate(QEXTTcpPacketHeader *qq)
    : QEXTObjectPrivate(qq)
{
    this->updateHeaderSize();
    m_contentSize = 0;
}

QEXTTcpPacketHeaderPrivate::~QEXTTcpPacketHeaderPrivate()
{

}

void QEXTTcpPacketHeaderPrivate::initHeaderData(const QEXTTcpPacketHeader::DataInfoVector &dataInfoVector)
{
    m_typeMap.clear();
    m_dataMap.clear();
    if (dataInfoVector.size() < QEXT_TCP_PACKET_HEADER_META_DATA_MAX_NUM) {
        m_dataInfoVector = dataInfoVector;
        for (int i = 0; i < dataInfoVector.size(); ++i) {
            if (m_dataMap.contains(dataInfoVector.at(i).second)) {
                qCritical() << QString("QEXTTcpPacketHeaderPrivate::initHeaderData():data key %1 already exist!")
                               .arg(dataInfoVector.at(i).second);
            } else if (dataInfoVector.at(i).second.isEmpty()) {
                qCritical() << QString("QEXTTcpPacketHeaderPrivate::initHeaderData():data key in No.%1 can not be empty!")
                               .arg(dataInfoVector.at(i).second);
            } else {
                m_typeMap.insert(dataInfoVector.at(i).second, dataInfoVector.at(i).first);
                m_dataMap.insert(dataInfoVector.at(i).second, QEXTTcpPacketVariant(QByteArray(), dataInfoVector.at(i).first));
            }
        }
        this->updateHeaderSize();
    } else {
        qCritical() << QString("QEXTTcpPacketHeaderPrivate::initDataPair():dataInfoVector size must less than %1")
                       .arg(QEXT_TCP_PACKET_HEADER_META_DATA_MAX_NUM);
    }
}

void QEXTTcpPacketHeaderPrivate::updateHeaderSize()
{
    m_headerSize = sizeof(m_headerSize);
    QList<QString> keyList = m_typeMap.keys();
    for (int i = 0; i < keyList.size(); ++i) {
        quint8 dataType = m_typeMap.value(keyList.at(i));
        m_headerSize += QEXTTcpPacketVariant::dataTypeSize(dataType);
    }
    m_headerSize += sizeof(m_contentSize);
}



QEXTTcpPacketHeader::QEXTTcpPacketHeader(const QEXTTcpPacketHeader::DataInfoVector &dataInfoVector)
    : QEXTObject(*(new QEXTTcpPacketHeaderPrivate(this)))
{
    QEXT_D(QEXTTcpPacketHeader);
    d->initHeaderData(dataInfoVector);
}

QEXTTcpPacketHeader::QEXTTcpPacketHeader(QEXTTcpPacketHeaderPrivate &dd, const DataInfoVector &dataInfoVector)
    : QEXTObject(dd)
{
    QEXT_D(QEXTTcpPacketHeader);
    d->initHeaderData(dataInfoVector);
}

QEXTTcpPacketHeader::~QEXTTcpPacketHeader()
{

}

quint16 QEXTTcpPacketHeader::headerSize() const
{
    QEXT_DC(QEXTTcpPacketHeader);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_headerSize;
}

quint16 QEXTTcpPacketHeader::contentSize() const
{
    QEXT_DC(QEXTTcpPacketHeader);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_contentSize;
}

void QEXTTcpPacketHeader::setContentSize(const quint16 &size)
{
    QEXT_D(QEXTTcpPacketHeader);
    QMutexLocker mutexLocker(&d->m_mutex);
    d->m_contentSize = size;
}

QByteArray QEXTTcpPacketHeader::stream() const
{
    QEXT_DC(QEXTTcpPacketHeader);
    QMutexLocker mutexLocker(&d->m_mutex);
    QByteArray stream;
    stream.append(QEXTNetworkUtils::quint16HostToNet(d->m_headerSize));

    QList<QString> keyList = d->m_typeMap.keys();
    for (int i = 0; i < keyList.size(); ++i) {
        QString key = keyList.at(i);
        quint8 type = d->m_typeMap.value(key);
        int size = QEXTTcpPacketVariant::dataTypeSize(type);
        QByteArray variantStream = d->m_dataMap.value(key).toStream().rightJustified(size, 0, true);
        stream.append(variantStream);
    }

    stream.append(QEXTNetworkUtils::quint16HostToNet(d->m_contentSize));
    return stream;
}

bool QEXTTcpPacketHeader::setStream(const QByteArray &stream)
{
    QEXT_D(QEXTTcpPacketHeader);
    QMutexLocker mutexLocker(&d->m_mutex);
    if (stream.size() == d->m_headerSize) {
        QList<QString> keyList = d->m_typeMap.keys();
        int offset = sizeof(d->m_headerSize);

        for (int i = 0; i < keyList.size(); ++i) {
            QString key = keyList.at(i);
            quint8 type = d->m_typeMap.value(key);
            int size = QEXTTcpPacketVariant::dataTypeSize(type);
            QByteArray data(stream.data() + offset, size);
            d->m_dataMap.insert(key, QEXTTcpPacketVariant(data, type));
            offset += size;
        }

        offset = d->m_headerSize - sizeof(d->m_contentSize);
        QEXTNetworkUtils::quint16NetToHost(stream.data() + offset, &d->m_contentSize);
        return true;
    }
    return false;
}

bool QEXTTcpPacketHeader::isHeaderDataExist(const QString &name) const
{
    QEXT_DC(QEXTTcpPacketHeader);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_dataMap.contains(name);
}

QList<QString> QEXTTcpPacketHeader::headerList() const
{
    QEXT_DC(QEXTTcpPacketHeader);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_dataMap.keys();
}

QEXTTcpPacketVariant QEXTTcpPacketHeader::headerData(const QString &name) const
{
    QEXT_DC(QEXTTcpPacketHeader);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_dataMap.value(name, QEXTTcpPacketVariant());
}

bool QEXTTcpPacketHeader::setHeaderData(const QString &name, const QEXTTcpPacketVariant &data)
{
    QEXT_D(QEXTTcpPacketHeader);
    QMutexLocker mutexLocker(&d->m_mutex);
    if (d->m_dataMap.contains(name)) {
        quint8 type = d->m_typeMap.value(name);
        bool isChars = data.dataType() >= QEXTTcpPacketVariant::Data_chars && data.dataType() <= type;
        if (data.dataType() == type || isChars) {
            d->m_dataMap.insert(name, data);
        } else {
            qCritical() << QString("QEXTTcpPacketHeader::setHeaderData():%1 data type must be %2!")
                           .arg(name).arg(type);
        }
    } else {
        qCritical() << QString("QEXTTcpPacketHeader::setHeaderData():%1 data not exist!");
    }
    return false;
}
