#ifndef _QEXTCHECKUTILS_H
#define _QEXTCHECKUTILS_H

#include <qextGlobal.h>

class QEXT_CORE_API QExtCheckUtils
{
public:
    enum CRC16Enum
    {
        CRC16_Modbus
    };

    QExtCheckUtils();
    virtual ~QExtCheckUtils() {}

    static quint16 calculateCRC16(CRC16Enum type, const char *chs, int len);
    static quint16 calculateCRC16(CRC16Enum type, const QByteArray &bytes);
    static quint16 calculateCRC16(CRC16Enum type, const QString &string);
};

#endif // _QEXTCHECKUTILS_H
