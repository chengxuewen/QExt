#include <QApplication>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlEngine>
#include <QProcess>
#include <QQmlApplicationEngine>
#include <QRegularExpression>
#include <QDebug>

#include <qextQuickControlsGlobal.h>
#include <qextQuickIpcWidgetItem.h>
#include <qextCoreConfig.h>
#include <qextQmlConfig.h>

#ifndef QEXT_BUILD_SHARED
#   include <qextQuickLoader.h>
#endif

using ProcessInterface = QExtQuickIpcWidgetItem::ProcessInterface;

class QProcessHandler : public QObject, public ProcessInterface
{
    Q_OBJECT
public:
    using SharedPtr = QSharedPointer<ProcessInterface>;

    explicit QProcessHandler(QObject *parent = nullptr)
        : QObject(parent)
        , mProcess(new QProcess(this))
    {
        connect(mProcess, &QProcess::readyReadStandardOutput,
                this, &QProcessHandler::onStdout);
        connect(mProcess, &QProcess::readyReadStandardError,
                this, &QProcessHandler::onStderr);
        connect(mProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                this, &QProcessHandler::onFinished);
    }

    bool start(const QString &path, const QStringList &args) override
    {
        mWorkingPath = path.left(path.lastIndexOf('/'));
        mProcess->setWorkingDirectory(mWorkingPath);
        mProcess->start(path, args);
        return mProcess->waitForStarted(5000);
    }

    void stop() override
    {
        if (mProcess->state() != QProcess::NotRunning) 
        {
            mProcess->terminate();
            if (!mProcess->waitForFinished(3000))
                mProcess->kill();
        }
    }

    bool isRunning() const override  { return mProcess->state() == QProcess::Running; }
    bool isStopped() const override  { return mProcess->state() == QProcess::NotRunning; }

    void setWorkingPath(const QString &path) override { mWorkingPath = path; }
    QString workingPath() const override              { return mWorkingPath; }

    void setWIdCallback(std::function<void(WId)> callback) override
    {
        mWIdCallback = std::move(callback);
    }

    void setLogCallback(std::function<void(const QString &)> callback) override
    {
        mLogCallback = std::move(callback);
    }
    void sendShowCommand() override
    {
        mProcess->write(">>>SHOW<<<\n");
        qDebug() << "[ProcessHandler] Sent SHOW";
    }

    void sendResizeCommand(int width, int height) override
    {
        if (!isRunning()) return;
        mProcess->write(QString(">>>SIZE:%1,%2<<<\n").arg(width).arg(height).toUtf8());
    }

private:
    void onStdout()
    {
        while (mProcess->canReadLine()) 
        {
            QString line = QString::fromUtf8(mProcess->readLine()).trimmed();
            static QRegularExpression widRx(">>>WID:(\\d+)<<<");
            auto match = widRx.match(line);
            if (match.hasMatch()) 
            {
                WId wid = match.captured(1).toULongLong();
                qDebug() << "[ProcessHandler] WId received:" << wid;
                if (mWIdCallback) mWIdCallback(wid);
            }
            else 
            {
                if (mLogCallback) mLogCallback("[stdout] " + line);
            }
        }
    }

    void onStderr()
    {
        QString text = QString::fromUtf8(mProcess->readAllStandardError());
        if (mLogCallback) mLogCallback("[stderr] " + text);
    }

    void onFinished(int code, QProcess::ExitStatus s)
    {
        qDebug() << "[ProcessHandler] Process exited:" << code << s;
    }

    QProcess *mProcess;
    QString mWorkingPath;
    std::function<void(WId)> mWIdCallback;
    std::function<void(const QString &)> mLogCallback;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
#ifndef QEXT_BUILD_SHARED
    QExtQuickLoader::load(&engine);
#else
    qDebug() << "addImportPath:" << QML_MODULES_DIR;
    engine.addImportPath(QML_MODULES_DIR);
#endif
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    auto *ipcItem = engine.rootObjects().first()->findChild<QExtQuickIpcWidgetItem *>("ipcItem");
    if (ipcItem) 
    {
        auto handler = QSharedPointer<QExtQuickIpcWidgetItem::ProcessInterface>(new QProcessHandler);
        ipcItem->setProcessPath("./QExtExpQuickIpcWidgetChild");
        ipcItem->setProcessInterface(handler);
        ipcItem->start();
        qDebug() << "[Main] ProcessHandler set on ipcItem";
    }
    else 
    {
        qWarning() << "[Main] ipcItem not found!";
    }

    return app.exec();
}

#include "main.moc"