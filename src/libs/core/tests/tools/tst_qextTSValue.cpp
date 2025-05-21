#include <qextTSValue.h>

#include <QtTest>
#include <QtEndian>
#include <QByteArray>
#include <QDebug>

class QExtTSValueTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void constructor();
};


void QExtTSValueTest::constructor()
{
    QExtTSValue<QAtomicInt> tsValue(0);
    QCOMPARE(tsValue->loadAcquire(), 0);
    QCOMPARE(tsValue.get(), 0);
}

QTEST_APPLESS_MAIN(QExtTSValueTest)

#include <tst_qextTSValue.moc>
