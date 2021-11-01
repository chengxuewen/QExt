#include <QApplication>
#include <QMainWindow>
#include <QSharedPointer>
#include <QDirIterator>
#include <QStringList>
#include <QTimer>
#include <QDebug>

#include <qtkinfo.h>
#include <QTKPluginFramework/QTKPluginFrameworkFactory>
#include <QTKPluginFramework/QTKPluginFramework>
#include <QTKPluginFramework/QTKPluginException>
#include <QTKPluginFramework/QTKPluginContext>
#include <QTKHello/QTKHelloService>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

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
    listNameFilters.append("*QTKHello.dll");
    listNameFilters.append("*QTKHello.so");
    listNameFilters.append("*QTKHello.dylib");
    listNameFilters.append("*QTKHellod.dll");
    listNameFilters.append("*QTKHellod.so");
    listNameFilters.append("*QTKHellod.dylib");
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

    try {
        QTKServiceReference serviceRef = pContext->getServiceReference<QTKHelloService>();
        if (serviceRef) {
            QTKHelloService *pService = qobject_cast<QTKHelloService *>(pContext->getService(serviceRef));
            if (nullptr != pService) {
                pService->sayHello();
            }
        }
    } catch (const QTKPluginException &e) {
        qCritical() << e.printStackTrace();
        return -1;
    }

    QTimer::singleShot(0, &app, SLOT(quit()));
    return app.exec();
}
