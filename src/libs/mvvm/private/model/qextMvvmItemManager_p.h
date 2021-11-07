#ifndef _QEXTMVVMITEMMANAGER_P_H
#define _QEXTMVVMITEMMANAGER_P_H

#include <qextMvvmGlobal.h>
#include <qextMvvmItemPool.h>
#include <qextMvvmItemFactoryInterface.h>

#include <QSharedPointer>
#include <QScopedPointer>

class QEXTMvvmItemManager;
class QEXT_MVVM_API QEXTMvvmItemManagerPrivate
{
public:
    explicit QEXTMvvmItemManagerPrivate(QEXTMvvmItemManager *q);
    virtual ~QEXTMvvmItemManagerPrivate();

    QEXTMvvmItemManager * const q_ptr;

    QSharedPointer<QEXTMvvmItemPool> m_itemPool;
    QScopedPointer<QEXTMvvmItemFactoryInterface> m_itemFactory;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmItemManagerPrivate)
    QEXT_DECL_PUBLIC(QEXTMvvmItemManager)
};

#endif // _QEXTMVVMITEMMANAGER_P_H
