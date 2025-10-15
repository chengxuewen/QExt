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
    static qint64 usecsTimeSinceEpoch();
    static qint64 nsecsTimeSinceEpoch();
    static QString localTimeStringFromSecsSinceEpoch(qint64 secs = -1);
    static QString localTimeStringFromMSecsSinceEpoch(qint64 msecs = -1);
    static QString localTimeTrimedStringFromSecsSinceEpoch(qint64 secs = -1);
    static QString localTimeTrimedStringFromMSecsSinceEpoch(qint64 msecs = -1);
};

#endif // _QEXTDATETIMEUTILS_H
