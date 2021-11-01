#include "qtkplugingenerator_p.h"

#include <qtkinfo.h>
#include <QTKPluginFramework/QTKPluginFrameworkFactory>
#include <QTKPluginFramework/QTKPluginFramework>
#include <QTKPluginFramework/QTKServiceReference>
#include <QTKPluginFramework/QTKPluginException>
#include <QTKPluginFramework/QTKPluginContext>
#include <QTKPluginGeneratorCore/QTKPluginGeneratorConstants>

#include <QApplication>
#include <QSettings>
#include <QDirIterator>
#include <QInputDialog>
#include <QSharedPointer>
#include <QDebug>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

int main(int argv, char** argc)
{
    QApplication app(argv, argc);

    qApp->setOrganizationName("QTK");
    qApp->setOrganizationDomain("commontk.org");
    qApp->setApplicationName("QTKPluginGenerator");

    // init global template defaults
    QSettings settings;
    if (!settings.contains(QTKPluginGeneratorConstants::PLUGIN_LICENSE_MARKER))
    {
        QFile license(":/generatordefaults/license.txt");
        license.open(QIODevice::ReadOnly);
        QString licenseText = license.readAll();
        bool ok;
        QString organization = QInputDialog::getText(0, qApp->translate("OrganizationInputDialog", "QTK Plugin Generator"),
                                                     qApp->translate("OrganizationInputDialog", "Enter the name of your organization:"),
                                                     QLineEdit::Normal, qApp->translate("OrganizationInputDialog", "<your-organization>"), &ok);
        if (!ok)
        {
            exit(0);
        }
        organization.replace("\\n", "\n");
        settings.setValue(QTKPluginGeneratorConstants::PLUGIN_LICENSE_MARKER, licenseText.arg(organization));
    }

    QTKPluginFrameworkFactory fwFactory;
    QSharedPointer<QTKPluginFramework> framework = fwFactory.getFramework();

    try {
        framework->init();
    }
    catch (const QTKPluginException& exc)
    {
        qCritical() << "Failed to initialize the plug-in framework:" << exc;
        exit(1);
    }

#ifdef CMAKE_INTDIR
    QString pluginPath = QTK_PLUGIN_DIR CMAKE_INTDIR "/";
#else
    QString pluginPath = QTK_PLUGIN_DIR;
#endif

    qApp->addLibraryPath(pluginPath);

    QStringList libFilter;
    libFilter << "*.dll" << "*.so" << "*.dylib";
    QDirIterator dirIter(pluginPath, libFilter, QDir::Files);
    while(dirIter.hasNext())
    {
        try
        {
            QString fileLocation = dirIter.next();
            if (fileLocation.contains("org_commontk_plugingenerator"))
            {
                QSharedPointer<QTKPlugin> plugin = framework->getPluginContext()->installPlugin(QUrl::fromLocalFile(fileLocation));
                plugin->start(QTKPlugin::StartOption_StartTransient);
            }
        }
        catch (const QTKPluginException& e)
        {
            qCritical() << e.what();
        }
    }

    framework->start();

    QTKPluginGenerator generator(framework.data());
    generator.show();

    return app.exec();

}
