#include "qtkplugingeneratorconstants.h"

#include <QStringList>

const QString QTKPluginGeneratorConstants::PLUGIN_LICENSE_MARKER = "plugin_license";
const QString QTKPluginGeneratorConstants::PLUGIN_EXPORTMACRO_MARKER = "plugin_exportmacro";
const QString QTKPluginGeneratorConstants::PLUGIN_NAMESPACE_MARKER = "plugin_namespace";

QStringList QTKPluginGeneratorConstants::getGlobalMarkers()
{
    return QStringList()
            << PLUGIN_LICENSE_MARKER
            << PLUGIN_EXPORTMACRO_MARKER
            << PLUGIN_NAMESPACE_MARKER;
}

const QString QTKPluginGeneratorConstants::TEMPLATE_CMAKELISTS_TXT = "CMakeLists.txt";
const QString QTKPluginGeneratorConstants::TEMPLATE_PLUGINACTIVATOR_H = "PluginActivator.h";
const QString QTKPluginGeneratorConstants::TEMPLATE_PLUGINACTIVATOR_CPP = "PluginActivator.cpp";
