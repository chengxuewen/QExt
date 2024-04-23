#ifndef _QEXTPROPERTYMODEL_H
#define _QEXTPROPERTYMODEL_H

#include <qextWidgetGlobal.h>

#include <QList>
#include <QObject>
#include <QAbstractItemModel>
#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>

class QEXT_WIDGETS_API QExtPropertyModelItem : public QObject
{
    Q_OBJECT
public:
    enum EditorEnum
    {
        Editor_Default = 0,
        Editor_SpinBox,
        Editor_ComboBox,
        Editor_LineEdit,
        Editor_DoubleSpinBox,
        Editor_Custom
    };
    QEXT_STATIC_CONSTANT(int, EditorEnumNum = 6);

    QExtPropertyModelItem();
    ~QExtPropertyModelItem() QEXT_OVERRIDE;

    int childrenCount() const;
    int childIndexOf(QExtPropertyModelItem *child) const;
    QExtPropertyModelItem *child(int index) const;
    QList<QExtPropertyModelItem *> childrenList() const;
    void appendChild(QExtPropertyModelItem *child);
    void appendChildren(const QList<QExtPropertyModelItem *> &children);
    void removeChild(QExtPropertyModelItem *child);

    QExtPropertyModelItem *parent() const;
    void setParent(QExtPropertyModelItem *parent);

    bool isEnabled() const;
    void setEnable(bool enable);

    virtual QString name() const = 0;
    virtual Qt::ItemFlags flags() const = 0;
    virtual EditorEnum editorType() const { return Editor_Default; }

    virtual QVariant data(int role = Qt::DisplayRole) const;
    virtual bool setData(const QVariant &value, int role = Qt::EditRole);

    virtual bool setEditorData(QWidget *editor, const QModelIndex &index) const;
    virtual bool setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index, const QSize &baseSize) const;
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual QWidget *initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    virtual bool paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual bool destroyEditor(QWidget *editor, const QModelIndex &index) const;

    static QList<QExtPropertyModelItem *> allSubItems(QExtPropertyModelItem *item);

signals:
    void beginResetModel();
    void endResetModel();

    void requestClosedEditor(QWidget *editor);

    void itemDataChanged(QExtPropertyModelItem *item);

    void childAboutToBeAppended(QExtPropertyModelItem *child);
    void childAppended(QExtPropertyModelItem *child);

    void childAboutToBeRemoveed(QExtPropertyModelItem *child);
    void childRemoveed(QExtPropertyModelItem *child);

protected:
    bool m_enable;
    QExtPropertyModelItem *m_parent;
    QList<QExtPropertyModelItem *> m_childrenList;
};

class QEXT_WIDGETS_API QExtPropertyModelRootItem : public QExtPropertyModelItem
{
public:
    QExtPropertyModelRootItem() {}
    ~QExtPropertyModelRootItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE { return "root"; }
    Qt::ItemFlags flags() const QEXT_OVERRIDE { return  Qt::NoItemFlags; }

    QVariant data(int /*role*/ = Qt::DisplayRole) const QEXT_OVERRIDE { return QVariant(); }
    bool setData(const QVariant &/*value*/, int /*role*/ = Qt::EditRole) QEXT_OVERRIDE { return true; }
};

class QExtPropertyModelItem;
class QExtPropertyModelPrivate;
class QEXT_WIDGETS_API QExtPropertyModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum { ItemRole = Qt::UserRole + 0x0FFFFFFF };

    enum ColumnEnum
    {
        Column_Property = 0,
        Column_Value,
    };
    QEXT_STATIC_CONSTANT(int, ColumnNum = 2);

    QExtPropertyModel(QObject *parent = QEXT_NULLPTR);
    ~QExtPropertyModel() QEXT_OVERRIDE;

    // implemented from QAbstractItemModel
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const QEXT_OVERRIDE;
    QModelIndex parent(const QModelIndex &child) const QEXT_OVERRIDE;

    int rowCount(const QModelIndex &parent = QModelIndex()) const QEXT_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const QEXT_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const QEXT_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const QEXT_OVERRIDE;

    QModelIndex indexFromItem(QExtPropertyModelItem *item) const;
    QExtPropertyModelItem *itemFromIndex(const QModelIndex &index) const;

    QExtPropertyModelItem *rootItem() const;
    void setRootItem(QExtPropertyModelItem *item);

    static QString columnEnumString(int type, bool isEng = false);

public slots:
    void updateModel();
    void resetModel();

    void onItemDataChanged(QExtPropertyModelItem *item);
    void onBeginResetModel();
    void onEndResetModel();

protected:
    QScopedPointer<QExtPropertyModelPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtPropertyModel)
    QEXT_DISABLE_COPY_MOVE(QExtPropertyModel)
};

class QEXT_WIDGETS_API QExtPropertyDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit QExtPropertyDelegate(QObject *parent = QEXT_NULLPTR);
    QExtPropertyDelegate(QExtPropertyModelItem *rootItem, QObject *parent = QEXT_NULLPTR);
    ~QExtPropertyDelegate() QEXT_OVERRIDE;

    void setRootItem(QExtPropertyModelItem *rootItem);
    QExtPropertyModelItem *rootItem() const;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;
    void destroyEditor(QWidget *editor, const QModelIndex &index) const QEXT_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const QEXT_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const QEXT_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;

protected Q_SLOTS:
    void updateItemMap();
    void closeItemEditor(QWidget *editor);

protected:
    bool helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index) QEXT_OVERRIDE;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) QEXT_OVERRIDE;

    QExtPropertyModelItem *m_rootItem;
    QHash<qulonglong, QExtPropertyModelItem *> m_itemMap;
};

#endif // _QEXTPROPERTYMODEL_H
