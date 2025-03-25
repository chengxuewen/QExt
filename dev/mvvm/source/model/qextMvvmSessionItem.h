// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_SESSIONITEM_H
#define MVVM_MODEL_SESSIONITEM_H


#include <qextMvvmCustomVariants.h>
#include <qextMvvmTypes.h>
#include <qextMvvmTagRow.h>
#include <qextMvvmGlobal.h>
#include <memory>
#include <stdexcept>
#include <vector>

namespace ModelView {

class QExtMvvmSessionModel;
class QExtMvvmTagInfo;
class QExtMvvmItemMapper;
class QExtMvvmSessionItemData;
class QExtMvvmSessionItemTags;

//! The main object representing an editable/displayable/serializable entity. Serves as a
//! construction element (node) of QExtMvvmSessionModel to represent all the data of GUI application.

class QEXT_MVVM_API QExtMvvmSessionItem {
public:
    explicit QExtMvvmSessionItem(QExtMvvmModelType modelType = Constants::BaseType);
    virtual ~QExtMvvmSessionItem();
    QExtMvvmSessionItem(const QExtMvvmSessionItem&) = delete;
    QExtMvvmSessionItem& operator=(const QExtMvvmSessionItem&) = delete;

    // basic item properties

    QExtMvvmModelType modelType() const;

    std::string identifier() const;

    virtual QExtMvvmSessionItem* setDisplayName(const std::string& name);
    virtual std::string displayName() const;

    QExtMvvmSessionModel* model() const;

    QExtMvvmSessionItem* parent() const;

    QExtMvvmTagRow tagRow() const;

    // methods to deal with item data

    bool hasData(int role = ItemDataRole::DATA) const;

    template <typename T> T data(int role = ItemDataRole::DATA) const;

    template <typename T>
    bool setData(const T& value, int role = ItemDataRole::DATA, bool direct = false);

    QExtMvvmSessionItemData* itemData();
    const QExtMvvmSessionItemData* itemData() const;

    // children access

    int childrenCount() const;

    std::vector<QExtMvvmSessionItem*> children() const;

    int itemCount(const std::string& tag) const;

    QExtMvvmSessionItem* getItem(const std::string& tag, int row = 0) const;

    std::vector<QExtMvvmSessionItem*> getItems(const std::string& tag) const;

    template <typename T> T* item(const std::string& tag) const;
    template <typename T = QExtMvvmSessionItem> std::vector<T*> items(const std::string& tag) const;

    QExtMvvmTagRow tagRowOfItem(const QExtMvvmSessionItem* item) const;

    void registerTag(const QExtMvvmTagInfo& tagInfo, bool set_as_default = false);

    QExtMvvmSessionItemTags* itemTags();
    const QExtMvvmSessionItemTags* itemTags() const;

    // item manipulation

    bool insertItem(QExtMvvmSessionItem* item, const QExtMvvmTagRow& tagrow);

    QExtMvvmSessionItem* insertItem(QExtUniquePointer<QExtMvvmSessionItem> item, const QExtMvvmTagRow& tagrow);
    template <typename T = QExtMvvmSessionItem> T* insertItem(const QExtMvvmTagRow& tagrow);

    QExtUniquePointer<QExtMvvmSessionItem> takeItem(const QExtMvvmTagRow& tagrow);

    // more convenience methods

    bool isEditable() const;
    QExtMvvmSessionItem* setEditable(bool value);

    bool isEnabled() const;
    QExtMvvmSessionItem* setEnabled(bool value);

    bool isVisible() const;
    QExtMvvmSessionItem* setVisible(bool value);

    std::string toolTip() const;
    QExtMvvmSessionItem* setToolTip(const std::string& tooltip);

    std::string editorType() const;
    QExtMvvmSessionItem* setEditorType(const std::string& editor_type);

    template <typename T> T property(const std::string& tag) const;
    template <typename T> void setProperty(const std::string& tag, const T& value);
    void setProperty(const std::string& tag, const char* value);

    QExtMvvmItemMapper* mapper();

private:
    friend class QExtMvvmSessionModel;
    friend class QExtMvvmJsonItemConverter;
    virtual void activate() {}
    bool set_data_internal(const QVariant& value, int role, bool direct);
    QVariant data_internal(int role) const;
    void setParent(QExtMvvmSessionItem* parent);
    void setModel(QExtMvvmSessionModel* model);
    void setAppearanceFlag(int flag, bool value);

    void setDataAndTags(QExtUniquePointer<QExtMvvmSessionItemData> data,
                        QExtUniquePointer<QExtMvvmSessionItemTags> tags);

    struct SessionItemImpl;
    QExtUniquePointer<SessionItemImpl> p_impl;
};

//! Sets data for a given role. When extra parameter `direct` is false (default case), will act
//! through the model to register command in undo/redo framework (if enabled) and so allow later
//! undo.

template <typename T> inline bool QExtMvvmSessionItem::setData(const T& value, int role, bool direct)
{
    return set_data_internal(QVariant::fromValue(value), role, direct);
}

//! Returns data of given type T for given role.

template <typename T> inline T QExtMvvmSessionItem::data(int role) const
{
    return data_internal(role).value<T>();
}

//! Returns first item under given tag casted to a specified type.
//! Returns nullptr, if item doesn't exist. If item exists but can't be casted will throw.

template <typename T> inline T* QExtMvvmSessionItem::item(const std::string& tag) const
{
    auto item = getItem(tag);
    if (item)
    {
        T* tag_item = dynamic_cast<T*>(item);
        if (!tag_item) throw std::runtime_error("Can't cast an item to given type");
        return tag_item;
    }
    return nullptr;
}

//! Returns all items under given tag casted to specific type.

template <typename T> std::vector<T*> QExtMvvmSessionItem::items(const std::string& tag) const
{
    std::vector<T*> result;
    for (auto item : getItems(tag))
    {
        auto casted = dynamic_cast<T*>(item);
        if (casted) result.push_back(casted);
    }
    return result;
}

//! Creates a new item and insert it into given tag under the given row.
//! Returns pointer to inserted item to the user.

template <typename T> inline T* QExtMvvmSessionItem::insertItem(const QExtMvvmTagRow& tagrow)
{
    return static_cast<T*>(insertItem(qextMakeUnique<T>(), tagrow));
}

//! Returns data stored in property item.
//! Property is single item registered under certain tag via QExtMvvmCompoundItem::addProperty method.

template <typename T> inline T QExtMvvmSessionItem::property(const std::string& tag) const
{
    return getItem(tag)->data<T>();
}

//! Sets value to property item.
//! Property is single item registered under certain tag via QExtMvvmCompoundItem::addProperty method, the
//! value will be assigned to it's data role.

template <typename T> inline void QExtMvvmSessionItem::setProperty(const std::string& tag, const T& value)
{
    getItem(tag)->setData(value);
}

//! Sets value to property item (specialized for special "const char *" case).
//! Property is single item registered under certain tag via QExtMvvmCompoundItem::addProperty method, the
//! value will be assigned to it's data role.

inline void QExtMvvmSessionItem::setProperty(const std::string& tag, const char* value)
{
    setProperty(tag, std::string(value));
}

} // namespace ModelView

#endif // MVVM_MODEL_SESSIONITEM_H
