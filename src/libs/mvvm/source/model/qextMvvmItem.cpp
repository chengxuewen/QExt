#include <qextMvvmItem.h>
#include <qextMvvmItem_p.h>
#include <qextMvvmUniqueIdGenerator.h>
#include <qextMvvmUtils.h>
#include <qextMvvmItemData.h>
#include <qextMvvmItemTags.h>
#include <qextMvvmModel.h>
#include <qextMvvmTagInfo.h>
#include <qextMvvmItemMapper.h>
#include <qextMvvmModelMapper.h>
#include <stdexcept>

namespace
{
    int qextMvvmAppearance(const QEXTMvvmItem &item)
    {
        const int defaultAppearance = Appearance::EDITABLE | Appearance::ENABLED;
        return item.hasData(QEXTMvvmItem::Role_Appearance) ? item.data<int>(QEXTMvvmItem::Role_Appearance)
                                                           : defaultAppearance;
    }
} // namespace


QEXTMvvmItemPrivate::QEXTMvvmItemPrivate(QEXTMvvmItem *q)
    : q_ptr(q)
    , m_parent(QEXT_DECL_NULLPTR)
    , m_model(QEXT_DECL_NULLPTR)
    , m_data(new QEXTMvvmItemData)
    , m_tags(new QEXTMvvmItemTags)
{

}

QEXTMvvmItemPrivate::~QEXTMvvmItemPrivate()
{
    if (!m_mapper.isNull())
    {
        m_mapper->callOnItemDestroy();
    }

    if (m_model)
    {
        m_model->unregisterItem(q_ptr);
    }
}

bool QEXTMvvmItemPrivate::setData(const QVariant &variant, int role)
{
    bool result = m_data->setData(variant, role);
    if (result && m_model)
    {
        m_model->mapper()->callOnDataChange(q_ptr, role);
    }
    return result;
}

int QEXTMvvmItemPrivate::appearance() const
{
    const int defaultAppearance = Appearance::EDITABLE | Appearance::ENABLED;
    return q_ptr->hasData(QEXTMvvmItem::Role_Appearance) ? q_ptr->data<int>(QEXTMvvmItem::Role_Appearance) : defaultAppearance;
}



QEXTMvvmItem::QEXTMvvmItem(const QString &modelType)
    : d_ptr(new QEXTMvvmItemPrivate(this))
{
    QEXT_DECL_D(QEXTMvvmItem);
    d->m_modelType = modelType;
    this->setData(QEXTMvvmUniqueIdGenerator::generate(), QEXTMvvmItem::Role_Identifier);
    this->setData(d->m_modelType, QEXTMvvmItem::Role_Display);
}

QEXTMvvmItem::~QEXTMvvmItem()
{
}

QString QEXTMvvmItem::modelType() const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return d->m_modelType;
}

QString QEXTMvvmItem::displayName() const
{
    return this->data<QString>(QEXTMvvmItem::Role_Display);
}

QEXTMvvmItem *QEXTMvvmItem::setDisplayName(const QString &name)
{
    this->setData(name, QEXTMvvmItem::Role_Display);
    return this;
}

QString QEXTMvvmItem::identifier() const
{
    return this->data<QString>(QEXTMvvmItem::Role_Identifier);
}

//! Returns true if item has data on board with given role.

bool QEXTMvvmItem::hasData(int role) const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return d->m_data->hasData(role);
}

QEXTMvvmModel *QEXTMvvmItem::model() const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return d->m_model;
}

QEXTMvvmItem *QEXTMvvmItem::parent() const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return d->m_parent;
}

int QEXTMvvmItem::childrenCount() const
{
    return this->children().size();
}

//! Insert item into given tag under the given row.

bool QEXTMvvmItem::insertItem(QEXTMvvmItem *item, const QEXTMvvmTagRow &tagrow)
{
    QEXT_DECL_D(QEXTMvvmItem);
    // think of passing unique_ptr directly
    if (!item)
    {
        throw std::runtime_error("QEXTMvvmItem::insertItem() -> Invalid item.");
    }

    if (item->parent())
    {
        throw std::runtime_error("QEXTMvvmItem::insertItem() -> Existing parent.");
    }

    if (item->model())
    {
        throw std::runtime_error("QEXTMvvmItem::insertItem() -> Existing model.");
    }

    bool result = d->m_tags->insertItem(item, tagrow);
    if (result)
    {
        item->setParent(this);
        item->setModel(model());
        if (d->m_model)
        {
            // FIXME think of actual_tagrow removal if input tag,row will be always valid
            QEXTMvvmTagRow actualTagrow = this->tagRowOfItem(item);
            d->m_model->mapper()->callOnItemInserted(this, actualTagrow);
        }
    }

    return result;
}

//! Removes item from given row from given tag, returns it to the caller.

QEXTMvvmItem *QEXTMvvmItem::takeItem(const QEXTMvvmTagRow &tagrow)
{
    QEXT_DECL_D(QEXTMvvmItem);
    if (!d->m_tags->canTakeItem(tagrow))
    {
        return QEXT_DECL_NULLPTR;
    }

    if (d->m_model)
    {
        d->m_model->mapper()->callOnItemAboutToBeRemoved(this, tagrow);
    }

    auto result = d->m_tags->takeItem(tagrow);
    result->setParent(nullptr);
    result->setModel(nullptr);
    // FIXME remaining problem is that QEXTMvvmItemMapper still looking to the model
    if (d->m_model)
    {
        d->m_model->mapper()->callOnItemRemoved(this, tagrow);
    }

    return result;
}

//! Returns vector of children formed from all chidlren from all tags.

QVector<QEXTMvvmItem *> QEXTMvvmItem::children() const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return d->m_tags->allItems();
}

//! Return vector of data roles which this item currently holds.

QVector<int> QEXTMvvmItem::roles() const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return d->m_data->roles();
}

//! Returns the name of the default tag.

QString QEXTMvvmItem::defaultTag() const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return d->m_tags->defaultTag();
}

//! Sets the default tag.

void QEXTMvvmItem::setDefaultTag(const QString &tag)
{
    QEXT_DECL_D(QEXTMvvmItem);
    d->m_tags->setDefaultTag(tag);
}

//! Registers tag to hold items under given name.

void QEXTMvvmItem::registerTag(const QEXTMvvmTagInfo &tagInfo, bool setAsDefault)
{
    QEXT_DECL_D(QEXTMvvmItem);
    d->m_tags->registerTag(tagInfo, setAsDefault);
}

//! Returns true if tag with given name exists.

bool QEXTMvvmItem::isTag(const QString &name) const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return d->m_tags->isTag(name);
}

//! Returns tag of this item under which it is accessible for its parent.

QString QEXTMvvmItem::tag() const
{
    return this->tagRow().tag;
}

//! Returns QEXTMvvmTagRow of this item under which it is accessible for its parent.

QEXTMvvmTagRow QEXTMvvmItem::tagRow() const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return this->parent() ? this->parent()->tagRowOfItem(const_cast<QEXTMvvmItem *>(this)) : QEXTMvvmTagRow();
}

//! Returns number of items in given tag.

int QEXTMvvmItem::itemCount(const QString &tag) const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return d->m_tags->itemCount(tag);
}

//! Returns item at given row of given tag.

QEXTMvvmItem *QEXTMvvmItem::item(const QString &tag, int row) const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return d->m_tags->getItem({tag, row});
}

QVector<QEXTMvvmItem *> QEXTMvvmItem::items(const QString &tag) const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return d->m_tags->getItems(tag);
}

//! Returns tag corresponding to given item.
//! Returns "" if item doesn't belong to children.

QString QEXTMvvmItem::tagOfItem(QEXTMvvmItem *item) const
{
    return this->tagRowOfItem(item).tag;
}

//! Returns pair of tag and row corresponding to given item.
//! Returns {"", -1} if item doesn't belong to children.

QEXTMvvmTagRow QEXTMvvmItem::tagRowOfItem(QEXTMvvmItem *item) const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return d->m_tags->tagRowOfItem(item);
}

QEXTMvvmItemMapper *QEXTMvvmItem::mapper()
{
    QEXT_DECL_D(QEXTMvvmItem);
    if (d->m_mapper.isNull())
    {
//        d->m_mapper.reset(new QEXTMvvmItemMapper(this));
    }
    return d->m_mapper.data();
}

bool QEXTMvvmItem::isEditable() const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return d->appearance() & Appearance::EDITABLE;
}

QEXTMvvmItem *QEXTMvvmItem::setEditable(bool value)
{
    this->setAppearanceFlag(Appearance::EDITABLE, value);
    return this;
}

bool QEXTMvvmItem::isEnabled() const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return d->appearance() & Appearance::ENABLED;
}

QEXTMvvmItem *QEXTMvvmItem::setEnabled(bool value)
{
    this->setAppearanceFlag(Appearance::ENABLED, value);
    return this;
}

//! Returns item's tooltip.

QString QEXTMvvmItem::toolTip() const
{
    return this->hasData(QEXTMvvmItem::Role_ToolTip) ? this->data<QString>(QEXTMvvmItem::Role_ToolTip)
           : QString();
}

//! Sets item tooltip.

QEXTMvvmItem *QEXTMvvmItem::setToolTip(const QString &tooltip)
{
    this->setData(tooltip, QEXTMvvmItem::Role_ToolTip);
    return this;
}

//! Returns editor type.

QString QEXTMvvmItem::editorType() const
{
    return this->hasData(QEXTMvvmItem::Role_Editor) ? this->data<QString>(QEXTMvvmItem::Role_Editor)
           : QString();
}

//! Sets editor type. Allows creating custom editors in the cells of Qt trees and tables.

QEXTMvvmItem *QEXTMvvmItem::setEditorType(const QString &editorType)
{
    this->setData(editorType, QEXTMvvmItem::Role_Editor);
    return this;
}

//! Returns true if given tag is related to single property tags.

bool QEXTMvvmItem::isSinglePropertyTag(const QString &tag) const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return d->m_tags->isSinglePropertyTag(tag);
}

//! Sets the data for given role.
//! Method invented to hide implementaiton details.

bool QEXTMvvmItem::setDataInternal(QVariant value, int role)
{
    return this->model() ? this->model()->setData(this, value, role) : this->setDataIntern(value, role);
}

//! Returns data for given role. Method invented to hide implementaiton details.

QVariant QEXTMvvmItem::dataInternal(int role) const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return d->m_data->data(role);
}

void QEXTMvvmItem::setParent(QEXTMvvmItem *parent)
{
    QEXT_DECL_D(QEXTMvvmItem);
    d->m_parent = parent;
}

void QEXTMvvmItem::setModel(QEXTMvvmModel *model)
{
    QEXT_DECL_D(QEXTMvvmItem);
    if (d->m_model)
    {
        d->m_model->unregisterItem(this);
    }

    d->m_model = model;

    if (d->m_model)
    {
        d->m_model->registerItem(this);
    }

    QVector<QEXTMvvmItem *> childrens = this->children();
    for (int i = 0; i < childrens.size(); ++i)
    {
        QEXTMvvmItem *child = childrens.at(i);
        child->setModel(model);
    }
}

void QEXTMvvmItem::setAppearanceFlag(int flag, bool value)
{
    QEXT_DECL_D(QEXTMvvmItem);
    int flags = d->appearance();
    if (value)
    {
        flags |= flag;
    }
    else
    {
        flags &= ~flag;
    }

    // By setting data with internal method we are bypassing the model, and so undo/redo.
    // So current convention is to not invoke undo when changing appearance properties.
    // Shall we change it?
    this->setDataIntern(flags, QEXTMvvmItem::Role_Appearance);
}

const QEXTMvvmItemData *QEXTMvvmItem::itemData() const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return d->m_data.data();
}

QEXTMvvmItemData *QEXTMvvmItem::itemData()
{
    QEXT_DECL_D(QEXTMvvmItem);
    return d->m_data.data();
}

QEXTMvvmItemTags *QEXTMvvmItem::itemTags() const
{
    QEXT_DECL_DC(QEXTMvvmItem);
    return d->m_tags.data();
}

void QEXTMvvmItem::setDataAndTags(QEXTMvvmItemData *data, QEXTMvvmItemTags *tags)
{
    QEXT_DECL_D(QEXTMvvmItem);
    d->m_data.reset(data);
    d->m_tags.reset(tags);
}

bool QEXTMvvmItem::setDataIntern(const QVariant &variant, int role)
{
    QEXT_DECL_D(QEXTMvvmItem);
    return d->setData(variant, role);
}

