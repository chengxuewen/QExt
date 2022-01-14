#ifndef _QEXTMVVMMODELSESSIONITEMTAGS_H
#define _QEXTMVVMMODELSESSIONITEMTAGS_H

#include <qextMvvmTagRow.h>
#include <qextMvvmGlobal.h>
#include <string>
#include <vector>

namespace ModelView
{

class QEXTMvvmSessionItemContainer;
class QEXTMvvmTagInfo;
class QEXTMvvmSessionItem;

//! Collection of QEXTMvvmSessionItem's containers according to their tags.

class QEXT_MVVM_API QEXTMvvmSessionItemTags
{
public:
    using container_t = std::vector<QEXTMvvmSessionItemContainer*>;
    using const_iterator = container_t::const_iterator;

    QEXTMvvmSessionItemTags();
    ~QEXTMvvmSessionItemTags();
    QEXTMvvmSessionItemTags(const QEXTMvvmSessionItemTags&) = delete;
    QEXTMvvmSessionItemTags& operator=(const QEXTMvvmSessionItemTags&) = delete;

    // tag

    void registerTag(const QEXTMvvmTagInfo& tagInfo, bool set_as_default = false);

    bool isTag(const std::string& name) const;

    std::string defaultTag() const;

    void setDefaultTag(const std::string& name);

    int itemCount(const std::string& tag_name) const;

    // adding and removal

    bool insertItem(QEXTMvvmSessionItem* item, const QEXTMvvmTagRow& tagrow);

    QEXTMvvmSessionItem* takeItem(const QEXTMvvmTagRow& tagrow);

    bool canTakeItem(const QEXTMvvmTagRow& tagrow) const;

    // item access
    QEXTMvvmSessionItem* getItem(const QEXTMvvmTagRow& tagrow) const;

    std::vector<QEXTMvvmSessionItem*> getItems(const std::string& tag = {}) const;

    std::vector<QEXTMvvmSessionItem*> allitems() const;

    QEXTMvvmTagRow tagRowOfItem(const QEXTMvvmSessionItem* item) const;

    const_iterator begin() const;
    const_iterator end() const;

    bool isSinglePropertyTag(const std::string& tag) const;

    int tagsCount() const;

    QEXTMvvmSessionItemContainer& at(int index);

private:
    QEXTMvvmSessionItemContainer* container(const std::string& tag_name) const;
    QEXTMvvmSessionItemContainer* find_container(const std::string& tag_name) const;
    std::vector<QEXTMvvmSessionItemContainer*> m_containers;
    std::string m_default_tag;
};

} // namespace ModelView

#endif // _QEXTMVVMMODELSESSIONITEMTAGS_H
