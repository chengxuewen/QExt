#include <private/qextTcpPacketHeader_p.h>
#include <qextTcpPacketVariant.h>
#include <qextNetworkUtils.h>

#include <QDebug>

static const int QEXT_TCP_PACKET_HEADER_META_DATA_MAX_NUM = 255;

QExtTcpPacketHeaderPrivate::QExtTcpPacketHeaderPrivate(QExtTcpPacketHeader *q)
    : q_ptr(q)
{
    this->updateHeaderSize();
    m_contentSize = 0;
}

QExtTcpPacketHeaderPrivate::~QExtTcpPacketHeaderPrivate()
{

}

void QExtTcpPacketHeaderPrivate::initHeaderData(const QExtTcpPacketHeader::DataInfoVector &dataInfoVector)
{
    m_typeMap.clear();
    m_dataMap.clear();
    if (dataInfoVector.size() < QEXT_TCP_PACKET_HEADER_META_DATA_MAX_NUM) {
        m_dataInfoVector = dataInfoVector;
        for (int i = 0; i < dataInfoVector.size(); ++i) {
            if (m_dataMap.contains(dataInfoVector.at(i).second)) {
                qCritical() << QString("QExtTcpPacketHeaderPrivate::initHeaderData():data key %1 already exist!")
                               .arg(dataInfoVector.at(i).second);
            } else if (dataInfoVector.at(i).second.isEmpty()) {
                qCritical() << QString("QExtTcpPacketHeaderPrivate::initHeaderData():data key in No.%1 can not be empty!")
                               .arg(dataInfoVector.at(i).second);
            } else {
                m_typeMap.insert(dataInfoVector.at(i).second, dataInfoVector.at(i).first);
                m_dataMap.insert(dataInfoVector.at(i).second, QExtTcpPacketVariant(QByteArray(), dataInfoVector.at(i).first));
            }
        }
        this->updateHeaderSize();
    } else {
        qCritical() << QString("QExtTcpPacketHeaderPrivate::initDataPair():dataInfoVector size must less than %1")
                       .arg(QEXT_TCP_PACKET_HEADER_META_DATA_MAX_NUM);
    }
}

void QExtTcpPacketHeaderPrivate::updateHeaderSize()
{
    m_headerSize = sizeof(m_headerSize);
    QList<QString> keyList = m_typeMap.keys();
    for (int i = 0; i < keyList.size(); ++i) {
        quint8 dataType = m_typeMap.value(keyList.at(i));
        m_headerSize += QExtTcpPacketVariant::dataTypeSize(dataType);
    }
    m_headerSize += sizeof(m_contentSize);
}



QExtTcpPacketHeader::QExtTcpPacketHeader(const QExtTcpPacketHeader::DataInfoVector &dataInfoVector)
    : dd_ptr(new QExtTcpPacketHeaderPrivate(this))
{
    Q_D(QExtTcpPacketHeader);
    d->initHeaderData(dataInfoVector);
}

QExtTcpPacketHeader::QExtTcpPacketHeader(QExtTcpPacketHeaderPrivate *d,
                                         const DataInfoVector &dataInfoVector)
    : dd_ptr(d)
{
    dd_ptr->initHeaderData(dataInfoVector);
}

QExtTcpPacketHeader::~QExtTcpPacketHeader()
{

}

quint16 QExtTcpPacketHeader::headerSize() const
{
    Q_D(const QExtTcpPacketHeader);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_headerSize;
}

quint16 QExtTcpPacketHeader::contentSize() const
{
    Q_D(const QExtTcpPacketHeader);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_contentSize;
}

void QExtTcpPacketHeader::setContentSize(const quint16 &size)
{
    Q_D(QExtTcpPacketHeader);
    QMutexLocker mutexLocker(&d->m_mutex);
    d->m_contentSize = size;
}

QByteArray QExtTcpPacketHeader::stream() const
{
    Q_D(const QExtTcpPacketHeader);
    QMutexLocker mutexLocker(&d->m_mutex);
    QByteArray stream;
    stream.append(QExtNetworkUtils::quint16HostToNet(d->m_headerSize));

    QList<QString> keyList = d->m_typeMap.keys();
    for (int i = 0; i < keyList.size(); ++i) {
        QString key = keyList.at(i);
        quint8 type = d->m_typeMap.value(key);
        int size = QExtTcpPacketVariant::dataTypeSize(type);
        QByteArray variantStream = d->m_dataMap.value(key).toStream().rightJustified(size, 0, true);
        stream.append(variantStream);
    }

    stream.append(QExtNetworkUtils::quint16HostToNet(d->m_contentSize));
    return stream;
}

bool QExtTcpPacketHeader::setStream(const QByteArray &stream)
{
    Q_D(QExtTcpPacketHeader);
    QMutexLocker mutexLocker(&d->m_mutex);
    if (stream.size() == d->m_headerSize) {
        QList<QString> keyList = d->m_typeMap.keys();
        int offset = sizeof(d->m_headerSize);

        for (int i = 0; i < keyList.size(); ++i) {
            QString key = keyList.at(i);
            quint8 type = d->m_typeMap.value(key);
            int size = QExtTcpPacketVariant::dataTypeSize(type);
            QByteArray data(stream.data() + offset, size);
            d->m_dataMap.insert(key, QExtTcpPacketVariant(data, type));
            offset += size;
        }

        offset = d->m_headerSize - sizeof(d->m_contentSize);
        QExtNetworkUtils::quint16NetToHost(stream.data() + offset, &d->m_contentSize);
        return true;
    }
    return false;
}

bool QExtTcpPacketHeader::isHeaderDataExist(const QString &name) const
{
    Q_D(const QExtTcpPacketHeader);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_dataMap.contains(name);
}

QList<QString> QExtTcpPacketHeader::headerList() const
{
    Q_D(const QExtTcpPacketHeader);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_dataMap.keys();
}

QExtTcpPacketVariant QExtTcpPacketHeader::headerData(const QString &name) const
{
    Q_D(const QExtTcpPacketHeader);
    QMutexLocker mutexLocker(&d->m_mutex);
    return d->m_dataMap.value(name, QExtTcpPacketVariant());
}

bool QExtTcpPacketHeader::setHeaderData(const QString &name, const QExtTcpPacketVariant &data)
{
    Q_D(QExtTcpPacketHeader);
    QMutexLocker mutexLocker(&d->m_mutex);
    if (d->m_dataMap.contains(name)) {
        quint8 type = d->m_typeMap.value(name);
        bool isChars = data.dataType() >= QExtTcpPacketVariant::Data_chars && data.dataType() <= type;
        if (data.dataType() == type || isChars) {
            d->m_dataMap.insert(name, data);
            return true;
        } else {
            qCritical() << QString("QExtTcpPacketHeader::setHeaderData():%1 data type must be %2!").arg(name).arg(type);
        }
    } else {
        qCritical() << QString("QExtTcpPacketHeader::setHeaderData():%1 data not exist!");
    }
    return false;
}
