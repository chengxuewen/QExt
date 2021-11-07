#ifndef _QEXTMVVMMODELMAPPER_H
#define _QEXTMVVMMODELMAPPER_H

#include <qextMvvmModelListenerInterface.h>

#include <QScopedPointer>

class QEXTMvvmItem;
class QEXTMvvmModel;

//! Provides notifications on various QEXTMvvmModel changes.
//! Allows to subscribe to QEXTMvvmModel's changes, and triggers notifications.

class QEXTMvvmModelMapperPrivate;
class QEXT_MVVM_API QEXTMvvmModelMapper : public QEXTMvvmModelListenerInterface
{
public:
    QEXTMvvmModelMapper(QEXTMvvmModel *model);
    ~QEXTMvvmModelMapper();

    QEXTConnection addItemAboutToBeInsertedListener(QEXTMvvmItemTagRowFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;
    QEXTConnection addItemInsertedListener(QEXTMvvmItemTagRowFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;

    QEXTConnection addItemAboutToBeRemovedListener(QEXTMvvmItemTagRowFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;
    QEXTConnection addItemRemovedListener(QEXTMvvmItemTagRowFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;

    QEXTConnection addItemDataAboutToBeChangedListener(QEXTMvvmItemRoleFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;
    QEXTConnection addItemDataChangedListener(QEXTMvvmItemRoleFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;

    QEXTConnection addItemAboutToBeDestroyedListener(QEXTMvvmItemFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;
    QEXTConnection addItemDestroyedListener(QEXTMvvmItemFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;

    QEXTConnection addModelAboutToBeDestroyedListener(QEXTMvvmModelFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;
    QEXTConnection addModelDestroyedListener(QEXTMvvmModelFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;

    QEXTConnection addModelAboutToBeResetedListener(QEXTMvvmModelFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;
    QEXTConnection addModelResetedListener(QEXTMvvmModelFunction function, void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;

    void removeListener(void *listener = QEXT_DECL_NULLPTR) QEXT_DECL_OVERRIDE;

    void setActive(bool value);

protected:
    friend class QEXTMvvmModel;
    friend class QEXTMvvmModelPrivate;
    friend class QEXTMvvmItem;
    friend class QEXTMvvmItemPrivate;

    void callOnDataChange(QEXTMvvmItem *item, int role);
    void callOnItemInserted(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);
    void callOnItemRemoved(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);
    void callOnItemAboutToBeRemoved(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow);
    void callOnModelDestroyed();
    void callOnModelAboutToBeReset();
    void callOnModelReset();

    QScopedPointer<QEXTMvvmModelMapperPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmModelMapper)
    QEXT_DECL_PRIVATE(QEXTMvvmModelMapper)
};

#endif // _QEXTMVVMMODELMAPPER_H
