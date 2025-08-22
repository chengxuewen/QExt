#ifndef _QEXTQWTPLOTSERIESDATA_P_H
#define _QEXTQWTPLOTSERIESDATA_P_H

#include <qextQwtSeriesData.h>

class QEXT_PLOT_API QExtPlotSeriesDataPrivate
{
    QExtPlotSeriesData * const q_ptr;
    QEXT_DECLARE_PUBLIC(QExtPlotSeriesData)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPlotSeriesDataPrivate)
public:
    explicit QExtPlotSeriesDataPrivate(QExtPlotSeriesData *q);
    virtual ~QExtPlotSeriesDataPrivate();

    void updateIndexs();

    QExtPlotSequenceDataBuffer *mXBuffer;
    QExtPlotAbstractDataBuffer *mYBuffer;

    size_t mIndexStart; ///< starting index of "rectangle of interest"
    size_t mIndexEnd;   ///< ending index of "rectangle of interest"
};

#endif // _QEXTQWTPLOTSERIESDATA_P_H
