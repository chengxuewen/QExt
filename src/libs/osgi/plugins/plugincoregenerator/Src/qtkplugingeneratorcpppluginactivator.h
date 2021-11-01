#ifndef QTKPLUGINGENERATORCPPPLUGINACTIVATOR_H
#define QTKPLUGINGENERATORCPPPLUGINACTIVATOR_H

#include "qtkplugingeneratorcpptemplate.h"

class QTK_PLUGINGENERATORCORE_EXPORT QTKPluginGeneratorCppPluginActivator
        : public QTKPluginGeneratorCppTemplate
{

public:

    static const QString PLUGINACTIVATOR_START_MARKER;
    static const QString PLUGINACTIVATOR_STOP_MARKER;

    QTKPluginGeneratorCppPluginActivator(QTKPluginGeneratorAbstractTemplate* parent = 0);

    QString generateContent();

    QStringList getMarkers() const;

};

#endif // QTKPLUGINGENERATORCPPPLUGINACTIVATOR_H
