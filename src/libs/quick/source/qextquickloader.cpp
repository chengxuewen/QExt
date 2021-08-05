#include <qextquickloader.h>
#include <qextquick.h>
#include <qextquickconfig.h>



void QEXTQuickLoader::load(QQmlEngine *engine)
{
    QEXTQuick::instance()->registerTypes(QEXTQUICK_NAME);
    QEXTQuick::instance()->initQmlEngine(engine, QEXTQUICK_NAME);
}

QString QEXTQuickLoader::version()
{
    return QEXTQuick::instance()->version();
}
