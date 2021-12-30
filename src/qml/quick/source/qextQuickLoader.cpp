#include <qextQuickLoader.h>
#include <qextQuick.h>
#include <qextQuickConfig.h>

void QEXTQuickLoader::load(QQmlEngine *engine)
{
    QEXTQuick::instance()->registerTypes(QEXT_QUICK_PLUGIN_NAME);
    QEXTQuick::instance()->initQmlEngine(engine, QEXT_QUICK_PLUGIN_NAME);
}

QString QEXTQuickLoader::version()
{
    return QEXTQuick::instance()->version();
}
