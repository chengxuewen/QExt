#ifndef _QEXTDATETIMEUTILS_H
#define _QEXTDATETIMEUTILS_H

#include <qextGlobal.h>
#include "qextUtilsGlobal.h"

#include <QObject>

class QEXT_UTILS_API QEXTDateTimeUtils
{
public:
    virtual ~QEXTDateTimeUtils() {}

    static void mSleep(const int &iMSec);
};

#endif // _QEXTDATETIMEUTILS_H
