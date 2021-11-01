#ifndef QTKPLUGINGENERATORCPPTEMPLATE_H
#define QTKPLUGINGENERATORCPPTEMPLATE_H

#include "qtkplugingeneratorabstracttemplate.h"

class QTK_PLUGINGENERATORCORE_EXPORT QTKPluginGeneratorCppTemplate :
        public QTKPluginGeneratorAbstractTemplate
{
public:

    static const QString CPP_CLASSNAME_MARKER;
    static const QString CPP_INCLUDES_MARKER;
    static const QString CPP_GLOBAL_MARKER;
    static const QString CPP_METHODS_MARKER;
    static const QString CPP_CONSTRUCTOR_INITLIST_MARKER;
    static const QString CPP_CONSTRUCTOR_BODY_MARKER;
    static const QString CPP_DESTRUCTOR_BODY_MARKER;

    QTKPluginGeneratorCppTemplate(const QString& name, QTKPluginGeneratorAbstractTemplate* parent = 0);

    QStringList getMarkers() const;

    QString generateContent();

protected:

    QString getClassNameToken() const;
};

#endif // QTKPLUGINGENERATORCPPTEMPLATE_H
