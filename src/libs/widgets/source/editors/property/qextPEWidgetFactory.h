#ifndef _QEXTPEWIDGETFACTORY_H
#define _QEXTPEWIDGETFACTORY_H

#include <qextPEProperty.h>
#include <qextPEPropertyManager.h>

#include <QSet>
#include <QWidget>

/**
 * @class class QExtPEAbstractWidgetFactoryBase
 * @brief The QExtPEAbstractWidgetFactoryBase provides an interface for editor factories.
 * An editor factory is a class that is able to create an editing widget of a specified type (e.g. line edits or
 * comboboxes) for a given QExtPEProperty object, and it is used in conjunction with the QExtPEAbstractPropertyManager and
 * QExtPEAbstractPropertyEditor classes.
 *
 * When using a property browser widget, the properties are created and managed by implementations of the
 * QExtPEAbstractPropertyManager class. To ensure that the properties' values will be displayed using suitable editing
 * widgets, the managers are associated with objects of QExtPEAbstractWidgetFactory subclasses. The property browser
 * will use these associations to determine which factories it should use to create the preferred editing widgets.
 *
 * Typically, an editor factory is created by subclassing the QExtPEAbstractWidgetFactory template class which inherits
 * QExtPEAbstractWidgetFactoryBase. But note that several ready-made implementations are available:
 *
 * @list
 *  @o QExtPECheckBoxFactory
 *  @o QExtPEDateEditFactory
 *  @o QExtPEDateTimeEditFactory
 *  @o QExtPEDoubleSpinBoxFactory
 *  @o QExtPEEnumEditorFactory
 *  @o QExtPELineEditFactory
 *  @o QExtPEScrollBarFactory
 *  @o QExtPESliderFactory
 *  @o QExtPESpinBoxFactory
 *  @o QExtPETimeEditFactory
 *  @o QExtPEVariantEditorFactory
 * @endlist
 *
 * @sa QExtPEAbstractPropertyManager, QExtPEAbstractPropertyEditor
 */
class QEXT_WIDGETS_API QExtPEAbstractWidgetFactoryBase : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Creates an editing widget (with the given @a parent) for the given @a property.
     * This function is reimplemented in QExtPEAbstractWidgetFactory template class which also provides a pure virtual
     * convenience overload of this function enabling access to the property's manager.
     * @sa QExtPEAbstractWidgetFactory::createEditor()
     */
    virtual QWidget *createEditor(QExtPEProperty *property, QWidget *parent) = 0;

protected:
    /**
     * @brief Creates an abstract editor factory with the given @a parent.
     */
    explicit QExtPEAbstractWidgetFactoryBase(QObject *parent = QEXT_NULLPTR) : QObject(parent) {}

    /**
     * @brief Detaches property manager from factory.
     * This method is reimplemented in QExtPEAbstractWidgetFactory template subclass.
     * You don't need to reimplement it in your subclasses. Instead implement more convenient
     * QExtPEAbstractWidgetFactory::disconnectPropertyManager() which gives you access to particular manager subclass.
     */
    virtual void breakConnection(QExtPEAbstractPropertyManager *manager) = 0;

protected Q_SLOTS:
    /**
     * @brief This method is called when property manager is being destroyed.
     * Basically it notifies factory not to produce editors for properties owned by @a manager.
     * You don't need to reimplement it in your subclass. This method is implemented in QExtPEAbstractWidgetFactory
     * template subclass.
     */
    virtual void managerDestroyed(QObject *manager) = 0;

    friend class QExtPEAbstractPropertyEditor;
};


/**
 * @brief brief The QExtPEAbstractWidgetFactory is the base template class for editor factories.
 * An editor factory is a class that is able to create an editing widget of a specified type (e.g. line edits or
 * comboboxes) for a given QExtPEProperty object, and it is used in conjunction with the QExtPEAbstractPropertyManager and
 * QExtPEAbstractPropertyEditor classes.
 *
 * Note that the QExtPEAbstractWidgetFactory functions are using the PropertyManager template argument class which can be
 * any QExtPEAbstractPropertyManager subclass. For example:
 *
 * @code
 *  QExtPESpinBoxFactory *factory;
 *  QSet<QExtPEIntPropertyManager *> managers = factory->propertyManagers();
 * @endcode
 *
 * Note that QExtPESpinBoxFactory by definition creates editing widgets @e only for properties created by
 * QExtPEIntPropertyManager.
 *
 * When using a property browser widget, the properties are created and managed by implementations of the
 * QExtPEAbstractPropertyManager class. To ensure that the properties' values will be displayed using suitable editing
 * widgets, the managers are associated with objects of QExtPEAbstractWidgetFactory subclasses. The property browser will
 * use these associations to determine which factories it should use to create the preferred editing widgets.
 *
 * A QExtPEAbstractWidgetFactory object is capable of producing editors for several property managers at the same time.
 * To create an association between this factory and a given manager, use the addPropertyManager() function. Use the
 * removePropertyManager() function to make this factory stop producing editors for a given property manager. Use the
 * propertyManagers() function to retrieve the set of managers currently associated with this factory.
 *
 * Several ready-made implementations of the QExtPEAbstractWidgetFactory class are available:
 *
 * @list
 *  @o QExtPECheckBoxFactory
 *  @o QExtPEDateEditFactory
 *  @o QExtPEDateTimeEditFactory
 *  @o QExtPEDoubleSpinBoxFactory
 *  @o QExtPEEnumEditorFactory
 *  @o QExtPELineEditFactory
 *  @o QExtPEScrollBarFactory
 *  @o QExtPESliderFactory
 *  @o QExtPESpinBoxFactory
 *  @o QExtPETimeEditFactory
 *  @o QExtPEVariantEditorFactory
 * @endlist
 *
 * When deriving from the QExtPEAbstractWidgetFactory class, several pure virtual functions must be implemented: the
 * connectPropertyManager() function is used by the factory to connect to the given manager's signals, the createEditor()
 * function is supposed to create an editor for the given property controlled by the given manager, and finally the
 * disconnectPropertyManager() function is used by the factory to disconnect from the specified manager's signals.
 *
 * @sa QExtPEAbstractWidgetFactoryBase, QExtPEAbstractPropertyManager
 */
template <typename PropertyManager>
class QExtPEAbstractWidgetFactory : public QExtPEAbstractWidgetFactoryBase
{
public:
    /**
     * @brief Creates an editor factory with the given @a parent.
     * @sa addPropertyManager()
     */
    explicit QExtPEAbstractWidgetFactory(QObject *parent) : QExtPEAbstractWidgetFactoryBase(parent) {}
    ~QExtPEAbstractWidgetFactory() QEXT_OVERRIDE {}

    /**
     * @brief Creates an editing widget (with the given @a parent) for the given @a property.
     */
    QWidget *createEditor(QExtPEProperty *property, QWidget *parent) QEXT_OVERRIDE
    {
        QSetIterator<PropertyManager *> iter(mManagers);
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
     * The PropertyManager type is a template argument class, and represents the chosen QExtPEAbstractPropertyManager subclass.
     * @sa propertyManagers(), removePropertyManager()
     */
    void addPropertyManager(PropertyManager *manager)
    {
        if (mManagers.contains(manager))
        {
            return;
        }
        mManagers.insert(manager);
        this->connectPropertyManager(manager);
        connect(manager, SIGNAL(destroyed(QObject *)), this, SLOT(managerDestroyed(QObject *)));
    }

    /**
     * @brief Removes the given @a manager from this factory's set of managers. The PropertyManager type is a template
     * argument class, and may be any QExtPEAbstractPropertyManager subclass.
     * @sa propertyManagers(), addPropertyManager()
     */
    void removePropertyManager(PropertyManager *manager)
    {
        if (!mManagers.contains(manager))
        {
            return;
        }
        disconnect(manager, SIGNAL(destroyed(QObject *)), this, SLOT(managerDestroyed(QObject *)));
        this->disconnectPropertyManager(manager);
        mManagers.remove(manager);
    }

    /**
     * @brief Returns the factory's set of associated managers.  The PropertyManager type is a template argument class,
     * and represents the chosen QExtPEAbstractPropertyManager subclass.
     *
     * @sa addPropertyManager(), removePropertyManager()
     */
    QSet<PropertyManager *> propertyManagers() const
    {
        return mManagers;
    }

    /**
     * @brief Returns the property manager for the given @a property, or 0 if the given @a property doesn't belong to
     * any of this factory's registered managers.
     *
     * The PropertyManager type is a template argument class, and represents the chosen QExtPEAbstractPropertyManager subclass.
     *
     * @sa propertyManagers()
     */
    PropertyManager *propertyManager(QExtPEProperty *property) const
    {
        QExtPEAbstractPropertyManager *manager = property->propertyManager();
        QSetIterator<PropertyManager *> iter(mManagers);
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
     * class, and represents the chosen QExtPEAbstractPropertyManager subclass.
     * This function is used internally by the addPropertyManager() function, and makes it possible to update an editing
     * widget when the associated property's data changes. This is typically done in custom slots responding to the
     * signals emitted by the property's manager, e.g. QExtPEIntPropertyManager::valueChanged() and
     * QExtPEIntPropertyManager::rangeChanged().
     *
     * @sa propertyManagers(), disconnectPropertyManager()
     */
    virtual void connectPropertyManager(PropertyManager *manager) = 0;

    /**
     * @brief Disconnects this factory from the given @a manager's signals. The PropertyManager type is a template
     * argument class, and represents the chosen QExtPEAbstractPropertyManager subclass.
     *
     * This function is used internally by the removePropertyManager() function.
     *
     * @sa propertyManagers(), connectPropertyManager()
     */
    virtual void disconnectPropertyManager(PropertyManager *manager) = 0;

    /**
     * @brief Creates an editing widget with the given @a parent for the specified @a property created by the given
     * @a manager. The PropertyManager type is a template argument class, and represents the chosen
     * QExtPEAbstractPropertyManager subclass.
     *
     * This function must be implemented in derived classes: It is recommended to store a pointer to the widget and map
     * it to the given @a property, since the widget must be updated whenever the associated property's data changes.
     * This is typically done in custom slots responding to the signals emitted by the property's manager, e.g.
     * QExtPEIntPropertyManager::valueChanged() and QExtPEIntPropertyManager::rangeChanged().
     *
     * @sa connectPropertyManager()
     */
    virtual QWidget *createEditor(PropertyManager *manager, QExtPEProperty *property, QWidget *parent) = 0;

    /**
     * @brief reimp
     */
    void managerDestroyed(QObject *manager) QEXT_OVERRIDE
    {
        QSetIterator<PropertyManager *> iter(mManagers);
        while (iter.hasNext())
        {
            PropertyManager *m = iter.next();
            if (m == manager)
            {
                mManagers.remove(m);
                return;
            }
        }
    }

private:
    void breakConnection(QExtPEAbstractPropertyManager *manager) QEXT_OVERRIDE
    {
        QSetIterator<PropertyManager *> iter(mManagers);
        while (iter.hasNext())
        {
            PropertyManager *m = iter.next();
            if (m == manager)
            {
                this->removePropertyManager(m);
                return;
            }
        }
    }

private:
    QSet<PropertyManager *> mManagers;
    friend class QExtAbstractPropertyEditor;
};



/**
 * @class QExtPESpinBoxFactory
 * @brief The QExtPESpinBoxFactory class provides QSpinBox widgets for properties created by QExtPEIntPropertyManager objects.
 *
 * @sa QExtPEAbstractWidgetFactory, QExtPEIntPropertyManager
 */
class QExtPESpinBoxFactoryPrivate;
class QEXT_WIDGETS_API QExtPESpinBoxFactory : public QExtPEAbstractWidgetFactory<QExtPEIntPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtPESpinBoxFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtPESpinBoxFactory() QEXT_OVERRIDE;

protected:
    /**
     * @internal
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void connectPropertyManager(QExtPEIntPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @internal
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void disconnectPropertyManager(QExtPEIntPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @internal
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    QWidget *createEditor(QExtPEIntPropertyManager *manager, QExtPEProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtPESpinBoxFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPESpinBoxFactory)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPESpinBoxFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtPEProperty *, int, int))
    Q_PRIVATE_SLOT(d_func(), void slotSingleStepChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotReadOnlyChanged(QExtPEProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(int))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};


/**
 * @class QExtPESliderFactory
 * @brief The QExtPESliderFactory class provides QSlider widgets for properties created by QExtPEIntPropertyManager objects.
 *
 * @sa QExtPEAbstractWidgetFactory, QExtPEIntPropertyManager
 */
class QExtPESliderFactoryPrivate;
class QEXT_WIDGETS_API QExtPESliderFactory : public QExtPEAbstractWidgetFactory<QExtPEIntPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtPESliderFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtPESliderFactory() QEXT_OVERRIDE;

protected:
    /**
     * @internal
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void connectPropertyManager(QExtPEIntPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void disconnectPropertyManager(QExtPEIntPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    QWidget *createEditor(QExtPEIntPropertyManager *manager, QExtPEProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtPESliderFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPESliderFactory)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPESliderFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtPEProperty *, int, int))
    Q_PRIVATE_SLOT(d_func(), void slotSingleStepChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(int))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};


/**
 * @class QExtPEScrollBarFactory
 * @brief The QExtPEScrollBarFactory class provides QScrollBar widgets for properties created by QExtPEIntPropertyManager
 * objects.
 *
 * @sa QExtPEAbstractWidgetFactory, QExtPEIntPropertyManager
 */
class QExtPEScrollBarFactoryPrivate;
class QEXT_WIDGETS_API QExtPEScrollBarFactory : public QExtPEAbstractWidgetFactory<QExtPEIntPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtPEScrollBarFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtPEScrollBarFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void connectPropertyManager(QExtPEIntPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void disconnectPropertyManager(QExtPEIntPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    QWidget *createEditor(QExtPEIntPropertyManager *manager, QExtPEProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtPEScrollBarFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEScrollBarFactory)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPEScrollBarFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtPEProperty *, int, int))
    Q_PRIVATE_SLOT(d_func(), void slotSingleStepChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(int))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};


/**
 * @class QExtPECheckBoxFactory
 * @brief The QExtPECheckBoxFactory class provides QCheckBox widgets for properties created by QExtPEBoolPropertyManager
 * objects.
 *
 * @sa QExtPEAbstractWidgetFactory, QExtPEBoolPropertyManager
 */
class QExtPECheckBoxFactoryPrivate;
class QEXT_WIDGETS_API QExtPECheckBoxFactory : public QExtPEAbstractWidgetFactory<QExtPEBoolPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtPECheckBoxFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtPECheckBoxFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void connectPropertyManager(QExtPEBoolPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void disconnectPropertyManager(QExtPEBoolPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    QWidget *createEditor(QExtPEBoolPropertyManager *manager, QExtPEProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtPECheckBoxFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPECheckBoxFactory)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPECheckBoxFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtPEProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotTextVisibleChanged(QExtPEProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(bool))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};


/**
 * @class QExtPEDoubleSpinBoxFactory
 * @brief The QExtPEDoubleSpinBoxFactory class provides QDoubleSpinBox widgets for properties created by
 * QExtPEDoublePropertyManager objects.
 *
 * @sa QExtPEAbstractWidgetFactory, QExtPEDoublePropertyManager
 */
class QExtPEDoubleSpinBoxFactoryPrivate;
class QEXT_WIDGETS_API QExtPEDoubleSpinBoxFactory : public QExtPEAbstractWidgetFactory<QExtPEDoublePropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtPEDoubleSpinBoxFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtPEDoubleSpinBoxFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void connectPropertyManager(QExtPEDoublePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void disconnectPropertyManager(QExtPEDoublePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    QWidget *createEditor(QExtPEDoublePropertyManager *manager, QExtPEProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtPEDoubleSpinBoxFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEDoubleSpinBoxFactory)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPEDoubleSpinBoxFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtPEProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtPEProperty *, double, double))
    Q_PRIVATE_SLOT(d_func(), void slotSingleStepChanged(QExtPEProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotDecimalsChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotReadOnlyChanged(QExtPEProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(double))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};


/**
 * @class QExtPELineEditFactory
 * @brief The QExtPELineEditFactory class provides QLineEdit widgets for properties created by QExtPEStringPropertyManager
 * objects.
 *
 * @sa QExtPEAbstractWidgetFactory, QExtPEStringPropertyManager
 */
class QExtPELineEditFactoryPrivate;
class QEXT_WIDGETS_API QExtPELineEditFactory : public QExtPEAbstractWidgetFactory<QExtPEStringPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtPELineEditFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtPELineEditFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void connectPropertyManager(QExtPEStringPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void disconnectPropertyManager(QExtPEStringPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    QWidget *createEditor(QExtPEStringPropertyManager *manager, QExtPEProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtPELineEditFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPELineEditFactory)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPELineEditFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtPEProperty *, const QString &))
    Q_PRIVATE_SLOT(d_func(), void slotRegExpChanged(QExtPEProperty *, const QRegExp &))
    Q_PRIVATE_SLOT(d_func(), void slotEchoModeChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotReadOnlyChanged(QExtPEProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QString &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};


/**
 * @class QExtPEDateEditFactory
 * @brief The QExtPEDateEditFactory class provides QDateEdit widgets for properties created by QExtPEDatePropertyManager
 * objects.
 *
 * @sa QExtPEAbstractWidgetFactory, QExtPEDatePropertyManager
 */
class QExtPEDateEditFactoryPrivate;
class QEXT_WIDGETS_API QExtPEDateEditFactory : public QExtPEAbstractWidgetFactory<QExtPEDatePropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtPEDateEditFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtPEDateEditFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void connectPropertyManager(QExtPEDatePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void disconnectPropertyManager(QExtPEDatePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    QWidget *createEditor(QExtPEDatePropertyManager *manager, QExtPEProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtPEDateEditFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEDateEditFactory)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPEDateEditFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtPEProperty *, const QDate &))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtPEProperty *, const QDate &, const QDate &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QDate &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};


/**
 * @class QExtPETimeEditFactory
 * @brief The QExtPETimeEditFactory class provides QTimeEdit widgets for properties created by QExtPETimePropertyManager
 * objects.
 *
 * @sa QExtPEAbstractWidgetFactory, QExtPETimePropertyManager
 */
class QExtPETimeEditFactoryPrivate;
class QEXT_WIDGETS_API QExtPETimeEditFactory : public QExtPEAbstractWidgetFactory<QExtPETimePropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtPETimeEditFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtPETimeEditFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void connectPropertyManager(QExtPETimePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void disconnectPropertyManager(QExtPETimePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    QWidget *createEditor(QExtPETimePropertyManager *manager, QExtPEProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtPETimeEditFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPETimeEditFactory)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPETimeEditFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtPEProperty *, const QTime &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QTime &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};


/**
 * @class QExtPEDateTimeEditFactory
 * @brief The QExtPEDateTimeEditFactory class provides QDateTimeEdit widgets for properties created by
 * QExtPEDateTimePropertyManager objects.
 *
 * @sa QExtPEAbstractWidgetFactory, QExtPEDateTimePropertyManager
 */
class QExtPEDateTimeEditFactoryPrivate;
class QEXT_WIDGETS_API QExtPEDateTimeEditFactory : public QExtPEAbstractWidgetFactory<QExtPEDateTimePropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtPEDateTimeEditFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtPEDateTimeEditFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void connectPropertyManager(QExtPEDateTimePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void disconnectPropertyManager(QExtPEDateTimePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    QWidget *createEditor(QExtPEDateTimePropertyManager *manager, QExtPEProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtPEDateTimeEditFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEDateTimeEditFactory)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPEDateTimeEditFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtPEProperty *, const QDateTime &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QDateTime &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};


/**
 * @class QExtPEKeySequenceEditorFactory
 * @brief The QExtPEKeySequenceEditorFactory class provides editor widgets for properties created by
 * QExtPEKeySequencePropertyManager objects.
 *
 * @sa QExtPEAbstractWidgetFactory
 */
class QExtPEKeySequenceEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtPEKeySequenceEditorFactory : public QExtPEAbstractWidgetFactory<QExtPEKeySequencePropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtPEKeySequenceEditorFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtPEKeySequenceEditorFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void connectPropertyManager(QExtPEKeySequencePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void disconnectPropertyManager(QExtPEKeySequencePropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    QWidget *createEditor(QExtPEKeySequencePropertyManager *manager, QExtPEProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtPEKeySequenceEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEKeySequenceEditorFactory)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPEKeySequenceEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtPEProperty *, const QKeySequence &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QKeySequence &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};


/**
 * @class QExtPECharEditorFactory
 * @brief The QExtPECharEditorFactory class provides editor widgets for properties created by QExtPECharPropertyManager
 * objects.
 *
 * @sa QExtPEAbstractWidgetFactory
 */
class QExtPECharEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtPECharEditorFactory : public QExtPEAbstractWidgetFactory<QExtPECharPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtPECharEditorFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtPECharEditorFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void connectPropertyManager(QExtPECharPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void disconnectPropertyManager(QExtPECharPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    QWidget *createEditor(QExtPECharPropertyManager *manager, QExtPEProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtPECharEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPECharEditorFactory)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPECharEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtPEProperty *, const QChar &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QChar &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};


/**
 * @class QExtPEEnumEditorFactory
 * @brief The QExtPEEnumEditorFactory class provides QComboBox widgets for properties created by QExtPEEnumPropertyManager
 * objects.
 *
 * @sa QExtPEAbstractWidgetFactory, QExtPEEnumPropertyManager
 */
class QExtPEEnumEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtPEEnumEditorFactory : public QExtPEAbstractWidgetFactory<QExtPEEnumPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    explicit QExtPEEnumEditorFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtPEEnumEditorFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void connectPropertyManager(QExtPEEnumPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void disconnectPropertyManager(QExtPEEnumPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    QWidget *createEditor(QExtPEEnumPropertyManager *manager, QExtPEProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtPEEnumEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEEnumEditorFactory)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPEEnumEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotEnumNamesChanged(QExtPEProperty *, const QStringList &))
    Q_PRIVATE_SLOT(d_func(), void slotEnumIconsChanged(QExtPEProperty *, const QMap<int, QIcon> &))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(int))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};


/**
 * @class QExtPECursorEditorFactory
 * @brief The QExtPECursorEditorFactory class provides QComboBox widgets for properties created by
 * QExtPECursorPropertyManager objects.
 *
 * @sa QExtPEAbstractWidgetFactory, QExtPECursorPropertyManager
 */
class QExtPECursorEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtPECursorEditorFactory : public QExtPEAbstractWidgetFactory<QExtPECursorPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtPECursorEditorFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtPECursorEditorFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void connectPropertyManager(QExtPECursorPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void disconnectPropertyManager(QExtPECursorPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    QWidget *createEditor(QExtPECursorPropertyManager *manager, QExtPEProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtPECursorEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPECursorEditorFactory)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPECursorEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtPEProperty *, const QCursor &))
    Q_PRIVATE_SLOT(d_func(), void slotEnumChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
};


/**
 * @class QExtPEColorEditorFactory
 * @brief The QExtPEColorEditorFactory class provides color editing  for properties created by QExtPEColorPropertyManager
 * objects.
 *
 * @sa QExtPEAbstractWidgetFactory, QExtPEColorPropertyManager
 */
class QExtPEColorEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtPEColorEditorFactory : public QExtPEAbstractWidgetFactory<QExtPEColorPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtPEColorEditorFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtPEColorEditorFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void connectPropertyManager(QExtPEColorPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void disconnectPropertyManager(QExtPEColorPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    QWidget *createEditor(QExtPEColorPropertyManager *manager, QExtPEProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtPEColorEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEColorEditorFactory)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPEColorEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtPEProperty *, const QColor &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QColor &))
};


/**
 * @class QExtPEFontEditorFactory
 * @brief The QExtPEFontEditorFactory class provides font editing for properties created by QExtPEFontPropertyManager
 * objects.
 *
 * @sa QExtPEAbstractWidgetFactory, QExtPEFontPropertyManager
 */
class QExtPEFontEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtPEFontEditorFactory : public QExtPEAbstractWidgetFactory<QExtPEFontPropertyManager>
{
    Q_OBJECT

public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    QExtPEFontEditorFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtPEFontEditorFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void connectPropertyManager(QExtPEFontPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void disconnectPropertyManager(QExtPEFontPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    QWidget *createEditor(QExtPEFontPropertyManager *manager, QExtPEProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtPEFontEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEFontEditorFactory)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPEFontEditorFactory)
    Q_PRIVATE_SLOT(d_func(), void slotPropertyChanged(QExtPEProperty *, const QFont &))
    Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed(QObject *))
    Q_PRIVATE_SLOT(d_func(), void slotSetValue(const QFont &))
};


#endif // _QEXTPEWIDGETFACTORY_H
