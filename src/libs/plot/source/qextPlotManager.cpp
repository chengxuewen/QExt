#include <qextPlotManager.h>

#include <qextOnceFlag.h>

QExtPlotManager *QExtPlotManager::instance()
{
    static QExtOnceFlag onceFlag;
    static QExtPlotManager *instance = QEXT_NULLPTR;
    if (onceFlag.enter())
    {
        instance = new QExtPlotManager;
        onceFlag.leave();
    }
    return instance;
}

QExtPlotManager::~QExtPlotManager()
{
}

QExtPlotManager::QExtPlotManager(QObject *parent)
    : QObject(parent)
{
}
