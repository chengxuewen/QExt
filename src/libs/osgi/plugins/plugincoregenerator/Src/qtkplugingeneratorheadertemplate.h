#ifndef QTKPLUGINGENERATORHEADERTEMPLATE_H
#define QTKPLUGINGENERATORHEADERTEMPLATE_H

#include "qtkplugingeneratorabstracttemplate.h"

class QTK_PLUGINGENERATORCORE_EXPORT QTKPluginGeneratorHeaderTemplate :
        public QTKPluginGeneratorAbstractTemplate
{
public:

    static const QString H_CLASSNAME_MARKER;
    static const QString H_INCLUDES_MARKER;
    static const QString H_FORWARD_DECL_MARKER;
    static const QString H_FORWARD_DECL_NAMESPACE_MARKER;
    static const QString H_SUPERCLASSES_MARKER;
    static const QString H_DEFAULT_ACCESS_MARKER;
    static const QString H_PUBLIC_MARKER;
    static const QString H_PROTECTED_MARKER;
    static const QString H_PRIVATE_MARKER;

    QTKPluginGeneratorHeaderTemplate(const QString& name, QTKPluginGeneratorAbstractTemplate* parent = 0);

    QStringList getMarkers() const;

    QString generateContent();
};

#endif // QTKPLUGINGENERATORHEADERTEMPLATE_H
