#ifndef _QEXTQUICKQWTSERIESSTORE_H
#define _QEXTQUICKQWTSERIESSTORE_H

#include <qextQuickQwtSeriesData.h>

#include <QRectF>

class QExtQuickQwtAbstractSeriesStore
{
public:
    virtual ~QExtQuickQwtAbstractSeriesStore() {}

protected:
    virtual void onDataChanged() = 0;
    virtual void setRectOfInterest(const QRectF&) = 0;

    virtual QRectF dataRect() const = 0;
    virtual size_t dataSize() const = 0;
};

template<typename T>
class QExtQuickQwtSeriesStore : public virtual QExtQuickQwtAbstractSeriesStore
{
public:
    explicit QExtQuickQwtSeriesStore() {}
    virtual ~QExtQuickQwtSeriesStore() { delete mSeries; }

    virtual QExtQuickQwtSeriesData<T>* data()
    {
        return mSeries;
    }
    virtual const QExtQuickQwtSeriesData<T>* data() const
    {
        return mSeries;
    }
    virtual void setData(QExtQuickQwtSeriesData<T>* series)
    {
        if (series != mSeries)
        {
            delete mSeries;
            mSeries = series;
            this->onDataChanged();
        }
    }
    void resetData(QExtQuickQwtSeriesData<T>* series = nullptr)
    {
        this->setData(series);
    }

    virtual T sample(int index) const
    {
        return mSeries ? mSeries->sample(index) : T();
    }
    virtual QExtQuickQwtSeriesData<T>* swapData(QExtQuickQwtSeriesData<T>* series)
    {
        auto swappedSeries = mSeries;
        mSeries = series;
        return swappedSeries;
    }

protected:
    size_t dataSize() const override
    {
        return mSeries ? mSeries->size() : 0;
    }
    QRectF dataRect() const override
    {
        return mSeries ? mSeries->boundingRect() : QRectF(1.0, 1.0, -2.0, -2.0);
    }
    void onDataChanged() override { }
    void setRectOfInterest(const QRectF& rect) override
    {
        if (mSeries)
        {
            mSeries->setRectOfInterest( rect );
        }
    }

private:
    QExtQuickQwtSeriesData<T> * mSeries{nullptr};
};

#endif // _QEXTQUICKQWTSERIESSTORE_H
