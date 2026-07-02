#ifndef _QEXTQUICKEMBEDIPCHANDLER_H
#define _QEXTQUICKEMBEDIPCHANDLER_H

#include <qextQuickIpcWidgetItem.h>

#include <QObject>
#include <QProcess>
#include <QPointer>
#include <QRegularExpression>
#include <QLoggingCategory>

#include <functional>
#include <cstdint>

class QExtQuickEmbedIpcHandler : public QObject,
                                 public QExtQuickIpcWidgetItem::ProcessInterface
{
    Q_OBJECT

public:
    using SharedPtr = QSharedPointer<ProcessInterface>;
    using ConnectionEpoch = ProcessInterface::ConnectionEpoch;

    static SharedPtr create() { return SharedPtr(new QExtQuickEmbedIpcHandler()); }

    explicit QExtQuickEmbedIpcHandler(QObject *parent = nullptr)
        : QObject(parent)
        , mProcess(new QProcess(this))
    {
        connect(mProcess, &QProcess::readyReadStandardOutput,
                this, &QExtQuickEmbedIpcHandler::onStdout);
        connect(mProcess, &QProcess::readyReadStandardError,
                this, &QExtQuickEmbedIpcHandler::onStderr);
        connect(mProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                this, &QExtQuickEmbedIpcHandler::onFinished);
        connect(mProcess, &QProcess::errorOccurred,
                this, &QExtQuickEmbedIpcHandler::onError);
    }

    ~QExtQuickEmbedIpcHandler() override
    {
        mWIdCallback = nullptr;
        mLogCallback = nullptr;
        mReadyCallback = nullptr;
        mLostCallback = nullptr;

        if (mProcess && mProcess->state() != QProcess::NotRunning) {
            mProcess->kill();
            mProcess->waitForFinished(3000);
        }
    }

    void setProcessPath(const QString &path) { mProcessPath = path; }
    void setProcessArgs(const QStringList &args) { mProcessArgs = args; }

    bool start() override
    {
        if (mState != Disconnected) return false;
        if (mProcessPath.isEmpty()) return false;

        mEpoch++;
        mState = Connecting;

        int lastSlash = mProcessPath.lastIndexOf(QLatin1Char('/'));
        if (lastSlash > 0)
            mProcess->setWorkingDirectory(mProcessPath.left(lastSlash));
        mProcess->start(mProcessPath, mProcessArgs);
        if (!mProcess->waitForStarted(5000)) {
            mState = Disconnected;
            return false;
        }
        return true;
    }

    void stop() override
    {
        if (mState == Disconnected) return;

        mState = Disconnecting;
        if (mProcess && mProcess->state() != QProcess::NotRunning) {
            mProcess->terminate();
            if (!mProcess->waitForFinished(3000))
                mProcess->kill();
        }
        mCachedWId = 0;
        mState = Disconnected;
    }

    bool probe() override
    {
        return !mProcessPath.isEmpty() && mState == Disconnected;
    }

    bool isAlive() const override
    {
        return mCachedWId != 0
            && mProcess
            && mProcess->state() == QProcess::Running;
    }

    void disconnect() override
    {
        mCachedWId = 0;
        mState = Disconnected;
    }

    void setWIdCallback(std::function<void(quintptr)> callback) override
    {
        mWIdCallback = std::move(callback);
    }

    void setLogCallback(std::function<void(const QString &)> callback) override
    {
        mLogCallback = std::move(callback);
    }

    void setReadyCallback(std::function<void()> callback) override
    {
        mReadyCallback = std::move(callback);
    }

    void setLostCallback(std::function<void()> callback) override
    {
        mLostCallback = std::move(callback);
    }

    void sendShowCommand() override
    {
        if (!isAlive()) return;
        mProcess->write(">>>SHOW<<<\n");
    }

    void sendResizeCommand(int width, int height) override
    {
        if (!isAlive()) return;
        mProcess->write(QString(">>>SIZE:%1,%2<<<\n").arg(width).arg(height).toUtf8());
    }

    void *commandChannel() override
    {
        return static_cast<void *>(mProcess);
    }

    bool initFrameTransport() override { return false; }
    void shutdownFrameTransport() override {}
    bool isFrameTransportAvailable() const override { return false; }
    void *acquireFrame() override { return nullptr; }
    void releaseFrame(void * /*handle*/) override {}
    void setFrameAvailableCallback(std::function<void()> /*callback*/) override {}
    void destroyGlResources() override {}

private Q_SLOTS:
    void onStdout()
    {
        while (mProcess->canReadLine()) {
            QString line = QString::fromUtf8(mProcess->readLine()).trimmed();
            static QRegularExpression widRx(">>>WID:(\\d+)<<<");
            auto match = widRx.match(line);
            if (match.hasMatch()) {
                quintptr wid = match.captured(1).toULongLong();
                ConnectionEpoch callbackEpoch = mEpoch;
                QMetaObject::invokeMethod(this, [=]() {
                    if (callbackEpoch != mEpoch) return;
                    mCachedWId = wid;
                    if (mWIdCallback) mWIdCallback(wid);
                    if (mReadyCallback) mReadyCallback();
                    mState = Connected;
                }, Qt::QueuedConnection);
            } else {
                if (mLogCallback) mLogCallback("[stdout] " + line);
            }
        }
    }

    void onStderr()
    {
        QString text = QString::fromUtf8(mProcess->readAllStandardError());
        if (mLogCallback) mLogCallback("[stderr] " + text);
    }

    void onFinished(int code, QProcess::ExitStatus status)
    {
        Q_UNUSED(code)
        Q_UNUSED(status)
        ConnectionEpoch callbackEpoch = mEpoch;
        QMetaObject::invokeMethod(this, [=]() {
            if (callbackEpoch != mEpoch) return;
            mCachedWId = 0;
            mState = Disconnected;
            if (mLostCallback) mLostCallback();
        }, Qt::QueuedConnection);
    }

    void onError(QProcess::ProcessError error)
    {
        if (error == QProcess::FailedToStart)
        {
            qCWarning(lcQExtQuickIpc) << "[QExtIPC] EmbedHandler: process failed to start (permanent error, no retry)";
            mCachedWId = 0;
            mState = Disconnected;
            return;
        }
        if (error == QProcess::Crashed)
        {
            qCWarning(lcQExtQuickIpc) << "[QExtIPC] EmbedHandler: process crashed";
            ConnectionEpoch callbackEpoch = mEpoch;
            QMetaObject::invokeMethod(this, [=]() {
                if (callbackEpoch != mEpoch) return;
                mCachedWId = 0;
                mState = Disconnected;
                if (mLostCallback) mLostCallback();
            }, Qt::QueuedConnection);
        }
    }
private:
    QPointer<QProcess> mProcess;
    quintptr mCachedWId{0};
    ConnectionEpoch mEpoch{0};
    State mState{Disconnected};

    std::function<void(quintptr)> mWIdCallback;
    std::function<void(const QString &)> mLogCallback;
    std::function<void()> mReadyCallback;
    std::function<void()> mLostCallback;

    QString mProcessPath;
    QStringList mProcessArgs;
};

#endif // _QEXTQUICKEMBEDIPCHANDLER_H
