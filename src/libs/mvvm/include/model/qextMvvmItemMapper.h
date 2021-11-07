#ifndef _QEXTMVVMITEMMAPPER_H
#define _QEXTMVVMITEMMAPPER_H

#include <qextMvvmItemListenerInterface.h>
#include <qextMvvmModelListener.h>

#include <QScopedPointer>

class QEXTMvvmItem;

//! Provides notifications on various changes for a specific item.
//! QEXTMvvmItemMapper listens signals coming from the model (i.e. via QEXTMvvmModelMapper) and processes only whose
//! signals which are related to the given item. Notifies all interested subscribers about things
//! going with the item and its relatives.
class QEXTMvvmItemMapperPrivate;
class QEXT_MVVM_API QEXTMvvmItemMapper : public QEXTMvvmItemListenerInterface
{
public:
    QEXTMvvmItemMapper(QEXTMvvmItem *item);
    ~QEXTMvvmItemMapper();

    QEXTConnection addItemAboutToBeInsertedListener(QEXTMvvmItemTagRowFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;
    QEXTConnection addItemInsertedListener(QEXTMvvmItemTagRowFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;

    QEXTConnection addItemAboutToBeRemovedListener(QEXTMvvmItemTagRowFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;
    QEXTConnection addItemRemovedListener(QEXTMvvmItemTagRowFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;

    QEXTConnection addItemDataAboutToBeChangedListener(QEXTMvvmItemRoleFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;
    QEXTConnection addItemDataChangedListener(QEXTMvvmItemRoleFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;

    QEXTConnection addItemAboutToBeDestroyedListener(QEXTMvvmItemFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;
    QEXTConnection addItemDestroyedListener(QEXTMvvmItemFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;

    QEXTConnection addItemPropertyAboutToBeChangedListener(QEXTMvvmItemPropertyFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;
    QEXTConnection addItemPropertyChangedListener(QEXTMvvmItemPropertyFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;

    QEXTConnection addItemChildPropertyAboutToBeChangedListener(QEXTMvvmItemPropertyFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;
    QEXTConnection addItemChildPropertyChangedListener(QEXTMvvmItemPropertyFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;

    void removeListener(void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;

    void setActive(bool value);

protected:
    void callOnItemDestroy();

    QScopedPointer<QEXTMvvmItemMapperPrivate> d_ptr;

private:
    friend class QEXTMvvmItem;
    friend class QEXTMvvmItemPrivate;
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmItemMapper)
    QEXT_DECL_PRIVATE(QEXTMvvmItemMapper)
};

#endif // _QEXTMVVMITEMMAPPER_H
