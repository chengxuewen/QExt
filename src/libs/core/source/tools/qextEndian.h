#ifndef _QEXTENDIAN_H
#define _QEXTENDIAN_H

#include <qextGlobal.h>

#include <QSysInfo>
#include <QtEndian>
#include <QByteArray>

template<typename T>
T qextHostToNet(T src)
{
#if Q_BYTE_ORDER == Q_BIG_ENDIAN
    return qToLittleEndian<T>(src);
#else
    return qToBigEndian<T>(src);
#endif
}
template<typename T>
void qextHostToNet(const void *source, qsizetype count, void *dest)
{
#if Q_BYTE_ORDER == Q_BIG_ENDIAN
    qToLittleEndian<T>(source, count, dest);
#else
    qToBigEndian<T>(source, count, dest);
#endif
}

template<typename T>
T qextNetToHost(T src)
{
#if Q_BYTE_ORDER == Q_BIG_ENDIAN
    return qToBigEndian<T>(src);
#else
    return qToLittleEndian<T>(src);
#endif
}
template<typename T>
void qextNetToHost(const void *source, qsizetype count, void *dest)
{
#if Q_BYTE_ORDER == Q_BIG_ENDIAN
    qToBigEndian<T>(source, count, dest);
#else
    qToLittleEndian<T>(source, count, dest);
#endif
}

static inline QByteArray qextHostToNetBytes(double value)
{
    QEXT_ASSERT_X(sizeof(double) == 8, "qextHostToNetBytes", "double must be 8 bytes");
    quint64 hostU64;
    std::memcpy(&hostU64, &value, sizeof(double));
    quint64 netU64 = qextHostToNet(hostU64);
    return QByteArray(reinterpret_cast<const char*>(&netU64), 8);
}

#endif // _QEXTENDIAN_H
