#include "htkplugingenerator_p.h"

#include <htkinfo.h>
#include <HTKPluginFramework/HTKPluginFrameworkFactory>
#include <HTKPluginFramework/HTKPluginFramework>
#include <HTKPluginFramework/HTKPluginException>
#include <HTKPluginFramework/HTKPluginContext>
#include <HTKPluginGeneratorCore/HTKPluginGeneratorConstants>

#include <QApplication>
#include <QSettings>
#include <QDirIterator>
#include <QInputDialog>
#include <QDebug>

int main(int argv, char** argc)
{
    QApplication app(argv, argc);

    qApp->setOrganizationName("HTK");
    qApp->setOrganizationDomain("commontk.org");
    qApp->setApplicationName("HTKPluginGenerator");

    // init global template defaults
    QSettings settings;
    if (!settings.contains(HTKPluginGeneratorConstants::PLUGIN_LICENSE_MARKER))
    {
        QFile license(":/generatordefaults/license.txt");
        license.open(QIODevice::ReadOnly);
        QString licenseText = license.readAll();
        bool ok;
        QString organization = QInputDialog::getText(0, qApp->translate("OrganizationInputDialog", "HTK Plugin Generator"),
                                                     qApp->translate("OrganizationInputDialog", "Enter the name of your organization:"),
                                                     QLineEdit::Normal, qApp->translate("OrganizationInputDialog", "<your-organization>"), &ok);
        if (!ok)
        {
            exit(0);
        }
        organization.replace("\\n", "\n");
        settings.setValue(HTKPluginGeneratorConstants::PLUGIN_LICENSE_MARKER, licenseText.arg(organization));
    }

    HTKPluginFrameworkFactory fwFactory;
    QSharedPointer<HTKPluginFramework> framework = fwFactory.getFramework();

    try {
        framework->init();
    }
    catch (const HTKPluginException& exc)
    {
        qCritical() << "Failed to initialize the plug-in framework:" << exc;
        exit(1);
    }

#ifdef CMAKE_INTDIR
    QString pluginPath = HTK_PLUGIN_DIR CMAKE_INTDIR "/";
#else
    QString pluginPath = HTK_PLUGIN_DIR;
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
                QSharedPointer<HTKPlugin> plugin = framework->getPluginContext()->installPlugin(QUrl::fromLocalFile(fileLocation));
                plugin->start(HTKPlugin::StartOption_StartTransient);
            }
        }
        catch (const HTKPluginException& e)
        {
            qCritical() << e.what();
        }
    }

    framework->start();

    HTKPluginGenerator generator(framework.data());
    generator.show();

    return app.exec();

}
