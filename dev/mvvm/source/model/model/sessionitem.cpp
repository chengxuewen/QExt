// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/model/sessionitem.h"
#include "model/core/uniqueidgenerator.h"
#include "model/model/sessionitemdata.h"
#include "model/model/sessionitemtags.h"
#include "model/model/sessionmodel.h"
#include "model/model/taginfo.h"
#include "model/signals/itemmapper.h"
#include "model/signals/modelmapper.h"
#include <stdexcept>

using namespace ModelView;

namespace {
int appearance(const ModelView::QExtMvvmSessionItem& item)
{
    const int default_appearance = Appearance::EDITABLE | Appearance::ENABLED | Appearance::VISIBLE;
    return item.hasData(ItemDataRole::APPEARANCE) ? item.data<int>(ItemDataRole::APPEARANCE)
                                                  : default_appearance;
}
} // namespace

struct QExtMvvmSessionItem::SessionItemImpl {
    QExtMvvmSessionItem* m_self{nullptr};
    QExtMvvmSessionItem* m_parent{nullptr};
    QExtMvvmSessionModel* m_model{nullptr};
    QExtUniquePointer<QExtMvvmItemMapper> m_mapper;
    QExtUniquePointer<QExtMvvmSessionItemData> m_data;
    QExtUniquePointer<QExtMvvmSessionItemTags> m_tags;
    QExtMvvmModelType m_modelType;

    SessionItemImpl(QExtMvvmSessionItem* this_item)
        : m_self(this_item)
        , m_data(qextMakeUnique<QExtMvvmSessionItemData>())
        , m_tags(qextMakeUnique<QExtMvvmSessionItemTags>())
    {
    }

    bool do_setData(const QVariant& variant, int role)
    {
        bool result = m_data->setData(variant, role);
        if (result && m_model)
            m_model->mapper()->callOnDataChange(m_self, role);
        return result;
    }
};

QExtMvvmSessionItem::QExtMvvmSessionItem(QExtMvvmModelType modelType) : p_impl(qextMakeUnique<SessionItemImpl>(this))
{
    p_impl->m_modelType = std::move(modelType);
    setData(QExtMvvmUniqueIdGenerator::generate(), ItemDataRole::IDENTIFIER);
    setData(p_impl->m_modelType, ItemDataRole::DISPLAY);
}

QExtMvvmSessionItem::~QExtMvvmSessionItem()
{
    if (p_impl->m_mapper)
        p_impl->m_mapper->callOnItemDestroy();

    if (p_impl->m_model)
        p_impl->m_model->unregisterFromPool(this);
}

//! Returns item's model type.

QExtMvvmModelType QExtMvvmSessionItem::modelType() const
{
    return p_impl->m_modelType;
}

//! Returns unique identifier.

std::string QExtMvvmSessionItem::identifier() const
{
    return data<std::string>(ItemDataRole::IDENTIFIER);
}

//! Returns display name.

std::string QExtMvvmSessionItem::displayName() const
{
    return data<std::string>(ItemDataRole::DISPLAY);
}

//! Sets display name (fluent interface).

QExtMvvmSessionItem* QExtMvvmSessionItem::setDisplayName(const std::string& name)
{
    setData(name, ItemDataRole::DISPLAY);
    return this;
}

//! Returns the model to which given item belongs to. Will return nullptr if item doesn't have a
//! model.

QExtMvvmSessionModel* QExtMvvmSessionItem::model() const
{
    return p_impl->m_model;
}

//! Returns parent item. Will return nullptr if item doesn't have a parent.

QExtMvvmSessionItem* QExtMvvmSessionItem::parent() const
{
    return p_impl->m_parent;
}

//! Returns QExtMvvmTagRow of this item under which it is accessible through its parent.

QExtMvvmTagRow QExtMvvmSessionItem::tagRow() const
{
    return parent() ? parent()->tagRowOfItem(this) : QExtMvvmTagRow();
}

//! Returns true if item has data on board with given role.

bool QExtMvvmSessionItem::hasData(int role) const
{
    return p_impl->m_data->hasData(role);
}

//! Returns pointer to item's data container (const version).

const QExtMvvmSessionItemData* QExtMvvmSessionItem::itemData() const
{
    return p_impl->m_data.get();
}

//! Returns pointer to item's data container (non-const version).

QExtMvvmSessionItemData* QExtMvvmSessionItem::itemData()
{
    return const_cast<QExtMvvmSessionItemData*>(static_cast<const QExtMvvmSessionItem*>(this)->itemData());
}

//! Returns total number of children in all tags.

int QExtMvvmSessionItem::childrenCount() const
{
    return static_cast<int>(children().size());
}

//! Returns vector of children formed from all chidlren from all tags.

std::vector<QExtMvvmSessionItem*> QExtMvvmSessionItem::children() const
{
    return p_impl->m_tags->allitems();
}

//! Returns number of items in given tag.

int QExtMvvmSessionItem::itemCount(const std::string& tag) const
{
    return p_impl->m_tags->itemCount(tag);
}

//! Returns item at given row of given tag.

QExtMvvmSessionItem* QExtMvvmSessionItem::getItem(const std::string& tag, int row) const
{
    return p_impl->m_tags->getItem({tag, row});
}

//! Returns all children stored at given tag.

std::vector<QExtMvvmSessionItem*> QExtMvvmSessionItem::getItems(const std::string& tag) const
{
    return p_impl->m_tags->getItems(tag);
}

//! Returns pair of tag and row corresponding to given item.
//! Returns {"", -1} if given item doesn't belong to children.

QExtMvvmTagRow QExtMvvmSessionItem::tagRowOfItem(const QExtMvvmSessionItem* item) const
{
    return p_impl->m_tags->tagRowOfItem(item);
}

//! Returns pointer to internal collection of tag-registered items (const version).

const QExtMvvmSessionItemTags* QExtMvvmSessionItem::itemTags() const
{
    return p_impl->m_tags.get();
}

//! Registers tag to hold items under given name.

void QExtMvvmSessionItem::registerTag(const QExtMvvmTagInfo& tagInfo, bool set_as_default)
{
    p_impl->m_tags->registerTag(tagInfo, set_as_default);
}

//! Returns pointer to internal collection of tag-registered items (non-const version).

QExtMvvmSessionItemTags* QExtMvvmSessionItem::itemTags()
{
    return const_cast<QExtMvvmSessionItemTags*>(static_cast<const QExtMvvmSessionItem*>(this)->itemTags());
}

//! Inserts the item into the given tag under the given row.
//! Returns 'true' in the case of success, take ownership over the item.
//! If an item can't be inserted for a given QExtMvvmTagRow (i.e. when the container is full, or not
//! intended for items of a given type) will return false and will not take ownership.

bool QExtMvvmSessionItem::insertItem(QExtMvvmSessionItem* item, const QExtMvvmTagRow& tagrow)
{
    if (!p_impl->m_tags->canInsertItem(item, tagrow))
        return false;
    return insertItem(QExtUniquePointer<QExtMvvmSessionItem>(item), tagrow) != nullptr;
}

//! Insert item into given tag under the given row. Will take ownership of inserted item.
//! Returns back a pointer to the same item for convenience.

QExtMvvmSessionItem* QExtMvvmSessionItem::insertItem(QExtUniquePointer<QExtMvvmSessionItem> item, const QExtMvvmTagRow& tagrow)
{
    if (!item)
        throw std::runtime_error("QExtMvvmSessionItem::insertItem() -> Invalid item.");

    if (item->parent())
        throw std::runtime_error("QExtMvvmSessionItem::insertItem() -> Existing parent.");

    if (item->model())
        throw std::runtime_error("QExtMvvmSessionItem::insertItem() -> Existing model.");

    if (!p_impl->m_tags->canInsertItem(item.get(), tagrow))
        throw std::runtime_error("QExtMvvmSessionItem::insertItem() -> Can't insert item.");

    auto result = item.release();
    p_impl->m_tags->insertItem(result, tagrow);
    result->setParent(this);
    result->setModel(model());

    if (p_impl->m_model) {
        // FIXME think of actual_tagrow removal if input tag,row will be always valid
        auto actual_tagrow = tagRowOfItem(result);
        p_impl->m_model->mapper()->callOnItemInserted(this, actual_tagrow);
    }

    return result;
}


//! Removes item from given row from given tag, returns it to the caller.
//! Ownership is granted to the caller.

QExtUniquePointer<QExtMvvmSessionItem> QExtMvvmSessionItem::takeItem(const QExtMvvmTagRow& tagrow)
{
    if (!p_impl->m_tags->canTakeItem(tagrow))
        return {};

    if (p_impl->m_model)
        p_impl->m_model->mapper()->callOnItemAboutToBeRemoved(this, tagrow);

    auto result = p_impl->m_tags->takeItem(tagrow);
    result->setParent(nullptr);
    result->setModel(nullptr);
    // FIXME remaining problem is that QExtMvvmItemMapper still looking to the model
    if (p_impl->m_model)
        p_impl->m_model->mapper()->callOnItemRemoved(this, tagrow);

    return QExtUniquePointer<QExtMvvmSessionItem>(result);
}

//! Returns true if this item has `editable` flag set.
//! The data value of an editable item normally can be changed when it appears in trees and tables.

bool QExtMvvmSessionItem::isEditable() const
{
    return appearance(*this) & Appearance::EDITABLE;
}

//! Sets `editable` flag to given value (fluent interface).

QExtMvvmSessionItem* QExtMvvmSessionItem::setEditable(bool value)
{
    setAppearanceFlag(Appearance::EDITABLE, value);
    return this;
}

//! Returns true if this item has `enabled` flag set.

bool QExtMvvmSessionItem::isEnabled() const
{
    return appearance(*this) & Appearance::ENABLED;
}

//! Sets `enabled` flag to given value (fluent interface). Used in Qt-widgets to show that given
//! property is currently enabled. Enabled items appear in normal color, disabled items are grayed
//! out.

QExtMvvmSessionItem* QExtMvvmSessionItem::setEnabled(bool value)
{
    setAppearanceFlag(Appearance::ENABLED, value);
    return this;
}

//! Returns true if this item has `visible` flag set.

bool QExtMvvmSessionItem::isVisible() const
{
    return appearance(*this) & Appearance::VISIBLE;
}

//! Sets `visible` flag to given value (fluent interface). Used in Qt-widgets to hide given
//! property from a view. For example, `QExtMvvmPropertyTreeView` will not show QExtMvvmPropertyItem with the given
//! flag set to `true` among other properties.

QExtMvvmSessionItem* QExtMvvmSessionItem::setVisible(bool value)
{
    setAppearanceFlag(Appearance::VISIBLE, value);
    return this;
}

//! Returns item tooltip, if exists.

std::string QExtMvvmSessionItem::toolTip() const
{
    return hasData(ItemDataRole::TOOLTIP) ? data<std::string>(ItemDataRole::TOOLTIP)
                                          : std::string();
}

//! Sets item tooltip (fluent interface).

QExtMvvmSessionItem* QExtMvvmSessionItem::setToolTip(const std::string& tooltip)
{
    setData(tooltip, ItemDataRole::TOOLTIP);
    return this;
}

//! Returns editor type.

std::string QExtMvvmSessionItem::editorType() const
{
    return hasData(ItemDataRole::EDITORTYPE) ? data<std::string>(ItemDataRole::EDITORTYPE)
                                             : std::string();
}

//! Sets editor type (fluent interface).
//! Allows creating custom editors in the cells of Qt trees and tables.

QExtMvvmSessionItem* QExtMvvmSessionItem::setEditorType(const std::string& editor_type)
{
    setData(editor_type, ItemDataRole::EDITORTYPE);
    return this;
}

//! Sets the data for given role. Method invented to hide implementaiton details.

bool QExtMvvmSessionItem::set_data_internal(const QVariant& value, int role, bool direct)
{
    // If model is present, and undo stack is enabled, will forward request to the model
    // (unless user explicitely asks for direct processing via direct=true flag).
    const bool act_through_model = !direct && model() && model()->undoStack();
    return act_through_model ? model()->setData(this, value, role)
                             : p_impl->do_setData(value, role);
}

//! Returns data for given role. Method invented to hide implementaiton details and avoid
//! placing sessionitemdata.h into 'sessionitem.h' header.

QVariant QExtMvvmSessionItem::data_internal(int role) const
{
    return p_impl->m_data->data(role);
}

void QExtMvvmSessionItem::setParent(QExtMvvmSessionItem* parent)
{
    p_impl->m_parent = parent;
}

void QExtMvvmSessionItem::setModel(QExtMvvmSessionModel* model)
{
    if (p_impl->m_model)
        p_impl->m_model->unregisterFromPool(this);

    p_impl->m_model = model;

    if (p_impl->m_model)
        p_impl->m_model->registerInPool(this);

    for (auto child : children())
        child->setModel(model);
}

void QExtMvvmSessionItem::setAppearanceFlag(int flag, bool value)
{
    int flags = appearance(*this);
    if (value)
        flags |= flag;
    else
        flags &= ~flag;

    // By setting data with internal method we are bypassing the model, and so undo/redo.
    // So current convention is to not invoke undo when changing appearance properties.
    // Shall we change it?
    p_impl->do_setData(flags, ItemDataRole::APPEARANCE);
}

//! Returns item mapper. Allows subscribing to various events happening to the item.

QExtMvvmItemMapper* QExtMvvmSessionItem::mapper()
{
    if (!p_impl->m_mapper)
        p_impl->m_mapper = qextMakeUnique<QExtMvvmItemMapper>(this);
    return p_impl->m_mapper.get();
}

void QExtMvvmSessionItem::setDataAndTags(QExtUniquePointer<QExtMvvmSessionItemData> data,
                                 QExtUniquePointer<QExtMvvmSessionItemTags> tags)
{
    p_impl->m_data = std::move(data);
    p_impl->m_tags = std::move(tags);
}
