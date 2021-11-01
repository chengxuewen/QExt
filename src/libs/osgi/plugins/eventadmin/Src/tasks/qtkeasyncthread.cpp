#include "qtkeasyncthread_p.h"

QTKEASyncThread::QTKEASyncThread(QTKEARunnable *pTarget, QObject *pParent)
    : QTKEAInterruptibleThread(pTarget, pParent)
{
    this->setObjectName(QString("QTKEASyncThread") + QString::number(reinterpret_cast<qint64>(pTarget)));
}
