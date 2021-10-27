#include <qextCodecUtils.h>

#include <QtTest>
#include <QtEndian>
#include <QByteArray>
#include <QDebug>

class QEXTCodecUtilsTest : public QObject
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

void QEXTCodecUtilsTest::isHexCodeTest()
{
    QVERIFY(!QEXTCodecUtils::isHexCode(-1));
    QVERIFY(QEXTCodecUtils::isHexCode(0));
    QVERIFY(QEXTCodecUtils::isHexCode(1));
    QVERIFY(QEXTCodecUtils::isHexCode(2));
    QVERIFY(QEXTCodecUtils::isHexCode(3));
    QVERIFY(QEXTCodecUtils::isHexCode(4));
    QVERIFY(QEXTCodecUtils::isHexCode(5));
    QVERIFY(QEXTCodecUtils::isHexCode(6));
    QVERIFY(QEXTCodecUtils::isHexCode(7));
    QVERIFY(QEXTCodecUtils::isHexCode(8));
    QVERIFY(QEXTCodecUtils::isHexCode(9));
    QVERIFY(QEXTCodecUtils::isHexCode(10));
    QVERIFY(QEXTCodecUtils::isHexCode(11));
    QVERIFY(QEXTCodecUtils::isHexCode(12));
    QVERIFY(QEXTCodecUtils::isHexCode(13));
    QVERIFY(QEXTCodecUtils::isHexCode(14));
    QVERIFY(QEXTCodecUtils::isHexCode(15));
    QVERIFY(!QEXTCodecUtils::isHexCode(16));
}

void QEXTCodecUtilsTest::isHexCharTest()
{
    QVERIFY(QEXTCodecUtils::isHexChar('0'));
    QVERIFY(QEXTCodecUtils::isHexChar('1'));
    QVERIFY(QEXTCodecUtils::isHexChar('2'));
    QVERIFY(QEXTCodecUtils::isHexChar('3'));
    QVERIFY(QEXTCodecUtils::isHexChar('4'));
    QVERIFY(QEXTCodecUtils::isHexChar('5'));
    QVERIFY(QEXTCodecUtils::isHexChar('6'));
    QVERIFY(QEXTCodecUtils::isHexChar('7'));
    QVERIFY(QEXTCodecUtils::isHexChar('8'));
    QVERIFY(QEXTCodecUtils::isHexChar('9'));
    QVERIFY(QEXTCodecUtils::isHexChar('a'));
    QVERIFY(QEXTCodecUtils::isHexChar('b'));
    QVERIFY(QEXTCodecUtils::isHexChar('c'));
    QVERIFY(QEXTCodecUtils::isHexChar('d'));
    QVERIFY(QEXTCodecUtils::isHexChar('e'));
    QVERIFY(QEXTCodecUtils::isHexChar('f'));
    QVERIFY(QEXTCodecUtils::isHexChar('A'));
    QVERIFY(QEXTCodecUtils::isHexChar('B'));
    QVERIFY(QEXTCodecUtils::isHexChar('C'));
    QVERIFY(QEXTCodecUtils::isHexChar('D'));
    QVERIFY(QEXTCodecUtils::isHexChar('E'));
    QVERIFY(QEXTCodecUtils::isHexChar('F'));
    QVERIFY(!QEXTCodecUtils::isHexChar('g'));
}

void QEXTCodecUtilsTest::isHexStringTest()
{
    char str1[] = "08fE";
    QVERIFY(QEXTCodecUtils::isHexString(str1, strlen(str1)));
    char str2[] = "0hfE";
    QVERIFY(!QEXTCodecUtils::isHexString(str2, strlen(str2)));

    QString str3("0123456789AbcDef");
    QVERIFY(QEXTCodecUtils::isHexString(str3));
    QString str4("0123456789AbcDefg");
    QVERIFY(!QEXTCodecUtils::isHexString(str4));
}

void QEXTCodecUtilsTest::hexCharToHexCodeTest()
{
    bool success = true;
    char ch = 0;
    ch = QEXTCodecUtils::hexCharToHexCode('1', &success);
    QVERIFY(success && (1 == ch));
    ch = QEXTCodecUtils::hexCharToHexCode('7', &success);
    QVERIFY(success && (7 == ch));
    ch = QEXTCodecUtils::hexCharToHexCode('e', &success);
    QVERIFY(success && (14 == ch));
    ch = QEXTCodecUtils::hexCharToHexCode('A', &success);
    QVERIFY(success && (10 == ch));
    ch = QEXTCodecUtils::hexCharToHexCode('0', &success);
    QVERIFY(success && (0 == ch));
    QEXTCodecUtils::hexCharToHexCode('g', &success);
    QVERIFY(!success);
}

void QEXTCodecUtilsTest::hexStringToHexByteArrayTest()
{
    bool success = true;
    QByteArray hexByteArray;
    for (int i = 0; i < 8; ++i) {
        char ch1 = (char(i * 2) << 4) & 0xf0;
        char ch2 = (char(i * 2 + 1) & 0x0f);
        hexByteArray.append(char(ch1 | ch2));
    }

    char str1[] = "0123456789AbcDef";
    const QByteArray value1 = QEXTCodecUtils::hexStringToHexByteArray(str1, strlen(str1), &success);
    QVERIFY(success && value1 == hexByteArray);

    char str2[] = "0123456789AbcDefGM";
    QEXTCodecUtils::hexStringToHexByteArray(str2, strlen(str2), &success);
    QVERIFY(!success);

    char str3[] = "012";
    QEXTCodecUtils::hexStringToHexByteArray(str3, strlen(str3), &success);
    QVERIFY(!success);

    const QByteArray value2 = QEXTCodecUtils::hexStringToHexByteArray(QString(str1), &success);
    QVERIFY(success && value2 == hexByteArray);

    QEXTCodecUtils::hexStringToHexByteArray(QString(str2), &success);
    QVERIFY(!success);

    QEXTCodecUtils::hexStringToHexByteArray(QString(str3), &success);
    QVERIFY(!success);
}

void QEXTCodecUtilsTest::hexCodeToHexCharTest()
{
    bool success = true;
    char ch = -1;
    ch = QEXTCodecUtils::hexCodeToHexChar(0, &success);
    QVERIFY(success && '0' == ch);
    ch = QEXTCodecUtils::hexCodeToHexChar(1, &success);
    QVERIFY(success && '1' == ch);
    ch = QEXTCodecUtils::hexCodeToHexChar(9, &success);
    QVERIFY(success && '9' == ch);
    ch = QEXTCodecUtils::hexCodeToHexChar(10, &success);
    QVERIFY(success && 'a' == ch);
    ch = QEXTCodecUtils::hexCodeToHexChar(15, &success);
    QVERIFY(success && 'f' == ch);
    QEXTCodecUtils::hexCodeToHexChar(16, &success);
    QVERIFY(!success);
    QEXTCodecUtils::hexCodeToHexChar(-1, &success);
    QVERIFY(!success);
}

void QEXTCodecUtilsTest::hexByteArrayToHexStringTest()
{
    QString hexString;
    for (int i = 0; i < 16; ++i) {
        hexString.append(QString::number(i, 16));
    }

    const unsigned char hexArray1[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    QString value1 = QEXTCodecUtils::hexByteArrayToHexString((char *)hexArray1, sizeof(hexArray1));
    QVERIFY(value1 == hexString);
    value1 = QEXTCodecUtils::hexByteArrayToHexString(QByteArray((char *)hexArray1, sizeof(hexArray1)));
    QVERIFY(value1 == hexString);
}

void QEXTCodecUtilsTest::hexIntToHexStringTest()
{
    QVERIFY("00" == QEXTCodecUtils::hexUInt8ToHexString(0));
    QVERIFY("01" == QEXTCodecUtils::hexUInt8ToHexString(1));
    QVERIFY("02" == QEXTCodecUtils::hexUInt8ToHexString(2));
    QVERIFY("03" == QEXTCodecUtils::hexUInt8ToHexString(3));
    QVERIFY("04" == QEXTCodecUtils::hexUInt8ToHexString(4));
    QVERIFY("05" == QEXTCodecUtils::hexUInt8ToHexString(5));
    QVERIFY("06" == QEXTCodecUtils::hexUInt8ToHexString(6));
    QVERIFY("07" == QEXTCodecUtils::hexUInt8ToHexString(7));
    QVERIFY("08" == QEXTCodecUtils::hexUInt8ToHexString(8));
    QVERIFY("09" == QEXTCodecUtils::hexUInt8ToHexString(9));
    QVERIFY("0a" == QEXTCodecUtils::hexUInt8ToHexString(10));
    QVERIFY("0b" == QEXTCodecUtils::hexUInt8ToHexString(11));
    QVERIFY("0c" == QEXTCodecUtils::hexUInt8ToHexString(12));
    QVERIFY("0d" == QEXTCodecUtils::hexUInt8ToHexString(13));
    QVERIFY("0e" == QEXTCodecUtils::hexUInt8ToHexString(14));
    QVERIFY("0f" == QEXTCodecUtils::hexUInt8ToHexString(15));
    QVERIFY("ff" == QEXTCodecUtils::hexUInt8ToHexString(255));

    QVERIFY("0000" == QEXTCodecUtils::hexUInt16ToHexString(0));
    QVERIFY("0001" == QEXTCodecUtils::hexUInt16ToHexString(1));
    QVERIFY("0002" == QEXTCodecUtils::hexUInt16ToHexString(2));
    QVERIFY("0003" == QEXTCodecUtils::hexUInt16ToHexString(3));
    QVERIFY("0004" == QEXTCodecUtils::hexUInt16ToHexString(4));
    QVERIFY("0005" == QEXTCodecUtils::hexUInt16ToHexString(5));
    QVERIFY("0006" == QEXTCodecUtils::hexUInt16ToHexString(6));
    QVERIFY("0007" == QEXTCodecUtils::hexUInt16ToHexString(7));
    QVERIFY("0008" == QEXTCodecUtils::hexUInt16ToHexString(8));
    QVERIFY("0009" == QEXTCodecUtils::hexUInt16ToHexString(9));
    QVERIFY("000a" == QEXTCodecUtils::hexUInt16ToHexString(10));
    QVERIFY("000b" == QEXTCodecUtils::hexUInt16ToHexString(11));
    QVERIFY("000c" == QEXTCodecUtils::hexUInt16ToHexString(12));
    QVERIFY("000d" == QEXTCodecUtils::hexUInt16ToHexString(13));
    QVERIFY("000e" == QEXTCodecUtils::hexUInt16ToHexString(14));
    QVERIFY("000f" == QEXTCodecUtils::hexUInt16ToHexString(15));
    QVERIFY("00ff" == QEXTCodecUtils::hexUInt16ToHexString(255));
    QVERIFY("ffff" == QEXTCodecUtils::hexUInt16ToHexString(65535));

    QVERIFY("00000000" == QEXTCodecUtils::hexUInt32ToHexString(0));
    QVERIFY("00000001" == QEXTCodecUtils::hexUInt32ToHexString(1));
    QVERIFY("00000002" == QEXTCodecUtils::hexUInt32ToHexString(2));
    QVERIFY("00000003" == QEXTCodecUtils::hexUInt32ToHexString(3));
    QVERIFY("00000004" == QEXTCodecUtils::hexUInt32ToHexString(4));
    QVERIFY("00000005" == QEXTCodecUtils::hexUInt32ToHexString(5));
    QVERIFY("00000006" == QEXTCodecUtils::hexUInt32ToHexString(6));
    QVERIFY("00000007" == QEXTCodecUtils::hexUInt32ToHexString(7));
    QVERIFY("00000008" == QEXTCodecUtils::hexUInt32ToHexString(8));
    QVERIFY("00000009" == QEXTCodecUtils::hexUInt32ToHexString(9));
    QVERIFY("0000000a" == QEXTCodecUtils::hexUInt32ToHexString(10));
    QVERIFY("0000000b" == QEXTCodecUtils::hexUInt32ToHexString(11));
    QVERIFY("0000000c" == QEXTCodecUtils::hexUInt32ToHexString(12));
    QVERIFY("0000000d" == QEXTCodecUtils::hexUInt32ToHexString(13));
    QVERIFY("0000000e" == QEXTCodecUtils::hexUInt32ToHexString(14));
    QVERIFY("0000000f" == QEXTCodecUtils::hexUInt32ToHexString(15));
    QVERIFY("000000ff" == QEXTCodecUtils::hexUInt32ToHexString(255));
    QVERIFY("ffffffff" == QEXTCodecUtils::hexUInt32ToHexString(4294967295));

    QVERIFY("0000000000000000" == QEXTCodecUtils::hexUInt64ToHexString(0));
    QVERIFY("0000000000000001" == QEXTCodecUtils::hexUInt64ToHexString(1));
    QVERIFY("0000000000000002" == QEXTCodecUtils::hexUInt64ToHexString(2));
    QVERIFY("0000000000000003" == QEXTCodecUtils::hexUInt64ToHexString(3));
    QVERIFY("0000000000000004" == QEXTCodecUtils::hexUInt64ToHexString(4));
    QVERIFY("0000000000000005" == QEXTCodecUtils::hexUInt64ToHexString(5));
    QVERIFY("0000000000000006" == QEXTCodecUtils::hexUInt64ToHexString(6));
    QVERIFY("0000000000000007" == QEXTCodecUtils::hexUInt64ToHexString(7));
    QVERIFY("0000000000000008" == QEXTCodecUtils::hexUInt64ToHexString(8));
    QVERIFY("0000000000000009" == QEXTCodecUtils::hexUInt64ToHexString(9));
    QVERIFY("000000000000000a" == QEXTCodecUtils::hexUInt64ToHexString(10));
    QVERIFY("000000000000000b" == QEXTCodecUtils::hexUInt64ToHexString(11));
    QVERIFY("000000000000000c" == QEXTCodecUtils::hexUInt64ToHexString(12));
    QVERIFY("000000000000000d" == QEXTCodecUtils::hexUInt64ToHexString(13));
    QVERIFY("000000000000000e" == QEXTCodecUtils::hexUInt64ToHexString(14));
    QVERIFY("000000000000000f" == QEXTCodecUtils::hexUInt64ToHexString(15));
    QVERIFY("00000000000000ff" == QEXTCodecUtils::hexUInt64ToHexString(255));
    QVERIFY("0fffffffffffffff" == QEXTCodecUtils::hexUInt64ToHexString(1152921504606846975));
}

void QEXTCodecUtilsTest::hexByteArrayToIntTest()
{
    char hexArray1[] = {char(0x11)};
    QVERIFY(17 == QEXTCodecUtils::hexByteArrayToUInt8(hexArray1, sizeof(hexArray1)));
    QVERIFY(17 == QEXTCodecUtils::hexByteArrayToUInt8(QByteArray(hexArray1, sizeof(hexArray1))));

    char hexArray2[] = {char(0x11), char(0x11)};
    QVERIFY(4369 == QEXTCodecUtils::hexByteArrayToUInt16(hexArray2, sizeof(hexArray2)));
    QVERIFY(4369 == QEXTCodecUtils::hexByteArrayToUInt16(QByteArray(hexArray2, sizeof(hexArray2))));

    char hexArray3[] = {char(0x11), char(0x11), char(0x11), char(0x11)};
    QVERIFY(286331153 == QEXTCodecUtils::hexByteArrayToUInt32(hexArray3, sizeof(hexArray3)));
    QVERIFY(286331153 == QEXTCodecUtils::hexByteArrayToUInt32(QByteArray(hexArray3, sizeof(hexArray3))));

    char hexArray4[] = {char(0x11), char(0x11), char(0x11), char(0x11), char(0x11), char(0x11), char(0x11), char(0x11)};
    QVERIFY(1229782938247303441 == QEXTCodecUtils::hexByteArrayToUInt64(hexArray4, sizeof(hexArray4)));
    QVERIFY(1229782938247303441 == QEXTCodecUtils::hexByteArrayToUInt64(QByteArray(hexArray4, sizeof(hexArray4))));
}


QTEST_APPLESS_MAIN(QEXTCodecUtilsTest)

#include <tst_qextCodecUtils.moc>
