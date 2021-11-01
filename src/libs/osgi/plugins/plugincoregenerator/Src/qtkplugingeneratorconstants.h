#ifndef QTKPLUGINGENERATORCONSTANTS_H
#define QTKPLUGINGENERATORCONSTANTS_H

#include "qtkplugingeneratorcore_global.h"

#include <QString>

struct QTK_PLUGINGENERATORCORE_EXPORT QTKPluginGeneratorConstants
{

    // project wide template markers
    static const QString PLUGIN_LICENSE_MARKER;
    static const QString PLUGIN_EXPORTMACRO_MARKER;
    static const QString PLUGIN_NAMESPACE_MARKER;

    static QStringList getGlobalMarkers();

    // template names
    static const QString TEMPLATE_CMAKELISTS_TXT;
    static const QString TEMPLATE_PLUGINACTIVATOR_H;
    static const QString TEMPLATE_PLUGINACTIVATOR_CPP;

};

#endif // QTKPLUGINGENERATORCONSTANTS_H
