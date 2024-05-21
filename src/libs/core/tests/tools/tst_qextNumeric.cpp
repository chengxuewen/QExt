#include <qextNumeric.h>

#include <QtTest>
#include <QtEndian>
#include <QByteArray>
#include <QDebug>

class QExtNumericTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void constructor();
};


void QExtNumericTest::constructor()
{
    const double dbl = 111111.111111;
    QCOMPARE(QExtNumeric::reducePrecision(dbl, -6), 000000.000000);
    QCOMPARE(QExtNumeric::reducePrecision(dbl, -5), 100000.000000);
    QCOMPARE(QExtNumeric::reducePrecision(dbl, -4), 110000.000000);
    QCOMPARE(QExtNumeric::reducePrecision(dbl, -3), 111000.000000);
    QCOMPARE(QExtNumeric::reducePrecision(dbl, -2), 111100.000000);
    QCOMPARE(QExtNumeric::reducePrecision(dbl, -1), 111110.000000);
    QCOMPARE(QExtNumeric::reducePrecision(dbl, 0), 111111.000000);
    QCOMPARE(QExtNumeric::reducePrecision(dbl, 1), 111111.100000);
    QCOMPARE(QExtNumeric::reducePrecision(dbl, 2), 111111.110000);
    QCOMPARE(QExtNumeric::reducePrecision(dbl, 3), 111111.111000);
    QCOMPARE(QExtNumeric::reducePrecision(dbl, 4), 111111.111100);
    QCOMPARE(QExtNumeric::reducePrecision(dbl, 5), 111111.111110);
    QCOMPARE(QExtNumeric::reducePrecision(dbl, 6), 111111.111111);
}

QTEST_APPLESS_MAIN(QExtNumericTest)

#include <tst_qextNumeric.moc>
