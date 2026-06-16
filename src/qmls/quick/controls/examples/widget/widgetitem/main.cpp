#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlEngine>

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>


#include <qextCoreConfig.h>
#include <qextQmlConfig.h>

#ifndef QEXT_BUILD_SHARED
#   include <qextQuickLoader.h>
#endif

class WidgetItemAccessor : public QObject
{
    Q_OBJECT
public:
    static void setWidget(QObject *item, QWidget *widget)
    {
        QMetaObject::invokeMethod(item, "setWidget",
            Qt::DirectConnection,
            Q_ARG(QWidget*, widget));
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto *container = new QWidget;
    container->setObjectName("embeddedWidget");
    container->setStyleSheet(
        "QWidget#embeddedWidget {"
        "  background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "    stop:0 #4a90d9, stop:1 #1a5276);"
        "  border-radius: 6px;"
        "}");

    auto *layout = new QVBoxLayout(container);
    layout->setAlignment(Qt::AlignCenter);

    auto *label = new QLabel("This is a QWidget\nembedded in QML!");
    label->setStyleSheet("color: white; font-size: 18px;");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    QQmlApplicationEngine engine;
#ifndef QEXT_BUILD_SHARED
    QExtQuickLoader::load(&engine);
#else
    qDebug() << "addImportPath:" << QML_MODULES_DIR;
    engine.addImportPath(QML_MODULES_DIR);
#endif
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    auto *item = engine.rootObjects().first()->findChild<QObject*>("widgetItem");
    if (item) 
    {
        WidgetItemAccessor::setWidget(item, container);
        qDebug() << "Widget embedded successfully";
    }
    else 
    {
        qWarning() << "Failed to find widgetItem!";
    }

    return app.exec();
}

#include "main.moc"