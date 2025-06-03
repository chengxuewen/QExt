#ifndef _QEXTENDIAN_H
#define _QEXTENDIAN_H

#include <qextGlobal.h>

#include <QSysInfo>
#include <QtEndian>

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
T qextNetToHost(T src)
{
#if Q_BYTE_ORDER == Q_BIG_ENDIAN
    return qToBigEndian<T>(src);
#else
    return qToLittleEndian<T>(src);
#endif
}

#endif // _QEXTENDIAN_H
