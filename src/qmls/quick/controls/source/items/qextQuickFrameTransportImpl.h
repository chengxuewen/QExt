#ifndef _QEXTQUICKFRAMETRANSPORTIMPL_H
#define _QEXTQUICKFRAMETRANSPORTIMPL_H

#include <functional>

class QExtQuickFrameTransportImpl
{
public:
    virtual ~QExtQuickFrameTransportImpl() = default;

    virtual bool init() { return false; }
    virtual void shutdown() {}
    virtual bool isAvailable() const { return false; }

    virtual void *acquireFrame() { return nullptr; }
    virtual void releaseFrame(void * /*handle*/) {}

    virtual void setFrameAvailableCallback(std::function<void()> /*callback*/) {}

    virtual void *commandChannel() { return nullptr; }
    virtual void destroyGlResources() {}
};

#endif // _QEXTQUICKFRAMETRANSPORTIMPL_H
