#include <QtTest>
#include <QApplication>
#include <QTimer>

// add necessary includes here
#include <qtkinfo.h>
#include <QTKPluginFramework/QTKPluginFrameworkFactory>
#include <QTKPluginFramework/QTKPluginFramework>
#include <QTKPluginFramework/QTKPluginException>
#include <QTKPluginFramework/QTKPluginContext>
#include <QTKHello/QTKHelloService>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKPluginFrameworkTest : public QObject
{
    Q_OBJECT

public:
    QTKPluginFrameworkTest();
    ~QTKPluginFrameworkTest();

private slots:
    void test_qtkHelloWorldPlugin();

};

QTKPluginFrameworkTest::QTKPluginFrameworkTest()
{

}

QTKPluginFrameworkTest::~QTKPluginFrameworkTest()
{

}

void QTKPluginFrameworkTest::test_qtkHelloWorldPlugin()
{
    int argc = 0;
    QApplication app(argc, nullptr);
    QString strHello;
    QTKPluginFrameworkFactory pfwFactory;
    QSharedPointer<QTKPluginFramework> pPluginFrameWork = pfwFactory.getFramework();
    try {
        pPluginFrameWork->init();
        pPluginFrameWork->start();
        qDebug() << "QTK plugin framework start...";
    } catch (const QTKPluginException &e) {
        qFatal("Failed to initialize the plugin framework: %s", e.what());
    }

    QTKPluginContext *pContext = pPluginFrameWork->getPluginContext();
    QString strPath = QTK_PLUGIN_DIR;

    QStringList listNameFilters;
    listNameFilters.append("*QTKHello.dll");
    listNameFilters.append("*QTKHello.so");
    listNameFilters.append("*QTKHello.dylib");
    listNameFilters.append("*QTKHellod.dll");
    listNameFilters.append("*QTKHellod.so");
    listNameFilters.append("*QTKHellod.dylib");
    QDirIterator itPlugin(strPath, listNameFilters, QDir::Files);
    while (itPlugin.hasNext()) {
        QString strPlugin = itPlugin.next();
        try {
            QSharedPointer<QTKPlugin> plugin = pContext->installPlugin(QUrl::fromLocalFile(strPlugin));
            plugin->start(QTKPlugin::StartOption_StartTransient);
            qDebug() << "Plugin start ...";
        } catch (const QTKPluginException &e) {
            qWarning() << e.printStackTrace();
            qFatal("Failed to install plugin!");
        }
    }

    try {
        QTKServiceReference reference = pContext->getServiceReference<QTKHelloService>();
        if (reference) {
            QTKHelloService *pService = qobject_cast<QTKHelloService *>(pContext->getService(reference));
            if (nullptr != pService) {
                strHello = pService->sayHello();
            } else {
                qFatal("Failed to get service pointer!");
            }
        } else {
            qFatal("Failed to get service reference!");
        }
    } catch (const QTKPluginException &e) {
        qCritical() << e.printStackTrace();
        qFatal("Failed to get service reference!");
    }

    QCOMPARE(strHello, QTK_HELLO_SERVICE_HELLO_STRING);

    QTimer::singleShot(0, &app, SLOT(quit()));
    app.exec();
}

QTEST_APPLESS_MAIN(QTKPluginFrameworkTest)

#include "tst_qtkpluginframeworktest.moc"
