#ifndef _QEXTPROPERTYBROWSER_H
#define _QEXTPROPERTYBROWSER_H

#include <qextWidgetGlobal.h>

#include <QSet>
#include <QIcon>
#include <QWidget>
#include <QLineEdit>
#include <QTreeWidget>

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
    friend class QExtAbstractPropertyEditor;
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
     * @brief Creates an abstract property browser with the given @a parent.
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
     * @brief Returns the property browser's list of all items associated with the given @a property.
     * There is one item per instance of the property in the browser.
     *
     * @sa topLevelItem()
     */
    QList<QExtBrowserItem *> items(QExtProperty *property) const;

    /**
     * @brief Returns the top-level items associated with the given @a property.
     *
     * Returns 0 if @a property wasn't inserted into this property browser or isn't a top-level one.
     *
     * @sa topLevelItems(), items()
     */
    QExtBrowserItem *topLevelItem(QExtProperty *property) const;

    /**
     * @brief Connects the given @a manager to the given @a factory, ensuring that properties of the @a manager's type
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
     * In this example the @c myInteger property's value is displayed with a QSpinBox widget, while the @c myDouble
     * property's value is displayed with a QDoubleSpinBox widget.
     *
     * Note that a factory can be associated with many managers, but a manager can only be associated with one single
     * factory.  If the given @a manager already is associated with another factory, the old association is broken before
     * the new one established.
     *
     * This function ensures that the given @a manager and the given @a factory are compatible, and it automatically
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
     * @brief Removes the association between the given @a manager and the factory bound to it, automatically calling the
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
     * @brief Sets the current item in the property browser to @a item.
     *
     * @sa currentItem(), currentItemChanged()
     */
    void setCurrentItem(QExtBrowserItem *);

Q_SIGNALS:
    void currentItemChanged(QExtBrowserItem *);

public Q_SLOTS:
    /**
     * @brief Removes the specified @a property (and its subproperties) from the property browser's list of top level
     * properties. All items that were associated with the given @a property and its children are deleted.
     *
     * Note that the properties are @e not deleted since they can still be used in other editors.
     *
     * @sa clear(), QExtProperty::removeSubProperty(), properties()
     */
    void removeProperty(QExtProperty *property);

    /**
     * @brief Appends the given @a property (and its subproperties) to the property browser's list of top level properties.
     * Returns the item created by property browser which is associated with the @a property.
     * In order to get all children items created by the property browser in this call, the returned item should be traversed.
     *
     * If the specified @a property is already added, this function does nothing and returns 0.
     *
     * @sa insertProperty(), QExtProperty::addSubProperty(), properties()
     */
    QExtBrowserItem *addProperty(QExtProperty *property);

    /**
     * @brief Inserts the given @a property (and its subproperties) after the specified @a afterProperty in the browser's
     * list of top level properties. Returns item created by property browser which is associated with the @a property.
     * In order to get all children items created by the property browser in this call returned item should be traversed.
     *
     * If the specified @a afterProperty is 0, the given @a property is inserted at the beginning of the list.
     * If @a property is already inserted, this function does nothing and returns 0.
     *
     * @sa addProperty(), QExtProperty::insertSubProperty(), properties()
     */
    QExtBrowserItem *insertProperty(QExtProperty *property, QExtProperty *afterProperty);

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
    virtual void itemRemoved(QExtBrowserItem *item) = 0;

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
     * @sa QExtProperty, items()
     * @note can be tooltip, statustip, whatsthis, name, icon, text.
     */
    virtual void itemChanged(QExtBrowserItem *item) = 0;

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
    virtual QWidget *createEditor(QExtProperty *property, QWidget *parent);

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
     * @brief Creates a manager with the given @a parent.
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
     * @brief Creates a manager with the given @a parent.
     */
    QExtIntPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * @brief Destroys this manager, and all the properties it has created.
     */
    ~QExtIntPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value.
     * If the given property is not managed by this manager, this function returns 0.
     *
     * @sa setValue()
     */
    int value(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's minimum value.
     *
     * @sa setMinimum(), maximum(), setRange()
     */
    int minimum(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's maximum value.
     *
     * @sa setMaximum(), minimum(), setRange()
     */
    int maximum(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's step value.
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
     * @brief Sets the value of the given @a property to @a value.
     * If the specified @a value is not valid according to the given @a property's range, the @a value is adjusted to
     * the nearest valid value within the range.
     *
     * @sa value(), setRange(), valueChanged()
     */
    void setValue(QExtProperty *property, int val);

    /**
     * @brief Sets the minimum value for the given @a property to @a minVal.
     * When setting the minimum value, the maximum and current values are adjusted if necessary (ensuring that the range
     * remains valid and that the current value is within the range).
     *
     * @sa minimum(), setRange(), rangeChanged()
     */
    void setMinimum(QExtProperty *property, int minVal);

    /**
     * @brief Sets the maximum value for the given @a property to @a maxVal.
     * When setting maximum value, the minimum and current values are adjusted if necessary (ensuring that the range
     * remains valid and that the current value is within the range).
     *
     * @sa maximum(), setRange(), rangeChanged()
     */
    void setMaximum(QExtProperty *property, int maxVal);

    /**
     * @brief Sets the range of valid values.
     * This is a convenience function defining the range of valid values in one go; setting the @a minimum and
     * @a maximum values for the given @a property with a single function call.
     *
     * When setting a new range, the current value is adjusted if necessary (ensuring that the value remains within range).
     *
     * @sa setMinimum(), setMaximum(), rangeChanged()
     */
    void setRange(QExtProperty *property, int minVal, int maxVal);

    /**
     * @brief Sets the step value for the given @a property to @a step.
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
     * the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, int val);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its range of valid values,
     * passing a pointer to the @a property and the new @a minimum and @a maximum values.
     *
     * @sa setRange()
     */
    void rangeChanged(QExtProperty *property, int minVal, int maxVal);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its single step property,
     * passing a pointer to the @a property and the new @a step value
     *
     * @sa setSingleStep()
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


/**
 * @class QExtBoolPropertyManager
 * @brief The QExtBoolPropertyManager class provides and manages boolean properties.
 * The property's value can be retrieved using the value() function, and set using the setValue() slot.
 *
 * In addition, QExtBoolPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtAbstractPropertyManager, QExtCheckBoxFactory
 */
class QExtBoolPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtBoolPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtBoolPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtBoolPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by @e this manager, this function returns false.
     *
     * @sa setValue()
     */
    bool value(const QExtProperty *property) const;
    bool textVisible(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     *
     * @sa value()
     */
    void setValue(QExtProperty *property, bool val);
    void setTextVisible(QExtProperty *property, bool textVisible);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     */
    void valueChanged(QExtProperty *property, bool val);
    void textVisibleChanged(QExtProperty *property, bool);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QIcon valueIcon(const QExtProperty *property) const QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

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
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtDoublePropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys  this manager, and all the properties it has created.
     */
    ~QExtDoublePropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value.
     * If the given property is not managed by this manager, this function returns 0.
     *
     * @sa setValue()
     */
    double value(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's minimum value.
     *
     * @sa maximum(), setRange()
     */
    double minimum(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's maximum value.
     *
     * @sa minimum(), setRange()
     */
    double maximum(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's step value.
     * The step is typically used to increment or decrement a property value while pressing an arrow key.
     *
     * @sa setSingleStep()
     */
    double singleStep(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's precision, in decimals.
     *
     * @sa setDecimals()
     */
    int decimals(const QExtProperty *property) const;

    /**
     * @brief Returns read-only status of the property.
     * When property is read-only it's value can be selected and copied from editor but not modified.
     *
     * @sa QExtDoublePropertyManager::setReadOnly
     */
    bool isReadOnly(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     * If the specified @a value is not valid according to the given @a property's range, the @a value is adjusted to
     * the nearest valid value within the range.
     *
     * @sa value(), setRange(), valueChanged()
     */
    void setValue(QExtProperty *property, double val);

    /**
     * @brief Sets the minimum value for the given @a property to @a minVal.
     * When setting the minimum value, the maximum and current values are adjusted if necessary (ensuring that the range
     * remains valid and that the current value is within in the range).
     *
     * @sa minimum(), setRange(), rangeChanged()
     */
    void setMinimum(QExtProperty *property, double minVal);

    /**
     * @brief Sets the maximum value for the given @a property to @a maxVal.
     * When setting the maximum value, the minimum and current values are adjusted if necessary (ensuring that the range
     * remains valid and that the current value is within in the range).
     *
     * @sa maximum(), setRange(), rangeChanged()
     */
    void setMaximum(QExtProperty *property, double maxVal);

    /**
     * @brief Sets the range of valid values.
     * This is a convenience function defining the range of valid values in one go; setting the @a minimum and @a
     * maximum values for the given @a property with a single function call.
     * When setting a new range, the current value is adjusted if necessary (ensuring that the value remains within range).
     *
     * @sa setMinimum(), setMaximum(), rangeChanged()
     */
    void setRange(QExtProperty *property, double minVal, double maxVal);

    /**
     * @brief Sets the step value for the given @a property to @a step.
     * The step is typically used to increment or decrement a property value while pressing an arrow key.
     *
     * @sa singleStep()
     */
    void setSingleStep(QExtProperty *property, double step);

    /**
     * @brief Sets the precision of the given @a property to @a prec.
     * The valid decimal range is 0-13. The default is 2.
     *
     * @sa decimals()
     */
    void setDecimals(QExtProperty *property, int prec);

    /**
     * @brief Sets read-only status of the property.
     *
     * @sa QExtDoublePropertyManager::setReadOnly
     */
    void setReadOnly(QExtProperty *property, bool readOnly);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, double val);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its range of valid values,
     * passing a pointer to the @a property and the new @a minimum and @a maximum values
     */
    void rangeChanged(QExtProperty *property, double minVal, double maxVal);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its single step property,
     * passing a pointer to the @a property and the new @a step value
     *
     * @sa setSingleStep()
     */
    void singleStepChanged(QExtProperty *property, double step);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its precision of value,
     * passing a pointer to the @a property and the new @a prec value
     * @sa setDecimals()
     */
    void decimalsChanged(QExtProperty *property, int prec);
    void readOnlyChanged(QExtProperty *property, bool readOnly);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtDoublePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtDoublePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtDoublePropertyManager)
};


/**
 * @class QExtStringPropertyManager
 * @brief The QExtStringPropertyManager provides and manages QString properties.
 * A string property's value can be retrieved using the value() function, and set using the setValue() slot.
 * The current value can be checked against a regular expression. To set the regular expression use the setRegExp()
 * slot, use the regExp() function to retrieve the currently set expression.
 *
 * In addition, QExtStringPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes, and the regExpChanged() signal which is emitted whenever such a property changes
 * its currently set regular expression.
 *
 * @sa QExtAbstractPropertyManager, QExtLineEditFactory
 */
class QExtStringPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtStringPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtStringPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtStringPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value.
     * If the given property is not managed by this manager, this function returns an empty string.
     *
     * @sa setValue()
     */
    QString value(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's currently set regular expression.
     * If the given @a property is not managed by this manager, this function returns an empty expression.
     *
     * @sa setRegExp()
     */
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
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, const QString &val);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its currenlty set regular
     * expression, passing a pointer to the @a property and the new @a regExp as parameters.
     *
     * @sa setRegExp()
     */
    void regExpChanged(QExtProperty *property, const QRegExp &regExp);
    void echoModeChanged(QExtProperty *property, const int);
    void readOnlyChanged(QExtProperty *property, bool);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString displayText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtStringPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtStringPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtStringPropertyManager)
};


/**
 * @class QExtDatePropertyManager
 * @brief The QExtDatePropertyManager provides and manages QDate properties.
 * A date property has a current value, and a range specifying the valid dates.
 * The range is defined by a minimum and a maximum value.
 *
 * The property's values can be retrieved using the minimum(), maximum() and value() functions, and can be set using
 * the setMinimum(), setMaximum() and setValue() slots. Alternatively, the range can be defined in one go using the
 * setRange() slot.
 *
 * In addition, QExtDatePropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes, and the rangeChanged() signal which is emitted whenever such a property changes
 * its range of valid dates.
 *
 * @sa QExtAbstractPropertyManager, QExtDateEditFactory, QExtDateTimePropertyManager
 */
class QExtDatePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtDatePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtDatePropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtDatePropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by @e this manager, this function returns an invalid date.
     *
     * @sa setValue()
     */
    QDate value(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a  property's  minimum date.
     *
     * @sa maximum(), setRange()
     */
    QDate minimum(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's maximum date.
     *
     * @sa minimum(), setRange()
     */
    QDate maximum(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     * If the specified @a value is not a valid date according to the given @a property's range, the value is
     * adjusted to the nearest valid value within the range.
     *
     * @sa value(), setRange(), valueChanged()
     */
    void setValue(QExtProperty *property, const QDate &val);

    /**
     * @brief Sets the minimum value for the given @a property to @a minVal.
     * When setting the minimum value, the maximum and current values are adjusted if necessary (ensuring that the
     * range remains valid and that the current value is within in the range).
     *
     *  @sa minimum(), setRange()
     */
    void setMinimum(QExtProperty *property, const QDate &minVal);

    /**
     * @brief Sets the maximum value for the given @a property to @a maxVal.
     * When setting the maximum value, the minimum and current values are adjusted if necessary (ensuring that the
     * range remains valid and that the current value is within in the range).
     *
     * @sa maximum(), setRange()
     */
    void setMaximum(QExtProperty *property, const QDate &maxVal);

    /**
     * @brief Sets the range of valid dates.
     * This is a convenience function defining the range of valid dates in one go; setting the @a minimum and @a
     * maximum values for the given @a property with a single function call.
     *
     * When setting a new date range, the current value is adjusted if necessary (ensuring that the value remains in
     * date range).
     *
     * @sa setMinimum(), setMaximum(), rangeChanged()
     */
    void setRange(QExtProperty *property, const QDate &minVal, const QDate &maxVal);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, const QDate &val);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its range of valid dates,
     * passing a pointer to the @a property and the new @a minimum and @a maximum dates.
     *
     * @sa setRange()
     */
    void rangeChanged(QExtProperty *property, const QDate &minVal, const QDate &maxVal);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtDatePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtDatePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtDatePropertyManager)
};


/**
 * @class QExtTimePropertyManager
 * @brief The QExtTimePropertyManager provides and manages QTime properties.
 * A time property's value can be retrieved using the value() function, and set using the setValue() slot.
 *
 * In addition, QExtTimePropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtAbstractPropertyManager, QExtTimeEditFactory
 */
class QExtTimePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtTimePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtTimePropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtTimePropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value.
     * If the given property is not managed by this manager, this function returns an invalid time object.
     *
     * @sa setValue()
     */
    QTime value(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtProperty *property, const QTime &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, const QTime &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtTimePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtTimePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtTimePropertyManager)
};

/**
 * @class QExtDateTimePropertyManager
 * @brief The QExtDateTimePropertyManager provides and manages QDateTime properties.
 * A date and time property has a current value which can be retrieved using the value() function, and set using
 * the setValue() slot. In addition, QExtDateTimePropertyManager provides the valueChanged() signal which is emitted
 * whenever a property created by this manager changes.
 *
 * @sa QExtAbstractPropertyManager, QExtDateTimeEditFactory, QExtDatePropertyManager
 */
class QExtDateTimePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtDateTimePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtDateTimePropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtDateTimePropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns an invalid QDateTime object.
     *
     * @sa setValue()
     */
    QDateTime value(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtProperty *property, const QDateTime &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     */
    void valueChanged(QExtProperty *property, const QDateTime &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtDateTimePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtDateTimePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtDateTimePropertyManager)
};


/**
 * @class QExtKeySequencePropertyManager
 * @brief The QExtKeySequencePropertyManager provides and manages QKeySequence properties.
 * A key sequence's value can be retrieved using the value() function, and set using the setValue() slot.
 *
 * In addition, QExtKeySequencePropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtAbstractPropertyManager
 */
class QExtKeySequencePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtKeySequencePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtKeySequencePropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtKeySequencePropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns an empty QKeySequence object.
     *
     * @sa setValue()
     */
    QKeySequence value(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtProperty *property, const QKeySequence &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     */
    void valueChanged(QExtProperty *property, const QKeySequence &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtKeySequencePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtKeySequencePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtKeySequencePropertyManager)
};

/**
 * @class QExtCharPropertyManager
 * @brief The QExtCharPropertyManager provides and manages QChar properties.
 * A char's value can be retrieved using the value() function, and set using the setValue() slot.
 *
 * In addition, QExtCharPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtAbstractPropertyManager
 */
class QExtCharPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtCharPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtCharPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtCharPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns an null QChar object.
     *
     * @sa setValue()
     */
    QChar value(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtProperty *property, const QChar &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     */
    void valueChanged(QExtProperty *property, const QChar &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtCharPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtCharPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtCharPropertyManager)
};

/**
 * @class QExtLocalePropertyManager
 * @brief The QExtLocalePropertyManager provides and manages QLocale properties.
 * A locale property has nested @e language and @e country subproperties. The top-level property's value can be
 * retrieved using the value() function, and set using the setValue() slot.
 *
 * The subproperties are created by QExtEnumPropertyManager object.
 * These submanager can be retrieved using the subEnumPropertyManager() function. In order to provide editing widgets
 * for the subproperties in a property browser widget, this manager must be associated with editor factory.
 *
 * In addition, QExtLocalePropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtAbstractPropertyManager, QExtEnumPropertyManager
 */
class QExtEnumPropertyManager;
class QExtLocalePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtLocalePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtLocalePropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtLocalePropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that creates the nested @e language and @e country subproperties.
     * In order to provide editing widgets for the mentioned subproperties in a property browser widget, this manager
     * must be associated with an editor factory.
     *
     * @sa QExtAbstractPropertyBrowser::setFactoryForManager()
     */
    QExtEnumPropertyManager *subEnumPropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given property is not managed by this manager, this function returns the default locale.
     *
     * @sa setValue()
     */
    QLocale value(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value. Nested properties are updated automatically.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtProperty *property, const QLocale &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, const QLocale &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtLocalePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtLocalePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtLocalePropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotEnumChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

/**
 * @class QExtPointPropertyManager
 * @brief The QExtPointPropertyManager provides and manages QPoint properties
 * A point property has nested @e x and @e y subproperties. The top-level property's value can be retrieved using
 * the value() function, and set using the setValue() slot.
 *
 * The subproperties are created by a QExtIntPropertyManager object. This manager can be retrieved using the
 * subIntPropertyManager() function. In order to provide editing widgets for the subproperties in a property browser
 * widget, this manager must be associated with an editor factory.
 *
 * In addition, QExtPointPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtAbstractPropertyManager, QExtIntPropertyManager, QExtPointFPropertyManager
 */
class QExtPointPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPointPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPointPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPointPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that creates the nested @e x and @e y subproperties.
     *
     * In order to provide editing widgets for the subproperties in a property browser widget, this manager must be
     * associated with an editor factory.
     *
     * @sa QExtAbstractPropertyBrowser::setFactoryForManager()
     */
    QExtIntPropertyManager *subIntPropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns a point with coordinates (0, 0).
     *
     * @sa setValue()
     */
    QPoint value(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value. Nested properties are updated automatically.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtProperty *property, const QPoint &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, const QPoint &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtPointPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPointPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPointPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

/**
 * @class QExtPointFPropertyManager
 * @brief The QExtPointFPropertyManager provides and manages QPointF properties.
 *
 * A point property has nested @e x and @e y subproperties. The top-level property's value can be retrieved using the
 * value() function, and set using the setValue() slot.
 *
 * The subproperties are created by a QExtDoublePropertyManager object. This manager can be retrieved using the
 * subDoublePropertyManager() function. In order to provide editing widgets for the subproperties in a property browser
 * widget, this manager must be associated with an editor factory.
 *
 * In addition, QExtPointFPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtAbstractPropertyManager, QExtDoublePropertyManager, QExtPointPropertyManager
 */
class QExtPointFPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPointFPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPointFPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPointFPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that creates the nested @e x and @e y subproperties.
     *
     * In order to provide editing widgets for the subproperties in a property browser widget, this manager must be
     * associated with an editor factory.
     *
     * @sa QExtAbstractPropertyBrowser::setFactoryForManager()
     */
    QExtDoublePropertyManager *subDoublePropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns a point with coordinates (0, 0).
     *
     * @sa setValue()
     */
    QPointF value(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's precision, in decimals.
     *
     * @sa setDecimals()
     */
    int decimals(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the precision of the given @a property to @a prec.
     * The valid decimal range is 0-13. The default is 2.
     *
     * @sa decimals()
     */
    void setDecimals(QExtProperty *property, int prec);

    /**
     * @brief Sets the value of the given @a property to @a value. Nested properties are updated automatically.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtProperty *property, const QPointF &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its precision of value,
     * passing a pointer to the @a property and the new @a prec value
     *
     * @sa setDecimals()
     */
    void decimalsChanged(QExtProperty *property, int prec);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, const QPointF &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtPointFPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPointFPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPointFPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotDoubleChanged(QExtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};


/**
 * @class QExtSizePropertyManager
 * @brief The QExtSizePropertyManager provides and manages QSize properties.
 * A size property has nested @e width and @e height subproperties. The top-level property's value can be retrieved
 * using the value() function, and set using the setValue() slot.
 *
 * The subproperties are created by a QExtIntPropertyManager object. This manager can be retrieved using the
 * subIntPropertyManager() function. In order to provide editing widgets for the subproperties in a property browser
 * widget, this manager must be associated with an editor factory.
 *
 * A size property also has a range of valid values defined by a minimum size and a maximum size. These sizes can be
 * retrieved using the minimum() and the maximum() functions, and set using the setMinimum() and setMaximum() slots.
 * Alternatively, the range can be defined in one go using the setRange() slot.
 *
 * In addition, QExtSizePropertyManager provides the valueChanged() signal which is emitted whenever a property created
 * by this manager changes, and the rangeChanged() signal which is emitted whenever such a property changes its range
 * of valid sizes.
 *
 * @sa QExtAbstractPropertyManager, QExtIntPropertyManager, QExtSizeFPropertyManager
 */
class QExtSizePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtSizePropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtSizePropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtSizePropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that creates the nested @e width and @e height subproperties.
     * In order to provide editing widgets for the @e width and @e height properties in a property browser widget,
     * this manager must be associated with an editor factory.
     *
     * @sa QExtAbstractPropertyBrowser::setFactoryForManager()
     */
    QExtIntPropertyManager *subIntPropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns an invalid size
     *
     * @sa setValue()
     */
    QSize value(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's minimum size value.
     *
     * sa setMinimum(), maximum(), setRange()
     */
    QSize minimum(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's maximum size value.
     *
     * sa setMaximum(), minimum(), setRange()
     */
    QSize maximum(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     *
     * If the specified @a value is not valid according to the given @a property's size range, the @a value is adjusted
     * to the nearest valid value within the size range.
     *
     * @sa value(), setRange(), valueChanged()
     */
    void setValue(QExtProperty *property, const QSize &val);

    /**
     * @brief Sets the minimum size value for the given @a property to @a minVal.
     * When setting the minimum size value, the maximum and current values are adjusted if necessary (ensuring that
     * the size range remains valid and that the current value is within the range).
     *
     * @sa minimum(), setRange(), rangeChanged()
     */
    void setMinimum(QExtProperty *property, const QSize &minVal);

    /**
     * @brief Sets the maximum size value for the given @a property to @a maxVal.
     * When setting the maximum size value, the minimum and current values are adjusted if necessary (ensuring that the
     * size range remains valid and that the current value is within the range).
     *
     * @sa maximum(), setRange(), rangeChanged()
     */
    void setMaximum(QExtProperty *property, const QSize &maxVal);

    /**
     * @brief Sets the range of valid values.
     * This is a convenience function defining the range of valid values in one go; setting the @a minimum and @a
     * maximum values for the given @a property with a single function call.
     *
     * When setting a new range, the current value is adjusted if necessary (ensuring that the value remains within
     * the range).
     *
     * @sa setMinimum(), setMaximum(), rangeChanged()
     */
    void setRange(QExtProperty *property, const QSize &minVal, const QSize &maxVal);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, const QSize &val);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its range of valid sizes,
     * passing a pointer to the @a property and the new @a minimum and @a maximum sizes.
     *
     * @sa setRange()
     */
    void rangeChanged(QExtProperty *property, const QSize &minVal, const QSize &maxVal);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtSizePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtSizePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtSizePropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};


/**
 * @class QExtSizeFPropertyManager
 * @brief The QExtSizeFPropertyManager provides and manages QSizeF properties.
 * A size property has nested @e width and @e height subproperties. The top-level property's value can be retrieved
 * using the value() function, and set using the setValue() slot.
 *
 * The subproperties are created by a QExtDoublePropertyManager object. This manager can be retrieved using the
 * subDoublePropertyManager() function. In order to provide editing widgets for the subproperties in a property browser
 * widget, this manager must be associated with an editor factory.
 *
 * A size property also has a range of valid values defined by a minimum size and a maximum size. These sizes can be
 * retrieved using the minimum() and the maximum() functions, and set using the setMinimum() and setMaximum() slots.
 * Alternatively, the range can be defined in one go using the setRange() slot.
 *
 * In addition, QExtSizeFPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes, and the rangeChanged() signal which is emitted whenever such a property changes
 * its range of valid sizes.
 *
 * @sa QExtAbstractPropertyManager, QExtDoublePropertyManager, QExtSizePropertyManager
 */
class QExtSizeFPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtSizeFPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT
public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtSizeFPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtSizeFPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that creates the nested @e width and @e height subproperties.
     * In order to provide editing widgets for the @e width and @e height properties in a property browser widget,
     * this manager must be associated with an editor factory.
     *
     * @sa QExtAbstractPropertyBrowser::setFactoryForManager()
     */
    QExtDoublePropertyManager *subDoublePropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns an invalid size
     *
     * @sa setValue()
     */
    QSizeF value(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's minimum size value.
     *
     * @sa setMinimum(), maximum(), setRange()
     */
    QSizeF minimum(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's maximum size value.
     *
     * @sa setMaximum(), minimum(), setRange()
     */
    QSizeF maximum(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's precision, in decimals.
     *
     * @sa setDecimals()
     */
    int decimals(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the precision of the given @a property to @a prec.
     * The valid decimal range is 0-13. The default is 2.
     *
     * @sa decimals()
     */
    void setDecimals(QExtProperty *property, int prec);

    /**
     * @brief Sets the value of the given @a property to @a value.
     * If the specified @a value is not valid according to the given @a property's size range, the @a value is adjusted
     * to the nearest valid value within the size range.
     *
     * @sa value(), setRange(), valueChanged()
     */
    void setValue(QExtProperty *property, const QSizeF &val);

    /**
     * @brief Sets the minimum size value for the given @a property to @a minVal.
     * When setting the minimum size value, the maximum and current values are adjusted if necessary (ensuring that
     * the size range remains valid and that the current value is within the range).
     *
     * @sa minimum(), setRange(), rangeChanged()
     */
    void setMinimum(QExtProperty *property, const QSizeF &minVal);

    /**
     * @brief Sets the maximum size value for the given @a property to @a maxVal.
     * When setting the maximum size value, the minimum and current values are adjusted if necessary (ensuring that the
     * size range remains valid and that the current value is within the range).
     *
     * @sa maximum(), setRange(), rangeChanged()
     */
    void setMaximum(QExtProperty *property, const QSizeF &maxVal);

    /**
     * @brief Sets the range of valid values.
     * This is a convenience function defining the range of valid values in one go; setting the @a minimum and
     * @a maximum values for the given @a property with a single function call.
     *
     * When setting a new range, the current value is adjusted if necessary (ensuring that the value remains within
     * the range).
     *
     * @sa setMinimum(), setMaximum(), rangeChanged()
     */
    void setRange(QExtProperty *property, const QSizeF &minVal, const QSizeF &maxVal);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its precision of value,
     * passing a pointer to the @a property and the new @a prec value
     *
     * @sa setDecimals()
     */
    void decimalsChanged(QExtProperty *property, int prec);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, const QSizeF &val);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its range of valid sizes,
     * passing a pointer to the @a property and the new @a minimum and @a maximum sizes.
     *
     * @sa setRange()
     */
    void rangeChanged(QExtProperty *property, const QSizeF &minVal, const QSizeF &maxVal);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtSizeFPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtSizeFPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtSizeFPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotDoubleChanged(QExtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

/**
 * @class QExtRectPropertyManager
 * @brief The QExtRectPropertyManager provides and manages QRect properties.
 * A rectangle property has nested @e x, @e y, @e width and @e height subproperties. The top-level property's value
 * can be retrieved using the value() function, and set using the setValue() slot.
 *
 * The subproperties are created by a QExtIntPropertyManager object. This manager can be retrieved using the
 * subIntPropertyManager() function. In order to provide editing widgets for the subproperties in a property browser
 * widget, this manager must be associated with an editor factory.
 *
 * A rectangle property also has a constraint rectangle which can be retrieved using the constraint() function, and
 * set using the setConstraint() slot.
 *
 * In addition, QExtRectPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes, and the constraintChanged() signal which is emitted whenever such a property
 * changes its constraint rectangle.
 *
 * @sa QExtAbstractPropertyManager, QExtIntPropertyManager, QExtRectFPropertyManager
 */
class QExtRectPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtRectPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtRectPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * @brief Destroys this manager, and all the properties it has created.
     */
    ~QExtRectPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that creates the nested @e x, @e y, @e width and @e height subproperties.
     * In order to provide editing widgets for the mentioned subproperties in a property browser widget, this manager
     * must be associated with an editor factory.
     *
     * @sa QExtAbstractPropertyBrowser::setFactoryForManager()
     */
    QExtIntPropertyManager *subIntPropertyManager() const;

    /**
     * @brief Returns the given @a property's value
     *
     * If the given @a property is not managed by this manager, this function returns an invalid rectangle.
     *
     * @sa setValue(), constraint()
     */
    QRect value(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's constraining rectangle. If returned value is null QRect it means there
     * is no constraint applied.
     *
     * @sa value(), setConstraint()
     */
    QRect constraint(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value. Nested properties are updated automatically.
     *
     * If the specified @a value is not inside the given @a property's constraining rectangle, the value is adjusted
     * accordingly to fit within the constraint.
     *
     * @sa value(), setConstraint(), valueChanged()
     */
    void setValue(QExtProperty *property, const QRect &val);

    /**
     * @brief Sets the given @a property's constraining rectangle to @a constraint.
     * When setting the constraint, the current value is adjusted if necessary (ensuring that the current rectangle
     * value is inside the constraint). In order to reset the constraint pass a null QRect value.
     *
     * @sa setValue(), constraint(), constraintChanged()
     */
    void setConstraint(QExtProperty *property, const QRect &constraint);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, const QRect &val);

    /**
     * @brief This signal is emitted whenever property changes its constraint rectangle, passing a pointer to the
     * @a property and the new @a constraint rectangle as parameters.
     *
     * @sa setConstraint()
     */
    void constraintChanged(QExtProperty *property, const QRect &constraint);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtRectPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtRectPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtRectPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};


/**
 * @class QExtRectFPropertyManager
 * @brief The QExtRectFPropertyManager provides and manages QRectF properties.
 * A rectangle property has nested @e x, @e y, @e width and @e height subproperties. The top-level property's value
 * can be retrieved using the value() function, and set using the setValue() slot.
 *
 * The subproperties are created by a QExtDoublePropertyManager object. This manager can be retrieved using the
 * subDoublePropertyManager() function. In order to provide editing widgets for the subproperties in a property browser
 * widget, this manager must be associated with an editor factory.
 *
 * A rectangle property also has a constraint rectangle which can be retrieved using the constraint() function, and set
 * using the setConstraint() slot.
 *
 * In addition, QExtRectFPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes, and the constraintChanged() signal which is emitted whenever such a property
 * changes its constraint rectangle.
 *
 * @sa QExtAbstractPropertyManager, QExtDoublePropertyManager, QExtRectPropertyManager
 */
class QExtRectFPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtRectFPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtRectFPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtRectFPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that creates the nested @e x, @e y, @e width and @e height subproperties.
     * In order to provide editing widgets for the mentioned subproperties in a property browser widget, this manager
     * must be associated with an editor factory.
     *
     * @sa QExtAbstractPropertyBrowser::setFactoryForManager()
     */
    QExtDoublePropertyManager *subDoublePropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns an invalid rectangle.
     *
     * @sa setValue(), constraint()
     */
    QRectF value(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's constraining rectangle. If returned value is null QRectF it means there
     * is no constraint applied.
     *
     * @sa value(), setConstraint()
     */
    QRectF constraint(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's precision, in decimals.
     *
     * @sa setDecimals()
     */
    int decimals(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the precision of the given @a property to @a prec.
     * The valid decimal range is 0-13. The default is 2.
     *
     * @sa decimals()
     */
    void setDecimals(QExtProperty *property, int prec);

    /**
     * @brief Sets the value of the given @a property to @a value. Nested properties are updated automatically.
     * If the specified @a value is not inside the given @a property's constraining rectangle, the value is adjusted
     * accordingly to fit within the constraint.
     *
     * @sa value(), setConstraint(), valueChanged()
     */
    void setValue(QExtProperty *property, const QRectF &val);

    /**
     * @brief Sets the given @a property's constraining rectangle to @a constraint.
     * When setting the constraint, the current value is adjusted if necessary (ensuring that the current rectangle
     * value is inside the constraint). In order to reset the constraint pass a null QRectF value.
     *
     * @sa setValue(), constraint(), constraintChanged()
     */
    void setConstraint(QExtProperty *property, const QRectF &constraint);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its precision of value,
     * passing a pointer to the @a property and the new @a prec value
     *
     * @sa setDecimals()
     */
    void decimalsChanged(QExtProperty *property, int prec);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, const QRectF &val);

    /**
     * @brief This signal is emitted whenever property changes its constraint rectangle, passing a pointer to the
     * @a property and the new @a constraint rectangle as parameters.
     *
     * @sa setConstraint()
     */
    void constraintChanged(QExtProperty *property, const QRectF &constraint);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtRectFPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtRectFPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtRectFPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotDoubleChanged(QExtProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

/**
 * @class QExtEnumPropertyManager
 * @brief The QExtEnumPropertyManager provides and manages enum properties.
 * Each enum property has an associated list of enum names which can be retrieved using the enumNames() function,
 * and set using the corresponding setEnumNames() function. An enum property's value is represented by an index in
 * this list, and can be retrieved and set using the value() and setValue() slots respectively.
 *
 * Each enum value can also have an associated icon. The mapping from values to icons can be set using the
 * setEnumIcons() function and queried with the enumIcons() function.
 *
 * In addition, QExtEnumPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes. The enumNamesChanged() or enumIconsChanged() signal is emitted whenever the list
 * of enum names or icons is altered.
 *
 * sa QExtAbstractPropertyManager, QExtEnumEditorFactory
 */
class QExtEnumPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtEnumPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent
     */
    QExtEnumPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtEnumPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value which is an index in the list returned by enumNames()
     * If the given property is not managed by this manager, this function returns -1.
     *
     * @sa enumNames(), setValue()
     */
    int value(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's list of enum names.
     *
     * @sa value(), setEnumNames()
     */
    QStringList enumNames(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's map of enum values to their icons.
     *
     * @sa value(), setEnumIcons()
     */
    QMap<int, QIcon> enumIcons(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given  @a property to @a value.
     * The specified @a value must be less than the size of the given @a property's enumNames() list, and larger
     * than (or equal to) 0.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtProperty *property, int val);

    /**
     * @brief Sets the given @a property's list of enum names to @a enumNames. The @a property's current value is
     * reset to 0 indicating the first item of the list.
     *
     * If the specified @a enumNames list is empty, the @a property's current value is set to -1.
     *
     * @sa enumNames(), enumNamesChanged()
     */
    void setEnumNames(QExtProperty *property, const QStringList &names);

    /**
     * @brief Sets the given @a property's map of enum values to their icons to @a enumIcons.
     * Each enum value can have associated icon. This association is represented with passed @a enumIcons map.
     *
     * @sa enumNames(), enumNamesChanged()
     */
    void setEnumIcons(QExtProperty *property, const QMap<int, QIcon> &icons);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, int val);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its enum names, passing a
     * pointer to the @a property and the new @a names as parameters.
     *
     * @sa setEnumNames()
     */
    void enumNamesChanged(QExtProperty *property, const QStringList &names);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its enum icons, passing a
     * pointer to the @a property and the new mapping of values to @a icons as parameters.
     *
     * @sa setEnumIcons()
     */
    void enumIconsChanged(QExtProperty *property, const QMap<int, QIcon> &icons);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QIcon valueIcon(const QExtProperty *property) const QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtEnumPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtEnumPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtEnumPropertyManager)
};

/**
 * @class QExtFlagPropertyManager
 * @brief The QExtFlagPropertyManager provides and manages flag properties.
 * Each flag property has an associated list of flag names which can be retrieved using the flagNames() function,
 * and set using the corresponding setFlagNames() function.
 *
 * The flag manager provides properties with nested boolean subproperties representing each flag, i.e. a flag
 * property's value is the binary combination of the subproperties' values. A property's value can be retrieved and set
 * using the value() and setValue() slots respectively. The combination of flags is represented by single int
 * value - that's why it's possible to store up to 32 independent flags in one flag property.
 *
 * The subproperties are created by a QExtBoolPropertyManager object. This manager can be retrieved using the
 * subBoolPropertyManager() function. In order to provide editing widgets for the subproperties in a property browser
 * widget, this manager must be associated with an editor factory.
 *
 * In addition, QExtFlagPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes, and the flagNamesChanged() signal which is emitted whenever the list of flag names
 * is altered.
 *
 * @sa QExtAbstractPropertyManager, QExtBoolPropertyManager
 */
class QExtFlagPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtFlagPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtFlagPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtFlagPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that produces the nested boolean subproperties representing each flag.
     *
     * In order to provide editing widgets for the subproperties in a property browser widget, this manager must be
     * associated with an editor factory.
     *
     * @sa QExtAbstractPropertyBrowser::setFactoryForManager()
     */
    QExtBoolPropertyManager *subBoolPropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given property is not managed by this manager, this function returns 0.
     *
     * @sa flagNames(), setValue()
     */
    int value(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's list of flag names.
     *
     * @sa value(), setFlagNames()
     */
    QStringList flagNames(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value. Nested properties are updated automatically.
     *
     * The specified @a value must be less than the binary combination of the property's flagNames() list
     * size (i.e. less than 2\sup n, where @c n is the size of the list) and larger than (or equal to) 0.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtProperty *property, int val);

    /**
     * @brief Sets the given @a property's list of flag names to @a flagNames. The property's current value is reset
     * to 0 indicating the first item of the list.
     *
     * @sa flagNames(), flagNamesChanged()
     */
    void setFlagNames(QExtProperty *property, const QStringList &names);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a  property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, int val);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its flag names, passing a
     * pointer to the @a property and the new @a names as parameters.
     *
     * @sa setFlagNames()
     */
    void flagNamesChanged(QExtProperty *property, const QStringList &names);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtFlagPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtFlagPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtFlagPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotBoolChanged(QExtProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};

/**
 * @class QExtSizePolicyPropertyManager
 * @brief The QExtSizePolicyPropertyManager provides and manages QSizePolicy properties.
 * A size policy property has nested @e horizontalPolicy, @e verticalPolicy, @e horizontalStretch and @e verticalStretch
 * subproperties. The top-level property's value can be retrieved using the value() function, and set using the
 * setValue() slot.
 *
 * The subproperties are created by QExtIntPropertyManager and QExtEnumPropertyManager objects.
 * These managers can be retrieved using the subIntPropertyManager() and subEnumPropertyManager() functions respectively.
 * In order to provide editing widgets for the subproperties in a property browser widget, these managers must be
 * associated with editor factories.
 *
 * In addition, QExtSizePolicyPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtAbstractPropertyManager, QExtIntPropertyManager, QExtEnumPropertyManager
 */
class QExtSizePolicyPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtSizePolicyPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    explicit QExtSizePolicyPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtSizePolicyPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that creates the nested @e horizontalStretch and @e verticalStretch subproperties.
     * In order to provide editing widgets for the mentioned subproperties in a property browser widget, this manager
     * must be associated with an editor factory.
     *
     * @sa QExtAbstractPropertyBrowser::setFactoryForManager()
     */
    QExtIntPropertyManager *subIntPropertyManager() const;

    /**
     * @brief Returns the manager that creates the nested @e horizontalPolicy and @e verticalPolicy subproperties.
     *
     * In order to provide editing widgets for the mentioned subproperties in a property browser widget, this manager
     * must be associated with an editor factory.
     *
     * @sa QExtAbstractPropertyBrowser::setFactoryForManager()
     */
    QExtEnumPropertyManager *subEnumPropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given property is not managed by this manager, this function returns the default size policy.
     *
     * @sa setValue()
     */
    QSizePolicy value(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value. Nested properties are updated automatically.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtProperty *property, const QSizePolicy &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, const QSizePolicy &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtSizePolicyPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtSizePolicyPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtSizePolicyPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotEnumChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};


/**
 * @class QExtFontPropertyManager
 * @brief The QExtFontPropertyManager provides and manages QFont properties.
 * A font property has nested @e family, @e pointSize, @e bold, @e italic, @e underline, @e strikeOut and @e kerning
 * subproperties. The top-level property's value can be retrieved using the value() function, and set using the
 * setValue() slot.
 *
 * The subproperties are created by QExtIntPropertyManager, QExtEnumPropertyManager and QExtBoolPropertyManager objects.
 * These managers can be retrieved using the corresponding subIntPropertyManager(), subEnumPropertyManager() and
 * subBoolPropertyManager() functions. In order to provide editing widgets for the subproperties in a property browser
 * widget, these managers must be associated with editor factories.
 *
 * In addition, QExtFontPropertyManager provides the valueChanged() signal which is emitted whenever a property created
 * by this manager changes.
 *
 * @sa QExtAbstractPropertyManager, QExtEnumPropertyManager, QExtIntPropertyManager, QExtBoolPropertyManager
 */
class QExtFontPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtFontPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtFontPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtFontPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that creates the @e pointSize subproperty.
     * In order to provide editing widgets for the @e pointSize property in a property browser widget, this manager
     * must be associated with an editor factory.
     *
     * @sa QExtAbstractPropertyBrowser::setFactoryForManager()
     */
    QExtIntPropertyManager *subIntPropertyManager() const;

    /**
     * @brief Returns the manager that create the @e family subproperty.
     * In order to provide editing widgets for the @e family property in a property browser widget, this manager must
     * be associated with an editor factory.
     *
     * @sa QExtAbstractPropertyBrowser::setFactoryForManager()
     */
    QExtEnumPropertyManager *subEnumPropertyManager() const;

    /**
     * @brief Returns the manager that creates the  @e bold, @e italic, @e underline, @e strikeOut and @e kerning
     * subproperties.
     * In order to provide editing widgets for the mentioned properties in a property browser widget, this manager must
     * be associated with an editor factory.
     *
     * @sa QExtAbstractPropertyBrowser::setFactoryForManager()
     */
    QExtBoolPropertyManager *subBoolPropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given property is not managed by this manager, this function returns a font object that uses the
     * application's default font.
     *
     * @sa setValue()
     */
    QFont value(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value. Nested properties are updated automatically.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtProperty *property, const QFont &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, const QFont &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QIcon valueIcon(const QExtProperty *property) const QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

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


/**
 * @class QExtColorPropertyManager
 * @brief The QExtColorPropertyManager provides and manages QColor properties.
 * A color property has nested @e red, @e green and @e blue subproperties. The top-level property's value can be
 * retrieved using the value() function, and set using the setValue() slot.
 *
 * The subproperties are created by a QExtIntPropertyManager object.
 * This manager can be retrieved using the subIntPropertyManager() function.  In order to provide editing widgets for
 * the subproperties in a property browser widget, this manager must be associated with an editor factory.
 *
 * In addition, QExtColorPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtAbstractPropertyManager, QExtAbstractPropertyBrowser, QExtIntPropertyManager
 */
class QExtColorPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtColorPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtColorPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtColorPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that produces the nested @e red, @e green and @e blue subproperties.
     * In order to provide editing widgets for the subproperties in a property browser widget, this manager must be
     * associated with an editor factory.
     *
     * @sa QExtAbstractPropertyBrowser::setFactoryForManager()
     */
    QExtIntPropertyManager *subIntPropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by @e this manager, this function returns an invalid color.
     *
     * @sa setValue()
     */
    QColor value(const QExtProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.  Nested properties are updated automatically.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtProperty *property, const QColor &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, const QColor &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QIcon valueIcon(const QExtProperty *property) const QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtColorPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtColorPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtColorPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtProperty *))
};


/**
 * @class QExtCursorPropertyManager
 * @brief The QExtCursorPropertyManager provides and manages QCursor properties.
 * A cursor property has a current value which can be retrieved using the value() function, and set using the setValue()
 * slot. In addition, QExtCursorPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtAbstractPropertyManager
 */
class QExtCursorPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtCursorPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtCursorPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtCursorPropertyManager() QEXT_OVERRIDE;

#ifndef QT_NO_CURSOR
    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns a default QCursor object.
     *
     * @sa setValue()
     */
    QCursor value(const QExtProperty *property) const;
#endif

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtProperty *property, const QCursor &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, const QCursor &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QIcon valueIcon(const QExtProperty *property) const QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

private:
    QExtCursorPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtCursorPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtCursorPropertyManager)
};


/***********************************************************************************************************************
** editor factory
***********************************************************************************************************************/
/**
 * @class QExtSpinBoxFactory
 * @brief The QExtSpinBoxFactory class provides QSpinBox widgets for properties created by QExtIntPropertyManager objects.
 *
 * @sa QExtAbstractEditorFactory, QExtIntPropertyManager
 */
class QExtSpinBoxFactoryPrivate;
class QEXT_WIDGETS_API QExtSpinBoxFactory : public QExtAbstractEditorFactory<QExtIntPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtSpinBoxFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtSpinBoxFactory() QEXT_OVERRIDE;

protected:
    /**
     * @internal
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void connectPropertyManager(QExtIntPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @internal
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void disconnectPropertyManager(QExtIntPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @internal
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
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


/**
 * @class QExtSliderFactory
 * @brief The QExtSliderFactory class provides QSlider widgets for properties created by QExtIntPropertyManager objects.
 *
 * @sa QExtAbstractEditorFactory, QExtIntPropertyManager
 */
class QExtSliderFactoryPrivate;
class QEXT_WIDGETS_API QExtSliderFactory : public QExtAbstractEditorFactory<QExtIntPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtSliderFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtSliderFactory() QEXT_OVERRIDE;

protected:
    /**
     * @internal
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void connectPropertyManager(QExtIntPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void disconnectPropertyManager(QExtIntPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
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


/**
 * @class QExtScrollBarFactory
 * @brief The QExtScrollBarFactory class provides QScrollBar widgets for properties created by QExtIntPropertyManager
 * objects.
 *
 * @sa QExtAbstractEditorFactory, QExtIntPropertyManager
 */
class QExtScrollBarFactoryPrivate;
class QEXT_WIDGETS_API QExtScrollBarFactory : public QExtAbstractEditorFactory<QExtIntPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtScrollBarFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtScrollBarFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void connectPropertyManager(QExtIntPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void disconnectPropertyManager(QExtIntPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
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


/**
 * @class QExtCheckBoxFactory
 * @brief The QExtCheckBoxFactory class provides QCheckBox widgets for properties created by QExtBoolPropertyManager
 * objects.
 *
 * @sa QExtAbstractEditorFactory, QExtBoolPropertyManager
 */
class QExtCheckBoxFactoryPrivate;
class QEXT_WIDGETS_API QExtCheckBoxFactory : public QExtAbstractEditorFactory<QExtBoolPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtCheckBoxFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtCheckBoxFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void connectPropertyManager(QExtBoolPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void disconnectPropertyManager(QExtBoolPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
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


/**
 * @class QExtDoubleSpinBoxFactory
 * @brief The QExtDoubleSpinBoxFactory class provides QDoubleSpinBox widgets for properties created by
 * QExtDoublePropertyManager objects.
 *
 * @sa QExtAbstractEditorFactory, QExtDoublePropertyManager
 */
class QExtDoubleSpinBoxFactoryPrivate;
class QEXT_WIDGETS_API QExtDoubleSpinBoxFactory : public QExtAbstractEditorFactory<QExtDoublePropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtDoubleSpinBoxFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtDoubleSpinBoxFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void connectPropertyManager(QExtDoublePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void disconnectPropertyManager(QExtDoublePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
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


/**
 * @class QExtLineEditFactory
 * @brief The QExtLineEditFactory class provides QLineEdit widgets for properties created by QExtStringPropertyManager
 * objects.
 *
 * @sa QExtAbstractEditorFactory, QExtStringPropertyManager
 */
class QExtLineEditFactoryPrivate;
class QEXT_WIDGETS_API QExtLineEditFactory : public QExtAbstractEditorFactory<QExtStringPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtLineEditFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtLineEditFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void connectPropertyManager(QExtStringPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void disconnectPropertyManager(QExtStringPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
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


/**
 * @class QExtDateEditFactory
 * @brief The QExtDateEditFactory class provides QDateEdit widgets for properties created by QExtDatePropertyManager
 * objects.
 *
 * @sa QExtAbstractEditorFactory, QExtDatePropertyManager
 */
class QExtDateEditFactoryPrivate;
class QEXT_WIDGETS_API QExtDateEditFactory : public QExtAbstractEditorFactory<QExtDatePropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtDateEditFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtDateEditFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void connectPropertyManager(QExtDatePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void disconnectPropertyManager(QExtDatePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
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


/**
 * @class QExtTimeEditFactory
 * @brief The QExtTimeEditFactory class provides QTimeEdit widgets for properties created by QExtTimePropertyManager
 * objects.
 *
 * @sa QExtAbstractEditorFactory, QExtTimePropertyManager
 */
class QExtTimeEditFactoryPrivate;
class QEXT_WIDGETS_API QExtTimeEditFactory : public QExtAbstractEditorFactory<QExtTimePropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtTimeEditFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtTimeEditFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void connectPropertyManager(QExtTimePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void disconnectPropertyManager(QExtTimePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    QWidget *createEditor(QExtTimePropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtTimeEditFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtTimeEditFactory)
    QEXT_DISABLE_COPY_MOVE(QExtTimeEditFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QTime &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QTime &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};


/**
 * @class QExtDateTimeEditFactory
 * @brief The QExtDateTimeEditFactory class provides QDateTimeEdit widgets for properties created by
 * QExtDateTimePropertyManager objects.
 *
 * @sa QExtAbstractEditorFactory, QExtDateTimePropertyManager
 */
class QExtDateTimeEditFactoryPrivate;
class QEXT_WIDGETS_API QExtDateTimeEditFactory : public QExtAbstractEditorFactory<QExtDateTimePropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtDateTimeEditFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtDateTimeEditFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void connectPropertyManager(QExtDateTimePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void disconnectPropertyManager(QExtDateTimePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    QWidget *createEditor(QExtDateTimePropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtDateTimeEditFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtDateTimeEditFactory)
    QEXT_DISABLE_COPY_MOVE(QExtDateTimeEditFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QDateTime &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QDateTime &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};


/**
 * @class QExtKeySequenceEditorFactory
 * @brief The QExtKeySequenceEditorFactory class provides editor widgets for properties created by
 * QExtKeySequencePropertyManager objects.
 *
 * @sa QExtAbstractEditorFactory
 */
class QExtKeySequenceEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtKeySequenceEditorFactory : public QExtAbstractEditorFactory<QExtKeySequencePropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtKeySequenceEditorFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtKeySequenceEditorFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void connectPropertyManager(QExtKeySequencePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void disconnectPropertyManager(QExtKeySequencePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    QWidget *createEditor(QExtKeySequencePropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtKeySequenceEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtKeySequenceEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtKeySequenceEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QKeySequence &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QKeySequence &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};


/**
 * @class QExtCharEditorFactory
 * @brief The QExtCharEditorFactory class provides editor widgets for properties created by QExtCharPropertyManager
 * objects.
 *
 * @sa QExtAbstractEditorFactory
 */
class QExtCharEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtCharEditorFactory : public QExtAbstractEditorFactory<QExtCharPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtCharEditorFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtCharEditorFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void connectPropertyManager(QExtCharPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void disconnectPropertyManager(QExtCharPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    QWidget *createEditor(QExtCharPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtCharEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtCharEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtCharEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QChar &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QChar &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};


/**
 * @class QExtEnumEditorFactory
 * @brief The QExtEnumEditorFactory class provides QComboBox widgets for properties created by QExtEnumPropertyManager
 * objects.
 *
 * @sa QExtAbstractEditorFactory, QExtEnumPropertyManager
 */
class QExtEnumEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtEnumEditorFactory : public QExtAbstractEditorFactory<QExtEnumPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    explicit QExtEnumEditorFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtEnumEditorFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void connectPropertyManager(QExtEnumPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void disconnectPropertyManager(QExtEnumPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
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


/**
 * @class QExtCursorEditorFactory
 * @brief The QExtCursorEditorFactory class provides QComboBox widgets for properties created by
 * QExtCursorPropertyManager objects.
 *
 * @sa QExtAbstractEditorFactory, QExtCursorPropertyManager
 */
class QExtCursorEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtCursorEditorFactory : public QExtAbstractEditorFactory<QExtCursorPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtCursorEditorFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtCursorEditorFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void connectPropertyManager(QExtCursorPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void disconnectPropertyManager(QExtCursorPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    QWidget *createEditor(QExtCursorPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtCursorEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtCursorEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtCursorEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QCursor &))
    Q_PRIVATE_SLOT(d_func(), void slotEnumChanged(QExtProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};


/**
 * @class QExtColorEditorFactory
 * @brief The QExtColorEditorFactory class provides color editing  for properties created by QExtColorPropertyManager
 * objects.
 *
 * @sa QExtAbstractEditorFactory, QExtColorPropertyManager
 */
class QExtColorEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtColorEditorFactory : public QExtAbstractEditorFactory<QExtColorPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtColorEditorFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtColorEditorFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void connectPropertyManager(QExtColorPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void disconnectPropertyManager(QExtColorPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    QWidget *createEditor(QExtColorPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtColorEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtColorEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtColorEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtProperty *, const QColor &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QColor &))
};


/**
 * @class QExtFontEditorFactory
 * @brief The QExtFontEditorFactory class provides font editing for properties created by QExtFontPropertyManager
 * objects.
 *
 * @sa QExtAbstractEditorFactory, QExtFontPropertyManager
 */
class QExtFontEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtFontEditorFactory : public QExtAbstractEditorFactory<QExtFontPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtFontEditorFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtFontEditorFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void connectPropertyManager(QExtFontPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void disconnectPropertyManager(QExtFontPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
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
/**
 * @class QExtButtonPropertyBrowser
 * @brief The QExtButtonPropertyBrowser class provides a drop down QToolButton based property browser.
 * A property browser is a widget that enables the user to edit a given set of properties. Each property is represented
 * by a label specifying the property's name, and an editing widget (e.g. a line edit or a combobox) holding its value.
 * A property can have zero or more subproperties.
 *
 * QExtButtonPropertyBrowser provides drop down button for all nested properties, i.e. subproperties are enclosed by a
 * container associated with the drop down button. The parent property's name is displayed as button text. For example:
 *
 * Use the QExtAbstractPropertyBrowser API to add, insert and remove properties from an instance of the
 * QExtButtonPropertyBrowser class. The properties themselves are created and managed by implementations of the
 * QExtAbstractPropertyManager class.
 *
 * @sa QExtTreePropertyBrowser, QExtAbstractPropertyBrowser
 */
class QExtButtonPropertyBrowserPrivate;
class QEXT_WIDGETS_API QExtButtonPropertyBrowser : public QExtAbstractPropertyBrowser
{
    Q_OBJECT

public:
    /**
     * @brief Creates a property browser with the given @a parent.
     */
    QExtButtonPropertyBrowser(QWidget *parent = QEXT_NULLPTR);

    /**
     * Destroys this property browser.
     * Note that the properties that were inserted into this browser are @e not destroyed since they may still be used
     * in other browsers. The properties are owned by the manager that created them.
     *
     * @sa QExtProperty, QExtAbstractPropertyManager
     */
    ~QExtButtonPropertyBrowser() QEXT_OVERRIDE;

    /**
     * @brief Sets the @a item to either collapse or expanded, depending on the value of @a expanded.
     *
     * @sa isExpanded(), expanded(), collapsed()
     */
    void setExpanded(QExtBrowserItem *item, bool expanded);

    /**
     * @brief Returns true if the @a item is expanded; otherwise returns false.
     *
     * @sa setExpanded()
     */
    bool isExpanded(QExtBrowserItem *item) const;

Q_SIGNALS:
    /**
     * @brief This signal is emitted when the @a item is collapsed.
     *
     * @sa expanded(), setExpanded()
     */
    void collapsed(QExtBrowserItem *item);

    /**
     * @brief This signal is emitted when the @a item is expanded.
     *
     * @sa collapsed(), setExpanded()
     */
    void expanded(QExtBrowserItem *item);

protected:
    /**
     * @brief reimp
     */
    void itemRemoved(QExtBrowserItem *item) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void itemChanged(QExtBrowserItem *item) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void itemInserted(QExtBrowserItem *item, QExtBrowserItem *afterItem) QEXT_OVERRIDE;

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
/**
 * @class QExtGroupBoxPropertyBrowser
 * @brief The QExtGroupBoxPropertyBrowser class provides a QGroupBox based property browser.
 * A property browser is a widget that enables the user to edit a given set of properties. Each property is represented
 * by a label specifying the property's name, and an editing widget (e.g. a line edit or a combobox) holding its value.
 * A property can have zero or more subproperties.
 *
 * QExtGroupBoxPropertyBrowser provides group boxes for all nested properties, i.e. subproperties are enclosed by a
 * group box with the parent property's name as its title. For example:
 *
 * Use the QExtAbstractPropertyBrowser API to add, insert and remove properties from an instance of the
 * QExtGroupBoxPropertyBrowser class. The properties themselves are created and managed by implementations of the
 * QExtAbstractPropertyManager class.
 *
 * @sa QExtTreePropertyBrowser, QExtAbstractPropertyBrowser
 */
class QExtGroupBoxPropertyBrowserPrivate;
class QEXT_WIDGETS_API QExtGroupBoxPropertyBrowser : public QExtAbstractPropertyBrowser
{
    Q_OBJECT

public:
    /**
     * @brief Creates a property browser with the given @a parent.
     */
    QExtGroupBoxPropertyBrowser(QWidget *parent = QEXT_NULLPTR);

    /**
     * Destroys this property browser.
     * Note that the properties that were inserted into this browser are @e not destroyed since they may still be used
     * in other browsers. The properties are owned by the manager that created them.
     *
     * @sa QExtProperty, QExtAbstractPropertyManager
     */
    ~QExtGroupBoxPropertyBrowser() QEXT_OVERRIDE;

protected:
    /**
     * @brief reimp
     */
    void itemRemoved(QExtBrowserItem *item) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void itemChanged(QExtBrowserItem *item) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void itemInserted(QExtBrowserItem *item, QExtBrowserItem *afterItem) QEXT_OVERRIDE;

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
/**
 * @class QExtTreePropertyBrowser
 * @brief The QExtTreePropertyBrowser class provides QTreeWidget based property browser.
 *
 * A property browser is a widget that enables the user to edit a given set of properties. Each property is represented
 * by a label specifying the property's name, and an editing widget (e.g. a line edit or a combobox) holding its value.
 * A property can have zero or more subproperties.
 *
 * QExtTreePropertyBrowser provides a tree based view for all nested properties, i.e. properties that have subproperties
 * can be in an expanded (subproperties are visible) or collapsed (subproperties are hidden) state. For example:
 *
 * Use the QExtAbstractPropertyBrowser API to add, insert and remove properties from an instance of the
 * QExtTreePropertyBrowser class.
 * The properties themselves are created and managed by implementations of the QExtAbstractPropertyManager class.
 *
 * @sa QExtGroupBoxPropertyBrowser, QExtAbstractPropertyBrowser
 */
class QTreeWidgetItem;
class QExtTreePropertyBrowserPrivate;
class QEXT_WIDGETS_API QExtTreePropertyBrowser : public QExtAbstractPropertyBrowser
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
    QExtTreePropertyBrowser(QWidget *parent = QEXT_NULLPTR);

    /**
     * Destroys this property browser.
     * Note that the properties that were inserted into this browser are @e not destroyed since they may still be used
     * in other browsers. The properties are owned by the manager that created them.
     *
     * @sa QExtProperty, QExtAbstractPropertyManager
     */
    ~QExtTreePropertyBrowser() QEXT_OVERRIDE;

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
    void setExpanded(QExtBrowserItem *item, bool expanded);

    /**
     * @brief Returns true if the @a item is expanded; otherwise returns false.
     *
     * @sa setExpanded()
     */
    bool isExpanded(QExtBrowserItem *item) const;

    /**
     * @brief Returns true if the @a item is visible; otherwise returns false.
     *
     * @sa setItemVisible()
     */
    bool isItemVisible(QExtBrowserItem *item) const;

    /**
     * @brief Sets the @a item to be visible, depending on the value of @a visible.
     *
     * @sa isItemVisible()
     */
    void setItemVisible(QExtBrowserItem *item, bool visible);

    /**
     * @brief Sets the @a item's background color to @a color. Note that while item's background is rendered every
     * second row is being drawn with alternate color (which is a bit lighter than items @a color)
     *
     * @sa backgroundColor(), calculatedBackgroundColor()
     */
    void setBackgroundColor(QExtBrowserItem *item, const QColor &color);

    /**
     * @brief Returns the @a item's color. If there is no color set for item it returns invalid color.
     *
     * @sa calculatedBackgroundColor(), setBackgroundColor()
     */
    QColor backgroundColor(QExtBrowserItem *item) const;

    /**
     * @brief Returns the @a item's color. If there is no color set for item it returns parent @a item's color
     * (if there is no color set for parent it returns grandparent's color and so on).
     * In case the color is not set for @a item and it's top level item it returns invalid color.
     *
     * @sa backgroundColor(), setBackgroundColor()
     */
    QColor calculatedBackgroundColor(QExtBrowserItem *item) const;

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
    void editItem(QExtBrowserItem *item);

Q_SIGNALS:
    /**
     * @brief This signal is emitted when the @a item is collapsed.
     *
     * @sa expanded(), setExpanded()
     */
    void collapsed(QExtBrowserItem *item);

    /**
     * @brief This signal is emitted when the @a item is expanded.
     *
     * @sa collapsed(), setExpanded()
     */
    void expanded(QExtBrowserItem *item);

protected:
    /**
     * @brief reimp
     */
    void changeEvent(QEvent *event) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void itemRemoved(QExtBrowserItem *item) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void itemChanged(QExtBrowserItem *item) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void itemInserted(QExtBrowserItem *item, QExtBrowserItem *afterItem) QEXT_OVERRIDE;

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
/**
 * @class QExtVariantProperty
 * @brief The QExtVariantProperty class is a convenience class handling QVariant based properties.
 * QExtVariantProperty provides additional API: A property's type, value type, attribute values and current value can
 * easily be retrieved using the propertyType(), valueType(), attributeValue() and value() functions respectively.
 * In addition, the attribute values and the current value can be set using the corresponding setValue() and
 * setAttribute() functions.
 *
 * For example, instead of writing:
 * @code
 *      QExtVariantPropertyManager *variantPropertyManager;
 *      QExtProperty *property;
 *      variantPropertyManager->setValue(property, 10);
 * @endcode
 *
 * you can write:
 *
 * @code
 *      QExtVariantPropertyManager *variantPropertyManager;
 *      QExtVariantProperty *property;
 *      property->setValue(10);
 * @endcode
 *
 * QExtVariantProperty instances can only be created by the QExtVariantPropertyManager class.
 *
 * @sa QExtProperty, QExtVariantPropertyManager, QExtVariantEditorFactory
 */
class QEXT_WIDGETS_API QExtVariantProperty : public QExtProperty
{
public:
    /**
     * Destroys this property.
     *
     * @sa QExtProperty::~QExtProperty()
     */
    ~QExtVariantProperty() QEXT_OVERRIDE;

    /**
     * @brief Returns the property's current value.
     *
     * @sa valueType(), setValue()
     */
    QVariant value() const;

    /**
     * @brief Returns this property's value for the specified @a attribute.
     * QExtVariantPropertyManager provides a couple of related functions:
     * @l{QExtVariantPropertyManager::attributes()}{attributes()} and
     * @l{QExtVariantPropertyManager::attributeType()}{attributeType()}.
     *
     * @sa setAttribute()
     */
    QVariant attributeValue(const QString &attribute) const;

    /**
     * @brief Returns the type of this property's value.
     *
     * @sa propertyType()
     */
    int valueType() const;

    /**
     * @brief Returns this property's type.
     * QExtVariantPropertyManager provides several related functions:
     * @l{QExtVariantPropertyManager::enumTypeId()}{enumTypeId()},
     * @l{QExtVariantPropertyManager::flagTypeId()}{flagTypeId()} and
     * @l{QExtVariantPropertyManager::groupTypeId()}{groupTypeId()}.
     *
     * @sa valueType()
     */
    int propertyType() const;

    /**
     * @brief Sets the value of this property to @a value.
     * The specified @a value must be of the type returned by valueType(), or of a type that can be converted to
     * valueType() using the QVariant::canConvert() function; otherwise this function does nothing.
     *
     * @sa value()
     */
    void setValue(const QVariant &value);

    /**
     * @brief Sets the @a attribute of property to @a value.
     * QExtVariantPropertyManager provides the related
     * @l{QExtVariantPropertyManager::setAttribute()}{setAttribute()} function.
     *
     * @sa attributeValue()
     */
    void setAttribute(const QString &attribute, const QVariant &value);

protected:
    /**
     * @brief Creates a variant property using the given @a manager.
     * Do not use this constructor to create variant property instances;
     * use the QExtVariantPropertyManager::addProperty() function instead.  This constructor is used internally by the
     * QExtVariantPropertyManager::createProperty() function.
     *
     * @sa QExtVariantPropertyManager
     */
    QExtVariantProperty(QExtVariantPropertyManager *manager);

private:
    friend class QExtVariantPropertyManager;
    QExtVariantPropertyPrivate *d_ptr;
};


/**
 * @class QExtVariantPropertyManager
 * @brief The QExtVariantPropertyManager class provides and manages QVariant based properties.
 * QExtVariantPropertyManager provides the addProperty() function which creates QExtVariantProperty objects.
 * The QExtVariantProperty class is a convenience class handling QVariant based properties inheriting QExtProperty.
 * A QExtProperty object created by a QExtVariantPropertyManager instance can be converted into a QExtVariantProperty
 * object using the variantProperty() function.
 *
 * The property's value can be retrieved using the value(), and set using the setValue() slot. In addition the
 * property's type, and the type of its value, can be retrieved using the propertyType() and valueType() functions
 * respectively.
 *
 * A property's type is a QVariant::Type enumerator value, and usually a property's type is the same as its value type.
 * But for some properties the types differ, for example for enums, flags and group types in which case
 * QExtVariantPropertyManager provides the enumTypeId(), flagTypeId() and groupTypeId() functions, respectively, to
 * identify their property type (the value types are QVariant::Int for the enum and flag types, and QVariant::Invalid
 * for the group type).
 *
 * Use the isPropertyTypeSupported() function to check if a particular property type is supported. The currently
 * supported property types are:
 *
 * @table
 *  @header
 *      @o Property Type
 *      @o Property Type Id
 *  @row
 *      @o int
 *      @o QVariant::Int
 *  @row
 *      @o double
 *      @o QVariant::Double
 *  @row
 *      @o bool
 *      @o QVariant::Bool
 *  @row
 *      @o QString
 *      @o QVariant::String
 *  @row
 *      @o QDate
 *      @o QVariant::Date
 *  @row
 *      @o QTime
 *      @o QVariant::Time
 *  @row
 *      @o QDateTime
 *      @o QVariant::DateTime
 *  @row
 *      @o QKeySequence
 *      @o QVariant::KeySequence
 *  @row
 *      @o QChar
 *      @o QVariant::Char
 *  @row
 *      @o QLocale
 *      @o QVariant::Locale
 *  @row
 *      @o QPoint
 *      @o QVariant::Point
 *  @row
 *      @o QPointF
 *      @o QVariant::PointF
 *  @row
 *      @o QSize
 *      @o QVariant::Size
 *  @row
 *      @o QSizeF
 *      @o QVariant::SizeF
 *  @row
 *      @o QRect
 *      @o QVariant::Rect
 *  @row
 *      @o QRectF
 *      @o QVariant::RectF
 *  @row
 *      @o QColor
 *      @o QVariant::Color
 *  @row
 *      @o QSizePolicy
 *      @o QVariant::SizePolicy
 *  @row
 *      @o QFont
 *      @o QVariant::Font
 *  @row
 *      @o QCursor
 *      @o QVariant::Cursor
 *  @row
 *      @o enum
 *      @o enumTypeId()
 *  @row
 *      @o flag
 *      @o flagTypeId()
 *  @row
 *      @o group
 *      @o groupTypeId()
 * @endtable
 *
 * Each property type can provide additional attributes, e.g. QVariant::Int and QVariant::Double provides minimum and
 * maximum values. The currently supported attributes are:
 *
 * @table
 *  @header
 *      @o Property Type
 *      @o Attribute Name
 *      @o Attribute Type
 *  @row
 *      @o @c int
 *      @o minimum
 *      @o QVariant::Int
 *  @row
 *      @o
 *      @o maximum
 *      @o QVariant::Int
 *  @row
 *      @o
 *      @o singleStep
 *      @o QVariant::Int
 *  @row
 *      @o @c double
 *      @o minimum
 *      @o QVariant::Double
 *  @row
 *      @o
 *      @o maximum
 *      @o QVariant::Double
 *  @row
 *      @o
 *      @o singleStep
 *      @o QVariant::Double
 *  @row
 *      @o
 *      @o decimals
 *      @o QVariant::Int
 *  @row
 *      @o @c bool
 *      @o textVisible
 *      @o QVariant::Bool
 *  @row
 *      @o QString
 *      @o regExp
 *      @o QVariant::RegExp
 *  @row
 *      @o
 *      @o echoMode
 *      @o QVariant::Int
 *  @row
 *      @o QDate
 *      @o minimum
 *      @o QVariant::Date
 *  @row
 *      @o
 *      @o maximum
 *      @o QVariant::Date
 *  @row
 *      @o QPointF
 *      @o decimals
 *      @o QVariant::Int
 *  @row
 *      @o QSize
 *      @o minimum
 *      @o QVariant::Size
 *  @row
 *      @o
 *      @o maximum
 *      @o QVariant::Size
 *  @row
 *      @o QSizeF
 *      @o minimum
 *      @o QVariant::SizeF
 *  @row
 *      @o
 *      @o maximum
 *      @o QVariant::SizeF
 *  @row
 *      @o
 *      @o decimals
 *      @o QVariant::Int
 *  @row
 *      @o QRect
 *      @o constraint
 *      @o QVariant::Rect
 *  @row
 *      @o QRectF
 *      @o constraint
 *      @o QVariant::RectF
 *  @row
 *      @o
 *      @o decimals
 *      @o QVariant::Int
 *  @row
 *      @o @c enum
 *      @o enumNames
 *      @o QVariant::StringList
 *  @row
 *      @o
 *      @o enumIcons
 *      @o iconMapTypeId()
 *  @row
 *      @o @c flag
 *      @o flagNames
 *      @o QVariant::StringList
 * @endtable
 *
 * The attributes for a given property type can be retrieved using the attributes() function. Each attribute has a
 * value type which can be retrieved using the attributeType() function, and a value accessible through the
 * attributeValue() function. In addition, the value can be set using the setAttribute() slot.
 *
 * QExtVariantManager also provides the valueChanged() signal which is emitted whenever a property created by this manager
 * change, and the attributeChanged() signal which is emitted whenever an attribute of such a property changes.
 *
 * @sa QExtVariantProperty, QExtVariantEditorFactory
 */
class QExtVariantPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtVariantPropertyManager : public QExtAbstractPropertyManager
{
    Q_OBJECT
public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtVariantPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtVariantPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Creates and returns a variant property of the given @a propertyType with the given @a name.
     * If the specified @a propertyType is not supported by this variant manager, this function returns 0.
     *
     * Do not use the inherited QExtAbstractPropertyManager::addProperty() function to create a variant property
     * (that function will always return 0 since it will not be clear what type the property should have).
     *
     * @sa isPropertyTypeSupported()
     */
    virtual QExtVariantProperty *addProperty(int propertyType, const QString &name = QString());

    /**
     * @brief Returns the given @a property's type.
     *
     * @sa valueType()
     */
    int propertyType(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's value type.
     *
     * @sa propertyType()
     */
    int valueType(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property converted into a QExtVariantProperty.
     * If the @a property was not created by this variant manager, the function returns 0.
     *
     * @sa createProperty()
     */
    QExtVariantProperty *variantProperty(const QExtProperty *property) const;

    /**
     * @overload
     * @brief Returns the value type associated with the given @a propertyType.
     */
    virtual int valueType(int propertyType) const;

    /**
     * @brief Returns a list of the given @a propertyType 's attributes.
     *
     * @sa attributeValue(), attributeType()
     */
    virtual QStringList attributes(int propertyType) const;

    /**
     * @brief Returns true if the given @a propertyType is supported by this variant manager; otherwise false.
     *
     * @sa propertyType()
     */
    virtual bool isPropertyTypeSupported(int propertyType) const;

    /**
     * @brief Returns the type of the specified @a attribute of the given @a propertyType.
     * If the given @a propertyType is not supported by @e this manager, or if the given @a propertyType does not
     * possess the specified @a attribute, this function returns QVariant::Invalid.
     *
     * @sa attributes(), valueType()
     */
    virtual int attributeType(int propertyType, const QString &attribute) const;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns an invalid variant.
     *
     * @sa setValue()
     */
    virtual QVariant value(const QExtProperty *property) const;

    /**
     * @brief Returns the given @a property's value for the specified @a attribute
     *
     * If the given @a property was not created by @e this manager, or if the specified @a attribute does not exist,
     * this function returns an invalid variant.
     *
     * @sa attributes(), attributeType(), setAttribute()
     */
    virtual QVariant attributeValue(const QExtProperty *property, const QString &attribute) const;

    /**
     * @brief Returns the type id for an enum property.
     * Note that the property's value type can be retrieved using the valueType() function (which is QVariant::Int for
     * the enum property type).
     *
     * @sa propertyType(), valueType()
     */
    static int enumTypeId();

    /**
     * @brief Returns the type id for a flag property.
     * Note that the property's value type can be retrieved using the valueType() function (which is QVariant::Int for
     * the flag property type).
     *
     * @sa propertyType(), valueType()
     */
    static int flagTypeId();

    /**
     * @brief Returns the type id for a group property.
     * Note that the property's value type can be retrieved using the valueType() function (which is QVariant::Invalid
     * for the group property type, since it doesn't provide any value).
     *
     * @sa propertyType(), valueType()
     */
    static int groupTypeId();

    /**
     * @brief Returns the type id for a icon map attribute.
     * Note that the property's attribute type can be retrieved using the attributeType() function.
     *
     * @sa attributeType(), QExtEnumPropertyManager::enumIcons()
     */
    static int iconMapTypeId();

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     * The specified @a value must be of a type returned by valueType(), or of type that can be converted to
     * valueType() using the QVariant::canConvert() function, otherwise this function does nothing.
     *
     * @sa value(), QExtVariantProperty::setValue(), valueChanged()
     */
    virtual void setValue(QExtProperty *property, const QVariant &val);

    /**
     * @brief Sets the value of the specified @a attribute of the given @a property, to @a value.
     * The new @a value's type must be of the type returned by attributeType(), or of a type that can be converted to
     * attributeType() using the QVariant::canConvert() function, otherwise this function does nothing.
     *
     * @sa attributeValue(), QExtVariantProperty::setAttribute(), attributeChanged()
     */
    virtual void setAttribute(QExtProperty *property, const QString &attribute, const QVariant &value);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtProperty *property, const QVariant &val);

    /**
     * @brief This signal is emitted whenever an attribute of a property created by this manager changes its value,
     * passing a pointer to the @a property, the @a attribute and the new @a value as parameters.
     *
     * @sa setAttribute()
     */
    void attributeChanged(QExtProperty *property, const QString &attribute, const QVariant &val);

protected:
    /**
     * @brief reimp
     */
    QExtProperty *createProperty() QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void initializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    bool hasValue(const QExtProperty *property) const QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QIcon valueIcon(const QExtProperty *property) const QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtProperty *property) const QEXT_OVERRIDE;

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


/**
 * @class QExtVariantEditorFactory
 * @brief The QExtVariantEditorFactory class provides widgets for properties created by QExtVariantPropertyManager
 * objects.
 *
 * The variant factory provides the following widgets for the specified property types:
 *
 * @table
 *  @header
 *      @o Property Type
 *      @o Widget
 *  @row
 *      @o @c int
 *      @o QSpinBox
 *  @row
 *      @o @c double
 *      @o QDoubleSpinBox
 *  @row
 *      @o @c bool
 *      @o QCheckBox
 *  @row
 *      @o QString
 *      @o QLineEdit
 *  @row
 *      @o QDate
 *      @o QDateEdit
 *  @row
 *      @o QTime
 *      @o QTimeEdit
 *  @row
 *      @o QDateTime
 *      @o QDateTimeEdit
 *  @row
 *      @o QKeySequence
 *      @o customized editor
 *  @row
 *      @o QChar
 *      @o customized editor
 *  @row
 *      @o @c enum
 *      @o QComboBox
 *  @row
 *      @o QCursor
 *      @o QComboBox
 * @endtable
 *
 * @Note that QExtVariantPropertyManager supports several additional property types for which the
 * QExtVariantEditorFactory class does not provide editing widgets, e.g. QPoint and QSize. To provide widgets for other
 * types using the variant approach, derive from the QExtVariantEditorFactory class.
 *
 * @sa QExtAbstractEditorFactory, QExtVariantPropertyManager
 */
class QExtVariantEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtVariantEditorFactory : public QExtAbstractEditorFactory<QExtVariantPropertyManager>
{
    Q_OBJECT
public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    explicit QExtVariantEditorFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtVariantEditorFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void connectPropertyManager(QExtVariantPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    void disconnectPropertyManager(QExtVariantPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtAbstractEditorFactory class.
     */
    QWidget *createEditor(QExtVariantPropertyManager *manager, QExtProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtVariantEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtVariantEditorFactory)
    QEXT_DISABLE_COPY_MOVE(QExtVariantEditorFactory)
};

Q_DECLARE_METATYPE(QIcon)
Q_DECLARE_METATYPE(QtIconMap)

#endif // _QEXTPROPERTYBROWSER_H
