#ifndef TESTAPPENDER_H
#define TESTAPPENDER_H

#include <qextLogAppenderSkeleton.h>

#include <QStringList>

class  TestAppender : public QExtLogAppenderSkeleton
{
    Q_OBJECT
public:
    explicit TestAppender(QObject *parent = QEXT_NULLPTR);
    TestAppender(const TestAppender &) = delete;
    TestAppender &operator=(const TestAppender &) = delete;

    QStringList list() const;
    QStringList clearList();
    virtual bool requiresLayout() const QEXT_OVERRIDE;

protected:
    virtual void append(const QExtLoggingEvent &event) QEXT_OVERRIDE;

private:
    QStringList mMessages;
};

#endif // TESTAPPENDER_H
