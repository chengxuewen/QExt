// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_SESSIONITEMCONTAINER_H
#define MVVM_MODEL_SESSIONITEMCONTAINER_H

#include <qextMvvmTagInfo.h>
#include <qextMvvmGlobal.h>
#include <vector>

namespace ModelView {

class QExtMvvmSessionItem;

//! Holds collection of QExtMvvmSessionItem objects related to the same tag.

class QEXT_MVVM_API QExtMvvmSessionItemContainer {
public:
    using container_t = std::vector<QExtMvvmSessionItem*>;
    using const_iterator = container_t::const_iterator;

    QExtMvvmSessionItemContainer(QExtMvvmTagInfo tag_info);
    QExtMvvmSessionItemContainer(const QExtMvvmSessionItemContainer&) = delete;
    QExtMvvmSessionItemContainer& operator=(const QExtMvvmSessionItemContainer&) = delete;
    ~QExtMvvmSessionItemContainer();

    bool empty() const;

    int itemCount() const;

    std::vector<QExtMvvmSessionItem*> items() const;

    bool insertItem(QExtMvvmSessionItem* item, int index);

    QExtMvvmSessionItem* takeItem(int index);

    bool canTakeItem(int index) const;

    bool canInsertItem(const QExtMvvmSessionItem* item, int index) const;

    int indexOfItem(const QExtMvvmSessionItem* item) const;

    QExtMvvmSessionItem* itemAt(int index) const;

    std::string name() const;

    QExtMvvmTagInfo tagInfo() const;

    const_iterator begin() const;

    const_iterator end() const;

private:
    bool maximum_reached() const;
    bool minimum_reached() const;
    bool is_valid_item(const QExtMvvmSessionItem* item) const;
    QExtMvvmTagInfo m_tag_info;
    container_t m_items;
};

} // namespace ModelView

#endif // MVVM_MODEL_SESSIONITEMCONTAINER_H
