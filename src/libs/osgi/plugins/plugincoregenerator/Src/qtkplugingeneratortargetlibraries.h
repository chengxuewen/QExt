#ifndef QTKPLUGINGENERATORTARGETLIBRARIES_H
#define QTKPLUGINGENERATORTARGETLIBRARIES_H

#include "qtkplugingeneratorabstracttemplate.h"

class QTK_PLUGINGENERATORCORE_EXPORT QTKPluginGeneratorTargetLibraries
        : public QTKPluginGeneratorAbstractTemplate
{

public:

    static const QString TARGETLIBRARIES_MARKER;

    QTKPluginGeneratorTargetLibraries(QTKPluginGeneratorAbstractTemplate* parent = 0);

    QString generateContent();

    QStringList getMarkers() const;
};

#endif // QTKPLUGINGENERATORTARGETLIBRARIES_H
