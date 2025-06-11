#include <qextBreakpadHandler.h>

#include <QFile>
#include <QStringList>
#include <QCoreApplication>

#include <cstdio>

void buggyFunc()
{
    std::printf("start call buggyFunc\n");
    delete reinterpret_cast<QString*>(0xFEE1DEAD);
}

void f3(int);

void f1(int i)
{
    if(i)
    {
        f3(i - 1);
    }
    else
    {
        buggyFunc();
    }
}

void f2(int i)
{
    f1(i > 0 ? i - 1 : i);
}

void f3(int i)
{
    f2(i > 0 ? i - 1 : i);
}

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    const QStringList args = app.arguments();
    const int method  = args.value(1).toInt();
    if(args.count() != 2 || method < 1 || method > 2 )
    {
        std::printf("Usage: %s <crash method>\n", qPrintable(app.applicationFilePath()));
        std::printf("Where <crash method> is '1' or '2'\n");
        return 0;
    }

    app.setApplicationName("test");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("no-such-org");
    app.setOrganizationDomain("no-such.org");
    qextBreakpadHandler->setDumpPath("crashes");

    if(method == 1)
    {
        // first method - simple crash
        f3(0);
    }
    else
    {
        // second method - more crazy call stack
        f3(10);
    }

    return app.exec();
}
