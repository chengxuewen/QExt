#include "qtkplugingeneratorcmakelists.h"
#include "qtkplugingeneratorconstants.h"

#include <QTextStream>

const QString QTKPluginGeneratorCMakeLists::PLUGIN_PROJECT_NAME_MARKER = "plugin_project_name";
const QString QTKPluginGeneratorCMakeLists::PLUGIN_SRCS_MARKER = "plugin_srcs";
const QString QTKPluginGeneratorCMakeLists::PLUGIN_MOC_SRCS_MARKER = "plugin_moc_srcs";
const QString QTKPluginGeneratorCMakeLists::PLUGIN_RESOURCES_MARKER = "plugin_resources";
const QString QTKPluginGeneratorCMakeLists::PLUGIN_UI_FORMS_MARKER = "plugin_ui_forms";

QTKPluginGeneratorCMakeLists::QTKPluginGeneratorCMakeLists(QTKPluginGeneratorAbstractTemplate *parent) :
    QTKPluginGeneratorAbstractTemplate("CMakeLists.txt", parent)
{
}

QString QTKPluginGeneratorCMakeLists::generateContent()
{
    QString content;
    QTextStream stream(&content);

    stream
            << "PROJECT(" << this->getContent(PLUGIN_PROJECT_NAME_MARKER).front() << ")\n\n"
            << "SET(PLUGIN_export_directive \"" << this->getContent(QTKPluginGeneratorConstants::PLUGIN_EXPORTMACRO_MARKER).front() << "\")\n\n"
            << "SET(PLUGIN_SRCS\n";

    QStringList markerContent = this->getContent(PLUGIN_SRCS_MARKER);
    markerContent.sort();
    for (QStringListIterator it(markerContent); it.hasNext();)
    {
        stream << "  " << it.next() << "\n";
    }

    stream
            << ")\n\n"
            << "# Files which should be processed by Qts moc\n"
            << "SET(PLUGIN_MOC_SRCS\n";

    markerContent = this->getContent(PLUGIN_MOC_SRCS_MARKER);
    markerContent.sort();
    for (QStringListIterator it(markerContent); it.hasNext();)
    {
        stream << "  " << it.next() << "\n";
    }

    stream
            << ")\n\n"
            << "# Qt Designer files which should be processed by Qts uic\n"
            << "SET(PLUGIN_UI_FORMS\n";

    markerContent = this->getContent(PLUGIN_UI_FORMS_MARKER);
    markerContent.sort();
    for (QStringListIterator it(markerContent); it.hasNext();)
    {
        stream << "  " << it.next() << "\n";
    }

    stream
            << ")\n\n"
            << "# QRC Files which should be compiled into the plugin\n"
            << "SET(PLUGIN_resources\n";

    markerContent = this->getContent(PLUGIN_RESOURCES_MARKER);
    markerContent.sort();
    for (QStringListIterator it(markerContent); it.hasNext();)
    {
        stream << "  " << it.next() << "\n";
    }

    stream
            << ")\n\n"
            << "#Compute the plugin dependencies\n"
            << "QTKFunctionGetTargetLibraries(PLUGIN_target_libraries)\n\n"
            << "QTKMacroBuildPlugin(\n"
            << "  NAME ${PROJECT_NAME}\n"
            << "  EXPORT_DIRECTIVE ${PLUGIN_export_directive}\n"
            << "  SRCS ${PLUGIN_SRCS}\n"
            << "  MOC_SRCS ${PLUGIN_MOC_SRCS}\n"
            << "  UI_FORMS ${PLUGIN_UI_FORMS}\n"
            << "  RESOURCES ${PLUGIN_resources}\n"
            << "  TARGET_LIBRARIES ${PLUGIN_target_libraries}\n"
            << ")\n";

    return content;
}

QStringList QTKPluginGeneratorCMakeLists::getMarkers() const
{
    QStringList markers = QTKPluginGeneratorAbstractTemplate::getMarkers();

    markers << PLUGIN_PROJECT_NAME_MARKER
            << PLUGIN_SRCS_MARKER
            << PLUGIN_MOC_SRCS_MARKER
            << PLUGIN_RESOURCES_MARKER;

    return markers;
}
