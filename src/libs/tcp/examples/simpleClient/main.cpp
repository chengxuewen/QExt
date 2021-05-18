#include "cmainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QByteArray>
#include <QtEndian>


#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
#include <QLoggingCategory>
#endif

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
#endif

    QApplication app(argc, argv);

    CMainWindow window;
    window.show();

    return app.exec();
}
