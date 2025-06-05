#ifndef _QEXTPEPROPERTYMANAGER_H
#define _QEXTPEPROPERTYMANAGER_H

#include <qextPEProperty.h>

#include <QLineEdit>

typedef QLineEdit::EchoMode EchoMode;

/**
 * @class QExtPEAbstractPropertyManager
 * @brief The QExtPEAbstractPropertyManager provides an interface for property managers.
 * A manager can create and manage properties of a given type, and is used in conjunction with the
 * QExtPEAbstractPropertyEditor class.
 *
 * When using a property browser widget, the properties are created and managed by implementations of the
 * QExtPEAbstractPropertyManager class. To ensure that the properties' values will be displayed using suitable editing
 * widgets, the managers are associated with objects of QExtPEAbstractWidgetFactory subclasses. The property browser
 * will use these associations to determine which factories it should use to create the preferred editing widgets.
 *
 * The QExtPEAbstractPropertyManager class provides common functionality like creating a property using the addProperty()
 * function, and retrieving the properties created by the manager using the properties() function. The class also
 * provides signals that are emitted when the manager's properties change: propertyInserted(), propertyRemoved(),
 * propertyChanged() and propertyDestroyed().
 *
 * QExtPEAbstractPropertyManager subclasses are supposed to provide their own type specific API. Note that several
 * ready-made implementations are available:
 *
 * @list
 * @o QExtPEBoolPropertyManager
 * @o QExtPEColorPropertyManager
 * @o QExtPEDatePropertyManager
 * @o QExtPEDateTimePropertyManager
 * @o QExtPEDoublePropertyManager
 * @o QExtPEEnumPropertyManager
 * @o QExtPEFlagPropertyManager
 * @o QExtPEFontPropertyManager
 * @o QExtPEGroupPropertyManager
 * @o QExtPEIntPropertyManager
 * @o QExtPEPointPropertyManager
 * @o QExtPERectPropertyManager
 * @o QExtPESizePropertyManager
 * @o QExtPESizePolicyPropertyManager
 * @o QExtPEStringPropertyManager
 * @o QExtPETimePropertyManager
 * @o QExtPEVariantPropertyManager
 * @endlist
 *
 * @sa QExtPEAbstractWidgetFactoryBase, QExtPEAbstractPropertyEditor, QExtPEProperty
 */
class QExtPEAbstractPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPEAbstractPropertyManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Creates an abstract property manager with the given @a parent.
     */
    explicit QExtPEAbstractPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * @brief Destroys the manager. All properties created by the manager are destroyed.
     */
    ~QExtPEAbstractPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Destroys all the properties that this manager has created.
     * @sa propertyDestroyed(), uninitializeProperty()
     */
    void clear() const;

    /**
     * @brief Returns the set of properties created by this manager.
     * @sa addProperty()
     */
    QSet<QExtPEProperty *> properties() const;

    /**
     * @brief Creates a property with the given @a name which then is owned by this manager.
     * Internally, this function calls the createProperty() and initializeProperty() functions.
     * @sa initializeProperty(), properties()
     */
    QExtPEProperty *addProperty(const QString &name = QString());

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property's data changes, passing a pointer to the @a property as parameter.
     * @Note that signal is only emitted for properties that are created by this manager.
     * @sa QExtPEAbstractPropertyEditor::itemChanged()
     */
    void propertyChanged(QExtPEProperty *property);

    /**
     * @brief This signal is emitted when the specified @a property is about to be destroyed.
     * Note that signal is only emitted for properties that are created by this manager.
     * @sa clear(), uninitializeProperty()
     */
    void propertyDestroyed(QExtPEProperty *property);

    /**
     * @brief This signal is emitted when a subproperty is removed, passing pointers to the removed @a property and the
     * @a parent property as parameters.
     * Note that signal is emitted only when the @a parent property is created by this manager.
     * @sa QExtPEAbstractPropertyEditor::itemRemoved()
     */
    void propertyRemoved(QExtPEProperty *property, QExtPEProperty *parent);

    /**
     * @brief This signal is emitted when a new subproperty is inserted into an existing property, passing pointers to
     * the @a newProperty, @a parentProperty and @a precedingProperty as parameters.
     * If @a precedingProperty is 0, the @a newProperty was inserted at the beginning of the @a parentProperty's
     * subproperties list.
     * Note that signal is emitted only if the @a parentProperty is created by this manager.
     * @sa QExtPEAbstractPropertyEditor::itemInserted()
     */
    void propertyInserted(QExtPEProperty *property, QExtPEProperty *parent, QExtPEProperty *after);

protected:
    /**
     * @brief Returns whether the given @a property has a value.
     * The default implementation of this function returns true.
     * @sa QExtPEProperty::hasValue()
     */
    virtual bool hasValue(const QExtPEProperty *property) const;

    /**
     * @brief Returns an icon representing the current state of the given @a property.
     * @param The default implementation of this function returns an invalid icon.
     * @sa QExtPEProperty::valueIcon()
     */
    virtual QIcon valueIcon(const QExtPEProperty *property) const;

    /**
     * @brief Returns a string representing the current state of the given @a property.
     * The default implementation of this function returns an empty string.
     * @sa QExtPEProperty::valueText()
     */
    virtual QString valueText(const QExtPEProperty *property) const;

    /**
     * @brief Returns a string representing the current state of the given @a property.
     * The default implementation of this function returns an empty string.
     * @sa QExtPEProperty::valueText()
     */
    virtual QString displayText(const QExtPEProperty *property) const;

    /**
     * @brief Returns the echo mode representing the current state of the given @a property.
     * The default implementation of this function returns QLineEdit::Normal.
     * @sa QExtPEProperty::valueText()
     */
    virtual EchoMode echoMode(const QExtPEProperty *) const;

    /**
     * @brief This function is called whenever a new valid property pointer has been created, passing the pointer as
     * parameter.
     * The purpose is to let the manager know that the @a property has been created so that it can provide additional
     * attributes for the new property, e.g. QExtPEIntPropertyManager adds @l {QExtPEIntPropertyManager::value()}{value},
     * @l{QExtPEIntPropertyManager::minimum()}{minimum} and @l {QExtPEIntPropertyManager::maximum()}{maximum} attributes.
     * Since each manager subclass adds type specific attributes, this function is pure virtual and must be reimplemented
     * when deriving from the QExtPEAbstractPropertyManager class.
     * @sa addProperty(), createProperty()
     */
    virtual void initializeProperty(QExtPEProperty *property) = 0;

    /**
     * @brief This function is called just before the specified @a property is destroyed.
     * The purpose is to let the property manager know that the @a property is being destroyed so that it can remove the
     * property's additional attributes.
     * @sa clear(), propertyDestroyed()
     */
    virtual void uninitializeProperty(QExtPEProperty *property);

    /**
     * @brief Creates a property.
     * The base implementation produce QExtPEProperty instances; Reimplement this function to make this manager produce
     * objects of a QExtPEProperty subclass.
     * @sa addProperty(), initializeProperty()
     */
    virtual QExtPEProperty *createProperty();

private:
    friend class QExtPEProperty;
    QScopedPointer<QExtPEAbstractPropertyManagerPrivate> dd_ptr;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtPEAbstractPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPEAbstractPropertyManager)
};


/**
 * @brief The QExtPEGroupPropertyManager provides and manages group properties.
 * This class is intended to provide a grouping element without any value.
 *
 * @sa QExtPEAbstractPropertyManager
 */
class QEXT_WIDGETS_API QExtPEGroupPropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPEGroupPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * @brief Destroys this manager, and all the properties it has created.
     */
    ~QExtPEGroupPropertyManager() QEXT_OVERRIDE;

protected:
    /**
     * @brief reimp
     */
    virtual void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    virtual void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    virtual bool hasValue(const QExtPEProperty *property) const QEXT_OVERRIDE;
};



/**
 * @class QExtPEIntPropertyManager
 * @brief The QExtPEIntPropertyManager provides and manages int properties.
 *
 * An int property has a current value, and a range specifying the valid values. The range is defined by a minimum and
 * a maximum value.
 *
 * The property's value and range can be retrieved using the value(), minimum() and maximum() functions, and can be set
 * using the setValue(), setMinimum() and setMaximum() slots. Alternatively, the range can be defined in one go using
 * the setRange() slot.
 *
 * In addition, QExtPEIntPropertyManager provides the valueChanged() signal which is emitted whenever a property created
 * by this manager changes, and the rangeChanged() signal which is emitted whenever such a property changes its range of
 * valid values.
 *
 * @sa QExtPEAbstractPropertyManager, QExtPESpinBoxFactory, QExtPESliderFactory, QExtPEScrollBarFactory
 */
class QExtPEIntPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPEIntPropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPEIntPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * @brief Destroys this manager, and all the properties it has created.
     */
    ~QExtPEIntPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value.
     * If the given property is not managed by this manager, this function returns 0.
     *
     * @sa setValue()
     */
    int value(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's minimum value.
     *
     * @sa setMinimum(), maximum(), setRange()
     */
    int minimum(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's maximum value.
     *
     * @sa setMaximum(), minimum(), setRange()
     */
    int maximum(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's step value.
     * The step is typically used to increment or decrement a property value while pressing an arrow key.
     *
     * @sa setSingleStep()
     */
    int singleStep(const QExtPEProperty *property) const;

    /**
     * @brief Returns read-only status of the property.
     * When property is read-only it's value can be selected and copied from editor but not modified.
     *
     * @sa QExtPEIntPropertyManager::setReadOnly
     */
    bool isReadOnly(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     * If the specified @a value is not valid according to the given @a property's range, the @a value is adjusted to
     * the nearest valid value within the range.
     *
     * @sa value(), setRange(), valueChanged()
     */
    void setValue(QExtPEProperty *property, int val);

    /**
     * @brief Sets the minimum value for the given @a property to @a minVal.
     * When setting the minimum value, the maximum and current values are adjusted if necessary (ensuring that the range
     * remains valid and that the current value is within the range).
     *
     * @sa minimum(), setRange(), rangeChanged()
     */
    void setMinimum(QExtPEProperty *property, int minVal);

    /**
     * @brief Sets the maximum value for the given @a property to @a maxVal.
     * When setting maximum value, the minimum and current values are adjusted if necessary (ensuring that the range
     * remains valid and that the current value is within the range).
     *
     * @sa maximum(), setRange(), rangeChanged()
     */
    void setMaximum(QExtPEProperty *property, int maxVal);

    /**
     * @brief Sets the range of valid values.
     * This is a convenience function defining the range of valid values in one go; setting the @a minimum and
     * @a maximum values for the given @a property with a single function call.
     *
     * When setting a new range, the current value is adjusted if necessary (ensuring that the value remains within range).
     *
     * @sa setMinimum(), setMaximum(), rangeChanged()
     */
    void setRange(QExtPEProperty *property, int minVal, int maxVal);

    /**
     * @brief Sets the step value for the given @a property to @a step.
     * The step is typically used to increment or decrement a property value while pressing an arrow key.
     *
     * @sa singleStep()
     */
    void setSingleStep(QExtPEProperty *property, int step);

    /**
     * @brief Sets read-only status of the property.
     *
     * @sa QExtPEIntPropertyManager::setReadOnly
     */
    void setReadOnly(QExtPEProperty *property, bool readOnly);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer to
     * the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, int val);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its range of valid values,
     * passing a pointer to the @a property and the new @a minimum and @a maximum values.
     *
     * @sa setRange()
     */
    void rangeChanged(QExtPEProperty *property, int minVal, int maxVal);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its single step property,
     * passing a pointer to the @a property and the new @a step value
     *
     * @sa setSingleStep()
     */
    void singleStepChanged(QExtPEProperty *property, int step);
    void readOnlyChanged(QExtPEProperty *property, bool readOnly);

protected:
    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    virtual void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    virtual void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

private:
    QExtPEIntPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEIntPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPEIntPropertyManager)
};


/**
 * @class QExtPEBoolPropertyManager
 * @brief The QExtPEBoolPropertyManager class provides and manages boolean properties.
 * The property's value can be retrieved using the value() function, and set using the setValue() slot.
 *
 * In addition, QExtPEBoolPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtPEAbstractPropertyManager, QExtPECheckBoxFactory
 */
class QExtPEBoolPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPEBoolPropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPEBoolPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPEBoolPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by @e this manager, this function returns false.
     *
     * @sa setValue()
     */
    bool value(const QExtPEProperty *property) const;
    bool textVisible(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     *
     * @sa value()
     */
    void setValue(QExtPEProperty *property, bool val);
    void setTextVisible(QExtPEProperty *property, bool textVisible);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     */
    void valueChanged(QExtPEProperty *property, bool val);
    void textVisibleChanged(QExtPEProperty *property, bool);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QIcon valueIcon(const QExtPEProperty *property) const QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPEBoolPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEBoolPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPEBoolPropertyManager)
};

/**
 * @brief The QExtPEDoublePropertyManager provides and manages double properties.
 *
 * A double property has a current value, and a range specifying the valid values. The range is defined by a minimum
 * and a maximum value.
 *
 * The property's value and range can be retrieved using the value(), minimum() and maximum() functions, and can be set
 * using the setValue(), setMinimum() and setMaximum() slots. Alternatively, the range can be defined in one go using
 * the setRange() slot.
 *
 * In addition, QExtPEDoublePropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes, and the rangeChanged() signal which is emitted whenever such a property changes its
 * range of valid values.
 *
 * @sa QExtPEAbstractPropertyManager, QExtPEDoubleSpinBoxFactory
 */
class QExtPEDoublePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPEDoublePropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPEDoublePropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys  this manager, and all the properties it has created.
     */
    ~QExtPEDoublePropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value.
     * If the given property is not managed by this manager, this function returns 0.
     *
     * @sa setValue()
     */
    double value(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's minimum value.
     *
     * @sa maximum(), setRange()
     */
    double minimum(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's maximum value.
     *
     * @sa minimum(), setRange()
     */
    double maximum(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's step value.
     * The step is typically used to increment or decrement a property value while pressing an arrow key.
     *
     * @sa setSingleStep()
     */
    double singleStep(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's precision, in decimals.
     *
     * @sa setDecimals()
     */
    int decimals(const QExtPEProperty *property) const;

    /**
     * @brief Returns read-only status of the property.
     * When property is read-only it's value can be selected and copied from editor but not modified.
     *
     * @sa QExtPEDoublePropertyManager::setReadOnly
     */
    bool isReadOnly(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     * If the specified @a value is not valid according to the given @a property's range, the @a value is adjusted to
     * the nearest valid value within the range.
     *
     * @sa value(), setRange(), valueChanged()
     */
    void setValue(QExtPEProperty *property, double val);

    /**
     * @brief Sets the minimum value for the given @a property to @a minVal.
     * When setting the minimum value, the maximum and current values are adjusted if necessary (ensuring that the range
     * remains valid and that the current value is within in the range).
     *
     * @sa minimum(), setRange(), rangeChanged()
     */
    void setMinimum(QExtPEProperty *property, double minVal);

    /**
     * @brief Sets the maximum value for the given @a property to @a maxVal.
     * When setting the maximum value, the minimum and current values are adjusted if necessary (ensuring that the range
     * remains valid and that the current value is within in the range).
     *
     * @sa maximum(), setRange(), rangeChanged()
     */
    void setMaximum(QExtPEProperty *property, double maxVal);

    /**
     * @brief Sets the range of valid values.
     * This is a convenience function defining the range of valid values in one go; setting the @a minimum and @a
     * maximum values for the given @a property with a single function call.
     * When setting a new range, the current value is adjusted if necessary (ensuring that the value remains within range).
     *
     * @sa setMinimum(), setMaximum(), rangeChanged()
     */
    void setRange(QExtPEProperty *property, double minVal, double maxVal);

    /**
     * @brief Sets the step value for the given @a property to @a step.
     * The step is typically used to increment or decrement a property value while pressing an arrow key.
     *
     * @sa singleStep()
     */
    void setSingleStep(QExtPEProperty *property, double step);

    /**
     * @brief Sets the precision of the given @a property to @a prec.
     * The valid decimal range is 0-13. The default is 2.
     *
     * @sa decimals()
     */
    void setDecimals(QExtPEProperty *property, int prec);

    /**
     * @brief Sets read-only status of the property.
     *
     * @sa QExtPEDoublePropertyManager::setReadOnly
     */
    void setReadOnly(QExtPEProperty *property, bool readOnly);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, double val);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its range of valid values,
     * passing a pointer to the @a property and the new @a minimum and @a maximum values
     */
    void rangeChanged(QExtPEProperty *property, double minVal, double maxVal);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its single step property,
     * passing a pointer to the @a property and the new @a step value
     *
     * @sa setSingleStep()
     */
    void singleStepChanged(QExtPEProperty *property, double step);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its precision of value,
     * passing a pointer to the @a property and the new @a prec value
     * @sa setDecimals()
     */
    void decimalsChanged(QExtPEProperty *property, int prec);
    void readOnlyChanged(QExtPEProperty *property, bool readOnly);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPEDoublePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEDoublePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPEDoublePropertyManager)
};


/**
 * @class QExtPEStringPropertyManager
 * @brief The QExtPEStringPropertyManager provides and manages QString properties.
 * A string property's value can be retrieved using the value() function, and set using the setValue() slot.
 * The current value can be checked against a regular expression. To set the regular expression use the setRegExp()
 * slot, use the regExp() function to retrieve the currently set expression.
 *
 * In addition, QExtPEStringPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes, and the regExpChanged() signal which is emitted whenever such a property changes
 * its currently set regular expression.
 *
 * @sa QExtPEAbstractPropertyManager, QExtPELineEditFactory
 */
class QExtPEStringPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPEStringPropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPEStringPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPEStringPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value.
     * If the given property is not managed by this manager, this function returns an empty string.
     *
     * @sa setValue()
     */
    QString value(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's currently set regular expression.
     * If the given @a property is not managed by this manager, this function returns an empty expression.
     *
     * @sa setRegExp()
     */
    QRegExp regExp(const QExtPEProperty *property) const;

    /**
     * @brief Returns read-only status of the property.
     * When property is read-only it's value can be selected and copied from editor but not modified.
     * @sa QExtPEStringPropertyManager::setReadOnly
     */
    bool isReadOnly(const QExtPEProperty *property) const;
    EchoMode echoMode(const QExtPEProperty *property) const QEXT_OVERRIDE;

public Q_SLOTS:
    void setValue(QExtPEProperty *property, const QString &val);
    void setRegExp(QExtPEProperty *property, const QRegExp &regExp);
    void setEchoMode(QExtPEProperty *property, EchoMode echoMode);

    /**
     * @brief Sets read-only status of the property.
     * @sa QExtPEStringPropertyManager::setReadOnly
     */
    void setReadOnly(QExtPEProperty *property, bool readOnly);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, const QString &val);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its currenlty set regular
     * expression, passing a pointer to the @a property and the new @a regExp as parameters.
     *
     * @sa setRegExp()
     */
    void regExpChanged(QExtPEProperty *property, const QRegExp &regExp);
    void echoModeChanged(QExtPEProperty *property, const int);
    void readOnlyChanged(QExtPEProperty *property, bool);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString displayText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPEStringPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEStringPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPEStringPropertyManager)
};


/**
 * @class QExtPEDatePropertyManager
 * @brief The QExtPEDatePropertyManager provides and manages QDate properties.
 * A date property has a current value, and a range specifying the valid dates.
 * The range is defined by a minimum and a maximum value.
 *
 * The property's values can be retrieved using the minimum(), maximum() and value() functions, and can be set using
 * the setMinimum(), setMaximum() and setValue() slots. Alternatively, the range can be defined in one go using the
 * setRange() slot.
 *
 * In addition, QExtPEDatePropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes, and the rangeChanged() signal which is emitted whenever such a property changes
 * its range of valid dates.
 *
 * @sa QExtPEAbstractPropertyManager, QExtPEDateEditFactory, QExtPEDateTimePropertyManager
 */
class QExtPEDatePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPEDatePropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPEDatePropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPEDatePropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by @e this manager, this function returns an invalid date.
     *
     * @sa setValue()
     */
    QDate value(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a  property's  minimum date.
     *
     * @sa maximum(), setRange()
     */
    QDate minimum(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's maximum date.
     *
     * @sa minimum(), setRange()
     */
    QDate maximum(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     * If the specified @a value is not a valid date according to the given @a property's range, the value is
     * adjusted to the nearest valid value within the range.
     *
     * @sa value(), setRange(), valueChanged()
     */
    void setValue(QExtPEProperty *property, const QDate &val);

    /**
     * @brief Sets the minimum value for the given @a property to @a minVal.
     * When setting the minimum value, the maximum and current values are adjusted if necessary (ensuring that the
     * range remains valid and that the current value is within in the range).
     *
     *  @sa minimum(), setRange()
     */
    void setMinimum(QExtPEProperty *property, const QDate &minVal);

    /**
     * @brief Sets the maximum value for the given @a property to @a maxVal.
     * When setting the maximum value, the minimum and current values are adjusted if necessary (ensuring that the
     * range remains valid and that the current value is within in the range).
     *
     * @sa maximum(), setRange()
     */
    void setMaximum(QExtPEProperty *property, const QDate &maxVal);

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
    void setRange(QExtPEProperty *property, const QDate &minVal, const QDate &maxVal);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, const QDate &val);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its range of valid dates,
     * passing a pointer to the @a property and the new @a minimum and @a maximum dates.
     *
     * @sa setRange()
     */
    void rangeChanged(QExtPEProperty *property, const QDate &minVal, const QDate &maxVal);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPEDatePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEDatePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPEDatePropertyManager)
};


/**
 * @class QExtPETimePropertyManager
 * @brief The QExtPETimePropertyManager provides and manages QTime properties.
 * A time property's value can be retrieved using the value() function, and set using the setValue() slot.
 *
 * In addition, QExtPETimePropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtPEAbstractPropertyManager, QExtPETimeEditFactory
 */
class QExtPETimePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPETimePropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPETimePropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPETimePropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value.
     * If the given property is not managed by this manager, this function returns an invalid time object.
     *
     * @sa setValue()
     */
    QTime value(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtPEProperty *property, const QTime &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, const QTime &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPETimePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPETimePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPETimePropertyManager)
};

/**
 * @class QExtPEDateTimePropertyManager
 * @brief The QExtPEDateTimePropertyManager provides and manages QDateTime properties.
 * A date and time property has a current value which can be retrieved using the value() function, and set using
 * the setValue() slot. In addition, QExtPEDateTimePropertyManager provides the valueChanged() signal which is emitted
 * whenever a property created by this manager changes.
 *
 * @sa QExtPEAbstractPropertyManager, QExtPEDateTimeEditFactory, QExtPEDatePropertyManager
 */
class QExtPEDateTimePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPEDateTimePropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPEDateTimePropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPEDateTimePropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns an invalid QDateTime object.
     *
     * @sa setValue()
     */
    QDateTime value(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtPEProperty *property, const QDateTime &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     */
    void valueChanged(QExtPEProperty *property, const QDateTime &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPEDateTimePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEDateTimePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPEDateTimePropertyManager)
};


/**
 * @class QExtPEKeySequencePropertyManager
 * @brief The QExtPEKeySequencePropertyManager provides and manages QKeySequence properties.
 * A key sequence's value can be retrieved using the value() function, and set using the setValue() slot.
 *
 * In addition, QExtPEKeySequencePropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtPEAbstractPropertyManager
 */
class QExtPEKeySequencePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPEKeySequencePropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPEKeySequencePropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPEKeySequencePropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns an empty QKeySequence object.
     *
     * @sa setValue()
     */
    QKeySequence value(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtPEProperty *property, const QKeySequence &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     */
    void valueChanged(QExtPEProperty *property, const QKeySequence &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPEKeySequencePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEKeySequencePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPEKeySequencePropertyManager)
};

/**
 * @class QExtPECharPropertyManager
 * @brief The QExtPECharPropertyManager provides and manages QChar properties.
 * A char's value can be retrieved using the value() function, and set using the setValue() slot.
 *
 * In addition, QExtPECharPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtPEAbstractPropertyManager
 */
class QExtPECharPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPECharPropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPECharPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPECharPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns an null QChar object.
     *
     * @sa setValue()
     */
    QChar value(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtPEProperty *property, const QChar &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     */
    void valueChanged(QExtPEProperty *property, const QChar &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPECharPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPECharPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPECharPropertyManager)
};

/**
 * @class QExtPELocalePropertyManager
 * @brief The QExtPELocalePropertyManager provides and manages QLocale properties.
 * A locale property has nested @e language and @e country subproperties. The top-level property's value can be
 * retrieved using the value() function, and set using the setValue() slot.
 *
 * The subproperties are created by QExtPEEnumPropertyManager object.
 * These submanager can be retrieved using the subEnumPropertyManager() function. In order to provide editing widgets
 * for the subproperties in a property browser widget, this manager must be associated with editor factory.
 *
 * In addition, QExtPELocalePropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtPEAbstractPropertyManager, QExtPEEnumPropertyManager
 */
class QExtPEEnumPropertyManager;
class QExtPELocalePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPELocalePropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPELocalePropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPELocalePropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that creates the nested @e language and @e country subproperties.
     * In order to provide editing widgets for the mentioned subproperties in a property browser widget, this manager
     * must be associated with an editor factory.
     *
     * @sa QExtPEAbstractPropertyEditor::setFactoryForManager()
     */
    QExtPEEnumPropertyManager *subEnumPropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given property is not managed by this manager, this function returns the default locale.
     *
     * @sa setValue()
     */
    QLocale value(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value. Nested properties are updated automatically.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtPEProperty *property, const QLocale &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, const QLocale &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPELocalePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPELocalePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPELocalePropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotEnumChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtPEProperty *))
};

/**
 * @class QExtPEPointPropertyManager
 * @brief The QExtPEPointPropertyManager provides and manages QPoint properties
 * A point property has nested @e x and @e y subproperties. The top-level property's value can be retrieved using
 * the value() function, and set using the setValue() slot.
 *
 * The subproperties are created by a QExtPEIntPropertyManager object. This manager can be retrieved using the
 * subIntPropertyManager() function. In order to provide editing widgets for the subproperties in a property browser
 * widget, this manager must be associated with an editor factory.
 *
 * In addition, QExtPEPointPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtPEAbstractPropertyManager, QExtPEIntPropertyManager, QExtPEPointFPropertyManager
 */
class QExtPEPointPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPEPointPropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPEPointPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPEPointPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that creates the nested @e x and @e y subproperties.
     *
     * In order to provide editing widgets for the subproperties in a property browser widget, this manager must be
     * associated with an editor factory.
     *
     * @sa QExtPEAbstractPropertyEditor::setFactoryForManager()
     */
    QExtPEIntPropertyManager *subIntPropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns a point with coordinates (0, 0).
     *
     * @sa setValue()
     */
    QPoint value(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value. Nested properties are updated automatically.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtPEProperty *property, const QPoint &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, const QPoint &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPEPointPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEPointPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPEPointPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtPEProperty *))
};

/**
 * @class QExtPEPointFPropertyManager
 * @brief The QExtPEPointFPropertyManager provides and manages QPointF properties.
 *
 * A point property has nested @e x and @e y subproperties. The top-level property's value can be retrieved using the
 * value() function, and set using the setValue() slot.
 *
 * The subproperties are created by a QExtPEDoublePropertyManager object. This manager can be retrieved using the
 * subDoublePropertyManager() function. In order to provide editing widgets for the subproperties in a property browser
 * widget, this manager must be associated with an editor factory.
 *
 * In addition, QExtPEPointFPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtPEAbstractPropertyManager, QExtPEDoublePropertyManager, QExtPEPointPropertyManager
 */
class QExtPEPointFPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPEPointFPropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPEPointFPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPEPointFPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that creates the nested @e x and @e y subproperties.
     *
     * In order to provide editing widgets for the subproperties in a property browser widget, this manager must be
     * associated with an editor factory.
     *
     * @sa QExtPEAbstractPropertyEditor::setFactoryForManager()
     */
    QExtPEDoublePropertyManager *subDoublePropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns a point with coordinates (0, 0).
     *
     * @sa setValue()
     */
    QPointF value(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's precision, in decimals.
     *
     * @sa setDecimals()
     */
    int decimals(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the precision of the given @a property to @a prec.
     * The valid decimal range is 0-13. The default is 2.
     *
     * @sa decimals()
     */
    void setDecimals(QExtPEProperty *property, int prec);

    /**
     * @brief Sets the value of the given @a property to @a value. Nested properties are updated automatically.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtPEProperty *property, const QPointF &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its precision of value,
     * passing a pointer to the @a property and the new @a prec value
     *
     * @sa setDecimals()
     */
    void decimalsChanged(QExtPEProperty *property, int prec);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, const QPointF &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPEPointFPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEPointFPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPEPointFPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotDoubleChanged(QExtPEProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtPEProperty *))
};


/**
 * @class QExtPESizePropertyManager
 * @brief The QExtPESizePropertyManager provides and manages QSize properties.
 * A size property has nested @e width and @e height subproperties. The top-level property's value can be retrieved
 * using the value() function, and set using the setValue() slot.
 *
 * The subproperties are created by a QExtPEIntPropertyManager object. This manager can be retrieved using the
 * subIntPropertyManager() function. In order to provide editing widgets for the subproperties in a property browser
 * widget, this manager must be associated with an editor factory.
 *
 * A size property also has a range of valid values defined by a minimum size and a maximum size. These sizes can be
 * retrieved using the minimum() and the maximum() functions, and set using the setMinimum() and setMaximum() slots.
 * Alternatively, the range can be defined in one go using the setRange() slot.
 *
 * In addition, QExtPESizePropertyManager provides the valueChanged() signal which is emitted whenever a property created
 * by this manager changes, and the rangeChanged() signal which is emitted whenever such a property changes its range
 * of valid sizes.
 *
 * @sa QExtPEAbstractPropertyManager, QExtPEIntPropertyManager, QExtPESizeFPropertyManager
 */
class QExtPESizePropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPESizePropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPESizePropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPESizePropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that creates the nested @e width and @e height subproperties.
     * In order to provide editing widgets for the @e width and @e height properties in a property browser widget,
     * this manager must be associated with an editor factory.
     *
     * @sa QExtPEAbstractPropertyEditor::setFactoryForManager()
     */
    QExtPEIntPropertyManager *subIntPropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns an invalid size
     *
     * @sa setValue()
     */
    QSize value(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's minimum size value.
     *
     * sa setMinimum(), maximum(), setRange()
     */
    QSize minimum(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's maximum size value.
     *
     * sa setMaximum(), minimum(), setRange()
     */
    QSize maximum(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     *
     * If the specified @a value is not valid according to the given @a property's size range, the @a value is adjusted
     * to the nearest valid value within the size range.
     *
     * @sa value(), setRange(), valueChanged()
     */
    void setValue(QExtPEProperty *property, const QSize &val);

    /**
     * @brief Sets the minimum size value for the given @a property to @a minVal.
     * When setting the minimum size value, the maximum and current values are adjusted if necessary (ensuring that
     * the size range remains valid and that the current value is within the range).
     *
     * @sa minimum(), setRange(), rangeChanged()
     */
    void setMinimum(QExtPEProperty *property, const QSize &minVal);

    /**
     * @brief Sets the maximum size value for the given @a property to @a maxVal.
     * When setting the maximum size value, the minimum and current values are adjusted if necessary (ensuring that the
     * size range remains valid and that the current value is within the range).
     *
     * @sa maximum(), setRange(), rangeChanged()
     */
    void setMaximum(QExtPEProperty *property, const QSize &maxVal);

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
    void setRange(QExtPEProperty *property, const QSize &minVal, const QSize &maxVal);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, const QSize &val);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its range of valid sizes,
     * passing a pointer to the @a property and the new @a minimum and @a maximum sizes.
     *
     * @sa setRange()
     */
    void rangeChanged(QExtPEProperty *property, const QSize &minVal, const QSize &maxVal);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPESizePropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPESizePropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPESizePropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtPEProperty *))
};


/**
 * @class QExtPESizeFPropertyManager
 * @brief The QExtPESizeFPropertyManager provides and manages QSizeF properties.
 * A size property has nested @e width and @e height subproperties. The top-level property's value can be retrieved
 * using the value() function, and set using the setValue() slot.
 *
 * The subproperties are created by a QExtPEDoublePropertyManager object. This manager can be retrieved using the
 * subDoublePropertyManager() function. In order to provide editing widgets for the subproperties in a property browser
 * widget, this manager must be associated with an editor factory.
 *
 * A size property also has a range of valid values defined by a minimum size and a maximum size. These sizes can be
 * retrieved using the minimum() and the maximum() functions, and set using the setMinimum() and setMaximum() slots.
 * Alternatively, the range can be defined in one go using the setRange() slot.
 *
 * In addition, QExtPESizeFPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes, and the rangeChanged() signal which is emitted whenever such a property changes
 * its range of valid sizes.
 *
 * @sa QExtPEAbstractPropertyManager, QExtPEDoublePropertyManager, QExtPESizePropertyManager
 */
class QExtPESizeFPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPESizeFPropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT
public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPESizeFPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPESizeFPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that creates the nested @e width and @e height subproperties.
     * In order to provide editing widgets for the @e width and @e height properties in a property browser widget,
     * this manager must be associated with an editor factory.
     *
     * @sa QExtPEAbstractPropertyEditor::setFactoryForManager()
     */
    QExtPEDoublePropertyManager *subDoublePropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns an invalid size
     *
     * @sa setValue()
     */
    QSizeF value(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's minimum size value.
     *
     * @sa setMinimum(), maximum(), setRange()
     */
    QSizeF minimum(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's maximum size value.
     *
     * @sa setMaximum(), minimum(), setRange()
     */
    QSizeF maximum(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's precision, in decimals.
     *
     * @sa setDecimals()
     */
    int decimals(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the precision of the given @a property to @a prec.
     * The valid decimal range is 0-13. The default is 2.
     *
     * @sa decimals()
     */
    void setDecimals(QExtPEProperty *property, int prec);

    /**
     * @brief Sets the value of the given @a property to @a value.
     * If the specified @a value is not valid according to the given @a property's size range, the @a value is adjusted
     * to the nearest valid value within the size range.
     *
     * @sa value(), setRange(), valueChanged()
     */
    void setValue(QExtPEProperty *property, const QSizeF &val);

    /**
     * @brief Sets the minimum size value for the given @a property to @a minVal.
     * When setting the minimum size value, the maximum and current values are adjusted if necessary (ensuring that
     * the size range remains valid and that the current value is within the range).
     *
     * @sa minimum(), setRange(), rangeChanged()
     */
    void setMinimum(QExtPEProperty *property, const QSizeF &minVal);

    /**
     * @brief Sets the maximum size value for the given @a property to @a maxVal.
     * When setting the maximum size value, the minimum and current values are adjusted if necessary (ensuring that the
     * size range remains valid and that the current value is within the range).
     *
     * @sa maximum(), setRange(), rangeChanged()
     */
    void setMaximum(QExtPEProperty *property, const QSizeF &maxVal);

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
    void setRange(QExtPEProperty *property, const QSizeF &minVal, const QSizeF &maxVal);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its precision of value,
     * passing a pointer to the @a property and the new @a prec value
     *
     * @sa setDecimals()
     */
    void decimalsChanged(QExtPEProperty *property, int prec);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, const QSizeF &val);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its range of valid sizes,
     * passing a pointer to the @a property and the new @a minimum and @a maximum sizes.
     *
     * @sa setRange()
     */
    void rangeChanged(QExtPEProperty *property, const QSizeF &minVal, const QSizeF &maxVal);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPESizeFPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPESizeFPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPESizeFPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotDoubleChanged(QExtPEProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtPEProperty *))
};

/**
 * @class QExtPERectPropertyManager
 * @brief The QExtPERectPropertyManager provides and manages QRect properties.
 * A rectangle property has nested @e x, @e y, @e width and @e height subproperties. The top-level property's value
 * can be retrieved using the value() function, and set using the setValue() slot.
 *
 * The subproperties are created by a QExtPEIntPropertyManager object. This manager can be retrieved using the
 * subIntPropertyManager() function. In order to provide editing widgets for the subproperties in a property browser
 * widget, this manager must be associated with an editor factory.
 *
 * A rectangle property also has a constraint rectangle which can be retrieved using the constraint() function, and
 * set using the setConstraint() slot.
 *
 * In addition, QExtPERectPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes, and the constraintChanged() signal which is emitted whenever such a property
 * changes its constraint rectangle.
 *
 * @sa QExtPEAbstractPropertyManager, QExtPEIntPropertyManager, QExtPERectFPropertyManager
 */
class QExtPERectPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPERectPropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPERectPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * @brief Destroys this manager, and all the properties it has created.
     */
    ~QExtPERectPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that creates the nested @e x, @e y, @e width and @e height subproperties.
     * In order to provide editing widgets for the mentioned subproperties in a property browser widget, this manager
     * must be associated with an editor factory.
     *
     * @sa QExtPEAbstractPropertyEditor::setFactoryForManager()
     */
    QExtPEIntPropertyManager *subIntPropertyManager() const;

    /**
     * @brief Returns the given @a property's value
     *
     * If the given @a property is not managed by this manager, this function returns an invalid rectangle.
     *
     * @sa setValue(), constraint()
     */
    QRect value(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's constraining rectangle. If returned value is null QRect it means there
     * is no constraint applied.
     *
     * @sa value(), setConstraint()
     */
    QRect constraint(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value. Nested properties are updated automatically.
     *
     * If the specified @a value is not inside the given @a property's constraining rectangle, the value is adjusted
     * accordingly to fit within the constraint.
     *
     * @sa value(), setConstraint(), valueChanged()
     */
    void setValue(QExtPEProperty *property, const QRect &val);

    /**
     * @brief Sets the given @a property's constraining rectangle to @a constraint.
     * When setting the constraint, the current value is adjusted if necessary (ensuring that the current rectangle
     * value is inside the constraint). In order to reset the constraint pass a null QRect value.
     *
     * @sa setValue(), constraint(), constraintChanged()
     */
    void setConstraint(QExtPEProperty *property, const QRect &constraint);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, const QRect &val);

    /**
     * @brief This signal is emitted whenever property changes its constraint rectangle, passing a pointer to the
     * @a property and the new @a constraint rectangle as parameters.
     *
     * @sa setConstraint()
     */
    void constraintChanged(QExtPEProperty *property, const QRect &constraint);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPERectPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPERectPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPERectPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtPEProperty *))
};


/**
 * @class QExtPERectFPropertyManager
 * @brief The QExtPERectFPropertyManager provides and manages QRectF properties.
 * A rectangle property has nested @e x, @e y, @e width and @e height subproperties. The top-level property's value
 * can be retrieved using the value() function, and set using the setValue() slot.
 *
 * The subproperties are created by a QExtPEDoublePropertyManager object. This manager can be retrieved using the
 * subDoublePropertyManager() function. In order to provide editing widgets for the subproperties in a property browser
 * widget, this manager must be associated with an editor factory.
 *
 * A rectangle property also has a constraint rectangle which can be retrieved using the constraint() function, and set
 * using the setConstraint() slot.
 *
 * In addition, QExtPERectFPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes, and the constraintChanged() signal which is emitted whenever such a property
 * changes its constraint rectangle.
 *
 * @sa QExtPEAbstractPropertyManager, QExtPEDoublePropertyManager, QExtPERectPropertyManager
 */
class QExtPERectFPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPERectFPropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPERectFPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPERectFPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that creates the nested @e x, @e y, @e width and @e height subproperties.
     * In order to provide editing widgets for the mentioned subproperties in a property browser widget, this manager
     * must be associated with an editor factory.
     *
     * @sa QExtPEAbstractPropertyEditor::setFactoryForManager()
     */
    QExtPEDoublePropertyManager *subDoublePropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns an invalid rectangle.
     *
     * @sa setValue(), constraint()
     */
    QRectF value(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's constraining rectangle. If returned value is null QRectF it means there
     * is no constraint applied.
     *
     * @sa value(), setConstraint()
     */
    QRectF constraint(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's precision, in decimals.
     *
     * @sa setDecimals()
     */
    int decimals(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the precision of the given @a property to @a prec.
     * The valid decimal range is 0-13. The default is 2.
     *
     * @sa decimals()
     */
    void setDecimals(QExtPEProperty *property, int prec);

    /**
     * @brief Sets the value of the given @a property to @a value. Nested properties are updated automatically.
     * If the specified @a value is not inside the given @a property's constraining rectangle, the value is adjusted
     * accordingly to fit within the constraint.
     *
     * @sa value(), setConstraint(), valueChanged()
     */
    void setValue(QExtPEProperty *property, const QRectF &val);

    /**
     * @brief Sets the given @a property's constraining rectangle to @a constraint.
     * When setting the constraint, the current value is adjusted if necessary (ensuring that the current rectangle
     * value is inside the constraint). In order to reset the constraint pass a null QRectF value.
     *
     * @sa setValue(), constraint(), constraintChanged()
     */
    void setConstraint(QExtPEProperty *property, const QRectF &constraint);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its precision of value,
     * passing a pointer to the @a property and the new @a prec value
     *
     * @sa setDecimals()
     */
    void decimalsChanged(QExtPEProperty *property, int prec);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, const QRectF &val);

    /**
     * @brief This signal is emitted whenever property changes its constraint rectangle, passing a pointer to the
     * @a property and the new @a constraint rectangle as parameters.
     *
     * @sa setConstraint()
     */
    void constraintChanged(QExtPEProperty *property, const QRectF &constraint);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPERectFPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPERectFPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPERectFPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotDoubleChanged(QExtPEProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtPEProperty *))
};

/**
 * @class QExtPEEnumPropertyManager
 * @brief The QExtPEEnumPropertyManager provides and manages enum properties.
 * Each enum property has an associated list of enum names which can be retrieved using the enumNames() function,
 * and set using the corresponding setEnumNames() function. An enum property's value is represented by an index in
 * this list, and can be retrieved and set using the value() and setValue() slots respectively.
 *
 * Each enum value can also have an associated icon. The mapping from values to icons can be set using the
 * setEnumIcons() function and queried with the enumIcons() function.
 *
 * In addition, QExtPEEnumPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes. The enumNamesChanged() or enumIconsChanged() signal is emitted whenever the list
 * of enum names or icons is altered.
 *
 * sa QExtPEAbstractPropertyManager, QExtPEEnumEditorFactory
 */
class QExtPEEnumPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPEEnumPropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent
     */
    QExtPEEnumPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPEEnumPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the given @a property's value which is an index in the list returned by enumNames()
     * If the given property is not managed by this manager, this function returns -1.
     *
     * @sa enumNames(), setValue()
     */
    int value(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's list of enum names.
     *
     * @sa value(), setEnumNames()
     */
    QStringList enumNames(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's map of enum values to their icons.
     *
     * @sa value(), setEnumIcons()
     */
    QMap<int, QIcon> enumIcons(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given  @a property to @a value.
     * The specified @a value must be less than the size of the given @a property's enumNames() list, and larger
     * than (or equal to) 0.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtPEProperty *property, int val);

    /**
     * @brief Sets the given @a property's list of enum names to @a enumNames. The @a property's current value is
     * reset to 0 indicating the first item of the list.
     *
     * If the specified @a enumNames list is empty, the @a property's current value is set to -1.
     *
     * @sa enumNames(), enumNamesChanged()
     */
    void setEnumNames(QExtPEProperty *property, const QStringList &names);

    /**
     * @brief Sets the given @a property's map of enum values to their icons to @a enumIcons.
     * Each enum value can have associated icon. This association is represented with passed @a enumIcons map.
     *
     * @sa enumNames(), enumNamesChanged()
     */
    void setEnumIcons(QExtPEProperty *property, const QMap<int, QIcon> &icons);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, int val);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its enum names, passing a
     * pointer to the @a property and the new @a names as parameters.
     *
     * @sa setEnumNames()
     */
    void enumNamesChanged(QExtPEProperty *property, const QStringList &names);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its enum icons, passing a
     * pointer to the @a property and the new mapping of values to @a icons as parameters.
     *
     * @sa setEnumIcons()
     */
    void enumIconsChanged(QExtPEProperty *property, const QMap<int, QIcon> &icons);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QIcon valueIcon(const QExtPEProperty *property) const QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPEEnumPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEEnumPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPEEnumPropertyManager)
};

/**
 * @class QExtPEFlagPropertyManager
 * @brief The QExtPEFlagPropertyManager provides and manages flag properties.
 * Each flag property has an associated list of flag names which can be retrieved using the flagNames() function,
 * and set using the corresponding setFlagNames() function.
 *
 * The flag manager provides properties with nested boolean subproperties representing each flag, i.e. a flag
 * property's value is the binary combination of the subproperties' values. A property's value can be retrieved and set
 * using the value() and setValue() slots respectively. The combination of flags is represented by single int
 * value - that's why it's possible to store up to 32 independent flags in one flag property.
 *
 * The subproperties are created by a QExtPEBoolPropertyManager object. This manager can be retrieved using the
 * subBoolPropertyManager() function. In order to provide editing widgets for the subproperties in a property browser
 * widget, this manager must be associated with an editor factory.
 *
 * In addition, QExtPEFlagPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes, and the flagNamesChanged() signal which is emitted whenever the list of flag names
 * is altered.
 *
 * @sa QExtPEAbstractPropertyManager, QExtPEBoolPropertyManager
 */
class QExtPEFlagPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPEFlagPropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPEFlagPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPEFlagPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that produces the nested boolean subproperties representing each flag.
     *
     * In order to provide editing widgets for the subproperties in a property browser widget, this manager must be
     * associated with an editor factory.
     *
     * @sa QExtPEAbstractPropertyEditor::setFactoryForManager()
     */
    QExtPEBoolPropertyManager *subBoolPropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given property is not managed by this manager, this function returns 0.
     *
     * @sa flagNames(), setValue()
     */
    int value(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's list of flag names.
     *
     * @sa value(), setFlagNames()
     */
    QStringList flagNames(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value. Nested properties are updated automatically.
     *
     * The specified @a value must be less than the binary combination of the property's flagNames() list
     * size (i.e. less than 2\sup n, where @c n is the size of the list) and larger than (or equal to) 0.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtPEProperty *property, int val);

    /**
     * @brief Sets the given @a property's list of flag names to @a flagNames. The property's current value is reset
     * to 0 indicating the first item of the list.
     *
     * @sa flagNames(), flagNamesChanged()
     */
    void setFlagNames(QExtPEProperty *property, const QStringList &names);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a  property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, int val);

    /**
     * @brief This signal is emitted whenever a property created by this manager changes its flag names, passing a
     * pointer to the @a property and the new @a names as parameters.
     *
     * @sa setFlagNames()
     */
    void flagNamesChanged(QExtPEProperty *property, const QStringList &names);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPEFlagPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEFlagPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPEFlagPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotBoolChanged(QExtPEProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtPEProperty *))
};

/**
 * @class QExtPESizePolicyPropertyManager
 * @brief The QExtPESizePolicyPropertyManager provides and manages QSizePolicy properties.
 * A size policy property has nested @e horizontalPolicy, @e verticalPolicy, @e horizontalStretch and @e verticalStretch
 * subproperties. The top-level property's value can be retrieved using the value() function, and set using the
 * setValue() slot.
 *
 * The subproperties are created by QExtPEIntPropertyManager and QExtPEEnumPropertyManager objects.
 * These managers can be retrieved using the subIntPropertyManager() and subEnumPropertyManager() functions respectively.
 * In order to provide editing widgets for the subproperties in a property browser widget, these managers must be
 * associated with editor factories.
 *
 * In addition, QExtPESizePolicyPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtPEAbstractPropertyManager, QExtPEIntPropertyManager, QExtPEEnumPropertyManager
 */
class QExtPESizePolicyPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPESizePolicyPropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    explicit QExtPESizePolicyPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPESizePolicyPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that creates the nested @e horizontalStretch and @e verticalStretch subproperties.
     * In order to provide editing widgets for the mentioned subproperties in a property browser widget, this manager
     * must be associated with an editor factory.
     *
     * @sa QExtPEAbstractPropertyEditor::setFactoryForManager()
     */
    QExtPEIntPropertyManager *subIntPropertyManager() const;

    /**
     * @brief Returns the manager that creates the nested @e horizontalPolicy and @e verticalPolicy subproperties.
     *
     * In order to provide editing widgets for the mentioned subproperties in a property browser widget, this manager
     * must be associated with an editor factory.
     *
     * @sa QExtPEAbstractPropertyEditor::setFactoryForManager()
     */
    QExtPEEnumPropertyManager *subEnumPropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given property is not managed by this manager, this function returns the default size policy.
     *
     * @sa setValue()
     */
    QSizePolicy value(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value. Nested properties are updated automatically.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtPEProperty *property, const QSizePolicy &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, const QSizePolicy &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPESizePolicyPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPESizePolicyPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPESizePolicyPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotEnumChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtPEProperty *))
};


/**
 * @class QExtPEFontPropertyManager
 * @brief The QExtPEFontPropertyManager provides and manages QFont properties.
 * A font property has nested @e family, @e pointSize, @e bold, @e italic, @e underline, @e strikeOut and @e kerning
 * subproperties. The top-level property's value can be retrieved using the value() function, and set using the
 * setValue() slot.
 *
 * The subproperties are created by QExtPEIntPropertyManager, QExtPEEnumPropertyManager and QExtPEBoolPropertyManager objects.
 * These managers can be retrieved using the corresponding subIntPropertyManager(), subEnumPropertyManager() and
 * subBoolPropertyManager() functions. In order to provide editing widgets for the subproperties in a property browser
 * widget, these managers must be associated with editor factories.
 *
 * In addition, QExtPEFontPropertyManager provides the valueChanged() signal which is emitted whenever a property created
 * by this manager changes.
 *
 * @sa QExtPEAbstractPropertyManager, QExtPEEnumPropertyManager, QExtPEIntPropertyManager, QExtPEBoolPropertyManager
 */
class QExtPEFontPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPEFontPropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPEFontPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPEFontPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that creates the @e pointSize subproperty.
     * In order to provide editing widgets for the @e pointSize property in a property browser widget, this manager
     * must be associated with an editor factory.
     *
     * @sa QExtPEAbstractPropertyEditor::setFactoryForManager()
     */
    QExtPEIntPropertyManager *subIntPropertyManager() const;

    /**
     * @brief Returns the manager that create the @e family subproperty.
     * In order to provide editing widgets for the @e family property in a property browser widget, this manager must
     * be associated with an editor factory.
     *
     * @sa QExtPEAbstractPropertyEditor::setFactoryForManager()
     */
    QExtPEEnumPropertyManager *subEnumPropertyManager() const;

    /**
     * @brief Returns the manager that creates the  @e bold, @e italic, @e underline, @e strikeOut and @e kerning
     * subproperties.
     * In order to provide editing widgets for the mentioned properties in a property browser widget, this manager must
     * be associated with an editor factory.
     *
     * @sa QExtPEAbstractPropertyEditor::setFactoryForManager()
     */
    QExtPEBoolPropertyManager *subBoolPropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given property is not managed by this manager, this function returns a font object that uses the
     * application's default font.
     *
     * @sa setValue()
     */
    QFont value(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value. Nested properties are updated automatically.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtPEProperty *property, const QFont &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, const QFont &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QIcon valueIcon(const QExtPEProperty *property) const QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPEFontPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEFontPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPEFontPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotEnumChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotBoolChanged(QExtPEProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtPEProperty *))
    Q_PRIVATE_SLOT(d_func(), void slotFontDatabaseChanged())
    Q_PRIVATE_SLOT(d_func(), void slotFontDatabaseDelayedChange())
};


/**
 * @class QExtPEColorPropertyManager
 * @brief The QExtPEColorPropertyManager provides and manages QColor properties.
 * A color property has nested @e red, @e green and @e blue subproperties. The top-level property's value can be
 * retrieved using the value() function, and set using the setValue() slot.
 *
 * The subproperties are created by a QExtPEIntPropertyManager object.
 * This manager can be retrieved using the subIntPropertyManager() function.  In order to provide editing widgets for
 * the subproperties in a property browser widget, this manager must be associated with an editor factory.
 *
 * In addition, QExtPEColorPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtPEAbstractPropertyManager, QExtPEAbstractPropertyEditor, QExtPEIntPropertyManager
 */
class QExtPEColorPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPEColorPropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPEColorPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPEColorPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Returns the manager that produces the nested @e red, @e green and @e blue subproperties.
     * In order to provide editing widgets for the subproperties in a property browser widget, this manager must be
     * associated with an editor factory.
     *
     * @sa QExtPEAbstractPropertyEditor::setFactoryForManager()
     */
    QExtPEIntPropertyManager *subIntPropertyManager() const;

    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by @e this manager, this function returns an invalid color.
     *
     * @sa setValue()
     */
    QColor value(const QExtPEProperty *property) const;

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.  Nested properties are updated automatically.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtPEProperty *property, const QColor &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, const QColor &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QIcon valueIcon(const QExtPEProperty *property) const QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPEColorPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEColorPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPEColorPropertyManager)
    Q_PRIVATE_SLOT(d_func(), void slotIntChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QExtPEProperty *))
};


/**
 * @class QExtPECursorPropertyManager
 * @brief The QExtPECursorPropertyManager provides and manages QCursor properties.
 * A cursor property has a current value which can be retrieved using the value() function, and set using the setValue()
 * slot. In addition, QExtPECursorPropertyManager provides the valueChanged() signal which is emitted whenever a property
 * created by this manager changes.
 *
 * @sa QExtPEAbstractPropertyManager
 */
class QExtPECursorPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPECursorPropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT

public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPECursorPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPECursorPropertyManager() QEXT_OVERRIDE;

#ifndef QT_NO_CURSOR
    /**
     * @brief Returns the given @a property's value.
     * If the given @a property is not managed by this manager, this function returns a default QCursor object.
     *
     * @sa setValue()
     */
    QCursor value(const QExtPEProperty *property) const;
#endif

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     *
     * @sa value(), valueChanged()
     */
    void setValue(QExtPEProperty *property, const QCursor &val);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, const QCursor &val);

protected:
    /**
     * @brief reimp
     */
    void initializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    void uninitializeProperty(QExtPEProperty *property) QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QIcon valueIcon(const QExtPEProperty *property) const QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPECursorPropertyManagerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPECursorPropertyManager)
    QEXT_DISABLE_COPY_MOVE(QExtPECursorPropertyManager)
};


#endif // _QEXTPEPROPERTYMANAGER_H
