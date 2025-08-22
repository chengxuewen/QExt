#include <qextSingleton.h>

#include <QtTest>
#include <QtEndian>
#include <QByteArray>
#include <QDebug>
#include <QThread>
#include <QSemaphore>
#include <QThreadPool>

class QExtSingletonTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void qobjectBase();
};

class Object : public QObject, public QExtSingleton<Object>
{
    QEXT_DECLARE_SINGLETON(Object)
public:
    Object() {}
};

class NonObject : public QExtSingleton<NonObject>
{
    QEXT_DECLARE_SINGLETON(NonObject)
public:
    NonObject() {}
    ~NonObject() {}
};

void QExtSingletonTest::qobjectBase()
{
    QPointer<Object> obj = Object::instance();
    obj->destroyLater();
    NonObject *nonobj = NonObject::instance();
    nonobj->destroyLater();
}

QTEST_APPLESS_MAIN(QExtSingletonTest)

#include <tst_qextSingleton.moc>
