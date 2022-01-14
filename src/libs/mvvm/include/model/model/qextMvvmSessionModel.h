#ifndef _QEXTMVVMMODELSESSIONMODEL_H
#define _QEXTMVVMMODELSESSIONMODEL_H

#include <qextMvvmTypes.h>
#include <qextMvvmFunctionTypes.h>
#include <qextMvvmPath.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmTagRow.h>
#include <qextMvvmGlobal.h>

#include <memory>

namespace ModelView
{

class QEXTMvvmSessionItem;
class ItemManager;
class QEXTMvvmCommandService;
class QEXTMvvmModelMapper;
class QEXTMvvmItemCatalogue;
class QEXTMvvmItemPool;
class QEXTMvvmItemFactoryInterface;
class QEXTMvvmUndoStackInterface;

class QEXT_MVVM_API QEXTMvvmSessionModel
{
public:
    explicit QEXTMvvmSessionModel(std::string model_type = {}, std::shared_ptr<QEXTMvvmItemPool> pool = {});

    virtual ~QEXTMvvmSessionModel();

    void setItemCatalogue(std::unique_ptr<QEXTMvvmItemCatalogue> catalogue);

    std::string modelType() const;

    QEXTMvvmSessionItem* insertNewItem(const model_type& modelType, QEXTMvvmSessionItem* parent = nullptr,
                               const QEXTMvvmTagRow& tagrow = {});

    template <typename T> T* insertItem(QEXTMvvmSessionItem* parent = nullptr, const QEXTMvvmTagRow& tagrow = {});

    QEXTMvvmSessionItem* copyItem(const QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* parent, const QEXTMvvmTagRow& tagrow = {});

    QEXTMvvmSessionItem* rootItem() const;

    QVariant data(QEXTMvvmSessionItem* item, int role) const;

    bool setData(QEXTMvvmSessionItem* item, const QVariant& value, int role);

    QEXTMvvmPath pathFromItem(const QEXTMvvmSessionItem* item) const;
    QEXTMvvmSessionItem* itemFromPath(const QEXTMvvmPath& path) const;

    void setUndoRedoEnabled(bool value);

    QEXTMvvmUndoStackInterface* undoStack() const;

    void removeItem(QEXTMvvmSessionItem* parent, const QEXTMvvmTagRow& tagrow);

    void moveItem(QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* new_parent, const QEXTMvvmTagRow& tagrow);

    void register_item(QEXTMvvmSessionItem* item);
    void unregister_item(QEXTMvvmSessionItem* item);

    QEXTMvvmModelMapper* mapper();

    void clear(std::function<void(QEXTMvvmSessionItem*)> callback = {});

    const QEXTMvvmItemFactoryInterface* factory() const;

    QEXTMvvmSessionItem* findItem(const identifier_type& id);

    template <typename T = QEXTMvvmSessionItem> std::vector<T*> topItems() const;

    template <typename T = QEXTMvvmSessionItem> T* topItem() const;

private:
    void createRootItem();
    QEXTMvvmSessionItem* intern_insert(const item_factory_func_t& func, QEXTMvvmSessionItem* parent,
                               const QEXTMvvmTagRow& tagrow);

    std::string m_model_type;
    std::unique_ptr<ItemManager> m_item_manager;
    std::unique_ptr<QEXTMvvmCommandService> m_commands;
    std::unique_ptr<QEXTMvvmModelMapper> m_mapper;
    std::unique_ptr<QEXTMvvmSessionItem> m_root_item;
};

template <typename T> T* QEXTMvvmSessionModel::insertItem(QEXTMvvmSessionItem* parent, const QEXTMvvmTagRow& tagrow)
{
    return static_cast<T*>(intern_insert([]() { return make_unique<T>(); }, parent, tagrow));
}

//! Returns top item of the given type. If more than one item exists, return the first one.
//! The top item is an item that is a child of an invisible root item.

template <typename T> std::vector<T*> QEXTMvvmSessionModel::topItems() const
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

template <typename T> T* QEXTMvvmSessionModel::topItem() const
{
    auto items = topItems<T>();
    return items.empty() ? nullptr : items.front();
}

} // namespace ModelView

#endif // _QEXTMVVMMODELSESSIONMODEL_H
