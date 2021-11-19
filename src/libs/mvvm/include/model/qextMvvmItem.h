#ifndef _QEXTMVVMITEM_H
#define _QEXTMVVMITEM_H

#include <qextMvvmConstants.h>
#include <qextMvvmTagRow.h>
#include <qextMvvmGlobal.h>
#include <qextMvvmTypes.h>
#include <qextMvvmUtils.h>

#include <QVector>
#include <QVariant>
#include <QSharedPointer>

class QEXTMvvmModel;
class QEXTMvvmTagInfo;
class QEXTMvvmItemMapper;
class QEXTMvvmItemTags;
class QEXTMvvmItemData;

class QEXTMvvmItemPrivate;
class QEXT_MVVM_API QEXTMvvmItem
{
public:
    enum ItemRoleType
    {
        Role_Identifier = 0,    // unique identifier
        Role_Data,              // main data role
        Role_Display,           // display name
        Role_Appearance,        // appearance flag
        Role_Limits,            // possibly limits on item's data
        Role_ToolTip,           // tooltip for item's data
        Role_Editor             // type of custom editor for the data role
    };

    explicit QEXTMvvmItem(const QString &modelType = QEXTMvvmConstants::BaseType);
    virtual ~QEXTMvvmItem();

    QString modelType() const;

    virtual QString displayName() const;
    virtual QEXTMvvmItem *setDisplayName(const QString &name);

    QString identifier() const;

    template <typename T> bool setData(const T &value, int role = QEXTMvvmItem::Role_Data);
    bool setDataIntern(const QVariant &variant, int role);

    bool hasData(int role = QEXTMvvmItem::Role_Data) const;
    template <typename T> T data(int role = QEXTMvvmItem::Role_Data) const;
    QVector<int> roles() const;

    QEXTMvvmItemMapper* mapper();
    QEXTMvvmModel *model() const;
    QEXTMvvmItem *parent() const;

    int childrenCount() const;
    QVector<QEXTMvvmItem *> children() const;

    bool insertItem(QEXTMvvmItem *item, const QEXTMvvmTagRow &tagrow);
    QEXTMvvmItem *takeItem(const QEXTMvvmTagRow &tagrow);

    // tags
    QString defaultTag() const;
    void setDefaultTag(const QString &tag);

    void registerTag(const QEXTMvvmTagInfo &tagInfo, bool setAsDefault = false);
    bool isTag(const QString &name) const;
    QString tag() const;
    QEXTMvvmTagRow tagRow() const;

    // access tagged items
    int itemCount(const QString &tag) const;

    template <typename T> T* item(const QString &tag) const;
    QEXTMvvmItem *item(const QString &tag, int row = 0) const; // FIXME QEXTMvvmTagRow?

    template <typename T> QVector<T *> items(const QString &tag) const;
    QVector<QEXTMvvmItem *> items(const QString &tag) const;

    QString tagOfItem(QEXTMvvmItem *item) const;
    QEXTMvvmTagRow tagRowOfItem(QEXTMvvmItem *item) const;

    bool isEditable() const;
    QEXTMvvmItem* setEditable(bool value);

    bool isEnabled() const;
    QEXTMvvmItem* setEnabled(bool value);

    QString toolTip() const;
    QEXTMvvmItem* setToolTip(const QString &tooltip);

    QString editorType() const;
    QEXTMvvmItem* setEditorType(const QString &editorType);

    bool isSinglePropertyTag(const QString &tag) const;

    template <typename T> T property(const QString &tag) const;
    template <typename T> void setProperty(const QString &tag, const T &value);

    void setProperty(const QString &tag, const char *value);

    // FIXME refactor converter access to item internals
    QEXTMvvmItemData *itemData();
    const QEXTMvvmItemData *itemData() const;

protected:
    virtual void activate() {}

    QVariant dataInternal(int role) const;
    bool setDataInternal(QVariant value, int role);

    void setParent(QEXTMvvmItem *parent);
    void setModel(QEXTMvvmModel *model);
    void setAppearanceFlag(int flag, bool value);

    QEXTMvvmItemTags *itemTags() const;
    void setDataAndTags(QEXTMvvmItemData *data, QEXTMvvmItemTags *tags);

    QScopedPointer<QEXTMvvmItemPrivate> d_ptr;

private:
    friend class QEXTMvvmModel;
    friend class QEXTMvvmJsonItemConverter;
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmItem)
    Q_DECLARE_PRIVATE(QEXTMvvmItem)
};

//! Sets data for given role.

template <typename T> inline bool QEXTMvvmItem::setData(const T& value, int role)
{
    if constexpr (std::is_same<T, QVariant>::value)
            return setDataInternal(value, role);
    return setDataInternal(QVariant::fromValue(value), role);
}

//! Returns data of given type T for given role.

template <typename T> inline T QEXTMvvmItem::data(int role) const
{
    if constexpr (std::is_same<T, QVariant>::value)
            return dataInternal(role);
    return dataInternal(role).value<T>();
}

//! Returns data stored in property item.
//! Property is single item registered under certain tag via QEXTMvvmCompoundItem::addProperty method.

template <typename T> inline T QEXTMvvmItem::property(const QString &tag) const
{
    return this->item(tag)->data<T>();
}

//! Sets value to property item.
//! Property is single item registered under certain tag via QEXTMvvmCompoundItem::addProperty method, the
//! value will be assigned to it's data role.

template <typename T> inline void QEXTMvvmItem::setProperty(const QString &tag, const T &value)
{
    this->item(tag)->setData(value);
}

//! Sets value to property item (specialized for special "const char *" case).
//! Property is single item registered under certain tag via QEXTMvvmCompoundItem::addProperty method, the
//! value will be assigned to it's data role.

inline void QEXTMvvmItem::setProperty(const QString &tag, const char* value)
{
    setProperty(tag, QString(value));
}

//! Returns first item under given tag casted to a specified type.
//! Returns nullptr, if item doesn't exist. If item exists but can't be casted will throw.

template <typename T> inline T *QEXTMvvmItem::item(const QString &tag) const
{
    QEXTMvvmItem *item = this->item(tag);
    if (item)
    {
        T *tagItem = dynamic_cast<T *>(item);
        if (!tagItem)
        {
            throw std::runtime_error("Can't cast an item to given type");
        }
        return tagItem;
    }
    return QEXT_DECL_NULLPTR;
}

//! Returns all items under given tag casted to specific type.

template <typename T> QVector<T *> QEXTMvvmItem::items(const QString &tag) const
{
    QVector<T*> result;
    QVector<QEXTMvvmItem *> itemVector = this->items(tag);
    for (int i = 0; i < itemVector.size(); ++i)
    {
        QEXTMvvmItem *item = itemVector.at(i);
        T *casted = dynamic_cast<T*>(item);
        if (casted)
        {
            result.append(casted);
        }
    }
    return result;
}


#endif // _QEXTMVVMITEM_H
