#ifndef _QEXTPLOTDATABUFFER_H
#define _QEXTPLOTDATABUFFER_H

#include <qextRange.h>
#include <qextOptional.h>
#include <qextPlotGlobal.h>

class QExtPlotBufferSink
{
public:
    QExtPlotBufferSink() : mConnected(false) {}
    virtual ~QExtPlotBufferSink()
    {
        for (auto &&sink : mFollowerList)
        {
            sink->mConnected.storeRelease(false);
        }
        mFollowerList.clear();
    }

    virtual bool isConnected() const { return mConnected.loadAcquire(); }

    virtual void addDatas(double *datas, size_t len, const QVariant &variant = QVariant())
    {
        for (auto &&sink : mFollowerList)
        {
            sink->addDatas(datas, len, variant);
        }
    }

    bool connectFollower(QExtPlotBufferSink *sink)
    {
        if (!mFollowerList.contains(sink) && !sink->mConnected.fetchAndStoreOrdered(true))
        {
            mFollowerList.append(sink);
            return true;
        }
        qWarning() << "QExtPlotBufferSink::connectFollower():sink already connected";
        return false;
    }

    void disconnectFollower(QExtPlotBufferSink *sink)
    {
        mFollowerList.removeOne(sink);
        sink->mConnected.storeRelease(false);
    }

protected:
    QList<QExtPlotBufferSink *> mFollowerList;
    QAtomicInt mConnected;
};

/**
 * @brief Abstract base class for plot data buffers.
 */
class QExtPlotAbstractDataBuffer
{
public:
    /// Placeholder virtual destructor
    virtual ~QExtPlotAbstractDataBuffer() {}

    /// Returns size of the buffer.
    virtual size_t size() const = 0;
    /// Returns minimum and maximum of the buffer values.
    virtual QExtRangeF range() const = 0;
    /// Returns a sample from given index.
    virtual double at(size_t index) const = 0;

    size_t lastIndex() const { return this->size() > 0 ? this->size() - 1 : 0; }
};

/// Common base class for index and writable frame buffers
class QExtPlotResizableDataBuffer : public QExtPlotAbstractDataBuffer
{
public:
    /**
     * @brief Resize the buffer.
     * @param size
     * @note Resizing to same value is an error.
     */
    virtual void resize(size_t size) = 0;
};

class QExtPlotWritableDataBuffer : public QExtPlotResizableDataBuffer, public QExtPlotBufferSink
{
public:
    virtual void clear() = 0;

    virtual size_t dataSize() const = 0;
    virtual size_t headIndex() const = 0;
};

/**
 * @brief Abstract base class for sequence buffers.
 * These buffers only contain increasing or equal (to previous) values.
 */
class QExtPlotSequenceDataBuffer : public QExtPlotResizableDataBuffer
{
public:
    /**
     * @brief Finds index for given value.
     * If given value is bigger than max or smaller than minimum returns `OUT_OF_RANGE`. If it's in between values,
     * smaller index is returned (not closer one).
     * @param value
     * @return smaller index.
     */
    virtual QExtOptional<size_t> findIndex(double value) const = 0;
};

/**
 * @brief A simple frame buffer that simply returns requested index as  sample value.
 * @note This buffer isn't for storing data.
 */
class QEXT_PLOT_API QExtPlotIndexBuffer : public QExtPlotSequenceDataBuffer
{
public:
    explicit QExtPlotIndexBuffer(size_t size = 1) : mSize(size) {}
    ~QExtPlotIndexBuffer() QEXT_OVERRIDE {}

    size_t size() const QEXT_OVERRIDE { return mSize; }
    QExtRangeF range() const QEXT_OVERRIDE { return QExtRangeF(0, mSize > 0 ? mSize - 1 : 0); }
    double at(size_t index) const QEXT_OVERRIDE { Q_ASSERT(index < mSize); return index; }
    QExtOptional<size_t> findIndex(double value) const QEXT_OVERRIDE
    {
        return value >= 0 && size_t(value) < mSize - 1 ? qextMakeOptional(size_t(value)) : qextMakeNullopt();
    }

    void resize(size_t size) QEXT_OVERRIDE { mSize = size; }

private:
    size_t mSize;
};


/**
 * @brief A fast buffer implementation for storing data.
 */
class QExtPlotRingBufferPrivate;
class QEXT_PLOT_API QExtPlotRingBuffer : public QExtPlotWritableDataBuffer
{
public:
    explicit QExtPlotRingBuffer(size_t size = 1);
    ~QExtPlotRingBuffer() QEXT_OVERRIDE;

    size_t size() const QEXT_OVERRIDE;
    QExtRangeF range() const QEXT_OVERRIDE;
    double at(size_t index) const QEXT_OVERRIDE;

    void clear() QEXT_OVERRIDE;
    void resize(size_t size) QEXT_OVERRIDE;
    size_t dataSize() const QEXT_OVERRIDE;
    size_t headIndex() const QEXT_OVERRIDE;

    void addDatas(double *datas, size_t len, const QVariant &variant = QVariant()) QEXT_OVERRIDE;

protected:
    QScopedPointer<QExtPlotRingBufferPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtPlotRingBuffer)
    QEXT_DISABLE_COPY_MOVE(QExtPlotRingBuffer)
};


#endif // _QEXTPLOTDATABUFFER_H
