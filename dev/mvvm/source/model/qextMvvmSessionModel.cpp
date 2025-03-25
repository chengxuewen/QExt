// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmSessionModel.h>
#include <qextMvvmCommandService.h>
// #include "model/commands/commandservice.h"
#include <qextMvvmItemCatalogueFactory.h>
#include <qextMvvmItemCatalogue.h>
#include <qextMvvmItemFactory.h>
#include <qextMvvmItemManager.h>
#include <qextMvvmItemPool.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmTagInfo.h>
#include <qextMvvmModelMapper.h>

using namespace ModelView;

//! Pimpl class for QExtMvvmSessionModel.

struct QExtMvvmSessionModel::SessionModelImpl {
    QExtMvvmSessionModel* m_self{nullptr};
    std::string m_modelType;
    QExtUniquePointer<QExtMvvmItemManager> m_itemManager;
    QExtUniquePointer<QExtMvvmCommandService> m_commands;
    QExtUniquePointer<QExtMvvmModelMapper> m_mapper;
    QExtUniquePointer<QExtMvvmSessionItem> m_root_item;
    SessionModelImpl(QExtMvvmSessionModel* self, std::string modelType, std::shared_ptr<QExtMvvmItemPool> pool)
        : m_self(self)
        , m_modelType(std::move(modelType))
        , m_itemManager(qextMakeUnique<QExtMvvmItemManager>())
        , m_commands(qextMakeUnique<QExtMvvmCommandService>(self))
        , m_mapper(qextMakeUnique<QExtMvvmModelMapper>(self))
    {
        setItemPool(pool);
    }

    void setItemPool(std::shared_ptr<QExtMvvmItemPool> pool)
    {
        m_itemManager->setItemPool(pool ? std::move(pool) : std::make_shared<QExtMvvmItemPool>());
    }

    //! Creates root item.
    void createRootItem()
    {
        m_root_item = m_itemManager->createRootItem();
        m_root_item->setModel(m_self);
        m_root_item->registerTag(QExtMvvmTagInfo::universalTag("rootTag"), /*set_as_default*/ true);
    }
};

//! Main c-tor.

QExtMvvmSessionModel::QExtMvvmSessionModel(std::string QExtMvvmModelType, std::shared_ptr<QExtMvvmItemPool> pool)
    : p_impl(qextMakeUnique<SessionModelImpl>(this, std::move(QExtMvvmModelType), std::move(pool)))

{
    p_impl->createRootItem();
}

QExtMvvmSessionModel::~QExtMvvmSessionModel()
{
    // Explicitely call root item's destructor. It uses p_impl pointer during own descruction
    // and we have to keep pimpl pointer intact. Without line below will crash on MacOS because
    // of pecularities of MacOS libc++. See explanations here:
    // http://ibob.github.io/blog/2019/11/07/dont-use-unique_ptr-for-pimpl/
    p_impl->m_root_item.reset();

    p_impl->m_mapper->callOnModelDestroyed();
}

//! Insert new item using item's modelType.

QExtMvvmSessionItem* QExtMvvmSessionModel::insertNewItem(const QExtMvvmModelType& modelType, QExtMvvmSessionItem* parent,
                                         const QExtMvvmTagRow& tagrow)
{
    // intentionally passing by value inside lambda
    auto create_func = [this, modelType]() { return factory()->createItem(modelType); };
    return intern_insert(create_func, parent, tagrow);
}

//! Removes given row from parent.

void QExtMvvmSessionModel::removeItem(QExtMvvmSessionItem* parent, const QExtMvvmTagRow& tagrow)
{
    p_impl->m_commands->removeItem(parent, tagrow);
}

//! Move item from it's current parent to a new parent under given tag and row.
//! Old and new parents should belong to this model.

void QExtMvvmSessionModel::moveItem(QExtMvvmSessionItem* item, QExtMvvmSessionItem* new_parent, const QExtMvvmTagRow& tagrow)
{
    p_impl->m_commands->moveItem(item, new_parent, tagrow);
}

//! Copy item and insert it in parent's tag and row. Item could belong to any model/parent.

QExtMvvmSessionItem* QExtMvvmSessionModel::copyItem(const QExtMvvmSessionItem* item, QExtMvvmSessionItem* parent,
                                    const QExtMvvmTagRow& tagrow)
{
    return p_impl->m_commands->copyItem(item, parent, tagrow);
}

//! Returns the data for given item and role.

QVariant QExtMvvmSessionModel::data(QExtMvvmSessionItem* item, int role) const
{
    return item->data<QVariant>(role);
}

//! Sets the data for given item.

bool QExtMvvmSessionModel::setData(QExtMvvmSessionItem* item, const QVariant& value, int role)
{
    return p_impl->m_commands->setData(item, value, role);
}

//! Returns model type.

std::string QExtMvvmSessionModel::modelType() const
{
    return p_impl->m_modelType;
}

//! Returns root item of the model.

QExtMvvmSessionItem* QExtMvvmSessionModel::rootItem() const
{
    return p_impl->m_root_item.get();
}

//! Returns model mapper. Can be used to subscribe to various model's signal.

QExtMvvmModelMapper* QExtMvvmSessionModel::mapper()
{
    return p_impl->m_mapper.get();
}

//! Returns command stack to perform undo/redo.

QExtMvvmUndoStackInterface* QExtMvvmSessionModel::undoStack() const
{
    return p_impl->m_commands->undoStack();
}

//! Returns item factory which can generate all items supported by this model.

const QExtMvvmItemFactoryInterface* QExtMvvmSessionModel::factory() const
{
    return p_impl->m_itemManager->factory();
}

//! Returns QExtMvvmSessionItem for given identifier.

QExtMvvmSessionItem* QExtMvvmSessionModel::findItem(const QExtMvvmIdentifierType& id)
{
    return p_impl->m_itemManager->findItem(id);
}

//! Sets brand new catalog of user-defined items. They become available for undo/redo and
//! serialization. Internally user catalog will be merged with the catalog of standard items.

void QExtMvvmSessionModel::setItemCatalogue(QExtUniquePointer<QExtMvvmItemCatalogue> catalogue)
{
    // adding standard items to the user catalogue
    QExtUniquePointer<QExtMvvmItemCatalogue> full_catalogue = std::move(catalogue);
    full_catalogue->merge(*qextMvvmCreateStandardItemCatalogue());
    p_impl->m_itemManager->setItemFactory(qextMakeUnique<QExtMvvmItemFactory>(std::move(full_catalogue)));
}

//! Sets undo/redo either enabled or disabled. By default undo/redo is disabled.

void QExtMvvmSessionModel::setUndoRedoEnabled(bool value)
{
    p_impl->m_commands->setUndoRedoEnabled(value);
}

//! Removes all items from the model. If callback is provided, use it to rebuild content of root
//! item (used while restoring the model from serialized content).

void QExtMvvmSessionModel::clear(std::function<void(QExtMvvmSessionItem*)> callback)
{
    if (undoStack())
        undoStack()->clear();
    mapper()->callOnModelAboutToBeReset();
    p_impl->createRootItem();
    if (callback)
        callback(rootItem());
    mapper()->callOnModelReset();
}

//! Registers item in pool. This will allow to find item pointer using its unique identifier.

void QExtMvvmSessionModel::registerInPool(QExtMvvmSessionItem* item)
{
    p_impl->m_itemManager->registerInPool(item);
    item->activate(); // activates buisiness logic
}

//! Unregister item from pool.

void QExtMvvmSessionModel::unregisterFromPool(QExtMvvmSessionItem* item)
{
    p_impl->m_itemManager->unregisterFromPool(item);
}

//! Insert new item into given parent using factory function provided.

QExtMvvmSessionItem* QExtMvvmSessionModel::intern_insert(const QExtMvvmItemFactoryFunc& func, QExtMvvmSessionItem* parent,
                                         const QExtMvvmTagRow& tagrow)
{
    return p_impl->m_commands->insertNewItem(func, parent, tagrow);
}

void QExtMvvmSessionModel::intern_register(const QExtMvvmModelType& modelType, const QExtMvvmItemFactoryFunc& func,
                                   const std::string& label)
{
    p_impl->m_itemManager->factory()->registerItem(modelType, func, label);
}
