#include <QCoreApplication>
#include <QProcess>
#include <QObject>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QDebug>

#include <qextCTestRunner.h>
#include <qextCTestRunnerConfig.h>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
#include <QLoggingCategory>
#endif

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
#endif

    QCoreApplication app(argc, argv);

    QEXTCTestRunner ctestRunner(QEXT_PROJECT_BINARY_DIR);
    QObject::connect(&ctestRunner, SIGNAL(testFinished()), QCoreApplication::instance(), SLOT(quit()));
    ctestRunner.runTest();

    return app.exec();
}
