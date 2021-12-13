#include <QCoreApplication>
#include <QProcess>
#include <QObject>
#include <QFileInfo>
#include <QFile>
#include <QDebug>

#include <qextTestRunner.h>
#include <qextAllTestRunnerConfig.h>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    #include <QLoggingCategory>
#endif

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
#endif

    QCoreApplication app(argc, argv);

    QEXTTestController testController(QEXT_TEST_OUTPUT_DIR, QEXTTestController::Output_Failure);
    QObject::connect(&testController, SIGNAL(allTestFinished()), QCoreApplication::instance(), SLOT(quit()));
    testController.runTest();

    return app.exec();
}
