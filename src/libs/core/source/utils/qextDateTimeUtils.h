#ifndef _QEXTDATETIMEUTILS_H
#define _QEXTDATETIMEUTILS_H

#include <qextGlobal.h>

#include <QObject>

class QEXT_CORE_API QExtDateTimeUtils
{
public:
    virtual ~QExtDateTimeUtils() {}

    static void mSleep(const int &iMSec);
};

#endif // _QEXTDATETIMEUTILS_H
