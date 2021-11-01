#include "qtkplugingeneratortargetlibraries.h"

#include <QTextStream>

const QString QTKPluginGeneratorTargetLibraries::TARGETLIBRARIES_MARKER = "targetlibraries";

QTKPluginGeneratorTargetLibraries::QTKPluginGeneratorTargetLibraries(QTKPluginGeneratorAbstractTemplate* parent)
    : QTKPluginGeneratorAbstractTemplate("target_libraries.cmake", parent)
{

}

QString QTKPluginGeneratorTargetLibraries::generateContent()
{
    QString content;
    QTextStream stream(&content);

    stream << "# See CMake/QTKFunctionGetTargetLibraries.cmake\n"
           << "#\n"
           << "# This file should list the libraries required to build the current QTK plugin.\n"
           << "# For specifying required plugins, see the manifest_headers.cmake file.\n"
           << "#\n\n"
           << "SET(target_libraries\n";

    QStringList libs = getContent(TARGETLIBRARIES_MARKER);
    foreach(QString lib, libs)
    {
        stream << "  " << lib << "\n";
    }

    stream << ")\n";

    return content;
}

QStringList QTKPluginGeneratorTargetLibraries::getMarkers() const
{
    QStringList markers = QTKPluginGeneratorAbstractTemplate::getMarkers();

    markers << TARGETLIBRARIES_MARKER;
    return markers;
}
