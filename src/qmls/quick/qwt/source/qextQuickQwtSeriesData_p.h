#ifndef _QEXTQUICKQWTSERIESDATA_P_H
#define _QEXTQUICKQWTSERIESDATA_P_H

#include <qextQuickQwtSeriesData.h>

#include <qwt_series_data.h>

#include <QDebug>

template<typename T>
class QExtQuickQwtSeriesDataAdaptor : public QwtSeriesData<T>
{
public:
    QExtQuickQwtSeriesDataAdaptor(const QExtQuickQwtSeriesData<T> *data = nullptr) : mRData(data) { }
    QExtQuickQwtSeriesDataAdaptor(QExtQuickQwtSeriesData<T> *data = nullptr) : mRData(data), mWData(data) { }
    ~QExtQuickQwtSeriesDataAdaptor() override {}

    size_t size() const override
    {
        return mRData ? mRData->size() : 0;
    }
    T sample(size_t index) const override
    {
        return mRData ? mRData->sample(index) : T();
    }
    QRectF boundingRect() const override
    {
        return mRData ? mRData->boundingRect() : QRectF();
    }
    void setRectOfInterest(const QRectF& rect) override
    {
        if (mWData)
        {
            mWData->setRectOfInterest(rect);
        }
    }

protected:
    const QExtQuickQwtSeriesData<T> *mRData{nullptr};
    QExtQuickQwtSeriesData<T> *mWData{nullptr};
};

#endif // _QEXTQUICKQWTSERIESDATA_P_H
