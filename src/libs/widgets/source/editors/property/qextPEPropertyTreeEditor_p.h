#ifndef _QEXTPEPROPERTYTREEEDITOR_P_H
#define _QEXTPEPROPERTYTREEEDITOR_P_H

#include <qextPEPropertyTreeEditor.h>

#include <QTreeWidget>
#include <QItemDelegate>

class QExtPEPropertyTreeEditorView : public QTreeWidget
{
    Q_OBJECT
public:
    explicit QExtPEPropertyTreeEditorView(QWidget *parent = QEXT_NULLPTR);
    ~QExtPEPropertyTreeEditorView() QEXT_OVERRIDE {}

    void setEditorPrivate(QExtPEPropertyTreeEditorPrivate *editorPrivate) { m_editorPrivate = editorPrivate; }
    QTreeWidgetItem *indexToItem(const QModelIndex &index) const { return this->itemFromIndex(index); }

    void paintEvent(QPaintEvent *paintEvent) QEXT_OVERRIDE;

protected:
    void keyPressEvent(QKeyEvent *event) QEXT_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) QEXT_OVERRIDE;
    void drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;

private:
    QExtPEPropertyTreeEditorPrivate *m_editorPrivate;
};

class QExtPEPropertyTreeEditorDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    QExtPEPropertyTreeEditorDelegate(QObject *parent = QEXT_NULLPTR)
        : QItemDelegate(parent), m_editorPrivate(0), m_editedItem(0), m_editedWidget(0), m_disablePainting(false)
        , m_itemMinimumHeight(-1)
    {}
    ~QExtPEPropertyTreeEditorDelegate() QEXT_OVERRIDE {}

    void setEditorPrivate(QExtPEPropertyTreeEditorPrivate *editorPrivate) { m_editorPrivate = editorPrivate; }

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;

    void setModelData(QWidget *, QAbstractItemModel *, const QModelIndex &) const QEXT_OVERRIDE {}

    void setEditorData(QWidget *, const QModelIndex &) const QEXT_OVERRIDE {}

    bool eventFilter(QObject *object, QEvent *event) QEXT_OVERRIDE;

    void closeEditor(QExtPEProperty *property);

    QTreeWidgetItem *editedItem() const { return m_editedItem; }

    int itemMinimumHeight() const { return m_itemMinimumHeight; }
    void setItemMinimumHeight(int height) { m_itemMinimumHeight = height; }

protected:
    void drawDecoration(QPainter *painter, const QStyleOptionViewItem &option,
                        const QRect &rect, const QPixmap &pixmap) const QEXT_OVERRIDE;
    void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option,
                     const QRect &rect, const QString &text) const QEXT_OVERRIDE;

private slots:
    void slotEditorDestroyed(QObject *object);

private:
    int indentation(const QModelIndex &index) const;

    typedef QMap<QWidget *, QExtPEProperty *> EditorToPropertyMap;
    mutable EditorToPropertyMap m_editorToProperty;

    typedef QMap<QExtPEProperty *, QWidget *> PropertyToEditorMap;
    mutable PropertyToEditorMap m_propertyToEditor;
    QExtPEPropertyTreeEditorPrivate *m_editorPrivate;
    mutable QTreeWidgetItem *m_editedItem;
    mutable QWidget *m_editedWidget;
    mutable bool m_disablePainting;
    int m_itemMinimumHeight;
};

class QExtPEPropertyTreeEditorView;
class QExtPEPropertyTreeEditorPrivate
{
    QExtPEPropertyTreeEditor *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEPropertyTreeEditor)
public:
    QExtPEPropertyTreeEditorPrivate();

    void init(QWidget *parent);

    void propertyInserted(QExtPEPropertyItem *index, QExtPEPropertyItem *afterIndex);
    void propertyRemoved(QExtPEPropertyItem *index);
    void propertyChanged(QExtPEPropertyItem *index);
    QWidget *createEditor(QExtPEProperty *property, QWidget *parent) const
    { return q_ptr->createEditor(property, parent); }
    QExtPEProperty *indexToProperty(const QModelIndex &index) const;
    QTreeWidgetItem *indexToItem(const QModelIndex &index) const;
    QExtPEPropertyItem *indexToBrowserItem(const QModelIndex &index) const;
    bool lastColumn(int column) const;
    void disableItem(QTreeWidgetItem *item) const;
    void enableItem(QTreeWidgetItem *item) const;
    bool hasValue(QTreeWidgetItem *item) const;

    void slotCollapsed(const QModelIndex &index);
    void slotExpanded(const QModelIndex &index);

    QColor calculatedBackgroundColor(QExtPEPropertyItem *item) const;

    QExtPEPropertyTreeEditorView *treeWidget() const { return m_treeWidget; }
    bool markPropertiesWithoutValue() const { return m_markPropertiesWithoutValue; }

    QExtPEPropertyItem *currentItem() const;
    void setCurrentItem(QExtPEPropertyItem *browserItem, bool block);
    void editItem(QExtPEPropertyItem *browserItem);

    void slotCurrentBrowserItemChanged(QExtPEPropertyItem *item);
    void slotCurrentTreeItemChanged(QTreeWidgetItem *newItem, QTreeWidgetItem *);

    QTreeWidgetItem *editedItem() const;

private:
    void updateItem(QTreeWidgetItem *item);

    QMap<QExtPEPropertyItem *, QTreeWidgetItem *> m_indexToItem;
    QMap<QTreeWidgetItem *, QExtPEPropertyItem *> m_itemToIndex;

    QMap<QExtPEPropertyItem *, QColor> m_indexToBackgroundColor;

    QExtPEPropertyTreeEditorView *m_treeWidget;
    QExtPEPropertyTreeEditorDelegate *m_delegate;

    bool m_headerVisible;
    QExtPEPropertyTreeEditor::ResizeMode m_resizeMode;
    bool m_markPropertiesWithoutValue;
    bool m_browserChangedBlocked;
    QIcon m_expandIcon;
};


#endif // _QEXTPEPROPERTYTREEEDITOR_P_H
