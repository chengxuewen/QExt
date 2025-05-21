#ifndef _QEXTCRCUTILS_H
#define _QEXTCRCUTILS_H

#include <qextGlobal.h>

class QEXT_CORE_API QExtCRCUtils
{
public:
    QExtCRCUtils();
    virtual ~QExtCRCUtils() {}

    static quint16 calculateCRC16(const char *chs, int len);
    static quint16 calculateCRC16(const QByteArray &bytes);
    static quint16 calculateCRC16(const QString &string);
};

#endif // _QEXTCRCUTILS_H
