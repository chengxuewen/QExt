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

#include "model/model/sessionitem.h"
#include <vector>

namespace ModelView {

//! Group item holds collection of predefined items.
//! Intended for the inheritance.

class QEXT_MVVM_API QExtMvvmGroupItem : public QExtMvvmSessionItem {
public:
    static inline const std::string T_GROUP_ITEMS = "T_GROUP_ITEMS";

    ~QExtMvvmGroupItem() override;

    int currentIndex() const;

    const QExtMvvmSessionItem* currentItem() const;
    QExtMvvmSessionItem* currentItem();

    std::string currentType() const;
    void setCurrentType(const std::string& QExtMvvmModelType);

protected:
    QExtMvvmGroupItem(QExtMvvmModelType modelType);
    void setCurrentIndex(int index);
    template <typename T> void addToGroup(const std::string& text = {}, bool make_selected = false);
    void updateCombo();

    int m_index_to_select;
    std::vector<std::string> m_item_text;
};

//! Adds an item of a given type to the group.
//! @param 'text' defines a text to be shown in ComboEditor when selecting an item in a group.
//! @param make_selected defines whether the item should be selected by default.
template <typename T> void QExtMvvmGroupItem::addToGroup(const std::string& text, bool make_selected)
{
    m_item_text.push_back(text.empty() ? T().modelType() : text);
    insertItem<T>(QExtMvvmTagRow::append(T_GROUP_ITEMS));
    if (make_selected)
        m_index_to_select = m_item_text.size() - 1;
    updateCombo();
}

} // namespace ModelView

#endif // MVVM_MODEL_GROUPITEM_H
