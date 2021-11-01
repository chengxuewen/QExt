#include "qtkplugingeneratormainextension.h"

#include <QTKPluginGeneratorCore/QTKPluginGeneratorCodeModel>
#include <QTKPluginGeneratorCore/QTKPluginGeneratorConstants>
#include <QTKPluginGeneratorCore/QTKPluginGeneratorCMakeLists>
#include <QTKPluginGeneratorCore/QTKPluginGeneratorHeaderTemplate>
#include <QTKPluginGeneratorCore/QTKPluginGeneratorCppPluginActivator>
#include <QTKPluginGeneratorCore/QTKPluginGeneratorTargetLibraries>

QTKPluginGeneratorMainExtension::QTKPluginGeneratorMainExtension()
    : ui(0)
{
    this->setTitle(tr("Main"));
    this->setDescription("The main parameters for a new plugin");
}

QWidget* QTKPluginGeneratorMainExtension::createWidget()
{
    ui = new Ui::QTKPluginGeneratorMainExtension();
    QWidget* container = new QWidget();
    ui->setupUi(container);

    connectSignals();

    setTitle(tr("Main"));

    return container;
}

void QTKPluginGeneratorMainExtension::connectSignals()
{
    connect(ui->symbolicNameEdit, SIGNAL(textChanged(QString)), this, SLOT(symbolicNameChanged()));
    connect(ui->activatorClassEdit, SIGNAL(textChanged(QString)), this, SLOT(activatorClassChanged()));
    connect(ui->symbolicNameEdit, SIGNAL(textChanged(QString)), this, SLOT(updateParameters()));
    connect(ui->exportDirectiveEdit, SIGNAL(textChanged(QString)), this, SLOT(updateParameters()));
    connect(ui->activatorClassEdit, SIGNAL(textChanged(QString)), this, SLOT(updateParameters()));
    connect(ui->activatorHeaderEdit, SIGNAL(textChanged(QString)), this, SLOT(updateParameters()));
    connect(ui->activatorSourceEdit, SIGNAL(textChanged(QString)), this, SLOT(updateParameters()));
}

void QTKPluginGeneratorMainExtension::symbolicNameChanged()
{
    QString symbolicName = ui->symbolicNameEdit->text().replace(".", "_");
    ui->exportDirectiveEdit->setText(symbolicName + "_EXPORT");

    QString activatorClassName;
    QStringList tokens = symbolicName.split('_');

    if (tokens.size() > 1)
    {
        tokens.pop_front();
        activatorClassName += tokens.takeFirst();
        foreach(QString token, tokens)
        {
            activatorClassName += token.left(1).toUpper() + token.mid(1);
        }
    }

    activatorClassName += "Plugin";

    ui->activatorClassEdit->setText(activatorClassName);
    ui->activatorHeaderEdit->setText(activatorClassName + "_p.h");
    ui->activatorSourceEdit->setText(activatorClassName + ".cpp");
}

void QTKPluginGeneratorMainExtension::activatorClassChanged()
{
    QString activatorClassName = ui->activatorClassEdit->text();
    ui->activatorHeaderEdit->setText(activatorClassName + "_p.h");
    ui->activatorSourceEdit->setText(activatorClassName + ".cpp");

    //  ui->advancedButton->setText(tr("Advanced (activator class: %1)").arg(activatorClassName));
}

bool QTKPluginGeneratorMainExtension::verifyParameters(
        const QHash<QString, QVariant>& params)
{
    if (params["symbolic-name"].toString().isEmpty())
    {
        this->setErrorMessage(tr("The symbolic name cannot be empty"));
        return false;
    }

    if (params["export-directive"].toString().isEmpty())
    {
        this->setErrorMessage(tr("The export directive cannot be empty"));
        return false;
    }

    if (params["activator-classname"].toString().isEmpty())
    {
        this->setErrorMessage(tr("The activator class name cannot be empty"));
        return false;
    }

    if (params["activator-headerfile"].toString().isEmpty())
    {
        this->setErrorMessage(tr("The activator header filename cannot be empty"));
        return false;
    }

    if (params["activator-sourcefile"].toString().isEmpty())
    {
        this->setErrorMessage(tr("The activator source filename cannot be empty"));
        return false;
    }

    this->setErrorMessage("");
    return true;
}

void QTKPluginGeneratorMainExtension::updateCodeModel(const QHash<QString, QVariant>& params)
{
    QTKPluginGeneratorCodeModel* codeModel = this->getCodeModel();

    codeModel->setSymbolicName(params["symbolic-name"].toString());
    codeModel->setExportMacroInclude(QString("#include <") + codeModel->getSymbolicName() + "_Export.h>");
    codeModel->setExportMacro(params["export-directive"].toString());

    // Add CMakeLists.txt template
    codeModel->addTemplate(new QTKPluginGeneratorCMakeLists());

    QTKPluginGeneratorAbstractTemplate* cmakelistsTemplate = codeModel->getTemplate(QTKPluginGeneratorConstants::TEMPLATE_CMAKELISTS_TXT);

    cmakelistsTemplate->addContent(QTKPluginGeneratorCMakeLists::PLUGIN_PROJECT_NAME_MARKER,
                                   codeModel->getSymbolicName(),
                                   QTKPluginGeneratorAbstractTemplate::REPLACE);
    cmakelistsTemplate->addContent(QTKPluginGeneratorConstants::PLUGIN_EXPORTMACRO_MARKER,
                                   codeModel->getExportMacro(),
                                   QTKPluginGeneratorAbstractTemplate::REPLACE);

    // Add <plugin-activator>.h template
    QString activatorClassName = params["activator-classname"].toString();
    QTKPluginGeneratorAbstractTemplate* activatorHeaderTemplate =
            new QTKPluginGeneratorHeaderTemplate(QTKPluginGeneratorConstants::TEMPLATE_PLUGINACTIVATOR_H);
    activatorHeaderTemplate->addContent(QTKPluginGeneratorConstants::PLUGIN_LICENSE_MARKER, codeModel->getLicense());
    activatorHeaderTemplate->addContent(QTKPluginGeneratorHeaderTemplate::H_INCLUDES_MARKER, "#include <QTKPluginActivator.h>");
    activatorHeaderTemplate->addContent(QTKPluginGeneratorHeaderTemplate::H_CLASSNAME_MARKER, activatorClassName);
    activatorHeaderTemplate->addContent(QTKPluginGeneratorHeaderTemplate::H_SUPERCLASSES_MARKER, "public QObject, public QTKPluginActivator");
    activatorHeaderTemplate->addContent(QTKPluginGeneratorHeaderTemplate::H_DEFAULT_ACCESS_MARKER, "Q_OBJECT\nQ_INTERFACES(QTKPluginActivator)");
    activatorHeaderTemplate->addContent(QTKPluginGeneratorHeaderTemplate::H_PUBLIC_MARKER, activatorClassName + "();\n~" + activatorClassName + "();");
    activatorHeaderTemplate->addContent(QTKPluginGeneratorHeaderTemplate::H_PUBLIC_MARKER, "void start(QTKPluginContext* context);\nvoid stop(QTKPluginContext* context);");
    activatorHeaderTemplate->addContent(QTKPluginGeneratorHeaderTemplate::H_PUBLIC_MARKER, QString("static ") + activatorClassName + "* getInstance();");
    activatorHeaderTemplate->addContent(QTKPluginGeneratorHeaderTemplate::H_PUBLIC_MARKER, "QTKPluginContext* getPluginContext() const;");
    activatorHeaderTemplate->addContent(QTKPluginGeneratorHeaderTemplate::H_PRIVATE_MARKER, QString("static ") + activatorClassName + "* instance;\nQTKPluginContext* context;");
    activatorHeaderTemplate->setFilename(params["activator-headerfile"].toString());

    codeModel->addTemplate(activatorHeaderTemplate);

    // Add <plugin-activator>.cpp template
    QTKPluginGeneratorAbstractTemplate* activatorCppTemplate =
            new QTKPluginGeneratorCppPluginActivator();
    activatorCppTemplate->addContent(QTKPluginGeneratorConstants::PLUGIN_LICENSE_MARKER, codeModel->getLicense());
    activatorCppTemplate->addContent(QTKPluginGeneratorCppTemplate::CPP_CLASSNAME_MARKER, activatorClassName);
    activatorCppTemplate->addContent(QTKPluginGeneratorCppTemplate::CPP_INCLUDES_MARKER, QString("#include \"") + activatorHeaderTemplate->getFilename() + "\"");
    activatorCppTemplate->addContent(QTKPluginGeneratorCppTemplate::CPP_GLOBAL_MARKER, activatorClassName + "* " + activatorClassName + "::instance = 0;");
    activatorCppTemplate->addContent(QTKPluginGeneratorCppTemplate::CPP_CONSTRUCTOR_INITLIST_MARKER, "context(0)");
    activatorCppTemplate->addContent(QTKPluginGeneratorCppTemplate::CPP_DESTRUCTOR_BODY_MARKER, "");
    activatorCppTemplate->addContent(QTKPluginGeneratorCppPluginActivator::PLUGINACTIVATOR_START_MARKER, "instance = this;\nthis->context = context;");
    activatorCppTemplate->addContent(QTKPluginGeneratorCppTemplate::CPP_METHODS_MARKER, activatorClassName + "* " + activatorClassName + "::getInstance()\n{\n  return instance;\n}");
    activatorCppTemplate->addContent(QTKPluginGeneratorCppTemplate::CPP_METHODS_MARKER, QString("QTKPluginContext* ") + activatorClassName + "::getPluginContext() const\n{\n  return context;\n}");
    activatorCppTemplate->setFilename(params["activator-sourcefile"].toString());
    codeModel->addTemplate(activatorCppTemplate);

    // Add target_libraries.cmake template
    // TODO only add the QTKPluginFramework library if there are no plugin dependencies
    QTKPluginGeneratorAbstractTemplate* targetLibrariesTemplate =
            new QTKPluginGeneratorTargetLibraries();
    targetLibrariesTemplate->addContent(QTKPluginGeneratorTargetLibraries::TARGETLIBRARIES_MARKER, "QTKPluginFramework");
    codeModel->addTemplate(targetLibrariesTemplate);

    // add project files to CMakeLists.txt
    cmakelistsTemplate->addContent(QTKPluginGeneratorCMakeLists::PLUGIN_SRCS_MARKER, activatorCppTemplate->getFilename());
    cmakelistsTemplate->addContent(QTKPluginGeneratorCMakeLists::PLUGIN_MOC_SRCS_MARKER, activatorHeaderTemplate->getFilename());
}

void QTKPluginGeneratorMainExtension::updateParameters()
{
    this->setParameter("symbolic-name", ui->symbolicNameEdit->text());
    this->setParameter("plugin-name", ui->nameEdit->text());
    this->setParameter("plugin-version", ui->versionEdit->text());
    this->setParameter("export-directive", ui->exportDirectiveEdit->text());
    this->setParameter("activator-classname", ui->activatorClassEdit->text());
    this->setParameter("activator-headerfile", ui->activatorHeaderEdit->text());
    this->setParameter("activator-sourcefile", ui->activatorSourceEdit->text());

    this->validate();
}

