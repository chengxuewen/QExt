#include <qextQuickLoader.h>
#include <qextQuick.h>
#include <qextQuickConfig.h>

void QExtQuickLoader::load(QQmlEngine *engine)
{
    QExtQuick::instance()->registerTypes(QEXT_QUICK_PLUGIN_NAME);
    QExtQuick::instance()->initQmlEngine(engine, QEXT_QUICK_PLUGIN_NAME);
}

QString QExtQuickLoader::version()
{
    return QExtQuick::instance()->version();
}
