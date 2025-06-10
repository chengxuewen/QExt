#ifndef _QEXTPLOTSERIESDATA_P_H
#define _QEXTPLOTSERIESDATA_P_H

#include <qextPlotSeriesData.h>

class QExtPlotSeriesDataPrivate
{
    QExtPlotSeriesData * const q_ptr;
    QEXT_DECL_PUBLIC(QExtPlotSeriesData)
    QEXT_DISABLE_COPY_MOVE(QExtPlotSeriesDataPrivate)
public:
    explicit QExtPlotSeriesDataPrivate(QExtPlotSeriesData *q);
    virtual ~QExtPlotSeriesDataPrivate();

    void updateIndexs();

    QExtPlotSequenceDataBuffer *mXBuffer;
    QExtPlotAbstractDataBuffer *mYBuffer;

    size_t mIndexStart; ///< starting index of "rectangle of interest"
    size_t mIndexEnd;   ///< ending index of "rectangle of interest"
};

#endif // _QEXTPLOTSERIESDATA_P_H
