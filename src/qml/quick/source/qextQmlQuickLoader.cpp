#include <qextQmlQuickLoader.h>
#include <qextQmlQuick.h>
#include <qextQmlQuickConfig.h>

void QEXTQmlQuickLoader::load(QQmlEngine *engine)
{
    QEXTQmlQuick::instance()->registerTypes(QEXT_QUICK_PLUGIN_NAME);
    QEXTQmlQuick::instance()->initQmlEngine(engine, QEXT_QUICK_PLUGIN_NAME);
}

QString QEXTQmlQuickLoader::version()
{
    return QEXTQmlQuick::instance()->version();
}
