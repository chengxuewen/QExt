#ifndef _QEXTPROPERTYBROWSER_H
#define _QEXTPROPERTYBROWSER_H

#include <qextWidgetGlobal.h>

#include <QSet>
#include <QIcon>
#include <QWidget>
#include <QLineEdit>

typedef QLineEdit::EchoMode EchoMode;

class QDate;
class QTime;
class QDateTime;
class QLocale;

/**
 * @class QExtProperty
 * @brief The QExtProperty class encapsulates an instance of a property.
 * Properties are created by objects of QExtAbstractPropertyManager subclasses; a manager can create properties of a
 * given type, and is used in conjunction with the QExtAbstractPropertyBrowser class. A property is always owned by the
 * manager that created it, which can be retrieved using the propertyManager() function.
 *
 * QExtProperty contains the most common property attributes, and provides functions for retrieving as well as setting
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
 * It is also possible to nest properties: QExtProperty provides the addSubProperty(), insertSubProperty() and
 * removeSubProperty() functions to manipulate the set of subproperties. Use the subProperties() function to retrieve a
 * property's current set of subproperties.
 * Note that nested properties are not owned by the parent property, i.e. each subproperty is owned by the manager that
 * created it.
 * @sa QExtAbstractPropertyManager, QExtBrowserItem
 */
class QExtAbstractPropertyManager;
class QExtPropertyPrivate;
class QEXT_WIDGETS_API QExtProperty
{
public:
    /**
     * @brief Destroys this property.
     * Note that subproperties are detached but not destroyed, i.e. they can still be used in another context.
     * @sa QExtAbstractPropertyManager::clear()
     */
    virtual ~QExtProperty();

    /**
     * @brief Returns the set of subproperties.
     * Note that subproperties are not owned by @e this property, but by the manager that created them.
     * @sa insertSubProperty(), removeSubProperty()
     */
    QList<QExtProperty *> subProperties() const;

    /**
     * @brief Returns a pointer to the manager that owns this property.
     */
    QExtAbstractPropertyManager *propertyManager() const;

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
     * @sa QExtAbstractPropertyManager::hasValue()
     */
    bool hasValue() const;

    /**
     * @brief Returns an icon representing the current state of this property.
     * If the given property type can not generate such an icon, this function returns an invalid icon.
     * @sa QExtAbstractPropertyManager::valueIcon()
     */
    QIcon valueIcon() const;

    /**
     * @brief Returns a string representing the current state of this property.
     * If the given property type can not generate such a string, this function returns an empty string.
     * @sa QExtAbstractPropertyManager::valueText()
     */
    QString valueText() const;

    /**
     * @brief Returns the display text according to the echo-mode set on the editor.
     * When the editor is a QLineEdit, this will return a string equal to what is displayed.
     * @sa QExtAbstractPropertyManager::valueText()
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
    void addSubProperty(QExtProperty *property);

    /**
     * @brief Inserts the given @a property after the specified @a precedingProperty into this property's list of
     * subproperties.  If @a precedingProperty is 0, the specified @a property is inserted at the beginning of the list.
     * If the given @a property already is inserted, this function does nothing.
     * @sa addSubProperty(), removeSubProperty()
     */
    void insertSubProperty(QExtProperty *property, QExtProperty *afterProperty);

    /**
     * @brief Removes the given @a property from the list of subproperties without deleting it.
     * @sa addSubProperty(), insertSubProperty()
     */
    void removeSubProperty(QExtProperty *property);

protected:
    /**
     * @brief Creates a property with the given @a manager.
     * This constructor is only useful when creating a custom QExtProperty subclass (e.g. QExtVariantProperty).
     * To create a regular QExtProperty object, use the QExtAbstractPropertyManager::addProperty() function instead.
     * @sa QExtAbstractPropertyManager::addProperty()
     */
    explicit QExtProperty(QExtAbstractPropertyManager *manager);

    void propertyChanged();

private:
    friend class QExtAbstractPropertyManager;
    QExtPropertyPrivate *d_ptr;
};

/**
 * @class QExtAbstractPropertyManager
 * @brief The QExtAbstractPropertyManager provides an interface for property managers.
 * A manager can create and manage properties of a given type, and is used in conjunction with the
 * QExtAbstractPropertyBrowser class.
 *
 * When using a property browser widget, the properties are created and managed by implementations of the
 * QExtAbstractPropertyManager class. To ensure that the properties' values will be displayed using suitable editing
 * widgets, the managers are associated with objects of QExtAbstractEditorFactory subclasses. The property browser
 * will use these associations to determine which factories it should use to create the preferred editing widgets.
 *
 * The QExtAbstractPropertyManager class provides common functionality like creating a property using the addProperty()
 * function, and retrieving the properties created by the manager using the properties() function. The class also
 * provides signals that are emitted when the manager's properties change: propertyInserted(), propertyRemoved(),
 * propertyChanged() and propertyDestroyed().
 *
 * QExtAbstractPropertyManager subclasses are supposed to provide their own type specific API. Note that several
 * ready-made implementations are available:
 *
 * @list
 * @o QExtBoolPropertyManager
 * @o QExtColorPropertyManager
 * @o QExtDatePropertyManager
 * @o QExtDateTimePropertyManager
 * @o QExtDoublePropertyManager
 * @o QExtEnumPropertyManager
 * @o QExtFlagPropertyManager
 * @o QExtFontPropertyManager
 * @o QExtGroupPropertyManager
 * @o QExtIntPropertyManager
 * @o QExtPointPropertyManager
 * @o QExtRectPropertyManager
 * @o QExtSizePropertyManager
 * @o QExtSizePolicyPropertyManager
 * @o QExtStringPropertyManager
 * @o QExtTimePropertyManager
 * @o QExtVariantPropertyManager
 * @endlist
 *
 * @sa QExtAbstractEditorFactoryBase, QExtAbstractPropertyBrowser, QExtProperty
 */
class QExtAbstractPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtAbstractPropertyManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Creates an abstract property manager with the given @a parent.
     */
    explicit QExtAbstractPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * @brief Destroys the manager. All properties created by the manager are destroyed.
     */
    ~QExtAbstractPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Destroys all the properties that this manager has created.
     * @sa propertyDestroyed(), uninitializeProperty()
     */
    void clear() const;

    /**
     * @brief Returns the set of properties created by this manager.
     * @sa addProperty()
     */
    QSet<QExtProperty *> properties() const;

    /**
     * @brief Creates a property with the given @a name which then is owned by this manager.
     * Internally, this function calls the createProperty() and initializeProperty() functions.
     * @sa initializeProperty(), properties()
     */
    QExtProperty *addProperty(const QString &name = QString());

Q_SIGNALS:    
    /**
     * @brief This signal is emitted whenever a property's data changes, passing a pointer to the @a property as parameter.
     * @Note that signal is only emitted for properties that are created by this manager.
     * @sa QExtAbstractPropertyBrowser::itemChanged()
     */
    void propertyChanged(QExtProperty *property);

    /**
     * @brief This signal is emitted when the specified @a property is about to be destroyed.
     * Note that signal is only emitted for properties that are created by this manager.
     * @sa clear(), uninitializeProperty()
     */
    void propertyDestroyed(QExtProperty *property);

    /**
     * @brief This signal is emitted when a subproperty is removed, passing pointers to the removed @a property and the
     * @a parent property as parameters.
     * Note that signal is emitted only when the @a parent property is created by this manager.
     * @sa QExtAbstractPropertyBrowser::itemRemoved()
     */
    void propertyRemoved(QExtProperty *property, QExtProperty *parent);

    /**
     * @brief This signal is emitted when a new subproperty is inserted into an existing property, passing pointers to
     * the @a newProperty, @a parentProperty and @a precedingProperty as parameters.
     * If @a precedingProperty is 0, the @a newProperty was inserted at the beginning of the @a parentProperty's
     * subproperties list.
     * Note that signal is emitted only if the @a parentProperty is created by this manager.
     * @sa QExtAbstractPropertyBrowser::itemInserted()
     */
    void propertyInserted(QExtProperty *property, QExtProperty *parent, QExtProperty *after);

protected:
    /**
     * @brief Returns whether the given @a property has a value.
     * The default implementation of this function returns true.
     * @sa QExtProperty::hasValue()
     */
    virtual bool hasValue(const QExtProperty *property) const;

    /**
     * @brief Returns an icon representing the current state of the given @a property.
     * @param The default implementation of this function returns an invalid icon.
     * @sa QExtProperty::valueIcon()
     */
    virtual QIcon valueIcon(const QExtProperty *property) const;

    /**
     * @brief Returns a string representing the current state of the given @a property.
     * The default implementation of this function returns an empty string.
     * @sa QExtProperty::valueText()
     */
    virtual QString valueText(const QExtProperty *property) const;

    /**
     * @brief Returns a string representing the current state of the given @a property.
     * The default implementation of this function returns an empty string.
     * @sa QExtProperty::valueText()
     */
    virtual QString displayText(const QExtProperty *property) const;

    /**
     * @brief Returns the echo mode representing the current state of the given @a property.
     * The default implementation of this function returns QLineEdit::Normal.
     * @sa QExtProperty::valueText()
     */
    virtual EchoMode echoMode(const QExtProperty *) const;

    /**
     * @brief This function is called whenever a new valid property pointer has been created, passing the pointer as
     * parameter.
     * The purpose is to let the manager know that the @a property has been created so that it can provide additional
     * attributes for the new property, e.g. QExtIntPropertyManager adds @l {QExtIntPropertyManager::value()}{value},
     * @l{QExtIntPropertyManager::minimum()}{minimum} and @l {QExtIntPropertyManager::maximum()}{maximum} attributes.
     * Since each manager subclass adds type specific attributes, this function is pure virtual and must be reimplemented
     * when deriving from the QExtAbstractPropertyManager class.
     * @sa addProperty(), createProperty()
     */
    virtual void initializeProperty(QExtProperty *property) = 0;

    /**
     * @brief This function is called just before the specified @a property is destroyed.
     * The purpose is to let the property manager know that the @a property is being destroyed so that it can remove the
     * property's additional attributes.
     * @sa clear(), propertyDestroyed()
     */
    virtual void uninitializeProperty(QExtProperty *property);

    /**
     * @brief Creates a property.
     * The base implementation produce QExtProperty instances; Reimplement this function to make this manager produce
     * objects of a QExtProperty subclass.
     * @sa addProperty(), initializeProperty()
     */
    virtual QExtProperty *createProperty();

private:
    friend class QExtProperty;
    QExtAbstractPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtAbstractPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtAbstractPropertyManager)
};

/**
 * @class class QExtAbstractEditorFactoryBase
 * @brief The QExtAbstractEditorFactoryBase provides an interface for editor factories.
 * An editor factory is a class that is able to create an editing widget of a specified type (e.g. line edits or
 * comboboxes) for a given QExtProperty object, and it is used in conjunction with the QExtAbstractPropertyManager and
 * QExtAbstractPropertyBrowser classes.
 *
 * When using a property browser widget, the properties are created and managed by implementations of the
 * QExtAbstractPropertyManager class. To ensure that the properties' values will be displayed using suitable editing
 * widgets, the managers are associated with objects of QExtAbstractEditorFactory subclasses. The property browser
 * will use these associations to determine which factories it should use to create the preferred editing widgets.
 *
 * Typically, an editor factory is created by subclassing the QExtAbstractEditorFactory template class which inherits
 * QExtAbstractEditorFactoryBase. But note that several ready-made implementations are available:
 *
 * @list
 *  @o QExtCheckBoxFactory
 *  @o QExtDateEditFactory
 *  @o QExtDateTimeEditFactory
 *  @o QExtDoubleSpinBoxFactory
 *  @o QExtEnumEditorFactory
 *  @o QExtLineEditFactory
 *  @o QExtScrollBarFactory
 *  @o QExtSliderFactory
 *  @o QExtSpinBoxFactory
 *  @o QExtTimeEditFactory
 *  @o QExtVariantEditorFactory
 * @endlist
 *
 * @sa QExtAbstractPropertyManager, QExtAbstractPropertyBrowser
 */
class QEXT_WIDGETS_API QExtAbstractEditorFactoryBase : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Creates an editing widget (with the given @a parent) for the given @a property.
     * This function is reimplemented in QExtAbstractEditorFactory template class which also provides a pure virtual
     * convenience overload of this function enabling access to the property's manager.
     * @sa QExtAbstractEditorFactory::createEditor()
     */
    virtual QWidget *createEditor(QExtProperty *property, QWidget *parent) = 0;

protected:
    /**
     * @brief Creates an abstract editor factory with the given @a parent.
     */
    explicit QExtAbstractEditorFactoryBase(QObject *parent = QEXT_NULLPTR) : QObject(parent) {}

    /**
     * @brief Detaches property manager from factory.
     * This method is reimplemented in QExtAbstractEditorFactory template subclass.
     * You don't need to reimplement it in your subclasses. Instead implement more convenient
     * QExtAbstractEditorFactory::disconnectPropertyManager() which gives you access to particular manager subclass.
     */
    virtual void breakConnection(QExtAbstractPropertyManager *manager) = 0;

protected Q_SLOTS:
    /**
     * @brief This method is called when property manager is being destroyed.
     * Basically it notifies factory not to produce editors for properties owned by @a manager.
     * You don't need to reimplement it in your subclass. This method is implemented in QExtAbstractEditorFactory
     * template subclass.
     */
    virtual void managerDestroyed(QObject *manager) = 0;

    friend class QExtAbstractPropertyBrowser;
};


/**
 * @brief brief The QExtAbstractEditorFactory is the base template class for editor factories.
 * An editor factory is a class that is able to create an editing widget of a specified type (e.g. line edits or
 * comboboxes) for a given QExtProperty object, and it is used in conjunction with the QExtAbstractPropertyManager and
 * QExtAbstractPropertyBrowser classes.
 *
 * Note that the QExtAbstractEditorFactory functions are using the PropertyManager template argument class which can be
 * any QExtAbstractPropertyManager subclass. For example:
 *
 * @code
 *  QExtSpinBoxFactory *factory;
 *  QSet<QExtIntPropertyManager *> managers = factory->propertyManagers();
 * @endcode
 *
 * Note that QExtSpinBoxFactory by definition creates editing widgets @e only for properties created by
 * QExtIntPropertyManager.
 *
 * When using a property browser widget, the properties are created and managed by implementations of the
 * QExtAbstractPropertyManager class. To ensure that the properties' values will be displayed using suitable editing
 * widgets, the managers are associated with objects of QExtAbstractEditorFactory subclasses. The property browser will
 * use these associations to determine which factories it should use to create the preferred editing widgets.
 *
 * A QExtAbstractEditorFactory object is capable of producing editors for several property managers at the same time.
 * To create an association between this factory and a given manager, use the addPropertyManager() function. Use the
 * removePropertyManager() function to make this factory stop producing editors for a given property manager. Use the
 * propertyManagers() function to retrieve the set of managers currently associated with this factory.
 *
 * Several ready-made implementations of the QExtAbstractEditorFactory class are available:
 *
 * @list
 *  @o QExtCheckBoxFactory
 *  @o QExtDateEditFactory
 *  @o QExtDateTimeEditFactory
 *  @o QExtDoubleSpinBoxFactory
 *  @o QExtEnumEditorFactory
 *  @o QExtLineEditFactory
 *  @o QExtScrollBarFactory
 *  @o QExtSliderFactory
 *  @o QExtSpinBoxFactory
 *  @o QExtTimeEditFactory
 *  @o QExtVariantEditorFactory
 * @endlist
 *
 * When deriving from the QExtAbstractEditorFactory class, several pure virtual functions must be implemented: the
 * connectPropertyManager() function is used by the factory to connect to the given manager's signals, the createEditor()
 * function is supposed to create an editor for the given property controlled by the given manager, and finally the
 * disconnectPropertyManager() function is used by the factory to disconnect from the specified manager's signals.
 *
 * @sa QExtAbstractEditorFactoryBase, QExtAbstractPropertyManager
 */
template <typename PropertyManager>
class QExtAbstractEditorFactory : public QExtAbstractEditorFactoryBase
{
public:
    /**
     * @brief Creates an editor factory with the given @a parent.
     * @sa addPropertyManager()
     */
    explicit QExtAbstractEditorFactory(QObject *parent) : QExtAbstractEditorFactoryBase(parent) {}
    ~QExtAbstractEditorFactory() QEXT_OVERRIDE {}

    /**
     * @brief Creates an editing widget (with the given @a parent) for the given @a property.
     */
    QWidget *createEditor(QExtProperty *property, QWidget *parent) QEXT_OVERRIDE
    {
        QSetIterator<PropertyManager *> iter(m_managers);
        while (iter.hasNext())
        {
            PropertyManager *manager = iter.next();
            if (manager == property->propertyManager())
            {
                return this->createEditor(manager, property, parent);
            }
        }
        return 0;
    }

    /**
     * @brief Adds the given @a manager to this factory's set of managers, making this factory produce editing widgets
     * for properties created by the given manager.
     * The PropertyManager type is a template argument class, and represents the chosen QExtAbstractPropertyManager subclass.
     * @sa propertyManagers(), removePropertyManager()
     */
    void addPropertyManager(PropertyManager *manager)
    {
        if (m_managers.contains(manager))
        {
            return;
        }
        m_managers.insert(manager);
        connectPropertyManager(manager);
        connect(manager, SIGNAL(destroyed(QObject *)), this, SLOT(managerDestroyed(QObject *)));
    }

    /**
     * @brief Removes the given @a manager from this factory's set of managers. The PropertyManager type is a template
     * argument class, and may be any QExtAbstractPropertyManager subclass.
     * @sa propertyManagers(), addPropertyManager()
     */
    void removePropertyManager(PropertyManager *manager)
    {
        if (!m_managers.contains(manager))
        {
            return;
        }
        disconnect(manager, SIGNAL(destroyed(QObject *)), this, SLOT(managerDestroyed(QObject *)));
        disconnectPropertyManager(manager);
        m_managers.remove(manager);
    }

    /**
     * @brief Returns the factory's set of associated managers.  The PropertyManager type is a template argument class,
     * and represents the chosen QExtAbstractPropertyManager subclass.
     *
     * @sa addPropertyManager(), removePropertyManager()
     */
    QSet<PropertyManager *> propertyManagers() const
    {
        return m_managers;
    }

    /**
     * @brief Returns the property manager for the given @a property, or 0 if the given @a property doesn't belong to
     * any of this factory's registered managers.
     *
     * The PropertyManager type is a template argument class, and represents the chosen QExtAbstractPropertyManager subclass.
     *
     * @sa propertyManagers()
     */
    PropertyManager *propertyManager(QExtProperty *property) const
    {
        QExtAbstractPropertyManager *manager = property->propertyManager();
        QSetIterator<PropertyManager *> iter(m_managers);
        while (iter.hasNext())
        {
            PropertyManager *m = iter.next();
            if (m == manager)
            {
                return m;
            }
        }
        return 0;
    }

protected:
    /**
     * @brief Connects this factory to the given @a manager's signals.  The PropertyManager type is a template argument
     * class, and represents the chosen QExtAbstractPropertyManager subclass.
     * This function is used internally by the addPropertyManager() function, and makes it possible to update an editing
     * widget when the associated property's data changes. This is typically done in custom slots responding to the
     * signals emitted by the property's manager, e.g. QExtIntPropertyManager::valueChanged() and
     * QExtIntPropertyManager::rangeChanged().
     *
     * @sa propertyManagers(), disconnectPropertyManager()
     */
    virtual void connectPropertyManager(PropertyManager *manager) = 0;

    /**
     * @brief Disconnects this factory from the given @a manager's signals. The PropertyManager type is a template
     * argument class, and represents the chosen QExtAbstractPropertyManager subclass.
     *
     * This function is used internally by the removePropertyManager() function.
     *
     * @sa propertyManagers(), connectPropertyManager()
     */
    virtual void disconnectPropertyManager(PropertyManager *manager) = 0;

    /**
     * @brief Creates an editing widget with the given @a parent for the specified @a property created by the given
     * @a manager. The PropertyManager type is a template argument class, and represents the chosen
     * QExtAbstractPropertyManager subclass.
     *
     * This function must be implemented in derived classes: It is recommended to store a pointer to the widget and map
     * it to the given @a property, since the widget must be updated whenever the associated property's data changes.
     * This is typically done in custom slots responding to the signals emitted by the property's manager, e.g.
     * QExtIntPropertyManager::valueChanged() and QExtIntPropertyManager::rangeChanged().
     *
     * @sa connectPropertyManager()
     */
    virtual QWidget *createEditor(PropertyManager *manager, QExtProperty *property, QWidget *parent) = 0;

    /**
     * @brief reimp
     */
    void managerDestroyed(QObject *manager) QEXT_OVERRIDE
    {
        QSetIterator<PropertyManager *> iter(m_managers);
        while (iter.hasNext())
        {
            PropertyManager *m = iter.next();
            if (m == manager)
            {
                m_managers.remove(m);
                return;
            }
        }
    }

private:
    void breakConnection(QExtAbstractPropertyManager *manager) QEXT_OVERRIDE
    {
        QSetIterator<PropertyManager *> iter(m_managers);
        while (iter.hasNext())
        {
            PropertyManager *m = iter.next();
            if (m == manager)
            {
                removePropertyManager(m);
                return;
            }
        }
    }

private:
    QSet<PropertyManager *> m_managers;
    friend class QtAbstractPropertyEditor;
};


/**
 * @brief The QExtBrowserItem class represents a property in a property browser instance.
 *
 * Browser items are created whenever a QExtProperty is inserted to the property browser. A QExtBrowserItem uniquely
 * identifies a browser's item. Thus, if the same QExtProperty is inserted multiple times, each occurrence gets its own
 * unique QExtBrowserItem. The items are owned by QExtAbstractPropertyBrowser and automatically deleted when they are
 * removed from the browser.
 *
 * You can traverse a browser's properties by calling parent() and children(). The property and the browser associated
 * with an item are available as property() and browser().
 *
 * @sa QExtAbstractPropertyBrowser, QExtProperty
 */
class QExtAbstractPropertyBrowser;
class QExtBrowserItemPrivate;
class QEXT_WIDGETS_API QExtBrowserItem
{
public:
    /**
     * @brief Returns the property which is accosiated with this item. Note that several items can be associated with
     * the same property instance in the same property browser.
     *
     * @sa QExtAbstractPropertyBrowser::items()
     */
    QExtProperty *property() const;

    /**
     * @brief Returns the parent item of @e this item. Returns 0 if @e this item is associated with top-level property
     * in item's property browser.
     *
     * @sa children()
     */
    QExtBrowserItem *parent() const;

    /**
     * @brief Returns the children items of @e this item. The properties reproduced from children items are always the
     * same as reproduced from associated property' children, for example:
     *
     * @code
     *  QExtBrowserItem *item;
     *  QList<QExtBrowserItem *> childrenItems = item->children();
     *  QList<QExtProperty *> childrenProperties = item->property()->subProperties();
     * @endcode
     *
     * @The @e childrenItems list represents the same list as @e childrenProperties.
     */
    QList<QExtBrowserItem *> children() const;

    /**
     * @brief Returns the property browser which owns @e this item.
     */
    QExtAbstractPropertyBrowser *browser() const;

private:
    explicit QExtBrowserItem(QExtAbstractPropertyBrowser *browser, QExtProperty *property, QExtBrowserItem *parent);
    ~QExtBrowserItem();

    QExtBrowserItemPrivate *d_ptr;
    friend class QExtAbstractPropertyBrowserPrivate;
};


/**
 * @brief QExtAbstractPropertyBrowser provides a base class for implementing property browsers.
 *
 * A property browser is a widget that enables the user to edit a given set of properties.  Each property is represented
 * by a label specifying the property's name, and an editing widget (e.g. a line edit or a combobox) holding its value.
 * A property can have zero or more subproperties.
 *
 * @image qtpropertybrowser.png
 *
 * The top level properties can be retrieved using the properties() function. To traverse each property's subproperties,
 * use the QExtProperty::subProperties() function. In addition, the set of top level properties can be manipulated using
 * the addProperty(), insertProperty() and removeProperty() functions. Note that the QExtProperty class provides a
 * corresponding set of functions making it possible to manipulate the set of subproperties as well.
 *
 * To remove all the properties from the property browser widget, use the clear() function. This function will clear the
 * editor, but it will not delete the properties since they can still be used in other editors.
 *
 * The properties themselves are created and managed by implementations of the QExtAbstractPropertyManager class.
 * A manager can handle (i.e. create and manage) properties of a given type. In the property browser the managers are
 * associated with implementations of the QExtAbstractEditorFactory: A factory is a class able to create an editing
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
 *      QExtProperty *property1, *property2, *property3;
 *
 *      property2->addSubProperty(property1);
 *      property3->addSubProperty(property2);
 *
 *      QExtAbstractPropertyBrowser *editor;
 *
 *      editor->addProperty(property1);
 *      editor->addProperty(property2);
 *      editor->addProperty(property3);
 *  @endcode
 *  @o  @image qtpropertybrowser-duplicate.png
 * @endtable
 *
 * The addProperty() function returns a QExtBrowserItem that uniquely identifies the created item.
 * To make a property editable in the property browser, the createEditor() function must be called to provide the
 * property with a suitable editing widget.
 *
 * Note that there are two ready-made property browser implementations:
 *
 * @list
 *  @o QExtGroupBoxPropertyBrowser
 *  @o QExtTreePropertyBrowser
 * @endlist
 *
 * @sa QExtAbstractPropertyManager, QExtAbstractEditorFactoryBase
 */
class QExtAbstractPropertyBrowserPrivate;
class QEXT_WIDGETS_API QExtAbstractPropertyBrowser : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Creates an abstract property browser with the given \a parent.
     */
    explicit QExtAbstractPropertyBrowser(QWidget *parent = QEXT_NULLPTR);

    /**
     * @brief Destroys the property browser, and destroys all the items that were created by this property browser.
     *
     * Note that the properties that were displayed in the editor are not deleted since they still can be used in other
     * editors. Neither does the destructor delete the property managers and editor factories that were used by this
     * property browser widget unless this widget was their parent.
     *
     * @sa QExtAbstractPropertyManager::~QExtAbstractPropertyManager()
     */
    ~QExtAbstractPropertyBrowser() QEXT_OVERRIDE;

    /**
     * @brief Removes all the properties from the editor, but does not delete them since they can still be used in
     * other editors.
     *
     * @sa removeProperty(), QExtAbstractPropertyManager::clear()
     */
    void clear();

    /**
     * @brief Returns the property browser's list of top level properties.
     * To traverse the subproperties, use the QExtProperty::subProperties() function.
     *
     * @sa addProperty(), insertProperty(), removeProperty()
     */
    QList<QExtProperty *> properties() const;

    /**
     * @brief Returns the list of top-level items.
     *
     * @sa topLevelItem()
     */
    QList<QExtBrowserItem *> topLevelItems() const;

    /**
     * @brief Returns the property browser's list of all items associated with the given \a property.
     * There is one item per instance of the property in the browser.
     *
     * @sa topLevelItem()
     */
    QList<QExtBrowserItem *> items(QExtProperty *property) const;

    /**
     * @brief Returns the top-level items associated with the given \a property.
     *
     * Returns 0 if \a property wasn't inserted into this property browser or isn't a top-level one.
     *
     * @sa topLevelItems(), items()
     */
    QExtBrowserItem *topLevelItem(QExtProperty *property) const;

    /**
     * @brief Connects the given \a manager to the given \a factory, ensuring that properties of the \a manager's type
     * will be displayed with an editing widget suitable for their value.
     *
     * For example:
     *
     * @code
     *  QExtIntPropertyManager *intManager;
     *  QExtDoublePropertyManager *doubleManager;
     *
     *  QExtProperty *myInteger = intManager->addProperty();
     *  QExtProperty *myDouble = doubleManager->addProperty();
     *
     *  QExtSpinBoxFactory  *spinBoxFactory;
     *  QExtDoubleSpinBoxFactory *doubleSpinBoxFactory;
     *
     *  QExtAbstractPropertyBrowser *editor;
     *  editor->setFactoryForManager(intManager, spinBoxFactory);
     *  editor->setFactoryForManager(doubleManager, doubleSpinBoxFactory);
     *
     *  editor->addProperty(myInteger);
     *  editor->addProperty(myDouble);
     * @endcode
     *
     * In this example the \c myInteger property's value is displayed with a QSpinBox widget, while the \c myDouble
     * property's value is displayed with a QDoubleSpinBox widget.
     *
     * Note that a factory can be associated with many managers, but a manager can only be associated with one single
     * factory.  If the given \a manager already is associated with another factory, the old association is broken before
     * the new one established.
     *
     * This function ensures that the given \a manager and the given \a factory are compatible, and it automatically
     * calls the QExtAbstractEditorFactory::addPropertyManager() function if necessary.
     *
     * @sa unsetFactoryForManager()
     */
    template <class PropertyManager>
    void setFactoryForManager(PropertyManager *manager, QExtAbstractEditorFactory<PropertyManager> *factory)
    {
        QExtAbstractPropertyManager *abstractManager = manager;
        QExtAbstractEditorFactoryBase *abstractFactory = factory;
        if (this->addFactory(abstractManager, abstractFactory))
        {
            factory->addPropertyManager(manager);
        }
    }

    /**
     * @brief Removes the association between the given \a manager and the factory bound to it, automatically calling the
     * QExtAbstractEditorFactory::removePropertyManager() function if necessary.
     *
     * @sa setFactoryForManager()
     */
    void unsetFactoryForManager(QExtAbstractPropertyManager *manager);

    /**
     * @brief Returns the current item in the property browser.
     *
     * @sa setCurrentItem()
     */
    QExtBrowserItem *currentItem() const;

    /**
     * @brief Sets the current item in the property browser to \a item.
     *
     * @sa currentItem(), currentItemChanged()
     */
    void setCurrentItem(QExtBrowserItem *);

Q_SIGNALS:
    void currentItemChanged(QExtBrowserItem *);

public Q_SLOTS:
    /**
     * @brief Removes the specified \a property (and its subproperties) from the property browser's list of top level
     * properties. All items that were associated with the given \a property and its children are deleted.
     *
     * Note that the properties are \e not deleted since they can still be used in other editors.
     *
     * @sa clear(), QExtProperty::removeSubProperty(), properties()
     */
    void removeProperty(QExtProperty *property);

    /**
     * @brief Appends the given \a property (and its subproperties) to the property browser's list of top level properties.
     * Returns the item created by property browser which is associated with the \a property.
     * In order to get all children items created by the property browser in this call, the returned item should be traversed.
     *
     * If the specified \a property is already added, this function does nothing and returns 0.
     *
     * @sa insertProperty(), QExtProperty::addSubProperty(), properties()
     */
    QExtBrowserItem *addProperty(QExtProperty *property);

    /**
     * @brief Inserts the given \a property (and its subproperties) after the specified \a afterProperty in the browser's
     * list of top level properties. Returns item created by property browser which is associated with the \a property.
     * In order to get all children items created by the property browser in this call returned item should be traversed.
     *
     * If the specified \a afterProperty is 0, the given \a property is inserted at the beginning of the list.
     * If \a property is already inserted, this function does nothing and returns 0.
     *
     * @sa addProperty(), QExtProperty::insertSubProperty(), properties()
     */
    QExtBrowserItem *insertProperty(QExtProperty *property, QExtProperty *afterProperty);

protected:
    /**
     * @brief This function is called to update the widget whenever a property is removed from the property browser,
     * passing the pointer to the \a item of the property as parameters. The passed \a item is deleted just after this
     * call is finished.
     *
     * If the the parent of \a item is 0, the removed \a item was a top level property in this editor.
     *
     * This function must be reimplemented in derived classes. Note that if the removed \a item's property has
     * subproperties, this method will be called for those properties just before the current call is started.
     *
     * @sa removeProperty()
     */
    virtual void itemRemoved(QExtBrowserItem *item) = 0;

    /**
     * @brief This function is called whenever a property's data changes, passing a pointer to the \a item of property
     * as parameter.
     *
     * This function must be reimplemented in derived classes in order to update the property browser widget whenever a
     * property's name, tool tip, status tip, "what's this" text, value text or value icon changes.
     *
     * Note that if the property browser contains several occurrences of the same property, this method will be called
     * once for each occurrence (with a different item each time).
     *
     * @sa QExtProperty, items()
     * @note can be tooltip, statustip, whatsthis, name, icon, text.
     */
    virtual void itemChanged(QExtBrowserItem *item) = 0;

    /**
     * @brief Creates an editing widget (with the given \a parent) for the given \a property according to the previously
     * established associations between property managers and editor factories.
     *
     * If the property is created by a property manager which was not associated with any of the existing factories in
     * \e this property editor, the function returns 0.
     *
     * To make a property editable in the property browser, the createEditor() function must be called to provide the
     * property with a suitable editing widget.
     *
     * Reimplement this function to provide additional decoration for the editing widgets created by the installed factories.
     *
     * @sa setFactoryForManager()
     */
    virtual QWidget *createEditor(QExtProperty *property, QWidget *parent);

    /**
     * @brief This function is called to update the widget whenever a property is inserted or added to the property
     * browser, passing pointers to the \a insertedItem of property and the specified \a precedingItem as parameters.
     *
     * If \a precedingItem is 0, the \a insertedItem was put at the beginning of its parent item's list of subproperties.
     * If the parent of \a insertedItem is 0, the \a insertedItem was added as a top level property of \e this property
     * browser.
     *
     * This function must be reimplemented in derived classes. Note that if the \a insertedItem's property has
     * subproperties, this method will be called for those properties as soon as the current call is finished.
     *
     * @sa insertProperty(), addProperty()
     */
    virtual void itemInserted(QExtBrowserItem *item, QExtBrowserItem *afterItem) = 0;

private:
    bool addFactory(QExtAbstractPropertyManager *abstractManager, QExtAbstractEditorFactoryBase *abstractFactory);

    QExtAbstractPropertyBrowserPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtAbstractPropertyBrowser)
    QEXT_DISABLE_COPY_MOVE(QExtAbstractPropertyBrowser)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyInserted(QExtProperty *, QExtProperty *, QExtProperty *))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyRemoved(QExtProperty *, QExtProperty *))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDataChanged(QExtProperty *))
};


/***********************************************************************************************************************
** property manager
***********************************************************************************************************************/
/**
 * @brief The QExtGroupPropertyManager provides and manages group properties.
 * This class is intended to provide a grouping element without any value.
 *
 * @sa QExtAbstractPropertyManager
 */
class QEXT_WIDGETS_API QExtGroupPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given \a parent.
     */
    QExtGroupPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * @brief Destroys this manager, and all the properties it has created.
     */
    ~QExtGroupPropertyManager() QEXT_OVERRIDE;

protected:
    /**
     * @brief reimp
     */
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    virtual bool hasValue(const QExtProperty *property) const QEXT_OVERRIDE;
};


/**
 * @class QExtIntPropertyManager
 * @brief The QExtIntPropertyManager provides and manages int properties.
 *
 * An int property has a current value, and a range specifying the valid values. The range is defined by a minimum and
 * a maximum value.
 *
 * The property's value and range can be retrieved using the value(), minimum() and maximum() functions, and can be set
 * using the setValue(), setMinimum() and setMaximum() slots. Alternatively, the range can be defined in one go using
 * the setRange() slot.
 *
 * In addition, QExtIntPropertyManager provides the valueChanged() signal which is emitted whenever a property created
 * by this manager changes, and the rangeChanged() signal which is emitted whenever such a property changes its range of
 * valid values.
 *
 * @sa QExtAbstractPropertyManager, QExtSpinBoxFactory, QExtSliderFactory, QExtScrollBarFactory
 */
class QExtIntPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtIntPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given \a parent.
     */
    QExtIntPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * @brief Destroys this manager, and all the properties it has created.
     */
    ~QExtIntPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given \a property's value.
     * If the given property is not managed by this manager, this function returns 0.
     *
     * @sa setValue()
     */
    int value(const QExtProperty *property) const;

    /**
     * @brief Returns the given \a property's minimum value.
     *
     * @sa setMinimum(), maximum(), setRange()
     */
    int minimum(const QExtProperty *property) const;

    /**
     * @brief Returns the given \a property's maximum value.
     *
     * @sa setMaximum(), minimum(), setRange()
     */
    int maximum(const QExtProperty *property) const;

    /**
     * @brief Returns the given \a property's step value.
     * The step is typically used to increment or decrement a property value while pressing an arrow key.
     *
     * @sa setSingleStep()
     */
    int singleStep(const QExtProperty *property) const;

    /**
     * @brief Returns read-only status of the property.
     * When property is read-only it's value can be selected and copied from editor but not modified.
     *
     * @sa QExtIntPropertyManager::setReadOnly
     */
    bool isReadOnly(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given \a property to \a value.
     * If the specified \a value is not valid according to the given \a property's range, the \a value is adjusted to
     * the nearest valid value within the range.
     *
     * @sa value(), setRange(), valueChanged()
     */
    void setValue(QExtProperty *property, int val);

    /**
     * @brief Sets the minimum value for the given \a property to \a minVal.
     * When setting the minimum value, the maximum and current values are adjusted if necessary (ensuring that the range
     * remains valid and that the current value is within the range).
     *
     * @sa minimum(), setRange(), rangeChanged()
     */
    void setMinimum(QExtProperty *property, int minVal);

    /**
     * @brief Sets the maximum value for the given \a property to \a maxVal.
     * When setting maximum value, the minimum and current values are adjusted if necessary (ensuring that the range
     * remains valid and that the current value is within the range).
     *
     * @sa maximum(), setRange(), rangeChanged()
     */
    void setMaximum(QExtProperty *property, int maxVal);

    /**
     * @brief Sets the range of valid values.
     * This is a convenience function defining the range of valid values in one go; setting the \a minimum and
     * \a maximum values for the given \a property with a single function call.
     *
     * When setting a new range, the current value is adjusted if necessary (ensuring that the value remains within range).
     *
     * @sa setMinimum(), setMaximum(), rangeChanged()
     */
    void setRange(QExtProperty *property, int minVal, int maxVal);

    /**
     * @brief Sets the step value for the given \a property to \a step.
     * The step is typically used to increment or decrement a property value while pressing an arrow key.
     *
     * @sa singleStep()
     */
    void setSingleStep(QExtProperty *property, int step);

    /**
     * @brief Sets read-only status of the property.
     *
     * @sa QExtIntPropertyManager::setReadOnly
     */
    void setReadOnly(QExtProperty *property, bool readOnly);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer to
     * the \a property and the new \a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, int val);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its range of valid values,
     * passing a pointer to the \a property and the new \a minimum and \a maximum values.
     *
     * @sa setRange()
     */
    void rangeChanged(QExtProperty *property, int minVal, int maxVal);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its single step property,
     * passing a pointer to the \a property and the new \a step value
     *
     * \sa setSingleStep()
     */
    void singleStepChanged(QExtProperty *property, int step);
    void readOnlyChanged(QExtProperty *property, bool readOnly);

protected:
    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtIntPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtIntPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtIntPropertyManager)
};


class QExtBoolPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtBoolPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtBoolPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtBoolPropertyManager() QEXT_OVERRIDE;

    bool value(const QExtProperty *property) const;
    bool textVisible(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, bool val);
    void setTextVisible(QExtProperty *property, bool textVisible);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, bool val);
    void textVisibleChanged(QExtProperty *property, bool);

protected:
    QIcon valueIcon(const QExtProperty *property) const QEXT_OVERRIDE;
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtBoolPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtBoolPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtBoolPropertyManager)
};

/**
 * @brief The QExtDoublePropertyManager provides and manages double properties.
 *
 * A double property has a current value, and a range specifying the valid values. The range is defined by a minimum
 * and a maximum value.
 *
 * The property's value and range can be retrieved using the value(), minimum() and maximum() functions, and can be set
 * using the setValue(), setMinimum() and setMaximum() slots. Alternatively, the range can be defined in one go using
 * the setRange() slot.
 *
 * In addition, QExtDoublePropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes, and the rangeChanged() signal which is emitted whenever such a property changes its
 * range of valid values.
 *
 * @sa QExtAbstractPropertyManager, QExtDoubleSpinBoxFactory
 */
class QExtDoublePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtDoublePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtDoublePropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtDoublePropertyManager() QEXT_OVERRIDE;

    double value(const QExtProperty *property) const;
    double minimum(const QExtProperty *property) const;
    double maximum(const QExtProperty *property) const;
    double singleStep(const QExtProperty *property) const;
    int decimals(const QExtProperty *property) const;
    bool isReadOnly(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, double val);
    void setMinimum(QExtProperty *property, double minVal);
    void setMaximum(QExtProperty *property, double maxVal);
    void setRange(QExtProperty *property, double minVal, double maxVal);
    void setSingleStep(QExtProperty *property, double step);
    void setDecimals(QExtProperty *property, int prec);
    void setReadOnly(QExtProperty *property, bool readOnly);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the \a property and the new \a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, double val);
    void rangeChanged(QExtProperty *property, double minVal, double maxVal);
    void singleStepChanged(QExtProperty *property, double step);
    void decimalsChanged(QExtProperty *property, int prec);
    void readOnlyChanged(QExtProperty *property, bool readOnly);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtDoublePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtDoublePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtDoublePropertyManager)
};

class QExtStringPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtStringPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtStringPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtStringPropertyManager() QEXT_OVERRIDE;

    QString value(const QExtProperty *property) const;
    QRegExp regExp(const QExtProperty *property) const;

    /**
     * @brief Returns read-only status of the property.
     * When property is read-only it's value can be selected and copied from editor but not modified.
     * @sa QExtStringPropertyManager::setReadOnly
     */
    bool isReadOnly(const QExtProperty *property) const;
    EchoMode echoMode(const QExtProperty *property) const QEXT_OVERRIDE;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QString &val);
    void setRegExp(QExtProperty *property, const QRegExp &regExp);
    void setEchoMode(QExtProperty *property, EchoMode echoMode);

    /**
     * @brief Sets read-only status of the property.
     * @sa QExtStringPropertyManager::setReadOnly
     */
    void setReadOnly(QExtProperty *property, bool readOnly);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QString &val);
    void regExpChanged(QExtProperty *property, const QRegExp &regExp);
    void echoModeChanged(QExtProperty *property, const int);
    void readOnlyChanged(QExtProperty *property, bool);

protected:
    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    QString displayText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtStringPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtStringPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtStringPropertyManager)
};

class QExtDatePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtDatePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtDatePropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtDatePropertyManager() QEXT_OVERRIDE;

    QDate value(const QExtProperty *property) const;
    QDate minimum(const QExtProperty *property) const;
    QDate maximum(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QDate &val);
    void setMinimum(QExtProperty *property, const QDate &minVal);
    void setMaximum(QExtProperty *property, const QDate &maxVal);
    void setRange(QExtProperty *property, const QDate &minVal, const QDate &maxVal);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QDate &val);
    void rangeChanged(QExtProperty *property, const QDate &minVal, const QDate &maxVal);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtDatePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtDatePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtDatePropertyManager)
};

class QExtTimePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtTimePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtTimePropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtTimePropertyManager() QEXT_OVERRIDE;

    QTime value(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QTime &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QTime &val);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtTimePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtTimePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtTimePropertyManager)
};

class QExtDateTimePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtDateTimePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtDateTimePropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtDateTimePropertyManager() QEXT_OVERRIDE;

    QDateTime value(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QDateTime &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QDateTime &val);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtDateTimePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtDateTimePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtDateTimePropertyManager)
};

class QExtKeySequencePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtKeySequencePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtKeySequencePropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtKeySequencePropertyManager() QEXT_OVERRIDE;

    QKeySequence value(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QKeySequence &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QKeySequence &val);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtKeySequencePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtKeySequencePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtKeySequencePropertyManager)
};

class QExtCharPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtCharPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtCharPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtCharPropertyManager() QEXT_OVERRIDE;

    QChar value(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QChar &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QChar &val);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtCharPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtCharPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtCharPropertyManager)
};

class QExtEnumPropertyManager;
class QExtLocalePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtLocalePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtLocalePropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtLocalePropertyManager() QEXT_OVERRIDE;

    QExtEnumPropertyManager *subEnumPropertyManager() const;

    QLocale value(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QLocale &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QLocale &val);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtLocalePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtLocalePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtLocalePropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotEnumChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtPointPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPointPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtPointPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtPointPropertyManager() QEXT_OVERRIDE;

    QExtIntPropertyManager *subIntPropertyManager() const;

    QPoint value(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QPoint &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QPoint &val);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtPointPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPointPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPointPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtPointFPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPointFPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtPointFPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtPointFPropertyManager() QEXT_OVERRIDE;

    QExtDoublePropertyManager *subDoublePropertyManager() const;

    QPointF value(const QExtProperty *property) const;
    int decimals(const QExtProperty *property) const;

public Q_SLOTS:
    void setDecimals(QExtProperty *property, int prec);
    void setValue(QExtProperty *property, const QPointF &val);

Q_SIGNALS:
    void decimalsChanged(QExtProperty *property, int prec);
    void valueChanged(QExtProperty *property, const QPointF &val);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtPointFPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPointFPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPointFPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotDoubleChanged(QExtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtSizePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtSizePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtSizePropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtSizePropertyManager() QEXT_OVERRIDE;

    QExtIntPropertyManager *subIntPropertyManager() const;

    QSize value(const QExtProperty *property) const;
    QSize minimum(const QExtProperty *property) const;
    QSize maximum(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QSize &val);
    void setMinimum(QExtProperty *property, const QSize &minVal);
    void setMaximum(QExtProperty *property, const QSize &maxVal);
    void setRange(QExtProperty *property, const QSize &minVal, const QSize &maxVal);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QSize &val);
    void rangeChanged(QExtProperty *property, const QSize &minVal, const QSize &maxVal);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtSizePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtSizePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtSizePropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtSizeFPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtSizeFPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT
public:
    QExtSizeFPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtSizeFPropertyManager() QEXT_OVERRIDE;

    QExtDoublePropertyManager *subDoublePropertyManager() const;

    QSizeF value(const QExtProperty *property) const;
    QSizeF minimum(const QExtProperty *property) const;
    QSizeF maximum(const QExtProperty *property) const;
    int decimals(const QExtProperty *property) const;

public Q_SLOTS:
    void setDecimals(QExtProperty *property, int prec);
    void setValue(QExtProperty *property, const QSizeF &val);
    void setMinimum(QExtProperty *property, const QSizeF &minVal);
    void setMaximum(QExtProperty *property, const QSizeF &maxVal);
    void setRange(QExtProperty *property, const QSizeF &minVal, const QSizeF &maxVal);

Q_SIGNALS:
    void decimalsChanged(QExtProperty *property, int prec);
    void valueChanged(QExtProperty *property, const QSizeF &val);
    void rangeChanged(QExtProperty *property, const QSizeF &minVal, const QSizeF &maxVal);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtSizeFPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtSizeFPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtSizeFPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotDoubleChanged(QExtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtRectPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtRectPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtRectPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtRectPropertyManager() QEXT_OVERRIDE;

    QExtIntPropertyManager *subIntPropertyManager() const;

    QRect value(const QExtProperty *property) const;
    QRect constraint(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QRect &val);
    void setConstraint(QExtProperty *property, const QRect &constraint);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QRect &val);
    void constraintChanged(QExtProperty *property, const QRect &constraint);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtRectPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtRectPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtRectPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtRectFPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtRectFPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtRectFPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtRectFPropertyManager() QEXT_OVERRIDE;

    QExtDoublePropertyManager *subDoublePropertyManager() const;

    QRectF value(const QExtProperty *property) const;
    QRectF constraint(const QExtProperty *property) const;
    int decimals(const QExtProperty *property) const;

public Q_SLOTS:
    void setDecimals(QExtProperty *property, int prec);
    void setValue(QExtProperty *property, const QRectF &val);
    void setConstraint(QExtProperty *property, const QRectF &constraint);

Q_SIGNALS:
    void decimalsChanged(QExtProperty *property, int prec);
    void valueChanged(QExtProperty *property, const QRectF &val);
    void constraintChanged(QExtProperty *property, const QRectF &constraint);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtRectFPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtRectFPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtRectFPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotDoubleChanged(QExtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtEnumPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtEnumPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtEnumPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtEnumPropertyManager() QEXT_OVERRIDE;

    int value(const QExtProperty *property) const;
    QStringList enumNames(const QExtProperty *property) const;
    QMap<int, QIcon> enumIcons(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, int val);
    void setEnumNames(QExtProperty *property, const QStringList &names);
    void setEnumIcons(QExtProperty *property, const QMap<int, QIcon> &icons);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, int val);
    void enumNamesChanged(QExtProperty *property, const QStringList &names);
    void enumIconsChanged(QExtProperty *property, const QMap<int, QIcon> &icons);

protected:
    QIcon valueIcon(const QExtProperty *property) const QEXT_OVERRIDE;
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtEnumPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtEnumPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtEnumPropertyManager)
};

class QExtFlagPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtFlagPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtFlagPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtFlagPropertyManager() QEXT_OVERRIDE;

    QExtBoolPropertyManager *subBoolPropertyManager() const;

    int value(const QExtProperty *property) const;
    QStringList flagNames(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, int val);
    void setFlagNames(QExtProperty *property, const QStringList &names);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, int val);
    void flagNamesChanged(QExtProperty *property, const QStringList &names);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtFlagPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtFlagPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtFlagPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotBoolChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtSizePolicyPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtSizePolicyPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtSizePolicyPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtSizePolicyPropertyManager() QEXT_OVERRIDE;

    QExtIntPropertyManager *subIntPropertyManager() const;
    QExtEnumPropertyManager *subEnumPropertyManager() const;

    QSizePolicy value(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QSizePolicy &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QSizePolicy &val);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtSizePolicyPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtSizePolicyPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtSizePolicyPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotEnumChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtFontPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtFontPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtFontPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtFontPropertyManager() QEXT_OVERRIDE;

    QExtIntPropertyManager *subIntPropertyManager() const;
    QExtEnumPropertyManager *subEnumPropertyManager() const;
    QExtBoolPropertyManager *subBoolPropertyManager() const;

    QFont value(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QFont &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QFont &val);

protected:
    QIcon valueIcon(const QExtProperty *property) const QEXT_OVERRIDE;
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtFontPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtFontPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtFontPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotEnumChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotBoolChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
    Q_PRIVATE_SLOT(d_func(), void slotFontDatabaseChanged())
    Q_PRIVATE_SLOT(d_func(), void slotFontDatabaseDelayedChange())
};

class QExtColorPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtColorPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtColorPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtColorPropertyManager() QEXT_OVERRIDE;

    QExtIntPropertyManager *subIntPropertyManager() const;

    QColor value(const QExtProperty *property) const;

public Q_SLOTS:
    void setValue(QExtProperty *property, const QColor &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QColor &val);

protected:
    QIcon valueIcon(const QExtProperty *property) const QEXT_OVERRIDE;
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtColorPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtColorPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtColorPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

class QExtCursorPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtCursorPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    QExtCursorPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtCursorPropertyManager() QEXT_OVERRIDE;

#ifndef QT_NO_CURSOR
    QCursor value(const QExtProperty *property) const;
#endif

public Q_SLOTS:
    void setValue(QExtProperty *property, const QCursor &val);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QCursor &val);

protected:
    QIcon valueIcon(const QExtProperty *property) const QEXT_OVERRIDE;
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

private:
    QExtCursorPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtCursorPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtCursorPropertyManager)
};


/***********************************************************************************************************************
** editor factory
***********************************************************************************************************************/
class QExtSpinBoxFactoryPrivate;
class QEXT_WIDGETS_API QExtSpinBoxFactory : public QExtAbstractEditorFactory<QExtIntPropertyManager>
{
    Q_OBJECT

public:
    QExtSpinBoxFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtSpinBoxFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtIntPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtIntPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtIntPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtSpinBoxFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtSpinBoxFactory)
    QEXT_DISABLE_COPY_MOVE(QExtSpinBoxFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, int, int))
    Q_PRIVATE_SLOT(d_func(), void slotSingleStepChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotReadOnlyChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(int))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtSliderFactoryPrivate;
class QEXT_WIDGETS_API QExtSliderFactory : public QExtAbstractEditorFactory<QExtIntPropertyManager>
{
    Q_OBJECT

public:
    QExtSliderFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtSliderFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtIntPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtIntPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtIntPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtSliderFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtSliderFactory)
    QEXT_DISABLE_COPY_MOVE(QExtSliderFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, int, int))
    Q_PRIVATE_SLOT(d_func(), void slotSingleStepChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(int))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtScrollBarFactoryPrivate;
class QEXT_WIDGETS_API QExtScrollBarFactory : public QExtAbstractEditorFactory<QExtIntPropertyManager>
{
    Q_OBJECT

public:
    QExtScrollBarFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtScrollBarFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtIntPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtIntPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtIntPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtScrollBarFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtScrollBarFactory)
    QEXT_DISABLE_COPY_MOVE(QExtScrollBarFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, int, int))
    Q_PRIVATE_SLOT(d_func(), void slotSingleStepChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(int))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtCheckBoxFactoryPrivate;
class QEXT_WIDGETS_API QExtCheckBoxFactory : public QExtAbstractEditorFactory<QExtBoolPropertyManager>
{
    Q_OBJECT

public:
    QExtCheckBoxFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtCheckBoxFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtBoolPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtBoolPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtBoolPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtCheckBoxFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtCheckBoxFactory)
    QEXT_DISABLE_COPY_MOVE(QExtCheckBoxFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotTextVisibleChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(bool))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtDoubleSpinBoxFactoryPrivate;
class QEXT_WIDGETS_API QExtDoubleSpinBoxFactory : public QExtAbstractEditorFactory<QExtDoublePropertyManager>
{
    Q_OBJECT

public:
    QExtDoubleSpinBoxFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtDoubleSpinBoxFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtDoublePropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtDoublePropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtDoublePropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtDoubleSpinBoxFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtDoubleSpinBoxFactory)
    QEXT_DISABLE_COPY_MOVE(QExtDoubleSpinBoxFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, double, double))
    Q_PRIVATE_SLOT(d_func(), void slotSingleStepChanged(QExtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotDecimalsChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotReadOnlyChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(double))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtLineEditFactoryPrivate;
class QEXT_WIDGETS_API QExtLineEditFactory : public QExtAbstractEditorFactory<QExtStringPropertyManager>
{
    Q_OBJECT

public:
    QExtLineEditFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtLineEditFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtStringPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtStringPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtStringPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtLineEditFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtLineEditFactory)
    QEXT_DISABLE_COPY_MOVE(QExtLineEditFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QString &))
    Q_PRIVATE_SLOT(d_func(), void slotRegExpChanged(QExtProperty *, const QRegExp &))
    Q_PRIVATE_SLOT(d_func(), void slotEchoModeChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotReadOnlyChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QString &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtDateEditFactoryPrivate;
class QEXT_WIDGETS_API QExtDateEditFactory : public QExtAbstractEditorFactory<QExtDatePropertyManager>
{
    Q_OBJECT

public:
    QExtDateEditFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtDateEditFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtDatePropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtDatePropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtDatePropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtDateEditFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtDateEditFactory)
    QEXT_DISABLE_COPY_MOVE(QExtDateEditFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QDate &))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, const QDate &, const QDate &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QDate &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtTimeEditFactoryPrivate;
class QEXT_WIDGETS_API QExtTimeEditFactory : public QExtAbstractEditorFactory<QExtTimePropertyManager>
{
    Q_OBJECT

public:
    QExtTimeEditFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtTimeEditFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtTimePropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtTimePropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtTimePropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtTimeEditFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtTimeEditFactory)
    QEXT_DISABLE_COPY_MOVE(QExtTimeEditFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QTime &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QTime &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtDateTimeEditFactoryPrivate;
class QEXT_WIDGETS_API QExtDateTimeEditFactory : public QExtAbstractEditorFactory<QExtDateTimePropertyManager>
{
    Q_OBJECT

public:
    QExtDateTimeEditFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtDateTimeEditFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtDateTimePropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtDateTimePropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtDateTimePropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtDateTimeEditFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtDateTimeEditFactory)
    QEXT_DISABLE_COPY_MOVE(QExtDateTimeEditFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QDateTime &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QDateTime &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtKeySequenceEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtKeySequenceEditorFactory : public QExtAbstractEditorFactory<QExtKeySequencePropertyManager>
{
    Q_OBJECT

public:
    QExtKeySequenceEditorFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtKeySequenceEditorFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtKeySequencePropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtKeySequencePropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtKeySequencePropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtKeySequenceEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtKeySequenceEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtKeySequenceEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QKeySequence &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QKeySequence &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtCharEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtCharEditorFactory : public QExtAbstractEditorFactory<QExtCharPropertyManager>
{
    Q_OBJECT

public:
    QExtCharEditorFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtCharEditorFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtCharPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtCharPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtCharPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtCharEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtCharEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtCharEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QChar &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QChar &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtEnumEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtEnumEditorFactory : public QExtAbstractEditorFactory<QExtEnumPropertyManager>
{
    Q_OBJECT

public:
    QExtEnumEditorFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtEnumEditorFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtEnumPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtEnumPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtEnumPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtEnumEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtEnumEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtEnumEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotEnumNamesChanged(QExtProperty *, const QStringList &))
    Q_PRIVATE_SLOT(d_func(), void slotEnumIconsChanged(QExtProperty *, const QMap<int, QIcon> &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(int))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtCursorEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtCursorEditorFactory : public QExtAbstractEditorFactory<QExtCursorPropertyManager>
{
    Q_OBJECT

public:
    QExtCursorEditorFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtCursorEditorFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtCursorPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtCursorPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtCursorPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtCursorEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtCursorEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtCursorEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QCursor &))
    Q_PRIVATE_SLOT(d_func(), void slotEnumChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};

class QExtColorEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtColorEditorFactory : public QExtAbstractEditorFactory<QExtColorPropertyManager>
{
    Q_OBJECT

public:
    QExtColorEditorFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtColorEditorFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtColorPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtColorPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtColorPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtColorEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtColorEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtColorEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QColor &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QColor &))
};

class QExtFontEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtFontEditorFactory : public QExtAbstractEditorFactory<QExtFontPropertyManager>
{
    Q_OBJECT
public:
    QExtFontEditorFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtFontEditorFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtFontPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtFontPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtFontPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtFontEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtFontEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtFontEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QFont &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QFont &))
};


/***********************************************************************************************************************
** button property browser
***********************************************************************************************************************/
class QExtButtonPropertyBrowserPrivate;
class QEXT_WIDGETS_API QExtButtonPropertyBrowser : public QExtAbstractPropertyBrowser
{
    Q_OBJECT

public:
    QExtButtonPropertyBrowser(QWidget *parent = QEXT_NULLPTR);
    ~QExtButtonPropertyBrowser() QEXT_OVERRIDE;

    void setExpanded(QExtBrowserItem *item, bool expanded);
    bool isExpanded(QExtBrowserItem *item) const;

Q_SIGNALS:
    void collapsed(QExtBrowserItem *item);
    void expanded(QExtBrowserItem *item);

protected:
    virtual void itemInserted(QExtBrowserItem *item, QExtBrowserItem *afterItem) QEXT_OVERRIDE;
    virtual void itemRemoved(QExtBrowserItem *item) QEXT_OVERRIDE;
    virtual void itemChanged(QExtBrowserItem *item) QEXT_OVERRIDE;

private:
    QExtButtonPropertyBrowserPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtButtonPropertyBrowser)
    QEXT_DISABLE_COPY_MOVE(QExtButtonPropertyBrowser)
    Q_PRIVATE_SLOT(d_func(), void slotUpdate())
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed())
    Q_PRIVATE_SLOT(d_func(), void slotToggled(bool))

};


/***********************************************************************************************************************
** groupbox property browser
***********************************************************************************************************************/
class QExtGroupBoxPropertyBrowserPrivate;
class QEXT_WIDGETS_API QExtGroupBoxPropertyBrowser : public QExtAbstractPropertyBrowser
{
    Q_OBJECT

public:
    QExtGroupBoxPropertyBrowser(QWidget *parent = QEXT_NULLPTR);
    ~QExtGroupBoxPropertyBrowser() QEXT_OVERRIDE;

protected:
    virtual void itemInserted(QExtBrowserItem *item, QExtBrowserItem *afterItem) QEXT_OVERRIDE;
    virtual void itemRemoved(QExtBrowserItem *item) QEXT_OVERRIDE;
    virtual void itemChanged(QExtBrowserItem *item) QEXT_OVERRIDE;

private:
    QExtGroupBoxPropertyBrowserPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtGroupBoxPropertyBrowser)
    QEXT_DISABLE_COPY_MOVE(QExtGroupBoxPropertyBrowser)
    Q_PRIVATE_SLOT(d_func(), void slotUpdate())
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed())

};


/***********************************************************************************************************************
** tree property browser
***********************************************************************************************************************/
class QTreeWidgetItem;
class QExtTreePropertyBrowserPrivate;
class QEXT_WIDGETS_API QExtTreePropertyBrowser : public QExtAbstractPropertyBrowser
{
    Q_OBJECT
    Q_ENUMS(ResizeMode)
    Q_PROPERTY(int indentation READ indentation WRITE setIndentation)
    Q_PROPERTY(bool rootIsDecorated READ rootIsDecorated WRITE setRootIsDecorated)
    Q_PROPERTY(bool alternatingRowColors READ alternatingRowColors WRITE setAlternatingRowColors)
    Q_PROPERTY(bool headerVisible READ isHeaderVisible WRITE setHeaderVisible)
    Q_PROPERTY(ResizeMode resizeMode READ resizeMode WRITE setResizeMode)
    Q_PROPERTY(int splitterPosition READ splitterPosition WRITE setSplitterPosition)
    Q_PROPERTY(bool propertiesWithoutValueMarked READ propertiesWithoutValueMarked WRITE setPropertiesWithoutValueMarked)

public:
    enum ResizeMode
    {
        Interactive,
        Stretch,
        Fixed,
        ResizeToContents
    };

    QExtTreePropertyBrowser(QWidget *parent = QEXT_NULLPTR);
    ~QExtTreePropertyBrowser() QEXT_OVERRIDE;

    int indentation() const;
    void setIndentation(int i);

    bool rootIsDecorated() const;
    void setRootIsDecorated(bool show);

    bool alternatingRowColors() const;
    void setAlternatingRowColors(bool enable);

    bool isHeaderVisible() const;
    void setHeaderVisible(bool visible);

    ResizeMode resizeMode() const;
    void setResizeMode(ResizeMode mode);

    int splitterPosition() const;
    void setSplitterPosition(int position);

    void setExpanded(QExtBrowserItem *item, bool expanded);
    bool isExpanded(QExtBrowserItem *item) const;

    bool isItemVisible(QExtBrowserItem *item) const;
    void setItemVisible(QExtBrowserItem *item, bool visible);

    void setBackgroundColor(QExtBrowserItem *item, const QColor &color);
    QColor backgroundColor(QExtBrowserItem *item) const;
    QColor calculatedBackgroundColor(QExtBrowserItem *item) const;

    void setPropertiesWithoutValueMarked(bool mark);
    bool propertiesWithoutValueMarked() const;

    void editItem(QExtBrowserItem *item);

Q_SIGNALS:
    void collapsed(QExtBrowserItem *item);
    void expanded(QExtBrowserItem *item);

protected:
    virtual void itemInserted(QExtBrowserItem *item, QExtBrowserItem *afterItem) QEXT_OVERRIDE;
    virtual void itemRemoved(QExtBrowserItem *item) QEXT_OVERRIDE;
    virtual void itemChanged(QExtBrowserItem *item) QEXT_OVERRIDE;

private:
    QExtTreePropertyBrowserPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtTreePropertyBrowser)
    QEXT_DISABLE_COPY_MOVE(QExtTreePropertyBrowser)

    Q_PRIVATE_SLOT(d_func(), void slotCollapsed(const QModelIndex &))
    Q_PRIVATE_SLOT(d_func(), void slotExpanded(const QModelIndex &))
    Q_PRIVATE_SLOT(d_func(), void slotCurrentBrowserItemChanged(QExtBrowserItem *))
    Q_PRIVATE_SLOT(d_func(), void slotCurrentTreeItemChanged(QTreeWidgetItem *, QTreeWidgetItem *))

};


/***********************************************************************************************************************
** variant property
***********************************************************************************************************************/
typedef QMap<int, QIcon> QtIconMap;
class QExtVariantPropertyManager;
class QExtVariantPropertyPrivate;
class QEXT_WIDGETS_API QExtVariantProperty : public QExtProperty
{
public:
    ~QExtVariantProperty() QEXT_OVERRIDE;

    QVariant value() const;
    QVariant attributeValue(const QString &attribute) const;
    int valueType() const;
    int propertyType() const;

    void setValue(const QVariant &value);
    void setAttribute(const QString &attribute, const QVariant &value);

protected:
    QExtVariantProperty(QExtVariantPropertyManager *manager);

private:
    friend class QExtVariantPropertyManager;
    QExtVariantPropertyPrivate *d_ptr;
};

class QExtVariantPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtVariantPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT
public:
    QExtVariantPropertyManager(QObject *parent = QEXT_NULLPTR);
    ~QExtVariantPropertyManager() QEXT_OVERRIDE;

    virtual QExtVariantProperty *addProperty(int propertyType, const QString &name = QString());

    int propertyType(const QExtProperty *property) const;
    int valueType(const QExtProperty *property) const;
    QExtVariantProperty *variantProperty(const QExtProperty *property) const;

    virtual bool isPropertyTypeSupported(int propertyType) const;
    virtual int valueType(int propertyType) const;
    virtual QStringList attributes(int propertyType) const;
    virtual int attributeType(int propertyType, const QString &attribute) const;

    virtual QVariant value(const QExtProperty *property) const;
    virtual QVariant attributeValue(const QExtProperty *property, const QString &attribute) const;

    static int enumTypeId();
    static int flagTypeId();
    static int groupTypeId();
    static int iconMapTypeId();

public Q_SLOTS:
    virtual void setValue(QExtProperty *property, const QVariant &val);
    virtual void setAttribute(QExtProperty *property, const QString &attribute, const QVariant &value);

Q_SIGNALS:
    void valueChanged(QExtProperty *property, const QVariant &val);
    void attributeChanged(QExtProperty *property, const QString &attribute, const QVariant &val);

protected:
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;
    QIcon valueIcon(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual bool hasValue(const QExtProperty *property) const QEXT_OVERRIDE;
    virtual void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;
    virtual QExtProperty *createProperty() QEXT_OVERRIDE;

private:
    QExtVariantPropertyManagerPrivate *d_ptr;
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, int, int))
    Q_PRIVATE_SLOT(d_func(), void slotSingleStepChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, double, double))
    Q_PRIVATE_SLOT(d_func(), void slotSingleStepChanged(QExtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotDecimalsChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QString &))
    Q_PRIVATE_SLOT(d_func(), void slotRegExpChanged(QExtProperty *, const QRegExp &))
    Q_PRIVATE_SLOT(d_func(), void slotEchoModeChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QDate &))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, const QDate &, const QDate &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QTime &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QDateTime &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QKeySequence &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QChar &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QLocale &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QPoint &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QPointF &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QSize &))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, const QSize &, const QSize &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QSizeF &))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtProperty *, const QSizeF &, const QSizeF &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QRect &))
    Q_PRIVATE_SLOT(d_func(), void slotConstraintChanged(QExtProperty *, const QRect &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QRectF &))
    Q_PRIVATE_SLOT(d_func(), void slotConstraintChanged(QExtProperty *, const QRectF &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QColor &))
    Q_PRIVATE_SLOT(d_func(), void slotEnumNamesChanged(QExtProperty *, const QStringList &))
    Q_PRIVATE_SLOT(d_func(), void slotEnumIconsChanged(QExtProperty *, const QMap<int, QIcon> &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QSizePolicy &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QFont &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtProperty *, const QCursor &))
    Q_PRIVATE_SLOT(d_func(), void slotFlagNamesChanged(QExtProperty *, const QStringList &))
    Q_PRIVATE_SLOT(d_func(), void slotReadOnlyChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotTextVisibleChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyInserted(QExtProperty *, QExtProperty *, QExtProperty *))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyRemoved(QExtProperty *, QExtProperty *))
    Q_DECLARE_PRIVATE(QExtVariantPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtVariantPropertyManager)
};

class QExtVariantEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtVariantEditorFactory : public QExtAbstractEditorFactory<QExtVariantPropertyManager>
{
    Q_OBJECT
public:
    QExtVariantEditorFactory(QObject *parent = QEXT_NULLPTR);
    ~QExtVariantEditorFactory() QEXT_OVERRIDE;

protected:
    void connectPropertyManager(QExtVariantPropertyManager *manager) QEXT_OVERRIDE;
    void disconnectPropertyManager(QExtVariantPropertyManager *manager) QEXT_OVERRIDE;
    QWidget *createEditor(QExtVariantPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtVariantEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtVariantEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtVariantEditorFactory)
};

Q_DECLARE_METATYPE(QIcon)
Q_DECLARE_METATYPE(QtIconMap)

#endif // _QEXTPROPERTYBROWSER_H
