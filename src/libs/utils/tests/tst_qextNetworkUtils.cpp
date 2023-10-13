#include <QtTest>
#include <qextNetworkUtils.h>

#include <QtEndian>
#include <QByteArray>
#include <QDebug>

class QExtNetworkUtilsTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void qint16TransTest();
    void quint16TransTest();
    void qint32TransTest();
    void quint32TransTest();
    void qint64TransTest();
    void quint64TransTest();
};

void QExtNetworkUtilsTest::qint16TransTest()
{
    qint16 value1 = 0x12;
    qint16 value2 = -value1;
    QByteArray netValue1ByteArray = QExtNetworkUtils::qint16HostToNet(value1);
    QByteArray netValue2ByteArray = QExtNetworkUtils::qint16HostToNet(value2);
    QVERIFY("0012" == netValue1ByteArray.toHex());
    QVERIFY("ffee" == netValue2ByteArray.toHex());

    const int size = sizeof(qint16);
    char netValue1Ch1[size];
    memset(netValue1Ch1, 0, size);
    QExtNetworkUtils::qint16HostToNet(value1, netValue1Ch1);
    char netValue1Ch2[size];
    memset(netValue1Ch2, 0, size);
    QExtNetworkUtils::qint16HostToNet(value2, netValue1Ch2);
    QVERIFY("0012" == QByteArray(netValue1Ch1, size).toHex());
    QVERIFY("ffee" == QByteArray(netValue1Ch2, size).toHex());

    qint16 netValue1 = QExtNetworkUtils::qint16NetToHost(netValue1ByteArray.data());
    qint16 netValue2 = QExtNetworkUtils::qint16NetToHost(netValue2ByteArray.data());
    QVERIFY(value1 == netValue1);
    QVERIFY(value2 == netValue2);
}

void QExtNetworkUtilsTest::quint16TransTest()
{
    quint16 value1 = 0x0012;
    quint16 value2 = 0x1122;
    QByteArray netValue1ByteArray = QExtNetworkUtils::quint16HostToNet(value1);
    QByteArray netValue2ByteArray = QExtNetworkUtils::quint16HostToNet(value2);
    QVERIFY("0012" == netValue1ByteArray.toHex());
    QVERIFY("1122" == netValue2ByteArray.toHex());

    const int size = sizeof(quint16);
    char netValue1Ch1[size];
    memset(netValue1Ch1, 0, size);
    QExtNetworkUtils::quint16HostToNet(value1, netValue1Ch1);
    char netValue1Ch2[size];
    memset(netValue1Ch2, 0, size);
    QExtNetworkUtils::quint16HostToNet(value2, netValue1Ch2);
    QVERIFY("0012" == QByteArray(netValue1Ch1, size).toHex());
    QVERIFY("1122" == QByteArray(netValue1Ch2, size).toHex());

    quint16 netValue1 = QExtNetworkUtils::quint16NetToHost(netValue1ByteArray.data());
    quint16 netValue2 = QExtNetworkUtils::quint16NetToHost(netValue2ByteArray.data());
    QVERIFY(value1 == netValue1);
    QVERIFY(value2 == netValue2);
}

void QExtNetworkUtilsTest::qint32TransTest()
{
    qint32 value1 = 0x00112233;
    qint32 value2 = 0x11223344;
    qint32 value3 = -value1;
    QByteArray netValue1ByteArray = QExtNetworkUtils::qint32HostToNet(value1);
    QByteArray netValue2ByteArray = QExtNetworkUtils::qint32HostToNet(value2);
    QByteArray netValue3ByteArray = QExtNetworkUtils::qint32HostToNet(value3);

    QVERIFY("00112233" == netValue1ByteArray.toHex());
    QVERIFY("11223344" == netValue2ByteArray.toHex());
    QVERIFY("ffeeddcd" == netValue3ByteArray.toHex());

    int size = sizeof(qint32);
    char netValue1Ch1[sizeof(qint32)];
    memset(netValue1Ch1, 0, size);
    QExtNetworkUtils::qint32HostToNet(value1, netValue1Ch1);
    char netValue1Ch2[sizeof(qint32)];
    memset(netValue1Ch2, 0, size);
    QExtNetworkUtils::qint32HostToNet(value2, netValue1Ch2);
    char netValue1Ch3[sizeof(qint32)];
    memset(netValue1Ch3, 0, size);
    QExtNetworkUtils::qint32HostToNet(value3, netValue1Ch3);
    QVERIFY("00112233" == QByteArray(netValue1Ch1, size).toHex());
    QVERIFY("11223344" == QByteArray(netValue1Ch2, size).toHex());
    QVERIFY("ffeeddcd" == QByteArray(netValue1Ch3, size).toHex());

    qint32 netValue1 = QExtNetworkUtils::qint32NetToHost(netValue1ByteArray.data());
    qint32 netValue2 = QExtNetworkUtils::qint32NetToHost(netValue2ByteArray.data());
    qint32 netValue3 = QExtNetworkUtils::qint32NetToHost(netValue3ByteArray.data());
    QVERIFY(value1 == netValue1);
    QVERIFY(value2 == netValue2);
    QVERIFY(value3 == netValue3);
}

void QExtNetworkUtilsTest::quint32TransTest()
{
    quint32 value1 = 0x00112233;
    quint32 value2 = 0x11223344;
    QByteArray netValue1ByteArray = QExtNetworkUtils::quint32HostToNet(value1);
    QByteArray netValue2ByteArray = QExtNetworkUtils::quint32HostToNet(value2);
    QVERIFY("00112233" == netValue1ByteArray.toHex());
    QVERIFY("11223344" == netValue2ByteArray.toHex());

    int size = sizeof(quint32);
    char netValue1Ch1[sizeof(quint32)];
    memset(netValue1Ch1, 0, size);
    QExtNetworkUtils::quint32HostToNet(value1, netValue1Ch1);
    char netValue1Ch2[sizeof(quint32)];
    memset(netValue1Ch2, 0, size);
    QExtNetworkUtils::quint32HostToNet(value2, netValue1Ch2);
    QVERIFY("00112233" == QByteArray(netValue1Ch1, size).toHex());
    QVERIFY("11223344" == QByteArray(netValue1Ch2, size).toHex());

    quint32 netValue1 = QExtNetworkUtils::quint32NetToHost(netValue1ByteArray.data());
    quint32 netValue2 = QExtNetworkUtils::quint32NetToHost(netValue2ByteArray.data());
    QVERIFY(value1 == netValue1);
    QVERIFY(value2 == netValue2);
}

void QExtNetworkUtilsTest::qint64TransTest()
{
    qint64 value1 = 0x0011223344556677;
    qint64 value2 = 0x1122334455667788;
    qint64 value3 = -value1;
    QByteArray netValue1ByteArray = QExtNetworkUtils::qint64HostToNet(value1);
    QByteArray netValue2ByteArray = QExtNetworkUtils::qint64HostToNet(value2);
    QByteArray netValue3ByteArray = QExtNetworkUtils::qint64HostToNet(value3);
    QVERIFY("0011223344556677" == netValue1ByteArray.toHex());
    QVERIFY("1122334455667788" == netValue2ByteArray.toHex());
    QVERIFY("ffeeddccbbaa9989" == netValue3ByteArray.toHex());

    int size = sizeof(qint64);
    char netValue1Ch1[sizeof(qint64)];
    memset(netValue1Ch1, 0, size);
    QExtNetworkUtils::qint64HostToNet(value1, netValue1Ch1);
    char netValue1Ch2[sizeof(qint64)];
    memset(netValue1Ch2, 0, size);
    QExtNetworkUtils::qint64HostToNet(value2, netValue1Ch2);
    char netValue1Ch3[sizeof(qint64)];
    memset(netValue1Ch3, 0, size);
    QExtNetworkUtils::qint64HostToNet(value3, netValue1Ch3);
    QVERIFY("0011223344556677" == QByteArray(netValue1Ch1, size).toHex());
    QVERIFY("1122334455667788" == QByteArray(netValue1Ch2, size).toHex());
    QVERIFY("ffeeddccbbaa9989" == QByteArray(netValue1Ch3, size).toHex());

    qint64 netValue1 = QExtNetworkUtils::quint64NetToHost(netValue1ByteArray.data());
    qint64 netValue2 = QExtNetworkUtils::quint64NetToHost(netValue2ByteArray.data());
    qint64 netValue3 = QExtNetworkUtils::quint64NetToHost(netValue3ByteArray.data());
    QVERIFY(value1 == netValue1);
    QVERIFY(value2 == netValue2);
    QVERIFY(value3 == netValue3);
}

void QExtNetworkUtilsTest::quint64TransTest()
{
    quint64 value1 = 0x0011223344556677;
    quint64 value2 = 0x1122334455667788;
    QByteArray netValue1ByteArray = QExtNetworkUtils::quint64HostToNet(value1);
    QByteArray netValue2ByteArray = QExtNetworkUtils::quint64HostToNet(value2);
    QVERIFY("0011223344556677" == netValue1ByteArray.toHex());
    QVERIFY("1122334455667788" == netValue2ByteArray.toHex());

    const int size = sizeof(quint64);
    char netValue1Ch1[size];
    memset(netValue1Ch1, 0, size);
    QExtNetworkUtils::quint64HostToNet(value1, netValue1Ch1);
    char netValue1Ch2[size];
    memset(netValue1Ch2, 0, size);
    QExtNetworkUtils::quint64HostToNet(value2, netValue1Ch2);
    QVERIFY("0011223344556677" == QByteArray(netValue1Ch1, size).toHex());
    QVERIFY("1122334455667788" == QByteArray(netValue1Ch2, size).toHex());

    quint64 netValue1 = QExtNetworkUtils::quint64NetToHost(netValue1ByteArray.data());
    quint64 netValue2 = QExtNetworkUtils::quint64NetToHost(netValue2ByteArray.data());
    QVERIFY(value1 == netValue1);
    QVERIFY(value2 == netValue2);
}

QTEST_APPLESS_MAIN(QExtNetworkUtilsTest)

#include <tst_qextNetworkUtils.moc>
