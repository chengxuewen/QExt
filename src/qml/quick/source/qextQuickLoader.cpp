#include <qextQuickLoader.h>
#include <qextQuick.h>
#include <qextQuickConfig.h>

void QEXTQuickLoader::load(QQmlEngine *engine)
{
    QEXTQuick::instance()->registerTypes(QEXTQUICK_NAME);
    QEXTQuick::instance()->initQmlEngine(engine, QEXTQUICK_NAME);
}

QString QEXTQuickLoader::version()
{
    return QEXTQuick::instance()->version();
}
