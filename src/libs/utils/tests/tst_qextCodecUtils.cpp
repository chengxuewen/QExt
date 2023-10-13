#include <qextCodecUtils.h>

#include <QtTest>
#include <QtEndian>
#include <QByteArray>
#include <QDebug>

class QExtCodecUtilsTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void isHexCodeTest();
    void isHexCharTest();
    void isHexStringTest();

    void hexCharToHexCodeTest();
    void hexStringToHexByteArrayTest();

    void hexCodeToHexCharTest();
    void hexByteArrayToHexStringTest();
    void hexIntToHexStringTest();

    void hexByteArrayToIntTest();
};

void QExtCodecUtilsTest::isHexCodeTest()
{
    QVERIFY(!QExtCodecUtils::isHexCode(-1));
    QVERIFY(QExtCodecUtils::isHexCode(0));
    QVERIFY(QExtCodecUtils::isHexCode(1));
    QVERIFY(QExtCodecUtils::isHexCode(2));
    QVERIFY(QExtCodecUtils::isHexCode(3));
    QVERIFY(QExtCodecUtils::isHexCode(4));
    QVERIFY(QExtCodecUtils::isHexCode(5));
    QVERIFY(QExtCodecUtils::isHexCode(6));
    QVERIFY(QExtCodecUtils::isHexCode(7));
    QVERIFY(QExtCodecUtils::isHexCode(8));
    QVERIFY(QExtCodecUtils::isHexCode(9));
    QVERIFY(QExtCodecUtils::isHexCode(10));
    QVERIFY(QExtCodecUtils::isHexCode(11));
    QVERIFY(QExtCodecUtils::isHexCode(12));
    QVERIFY(QExtCodecUtils::isHexCode(13));
    QVERIFY(QExtCodecUtils::isHexCode(14));
    QVERIFY(QExtCodecUtils::isHexCode(15));
    QVERIFY(!QExtCodecUtils::isHexCode(16));
}

void QExtCodecUtilsTest::isHexCharTest()
{
    QVERIFY(QExtCodecUtils::isHexChar('0'));
    QVERIFY(QExtCodecUtils::isHexChar('1'));
    QVERIFY(QExtCodecUtils::isHexChar('2'));
    QVERIFY(QExtCodecUtils::isHexChar('3'));
    QVERIFY(QExtCodecUtils::isHexChar('4'));
    QVERIFY(QExtCodecUtils::isHexChar('5'));
    QVERIFY(QExtCodecUtils::isHexChar('6'));
    QVERIFY(QExtCodecUtils::isHexChar('7'));
    QVERIFY(QExtCodecUtils::isHexChar('8'));
    QVERIFY(QExtCodecUtils::isHexChar('9'));
    QVERIFY(QExtCodecUtils::isHexChar('a'));
    QVERIFY(QExtCodecUtils::isHexChar('b'));
    QVERIFY(QExtCodecUtils::isHexChar('c'));
    QVERIFY(QExtCodecUtils::isHexChar('d'));
    QVERIFY(QExtCodecUtils::isHexChar('e'));
    QVERIFY(QExtCodecUtils::isHexChar('f'));
    QVERIFY(QExtCodecUtils::isHexChar('A'));
    QVERIFY(QExtCodecUtils::isHexChar('B'));
    QVERIFY(QExtCodecUtils::isHexChar('C'));
    QVERIFY(QExtCodecUtils::isHexChar('D'));
    QVERIFY(QExtCodecUtils::isHexChar('E'));
    QVERIFY(QExtCodecUtils::isHexChar('F'));
    QVERIFY(!QExtCodecUtils::isHexChar('g'));
}

void QExtCodecUtilsTest::isHexStringTest()
{
    char str1[] = "08fE";
    QVERIFY(QExtCodecUtils::isHexString(str1, strlen(str1)));
    char str2[] = "0hfE";
    QVERIFY(!QExtCodecUtils::isHexString(str2, strlen(str2)));

    QString str3("0123456789AbcDef");
    QVERIFY(QExtCodecUtils::isHexString(str3));
    QString str4("0123456789AbcDefg");
    QVERIFY(!QExtCodecUtils::isHexString(str4));
}

void QExtCodecUtilsTest::hexCharToHexCodeTest()
{
    bool success = true;
    char ch = 0;
    ch = QExtCodecUtils::hexCharToHexCode('1', &success);
    QVERIFY(success && (1 == ch));
    ch = QExtCodecUtils::hexCharToHexCode('7', &success);
    QVERIFY(success && (7 == ch));
    ch = QExtCodecUtils::hexCharToHexCode('e', &success);
    QVERIFY(success && (14 == ch));
    ch = QExtCodecUtils::hexCharToHexCode('A', &success);
    QVERIFY(success && (10 == ch));
    ch = QExtCodecUtils::hexCharToHexCode('0', &success);
    QVERIFY(success && (0 == ch));
    QExtCodecUtils::hexCharToHexCode('g', &success);
    QVERIFY(!success);
}

void QExtCodecUtilsTest::hexStringToHexByteArrayTest()
{
    bool success = true;
    QByteArray hexByteArray;
    for (int i = 0; i < 8; ++i) {
        char ch1 = (char(i * 2) << 4) & 0xf0;
        char ch2 = (char(i * 2 + 1) & 0x0f);
        hexByteArray.append(char(ch1 | ch2));
    }

    char str1[] = "0123456789AbcDef";
    const QByteArray value1 = QExtCodecUtils::hexStringToHexByteArray(str1, strlen(str1), &success);
    QVERIFY(success && value1 == hexByteArray);

    char str2[] = "0123456789AbcDefGM";
    QExtCodecUtils::hexStringToHexByteArray(str2, strlen(str2), &success);
    QVERIFY(!success);

    char str3[] = "012";
    QExtCodecUtils::hexStringToHexByteArray(str3, strlen(str3), &success);
    QVERIFY(!success);

    const QByteArray value2 = QExtCodecUtils::hexStringToHexByteArray(QString(str1), &success);
    QVERIFY(success && value2 == hexByteArray);

    QExtCodecUtils::hexStringToHexByteArray(QString(str2), &success);
    QVERIFY(!success);

    QExtCodecUtils::hexStringToHexByteArray(QString(str3), &success);
    QVERIFY(!success);
}

void QExtCodecUtilsTest::hexCodeToHexCharTest()
{
    bool success = true;
    char ch = -1;
    ch = QExtCodecUtils::hexCodeToHexChar(0, &success);
    QVERIFY(success && '0' == ch);
    ch = QExtCodecUtils::hexCodeToHexChar(1, &success);
    QVERIFY(success && '1' == ch);
    ch = QExtCodecUtils::hexCodeToHexChar(9, &success);
    QVERIFY(success && '9' == ch);
    ch = QExtCodecUtils::hexCodeToHexChar(10, &success);
    QVERIFY(success && 'a' == ch);
    ch = QExtCodecUtils::hexCodeToHexChar(15, &success);
    QVERIFY(success && 'f' == ch);
    QExtCodecUtils::hexCodeToHexChar(16, &success);
    QVERIFY(!success);
    QExtCodecUtils::hexCodeToHexChar(-1, &success);
    QVERIFY(!success);
}

void QExtCodecUtilsTest::hexByteArrayToHexStringTest()
{
    QString hexString;
    for (int i = 0; i < 16; ++i) {
        hexString.append(QString::number(i, 16));
    }

    const unsigned char hexArray1[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    QString value1 = QExtCodecUtils::hexByteArrayToHexString((char *)hexArray1, sizeof(hexArray1));
    QVERIFY(value1 == hexString);
    value1 = QExtCodecUtils::hexByteArrayToHexString(QByteArray((char *)hexArray1, sizeof(hexArray1)));
    QVERIFY(value1 == hexString);
}

void QExtCodecUtilsTest::hexIntToHexStringTest()
{
    QVERIFY("00" == QExtCodecUtils::hexUInt8ToHexString(0));
    QVERIFY("01" == QExtCodecUtils::hexUInt8ToHexString(1));
    QVERIFY("02" == QExtCodecUtils::hexUInt8ToHexString(2));
    QVERIFY("03" == QExtCodecUtils::hexUInt8ToHexString(3));
    QVERIFY("04" == QExtCodecUtils::hexUInt8ToHexString(4));
    QVERIFY("05" == QExtCodecUtils::hexUInt8ToHexString(5));
    QVERIFY("06" == QExtCodecUtils::hexUInt8ToHexString(6));
    QVERIFY("07" == QExtCodecUtils::hexUInt8ToHexString(7));
    QVERIFY("08" == QExtCodecUtils::hexUInt8ToHexString(8));
    QVERIFY("09" == QExtCodecUtils::hexUInt8ToHexString(9));
    QVERIFY("0a" == QExtCodecUtils::hexUInt8ToHexString(10));
    QVERIFY("0b" == QExtCodecUtils::hexUInt8ToHexString(11));
    QVERIFY("0c" == QExtCodecUtils::hexUInt8ToHexString(12));
    QVERIFY("0d" == QExtCodecUtils::hexUInt8ToHexString(13));
    QVERIFY("0e" == QExtCodecUtils::hexUInt8ToHexString(14));
    QVERIFY("0f" == QExtCodecUtils::hexUInt8ToHexString(15));
    QVERIFY("ff" == QExtCodecUtils::hexUInt8ToHexString(255));

    QVERIFY("0000" == QExtCodecUtils::hexUInt16ToHexString(0));
    QVERIFY("0001" == QExtCodecUtils::hexUInt16ToHexString(1));
    QVERIFY("0002" == QExtCodecUtils::hexUInt16ToHexString(2));
    QVERIFY("0003" == QExtCodecUtils::hexUInt16ToHexString(3));
    QVERIFY("0004" == QExtCodecUtils::hexUInt16ToHexString(4));
    QVERIFY("0005" == QExtCodecUtils::hexUInt16ToHexString(5));
    QVERIFY("0006" == QExtCodecUtils::hexUInt16ToHexString(6));
    QVERIFY("0007" == QExtCodecUtils::hexUInt16ToHexString(7));
    QVERIFY("0008" == QExtCodecUtils::hexUInt16ToHexString(8));
    QVERIFY("0009" == QExtCodecUtils::hexUInt16ToHexString(9));
    QVERIFY("000a" == QExtCodecUtils::hexUInt16ToHexString(10));
    QVERIFY("000b" == QExtCodecUtils::hexUInt16ToHexString(11));
    QVERIFY("000c" == QExtCodecUtils::hexUInt16ToHexString(12));
    QVERIFY("000d" == QExtCodecUtils::hexUInt16ToHexString(13));
    QVERIFY("000e" == QExtCodecUtils::hexUInt16ToHexString(14));
    QVERIFY("000f" == QExtCodecUtils::hexUInt16ToHexString(15));
    QVERIFY("00ff" == QExtCodecUtils::hexUInt16ToHexString(255));
    QVERIFY("ffff" == QExtCodecUtils::hexUInt16ToHexString(65535));

    QVERIFY("00000000" == QExtCodecUtils::hexUInt32ToHexString(0));
    QVERIFY("00000001" == QExtCodecUtils::hexUInt32ToHexString(1));
    QVERIFY("00000002" == QExtCodecUtils::hexUInt32ToHexString(2));
    QVERIFY("00000003" == QExtCodecUtils::hexUInt32ToHexString(3));
    QVERIFY("00000004" == QExtCodecUtils::hexUInt32ToHexString(4));
    QVERIFY("00000005" == QExtCodecUtils::hexUInt32ToHexString(5));
    QVERIFY("00000006" == QExtCodecUtils::hexUInt32ToHexString(6));
    QVERIFY("00000007" == QExtCodecUtils::hexUInt32ToHexString(7));
    QVERIFY("00000008" == QExtCodecUtils::hexUInt32ToHexString(8));
    QVERIFY("00000009" == QExtCodecUtils::hexUInt32ToHexString(9));
    QVERIFY("0000000a" == QExtCodecUtils::hexUInt32ToHexString(10));
    QVERIFY("0000000b" == QExtCodecUtils::hexUInt32ToHexString(11));
    QVERIFY("0000000c" == QExtCodecUtils::hexUInt32ToHexString(12));
    QVERIFY("0000000d" == QExtCodecUtils::hexUInt32ToHexString(13));
    QVERIFY("0000000e" == QExtCodecUtils::hexUInt32ToHexString(14));
    QVERIFY("0000000f" == QExtCodecUtils::hexUInt32ToHexString(15));
    QVERIFY("000000ff" == QExtCodecUtils::hexUInt32ToHexString(255));
    QVERIFY("ffffffff" == QExtCodecUtils::hexUInt32ToHexString(4294967295));

    QVERIFY("0000000000000000" == QExtCodecUtils::hexUInt64ToHexString(0));
    QVERIFY("0000000000000001" == QExtCodecUtils::hexUInt64ToHexString(1));
    QVERIFY("0000000000000002" == QExtCodecUtils::hexUInt64ToHexString(2));
    QVERIFY("0000000000000003" == QExtCodecUtils::hexUInt64ToHexString(3));
    QVERIFY("0000000000000004" == QExtCodecUtils::hexUInt64ToHexString(4));
    QVERIFY("0000000000000005" == QExtCodecUtils::hexUInt64ToHexString(5));
    QVERIFY("0000000000000006" == QExtCodecUtils::hexUInt64ToHexString(6));
    QVERIFY("0000000000000007" == QExtCodecUtils::hexUInt64ToHexString(7));
    QVERIFY("0000000000000008" == QExtCodecUtils::hexUInt64ToHexString(8));
    QVERIFY("0000000000000009" == QExtCodecUtils::hexUInt64ToHexString(9));
    QVERIFY("000000000000000a" == QExtCodecUtils::hexUInt64ToHexString(10));
    QVERIFY("000000000000000b" == QExtCodecUtils::hexUInt64ToHexString(11));
    QVERIFY("000000000000000c" == QExtCodecUtils::hexUInt64ToHexString(12));
    QVERIFY("000000000000000d" == QExtCodecUtils::hexUInt64ToHexString(13));
    QVERIFY("000000000000000e" == QExtCodecUtils::hexUInt64ToHexString(14));
    QVERIFY("000000000000000f" == QExtCodecUtils::hexUInt64ToHexString(15));
    QVERIFY("00000000000000ff" == QExtCodecUtils::hexUInt64ToHexString(255));
    QVERIFY("0fffffffffffffff" == QExtCodecUtils::hexUInt64ToHexString(1152921504606846975));
}

void QExtCodecUtilsTest::hexByteArrayToIntTest()
{
    char hexArray1[] = {char(0x11)};
    QVERIFY(17 == QExtCodecUtils::hexByteArrayToUInt8(hexArray1, sizeof(hexArray1)));
    QVERIFY(17 == QExtCodecUtils::hexByteArrayToUInt8(QByteArray(hexArray1, sizeof(hexArray1))));

    char hexArray2[] = {char(0x11), char(0x11)};
    QVERIFY(4369 == QExtCodecUtils::hexByteArrayToUInt16(hexArray2, sizeof(hexArray2)));
    QVERIFY(4369 == QExtCodecUtils::hexByteArrayToUInt16(QByteArray(hexArray2, sizeof(hexArray2))));

    char hexArray3[] = {char(0x11), char(0x11), char(0x11), char(0x11)};
    QVERIFY(286331153 == QExtCodecUtils::hexByteArrayToUInt32(hexArray3, sizeof(hexArray3)));
    QVERIFY(286331153 == QExtCodecUtils::hexByteArrayToUInt32(QByteArray(hexArray3, sizeof(hexArray3))));

    char hexArray4[] = {char(0x11), char(0x11), char(0x11), char(0x11), char(0x11), char(0x11), char(0x11), char(0x11)};
    QVERIFY(1229782938247303441 == QExtCodecUtils::hexByteArrayToUInt64(hexArray4, sizeof(hexArray4)));
    QVERIFY(1229782938247303441 == QExtCodecUtils::hexByteArrayToUInt64(QByteArray(hexArray4, sizeof(hexArray4))));
}


QTEST_APPLESS_MAIN(QExtCodecUtilsTest)

#include <tst_qextCodecUtils.moc>
