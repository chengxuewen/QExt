// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmSessionItemTags.h>
#include <qextMvvmSessionItemContainer.h>
#include <stdexcept>

using namespace ModelView;

QExtMvvmSessionItemTags::QExtMvvmSessionItemTags() = default;

QExtMvvmSessionItemTags::~QExtMvvmSessionItemTags()
{
    for (auto tag : m_containers)
        delete tag;
}

void QExtMvvmSessionItemTags::registerTag(const QExtMvvmTagInfo& tagInfo, bool set_as_default)
{
    if (isTag(tagInfo.name()))
        throw std::runtime_error("QExtMvvmSessionItemTags::registerTag() -> Error. Existing name '"
                                 + tagInfo.name() + "'");

    m_containers.push_back(new QExtMvvmSessionItemContainer(tagInfo));
    if (set_as_default)
        m_default_tag = tagInfo.name();
}

//! Returns true if container with such name exists.

bool QExtMvvmSessionItemTags::isTag(const std::string& name) const
{
    for (auto tag : m_containers)
        if (tag->name() == name)
            return true;
    return false;
}

//! Returns the name of the default tag.

std::string QExtMvvmSessionItemTags::defaultTag() const
{
    return m_default_tag;
}

void QExtMvvmSessionItemTags::setDefaultTag(const std::string& name)
{
    m_default_tag = name;
}

int QExtMvvmSessionItemTags::itemCount(const std::string& tag_name) const
{
    return container(tag_name)->itemCount();
}

//! Returns true if item can be inserted.

bool QExtMvvmSessionItemTags::canInsertItem(const QExtMvvmSessionItem* item, const QExtMvvmTagRow &tagrow) const
{
    auto tag_container = container(tagrow.tag);
    // negative row means appending to the vector
    auto row = tagrow.row < 0 ? tag_container->itemCount() : tagrow.row;
    return container(tagrow.tag)->canInsertItem(item, row);
}

//! Inserts item in container with given tag name and at given row.
//! Returns true in the case of success. If tag name is empty, default tag will be used.

bool QExtMvvmSessionItemTags::insertItem(QExtMvvmSessionItem* item, const QExtMvvmTagRow& tagrow)
{
    auto tag_container = container(tagrow.tag);
    // negative row means appending to the vector
    auto row = tagrow.row < 0 ? tag_container->itemCount() : tagrow.row;
    return container(tagrow.tag)->insertItem(item, row);
}

//! Returns true if item can be taken.

bool QExtMvvmSessionItemTags::canTakeItem(const QExtMvvmTagRow& tagrow) const
{
    return container(tagrow.tag)->canTakeItem(tagrow.row);
}

//! Removes item at given row and for given tag, returns it to the user.

QExtMvvmSessionItem* QExtMvvmSessionItemTags::takeItem(const QExtMvvmTagRow& tagrow)
{
    return container(tagrow.tag)->takeItem(tagrow.row);
}

//! Returns item at given row of given tag.

QExtMvvmSessionItem* QExtMvvmSessionItemTags::getItem(const QExtMvvmTagRow& tagrow) const
{
    return container(tagrow.tag)->itemAt(tagrow.row);
}

//! Returns vector of items in the container with given name.
//! If tag name is empty, default tag will be used.

std::vector<QExtMvvmSessionItem*> QExtMvvmSessionItemTags::getItems(const std::string& tag) const
{
    return container(tag)->items();
}

std::vector<QExtMvvmSessionItem*> QExtMvvmSessionItemTags::allitems() const
{
    std::vector<QExtMvvmSessionItem*> result;
    for (auto cont : m_containers) {
        auto container_items = cont->items();
        result.insert(result.end(), container_items.begin(), container_items.end());
    }

    return result;
}

//! Returns tag name and row of item in container.

QExtMvvmTagRow QExtMvvmSessionItemTags::tagRowOfItem(const QExtMvvmSessionItem* item) const
{
    for (auto cont : m_containers) {
        int row = cont->indexOfItem(item);
        if (row != -1)
            return {cont->name(), row};
    }

    return {};
}

QExtMvvmSessionItemTags::const_iterator QExtMvvmSessionItemTags::begin() const
{
    return m_containers.begin();
}

QExtMvvmSessionItemTags::const_iterator QExtMvvmSessionItemTags::end() const
{
    return m_containers.end();
}

//! Returns true if given tag corresponds to registered single property tag.

bool QExtMvvmSessionItemTags::isSinglePropertyTag(const std::string& tag) const
{
    auto cont = find_container(tag);
    return cont ? cont->tagInfo().isSinglePropertyTag() : false;
}

int QExtMvvmSessionItemTags::tagsCount() const
{
    return static_cast<int>(m_containers.size());
}

QExtMvvmSessionItemContainer& QExtMvvmSessionItemTags::at(int index)
{
    if (index < 0 || index >= tagsCount())
        throw std::runtime_error("Error it QExtMvvmSessionItemTags: wrong container index");
    return *m_containers.at(index);
}

//! Returns container corresponding to given tag name. If name is empty,
//! default tag will be used. Exception is thrown if no such tag exists.

QExtMvvmSessionItemContainer* QExtMvvmSessionItemTags::container(const std::string& tag_name) const
{
    std::string tagName = tag_name.empty() ? defaultTag() : tag_name;
    auto container = find_container(tagName);
    if (!container)
        throw std::runtime_error("QExtMvvmSessionItemTags::container() -> Error. No such container '"
                                 + tagName + "'");

    return container;
}

//! Returns container corresponding to given tag name.

QExtMvvmSessionItemContainer* QExtMvvmSessionItemTags::find_container(const std::string& tag_name) const
{
    for (auto cont : m_containers)
        if (cont->name() == tag_name)
            return cont;

    return nullptr;
}
