#include <qextOnceFlag.h>

#include <QGlobalStatic>
#include <QThreadStorage>

Q_GLOBAL_STATIC(QThreadStorage<QExtOnceFlag*>, sgLocalOnceFlag)

QExtOnceFlag *QExtOnceFlag::localOnceFlag()
{
    if (!sgLocalOnceFlag()->hasLocalData())
    {
        sgLocalOnceFlag()->setLocalData(new QExtOnceFlag);
    }
    return sgLocalOnceFlag()->localData();
}

