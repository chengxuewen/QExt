#include "smainwindow.h"

#include <QApplication>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
#include <QLoggingCategory>
#endif

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
#endif

    QApplication app(argc, argv);

    SMainWindow window;
    window.show();

    return app.exec();
}
