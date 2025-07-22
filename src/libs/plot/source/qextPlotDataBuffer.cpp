#include <qextPlotDataBuffer.h>

#include <memory>
#include <cstring>

class QExtPlotRingBufferPrivate
{
    QExtPlotRingBuffer * const q_ptr;
    QEXT_DECL_PUBLIC(QExtPlotRingBuffer)
    QEXT_DISABLE_COPY_MOVE(QExtPlotRingBufferPrivate)
public:
    QExtPlotRingBufferPrivate(QExtPlotRingBuffer *q, size_t size);
    virtual ~QExtPlotRingBufferPrivate();

    void updateLimits() const; ///< Updates limits cache

    size_t mSize;            ///< size of `buffer`
    double *mDatas;              ///< storage
    size_t mHeadIndex;        ///< indicates the actual `0` index of the ring buffer

    bool mEmpty;
    bool mIsRinged;

    // size_t m_sampleSize;
    // mutable QAtomicInt m_dataOutdated;

    mutable QExtRangeF mRange;    ///< Cache for limits()
    mutable bool mRangeOutdated;   ///< Indicates that limits needs to be re-calculated
};

QExtPlotRingBufferPrivate::QExtPlotRingBufferPrivate(QExtPlotRingBuffer *q, size_t size)
    : q_ptr(q)
{
    mSize = size;
    mDatas = new double[size]();
    std::memset(mDatas, 0, size * sizeof(double));
    mHeadIndex = 0;

    mEmpty = true;
    mIsRinged = false;
    mRangeOutdated = true;
}

QExtPlotRingBufferPrivate::~QExtPlotRingBufferPrivate()
{
    if (mDatas)
    {
        std::free(mDatas);
        mDatas = QEXT_NULLPTR;
    };
}

void QExtPlotRingBufferPrivate::updateLimits() const
{
    mRange.reset(mDatas[0], mDatas[0]);
    for (size_t i = 0; i < mSize; i++)
    {
        if (mDatas[i] > mRange.max())
        {
            mRange.setMax(mDatas[i]);
        }
        else if (mDatas[i] < mRange.min())
        {
            mRange.setMin(mDatas[i]);
        }
    }
    mRangeOutdated = false;
}

QExtPlotRingBuffer::QExtPlotRingBuffer(size_t size)
    : dd_ptr(new QExtPlotRingBufferPrivate(this, size))
{
}

QExtPlotRingBuffer::~QExtPlotRingBuffer()
{
}

size_t QExtPlotRingBuffer::size() const
{
    Q_D(const QExtPlotRingBuffer);
    return d->mSize;
}

QExtRangeF QExtPlotRingBuffer::range() const
{
    Q_D(const QExtPlotRingBuffer);
    if (d->mRangeOutdated)
    {
        d->updateLimits();
    }
    return d->mRange;
}

double QExtPlotRingBuffer::at(size_t index) const
{
    Q_D(const QExtPlotRingBuffer);
    Q_ASSERT_X(index >= 0 && index + 1 <= d->mSize, "QExtPlotRingBuffer::at", "index out of range");
    if (d->mIsRinged)
    {
        index = d->mHeadIndex + index;
        if (index >= d->mSize)
        {
            index -= d->mSize;
        }
    }
    return d->mDatas[index];
}

void QExtPlotRingBuffer::clear()
{
    Q_D(QExtPlotRingBuffer);
    for (size_t i = 0; i < d->mSize; i++)
    {
        d->mDatas[i] = 0.0;
    }

    d->mHeadIndex = 0;
    d->mIsRinged = false;
    d->mEmpty = true;
    d->mRange.clear();
    d->mRangeOutdated = false;
}

void QExtPlotRingBuffer::resize(size_t size)
{
    Q_D(QExtPlotRingBuffer);
    if (size != d->mSize)
    {
        double *newData = new double[size];
        const size_t fillLen = std::min(size, d->mSize);
        for (size_t i = 0; i < fillLen; i++)
        {
            newData[i] = this->at(i);
        }
        if (size > d->mSize)
        {
            const size_t offset = size - d->mSize;
            std::memset(newData + offset, 0, offset);
        }

        delete d->mDatas;
        d->mDatas = newData;
        d->mRangeOutdated = true;
        d->mIsRinged = false;
        d->mHeadIndex = 0;
        d->mSize = size;
    }
}

size_t QExtPlotRingBuffer::dataSize() const
{
    Q_D(const QExtPlotRingBuffer);
    if (d->mIsRinged)
    {
        return d->mSize;
    }
    else
    {
        return d->mEmpty ? 0 : d->mHeadIndex + 1;
    }
}

size_t QExtPlotRingBuffer::headIndex() const
{
    Q_D(const QExtPlotRingBuffer);
    return d->mHeadIndex;
}

void QExtPlotRingBuffer::addDatas(double *datas, size_t len, const QVariant &variant)
{
    Q_D(QExtPlotRingBuffer);
    const size_t shift = len;
    if (shift < d->mSize)
    {
        const size_t distance = d->mSize - d->mHeadIndex; // distance of `head` to end
        if (shift <= distance)
        {
            // there is enough room at the end of array
            for (size_t i = 0; i < shift; i++)
            {
                d->mDatas[i + d->mHeadIndex] = datas[i];
            }

            if (distance == shift)
            {
                // we used all the room at the end
                d->mHeadIndex = 0;
                d->mIsRinged = true;
            }
            else
            {
                d->mHeadIndex += shift;
            }
        }
        else
        {
            // there isn't enough room
            for (size_t i = 0; i < distance; i++)
            { // fill the end part
                d->mDatas[i + d->mHeadIndex] = datas[i];
            }
            for (size_t i = 0; i < (shift - distance); i++)
            { // continue from the beginning
                d->mDatas[i] = datas[i + distance];
            }
            d->mHeadIndex = shift - distance;
            d->mIsRinged = true;
        }
    }
    else
    { // number of new samples equal or bigger than current size (doesn't fit)
        const size_t x = shift - d->mSize;
        for (size_t i = 0; i < d->mSize; i++)
        {
            d->mDatas[i] = datas[i + x];
        }
        d->mHeadIndex = 0;
        d->mIsRinged = true;
    }

    // invalidate cache
    d->mRangeOutdated = true;
    d->mEmpty = false;

    QExtPlotRingBuffer::addDatas(datas, len, variant);
}
