#ifndef _QEXTSTRINGUTILS_H
#define _QEXTSTRINGUTILS_H

#include <qextGlobal.h>

#include <QObject>

class QEXT_CORE_API QExtStringUtils
{
public:
    QExtStringUtils() {}
    virtual ~QExtStringUtils() {}

    static QString toUnicodesString(const QString &string);
    static QString fromUnicodesString(const QString &string);
};

#define QEXT_TO_UNICODES_STRING(s) QExtStringUtils::toUnicodesString(s)
#define QEXT_FROM_UNICODES_STRING(s) QExtStringUtils::fromUnicodesString(s)

#endif // _QEXTSTRINGUTILS_H
