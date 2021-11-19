#ifndef _QEXTMVVMITEMPOOL_P_H
#define _QEXTMVVMITEMPOOL_P_H

#include <qextMvvmGlobal.h>
#include <qextMvvmItem.h>

#include <QMap>

class QEXTMvvmItemPool;
class QEXT_MVVM_API QEXTMvvmItemPoolPrivate
{
public:
    explicit QEXTMvvmItemPoolPrivate(QEXTMvvmItemPool *q);
    virtual ~QEXTMvvmItemPoolPrivate();

    QEXTMvvmItemPool * const q_ptr;

    QMap<QString, QEXTMvvmItem *> m_keyToItem;
    QMap<QEXTMvvmItem *, QString> m_itemToKey;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmItemPoolPrivate)
    Q_DECLARE_PUBLIC(QEXTMvvmItemPool)
};

#endif // _QEXTMVVMITEMPOOL_P_H
