#ifndef _QEXTMVVMITEM_P_H
#define _QEXTMVVMITEM_P_H

#include <qextMvvmGlobal.h>
#include <qextMvvmTypes.h>
#include <qextMvvmModel.h>
#include <qextMvvmItemTags.h>

#include <QScopedPointer>

class QEXTMvvmItem;
class QEXT_MVVM_API QEXTMvvmItemPrivate
{
public:
    explicit QEXTMvvmItemPrivate(QEXTMvvmItem *q);
    virtual ~QEXTMvvmItemPrivate();

    bool setData(const QVariant &variant, int role);
    int appearance() const;

    QEXTMvvmItem * const q_ptr;

    QEXTMvvmItem *m_parent;
    QEXTMvvmModel *m_model;
    QString m_modelType;
    QScopedPointer<QEXTMvvmItemMapper> m_mapper;
    QScopedPointer<QEXTMvvmItemData> m_data;
    QScopedPointer<QEXTMvvmItemTags> m_tags;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmItemPrivate)
    QEXT_DECL_PUBLIC(QEXTMvvmItem)
};

#endif // _QEXTMVVMITEM_P_H
