#include <qextQmlThemePalette.h>

QString QExtQmlThemePalette::version() const
{
    return QString("%1.%2").arg(QEXT_VERSION_MAJOR).arg(QEXT_VERSION_MAJOR);
}
