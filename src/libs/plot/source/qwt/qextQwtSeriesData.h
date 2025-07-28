#ifndef _QEXTQWTSERIESDATA_H
#define _QEXTQWTSERIESDATA_H

#include <qextPlotData.h>
#include <qextPlotDataBuffer.h>
#include <qextPlotDataTransform.h>

#include <qwt_series_data.h>

class QEXT_PLOT_API QExtQwtSeriesDataBase : public QwtSeriesData<QPointF>
{
public:
    typedef QwtSeriesData<QPointF> Base;

    QExtQwtSeriesDataBase() {}
    ~QExtQwtSeriesDataBase() QEXT_OVERRIDE {}

    // QwtSeriesData implementations
    size_t size() const QEXT_OVERRIDE
    {
        return this->plotDataBase()->size();
    }
    // QRectF boundingRect() const QEXT_OVERRIDE;
    // QPointF sample(size_t i) const QEXT_OVERRIDE;
    // void setRectOfInterest(const QRectF &rect) QEXT_OVERRIDE;

    virtual const QExtPlotDataBase* plotDataBase() const = 0;

    virtual void updateCache(bool resetOldData) {}
    virtual QExtRangeF getVisualizationXRange() = 0;
    virtual QExtRangeF getVisualizationYRange(const QExtRangeF &xRange) = 0;
};

class QEXT_PLOT_API QExtQwtXYSeriesData : public QExtQwtSeriesDataBase
{
public:
    explicit QExtQwtXYSeriesData(const QExtPlotScatterData *data) : mData(data) {}
    ~QExtQwtXYSeriesData() QEXT_OVERRIDE {}

    // QwtSeriesData implementations
    QRectF boundingRect() const QEXT_OVERRIDE;
    QPointF sample(size_t i) const QEXT_OVERRIDE;

    const QExtPlotDataBase* plotDataBase() const QEXT_OVERRIDE
    {
        return dynamic_cast<const QExtPlotDataBase *>(this->plotData());
    }
    virtual const QExtPlotScatterData* plotData() const { return mData; }

    void updateCache(bool resetOldData) QEXT_OVERRIDE;
    QExtRangeF getVisualizationXRange() QEXT_OVERRIDE;
    QExtRangeF getVisualizationYRange(const QExtRangeF &xRange) QEXT_OVERRIDE;

private:
    const QExtPlotScatterData *mData;
};

class QEXT_PLOT_API QExtQwtTimeSeriesData : public QExtQwtXYSeriesData
{
public:
    explicit QExtQwtTimeSeriesData(const QExtPlotTimeSeriesData *data);
    ~QExtQwtTimeSeriesData() QEXT_OVERRIDE {}

    // QwtSeriesData implementations
    QRectF boundingRect() const QEXT_OVERRIDE;
    QPointF sample(size_t i) const QEXT_OVERRIDE;

    void updateCache(bool resetOldData) QEXT_OVERRIDE;
    QExtRangeF getVisualizationXRange() QEXT_OVERRIDE;
    QExtRangeF getVisualizationYRange(const QExtRangeF &xRange) QEXT_OVERRIDE;

    void setTimeOffset(double offset);
    virtual QExtOptional<QPointF> sampleFromTime(double time);

protected:
    double mTimeOffset;
    const QExtPlotTimeSeriesData *mTimeSeriesData;
};

class QEXT_PLOT_API QExtQwtTransformedTimeSeriesData : public QExtQwtTimeSeriesData
{
public:
    explicit QExtQwtTransformedTimeSeriesData(const QExtPlotTimeSeriesData *data);
    ~QExtQwtTransformedTimeSeriesData() QEXT_OVERRIDE {}

    void updateCache(bool resetOldData) QEXT_OVERRIDE;

    QString transformName() const;
    void setTransform(const QString &transformId);
    QExtPlotDataTransform::SharedPtr transform() const;

    QString alias() const;
    void setAlias(const QString &alias);

protected:
    QString mAlias;
    QExtPlotTimeSeriesData mDstData;
    const QExtPlotTimeSeriesData* mSrcData;
    QExtPlotDataTransform::SharedPtr mTransform;
};


class QExtPlotSeriesDataPrivate;
class QEXT_PLOT_API QExtPlotSeriesData : public QwtSeriesData<QPointF>
{
public:
    explicit QExtPlotSeriesData(QExtPlotSeriesDataPrivate *d);
    QExtPlotSeriesData(QExtPlotSequenceDataBuffer *xBuffer, QExtPlotAbstractDataBuffer *yBuffer);
    ~QExtPlotSeriesData() QEXT_OVERRIDE;

    bool isBufferValid() const;
    void clear();

    QExtPlotSequenceDataBuffer *xBuffer() const;
    void setXBuffer(QExtPlotSequenceDataBuffer *xBuffer);

    QExtPlotAbstractDataBuffer *yBuffer() const;
    void setYBuffer(QExtPlotAbstractDataBuffer *yBuffer);

    // QwtSeriesData implementations
    size_t size() const QEXT_OVERRIDE;
    QRectF boundingRect() const QEXT_OVERRIDE;
    QPointF sample(size_t i) const QEXT_OVERRIDE;

    void setRectOfInterest(const QRectF &rect) QEXT_OVERRIDE;

protected:
    QScopedPointer<QExtPlotSeriesDataPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtPlotSeriesData)
    QEXT_DISABLE_COPY_MOVE(QExtPlotSeriesData)
};

// class QExtPlotSeriesWritableDataPrivate;
// class QEXT_PLOT_API QExtPlotWritableSeriesData : public QwtSeriesData<QPointF>
// {
// public:
//     explicit QExtPlotWritableSeriesData(QExtPlotSeriesDataPrivate *d);
//     QExtPlotWritableSeriesData(QExtPlotSequenceDataBuffer *xBuffer, QExtPlotWritableDataBuffer *yBuffer);
//     ~QExtPlotWritableSeriesData() QEXT_OVERRIDE;

//     void clear();

//     QExtPlotWritableDataBuffer *yWritableBuffer() const;
//     void setYBuffer(QExtPlotWritableDataBuffer *yWritableBuffer);

// private:
//     QEXT_DECL_PRIVATE_D(dd_ptr, QExtPlotWritableSeriesData)
//     QEXT_DISABLE_COPY_MOVE(QExtPlotWritableSeriesData)
// };


#endif // _QEXTQWTSERIESDATA_H
