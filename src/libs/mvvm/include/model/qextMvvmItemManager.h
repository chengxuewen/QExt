#ifndef _QEXTMVVMITEMMANAGER_H
#define _QEXTMVVMITEMMANAGER_H

#include <memory>
#include <qextMvvmTypes.h>
#include <qextMvvmGlobal.h>

#include <QSharedPointer>

class QEXTMvvmItem;
class QEXTMvvmItemPool;
class QEXTMvvmItemFactoryInterface;

//! Manages item creation/registration for QEXTMvvmModel.
class QEXTMvvmItemManagerPrivate;
class QEXT_MVVM_API QEXTMvvmItemManager
{
public:
    QEXTMvvmItemManager();
    ~QEXTMvvmItemManager();

    void setItemFactory(QEXTMvvmItemFactoryInterface *factory);
    void setItemPool(const QSharedPointer<QEXTMvvmItemPool> &pool);

    QEXTMvvmItem *createItem(const QString &modelType = QString()) const;
    QEXTMvvmItem *createRootItem() const;

    QEXTMvvmItem *findItem(const QString &id) const;
    QString findIdentifier(QEXTMvvmItem *item) const;

    const QEXTMvvmItemPool *itemPool() const;
    QEXTMvvmItemPool *itemPool();

    void registerItem(QEXTMvvmItem *item);
    void unregisterItem(QEXTMvvmItem *item);

    const QEXTMvvmItemFactoryInterface *factory() const;

protected:
    QScopedPointer<QEXTMvvmItemManagerPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmItemManager)
    Q_DECLARE_PRIVATE(QEXTMvvmItemManager)
};

#endif // _QEXTMVVMITEMMANAGER_H
