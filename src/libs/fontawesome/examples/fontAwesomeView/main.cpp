#include <QApplication>
#include <QTextCodec>
#include <QDebug>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    #include <QLoggingCategory>
#endif

#include <MainWindow.h>


int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
#endif

    QApplication app(argc, argv);

    LFAMMainWindow w;
    w.show();

    return app.exec();
}

