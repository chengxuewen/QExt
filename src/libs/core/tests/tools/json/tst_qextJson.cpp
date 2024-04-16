// Copyright (C) 2022 The Qt Company Ltd.
// Copyright (C) 2022 Intel Corporation.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#include <QMap>
#include <QTest>
#include <QVariantList>
#include <QRegularExpression>

// QT_WARNING_DISABLE_DEPRECATED

#include <qextJson.h>


#include <limits>

#define INVALID_UNICODE "\xCE\xBA\xE1"
#define UNICODE_NON_CHARACTER "\xEF\xBF\xBF"
#define UNICODE_DJE "\320\202" // Character from the Serbian Cyrillic alphabet

class tst_qextJson: public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void initTestCase();

    void testValueSimple();
    void testNumbers();
    void testNumbers_2();
    void testNumbers_3();
    void testNumbers_4();

    void testNumberComparisons();

    void testObjectSimple();
    void testObjectTakeDetach();
    void testObjectSmallKeys();
    void testObjectInsertCopies();
    void testArraySimple();
    void testArrayInsertCopies();
    void testValueObject();
    void testValueArray();
    void testObjectNested();
    void testArrayNested();
    void testArrayNestedEmpty();
    void testArrayComfortOperators();
    void testObjectNestedEmpty();

    void testValueRef();

#if 0
    void testValueRefComparison();
    void testObjectIteration();
    void testArrayIteration();

    void testObjectFind();

    void testDocument();

    void nullValues();
    void nullArrays();
    void nullObject();
    void constNullObject();

    void keySorting_data();
    void keySorting();

    void undefinedValues();

    void fromVariant_data();
    void fromVariant();
    void fromVariantSpecial_data();
    void fromVariantSpecial();
    void toVariant_data();
    void toVariant();
    void fromVariantMap();
    void fromVariantHash();
    void toVariantMap();
    void toVariantHash();
    void toVariantList();

    void toJson();
    void toJsonSillyNumericValues();
    void toJsonLargeNumericValues();
    void toJsonDenormalValues();
    void fromJson();
    void fromJsonErrors();
    void parseNumbers();
    void parseStrings();
    void parseDuplicateKeys();
    void testParser();

    void assignToDocument();

    void testDuplicateKeys();
    void testCompaction();
    void testDebugStream();

    void parseEscapes_data();
    void parseEscapes();
    void makeEscapes_data();
    void makeEscapes();

    void assignObjects();
    void assignArrays();

    void testTrailingComma();
    void testDetachBug();
    void testJsonValueRefDefault();

    void valueEquals();
    void objectEquals_data();
    void objectEquals();
    void arrayEquals_data();
    void arrayEquals();
    void documentEquals_data();
    void documentEquals();

    void bom();
    void nesting();

    void longStrings();

    void arrayInitializerList();
    void objectInitializerList();

    void unicodeKeys();
    void garbageAtEnd();

    void removeNonLatinKey();
    void documentFromVariant();

    void parseErrorOffset_data();
    void parseErrorOffset();

    void implicitValueType();
    void implicitDocumentType();

    void streamSerializationQExtJsonDocument_data();
    void streamSerializationQExtJsonDocument();
    void streamSerializationQExtJsonArray_data();
    void streamSerializationQExtJsonArray();
    void streamSerializationQExtJsonObject_data();
    void streamSerializationQExtJsonObject();
    void streamSerializationQExtJsonValue_data();
    void streamSerializationQExtJsonValue();
    void streamSerializationQExtJsonValueEmpty();
    void streamVariantSerialization();
    void escapeSurrogateCodePoints_data();
    void escapeSurrogateCodePoints();

    void fromToVariantConversions_data();
    void fromToVariantConversions();

    void testIteratorComparison();

    void noLeakOnNameClash_data();
    void noLeakOnNameClash();
#endif

private:
    QString testDataDir;
};

void tst_qextJson::initTestCase()
{
    testDataDir = QFileInfo(QFINDTESTDATA("test.json")).absolutePath();
    if (testDataDir.isEmpty())
        testDataDir = QCoreApplication::applicationDirPath();
}

void tst_qextJson::testValueSimple()
{
    QExtJsonObject object;
    object.insert("number", 999.);
    QExtJsonArray array;
    for (int i = 0; i < 10; ++i)
        array.append((double)i);

    QExtJsonValue value(true);
    QCOMPARE(value.type(), QExtJsonValue::Type_Bool);
    QCOMPARE(value.toDouble(), 0.);
    QCOMPARE(value.toString(), QString());
    QCOMPARE(value.toBool(), true);
    QCOMPARE(value.toObject(), QExtJsonObject());
    QCOMPARE(value.toArray(), QExtJsonArray());
    QCOMPARE(value.toDouble(99.), 99.);
    QCOMPARE(value.toString(QString("test")), QString("test"));
    QCOMPARE(value.toObject(object), object);
    QCOMPARE(value.toArray(array), array);

    value = 999.;
    QCOMPARE(value.type(), QExtJsonValue::Type_Number);
    QCOMPARE(value.toDouble(), 999.);
    QCOMPARE(value.toString(), QString());
    QCOMPARE(value.toBool(), false);
    QCOMPARE(value.toBool(true), true);
    QCOMPARE(value.toObject(), QExtJsonObject());
    QCOMPARE(value.toArray(), QExtJsonArray());

    value = QLatin1String("test");
    QCOMPARE(value.toDouble(), 0.);
    QCOMPARE(value.toString(), QLatin1String("test"));
    QCOMPARE(value.toBool(), false);
    QCOMPARE(value.toObject(), QExtJsonObject());
    QCOMPARE(value.toArray(), QExtJsonArray());
}

void tst_qextJson::testNumbers()
{
    {
        int numbers[] = {
            0,
            1,
            2,
            -1,
            -2,
            (1<<25),
            (1<<26),
            (1<<27),
            (1<<28),
            -(1<<25),
            -(1<<26),
            -(1<<27),
            -(1<<28),
            (1<<26) - 1,
            (1<<27) - 1,
            (1<<28) - 1,
            (1<<29) - 1,
            -((1<<26) - 1),
            -((1<<27) - 1),
            -((1<<28) - 1),
            -((1<<29) - 1)
        };
        int n = sizeof(numbers)/sizeof(int);

        QExtJsonArray array;
        for (int i = 0; i < n; ++i)
            array.append(numbers[i]);

        QByteArray serialized = QExtJsonDocument(array).toJson();
        QExtJsonDocument json = QExtJsonDocument::fromJson(serialized);
        QExtJsonArray array2 = json.array();

        QCOMPARE(array.size(), array2.size());
        for (int i = 0; i < array.size(); ++i) {
            QCOMPARE(array.at(i).type(), QExtJsonValue::Type_Number);
            QCOMPARE(array.at(i).toInt(), numbers[i]);
            QCOMPARE(array.at(i).toDouble(), (double)numbers[i]);
            QCOMPARE(array2.at(i).type(), QExtJsonValue::Type_Number);
            QCOMPARE(array2.at(i).toInt(), numbers[i]);
            QCOMPARE(array2.at(i).toDouble(), (double)numbers[i]);
        }
    }

    {
        qint64 numbers[] = {
            0,
            1,
            2,
            -1,
            -2,
            (1ll<<54),
            (1ll<<55),
            (1ll<<56),
            -(1ll<<54),
            -(1ll<<55),
            -(1ll<<56),
            (1ll<<54) - 1,
            (1ll<<55) - 1,
            (1ll<<56) - 1,
            (1ll<<57) - 1,
            (1ll<<58) - 1,
            (1ll<<59) + 1001,
            -((1ll<<54) - 1),
            -((1ll<<55) - 1),
            -((1ll<<56) - 1),
            -((1ll<<57) - 1),
            -((1ll<<58) - 1),
            -((1ll<<59) + 1001),
        };
        int n = sizeof(numbers)/sizeof(qint64);

        QExtJsonArray array;
        for (int i = 0; i < n; ++i)
        {
            array.append(QExtJsonValue(numbers[i]));
        }

        QByteArray serialized = QExtJsonDocument(array).toJson();
        QExtJsonDocument json = QExtJsonDocument::fromJson(serialized);
        QExtJsonArray array2 = json.array();

        QCOMPARE(array.size(), array2.size());
        for (int i = 0; i < array.size(); ++i)
        {
            QCOMPARE(array.at(i).type(), QExtJsonValue::Type_Number);
            QCOMPARE(array.at(i).toInt(), numbers[i]);
            QCOMPARE(array.at(i).toDouble(), (double)numbers[i]);
            QCOMPARE(array2.at(i).type(), QExtJsonValue::Type_Number);
            QCOMPARE(array2.at(i).toInt(), numbers[i]);
            QCOMPARE(array2.at(i).toDouble(), (double)numbers[i]);
        }
    }

    {
        double numbers[] = {
            0,
            -1,
            1,
            double(1ll<<54),
            double(1ll<<55),
            double(1ll<<56),
            double(-(1ll<<54)),
            double(-(1ll<<55)),
            double(-(1ll<<56)),
            double((1ll<<54) - 1),
            double((1ll<<55) - 1),
            double((1ll<<56) - 1),
            double(-((1ll<<54) - 1)),
            double(-((1ll<<55) - 1)),
            double(-((1ll<<56) - 1)),
            1.1,
            0.1,
            -0.1,
            -1.1,
            1e200,
            -1e200
        };
        int n = sizeof(numbers)/sizeof(double);

        QExtJsonArray array;
        for (int i = 0; i < n; ++i)
            array.append(numbers[i]);

        QByteArray serialized = QExtJsonDocument(array).toJson();
        QExtJsonDocument json = QExtJsonDocument::fromJson(serialized);
        QExtJsonArray array2 = json.array();

        QCOMPARE(array.size(), array2.size());
        for (int i = 0; i < array.size(); ++i)
        {
            QCOMPARE(array.at(i).type(), QExtJsonValue::Type_Number);
            QCOMPARE(array.at(i).toDouble(), numbers[i]);
            QCOMPARE(array2.at(i).type(), QExtJsonValue::Type_Number);
            QCOMPARE(array2.at(i).toDouble(), numbers[i]);
        }
    }

}

void tst_qextJson::testNumbers_2()
{
    // test cases from TC39 test suite for ECMAScript
    // http://hg.ecmascript.org/tests/test262/file/d067d2f0ca30/test/suite/ch08/8.5/8.5.1.js

    // Fill an array with 2 to the power of (0 ... -1075)
    double value = 1;
    double floatValues[1076], floatValues_1[1076];
    QExtJsonObject jObject;
    for (int power = 0; power <= 1075; power++)
    {
        floatValues[power] = value;
        jObject.insert(QString::number(power), QExtJsonValue(floatValues[power]));
        // Use basic math operations for testing, which are required to support 'gradual underflow' rather
        // than Math.pow etc..., which are defined as 'implementation dependent'.
        value = value * 0.5;
    }

    QExtJsonDocument jDocument1(jObject);
    QByteArray ba(jDocument1.toJson());

    QExtJsonDocument jDocument2(QExtJsonDocument::fromJson(ba));
    for (int power = 0; power <= 1075; power++)
    {
        floatValues_1[power] = jDocument2.object().value(QString::number(power)).toDouble();
        QVERIFY2(floatValues[power] == floatValues_1[power], QString("floatValues[%1] != floatValues_1[%1]").arg(power).toLatin1());
    }

    // The last value is below min denorm and should round to 0, everything else should contain a value
    QVERIFY2(floatValues_1[1075] == 0, "Value after min denorm should round to 0");

    // Validate the last actual value is min denorm
    QVERIFY2(floatValues_1[1074] == 4.9406564584124654417656879286822e-324, QString("Min denorm value is incorrect: %1").arg(floatValues_1[1074]).toLatin1());

    if constexpr (std::numeric_limits<double>::has_denorm == std::denorm_present)
    {
        // Validate that every value is half the value before it up to 1
        for (int index = 1074; index > 0; index--)
        {
            QVERIFY2(floatValues_1[index] != 0, QString("2**- %1 should not be 0").arg(index).toLatin1());
            QVERIFY2(floatValues_1[index - 1] == (floatValues_1[index] * 2), QString("Value should be double adjacent value at index %1").arg(index).toLatin1());
        }
    }
    else
    {
        qInfo("Skipping denormal test as this system's double type lacks support");
    }
}

void tst_qextJson::testNumbers_3()
{
    // test case from QTBUG-31926
    double d1 = 1.123451234512345;
    double d2 = 1.123451234512346;

    QExtJsonObject jObject;
    jObject.insert("d1", QExtJsonValue(d1));
    jObject.insert("d2", QExtJsonValue(d2));
    QExtJsonDocument jDocument1(jObject);
    QByteArray ba(jDocument1.toJson());

    QExtJsonDocument jDocument2(QExtJsonDocument::fromJson(ba));

    double d1_1(jDocument2.object().value("d1").toDouble());
    double d2_1(jDocument2.object().value("d2").toDouble());
    QVERIFY(d1_1 != d2_1);
}

void tst_qextJson::testNumbers_4()
{
    // no exponent notation used to print numbers between -2^64 and 2^64
    QExtJsonArray array;
    array << QExtJsonValue(+1000000000000000.0);
    array << QExtJsonValue(-1000000000000000.0);
    array << QExtJsonValue(+9007199254740992.0);
    array << QExtJsonValue(-9007199254740992.0);
    array << QExtJsonValue(+9223372036854775808.0);
    array << QExtJsonValue(-9223372036854775808.0);
    array << QExtJsonValue(+18446744073709551616.0);
    array << QExtJsonValue(-18446744073709551616.0);
    const QByteArray json(QExtJsonDocument(array).toJson());
    const QByteArray expected =
        "[\n"
        "    1000000000000000,\n"
        "    -1000000000000000,\n"
        "    9007199254740992,\n"
        "    -9007199254740992,\n"
        "    9223372036854776000,\n"
        "    -9223372036854776000,\n"
        "    18446744073709552000,\n"
        "    -18446744073709552000\n"
        "]\n";
    QCOMPARE(json, expected);

    QExtJsonArray array2;
    array2 << QExtJsonValue(Q_INT64_C(+1000000000000000));
    array2 << QExtJsonValue(Q_INT64_C(-1000000000000000));
    array2 << QExtJsonValue(Q_INT64_C(+9007199254740992));
    array2 << QExtJsonValue(Q_INT64_C(-9007199254740992));
    array2 << QExtJsonValue(Q_INT64_C(+9223372036854775807));
    array2 << QExtJsonValue(Q_INT64_C(-9223372036854775807));
    const QByteArray json2(QExtJsonDocument(array2).toJson());
    const QByteArray expected2 =
        "[\n"
        "    1000000000000000,\n"
        "    -1000000000000000,\n"
        "    9007199254740992,\n"
        "    -9007199254740992,\n"
        "    9223372036854775807,\n"
        "    -9223372036854775807\n"
        "]\n";
    QCOMPARE(json2, expected2);
}

void tst_qextJson::testNumberComparisons()
{
    // QExtJsonValues created using doubles only have double precision
    QExtJsonValue llMinDbl(-9223372036854775807.0);
    QExtJsonValue llMinPlus1Dbl(-9223372036854775806.0);
    QCOMPARE(llMinDbl == llMinPlus1Dbl, -9223372036854775807.0 == -9223372036854775806.0); // true

    // QExtJsonValues created using qint64 have full qint64 precision
    QExtJsonValue llMin(Q_INT64_C(-9223372036854775807));
    QExtJsonValue llMinPlus1(Q_INT64_C(-9223372036854775806));
    QCOMPARE(llMin == llMinPlus1, Q_INT64_C(-9223372036854775807) == Q_INT64_C(-9223372036854775806)); // false

    // The different storage formats should be able to compare as their C++ versions (all true)
    QCOMPARE(llMin == llMinDbl, Q_INT64_C(-9223372036854775807) == -9223372036854775807.0);
    QCOMPARE(llMinDbl == llMin, -9223372036854775807.0 == Q_INT64_C(-9223372036854775807));
    QCOMPARE(llMinPlus1 == llMinPlus1Dbl, Q_INT64_C(-9223372036854775806) == -9223372036854775806.0);
    QCOMPARE(llMinPlus1Dbl == llMinPlus1, -9223372036854775806.0 == Q_INT64_C(-9223372036854775806));
    QCOMPARE(llMinPlus1 == llMinDbl, Q_INT64_C(-9223372036854775806) == -9223372036854775807.0);
    QCOMPARE(llMinPlus1Dbl == llMin, -9223372036854775806.0 == Q_INT64_C(-9223372036854775807));
}

void tst_qextJson::testObjectSimple()
{
    QExtJsonObject object;
    object.insert("number", 999.);
    QCOMPARE(object.value("number").type(), QExtJsonValue::Type_Number);
    QCOMPARE(object.value(QLatin1String("number")).toDouble(), 999.);
    object.insert("string", QString::fromLatin1("test"));
    QCOMPARE(object.value("string").type(), QExtJsonValue::Type_String);
    QCOMPARE(object.value(QLatin1String("string")).toString(), QString("test"));
    object.insert("boolean", true);
    QCOMPARE(object.value("boolean").toBool(), true);
    QCOMPARE(object.value(QLatin1String("boolean")).toBool(), true);
    QExtJsonObject object2 = object;
    QExtJsonObject object3 = object;

    QStringList keys = object.keys();
    QVERIFY2(keys.contains("number"), "key number not found");
    QVERIFY2(keys.contains("string"), "key string not found");
    QVERIFY2(keys.contains("boolean"), "key boolean not found");

    // if we put a JsonValue into the JsonObject and retrieve
    // it, it should be identical.
    QExtJsonValue value(QLatin1String("foo"));
    object.insert("value", value);
    QCOMPARE(object.value("value"), value);

    int size = object.size();
    object.remove("boolean");
    QCOMPARE(object.size(), size - 1);
    QVERIFY2(!object.contains("boolean"), "key boolean should have been removed");

    QExtJsonValue taken = object.take("value");
    QCOMPARE(taken, value);
    QVERIFY2(!object.contains("value"), "key value should have been removed");

    QString before = object.value("string").toString();
    object.insert("string", QString::fromLatin1("foo"));
    QVERIFY2(object.value(QLatin1String("string")).toString() != before, "value should have been updated");

    // same tests again but with QStringView keys
    object2.insert(QStringView(u"value"), value);
    QCOMPARE(object2.value("value"), value);

    size = object2.size();
    object2.remove(QStringView(u"boolean"));
    QCOMPARE(object2.size(), size - 1);
    QVERIFY2(!object2.contains(QStringView(u"boolean")), "key boolean should have been removed");

    taken = object2.take(QStringView(u"value"));
    QCOMPARE(taken, value);
    QVERIFY2(!object2.contains("value"), "key value should have been removed");

    before = object2.value("string").toString();
    object2.insert(QStringView(u"string"), QString::fromLatin1("foo"));
    QVERIFY2(object2.value(QStringView(u"string")).toString() != before, "value should have been updated");

    // same tests again but with QLatin1String keys
    object3.insert(QLatin1String("value"), value);
    QCOMPARE(object3.value("value"), value);

    size = object3.size();
    object3.remove(QLatin1String("boolean"));
    QCOMPARE(object3.size(), size - 1);
    QVERIFY2(!object3.contains("boolean"), "key boolean should have been removed");

    taken = object3.take(QLatin1String("value"));
    QCOMPARE(taken, value);
    QVERIFY2(!object3.contains("value"), "key value should have been removed");

    before = object3.value("string").toString();
    object3.insert(QLatin1String("string"), QString::fromLatin1("foo"));
    QVERIFY2(object3.value(QLatin1String("string")).toString() != before, "value should have been updated");

    size = object.size();
    QExtJsonObject subobject;
    subobject.insert("number", 42);
    subobject.insert(QLatin1String("string"), QLatin1String("foobar"));
    object.insert("subobject", subobject);
    QCOMPARE(object.size(), size+1);
    QExtJsonValue subvalue = object.take(QLatin1String("subobject"));
    QCOMPARE(object.size(), size);
    QCOMPARE(subvalue.toObject(), subobject);
    // make object detach by modifying it many times
    for (int i = 0; i < 64; ++i)
        object.insert(QLatin1String("string"), QLatin1String("bar"));
    QCOMPARE(object.size(), size);
    QCOMPARE(subvalue.toObject(), subobject);
}

void tst_qextJson::testObjectTakeDetach()
{
    QExtJsonObject object1, object2;
    object1["key1"] = 1;
    object1["key2"] = 2;
    object2 = object1;

    object1.take("key2");
    object1.remove("key1");
    QVERIFY(!object1.contains("key1"));
    QVERIFY(object2.contains("key1"));
    QVERIFY(object2.value("key1").isNumber());

    QVERIFY(!object1.contains("key2"));
    QVERIFY(object2.contains("key2"));
    QVERIFY(object2.value("key2").isNumber());
}

void tst_qextJson::testObjectSmallKeys()
{
    QExtJsonObject data1;
    data1.insert(QStringLiteral("1"), 123.);
    QVERIFY(data1.contains(QStringLiteral("1")));
    QCOMPARE(data1.value(QStringLiteral("1")).toDouble(), (double)123);
    data1.insert(QStringLiteral("12"), 133.);
    QCOMPARE(data1.value(QStringLiteral("12")).toDouble(), (double)133);
    QVERIFY(data1.contains(QStringLiteral("12")));
    data1.insert(QStringLiteral("123"), 323.);
    QCOMPARE(data1.value(QStringLiteral("12")).toDouble(), (double)133);
    QVERIFY(data1.contains(QStringLiteral("123")));
    QCOMPARE(data1.value(QStringLiteral("123")).type(), QExtJsonValue::Type_Number);
    QCOMPARE(data1.value(QStringLiteral("123")).toDouble(), (double)323);
    QCOMPARE(data1.constEnd() - data1.constBegin(), 3);
    QCOMPARE(data1.end() - data1.begin(), 3);
}

void tst_qextJson::testObjectInsertCopies()
{
    {
        QExtJsonObject obj;
        obj["prop1"] = "TEST";
        QCOMPARE(obj.size(), 1);
        QCOMPARE(obj.value("prop1"), "TEST");

        obj["prop2"] = obj.value("prop1");
        QCOMPARE(obj.size(), 2);
        QCOMPARE(obj.value("prop1"), "TEST");
        QCOMPARE(obj.value("prop2"), "TEST");
    }
    {
        // see QTBUG-83366
        QExtJsonObject obj;
        obj["value"] = "TEST";
        QCOMPARE(obj.size(), 1);
        QCOMPARE(obj.value("value"), "TEST");

        obj["prop2"] = obj.value("value");
        QCOMPARE(obj.size(), 2);
        QCOMPARE(obj.value("value"), "TEST");
        QCOMPARE(obj.value("prop2"), "TEST");
    }
    {
        QExtJsonObject obj;
        obj["value"] = "TEST";
        QCOMPARE(obj.size(), 1);
        QCOMPARE(obj.value("value"), "TEST");

        // same as previous, but this is a QExtJsonValueRef
        QExtJsonValueRef rv = obj["prop2"];
        rv = obj["value"];
        QCOMPARE(obj.size(), 2);
        QCOMPARE(obj.value("value"), "TEST");
        QCOMPARE(obj.value("prop2"), "TEST");
    }
    {
        QExtJsonObject obj;
        obj["value"] = "TEST";
        QCOMPARE(obj.size(), 1);
        QCOMPARE(obj.value("value"), "TEST");

        // same as previous, but this is a QExtJsonValueRef
        QExtJsonValueRef rv = obj["value"];
        obj["prop2"] = rv;
        QCOMPARE(obj.size(), 2);
        QCOMPARE(obj.value("value"), "TEST");
        QEXPECT_FAIL("", "QTBUG-83398: design flaw: the obj[] call invalidates the QExtJsonValueRef", Continue);
        QCOMPARE(obj.value("prop2"), "TEST");
    }
    {
        QExtJsonObject obj;
        obj["value"] = "TEST";
        QCOMPARE(obj.size(), 1);
        QCOMPARE(obj.value("value"), "TEST");

        QExtJsonValueRef v = obj["value"];
        QExtJsonObject obj2 = obj;
        obj.insert("prop2", v);
        QCOMPARE(obj.size(), 2);
        QCOMPARE(obj.value("value"), "TEST");
        QCOMPARE(obj.value("prop2"), "TEST");
        QCOMPARE(obj2.size(), 1);
        QCOMPARE(obj2.value("value"), "TEST");
    }
}

void tst_qextJson::testArraySimple()
{
    QExtJsonArray array;
    array.append(999.);
    array.append(QString::fromLatin1("test"));
    array.append(true);

    QExtJsonValue val = array.at(0);
    QCOMPARE(array.at(0).toDouble(), 999.);
    QCOMPARE(array.at(1).toString(), QString("test"));
    QCOMPARE(array.at(2).toBool(), true);
    QCOMPARE(array.size(), 3);

    // if we put a JsonValue into the JsonArray and retrieve
    // it, it should be identical.
    QExtJsonValue value(QLatin1String("foo"));
    array.append(value);
    QCOMPARE(array.at(3), value);

    int size = array.size();
    array.removeAt(2);
    --size;
    QCOMPARE(array.size(), size);

    QExtJsonValue taken = array.takeAt(0);
    --size;
    QCOMPARE(taken.toDouble(), 999.);
    QCOMPARE(array.size(), size);

    // check whether null values work
    array.append(QExtJsonValue());
    ++size;
    QCOMPARE(array.size(), size);
    QCOMPARE(array.last().type(), QExtJsonValue::Type_Null);
    QCOMPARE(array.last(), QExtJsonValue());

    QCOMPARE(array.first().type(), QExtJsonValue::Type_String);
    QCOMPARE(array.first(), QExtJsonValue(QLatin1String("test")));

    array.prepend(false);
    QCOMPARE(array.first().type(), QExtJsonValue::Type_Bool);
    QCOMPARE(array.first(), QExtJsonValue(false));

    QCOMPARE(array.at(-1), QExtJsonValue(QExtJsonValue::Type_Undefined));
    QCOMPARE(array.at(array.size()), QExtJsonValue(QExtJsonValue::Type_Undefined));

    array.replace(0, -555.);
    QCOMPARE(array.first().type(), QExtJsonValue::Type_Number);
    QCOMPARE(array.first(), QExtJsonValue(-555.));
    QCOMPARE(array.at(1).type(), QExtJsonValue::Type_String);
    QCOMPARE(array.at(1), QExtJsonValue(QLatin1String("test")));
}

void tst_qextJson::testArrayInsertCopies()
{
    {
        QExtJsonArray array;
        array.append("TEST");
        QCOMPARE(array.size(), 1);
        QCOMPARE(array.at(0), "TEST");

        array.append(array.at(0));
        QCOMPARE(array.size(), 2);
        QCOMPARE(array.at(0), "TEST");
        QCOMPARE(array.at(1), "TEST");
    }
    {
        QExtJsonArray array;
        array.append("TEST");
        QCOMPARE(array.size(), 1);
        QCOMPARE(array.at(0), "TEST");

        array.prepend(array.at(0));
        QCOMPARE(array.size(), 2);
        QCOMPARE(array.at(0), "TEST");
        QCOMPARE(array.at(1), "TEST");
    }
}

void tst_qextJson::testValueObject()
{
    QExtJsonObject object;
    object.insert("number", 999.);
    object.insert("string", QLatin1String("test"));
    object.insert("boolean", true);

    QExtJsonValue value(object);

    // if we don't modify the original JsonObject, toObject()
    // on the JsonValue should return the same object (non-detached).
    QCOMPARE(value.toObject(), object);

    // if we modify the original object, it should detach
    object.insert("test", QExtJsonValue(QLatin1String("test")));
    QVERIFY2(value.toObject() != object, "object should have detached");
}

void tst_qextJson::testValueArray()
{
    QExtJsonArray array;
    QList<QExtJsonValue> args;
    args << "wrong value";
    QExtJsonArray otherArray(args);
    QExtJsonValue value(array);
    QCOMPARE(value.toArray(), array);
    QCOMPARE(value.toArray(otherArray), array);

    array.append(999.);
    array.append(QLatin1String("test"));
    array.append(true);
    value = array;

    // if we don't modify the original JsonArray, toArray()
    // on the JsonValue should return the same object (non-detached).
    QCOMPARE(value.toArray(), array);
    QCOMPARE(value.toArray(otherArray), array);

    // if we modify the original array, it should detach
    array.append(QLatin1String("test"));
    QVERIFY2(value.toArray() != array, "array should have detached");
}

void tst_qextJson::testObjectNested()
{
    QExtJsonObject inner, outer;
    QList<QExtJsonValue> args;
    args << "wrong key";
    args << "wrong value";
    QExtJsonObject otherObject(args);
    QExtJsonValue v = inner;
    QCOMPARE(v.toObject(), inner);
    QCOMPARE(v.toObject(otherObject), inner);

    inner.insert("number", 999.);
    outer.insert("nested", inner);

    // if we don't modify the original JsonObject, value()
    // should return the same object (non-detached).
    QExtJsonObject value = outer.value("nested").toObject();
    v = value;
    QCOMPARE(value, inner);
    QCOMPARE(value.value("number").toDouble(), 999.);
    QCOMPARE(v.toObject(), inner);
    QCOMPARE(v.toObject(otherObject), inner);
    QCOMPARE(v["number"].toDouble(), 999.);

    // if we modify the original object, it should detach and not
    // affect the nested object
    inner.insert("number", 555.);
    value = outer.value("nested").toObject();
    QVERIFY2(inner.value("number").toDouble() != value.value("number").toDouble(),
             "object should have detached");

    // array in object
    QExtJsonArray array;
    array.append(123.);
    array.append(456.);
    outer.insert("array", array);
    QCOMPARE(outer.value("array").toArray(), array);
    QCOMPARE(outer.value("array").toArray().at(1).toDouble(), 456.);

    // two deep objects
    QExtJsonObject twoDeep;
    twoDeep.insert("boolean", true);
    inner.insert("nested", twoDeep);
    outer.insert("nested", inner);
    QCOMPARE(outer.value("nested").toObject().value("nested").toObject(), twoDeep);
    QCOMPARE(outer.value("nested").toObject().value("nested").toObject().value("boolean").toBool(), true);
}

void tst_qextJson::testArrayNested()
{
    QExtJsonArray inner, outer;
    inner.append(999.);
    outer.append(inner);

    // if we don't modify the original JsonArray, value()
    // should return the same array (non-detached).
    QExtJsonArray value = outer.at(0).toArray();
    QCOMPARE(value, inner);
    QCOMPARE(value.at(0).toDouble(), 999.);

    // if we modify the original array, it should detach and not
    // affect the nested array
    inner.append(555.);
    value = outer.at(0).toArray();
    QVERIFY2(inner.size() != value.size(), "array should have detached");

    // objects in arrays
    QExtJsonObject object;
    object.insert("boolean", true);
    outer.append(object);
    QCOMPARE(outer.last().toObject(), object);
    QCOMPARE(outer.last().toObject().value("boolean").toBool(), true);

    // two deep arrays
    QExtJsonArray twoDeep;
    twoDeep.append(QExtJsonValue(QString::fromLatin1("nested")));
    inner.append(twoDeep);
    outer.append(inner);
    QCOMPARE(outer.last().toArray().last().toArray(), twoDeep);
    QCOMPARE(outer.last().toArray().last().toArray().at(0).toString(), QString("nested"));
}

void tst_qextJson::testArrayNestedEmpty()
{
    QExtJsonObject object;
    QExtJsonArray inner;
    object.insert("inner", inner);
    QExtJsonValue val = object.value("inner");
    QExtJsonArray value = object.value("inner").toArray();
    QVERIFY(QExtJsonDocument(value).isArray());
    QCOMPARE(value.size(), 0);
    QCOMPARE(value, inner);
    QCOMPARE(value.size(), 0);
    object.insert("count", 0.);
    QCOMPARE(object.value("inner").toArray().size(), 0);
    QVERIFY(object.value("inner").toArray().isEmpty());
}

void tst_qextJson::testObjectNestedEmpty()
{
    QExtJsonObject object;
    QExtJsonObject inner;
    QExtJsonObject inner2;
    object.insert("inner", inner);
    object.insert("inner2", inner2);
    QExtJsonObject value = object.value("inner").toObject();
    QVERIFY(QExtJsonDocument(value).isObject());
    QCOMPARE(value.size(), 0);
    QCOMPARE(value, inner);
    QCOMPARE(value.size(), 0);
    object.insert("count", 0.);
    QCOMPARE(object.value("inner").toObject().size(), 0);
    QCOMPARE(object.value("inner").type(), QExtJsonValue::Type_Object);
}

void tst_qextJson::testArrayComfortOperators()
{
    QExtJsonArray first;
    first.append(123.);
    first.append(QLatin1String("foo"));

    QExtJsonArray second = QExtJsonArray() << 123. << QLatin1String("foo");
    QCOMPARE(first, second);

    first = first + QLatin1String("bar");
    second += QLatin1String("bar");
    QCOMPARE(first, second);
}

void tst_qextJson::testValueRef()
{
    QExtJsonArray array;
    array.append(1.);
    array.append(2.);
    array.append(3.);
    array.append(4);
    array.append(4.1);
    array[1] = false;

    QCOMPARE(array.size(), 5);
    QCOMPARE(array.at(0).toDouble(), 1.);
    QCOMPARE(array.at(2).toDouble(), 3.);
    QCOMPARE(array.at(3).toInt(), 4);
    QCOMPARE(array.at(4).toInt(), 0);
    QCOMPARE(array.at(1).type(), QExtJsonValue::Type_Bool);
    QCOMPARE(array.at(1).toBool(), false);

    QExtJsonObject object;
    object[QLatin1String("key")] = true;
    QCOMPARE(object.size(), 1);
    object.insert(QLatin1String("null"), QExtJsonValue());
    QCOMPARE(object.value(QLatin1String("null")), QExtJsonValue());
    object[QLatin1String("null")] = 100.;
    QCOMPARE(object.value(QLatin1String("null")).type(), QExtJsonValue::Type_Number);
    // QExtJsonValue val = std::as_const(object)[QLatin1String("null")];
    // QCOMPARE(val.toDouble(), 100.);
    QCOMPARE(object.size(), 2);

    array[1] = array[2] = object[QLatin1String("key")] = 42;
    QCOMPARE(array[1], array[2]);
    QCOMPARE(array[2], object[QLatin1String("key")]);
    QCOMPARE(object.value(QLatin1String("key")), QExtJsonValue(42));
}

#if 0
void tst_qextJson::testValueRefComparison()
{
    QExtJsonValue a0 = 42.;
    QExtJsonValue a1 = QStringLiteral("142");

#define CHECK_IMPL(lhs, rhs, ineq) \
    QCOMPARE(lhs, rhs); \
        QVERIFY(!(lhs != rhs)); \
        QVERIFY(lhs != ineq); \
        QVERIFY(!(lhs == ineq)); \
        QVERIFY(ineq != rhs); \
        QVERIFY(!(ineq == rhs)); \
    /* end */

#define CHECK(lhs, rhs, ineq) \
        do { \
            CHECK_IMPL(lhs, rhs, ineq) \
            CHECK_IMPL(std::as_const(lhs), rhs, ineq) \
            CHECK_IMPL(lhs, std::as_const(rhs), ineq) \
            CHECK_IMPL(std::as_const(lhs), std::as_const(rhs), ineq) \
    } while (0)

        // check that the (in)equality operators aren't ambiguous in C++20:
        QExtJsonArray a = {a0, a1};

    static_assert(std::is_same_v<decltype(a[0]), QExtJsonValueRef>);

    auto r0 = a.begin()[0];
    auto r1 = a.begin()[1];
    auto c0 = std::as_const(a).begin()[0];
    // ref <> ref
    CHECK(r0, r0, r1);
    // cref <> ref
    CHECK(c0, r0, r1);
    // ref <> cref
    CHECK(r0, c0, r1);
    // ref <> val
    CHECK(r0, a0, r1);
    // cref <> val
    CHECK(c0, a0, r1);
    // val <> ref
    CHECK(a0, r0, a1);
    // val <> cref
    CHECK(a0, c0, a1);
    // val <> val
    CHECK(a0, a0, a1);

#undef CHECK
#undef CHECK_IMPL
}

void tst_qextJson::testObjectIteration()
{
    QExtJsonObject object;

    for (QExtJsonObject::iterator it = object.begin(); it != object.end(); ++it)
        QFAIL("Iterator of default-initialized object should be empty");

    const QString property = "kkk";
    object.insert(property, 11);
    object.take(property);
    for (QExtJsonObject::iterator it = object.begin(); it != object.end(); ++it)
        QFAIL("Iterator after property add-and-remove should be empty");

    // insert in weird order to confirm keys are sorted
    for (int i : {0, 9, 5, 7, 8, 2, 1, 3, 6, 4})
        object[QString::number(i)] = double(i);

    QCOMPARE(object.size(), 10);

    QCOMPARE(object.begin()->toDouble(), object.constBegin()->toDouble());

    for (QExtJsonObject::iterator it = object.begin(); it != object.end(); ++it) {
        QExtJsonValue value = it.value();
        QCOMPARE((double)it.key().toInt(), value.toDouble());
    }

    {
        QExtJsonObject object2 = object;
        QCOMPARE(object, object2);

        QExtJsonValue val = *object2.begin();
        auto next = object2.erase(object2.begin());
        QCOMPARE(object.size(), 10);
        QCOMPARE(object2.size(), 9);
        QVERIFY(next == object2.begin());

        double d = 1;   // we erased the first item
        for (auto it = object2.constBegin(); it != object2.constEnd(); ++it, d += 1) {
            QExtJsonValue value = it.value();
            QVERIFY(it.value() != val);
            QCOMPARE(it.value(), d);
            QCOMPARE(it.value().toDouble(), d);
            QCOMPARE(it.key().toInt(), value.toDouble());
        }
    }

    {
        QExtJsonObject object2 = object;
        QCOMPARE(object, object2);

        QExtJsonValue val = *(object2.end() - 1);
        auto next = object2.erase(object2.end() - 1);
        QCOMPARE(object.size(), 10);
        QCOMPARE(object2.size(), 9);
        QVERIFY(next == object2.end());
        double d = 0;
        for (auto it = object2.constBegin(); it != object2.constEnd(); ++it, d += 1) {
            QExtJsonValue value = it.value();
            QVERIFY(it.value() != val);
            QCOMPARE(it.value(), d);
            QCOMPARE(it.value().toDouble(), d);
            QCOMPARE(it.key().toInt(), value.toDouble());
        }
    }

    {
        QExtJsonObject object2 = object;
        QCOMPARE(object, object2);

        QExtJsonObject::iterator it = object2.find(QString::number(5));
        QExtJsonValue val = *it;
        auto next = object2.erase(it);
        QCOMPARE(object.size(), 10);
        QCOMPARE(object2.size(), 9);
        QCOMPARE(*next, 6);

        int i = 0;
        for (auto it = object2.constBegin(); it != object2.constEnd(); ++it, ++i) {
            if (i == 5)
                ++i;
            QExtJsonValue value = it.value();
            QVERIFY(it.value() != val);
            QCOMPARE(it.value(), i);
            QCOMPARE(it.value().toInt(), i);
            QCOMPARE(it.key().toInt(), value.toDouble());
        }
    }

    {
        QExtJsonObject::Iterator it = object.begin();
        it += 5;
        QCOMPARE(QExtJsonValue(it.value()).toDouble(), 5.);
        it -= 3;
        QCOMPARE(QExtJsonValue(it.value()).toDouble(), 2.);
        QExtJsonObject::Iterator it2 = it + 5;
        QCOMPARE(QExtJsonValue(it2.value()).toDouble(), 7.);
        it2 = it - 1;
        QCOMPARE(QExtJsonValue(it2.value()).toDouble(), 1.);
    }

    {
        QExtJsonObject::ConstIterator it = object.constBegin();
        it += 5;
        QCOMPARE(QExtJsonValue(it.value()).toDouble(), 5.);
        it -= 3;
        QCOMPARE(QExtJsonValue(it.value()).toDouble(), 2.);
        QExtJsonObject::ConstIterator it2 = it + 5;
        QCOMPARE(QExtJsonValue(it2.value()).toDouble(), 7.);
        it2 = it - 1;
        QCOMPARE(QExtJsonValue(it2.value()).toDouble(), 1.);
    }

    QExtJsonObject::Iterator it = object.begin();
    while (!object.isEmpty())
        it = object.erase(it);
    QCOMPARE(object.size() , 0);
    QCOMPARE(it, object.end());
}

void tst_qextJson::testArrayIteration()
{
    QExtJsonArray array;
    for (int i = 0; i < 10; ++i)
        array.append(i);

    QCOMPARE(array.size(), 10);

    int i = 0;
    for (QExtJsonArray::iterator it = array.begin(); it != array.end(); ++it, ++i) {
        QExtJsonValue value = (*it);
        QCOMPARE((double)i, value.toDouble());
    }

    QCOMPARE(array.begin()->toDouble(), array.constBegin()->toDouble());

    {
        QExtJsonArray array2 = array;
        QCOMPARE(array, array2);

        QExtJsonValue val = *array2.begin();
        auto next = array2.erase(array2.begin());
        QCOMPARE(array.size(), 10);
        QCOMPARE(array2.size(), 9);
        QVERIFY(next == array2.begin());

        i = 1;
        for (auto it = array2.constBegin(); it != array2.constEnd(); ++it, ++i) {
            QExtJsonValue value = (*it);
            QCOMPARE(value.toInt(), i);
            QCOMPARE(value.toDouble(), i);
            QCOMPARE(it->toInt(), i);
            QCOMPARE(it->toDouble(), i);
        }
    }

    {
        QExtJsonArray array2 = array;
        QCOMPARE(array, array2);

        QExtJsonValue val = array2.last();
        auto next = array2.erase(array2.end() - 1);
        QCOMPARE(array.size(), 10);
        QCOMPARE(array2.size(), 9);
        QVERIFY(next == array2.end());

        i = 0;
        for (auto it = array2.constBegin(); it != array2.constEnd(); ++it, ++i) {
            QExtJsonValue value = (*it);
            QCOMPARE(value.toInt(), i);
            QCOMPARE(value.toDouble(), i);
            QCOMPARE(it->toInt(), i);
            QCOMPARE(it->toDouble(), i);
        }
    }

    {
        QExtJsonArray::Iterator it = array.begin();
        it += 5;
        QCOMPARE(QExtJsonValue((*it)).toDouble(), 5.);
        it -= 3;
        QCOMPARE(QExtJsonValue((*it)).toDouble(), 2.);
        QExtJsonArray::Iterator it2 = it + 5;
        QCOMPARE(QExtJsonValue(*it2).toDouble(), 7.);
        it2 = it - 1;
        QCOMPARE(QExtJsonValue(*it2).toDouble(), 1.);
    }

    {
        QExtJsonArray::ConstIterator it = array.constBegin();
        it += 5;
        QCOMPARE(QExtJsonValue((*it)).toDouble(), 5.);
        it -= 3;
        QCOMPARE(QExtJsonValue((*it)).toDouble(), 2.);
        QExtJsonArray::ConstIterator it2 = it + 5;
        QCOMPARE(QExtJsonValue(*it2).toDouble(), 7.);
        it2 = it - 1;
        QCOMPARE(QExtJsonValue(*it2).toDouble(), 1.);
    }

    QExtJsonArray::Iterator it = array.begin();
    while (!array.isEmpty())
        it = array.erase(it);
    QCOMPARE(array.size() , 0);
    QCOMPARE(it, array.end());
}

void tst_qextJson::testObjectFind()
{
    QExtJsonObject object;
    for (int i = 0; i < 10; ++i)
        object[QString::number(i)] = i;

    QCOMPARE(object.size(), 10);

    QExtJsonObject::iterator it = object.find(QLatin1String("1"));
    QCOMPARE((*it).toDouble(), 1.);
    it = object.find(QString("11"));
    QCOMPARE(it, object.end());

    QExtJsonObject::const_iterator cit = object.constFind(QLatin1String("1"));
    QCOMPARE((*cit).toDouble(), 1.);
    cit = object.constFind(QString("11"));
    QCOMPARE(cit, object.constEnd());
}

void tst_qextJson::testDocument()
{
    QExtJsonDocument doc;
    QCOMPARE(doc.isEmpty(), true);
    QCOMPARE(doc.isArray(), false);
    QCOMPARE(doc.isObject(), false);

    QExtJsonObject object;
    doc.setObject(object);
    QCOMPARE(doc.isEmpty(), false);
    QCOMPARE(doc.isArray(), false);
    QCOMPARE(doc.isObject(), true);

    object.insert(QLatin1String("Key"), QLatin1String("Value"));
    doc.setObject(object);
    QCOMPARE(doc.isEmpty(), false);
    QCOMPARE(doc.isArray(), false);
    QCOMPARE(doc.isObject(), true);
    QCOMPARE(doc.object(), object);
    QCOMPARE(doc.array(), QExtJsonArray());

    doc = QExtJsonDocument();
    QCOMPARE(doc.isEmpty(), true);
    QCOMPARE(doc.isArray(), false);
    QCOMPARE(doc.isObject(), false);

    QExtJsonArray array;
    doc.setArray(array);
    QCOMPARE(doc.isEmpty(), false);
    QCOMPARE(doc.isArray(), true);
    QCOMPARE(doc.isObject(), false);

    array.append(QLatin1String("Value"));
    doc.setArray(array);
    QCOMPARE(doc.isEmpty(), false);
    QCOMPARE(doc.isArray(), true);
    QCOMPARE(doc.isObject(), false);
    QCOMPARE(doc.array(), array);
    QCOMPARE(doc.object(), QExtJsonObject());

    QExtJsonObject outer;
    outer.insert(QLatin1String("outerKey"), 22);
    QExtJsonObject inner;
    inner.insert(QLatin1String("innerKey"), 42);
    outer.insert(QLatin1String("innter"), inner);
    QExtJsonArray innerArray;
    innerArray.append(23);
    outer.insert(QLatin1String("innterArray"), innerArray);

    QExtJsonDocument doc2(outer.value(QLatin1String("innter")).toObject());
    QVERIFY(doc2.object().contains(QLatin1String("innerKey")));
    QCOMPARE(doc2.object().value(QLatin1String("innerKey")), QExtJsonValue(42));

    QExtJsonDocument doc3;
    doc3.setObject(outer.value(QLatin1String("innter")).toObject());
    QCOMPARE(doc3.isArray(), false);
    QCOMPARE(doc3.isObject(), true);
    QVERIFY(doc3.object().contains(QString("innerKey")));
    QCOMPARE(doc3.object().value(QLatin1String("innerKey")), QExtJsonValue(42));

    QExtJsonDocument doc4(outer.value(QLatin1String("innterArray")).toArray());
    QCOMPARE(doc4.isArray(), true);
    QCOMPARE(doc4.isObject(), false);
    QCOMPARE(doc4.array().size(), 1);
    QCOMPARE(doc4.array().at(0), QExtJsonValue(23));

    QExtJsonDocument doc5;
    doc5.setArray(outer.value(QLatin1String("innterArray")).toArray());
    QCOMPARE(doc5.isArray(), true);
    QCOMPARE(doc5.isObject(), false);
    QCOMPARE(doc5.array().size(), 1);
    QCOMPARE(doc5.array().at(0), QExtJsonValue(23));
}

void tst_qextJson::nullValues()
{
    QExtJsonArray array;
    array.append(QExtJsonValue());

    QCOMPARE(array.size(), 1);
    QCOMPARE(array.at(0), QExtJsonValue());

    QExtJsonObject object;
    object.insert(QString("key"), QExtJsonValue());
    QCOMPARE(object.contains(QLatin1String("key")), true);
    QCOMPARE(object.size(), 1);
    QCOMPARE(object.value(QString("key")), QExtJsonValue());
}

void tst_qextJson::nullArrays()
{
    QExtJsonArray nullArray;
    QExtJsonArray nonNull;
    nonNull.append(QLatin1String("bar"));

    QCOMPARE(nullArray, QExtJsonArray());
    QVERIFY(nullArray != nonNull);
    QVERIFY(nonNull != nullArray);

    QCOMPARE(nullArray.size(), 0);
    QCOMPARE(nullArray.takeAt(0), QExtJsonValue(QExtJsonValue::Undefined));
    QCOMPARE(nullArray.first(), QExtJsonValue(QExtJsonValue::Undefined));
    QCOMPARE(nullArray.last(), QExtJsonValue(QExtJsonValue::Undefined));
    nullArray.removeAt(0);
    nullArray.removeAt(-1);

    nullArray.append(QString("bar"));
    nullArray.removeAt(0);

    QCOMPARE(nullArray.size(), 0);
    QCOMPARE(nullArray.takeAt(0), QExtJsonValue(QExtJsonValue::Undefined));
    QCOMPARE(nullArray.first(), QExtJsonValue(QExtJsonValue::Undefined));
    QCOMPARE(nullArray.last(), QExtJsonValue(QExtJsonValue::Undefined));
    nullArray.removeAt(0);
    nullArray.removeAt(-1);
}

void tst_qextJson::nullObject()
{
    QExtJsonObject nullObject;
    QExtJsonObject nonNull;
    nonNull.insert(QLatin1String("foo"), QLatin1String("bar"));

    QCOMPARE(nullObject, QExtJsonObject());
    QVERIFY(nullObject != nonNull);
    QVERIFY(nonNull != nullObject);

    QCOMPARE(nullObject.size(), 0);
    QCOMPARE(nullObject.keys(), QStringList());
    nullObject.remove("foo");
    QCOMPARE(nullObject, QExtJsonObject());
    QCOMPARE(nullObject.take("foo"), QExtJsonValue(QExtJsonValue::Undefined));
    QCOMPARE(nullObject.contains("foo"), false);

    nullObject.insert("foo", QString("bar"));
    nullObject.remove("foo");

    QCOMPARE(nullObject.size(), 0);
    QCOMPARE(nullObject.keys(), QStringList());
    nullObject.remove("foo");
    QCOMPARE(nullObject, QExtJsonObject());
    QCOMPARE(nullObject.take("foo"), QExtJsonValue(QExtJsonValue::Undefined));
    QCOMPARE(nullObject.contains("foo"), false);
}

void tst_qextJson::constNullObject()
{
    const QExtJsonObject nullObject;
    QExtJsonObject nonNull;
    nonNull.insert(QLatin1String("foo"), QLatin1String("bar"));

    QCOMPARE(nullObject, QExtJsonObject());
    QVERIFY(nullObject != nonNull);
    QVERIFY(nonNull != nullObject);

    QCOMPARE(nullObject.size(), 0);
    QCOMPARE(nullObject.keys(), QStringList());
    QCOMPARE(nullObject, QExtJsonObject());
    QCOMPARE(nullObject.contains("foo"), false);
    QCOMPARE(nullObject["foo"], QExtJsonValue(QExtJsonValue::Undefined));
}

void tst_qextJson::keySorting_data()
{
    QTest::addColumn<QString>("json");
    QTest::addColumn<QStringList>("sortedKeys");

    QStringList list = {"A", "B"};
    QTest::newRow("sorted-ascii-2") << R"({ "A": false, "B": true })" << list;
    const char *json = "{ \"B\": true, \"A\": false }";
    QTest::newRow("unsorted-ascii-2") << json << list;

    list = QStringList{"A", "B", "C", "D", "E"};
    QTest::newRow("sorted-ascii-5") << R"({"A": 1, "B": 2, "C": 3, "D": 4, "E": 5})" << list;
    QTest::newRow("unsorted-ascii-5") << R"({"A": 1, "C": 3, "D": 4, "B": 2, "E": 5})" << list;
    QTest::newRow("inverse-sorted-ascii-5") << R"({"E": 5, "D": 4, "C": 3, "B": 2, "A": 1})" << list;

    list = QStringList{"á", "é", "í", "ó", "ú"};
    QTest::newRow("sorted-latin1") << R"({"á": 1, "é": 2, "í": 3, "ó": 4, "ú": 5})" << list;
    QTest::newRow("unsorted-latin1") << R"({"á": 1, "í": 3, "ó": 4, "é": 2, "ú": 5})" << list;
    QTest::newRow("inverse-sorted-latin1") << R"({"ú": 5, "ó": 4, "í": 3, "é": 2, "á": 1})" << list;

    QTest::newRow("sorted-escaped-latin1") << R"({"\u00e1": 1, "\u00e9": 2, "\u00ed": 3, "\u00f3": 4, "\u00fa": 5})" << list;
    QTest::newRow("unsorted-escaped-latin1") << R"({"\u00e1": 1, "\u00ed": 3, "\u00f3": 4, "\u00e9": 2, "\u00fa": 5})" << list;
    QTest::newRow("inverse-sorted-escaped-latin1") << R"({"\u00fa": 5, "\u00f3": 4, "\u00ed": 3, "\u00e9": 2, "\u00e1": 1})" << list;

    list = QStringList{"A", "α", "Я", "€", "测"};
    QTest::newRow("sorted") << R"({"A": 1, "α": 2, "Я": 3, "€": 4, "测": 5})" << list;
    QTest::newRow("unsorted") << R"({"A": 1, "Я": 3, "€": 4, "α": 2, "测": 5})" << list;
    QTest::newRow("inverse-sorted") << R"({"测": 5, "€": 4, "Я": 3, "α": 2, "A": 1})" << list;

    QTest::newRow("sorted-escaped") << R"({"A": 1, "\u03b1": 2, "\u042f": 3, "\u20ac": 4, "\u6d4b": 5})" << list;
    QTest::newRow("unsorted-escaped") << R"({"A": 1, "\u042f": 3, "\u20ac": 4, "\u03b1": 2, "\u6d4b": 5})" << list;
    QTest::newRow("inverse-sorted-escaped") << R"({"\u6d4b": 5, "\u20ac": 4, "\u042f": 3, "\u03b1": 2, "A": 1})" << list;
}

void tst_qextJson::keySorting()
{
    QFETCH(QString, json);
    QFETCH(QStringList, sortedKeys);
    QExtJsonDocument doc = QExtJsonDocument::fromJson(json.toUtf8());

    QCOMPARE(doc.isObject(), true);

    QExtJsonObject o = doc.object();
    QCOMPARE(o.size(), sortedKeys.size());
    QCOMPARE(o.keys(), sortedKeys);
    QExtJsonObject::const_iterator it = o.constBegin();
    QStringList::const_iterator it2 = sortedKeys.constBegin();
    for ( ; it != o.constEnd(); ++it, ++it2)
        QCOMPARE(it.key(), *it2);
}

void tst_qextJson::undefinedValues()
{
    QExtJsonObject object;
    object.insert("Key", QExtJsonValue(QExtJsonValue::Undefined));
    QCOMPARE(object.size(), 0);
    object["Key"] = QExtJsonValue(QExtJsonValue::Undefined);
    QCOMPARE(object.size(), 0);

    object.insert("Key", QLatin1String("Value"));
    QCOMPARE(object.size(), 1);
    QCOMPARE(object.value("Key").type(), QExtJsonValue::String);
    QCOMPARE(object.value("foo").type(), QExtJsonValue::Undefined);
    object.insert("Key", QExtJsonValue(QExtJsonValue::Undefined));
    QCOMPARE(object.size(), 0);
    QCOMPARE(object.value("Key").type(), QExtJsonValue::Undefined);

    QExtJsonArray array;
    array.append(QExtJsonValue(QExtJsonValue::Undefined));
    QCOMPARE(array.size(), 1);
    QCOMPARE(array.at(0).type(), QExtJsonValue::Null);

    QCOMPARE(array.at(1).type(), QExtJsonValue::Undefined);
    QCOMPARE(array.at(-1).type(), QExtJsonValue::Undefined);
}

void tst_qextJson::fromVariant_data()
{
    QTest::addColumn<QVariant>("variant");
    QTest::addColumn<QExtJsonValue>("jsonvalue");

    bool boolValue = true;
    int intValue = -1;
    uint uintValue = 1;
    qlonglong longlongValue = -2;
    qulonglong ulonglongValue = 2;
    float floatValue = 3.3f;
    double doubleValue = 4.4;
    QString stringValue("str");

    QStringList stringList;
    stringList.append(stringValue);
    stringList.append("str2");
    QExtJsonArray jsonArray_string;
    jsonArray_string.append(stringValue);
    jsonArray_string.append("str2");

    QVariantList variantList;
    variantList.append(boolValue);
    variantList.append(floatValue);
    variantList.append(doubleValue);
    variantList.append(stringValue);
    variantList.append(stringList);
    variantList.append(QVariant::fromValue(nullptr));
    variantList.append(QVariant());
    QExtJsonArray jsonArray_variant;
    jsonArray_variant.append(boolValue);
    jsonArray_variant.append(floatValue);
    jsonArray_variant.append(doubleValue);
    jsonArray_variant.append(stringValue);
    jsonArray_variant.append(jsonArray_string);
    jsonArray_variant.append(QExtJsonValue(QExtJsonValue::Null));
    jsonArray_variant.append(QExtJsonValue());

    QVariantMap variantMap;
    variantMap["bool"] = boolValue;
    variantMap["float"] = floatValue;
    variantMap["string"] = stringValue;
    variantMap["array"] = variantList;
    variantMap["null"] = QVariant::fromValue(nullptr);
    variantMap["default"] = QVariant();
    QVariantHash variantHash;
    variantHash["bool"] = boolValue;
    variantHash["float"] = floatValue;
    variantHash["string"] = stringValue;
    variantHash["array"] = variantList;
    variantHash["null"] = QVariant::fromValue(nullptr);
    variantHash["default"] = QVariant();
    QExtJsonObject jsonObject;
    jsonObject["bool"] = boolValue;
    jsonObject["float"] = floatValue;
    jsonObject["string"] = stringValue;
    jsonObject["array"] = jsonArray_variant;
    jsonObject["null"] = QExtJsonValue::Null;
    jsonObject["default"] = QExtJsonValue();

    QTest::newRow("default") << QVariant() <<  QExtJsonValue();
    QTest::newRow("nullptr") << QVariant::fromValue(nullptr) <<  QExtJsonValue(QExtJsonValue::Null);
    QTest::newRow("bool") << QVariant(boolValue) <<  QExtJsonValue(boolValue);
    QTest::newRow("int") << QVariant(intValue) <<  QExtJsonValue(intValue);
    QTest::newRow("uint") << QVariant(uintValue) <<  QExtJsonValue(static_cast<qint64>(uintValue));
    QTest::newRow("longlong") << QVariant(longlongValue) <<  QExtJsonValue(longlongValue);
    QTest::newRow("ulonglong") << QVariant(ulonglongValue) <<  QExtJsonValue(static_cast<double>(ulonglongValue));
    QTest::newRow("float") << QVariant(floatValue) <<  QExtJsonValue(floatValue);
    QTest::newRow("double") << QVariant(doubleValue) <<  QExtJsonValue(doubleValue);
    QTest::newRow("string") << QVariant(stringValue) <<  QExtJsonValue(stringValue);
    QTest::newRow("stringList") << QVariant(stringList) <<  QExtJsonValue(jsonArray_string);
    QTest::newRow("variantList") << QVariant(variantList) <<  QExtJsonValue(jsonArray_variant);
    QTest::newRow("variantMap") << QVariant(variantMap) <<  QExtJsonValue(jsonObject);
    QTest::newRow("variantHash") << QVariant(variantHash) <<  QExtJsonValue(jsonObject);
}

// replaces QVariant() with QVariant(nullptr)
static QVariant normalizedVariant(const QVariant &v)
{
    switch (v.userType()) {
    case QMetaType::UnknownType:
        return QVariant::fromValue(nullptr);
    case QMetaType::QVariantList: {
        const QVariantList in = v.toList();
        QVariantList out;
        out.reserve(in.size());
        for (const QVariant &v : in)
            out << normalizedVariant(v);
        return out;
    }
    case QMetaType::QStringList: {
        const QStringList in = v.toStringList();
        QVariantList out;
        out.reserve(in.size());
        for (const QString &v : in)
            out << v;
        return out;
    }
    case QMetaType::QVariantMap: {
        const QVariantMap in = v.toMap();
        QVariantMap out;
        for (auto it = in.begin(); it != in.end(); ++it)
            out.insert(it.key(), normalizedVariant(it.value()));
        return out;
    }
    case QMetaType::QVariantHash: {
        const QVariantHash in = v.toHash();
        QVariantMap out;
        for (auto it = in.begin(); it != in.end(); ++it)
            out.insert(it.key(), normalizedVariant(it.value()));
        return out;
    }

    default:
        return v;
    }
}

void tst_qextJson::fromVariant()
{
    QFETCH( QVariant, variant );
    QFETCH( QExtJsonValue, jsonvalue );

    QCOMPARE(QExtJsonValue::fromVariant(variant), jsonvalue);
    QCOMPARE(normalizedVariant(variant).toJsonValue(), jsonvalue);
}

void tst_qextJson::fromVariantSpecial_data()
{
    QTest::addColumn<QVariant>("variant");
    QTest::addColumn<QExtJsonValue>("jsonvalue");

    // Qt types with special encoding
    QTest::newRow("url") << QVariant(QUrl("https://example.com/\xc2\xa9 "))
                         << QExtJsonValue("https://example.com/%C2%A9%20");
    QTest::newRow("uuid") << QVariant(QUuid(0x40c01df6, 0x1ad5, 0x4762, 0x9c, 0xfe, 0xfd, 0xba, 0xfa, 0xb5, 0xde, 0xf8))
                          << QExtJsonValue("40c01df6-1ad5-4762-9cfe-fdbafab5def8");
}

void tst_qextJson::fromVariantSpecial()
{
    QFETCH( QVariant, variant );
    QFETCH( QExtJsonValue, jsonvalue );

    QCOMPARE(QExtJsonValue::fromVariant(variant), jsonvalue);
}

void tst_qextJson::toVariant_data()
{
    fromVariant_data();
}

void tst_qextJson::toVariant()
{
    QFETCH( QVariant, variant );
    QFETCH( QExtJsonValue, jsonvalue );

    QCOMPARE(jsonvalue.toVariant(), normalizedVariant(variant));
}

void tst_qextJson::fromVariantMap()
{
    QVariantMap map;
    map.insert(QLatin1String("key1"), QLatin1String("value1"));
    map.insert(QLatin1String("key2"), QLatin1String("value2"));
    QExtJsonObject object = QExtJsonObject::fromVariantMap(map);
    QCOMPARE(object.size(), 2);
    QCOMPARE(object.value(QLatin1String("key1")), QExtJsonValue(QLatin1String("value1")));
    QCOMPARE(object.value(QLatin1String("key2")), QExtJsonValue(QLatin1String("value2")));

    QVariantList list;
    list.append(true);
    list.append(QVariant());
    list.append(999.);
    list.append(QLatin1String("foo"));
    map.insert("list", list);
    object = QExtJsonObject::fromVariantMap(map);
    QCOMPARE(object.size(), 3);
    QCOMPARE(object.value(QLatin1String("key1")), QExtJsonValue(QLatin1String("value1")));
    QCOMPARE(object.value(QLatin1String("key2")), QExtJsonValue(QLatin1String("value2")));
    QCOMPARE(object.value(QLatin1String("list")).type(), QExtJsonValue::Array);
    QExtJsonArray array = object.value(QLatin1String("list")).toArray();
    QCOMPARE(array.size(), 4);
    QCOMPARE(array.at(0).type(), QExtJsonValue::Bool);
    QCOMPARE(array.at(0).toBool(), true);
    QCOMPARE(array.at(1).type(), QExtJsonValue::Null);
    QCOMPARE(array.at(2).type(), QExtJsonValue::Double);
    QCOMPARE(array.at(2).toDouble(), 999.);
    QCOMPARE(array.at(3).type(), QExtJsonValue::String);
    QCOMPARE(array.at(3).toString(), QLatin1String("foo"));
}

void tst_qextJson::fromVariantHash()
{
    QVariantHash map;
    map.insert(QLatin1String("key1"), QLatin1String("value1"));
    map.insert(QLatin1String("key2"), QLatin1String("value2"));
    QExtJsonObject object = QExtJsonObject::fromVariantHash(map);
    QCOMPARE(object.size(), 2);
    QCOMPARE(object.value(QLatin1String("key1")), QExtJsonValue(QLatin1String("value1")));
    QCOMPARE(object.value(QLatin1String("key2")), QExtJsonValue(QLatin1String("value2")));
}

void tst_qextJson::toVariantMap()
{
    QCOMPARE(QMetaType::Type(QExtJsonValue(QExtJsonObject()).toVariant().type()), QMetaType::QVariantMap); // QTBUG-32524

    QExtJsonObject object;
    QVariantMap map = object.toVariantMap();
    QVERIFY(map.isEmpty());

    object.insert("Key", QString("Value"));
    object.insert("null", QExtJsonValue());
    QExtJsonArray array;
    array.append(true);
    array.append(999.);
    array.append(QLatin1String("string"));
    array.append(QExtJsonValue::Null);
    object.insert("Array", array);

    map = object.toVariantMap();

    QCOMPARE(map.size(), 3);
    QCOMPARE(map.value("Key"), QVariant(QString("Value")));
    QCOMPARE(map.value("null"), QVariant::fromValue(nullptr));
    QCOMPARE(map.value("Array").type(), QVariant::List);
    QVariantList list = map.value("Array").toList();
    QCOMPARE(list.size(), 4);
    QCOMPARE(list.at(0), QVariant(true));
    QCOMPARE(list.at(1), QVariant(999.));
    QCOMPARE(list.at(2), QVariant(QLatin1String("string")));
    QCOMPARE(list.at(3), QVariant::fromValue(nullptr));
}

void tst_qextJson::toVariantHash()
{
    QExtJsonObject object;
    QVariantHash hash = object.toVariantHash();
    QVERIFY(hash.isEmpty());

    object.insert("Key", QString("Value"));
    object.insert("null", QExtJsonValue::Null);
    QExtJsonArray array;
    array.append(true);
    array.append(999.);
    array.append(QLatin1String("string"));
    array.append(QExtJsonValue::Null);
    object.insert("Array", array);

    hash = object.toVariantHash();

    QCOMPARE(hash.size(), 3);
    QCOMPARE(hash.value("Key"), QVariant(QString("Value")));
    QCOMPARE(hash.value("null"), QVariant::fromValue(nullptr));
    QCOMPARE(hash.value("Array").type(), QVariant::List);
    QVariantList list = hash.value("Array").toList();
    QCOMPARE(list.size(), 4);
    QCOMPARE(list.at(0), QVariant(true));
    QCOMPARE(list.at(1), QVariant(999.));
    QCOMPARE(list.at(2), QVariant(QLatin1String("string")));
    QCOMPARE(list.at(3), QVariant::fromValue(nullptr));
}

void tst_qextJson::toVariantList()
{
    QCOMPARE(QMetaType::Type(QExtJsonValue(QExtJsonArray()).toVariant().type()), QMetaType::QVariantList); // QTBUG-32524

    QExtJsonArray array;
    QVariantList list = array.toVariantList();
    QVERIFY(list.isEmpty());

    array.append(QString("Value"));
    array.append(QExtJsonValue());
    QExtJsonArray inner;
    inner.append(true);
    inner.append(999.);
    inner.append(QLatin1String("string"));
    inner.append(QExtJsonValue());
    array.append(inner);

    list = array.toVariantList();

    QCOMPARE(list.size(), 3);
    QCOMPARE(list[0], QVariant(QString("Value")));
    QCOMPARE(list[1], QVariant::fromValue(nullptr));
    QCOMPARE(list[2].type(), QVariant::List);
    QVariantList vlist = list[2].toList();
    QCOMPARE(vlist.size(), 4);
    QCOMPARE(vlist.at(0), QVariant(true));
    QCOMPARE(vlist.at(1), QVariant(999.));
    QCOMPARE(vlist.at(2), QVariant(QLatin1String("string")));
    QCOMPARE(vlist.at(3), QVariant::fromValue(nullptr));
}

void tst_qextJson::toJson()
{
    // Test QExtJsonDocument::Indented format
    {
        QExtJsonObject object;
        object.insert("\\Key\n", QString("Value"));
        object.insert("null", QExtJsonValue());
        QExtJsonArray array;
        array.append(true);
        array.append(999.);
        array.append(QLatin1String("string"));
        array.append(QExtJsonValue());
        array.append(QLatin1String("\\\a\n\r\b\tabcABC\""));
        object.insert("Array", array);

        QByteArray json = QExtJsonDocument(object).toJson();

        QByteArray expected =
            "{\n"
            "    \"Array\": [\n"
            "        true,\n"
            "        999,\n"
            "        \"string\",\n"
            "        null,\n"
            "        \"\\\\\\u0007\\n\\r\\b\\tabcABC\\\"\"\n"
            "    ],\n"
            "    \"\\\\Key\\n\": \"Value\",\n"
            "    \"null\": null\n"
            "}\n";
        QCOMPARE(json, expected);

        QExtJsonDocument doc;
        doc.setObject(object);
        json = doc.toJson();
        QCOMPARE(json, expected);

        doc.setArray(array);
        json = doc.toJson();
        expected =
            "[\n"
            "    true,\n"
            "    999,\n"
            "    \"string\",\n"
            "    null,\n"
            "    \"\\\\\\u0007\\n\\r\\b\\tabcABC\\\"\"\n"
            "]\n";
        QCOMPARE(json, expected);
    }

    // Test QExtJsonDocument::Compact format
    {
        QExtJsonObject object;
        object.insert("\\Key\n", QString("Value"));
        object.insert("null", QExtJsonValue());
        QExtJsonArray array;
        array.append(true);
        array.append(999.);
        array.append(QLatin1String("string"));
        array.append(QExtJsonValue());
        array.append(QLatin1String("\\\a\n\r\b\tabcABC\""));
        object.insert("Array", array);

        QByteArray json = QExtJsonDocument(object).toJson(QExtJsonDocument::Compact);
        QByteArray expected =
            "{\"Array\":[true,999,\"string\",null,\"\\\\\\u0007\\n\\r\\b\\tabcABC\\\"\"],\"\\\\Key\\n\":\"Value\",\"null\":null}";
        QCOMPARE(json, expected);

        QExtJsonDocument doc;
        doc.setObject(object);
        json = doc.toJson(QExtJsonDocument::Compact);
        QCOMPARE(json, expected);

        doc.setArray(array);
        json = doc.toJson(QExtJsonDocument::Compact);
        expected = "[true,999,\"string\",null,\"\\\\\\u0007\\n\\r\\b\\tabcABC\\\"\"]";
        QCOMPARE(json, expected);
    }
}

void tst_qextJson::toJsonSillyNumericValues()
{
    QExtJsonObject object;
    QExtJsonArray array;
    array.append(QExtJsonValue(std::numeric_limits<double>::infinity()));  // encode to: null
    array.append(QExtJsonValue(-std::numeric_limits<double>::infinity())); // encode to: null
    array.append(QExtJsonValue(std::numeric_limits<double>::quiet_NaN())); // encode to: null
    object.insert("Array", array);

    QByteArray json = QExtJsonDocument(object).toJson();

    QByteArray expected =
        "{\n"
        "    \"Array\": [\n"
        "        null,\n"
        "        null,\n"
        "        null\n"
        "    ]\n"
        "}\n";

    QCOMPARE(json, expected);

    QExtJsonDocument doc;
    doc.setObject(object);
    json = doc.toJson();
    QCOMPARE(json, expected);
}

void tst_qextJson::toJsonLargeNumericValues()
{
    QExtJsonObject object;
    QExtJsonArray array;
    array.append(QExtJsonValue(1.234567)); // actual precision bug in Qt 5.0.0
    array.append(QExtJsonValue(1.7976931348623157e+308)); // JS Number.MAX_VALUE
    array.append(QExtJsonValue(std::numeric_limits<double>::min()));
    array.append(QExtJsonValue(std::numeric_limits<double>::max()));
    array.append(QExtJsonValue(std::numeric_limits<double>::epsilon()));
    array.append(QExtJsonValue(0.0));
    array.append(QExtJsonValue(-std::numeric_limits<double>::min()));
    array.append(QExtJsonValue(-std::numeric_limits<double>::max()));
    array.append(QExtJsonValue(-std::numeric_limits<double>::epsilon()));
    array.append(QExtJsonValue(-0.0));
    array.append(QExtJsonValue(9007199254740992LL));  // JS Number max integer
    array.append(QExtJsonValue(-9007199254740992LL)); // JS Number min integer
    object.insert("Array", array);

    QByteArray json = QExtJsonDocument(object).toJson();

    QByteArray expected =
        "{\n"
        "    \"Array\": [\n"
        "        1.234567,\n"
        "        1.7976931348623157e+308,\n"
#ifdef QT_NO_DOUBLECONVERSION // "shortest" double conversion is not very short then
        "        2.2250738585072014e-308,\n"
        "        1.7976931348623157e+308,\n"
        "        2.2204460492503131e-16,\n"
        "        0,\n"
        "        -2.2250738585072014e-308,\n"
        "        -1.7976931348623157e+308,\n"
        "        -2.2204460492503131e-16,\n"
#else
        "        2.2250738585072014e-308,\n"
        "        1.7976931348623157e+308,\n"
        "        2.220446049250313e-16,\n"
        "        0,\n"
        "        -2.2250738585072014e-308,\n"
        "        -1.7976931348623157e+308,\n"
        "        -2.220446049250313e-16,\n"
#endif
        "        0,\n"
        "        9007199254740992,\n"
        "        -9007199254740992\n"
        "    ]\n"
        "}\n";

    QCOMPARE(json, expected);

    QExtJsonDocument doc;
    doc.setObject(object);
    json = doc.toJson();
    QCOMPARE(json, expected);
}

void tst_qextJson::toJsonDenormalValues()
{
    if constexpr (std::numeric_limits<double>::has_denorm == std::denorm_present) {
        QExtJsonObject object;
        QExtJsonArray array;
        array.append(QExtJsonValue(5e-324));                  // JS Number.MIN_VALUE
        array.append(QExtJsonValue(std::numeric_limits<double>::denorm_min()));
        array.append(QExtJsonValue(-std::numeric_limits<double>::denorm_min()));
        object.insert("Array", array);

        QByteArray json = QExtJsonDocument(object).toJson();
        QByteArray expected =
            "{\n"
            "    \"Array\": [\n"
#ifdef QT_NO_DOUBLECONVERSION // "shortest" double conversion is not very short then
            "        4.9406564584124654e-324,\n"
            "        4.9406564584124654e-324,\n"
            "        -4.9406564584124654e-324\n"
#else
            "        5e-324,\n"
            "        5e-324,\n"
            "        -5e-324\n"
#endif
            "    ]\n"
            "}\n";

        QCOMPARE(json, expected);
        QExtJsonDocument doc;
        doc.setObject(object);
        json = doc.toJson();
        QCOMPARE(json, expected);
    } else {
        QSKIP("Skipping 'denorm' as this type lacks denormals on this system");
    }
}

void tst_qextJson::fromJson()
{
    {
        QByteArray json = "[\n    true\n]\n";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json);
        QVERIFY(!doc.isEmpty());
        QCOMPARE(doc.isArray(), true);
        QCOMPARE(doc.isObject(), false);
        QExtJsonArray array = doc.array();
        QCOMPARE(array.size(), 1);
        QCOMPARE(array.at(0).type(), QExtJsonValue::Bool);
        QCOMPARE(array.at(0).toBool(), true);
        QCOMPARE(doc.toJson(), json);
    }
    {
        //regression test: test if unicode_control_characters are correctly decoded
        QByteArray json = "[\n    \"" UNICODE_NON_CHARACTER "\"\n]\n";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json);
        QVERIFY(!doc.isEmpty());
        QCOMPARE(doc.isArray(), true);
        QCOMPARE(doc.isObject(), false);
        QExtJsonArray array = doc.array();
        QCOMPARE(array.size(), 1);
        QCOMPARE(array.at(0).type(), QExtJsonValue::String);
        QCOMPARE(array.at(0).toString(), QString::fromUtf8(UNICODE_NON_CHARACTER));
        QCOMPARE(doc.toJson(), json);
    }
    {
        QByteArray json = "[]";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json);
        QVERIFY(!doc.isEmpty());
        QCOMPARE(doc.isArray(), true);
        QCOMPARE(doc.isObject(), false);
        QExtJsonArray array = doc.array();
        QCOMPARE(array.size(), 0);
    }
    {
        QByteArray json = "{}";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json);
        QVERIFY(!doc.isEmpty());
        QCOMPARE(doc.isArray(), false);
        QCOMPARE(doc.isObject(), true);
        QExtJsonObject object = doc.object();
        QCOMPARE(object.size(), 0);
    }
    {
        QByteArray json = "{\n    \"Key\": true\n}\n";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json);
        QVERIFY(!doc.isEmpty());
        QCOMPARE(doc.isArray(), false);
        QCOMPARE(doc.isObject(), true);
        QExtJsonObject object = doc.object();
        QCOMPARE(object.size(), 1);
        QCOMPARE(object.value("Key"), QExtJsonValue(true));
        QCOMPARE(doc.toJson(), json);
    }
    {
        QByteArray json = "[ null, true, false, \"Foo\", 1, [], {} ]";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json);
        QVERIFY(!doc.isEmpty());
        QCOMPARE(doc.isArray(), true);
        QCOMPARE(doc.isObject(), false);
        QExtJsonArray array = doc.array();
        QCOMPARE(array.size(), 7);
        QCOMPARE(array.at(0).type(), QExtJsonValue::Null);
        QCOMPARE(array.at(1).type(), QExtJsonValue::Bool);
        QCOMPARE(array.at(1).toBool(), true);
        QCOMPARE(array.at(2).type(), QExtJsonValue::Bool);
        QCOMPARE(array.at(2).toBool(), false);
        QCOMPARE(array.at(3).type(), QExtJsonValue::String);
        QCOMPARE(array.at(3).toString(), QLatin1String("Foo"));
        QCOMPARE(array.at(4).type(), QExtJsonValue::Double);
        QCOMPARE(array.at(4).toDouble(), 1.);
        QCOMPARE(array.at(5).type(), QExtJsonValue::Array);
        QCOMPARE(array.at(5).toArray().size(), 0);
        QCOMPARE(array.at(6).type(), QExtJsonValue::Object);
        QCOMPARE(array.at(6).toObject().size(), 0);
    }
    {
        QByteArray json = "{ \"0\": null, \"1\": true, \"2\": false, \"3\": \"Foo\", \"4\": 1, \"5\": [], \"6\": {} }";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json);
        QVERIFY(!doc.isEmpty());
        QCOMPARE(doc.isArray(), false);
        QCOMPARE(doc.isObject(), true);
        QExtJsonObject object = doc.object();
        QCOMPARE(object.size(), 7);
        QCOMPARE(object.value("0").type(), QExtJsonValue::Null);
        QCOMPARE(object.value("1").type(), QExtJsonValue::Bool);
        QCOMPARE(object.value("1").toBool(), true);
        QCOMPARE(object.value("2").type(), QExtJsonValue::Bool);
        QCOMPARE(object.value("2").toBool(), false);
        QCOMPARE(object.value("3").type(), QExtJsonValue::String);
        QCOMPARE(object.value("3").toString(), QLatin1String("Foo"));
        QCOMPARE(object.value("4").type(), QExtJsonValue::Double);
        QCOMPARE(object.value("4").toDouble(), 1.);
        QCOMPARE(object.value("5").type(), QExtJsonValue::Array);
        QCOMPARE(object.value("5").toArray().size(), 0);
        QCOMPARE(object.value("6").type(), QExtJsonValue::Object);
        QCOMPARE(object.value("6").toObject().size(), 0);
    }
    {
        QByteArray compactJson = "{\"Array\": [true,999,\"string\",null,\"\\\\\\u0007\\n\\r\\b\\tabcABC\\\"\"],\"\\\\Key\\n\": \"Value\",\"null\": null}";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(compactJson);
        QVERIFY(!doc.isEmpty());
        QCOMPARE(doc.isArray(), false);
        QCOMPARE(doc.isObject(), true);
        QExtJsonObject object = doc.object();
        QCOMPARE(object.size(), 3);
        QCOMPARE(object.value("\\Key\n").isString(), true);
        QCOMPARE(object.value("\\Key\n").toString(), QString("Value"));
        QCOMPARE(object.value("null").isNull(), true);
        QCOMPARE(object.value("Array").isArray(), true);
        QExtJsonArray array = object.value("Array").toArray();
        QCOMPARE(array.size(), 5);
        QCOMPARE(array.at(0).isBool(), true);
        QCOMPARE(array.at(0).toBool(), true);
        QCOMPARE(array.at(1).isDouble(), true);
        QCOMPARE(array.at(1).toDouble(), 999.);
        QCOMPARE(array.at(2).isString(), true);
        QCOMPARE(array.at(2).toString(), QLatin1String("string"));
        QCOMPARE(array.at(3).isNull(), true);
        QCOMPARE(array.at(4).isString(), true);
        QCOMPARE(array.at(4).toString(), QLatin1String("\\\a\n\r\b\tabcABC\""));
    }
}

void tst_qextJson::fromJsonErrors()
{
    {
        QExtJsonParseError error;
        QByteArray json = "{\n    \n\n";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::UnterminatedObject);
        QCOMPARE(error.offset, 8);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "{\n    \"key\" 10\n";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::MissingNameSeparator);
        QCOMPARE(error.offset, 13);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "[\n    \n\n";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::UnterminatedArray);
        QCOMPARE(error.offset, 8);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "[\n   1, true\n\n";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::UnterminatedArray);
        QCOMPARE(error.offset, 14);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "[\n  1 true\n\n";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::MissingValueSeparator);
        QCOMPARE(error.offset, 7);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "[\n    nul";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::IllegalValue);
        QCOMPARE(error.offset, 7);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "[\n    nulzz";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::IllegalValue);
        QCOMPARE(error.offset, 10);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "[\n    tru";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::IllegalValue);
        QCOMPARE(error.offset, 7);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "[\n    trud]";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::IllegalValue);
        QCOMPARE(error.offset, 10);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "[\n    fal";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::IllegalValue);
        QCOMPARE(error.offset, 7);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "[\n    falsd]";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::IllegalValue);
        QCOMPARE(error.offset, 11);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "[\n    11111";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::TerminationByNumber);
        QCOMPARE(error.offset, 11);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "[\n    -1E10000]";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::IllegalNumber);
        QCOMPARE(error.offset, 14);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "[\n    -1e-10000]";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::IllegalNumber);
        QCOMPARE(error.offset, 15);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "[\n    \"\\u12\"]";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::IllegalEscapeSequence);
        QCOMPARE(error.offset, 11);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "[\n    \"foo" INVALID_UNICODE "bar\"]";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::IllegalUTF8String);
        QCOMPARE(error.offset, 12);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "[\n    \"";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::UnterminatedString);
        QCOMPARE(error.offset, 8);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "[\n    \"c" UNICODE_DJE "a\\u12\"]";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::IllegalEscapeSequence);
        QCOMPARE(error.offset, 15);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "[\n    \"c" UNICODE_DJE "a" INVALID_UNICODE "bar\"]";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::IllegalUTF8String);
        QCOMPARE(error.offset, 13);
    }
    {
        QExtJsonParseError error;
        QByteArray json = "[\n    \"c" UNICODE_DJE "a ]";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
        QVERIFY(doc.isEmpty());
        QCOMPARE(error.error, QExtJsonParseError::UnterminatedString);
        QCOMPARE(error.offset, 14);
    }
}

void tst_qextJson::parseNumbers()
{
    {
        // test number parsing
        struct Numbers {
            const char *str;
            int n;
        };
        Numbers numbers [] = {
            { "0", 0 },
            { "1", 1 },
            { "10", 10 },
            { "-1", -1 },
            { "100000", 100000 },
            { "-999", -999 }
        };
        int size = sizeof(numbers)/sizeof(Numbers);
        for (int i = 0; i < size; ++i) {
            QByteArray json = "[ ";
            json += numbers[i].str;
            json += " ]";
            QExtJsonDocument doc = QExtJsonDocument::fromJson(json);
            QVERIFY(!doc.isEmpty());
            QCOMPARE(doc.isArray(), true);
            QCOMPARE(doc.isObject(), false);
            QExtJsonArray array = doc.array();
            QCOMPARE(array.size(), 1);
            QExtJsonValue val = array.at(0);
            QCOMPARE(val.type(), QExtJsonValue::Double);
            QCOMPARE(val.toDouble(), (double)numbers[i].n);
        }
    }
    // test number parsing
    struct Numbers {
        const char *str;
        double n;
    };
    {
        Numbers numbers [] = {
            { "0", 0 },
            { "1", 1 },
            { "10", 10 },
            { "-1", -1 },
            { "100000", 100000 },
            { "-999", -999 },
            { "1.1", 1.1 },
            { "1e10", 1e10 },
            { "-1.1", -1.1 },
            { "-1e10", -1e10 },
            { "-1E10", -1e10 },
            { "1.1e10", 1.1e10 },
            { "1.1e308", 1.1e308 },
            { "-1.1e308", -1.1e308 },
            { "1.1e+308", 1.1e+308 },
            { "-1.1e+308", -1.1e+308 },
            { "1.e+308", 1.e+308 },
            { "-1.e+308", -1.e+308 }
        };
        int size = sizeof(numbers)/sizeof(Numbers);
        for (int i = 0; i < size; ++i) {
            QByteArray json = "[ ";
            json += numbers[i].str;
            json += " ]";
            QExtJsonDocument doc = QExtJsonDocument::fromJson(json);
            QVERIFY(!doc.isEmpty());
            QCOMPARE(doc.isArray(), true);
            QCOMPARE(doc.isObject(), false);
            QExtJsonArray array = doc.array();
            QCOMPARE(array.size(), 1);
            QExtJsonValue val = array.at(0);
            QCOMPARE(val.type(), QExtJsonValue::Double);
            QCOMPARE(val.toDouble(), numbers[i].n);
        }
    }
    if constexpr (std::numeric_limits<double>::has_denorm == std::denorm_present) {
        Numbers numbers [] = {
            { "1.1e-308", 1.1e-308 },
            { "-1.1e-308", -1.1e-308 }
        };
        int size = sizeof(numbers)/sizeof(Numbers);
        for (int i = 0; i < size; ++i) {
            QByteArray json = "[ ";
            json += numbers[i].str;
            json += " ]";
            QExtJsonDocument doc = QExtJsonDocument::fromJson(json);
            QVERIFY(!doc.isEmpty());
            QCOMPARE(doc.isArray(), true);
            QCOMPARE(doc.isObject(), false);
            QExtJsonArray array = doc.array();
            QCOMPARE(array.size(), 1);
            QExtJsonValue val = array.at(0);
            QCOMPARE(val.type(), QExtJsonValue::Double);
            QCOMPARE(val.toDouble(), numbers[i].n);
        }
    } else {
        qInfo("Skipping denormal test as this system's double type lacks support");
    }
}

void tst_qextJson::parseStrings()
{
    const char *strings [] =
        {
            "Foo",
            "abc\\\"abc",
            "abc\\\\abc",
            "abc\\babc",
            "abc\\fabc",
            "abc\\nabc",
            "abc\\rabc",
            "abc\\tabc",
            "abc\\u0019abc",
            "abc" UNICODE_DJE "abc",
            UNICODE_NON_CHARACTER
        };
    int size = sizeof(strings)/sizeof(const char *);

    for (int i = 0; i < size; ++i) {
        QByteArray json = "[\n    \"";
        json += strings[i];
        json += "\"\n]\n";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json);
        QVERIFY(!doc.isEmpty());
        QCOMPARE(doc.isArray(), true);
        QCOMPARE(doc.isObject(), false);
        QExtJsonArray array = doc.array();
        QCOMPARE(array.size(), 1);
        QExtJsonValue val = array.at(0);
        QCOMPARE(val.type(), QExtJsonValue::String);

        QCOMPARE(doc.toJson(), json);
    }

    struct Pairs {
        const char *in;
        const char *out;
    };
    Pairs pairs [] = {
        { "abc\\/abc", "abc/abc" },
        { "abc\\u0402abc", "abc" UNICODE_DJE "abc" },
        { "abc\\u0065abc", "abceabc" },
        { "abc\\uFFFFabc", "abc" UNICODE_NON_CHARACTER "abc" }
    };
    size = sizeof(pairs)/sizeof(Pairs);

    for (int i = 0; i < size; ++i) {
        QByteArray json = "[\n    \"";
        json += pairs[i].in;
        json += "\"\n]\n";
        QByteArray out = "[\n    \"";
        out += pairs[i].out;
        out += "\"\n]\n";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json);
        QVERIFY(!doc.isEmpty());
        QCOMPARE(doc.isArray(), true);
        QCOMPARE(doc.isObject(), false);
        QExtJsonArray array = doc.array();
        QCOMPARE(array.size(), 1);
        QExtJsonValue val = array.at(0);
        QCOMPARE(val.type(), QExtJsonValue::String);

        QCOMPARE(doc.toJson(), out);
    }

}

void tst_qextJson::parseDuplicateKeys()
{
    const char *json = "{ \"B\": true, \"A\": null, \"B\": false }";

    QExtJsonDocument doc = QExtJsonDocument::fromJson(json);
    QCOMPARE(doc.isObject(), true);

    QExtJsonObject o = doc.object();
    QCOMPARE(o.size(), 2);
    QExtJsonObject::const_iterator it = o.constBegin();
    QCOMPARE(it.key(), QLatin1String("A"));
    QCOMPARE(it.value(), QExtJsonValue());
    ++it;
    QCOMPARE(it.key(), QLatin1String("B"));
    QCOMPARE(it.value(), QExtJsonValue(false));
}

void tst_qextJson::testParser()
{
    QFile file(testDataDir + "/test.json");
    file.open(QFile::ReadOnly);
    QByteArray testJson = file.readAll();

    QExtJsonDocument doc = QExtJsonDocument::fromJson(testJson);
    QVERIFY(!doc.isEmpty());
}

void tst_qextJson::assignToDocument()
{
    {
        const char *json = "{ \"inner\": { \"key\": true } }";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json);

        QExtJsonObject o = doc.object();
        QExtJsonValue inner = o.value("inner");

        QExtJsonDocument innerDoc(inner.toObject());

        QVERIFY(innerDoc != doc);
        QCOMPARE(innerDoc.object(), inner.toObject());
    }
    {
        const char *json = "[ [ true ] ]";
        QExtJsonDocument doc = QExtJsonDocument::fromJson(json);

        QExtJsonArray a = doc.array();
        QExtJsonValue inner = a.at(0);

        QExtJsonDocument innerDoc(inner.toArray());

        QVERIFY(innerDoc != doc);
        QCOMPARE(innerDoc.array(), inner.toArray());
    }
}


void tst_qextJson::testDuplicateKeys()
{
    QExtJsonObject obj;
    obj.insert(QLatin1String("foo"), QLatin1String("bar"));
    obj.insert(QLatin1String("foo"), QLatin1String("zap"));
    QCOMPARE(obj.size(), 1);
    QCOMPARE(obj.value(QLatin1String("foo")).toString(), QLatin1String("zap"));
}

void tst_qextJson::testCompaction()
{
    // modify object enough times to trigger compactionCounter
    // and make sure the data is still valid
    QExtJsonObject obj;
    for (int i = 0; i < 33; ++i) {
        obj.remove(QLatin1String("foo"));
        obj.insert(QLatin1String("foo"), QLatin1String("bar"));
    }
    QCOMPARE(obj.size(), 1);
    QCOMPARE(obj.value(QLatin1String("foo")).toString(), QLatin1String("bar"));
}

void tst_qextJson::testDebugStream()
{
    {
        // QExtJsonObject

        QExtJsonObject object;
        QTest::ignoreMessage(QtDebugMsg, "QExtJsonObject()");
        qDebug() << object;

        object.insert(QLatin1String("foo"), QLatin1String("bar"));
        QTest::ignoreMessage(QtDebugMsg, "QExtJsonObject({\"foo\":\"bar\"})");
        qDebug() << object;
    }

    {
        // QExtJsonArray

        QExtJsonArray array;
        QTest::ignoreMessage(QtDebugMsg, "QExtJsonArray()");
        qDebug() << array;

        array.append(1);
        array.append(QLatin1String("foo"));
        QTest::ignoreMessage(QtDebugMsg, "QExtJsonArray([1,\"foo\"])");
        qDebug() << array;
    }

    {
        // QExtJsonDocument

        QExtJsonDocument doc;
        QTest::ignoreMessage(QtDebugMsg, "QExtJsonDocument()");
        qDebug() << doc;

        QExtJsonObject object;
        object.insert(QLatin1String("foo"), QLatin1String("bar"));
        doc.setObject(object);
        QTest::ignoreMessage(QtDebugMsg, "QExtJsonDocument({\"foo\":\"bar\"})");
        qDebug() << doc;

        QExtJsonArray array;
        array.append(1);
        array.append(QLatin1String("foo"));
        QTest::ignoreMessage(QtDebugMsg, "QExtJsonDocument([1,\"foo\"])");
        doc.setArray(array);
        qDebug() << doc;
    }

    {
        // QExtJsonValue

        QExtJsonValue value;

        QTest::ignoreMessage(QtDebugMsg, "QExtJsonValue(null)");
        qDebug() << value;

        value = QExtJsonValue(true); // bool
        QTest::ignoreMessage(QtDebugMsg, "QExtJsonValue(bool, true)");
        qDebug() << value;

        value = QExtJsonValue((double)4.2); // double
        QTest::ignoreMessage(QtDebugMsg, "QExtJsonValue(double, 4.2)");
        qDebug() << value;

        value = QExtJsonValue((int)42); // int
        QTest::ignoreMessage(QtDebugMsg, "QExtJsonValue(double, 42)");
        qDebug() << value;

        value = QExtJsonValue(QLatin1String("foo")); // string
        QTest::ignoreMessage(QtDebugMsg, "QExtJsonValue(string, \"foo\")");
        qDebug() << value;

        QExtJsonArray array;
        array.append(1);
        array.append(QLatin1String("foo"));
        value = QExtJsonValue(array); // array
        QTest::ignoreMessage(QtDebugMsg, "QExtJsonValue(array, QExtJsonArray([1,\"foo\"]))");
        qDebug() << value;

        QExtJsonObject object;
        object.insert(QLatin1String("foo"), QLatin1String("bar"));
        value = QExtJsonValue(object); // object
        QTest::ignoreMessage(QtDebugMsg, "QExtJsonValue(object, QExtJsonObject({\"foo\":\"bar\"}))");
        qDebug() << value;
    }
}

void tst_qextJson::parseEscapes_data()
{
    QTest::addColumn<QByteArray>("json");
    QTest::addColumn<QString>("result");

    auto addUnicodeRow = [](char32_t u) {
        char buf[32];   // more than enough
        char *ptr = buf;
        const QString result = QString::fromUcs4(&u, 1);
        for (QChar c : result)
            ptr += snprintf(ptr, std::end(buf) - ptr, "\\u%04x", c.unicode());
        QTest::addRow("U+%04X", u) << "[\"" + QByteArray(buf) + "\"]" << result;
    };

    char singleCharJson[] = R"(["\x"])";
    Q_ASSERT(singleCharJson[3] == 'x');
    auto makeSingleCharEscape = [&singleCharJson](char c) {
        singleCharJson[3] = char(c);
        return QByteArray(singleCharJson, std::size(singleCharJson) - 1);
    };

    QTest::addRow("quote") << makeSingleCharEscape('"') << "\"";
    QTest::addRow("backslash") << makeSingleCharEscape('\\') << "\\";
    QTest::addRow("slash") << makeSingleCharEscape('/') << "/";
    QTest::addRow("backspace") << makeSingleCharEscape('b') << "\b";
    QTest::addRow("form-feed") << makeSingleCharEscape('f') << "\f";
    QTest::addRow("newline") << makeSingleCharEscape('n') << "\n";
    QTest::addRow("carriage-return") << makeSingleCharEscape('r') << "\r";
    QTest::addRow("tab") << makeSingleCharEscape('t') << "\t";

    // we're not going to exhaustively test all Unicode possibilities
    for (char16_t c = 0; c < 0x21; ++c)
        addUnicodeRow(c);
    addUnicodeRow(u'\u007f');
    addUnicodeRow(u'\u0080');
    addUnicodeRow(u'\u00ff');
    addUnicodeRow(u'\u0100');
    addUnicodeRow(char16_t(0xd800));
    addUnicodeRow(char16_t(0xdc00));
    addUnicodeRow(u'\ufffe');
    addUnicodeRow(u'\uffff');
    addUnicodeRow(U'\U00010000');
    addUnicodeRow(U'\U00100000');
    addUnicodeRow(U'\U0010ffff');

    QTest::addRow("mojibake-utf8") << QByteArrayLiteral(R"(["A\u00e4\u00C4"])")
                                   << QStringLiteral(u"A\u00e4\u00C4");

    // characters for which, preceded by backslash, it is a valid (recognized)
    // escape sequence (should match the above list)
    static const char validEscapes[] = "\"\\/bfnrtu";
    for (int i = 0; i <= 0xff; ++i) {
        if (i && strchr(validEscapes, i))
            continue;
        QTest::addRow("invalid-uchar-0x%02x", i) << makeSingleCharEscape(i) << QString(char16_t(i));
    }
}

void tst_qextJson::parseEscapes()
{
    QFETCH(QByteArray, json);
    QFETCH(QString, result);

    QExtJsonDocument doc = QExtJsonDocument::fromJson(json);
    QExtJsonArray array = doc.array();

    QCOMPARE(array.first().toString(), result);
}

void tst_qextJson::makeEscapes_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QByteArray>("result");

    auto addUnicodeRow = [](char16_t c) {
        char buf[32];   // more than enough
        snprintf(buf, std::size(buf), "\\u%04x", c);
        QTest::addRow("U+%04X", c) << QString(c) << QByteArray(buf);
    };


    QTest::addRow("quote") << "\"" << QByteArray(R"(\")");
    QTest::addRow("backslash") << "\\" << QByteArray(R"(\\)");
    //QTest::addRow("slash") << "/" << QByteArray(R"(\/)");    // does not get escaped
    QTest::addRow("backspace") << "\b" << QByteArray(R"(\b)");
    QTest::addRow("form-feed") << "\f" << QByteArray(R"(\f)");
    QTest::addRow("newline") << "\n" << QByteArray(R"(\n)");
    QTest::addRow("carriage-return") << "\r" << QByteArray(R"(\r)");
    QTest::addRow("tab") << "\t" << QByteArray(R"(\t)");

    // control characters other than the above
    for (char16_t c = 0; c < 0x20; ++c) {
        if (c && strchr("\b\f\n\r\t", c))
            continue;
        addUnicodeRow(c);
    }
    // unpaired surrogates
    addUnicodeRow(char16_t(0xd800));
    addUnicodeRow(char16_t(0xdc00));

    QString improperlyPaired;
    improperlyPaired.append(char16_t(0xdc00));
    improperlyPaired.append(char16_t(0xd800));
    QTest::addRow("inverted-surrogates") << improperlyPaired << QByteArray("\\udc00\\ud800");
}

void tst_qextJson::makeEscapes()
{
    QFETCH(QString, input);
    QFETCH(QByteArray, result);

    QExtJsonArray array = { input };
    QByteArray json = QExtJsonDocument(array).toJson(QExtJsonDocument::Compact);

    QVERIFY(json.startsWith("[\""));
    result.prepend("[\"");
    QVERIFY(json.endsWith("\"]"));
    result.append("\"]");

    QCOMPARE(json, result);
}

void tst_qextJson::assignObjects()
{
    const char *json =
        "[ { \"Key\": 1 }, { \"Key\": 2 } ]";

    QExtJsonDocument doc = QExtJsonDocument::fromJson(json);
    QExtJsonArray array = doc.array();

    QExtJsonObject object = array.at(0).toObject();
    QCOMPARE(object.value("Key").toDouble(), 1.);

    object = array.at(1).toObject();
    QCOMPARE(object.value("Key").toDouble(), 2.);
}

void tst_qextJson::assignArrays()
{
    const char *json =
        "[ [ 1 ], [ 2 ] ]";

    QExtJsonDocument doc = QExtJsonDocument::fromJson(json);
    QExtJsonArray array = doc.array();

    QExtJsonArray inner = array.at(0).toArray()  ;
    QCOMPARE(inner.at(0).toDouble(), 1.);

    inner= array.at(1).toArray();
    QCOMPARE(inner.at(0).toDouble(), 2.);
}

void tst_qextJson::testTrailingComma()
{
    const char *jsons[] = { "{ \"Key\": 1, }", "[ { \"Key\": 1 }, ]" };

    for (unsigned i = 0; i < sizeof(jsons)/sizeof(jsons[0]); ++i) {
        QExtJsonParseError error;
        QExtJsonDocument doc = QExtJsonDocument::fromJson(jsons[i], &error);
        QCOMPARE(error.error, QExtJsonParseError::MissingObject);
    }
}

void tst_qextJson::testDetachBug()
{
    QExtJsonObject dynamic;
    QExtJsonObject embedded;

    QExtJsonObject local;

    embedded.insert("Key1", QString("Value1"));
    embedded.insert("Key2", QString("Value2"));
    dynamic.insert(QStringLiteral("Bogus"), QString("bogusValue"));
    dynamic.insert("embedded", embedded);
    local = dynamic.value("embedded").toObject();

    dynamic.remove("embedded");

    QCOMPARE(local.keys().size(),2);
    local.remove("Key1");
    local.remove("Key2");
    QCOMPARE(local.keys().size(), 0);

    local.insert("Key1", QString("anotherValue"));
    QCOMPARE(local.keys().size(), 1);
}

void tst_qextJson::valueEquals()
{
    QCOMPARE(QExtJsonValue(), QExtJsonValue());
    QVERIFY(QExtJsonValue() != QExtJsonValue(QExtJsonValue::Undefined));
    QVERIFY(QExtJsonValue() != QExtJsonValue(true));
    QVERIFY(QExtJsonValue() != QExtJsonValue(1.));
    QVERIFY(QExtJsonValue() != QExtJsonValue(QExtJsonArray()));
    QVERIFY(QExtJsonValue() != QExtJsonValue(QExtJsonObject()));

    QCOMPARE(QExtJsonValue(true), QExtJsonValue(true));
    QVERIFY(QExtJsonValue(true) != QExtJsonValue(false));
    QVERIFY(QExtJsonValue(true) != QExtJsonValue(QExtJsonValue::Undefined));
    QVERIFY(QExtJsonValue(true) != QExtJsonValue());
    QVERIFY(QExtJsonValue(true) != QExtJsonValue(1.));
    QVERIFY(QExtJsonValue(true) != QExtJsonValue(QExtJsonArray()));
    QVERIFY(QExtJsonValue(true) != QExtJsonValue(QExtJsonObject()));

    QCOMPARE(QExtJsonValue(1), QExtJsonValue(1));
    QVERIFY(QExtJsonValue(1) != QExtJsonValue(2));
    QCOMPARE(QExtJsonValue(1), QExtJsonValue(1.));
    QVERIFY(QExtJsonValue(1) != QExtJsonValue(1.1));
    QVERIFY(QExtJsonValue(1) != QExtJsonValue(QExtJsonValue::Undefined));
    QVERIFY(QExtJsonValue(1) != QExtJsonValue());
    QVERIFY(QExtJsonValue(1) != QExtJsonValue(true));
    QVERIFY(QExtJsonValue(1) != QExtJsonValue(QExtJsonArray()));
    QVERIFY(QExtJsonValue(1) != QExtJsonValue(QExtJsonObject()));

    QCOMPARE(QExtJsonValue(1.), QExtJsonValue(1.));
    QVERIFY(QExtJsonValue(1.) != QExtJsonValue(2.));
    QVERIFY(QExtJsonValue(1.) != QExtJsonValue(QExtJsonValue::Undefined));
    QVERIFY(QExtJsonValue(1.) != QExtJsonValue());
    QVERIFY(QExtJsonValue(1.) != QExtJsonValue(true));
    QVERIFY(QExtJsonValue(1.) != QExtJsonValue(QExtJsonArray()));
    QVERIFY(QExtJsonValue(1.) != QExtJsonValue(QExtJsonObject()));

    QCOMPARE(QExtJsonValue(QExtJsonArray()), QExtJsonValue(QExtJsonArray()));
    QExtJsonArray nonEmptyArray;
    nonEmptyArray.append(true);
    QVERIFY(QExtJsonValue(QExtJsonArray()) != nonEmptyArray);
    QVERIFY(QExtJsonValue(QExtJsonArray()) != QExtJsonValue(QExtJsonValue::Undefined));
    QVERIFY(QExtJsonValue(QExtJsonArray()) != QExtJsonValue());
    QVERIFY(QExtJsonValue(QExtJsonArray()) != QExtJsonValue(true));
    QVERIFY(QExtJsonValue(QExtJsonArray()) != QExtJsonValue(1.));
    QVERIFY(QExtJsonValue(QExtJsonArray()) != QExtJsonValue(QExtJsonObject()));

    QCOMPARE(QExtJsonValue(QExtJsonObject()), QExtJsonValue(QExtJsonObject()));
    QExtJsonObject nonEmptyObject;
    nonEmptyObject.insert("Key", true);
    QVERIFY(QExtJsonValue(QExtJsonObject()) != nonEmptyObject);
    QVERIFY(QExtJsonValue(QExtJsonObject()) != QExtJsonValue(QExtJsonValue::Undefined));
    QVERIFY(QExtJsonValue(QExtJsonObject()) != QExtJsonValue());
    QVERIFY(QExtJsonValue(QExtJsonObject()) != QExtJsonValue(true));
    QVERIFY(QExtJsonValue(QExtJsonObject()) != QExtJsonValue(1.));
    QVERIFY(QExtJsonValue(QExtJsonObject()) != QExtJsonValue(QExtJsonArray()));

    QCOMPARE(QExtJsonValue("foo"), QExtJsonValue(QLatin1String("foo")));
    QCOMPARE(QExtJsonValue("foo"), QExtJsonValue(QString("foo")));
    QCOMPARE(QExtJsonValue("\x66\x6f\x6f"), QExtJsonValue(QString("foo")));
    QCOMPARE(QExtJsonValue("\x62\x61\x72"), QExtJsonValue("bar"));
    QCOMPARE(QExtJsonValue(UNICODE_NON_CHARACTER), QExtJsonValue(QString(UNICODE_NON_CHARACTER)));
    QCOMPARE(QExtJsonValue(UNICODE_DJE), QExtJsonValue(QString(UNICODE_DJE)));
    QCOMPARE(QExtJsonValue("\xc3\xa9"), QExtJsonValue(QString("\xc3\xa9")));
}

void tst_qextJson::objectEquals_data()
{
    QTest::addColumn<QExtJsonObject>("left");
    QTest::addColumn<QExtJsonObject>("right");
    QTest::addColumn<bool>("result");

    QTest::newRow("two defaults") << QExtJsonObject() << QExtJsonObject() << true;

    QExtJsonObject object1;
    object1.insert("property", 1);
    QExtJsonObject object2;
    object2["property"] = 1;
    QExtJsonObject object3;
    object3.insert("property1", 1);
    object3.insert("property2", 2);

    QTest::newRow("the same object (1 vs 2)") << object1 << object2 << true;
    QTest::newRow("the same object (3 vs 3)") << object3 << object3 << true;
    QTest::newRow("different objects (2 vs 3)") << object2 << object3 << false;
    QTest::newRow("object vs default") << object1 << QExtJsonObject() << false;

    QExtJsonObject empty;
    empty.insert("property", 1);
    empty.take("property");
    QTest::newRow("default vs empty") << QExtJsonObject() << empty << true;
    QTest::newRow("empty vs empty") << empty << empty << true;
    QTest::newRow("object vs empty") << object1 << empty << false;

    QExtJsonObject referencedEmpty;
    referencedEmpty["undefined"];
    QTest::newRow("referenced empty vs referenced empty") << referencedEmpty << referencedEmpty << true;
    QTest::newRow("referenced empty vs object") << referencedEmpty << object1 << false;

    QExtJsonObject referencedObject1;
    referencedObject1.insert("property", 1);
    referencedObject1["undefined"];
    QExtJsonObject referencedObject2;
    referencedObject2.insert("property", 1);
    referencedObject2["aaaaaaaaa"]; // earlier then "property"
    referencedObject2["zzzzzzzzz"]; // after "property"
    QTest::newRow("referenced object vs default") << referencedObject1 << QExtJsonObject() << false;
    QTest::newRow("referenced object vs referenced object") << referencedObject1 << referencedObject1 << true;
    QTest::newRow("referenced object vs object (different)") << referencedObject1 << object3 << false;
}

void tst_qextJson::objectEquals()
{
    QFETCH(QExtJsonObject, left);
    QFETCH(QExtJsonObject, right);
    QFETCH(bool, result);

    QCOMPARE(left == right, result);
    QCOMPARE(right == left, result);

    // invariants checks
    QCOMPARE(left, left);
    QCOMPARE(right, right);
    QCOMPARE(left != right, !result);
    QCOMPARE(right != left, !result);

    // The same but from QExtJsonValue perspective
    QCOMPARE(QExtJsonValue(left) == QExtJsonValue(right), result);
    QCOMPARE(QExtJsonValue(left) != QExtJsonValue(right), !result);
    QCOMPARE(QExtJsonValue(right) == QExtJsonValue(left), result);
    QCOMPARE(QExtJsonValue(right) != QExtJsonValue(left), !result);

    // The same, but from a QExtJsonDocument perspective
    QCOMPARE(QExtJsonDocument(left) == QExtJsonDocument(right), result);
    QCOMPARE(QExtJsonDocument(left) != QExtJsonDocument(right), !result);
    QCOMPARE(QExtJsonDocument(right) == QExtJsonDocument(left), result);
    QCOMPARE(QExtJsonDocument(right) != QExtJsonDocument(left), !result);
}

void tst_qextJson::arrayEquals_data()
{
    QTest::addColumn<QExtJsonArray>("left");
    QTest::addColumn<QExtJsonArray>("right");
    QTest::addColumn<bool>("result");

    QTest::newRow("two defaults") << QExtJsonArray() << QExtJsonArray() << true;

    QExtJsonArray array1;
    array1.append(1);
    QExtJsonArray array2;
    array2.append(2111);
    array2[0] = 1;
    QExtJsonArray array3;
    array3.insert(0, 1);
    array3.insert(1, 2);

    QTest::newRow("the same array (1 vs 2)") << array1 << array2 << true;
    QTest::newRow("the same array (3 vs 3)") << array3 << array3 << true;
    QTest::newRow("different arrays (2 vs 3)") << array2 << array3 << false;
    QTest::newRow("array vs default") << array1 << QExtJsonArray() << false;

    QExtJsonArray empty;
    empty.append(1);
    empty.takeAt(0);
    QTest::newRow("default vs empty") << QExtJsonArray() << empty << true;
    QTest::newRow("empty vs default") << empty << QExtJsonArray() << true;
    QTest::newRow("empty vs empty") << empty << empty << true;
    QTest::newRow("array vs empty") << array1 << empty << false;
}

void tst_qextJson::arrayEquals()
{
    QFETCH(QExtJsonArray, left);
    QFETCH(QExtJsonArray, right);
    QFETCH(bool, result);

    QCOMPARE(left == right, result);
    QCOMPARE(right == left, result);

    // invariants checks
    QCOMPARE(left, left);
    QCOMPARE(right, right);
    QCOMPARE(left != right, !result);
    QCOMPARE(right != left, !result);

    // The same but from QExtJsonValue perspective
    QCOMPARE(QExtJsonValue(left) == QExtJsonValue(right), result);
    QCOMPARE(QExtJsonValue(left) != QExtJsonValue(right), !result);
    QCOMPARE(QExtJsonValue(right) == QExtJsonValue(left), result);
    QCOMPARE(QExtJsonValue(right) != QExtJsonValue(left), !result);

    // The same but from QExtJsonDocument perspective
    QCOMPARE(QExtJsonDocument(left) == QExtJsonDocument(right), result);
    QCOMPARE(QExtJsonDocument(left) != QExtJsonDocument(right), !result);
    QCOMPARE(QExtJsonDocument(right) == QExtJsonDocument(left), result);
    QCOMPARE(QExtJsonDocument(right) != QExtJsonDocument(left), !result);
}

void tst_qextJson::documentEquals_data()
{
    QTest::addColumn<QExtJsonDocument>("left");
    QTest::addColumn<QExtJsonDocument>("right");
    QTest::addColumn<bool>("result");

    QTest::newRow("two defaults") << QExtJsonDocument() << QExtJsonDocument() << true;

    QExtJsonDocument emptyobj(QExtJsonObject{});
    QExtJsonDocument emptyarr(QExtJsonArray{});
    QTest::newRow("emptyarray vs default") << emptyarr << QExtJsonDocument() << false;
    QTest::newRow("emptyobject vs default") << emptyobj << QExtJsonDocument() << false;
    QTest::newRow("emptyarray vs emptyobject") << emptyarr << emptyobj << false;

    QExtJsonDocument array1(QExtJsonArray{1});
    QExtJsonDocument array2(QExtJsonArray{2});
    QTest::newRow("emptyarray vs emptyarray") << emptyarr << emptyarr << true;
    QTest::newRow("emptyarray vs array") << emptyarr << array1 << false;
    QTest::newRow("array vs array") << array1 << array1 << true;
    QTest::newRow("array vs otherarray") << array1 << array2 << false;

    QExtJsonDocument object1(QExtJsonObject{{"hello", "world"}});
    QExtJsonDocument object2(QExtJsonObject{{"hello", 2}});
    QTest::newRow("emptyobject vs emptyobject") << emptyobj << emptyobj << true;
    QTest::newRow("emptyobject vs object") << emptyobj << object1 << false;
    QTest::newRow("object vs object") << object1 << object1 << true;
    QTest::newRow("object vs otherobject") << object1 << object2 << false;

    QTest::newRow("object vs array") << array1 << object1 << false;
}

void tst_qextJson::documentEquals()
{
    QFETCH(QExtJsonDocument, left);
    QFETCH(QExtJsonDocument, right);
    QFETCH(bool, result);

    QCOMPARE(left == right, result);
    QCOMPARE(right == left, result);

    // invariants checks
    QCOMPARE(left, left);
    QCOMPARE(right, right);
    QCOMPARE(left != right, !result);
    QCOMPARE(right != left, !result);
}

void tst_qextJson::bom()
{
    QFile file(testDataDir + "/bom.json");
    file.open(QFile::ReadOnly);
    QByteArray json = file.readAll();

    // Import json document into a QExtJsonDocument
    QExtJsonParseError error;
    QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);

    QVERIFY(!doc.isNull());
    QCOMPARE(error.error, QExtJsonParseError::NoError);
}

void tst_qextJson::nesting()
{
    // check that we abort parsing too deeply nested json documents.
    // this is to make sure we don't crash because the parser exhausts the
    // stack.

    const char *array_data =
        "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[["
        "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[["
        "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[["
        "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[["
        "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[["
        "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[["
        "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[["
        "[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[["
        "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]"
        "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]"
        "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]"
        "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]"
        "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]"
        "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]"
        "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]"
        "]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]";

    QByteArray json(array_data);
    QExtJsonParseError error;
    QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);

    QVERIFY(!doc.isNull());
    QCOMPARE(error.error, QExtJsonParseError::NoError);

    json.prepend('[');
    json.append(']');
    doc = QExtJsonDocument::fromJson(json, &error);

    QVERIFY(doc.isNull());
    QCOMPARE(error.error, QExtJsonParseError::DeepNesting);

    json = QByteArray("true ");

    for (int i = 0; i < 1024; ++i) {
        json.prepend("{ \"Key\": ");
        json.append(" }");
    }

    doc = QExtJsonDocument::fromJson(json, &error);

    QVERIFY(!doc.isNull());
    QCOMPARE(error.error, QExtJsonParseError::NoError);

    json.prepend('[');
    json.append(']');
    doc = QExtJsonDocument::fromJson(json, &error);

    QVERIFY(doc.isNull());
    QCOMPARE(error.error, QExtJsonParseError::DeepNesting);

}

void tst_qextJson::longStrings()
{
    // test around 15 and 16 bit boundaries, as these are limits
    // in the data structures (for Latin1String in qjson_p.h)
    QString s(0x7ff0, 'a');
    QByteArray ba(0x7ff0, 'a');
    ba.append(0x8010 - 0x7ff0, 'c');
    for (int i = 0x7ff0; i < 0x8010; i++) {
        s.append(QLatin1Char('c'));

        QMap <QString, QVariant> map;
        map["key"] = s;

        /* Create a QExtJsonDocument from the QMap ... */
        QExtJsonDocument d1 = QExtJsonDocument::fromVariant(QVariant(map));
        /* ... and a QByteArray from the QExtJsonDocument */
        QByteArray a1 = d1.toJson();

        /* Create a QExtJsonDocument from the QByteArray ... */
        QExtJsonDocument d2 = QExtJsonDocument::fromJson(a1);
        /* ... and a QByteArray from the QExtJsonDocument */
        QByteArray a2 = d2.toJson();
        QCOMPARE(a1, a2);

        // Test long keys
        QExtJsonObject o1, o2;
        o1[s] = 42;
        o2[QLatin1String(ba.data(), i + 1)] = 42;
        d1.setObject(o1);
        d2.setObject(o2);
        a1 = d1.toJson();
        a2 = d2.toJson();
        QCOMPARE(a1, a2);
    }

    s = QString(0xfff0, 'a');
    ba = QByteArray(0xfff0, 'a');
    ba.append(0x10010 - 0xfff0, 'c');
    for (int i = 0xfff0; i < 0x10010; i++) {
        s.append(QLatin1Char('c'));

        QMap <QString, QVariant> map;
        map["key"] = s;

        /* Create a QExtJsonDocument from the QMap ... */
        QExtJsonDocument d1 = QExtJsonDocument::fromVariant(QVariant(map));
        /* ... and a QByteArray from the QExtJsonDocument */
        QByteArray a1 = d1.toJson();

        /* Create a QExtJsonDocument from the QByteArray ... */
        QExtJsonDocument d2 = QExtJsonDocument::fromJson(a1);
        /* ... and a QByteArray from the QExtJsonDocument */
        QByteArray a2 = d2.toJson();
        QCOMPARE(a1, a2);

        // Test long keys
        QExtJsonObject o1, o2;
        o1[s] = 42;
        o2[QLatin1String(ba.data(), i + 1)] = 42;
        d1.setObject(o1);
        d2.setObject(o2);
        a1 = d1.toJson();
        a2 = d2.toJson();
        QCOMPARE(a1, a2);
    }
}

void tst_qextJson::testJsonValueRefDefault()
{
    QExtJsonObject empty;

    QCOMPARE(empty["n/a"].toString(), QString());
    QCOMPARE(empty["n/a"].toString("default"), QStringLiteral("default"));

    QCOMPARE(empty["n/a"].toBool(), false);
    QCOMPARE(empty["n/a"].toBool(true), true);

    QCOMPARE(empty["n/a"].toInt(), 0);
    QCOMPARE(empty["n/a"].toInt(42), 42);

    QCOMPARE(empty["n/a"].toDouble(), 0.0);
    QCOMPARE(empty["n/a"].toDouble(42.0), 42.0);
}

void tst_qextJson::arrayInitializerList()
{
    QVERIFY(QExtJsonArray{}.isEmpty());
    QCOMPARE(QExtJsonArray{"one"}.count(), 1);
    QCOMPARE(QExtJsonArray{1}.count(), 1);

    {
        QExtJsonArray a{1.3, "hello", 0};
        QCOMPARE(QExtJsonValue(a[0]), QExtJsonValue(1.3));
        QCOMPARE(QExtJsonValue(a[1]), QExtJsonValue("hello"));
        QCOMPARE(QExtJsonValue(a[2]), QExtJsonValue(0));
        QCOMPARE(a.count(), 3);
    }
    {
        QExtJsonObject o;
        o["property"] = 1;
        QExtJsonArray a1 {o};
        QCOMPARE(a1.count(), 1);
        QCOMPARE(a1[0].toObject(), o);

        QExtJsonArray a2 {o, 23};
        QCOMPARE(a2.count(), 2);
        QCOMPARE(a2[0].toObject(), o);
        QCOMPARE(QExtJsonValue(a2[1]), QExtJsonValue(23));

        QExtJsonArray a3 { a1, o, a2 };
        QCOMPARE(QExtJsonValue(a3[0]), QExtJsonValue(a1));
        QCOMPARE(QExtJsonValue(a3[1]), QExtJsonValue(o));
        QCOMPARE(QExtJsonValue(a3[2]), QExtJsonValue(a2));

        QExtJsonArray a4 { 1, QExtJsonArray{1,2,3}, QExtJsonArray{"hello", 2}, QExtJsonObject{{"one", 1}} };
        QCOMPARE(a4.count(), 4);
        QCOMPARE(QExtJsonValue(a4[0]), QExtJsonValue(1));

        {
            QExtJsonArray a41 = a4[1].toArray();
            QExtJsonArray a42 = a4[2].toArray();
            QExtJsonObject a43 = a4[3].toObject();
            QCOMPARE(a41.count(), 3);
            QCOMPARE(a42.count(), 2);
            QCOMPARE(a43.count(), 1);

            QCOMPARE(QExtJsonValue(a41[2]), QExtJsonValue(3));
            QCOMPARE(QExtJsonValue(a42[1]), QExtJsonValue(2));
            QCOMPARE(QExtJsonValue(a43["one"]), QExtJsonValue(1));
        }
    }
}

void tst_qextJson::objectInitializerList()
{
    QVERIFY(QExtJsonObject{}.isEmpty());

    {   // one property
        QExtJsonObject one {{"one", 1}};
        QCOMPARE(one.count(), 1);
        QVERIFY(one.contains("one"));
        QCOMPARE(QExtJsonValue(one["one"]), QExtJsonValue(1));
    }
    {   // two properties
        QExtJsonObject two {
            {"one", 1},
            {"two", 2}
        };
        QCOMPARE(two.count(), 2);
        QVERIFY(two.contains("one"));
        QVERIFY(two.contains("two"));
        QCOMPARE(QExtJsonValue(two["one"]), QExtJsonValue(1));
        QCOMPARE(QExtJsonValue(two["two"]), QExtJsonValue(2));
    }
    {   // nested object
        QExtJsonObject object{{"nested", QExtJsonObject{{"innerProperty", 2}}}};
        QCOMPARE(object.count(), 1);
        QVERIFY(object.contains("nested"));
        QVERIFY(object["nested"].isObject());

        QExtJsonObject nested = object["nested"].toObject();
        QCOMPARE(QExtJsonValue(nested["innerProperty"]), QExtJsonValue(2));
    }
    {   // nested array
        QExtJsonObject object{{"nested", QExtJsonArray{"innerValue", 2.1, "bum cyk cyk"}}};
        QCOMPARE(object.count(), 1);
        QVERIFY(object.contains("nested"));
        QVERIFY(object["nested"].isArray());

        QExtJsonArray nested = object["nested"].toArray();
        QCOMPARE(nested.count(), 3);
        QCOMPARE(QExtJsonValue(nested[0]), QExtJsonValue("innerValue"));
        QCOMPARE(QExtJsonValue(nested[1]), QExtJsonValue(2.1));
    }
}

void tst_qextJson::unicodeKeys()
{
    QByteArray json = "{"
                      "\"x\\u2090_1\": \"hello_1\","
                      "\"y\\u2090_2\": \"hello_2\","
                      "\"T\\u2090_3\": \"hello_3\","
                      "\"xyz_4\": \"hello_4\","
                      "\"abc_5\": \"hello_5\""
                      "}";

    QExtJsonParseError error;
    QExtJsonDocument doc = QExtJsonDocument::fromJson(json, &error);
    QCOMPARE(error.error, QExtJsonParseError::NoError);
    QExtJsonObject o = doc.object();

    const auto keys = o.keys();
    QCOMPARE(keys.size(), 5);
    for (const QString &key : keys) {
        QString suffix = key.mid(key.indexOf(QLatin1Char('_')));
        QCOMPARE(o[key].toString(), QString("hello") + suffix);
    }
}

void tst_qextJson::garbageAtEnd()
{
    QExtJsonParseError error;
    QExtJsonDocument doc = QExtJsonDocument::fromJson("{},", &error);
    QCOMPARE(error.error, QExtJsonParseError::GarbageAtEnd);
    QCOMPARE(error.offset, 2);
    QVERIFY(doc.isEmpty());

    doc = QExtJsonDocument::fromJson("{}    ", &error);
    QCOMPARE(error.error, QExtJsonParseError::NoError);
    QVERIFY(!doc.isEmpty());
}

void tst_qextJson::removeNonLatinKey()
{
    const QString nonLatinKeyName = QString::fromUtf8("Атрибут100500");

    QExtJsonObject sourceObject;

    sourceObject.insert("code", 1);
    sourceObject.remove("code");

    sourceObject.insert(nonLatinKeyName, 1);

    const QByteArray json = QExtJsonDocument(sourceObject).toJson();
    const QExtJsonObject restoredObject = QExtJsonDocument::fromJson(json).object();

    QCOMPARE(sourceObject.keys(), restoredObject.keys());
    QVERIFY(sourceObject.contains(nonLatinKeyName));
    QVERIFY(restoredObject.contains(nonLatinKeyName));
}

void tst_qextJson::documentFromVariant()
{
    // Test the valid forms of QExtJsonDocument::fromVariant.

    QString string = QStringLiteral("value");

    QStringList strList;
    strList.append(string);

    QExtJsonDocument da1 = QExtJsonDocument::fromVariant(QVariant(strList));
    QVERIFY(da1.isArray());

    QVariantList list;
    list.append(string);

    QExtJsonDocument da2 = QExtJsonDocument::fromVariant(list);
    QVERIFY(da2.isArray());

    // As JSON arrays they should be equal.
    QCOMPARE(da1.array(), da2.array());


    QMap <QString, QVariant> map;
    map["key"] = string;

    QExtJsonDocument do1 = QExtJsonDocument::fromVariant(QVariant(map));
    QVERIFY(do1.isObject());

    QHash <QString, QVariant> hash;
    hash["key"] = string;

    QExtJsonDocument do2 = QExtJsonDocument::fromVariant(QVariant(hash));
    QVERIFY(do2.isObject());

    // As JSON objects they should be equal.
    QCOMPARE(do1.object(), do2.object());
}

void tst_qextJson::parseErrorOffset_data()
{
    QTest::addColumn<QByteArray>("json");
    QTest::addColumn<int>("errorOffset");

    QTest::newRow("Trailing comma in object") << QByteArray("{ \"value\": false, }") << 19;
    QTest::newRow("Trailing comma in object plus whitespace") << QByteArray("{ \"value\": false, }    ") << 19;
    QTest::newRow("Trailing comma in array") << QByteArray("[ false, ]") << 10;
    QTest::newRow("Trailing comma in array plus whitespace") << QByteArray("[ false, ]    ") << 10;
    QTest::newRow("Missing value in object") << QByteArray("{ \"value\": , } ") << 12;
    QTest::newRow("Missing value in array") << QByteArray("[ \"value\" , , ] ") << 13;
    QTest::newRow("Leading comma in object") << QByteArray("{ ,  \"value\": false}") << 3;
    QTest::newRow("Leading comma in array") << QByteArray("[ ,  false]") << 3;
    QTest::newRow("Stray ,") << QByteArray("  ,  ") << 3;
    QTest::newRow("Stray [") << QByteArray("  [  ") << 5;
    QTest::newRow("Stray }") << QByteArray("  }  ") << 3;
}

void tst_qextJson::parseErrorOffset()
{
    QFETCH(QByteArray, json);
    QFETCH(int, errorOffset);

    QExtJsonParseError error;
    QExtJsonDocument::fromJson(json, &error);

    QVERIFY(error.error != QExtJsonParseError::NoError);
    QCOMPARE(error.offset, errorOffset);
}

void tst_qextJson::implicitValueType()
{
    QExtJsonObject rootObject{
        {"object", QExtJsonObject{{"value", 42}}},
        {"array", QExtJsonArray{665, 666, 667}}
    };

    QExtJsonValue objectValue = rootObject["object"];
    QCOMPARE(objectValue["value"].toInt(), 42);
    QCOMPARE(objectValue["missingValue"], QExtJsonValue(QExtJsonValue::Undefined));
    QCOMPARE(objectValue[123], QExtJsonValue(QExtJsonValue::Undefined));
    QCOMPARE(objectValue["missingValue"].toInt(123), 123);

    QExtJsonValue arrayValue = rootObject["array"];
    QCOMPARE(arrayValue[1].toInt(), 666);
    QCOMPARE(arrayValue[-1], QExtJsonValue(QExtJsonValue::Undefined));
    QCOMPARE(arrayValue["asObject"], QExtJsonValue(QExtJsonValue::Undefined));
    QCOMPARE(arrayValue[-1].toInt(123), 123);

    const QExtJsonObject constObject = rootObject;
    QCOMPARE(constObject["object"]["value"].toInt(), 42);
    QCOMPARE(constObject["array"][1].toInt(), 666);

    QExtJsonValue objectAsValue(rootObject);
    QCOMPARE(objectAsValue["object"]["value"].toInt(), 42);
    QCOMPARE(objectAsValue["array"][1].toInt(), 666);
}

void tst_qextJson::implicitDocumentType()
{
    QExtJsonDocument emptyDocument;
    QCOMPARE(emptyDocument["asObject"], QExtJsonValue(QExtJsonValue::Undefined));
    QCOMPARE(emptyDocument[123], QExtJsonValue(QExtJsonValue::Undefined));

    QExtJsonDocument objectDocument(QExtJsonObject{{"value", 42}});
    QCOMPARE(objectDocument["value"].toInt(), 42);
    QCOMPARE(objectDocument["missingValue"], QExtJsonValue(QExtJsonValue::Undefined));
    QCOMPARE(objectDocument[123], QExtJsonValue(QExtJsonValue::Undefined));
    QCOMPARE(objectDocument["missingValue"].toInt(123), 123);

    QExtJsonDocument arrayDocument(QExtJsonArray{665, 666, 667});
    QCOMPARE(arrayDocument[1].toInt(), 666);
    QCOMPARE(arrayDocument[-1], QExtJsonValue(QExtJsonValue::Undefined));
    QCOMPARE(arrayDocument["asObject"], QExtJsonValue(QExtJsonValue::Undefined));
    QCOMPARE(arrayDocument[-1].toInt(123), 123);
}

void tst_qextJson::streamSerializationQExtJsonDocument_data()
{
    QTest::addColumn<QExtJsonDocument>("document");
    QTest::newRow("empty") << QExtJsonDocument();
    QTest::newRow("object") << QExtJsonDocument(QExtJsonObject{{"value", 42}});
}

void tst_qextJson::streamSerializationQExtJsonDocument()
{
    // Check interface only, implementation is tested through to and from
    // json functions.
    QByteArray buffer;
    QFETCH(QExtJsonDocument, document);
    QExtJsonDocument output;
    QDataStream save(&buffer, QIODevice::WriteOnly);
    save << document;
    QDataStream load(buffer);
    load >> output;
    QCOMPARE(output, document);
}

void tst_qextJson::streamSerializationQExtJsonArray_data()
{
    QTest::addColumn<QExtJsonArray>("array");
    QTest::newRow("empty") << QExtJsonArray();
    QTest::newRow("values") << QExtJsonArray{665, 666, 667};
}

void tst_qextJson::streamSerializationQExtJsonArray()
{
    // Check interface only, implementation is tested through to and from
    // json functions.
    QByteArray buffer;
    QFETCH(QExtJsonArray, array);
    QExtJsonArray output;
    QDataStream save(&buffer, QIODevice::WriteOnly);
    save << array;
    QDataStream load(buffer);
    load >> output;
    QCOMPARE(output, array);
}

void tst_qextJson::streamSerializationQExtJsonObject_data()
{
    QTest::addColumn<QExtJsonObject>("object");
    QTest::newRow("empty") << QExtJsonObject();
    QTest::newRow("non-empty") << QExtJsonObject{{"foo", 665}, {"bar", 666}};
}

void tst_qextJson::streamSerializationQExtJsonObject()
{
    // Check interface only, implementation is tested through to and from
    // json functions.
    QByteArray buffer;
    QFETCH(QExtJsonObject, object);
    QExtJsonObject output;
    QDataStream save(&buffer, QIODevice::WriteOnly);
    save << object;
    QDataStream load(buffer);
    load >> output;
    QCOMPARE(output, object);
}

void tst_qextJson::streamSerializationQExtJsonValue_data()
{
    QTest::addColumn<QExtJsonValue>("value");
    QTest::newRow("double") << QExtJsonValue{665};
    QTest::newRow("bool") << QExtJsonValue{true};
    QTest::newRow("string") << QExtJsonValue{QStringLiteral("bum")};
    QTest::newRow("array") << QExtJsonValue{QExtJsonArray{12,1,5,6,7}};
    QTest::newRow("object") << QExtJsonValue{QExtJsonObject{{"foo", 665}, {"bar", 666}}};
    // test json escape sequence
    QTest::newRow("array with 0xD800") << QExtJsonValue(QExtJsonArray{QString(QChar(0xD800))});
    QTest::newRow("array with 0xDF06,0xD834") << QExtJsonValue(QExtJsonArray{QString(QChar(0xDF06)).append(QChar(0xD834))});
}

void tst_qextJson::streamSerializationQExtJsonValue()
{
    QByteArray buffer;
    QFETCH(QExtJsonValue, value);
    QExtJsonValue output;
    QDataStream save(&buffer, QIODevice::WriteOnly);
    save << value;
    QDataStream load(buffer);
    load >> output;
    QCOMPARE(output, value);
}

void tst_qextJson::streamSerializationQExtJsonValueEmpty()
{
    QByteArray buffer;
    {
        QExtJsonValue undef{QExtJsonValue::Undefined};
        QDataStream save(&buffer, QIODevice::WriteOnly);
        save << undef;
        QDataStream load(buffer);
        QExtJsonValue output;
        load >> output;
        QVERIFY(output.isUndefined());
    }
    {
        QExtJsonValue null{QExtJsonValue::Null};
        QDataStream save(&buffer, QIODevice::WriteOnly);
        save << null;
        QDataStream load(buffer);
        QExtJsonValue output;
        load >> output;
        QVERIFY(output.isNull());
    }
}

void tst_qextJson::streamVariantSerialization()
{
    // Check interface only, implementation is tested through to and from
    // json functions.
    QByteArray buffer;
    {
        QExtJsonDocument objectDoc(QExtJsonArray{665, 666, 667});
        QVariant output;
        QVariant variant(objectDoc);
        QDataStream save(&buffer, QIODevice::WriteOnly);
        save << variant;
        QDataStream load(buffer);
        load >> output;
        QCOMPARE(output.userType(), QMetaType::QExtJsonDocument);
        QCOMPARE(output.toJsonDocument(), objectDoc);
    }
    {
        QExtJsonArray array{665, 666, 667};
        QVariant output;
        QVariant variant(array);
        QDataStream save(&buffer, QIODevice::WriteOnly);
        save << variant;
        QDataStream load(buffer);
        load >> output;
        QCOMPARE(output.userType(), QMetaType::QExtJsonArray);
        QCOMPARE(output.toJsonArray(), array);
    }
    {
        QExtJsonObject obj{{"foo", 42}};
        QVariant output;
        QVariant variant(obj);
        QDataStream save(&buffer, QIODevice::WriteOnly);
        save << variant;
        QDataStream load(buffer);
        load >> output;
        QCOMPARE(output.userType(), QMetaType::QExtJsonObject);
        QCOMPARE(output.toJsonObject(), obj);
    }
    {
        QExtJsonValue value{42};
        QVariant output;
        QVariant variant(value);
        QDataStream save(&buffer, QIODevice::WriteOnly);
        save << variant;
        QDataStream load(buffer);
        load >> output;
        QCOMPARE(output.userType(), QMetaType::QExtJsonValue);
        QCOMPARE(output.toJsonValue(), value);
    }
}

void tst_qextJson::escapeSurrogateCodePoints_data()
{
    QTest::addColumn<QString>("str");
    QTest::addColumn<QByteArray>("escStr");
    QTest::newRow("0xD800") << QString(QChar(0xD800)) << QByteArray("\\ud800");
    QTest::newRow("0xDF06,0xD834") << QString(QChar(0xDF06)).append(QChar(0xD834)) << QByteArray("\\udf06\\ud834");
}

void tst_qextJson::escapeSurrogateCodePoints()
{
    QFETCH(QString, str);
    QFETCH(QByteArray, escStr);
    QExtJsonArray array;
    array.append(str);
    QByteArray buffer;
    QDataStream save(&buffer, QIODevice::WriteOnly);
    save << array;
    // verify the buffer has escaped values
    QVERIFY(buffer.contains(escStr));
}

void tst_qextJson::fromToVariantConversions_data()
{
    QTest::addColumn<QVariant>("variant");
    QTest::addColumn<QExtJsonValue>("json");
    QTest::addColumn<QVariant>("jsonToVariant");

    QByteArray utf8("\xC4\x90\xC4\x81\xC5\xA3\xC3\xA2"); // Đāţâ
    QDateTime dt = QDateTime::currentDateTimeUtc();
    QUuid uuid = QUuid::createUuid();

    constexpr qlonglong maxInt = std::numeric_limits<qlonglong>::max();
    constexpr qlonglong minInt = std::numeric_limits<qlonglong>::min();
    constexpr double maxDouble = std::numeric_limits<double>::max();
    constexpr double minDouble = std::numeric_limits<double>::min();

    QTest::newRow("default")     << QVariant() << QExtJsonValue(QExtJsonValue::Null)
                             << QVariant::fromValue(nullptr);
    QTest::newRow("nullptr")     << QVariant::fromValue(nullptr) << QExtJsonValue(QExtJsonValue::Null)
                             << QVariant::fromValue(nullptr);
    QTest::newRow("bool")        << QVariant(true) << QExtJsonValue(true) << QVariant(true);
    QTest::newRow("int pos")     << QVariant(123) << QExtJsonValue(123) << QVariant(qlonglong(123));
    QTest::newRow("int neg")     << QVariant(-123) << QExtJsonValue(-123) << QVariant(qlonglong(-123));
    QTest::newRow("int big pos") << QVariant((1ll << 55) +1) << QExtJsonValue((1ll << 55) + 1)
                                 << QVariant(qlonglong((1ll << 55) + 1));
    QTest::newRow("int big neg") << QVariant(-(1ll << 55) + 1) << QExtJsonValue(-(1ll << 55) + 1)
                                 << QVariant(qlonglong(-(1ll << 55) + 1));
    QTest::newRow("int max")     << QVariant(maxInt) << QExtJsonValue(maxInt) << QVariant(maxInt);
    QTest::newRow("int min")     << QVariant(minInt) << QExtJsonValue(minInt) << QVariant(minInt);
    QTest::newRow("double pos")  << QVariant(123.) << QExtJsonValue(123.) << QVariant(qlonglong(123.));
    QTest::newRow("double neg")  << QVariant(-123.) << QExtJsonValue(-123.)
                                << QVariant(qlonglong(-123.));
    QTest::newRow("double big")  << QVariant(maxDouble - 1000) << QExtJsonValue(maxDouble - 1000)
                                << QVariant(maxDouble - 1000);
    QTest::newRow("double max")  << QVariant(maxDouble) << QExtJsonValue(maxDouble)
                                << QVariant(maxDouble);
    QTest::newRow("double min")  << QVariant(minDouble) << QExtJsonValue(minDouble)
                                << QVariant(minDouble);
    QTest::newRow("double big neg")  << QVariant(1000 - maxDouble) << QExtJsonValue(1000 - maxDouble)
                                    << QVariant(1000 - maxDouble);
    QTest::newRow("double max neg")  << QVariant(-maxDouble) << QExtJsonValue(-maxDouble)
                                    << QVariant(-maxDouble);
    QTest::newRow("double min neg")  << QVariant(-minDouble) << QExtJsonValue(-minDouble)
                                    << QVariant(-minDouble);

    QTest::newRow("string null")     << QVariant(QString()) << QExtJsonValue(QString())
                                 << QVariant(QString());
    QTest::newRow("string empty")    << QVariant(QString("")) << QExtJsonValue(QString(""))
                                  << QVariant(QString(""));
    QTest::newRow("string ascii")    << QVariant(QString("Data")) << QExtJsonValue(QString("Data"))
                                  << QVariant(QString("Data"));
    QTest::newRow("string utf8")     << QVariant(QString(utf8)) << QExtJsonValue(QString(utf8))
                                 << QVariant(QString(utf8));

    QTest::newRow("bytearray null")  << QVariant(QByteArray()) << QExtJsonValue(QExtJsonValue::Null)
                                    << QVariant::fromValue(nullptr);
    QTest::newRow("bytearray empty") << QVariant(QByteArray()) << QExtJsonValue(QExtJsonValue::Null)
                                     << QVariant::fromValue(nullptr);
    QTest::newRow("bytearray ascii") << QVariant(QByteArray("Data")) << QExtJsonValue(QString("Data"))
                                     << QVariant(QString("Data"));
    QTest::newRow("bytearray utf8")  << QVariant(utf8) << QExtJsonValue(QString(utf8))
                                    << QVariant(QString(utf8));

    QTest::newRow("datetime") << QVariant(dt) << QExtJsonValue(dt.toString(Qt::ISODateWithMs))
                              << QVariant(dt.toString(Qt::ISODateWithMs));
    QTest::newRow("url")      << QVariant(QUrl("http://example.com/{q}"))
                         << QExtJsonValue("http://example.com/%7Bq%7D")
                         << QVariant(QString("http://example.com/%7Bq%7D"));
    QTest::newRow("uuid")     << QVariant(QUuid(uuid))
                          << QExtJsonValue(uuid.toString(QUuid::WithoutBraces))
                          << QVariant(uuid.toString(QUuid::WithoutBraces));
    QTest::newRow("regexp")   << QVariant(QRegularExpression(".")) << QExtJsonValue(QExtJsonValue::Null)
                            << QVariant::fromValue(nullptr);

    QTest::newRow("inf")      << QVariant(qInf()) << QExtJsonValue(QExtJsonValue::Null)
                         << QVariant::fromValue(nullptr);
    QTest::newRow("-inf")     << QVariant(-qInf()) << QExtJsonValue(QExtJsonValue::Null)
                          << QVariant::fromValue(nullptr);
    QTest::newRow("NaN")      << QVariant(qQNaN()) << QExtJsonValue(QExtJsonValue::Null)
                         << QVariant::fromValue(nullptr);

    static_assert(std::numeric_limits<double>::digits <= 63,
                  "double is too big on this platform, this test would fail");
    constexpr quint64 Threshold = Q_UINT64_C(1) << 63;
    const qulonglong ulongValue = qulonglong(Threshold) + 1;
    const double uLongToDouble = Threshold;
    QTest::newRow("ulonglong") << QVariant(ulongValue) << QExtJsonValue(uLongToDouble)
                               << QVariant(uLongToDouble);
}

void tst_qextJson::fromToVariantConversions()
{
    QFETCH(QVariant, variant);
    QFETCH(QExtJsonValue, json);
    QFETCH(QVariant, jsonToVariant);

    QVariant variantFromJson(json);
    QVariant variantFromJsonArray(QExtJsonArray { json });
    QVariant variantFromJsonObject(QVariantMap { { "foo", variant } });

    QExtJsonObject object { QPair<QString, QExtJsonValue>("foo", json) };

    // QExtJsonValue <> QVariant
    {
        QCOMPARE(QExtJsonValue::fromVariant(variant), json);

        // test the same for QVariant from QExtJsonValue/QExtJsonArray/QExtJsonObject
        QCOMPARE(QExtJsonValue::fromVariant(variantFromJson), json);
        QCOMPARE(QExtJsonValue::fromVariant(variantFromJsonArray), QExtJsonArray { json });
        QCOMPARE(QExtJsonValue::fromVariant(variantFromJsonObject), object);

        // QExtJsonValue to variant
        QCOMPARE(json.toVariant(), jsonToVariant);
        QCOMPARE(json.toVariant().userType(), jsonToVariant.userType());

        // variant to QExtJsonValue
        QCOMPARE(QVariant(json).toJsonValue(), json);
    }

    // QExtJsonArray <> QVariantList
    {
        QCOMPARE(QExtJsonArray::fromVariantList(QVariantList { variant }), QExtJsonArray { json });

        // test the same for QVariantList from QExtJsonValue/QExtJsonArray/QExtJsonObject
        QCOMPARE(QExtJsonArray::fromVariantList(QVariantList { variantFromJson }),
                 QExtJsonArray { json });
        QCOMPARE(QExtJsonArray::fromVariantList(QVariantList { variantFromJsonArray }),
                 QExtJsonArray {{ QExtJsonArray { json } }});
        QCOMPARE(QExtJsonArray::fromVariantList(QVariantList { variantFromJsonObject }),
                 QExtJsonArray { object });

        // QExtJsonArray to variant
        QCOMPARE(QExtJsonArray { json }.toVariantList(), QVariantList { jsonToVariant });
        // variant to QExtJsonArray
        QCOMPARE(QVariant(QExtJsonArray { json }).toJsonArray(), QExtJsonArray { json });
    }

    // QExtJsonObject <> QVariantMap
    {
        QCOMPARE(QExtJsonObject::fromVariantMap(QVariantMap { { "foo", variant } }), object);

        // test the same for QVariantMap from QExtJsonValue/QExtJsonArray/QExtJsonObject
        QCOMPARE(QExtJsonObject::fromVariantMap(QVariantMap { { "foo", variantFromJson } }), object);

        QExtJsonObject nestedArray { QPair<QString, QExtJsonArray>("bar", QExtJsonArray { json }) };
        QExtJsonObject nestedObject { QPair<QString, QExtJsonObject>("bar", object) };
        QCOMPARE(QExtJsonObject::fromVariantMap(QVariantMap { { "bar", variantFromJsonArray } }),
                 nestedArray);
        QCOMPARE(QExtJsonObject::fromVariantMap(QVariantMap { { "bar", variantFromJsonObject } }),
                 nestedObject);

        // QExtJsonObject to variant
        QCOMPARE(object.toVariantMap(), QVariantMap({ { "foo", jsonToVariant } }));
        // variant to QExtJsonObject
        QCOMPARE(QVariant(object).toJsonObject(), object);
    }
}

void tst_qextJson::testIteratorComparison()
{
    QExtJsonObject t = QExtJsonObject::fromVariantHash({
        { QStringLiteral("a"), QVariant(12) },
        { QStringLiteral("b"), QVariant(13) }
    });

    QVERIFY(t.begin() == t.begin());
    QVERIFY(t.begin() <= t.begin());
    QVERIFY(t.begin() >= t.begin());
    QVERIFY(!(t.begin() != t.begin()));
    QVERIFY(!(t.begin() < t.begin()));
    QVERIFY(!(t.begin() > t.begin()));

    QVERIFY(!(t.begin() == t.end()));
    QVERIFY(t.begin() <= t.end());
    QVERIFY(!(t.begin() >= t.end()));
    QVERIFY(t.begin() != t.end());
    QVERIFY(t.begin() < t.end());
    QVERIFY(!(t.begin() > t.end()));

    QVERIFY(!(t.end() == t.begin()));
    QVERIFY(!(t.end() <= t.begin()));
    QVERIFY(t.end() >= t.begin());
    QVERIFY(t.end() != t.begin());
    QVERIFY(!(t.end() < t.begin()));
    QVERIFY(t.end() > t.begin());
}

void tst_qextJson::noLeakOnNameClash_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<QByteArray>("result");
    QTest::addRow("simple")
        << QStringLiteral("simple.duplicates.json")
        << QByteArray(R"({"": 0})");
    QTest::addRow("test")
        << QStringLiteral("test.duplicates.json")
        << QByteArray(R"([
                    "JSON Test Pattern pass1", {"a": ["array with 1 element"]}, {}, [], -42, true,
                    false, null, {"a": "A key can be any string"}, 0.5, 98.6, 99.44, 1066, 10, 1,
                    0.1, 1, 2, 2, "rosebud", {"a": "bar"}, {"a": {"a": 2000}}, {"a": {"a": 2000}},
                    {"a": {"a": 2000}}, {"a": {"a": 2000}}
                ])");
    QTest::addRow("test3")
        << QStringLiteral("test3.duplicates.json")
        << QByteArray(R"({"a": [{"a": "212 555-1234"}, {"a": "646 555-4567"}]})");
}

void tst_qextJson::noLeakOnNameClash()
{
    QFETCH(QString, fileName);
    QFETCH(QByteArray, result);

    QFile file(testDataDir + u'/' + fileName);
    QVERIFY(file.open(QFile::ReadOnly));
    QByteArray testJson = file.readAll();
    QVERIFY(!testJson.isEmpty());

    QExtJsonParseError error;

    // Retains the last one of each set of duplicate keys.
    QExtJsonDocument doc = QExtJsonDocument::fromJson(testJson, &error);
    QVERIFY2(!doc.isNull(), qPrintable(error.errorString()));
    QExtJsonDocument expected = QExtJsonDocument::fromJson(result, &error);
    QVERIFY2(!expected.isNull(), qPrintable(error.errorString()));

    QCOMPARE(doc, expected);

    // It should not leak.
    // In particular it should not forget to deref the container for the inner objects.
}
#endif

QTEST_MAIN(tst_qextJson)
#include "tst_qextJson.moc"
