/******************************************************************************
 *
 * package:     Log4Qt
 * file:        log4qttest.cpp
 * created:     September 2007
 * author:      Martin Heinrich
 *
 *
 * Copyright 2007 Martin Heinrich
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/


// #include "log4qttest.h"

#include <qextLogBasicConfigurator.h>
#include <qextLogConsoleAppender.h>
#include <qextLogDailyRollingFileAppender.h>
#include <qextLogFileAppender.h>
#include <qextLogConfiguratorHelper.h>
#include <qextLogDatetime.h>
#include <qextLogFactory.h>
#include <qextLogInitialisationHelper.h>
#include <qextLogOptionConverter.h>
#include <qextLogPatternFormatter.h>
#include <qextLogProperties.h>
#include <qextLogManager.h>
#include <qextLoggerRepository.h>
#include <qextLogPatternLayout.h>
#include <qextLogPropertyConfigurator.h>
#include <qextLogRollingFileAppender.h>
#include <qextLogSimpleLayout.h>
#include <qextLogTTCCLayout.h>
#include <qextLogDenyAllFilter.h>
#include <qextLogLevelMatchFilter.h>
#include <qextLogLevelRangeFilter.h>
#include <qextLogStringMatchFilter.h>
#include <qextLogProperties.h>
#include <qextLogger.h>
#include <qextLogListAppender.h>

#include <QBuffer>
#include <QBitArray>
#include <QDataStream>
#include <QFile>
#include <QMetaEnum>
#include <QDateTime>
#include <QSettings>
#include <QTextStream>
#include <QThread>
#include <QDir>
#include <QObject>
#include <QtTest/QTest>

#if QT_VERSION >= 0x050E00
using Qt::endl;
#endif


/*!
 * \brief The class Log4QtTest provides a unit test for the package Log4Qt.
 *
 * The class Log4QtTest implements a unit test based on th Qt testing framework.
 */
class Log4QtTest : public QObject
{
    Q_OBJECT

public:
    explicit Log4QtTest(QObject *parent = QEXT_NULLPTR);
    virtual ~Log4QtTest();
private:
    Log4QtTest(const Log4QtTest &other); // Not implemented
    Log4QtTest &operator=(const Log4QtTest &other); // Not implemented

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    // log4qt
    void dateTime_alternativelyFormat_data();
    void dateTime_alternativelyFormat();

    void dateTime_milliseconds_data();
    void dateTime_milliseconds();
    void patternFormatter_data();
    void patternFormatter();
    void properties_default_data();
    void properties_default();
    void properties_names();
    void properties_load_device_data();
    void properties_load_device();
    void properties_load_settings();

    // QExtLogOptionConverter requires QExtLogProperties
    void optionConverter_boolean_data();
    void optionConverter_boolean();
    void optionConverter_filesize_data();
    void optionConverter_filesize();
    void optionConverter_int_data();
    void optionConverter_int();
    void optionConverter_level_data();
    void optionConverter_level();
    void optionConverter_substitution_data();
    void optionConverter_substitution();
    void optionConverter_target_data();
    void optionConverter_target();

    // QExtLogFactory requires QExtLogOptionConverter
    void factory_createAppender_data();
    void factory_createAppender();
    void factory_createFilter_data();
    void factory_createFilter();
    void factory_createLayout_data();
    void factory_createLayout();
    void factory_setObjectProperty_data();
    void factory_setObjectProperty();

    // log4qt/varia
    void listAppender();
    void denyAllFilter();
    void levelMatchFilter_data();
    void levelMatchFilter();
    void levelRangeFilter_data();
    void levelRangeFilter();
    void stringMatchFilter_data();
    void stringMatchFilter();
    void stringMatchFilterCaseInsensitive_data();
    void stringMatchFilterCaseInsensitive();

    // log4qt
    void appenderSkeleton_threshold();
    void appenderSkeleton_filter_data();
    void appenderSkeleton_filter();
    void basicConfigurator();
    void fileAppender();
    void dailyRollingFileAppender();
    void loggingEvent_stream_data();
    void loggingEvent_stream();
    void logManager_configureLogLogger();
    void propertyConfigurator_missing_appender();
    void propertyConfigurator_unknown_appender_class();
    void propertyConfigurator_missing_layout();
    void propertyConfigurator_unknown_layout_class();
    void propertyConfigurator_reset();
    void propertyConfigurator_debug();
    void propertyConfigurator_threshold();
    void propertyConfigurator_handleQtMessages();
    void propertyConfigurator_example();
    void rollingFileAppender();

private:
    QString dailyRollingFileAppenderSuffix(QDateTime dateTime);
    QString enumValueToKey(QObject *pObject,
                           const char *pEnumeration,
                           int value);
    void resetLogging();
    static bool compareStringLists(const QStringList &actual,
                                   const QStringList &expected,
                                   const QString &entry,
                                   const QString &entries,
                                   QString &result);
    static bool deleteDirectoryTree(const QString &name);
    static bool validateDirContents(const QString &name,
                                    const QStringList &expected,
                                    QString &result);
    static bool validateFileContents(const QString &name,
                                     const QStringList &expected,
                                     QString &result);

private:
    bool mSkipLongTests;
    QDir mTemporaryDirectory;
    QExtLogAppenderSharedPtr mpLoggingEvents;
    QExtLogProperties mDefaultProperties;
    QExtLogProperties mProperties;
    QExtLogListAppender *loggingEvents() const;
};

QTEST_MAIN(Log4QtTest)
QEXT_DECLARE_STATIC_LOGGER(test_logger, Test::TestLog4Qt)

Log4QtTest::Log4QtTest(QObject *parent) : QObject(parent),
    mSkipLongTests(false),
    mProperties(&mDefaultProperties)
{
#ifdef QEXT_DISABLE_LONG_TESTS
    mSkipLongTests = true;
#endif
}

Log4QtTest::~Log4QtTest() = default;

void Log4QtTest::initTestCase()
{
    // Logging
    QExtLogManager::resetConfiguration();

    // File system
    QString name = QDir::tempPath() + "/Log4QtTest_"
                   + QDateTime::currentDateTime().toString(QStringLiteral("yyyyMMdd_hhmmsszzz"));
    if (!mTemporaryDirectory.mkdir(name))
        QFAIL("Creation of temporary directory failed");
    mTemporaryDirectory.setPath(name);
    qDebug() << "Using temporaray directory: " << mTemporaryDirectory.path();

    // QExtLogAppender to track events generated by Log4Qt
    mpLoggingEvents.reset(new QExtLogListAppender(this));
    mpLoggingEvents->setName(QStringLiteral("Log4QtTest"));
    loggingEvents()->setConfiguratorList(true);
    resetLogging();
}


void Log4QtTest::cleanupTestCase()
{
    QExtLogManager::resetConfiguration();

    QTest::qWait(1000);
    if (!deleteDirectoryTree(mTemporaryDirectory.path()))
        QFAIL("Cleanup of temporary directory failed");
}

void Log4QtTest::dateTime_alternativelyFormat_data()
{
    QTest::addColumn<QString>("format");
    QTest::addColumn<QDateTime>("datetime");
    QTest::addColumn<QString>("datetimestring");
    QDateTime reference(QDate(2016, 5, 3), QTime(15, 7, 5, 9));
    qint64 diffTime = reference.toMSecsSinceEpoch() - QExtLogInitialisationHelper::startTime();
    QTest::newRow("EMPTY") << QString() << reference << QString();
    QTest::newRow("INVALID") << QStringLiteral("ISO8601") << QDateTime() << QString();
    QTest::newRow("NONE") << QStringLiteral("NONE") << reference << QString();
    QTest::newRow("RELATIVE") << QStringLiteral("RELATIVE") << reference << QString::number(diffTime);
    QTest::newRow("ISO8601") << QStringLiteral("ISO8601") << reference << QStringLiteral("2016-05-03 15:07:05.009");
    QTest::newRow("ABSOLUTE") << QStringLiteral("ABSOLUTE") << reference << QStringLiteral("15:07:05.009");
    QTest::newRow("DATE") << QStringLiteral("DATE") << reference << QStringLiteral("03 05 2016 15:07:05.009");
    QTest::newRow("CUSTOM1") << QStringLiteral("yyyy-MM-dd hh:mm:ss.zzz") << reference << QStringLiteral("2016-05-03 15:07:05.009");
}

void Log4QtTest::dateTime_alternativelyFormat()
{
    QFETCH(QString, format);
    QFETCH(QDateTime, datetime);
    QFETCH(QString, datetimestring);

    QCOMPARE(QExtLogDateTime(datetime).toString(format), datetimestring);
}

void Log4QtTest::dateTime_milliseconds_data()
{
    QTest::addColumn<QDateTime>("datetime");
    QTest::addColumn<qint64>("milliseconds");

    QTest::newRow("2001-09-07 15:07:05.009") << QDateTime(QDate(2001, 9, 7), QTime(15, 7, 5, 9), QTimeZone::utc()) << Q_INT64_C(999875225009);
}

void Log4QtTest::dateTime_milliseconds()
{
    QFETCH(QDateTime, datetime);
    QFETCH(qint64, milliseconds);

    QCOMPARE(QExtLogDateTime(datetime).toMSecsSinceEpoch(), milliseconds);
    QCOMPARE(QExtLogDateTime::fromMSecsSinceEpoch(milliseconds).toUTC(), datetime);
}

void Log4QtTest::patternFormatter_data()
{
    QTest::addColumn<QExtLoggingEvent>("event");
    QTest::addColumn<QString>("pattern");
    QTest::addColumn<QString>("result");
    QTest::addColumn<int>("event_count");

    // Create end of line
    QString eol;
#ifdef Q_OS_WIN
    eol = QStringLiteral("\n");
#else
    eol = QStringLiteral("\n");
#endif
    // Prepare event data
    int relative_offset = 17865;
    qint64 relative_timestamp = QExtLogInitialisationHelper::startTime() + relative_offset;
    QString relative_string = QString::number(relative_offset);
    qint64 absolute_timestamp =
        QExtLogDateTime(QDateTime(QDate(2001, 9, 7), QTime(15, 7, 5, 9))).toMSecsSinceEpoch();
    QHash<QString, QString> properties;
    properties.insert(QStringLiteral("A"), QStringLiteral("a"));
    properties.insert(QStringLiteral("B"), QStringLiteral("b"));
    properties.insert(QStringLiteral("C"), QStringLiteral("c"));

    QTest::newRow("Default conversion")
        << QExtLoggingEvent(test_logger(),
                            QExtLogLevel(QExtLogLevel::Debug),
                            QStringLiteral("This is the message"))
        << "%m%n"
        << "This is the message" + eol
        << 0;
    QTest::newRow("TTCC conversion")
        << QExtLoggingEvent(test_logger(),
                            QExtLogLevel(QExtLogLevel::Debug),
                            QStringLiteral("This is the message"),
                            QStringLiteral("QExtLogNDC"),
                            properties,
                            QStringLiteral("main"),
                            relative_timestamp)
        << "%r [%t] %p %c %x - %m%n"
        << relative_string + " [main] DEBUG Test::TestLog4Qt QExtLogNDC - This is the message" + eol
        << 0;
    QTest::newRow("Java class documentation example 1")
        << QExtLoggingEvent(test_logger(),
                            QExtLogLevel(QExtLogLevel::Warn),
                            QStringLiteral("This is the message"),
                            QStringLiteral("QExtLogNDC"),
                            properties,
                            QStringLiteral("main"),
                            relative_timestamp)
        << "%-5p [%t]: %m%n"
        << "WARN  [main]: This is the message" + eol
        << 0;
    QTest::newRow("Java class documentation example 2")
        << QExtLoggingEvent(test_logger(),
                            QExtLogLevel(QExtLogLevel::Info),
                            QStringLiteral("This is the message"),
                            QStringLiteral("QExtLogNDC"),
                            properties,
                            QStringLiteral("main"),
                            relative_timestamp)
        << "%r [%t] %-5p %c %x - %m%n"
        << relative_string + " [main] INFO  Test::TestLog4Qt QExtLogNDC - This is the message" + eol
        << 0;
    QTest::newRow("Java class documentation example 2")
        << QExtLoggingEvent(test_logger(),
                            QExtLogLevel(QExtLogLevel::Info),
                            QStringLiteral("This is the message"),
                            QStringLiteral("QExtLogNDC"),
                            properties,
                            QStringLiteral("main"),
                            relative_timestamp)
        << "%-6r [%15.15t] %-5p %30.30c %x - %m%n"
        << relative_string + "  [           main] INFO                Test::TestLog4Qt QExtLogNDC - This is the message" + eol
        << 0;
    QTest::newRow("Java class documentation example 2, truncating")
        << QExtLoggingEvent(test_logger(),
                            QExtLogLevel(QExtLogLevel::Info),
                            QStringLiteral("This is the message"),
                            QStringLiteral("QExtLogNDC"),
                            properties,
                            QStringLiteral("threadwithextralongname"),
                            relative_timestamp)
        << "%-6r [%15.15t] %-5p %30.30c %x - %m%n"
        << relative_string + "  [thextralongname] INFO                Test::TestLog4Qt QExtLogNDC - This is the message" + eol
        << 0;
    QTest::newRow("TTCC with ISO date")
        << QExtLoggingEvent(test_logger(),
                            QExtLogLevel(QExtLogLevel::Debug),
                            QStringLiteral("This is the message"),
                            QStringLiteral("QExtLogNDC"),
                            properties,
                            QStringLiteral("main"),
                            absolute_timestamp)
        << "%d{ISO8601} [%t] %p %c %x - %m%n"
        << "2001-09-07 15:07:05.009 [main] DEBUG Test::TestLog4Qt QExtLogNDC - This is the message" + eol
        << 0;
    QTest::newRow("TTCC conversion with file, line and method")
        << QExtLoggingEvent(test_logger(),
                            QExtLogLevel(QExtLogLevel::Debug),
                            QStringLiteral("This is the message"),
                            QStringLiteral("QExtLogNDC"),
                            properties,
                            QStringLiteral("main"),
                            relative_timestamp,
                            QExtLogMessageContext("foo.cpp", 100, "foo()"),
                            QStringLiteral("category")
                            )
        << "%r [%t] %p %c %F:%L-%M %x - %m%n"
        << relative_string + " [main] DEBUG Test::TestLog4Qt foo.cpp:100-foo() QExtLogNDC - This is the message" + eol
        << 0;
    QTest::newRow("TTCC conversion with location information")
        << QExtLoggingEvent(test_logger(),
                            QExtLogLevel(QExtLogLevel::Debug),
                            QStringLiteral("This is the message"),
                            QStringLiteral("QExtLogNDC"),
                            properties,
                            QStringLiteral("main"),
                            relative_timestamp,
                            QExtLogMessageContext("foo.cpp", 100, "foo()"),
                            QStringLiteral("category")
                            )
        << "%r [%t] %p %c %l %x - %m%n"
        << relative_string + " [main] DEBUG Test::TestLog4Qt foo.cpp:100 - foo() QExtLogNDC - This is the message" + eol
        << 0;
    QTest::newRow("TTCC conversion with file, line and method - Qt logger")
        << QExtLoggingEvent(QExtLogManager::instance()->qtLogger(),
                            QExtLogLevel(QExtLogLevel::Debug),
                            QStringLiteral("This is the message"),
                            QStringLiteral("QExtLogNDC"),
                            properties,
                            QStringLiteral("main"),
                            relative_timestamp,
                            QExtLogMessageContext("foo.cpp", 100, "foo()"),
                            QStringLiteral("Qt category")
                            )
        << "%r [%t] %p %c %F:%L-%M %x - %m%n"
        << relative_string + " [main] DEBUG Qt category foo.cpp:100-foo() QExtLogNDC - This is the message" + eol
        << 0;
    QTest::newRow("TTCC conversion with file, line and method - Qt logger no category")
        << QExtLoggingEvent(QExtLogManager::instance()->qtLogger(),
                            QExtLogLevel(QExtLogLevel::Debug),
                            QStringLiteral("This is the message"),
                            QStringLiteral("QExtLogNDC"),
                            properties,
                            QStringLiteral("main"),
                            relative_timestamp,
                            QExtLogMessageContext("foo.cpp", 100, "foo()"),
                            QString()
                            )
        << "%r [%t] %p %c %F:%L-%M %x - %m%n"
        << relative_string + " [main] DEBUG Qt foo.cpp:100-foo() QExtLogNDC - This is the message" + eol
        << 0;

    resetLogging();
}

void Log4QtTest::patternFormatter()
{
    QFETCH(QExtLoggingEvent, event);
    QFETCH(QString, pattern);
    QFETCH(QString, result);
    QFETCH(int, event_count);

    QExtLogPatternFormatter pattern_formatter(pattern);
    QCOMPARE(pattern_formatter.format(event), result);

    QCOMPARE(loggingEvents()->list().count(), event_count);
}

void Log4QtTest::properties_default_data()
{
    mDefaultProperties.clear();
    mDefaultProperties.setProperty(QStringLiteral("X"), QStringLiteral("x"));

    mProperties.clear();
    mProperties.setProperty(QStringLiteral("A"), QStringLiteral("a"));
    mProperties.setProperty(QStringLiteral("B"), QLatin1String(""));
    mProperties.setProperty(QStringLiteral("C"), QString());

    QTest::addColumn<QString>("key");
    QTest::addColumn<QString>("value");

    QTest::newRow("Existing value") << "A" << "a";
    QTest::newRow("Empty value") << "B" << "";
    QTest::newRow("Null value") << "C" << "";
    QTest::newRow("Default value") << "X" << "x";
    QTest::newRow("Non existing value") << "D" << QString();
}

void Log4QtTest::properties_default()
{
    QFETCH(QString, key);
    QFETCH(QString, value);

    QCOMPARE(mProperties.property(key), value);
}

void Log4QtTest::properties_names()
{
    mDefaultProperties.clear();
    mDefaultProperties.setProperty(QStringLiteral("X"), QStringLiteral("x"));

    mProperties.clear();
    mProperties.setProperty(QStringLiteral("A"), QStringLiteral("a"));
    mProperties.setProperty(QStringLiteral("B"), QLatin1String(""));

    QStringList property_names = mProperties.propertyNames();
    QCOMPARE(property_names.count(), 3);
    QVERIFY(property_names.contains("A"));
    QVERIFY(property_names.count("B"));
    QVERIFY(property_names.count("X"));
}


void Log4QtTest::properties_load_device_data()
{
    QTest::addColumn<QByteArray>("buffer");
    QTest::addColumn<int>("property_count");
    QTest::addColumn<QString>("key");
    QTest::addColumn<QString>("value");
    QTest::addColumn<int>("event_count");

    QByteArray buffer;
    QBuffer device(&buffer);
    QTextStream stream(&device);

    buffer.clear();
    device.open(QIODevice::WriteOnly);
    stream << "Truth = Beauty" << Qt::endl;
    device.close();
    QTest::newRow("Java class documentation example 1a")
        << buffer << 1 << "Truth" << "Beauty" << 0;

    buffer.clear();
    device.open(QIODevice::WriteOnly);
    stream << "         Truth:Beauty" << Qt::endl;
    device.close();
    QTest::newRow("Java class documentation example 1b")
        << buffer << 1 << "Truth" << "Beauty" << 0;

    buffer.clear();
    device.open(QIODevice::WriteOnly);
    stream << "Truth        :Beauty" << Qt::endl;
    device.close();
    QTest::newRow("Java class documentation example 1c")
        << buffer << 1 << "Truth" << "Beauty" << 0;

    buffer.clear();
    device.open(QIODevice::WriteOnly);
    stream << "fruits                apple, banana, pear, \\" << Qt::endl;
    stream << "                      cantaloupe, watermelon, \\" << Qt::endl;
    stream << "                      kiwi, mango" << Qt::endl;
    device.close();
    QTest::newRow("Java class documentation example 2")
        << buffer << 1 << "fruits"
        << "apple, banana, pear, cantaloupe, watermelon, kiwi, mango" << 0;

    buffer.clear();
    device.open(QIODevice::WriteOnly);
    stream << "cheese" << Qt::endl;
    device.close();
    QTest::newRow("Java class documentation example 3")
        << buffer << 1 << "cheese" << "" << 0;

    buffer.clear();
    device.open(QIODevice::WriteOnly);
    stream << "K\\ e\\=\\:y Value" << Qt::endl;
    device.close();
    QTest::newRow("Key escape sequences")
        << buffer << 1 << "K e=:y" << "Value" << 0;

    buffer.clear();
    device.open(QIODevice::WriteOnly);
    stream << "Key V\\t\\n\\ra\\\\l\\\"u\\\'e" << Qt::endl;
    device.close();
    QTest::newRow("Value escape sequences")
        << buffer << 1 << "Key" << "V\t\n\ra\\l\"u\'e" << 0;

    buffer.clear();
    device.open(QIODevice::WriteOnly);
    stream << "Key\\t Value\\j" << Qt::endl;
    device.close();
    QTest::newRow("Invalid escape sequences")
        << buffer << 1 << "Keyt" << "Valuej" << 2;

    buffer.clear();
    device.open(QIODevice::WriteOnly);
    stream << "Key Valu\\u006fe" << Qt::endl;
    device.close();
    QTest::newRow("Unicode escape sequence")
        << buffer << 1 << "Key" << "Valuoe" << 0;

    buffer.clear();
    device.open(QIODevice::WriteOnly);
    stream << "Key Value\\u6f" << Qt::endl;
    device.close();
    QTest::newRow("Unicode escape sequence at the end")
        << buffer << 1 << "Key" << "Valueo" << 0;

    buffer.clear();
    device.open(QIODevice::WriteOnly);
    stream << ": Value" << Qt::endl;
    device.close();
    QTest::newRow("Empty key")
        << buffer << 1 << "" << "Value" << 1;

    resetLogging();
}


void Log4QtTest::properties_load_device()
{
    QFETCH(QByteArray, buffer);
    QFETCH(int, property_count);
    QFETCH(QString, key);
    QFETCH(QString, value);
    QFETCH(int, event_count);

    loggingEvents()->clearList();

    QBuffer device(&buffer);
    QTextStream stream(&device);
    device.open(QIODevice::ReadOnly);

    QExtLogProperties properties;
    properties.load(&device);

    QCOMPARE(properties.count(), property_count);
    QVERIFY(properties.contains(key));
    QCOMPARE(properties.value(key), value);
    QCOMPARE(loggingEvents()->list().count(), event_count);
}


void Log4QtTest::properties_load_settings()
{
    QSettings settings(mTemporaryDirectory.path()
                       + "/PropetiesLoadSettings.ini", QSettings::IniFormat);
    QBitArray bit_array(5, true);

    settings.setValue(QStringLiteral("A"), "a");
    settings.setValue(QStringLiteral("Group/B"), "b");
    settings.setValue(QStringLiteral("Group/C"), true);
    settings.setValue(QStringLiteral("Group/D"), bit_array);
    settings.setValue(QStringLiteral("Group/Subgroup/E"), "e");

    settings.beginGroup(QStringLiteral("Group"));
    QExtLogProperties properties;
    properties.load(settings);

    QCOMPARE(properties.count(), 3);
    QVERIFY(properties.contains("B"));
    QCOMPARE(properties.value("B"), QString("b"));
    QVERIFY(properties.contains("C"));
    QCOMPARE(properties.value("C"), QString("true"));
    QVERIFY(properties.contains("D"));
    QCOMPARE(properties.value("D"), QString());
}

void Log4QtTest::optionConverter_boolean_data()
{
    QTest::addColumn<QString>("value");
    QTest::addColumn<bool>("default_value");
    QTest::addColumn<bool>("result");
    QTest::addColumn<int>("event_count");

    QTest::newRow("true") << "true" << false << true << 0;
    QTest::newRow("enabled") << "enabled" << false << true << 0;
    QTest::newRow("1") << "1" << false << true << 0;
    QTest::newRow("false") << "false" << true << false << 0;
    QTest::newRow("disabled") << "disabled" << true << false << 0;
    QTest::newRow("0") << "0" << true << false << 0;
    QTest::newRow("Case") << "tRuE" << false << true << 0;
    QTest::newRow("Trim") << " true " << false << true << 0;
    QTest::newRow("No Boolean") << "NoBool" << false << false << 1;

    resetLogging();
}


void Log4QtTest::optionConverter_boolean()
{
    QFETCH(QString, value);
    QFETCH(bool, default_value);
    QFETCH(bool, result);
    QFETCH(int, event_count);

    loggingEvents()->clearList();
    QCOMPARE(QExtLogOptionConverter::toBoolean(value, default_value), result);
    QCOMPARE(loggingEvents()->list().count(), event_count);
}


void Log4QtTest::optionConverter_filesize_data()
{
    QTest::addColumn<QString>("value");
    QTest::addColumn<bool>("result_ok");
    QTest::addColumn<qint64>("result");
    QTest::addColumn<int>("event_count");

    QTest::newRow("Int")
        << "135" << true << Q_INT64_C(135) << 0;
    QTest::newRow("Trim")
        << " 135 " << true << Q_INT64_C(135) << 0;
    QTest::newRow("KB")
        << "2KB" << true << Q_INT64_C(2048) << 0;
    QTest::newRow("KB case")
        << "2kb" << true << Q_INT64_C(2048) << 0;
    QTest::newRow("KB trim")
        << " 2KB " << true << Q_INT64_C(2048) << 0;
    QTest::newRow("MB")
        << "100MB" << true << Q_INT64_C(104857600) << 0;
    QTest::newRow("GB")
        << "2GB" << true << Q_INT64_C(2147483648) << 0;
    QTest::newRow("Invalid negative")
        << "-1" << false << Q_INT64_C(0) << 1;
    QTest::newRow("Invalid character")
        << "x" << false << Q_INT64_C(0) << 1;
    QTest::newRow("Invalid character with unit")
        << "xkb" << false << Q_INT64_C(0) << 1;
    QTest::newRow("Invalid additional text")
        << "2KBx" << false << Q_INT64_C(0) << 1;

    resetLogging();
}


void Log4QtTest::optionConverter_filesize()
{
    QFETCH(QString, value);
    QFETCH(bool, result_ok);
    QFETCH(qint64, result);
    QFETCH(int, event_count);

    loggingEvents()->clearList();
    bool ok;
    QCOMPARE(QExtLogOptionConverter::toFileSize(value, &ok), result);
    QCOMPARE(ok, result_ok);
    QCOMPARE(loggingEvents()->list().count(), event_count);
}


void Log4QtTest::optionConverter_int_data()
{
    QTest::addColumn<QString>("value");
    QTest::addColumn<bool>("result_ok");
    QTest::addColumn<int>("result");
    QTest::addColumn<int>("event_count");

    QTest::newRow("Positive") << "12" << true << 12 << 0;
    QTest::newRow("Negative") << "-1" << true << -1 << 0;
    QTest::newRow("Trim") << " 12 " << true << 12 << 0;
    QTest::newRow("No integer") << "12x" << false << 0 << 1;

    resetLogging();
}


void Log4QtTest::optionConverter_int()
{
    QFETCH(QString, value);
    QFETCH(bool, result_ok);
    QFETCH(int, result);
    QFETCH(int, event_count);

    loggingEvents()->clearList();
    bool ok;
    QCOMPARE(QExtLogOptionConverter::toInt(value, &ok), result);
    QCOMPARE(ok, result_ok);
    QCOMPARE(loggingEvents()->list().count(), event_count);
}


void Log4QtTest::optionConverter_level_data()
{
    QTest::addColumn<QString>("value");
    QTest::addColumn<QExtLogLevel>("default_value");
    QTest::addColumn<QExtLogLevel>("result");
    QTest::addColumn<int>("event_count");

    QTest::newRow("Case")
        << "WaRn"
        << QExtLogLevel(QExtLogLevel::Error)
        << QExtLogLevel(QExtLogLevel::Warn)
        << 0;
    QTest::newRow("Trim")
        << " warn "
        << QExtLogLevel(QExtLogLevel::Error)
        << QExtLogLevel(QExtLogLevel::Warn)
        << 0;
    QTest::newRow("Default")
        << "NoLevel"
        << QExtLogLevel(QExtLogLevel::Error)
        << QExtLogLevel(QExtLogLevel::Error)
        << 2; // One from QExtLogLevel + one from QExtLogOptionConverter

    resetLogging();
}


void Log4QtTest::optionConverter_level()
{
    QFETCH(QString, value);
    QFETCH(QExtLogLevel, default_value);
    QFETCH(QExtLogLevel, result);
    QFETCH(int, event_count);

    loggingEvents()->clearList();
    QCOMPARE(QExtLogOptionConverter::toLevel(value, default_value), result);
    QCOMPARE(loggingEvents()->list().count(), event_count);
}


void Log4QtTest::optionConverter_substitution_data()
{
    mDefaultProperties.clear();
    mProperties.clear();

    QTest::addColumn<QString>("key");
    QTest::addColumn<QString>("value");
    QTest::addColumn<QString>("result");
    QTest::addColumn<int>("event_count");

    QTest::newRow("Existing value")
        << "A" << "a" << "a" << 0;
    QTest::newRow("Existing value")
        << "B" << "b" << "b" << 0;
    QTest::newRow("Empty value")
        << "C" << "" << "" << 0;
    QTest::newRow("Null value")
        << "D" << QString() << "" << 0;
    QTest::newRow("Substitution")
        << "S1" << "begin${A}end" << "beginaend" << 0;
    QTest::newRow("Substitution with two values")
        << "S2" << "begin${A}end${B}" << "beginaendb" << 0;
    QTest::newRow("Substitution recursive")
        << "S3" << "${S1}" << "beginaend" << 0;
    QTest::newRow("Substitution missing bracket")
        << "S4" << "begin${end" << "begin" << 1;
    QTest::newRow("Substitution spare brackets")
        << "S5" << "begin}${A}}end" << "begin}a}end" << 0;
}


void Log4QtTest::optionConverter_substitution()
{
    QFETCH(QString, key);
    QFETCH(QString, value);
    QFETCH(QString, result);
    QFETCH(int, event_count);

    loggingEvents()->clearList();
    mProperties.setProperty(key, value);
    QCOMPARE(QExtLogOptionConverter::findAndSubst(mProperties, key), result);
    QCOMPARE(loggingEvents()->list().count(), event_count);
}


void Log4QtTest::optionConverter_target_data()
{
    QTest::addColumn<QString>("value");
    QTest::addColumn<bool>("result_ok");
    QTest::addColumn<int>("result");
    QTest::addColumn<int>("event_count");

    QTest::newRow("stdout cpp")
        << "Target_Stdout" << true << static_cast<int>(QExtLogConsoleAppender::Target_Stdout) << 0;
    QTest::newRow("stdout java")
        << "System.out" << true << static_cast<int>(QExtLogConsoleAppender::Target_Stdout) << 0;
    QTest::newRow("stderr cpp")
        << "Target_Stderr" << true << static_cast<int>(QExtLogConsoleAppender::Target_Stderr) << 0;
    QTest::newRow("stderr java")
        << "System.err" << true << static_cast<int>(QExtLogConsoleAppender::Target_Stderr) << 0;
    QTest::newRow("trim")
        << "  Target_Stdout  " << true << static_cast<int>(QExtLogConsoleAppender::Target_Stdout) << 0;
    QTest::newRow("error")
        << "Hello" << false << static_cast<int>(QExtLogConsoleAppender::Target_Stdout) << 1;
}


void Log4QtTest::optionConverter_target()
{
    QFETCH(QString, value);
    QFETCH(bool, result_ok);
    QFETCH(int, result);
    QFETCH(int, event_count);

    loggingEvents()->clearList();
    bool ok;
    QCOMPARE(QExtLogOptionConverter::toTarget(value, &ok), result);
    QCOMPARE(ok, result_ok);
    QCOMPARE(loggingEvents()->list().count(), event_count);
}



/******************************************************************************
 * QExtLogFactory requires QExtLogOptionConverter                                           */


void Log4QtTest::factory_createAppender_data()
{
    QTest::addColumn<QString>("classname");
    QTest::addColumn<QString>("result");
    QTest::addColumn<int>("event_count");

    QTest::newRow("QExtLogConsoleAppender java")
        << "org.QExt.LogConsoleAppender" << "QExtLogConsoleAppender" << 0;
    QTest::newRow("QExtLogConsoleAppender cpp")
        << "QExtLogConsoleAppender" << "QExtLogConsoleAppender" << 0;
    QTest::newRow("QExtLogDailyRollingFileAppender java")
        << "org.QExt.LogDailyRollingFileAppender" << "QExtLogDailyRollingFileAppender" << 0;
    QTest::newRow("QExtLogDailyRollingFileAppender cpp")
        << "QExtLogDailyRollingFileAppender" << "QExtLogDailyRollingFileAppender" << 0;
    QTest::newRow("QExtLogDebugAppender java")
        << "org.QExt.LogDebugAppender" << "QExtLogDebugAppender" << 0;
    QTest::newRow("QExtLogDebugAppender cpp")
        << "QExtLogDebugAppender" << "QExtLogDebugAppender" << 0;
    QTest::newRow("QExtLogFileAppender java")
        << "org.QExt.LogFileAppender" << "QExtLogFileAppender" << 0;
    QTest::newRow("QExtLogFileAppender cpp")
        << "QExtLogFileAppender" << "QExtLogFileAppender" << 0;
    QTest::newRow("QExtLogListAppender java")
        << "org.QExt.LogListAppender" << "QExtLogListAppender" << 0;
    QTest::newRow("QExtLogListAppender cpp")
        << "QExtLogListAppender" << "QExtLogListAppender" << 0;
    QTest::newRow("QExtLogNullAppender java")
        << "org.QExt.LogNullAppender" << "QExtLogNullAppender" << 0;
    QTest::newRow("QExtLogNullAppender cpp")
        << "QExtLogNullAppender" << "QExtLogNullAppender" << 0;
    QTest::newRow("QExtLogRollingFileAppender java")
        << "org.QExt.LogRollingFileAppender" << "QExtLogRollingFileAppender" << 0;
    QTest::newRow("QExtLogRollingFileAppender cpp")
        << "QExtLogRollingFileAppender" << "QExtLogRollingFileAppender" << 0;
}


void Log4QtTest::factory_createAppender()
{
    QFETCH(QString, classname);
    QFETCH(QString, result);
    QFETCH(int, event_count);

    loggingEvents()->clearList();
    QObject *p_object = QExtLogFactory::createAppender(classname);
    QVERIFY(p_object != QEXT_NULLPTR);
    QCOMPARE(QString::fromLatin1(p_object->metaObject()->className()), result);
    delete p_object;
    QCOMPARE(loggingEvents()->list().count(), event_count);
}


void Log4QtTest::factory_createFilter_data()
{
    QTest::addColumn<QString>("classname");
    QTest::addColumn<QString>("result");
    QTest::addColumn<int>("event_count");

    QTest::newRow("QExtLogDenyAllFilter java")
        << "org.QExt.LogDenyAllFilter" << "QExtLogDenyAllFilter" << 0;
    QTest::newRow("QExtLogDenyAllFilter cpp")
        << "QExtLogDenyAllFilter" << "QExtLogDenyAllFilter" << 0;
    QTest::newRow("QExtLogLevelMatchFilter java")
        << "org.QExt.LogLevelMatchFilter" << "QExtLogLevelMatchFilter" << 0;
    QTest::newRow("QExtLogLevelMatchFilter cpp")
        << "QExtLogLevelMatchFilter" << "QExtLogLevelMatchFilter" << 0;
    QTest::newRow("QExtLogLevelRangeFilter java")
        << "org.QExt.LogLevelRangeFilter" << "QExtLogLevelRangeFilter" << 0;
    QTest::newRow("QExtLogLevelRangeFilter cpp")
        << "QExtLogLevelRangeFilter" << "QExtLogLevelRangeFilter" << 0;
    QTest::newRow("QExtLogStringMatchFilter java")
        << "org.QExt.LogStringMatchFilter" << "QExtLogStringMatchFilter" << 0;
    QTest::newRow("QExtLogStringMatchFilter cpp")
        << "QExtLogStringMatchFilter" << "QExtLogStringMatchFilter" << 0;
}


void Log4QtTest::factory_createFilter()
{
    QFETCH(QString, classname);
    QFETCH(QString, result);
    QFETCH(int, event_count);

    loggingEvents()->clearList();
    QObject *p_object = QExtLogFactory::createFilter(classname);
    QVERIFY(p_object != QEXT_NULLPTR);
    QCOMPARE(QString::fromLatin1(p_object->metaObject()->className()), result);
    delete p_object;
    QCOMPARE(loggingEvents()->list().count(), event_count);
}


void Log4QtTest::factory_createLayout_data()
{
    QTest::addColumn<QString>("classname");
    QTest::addColumn<QString>("result");
    QTest::addColumn<int>("event_count");

    QTest::newRow("QExtLogPatternLayout java")
        << "org.QExt.LogPatternLayout" << "QExtLogPatternLayout" << 0;
    QTest::newRow("QExtLogPatternLayout cpp")
        << "QExtLogPatternLayout" << "QExtLogPatternLayout" << 0;
    QTest::newRow("QExtLogSimpleLayout java")
        << "org.QExt.LogSimpleLayout" << "QExtLogSimpleLayout" << 0;
    QTest::newRow("QExtLogSimpleLayout cpp")
        << "QExtLogSimpleLayout" << "QExtLogSimpleLayout" << 0;
    QTest::newRow("QExtLogTTCCLayout java")
        << "org.QExt.LogTTCCLayout" << "QExtLogTTCCLayout" << 0;
    QTest::newRow("QExtLogTTCCLayout cpp")
        << "QExtLogTTCCLayout" << "QExtLogTTCCLayout" << 0;
}


void Log4QtTest::factory_createLayout()
{
    QFETCH(QString, classname);
    QFETCH(QString, result);
    QFETCH(int, event_count);

    loggingEvents()->clearList();
    QObject *p_object = QExtLogFactory::createLayout(classname);
    QVERIFY(p_object != QEXT_NULLPTR);
    QCOMPARE(QString::fromLatin1(p_object->metaObject()->className()), result);
    delete p_object;
    QCOMPARE(loggingEvents()->list().count(), event_count);
}


void Log4QtTest::factory_setObjectProperty_data()
{
    QTest::addColumn<QString>("appenderclass");
    QTest::addColumn<QString>("property");
    QTest::addColumn<QString>("value");
    QTest::addColumn<QString>("result_value");
    QTest::addColumn<int>("event_count");

    QTest::newRow("Bool")
        << "QExtLogFileAppender"
        << "immediateFlush" << "false"
        << "false" << 0;
    QTest::newRow("Int")
        << "QExtLogListAppender"
        << "maxCount" << "10"
        << "10" << 0;
    QTest::newRow("QString")
        << "QExtLogFileAppender"
        << "file" << "C:\\tmp\\mylog.txt"
        << "C:\\tmp\\mylog.txt" << 0;
    QTest::newRow("Null object")
        << "QExtLogNullAppender"
        << "maxCount" << "10"
        << "" << 1;
    QTest::newRow("Empty property string")
        << "QExtLogNullAppender"
        << "" << "10"
        << "" << 1;
    QTest::newRow("Property does not exist")
        << "QExtLogNullAppender"
        << "Colour" << "10"
        << "" << 1;
    QTest::newRow("Property not writable")
        << "QExtLogNullAppender"
        << "isClosed" << "10"
        << "" << 1;
    QTest::newRow("Property of wrong type")
        << "QExtLogRollingFileAppender"
        << "maximumFileSize" << "7"
        << "" << 1;
}


void Log4QtTest::factory_setObjectProperty()
{
    QFETCH(QString, appenderclass);
    QFETCH(QString, property);
    QFETCH(QString, value);
    QFETCH(QString, result_value);
    QFETCH(int, event_count);

    loggingEvents()->clearList();
    QObject *p_object = QExtLogFactory::createAppender(appenderclass);

    QExtLogFactory::setObjectProperty(p_object, property, value);
    QCOMPARE(loggingEvents()->list().count(), event_count);
    if (loggingEvents()->list().count() == 0)
        QCOMPARE(p_object->property(property.toLatin1()).toString(), result_value);

    delete p_object;
}



/******************************************************************************
 * varia                                                               */


void Log4QtTest::listAppender()
{
    QExtLogListAppender appender;

    // Store messages
    QCOMPARE(appender.list().count(), 0);
    appender.doAppend(QExtLoggingEvent(test_logger(), QExtLogLevel::Warn, QStringLiteral("Message1")));
    appender.doAppend(QExtLoggingEvent(test_logger(), QExtLogLevel::Warn, QStringLiteral("Message2")));
    appender.doAppend(QExtLoggingEvent(test_logger(), QExtLogLevel::Warn, QStringLiteral("Message3")));
    QCOMPARE(appender.list().count(), 3);

    // Delete oldest, if max is set
    appender.setMaxCount(2);
    QCOMPARE(appender.list().count(), 2);
    QCOMPARE(appender.list().at(0).message(), QString("Message2"));
    QCOMPARE(appender.list().at(1).message(), QString("Message3"));

    // Ignore new ones added
    appender.doAppend(QExtLoggingEvent(test_logger(), QExtLogLevel::Warn, QStringLiteral("Message4")));
    QCOMPARE(appender.list().count(), 2);
    QCOMPARE(appender.list().at(0).message(), QString("Message2"));
    QCOMPARE(appender.list().at(1).message(), QString("Message3"));

    // Clear
    appender.clearList();
    QCOMPARE(appender.list().count(), 0);
}


void Log4QtTest::denyAllFilter()
{
    QExtLogDenyAllFilter filter;
    QExtLoggingEvent event(test_logger(), QExtLogLevel::Warn, QStringLiteral("Message"));
    QCOMPARE(filter.decide(event), QExtLogFilter::DENY);
}


void Log4QtTest::levelMatchFilter_data()
{
    QTest::addColumn<QString>("filter_level");
    QTest::addColumn<bool>("accept_on_match");
    QTest::addColumn<QString>("event_level");
    QTest::addColumn<QString>("result");

    QTest::newRow("No match, No accept") << "WARN" << false << "TRACE" << "NEUTRAL";
    QTest::newRow("No match, Accept") << "WARN" << true << "TRACE" << "NEUTRAL";
    QTest::newRow("Match, No accept") << "WARN" << false << "WARN" << "DENY";
    QTest::newRow("Match, Accept") << "WARN" << true << "WARN" << "ACCEPT";
}


void Log4QtTest::levelMatchFilter()
{
    QFETCH(QString, filter_level);
    QFETCH(bool, accept_on_match);
    QFETCH(QString, event_level);
    QFETCH(QString, result);

    QExtLogLevelMatchFilter filter;
    filter.setLevelToMatch(QExtLogLevel::fromString(filter_level));
    filter.setAcceptOnMatch(accept_on_match);
    QExtLoggingEvent
        event(test_logger(), QExtLogLevel::fromString(event_level),
              QStringLiteral("Message"));

    QString decision =
        enumValueToKey(&filter, "Decision", filter.decide(event));
    QCOMPARE(decision, result);
}


void Log4QtTest::levelRangeFilter_data()
{
    QTest::addColumn<QString>("filter_min_level");
    QTest::addColumn<QString>("filter_max_level");
    QTest::addColumn<bool>("accept_on_match");
    QTest::addColumn<QString>("event_level");
    QTest::addColumn<QString>("result");

    QTest::newRow("Too low, No accept") << "DEBUG" << "ERROR" << false << "TRACE" << "DENY";
    QTest::newRow("Too high, No accept") << "DEBUG" << "ERROR" << false << "FATAL" << "DENY";
    QTest::newRow("Min, No accept") << "DEBUG" << "ERROR" << false << "DEBUG" << "NEUTRAL";
    QTest::newRow("Inside, No accept") << "DEBUG" << "ERROR" << false << "WARN" << "NEUTRAL";
    QTest::newRow("Max, No accept") << "DEBUG" << "ERROR" << false << "ERROR" << "NEUTRAL";
    QTest::newRow("Min not initialised, No accept") << "" << "ERROR" << false << "TRACE" << "NEUTRAL";
    QTest::newRow("Max not initialised, No accept") << "DEBUG" << "" << false << "FATAL" << "NEUTRAL";
    QTest::newRow("Too low, Accept") << "DEBUG" << "ERROR" << true << "TRACE" << "DENY";
    QTest::newRow("Too high, Accept") << "DEBUG" << "ERROR" << true << "FATAL" << "DENY";
    QTest::newRow("Min, Accept") << "DEBUG" << "ERROR" << true << "DEBUG" << "ACCEPT";
    QTest::newRow("Inside, Accept") << "DEBUG" << "ERROR" << true << "WARN" << "ACCEPT";
    QTest::newRow("Max, Accept") << "DEBUG" << "ERROR" << true << "ERROR" << "ACCEPT";
    QTest::newRow("Min not initialised, Accept") << "" << "ERROR" << true << "TRACE" << "ACCEPT";
    QTest::newRow("Max not initialised, Accept") << "DEBUG" << "" << true << "FATAL" << "ACCEPT";
}


void Log4QtTest::levelRangeFilter()
{
    QFETCH(QString, filter_min_level);
    QFETCH(QString, filter_max_level);
    QFETCH(bool, accept_on_match);
    QFETCH(QString, event_level);
    QFETCH(QString, result);

    QExtLogLevelRangeFilter filter;
    if (!filter_min_level.isEmpty())
        filter.setLevelMin(QExtLogLevel::fromString(filter_min_level));
    if (!filter_max_level.isEmpty())
        filter.setLevelMax(QExtLogLevel::fromString(filter_max_level));
    filter.setAcceptOnMatch(accept_on_match);
    QExtLoggingEvent
        event(test_logger(), QExtLogLevel::fromString(event_level),
              QStringLiteral("Message"));

    QString decision =
        enumValueToKey(&filter, "Decision", filter.decide(event));
    QCOMPARE(decision, result);
}

void Log4QtTest::stringMatchFilter_data()
{
    QTest::addColumn<QString>("filter_string");
    QTest::addColumn<bool>("accept_on_match");
    QTest::addColumn<QString>("event_string");
    QTest::addColumn<QString>("result");

    QTest::newRow("No match, No accept") << "MESSAGE" << false << "This is a message" << "NEUTRAL";
    QTest::newRow("Match, No accept") << "This" << false << "This is a message" << "DENY";
    QTest::newRow("No match, Accept") << "MESSAGE" << true << "This is a message" << "NEUTRAL";
    QTest::newRow("Match, Accept") << "This" << true << "This is a message" << "ACCEPT";
    QTest::newRow("Empty message, No accept") << "This" << false << "" << "NEUTRAL";
    QTest::newRow("Empty message, Accept") << "This" << true << "" << "NEUTRAL";
    QTest::newRow("Empty filter, No accept") << "" << false << "This is a message" << "NEUTRAL";
    QTest::newRow("Empty filter, Accept") << "" << true << "This is a message" << "NEUTRAL";
}

void Log4QtTest::stringMatchFilter()
{
    QFETCH(QString, filter_string);
    QFETCH(bool, accept_on_match);
    QFETCH(QString, event_string);
    QFETCH(QString, result);

    QExtLogStringMatchFilter filter;
    filter.setStringToMatch(filter_string);
    filter.setAcceptOnMatch(accept_on_match);
    QExtLoggingEvent event(test_logger(), QExtLogLevel::Warn, event_string);

    QString decision =
        enumValueToKey(&filter, "Decision", filter.decide(event));
    QCOMPARE(decision, result);
}

void Log4QtTest::stringMatchFilterCaseInsensitive_data()
{
    QTest::addColumn<QString>("filter_string");
    QTest::addColumn<Qt::CaseSensitivity>("case_sensitivity");
    QTest::addColumn<bool>("accept_on_match");
    QTest::addColumn<QString>("event_string");
    QTest::addColumn<QString>("result");

    QTest::newRow("No match, CaseInsensitive, No accept") << "MESSAGES" << Qt::CaseInsensitive << false << "This is a message" << "NEUTRAL";
    QTest::newRow("Match, CaseInsensitive, No accept") << "MESSAGE" << Qt::CaseInsensitive << false << "This is a message" << "DENY";
    QTest::newRow("No Match, CaseInsensitive, Accept") << "MESSAGES" << Qt::CaseInsensitive << true << "This is a message" << "NEUTRAL";
    QTest::newRow("Match, CaseInsensitive, Accept") << "this" << Qt::CaseInsensitive << true << "This is a message" << "ACCEPT";
    QTest::newRow("Empty message, CaseInsensitive, No accept") << "This" << Qt::CaseInsensitive << false << "" << "NEUTRAL";
    QTest::newRow("Empty message, CaseInsensitive, Accept") << "This" << Qt::CaseInsensitive << true << "" << "NEUTRAL";
    QTest::newRow("Empty filter, CaseInsensitive, No accept") << "" << Qt::CaseInsensitive << false << "This is a message" << "NEUTRAL";
    QTest::newRow("Empty filter, CaseInsensitive, Accept") << "" << Qt::CaseInsensitive << true << "This is a message" << "NEUTRAL";
}


void Log4QtTest::stringMatchFilterCaseInsensitive()
{
    QFETCH(QString, filter_string);
    QFETCH(Qt::CaseSensitivity, case_sensitivity);
    QFETCH(bool, accept_on_match);
    QFETCH(QString, event_string);
    QFETCH(QString, result);

    QExtLogStringMatchFilter filter;
    filter.setStringToMatch(filter_string,case_sensitivity);
    filter.setAcceptOnMatch(accept_on_match);
    QExtLoggingEvent event(test_logger(), QExtLogLevel::Warn, event_string);

    QString decision =
        enumValueToKey(&filter, "Decision", filter.decide(event));
    QCOMPARE(decision, result);
}



/******************************************************************************
 * log4qt                                                                     */


void Log4QtTest::appenderSkeleton_threshold()
{
    resetLogging();

    auto *p_appender = new QExtLogListAppender();
    QExtLogger *p_logger = test_logger();
    p_logger->addAppender(p_appender);

    // Threshold
    p_appender->setThreshold(QExtLogLevel::Error);
    p_appender->doAppend(QExtLoggingEvent(p_logger, QExtLogLevel::Warn, QStringLiteral("Warn")));
    p_appender->doAppend(QExtLoggingEvent(p_logger, QExtLogLevel::Error, QStringLiteral("Error")));
    p_appender->doAppend(QExtLoggingEvent(p_logger, QExtLogLevel::Fatal, QStringLiteral("Fatal")));
    QCOMPARE(p_appender->list().count(), 2);
    QCOMPARE(p_appender->list().at(0).level(), QExtLogLevel(QExtLogLevel::Error));
    QCOMPARE(p_appender->list().at(1).level(), QExtLogLevel(QExtLogLevel::Fatal));
}


void Log4QtTest::appenderSkeleton_filter_data()
{
    resetLogging();

    QTest::addColumn<QString>("filter1_level");
    QTest::addColumn<bool>("filter1_accept");
    QTest::addColumn<QString>("filter2_level");
    QTest::addColumn<bool>("filter2_accept");
    QTest::addColumn<QString>("event_level");
    QTest::addColumn<int>("event_count");

    QTest::newRow("Single filter, NEUTRAL")
        << "WARN" << true << "" << true << "TRACE" << 1;
    QTest::newRow("Single filter, ACCEPT")
        << "WARN" << true << "" << true << "WARN" << 1;
    QTest::newRow("Single filter, DENY")
        << "WARN" << false << "" << true << "WARN" << 0;

    QTest::newRow("Double filter, NEUTRAL NEUTRAL")
        << "WARN" << true << "WARN" << true << "TRACE" << 1;
    QTest::newRow("Double filter, NEUTRAL ACCEPT")
        << "WARN" << true << "TRACE" << true << "TRACE" << 1;
    QTest::newRow("Double filter, NEUTRAL DENY")
        << "WARN" << true << "TRACE" << false << "TRACE" << 0;

    QTest::newRow("Double filter, ACCEPT NEUTRAL")
        << "WARN" << true << "TRACE" << true << "WARN" << 1;
    QTest::newRow("Double filter, ACCEPT ACCEPT")
        << "WARN" << true << "WARN" << true << "WARN" << 1;
    QTest::newRow("Double filter, ACCEPT DENY")
        << "WARN" << true << "WARN" << false << "WARN" << 1;

    QTest::newRow("Double filter, DENY NEUTRAL")
        << "WARN" << false << "TRACE" << true << "WARN" << 0;
    QTest::newRow("Double filter, DENY ACCEPT")
        << "WARN" << false << "WARN" << true << "WARN" << 0;
    QTest::newRow("Double filter, DENY DENY")
        << "WARN" << false << "WARN" << false << "WARN" << 0;
}


void Log4QtTest::appenderSkeleton_filter()
{
    QFETCH(QString, filter1_level);
    QFETCH(bool, filter1_accept);
    QFETCH(QString, filter2_level);
    QFETCH(bool, filter2_accept);
    QFETCH(QString, event_level);
    QFETCH(int, event_count);

    QExtLogListAppender appender;

    if (!filter1_level.isEmpty())
    {
        auto *filter = new QExtLogLevelMatchFilter();
        filter->setLevelToMatch(QExtLogLevel::fromString(filter1_level));
        filter->setAcceptOnMatch(filter1_accept);
        appender.addFilter(QExtLogFilterSharedPtr(filter));
    }
    if (!filter2_level.isEmpty())
    {
        auto *filter = new QExtLogLevelMatchFilter();
        filter->setLevelToMatch(QExtLogLevel::fromString(filter2_level));
        filter->setAcceptOnMatch(filter2_accept);
        appender.addFilter(QExtLogFilterSharedPtr(filter));
    }

    appender.doAppend(QExtLoggingEvent(test_logger(),
                                       QExtLogLevel::fromString(event_level), QStringLiteral("Message")));
    QCOMPARE(appender.list().count(), event_count);
}


void Log4QtTest::basicConfigurator()
{
    QExtLogManager::resetConfiguration();
    resetLogging();
    QVERIFY(QExtLogBasicConfigurator::configure());

    QExtLogger *p_logger = QExtLogManager::rootLogger();
    QCOMPARE(p_logger->appenders().count(), 1);
    auto *p_appender =
        qobject_cast<QExtLogConsoleAppender *>(p_logger->appenders().at(0).data());
    QCOMPARE(p_appender != QEXT_NULLPTR, true);
    QVERIFY(p_appender->isActive());
    QVERIFY(!p_appender->isClosed());
    QCOMPARE(p_appender->target(), QString::fromLatin1("Target_Stdout"));
    auto *p_layout =
        qobject_cast<QExtLogPatternLayout *>(p_appender->layout().data());
    QVERIFY(p_layout != QEXT_NULLPTR);
    QCOMPARE(p_layout->conversionPattern(), QString("%r [%t] %p %c %x - %m%n"));

    QExtLogger *logger = QExtLogManager::rootLogger();
    logger->trace(QStringLiteral("Trace message")); //Disabled by default
    logger->debug(QStringLiteral("Debug message"));
    logger->info(QStringLiteral("Info message"));
    logger->warn(QStringLiteral("Warn message"));
    logger->error(QStringLiteral("Error message"));
    logger->fatal(QStringLiteral("Fatal message"));
}


void Log4QtTest::fileAppender()
{
    resetLogging();

    QString dir(mTemporaryDirectory.path() + "/QExtLogFileAppender");
    QString file(QStringLiteral("/log"));

    QExtLogFileAppender appender1(QExtLogLayoutSharedPtr(new QExtLogSimpleLayout()), dir + file, false);
    appender1.setName(QStringLiteral("Fileappender1"));
    appender1.activateOptions();
    appender1.doAppend(QExtLoggingEvent(test_logger(), QExtLogLevel::Debug,
                                        QStringLiteral("Message 0")));
    appender1.doAppend(QExtLoggingEvent(test_logger(), QExtLogLevel::Debug,
                                        QStringLiteral("Message 1")));
    appender1.close();
    QStringList expected;
    QString result;
    expected << QStringLiteral("log");
    if (!validateDirContents(dir, expected, result))
        QFAIL(qPrintable(result));
    expected.clear();
    expected << QStringLiteral("DEBUG - Message 0") << QStringLiteral("DEBUG - Message 1");
    if (!validateFileContents(dir + file, expected, result))
        QFAIL(qPrintable(result));

    QExtLogFileAppender appender2(QExtLogLayoutSharedPtr(new QExtLogSimpleLayout()), dir + file, false);
    appender2.setName(QStringLiteral("Fileappender2"));
    appender2.activateOptions();
    appender2.doAppend(QExtLoggingEvent(test_logger(), QExtLogLevel::Debug,
                                        QStringLiteral("Message 2")));
    appender2.doAppend(QExtLoggingEvent(test_logger(), QExtLogLevel::Debug,
                                        QStringLiteral("Message 3")));
    appender2.close();
    expected.clear();
    expected << QStringLiteral("log");
    if (!validateDirContents(dir, expected, result))
        QFAIL(qPrintable(result));
    expected.clear();
    expected << QStringLiteral("DEBUG - Message 2") << QStringLiteral("DEBUG - Message 3");
    if (!validateFileContents(dir + file, expected, result))
        QFAIL(qPrintable(result));

    QExtLogFileAppender appender3(QExtLogLayoutSharedPtr(new QExtLogSimpleLayout()), dir + file, true);
    appender3.setName(QStringLiteral("Fileappender3"));
    appender3.activateOptions();
    appender3.doAppend(QExtLoggingEvent(test_logger(), QExtLogLevel::Debug,
                                        QStringLiteral("Message 4")));
    appender3.doAppend(QExtLoggingEvent(test_logger(), QExtLogLevel::Debug,
                                        QStringLiteral("Message 5")));
    appender3.close();
    expected.clear();
    expected << QStringLiteral("log");
    if (!validateDirContents(dir, expected, result))
        QFAIL(qPrintable(result));
    expected.clear();
    expected
        << QStringLiteral("DEBUG - Message 2") << QStringLiteral("DEBUG - Message 3")
        << QStringLiteral("DEBUG - Message 4") << QStringLiteral("DEBUG - Message 5");
    if (!validateFileContents(dir + file, expected, result))
        QFAIL(qPrintable(result));

    QCOMPARE(loggingEvents()->list().count(), 0);
}


void Log4QtTest::dailyRollingFileAppender()
{
    resetLogging();

    if (mSkipLongTests)
        QSKIP("Skipping long running test", SkipSingle);
    qDebug() << "The test is time based and takes approximately 3 minutes ...";

    QString dir(mTemporaryDirectory.path() + "/QExtLogDailyRollingFileAppender");
    QString file(QStringLiteral("/log"));

    // Using a QExtLogRollingFileAppender with 2 files history and 3 messages per file
    QExtLogDailyRollingFileAppender appender;
    appender.setName(QStringLiteral("QExtLogDailyRollingFileAppender"));
    appender.setFile(dir + file);
    appender.setLayout(QExtLogLayoutSharedPtr(new QExtLogSimpleLayout()));
    appender.setDatePattern(QExtLogDailyRollingFileAppender::MINUTELY_ROLLOVER);

    // Start on a full minute
    QDateTime now = QDateTime::currentDateTime();
    QTest::qSleep((60 - now.time().second()) * 1000);
    appender.activateOptions();

    qDebug() << "   1 / 7";
    appender.doAppend(QExtLoggingEvent(test_logger(), QExtLogLevel::Debug,
                                       QStringLiteral("Message 0")));
    int i;
    for (i = 1; i < 7; i++)
    {
        QTest::qSleep(21 * 1000);
        qDebug() << "  " << i + 1 << "/" << 7;
        appender.doAppend(QExtLoggingEvent(test_logger(), QExtLogLevel::Debug,
                                           QStringLiteral("Message %1").arg(i)));
    }

    QCOMPARE(loggingEvents()->list().count(), 0);

    // Validate directory
    QStringList expected;
    QString result;
    expected << QStringLiteral("log") << "log"
                                             + dailyRollingFileAppenderSuffix(now.addSecs(60)) << "log"
                    + dailyRollingFileAppenderSuffix(now.addSecs(120));
    if (!validateDirContents(dir, expected, result))
        QFAIL(qPrintable(result));

    // Validate files
    expected.clear();
    expected << QStringLiteral("DEBUG - Message 6");
    if (!validateFileContents(dir + file, expected, result))
        QFAIL(qPrintable(result));
    expected.clear();
    expected << QStringLiteral("DEBUG - Message 0") << QStringLiteral("DEBUG - Message 1")
             << QStringLiteral("DEBUG - Message 2");
    if (!validateFileContents(dir + file
                                  + dailyRollingFileAppenderSuffix(now.addSecs(60)),
                              expected, result))
        QFAIL(qPrintable(result));
    expected.clear();
    expected << QStringLiteral("DEBUG - Message 3") << QStringLiteral("DEBUG - Message 4")
             << QStringLiteral("DEBUG - Message 5");
    if (!validateFileContents(dir + file
                                  + dailyRollingFileAppenderSuffix(now.addSecs(120)),
                              expected, result))
        QFAIL(qPrintable(result));
}

void Log4QtTest::loggingEvent_stream_data()
{
    QTest::addColumn<QExtLoggingEvent>("original");

    qint64 timestamp =
        QExtLogDateTime(QDateTime(QDate(2001, 9, 7), QTime(15, 7, 5, 9))).toMSecsSinceEpoch();
    QHash<QString, QString> properties;
    properties.insert(QStringLiteral("A"), QStringLiteral("a"));
    properties.insert(QStringLiteral("B"), QStringLiteral("b"));
    properties.insert(QStringLiteral("C"), QStringLiteral("c"));

    QTest::newRow("Empty logging event")
        << QExtLoggingEvent();
    QTest::newRow("Logging event")
        << QExtLoggingEvent(test_logger(),
                            QExtLogLevel(QExtLogLevel::Warn),
                            QStringLiteral("This is a message"),
                            QStringLiteral("QExtLogNDC"),
                            properties,
                            QStringLiteral("main"),
                            timestamp);
    QTest::newRow("Logging no logger")
        << QExtLoggingEvent(QEXT_NULLPTR,
                            QExtLogLevel(QExtLogLevel::Warn),
                            QStringLiteral("This is a message"),
                            QStringLiteral("QExtLogNDC"),
                            properties,
                            QStringLiteral("main"),
                            timestamp);

    resetLogging();
}


void Log4QtTest::loggingEvent_stream()
{
    QFETCH(QExtLoggingEvent, original);

    QByteArray array;
    QBuffer buffer(&array);
    buffer.open(QIODevice::WriteOnly);
    QDataStream stream(&buffer);
    stream << original;
    buffer.close();

    buffer.open(QIODevice::ReadOnly);
    QExtLoggingEvent streamed;
    stream >> streamed;
    buffer.close();

    QCOMPARE(original.level(), streamed.level());
    QCOMPARE(original.loggename(), streamed.loggename());
    QCOMPARE(original.message(), streamed.message());
    QCOMPARE(original.ndc(), streamed.ndc());
    QCOMPARE(original.properties().count(), streamed.properties().count());
    const auto keys = original.properties().keys();
    for (const auto &key : keys)
    {
        QVERIFY(streamed.properties().contains(key));
        QCOMPARE(original.properties().value(key),
                 streamed.properties().value(key));
    }
    QCOMPARE(original.sequenceNumber(), streamed.sequenceNumber());
    QCOMPARE(original.threadName(), streamed.threadName());
    QCOMPARE(original.timeStamp(), streamed.timeStamp());

    QCOMPARE(loggingEvents()->list().count(), 0);
}

void Log4QtTest::logManager_configureLogLogger()
{
    resetLogging();
    QExtLogManager::logLogger()->removeAppender(mpLoggingEvents);

    QExtLogManager::resetConfiguration();
    QExtLogger *p_logger = QExtLogManager::logLogger();
    QCOMPARE(p_logger->appenders().count(), 2);
    QExtLogConsoleAppender *p_appender;
    QExtLogTTCCLayout *p_layout;

    p_appender = qobject_cast<QExtLogConsoleAppender *>(p_logger->appenders().at(0).data());
    QCOMPARE(p_appender != QEXT_NULLPTR, true);
    QVERIFY(p_appender->isActive());
    QVERIFY(!p_appender->isClosed());
    QCOMPARE(p_appender->target(), QString::fromLatin1("Target_Stdout"));
    p_layout = qobject_cast<QExtLogTTCCLayout *>(p_appender->layout().data());
    QVERIFY(p_layout != QEXT_NULLPTR);

    p_appender = qobject_cast<QExtLogConsoleAppender *>(p_logger->appenders().at(1).data());
    QCOMPARE(p_appender != QEXT_NULLPTR, true);
    QVERIFY(p_appender->isActive());
    QVERIFY(!p_appender->isClosed());
    QCOMPARE(p_appender->target(), QString::fromLatin1("Target_Stderr"));
    p_layout = qobject_cast<QExtLogTTCCLayout *>(p_appender->layout().data());
    QVERIFY(p_layout != QEXT_NULLPTR);

}


void Log4QtTest::propertyConfigurator_missing_appender()
{
    QExtLogManager::resetConfiguration();
    resetLogging();
    mDefaultProperties.clear();
    mProperties.clear();

    mProperties.setProperty(QStringLiteral("QExt.logger.MissingAppender"),
                            QStringLiteral("INHERITED, A"));
    QVERIFY(!QExtLogPropertyConfigurator::configure(mProperties));
    QCOMPARE(QExtLogConfiguratorHelper::configureError().count(), 1);
    QCOMPARE(loggingEvents()->list().count(), 1);
}


void Log4QtTest::propertyConfigurator_unknown_appender_class()
{
    QExtLogManager::resetConfiguration();
    resetLogging();
    mDefaultProperties.clear();
    mProperties.clear();

    mProperties.setProperty(QStringLiteral("QExt.logger.UnknownAppender"),
                            QStringLiteral("INHERITED, A"));
    mProperties.setProperty(QStringLiteral("QExtLogging.Appender.A"),
                            QStringLiteral("org.QExt.LogUnknownAppender"));
    QVERIFY(!QExtLogPropertyConfigurator::configure(mProperties));
    QCOMPARE(QExtLogConfiguratorHelper::configureError().count(), 1);
    QCOMPARE(loggingEvents()->list().count(), 2); // Warning from QExtLogFactory, Error QExtLogPropertyConfigurator
}


void Log4QtTest::propertyConfigurator_missing_layout()
{
    resetLogging();
    mDefaultProperties.clear();
    mProperties.clear();

    mProperties.setProperty(QStringLiteral("QExt.logger.MissingLayout"),
                            QStringLiteral("INHERITED, A"));
    mProperties.setProperty(QStringLiteral("QExtLogging.Appender.A"),
                            QStringLiteral("org.QExt.LogConsoleAppender"));
    QVERIFY(!QExtLogPropertyConfigurator::configure(mProperties));
    QCOMPARE(QExtLogConfiguratorHelper::configureError().count(), 1);
    QCOMPARE(loggingEvents()->list().count(), 1);
}


void Log4QtTest::propertyConfigurator_unknown_layout_class()
{
    resetLogging();
    mDefaultProperties.clear();
    mProperties.clear();

    mProperties.setProperty(QStringLiteral("QExt.logger.UnknownLayout"),
                            QStringLiteral("INHERITED, A"));
    mProperties.setProperty(QStringLiteral("QExt.appender.A"),
                            QStringLiteral("org.QExt.LogConsoleAppender"));
    mProperties.setProperty(QStringLiteral("QExt.appender.A.layout"),
                            QStringLiteral("org.QExt.LogUnknownLayout"));
    QVERIFY(!QExtLogPropertyConfigurator::configure(mProperties));
    QCOMPARE(QExtLogConfiguratorHelper::configureError().count(), 1);
    QCOMPARE(loggingEvents()->list().count(), 2); // Warning from QExtLogFactory, Error QExtLogPropertyConfigurator
}


void Log4QtTest::propertyConfigurator_reset()
{
    resetLogging();
    mDefaultProperties.clear();
    mProperties.clear();

    // - Create a logger with an appender
    // - If the reset flag is not set, configure must leave the appender
    // - If the reset flag is set to an invalid value, configure must raise an
    //   error and leave the appender
    // - If the reset flag is set, configure must remove the appender

    const QLatin1String key_reset("QExtLogging.reset");
    test_logger()->addAppender(new QExtLogListAppender);
    mProperties.setProperty(key_reset,
                            QStringLiteral("false"));
    QVERIFY(QExtLogPropertyConfigurator::configure(mProperties));
    QCOMPARE(QExtLogConfiguratorHelper::configureError().count(), 0);
    QCOMPARE(loggingEvents()->list().count(), 0);
    QCOMPARE(test_logger()->appenders().count(), 1);

    mProperties.setProperty(key_reset,
                            QStringLiteral("No boolean"));
    QVERIFY(!QExtLogPropertyConfigurator::configure(mProperties));
    QCOMPARE(QExtLogConfiguratorHelper::configureError().count(), 1);
    QCOMPARE(loggingEvents()->list().count(), 1);
    QCOMPARE(test_logger()->appenders().count(), 1);

    resetLogging();
    mProperties.setProperty(key_reset,
                            QStringLiteral("true"));
    QVERIFY(QExtLogPropertyConfigurator::configure(mProperties));
    QCOMPARE(QExtLogConfiguratorHelper::configureError().count(), 0);
    QCOMPARE(loggingEvents()->list().count(), 0);
    QCOMPARE(test_logger()->appenders().count(), 0);
}


void Log4QtTest::propertyConfigurator_debug()
{
    resetLogging();
    mDefaultProperties.clear();
    mProperties.clear();

    // - Set the log logger level to INFO
    // - If debug is not set, configure must leave the log logger level
    //   unaltered
    // - If debug is set, but with no valid level string, configure must set
    //   the log logger level to DEBUG
    // - If debug is set to the level TRACE, configure must set the log logger
    //   level to TRACE

    const QLatin1String key_debug("QExtLogging.Debug");
    QExtLogger *p_logger = QExtLogManager::logLogger();
    p_logger->setLevel(QExtLogLevel::Info);

    QVERIFY(QExtLogPropertyConfigurator::configure(mProperties));
    QCOMPARE(QExtLogConfiguratorHelper::configureError().count(), 0);
    QCOMPARE(loggingEvents()->list().count(), 0);
    QCOMPARE(p_logger->level(), QExtLogLevel(QExtLogLevel::Info));

    mProperties.setProperty(key_debug,
                            QStringLiteral("true"));
    QVERIFY(QExtLogPropertyConfigurator::configure(mProperties));
    QCOMPARE(QExtLogConfiguratorHelper::configureError().count(), 0);
    // QCOMPARE(loggingEvents()->list().count(), 1); // Warning from QExtLogLevel::fromString() & several debug messages
    QCOMPARE(p_logger->level(), QExtLogLevel(QExtLogLevel::Debug));

    loggingEvents()->clearList();
    mProperties.setProperty(key_debug,
                            QStringLiteral("TRACE"));
    QVERIFY(QExtLogPropertyConfigurator::configure(mProperties));
    QCOMPARE(QExtLogConfiguratorHelper::configureError().count(), 0);
    // QCOMPARE(loggingEvents()->list().count(), 1); // Warning from QExtLogPropertyConfigurator & several debug/trace messages
    QCOMPARE(p_logger->level(), QExtLogLevel(QExtLogLevel::Trace));
}


void Log4QtTest::propertyConfigurator_threshold()
{
    resetLogging();
    mDefaultProperties.clear();
    mProperties.clear();

    // - Set the repository threshold to INFO
    // - If the threshold is not set, configure must leave the repository
    //   threshold unaltered
    // - If the threshold is set to an invalid value, configure must raise an
    //   error and set the threshold to ALL
    // - If the threshold is set to WARN, configure must set the repository
    //   threshold to WARN

    const QLatin1String key_threshold("QExtLogging.Threshold");
    QExtLogManager::loggerRepository()->setThreshold(QExtLogLevel::Info);

    QVERIFY(QExtLogPropertyConfigurator::configure(mProperties));
    QCOMPARE(QExtLogConfiguratorHelper::configureError().count(), 0);
    QCOMPARE(loggingEvents()->list().count(), 0);
    QCOMPARE(QExtLogManager::loggerRepository()->threshold(), QExtLogLevel(QExtLogLevel::Info));

    mProperties.setProperty(key_threshold,
                            QStringLiteral("Not a value"));
    QVERIFY(!QExtLogPropertyConfigurator::configure(mProperties));
    QCOMPARE(QExtLogConfiguratorHelper::configureError().count(), 1);
    QCOMPARE(loggingEvents()->list().count(), 2); // Warning by QExtLogLevel, Error from QExtLogOptionConverter
    QCOMPARE(QExtLogManager::loggerRepository()->threshold(), QExtLogLevel(QExtLogLevel::All));

    loggingEvents()->clearList();
    mProperties.setProperty(key_threshold,
                            QStringLiteral("WARN"));
    QVERIFY(QExtLogPropertyConfigurator::configure(mProperties));
    QCOMPARE(QExtLogConfiguratorHelper::configureError().count(), 0);
    QCOMPARE(loggingEvents()->list().count(), 0);
    QCOMPARE(QExtLogManager::loggerRepository()->threshold(), QExtLogLevel(QExtLogLevel::Warn));
}


void Log4QtTest::propertyConfigurator_handleQtMessages()
{
    resetLogging();
    mDefaultProperties.clear();
    mProperties.clear();

    // - Set handle Qt messages to true
    // - If handle Qt messages is not set, configure must leave handle Qt
    //   messages unaltered
    // - If handle Qt messages is set to an invalid value, configure must raise
    //   an error and set handle Qt messages to false
    // - If handle Qt messages is true, configure must set handle Qt messages
    //   to true

    const QLatin1String key_handle_qt_messages("QExtLogging.HandleQtMessages");
    QExtLogManager::setHandleQtMessages(true);

    QVERIFY(QExtLogPropertyConfigurator::configure(mProperties));
    QCOMPARE(QExtLogConfiguratorHelper::configureError().count(), 0);
    QCOMPARE(loggingEvents()->list().count(), 0);
    QCOMPARE(QExtLogManager::handleQtMessages(), true);

    mProperties.setProperty(key_handle_qt_messages,
                            QStringLiteral("No boolean"));
    QVERIFY(!QExtLogPropertyConfigurator::configure(mProperties));
    QCOMPARE(QExtLogConfiguratorHelper::configureError().count(), 1);
    QCOMPARE(loggingEvents()->list().count(), 1);
    QCOMPARE(QExtLogManager::handleQtMessages(), false);

    loggingEvents()->clearList();
    mProperties.setProperty(key_handle_qt_messages,
                            QStringLiteral("true"));
    QVERIFY(QExtLogPropertyConfigurator::configure(mProperties));
    QCOMPARE(QExtLogConfiguratorHelper::configureError().count(), 0);
    QCOMPARE(loggingEvents()->list().count(), 0);
    QCOMPARE(QExtLogManager::handleQtMessages(), true);
}


void Log4QtTest::propertyConfigurator_example()
{
    QExtLogManager::resetConfiguration();
    resetLogging();
    mDefaultProperties.clear();
    mProperties.clear();

    QString file(mTemporaryDirectory.path() + "/QExtLogPropertyConfigurator/log");

    // Based on the JavaDoc example:
    // - A1: JavaDoc uses SyslogAppender, which is not available on all platforms
    // - A2: JavaDoc does not set a file, which causes error on activation
    // - A2: JavaDoc uses default values for file size and backup index. Use
    //       different values.
    // - A2 QExtLogLayout: ContextPrinting uses default enabled. Use disabled instead.
    // - root: JavaDoc uses default level DEBUG. Use INFO instead.
    // - SECURITY: JavaDoc uses INHERIT. Use INHERITED instead
    // - QExtLogging.Logger.class.of.the.day: JavaDoc uses INHERIT. Use INHERITED
    //   instead

    // QExtLogAppender A1: QExtLogConsoleAppender with QExtLogPatternLayout
    mProperties.setProperty(QStringLiteral("QExtLogging.Appender.A1"),
                            QStringLiteral("org.QExt.LogConsoleAppender"));
    mProperties.setProperty(QStringLiteral("QExtLogging.Appender.A1.Target"), QStringLiteral("System.Out"));
    mProperties.setProperty(QStringLiteral("QExtLogging.Appender.A1.Layout"),
                            QStringLiteral("org.QExt.LogPatternLayout"));
    mProperties.setProperty(QStringLiteral("QExtLogging.Appender.A1.layout.ConversionPattern"),
                            QStringLiteral("%-4r %-5p %c{2} %M.%L %x - %m\n"));
    // QExtLogAppender A2: QExtLogRollingFileAppender with QExtLogTTCCLayout
    mProperties.setProperty(QStringLiteral("QExtLogging.Appender.A2"),
                            QStringLiteral("org.QExt.LogRollingFileAppender"));
    mProperties.setProperty(QStringLiteral("QExtLogging.Appender.A2.File"), file);
    mProperties.setProperty(QStringLiteral("QExtLogging.Appender.A2.MaxFileSize"), QStringLiteral("13MB"));
    mProperties.setProperty(QStringLiteral("QExtLogging.Appender.A2.MaxBackupIndex"), QStringLiteral("7"));
    mProperties.setProperty(QStringLiteral("QExtLogging.Appender.A2.Layout"),
                            QStringLiteral("org.QExt.LogTTCCLayout"));
    mProperties.setProperty(QStringLiteral("QExtLogging.Appender.A2.Layout.ContextPrinting"),
                            QStringLiteral("disabled"));
    mProperties.setProperty(QStringLiteral("QExtLogging.Appender.A2.Layout.DateFormat"), QStringLiteral("ISO8601"));
    // Root QExtLogger: Uses A2
    mProperties.setProperty(QStringLiteral("QExtLogging.RootLogger"), QStringLiteral("INFO, A2"));
    // QExtLogger SECURITY: Uses A1
    mProperties.setProperty(QStringLiteral("QExtLogging.Logger.SECURITY"), QStringLiteral("INHERITED, A1"));
    mProperties.setProperty(QStringLiteral("QExtLogging.Additivity.SECURITY"), QStringLiteral("false"));
    // QExtLogger SECURITY.access:
    mProperties.setProperty(QStringLiteral("QExtLogging.Logger.SECURITY.access"), QStringLiteral("WARN"));
    // QExtLogger class.of.the.day:
    mProperties.setProperty(QStringLiteral("QExtLogging.Logger.Class.Of.The.Day"), QStringLiteral("INHERITED"));

    // No warnings, no errors expected
    QVERIFY(QExtLogPropertyConfigurator::configure(mProperties));
    QCOMPARE(QExtLogConfiguratorHelper::configureError().count(), 0);
    QCOMPARE(loggingEvents()->list().count(), 0);

    // Root logger
    QExtLogger *p_logger = QExtLogManager::rootLogger();
    QCOMPARE(p_logger->level(), QExtLogLevel(QExtLogLevel::Info));
    QCOMPARE(p_logger->appenders().count(), 1);
    auto *p_a2 =
        qobject_cast<QExtLogRollingFileAppender *>(p_logger->appenders().at(0).data());
    QVERIFY(p_a2 != QEXT_NULLPTR);
    QCOMPARE(p_a2->file(), file);
    QCOMPARE(p_a2->maximumFileSize(), Q_INT64_C(13 * 1024 * 1024));
    QCOMPARE(p_a2->maxBackupIndex(), 7);
    auto *p_a2layout =
        qobject_cast<QExtLogTTCCLayout *>(p_a2->layout().data());
    QVERIFY(p_a2layout != QEXT_NULLPTR);
    QCOMPARE(p_a2layout->contextPrinting(), false);
    QCOMPARE(p_a2layout->dateFormat(), QString::fromLatin1("ISO8601"));

    // QExtLogger SECURITY
    QVERIFY(QExtLogManager::exists("SECURITY"));
    p_logger = QExtLogManager::logger(QStringLiteral("SECURITY"));
    QCOMPARE(p_logger->level(), QExtLogLevel(QExtLogLevel::Null));
    QCOMPARE(p_logger->appenders().count(), 1);
    auto *p_a1 =
        qobject_cast<QExtLogConsoleAppender *>(p_logger->appenders().at(0).data());
    QVERIFY(p_a1 != QEXT_NULLPTR);
    QCOMPARE(p_a1->target(), QString::fromLatin1("Target_Stdout"));
    auto *p_a1layout =
        qobject_cast<QExtLogPatternLayout *>(p_a1->layout().data());
    QVERIFY(p_a1layout != QEXT_NULLPTR);
    QCOMPARE(p_a1layout->conversionPattern(), QString::fromLatin1("%-4r %-5p %c{2} %M.%L %x - %m\n"));

    // QExtLogger SECURITY::access
    QVERIFY(QExtLogManager::exists("SECURITY::access"));
    p_logger = QExtLogManager::logger(QStringLiteral("SECURITY::access"));
    QCOMPARE(p_logger->level(), QExtLogLevel(QExtLogLevel::Warn));

    // QExtLogger class::of::the::day
    QVERIFY(QExtLogManager::exists("class::of::the::day"));
}

void Log4QtTest::rollingFileAppender()
{
    resetLogging();

    QString dir(mTemporaryDirectory.path() + "/QExtLogRollingFileAppender");
    QString file(QStringLiteral("/log"));

    // Using a QExtLogRollingFileAppender with 2 files history and 3 messages per file
    QExtLogRollingFileAppender appender;
    appender.setName(QStringLiteral("QExtLogRollingFileAppender"));
    appender.setFile(dir + file);
    appender.setLayout(QExtLogLayoutSharedPtr(new QExtLogSimpleLayout()));
    appender.setMaxBackupIndex(2);
    appender.setMaximumFileSize(40);
    appender.activateOptions();

    // Output 9 messages
    int i;
    for (i = 0; i < 10; i++)
        appender.doAppend(QExtLoggingEvent(test_logger(), QExtLogLevel::Debug,
                                           QStringLiteral("Message %1").arg(i)));

    // No warnings or errors expected
    QCOMPARE(loggingEvents()->list().count(), 0);

    // Validate diretcory
    QStringList expected;
    QString result;
    expected << QStringLiteral("log") << QStringLiteral("log.1") << QStringLiteral("log.2");
    if (!validateDirContents(dir, expected, result))
        QFAIL(qPrintable(result));

    // Validate files
    expected.clear();
    expected << QStringLiteral("DEBUG - Message 9");
    if (!validateFileContents(dir + file, expected, result))
        QFAIL(qPrintable(result));
    expected.clear();
    expected << QStringLiteral("DEBUG - Message 6") << QStringLiteral("DEBUG - Message 7")
             << QStringLiteral("DEBUG - Message 8");
    if (!validateFileContents(dir + file + ".1", expected, result))
        QFAIL(qPrintable(result));
    expected.clear();
    expected << QStringLiteral("DEBUG - Message 3") << QStringLiteral("DEBUG - Message 4")
             << QStringLiteral("DEBUG - Message 5");
    if (!validateFileContents(dir + file + ".2", expected, result))
        QFAIL(qPrintable(result));

    QCOMPARE(loggingEvents()->list().count(), 0);
}


QString Log4QtTest::dailyRollingFileAppenderSuffix(QDateTime dateTime)
{
    QString result(QStringLiteral("."));
    result += QString::number(dateTime.date().year()).rightJustified(4, '0');
    result += '-';
    result += QString::number(dateTime.date().month()).rightJustified(2, '0');
    result += '-';
    result += QString::number(dateTime.date().day()).rightJustified(2, '0');
    result += '-';
    result += QString::number(dateTime.time().hour()).rightJustified(2, '0');
    result += '-';
    result += QString::number(dateTime.time().minute()).rightJustified(2, '0');
    return result;
}


QString Log4QtTest::enumValueToKey(QObject *pObject,
                                   const char *pEnumeration,
                                   int value)
{
    Q_ASSERT(pObject);
    Q_ASSERT(!QString(pEnumeration).isEmpty());

    int i = pObject->metaObject()->indexOfEnumerator(pEnumeration);
    Q_ASSERT(i >= 0);
    QMetaEnum enumerator = pObject->metaObject()->enumerator(i);
    Q_ASSERT(enumerator.isValid());
    QString result = enumerator.valueToKey(value);
    Q_ASSERT(!result.isNull());
    return result;
}


void Log4QtTest::resetLogging()
{
    QExtLogger *p_logger;

    // Log4Qt logger
    p_logger = QExtLogManager::logLogger();
    p_logger->setAdditivity(false);
    p_logger->setLevel(QExtLogLevel::Warn);
    p_logger->removeAllAppenders();

    // Log4QtTest appender
    p_logger->addAppender(mpLoggingEvents);
    loggingEvents()->clearList();
    loggingEvents()->clearFilters();
    loggingEvents()->setThreshold(QExtLogLevel::Warn);

    // Test logger
    p_logger = test_logger();
    p_logger->setAdditivity(true);
    p_logger->setLevel(QExtLogLevel::Null);
}


bool Log4QtTest::compareStringLists(const QStringList &actual,
                                    const QStringList &expected,
                                    const QString &entry,
                                    const QString &entries,
                                    QString &result)
{
    QString tab(QStringLiteral("   "));
    QString eol(QStringLiteral("\n"));

    // Generate content string
    QString content;
    int i;
    content += tab + "Actual: " + entries + ": "
               + QString::number(actual.count()) + eol;
    for (i = 0; i < actual.count(); i++)
        content += tab + tab + '\'' + actual.at(i) + '\'' + eol;
    content += tab + "Expected: " + entries + ": "
               + QString::number(expected.count()) + eol;
    for (i = 0; i < expected.count(); i++)
        content += tab + tab + '\'' + expected.at(i) + '\'' + eol;

    // Check count
    if (actual.count() != expected.count())
    {
        result = tab + "Compared " + entry + " counts are not the same" + eol;
        result += content;
        return false;
    }

    // Check entries
    for (i = 0; i < actual.count(); i++)
    {
        if (actual.at(i) != expected.at(i))
        {
            result = tab + entry + " " + QString::number(i + 1)
            + " is not the same" + eol;
            result += content;
            return false;
        }
    }

    result.clear();
    return true;
}


bool Log4QtTest::deleteDirectoryTree(const QString &name)
{
    QFileInfo file_info(name);
    if (!file_info.exists())
        return true;
    if (file_info.isDir())
    {
        QDir d(name);
        const QStringList members = d.entryList(QDir::Dirs | QDir::Files
                                                    | QDir::NoDotAndDotDot | QDir::NoSymLinks
                                                    | QDir::Hidden, QDir::Name | QDir::DirsFirst);
        for (const auto &member : members)
            if (!deleteDirectoryTree(name + '/' + member))
                return false;
        if (d.rmdir(name))
            return true;
        qDebug() << "Unable to remove directory: " << name;
        return false;
    }

    QFile f(name);
    if (f.remove())
        return true;

    qDebug() << "Unable to remove file: " << name << "("
             << f.errorString() << ")";
    return false;
}


bool Log4QtTest::validateDirContents(const QString &name,
                                     const QStringList &expected,
                                     QString &result)
{
    QDir dir(name);
    if (!dir.exists())
    {
        result = QStringLiteral("The dir '%1' does not exist").arg(name);
        return false;
    }

    QStringList actual = dir.entryList(QDir::Dirs | QDir::Files
                                           | QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Hidden,
                                       QDir::Name | QDir::DirsFirst);
    if (!compareStringLists(actual, expected, QStringLiteral("Entry"), QStringLiteral("Entries"), result))
    {
        QString error =
            QStringLiteral("The directory contents validation failed.\n   '%1'\n%2");
        result = error.arg(name, result);
        return false;
    }

    return true;
}


bool Log4QtTest::validateFileContents(const QString &name,
                                      const QStringList &expected,
                                      QString &result)
{
    QFile file(name);
    if (!file.exists())
    {
        result = QStringLiteral("The expected file '%1' does not exist (%2)").arg(name, file.errorString());
        return false;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        result = QStringLiteral("The expected file '%1' cannot be opened (%2)").arg(name, file.errorString());
        return false;
    }

    QStringList actual;
    QTextStream textstream(&file);
    QString line = textstream.readLine();
    while (!line.isNull())
    {
        actual << line;
        line = textstream.readLine();
    }
    if (!compareStringLists(actual, expected, QStringLiteral("Line"), QStringLiteral("Lines"), result))
    {
        QString error = QStringLiteral("The file contents validation failed.\n   '%1'\n%2");
        result = error.arg(name, result);
        return false;
    }

    return true;
}

QExtLogListAppender *Log4QtTest::loggingEvents() const
{
    return qobject_cast<QExtLogListAppender *>(mpLoggingEvents.data());
}

#include "tst_Logging.moc"
