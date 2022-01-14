// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmSessionItemContainer.h>
#include <qextMvvmSessionItemTags.h>
#include <stdexcept>

using namespace ModelView;

QEXTMvvmSessionItemTags::QEXTMvvmSessionItemTags() = default;

QEXTMvvmSessionItemTags::~QEXTMvvmSessionItemTags()
{
    for (auto tag : m_containers)
        delete tag;
}

void QEXTMvvmSessionItemTags::registerTag(const QEXTMvvmTagInfo& tagInfo, bool set_as_default)
{
    if (isTag(tagInfo.name()))
        throw std::runtime_error("SessionItemTags::registerTag() -> Error. Existing name '"
                                 + tagInfo.name() + "'");

    m_containers.push_back(new QEXTMvvmSessionItemContainer(tagInfo));
    if (set_as_default)
        m_default_tag = tagInfo.name();
}

//! Returns true if container with such name exists.

bool QEXTMvvmSessionItemTags::isTag(const std::string& name) const
{
    for (auto tag : m_containers)
        if (tag->name() == name)
            return true;
    return false;
}

//! Returns the name of the default tag.

std::string QEXTMvvmSessionItemTags::defaultTag() const
{
    return m_default_tag;
}

void QEXTMvvmSessionItemTags::setDefaultTag(const std::string& name)
{
    m_default_tag = name;
}

int QEXTMvvmSessionItemTags::itemCount(const std::string& tag_name) const
{
    return container(tag_name)->itemCount();
}

//! Inserts item in container with given tag name and at given row.
//! Returns true in the case of success. If tag name is empty, default tag will be used.

bool QEXTMvvmSessionItemTags::insertItem(QEXTMvvmSessionItem* item, const QEXTMvvmTagRow& tagrow)
{
    auto tag_container = container(tagrow.tag);
    auto row = tagrow.row < 0 ? tag_container->itemCount() : tagrow.row;
    return container(tagrow.tag)->insertItem(item, row);
}

//! Removes item at given row and for given tag, returns it to the user.

QEXTMvvmSessionItem* QEXTMvvmSessionItemTags::takeItem(const QEXTMvvmTagRow& tagrow)
{
    return container(tagrow.tag)->takeItem(tagrow.row);
}

//! Returns true if item can be taken.

bool QEXTMvvmSessionItemTags::canTakeItem(const QEXTMvvmTagRow& tagrow) const
{
    return container(tagrow.tag)->canTakeItem(tagrow.row);
}

//! Returns item at given row of given tag.

QEXTMvvmSessionItem* QEXTMvvmSessionItemTags::getItem(const QEXTMvvmTagRow& tagrow) const
{
    return container(tagrow.tag)->itemAt(tagrow.row);
}

//! Returns vector of items in the container with given name.
//! If tag name is empty, default tag will be used.

std::vector<QEXTMvvmSessionItem*> QEXTMvvmSessionItemTags::getItems(const std::string& tag) const
{
    return container(tag)->items();
}

std::vector<QEXTMvvmSessionItem*> QEXTMvvmSessionItemTags::allitems() const
{
    std::vector<QEXTMvvmSessionItem*> result;
    for (auto cont : m_containers) {
        auto container_items = cont->items();
        result.insert(result.end(), container_items.begin(), container_items.end());
    }

    return result;
}

//! Returns tag name and row of item in container.

QEXTMvvmTagRow QEXTMvvmSessionItemTags::tagRowOfItem(const QEXTMvvmSessionItem* item) const
{
    for (auto cont : m_containers) {
        int row = cont->indexOfItem(item);
        if (row != -1)
            return {cont->name(), row};
    }

    return {};
}

QEXTMvvmSessionItemTags::const_iterator QEXTMvvmSessionItemTags::begin() const
{
    return m_containers.begin();
}

QEXTMvvmSessionItemTags::const_iterator QEXTMvvmSessionItemTags::end() const
{
    return m_containers.end();
}

//! Returns true if given tag corresponds to registered single property tag.

bool QEXTMvvmSessionItemTags::isSinglePropertyTag(const std::string& tag) const
{
    auto cont = find_container(tag);
    return cont ? cont->tagInfo().isSinglePropertyTag() : false;
}

int QEXTMvvmSessionItemTags::tagsCount() const
{
    return static_cast<int>(m_containers.size());
}

QEXTMvvmSessionItemContainer& QEXTMvvmSessionItemTags::at(int index)
{
    if (index < 0 || index >= tagsCount())
        throw std::runtime_error("Error it SessionItemTags: wrong container index");
    return *m_containers.at(index);
}

//! Returns container corresponding to given tag name. If name is empty,
//! default tag will be used. Exception is thrown if no such tag exists.

QEXTMvvmSessionItemContainer* QEXTMvvmSessionItemTags::container(const std::string& tag_name) const
{
    std::string tagName = tag_name.empty() ? defaultTag() : tag_name;
    auto container = find_container(tagName);
    if (!container)
        throw std::runtime_error("SessionItemTags::container() -> Error. No such container '"
                                 + tagName + "'");

    return container;
}

//! Returns container corresponding to given tag name.

QEXTMvvmSessionItemContainer* QEXTMvvmSessionItemTags::find_container(const std::string& tag_name) const
{
    for (auto cont : m_containers)
        if (cont->name() == tag_name)
            return cont;

    return nullptr;
}
