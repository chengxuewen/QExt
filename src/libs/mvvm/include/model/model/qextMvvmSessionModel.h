// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_SESSIONMODEL_H
#define MVVM_MODEL_SESSIONMODEL_H

#include <memory>
#include <qextMvvmTypes.h>
#include <qextMvvmVariant.h>
#include <qextMvvmFunctionTypes.h>
#include <qextMvvmPath.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmTagRow.h>
#include <qextMvvmGlobal.h>

namespace ModelView
{

class QEXTMvvmSessionItem;
class ItemManager;
class QEXTMvvmCommandService;
class ModelMapper;
class ItemCatalogue;
class ItemPool;
class ItemFactoryInterface;
class QEXTMvvmUndoStackInterface;

class QEXT_MVVM_API SessionModel
{
public:
    explicit SessionModel(std::string model_type = {}, std::shared_ptr<ItemPool> pool = {});

    virtual ~SessionModel();

    void setItemCatalogue(std::unique_ptr<ItemCatalogue> catalogue);

    std::string modelType() const;

    QEXTMvvmSessionItem* insertNewItem(const model_type& modelType, QEXTMvvmSessionItem* parent = nullptr,
                               const TagRow& tagrow = {});

    template <typename T> T* insertItem(QEXTMvvmSessionItem* parent = nullptr, const TagRow& tagrow = {});

    QEXTMvvmSessionItem* copyItem(const QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* parent, const TagRow& tagrow = {});

    QEXTMvvmSessionItem* rootItem() const;

    Variant data(QEXTMvvmSessionItem* item, int role) const;

    bool setData(QEXTMvvmSessionItem* item, const Variant& value, int role);

    Path pathFromItem(const QEXTMvvmSessionItem* item) const;
    QEXTMvvmSessionItem* itemFromPath(const Path& path) const;

    void setUndoRedoEnabled(bool value);

    QEXTMvvmUndoStackInterface* undoStack() const;

    void removeItem(QEXTMvvmSessionItem* parent, const TagRow& tagrow);

    void moveItem(QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* new_parent, const TagRow& tagrow);

    void register_item(QEXTMvvmSessionItem* item);
    void unregister_item(QEXTMvvmSessionItem* item);

    ModelMapper* mapper();

    void clear(std::function<void(QEXTMvvmSessionItem*)> callback = {});

    const ItemFactoryInterface* factory() const;

    QEXTMvvmSessionItem* findItem(const identifier_type& id);

    template <typename T = QEXTMvvmSessionItem> std::vector<T*> topItems() const;

    template <typename T = QEXTMvvmSessionItem> T* topItem() const;

private:
    void createRootItem();
    QEXTMvvmSessionItem* intern_insert(const item_factory_func_t& func, QEXTMvvmSessionItem* parent,
                               const TagRow& tagrow);

    std::string m_model_type;
    std::unique_ptr<ItemManager> m_item_manager;
    std::unique_ptr<QEXTMvvmCommandService> m_commands;
    std::unique_ptr<ModelMapper> m_mapper;
    std::unique_ptr<QEXTMvvmSessionItem> m_root_item;
};

template <typename T> T* SessionModel::insertItem(QEXTMvvmSessionItem* parent, const TagRow& tagrow)
{
    return static_cast<T*>(intern_insert([]() { return std::make_unique<T>(); }, parent, tagrow));
}

//! Returns top item of the given type. If more than one item exists, return the first one.
//! The top item is an item that is a child of an invisible root item.

template <typename T> std::vector<T*> SessionModel::topItems() const
{
    std::vector<T*> result;
    for (auto child : rootItem()->children()) {
        if (auto item = dynamic_cast<T*>(child))
            result.push_back(item);
    }

    return result;
}

//! Returns top items of the given type.
//! The top item is an item that is a child of an invisible root item.

template <typename T> T* SessionModel::topItem() const
{
    auto items = topItems<T>();
    return items.empty() ? nullptr : items.front();
}

} // namespace ModelView

#endif // MVVM_MODEL_SESSIONMODEL_H
