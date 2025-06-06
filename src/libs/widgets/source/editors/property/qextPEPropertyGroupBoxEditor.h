#ifndef _QEXTPEPROPERTYGROUPBOXEDITOR_H
#define _QEXTPEPROPERTYGROUPBOXEDITOR_H

#include <qextPEAbstractPropertyEditor.h>

/**
 * @class QExtPEPropertyGroupBoxEditor
 * @brief The QExtPEPropertyGroupBoxEditor class provides a QGroupBox based property browser.
 * A property browser is a widget that enables the user to edit a given set of properties. Each property is represented
 * by a label specifying the property's name, and an editing widget (e.g. a line edit or a combobox) holding its value.
 * A property can have zero or more subproperties.
 *
 * QExtPEPropertyGroupBoxEditor provides group boxes for all nested properties, i.e. subproperties are enclosed by a
 * group box with the parent property's name as its title. For example:
 *
 * Use the QExtPEAbstractPropertyEditor API to add, insert and remove properties from an instance of the
 * QExtPEPropertyGroupBoxEditor class. The properties themselves are created and managed by implementations of the
 * QExtPEAbstractPropertyManager class.
 *
 * @sa QExtPEPropertyTreeEditor, QExtPEAbstractPropertyEditor
 */
class QExtPEPropertyGroupBoxEditorPrivate;
class QEXT_WIDGETS_API QExtPEPropertyGroupBoxEditor : public QExtPEAbstractPropertyEditor
{
    Q_OBJECT

public:
    /**
     * @brief Creates a property browser with the given @a parent.
     */
    QExtPEPropertyGroupBoxEditor(QWidget *parent = QEXT_NULLPTR);

    /**
     * Destroys this property browser.
     * Note that the properties that were inserted into this browser are @e not destroyed since they may still be used
     * in other browsers. The properties are owned by the manager that created them.
     *
     * @sa QExtPEProperty, QExtPEAbstractPropertyManager
     */
    ~QExtPEPropertyGroupBoxEditor() QEXT_OVERRIDE;

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
    QExtPEPropertyGroupBoxEditorPrivate *dd_ptr;
    Q_DECLARE_PRIVATE(QExtPEPropertyGroupBoxEditor)
    QEXT_DISABLE_COPY_MOVE(QExtPEPropertyGroupBoxEditor)
    Q_PRIVATE_SLOT(d_func(), void slotUpdate())
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed())
};

#endif // _QEXTPEPROPERTYGROUPBOXEDITOR_H
