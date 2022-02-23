#include <QtGui>
#include <QtWidgets>
#include <QtQml>

#ifndef QEXT_BUILD_SHARED_LIBS
#include <qextQmlFramelessHelperLoader.h>
#else
#include <qextQmlFramelessHelperExampleConfig.h>
#endif


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
#endif

    QApplication a(argc, argv);

    QQmlApplicationEngine engine;

#ifndef QEXT_BUILD_SHARED_LIBS
    QEXTQmlFramelessHelperLoader::load(&engine);
#else
    engine.addImportPath(QEXT_OUTPUT_QML_DIR);
#endif

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return a.exec();
}
