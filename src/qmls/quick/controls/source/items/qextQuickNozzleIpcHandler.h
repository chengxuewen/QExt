#ifndef _QEXTQUICKNOZZLEIPCHANDLER_H
#define _QEXTQUICKNOZZLEIPCHANDLER_H

#ifdef QEXT_HAVE_NOZZLE

#include <qextQuickIpcWidgetItem.h>
#include <qextQuickFrameTransportImpl.h>

#include <memory>
#include <functional>
#include <cstdint>

class QExtQuickNozzleIpcHandler : public QExtQuickIpcWidgetItem::ProcessInterface
{
public:
    using SharedPtr = QSharedPointer<ProcessInterface>;
    using ConnectionEpoch = ProcessInterface::ConnectionEpoch;

    static SharedPtr create() { return SharedPtr(new QExtQuickNozzleIpcHandler()); }

    QExtQuickNozzleIpcHandler() = default;

    ~QExtQuickNozzleIpcHandler() override
    {
        mWIdCallback = nullptr;
        mLogCallback = nullptr;
        mReadyCallback = nullptr;
        mLostCallback = nullptr;

        if (mTransport) {
            mTransport->destroyGlResources();
            mTransport->shutdown();
            mTransport.reset();
        }
    }

    bool start() override { return false; }
    void stop() override {}
    bool probe() override { return false; }
    bool isAlive() const override { return false; }
    void disconnect() override {}

    void setWIdCallback(std::function<void(quintptr)> callback) override
    { mWIdCallback = std::move(callback); }
    void setLogCallback(std::function<void(const QString &)> callback) override
    { mLogCallback = std::move(callback); }
    void setReadyCallback(std::function<void()> callback) override
    { mReadyCallback = std::move(callback); }
    void setLostCallback(std::function<void()> callback) override
    { mLostCallback = std::move(callback); }

    void sendShowCommand() override {}
    void sendResizeCommand(int /*width*/, int /*height*/) override {}
    void *commandChannel() override { return nullptr; }

    bool initFrameTransport() override
    { return mTransport ? mTransport->init() : false; }
    void shutdownFrameTransport() override
    { if (mTransport) mTransport->shutdown(); }
    bool isFrameTransportAvailable() const override
    { return mTransport && mTransport->isAvailable(); }
    void *acquireFrame() override
    { return mTransport ? mTransport->acquireFrame() : nullptr; }
    void releaseFrame(void *handle) override
    { if (mTransport) mTransport->releaseFrame(handle); }
    void setFrameAvailableCallback(std::function<void()> callback) override
    { if (mTransport) mTransport->setFrameAvailableCallback(std::move(callback)); }
    void destroyGlResources() override
    { if (mTransport) mTransport->destroyGlResources(); }

private:
    std::unique_ptr<QExtQuickFrameTransportImpl> mTransport;
    ConnectionEpoch mEpoch{0};
    State mState{Disconnected};
    void *mNozzleHandle{nullptr};

    std::function<void(quintptr)> mWIdCallback;
    std::function<void(const QString &)> mLogCallback;
    std::function<void()> mReadyCallback;
    std::function<void()> mLostCallback;
};

#endif // QEXT_HAVE_NOZZLE

#endif // _QEXTQUICKNOZZLEIPCHANDLER_H
