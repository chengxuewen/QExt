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

#include <qextMvvmTypes.h>

#include <qextMvvmFunctionTypes.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmTagRow.h>
#include <qextMvvmGlobal.h>
#include <memory>

namespace ModelView {

class QExtMvvmSessionItem;
class QExtMvvmItemCatalogue;
class QExtMvvmItemPool;
class QExtMvvmModelMapper;
class QExtMvvmItemFactoryInterface;
class QExtMvvmUndoStackInterface;

//! Main class to hold hierarchy of QExtMvvmSessionItem objects.

class QEXT_MVVM_API QExtMvvmSessionModel {
public:
    explicit QExtMvvmSessionModel(std::string QExtMvvmModelType = {}, std::shared_ptr<QExtMvvmItemPool> pool = {});
    virtual ~QExtMvvmSessionModel();
    QExtMvvmSessionModel(const QExtMvvmSessionModel& other) = delete;
    QExtMvvmSessionModel& operator=(const QExtMvvmSessionModel& other) = delete;

    // Methods to manipulate data and items.

    QExtMvvmSessionItem* insertNewItem(const QExtMvvmModelType& modelType, QExtMvvmSessionItem* parent = nullptr,
                               const QExtMvvmTagRow& tagrow = {});

    template <typename T> T* insertItem(QExtMvvmSessionItem* parent = nullptr, const QExtMvvmTagRow& tagrow = {});

    void removeItem(QExtMvvmSessionItem* parent, const QExtMvvmTagRow& tagrow);

    void moveItem(QExtMvvmSessionItem* item, QExtMvvmSessionItem* new_parent, const QExtMvvmTagRow& tagrow);

    QExtMvvmSessionItem* copyItem(const QExtMvvmSessionItem* item, QExtMvvmSessionItem* parent, const QExtMvvmTagRow& tagrow = {});

    QVariant data(QExtMvvmSessionItem* item, int role) const;

    bool setData(QExtMvvmSessionItem* item, const QVariant& value, int role);

    // Various getters.

    std::string modelType() const;

    QExtMvvmSessionItem* rootItem() const;

    QExtMvvmModelMapper* mapper();

    QExtMvvmUndoStackInterface* undoStack() const;

    const QExtMvvmItemFactoryInterface* factory() const;

    QExtMvvmSessionItem* findItem(const QExtMvvmIdentifierType& id);

    template <typename T = QExtMvvmSessionItem> std::vector<T*> topItems() const;

    template <typename T = QExtMvvmSessionItem> T* topItem() const;

    // Methods to steer global behaviour.

    void setItemCatalogue(QExtUniquePointer<QExtMvvmItemCatalogue> catalogue);

    void setUndoRedoEnabled(bool value);

    void clear(std::function<void(QExtMvvmSessionItem*)> callback = {});

    template <typename T> void registerItem(const std::string& label = {});

private:
    friend class QExtMvvmSessionItem;
    void registerInPool(QExtMvvmSessionItem* item);
    void unregisterFromPool(QExtMvvmSessionItem* item);
    QExtMvvmSessionItem* intern_insert(const QExtMvvmItemFactoryFunc& func, QExtMvvmSessionItem* parent,
                               const QExtMvvmTagRow& tagrow);
    void intern_register(const QExtMvvmModelType& modelType, const QExtMvvmItemFactoryFunc& func,
                         const std::string& label);

    struct SessionModelImpl;
    QExtUniquePointer<SessionModelImpl> p_impl;
};

//! Inserts item into given parent under given tagrow.

template <typename T> T* QExtMvvmSessionModel::insertItem(QExtMvvmSessionItem* parent, const QExtMvvmTagRow& tagrow)
{
    return static_cast<T*>(intern_insert(qextMvvmItemFactoryFunction<T>(), parent, tagrow));
}

//! Returns top items of the given type.
//! The top item is an item that is a child of an invisible root item.

template <typename T> std::vector<T*> QExtMvvmSessionModel::topItems() const
{
    std::vector<T*> result;
    for (auto child : rootItem()->children()) {
        if (auto item = dynamic_cast<T*>(child))
            result.push_back(item);
    }

    return result;
}

//! Returns top item of the given type. If more than one item exists, return the first one.
//! The top item is an item that is a child of an invisible root item.

template <typename T> T* QExtMvvmSessionModel::topItem() const
{
    auto items = topItems<T>();
    return items.empty() ? nullptr : items.front();
}

//! Register used defined item to use with the model. It will become possible to undo/redo
//! operations with this item, as well as serialize it to/from JSON.

template <typename T> void QExtMvvmSessionModel::registerItem(const std::string& label)
{
    intern_register(T().modelType(), qextMvvmItemFactoryFunction<T>(), label);
}

} // namespace ModelView

#endif // MVVM_MODEL_SESSIONMODEL_H
