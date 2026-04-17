#include <private/qextQuickQwtSeriesData_p.h>

QRectF qextQuickQwtBoundingRect(const QExtQuickQwtSeriesData<QPointF> &data, int from, int to)
{
    const QExtQuickQwtSeriesDataAdaptor<QPointF> adaptor(&data);
    return qwtBoundingRect(adaptor, from, to);
}
