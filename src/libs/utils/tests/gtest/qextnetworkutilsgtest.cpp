#include <gtest/gtest.h>
#include <qextnetworkutils.h>

#include <QtEndian>
#include <QByteArray>
#include <QDebug>

TEST(QEXTNetworkUtilsTest, qint16HostToNet_qint16NetToHost)
{
    qint16 value1 = 0x12;
    qint16 value2 = -value1;
    QByteArray netValue1ByteArray = QEXTNetworkUtils::qint16HostToNet(value1);
    QByteArray netValue2ByteArray = QEXTNetworkUtils::qint16HostToNet(value2);
    ASSERT_TRUE("0012" == netValue1ByteArray.toHex()) << netValue1ByteArray.toHex().data();
    ASSERT_TRUE("ffee" == netValue2ByteArray.toHex()) << netValue2ByteArray.toHex().data();

    int size = sizeof(qint16);
    char netValue1Ch1[size];
    memset(netValue1Ch1, 0, size);
    QEXTNetworkUtils::qint16HostToNet(value1, netValue1Ch1);
    char netValue1Ch2[size];
    memset(netValue1Ch2, 0, size);
    QEXTNetworkUtils::qint16HostToNet(value2, netValue1Ch2);
    ASSERT_TRUE("0012" == QByteArray(netValue1Ch1, size).toHex()) << QByteArray(netValue1Ch1, size).toHex().data();
    ASSERT_TRUE("ffee" == QByteArray(netValue1Ch2, size).toHex()) << QByteArray(netValue1Ch2, size).toHex().data();

    qint16 netValue1 = QEXTNetworkUtils::qint16NetToHost(netValue1ByteArray.data());
    qint16 netValue2 = QEXTNetworkUtils::qint16NetToHost(netValue2ByteArray.data());
    ASSERT_TRUE(value1 == netValue1) << netValue1;
    ASSERT_TRUE(value2 == netValue2) << netValue2;
}

TEST(QEXTNetworkUtilsTest, quint16HostToNet_quint16NetToHost)
{
    quint16 value1 = 0x0012;
    quint16 value2 = 0x1122;
    QByteArray netValue1ByteArray = QEXTNetworkUtils::quint16HostToNet(value1);
    QByteArray netValue2ByteArray = QEXTNetworkUtils::quint16HostToNet(value2);
    ASSERT_TRUE("0012" == netValue1ByteArray.toHex()) << netValue1ByteArray.toHex().data();
    ASSERT_TRUE("1122" == netValue2ByteArray.toHex()) << netValue2ByteArray.toHex().data();

    int size = sizeof(quint16);
    char netValue1Ch1[size];
    memset(netValue1Ch1, 0, size);
    QEXTNetworkUtils::quint16HostToNet(value1, netValue1Ch1);
    char netValue1Ch2[size];
    memset(netValue1Ch2, 0, size);
    QEXTNetworkUtils::quint16HostToNet(value2, netValue1Ch2);
    ASSERT_TRUE("0012" == QByteArray(netValue1Ch1, size).toHex()) << QByteArray(netValue1Ch1, size).toHex().data();
    ASSERT_TRUE("1122" == QByteArray(netValue1Ch2, size).toHex()) << QByteArray(netValue1Ch2, size).toHex().data();

    quint16 netValue1 = QEXTNetworkUtils::quint16NetToHost(netValue1ByteArray.data());
    quint16 netValue2 = QEXTNetworkUtils::quint16NetToHost(netValue2ByteArray.data());
    ASSERT_TRUE(value1 == netValue1) << netValue1;
    ASSERT_TRUE(value2 == netValue2) << netValue2;
}

TEST(QEXTNetworkUtilsTest, qint32HostToNet_qint32NetToHost)
{
    qint32 value1 = 0x00112233;
    qint32 value2 = 0x11223344;
    qint32 value3 = -value1;
    QByteArray netValue1ByteArray = QEXTNetworkUtils::qint32HostToNet(value1);
    QByteArray netValue2ByteArray = QEXTNetworkUtils::qint32HostToNet(value2);
    QByteArray netValue3ByteArray = QEXTNetworkUtils::qint32HostToNet(value3);

    ASSERT_TRUE("00112233" == netValue1ByteArray.toHex()) << netValue1ByteArray.toHex().data();
    ASSERT_TRUE("11223344" == netValue2ByteArray.toHex()) << netValue2ByteArray.toHex().data();
    ASSERT_TRUE("ffeeddcd" == netValue3ByteArray.toHex()) << netValue3ByteArray.toHex().data();

    int size = sizeof(qint32);
    char netValue1Ch1[size];
    memset(netValue1Ch1, 0, size);
    QEXTNetworkUtils::qint32HostToNet(value1, netValue1Ch1);
    char netValue1Ch2[size];
    memset(netValue1Ch2, 0, size);
    QEXTNetworkUtils::qint32HostToNet(value2, netValue1Ch2);
    char netValue1Ch3[size];
    memset(netValue1Ch3, 0, size);
    QEXTNetworkUtils::qint32HostToNet(value3, netValue1Ch3);
    ASSERT_TRUE("00112233" == QByteArray(netValue1Ch1, size).toHex()) << QByteArray(netValue1Ch1, size).toHex().data();
    ASSERT_TRUE("11223344" == QByteArray(netValue1Ch2, size).toHex()) << QByteArray(netValue1Ch2, size).toHex().data();
    ASSERT_TRUE("ffeeddcd" == QByteArray(netValue1Ch3, size).toHex()) << QByteArray(netValue1Ch3, size).toHex().data();

    qint32 netValue1 = QEXTNetworkUtils::qint32NetToHost(netValue1ByteArray.data());
    qint32 netValue2 = QEXTNetworkUtils::qint32NetToHost(netValue2ByteArray.data());
    qint32 netValue3 = QEXTNetworkUtils::qint32NetToHost(netValue3ByteArray.data());
    ASSERT_TRUE(value1 == netValue1) << netValue1;
    ASSERT_TRUE(value2 == netValue2) << netValue2;
    ASSERT_TRUE(value3 == netValue3) << netValue3;
}

TEST(QEXTNetworkUtilsTest, quint32HostToNet_quint32NetToHost)
{
    quint32 value1 = 0x00112233;
    quint32 value2 = 0x11223344;
    QByteArray netValue1ByteArray = QEXTNetworkUtils::quint32HostToNet(value1);
    QByteArray netValue2ByteArray = QEXTNetworkUtils::quint32HostToNet(value2);
    ASSERT_TRUE("00112233" == netValue1ByteArray.toHex()) << netValue1ByteArray.toHex().data();
    ASSERT_TRUE("11223344" == netValue2ByteArray.toHex()) << netValue2ByteArray.toHex().data();

    int size = sizeof(quint32);
    char netValue1Ch1[size];
    memset(netValue1Ch1, 0, size);
    QEXTNetworkUtils::quint32HostToNet(value1, netValue1Ch1);
    char netValue1Ch2[size];
    memset(netValue1Ch2, 0, size);
    QEXTNetworkUtils::quint32HostToNet(value2, netValue1Ch2);
    ASSERT_TRUE("00112233" == QByteArray(netValue1Ch1, size).toHex()) << QByteArray(netValue1Ch1, size).toHex().data();
    ASSERT_TRUE("11223344" == QByteArray(netValue1Ch2, size).toHex()) << QByteArray(netValue1Ch2, size).toHex().data();

    quint32 netValue1 = QEXTNetworkUtils::quint32NetToHost(netValue1ByteArray.data());
    quint32 netValue2 = QEXTNetworkUtils::quint32NetToHost(netValue2ByteArray.data());
    ASSERT_TRUE(value1 == netValue1) << netValue1;
    ASSERT_TRUE(value2 == netValue2) << netValue2;
}

TEST(QEXTNetworkUtilsTest, qint64HostToNet_quint64NetToHost)
{
    qint64 value1 = 0x0011223344556677;
    qint64 value2 = 0x1122334455667788;
    qint64 value3 = -value1;
    QByteArray netValue1ByteArray = QEXTNetworkUtils::qint64HostToNet(value1);
    QByteArray netValue2ByteArray = QEXTNetworkUtils::qint64HostToNet(value2);
    QByteArray netValue3ByteArray = QEXTNetworkUtils::qint64HostToNet(value3);
    ASSERT_TRUE("0011223344556677" == netValue1ByteArray.toHex()) << netValue1ByteArray.toHex().data();
    ASSERT_TRUE("1122334455667788" == netValue2ByteArray.toHex()) << netValue2ByteArray.toHex().data();
    ASSERT_TRUE("ffeeddccbbaa9989" == netValue3ByteArray.toHex()) << netValue3ByteArray.toHex().data();

    int size = sizeof(qint64);
    char netValue1Ch1[size];
    memset(netValue1Ch1, 0, size);
    QEXTNetworkUtils::qint64HostToNet(value1, netValue1Ch1);
    char netValue1Ch2[size];
    memset(netValue1Ch2, 0, size);
    QEXTNetworkUtils::qint64HostToNet(value2, netValue1Ch2);
    char netValue1Ch3[size];
    memset(netValue1Ch3, 0, size);
    QEXTNetworkUtils::qint64HostToNet(value3, netValue1Ch3);
    ASSERT_TRUE("0011223344556677" == QByteArray(netValue1Ch1, size).toHex()) << QByteArray(netValue1Ch1, size).toHex().data();
    ASSERT_TRUE("1122334455667788" == QByteArray(netValue1Ch2, size).toHex()) << QByteArray(netValue1Ch2, size).toHex().data();
    ASSERT_TRUE("ffeeddccbbaa9989" == QByteArray(netValue1Ch3, size).toHex()) << QByteArray(netValue1Ch3, size).toHex().data();

    qint64 netValue1 = QEXTNetworkUtils::quint64NetToHost(netValue1ByteArray.data());
    qint64 netValue2 = QEXTNetworkUtils::quint64NetToHost(netValue2ByteArray.data());
    qint64 netValue3 = QEXTNetworkUtils::quint64NetToHost(netValue3ByteArray.data());
    ASSERT_TRUE(value1 == netValue1) << netValue1;
    ASSERT_TRUE(value2 == netValue2) << netValue2;
    ASSERT_TRUE(value3 == netValue3) << netValue3;
}

TEST(QEXTNetworkUtilsTest, quint64HostToNet_quint64NetToHost)
{
    quint64 value1 = 0x0011223344556677;
    quint64 value2 = 0x1122334455667788;
    QByteArray netValue1ByteArray = QEXTNetworkUtils::quint64HostToNet(value1);
    QByteArray netValue2ByteArray = QEXTNetworkUtils::quint64HostToNet(value2);
    ASSERT_TRUE("0011223344556677" == netValue1ByteArray.toHex()) << netValue1ByteArray.toHex().data();
    ASSERT_TRUE("1122334455667788" == netValue2ByteArray.toHex()) << netValue2ByteArray.toHex().data();

    int size = sizeof(quint64);
    char netValue1Ch1[size];
    memset(netValue1Ch1, 0, size);
    QEXTNetworkUtils::quint64HostToNet(value1, netValue1Ch1);
    char netValue1Ch2[size];
    memset(netValue1Ch2, 0, size);
    QEXTNetworkUtils::quint64HostToNet(value2, netValue1Ch2);
    ASSERT_TRUE("0011223344556677" == QByteArray(netValue1Ch1, size).toHex()) << QByteArray(netValue1Ch1, size).toHex().data();
    ASSERT_TRUE("1122334455667788" == QByteArray(netValue1Ch2, size).toHex()) << QByteArray(netValue1Ch2, size).toHex().data();

    quint64 netValue1 = QEXTNetworkUtils::quint64NetToHost(netValue1ByteArray.data());
    quint64 netValue2 = QEXTNetworkUtils::quint64NetToHost(netValue2ByteArray.data());
    ASSERT_TRUE(value1 == netValue1) << netValue1;
    ASSERT_TRUE(value2 == netValue2) << netValue2;
}
