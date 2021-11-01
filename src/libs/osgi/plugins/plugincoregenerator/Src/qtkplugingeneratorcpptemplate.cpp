#include "qtkplugingeneratorcpptemplate.h"
#include "qtkplugingeneratorconstants.h"

#include <QTextStream>

const QString QTKPluginGeneratorCppTemplate::CPP_CLASSNAME_MARKER = "cpp_classname";
const QString QTKPluginGeneratorCppTemplate::CPP_INCLUDES_MARKER = "cpp_includes";
const QString QTKPluginGeneratorCppTemplate::CPP_GLOBAL_MARKER = "cpp_globals";
const QString QTKPluginGeneratorCppTemplate::CPP_METHODS_MARKER = "cpp_methods";
const QString QTKPluginGeneratorCppTemplate::CPP_CONSTRUCTOR_INITLIST_MARKER = "cpp_constructor_initlist";
const QString QTKPluginGeneratorCppTemplate::CPP_CONSTRUCTOR_BODY_MARKER = "cpp_constructor_body";
const QString QTKPluginGeneratorCppTemplate::CPP_DESTRUCTOR_BODY_MARKER = "cpp_destructor_body";

QTKPluginGeneratorCppTemplate::QTKPluginGeneratorCppTemplate(
        const QString& name, QTKPluginGeneratorAbstractTemplate* parent)
    : QTKPluginGeneratorAbstractTemplate(name, parent)
{

}

QStringList QTKPluginGeneratorCppTemplate::getMarkers() const
{
    QStringList markers = QTKPluginGeneratorAbstractTemplate::getMarkers();

    markers << CPP_CLASSNAME_MARKER
            << CPP_INCLUDES_MARKER
            << CPP_GLOBAL_MARKER
            << CPP_METHODS_MARKER
            << CPP_CONSTRUCTOR_INITLIST_MARKER
            << CPP_CONSTRUCTOR_BODY_MARKER;

    return markers;
}

QString QTKPluginGeneratorCppTemplate::generateContent()
{
    QString content;
    QTextStream stream(&content);

    // get the namespace
    QString namespaceToken;
    QStringList namespc = this->getContent(QTKPluginGeneratorConstants::PLUGIN_NAMESPACE_MARKER);
    if (!namespc.isEmpty() && !namespc.back().isEmpty())
    {
        namespaceToken = namespc.back();
    }

    // License header
    QStringList licenseText = this->getContent(QTKPluginGeneratorConstants::PLUGIN_LICENSE_MARKER);
    if (!licenseText.isEmpty() && !licenseText.back().isEmpty())
    {
        stream << licenseText.back() << "\n\n";
    }

    // include statements
    QStringList includes = this->getContent(CPP_INCLUDES_MARKER);
    if (!includes.isEmpty())
    {
        foreach(QString includeStatement, includes)
        {
            stream << includeStatement << "\n";
        }
        stream << "\n";
    }

    // namespace
    if (!namespaceToken.isEmpty())
    {
        stream << "namespace " << namespaceToken << " {\n\n";
    }

    // global definitions
    QStringList globals = this->getContent(CPP_GLOBAL_MARKER);
    if (!globals.isEmpty())
    {
        foreach (QString global, globals)
        {
            stream << global << "\n";
        }
        stream << "\n";
    }

    // method definitions
    QStringList methods = this->getContent(CPP_METHODS_MARKER);
    if (!methods.isEmpty())
    {
        foreach (QString method, methods)
        {
            stream << method << "\n\n";
        }
    }

    // end namespace
    if (!namespaceToken.isEmpty())
    {
        stream << "} // end namespace " << namespaceToken << "\n";
    }

    return content;
}

QString QTKPluginGeneratorCppTemplate::getClassNameToken() const
{
    QString classNameToken;
    QStringList classname = this->getContent(CPP_CLASSNAME_MARKER);
    if (!classname.isEmpty() && !classname.back().isEmpty())
    {
        classNameToken = classname.back();
    }
    else
    {
        // use the filename without ending
        classNameToken = getFilename().left(getFilename().lastIndexOf("."));
    }

    return classNameToken;
}
