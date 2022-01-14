// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <commands/qextMvvmCommandService.h>
#include <qextMvvmItemCatalogueFactory.h>
#include <qextMvvmCustomVariants.h>
#include <qextMvvmItemCatalogue.h>
#include <qextMvvmItemFactory.h>
#include <qextMvvmItemManager.h>
#include <qextMvvmItemPool.h>
#include <qextMvvmItemUtils.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>
#include <qextMvvmTagInfo.h>
#include <qextMvvmTagRow.h>
#include <qextMvvmModelMapper.h>

using namespace ModelView;

QEXTMvvmSessionModel::QEXTMvvmSessionModel(std::string model_type, std::shared_ptr<QEXTMvvmItemPool> pool)
    : m_model_type(std::move(model_type))
    , m_item_manager(make_unique<ItemManager>())
    , m_commands(make_unique<QEXTMvvmCommandService>(this))
    , m_mapper(make_unique<QEXTMvvmModelMapper>(this))
{
    if (pool)
        m_item_manager->setItemPool(std::move(pool));
    else
        m_item_manager->setItemPool(std::make_shared<QEXTMvvmItemPool>());
    createRootItem();
}

QEXTMvvmSessionModel::~QEXTMvvmSessionModel()
{
    m_mapper->callOnModelDestroyed();
}

void QEXTMvvmSessionModel::setItemCatalogue(std::unique_ptr<QEXTMvvmItemCatalogue> catalogue)
{
    // adding standard items to the user catalogue
    std::unique_ptr<QEXTMvvmItemCatalogue> full_catalogue = std::move(catalogue);
    full_catalogue->merge(*CreateStandardItemCatalogue());
    m_item_manager->setItemFactory(make_unique<QEXTMvvmItemFactory>(std::move(full_catalogue)));
}

std::string QEXTMvvmSessionModel::modelType() const
{
    return m_model_type;
}

QEXTMvvmSessionItem* QEXTMvvmSessionModel::insertNewItem(const model_type& modelType, QEXTMvvmSessionItem* parent,
                                         const QEXTMvvmTagRow& tagrow)
{
    // intentionally passing by value inside lambda
    auto create_func = [this, modelType]() { return factory()->createItem(modelType); };
    return intern_insert(create_func, parent, tagrow);
}

//! Copy item and insert it in parent's tag and row.
//! Item could belong to any model/parent.

QEXTMvvmSessionItem* QEXTMvvmSessionModel::copyItem(const QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* parent,
                                    const QEXTMvvmTagRow& tagrow)
{
    return m_commands->copyItem(item, parent, tagrow);
}

QEXTMvvmSessionItem* QEXTMvvmSessionModel::rootItem() const
{
    return m_root_item.get();
}

QVariant QEXTMvvmSessionModel::data(QEXTMvvmSessionItem* item, int role) const
{
    return item->data<QVariant>(role);
}

bool QEXTMvvmSessionModel::setData(QEXTMvvmSessionItem* item, const QVariant& value, int role)
{
    return m_commands->setData(item, value, role);
}

//! Returns path from item.

QEXTMvvmPath QEXTMvvmSessionModel::pathFromItem(const QEXTMvvmSessionItem* item) const
{
    QEXTMvvmPath result;
    const QEXTMvvmSessionItem* current(item);
    while (current && current->parent()) {
        result.prepend(QEXTMvvmUtils::IndexOfChild(current->parent(), current));
        current = current->parent();
    }
    return result;
}

//! Returns item from path.

QEXTMvvmSessionItem* QEXTMvvmSessionModel::itemFromPath(const QEXTMvvmPath& path) const
{
    QEXTMvvmSessionItem* result(rootItem());
    for (const auto& x : path) {
        result = QEXTMvvmUtils::ChildAt(result, x);
        if (!result)
            break;
    }
    return result;
}

void QEXTMvvmSessionModel::setUndoRedoEnabled(bool value)
{
    m_commands->setUndoRedoEnabled(value);
}

QEXTMvvmUndoStackInterface* QEXTMvvmSessionModel::undoStack() const
{
    return m_commands->undoStack();
}

//! Removes given row from parent.

void QEXTMvvmSessionModel::removeItem(QEXTMvvmSessionItem* parent, const QEXTMvvmTagRow& tagrow)
{
    m_commands->removeItem(parent, tagrow);
}

//! Move item from it's current parent to a new parent under given tag and row.
//! Old and new parents should belong to this model.

void QEXTMvvmSessionModel::moveItem(QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* new_parent, const QEXTMvvmTagRow& tagrow)
{
    m_commands->moveItem(item, new_parent, tagrow);
}

void QEXTMvvmSessionModel::register_item(QEXTMvvmSessionItem* item)
{
    m_item_manager->register_item(item);
    item->activate(); // activates buisiness logic
}

void QEXTMvvmSessionModel::unregister_item(QEXTMvvmSessionItem* item)
{
    m_item_manager->unregister_item(item);
}

QEXTMvvmModelMapper* QEXTMvvmSessionModel::mapper()
{
    return m_mapper.get();
}

//! Removes all items from the model. If callback is provided, use it to rebuild content of root
//! item. Used while restoring the model from serialized content.

void QEXTMvvmSessionModel::clear(std::function<void(QEXTMvvmSessionItem*)> callback)
{
    mapper()->callOnModelAboutToBeReset();
    createRootItem();
    if (callback)
        callback(rootItem());
    mapper()->callOnModelReset();
}

//! Returns pointer to ItemFactory which can generate all items supported by this model,

const QEXTMvvmItemFactoryInterface* QEXTMvvmSessionModel::factory() const
{
    return m_item_manager->factory();
}

//! Returns QEXTMvvmSessionItem for given identifier.

QEXTMvvmSessionItem* QEXTMvvmSessionModel::findItem(const identifier_type& id)
{
    return m_item_manager->findItem(id);
}

//! Creates root item.

void QEXTMvvmSessionModel::createRootItem()
{
    m_root_item = m_item_manager->createRootItem();
    m_root_item->setModel(this);
    m_root_item->registerTag(QEXTMvvmTagInfo::universalTag("rootTag"), /*set_as_default*/ true);
}

QEXTMvvmSessionItem* QEXTMvvmSessionModel::intern_insert(const item_factory_func_t& func, QEXTMvvmSessionItem* parent,
                                         const QEXTMvvmTagRow& tagrow)
{
    return m_commands->insertNewItem(func, parent, tagrow);
}
