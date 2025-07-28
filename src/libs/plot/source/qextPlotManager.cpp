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

    void removePlotSerializable(const QString &tag);
    void removePlotSerializable(QExtSerializable *serializable);
    void insertPlotSerializable(const QString &tag, QExtSerializable *serializable);
    void insertPlotSerializable(const QString &tag, const QExtSerializable::SerializedItems &items);

    QExtIdRegistry mIdRegistry;
    QExtPlotFactory mPlotFactory;
    QList<QExtPlot::SharedPtr> mPlotList;
    QHash<qint64, QExtPlot::SharedPtr> mIdToPlotMap;
    QHash<QString, QExtPlot::SharedPtr> mNameToPlotMap;
    QHash<QString, QExtPlotGroup::SharedPtr> mPlotGroupMap;
    QSet<QExtSerializable*> mPlotSerializableConstructEnableSet;
    QHash<QString, QExtSerializableProxy> mPlotSerializableProxyMap;
};

QExtPlotManagerPrivate::QExtPlotManagerPrivate(QExtPlotManager *q)
    : q_ptr(q)
{
}

QExtPlotManagerPrivate::~QExtPlotManagerPrivate()
{
}

void QExtPlotManagerPrivate::removePlotSerializable(const QString &tag)
{
    mPlotSerializableProxyMap.remove(tag);
}

void QExtPlotManagerPrivate::removePlotSerializable(QExtSerializable *serializable)
{
    foreach (const QString &tag, mPlotSerializableProxyMap.keys())
    {
        if (serializable == mPlotSerializableProxyMap.value(tag, QExtSerializableProxy()).serializable())
        {
            mPlotSerializableProxyMap.remove(tag);
            return;
        }
    }
}

namespace detail
{
void plotSerializableDestroyedNotifyFunction(QExtSerializable *serializable, const QVariant &usrdata)
{
    if (usrdata.canConvert<qulonglong>())
    {
        QExtPlotManagerPrivate *manager = reinterpret_cast<QExtPlotManagerPrivate*>(usrdata.toULongLong());
        if (manager)
        {
            manager->removePlotSerializable(serializable);
        }
    }
}
}
void QExtPlotManagerPrivate::insertPlotSerializable(const QString &tag, QExtSerializable *serializable)
{
    QExtSerializableProxy proxy = mPlotSerializableProxyMap.value(tag, QExtSerializableProxy());
    if (proxy.serializable())
    {
        proxy.serializable()->removeDestroyedNotifyFunction(detail::plotSerializableDestroyedNotifyFunction);
    }
    if (serializable)
    {
        serializable->appendDestroyedNotifyFunction(detail::plotSerializableDestroyedNotifyFunction,
                                                    reinterpret_cast<qulonglong>(this));
        mPlotSerializableProxyMap.insert(tag, QExtSerializableProxy(serializable));
    }
}

void QExtPlotManagerPrivate::insertPlotSerializable(const QString &tag, const QExtSerializable::SerializedItems &items)
{
    mPlotSerializableProxyMap.insert(tag, QExtSerializableProxy(items));
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

bool QExtPlotManager::isPlotSerializationConstructEnabled(const QExtPlot::SharedPtr &plot)
{
    Q_D(const QExtPlotManager);
    return d->mIdToPlotMap.contains(plot->id()) && d->mPlotSerializableConstructEnableSet.contains(plot.data());
}

void QExtPlotManager::setPlotSerializationConstructEnable(const QExtPlot::SharedPtr &plot, bool enable)
{
    Q_D(QExtPlotManager);
    if (d->mIdToPlotMap.contains(plot->id()))
    {
        if (enable)
        {
            d->mPlotSerializableConstructEnableSet.insert(plot.data());
        }
        else
        {
            d->mPlotSerializableConstructEnableSet.remove(plot.data());
        }
    }
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
        d->mPlotSerializableConstructEnableSet.insert(plot.data());
        d->removePlotSerializable(plot->name());
        d->mNameToPlotMap.remove(plot->name());
        d->mIdToPlotMap.remove(plot->id());
        d->mPlotList.removeOne(plot);
        emit this->plotUnregistered(plot);
    }
    if (!plot.isNull())
    {
        plot->setParent(QEXT_NULLPTR);
    }
}

QExtPlot::SharedPtr QExtPlotManager::createRegisterPlot(const QString &type, qint64 id, const QString &groupName)
{
    Q_D(QExtPlotManager);
    QExtPlot::SharedPtr plot = d->mPlotFactory.createPlot(type);
    if (this->registerPlot(plot, id, groupName).isNull())
    {
        return QEXT_NULLPTR;
    }
    return plot;
}

QExtPlot::SharedPtr QExtPlotManager::createRegisterPlot(const QString &type, const QString &name,
                                                        const QString &groupName)
{
    Q_D(QExtPlotManager);
    QExtPlot::SharedPtr plot = d->mPlotFactory.createPlot(type);
    if (this->registerPlot(plot, name, groupName).isNull())
    {
        return QEXT_NULLPTR;
    }
    return plot;
}

QExtPlotGroup::SharedPtr QExtPlotManager::registerPlot(QExtPlot::SharedPtr &plot, qint64 id, const QString &name,
                                                       const QString &groupName)
{
    Q_D(QExtPlotManager);
    Q_ASSERT(!plot.isNull());

    if (d->mNameToPlotMap.contains(name))
    {
        qCritical() << QString("QExtPlotManager::registerPlot():plot name %1 exist!").arg(name);
        return QEXT_NULLPTR;
    }

    /* init plot */
    if (0 == id || d->mIdRegistry.isIdRegisterd(id))
    {
        id = d->mIdRegistry.requestId();
    }
    d->mIdRegistry.registerId(id);
    if (!plot->initPlot(id, name, groupName))
    {
        qCritical() << QString("QExtPlotManager::registerPlot():plot init failed!");
        return QEXT_NULLPTR;
    }

    /* init plot group */
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

    /* register plot */
    emit this->plotAboutToBeRegistered(plot);
    plot->serializeLoad(this->plotSerializedItems(plot->name()));
    d->mPlotSerializableConstructEnableSet.insert(plot.data());
    d->insertPlotSerializable(plot->name(), plot.data());
    d->mPlotGroupMap.insert(groupName, plotGroup);
    d->mNameToPlotMap.insert(plot->name(), plot);
    d->mIdToPlotMap.insert(id, plot);
    d->mPlotList.append(plot);
    emit this->plotRegistered(plot);
    emit this->plotListChanged(d->mPlotList);
    return plotGroup;
}

QExtPlotModel *QExtPlotManager::makePlotModel(QObject *parent)
{
    return new QExtPlotModel(this, parent ? parent : this);
}

QExtSerializable::SerializedItems QExtPlotManager::plotSerializedItems(const QString &tag) const
{
    Q_D(const QExtPlotManager);
    return d->mPlotSerializableProxyMap.value(tag, QExtSerializableProxy()).serializeSave();
}

// bool QExtPlotManager::containsPlotSerializable(const QString &tag) const
// {
//     Q_D(const QExtPlotManager);
//     return d->mPlotSerializableMap.contains(tag);
// }

// bool QExtPlotManager::containsPlotSerializable(QExtSerializable *serializable) const
// {
//     Q_D(const QExtPlotManager);
//     foreach (const QExtSerializableProxy &proxy, d->mPlotSerializableMap.values())
//     {
//         if (serializable == proxy.serializable())
//         {
//             return true;
//         }
//     }
//     return false;
// }

// void QExtPlotManager::removePlotSerializable(const QString &tag)
// {
//     Q_D(QExtPlotManager);
//     d->mPlotSerializableMap.remove(tag);
// }

// void QExtPlotManager::removePlotSerializable(QExtSerializable *serializable)
// {
//     Q_D(QExtPlotManager);
//     foreach (const QString &tag, d->mPlotSerializableMap.keys())
//     {
//         if (serializable == d->mPlotSerializableMap.value(tag, QExtSerializableProxy()).serializable())
//         {
//             d->mPlotSerializableMap.remove(tag);
//             return;
//         }
//     }
// }

// namespace detail
// {
// void plotSerializableDestroyedNotifyFunction(QExtSerializable *serializable, const QVariant &usrdata)
// {
//     if (usrdata.canConvert<QExtPlotManager*>())
//     {
//         QExtPlotManager *manager = usrdata.value<QExtPlotManager*>();
//         if (manager)
//         {
//             manager->removePlotSerializable(serializable);
//         }
//     }
// }
// }
// void QExtPlotManager::insertPlotSerializable(const QString &tag, QExtSerializable *serializable)
// {
//     Q_D(QExtPlotManager);
//     QExtSerializableProxy proxy = d->mPlotSerializableMap.value(tag, QExtSerializableProxy());
//     if (proxy.serializable())
//     {
//         proxy.serializable()->removeDestroyedNotifyFunction(detail::plotSerializableDestroyedNotifyFunction);
//     }
//     if (serializable)
//     {
//         serializable->appendDestroyedNotifyFunction(detail::plotSerializableDestroyedNotifyFunction,
//                                                     QVariant::fromValue<QExtPlotManager*>(this));
//         d->mPlotSerializableMap.insert(tag, QExtSerializableProxy(serializable));
//     }
// }

// void QExtPlotManager::reloadPlotSerializable(const QString &tag, QExtSerializable *serializable) const
// {
//     Q_D(const QExtPlotManager);
//     if (serializable)
//     {
//         QExtSerializableProxy proxy = d->mPlotSerializableProxyMap.value(tag, QExtSerializableProxy());
//         serializable->serializeLoad(proxy.serializeSave());
//     }
// }

void QExtPlotManager::serializeLoad(const SerializedItems &items)
{
    Q_D(QExtPlotManager);
    QExtSerializable::SerializedItems::ConstIterator iter(items.constBegin());
    while (items.constEnd() != iter)
    {
        const QExtSerializable::SerializedItems childItems = iter.value().toHash();
        const QString key = iter.key();

        const bool instantiation = childItems.value(QExtPlotConstants::PLOT_PROPERTY_CONSTRUCT, false).toBool();
        if (instantiation)
        {
            const QString group = QExtPlot::loadGroup(childItems);
            const QString type = QExtPlot::loadType(childItems);
            const qint64 id = QExtPlot::loadId(childItems);
            if (id >= 0 && !type.isEmpty())
            {
                QExtPlot::SharedPtr plot = this->createRegisterPlot(type, id, group);
                if (!plot.isNull())
                {
                    d->insertPlotSerializable(key, plot.data());
                    plot->serializeLoad(childItems);
                    plot->hide();
                }
            }
        }
        else
        {
            d->insertPlotSerializable(key, childItems);
        }
        iter++;
    }
}

QExtSerializable::SerializedItems QExtPlotManager::serializeSave() const
{
    Q_D(const QExtPlotManager);
    QExtSerializable::SerializedItems items;
    QHashIterator<QString, QExtSerializableProxy> iter(d->mPlotSerializableProxyMap);
    while (iter.hasNext())
    {
        iter.next();
        QExtSerializableProxy proxy = iter.value();
        QExtSerializable *serializable = proxy.serializable();
        if (serializable)
        {
            SerializedItems childItems = serializable->serializeSave();
            const bool constructEnable = d->mPlotSerializableConstructEnableSet.contains(serializable);
            childItems[QExtPlotConstants::PLOT_PROPERTY_CONSTRUCT] = constructEnable;
            items.insert(iter.key(), childItems);
        }
    }
    return items;
}

QExtPlotManager::QExtPlotManager(QObject *parent)
    : QExtSerializableObject(parent)
    , dd_ptr(new QExtPlotManagerPrivate(this))
{
}

void QExtPlotManager::onAboutToBeDestroyed()
{
    Q_D(QExtPlotManager);
    QList<QExtPlot::SharedPtr>::ConstIterator iter(d->mPlotList.constBegin());
    while (d->mPlotList.constEnd() != iter)
    {
        this->unregisterPlot(*iter);
        (*iter)->removeDestroyedNotifyFunction(detail::plotSerializableDestroyedNotifyFunction);
        iter++;
    }
}

QExtPlotManager::~QExtPlotManager()
{
}
