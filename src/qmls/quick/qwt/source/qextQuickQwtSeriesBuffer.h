#ifndef _QEXTQUICKQWTSERIESBUFFER_H
#define _QEXTQUICKQWTSERIESBUFFER_H

#include <qextRange.h>

#include <memory>

template <typename T>
class QExtQuickQwtSeriesBuffer
{
public:
    virtual ~QExtQuickQwtSeriesBuffer() {}

    virtual size_t size() const = 0;
    virtual T sample(size_t i) const = 0;
};

template <typename T>
class QExtQuickQwtResizableSeriesBuffer : public QExtQuickQwtSeriesBuffer<T>
{
public:
    virtual void resize(size_t n) = 0;
};

template <typename T>
class QExtQuickQwtSequenceSeriesBuffer : public QExtQuickQwtResizableSeriesBuffer<T>
{
public:
    virtual size_t findIndex(T value) const = 0;
};

template <typename T>
class QExtQuickQwtIndexSeriesBuffer : public QExtQuickQwtSequenceSeriesBuffer<T>
{
    size_t mSize{0};
public:
    QExtQuickQwtIndexSeriesBuffer(size_t size) : mSize(size) {}
    ~QExtQuickQwtIndexSeriesBuffer() override {}

    size_t size() const override { return mSize; }
    T sample(size_t i) const override { return T(i); }
    void resize(size_t size) override { mSize = size; }
    size_t findIndex(T value) const override { return 0; }
};

template <typename T>
class QExtQuickQwtWritableSeriesBuffer : public QExtQuickQwtResizableSeriesBuffer<T>
{
public:
    virtual void clear() = 0;
    virtual bool setSample(size_t i, const T& value) = 0;
    virtual size_t addSamples(T *samples, size_t count = 1) = 0;
    virtual bool checkValueValid(const T &value) const { return true; }
};

template <typename T>
class QExtQuickQwtRingSeriesBuffer : public QExtQuickQwtWritableSeriesBuffer<T>
{
    size_t mSize{0};
    size_t mValidSize{0};
    size_t mHeadIndex{0};
    QVector<T> mData;
public:
    QExtQuickQwtRingSeriesBuffer(size_t size) { this->resize(size); }
    ~QExtQuickQwtRingSeriesBuffer() override { }

    size_t size() const override { return mValidSize; }
    T sample(size_t i) const override
    {
        if (mSize == mValidSize)
        {
            size_t index = (mHeadIndex + i) % mSize;
            return mData.at(index);
        }
        else
        {
            return mData.at(i);
        }
    }
    void resize(size_t size) override
    {
        size = qMax<size_t>(1, size);
        if (size != mSize)
        {
            QVector<T> newData(size, T());
            if (mValidSize > 0)
            {
                const auto beginOffset = qMin(mSize - mHeadIndex, mValidSize);
                memcpy(newData.data(), mData.data() + mHeadIndex, beginOffset);
                const auto endOffset = mValidSize - beginOffset;
                if (endOffset > 0)
                {
                    memcpy(newData.data() + beginOffset, mData.data(), endOffset);
                }
            }
            mData.swap(newData);
            mHeadIndex = 0;
            mSize = size;
        }
    }

    void clear() override
    {
        mData.fill(T());
        mValidSize = 0;
        mHeadIndex = 0;
    }
    bool setSample(size_t i, const T &value) override
    {
        if (i < mSize)
        {
            mData[i] = value;
            return true;
        }
        return false;
    }
    size_t addSamples(T *samples, size_t count) override
    {
        size_t validCount = 0;
        for (size_t i = 0; i < count; ++i)
        {
            if (this->checkValueValid(samples[i]))
            {
                if (0 == mValidSize)
                {
                    mData[0] = samples[i];
                }
                else
                {
                    mData[mHeadIndex] = samples[i];
                    mHeadIndex = (mHeadIndex + 1) % mSize;
                }
                validCount++;
            }
        }
        mValidSize = qMin(mSize, mValidSize + validCount);
        return validCount;
    }
};

#endif // _QEXTQUICKQWTSERIESBUFFER_H
