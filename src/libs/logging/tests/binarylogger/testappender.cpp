#include "testappender.h"
#include <QMutexLocker>

#include <qextLogLayout.h>

TestAppender::TestAppender(QObject *parent)
    : QExtLogAppenderSkeleton(parent)
{
}

QStringList TestAppender::list() const
{
    QMutexLocker locker(&mObjectGuard);
    return mMessages;
}

QStringList TestAppender::clearList()
{
    QMutexLocker locker(&mObjectGuard);
    QStringList copy(mMessages);
    mMessages.clear();
    return copy;
}

bool TestAppender::requiresLayout() const
{
    return true;
}

void TestAppender::append(const QExtLoggingEvent &event)
{
    Q_ASSERT_X(layout(), "TestAppender::append()", "QExtLogLayout must not be null");
    mMessages << layout()->format(event);
}

#include "moc_testappender.cpp"
