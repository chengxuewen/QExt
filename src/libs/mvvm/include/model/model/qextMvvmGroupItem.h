// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_GROUPITEM_H
#define MVVM_MODEL_GROUPITEM_H

#include <memory>
#include <qextMvvmItemCatalogue.h>
#include <qextMvvmSessionItem.h>

namespace ModelView
{

//! Group item holds collection of predefined items.

class QEXT_MVVM_API GroupItem : public QEXTMvvmSessionItem
{
public:
    static inline const std::string T_GROUP_ITEMS = "T_GROUP_ITEMS";

    GroupItem(model_type modelType = Constants::GroupItemType);
    ~GroupItem() override;

    int currentIndex() const;

    const QEXTMvvmSessionItem* currentItem() const;
    QEXTMvvmSessionItem* currentItem();

    std::string currentType() const;
    void setCurrentType(const std::string& model_type);

protected:
    void setCurrentIndex(int index);
    bool is_valid_index() const;
    template <typename T> void registerItem(const std::string& text, bool make_selected = false);
    // FIXME how to make sure that init_group() was called in constructor?
    // Shell we delegate this call to QEXTMvvmCompoundItem::addProperty ?
    void init_group();
    std::unique_ptr<ItemCatalogue> m_catalogue;
    int m_default_selected_index;
};

template <typename T> void GroupItem::registerItem(const std::string& text, bool make_selected)
{
    m_catalogue->registerItem<T>(text);
    if (make_selected)
        m_default_selected_index = m_catalogue->itemCount() - 1;
}

} // namespace ModelView

#endif // MVVM_MODEL_GROUPITEM_H
