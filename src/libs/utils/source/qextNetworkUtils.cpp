#include "qextNetworkUtils.h"

#include <QDebug>
#include <QtEndian>
#include <qmath.h>


#define QEXT_NET_UTILS_INT_BYTE_SIZE            4
#define QEXT_NET_UTILS_DOUBLE_BYTE_SIZE         6
#define QEXT_NET_UTILS_DOUBLE_PRECISION         10000000

template<typename T>
QByteArray hostToNet(T src)
{
    QByteArray byteArray;
    int byteSize = sizeof(T);

    uchar *uch = (uchar *) malloc(byteSize);
    memset(uch, 0, byteSize);

    qToBigEndian<T>(src, uch);

    for (int i = 0; i < byteSize; ++i)
    {
        byteArray.append(uch[i]);
    }
    free(uch);
    return byteArray;
}

template<typename T>
void hostToNet(T src, char *des)
{
    int byteSize = sizeof(T);
    memset(des, 0, byteSize);

    uchar *uch = (uchar *) malloc(byteSize);
    memset(uch, 0, byteSize);

    qToBigEndian<T>(src, uch);
    memcpy(des, uch, byteSize);
    free(uch);
}

template<typename T>
T netToHost(QByteArray src)
{
    int byteSize = sizeof(T);

    uchar *uch = (uchar *) malloc(byteSize);
    memset(uch, 0, byteSize);
    memcpy(uch, src.data(), src.size());

    T value = qFromBigEndian<T>(uch);
    free(uch);
    return value;
}

template<typename T>
T netToHost(char *src)
{
    int byteSize = sizeof(T);

    uchar *uch = (uchar *) malloc(byteSize);
    memcpy(uch, src, byteSize);

    T value = qFromBigEndian<T>(uch);
    free(uch);
    return value;
}

template<typename T>
void netToHost(const char *src, T *des)
{
    int byteSize = sizeof(T);

    uchar *uch = (uchar *) malloc(byteSize);
    memcpy(uch, src, byteSize);

    *des = qFromBigEndian<T>(uch);
    free(uch);
}

template<typename T>
QString valueToBinaryString(T src)
{
    int byteSize = sizeof(T);
    char *ch = (char *) malloc(byteSize);
    memcpy(ch, &src, byteSize);

    QString binary;
    for (int i = byteSize - 1; i >= 0; --i)
    {
        int bit[8] = {0};
        for (int j = 7; j >= 0; --j)
        {
            bit[j] = QExtNetworkUtils::testBit(ch[i], j);
            binary.append(QString::number(bit[j]));
        }
    }
    free(ch);
    return binary;
}

QExtNetworkUtils::QExtNetworkUtils()
{

}

QByteArray QExtNetworkUtils::qint16HostToNet(qint16 src)
{
    return hostToNet<qint16>(src);
}

QByteArray QExtNetworkUtils::quint16HostToNet(quint16 src)
{
    return hostToNet<quint16>(src);
}

QByteArray QExtNetworkUtils::qint32HostToNet(qint32 src)
{
    return hostToNet<qint32>(src);
}

QByteArray QExtNetworkUtils::quint32HostToNet(quint32 src)
{
    return hostToNet<quint32>(src);
}

QByteArray QExtNetworkUtils::qint64HostToNet(qint64 src)
{
    return hostToNet<qint64>(src);
}

QByteArray QExtNetworkUtils::quint64HostToNet(quint64 src)
{
    return hostToNet<quint64>(src);
}

void QExtNetworkUtils::qint16HostToNet(qint16 src, char *des)
{
    hostToNet<qint16>(src, des);
}

void QExtNetworkUtils::quint16HostToNet(quint16 src, char *des)
{
    hostToNet<quint16>(src, des);
}

void QExtNetworkUtils::qint32HostToNet(qint32 src, char *des)
{
    hostToNet<qint32>(src, des);
}

void QExtNetworkUtils::quint32HostToNet(quint32 src, char *des)
{
    hostToNet<quint32>(src, des);
}

void QExtNetworkUtils::qint64HostToNet(qint64 src, char *des)
{
    hostToNet<qint64>(src, des);
}

void QExtNetworkUtils::quint64HostToNet(quint64 src, char *des)
{
    hostToNet<quint64>(src, des);
}

qint16 QExtNetworkUtils::qint16NetToHost(QByteArray src)
{
    return netToHost<qint16>(src);
}

quint16 QExtNetworkUtils::quint16NetToHost(QByteArray src)
{
    return netToHost<quint16>(src);
}

qint32 QExtNetworkUtils::qint32NetToHost(QByteArray src)
{
    return netToHost<qint32>(src);
}

quint32 QExtNetworkUtils::quint32NetToHost(QByteArray src)
{
    return netToHost<quint32>(src);
}

qint64 QExtNetworkUtils::qint64NetToHost(QByteArray src)
{
    return netToHost<qint64>(src);
}

quint64 QExtNetworkUtils::quint64NetToHost(QByteArray src)
{
    return netToHost<quint64>(src);
}

qint16 QExtNetworkUtils::qint16NetToHost(char *src)
{
    return netToHost<qint16>(src);
}

quint16 QExtNetworkUtils::quint16NetToHost(char *src)
{
    return netToHost<quint16>(src);
}

qint32 QExtNetworkUtils::qint32NetToHost(char *src)
{
    return netToHost<qint32>(src);
}

quint32 QExtNetworkUtils::quint32NetToHost(char *src)
{
    return netToHost<quint32>(src);
}

qint64 QExtNetworkUtils::qint64NetToHost(char *src)
{
    return netToHost<qint64>(src);
}

quint64 QExtNetworkUtils::quint64NetToHost(char *src)
{
    return netToHost<quint64>(src);
}

void QExtNetworkUtils::qint16NetToHost(const char *src, qint16 *des)
{
    netToHost<qint16>(src, des);
}

void QExtNetworkUtils::quint16NetToHost(const char *src, quint16 *des)
{
    netToHost<quint16>(src, des);
}

void QExtNetworkUtils::qint32NetToHost(const char *src, qint32 *des)
{
    netToHost<qint32>(src, des);
}

void QExtNetworkUtils::quint32NetToHost(const char *src, quint32 *des)
{
    netToHost<quint32>(src, des);
}

void QExtNetworkUtils::qint64NetToHost(const char *src, qint64 *des)
{
    netToHost<qint64>(src, des);
}

void QExtNetworkUtils::quint64NetToHost(const char *src, quint64 *des)
{
    netToHost<quint64>(src, des);
}

void QExtNetworkUtils::setBitValue(char *c, int bit, int value)
{
    if (value)
    {
        QExtNetworkUtils::setBit(c, bit);
    }
    else
    {
        QExtNetworkUtils::clearBit(c, bit);
    }
}

void QExtNetworkUtils::setBit(char *c, int bit)
{
    *c |= (1 << bit);
}

void QExtNetworkUtils::clearBit(char *c, int bit)
{
    *c &= ~(1 << bit);
}

bool QExtNetworkUtils::testBit(char c, int bit)
{
    return c &= (1 << bit);
}

QString QExtNetworkUtils::charToBinaryString(char c)
{
    QString binary;
    bool bit[8] = {0};
    for (int i = 7; i >= 0; --i)
    {
        bit[i] = QExtNetworkUtils::testBit(c, i);
        binary.append(QString::number(bit[i]));
    }
    return binary;
}

QString QExtNetworkUtils::qint8ToBinaryString(qint8 src)
{
    return charToBinaryString(src);
}

QString QExtNetworkUtils::quint8ToBinaryString(quint8 src)
{
    return valueToBinaryString<quint8>(src);
}

QString QExtNetworkUtils::qint16ToBinaryString(qint16 src)
{
    return valueToBinaryString<qint16>(src);
}

QString QExtNetworkUtils::quint16ToBinaryString(quint16 src)
{
    return valueToBinaryString<quint16>(src);
}

QString QExtNetworkUtils::qint32ToBinaryString(qint32 src)
{
    return valueToBinaryString<qint32>(src);
}

QString QExtNetworkUtils::quint32ToBinaryString(quint32 src)
{
    return valueToBinaryString<quint32>(src);
}

QString QExtNetworkUtils::qint64ToBinaryString(qint64 src)
{
    return valueToBinaryString<qint64>(src);
}

QString QExtNetworkUtils::quint64ToBinaryString(quint64 src)
{
    return valueToBinaryString<quint64>(src);
}

QString QExtNetworkUtils::byteArrayToBinaryString(QByteArray src)
{
    int byteSize = src.size();
    char *ch = (char *) malloc(byteSize);
    memcpy(ch, src.data(), byteSize);

    QString binary;
    for (int i = byteSize; i >= 0; --i)
    {
        binary.append(QExtNetworkUtils::charToBinaryString(ch[i]));
    }
    free(ch);
    return binary;
}


