#ifndef _QEXTPEVARIANTPROPERTY_H
#define _QEXTPEVARIANTPROPERTY_H

#include <qextPEProperty.h>
#include <qextPEWidgetFactory.h>
#include <qextPEPropertyManager.h>

#include <QIcon>

typedef QMap<int, QIcon> QExtPEIconMap;
class QExtPEVariantPropertyManager;
class QExtPEVariantPropertyPrivate;
/**
 * @class QExtPEVariantProperty
 * @brief The QExtPEVariantProperty class is a convenience class handling QVariant based properties.
 * QExtPEVariantProperty provides additional API: A property's type, value type, attribute values and current value can
 * easily be retrieved using the propertyType(), valueType(), attributeValue() and value() functions respectively.
 * In addition, the attribute values and the current value can be set using the corresponding setValue() and
 * setAttribute() functions.
 *
 * For example, instead of writing:
 * @code
 *      QExtPEVariantPropertyManager *variantPropertyManager;
 *      QExtPEProperty *property;
 *      variantPropertyManager->setValue(property, 10);
 * @endcode
 *
 * you can write:
 *
 * @code
 *      QExtPEVariantPropertyManager *variantPropertyManager;
 *      QExtPEVariantProperty *property;
 *      property->setValue(10);
 * @endcode
 *
 * QExtPEVariantProperty instances can only be created by the QExtPEVariantPropertyManager class.
 *
 * @sa QExtPEProperty, QExtPEVariantPropertyManager, QExtPEVariantEditorFactory
 */
class QEXT_WIDGETS_API QExtPEVariantProperty : public QExtPEProperty
{
public:
    /**
     * Destroys this property.
     *
     * @sa QExtPEProperty::~QExtPEProperty()
     */
    ~QExtPEVariantProperty() QEXT_OVERRIDE;

    /**
     * @brief Returns the property's current value.
     *
     * @sa valueType(), setValue()
     */
    QVariant value() const;

    /**
     * @brief Returns this property's value for the specified @a attribute.
     * QExtPEVariantPropertyManager provides a couple of related functions:
     * @l{QExtPEVariantPropertyManager::attributes()}{attributes()} and
     * @l{QExtPEVariantPropertyManager::attributeType()}{attributeType()}.
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
     * QExtPEVariantPropertyManager provides several related functions:
     * @l{QExtPEVariantPropertyManager::enumTypeId()}{enumTypeId()},
     * @l{QExtPEVariantPropertyManager::flagTypeId()}{flagTypeId()} and
     * @l{QExtPEVariantPropertyManager::groupTypeId()}{groupTypeId()}.
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
     * QExtPEVariantPropertyManager provides the related
     * @l{QExtPEVariantPropertyManager::setAttribute()}{setAttribute()} function.
     *
     * @sa attributeValue()
     */
    void setAttribute(const QString &attribute, const QVariant &value);

protected:
    /**
     * @brief Creates a variant property using the given @a manager.
     * Do not use this constructor to create variant property instances;
     * use the QExtPEVariantPropertyManager::addProperty() function instead.  This constructor is used internally by the
     * QExtPEVariantPropertyManager::createProperty() function.
     *
     * @sa QExtPEVariantPropertyManager
     */
    QExtPEVariantProperty(QExtPEVariantPropertyManager *manager);

private:
    friend class QExtPEVariantPropertyManager;
    QExtPEVariantPropertyPrivate *dd_ptr;
};

/**
 * @class QExtPEVariantPropertyManager
 * @brief The QExtPEVariantPropertyManager class provides and manages QVariant based properties.
 * QExtPEVariantPropertyManager provides the addProperty() function which creates QExtPEVariantProperty objects.
 * The QExtPEVariantProperty class is a convenience class handling QVariant based properties inheriting QExtPEProperty.
 * A QExtPEProperty object created by a QExtPEVariantPropertyManager instance can be converted into a QExtPEVariantProperty
 * object using the variantProperty() function.
 *
 * The property's value can be retrieved using the value(), and set using the setValue() slot. In addition the
 * property's type, and the type of its value, can be retrieved using the propertyType() and valueType() functions
 * respectively.
 *
 * A property's type is a QVariant::Type enumerator value, and usually a property's type is the same as its value type.
 * But for some properties the types differ, for example for enums, flags and group types in which case
 * QExtPEVariantPropertyManager provides the enumTypeId(), flagTypeId() and groupTypeId() functions, respectively, to
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
 * @sa QExtPEVariantProperty, QExtPEVariantEditorFactory
 */
class QExtPEVariantPropertyManagerPrivate;
class QEXT_WIDGETS_API QExtPEVariantPropertyManager : public QExtPEAbstractPropertyManager
{
    Q_OBJECT
public:
    /**
     * @brief Creates a manager with the given @a parent.
     */
    QExtPEVariantPropertyManager(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this manager, and all the properties it has created.
     */
    ~QExtPEVariantPropertyManager() QEXT_OVERRIDE;

    /**
     * @brief Creates and returns a variant property of the given @a propertyType with the given @a name.
     * If the specified @a propertyType is not supported by this variant manager, this function returns 0.
     *
     * Do not use the inherited QExtPEAbstractPropertyManager::addProperty() function to create a variant property
     * (that function will always return 0 since it will not be clear what type the property should have).
     *
     * @sa isPropertyTypeSupported()
     */
    virtual QExtPEVariantProperty *addProperty(int propertyType, const QString &name = QString());

    /**
     * @brief Returns the given @a property's type.
     *
     * @sa valueType()
     */
    int propertyType(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's value type.
     *
     * @sa propertyType()
     */
    int valueType(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property converted into a QExtPEVariantProperty.
     * If the @a property was not created by this variant manager, the function returns 0.
     *
     * @sa createProperty()
     */
    QExtPEVariantProperty *variantProperty(const QExtPEProperty *property) const;

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
    virtual QVariant value(const QExtPEProperty *property) const;

    /**
     * @brief Returns the given @a property's value for the specified @a attribute
     *
     * If the given @a property was not created by @e this manager, or if the specified @a attribute does not exist,
     * this function returns an invalid variant.
     *
     * @sa attributes(), attributeType(), setAttribute()
     */
    virtual QVariant attributeValue(const QExtPEProperty *property, const QString &attribute) const;

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
     * @sa attributeType(), QExtPEEnumPropertyManager::enumIcons()
     */
    static int iconMapTypeId();

public Q_SLOTS:
    /**
     * @brief Sets the value of the given @a property to @a value.
     * The specified @a value must be of a type returned by valueType(), or of type that can be converted to
     * valueType() using the QVariant::canConvert() function, otherwise this function does nothing.
     *
     * @sa value(), QExtPEVariantProperty::setValue(), valueChanged()
     */
    virtual void setValue(QExtPEProperty *property, const QVariant &val);

    /**
     * @brief Sets the value of the specified @a attribute of the given @a property, to @a value.
     * The new @a value's type must be of the type returned by attributeType(), or of a type that can be converted to
     * attributeType() using the QVariant::canConvert() function, otherwise this function does nothing.
     *
     * @sa attributeValue(), QExtPEVariantProperty::setAttribute(), attributeChanged()
     */
    virtual void setAttribute(QExtPEProperty *property, const QString &attribute, const QVariant &value);

Q_SIGNALS:
    /**
     * @brief This signal is emitted whenever a property created by this manager changes its value, passing a pointer
     * to the @a property and the new @a value as parameters.
     *
     * @sa setValue()
     */
    void valueChanged(QExtPEProperty *property, const QVariant &val);

    /**
     * @brief This signal is emitted whenever an attribute of a property created by this manager changes its value,
     * passing a pointer to the @a property, the @a attribute and the new @a value as parameters.
     *
     * @sa setAttribute()
     */
    void attributeChanged(QExtPEProperty *property, const QString &attribute, const QVariant &val);

protected:
    /**
     * @brief reimp
     */
    QExtPEProperty *createProperty() QEXT_OVERRIDE;

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
    bool hasValue(const QExtPEProperty *property) const QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QIcon valueIcon(const QExtPEProperty *property) const QEXT_OVERRIDE;

    /**
     * @brief reimp
     */
    QString valueText(const QExtPEProperty *property) const QEXT_OVERRIDE;

private:
    QExtPEVariantPropertyManagerPrivate *d_ptr;
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtPEProperty *, int, int))
    Q_PRIVATE_SLOT(d_func(), void slotSingleStepChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtPEProperty *, double, double))
    Q_PRIVATE_SLOT(d_func(), void slotSingleStepChanged(QExtPEProperty *, double))
    Q_PRIVATE_SLOT(d_func(), void slotDecimalsChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, const QString &))
    Q_PRIVATE_SLOT(d_func(), void slotRegExpChanged(QExtPEProperty *, const QRegExp &))
    Q_PRIVATE_SLOT(d_func(), void slotEchoModeChanged(QExtPEProperty *, int))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, const QDate &))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtPEProperty *, const QDate &, const QDate &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, const QTime &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, const QDateTime &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, const QKeySequence &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, const QChar &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, const QLocale &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, const QPoint &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, const QPointF &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, const QSize &))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtPEProperty *, const QSize &, const QSize &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, const QSizeF &))
    Q_PRIVATE_SLOT(d_func(), void slotRangeChanged(QExtPEProperty *, const QSizeF &, const QSizeF &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, const QRect &))
    Q_PRIVATE_SLOT(d_func(), void slotConstraintChanged(QExtPEProperty *, const QRect &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, const QRectF &))
    Q_PRIVATE_SLOT(d_func(), void slotConstraintChanged(QExtPEProperty *, const QRectF &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, const QColor &))
    Q_PRIVATE_SLOT(d_func(), void slotEnumNamesChanged(QExtPEProperty *, const QStringList &))
    Q_PRIVATE_SLOT(d_func(), void slotEnumIconsChanged(QExtPEProperty *, const QMap<int, QIcon> &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, const QSizePolicy &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, const QFont &))
    Q_PRIVATE_SLOT(d_func(), void slotValueChanged(QExtPEProperty *, const QCursor &))
    Q_PRIVATE_SLOT(d_func(), void slotFlagNamesChanged(QExtPEProperty *, const QStringList &))
    Q_PRIVATE_SLOT(d_func(), void slotReadOnlyChanged(QExtPEProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotTextVisibleChanged(QExtPEProperty *, bool))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *))
    Q_PRIVATE_SLOT(d_func(), void slotPropertyRemoved(QExtPEProperty *, QExtPEProperty *))
    Q_DECLARE_PRIVATE(QExtPEVariantPropertyManager)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPEVariantPropertyManager)
};



/**
 * @class QExtPEVariantEditorFactory
 * @brief The QExtPEVariantEditorFactory class provides widgets for properties created by QExtPEVariantPropertyManager
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
 * @Note that QExtPEVariantPropertyManager supports several additional property types for which the
 * QExtPEVariantEditorFactory class does not provide editing widgets, e.g. QPoint and QSize. To provide widgets for other
 * types using the variant approach, derive from the QExtPEVariantEditorFactory class.
 *
 * @sa QExtPEAbstractWidgetFactory, QExtPEVariantPropertyManager
 */
class QExtPEVariantEditorFactoryPrivate;
class QEXT_WIDGETS_API QExtPEVariantEditorFactory : public QExtPEAbstractWidgetFactory<QExtPEVariantPropertyManager>
{
    Q_OBJECT
public:
    /**
     * @brief Creates a factory with the given @a parent.
     */
    explicit QExtPEVariantEditorFactory(QObject *parent = QEXT_NULLPTR);

    /**
     * Destroys this factory, and all the widgets it has created.
     */
    ~QExtPEVariantEditorFactory() QEXT_OVERRIDE;

protected:
    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void connectPropertyManager(QExtPEVariantPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    void disconnectPropertyManager(QExtPEVariantPropertyManager *manager) QEXT_OVERRIDE;

    /**
     * @brief Reimplemented from the QExtPEAbstractWidgetFactory class.
     */
    QWidget *createEditor(QExtPEVariantPropertyManager *manager, QExtPEProperty *property, QWidget *parent) QEXT_OVERRIDE;

private:
    QExtPEVariantEditorFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QExtPEVariantEditorFactory)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPEVariantEditorFactory)
};

Q_DECLARE_METATYPE(QIcon)
Q_DECLARE_METATYPE(QExtPEIconMap)

#endif // _QEXTPEVARIANTPROPERTY_H
