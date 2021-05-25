#ifndef QEXTTESTRUNNER_H
#define QEXTTESTRUNNER_H

#include <QDir>
#include <QObject>
#include <QDebug>
#include <QProcess>
#include <QPointer>
#include <QElapsedTimer>
#include <QFileInfo>

#define QEXT_ALL_TEST_SPACE_PLACEHOLDER         "        "
#define QEXT_ALL_TEST_NOTICE_PLACEHOLDER        ">>>>>>>>"
#define QEXT_ALL_TEST_PLACEHOLDER_NUM           8

class QEXTTestRunner : public QObject
{
    Q_OBJECT
public:
    QEXTTestRunner(const QFileInfo &testInfo, int index, bool outPutAll)
        : m_testInfo(testInfo), m_index(index), m_consumingTime(0), m_outPutAll(outPutAll) {
        connect(&m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(onReadData()));
        connect(&m_process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onFinished(int,QProcess::ExitStatus)));
        m_process.setReadChannel(QProcess::StandardOutput);
        m_process.setWorkingDirectory(testInfo.dir().absolutePath());
    }

    void runTest() {
        m_process.start(QString("./%1").arg(m_testInfo.fileName()));
        m_elapsedTimer.start();
    }

    QFileInfo testInfo() const { return m_testInfo; }
    qint64 consumingTime() const { return m_consumingTime; }
    int index() const { return m_index; }
    int exitCode() const { return m_exitCode; }
    QProcess::ExitStatus exitStatus() const { return m_exitStatus; }
    QList<QByteArray> testDataList() const { return m_testDataList; }

signals:
    void testFinished(int exitCode, QProcess::ExitStatus exitStatus);

public Q_SLOTS:
    void onFinished(int exitCode, QProcess::ExitStatus exitStatus) {
        m_consumingTime = m_elapsedTimer.elapsed();
        m_elapsedTimer.invalidate();
        m_exitCode = exitCode;
        m_exitStatus = exitStatus;
        emit this->testFinished(exitCode, exitStatus);
    }

    void onReadData() {
        QList<QByteArray> dataList = m_process.readAllStandardOutput().split('\n');
        m_testDataList.append(dataList);
        QListIterator<QByteArray> iter(dataList);
        while (iter.hasNext()) {
            QByteArray data = iter.next();
            if (!data.isEmpty()) {
                if (m_outPutAll || data.contains("FAIL") || data.contains("Loc")) {
                    qDebug() << QString("       %1%2").arg(QEXT_ALL_TEST_SPACE_PLACEHOLDER).arg(data.data());
                }
            }
        }
    }

protected:
    QProcess m_process;
    QFileInfo m_testInfo;
    qint64 m_consumingTime;
    int m_exitCode;
    int m_index;
    QElapsedTimer m_elapsedTimer;
    QProcess::ExitStatus m_exitStatus;
    QList<QByteArray> m_testDataList;
    bool m_outPutAll;
};

class QEXTTestController : public QObject
{
    Q_OBJECT
public:
    enum OutputType {
        Output_All = 0,
        Output_Failure
    };

    QEXTTestController(const QString &rootDir, OutputType output)
        : m_rootDir(rootDir), m_outputType(output), m_testIndex(-1) {
        QDir dir(m_rootDir);
        m_testInfoList = dir.entryInfoList(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    }
    ~QEXTTestController() {
        qDeleteAll(m_allTestList);
        m_allTestList.clear();
        m_successTestList.clear();
        m_failedTestList.clear();
    }

    void runTest() {
        if (m_testInfoList.size() > 0 && m_testIndex < m_testInfoList.size() - 1) {
            QFileInfo testInfo = m_testInfoList.at(++m_testIndex);
            m_testRunner = new QEXTTestRunner(testInfo, m_testIndex, Output_All == m_outputType);
            QObject::connect(m_testRunner.data(), SIGNAL(testFinished(int,QProcess::ExitStatus)),
                             this, SLOT(onTestFinished(int,QProcess::ExitStatus)));
            QString progress = QString("%1/%2").arg(m_testIndex + 1).arg(m_testInfoList.size());
            qDebug() << QString("Start %2: %3")
                        .arg(progress, QEXT_ALL_TEST_PLACEHOLDER_NUM, '>')
                        .arg(testInfo.fileName());
            m_testRunner->runTest();
        } else {
            qDebug() << QString("%1% tests passed, %2 tests failed out of %3")
                        .arg((double)m_successTestList.size() / (double)m_testInfoList.size() * 100)
                        .arg(m_failedTestList.size())
                        .arg(m_testInfoList.size());

            qint64 totalTime = 0;
            QListIterator<QEXTTestRunner *> iter(m_allTestList);
            while (iter.hasNext()) {
                QEXTTestRunner *testRunner = iter.next();
                totalTime += testRunner->consumingTime();
            }
            qDebug() << QString("\nTotal Test time (real) =   %1 sec\n").arg((double)totalTime / 1000);

            if (!m_failedTestList.isEmpty()) {
                qDebug() << "\nThe following tests FAILED:\n";
                QListIterator<QEXTTestRunner *> iter(m_failedTestList);
                while (iter.hasNext()) {
                    QEXTTestRunner *testRunner = iter.next();
                    qDebug() << QString("%1%2 - %3 (Failed)")
                                .arg(QEXT_ALL_TEST_SPACE_PLACEHOLDER)
                                .arg(testRunner->index())
                                .arg(testRunner->testInfo().fileName());
                }
            }
            emit this->allTestFinished();
        }
    }

signals:
    void allTestFinished();

public Q_SLOTS:
    void onTestFinished(int exitCode, QProcess::ExitStatus exitStatus) {
        m_allTestList.append(m_testRunner.data());
        if (exitCode > 0) {
            m_failedTestList.append(m_testRunner.data());
        } else {
            m_successTestList.append(m_testRunner.data());
        }
        QString testName = m_testRunner->testInfo().fileName();
        QString result = (0 == exitCode) ? "Success" : QString("***Failed %1").arg(exitCode);
        qDebug() << QString("%1: %2%3    %4 sec %5\n")
                    .arg("Finish", 14, ' ')
                    .arg(testName)
                    .arg(result, 80 - testName.size(), '.')
                    .arg(double(m_testRunner->consumingTime()) / 1000)
                    .arg(QProcess::NormalExit == exitStatus ? "" : "-CrashExit");
        if (!m_testInfoList.isEmpty()) {
            this->runTest();
        }
    }

protected:
    QString m_rootDir;
    QFileInfoList m_testInfoList;
    QPointer<QEXTTestRunner> m_testRunner;
    QList<QEXTTestRunner *> m_successTestList;
    QList<QEXTTestRunner *> m_failedTestList;
    QList<QEXTTestRunner *> m_allTestList;
    const OutputType m_outputType;
    int m_testIndex;
};

#endif // QEXTTESTRUNNER_H
