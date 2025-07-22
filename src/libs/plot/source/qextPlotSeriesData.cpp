#include <private/qextPlotSeriesData_p.h>

QExtPlotSeriesDataPrivate::QExtPlotSeriesDataPrivate(QExtPlotSeriesData *q)
    : q_ptr(q)
{
    mXBuffer = QEXT_NULLPTR;
    mYBuffer = QEXT_NULLPTR;
    mIndexStart = 0;
    mIndexEnd = 0;
}

QExtPlotSeriesDataPrivate::~QExtPlotSeriesDataPrivate()
{
}

void QExtPlotSeriesDataPrivate::updateIndexs()
{
    mIndexStart = 0;
    mIndexEnd = mXBuffer && mYBuffer ? qMin(mXBuffer->size(), mYBuffer->size()) : 0;
}


QExtPlotSeriesData::QExtPlotSeriesData(QExtPlotSeriesDataPrivate *d)
    : dd_ptr(d)
{
}

QExtPlotSeriesData::QExtPlotSeriesData(QExtPlotSequenceDataBuffer *xBuffer, QExtPlotAbstractDataBuffer *yBuffer)
    : dd_ptr(new QExtPlotSeriesDataPrivate(this))
{
    this->setXBuffer(xBuffer);
    this->setYBuffer(yBuffer);
}

QExtPlotSeriesData::~QExtPlotSeriesData()
{
}

bool QExtPlotSeriesData::isBufferValid() const
{
    Q_D(const QExtPlotSeriesData);
    return d->mXBuffer && d->mYBuffer;
}

QExtPlotSequenceDataBuffer *QExtPlotSeriesData::xBuffer() const
{
    Q_D(const QExtPlotSeriesData);
    return d->mXBuffer;
}

void QExtPlotSeriesData::setXBuffer(QExtPlotSequenceDataBuffer *xBuffer)
{
    Q_D(QExtPlotSeriesData);
    if (xBuffer != d->mXBuffer)
    {
        if (d->mXBuffer)
        {
            delete d->mXBuffer;
        }
        d->mXBuffer = xBuffer;
        d->updateIndexs();
    }
}

QExtPlotAbstractDataBuffer *QExtPlotSeriesData::yBuffer() const
{
    Q_D(const QExtPlotSeriesData);
    return d->mYBuffer;
}

void QExtPlotSeriesData::setYBuffer(QExtPlotAbstractDataBuffer *yBuffer)
{
    Q_D(QExtPlotSeriesData);
    if (yBuffer != d->mYBuffer)
    {
        if (d->mYBuffer)
        {
            delete d->mYBuffer;
        }
        d->mYBuffer = yBuffer;
        d->updateIndexs();
    }
}

size_t QExtPlotSeriesData::size() const
{
    Q_D(const QExtPlotSeriesData);
    return d->mIndexEnd - d->mIndexStart + 1;
}

QRectF QExtPlotSeriesData::boundingRect() const
{
    Q_D(const QExtPlotSeriesData);
    QRectF rect;
    const QExtRangeF xBufferRange = d->mXBuffer ? d->mXBuffer->range() : QExtRangeF();
    const QExtRangeF yBufferRange = d->mYBuffer ? d->mYBuffer->range() : QExtRangeF();
    rect.setBottom(yBufferRange.min());
    rect.setTop(yBufferRange.max());
    rect.setLeft(xBufferRange.min());
    rect.setRight(xBufferRange.max());
    return rect.normalized();
}

QPointF QExtPlotSeriesData::sample(size_t i) const
{
    Q_D(const QExtPlotSeriesData);
    i += d->mIndexStart;
    return this->isBufferValid() ? QPointF(d->mXBuffer->at(i), d->mYBuffer->at(i)) : QPointF();
}

void QExtPlotSeriesData::setRectOfInterest(const QRectF &rect)
{
    Q_D(QExtPlotSeriesData);
    if (d->mXBuffer)
    {
        const QExtOptional<size_t> startIndex = d->mXBuffer->findIndex(rect.left());
        const QExtOptional<size_t> endIndex = d->mXBuffer->findIndex(rect.right());

        d->mIndexStart = startIndex.has_value() ? startIndex.value() : 0;
        d->mIndexEnd = endIndex.has_value() ? endIndex.value() : d->mXBuffer->lastIndex();

        if (d->mIndexStart > 0)
        {
            d->mIndexStart -= 1;
        }

        if (d->mIndexEnd < d->mXBuffer->lastIndex())
        {
            d->mIndexEnd += 1;
        }
    }
}
