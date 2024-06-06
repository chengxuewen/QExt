#include <QApplication>
#include <QDebug>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    #include <QLoggingCategory>
#endif

#include <MainWindow.h>

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
#endif

    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}

