#include <QApplication>
#include <QTimer>
#include <QDateTime>

#include <TestThread.h>

#include <qextBreakpadHandler.h>

int main(int argc, char* argv[])
{
    // QCoreApplication app(argc, argv);
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("AppName");
    QCoreApplication::setApplicationVersion("1.0");
    QCoreApplication::setOrganizationName("OrgName");
    QCoreApplication::setOrganizationDomain("name.org");

    qextBreakpadHandler->setDumpPath(QApplication::applicationDirPath() + "/crashes");

    TestThread t1(false, rand());
    TestThread t2(true, rand());

    t1.start();
    t2.start();

    QTimer::singleShot(3000, qApp, SLOT(quit()));
    return app.exec();
}
