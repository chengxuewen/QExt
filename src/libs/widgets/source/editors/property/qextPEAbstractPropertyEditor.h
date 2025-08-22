#ifndef _QEXTPEABSTRACTPROPERTYEDITOR_H
#define _QEXTPEABSTRACTPROPERTYEDITOR_H

#include <qextPEProperty.h>
#include <qextPEWidgetFactory.h>

#include <QIcon>
#include <QWidget>

class QTreeWidget;

/**
 * @brief QExtPEAbstractPropertyEditor provides a base class for implementing property browsers.
 *
 * A property browser is a widget that enables the user to edit a given set of properties.  Each property is represented
 * by a label specifying the property's name, and an editing widget (e.g. a line edit or a combobox) holding its value.
 * A property can have zero or more subproperties.
 *
 * @image qtpropertybrowser.png
 *
 * The top level properties can be retrieved using the properties() function. To traverse each property's subproperties,
 * use the QExtPEProperty::subProperties() function. In addition, the set of top level properties can be manipulated using
 * the addProperty(), insertProperty() and removeProperty() functions. Note that the QExtPEProperty class provides a
 * corresponding set of functions making it possible to manipulate the set of subproperties as well.
 *
 * To remove all the properties from the property browser widget, use the clear() function. This function will clear the
 * editor, but it will not delete the properties since they can still be used in other editors.
 *
 * The properties themselves are created and managed by implementations of the QExtPEAbstractPropertyManager class.
 * A manager can handle (i.e. create and manage) properties of a given type. In the property browser the managers are
 * associated with implementations of the QExtPEAbstractWidgetFactory: A factory is a class able to create an editing
 * widget of a specified type.
 *
 * When using a property browser widget, managers must be created for each of the required property types before the
 * properties themselves can be created. To ensure that the properties' values will be displayed using suitable editing
 * widgets, the managers must be associated with objects of the preferred factory implementations using the
 * setFactoryForManager() function. The property browser will use these associations to determine which factory it
 * should use to create the preferred editing widget.
 *
 * Note that a factory can be associated with many managers, but a manager can only be associated with one single factory
 * within the context of a single property browser.  The associations between managers and factories can at any time be
 * removed using the unsetFactoryForManager() function.
 *
 * Whenever the property data changes or a property is inserted or removed, the itemChanged(), itemInserted() or
 * itemRemoved() functions are called, respectively. These functions must be reimplemented in derived classes in order to
 * update the property browser widget. Be aware that some property instances can appear several times in an abstract tree
 * structure. For example:
 *
 * @table 100%
 *  @row
 *  @o
 *  @code
 *      QExtPEProperty *property1, *property2, *property3;
 *
 *      property2->addSubProperty(property1);
 *      property3->addSubProperty(property2);
 *
 *      QExtPEAbstractPropertyEditor *editor;
 *
 *      editor->addProperty(property1);
 *      editor->addProperty(property2);
 *      editor->addProperty(property3);
 *  @endcode
 *  @o  @image qtpropertybrowser-duplicate.png
 * @endtable
 *
 * The addProperty() function returns a QExtPEPropertyItem that uniquely identifies the created item.
 * To make a property editable in the property browser, the createEditor() function must be called to provide the
 * property with a suitable editing widget.
 *
 * Note that there are two ready-made property browser implementations:
 *
 * @list
 *  @o QExtPEPropertyGroupBoxEditor
 *  @o QExtPEPropertyTreeEditor
 * @endlist
 *
 * @sa QExtPEAbstractPropertyManager, QExtPEAbstractWidgetFactoryBase
 */
class QExtPEAbstractPropertyEditorPrivate;
class QEXT_WIDGETS_API QExtPEAbstractPropertyEditor : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Creates an abstract property browser with the given @a parent.
     */
    explicit QExtPEAbstractPropertyEditor(QWidget *parent = QEXT_NULLPTR);

    /**
     * @brief Destroys the property browser, and destroys all the items that were created by this property browser.
     *
     * Note that the properties that were displayed in the editor are not deleted since they still can be used in other
     * editors. Neither does the destructor delete the property managers and editor factories that were used by this
     * property browser widget unless this widget was their parent.
     *
     * @sa QExtPEAbstractPropertyManager::~QExtPEAbstractPropertyManager()
     */
    ~QExtPEAbstractPropertyEditor() QEXT_OVERRIDE;

    /**
     * @brief Removes all the properties from the editor, but does not delete them since they can still be used in
     * other editors.
     *
     * @sa removeProperty(), QExtPEAbstractPropertyManager::clear()
     */
    void clear();

    /**
     * @brief Returns the property browser's list of top level properties.
     * To traverse the subproperties, use the QExtPEProperty::subProperties() function.
     *
     * @sa addProperty(), insertProperty(), removeProperty()
     */
    QList<QExtPEProperty *> properties() const;

    /**
     * @brief Returns the list of top-level items.
     *
     * @sa topLevelItem()
     */
    QList<QExtPEPropertyItem *> topLevelItems() const;

    /**
     * @brief Returns the property browser's list of all items associated with the given @a property.
     * There is one item per instance of the property in the browser.
     *
     * @sa topLevelItem()
     */
    QList<QExtPEPropertyItem *> items(QExtPEProperty *property) const;

    /**
     * @brief Returns the top-level items associated with the given @a property.
     *
     * Returns 0 if @a property wasn't inserted into this property browser or isn't a top-level one.
     *
     * @sa topLevelItems(), items()
     */
    QExtPEPropertyItem *topLevelItem(QExtPEProperty *property) const;

    /**
     * @brief Connects the given @a manager to the given @a factory, ensuring that properties of the @a manager's type
     * will be displayed with an editing widget suitable for their value.
     *
     * For example:
     *
     * @code
     *  QExtPEIntPropertyManager *intManager;
     *  QExtPEDoublePropertyManager *doubleManager;
     *
     *  QExtPEProperty *myInteger = intManager->addProperty();
     *  QExtPEProperty *myDouble = doubleManager->addProperty();
     *
     *  QExtPESpinBoxFactory  *spinBoxFactory;
     *  QExtPEDoubleSpinBoxFactory *doubleSpinBoxFactory;
     *
     *  QExtPEAbstractPropertyEditor *editor;
     *  editor->setFactoryForManager(intManager, spinBoxFactory);
     *  editor->setFactoryForManager(doubleManager, doubleSpinBoxFactory);
     *
     *  editor->addProperty(myInteger);
     *  editor->addProperty(myDouble);
     * @endcode
     *
     * In this example the @c myInteger property's value is displayed with a QSpinBox widget, while the @c myDouble
     * property's value is displayed with a QDoubleSpinBox widget.
     *
     * Note that a factory can be associated with many managers, but a manager can only be associated with one single
     * factory.  If the given @a manager already is associated with another factory, the old association is broken before
     * the new one established.
     *
     * This function ensures that the given @a manager and the given @a factory are compatible, and it automatically
     * calls the QExtPEAbstractWidgetFactory::addPropertyManager() function if necessary.
     *
     * @sa unsetFactoryForManager()
     */
    template <class PropertyManager>
    void setFactoryForManager(PropertyManager *manager, QExtPEAbstractWidgetFactory<PropertyManager> *factory)
    {
        QExtPEAbstractPropertyManager *abstractManager = manager;
        QExtPEAbstractWidgetFactoryBase *abstractFactory = factory;
        if (this->addFactory(abstractManager, abstractFactory))
        {
            factory->addPropertyManager(manager);
        }
    }

    /**
     * @brief Removes the association between the given @a manager and the factory bound to it, automatically calling the
     * QExtPEAbstractWidgetFactory::removePropertyManager() function if necessary.
     *
     * @sa setFactoryForManager()
     */
    void unsetFactoryForManager(QExtPEAbstractPropertyManager *manager);

    /**
     * @brief Returns the current item in the property browser.
     *
     * @sa setCurrentItem()
     */
    QExtPEPropertyItem *currentItem() const;

    /**
     * @brief Sets the current item in the property browser to @a item.
     *
     * @sa currentItem(), currentItemChanged()
     */
    void setCurrentItem(QExtPEPropertyItem *);

Q_SIGNALS:
    void currentItemChanged(QExtPEPropertyItem *);

public Q_SLOTS:
    /**
     * @brief Removes the specified @a property (and its subproperties) from the property browser's list of top level
     * properties. All items that were associated with the given @a property and its children are deleted.
     *
     * Note that the properties are @e not deleted since they can still be used in other editors.
     *
     * @sa clear(), QExtPEProperty::removeSubProperty(), properties()
     */
    void removeProperty(QExtPEProperty *property);

    /**
     * @brief Appends the given @a property (and its subproperties) to the property browser's list of top level properties.
     * Returns the item created by property browser which is associated with the @a property.
     * In order to get all children items created by the property browser in this call, the returned item should be traversed.
     *
     * If the specified @a property is already added, this function does nothing and returns 0.
     *
     * @sa insertProperty(), QExtPEProperty::addSubProperty(), properties()
     */
    QExtPEPropertyItem *addProperty(QExtPEProperty *property);

    /**
     * @brief Inserts the given @a property (and its subproperties) after the specified @a afterProperty in the browser's
     * list of top level properties. Returns item created by property browser which is associated with the @a property.
     * In order to get all children items created by the property browser in this call returned item should be traversed.
     *
     * If the specified @a afterProperty is 0, the given @a property is inserted at the beginning of the list.
     * If @a property is already inserted, this function does nothing and returns 0.
     *
     * @sa addProperty(), QExtPEProperty::insertSubProperty(), properties()
     */
    QExtPEPropertyItem *insertProperty(QExtPEProperty *property, QExtPEProperty *afterProperty);

protected:
    /**
     * @brief This function is called to update the widget whenever a property is removed from the property browser,
     * passing the pointer to the @a item of the property as parameters. The passed @a item is deleted just after this
     * call is finished.
     *
     * If the the parent of @a item is 0, the removed @a item was a top level property in this editor.
     *
     * This function must be reimplemented in derived classes. Note that if the removed @a item's property has
     * subproperties, this method will be called for those properties just before the current call is started.
     *
     * @sa removeProperty()
     */
    virtual void itemRemoved(QExtPEPropertyItem *item) = 0;

    /**
     * @brief This function is called whenever a property's data changes, passing a pointer to the @a item of property
     * as parameter.
     *
     * This function must be reimplemented in derived classes in order to update the property browser widget whenever a
     * property's name, tool tip, status tip, "what's this" text, value text or value icon changes.
     *
     * Note that if the property browser contains several occurrences of the same property, this method will be called
     * once for each occurrence (with a different item each time).
     *
     * @sa QExtPEProperty, items()
     * @note can be tooltip, statustip, whatsthis, name, icon, text.
     */
    virtual void itemChanged(QExtPEPropertyItem *item) = 0;

    /**
     * @brief Creates an editing widget (with the given @a parent) for the given @a property according to the previously
     * established associations between property managers and editor factories.
     *
     * If the property is created by a property manager which was not associated with any of the existing factories in
     * @e this property editor, the function returns 0.
     *
     * To make a property editable in the property browser, the createEditor() function must be called to provide the
     * property with a suitable editing widget.
     *
     * Reimplement this function to provide additional decoration for the editing widgets created by the installed factories.
     *
     * @sa setFactoryForManager()
     */
    virtual QWidget *createEditor(QExtPEProperty *property, QWidget *parent);

    /**
     * @brief This function is called to update the widget whenever a property is inserted or added to the property
     * browser, passing pointers to the @a insertedItem of property and the specified @a precedingItem as parameters.
     *
     * If @a precedingItem is 0, the @a insertedItem was put at the beginning of its parent item's list of subproperties.
     * If the parent of @a insertedItem is 0, the @a insertedItem was added as a top level property of @e this property
     * browser.
     *
     * This function must be reimplemented in derived classes. Note that if the @a insertedItem's property has
     * subproperties, this method will be called for those properties as soon as the current call is finished.
     *
     * @sa insertProperty(), addProperty()
     */
    virtual void itemInserted(QExtPEPropertyItem *item, QExtPEPropertyItem *afterItem) = 0;

private:
    bool addFactory(QExtPEAbstractPropertyManager *abstractManager, QExtPEAbstractWidgetFactoryBase *abstractFactory);

    QScopedPointer<QExtPEAbstractPropertyEditorPrivate> dd_ptr;
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtPEAbstractPropertyEditor)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPEAbstractPropertyEditor)

    Q_PRIVATE_SLOT(d_func(), void slotPropertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyRemoved(QExtPEProperty *, QExtPEProperty *))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtPEProperty *))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDataChanged(QExtPEProperty *))
};


#endif // _QEXTPEABSTRACTPROPERTYEDITOR_H
