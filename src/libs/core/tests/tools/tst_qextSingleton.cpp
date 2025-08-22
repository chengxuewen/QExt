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

void QExtSingletonTest::qobjectBase()
{
    QPointer<Object> obj = Object::instance();
    obj->destroyLater();
}

QTEST_APPLESS_MAIN(QExtSingletonTest)

#include <tst_qextSingleton.moc>
