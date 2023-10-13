#include <qextDateTimeUtils.h>

#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QProcess>
#include <QTime>

void QExtDateTimeUtils::mSleep(const int &iMSec)
{
    QTime dieTime = QTime::currentTime().addMSecs(iMSec);
    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
