#ifndef _QEXTMVVMITEMLISTENERINTERFACE_H
#define _QEXTMVVMITEMLISTENERINTERFACE_H

#include <qextMvvmGlobal.h>
#include <qextMvvmFunctionTypes.h>

class QEXTMvvmItem;
class QEXTMvvmModel;
class QEXTMvvmTagRow;

//! Interface to subscribe to various events happening with specific QEXTMvvmItem.

class QEXT_MVVM_API QEXTMvvmItemListenerInterface
{
public:
    virtual ~QEXTMvvmItemListenerInterface() { }

    virtual QEXTConnection addItemAboutToBeInsertedListener(QEXTMvvmItemTagRowFunction function, void *listener = QEXT_DECL_NULLPTR) = 0;
    virtual QEXTConnection addItemInsertedListener(QEXTMvvmItemTagRowFunction function, void *listener = QEXT_DECL_NULLPTR) = 0;

    virtual QEXTConnection addItemAboutToBeRemovedListener(QEXTMvvmItemTagRowFunction function, void *listener = QEXT_DECL_NULLPTR) = 0;
    virtual QEXTConnection addItemRemovedListener(QEXTMvvmItemTagRowFunction function, void *listener = QEXT_DECL_NULLPTR) = 0;

    virtual QEXTConnection addItemDataAboutToBeChangedListener(QEXTMvvmItemRoleFunction function, void *listener = QEXT_DECL_NULLPTR) = 0;
    virtual QEXTConnection addItemDataChangedListener(QEXTMvvmItemRoleFunction function, void *listener = QEXT_DECL_NULLPTR) = 0;

    virtual QEXTConnection addItemAboutToBeDestroyedListener(QEXTMvvmItemFunction function, void *listener = QEXT_DECL_NULLPTR) = 0;
    virtual QEXTConnection addItemDestroyedListener(QEXTMvvmItemFunction function, void *listener = QEXT_DECL_NULLPTR) = 0;

    virtual QEXTConnection addItemPropertyAboutToBeChangedListener(QEXTMvvmItemPropertyFunction function, void *listener = QEXT_DECL_NULLPTR) = 0;
    virtual QEXTConnection addItemPropertyChangedListener(QEXTMvvmItemPropertyFunction function, void *listener = QEXT_DECL_NULLPTR) = 0;

    virtual QEXTConnection addItemChildPropertyAboutToBeChangedListener(QEXTMvvmItemPropertyFunction function, void *listener = QEXT_DECL_NULLPTR) = 0;
    virtual QEXTConnection addItemChildPropertyChangedListener(QEXTMvvmItemPropertyFunction function, void *listener = QEXT_DECL_NULLPTR) = 0;

    virtual void removeListener(void *listener = QEXT_DECL_NULLPTR) = 0;
};


#endif // _QEXTMVVMITEMLISTENERINTERFACE_H
