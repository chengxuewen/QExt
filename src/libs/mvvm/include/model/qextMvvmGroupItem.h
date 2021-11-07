#ifndef _QEXTMVVMGROUPITEM_H
#define _QEXTMVVMGROUPITEM_H

#include <qextMvvmItemCatalogue.h>
#include <qextMvvmItem.h>

#include <QScopedPointer>

//! Group item holds collection of predefined items.

class QEXT_MVVM_API QEXTMvvmGroupItem : public QEXTMvvmItem
{
public:
    static inline const QString T_GROUP_ITEMS = "T_GROUP_ITEMS";

    QEXTMvvmGroupItem(QString modelType = QEXTMvvmConstants::GroupItemType);
    ~QEXTMvvmGroupItem() QEXT_DECL_OVERRIDE;

    int currentIndex() const;

    const QEXTMvvmItem *currentItem() const;
    QEXTMvvmItem *currentItem();

    QString currentType() const;
    void setCurrentType(const QString &modelType);

protected:
    void setCurrentIndex(int index);
    bool isValidIndex() const;
    template <typename T> void registerItem(const QString& text, bool make_selected = false);
    // FIXME how to make sure that init_group() was called in constructor?
    // Shell we delegate this call to QEXTMvvmCompoundItem::addProperty ?
    void initGroup();
    QScopedPointer<QEXTMvvmItemCatalogue> m_catalogue;
    int m_defaultSelectedIndex;
};

template <typename T> void QEXTMvvmGroupItem::registerItem(const QString& text, bool make_selected)
{
    m_catalogue->registerItem<T>(text);
    if (make_selected)
        m_defaultSelectedIndex = m_catalogue->itemCount() - 1;
}


#endif // _QEXTMVVMGROUPITEM_H
