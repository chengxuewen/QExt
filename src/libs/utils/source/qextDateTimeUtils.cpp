#include "qextDateTimeUtils.h"
#include <QDebug>
#include <QTime>
#include <QDateTime>
#include <QProcess>
#include <QCoreApplication>



void QEXTDateTimeUtils::mSleep(const int &iMSec)
{
    QTime dieTime = QTime::currentTime().addMSecs(iMSec);
    while( QTime::currentTime() < dieTime ) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
