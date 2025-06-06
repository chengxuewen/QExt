#ifndef _QEXTPEPROPERTYTREEEDITOR_H
#define _QEXTPEPROPERTYTREEEDITOR_H

#include <qextPEAbstractPropertyEditor.h>

class QTreeWidget;

/**
 * @class QExtPEPropertyTreeEditor
 * @brief The QExtPEPropertyTreeEditor class provides QTreeWidget based property browser.
 *
 * A property browser is a widget that enables the user to edit a given set of properties. Each property is represented
 * by a label specifying the property's name, and an editing widget (e.g. a line edit or a combobox) holding its value.
 * A property can have zero or more subproperties.
 *
 * QExtPEPropertyTreeEditor provides a tree based view for all nested properties, i.e. properties that have subproperties
 * can be in an expanded (subproperties are visible) or collapsed (subproperties are hidden) state. For example:
 *
 * Use the QExtPEAbstractPropertyEditor API to add, insert and remove properties from an instance of the
 * QExtPEPropertyTreeEditor class.
 * The properties themselves are created and managed by implementations of the QExtPEAbstractPropertyManager class.
 *
 * @sa QExtPEPropertyGroupBoxEditor, QExtPEAbstractPropertyEditor
 */
class QTreeWidgetItem;
class QExtPEPropertyTreeEditorPrivate;
class QEXT_WIDGETS_API QExtPEPropertyTreeEditor : public QExtPEAbstractPropertyEditor
{
    Q_OBJECT
    Q_PROPERTY(int indentation READ indentation WRITE setIndentation)
    Q_PROPERTY(bool rootIsDecorated READ rootIsDecorated WRITE setRootIsDecorated)
    Q_PROPERTY(bool alternatingRowColors READ alternatingRowColors WRITE setAlternatingRowColors)
    Q_PROPERTY(bool headerVisible READ isHeaderVisible WRITE setHeaderVisible)
    Q_PROPERTY(ResizeMode resizeMode READ resizeMode WRITE setResizeMode)
    Q_PROPERTY(int splitterPosition READ splitterPosition WRITE setSplitterPosition)
    Q_PROPERTY(bool propertiesWithoutValueMarked READ propertiesWithoutValueMarked WRITE setPropertiesWithoutValueMarked)

public:
    /**
     * @brief The ResizeMode enum
     *
     * @value Interactive The user can resize the sections.
     * The sections can also be resized programmatically using setSplitterPosition().
     *
     * @value Fixed The user cannot resize the section.
     * The section can only be resized programmatically using setSplitterPosition().
     *
     * @value Stretch QHeaderView will automatically resize the section to fill the available space.
     * The size cannot be changed by the user or programmatically.
     *
     * @value ResizeToContents QHeaderView will automatically resize the section to its optimal size based on the
     * contents of the entire column. The size cannot be changed by the user or programmatically.
     *
     * @sa setResizeMode()
     */
    enum ResizeMode
    {
        Interactive,
        Stretch,
        Fixed,
        ResizeToContents
    };
    Q_ENUMS(ResizeMode)

    /**
     * @brief Creates a property browser with the given @a parent.
     */
    QExtPEPropertyTreeEditor(QWidget *parent = QEXT_NULLPTR);

    /**
     * Destroys this property browser.
     * Note that the properties that were inserted into this browser are @e not destroyed since they may still be used
     * in other browsers. The properties are owned by the manager that created them.
     *
     * @sa QExtPEProperty, QExtPEAbstractPropertyManager
     */
    ~QExtPEPropertyTreeEditor() QEXT_OVERRIDE;

    QTreeWidget *editorView() const;

    int editorViewRowHeight() const;
    void setEditorViewRowHeight(int height);

    /**
     * @brief indentation of the items in the tree view.
     */
    int indentation() const;
    void setIndentation(int i);

    /**
     * @brief whether to show controls for expanding and collapsing root items.
     */
    bool rootIsDecorated() const;
    void setRootIsDecorated(bool show);

    /**
     * @brief whether to draw the background using alternating colors.
     * By default this property is set to true.
     */
    bool alternatingRowColors() const;
    void setAlternatingRowColors(bool enable);

    /**
     * @brief whether to show the header.
     */
    bool isHeaderVisible() const;
    void setHeaderVisible(bool visible);

    /**
     * @brief the resize mode of setions in the header.
     */
    ResizeMode resizeMode() const;
    void setResizeMode(ResizeMode mode);

    /**
     * @brief the position of the splitter between the colunms.
     */
    int splitterPosition() const;
    void setSplitterPosition(int position);

    /**
     * @brief Sets the @a item to either collapse or expanded, depending on the value of @a expanded.
     *
     * @sa isExpanded(), expanded(), collapsed()
     */
    void setExpanded(QExtPEPropertyItem *item, bool expanded);

    /**
     * @brief Returns true if the @a item is expanded; otherwise returns false.
     *
     * @sa setExpanded()
     */
    bool isExpanded(QExtPEPropertyItem *item) const;

    /**
     * @brief Returns true if the @a item is visible; otherwise returns false.
     *
     * @sa setItemVisible()
     */
    bool isItemVisible(QExtPEPropertyItem *item) const;

    /**
     * @brief Sets the @a item to be visible, depending on the value of @a visible.
     *
     * @sa isItemVisible()
     */
    void setItemVisible(QExtPEPropertyItem *item, bool visible);

    /**
     * @brief Sets the @a item's background color to @a color. Note that while item's background is rendered every
     * second row is being drawn with alternate color (which is a bit lighter than items @a color)
     *
     * @sa backgroundColor(), calculatedBackgroundColor()
     */
    void setBackgroundColor(QExtPEPropertyItem *item, const QColor &color);

    /**
     * @brief Returns the @a item's color. If there is no color set for item it returns invalid color.
     *
     * @sa calculatedBackgroundColor(), setBackgroundColor()
     */
    QColor backgroundColor(QExtPEPropertyItem *item) const;

    /**
     * @brief Returns the @a item's color. If there is no color set for item it returns parent @a item's color
     * (if there is no color set for parent it returns grandparent's color and so on).
     * In case the color is not set for @a item and it's top level item it returns invalid color.
     *
     * @sa backgroundColor(), setBackgroundColor()
     */
    QColor calculatedBackgroundColor(QExtPEPropertyItem *item) const;

    /**
     * @brief whether to enable or disable marking properties without value.
     * When marking is enabled the item's background is rendered in dark color and item's foreground is rendered with
     * light color.
     *
     * @sa propertiesWithoutValueMarked()
     */
    void setPropertiesWithoutValueMarked(bool mark);
    bool propertiesWithoutValueMarked() const;

    /**
     * @brief Sets the current item to @a item and opens the relevant editor for it.
     */
    void editItem(QExtPEPropertyItem *item);

Q_SIGNALS:
    /**
     * @brief This signal is emitted when the @a item is collapsed.
     *
     * @sa expanded(), setExpanded()
     */
    void collapsed(QExtPEPropertyItem *item);

    /**
     * @brief This signal is emitted when the @a item is expanded.
     *
     * @sa collapsed(), setExpanded()
     */
    void expanded(QExtPEPropertyItem *item);

protected:
    /**
     * @brief reimp
     */
    void changeEvent(QEvent *event) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void itemRemoved(QExtPEPropertyItem *item) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void itemChanged(QExtPEPropertyItem *item) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void itemInserted(QExtPEPropertyItem *item, QExtPEPropertyItem *afterItem) QEXT_OVERRIDE;

private:
    QExtPEPropertyTreeEditorPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEPropertyTreeEditor)
    QEXT_DISABLE_COPY_MOVE(QExtPEPropertyTreeEditor)

    Q_PRIVATE_SLOT(d_func(), void slotCollapsed(const QModelIndex &))
    Q_PRIVATE_SLOT(d_func(), void slotExpanded(const QModelIndex &))
    Q_PRIVATE_SLOT(d_func(), void slotCurrentBrowserItemChanged(QExtPEPropertyItem *))
    Q_PRIVATE_SLOT(d_func(), void slotCurrentTreeItemChanged(QTreeWidgetItem *, QTreeWidgetItem *))

};

#endif // _QEXTPEPROPERTYTREEEDITOR_H
