#include <private/qextPlot_p.h>
#include <qextPlotConstants.h>
#include <qextDoubleSpinBox.h>
#include <qextStringUtils.h>
#include <qextNumeric.h>

#include <QDebug>

class QExtPlotXAxisAutoRangeUpdater : public QExtPlotAutoRangeUpdater
{
public:
    QExtPlotXAxisAutoRangeUpdater(QExtPlot *plot) : QExtPlotAutoRangeUpdater(true), mPlot(plot) {}
    ~QExtPlotXAxisAutoRangeUpdater() QEXT_OVERRIDE {}

protected:
    void onEnableChanged(bool enable) QEXT_OVERRIDE
    {
        if (enable)
        {
            mPlot->setAxisAutoScale(QwtPlot::xBottom);
        }
        else
        {
            mPlot->setAxisScale(QwtPlot::xBottom, mPlot->xAxisMin(), mPlot->xAxisMax());
        }
    }

private:
    QExtPlot *mPlot;
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPlotXAxisAutoRangeUpdater)
};

class QExtPlotYAxisAutoRangeUpdater : public QExtPlotAutoRangeUpdater
{
public:
    QExtPlotYAxisAutoRangeUpdater(QExtPlot *plot) : QExtPlotAutoRangeUpdater(true), mPlot(plot) {}
    ~QExtPlotYAxisAutoRangeUpdater() QEXT_OVERRIDE {}

protected:
    void onEnableChanged(bool enable) QEXT_OVERRIDE
    {
        if (enable)
        {
            mPlot->setAxisAutoScale(QwtPlot::yLeft);
        }
        else
        {
            mPlot->setAxisScale(QwtPlot::yLeft, mPlot->yAxisMin(), mPlot->yAxisMax());
        }
    }

private:
    QExtPlot *mPlot;
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPlotYAxisAutoRangeUpdater)
};


QExtPlotPrivate::QExtPlotPrivate(QExtPlot *q)
    : q_ptr(q), mId(-1)
    , mXMin(0)
    , mXMax(0)
    , mYMin(0)
    , mYMax(0)
    , mPlotWidth(1000)
    , mPlotVisible(true)
{
    mXAxisAutoRangeUpdater.reset(new QExtPlotXAxisAutoRangeUpdater(q));
    mYAxisAutoRangeUpdater.reset(new QExtPlotYAxisAutoRangeUpdater(q));
}

QExtPlotPrivate::~QExtPlotPrivate()
{
}

QExtPlot::QExtPlot(QWidget *parent)
    : QwtPlot(parent)
    , dd_ptr(new QExtPlotPrivate(this))
{
}

QExtPlot::QExtPlot(QExtPlotPrivate *d, QWidget *parent)
    : QwtPlot(parent)
    , dd_ptr(d)
{
}

QExtPlot::QExtPlot(const QwtText &title, QWidget *parent)
    : QwtPlot(title, parent)
    , dd_ptr(new QExtPlotPrivate(this))
{
}

QExtPlot::~QExtPlot()
{
}

qint64 QExtPlot::id() const
{
    Q_D(const QExtPlot);
    return d->mId;
}

QString QExtPlot::name() const
{
    Q_D(const QExtPlot);
    return d->mName;
}

QString QExtPlot::groupName() const
{
    Q_D(const QExtPlot);
    return d->mGroupName;
}

double QExtPlot::plotWidth() const
{
    Q_D(const QExtPlot);
    return d->mPlotWidth;
}

void QExtPlot::setPlotWidth(double width)
{
    Q_D(QExtPlot);
    if (width != d->mPlotWidth)
    {
        d->mPlotWidth = width;
        d->mZoomer->setHViewSize(width);
        emit this->plotPropertyChanged(QExtPlotConstants::PLOT_PROPERTY_WIDTH);
    }
}

bool QExtPlot::isPlotVisible() const
{
    Q_D(const QExtPlot);
    return d->mPlotVisible;
}

void QExtPlot::setPlotVisible(bool visiable)
{
    Q_D(QExtPlot);
    if (visiable != d->mPlotVisible)
    {
        d->mPlotVisible = visiable;
        emit this->visibilityChanged(visiable);
        emit this->plotPropertyChanged(QExtPlotConstants::PLOT_PROPERTY_VISIBLE);
    }
    this->setVisible(visiable);
}

bool QExtPlot::isXAxisGridVisible() const
{
    Q_D(const QExtPlot);
    return d->mGrid.xEnabled();
}

void QExtPlot::setXAxisGridVisible(bool visible)
{
    Q_D(QExtPlot);
    if (visible != d->mGrid.xEnabled())
    {
        d->mGrid.enableX(visible);
        emit this->plotPropertyChanged(QExtPlotConstants::PLOT_PROPERTY_XAXIS_GRID_VISIBLE);
    }
}

bool QExtPlot::isYAxisGridVisible() const
{
    Q_D(const QExtPlot);
    return d->mGrid.yEnabled();
}

void QExtPlot::setYAxisGridVisible(bool visible)
{
    Q_D(QExtPlot);
    if (visible != d->mGrid.yEnabled())
    {
        d->mGrid.enableY(visible);
        emit this->plotPropertyChanged(QExtPlotConstants::PLOT_PROPERTY_YAXIS_GRID_VISIBLE);
    }
}

bool QExtPlot::isXAxisMinorGridVisible() const
{
    Q_D(const QExtPlot);
    return d->mGrid.xMinEnabled();
}

void QExtPlot::setXAxisMinorGridVisible(bool visible)
{
    Q_D(QExtPlot);
    if (visible != d->mGrid.xMinEnabled())
    {
        d->mGrid.enableXMin(visible);
        emit this->plotPropertyChanged(QExtPlotConstants::PLOT_PROPERTY_XAXIS_MINOR_GRID_VISIBLE);
    }
}

bool QExtPlot::isYAxisMinorGridVisible() const
{
    Q_D(const QExtPlot);
    return d->mGrid.yMinEnabled();
}

void QExtPlot::setYAxisMinorGridVisible(bool visible)
{
    Q_D(QExtPlot);
    if (visible != d->mGrid.yMinEnabled())
    {
        d->mGrid.enableYMin(visible);
        emit this->plotPropertyChanged(QExtPlotConstants::PLOT_PROPERTY_YAXIS_MINOR_GRID_VISIBLE);
    }
}

double QExtPlot::xAxisMin() const
{
    Q_D(const QExtPlot);
    return d->mXMin;
}

double QExtPlot::xAxisMax() const
{
    Q_D(const QExtPlot);
    return d->mXMax;
}

QExtRangeF QExtPlot::xAxisRange() const
{
    Q_D(const QExtPlot);
    return QExtRangeF(d->mXMin, d->mXMax);
}

void QExtPlot::setXAxisMin(double value)
{
    Q_D(QExtPlot);
    this->setXAxisRange(value, d->mXMax);
}

void QExtPlot::setXAxisMax(double value)
{
    Q_D(QExtPlot);
    this->setXAxisRange(d->mXMin, value);
}

QString QExtPlot::xAxisRangeText() const
{
    Q_D(const QExtPlot);
    return this->isXAxisAutoScaled() ? d->mXAxisAutoRangeUpdater->labelText()
                                     : QString("%1~%2").arg(d->mXMin).arg(d->mXMax);
}

void QExtPlot::setXAxisRange(double min, double max)
{
    Q_D(QExtPlot);
    Q_ASSERT(min <= max);
    if (!QExtNumeric::isDoubleEqual(min, d->mXMin) || !QExtNumeric::isDoubleEqual(max, d->mXMax))
    {
        d->mXMin = min;
        d->mXMax = max;

        d->mZoomer->zoom(0); // unzoom
        d->mZoomer->setXLimits(min, max);

        this->resetAxes();

        emit this->xAxisRangeChanged();
        emit this->plotPropertyChanged(QExtPlotConstants::PLOT_PROPERTY_XAXIS_RANGE);
    }
}

double QExtPlot::yAxisMin() const
{
    Q_D(const QExtPlot);
    return d->mYMin;
}

double QExtPlot::yAxisMax() const
{
    Q_D(const QExtPlot);
    return d->mYMax;
}

QExtRangeF QExtPlot::yAxisRange() const
{
    Q_D(const QExtPlot);
    return QExtRangeF(d->mYMin, d->mYMax);
}

void QExtPlot::setYAxisMin(double value)
{
    Q_D(QExtPlot);
    this->setYAxisRange(value, d->mYMax);
}

void QExtPlot::setYAxisMax(double value)
{
    Q_D(QExtPlot);
    this->setYAxisRange(d->mYMin, value);
}

QString QExtPlot::yAxisRangeText() const
{
    Q_D(const QExtPlot);
    return this->isYAxisAutoScaled() ? d->mYAxisAutoRangeUpdater->labelText()
                                     : QString("%1~%2").arg(d->mYMin).arg(d->mYMax);
}

void QExtPlot::setYAxisRange(double min, double max)
{
    Q_D(QExtPlot);
    Q_ASSERT(min <= max);
    if (!QExtNumeric::isDoubleEqual(min, d->mYMin) || !QExtNumeric::isDoubleEqual(max, d->mYMax))
    {
        d->mYMin = min;
        d->mYMax = max;

        d->mZoomer->zoom(0);
        this->setAxisScale(QwtPlot::yLeft, min, max);
        this->resetAxes();

        emit this->yAxisRangeChanged();
        emit this->plotPropertyChanged(QExtPlotConstants::PLOT_PROPERTY_YAXIS_RANGE);
    }
}

bool QExtPlot::isXAxisAutoScaled() const
{
    Q_D(const QExtPlot);
    return !d->mXAxisAutoRangeUpdater.isNull() && d->mXAxisAutoRangeUpdater->isEnabled();
}

void QExtPlot::setXAxisAutoScaled(bool autoScaled)
{
    Q_D(QExtPlot);
    if (!d->mXAxisAutoRangeUpdater.isNull())
    {
        d->mXAxisAutoRangeUpdater->setEnable(autoScaled);
    }
}

QExtPlotAutoRangeUpdater *QExtPlot::xAxisAutoRangeUpdater() const
{
    Q_D(const QExtPlot);
    return d->mXAxisAutoRangeUpdater.data();
}

void QExtPlot::setXAxisAutoRangeUpdater(QExtPlotAutoRangeUpdater *updater)
{
    Q_D(QExtPlot);
    if (d->mXAxisAutoRangeUpdater.data() != updater)
    {
        if (!d->mXAxisAutoRangeUpdater.isNull())
        {
            d->mXAxisAutoRangeUpdater->disconnect(this);
        }
        d->mXAxisAutoRangeUpdater.reset(updater);
        Q_EMIT this->xAxisAutoScaleChanged(this->isXAxisAutoScaled());
        if (!d->mXAxisAutoRangeUpdater.isNull())
        {
            connect(d->mXAxisAutoRangeUpdater.data(), SIGNAL(enableChanged(bool)),
                    this, SIGNAL(xAxisAutoScaleChanged(bool)));
        }
    }
}

bool QExtPlot::isYAxisAutoScaled() const
{
    Q_D(const QExtPlot);
    return !d->mYAxisAutoRangeUpdater.isNull() && d->mYAxisAutoRangeUpdater->isEnabled();
}

void QExtPlot::setYAxisAutoScaled(bool autoScaled)
{
    Q_D(QExtPlot);
    if (!d->mYAxisAutoRangeUpdater.isNull())
    {
        d->mYAxisAutoRangeUpdater->setEnable(autoScaled);
    }
}

QExtPlotAutoRangeUpdater *QExtPlot::yAxisAutoRangeUpdater() const
{
    Q_D(const QExtPlot);
    return d->mYAxisAutoRangeUpdater.data();
}

void QExtPlot::setYAxisAutoRangeUpdater(QExtPlotAutoRangeUpdater *updater)
{
    Q_D(QExtPlot);
    if (d->mYAxisAutoRangeUpdater.data() != updater)
    {
        if (!d->mYAxisAutoRangeUpdater.isNull())
        {
            d->mYAxisAutoRangeUpdater->disconnect(this);
        }
        d->mYAxisAutoRangeUpdater.reset(updater);
        Q_EMIT this->yAxisAutoScaleChanged(this->isYAxisAutoScaled());
        if (!d->mYAxisAutoRangeUpdater.isNull())
        {
            connect(d->mYAxisAutoRangeUpdater.data(), SIGNAL(enableChanged(bool)),
                    this, SIGNAL(yAxisAutoScaleChanged(bool)));
        }
    }
}

bool QExtPlot::initPlot(qint64 id, const QString &name, const QString &groupName)
{
    Q_D(QExtPlot);
    if (d->mInitOnceFlag.enter())
    {
        d->mId = id;
        d->mGroupName = groupName;
        d->mName = name.isEmpty() ? QString("%1-%2").arg(this->typeString()).arg(id) : name;

        d->mZoomer = new QExtPlotZoomer(this);
        d->mScaleZoomer = new QExtPlotScaleZoomer(this, d->mZoomer);
        d->mScaleZoomer->setBottomPickerValueResolution(0);
        connect(d->mZoomer, SIGNAL(unzoomed()), this, SLOT(unzoom()));
        d->mZoomer->setZoomBase();

        d->mGrid.setPen(QPen(Qt::DotLine));
        d->mGrid.attach(this);

        this->setXAxisRange(0, 1);
        this->setYAxisRange(0, 1);

        this->setXAxisGridVisible(false);
        this->setYAxisGridVisible(false);

        /* init ploylayout */
        d->mLayout = new QExtPlotLayout;
        d->mLayout->setAxisMinimumSize(QwtPlot::yLeft, 50);
        d->mLayout->setAxisMinimumSize(QwtPlot::xBottom, 30);
        this->setPlotLayout(d->mLayout);

        /* init replot timer */
        connect(&d->mReplotTimer, SIGNAL(timeout()), this, SLOT(replot()));
        d->mReplotTimer.setInterval(40);
        d->mReplotTimer.start();

        d->mInitOnceFlag.leave();
        return true;
    }
    return false;
}

QExtPropertyModel *QExtPlot::propertyModel()
{
    Q_D(QExtPlot);
    if (d->mPropertyModel.isNull())
    {
        d->mPropertyModel.reset(new QExtPropertyModel);
        this->initPropertyModel(d->mPropertyModel.data());
    }
    return d->mPropertyModel.data();
}

QExtPropertyDelegate *QExtPlot::propertyDelegate(QObject *parent)
{
    return new QExtPropertyDelegate(parent ? parent : this);
}

QString QExtPlot::typeString() const
{
    return QExtPlotConstants::PLOT_TYPE_BASE;
}

void QExtPlot::serializeLoad(const SerializedItemsMap &items)
{
    this->setVisible(items.value(QExtPlotConstants::PLOT_PROPERTY_VISIBLE, true).toBool());
    this->setXAxisMin(items.value(QExtPlotConstants::PLOT_PROPERTY_XAXIS_RANGE_MIN, 0).toDouble());
    this->setXAxisMax(items.value(QExtPlotConstants::PLOT_PROPERTY_XAXIS_RANGE_MAX, 1).toDouble());
    this->setYAxisMin(items.value(QExtPlotConstants::PLOT_PROPERTY_YAXIS_RANGE_MIN, 0).toDouble());
    this->setYAxisMax(items.value(QExtPlotConstants::PLOT_PROPERTY_YAXIS_RANGE_MAX, 1).toDouble());
    this->setXAxisAutoScaled(items.value(QExtPlotConstants::PLOT_PROPERTY_XAXIS_AUTO_SCALE, true).toBool());
    this->setYAxisAutoScaled(items.value(QExtPlotConstants::PLOT_PROPERTY_YAXIS_AUTO_SCALE, true).toBool());
    this->setXAxisGridVisible(items.value(QExtPlotConstants::PLOT_PROPERTY_XAXIS_GRID_VISIBLE, true).toBool());
    this->setYAxisGridVisible(items.value(QExtPlotConstants::PLOT_PROPERTY_YAXIS_GRID_VISIBLE, true).toBool());
    this->setXAxisMinorGridVisible(items.value(QExtPlotConstants::PLOT_PROPERTY_XAXIS_MINOR_GRID_VISIBLE, false).toBool());
    this->setYAxisMinorGridVisible(items.value(QExtPlotConstants::PLOT_PROPERTY_YAXIS_MINOR_GRID_VISIBLE, false).toBool());
    this->setTitle(QEXT_FROM_UNICODES_STRING(items.value(QExtPlotConstants::PLOT_PROPERTY_TITLE, "").toString()));
}

QExtSerializable::SerializedItemsMap QExtPlot::serializeSave() const
{
    QExtSerializable::SerializedItemsMap items;
    items[QExtPlotConstants::PLOT_PROPERTY_ID] = this->id();
    items[QExtPlotConstants::PLOT_PROPERTY_TYPE] = this->typeString();
    items[QExtPlotConstants::PLOT_PROPERTY_GROUP] = this->groupName();
    items[QExtPlotConstants::PLOT_PROPERTY_VISIBLE] = this->isVisible();
    items[QExtPlotConstants::PLOT_PROPERTY_XAXIS_RANGE_MIN] = this->xAxisMin();
    items[QExtPlotConstants::PLOT_PROPERTY_XAXIS_RANGE_MAX] = this->xAxisMax();
    items[QExtPlotConstants::PLOT_PROPERTY_YAXIS_RANGE_MIN] = this->yAxisMin();
    items[QExtPlotConstants::PLOT_PROPERTY_YAXIS_RANGE_MAX] = this->yAxisMax();
    items[QExtPlotConstants::PLOT_PROPERTY_XAXIS_AUTO_SCALE] = this->isXAxisAutoScaled();
    items[QExtPlotConstants::PLOT_PROPERTY_YAXIS_AUTO_SCALE] = this->isYAxisAutoScaled();
    items[QExtPlotConstants::PLOT_PROPERTY_XAXIS_GRID_VISIBLE] = this->isXAxisGridVisible();
    items[QExtPlotConstants::PLOT_PROPERTY_YAXIS_GRID_VISIBLE] = this->isYAxisGridVisible();
    items[QExtPlotConstants::PLOT_PROPERTY_XAXIS_MINOR_GRID_VISIBLE] = this->isXAxisMinorGridVisible();
    items[QExtPlotConstants::PLOT_PROPERTY_YAXIS_MINOR_GRID_VISIBLE] = this->isYAxisMinorGridVisible();
    items[QExtPlotConstants::PLOT_PROPERTY_TITLE] = QEXT_TO_UNICODES_STRING(this->title().text());
    return items;
}

qint64 QExtPlot::loadId(const SerializedItemsMap &items)
{
    return items.value(QExtPlotConstants::PLOT_PROPERTY_ID, -1).toLongLong();
}

QString QExtPlot::loadType(const SerializedItemsMap &items)
{
    return items.value(QExtPlotConstants::PLOT_PROPERTY_TYPE, "").toString();
}

QString QExtPlot::loadGroup(const SerializedItemsMap &items)
{
    return items.value(QExtPlotConstants::PLOT_PROPERTY_GROUP, "").toString();
}

void QExtPlot::resetAxes()
{
    Q_D(QExtPlot);
    d->mZoomer->setZoomBase();
    if (!d->mXAxisAutoRangeUpdater.isNull())
    {
        d->mXAxisAutoRangeUpdater->updateRange();
    }
    if (!d->mYAxisAutoRangeUpdater.isNull())
    {
        d->mYAxisAutoRangeUpdater->updateRange();
    }
}

void QExtPlot::unzoom()
{
    this->resetAxes();
}

void QExtPlot::initPropertyModel(QExtPropertyModel *propertyModel)
{
    QExtPropertyModelItem *rootItem = propertyModel->rootItem();
    rootItem->appendChild(new QExtPlotGridVisibleItem(this));
    rootItem->appendChild(new QExtPlotXAxisRangeItem(this));
    rootItem->appendChild(new QExtPlotYAxisRangeItem(this));
}

QExtPlotGridVisibleItem::QExtPlotGridVisibleItem(QExtPlot *plot)
    : mPlot(plot)
{
    this->appendChild(new QExtPlotXAxisGridVisibleItem(plot));
    this->appendChild(new QExtPlotXAxisMinorGridVisibleItem(plot));
    this->appendChild(new QExtPlotYAxisGridVisibleItem(plot));
    this->appendChild(new QExtPlotYAxisMinorGridVisibleItem(plot));
}

QString QExtPlotGridVisibleItem::name() const
{
    return tr("Grid Visible");
}

Qt::ItemFlags QExtPlotGridVisibleItem::flags() const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QExtPlotXAxisGridVisibleItem::QExtPlotXAxisGridVisibleItem(QExtPlot *plot)
    : mPlot(plot)
{
    connect(plot, SIGNAL(xAxisGridVisibleChanged(bool)), this, SLOT(updateItem()));
}

QString QExtPlotXAxisGridVisibleItem::name() const
{
    return tr("XAxis Grid");
}

Qt::ItemFlags QExtPlotXAxisGridVisibleItem::flags() const
{
    return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}

QVariant QExtPlotXAxisGridVisibleItem::data(int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return mPlot->isXAxisGridVisible() ? tr("visible") : tr("invisible");
    }
    else if (role == Qt::CheckStateRole)
    {
        return mPlot->isXAxisGridVisible() ? Qt::Checked : Qt::Unchecked;
    }
    return QVariant();
}

bool QExtPlotXAxisGridVisibleItem::setData(const QVariant &value, int role)
{
    if (role == Qt::CheckStateRole)
    {
        bool checked = value.toInt() == Qt::Checked;
        mPlot->setXAxisGridVisible(checked);
        return true;
    }
    return false;
}

QExtPlotXAxisMinorGridVisibleItem::QExtPlotXAxisMinorGridVisibleItem(QExtPlot *plot)
    : mPlot(plot)
{
    connect(plot, SIGNAL(xAxisGridVisibleChanged(bool)), this, SLOT(updateItem()));
    connect(plot, SIGNAL(xAxisMinorGridVisibleChanged(bool)), this, SLOT(updateItem()));
}

QString QExtPlotXAxisMinorGridVisibleItem::name() const
{
    return tr("XAxis Minor Grid");
}

Qt::ItemFlags QExtPlotXAxisMinorGridVisibleItem::flags() const
{
    Qt::ItemFlags flags = Qt::NoItemFlags;
    if (mPlot->isXAxisGridVisible())
    {
        flags |= Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    return flags;
}

QVariant QExtPlotXAxisMinorGridVisibleItem::data(int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return mPlot->isXAxisMinorGridVisible() ? tr("visible") : tr("invisible");
    }
    else if (role == Qt::CheckStateRole)
    {
        return mPlot->isXAxisMinorGridVisible() ? Qt::Checked : Qt::Unchecked;
    }
    return QVariant();
}

bool QExtPlotXAxisMinorGridVisibleItem::setData(const QVariant &value, int role)
{
    if (role == Qt::CheckStateRole)
    {
        bool checked = value.toInt() == Qt::Checked;
        mPlot->setXAxisMinorGridVisible(checked);
        return true;
    }
    return false;
}

QExtPlotYAxisGridVisibleItem::QExtPlotYAxisGridVisibleItem(QExtPlot *plot)
    : mPlot(plot)
{
    connect(plot, SIGNAL(yAxisGridVisibleChanged(bool)), this, SLOT(updateItem()));
}

QString QExtPlotYAxisGridVisibleItem::name() const
{
    return tr("YAxis Grid");
}

Qt::ItemFlags QExtPlotYAxisGridVisibleItem::flags() const
{
    return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}

QVariant QExtPlotYAxisGridVisibleItem::data(int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return mPlot->isYAxisGridVisible() ? tr("visible") : tr("invisible");
    }
    else if (role == Qt::CheckStateRole)
    {
        return mPlot->isYAxisGridVisible() ? Qt::Checked : Qt::Unchecked;
    }
    return QVariant();
}

bool QExtPlotYAxisGridVisibleItem::setData(const QVariant &value, int role)
{
    if (role == Qt::CheckStateRole)
    {
        bool checked = value.toInt() == Qt::Checked;
        mPlot->setYAxisGridVisible(checked);
        return true;
    }
    return false;
}

QExtPlotYAxisMinorGridVisibleItem::QExtPlotYAxisMinorGridVisibleItem(QExtPlot *plot)
    : mPlot(plot)
{
    connect(plot, SIGNAL(yAxisGridVisibleChanged(bool)), this, SLOT(updateItem()));
    connect(plot, SIGNAL(yAxisMinorGridVisibleChanged(bool)), this, SLOT(updateItem()));
}

QString QExtPlotYAxisMinorGridVisibleItem::name() const
{
    return tr("YAxis Minor Grid");
}

Qt::ItemFlags QExtPlotYAxisMinorGridVisibleItem::flags() const
{
    Qt::ItemFlags flags = Qt::NoItemFlags;
    if (mPlot->isYAxisGridVisible())
    {
        flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
    }
    return flags;
}

QVariant QExtPlotYAxisMinorGridVisibleItem::data(int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return mPlot->isYAxisMinorGridVisible() ? tr("visible") : tr("invisible");
    }
    else if (role == Qt::CheckStateRole)
    {
        return mPlot->isYAxisMinorGridVisible() ? Qt::Checked : Qt::Unchecked;
    }
    return QVariant();
}

bool QExtPlotYAxisMinorGridVisibleItem::setData(const QVariant &value, int role)
{
    if (role == Qt::CheckStateRole)
    {
        bool checked = value.toInt() == Qt::Checked;
        mPlot->setYAxisMinorGridVisible(checked);
        return true;
    }
    return false;
}



QExtPlotXAxisRangeItem::QExtPlotXAxisRangeItem(QExtPlot *plot)
    : mPlot(plot)
{
    this->appendChild(new QExtPlotXAxisMinItem(plot));
    this->appendChild(new QExtPlotXAxisMaxItem(plot));
    connect(plot, SIGNAL(xAxisAutoScaleChanged(bool)), this, SLOT(updateItem()));
}

QString QExtPlotXAxisRangeItem::name() const
{
    return tr("X Axis Range");
}

Qt::ItemFlags QExtPlotXAxisRangeItem::flags() const
{
    Qt::ItemFlags flags =  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if (mPlot->xAxisAutoRangeUpdater())
    {
        flags |= Qt::ItemIsUserCheckable;
    }
    return flags;
}

QVariant QExtPlotXAxisRangeItem::data(int role) const
{
    if (Qt::DisplayRole == role)
    {
        return mPlot->xAxisAutoRangeUpdater() ? mPlot->xAxisAutoRangeUpdater()->labelText() : "";
    }
    else if (Qt::EditRole == role)
    {
        return mPlot->isXAxisAutoScaled() ? Qt::Checked : Qt::Unchecked;
    }
    else if (mPlot->xAxisAutoRangeUpdater() && Qt::CheckStateRole == role)
    {
        return mPlot->isXAxisAutoScaled() ? Qt::Checked : Qt::Unchecked;
    }
    return QVariant();
}

bool QExtPlotXAxisRangeItem::setData(const QVariant &value, int role)
{
    if (role == Qt::CheckStateRole)
    {
        bool checked = value.toInt() == Qt::Checked;
        mPlot->setXAxisAutoScaled(checked);
        this->updateChildrenItems();
        return true;
    }
    return false;
}


QExtPlotXAxisMinItem::QExtPlotXAxisMinItem(QExtPlot *plot)
    : mPlot(plot)
{
    connect(plot, SIGNAL(xAxisRangeChanged()), this, SLOT(updateItem()));
    connect(plot, SIGNAL(xAxisAutoScaleChanged(bool)), this, SLOT(updateItem()));
}

QString QExtPlotXAxisMinItem::name() const
{
    return tr("X Min");
}

Qt::ItemFlags QExtPlotXAxisMinItem::flags() const
{
    Qt::ItemFlags flags = Qt::NoItemFlags;
    if (!mPlot->isXAxisAutoScaled())
    {
        flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
    }
    return flags;
}

QWidget *QExtPlotXAxisMinItem::initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                                  const QModelIndex &index) const
{
    QExtDoubleSpinBox *widget = dynamic_cast<QExtDoubleSpinBox *>(editor);
    if (widget)
    {
        widget->setRange(QEXT_INT_MIN, mPlot->xAxisMax());
    }
    return QExtPropertyModelItem::initEditorProperty(editor, option, index);
}

QVariant QExtPlotXAxisMinItem::data(int role) const
{
    if (Qt::DisplayRole == role)
    {
        return QExtNumeric::doubleTrimmedText(mPlot->xAxisMin());
    }
    else if (Qt::EditRole == role)
    {
        return mPlot->xAxisMin();
    }
    return QVariant();
}

bool QExtPlotXAxisMinItem::setData(const QVariant &value, int role)
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        mPlot->setXAxisMin(value.toDouble());
        return true;
    }
    return false;
}

QExtPlotXAxisMaxItem::QExtPlotXAxisMaxItem(QExtPlot *plot)
    : mPlot(plot)
{
    connect(plot, SIGNAL(xAxisRangeChanged()), this, SLOT(updateItem()));
    connect(plot, SIGNAL(xAxisAutoScaleChanged(bool)), this, SLOT(updateItem()));
}

QString QExtPlotXAxisMaxItem::name() const
{
    return tr("X Max");
}

Qt::ItemFlags QExtPlotXAxisMaxItem::flags() const
{
    Qt::ItemFlags flags = Qt::NoItemFlags;
    if (!mPlot->isXAxisAutoScaled())
    {
        flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
    }
    return flags;
}

QWidget *QExtPlotXAxisMaxItem::initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                                  const QModelIndex &index) const
{
    QExtDoubleSpinBox *widget = dynamic_cast<QExtDoubleSpinBox *>(editor);
    if (widget)
    {
        widget->setRange(mPlot->xAxisMin(), QEXT_INT_MAX);
    }
    return QExtPropertyModelItem::initEditorProperty(editor, option, index);
}

QVariant QExtPlotXAxisMaxItem::data(int role) const
{
    if (Qt::DisplayRole == role)
    {
        return QExtNumeric::doubleTrimmedText(mPlot->xAxisMax());
    }
    else if (Qt::EditRole == role)
    {
        return mPlot->xAxisMax();
    }
    return QVariant();
}

bool QExtPlotXAxisMaxItem::setData(const QVariant &value, int role)
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        mPlot->setXAxisMax(value.toDouble());
        return true;
    }
    return false;
}



QExtPlotYAxisRangeItem::QExtPlotYAxisRangeItem(QExtPlot *plot)
    : mPlot(plot)
{
    this->appendChild(new QExtPlotYAxisMinItem(plot));
    this->appendChild(new QExtPlotYAxisMaxItem(plot));
    connect(plot, SIGNAL(yAxisAutoScaleChanged(bool)), this, SLOT(updateItem()));
}

QString QExtPlotYAxisRangeItem::name() const
{
    return tr("Y Axis Range");
}

Qt::ItemFlags QExtPlotYAxisRangeItem::flags() const
{
    Qt::ItemFlags flags =  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if (mPlot->yAxisAutoRangeUpdater())
    {
        flags |= Qt::ItemIsUserCheckable;
    }
    return flags;
}

QVariant QExtPlotYAxisRangeItem::data(int role) const
{
    if (Qt::DisplayRole == role)
    {
        return mPlot->yAxisAutoRangeUpdater() ? mPlot->yAxisAutoRangeUpdater()->labelText() : "";
    }
    else if (Qt::EditRole == role)
    {
        return mPlot->isYAxisAutoScaled() ? Qt::Checked : Qt::Unchecked;
    }
    else if (mPlot->yAxisAutoRangeUpdater() && Qt::CheckStateRole == role)
    {
        return mPlot->isYAxisAutoScaled() ? Qt::Checked : Qt::Unchecked;
    }
    return QVariant();
}

bool QExtPlotYAxisRangeItem::setData(const QVariant &value, int role)
{
    if (role == Qt::CheckStateRole)
    {
        bool checked = value.toInt() == Qt::Checked;
        mPlot->setYAxisAutoScaled(checked);
        this->updateChildrenItems();
        return true;
    }
    return false;
}


QExtPlotYAxisMinItem::QExtPlotYAxisMinItem(QExtPlot *plot)
    : mPlot(plot)
{
    connect(plot, SIGNAL(yAxisRangeChanged()), this, SLOT(updateItem()));
    connect(plot, SIGNAL(yAxisAutoScaleChanged(bool)), this, SLOT(updateItem()));
}

QString QExtPlotYAxisMinItem::name() const
{
    return tr("Y Min");
}

Qt::ItemFlags QExtPlotYAxisMinItem::flags() const
{
    Qt::ItemFlags flags = Qt::NoItemFlags;
    if (!mPlot->isYAxisAutoScaled())
    {
        flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
    }
    return flags;
}

QWidget *QExtPlotYAxisMinItem::initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                                  const QModelIndex &index) const
{
    QExtDoubleSpinBox *widget = dynamic_cast<QExtDoubleSpinBox *>(editor);
    if (widget)
    {
        widget->setRange(QEXT_INT_MIN, mPlot->yAxisMax());
    }
    return QExtPropertyModelItem::initEditorProperty(editor, option, index);
}

QVariant QExtPlotYAxisMinItem::data(int role) const
{
    if (Qt::DisplayRole == role)
    {
        return QExtNumeric::doubleTrimmedText(mPlot->yAxisMin());
    }
    else if (Qt::EditRole == role)
    {
        return mPlot->yAxisMin();
    }
    return QVariant();
}

bool QExtPlotYAxisMinItem::setData(const QVariant &value, int role)
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        mPlot->setYAxisMin(value.toDouble());
        return true;
    }
    return false;
}

QExtPlotYAxisMaxItem::QExtPlotYAxisMaxItem(QExtPlot *plot)
    : mPlot(plot)
{
    connect(plot, SIGNAL(yAxisRangeChanged()), this, SLOT(updateItem()));
    connect(plot, SIGNAL(yAxisAutoScaleChanged(bool)), this, SLOT(updateItem()));
}

QString QExtPlotYAxisMaxItem::name() const
{
    return tr("Y Max");
}

Qt::ItemFlags QExtPlotYAxisMaxItem::flags() const
{
    Qt::ItemFlags flags = Qt::NoItemFlags;
    if (!mPlot->isYAxisAutoScaled())
    {
        flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
    }
    return flags;
}

QWidget *QExtPlotYAxisMaxItem::initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                                  const QModelIndex &index) const
{
    QExtDoubleSpinBox *widget = dynamic_cast<QExtDoubleSpinBox *>(editor);
    if (widget)
    {
        widget->setRange(mPlot->yAxisMin(), QEXT_INT_MAX);
    }
    return QExtPropertyModelItem::initEditorProperty(editor, option, index);
}

QVariant QExtPlotYAxisMaxItem::data(int role) const
{
    if (Qt::DisplayRole == role)
    {
        return QExtNumeric::doubleTrimmedText(mPlot->yAxisMax());
    }
    else if (Qt::EditRole == role)
    {
        return mPlot->yAxisMax();
    }
    return QVariant();
}

bool QExtPlotYAxisMaxItem::setData(const QVariant &value, int role)
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        mPlot->setYAxisMax(value.toDouble());
        return true;
    }
    return false;
}
