#include "TestThread.h"

#include <QTimer>

TestThread::TestThread(bool buggy, uint seed)
    : mBuggy(buggy)
{
    // qsrand(seed);
}

TestThread::~TestThread()
{
}

void TestThread::crash()
{
    reinterpret_cast<QString*>(1)->toInt();
    throw 1;
}

void TestThread::run()
{
    if(mBuggy)
    {
        QTimer::singleShot(rand() % 2000 + 100, this, SLOT(crash()));
    }
    else
    {
        QTimer::singleShot(rand() % 2000 + 100, this, SLOT(quit()));
    }
    exec();
}
