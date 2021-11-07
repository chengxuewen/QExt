#include <qextMvvmModel.h>
#include <qextMvvmModel_p.h>
#include <qextMvvmCommandService.h>
#include <qextMvvmFactory.h>
#include <qextMvvmUtils.h>
#include <qextMvvmItemCatalogue.h>
#include <qextMvvmItemFactory.h>
#include <qextMvvmItemManager.h>
#include <qextMvvmItemPool.h>
#include <qextMvvmUtils.h>
#include <qextMvvmItem.h>
#include <qextMvvmTagInfo.h>
#include <qextMvvmTagRow.h>
#include <qextMvvmModelMapper.h>
#include <qextMvvmFactory.h>


QEXTMvvmModelPrivate::QEXTMvvmModelPrivate(QEXTMvvmModel *q)
    : q_ptr(q)
    , m_itemManager(new QEXTMvvmItemManager)
    , m_commands(new QEXTMvvmCommandService(q))
    , m_mapper(new QEXTMvvmModelMapper(q))
{

}

QEXTMvvmModelPrivate::~QEXTMvvmModelPrivate()
{
    m_mapper->callOnModelDestroyed();
}



QEXTMvvmModel::QEXTMvvmModel(const QString &modelType, const QSharedPointer<QEXTMvvmItemPool> &pool)
    : d_ptr(new QEXTMvvmModelPrivate(this))
{
    QEXT_DECL_D(QEXTMvvmModel);
    d->m_modelType = modelType;
    if (!pool.isNull())
    {
        d->m_itemManager->setItemPool(pool);
    }
    else
    {
        d->m_itemManager->setItemPool(QSharedPointer<QEXTMvvmItemPool>(new QEXTMvvmItemPool));
        this->createRootItem();
    }
}

QEXTMvvmModel::~QEXTMvvmModel()
{

}

void QEXTMvvmModel::setItemCatalogue(QEXTMvvmItemCatalogue *catalogue)
{
    QEXT_DECL_D(QEXTMvvmModel);
    // adding standard items to the user catalogue
    catalogue->merge(*QEXTMvvmFactory::createStandardItemCatalogue());
    d->m_itemManager->setItemFactory(new QEXTMvvmItemFactory(catalogue));
}

QString QEXTMvvmModel::modelType() const
{
    QEXT_DECL_DC(QEXTMvvmModel);
    return d->m_modelType;
}

QEXTMvvmItem *QEXTMvvmModel::insertNewItem(const QString &modelType, QEXTMvvmItem *parent,
                                           const QEXTMvvmTagRow &tagrow)
{
    // intentionally passing by value inside lambda
    auto create_func = [this, modelType]() { return factory()->createItem(modelType); };
    return this->internInsert(create_func, parent, tagrow);
}

//! Copy item and insert it in parent's tag and row.
//! Item could belong to any model/parent.

QEXTMvvmItem* QEXTMvvmModel::copyItem(QEXTMvvmItem *item, QEXTMvvmItem *parent,
                                      const QEXTMvvmTagRow &tagrow)
{
    QEXT_DECL_D(QEXTMvvmModel);
    return d->m_commands->copyItem(item, parent, tagrow);
}

QEXTMvvmItem *QEXTMvvmModel::rootItem() const
{
    QEXT_DECL_DC(QEXTMvvmModel);
    return d->m_rootItem.data();
}

QVariant QEXTMvvmModel::data(QEXTMvvmItem *item, int role) const
{
    return item->data<QVariant>(role);
}

bool QEXTMvvmModel::setData(QEXTMvvmItem *item, const QVariant &value, int role)
{
    QEXT_DECL_D(QEXTMvvmModel);
    return d->m_commands->setData(item, value, role);
}

//! Returns path from item.

QEXTMvvmPath QEXTMvvmModel::pathFromItem(QEXTMvvmItem *item) const
{
    QEXT_DECL_DC(QEXTMvvmModel);
    QEXTMvvmPath result;
    QEXTMvvmItem *current = item;
    while (current && current->parent())
    {
        result.prepend(current->parent()->children().indexOf(current));
        current = current->parent();
    }
    return result;
}

//! Returns item from path.
QEXTMvvmItem *QEXTMvvmModel::itemFromPath(const QEXTMvvmPath &path) const
{
    QEXT_DECL_DC(QEXTMvvmModel);
    QEXTMvvmItem *result = this->rootItem();
    QEXTMvvmPath::ConstIterator iter;
    for (iter = path.begin(); iter != path.end(); ++iter)
    {
        int index = *iter;
        if (index >= 0 && index < result->childrenCount())
        {
            result = result->children().at(index);
        }
        if (!result)
        {
            break;
        }
    }
    return result;
}

void QEXTMvvmModel::setUndoRedoEnabled(bool value)
{
    QEXT_DECL_D(QEXTMvvmModel);
    d->m_commands->setUndoRedoEnabled(value);
}

QEXTMvvmUndoStackInterface* QEXTMvvmModel::undoStack() const
{
    QEXT_DECL_DC(QEXTMvvmModel);
    return d->m_commands->undoStack();
}

//! Removes given row from parent.

void QEXTMvvmModel::removeItem(QEXTMvvmItem *parent, const QEXTMvvmTagRow &tagrow)
{
    QEXT_DECL_D(QEXTMvvmModel);
    d->m_commands->removeItem(parent, tagrow);
}

//! Move item from it's current parent to a new parent under given tag and row.
//! Old and new parents should belong to this model.

void QEXTMvvmModel::moveItem(QEXTMvvmItem *item, QEXTMvvmItem *newParent, const QEXTMvvmTagRow &tagrow)
{
    QEXT_DECL_D(QEXTMvvmModel);
    d->m_commands->moveItem(item, newParent, tagrow);
}

void QEXTMvvmModel::registerItem(QEXTMvvmItem *item)
{
    QEXT_DECL_D(QEXTMvvmModel);
    d->m_itemManager->registerItem(item);
    item->activate(); // activates buisiness logic
}

void QEXTMvvmModel::unregisterItem(QEXTMvvmItem *item)
{
    QEXT_DECL_D(QEXTMvvmModel);
    d->m_itemManager->unregisterItem(item);
}

QEXTMvvmModelMapper *QEXTMvvmModel::mapper() const
{
    QEXT_DECL_DC(QEXTMvvmModel);
    return d->m_mapper.data();
}

//! Removes all items from the model. If callback is provided, use it to rebuild content of root
//! item. Used while restoring the model from serialized content.

void QEXTMvvmModel::clear(QEXTMvvmItemFunction callback)
{
    QEXT_DECL_D(QEXTMvvmModel);
    this->mapper()->callOnModelAboutToBeReset();
    this->createRootItem();
    if (callback.isValid())
    {
        callback(this->rootItem());
    }
    this->mapper()->callOnModelReset();
}

//! Returns pointer to QEXTMvvmItemFactory which can generate all items supported by this model,

const QEXTMvvmItemFactoryInterface* QEXTMvvmModel::factory() const
{
    QEXT_DECL_DC(QEXTMvvmModel);
    return d->m_itemManager->factory();
}

//! Returns QEXTMvvmItem for given identifier.

QEXTMvvmItem* QEXTMvvmModel::findItem(const QString& id)
{
    QEXT_DECL_D(QEXTMvvmModel);
    return d->m_itemManager->findItem(id);
}

//! Creates root item.

void QEXTMvvmModel::createRootItem()
{
    QEXT_DECL_D(QEXTMvvmModel);
    d->m_rootItem.reset(d->m_itemManager->createRootItem());
    d->m_rootItem->setModel(this);
    d->m_rootItem->registerTag(QEXTMvvmTagInfo::universalTag("rootTag"), /*set_as_default*/ true);
}

QEXTMvvmItem *QEXTMvvmModel::internInsert(const QEXTMvvmItemFactoryFunction &func,
                                          QEXTMvvmItem *parent,
                                          const QEXTMvvmTagRow &tagrow)
{
    QEXT_DECL_D(QEXTMvvmModel);
    return d->m_commands->insertNewItem(func, parent, tagrow);
}

