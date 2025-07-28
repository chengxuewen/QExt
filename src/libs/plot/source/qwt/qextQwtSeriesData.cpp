#include <private/qextQwtSeriesData_p.h>

QRectF QExtQwtXYSeriesData::boundingRect() const
{
    QRectF rect;
    if (this->size() == 0)
    {
        return rect;
    }
    QExtRangeF xRange = this->plotDataBase()->xRange();
    QExtRangeF yRange = this->plotDataBase()->yRange();

    rect.setLeft(xRange.min());
    rect.setRight(xRange.max());
    rect.setTop(yRange.max());
    rect.setBottom(yRange.min());
    return rect;
}

QPointF QExtQwtXYSeriesData::sample(size_t i) const
{
    const QExtPlotScatterData::Point& point = mData->at(i);
    return QPointF(point.x, point.y);
}

void QExtQwtXYSeriesData::updateCache(bool resetOldData)
{
    Q_UNUSED(resetOldData);
}

QExtRangeF QExtQwtXYSeriesData::getVisualizationXRange()
{
    return this->size() < 2 ? QExtRangeF() : this->plotDataBase()->xRange();
}

QExtRangeF QExtQwtXYSeriesData::getVisualizationYRange(const QExtRangeF &xRange)
{
    if (xRange.min() <= std::numeric_limits<double>::lowest() &&
        xRange.min() <= std::numeric_limits<double>::max())
    {
        return mData->yRange();
    }

    double yMin = (std::numeric_limits<double>::max());
    double yMax = (std::numeric_limits<double>::lowest());

    for (size_t i = 0; i < this->size(); i++)
    {
        const double yValue = this->sample(i).y();
        yMin = std::min(yMin, yValue);
        yMax = std::max(yMax, yValue);
    }
    return QExtRangeF(yMin, yMax);
}



QExtQwtTimeSeriesData::QExtQwtTimeSeriesData(const QExtPlotTimeSeriesData *data)
    : QExtQwtXYSeriesData(data), mTimeOffset(0), mTimeSeriesData(data)
{
}

QRectF QExtQwtTimeSeriesData::boundingRect() const
{
    QRectF rect;
    if (this->size() == 0)
    {
        return rect;
    }
    QExtRangeF xRange = this->plotDataBase()->xRange();
    QExtRangeF yRange = this->plotDataBase()->yRange();

    rect.setLeft(xRange.min() - mTimeOffset);
    rect.setRight(xRange.max() - mTimeOffset);
    rect.setTop(yRange.max());
    rect.setBottom(yRange.min());
    return rect;
}

QPointF QExtQwtTimeSeriesData::sample(size_t i) const
{
    const QExtPlotTimeSeriesData::Point& point = mTimeSeriesData->at(i);
    return QPointF(point.x - mTimeOffset, point.y);
}

void QExtQwtTimeSeriesData::updateCache(bool resetOldData)
{
    Q_UNUSED(resetOldData);
}

QExtRangeF QExtQwtTimeSeriesData::getVisualizationXRange()
{
    if (this->size() < 2)
    {
        return QExtRangeF();
    }
    else
    {
        QExtRangeF xRange = mTimeSeriesData->xRange();
        return QExtRangeF(xRange.min() - mTimeOffset, xRange.max() - mTimeOffset);
    }
}

QExtRangeF QExtQwtTimeSeriesData::getVisualizationYRange(const QExtRangeF &xRange)
{
    int firstIndex = mTimeSeriesData->getIndexFromX(xRange.min() + mTimeOffset);
    int lastIndex = mTimeSeriesData->getIndexFromX(xRange.max() + mTimeOffset);

    if (firstIndex > lastIndex || firstIndex < 0 || lastIndex < 0)
    {
        return QExtRangeF();
    }

    if (firstIndex == 0 && lastIndex == this->plotDataBase()->size() - 1)
    {
        return mTimeSeriesData->yRange();
    }

    double yMin = (std::numeric_limits<double>::max());
    double yMax = (std::numeric_limits<double>::lowest());

    for (size_t i = firstIndex; i < lastIndex; i++)
    {
        const double yValue = this->sample(i).y();
        yMin = std::min(yMin, yValue);
        yMax = std::max(yMax, yValue);
    }
    return QExtRangeF(yMin, yMax);
}

void QExtQwtTimeSeriesData::setTimeOffset(double offset)
{
    mTimeOffset = offset;
}

QExtOptional<QPointF> QExtQwtTimeSeriesData::sampleFromTime(double time)
{
    const int index = mTimeSeriesData->getIndexFromX(time);
    if (index < 0)
    {
        return qextMakeNullopt();
    }
    const QExtPlotTimeSeriesData::Point &point = this->plotData()->at(size_t(index));
    return QPointF(point.x, point.y);
}


QExtQwtTransformedTimeSeriesData::QExtQwtTransformedTimeSeriesData(const QExtPlotTimeSeriesData *data)
    : QExtQwtTimeSeriesData(&mDstData)
    , mDstData(data->plotName())
    , mSrcData(data)
{
}

void QExtQwtTransformedTimeSeriesData::updateCache(bool resetOldData)
{
    if (mTransform)
    {
        if (resetOldData)
        {
            mDstData.clear();
            // mTransform->reset();
        }
        // std::vector<PlotData*> dest = { &mDstData };
        // _transform->calculate();
    }
    else
    {
        // TODO: optimize ??
        mDstData.clear();
        for (size_t i = 0; i < mSrcData->size(); i++)
        {
            mDstData.pushBack(mSrcData->at(i));
        }
    }
}

QString QExtQwtTransformedTimeSeriesData::transformName() const
{
    return (!mTransform) ? QString() : mTransform->name();
}

void QExtQwtTransformedTimeSeriesData::setTransform(const QString &transformId)
{
    if (this->transformName() == transformId)
    {
        return;
    }
    if (transformId.isEmpty())
    {
        mTransform.reset();
    }
    else
    {
        mDstData.clear();
        mTransform = qextPlotDataTransformFactory->createTransform(transformId);
        // std::vector<PlotData*> dest = { &_dst_data };
        // mTransform->setData(nullptr, { _src_data }, dest);
    }
}

QExtPlotDataTransform::SharedPtr QExtQwtTransformedTimeSeriesData::transform() const
{
    return mTransform;
}

QString QExtQwtTransformedTimeSeriesData::alias() const
{
    return mAlias;
}

void QExtQwtTransformedTimeSeriesData::setAlias(const QString &alias)
{
    mAlias = alias;
}






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
