#ifndef QTKPLUGINGENERATORCMAKELISTS_H
#define QTKPLUGINGENERATORCMAKELISTS_H

#include "qtkplugingeneratorabstracttemplate.h"

class QTK_PLUGINGENERATORCORE_EXPORT QTKPluginGeneratorCMakeLists : public QTKPluginGeneratorAbstractTemplate
{

public:

    static const QString PLUGIN_PROJECT_NAME_MARKER;
    static const QString PLUGIN_SRCS_MARKER;
    static const QString PLUGIN_MOC_SRCS_MARKER;
    static const QString PLUGIN_RESOURCES_MARKER;
    static const QString PLUGIN_UI_FORMS_MARKER;

    QTKPluginGeneratorCMakeLists(QTKPluginGeneratorAbstractTemplate *parent = 0);

    QString generateContent();

    QStringList getMarkers() const;

};

#endif // QTKPLUGINGENERATORCMAKELISTS_H
