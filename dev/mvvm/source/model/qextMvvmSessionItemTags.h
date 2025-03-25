// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_SESSIONITEMTAGS_H
#define MVVM_MODEL_SESSIONITEMTAGS_H

#include <qextMvvmTagRow.h>
#include <qextMvvmGlobal.h>
#include <string>
#include <vector>

namespace ModelView {

class QExtMvvmSessionItemContainer;
class QExtMvvmTagInfo;
class QExtMvvmSessionItem;

//! Collection of QExtMvvmSessionItem's containers according to their tags.

class QEXT_MVVM_API QExtMvvmSessionItemTags {
public:
    using container_t = std::vector<QExtMvvmSessionItemContainer*>;
    using const_iterator = container_t::const_iterator;

    QExtMvvmSessionItemTags();
    ~QExtMvvmSessionItemTags();
    QExtMvvmSessionItemTags(const QExtMvvmSessionItemTags&) = delete;
    QExtMvvmSessionItemTags& operator=(const QExtMvvmSessionItemTags&) = delete;

    // tag

    void registerTag(const QExtMvvmTagInfo& tagInfo, bool set_as_default = false);

    bool isTag(const std::string& name) const;

    std::string defaultTag() const;

    void setDefaultTag(const std::string& name);

    int itemCount(const std::string& tag_name) const;

    // adding and removal

    bool canInsertItem(const QExtMvvmSessionItem *item, const QExtMvvmTagRow& tagrow) const;

    bool insertItem(QExtMvvmSessionItem* item, const QExtMvvmTagRow& tagrow);

    bool canTakeItem(const QExtMvvmTagRow& tagrow) const;

    QExtMvvmSessionItem* takeItem(const QExtMvvmTagRow& tagrow);

    // item access
    QExtMvvmSessionItem* getItem(const QExtMvvmTagRow& tagrow) const;

    std::vector<QExtMvvmSessionItem*> getItems(const std::string& tag = {}) const;

    std::vector<QExtMvvmSessionItem*> allitems() const;

    QExtMvvmTagRow tagRowOfItem(const QExtMvvmSessionItem* item) const;

    const_iterator begin() const;
    const_iterator end() const;

    bool isSinglePropertyTag(const std::string& tag) const;

    int tagsCount() const;

    QExtMvvmSessionItemContainer& at(int index);

private:
    QExtMvvmSessionItemContainer* container(const std::string& tag_name) const;
    QExtMvvmSessionItemContainer* find_container(const std::string& tag_name) const;
    std::vector<QExtMvvmSessionItemContainer*> m_containers;
    std::string m_default_tag;
};

} // namespace ModelView

#endif // MVVM_MODEL_SESSIONITEMTAGS_H
