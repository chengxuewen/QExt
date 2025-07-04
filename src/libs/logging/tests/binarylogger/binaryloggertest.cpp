#include <QtTest/QTest>

#include "testappender.h"

#include <qextLogger.h>
#include <qextLogManager.h>
#include <qextLogTTCCLayout.h>
#include <qextLogConsoleAppender.h>
#include <qextLoggerRepository.h>
#include <qextLogSimpleLayout.h>
#include <qextLogLevelRangeFilter.h>
#include <qextLogDenyAllFilter.h>

#include <qextLogBinaryEventFilter.h>
#include <qextLogBinaryToTextLayout.h>
#include <qextLogBinaryLayout.h>
#include <qextBinaryLoggingEvent.h>
#include <qextLogBinaryWriterAppender.h>
#include <qextLogBinaryFileAppender.h>
#include <qextBinaryLogStream.h>
#include <qextLogBinaryLogger.h>

#include "atscopeexit.h"
#include "elementsinarray.h"

#include <QDataStream>
#include <QTemporaryFile>

const auto loggingLevel = QExtLogLevel::All; // set to Off to enable logging to the console;
static const char binLogger[] = "binlogger";

class BinaryLoggerTest: public QObject
{
    Q_OBJECT
    QEXT_DECLARE_QCLASS_BINARYLOGGER
public:
    explicit BinaryLoggerTest(QObject *parent = QEXT_NULLPTR)
        : QObject(parent)
        , mAppender{QEXT_NULLPTR}
    {
    }

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void init();

    void testBinaryToTextLayout();
    void testBinaryEventFilter();
    void testBinaryWriterAppender();
    void testBinaryFileAppender();
    void testBinaryLogStream();
    void testBinaryLogger();
    void testBinaryClassLogger();
    void testBinaryLayout();

private:
    TestAppender *mAppender;
    class AppenderData
    {
    public:
        void setAppender(QExtLogBinaryWriterAppender *newAppender)
        {
            appender = newAppender;
        }

        void reset()
        {
            data.clear();
            pds.reset(new QDataStream(&data, QIODevice::WriteOnly));
            pds->setByteOrder(QDataStream::LittleEndian);
            Q_ASSERT_X(!appender.isNull(), __FUNCTION__, "No QExtLogAppender");
            appender->setWriter(pds.data());
            appender->activateOptions();
        }

        QByteArray flush()
        {
            return data;
        }

    private:
        QByteArray data;
        QScopedPointer<QDataStream> pds;
        QPointer<QExtLogBinaryWriterAppender> appender;
    } mAppenderData[3];
    QMap<QString, int> mLoggenameToAppenderDataIndex;

    AppenderData &getAppenderDataFromLogger(QExtLogger *plogger)
    {
        auto loggename = plogger->name();

        if (!mLoggenameToAppenderDataIndex.contains(loggename))
            mLoggenameToAppenderDataIndex.insert(loggename, mLoggenameToAppenderDataIndex.size());

        return mAppenderData[mLoggenameToAppenderDataIndex[loggename]];
    }

    void log(const QByteArray &data, const QString &loggename = QString{})
    {
        auto mylogger = QExtLogger::logger(loggename);
        QExtBinaryLoggingEvent event(mylogger, QExtLogLevel::Info, data);
        mylogger->callAppenders(event);
    }

    void configureLogger(QExtLogger *mylogger)
    {
        auto &appenderData = getAppenderDataFromLogger(mylogger);
        auto writerAppender = new QExtLogBinaryWriterAppender(mylogger);
        writerAppender->setName(QString{QStringLiteral("QExtLogAppender for '%1'")} .arg(mylogger->name()));
        appenderData.setAppender(writerAppender);
        mylogger->addAppender(writerAppender);
        mylogger->setAdditivity(false);
        mylogger->setLevel(QExtLogLevel::All);
    }

    QByteArray flushLogger(QExtLogger *mylogger)
    {
        return getAppenderDataFromLogger(mylogger).flush();
    }
};

QEXT_DECLARE_STATIC_BINARYLOGGER(unitTestLogger, StaticBinaryLogger)

void BinaryLoggerTest::initTestCase()
{
    QExtLogger *rootLogger = QExtLogger::rootLogger();
    QExtLogManager::setHandleQtMessages(true);

    QExtLogLayoutSharedPtr layout(new QExtLogTTCCLayout(rootLogger));
    static_cast<QExtLogTTCCLayout *>(layout.data())->setDateFormat(QStringLiteral("dd.MM.yyyy hh:mm:ss.zzz"));
    static_cast<QExtLogTTCCLayout *>(layout.data())->setContextPrinting(false);

    QExtLogLayoutSharedPtr binlayout(new QExtLogBinaryToTextLayout(layout, rootLogger));

    auto *consoleAppender = new QExtLogConsoleAppender(rootLogger);
    consoleAppender->setLayout(binlayout);
    consoleAppender->setTarget(QExtLogConsoleAppender::STDOUT_TARGET);
    consoleAppender->activateOptions();

    QExtLogFilter *denyall = new QExtLogDenyAllFilter;
    denyall->activateOptions();
    auto *levelFilter = new QExtLogLevelRangeFilter(rootLogger);
    levelFilter->setNext(QExtLogFilterSharedPtr(denyall));
    levelFilter->setLevelMin(QExtLogLevel::Null);
    levelFilter->setLevelMax(loggingLevel);
    levelFilter->activateOptions();
    consoleAppender->addFilter(QExtLogFilterSharedPtr(levelFilter));
    rootLogger->addAppender(consoleAppender);

    // add appender for tests
    QExtLogLayoutSharedPtr simpleLayout(new QExtLogSimpleLayout(rootLogger));
    QExtLogLayoutSharedPtr binlayout1(new QExtLogBinaryToTextLayout(simpleLayout, rootLogger));
    auto *appender = new TestAppender(rootLogger);
    appender->setLayout(binlayout1);
    appender->activateOptions();
    mAppender = appender;
    rootLogger->addAppender(appender);

    configureLogger(QExtLogger::logger(binLogger));
    configureLogger(unitTestLogger());
    configureLogger(logger());

    QCOMPARE(rootLogger->metaObject()->className(), "QExtLogger");
    QCOMPARE(QExtLogger::logger(binLogger)->metaObject()->className(), "QExtLogger");
    QCOMPARE(unitTestLogger()->metaObject()->className(), "QExtBinaryLogger");
    QCOMPARE(logger()->metaObject()->className(), "QExtBinaryLogger");
}

void BinaryLoggerTest::cleanupTestCase()
{
    QExtLogger::logger(binLogger)->removeAllAppenders();
    unitTestLogger()->removeAllAppenders();
    logger()->removeAllAppenders();

    QExtLogger::rootLogger()->info(QStringLiteral("Unit test logger was shutdown."));
    QExtLogger::rootLogger()->removeAllAppenders();
    QExtLogger::rootLogger()->loggerRepository()->shutdown();
}

void BinaryLoggerTest::init()
{
    for (auto &appenderData : mAppenderData)
        appenderData.reset();
}

void BinaryLoggerTest::testBinaryToTextLayout()
{
    log("Hello world!");
    auto list = mAppender->clearList();
    QCOMPARE(list.size(), 1);
    auto result = list.at(0);
    QVERIFY(result.contains(QStringLiteral("12 bytes: 48 65 6c 6c 6f 20 77 6f 72 6c 64 21")));
}

void BinaryLoggerTest::testBinaryEventFilter()
{
    auto blogger = QExtLogger::rootLogger();
    QExtLogFilter *denyall = new QExtLogDenyAllFilter;
    denyall->activateOptions();

    auto *binfilter = new QExtLogBinaryEventFilter(blogger);

    binfilter->setAcceptBinaryEvents(true);
    binfilter->setNext(QExtLogFilterSharedPtr(denyall));
    binfilter->activateOptions();

    mAppender->addFilter(QExtLogFilterSharedPtr(binfilter));

    auto _ = createScopeExitGuard([this, binfilter] {mAppender->removeEventFilter(binfilter);});

    log("Hello world!");
    auto list = mAppender->clearList();
    QCOMPARE(list.size(), 1);
    QVERIFY(list.at(0).contains("12 bytes: 48 65 6c 6c 6f 20 77 6f 72 6c 64 21"));

    binfilter->setAcceptBinaryEvents(false);

    log("Hello world!");
    QVERIFY(mAppender->clearList().isEmpty());

}

void BinaryLoggerTest::testBinaryWriterAppender()
{
    auto blogger = QExtLogger::logger(binLogger);

    blogger->debug(QStringLiteral("Hello world!"));
    char expected[] = {0x18, 0x00, 0x00, 0x00, 0x48, 0x00, 0x65, 0x00,
                       0x6C, 0x00, 0x6C, 0x00, 0x6F, 0x00, 0x20, 0x00,
                       0x77, 0x00, 0x6F, 0x00, 0x72, 0x00, 0x6C, 0x00,
                       0x64, 0x00, 0x21, 0x00
                      };
    QCOMPARE(flushLogger(blogger), QByteArray(expected, elementsInArray(expected)));

    QExtBinaryLoggingEvent event(blogger, QExtLogLevel::Info, QByteArray("\0\1\2\3", 4));
    blogger->callAppenders(event);
    char expected1[] = {0x18, 0x00, 0x00, 0x00, 0x48, 0x00, 0x65, 0x00,
                        0x6C, 0x00, 0x6C, 0x00, 0x6F, 0x00, 0x20, 0x00,
                        0x77, 0x00, 0x6F, 0x00, 0x72, 0x00, 0x6C, 0x00,
                        0x64, 0x00, 0x21, 0x00, 0x04, 0x00, 0x00, 0x00,
                        0x00, 0x01, 0x02, 0x03
                       };
    QCOMPARE(flushLogger(blogger), QByteArray(expected1, elementsInArray(expected1)));
}

void BinaryLoggerTest::testBinaryFileAppender()
{
    auto blogger = QExtLogger::logger(binLogger);

    QTemporaryFile file;
    QVERIFY(file.open());
    file.close();
    QExtLogBinaryFileAppender *bfa = new QExtLogBinaryFileAppender(file.fileName(), blogger);
    bfa->activateOptions();
    blogger->addAppender(bfa);

    auto _ = createScopeExitGuard([blogger, bfa] {blogger->removeAppender(bfa);});

    blogger->debug(QStringLiteral("Hello world!"));
    QExtBinaryLoggingEvent event(blogger, QExtLogLevel::Info, QByteArray("\0\1\2\3", 4));
    blogger->callAppenders(event);

    char expected[] = {0x18, 0x00, 0x00, 0x00, 0x48, 0x00, 0x65, 0x00,
                       0x6c, 0x00, 0x6c, 0x00, 0x6f, 0x00, 0x20, 0x00,
                       0x77, 0x00, 0x6f, 0x00, 0x72, 0x00, 0x6c, 0x00,
                       0x64, 0x00, 0x21, 0x00, 0x04, 0x00, 0x00, 0x00,
                       0x00, 0x01, 0x02, 0x03
                      };

    bfa->close();
    QVERIFY(file.open());
    QByteArray data = file.readAll();
    QCOMPARE(data, QByteArray(expected, elementsInArray(expected)));
}

void BinaryLoggerTest::testBinaryLogStream()
{
    char expected[] = {0x1d, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x40,
                       0x0d, 0x00, 0x00, 0x00, 0x48, 0x65, 0x6c, 0x6c,
                       0x6f, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21,
                       0x00
                      };
    {
        QExtLogBinaryStream bls{QExtLogger::logger(binLogger), QExtLogLevel::Info};
        bls << QByteArray(expected + 4, 4);
        bls << QByteArray(expected + 8, 8)
            << QByteArray(expected + 16, 4)
            << QByteArray(expected + 20, 13);
    }

    auto blogger = QExtLogger::logger(binLogger);
    QCOMPARE(flushLogger(blogger), QByteArray(expected, elementsInArray(expected)));
}

void BinaryLoggerTest::testBinaryLogger()
{
    auto ulogger = unitTestLogger();

    ulogger->debug(QByteArray("Hello world!"));

    char expected[] = {0x0c, 0x00, 0x00, 0x00, 0x48, 0x65, 0x6c, 0x6c,
                       0x6f, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21
                      };

    QCOMPARE(flushLogger(ulogger), QByteArray(expected, elementsInArray(expected)));
}

void BinaryLoggerTest::testBinaryClassLogger()
{
    auto clogger = logger();

    clogger->debug(QByteArray("Hello world!"));

    char expected[] = {0x0c, 0x00, 0x00, 0x00, 0x48, 0x65, 0x6c, 0x6c,
                       0x6f, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21
                      };

    QCOMPARE(flushLogger(clogger), QByteArray(expected, elementsInArray(expected)));
}

void BinaryLoggerTest::testBinaryLayout()
{
    auto clogger = logger();
    auto appender = new QExtLogBinaryWriterAppender(clogger);
    auto layout = new QExtLogBinaryLayout(appender);
    layout->setBinaryHeader("This is the header:");
    layout->setBinaryFooter(":This is the footer");
    appender->setLayout(QExtLogLayoutSharedPtr(layout));
    clogger->addAppender(appender);
    auto _ = createScopeExitGuard([clogger, appender] {clogger->removeAppender(appender);});
    QByteArray data;
    QDataStream ds(&data, QIODevice::WriteOnly);
    ds.setByteOrder(QDataStream::LittleEndian);
    appender->setWriter(&ds);
    appender->activateOptions();

    clogger->debug("Hello world!");
    appender->close();

    char expected[] =
    {
        0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x74, 0x68, 0x65, 0x20, 0x68, 0x65, 0x61, 0x64, 0x65, 0x72, 0x3a,
        0x0c, 0x00, 0x00, 0x00, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21,
        0x3a, 0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x74, 0x68, 0x65, 0x20, 0x66, 0x6f, 0x6f, 0x74, 0x65, 0x72
    };
    QCOMPARE(QByteArray(expected, elementsInArray(expected)), data);
}

QTEST_GUILESS_MAIN(BinaryLoggerTest)

#include "binaryloggertest.moc"
