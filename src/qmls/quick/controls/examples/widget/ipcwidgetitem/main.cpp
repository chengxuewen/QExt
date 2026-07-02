#include <QApplication>
#include <QQuickItem>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <qextQuickControlsGlobal.h>
#include <qextQuickIpcWidgetItem.h>
#include <qextCoreConfig.h>
#include <qextQmlConfig.h>

#ifndef QEXT_BUILD_SHARED
#   include <qextQuickLoader.h>
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
#ifndef QEXT_BUILD_SHARED
    QExtQuickLoader::load(&engine);
#else
    qDebug() << "addImportPath:" << QML_MODULES_DIR;
    engine.addImportPath(QML_MODULES_DIR);
#endif

    // 将 examples 目录加入 PATH，使子进程可通过裸名称找到
    QString examplesDir = QCoreApplication::applicationDirPath();
    QByteArray path = qgetenv("PATH");
    path = examplesDir.toUtf8() + ":" + path;
    qputenv("PATH", path);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }


    auto rootObject = engine.rootObjects().first();
    if (!rootObject) return -1;

    // Set up default EmbedIpcHandler for both IPC items
    // Process path and args come from QML processPath/processArgs properties
    auto *ipcItemA = rootObject->findChild<QExtQuickIpcWidgetItem *>("ipcItemA");
    if (ipcItemA)
    {
        ipcItemA->setProcessInterface(QExtQuickIpcWidgetItem::createDefaultHandler());
        ipcItemA->start();
        qDebug() << "[Main] Default handler set on ipcItemA";
    }
    else
    {
        qWarning() << "[Main] ipcItemA not found!";
    }

    auto *ipcItemB = rootObject->findChild<QExtQuickIpcWidgetItem *>("ipcItemB");
    if (ipcItemB)
    {
        ipcItemB->setProcessInterface(QExtQuickIpcWidgetItem::createDefaultHandler());
        ipcItemB->start();
        qDebug() << "[Main] Default handler set on ipcItemB";
    }
    else
    {
        qWarning() << "[Main] ipcItemB not found!";
    }
    return app.exec();
}

