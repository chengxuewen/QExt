#ifndef QEXTMVVMITEM_H
#define QEXTMVVMITEM_H

#include <qextmvvmglobal.h>
#include <qextmvvmtagrow.h>

#include <qextobject.h>

#include <QList>
#include <QVariant>



class QEXTMvvmModel;
class QEXTMvvmTagRow;
class QEXTMvvmTagInfo;
class QEXTMvvmItemData;
class QEXTMvvmItemTags;
class QEXTMvvmItemMapper;
class QEXTMvvmItemPrivate;
class QEXT_MVVM_API QEXTMvvmItem : public QEXTObject
{
public:
    enum RoleType {
        Role_Identifier = 0,
        Role_Data,
        Role_Display,
        Role_Appearance,
        Role_Limits,
        Role_Tooltip,
        Role_Editor
    };

    QEXTMvvmItem(const QString &modelType = "QEXTMvvmItem");
    virtual ~QEXTMvvmItem();

    QString modelType() const;
    QString identifier() const;

    virtual QString displayName() const;
    virtual QEXTMvvmItem *setDisplayName(const QString &name);

    QEXTMvvmModel *model() const;
    QEXTMvvmItem *parent() const;
    QEXTMvvmItemMapper *mapper() const;

    int childrenCount() const;
    QList<QEXTMvvmItem *> children() const;

    // tags
    QString defaultTag() const;
    void setDefaultTag(const QString &tag);
    void registerTag(const QEXTMvvmTagInfo &tagInfo, bool set_as_default = false);
    bool isTag(const QString &name) const;
    QString tag() const;
    QEXTMvvmTagRow tagRow() const;

    // access tagged items
    int itemCount(const QString &tag) const;
    QEXTMvvmItem *getItem(const QString &tag, int row = 0) const; // FIXME TagRow?
    QList<QEXTMvvmItem *> getItems(const QString &tag) const;
    QString tagOfItem(const QEXTMvvmItem *item) const;
    QEXTMvvmTagRow tagRowOfItem(const QEXTMvvmItem *item) const;
    bool insertItem(QEXTMvvmItem *item, const QEXTMvvmTagRow &tagrow);
    QEXTMvvmItem *takeItem(const QEXTMvvmTagRow &tagrow);
    template <typename T> T* item(const QString &tag) const;
    template <typename T = QEXTMvvmItem> QList<T*> items(const QString &tag) const;

    QVector<int> roles() const;

    bool hasData(int role = Role_Data) const;
    QEXTMvvmItemData *itemData() const;
    template <typename T> T data(int role = Role_Data) const;
    template <typename T> bool setData(const T &value, int role = Role_Data);

    bool isEditable() const;
    QEXTMvvmItem *setEditable(bool value);

    bool isEnabled() const;
    QEXTMvvmItem *setEnabled(bool value);

    QString toolTip() const;
    QEXTMvvmItem *setToolTip(const QString &tooltip);

    QString editorType() const;
    QEXTMvvmItem *setEditorType(const QString &editor_type);

    bool isSinglePropertyTag(const QString &tag) const;
    template <typename T> T property(const QString &tag) const;
    template <typename T> void setProperty(const QString &tag, const T &value);
    void setProperty(const QString &tag, const char *value);

private:
private:
    friend class QEXTMvvmModel;

    virtual void activate() {}

    bool set_data_internal(QVariant value, int role);
    QVariant data_internal(int role) const;
    void setParent(QEXTMvvmItem *parent);
    void setModel(QEXTMvvmModel *model);
    void setAppearanceFlag(int flag, bool value);

    QEXTMvvmItemTags *itemTags() const;
    void setDataAndTags(QEXTMvvmItemData *data, QEXTMvvmItemTags *tags);

    QEXT_DECLARE_PRIVATE(QEXTMvvmItem)
    QEXT_DISABLE_COPY_MOVE(QEXTMvvmItem)
};

template<typename T>
qext::QEXTMvvmItem::T *QEXTMvvmItem::item<T>(const QString &tag) const
{

}

template<typename T>
QList<qext::QEXTMvvmItem::T *> QEXTMvvmItem::items<T>(const QString &tag) const
{

}


template<typename T>
qext::QEXTMvvmItem::T QEXTMvvmItem::data<T>(int role) const
{

}

template<typename T>
bool QEXTMvvmItem::setData<T>(const qext::QEXTMvvmItem::T &value, int role)
{

}

template<typename T>
qext::QEXTMvvmItem::T QEXTMvvmItem::property<T>(const QString &tag) const
{

}

template<typename T>
void QEXTMvvmItem::setProperty<T>(const QString &tag, const qext::QEXTMvvmItem::T &value)
{

}



#endif // QEXTMVVMITEM_H
