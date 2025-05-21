#include <qextIdRegistry.h>

#include <QMap>
#include <QList>
#include <QDebug>

class QExtIdRegistryPrivate
{
public:
    explicit QExtIdRegistryPrivate(QExtIdRegistry *q);
    virtual ~QExtIdRegistryPrivate();

    QExtIdRegistry * const q_ptr;

    qint64 mCounter;
    QList<qint64> mFreeIdList;
    QList<qint64> mUsedIdList;
    QMap<QObject *, qint64> mObjectToIdMap;

private:
    Q_DECLARE_PUBLIC(QExtIdRegistry)
    Q_DISABLE_COPY(QExtIdRegistryPrivate)
};

QExtIdRegistryPrivate::QExtIdRegistryPrivate(QExtIdRegistry *q)
    : q_ptr(q)
    , mCounter(0)
{
}

QExtIdRegistryPrivate::~QExtIdRegistryPrivate()
{
}

QExtIdRegistry::QExtIdRegistry(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtIdRegistryPrivate(this))
{
}

QExtIdRegistry::~QExtIdRegistry()
{
}

qint64 QExtIdRegistry::registerdIdCount() const
{
    Q_D(const QExtIdRegistry);
    return d->mUsedIdList.size();
}

bool QExtIdRegistry::isIdRegisterd(qint64 id) const
{
    Q_D(const QExtIdRegistry);
    return d->mUsedIdList.contains(id);
}

qint64 QExtIdRegistry::requestId(QObject *obj)
{
    Q_D(QExtIdRegistry);
    qint64 id = d->mFreeIdList.isEmpty() ? ++d->mCounter : d->mFreeIdList.takeFirst();
    while (d->mFreeIdList.isEmpty() && d->mUsedIdList.contains(id))
    {
        id = ++d->mCounter;
    }
    if (obj)
    {
        if (d->mObjectToIdMap.contains(obj))
        {
            qWarning() << "QExtIdRegistry::requestId(): obj repeated requests id";
            return d->mObjectToIdMap.value(obj);
        }
        connect(obj, &QObject::destroyed, this, &QExtIdRegistry::onRequestIdObjectDestroyed);
        d->mObjectToIdMap.insert(obj, id);
    }
    this->registerId(id);
    return id;
}

void QExtIdRegistry::registerId(qint64 id)
{
    Q_D(QExtIdRegistry);
    if (d->mFreeIdList.contains(id))
    {
        d->mFreeIdList.removeOne(id);
        qSort(d->mFreeIdList);
    }
    if (!d->mUsedIdList.contains(id))
    {
        d->mUsedIdList.append(id);
        qSort(d->mUsedIdList);
    }
}

void QExtIdRegistry::unregisterId(qint64 id)
{
    Q_D(QExtIdRegistry);
    if (!d->mFreeIdList.contains(id))
    {
        d->mFreeIdList.append(id);
        qSort(d->mFreeIdList);
    }
    if (d->mUsedIdList.contains(id))
    {
        d->mUsedIdList.removeOne(id);
        qSort(d->mUsedIdList);
    }
}

void QExtIdRegistry::registerObjectWithId(QObject *obj, qint64 id)
{
    Q_D(QExtIdRegistry);
    if (obj)
    {
        if (d->mObjectToIdMap.contains(obj))
        {
            obj->disconnect(this);
            qint64 oldId = d->mObjectToIdMap.value(obj);
            this->unregisterId(oldId);
        }
        connect(obj, &QObject::destroyed, this, &QExtIdRegistry::onRequestIdObjectDestroyed);
        d->mObjectToIdMap.insert(obj, id);
        this->registerId(id);
    }
}

void QExtIdRegistry::onRequestIdObjectDestroyed(QObject *obj)
{
    Q_D(QExtIdRegistry);
    if (d->mObjectToIdMap.contains(obj))
    {
        qint64 id = d->mObjectToIdMap.value(obj);
        d->mObjectToIdMap.remove(obj);
        this->unregisterId(id);
    }
}
