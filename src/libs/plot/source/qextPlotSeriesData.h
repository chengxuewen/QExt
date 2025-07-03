#ifndef _QEXTPLOTSERIESDATA_H
#define _QEXTPLOTSERIESDATA_H

#include <qextPlotDataBuffer.h>

#include <qwt_series_data.h>

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


#endif // _QEXTPLOTSERIESDATA_H
