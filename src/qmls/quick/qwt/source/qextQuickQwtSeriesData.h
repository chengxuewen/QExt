#ifndef _QEXTQUICKQWTSERIESDATA_H
#define _QEXTQUICKQWTSERIESDATA_H

#include <qextQuickQwtGlobal.h>
#include <qextQuickQwtSeriesBuffer.h>

#include <QRectF>
#include <QVector>
#include <QPointF>

#include <memory>

template<typename T>
class QExtQuickQwtSeriesData
{
public:
    using StdSharedPtr = std::shared_ptr<QExtQuickQwtSeriesData<T>>;

    QExtQuickQwtSeriesData(): cachedBoundingRect(0.0, 0.0, -1.0, -1.0) { }
    virtual ~QExtQuickQwtSeriesData() {}

    virtual size_t size() const = 0;
    virtual T sample(size_t i) const = 0;

    virtual QRectF boundingRect() const
    {
        if (cachedBoundingRect.width() < 0.0 || cachedBoundingRect.height() < 0.0)
        {
            cachedBoundingRect = qextQuickQwtBoundingRect(*this);
        }
        return cachedBoundingRect;
    }
    virtual void setRectOfInterest(const QRectF& rect) {}

    inline T firstSample() const { return this->sample( 0 ); }
    inline T lastSample() const { return this->sample(this->size() - 1); }

protected:
    void resetCachedBoundingRect()
    {
        cachedBoundingRect = QRectF(0.0, 0.0, -1.0, -1.0);
    }
    //! Can be used to cache a calculated bounding rectangle
    mutable QRectF cachedBoundingRect;

private:
    QExtQuickQwtSeriesData<T>& operator=( const QExtQuickQwtSeriesData<T>& );
};

template<typename T>
class QExtQuickQwtArraySeriesData : public QExtQuickQwtSeriesData<T>
{
public:
    QExtQuickQwtArraySeriesData() {}
    QExtQuickQwtArraySeriesData(QVector<T> &&data) : mSamples(std::move(data)) {}
    explicit QExtQuickQwtArraySeriesData(const QVector<T>& samples)  : mSamples(samples) {}
    virtual ~QExtQuickQwtArraySeriesData() {}

    inline void popBack()
    {
        this->resetCachedBoundingRect();
        mSamples.removeLast();
    }
    inline void popFront()
    {
        this->resetCachedBoundingRect();
        mSamples.removeFirst();
    }
    inline void pushBack(const T &t)
    {
        this->resetCachedBoundingRect();
        mSamples.push_back();
    }
    inline void pushBack(T &&t)
    {
        this->resetCachedBoundingRect();
        mSamples.push_back(std::move(t));
    }
    inline void pushFront(const T &t)
    {
        this->resetCachedBoundingRect();
        mSamples.push_front(t);
    }
    inline void pushFront(T &&t)
    {
        this->resetCachedBoundingRect();
        mSamples.push_front(std::move(t));
    }
    inline void append(const T &t)
    {
        this->resetCachedBoundingRect();
        mSamples.append(t);
    }
    inline void append(T &&t)
    {
        this->resetCachedBoundingRect();
        mSamples.append(std::move(t));
    }
    inline void append(const QVector<T> &l)
    {
        this->resetCachedBoundingRect();
        mSamples.append(l);
    }

    const QVector<T> &samples() const
    {
        return mSamples;
    }
    void setSamples(const QVector<T>& samples)
    {
        this->resetCachedBoundingRect();
        mSamples = samples;
    }

    size_t size() const override
    {
        return mSamples.size();
    }
    T sample(size_t index) const override
    {
        return mSamples[static_cast<int>(index)];
    }

protected:
    QVector<T> mSamples;
};
using  QExtQuickQwtPointSeriesData = QExtQuickQwtArraySeriesData<QPointF>;

class QExtQuickQwtPointIndexRingSeriesData : public QExtQuickQwtSeriesData<QPointF>
{
    QExtQuickQwtIndexSeriesBuffer<double> mIndexBuffer;
    QExtQuickQwtRingSeriesBuffer<double> mRingBuffer;
public:
    explicit QExtQuickQwtPointIndexRingSeriesData(size_t size = 1) : mIndexBuffer(size), mRingBuffer(size) {}
    virtual ~QExtQuickQwtPointIndexRingSeriesData() {}

    void clear()
    {
        this->resetCachedBoundingRect();
        return mRingBuffer.clear();
    }
    bool setSample(size_t i, const double &value)
    {
        this->resetCachedBoundingRect();
        return mRingBuffer.setSample(i, value);
    }
    size_t addSamples(double *samples, size_t count = 1)
    {
        this->resetCachedBoundingRect();
        return mRingBuffer.addSamples(samples, count);
    }
    void resize(size_t size)
    {
        mIndexBuffer.resize(size);
        mRingBuffer.resize(size);
    }

    size_t size() const override
    {
        return mRingBuffer.size();
    }
    QPointF sample(size_t index) const override
    {
        return QPointF(mIndexBuffer.sample(index), mRingBuffer.sample(index));
    }
};

QEXT_QUICKQWT_API QRectF qextQuickQwtBoundingRect(const QExtQuickQwtSeriesData<QPointF>& data, int from = 0, int to = -1);

#endif // _QEXTQUICKQWTSERIESDATA_H
