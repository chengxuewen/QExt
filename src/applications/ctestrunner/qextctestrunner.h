#ifndef QEXTCTESTRUNNER_H
#define QEXTCTESTRUNNER_H

#include <QObject>
#include <QDebug>
#include <QProcess>

class QEXTCTestRunner : public QObject
{
    Q_OBJECT
public:
    QEXTCTestRunner(const QString &workingDir) : m_workingDir(workingDir) {
        connect(&m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(onReadData()));
        connect(&m_process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(onFinished(int,QProcess::ExitStatus)));
        m_process.setReadChannel(QProcess::StandardOutput);
        m_process.setWorkingDirectory(m_workingDir);
    }

    void runTest() {
        m_process.start("ctest");
    }

signals:
    void testFinished();

public slots:
    void onFinished(int exitCode, QProcess::ExitStatus exitStatus) {
        qDebug() << QString("exitCode=%1, exitStatus=%2").arg(exitCode).arg(exitStatus);
        emit this->testFinished();
    }

    void onReadData() {
        qDebug() << m_process.readAllStandardOutput();
    }

protected:
    QProcess m_process;
    QString m_workingDir;
};

#endif // QEXTCTESTRUNNER_H
