#ifndef _QEXTPEPROPERTYBUTTONEDITOR_H
#define _QEXTPEPROPERTYBUTTONEDITOR_H

#include <qextPEAbstractPropertyEditor.h>

/**
 * @class QExtPEPropertyButtonEditor
 * @brief The QExtPEPropertyButtonEditor class provides a drop down QToolButton based property browser.
 * A property browser is a widget that enables the user to edit a given set of properties. Each property is represented
 * by a label specifying the property's name, and an editing widget (e.g. a line edit or a combobox) holding its value.
 * A property can have zero or more subproperties.
 *
 * QExtPEPropertyButtonEditor provides drop down button for all nested properties, i.e. subproperties are enclosed by a
 * container associated with the drop down button. The parent property's name is displayed as button text. For example:
 *
 * Use the QExtPEAbstractPropertyEditor API to add, insert and remove properties from an instance of the
 * QExtPEPropertyButtonEditor class. The properties themselves are created and managed by implementations of the
 * QExtPEAbstractPropertyManager class.
 *
 * @sa QExtPEPropertyTreeEditor, QExtPEAbstractPropertyEditor
 */
class QExtPEPropertyButtonEditorPrivate;
class QEXT_WIDGETS_API QExtPEPropertyButtonEditor : public QExtPEAbstractPropertyEditor
{
    Q_OBJECT
public:
    /**
     * @brief Creates a property browser with the given @a parent.
     */
    QExtPEPropertyButtonEditor(QWidget *parent = QEXT_NULLPTR);

    /**
     * Destroys this property browser.
     * Note that the properties that were inserted into this browser are @e not destroyed since they may still be used
     * in other browsers. The properties are owned by the manager that created them.
     *
     * @sa QExtPEProperty, QExtPEAbstractPropertyManager
     */
    ~QExtPEPropertyButtonEditor() QEXT_OVERRIDE;

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
    QExtPEPropertyButtonEditorPrivate *dd_ptr;
    Q_DECLARE_PRIVATE(QExtPEPropertyButtonEditor)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPEPropertyButtonEditor)
    Q_PRIVATE_SLOT(d_func(), void slotUpdate())
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed())
    Q_PRIVATE_SLOT(d_func(), void slotToggled(bool))

};

#endif // _QEXTPEPROPERTYBUTTONEDITOR_H
