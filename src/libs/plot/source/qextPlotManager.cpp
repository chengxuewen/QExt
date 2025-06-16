#include <qextPlotManager.h>
#include <qextIdRegistry.h>

#include <qextOnceFlag.h>

class QExtPlotManagerPrivate
{
    QExtPlotManager * const q_ptr;
    QEXT_DECL_PUBLIC(QExtPlotManager)
    QEXT_DISABLE_COPY_MOVE(QExtPlotManagerPrivate)
public:
    explicit QExtPlotManagerPrivate(QExtPlotManager *q);
    virtual ~QExtPlotManagerPrivate();

    QExtIdRegistry mIdRegistry;
    QExtPlotFactory mPlotFactory;
    QList<QExtPlot::SharedPtr> mPlotList;
    QHash<qint64, QExtPlot::SharedPtr> mIdToPlotMap;
    QHash<QString, QExtPlotGroup::SharedPtr> mPlotGroupMap;
};

QExtPlotManagerPrivate::QExtPlotManagerPrivate(QExtPlotManager *q)
    : q_ptr(q)
{
}

QExtPlotManagerPrivate::~QExtPlotManagerPrivate()
{
}


QExtPlotFactory &QExtPlotManager::plotFactory()
{
    Q_D(QExtPlotManager);
    return d->mPlotFactory;
}

int QExtPlotManager::plotCount() const
{
    Q_D(const QExtPlotManager);
    return d->mPlotList.size();
}

QExtPlot::SharedPtr QExtPlotManager::plot(int index) const
{
    Q_D(const QExtPlotManager);
    return index >= 0 && index < d->mPlotList.size() ? d->mPlotList.at(index) : QEXT_NULLPTR;
}

QList<QExtPlot::SharedPtr> QExtPlotManager::plotList() const
{
    Q_D(const QExtPlotManager);
    return d->mPlotList;
}

int QExtPlotManager::plotIndex(const QExtPlot::SharedPtr &plot) const
{
    Q_D(const QExtPlotManager);
    return d->mPlotList.indexOf(plot);
}

QExtPlotGroup::SharedPtr QExtPlotManager::plotGroup(const QString &name) const
{
    Q_D(const QExtPlotManager);
    return d->mPlotGroupMap.value(name);
}

void QExtPlotManager::unregisterPlot(const QExtPlot::SharedPtr &plot)
{
    Q_D(QExtPlotManager);
    if (!d->mPlotList.contains(plot))
    {
        emit this->plotAboutToBeUnregistered(plot);
        QHash<QString, QExtPlotGroup::SharedPtr>::Iterator iter = d->mPlotGroupMap.begin();
        while (d->mPlotGroupMap.end() != iter)
        {
            (*iter)->remove(plot);
            iter++;
        }
        d->mIdToPlotMap.remove(plot->id());
        d->mPlotList.removeOne(plot);
        emit this->plotUnregistered(plot);
    }
    if (!plot.isNull())
    {
        plot->setParent(QEXT_NULLPTR);
    }
}

QExtPlot::SharedPtr QExtPlotManager::createRegisterPlot(const QString &type, const QString &groupName)
{
    Q_D(QExtPlotManager);
    QExtPlot::SharedPtr plot = d->mPlotFactory.createPlot(type);
    this->registerPlot(plot, groupName);
    return plot;
}

QExtPlotGroup::SharedPtr QExtPlotManager::registerPlot(QExtPlot::SharedPtr &plot, const QString &groupName)
{
    Q_D(QExtPlotManager);
    Q_ASSERT(!plot.isNull());

    QExtPlotGroup::SharedPtr plotGroup = d->mPlotGroupMap.value(groupName);
    if (plotGroup.isNull())
    {
        emit this->plotGroupAboutToBeCreated(plotGroup);
        plotGroup.reset(new QExtPlotGroup(groupName, this));
        emit this->plotGroupCreated(plotGroup);
    }
    if (plotGroup->contains(plot))
    {
        return plotGroup;
    }

    emit this->plotAboutToBeRegistered(plot);
    const qint64 plotId = d->mIdRegistry.requestId();
    plot->initPlot(plotId);
    d->mPlotGroupMap.insert(groupName, plotGroup);
    d->mIdToPlotMap.insert(plotId, plot);
    d->mPlotList.append(plot);
    emit this->plotRegistered(plot);
    emit this->plotListChanged(d->mPlotList);
    return plotGroup;
}

QExtPlotModel *QExtPlotManager::makePlotModel(QObject *parent)
{
    return new QExtPlotModel(this, parent ? parent : this);
}

void QExtPlotManager::serializeLoad(const SerializedItems &items)
{

}

QExtSerializable::SerializedItems QExtPlotManager::serializeSave() const
{
    Q_D(const QExtPlotManager);
    QExtSerializable::SerializedItems items;

    return items;
}

QExtPlotManager::QExtPlotManager(QObject *parent)
    : QExtSerializableObject(parent)
    , dd_ptr(new QExtPlotManagerPrivate(this))
{
}

QExtPlotManager::~QExtPlotManager()
{
}
