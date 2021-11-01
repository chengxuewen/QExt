#ifndef _QEXTMVVMGROUPITEM_H
#define _QEXTMVVMGROUPITEM_H

#include <memory>
#include <qextMvvmItemCatalogue.h>
#include <qextMvvmSessionItem.h>

namespace ModelView
{

//! Group item holds collection of predefined items.

class QEXT_MVVM_API QEXTMvvmGroupItem : public QEXTMvvmSessionItem
{
public:
    static inline const std::string T_GROUP_ITEMS = "T_GROUP_ITEMS";

    QEXTMvvmGroupItem(QEXTMvvmModelType modelType = Constants::GroupItemType);
    ~QEXTMvvmGroupItem() override;

    int currentIndex() const;

    const QEXTMvvmSessionItem* currentItem() const;
    QEXTMvvmSessionItem* currentItem();

    std::string currentType() const;
    void setCurrentType(const std::string& QEXTMvvmModelType);

protected:
    void setCurrentIndex(int index);
    bool is_valid_index() const;
    template <typename T> void registerItem(const std::string& text, bool make_selected = false);
    // FIXME how to make sure that init_group() was called in constructor?
    // Shell we delegate this call to QEXTMvvmCompoundItem::addProperty ?
    void init_group();
    std::unique_ptr<QEXTMvvmItemCatalogue> m_catalogue;
    int m_default_selected_index;
};

template <typename T> void QEXTMvvmGroupItem::registerItem(const std::string& text, bool make_selected)
{
    m_catalogue->registerItem<T>(text);
    if (make_selected)
        m_default_selected_index = m_catalogue->itemCount() - 1;
}

} // namespace ModelView

#endif // _QEXTMVVMGROUPITEM_H
