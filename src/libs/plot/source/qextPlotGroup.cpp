#include <qextPlotGroup.h>

class QExtPlotGroupPrivate
{
    QExtPlotGroup * const q_ptr;
    QEXT_DECL_PUBLIC(QExtPlotGroup)
    QEXT_DISABLE_COPY_MOVE(QExtPlotGroupPrivate)
public:
    QExtPlotGroupPrivate(QExtPlotGroup *q, const QString &name);
    virtual ~QExtPlotGroupPrivate();

    QString mName;
    QList<QExtPlot::SharedPtr> mPlotList;
    QHash<qint64, QExtPlot::SharedPtr> mPlotMap;
};

QExtPlotGroupPrivate::QExtPlotGroupPrivate(QExtPlotGroup *q, const QString &name)
    : q_ptr(q), mName(name)
{
}

QExtPlotGroupPrivate::~QExtPlotGroupPrivate()
{
}

QExtPlotGroup::QExtPlotGroup(const QString &name, QObject *parent)
    : QExtSerializableObject(parent)
    , dd_ptr(new QExtPlotGroupPrivate(this, name))
{
}

QExtPlotGroup::~QExtPlotGroup()
{
}

QString QExtPlotGroup::name() const
{
    Q_D(const QExtPlotGroup);
    return d->mName;
}

QExtPlot::SharedPtr QExtPlotGroup::plot(qint64 id) const
{
    Q_D(const QExtPlotGroup);
    return d->mPlotMap.value(id);
}

QList<QExtPlot::SharedPtr> QExtPlotGroup::plotList() const
{
    Q_D(const QExtPlotGroup);
    return d->mPlotList;
}

void QExtPlotGroup::insert(const QExtPlot::SharedPtr &plot)
{
    Q_D(QExtPlotGroup);
    if (!d->mPlotList.contains(plot))
    {
        Q_EMIT this->plotAboutToBeInserted(plot);
        d->mPlotList.append(plot);
        Q_EMIT this->plotInserted(plot);
    }
}

void QExtPlotGroup::remove(const QExtPlot::SharedPtr &plot)
{
    Q_D(QExtPlotGroup);
    if (d->mPlotList.contains(plot))
    {
        Q_EMIT this->plotAboutToBeRemoved(plot);
        d->mPlotList.removeOne(plot);
        Q_EMIT this->plotRemoved(plot);
    }
}

bool QExtPlotGroup::contains(qint64 plotId) const
{
    Q_D(const QExtPlotGroup);
    return d->mPlotMap.contains(plotId);
}

bool QExtPlotGroup::contains(const QExtPlot::SharedPtr &plot) const
{
    Q_D(const QExtPlotGroup);
    return d->mPlotList.contains(plot);
}

void QExtPlotGroup::serializeLoad(const SerializedItems &items)
{

}

QExtSerializable::SerializedItems QExtPlotGroup::serializeSave() const
{
    Q_D(const QExtPlotGroup);
    QExtSerializable::SerializedItems items;
    return items;
}

