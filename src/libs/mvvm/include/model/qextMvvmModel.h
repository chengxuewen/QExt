#ifndef _QEXTMVVMMODEL_H
#define _QEXTMVVMMODEL_H

#include <qextMvvmGlobal.h>
#include <qextMvvmTypes.h>
#include <qextMvvmPath.h>
#include <qextMvvmItem.h>
#include <qextMvvmTagRow.h>
#include <qextMvvmFunctionTypes.h>

class QEXTMvvmItem;
class QEXTMvvmItemManager;
class QEXTMvvmCommandService;
class QEXTMvvmModelMapper;
class QEXTMvvmItemCatalogue;
class QEXTMvvmItemPool;
class QEXTMvvmItemFactoryInterface;
class QEXTMvvmUndoStackInterface;

class QEXTMvvmModelPrivate;
class QEXT_MVVM_API QEXTMvvmModel
{
public:
    explicit QEXTMvvmModel(const QString &modelType = QString(),
                           const QSharedPointer<QEXTMvvmItemPool> &pool = QSharedPointer<QEXTMvvmItemPool>());

    virtual ~QEXTMvvmModel();

    void setItemCatalogue(QEXTMvvmItemCatalogue *catalogue);

    QString modelType() const;

    QEXTMvvmItem *insertNewItem(const QString &modelType,
                                QEXTMvvmItem *parent = QEXT_DECL_NULLPTR,
                                const QEXTMvvmTagRow &tagrow = QEXTMvvmTagRow());
    template <typename T> T *insertItem(QEXTMvvmItem *parent = QEXT_DECL_NULLPTR,
                                        const QEXTMvvmTagRow &tagrow = QEXTMvvmTagRow());
    QEXTMvvmItem *copyItem(QEXTMvvmItem *item, QEXTMvvmItem *parent,
                           const QEXTMvvmTagRow &tagrow = QEXTMvvmTagRow());
    QEXTMvvmItem *rootItem() const;

    QVariant data(QEXTMvvmItem *item, int role) const;
    bool setData(QEXTMvvmItem *item, const QVariant &value, int role);

    QEXTMvvmPath pathFromItem(QEXTMvvmItem *item) const;
    QEXTMvvmItem *itemFromPath(const QEXTMvvmPath &path) const;

    void setUndoRedoEnabled(bool value);

    QEXTMvvmUndoStackInterface *undoStack() const;

    void removeItem(QEXTMvvmItem *parent, const QEXTMvvmTagRow &tagrow);

    void moveItem(QEXTMvvmItem *item, QEXTMvvmItem *newParent, const QEXTMvvmTagRow &tagrow);

    void registerItem(QEXTMvvmItem *item);
    void unregisterItem(QEXTMvvmItem *item);

    QEXTMvvmModelMapper *mapper() const;

    void clear(QEXTMvvmItemFunction callback = QEXTMvvmItemFunction());

    const QEXTMvvmItemFactoryInterface* factory() const;

    QEXTMvvmItem *findItem(const QString &id);

    template <typename T = QEXTMvvmItem> QVector<T*> topItems() const;

    template <typename T = QEXTMvvmItem> T *topItem() const;

protected:
    void createRootItem();
    QEXTMvvmItem *internInsert(const QEXTMvvmItemFactoryFunction &func, QEXTMvvmItem *parent,
                               const QEXTMvvmTagRow &tagrow);

    QScopedPointer<QEXTMvvmModelPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmModel)
    QEXT_DECL_PRIVATE(QEXTMvvmModel)
};

template <typename T> T* QEXTMvvmModel::insertItem(QEXTMvvmItem *parent, const QEXTMvvmTagRow &tagrow)
{
    return static_cast<T*>(internInsert([]() { return new T; }, parent, tagrow));
}

//! Returns top item of the given type. If more than one item exists, return the first one.
//! The top item is an item that is a child of an invisible root item.

template <typename T> QVector<T*> QEXTMvvmModel::topItems() const
{
    QVector<T*> result;
    for (auto child : rootItem()->children()) {
        if (auto item = dynamic_cast<T*>(child))
            result.push_back(item);
    }

    return result;
}

//! Returns top items of the given type.
//! The top item is an item that is a child of an invisible root item.

template <typename T> T* QEXTMvvmModel::topItem() const
{
    auto items = topItems<T>();
    return items.empty() ? nullptr : items.front();
}


#endif // _QEXTMVVMMODEL_H
