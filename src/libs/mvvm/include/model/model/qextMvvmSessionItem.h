#ifndef _QEXTMVVMMODELSESSIONITEM_H
#define _QEXTMVVMMODELSESSIONITEM_H

#include <qextMvvmCustomVariants.h>
#include <qextMvvmTypes.h>
#include <qextMvvmConstantsTypes.h>
#include <qextMvvmTagRow.h>
#include <qextMvvmGlobal.h>

#include <QVariant>

#include <memory>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace ModelView
{

class QEXTMvvmSessionItemTags;
class QEXTMvvmSessionModel;
class QEXTMvvmTagInfo;
class QEXTMvvmItemMapper;
class QEXTMvvmSessionItemData;

class QEXT_MVVM_API QEXTMvvmSessionItem
{
public:
    explicit QEXTMvvmSessionItem(model_type modelType = QEXTMvvmConstants::BaseType);
    virtual ~QEXTMvvmSessionItem();
    QEXTMvvmSessionItem(const QEXTMvvmSessionItem&) = delete;
    QEXTMvvmSessionItem& operator=(const QEXTMvvmSessionItem&) = delete;

    model_type modelType() const;

    virtual std::string displayName() const;
    virtual QEXTMvvmSessionItem* setDisplayName(const std::string& name);

    std::string identifier() const;

    template <typename T> bool setData(const T& value, int role = ItemDataRole::DATA);
    bool setDataIntern(const QVariant& variant, int role);

    bool hasData(int role = ItemDataRole::DATA) const;

    template <typename T> T data(int role = ItemDataRole::DATA) const;

    QEXTMvvmSessionModel* model() const;

    QEXTMvvmSessionItem* parent() const;

    int childrenCount() const;

    bool insertItem(QEXTMvvmSessionItem* item, const QEXTMvvmTagRow& tagrow);

    QEXTMvvmSessionItem* takeItem(const QEXTMvvmTagRow& tagrow);

    std::vector<QEXTMvvmSessionItem*> children() const;

    std::vector<int> roles() const;

    // tags
    std::string defaultTag() const;
    void setDefaultTag(const std::string& tag);

    void registerTag(const QEXTMvvmTagInfo& tagInfo, bool set_as_default = false);

    bool isTag(const std::string& name) const;

    std::string tag() const;

    QEXTMvvmTagRow tagRow() const;

    // access tagged items
    int itemCount(const std::string& tag) const;
    QEXTMvvmSessionItem* getItem(const std::string& tag, int row = 0) const; // FIXME TagRow?
    std::vector<QEXTMvvmSessionItem*> getItems(const std::string& tag) const;
    template <typename T> T* item(const std::string& tag) const;
    template <typename T = QEXTMvvmSessionItem> std::vector<T*> items(const std::string& tag) const;
    std::string tagOfItem(const QEXTMvvmSessionItem* item) const;
    QEXTMvvmTagRow tagRowOfItem(const QEXTMvvmSessionItem* item) const;

    QEXTMvvmItemMapper* mapper();

    bool isEditable() const;
    QEXTMvvmSessionItem* setEditable(bool value);

    bool isEnabled() const;
    QEXTMvvmSessionItem* setEnabled(bool value);

    std::string toolTip() const;
    QEXTMvvmSessionItem* setToolTip(const std::string& tooltip);

    std::string editorType() const;
    QEXTMvvmSessionItem* setEditorType(const std::string& editor_type);

    bool isSinglePropertyTag(const std::string& tag) const;

    template <typename T> T property(const std::string& tag) const;

    template <typename T> void setProperty(const std::string& tag, const T& value);

    void setProperty(const std::string& tag, const char* value);

    // FIXME refactor converter access to item internals
    QEXTMvvmSessionItemData* itemData();
    const QEXTMvvmSessionItemData* itemData() const;

private:
    friend class QEXTMvvmSessionModel;
    friend class QEXTMvvmJsonItemConverter;
    virtual void activate() {}
    bool set_data_internal(QVariant value, int role);
    QVariant data_internal(int role) const;
    void setParent(QEXTMvvmSessionItem* parent);
    void setModel(QEXTMvvmSessionModel* model);
    void setAppearanceFlag(int flag, bool value);

    QEXTMvvmSessionItemTags* itemTags() const;
    void setDataAndTags(std::unique_ptr<QEXTMvvmSessionItemData> data,
                        std::unique_ptr<QEXTMvvmSessionItemTags> tags);

    struct SessionItemImpl;
    std::unique_ptr<SessionItemImpl> p_impl;
};

//! Sets data for given role.

template <typename T> inline bool QEXTMvvmSessionItem::setData(const T& value, int role)
{
    if constexpr (std::is_same<T, QVariant>::value)
        return set_data_internal(value, role);
    return set_data_internal(QVariant::fromValue(value), role);
}

//! Returns data of given type T for given role.

template <typename T> inline T QEXTMvvmSessionItem::data(int role) const
{
    if constexpr (std::is_same<T, QVariant>::value)
        return data_internal(role);
    return data_internal(role).value<T>();
}

//! Returns data stored in property item.
//! Property is single item registered under certain tag via QEXTMvvmCompoundItem::addProperty method.

template <typename T> inline T QEXTMvvmSessionItem::property(const std::string& tag) const
{
    return getItem(tag)->data<T>();
}

//! Sets value to property item.
//! Property is single item registered under certain tag via QEXTMvvmCompoundItem::addProperty method, the
//! value will be assigned to it's data role.

template <typename T> inline void QEXTMvvmSessionItem::setProperty(const std::string& tag, const T& value)
{
    getItem(tag)->setData(value);
}

//! Sets value to property item (specialized for special "const char *" case).
//! Property is single item registered under certain tag via QEXTMvvmCompoundItem::addProperty method, the
//! value will be assigned to it's data role.

inline void QEXTMvvmSessionItem::setProperty(const std::string& tag, const char* value)
{
    setProperty(tag, std::string(value));
}

//! Returns first item under given tag casted to a specified type.
//! Returns nullptr, if item doesn't exist. If item exists but can't be casted will throw.

template <typename T> inline T* QEXTMvvmSessionItem::item(const std::string& tag) const
{
    if (auto item = getItem(tag); item) {
        T* tag_item = dynamic_cast<T*>(item);
        if (!tag_item)
            throw std::runtime_error("Can't cast an item to given type");
        return tag_item;
    }

    return nullptr;
}

//! Returns all items under given tag casted to specific type.

template <typename T> std::vector<T*> QEXTMvvmSessionItem::items(const std::string& tag) const
{
    std::vector<T*> result;
    for (auto item : getItems(tag))
        if (auto casted = dynamic_cast<T*>(item); casted)
            result.push_back(casted);

    return result;
}

} // namespace ModelView

#endif // _QEXTMVVMMODELSESSIONITEM_H
