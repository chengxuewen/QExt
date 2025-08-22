#ifndef _QEXTPEPROPERTY_H
#define _QEXTPEPROPERTY_H

#include <qextWidgetGlobal.h>

#include <QIcon>

class QExtPEAbstractPropertyManager;
class QExtPEAbstractPropertyEditor;

/**
 * @class QExtPEProperty
 * @brief The QExtPEProperty class encapsulates an instance of a property.
 * Properties are created by objects of QExtPEAbstractPropertyManager subclasses; a manager can create properties of a
 * given type, and is used in conjunction with the QExtPEAbstractPropertyEditor class. A property is always owned by the
 * manager that created it, which can be retrieved using the propertyManager() function.
 *
 * QExtPEProperty contains the most common property attributes, and provides functions for retrieving as well as setting
 * their values:
 *
 * @table
 * @header @o Getter @o Setter
 * @raw
 * @o propertyName() @o setPropertyName()
 * @raw
 * @o statusTip() @o setStatusTip()
 * @raw
 * @o toolTip() @o setToolTip()
 * @raw
 * @o whatsThis() @o setWhatsThis()
 * @raw
 * @o isEnabled() @o setEnabled()
 * @raw
 * @o isModified() @o setModified()
 * @raw
 * @o valueText() @o Nop
 * @raw
 * @o valueIcon() @o Nop
 * @endtable
 *
 * It is also possible to nest properties: QExtPEProperty provides the addSubProperty(), insertSubProperty() and
 * removeSubProperty() functions to manipulate the set of subproperties. Use the subProperties() function to retrieve a
 * property's current set of subproperties.
 * Note that nested properties are not owned by the parent property, i.e. each subproperty is owned by the manager that
 * created it.
 * @sa QExtPEAbstractPropertyManager, QExtPEPropertyItem
 */
class QExtPEPropertyPrivate;
class QEXT_WIDGETS_API QExtPEProperty
{
public:
    /**
     * @brief Destroys this property.
     * Note that subproperties are detached but not destroyed, i.e. they can still be used in another context.
     * @sa QExtPEAbstractPropertyManager::clear()
     */
    virtual ~QExtPEProperty();

    /**
     * @brief Returns the set of subproperties.
     * Note that subproperties are not owned by @e this property, but by the manager that created them.
     * @sa insertSubProperty(), removeSubProperty()
     */
    QList<QExtPEProperty *> subProperties() const;

    /**
     * @brief Returns a pointer to the manager that owns this property.
     */
    QExtPEAbstractPropertyManager *propertyManager() const;

    /**
     * @brief Returns the property's  tool tip.
     * @sa setToolTip()
     */
    QString toolTip() const;

    /**
     * @brief Returns the property's status tip.
     * @sa setStatusTip()
     */
    QString statusTip() const;

    /**
     * @brief Returns the property's "What's This" help text.
     * @sa setWhatsThis()
     */
    QString whatsThis() const;

    /**
     * @brief Returns the property's name.
     * @sa setPropertyName()
     */
    QString propertyName() const;

    /**
     * @brief Returns whether the property's style is changed.
     * @sa setStyleChanged()
     */
    bool isStyleChanged() const;

    /**
     * @brief Returns whether the property is enabled.
     * @sa setEnabled()
     */
    bool isEnabled() const;

    /**
     * @brief Returns whether the property is modified.
     * @sa setModified()
     */
    bool isModified() const;

    /**
     * @brief Returns whether the property has a value.
     * @sa QExtPEAbstractPropertyManager::hasValue()
     */
    bool hasValue() const;

    /**
     * @brief Returns an icon representing the current state of this property.
     * If the given property type can not generate such an icon, this function returns an invalid icon.
     * @sa QExtPEAbstractPropertyManager::valueIcon()
     */
    QIcon valueIcon() const;

    /**
     * @brief Returns a string representing the current state of this property.
     * If the given property type can not generate such a string, this function returns an empty string.
     * @sa QExtPEAbstractPropertyManager::valueText()
     */
    QString valueText() const;

    /**
     * @brief Returns the display text according to the echo-mode set on the editor.
     * When the editor is a QLineEdit, this will return a string equal to what is displayed.
     * @sa QExtPEAbstractPropertyManager::valueText()
     */
    QString displayText() const;

    /**
     * @brief Sets the property's tool tip to the given @a text.
     * @sa toolTip()
     */
    void setToolTip(const QString &text);

    /**
     * @brief Sets the property's status tip to the given @a text.
     * @sa statusTip()
     */
    void setStatusTip(const QString &text);

    /**
     * @brief Sets the property's "What's This" help text to the given @a text.
     * @sa whatsThis()
     */
    void setWhatsThis(const QString &text);

    /**
     * @brief Sets the property's  name to the given @a name.
     * @sa propertyName()
     */
    void setPropertyName(const QString &text);

    /**
     * @brief Sets the property's style changed state according to the given @a changed value.
     * @sa isStyleChanged()
     */
    void setStyleChanged(bool changed);

    /**
     * @brief Enables or disables the property according to the passed @a enable value.
     * @sa isEnabled()
     */
    void setEnabled(bool enable);

    /**
     * @brief Sets the property's modified state according to the passed @a modified value.
     * @sa isModified()
     */
    void setModified(bool modified);

    /**
     * @brief Appends the given @a property to this property's subproperties.
     * If the given @a property already is added, this function does nothing.
     * @sa insertSubProperty(), removeSubProperty()
     */
    void addSubProperty(QExtPEProperty *property);

    /**
     * @brief Inserts the given @a property after the specified @a precedingProperty into this property's list of
     * subproperties.  If @a precedingProperty is 0, the specified @a property is inserted at the beginning of the list.
     * If the given @a property already is inserted, this function does nothing.
     * @sa addSubProperty(), removeSubProperty()
     */
    void insertSubProperty(QExtPEProperty *property, QExtPEProperty *afterProperty);

    /**
     * @brief Removes the given @a property from the list of subproperties without deleting it.
     * @sa addSubProperty(), insertSubProperty()
     */
    void removeSubProperty(QExtPEProperty *property);

protected:
    /**
     * @brief Creates a property with the given @a manager.
     * This constructor is only useful when creating a custom QExtPEProperty subclass (e.g. QExtPEVariantProperty).
     * To create a regular QExtPEProperty object, use the QExtPEAbstractPropertyManager::addProperty() function instead.
     * @sa QExtPEAbstractPropertyManager::addProperty()
     */
    explicit QExtPEProperty(QExtPEAbstractPropertyManager *manager);

    void onPropertyChanged();

private:
    friend class QExtPEAbstractPropertyManager;
    QScopedPointer<QExtPEPropertyPrivate> dd_ptr;
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtPEProperty)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPEProperty)
};


/**
 * @brief The QExtPEPropertyItem class represents a property in a property browser instance.
 *
 * Browser items are created whenever a QExtPEProperty is inserted to the property browser. A QExtPEPropertyItem uniquely
 * identifies a browser's item. Thus, if the same QExtPEProperty is inserted multiple times, each occurrence gets its own
 * unique QExtPEPropertyItem. The items are owned by QExtPEAbstractPropertyEditor and automatically deleted when they are
 * removed from the browser.
 *
 * You can traverse a browser's properties by calling parent() and children(). The property and the browser associated
 * with an item are available as property() and browser().
 *
 * @sa QExtPEAbstractPropertyEditor, QExtPEProperty
 */
class QExtPEPropertyItemPrivate;
class QEXT_WIDGETS_API QExtPEPropertyItem
{
public:
    /**
     * @brief Returns the property which is accosiated with this item. Note that several items can be associated with
     * the same property instance in the same property browser.
     *
     * @sa QExtPEAbstractPropertyEditor::items()
     */
    QExtPEProperty *property() const;

    /**
     * @brief Returns the parent item of @e this item. Returns 0 if @e this item is associated with top-level property
     * in item's property browser.
     *
     * @sa children()
     */
    QExtPEPropertyItem *parent() const;

    /**
     * @brief Returns the children items of @e this item. The properties reproduced from children items are always the
     * same as reproduced from associated property' children, for example:
     *
     * @code
     *  QExtPEPropertyItem *item;
     *  QList<QExtPEPropertyItem *> childrenItems = item->children();
     *  QList<QExtPEProperty *> childrenProperties = item->property()->subProperties();
     * @endcode
     *
     * @The @e childrenItems list represents the same list as @e childrenProperties.
     */
    QList<QExtPEPropertyItem *> children() const;

    /**
     * @brief Returns the property browser which owns @e this item.
     */
    QExtPEAbstractPropertyEditor *browser() const;

private:
    QExtPEPropertyItem(QExtPEAbstractPropertyEditor *browser, QExtPEProperty *property, QExtPEPropertyItem *parent);
    virtual ~QExtPEPropertyItem();

    friend class QExtPEAbstractPropertyEditorPrivate;
    QScopedPointer<QExtPEPropertyItemPrivate> dd_ptr;
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtPEPropertyItem)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPEPropertyItem)
};

#endif // QEXTPEPROPERTY_H
