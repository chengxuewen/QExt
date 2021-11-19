#ifndef _QEXTMVVMITEMPOOL_H
#define _QEXTMVVMITEMPOOL_H

#include <qextMvvmGlobal.h>
#include <qextMvvmTypes.h>

class QEXTMvvmItem;

//! Provides registration of QEXTMvvmItem pointers and their unique identifiers
//! in global memory pool.

class QEXTMvvmItemPoolPrivate;
class QEXT_MVVM_API QEXTMvvmItemPool
{
public:
    QEXTMvvmItemPool();
    virtual ~QEXTMvvmItemPool();

    int size() const;

    QString registerItem(QEXTMvvmItem *item, QString key = QString());
    void unregisterItem(QEXTMvvmItem *item);

    QString keyForItem(QEXTMvvmItem *item) const;
    QEXTMvvmItem *itemForKey(const QString &key) const;

protected:
    QScopedPointer<QEXTMvvmItemPoolPrivate> d_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmItemPool)
    Q_DECLARE_PRIVATE(QEXTMvvmItemPool)
};


#endif // _QEXTMVVMITEMPOOL_H
