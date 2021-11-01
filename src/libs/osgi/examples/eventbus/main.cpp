#include "mainwindow.h"

#include <qtkinfo.h>
#include <QTKPluginFramework/QTKPluginFrameworkFactory>
#include <QTKPluginFramework/QTKPluginFramework>
#include <QTKPluginFramework/QTKPluginException>
#include <QTKPluginFramework/QTKPluginContext>
#include <QTKPluginFramework/QTKServiceReference>
#include <QTKEventBus/QTKEventAdminBus>

#include <QApplication>
#include <QString>
#include <QStringList>
#include <QDirIterator>
#include <QWidget>
#include <QFileInfo>


int main(int argv, char** argc) {

    QApplication app(argv, argc);

    // setup the plugin framework
    QTKPluginFrameworkFactory pfwFactory;
    QSharedPointer<QTKPluginFramework> pPluginFrameWork = pfwFactory.getFramework();

    try {
        pPluginFrameWork->init();
        pPluginFrameWork->start();
        qDebug() << "QTK plugin framework start...";
    } catch (const QTKPluginException &e) {
        qCritical() << e.printStackTrace();
        return -1;
    }

    QTKPluginContext *pContext = pPluginFrameWork->getPluginContext();
    QString strPluginPath = QTK_PLUGIN_DIR;

    QStringList listNameFilters;
    listNameFilters.append("*QTKEventBus.dll");
    listNameFilters.append("*QTKEventBus.so");
    listNameFilters.append("*QTKEventBus.dylib");
    QDirIterator dirIter(strPluginPath, listNameFilters, QDir::Files);
    while (dirIter.hasNext()) {
        QString strPlugin = dirIter.next();
        try {
            QSharedPointer<QTKPlugin> plugin = pContext->installPlugin(QUrl::fromLocalFile(strPlugin));
            plugin->start(QTKPlugin::StartOption_StartTransient);
            qDebug() << "Plugin start ...";
        } catch (const QTKPluginException &e) {
            qCritical() << e.printStackTrace();
            return -1;
        }
    }

    QTKEventAdminBus *pService = nullptr;
    try {
        QTKServiceReference serviceRef = pContext->getServiceReference<QTKEventAdminBus>();
        if (serviceRef) {
            pService = qobject_cast<QTKEventAdminBus*>(pContext->getService(serviceRef));
            if (!pService) {
                qCritical() << "Get plugin service failed!";
                return -1;
            }
        }
    } catch (const QTKPluginException &e) {
        qCritical() << e.printStackTrace();
        return -1;
    }

    qDebug() << "Get plugin service success...";
    MainWindow mainWindow(pService);
    mainWindow.show();

    return app.exec();
}
