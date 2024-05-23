#ifndef _QEXTDATETIMEUTILS_H
#define _QEXTDATETIMEUTILS_H

#include <qextGlobal.h>

#include <QObject>

class QEXT_CORE_API QExtDateTimeUtils
{
public:
    virtual ~QExtDateTimeUtils() {}

    static void loopWait(const int &msec);

    static qint64 secsTimeSinceEpoch();
    static qint64 msecsTimeSinceEpoch();
    static QString secsTimeSinceEpochString(qint64 secs = -1);
    static QString msecsTimeSinceEpochString(qint64 msecs = -1);
};

#endif // _QEXTDATETIMEUTILS_H
