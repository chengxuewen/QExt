#ifndef QEXTMVVMITEM_P_H
#define QEXTMVVMITEM_P_H

#include <qextmvvmglobal.h>

#include <qextobject_p.h>

#include <QScopedPointer>
#include <QVariant>



class QEXTMvvmItemData;
class QEXTMvvmItemMapper;
class QEXTMvvmItem;
class QEXT_MVVM_API QEXTMvvmItemPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTMvvmItemPrivate(QEXTMvvmItem *qq);
    ~QEXTMvvmItemPrivate();

    bool setData(const QVariant &variant, int role);

    QEXTMvvmItem *m_this_item;
    QEXTMvvmItem *m_parent;
    QEXTMvvmItem *m_model;
    QScopedPointer<QEXTMvvmItemMapper> m_mapper;
    QScopedPointer<QEXTMvvmItemData> m_data;
    QScopedPointer<QEXTMvvmItemTags> m_tags;
    QString m_modelType;

private:
    QEXT_DECLARE_PUBLIC(QEXTMvvmItem)
    QEXT_DISABLE_COPY_MOVE(QEXTMvvmItemPrivate)
};



#endif // QEXTMVVMITEM_P_H
