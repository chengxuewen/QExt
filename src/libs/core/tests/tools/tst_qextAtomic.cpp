#include <qextAtomic.h>

#include <QtTest>
#include <QtEndian>
#include <QByteArray>
#include <QDebug>

class QExtAtomicTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void doubleTest();
};




void QExtAtomicTest::doubleTest()
{

}

QTEST_APPLESS_MAIN(QExtAtomicTest)

#include <tst_qextAtomic.moc>
