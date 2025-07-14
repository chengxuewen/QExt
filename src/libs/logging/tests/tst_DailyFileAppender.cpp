#include <qextLogDailyFileAppender.h>
#include <qextLogSimpleLayout.h>
#include <qextLoggingEvent.h>

#include <QDate>
#include <QSharedPointer>
#include <QTemporaryDir>
#include <QtTest/QTest>

namespace
{

class DateRetrieverMock final : public QExtLogDateRetrieverInterface
{
public:
    QDate currentDate() const QEXT_OVERRIDE
    {
        return mCurrentDate;
    }

    void setCurrentDate(const QDate currentDate)
    {
        mCurrentDate = currentDate;
    }

private:
    QDate mCurrentDate = QDate(2019, 1, 15);
};

}

class DailyFileAppenderTest : public QObject
{
    Q_OBJECT
public:
    explicit DailyFileAppenderTest(QObject * parent = QEXT_NULLPTR) :
                                QObject(parent),
                                mLogDirectory(QEXT_NULLPTR),
                                mAppender(QEXT_NULLPTR) {}
private Q_SLOTS:
    void init();
    void cleanup();

    void testFileCreation_data();
    void testFileCreation();
    void testAppend();
    void testRollOver();
    void testObsoleteLogFileDeletion();

private:
    QTemporaryDir *mLogDirectory;
    QSharedPointer<DateRetrieverMock> mDateRetriever;
    QExtLogDailyFileAppender *mAppender;
};

void DailyFileAppenderTest::init()
{
    mLogDirectory = new QTemporaryDir;

    mDateRetriever.reset(new DateRetrieverMock);

    mAppender = new QExtLogDailyFileAppender;
    mAppender->setLayout(QExtLogLayoutSharedPtr(new QExtLogSimpleLayout));

    mAppender->setDateRetriever(mDateRetriever);
}

void DailyFileAppenderTest::cleanup()
{
    delete mAppender;
    delete mLogDirectory;  // destructor will remove temporary directory
}

void DailyFileAppenderTest::testFileCreation_data()
{
    QTest::addColumn<QString>("appName");
    QTest::addColumn<QString>("datePattern");
    QTest::addColumn<QString>("fileName");

    QTest::newRow("default") << "app" << "_yyyy_MM_dd" << "app_2019_07_09.log";
    QTest::newRow("Austria") << "app" << "_dd.MM.yyyy" << "app_09.07.2019.log";
    QTest::newRow("service") << "srv" << "_yyyy_MM_dd" << "srv_2019_07_09.log";
}

void DailyFileAppenderTest::testFileCreation()
{
    mDateRetriever->setCurrentDate(QDate(2019, 7, 9));

    QFETCH(QString, appName);
    QFETCH(QString, datePattern);
    QFETCH(QString, fileName);

    mAppender->setDatePattern(datePattern);
    mAppender->setFile(mLogDirectory->path() + QLatin1Char('/') + appName +  QStringLiteral(".log"));

    mAppender->activateOptions();

    const QFileInfo fileInfo(mAppender->file());

    QVERIFY(fileInfo.exists());

    QCOMPARE(fileInfo.fileName(), fileName);
}

void DailyFileAppenderTest::testAppend()
{
    mAppender->setFile(mLogDirectory->path() + QLatin1Char('/') + QStringLiteral("app.log"));
    mAppender->activateOptions();

    const auto fileName = mAppender->file();

    QVERIFY(QFileInfo::exists(fileName));

    const QFile logFile(fileName);

    // nothing written yet
    QCOMPARE(logFile.size(), 0);

    mAppender->append(QExtLoggingEvent());

    QVERIFY(logFile.size() > 0);
}

void DailyFileAppenderTest::testRollOver()
{
    mAppender->setFile(mLogDirectory->path() + QLatin1Char('/') + QStringLiteral("app.log"));
    mAppender->activateOptions();

    mAppender->append(QExtLoggingEvent());

    const auto fileNameDay1 = mAppender->file();
    QVERIFY(QFileInfo::exists(fileNameDay1));

    // one day has passed ...
    mDateRetriever->setCurrentDate(mDateRetriever->currentDate().addDays(1));

    // ... and when we try to append ...
    mAppender->append(QExtLoggingEvent());

    // ... we get a new log file
    const auto fileNameDay2 = mAppender->file();

    QVERIFY(QFileInfo::exists(fileNameDay2));
    QVERIFY(fileNameDay1 != fileNameDay2);
}

namespace
{

void createFile(const QString& fileName)
{
    QFile file(fileName);
    QVERIFY(file.open(QFile::WriteOnly));
    file.close();
    QVERIFY2(file.exists(), qPrintable(fileName));
}

}

void DailyFileAppenderTest::testObsoleteLogFileDeletion()
{
    const QString deleteOnActivateFileName = mLogDirectory->path() + QLatin1Char('/') + QStringLiteral("app_2019_01_05.log");

    createFile(deleteOnActivateFileName);

    const QString deleteAfterOneDayFileName = mLogDirectory->path() + QLatin1Char('/') + QStringLiteral("app_2019_01_06.log");

    createFile(deleteAfterOneDayFileName);

    const QString alwaysKeptFileName = mLogDirectory->path() + QLatin1Char('/') + QStringLiteral("app_2019_01_07.log");

    createFile(alwaysKeptFileName);

    mDateRetriever->setCurrentDate(QDate(2019, 01, 10));

    mAppender->setFile(mLogDirectory->path() + QLatin1Char('/') + QStringLiteral("app.log"));

    mAppender->setDatePattern(QStringLiteral("_yyyy_MM_dd"));
    mAppender->setKeepDays(4);

    // after configuration ...
    mAppender->activateOptions();

    // ... we delete obsolete files
    QVERIFY(!QFileInfo::exists(deleteOnActivateFileName));
    QVERIFY(QFileInfo::exists(deleteAfterOneDayFileName));
    QVERIFY(QFileInfo::exists(alwaysKeptFileName));

    // appending later today ...
    mAppender->append(QExtLoggingEvent());

    // ... does not delete anything
    QVERIFY(QFileInfo::exists(deleteAfterOneDayFileName));
    QVERIFY(QFileInfo::exists(alwaysKeptFileName));

    // one day has passed ...
    mDateRetriever->setCurrentDate(mDateRetriever->currentDate().addDays(1));

    // ... and we append additional messages ...
    mAppender->append(QExtLoggingEvent());

    // ... one file becomes obsolete and is deleted automatically
    // Since deletion takes place in a separate thread, we would need to sleep here. To avoid that,
    // we rely on the appender to wait for completion in its destructor
    delete mAppender;
    mAppender = QEXT_NULLPTR;
    QVERIFY(!QFileInfo::exists(deleteAfterOneDayFileName));
    QVERIFY(QFileInfo::exists(alwaysKeptFileName));
}

QTEST_GUILESS_MAIN(DailyFileAppenderTest)

#include "tst_DailyFileAppender.moc"
