#include <qextModelItem.h>
#include <qextModelItemTags.h>

class QExtModelItemPrivate
{
public:
    explicit QExtModelItemPrivate(QExtModelItem *q);
    virtual ~QExtModelItemPrivate();

    QExtModelItem * const q_ptr;

    QString m_type;


    QExtModelItem *m_parentItem;
    QScopedPointer<QExtModelItemData> m_data;
    QScopedPointer<QExtModelItemTags> m_tags;

private:
    QEXT_DECL_PUBLIC(QExtModelItem)
    QEXT_DISABLE_COPY_MOVE(QExtModelItemPrivate)
};

QExtModelItemPrivate::QExtModelItemPrivate(QExtModelItem *q)
    : q_ptr(q)
    , m_parentItem(QEXT_NULLPTR)
{

}

QExtModelItemPrivate::~QExtModelItemPrivate()
{

}

QExtModelItem::QExtModelItem(const QString &type)
    : dd_ptr(new QExtModelItemPrivate(this))
{
    dd_ptr->m_type = type;
}

QExtModelItem::QExtModelItem(QExtModelItemPrivate *d, const QString &type)
    : dd_ptr(d)
{
    dd_ptr->m_type = type;
}

QExtModelItem::~QExtModelItem()
{

}

QString QExtModelItem::modelType() const
{
    Q_D(const QExtModelItem);
    return d->m_type;
}

QVector<int> QExtModelItem::roles() const
{
    Q_D(const QExtModelItem);
    return d->m_data->roles();
}

QExtModelItem *QExtModelItem::parentItem() const
{
    Q_D(const QExtModelItem);
    return d->m_parentItem;
}

QVector<QExtModelItem *> QExtModelItem::childItems() const
{
    Q_D(const QExtModelItem);
    return d->m_tags->allItems();
}


