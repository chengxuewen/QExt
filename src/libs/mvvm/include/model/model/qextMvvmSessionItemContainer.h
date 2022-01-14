#ifndef _QEXTMVVMMODELSESSIONITEMCONTAINER_H
#define _QEXTMVVMMODELSESSIONITEMCONTAINER_H

#include <qextMvvmTagInfo.h>
#include <qextMvvmGlobal.h>

#include <vector>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Holds collection of QEXTMvvmSessionItem objects related to the same tag.

class QEXT_MVVM_API QEXTMvvmSessionItemContainer
{
public:
    using container_t = std::vector<QEXTMvvmSessionItem*>;
    using const_iterator = container_t::const_iterator;

    QEXTMvvmSessionItemContainer(QEXTMvvmTagInfo tag_info);
    QEXTMvvmSessionItemContainer(const QEXTMvvmSessionItemContainer&) = delete;
    QEXTMvvmSessionItemContainer& operator=(const QEXTMvvmSessionItemContainer&) = delete;
    ~QEXTMvvmSessionItemContainer();

    bool empty() const;

    int itemCount() const;

    std::vector<QEXTMvvmSessionItem*> items() const;

    bool insertItem(QEXTMvvmSessionItem* item, int index);

    QEXTMvvmSessionItem* takeItem(int index);

    bool canTakeItem(int index) const;

    bool canInsertItem(const QEXTMvvmSessionItem* item, int index) const;

    int indexOfItem(const QEXTMvvmSessionItem* item) const;

    QEXTMvvmSessionItem* itemAt(int index) const;

    std::string name() const;

    QEXTMvvmTagInfo tagInfo() const;

    const_iterator begin() const;

    const_iterator end() const;

private:
    bool maximum_reached() const;
    bool minimum_reached() const;
    bool is_valid_item(const QEXTMvvmSessionItem* item) const;
    QEXTMvvmTagInfo m_tag_info;
    container_t m_items;
};

} // namespace ModelView

#endif // _QEXTMVVMMODELSESSIONITEMCONTAINER_H
