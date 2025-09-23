#include <private/qextPEVariantProperty_p.h>

#include <QLocale>
#include <QDateTime>

/***********************************************************************************************************************
 * QExtPEVariantProperty
***********************************************************************************************************************/
QExtPEVariantProperty::QExtPEVariantProperty(QExtPEVariantPropertyManager *manager)
    : QExtPEProperty(manager)
    , dd_ptr(new QExtPEVariantPropertyPrivate(manager))
{

}

QExtPEVariantProperty::~QExtPEVariantProperty()
{
    delete dd_ptr;
}

QVariant QExtPEVariantProperty::value() const
{
    return dd_ptr->manager->value(this);
}

QVariant QExtPEVariantProperty::attributeValue(const QString &attribute) const
{
    return dd_ptr->manager->attributeValue(this, attribute);
}

int QExtPEVariantProperty::valueType() const
{
    return dd_ptr->manager->valueType(this);
}

int QExtPEVariantProperty::propertyType() const
{
    return dd_ptr->manager->propertyType(this);
}

void QExtPEVariantProperty::setValue(const QVariant &value)
{
    dd_ptr->manager->setValue(this, value);
}

void QExtPEVariantProperty::setAttribute(const QString &attribute, const QVariant &value)
{
    dd_ptr->manager->setAttribute(this, attribute, value);
}


/***********************************************************************************************************************
** QExtPEVariantPropertyManager
***********************************************************************************************************************/
class QExtEnumPropertyType
{
};

class QExtFlagPropertyType
{
};


class QExtGroupPropertyType
{
};

Q_DECLARE_METATYPE(QExtEnumPropertyType)
Q_DECLARE_METATYPE(QExtFlagPropertyType)
Q_DECLARE_METATYPE(QExtGroupPropertyType)

int QExtPEVariantPropertyManager::enumTypeId()
{
    return qMetaTypeId<QExtEnumPropertyType>();
}

int QExtPEVariantPropertyManager::flagTypeId()
{
    return qMetaTypeId<QExtFlagPropertyType>();
}

int QExtPEVariantPropertyManager::groupTypeId()
{
    return qMetaTypeId<QExtGroupPropertyType>();
}

int QExtPEVariantPropertyManager::iconMapTypeId()
{
    return qMetaTypeId<QExtPEIconMap>();
}

typedef QMap<const QExtPEProperty *, QExtPEProperty *> PropertyMap;
Q_GLOBAL_STATIC(PropertyMap, propertyToWrappedProperty)

static QExtPEProperty *wrappedProperty(QExtPEProperty *property)
{
    return propertyToWrappedProperty()->value(property, QEXT_NULLPTR);
}



QExtPEVariantPropertyManagerPrivate::QExtPEVariantPropertyManagerPrivate() :
    m_constraintAttribute(QLatin1String("constraint")),
    m_singleStepAttribute(QLatin1String("singleStep")),
    m_decimalsAttribute(QLatin1String("decimals")),
    m_enumIconsAttribute(QLatin1String("enumIcons")),
    m_enumNamesAttribute(QLatin1String("enumNames")),
    m_flagNamesAttribute(QLatin1String("flagNames")),
    m_maximumAttribute(QLatin1String("maximum")),
    m_minimumAttribute(QLatin1String("minimum")),
    m_regExpAttribute(QLatin1String("regExp")),
    m_echoModeAttribute(QLatin1String("echoMode")),
    m_readOnlyAttribute(QLatin1String("readOnly")),
    m_textVisibleAttribute(QLatin1String("textVisible"))
{
}

int QExtPEVariantPropertyManagerPrivate::internalPropertyToType(QExtPEProperty *property) const
{
    int type = 0;
    QExtPEAbstractPropertyManager *internPropertyManager = property->propertyManager();
    if (qobject_cast<QExtPEIntPropertyManager *>(internPropertyManager))
    {
        type = QVariant::Int;
    }
    else if (qobject_cast<QExtPEEnumPropertyManager *>(internPropertyManager))
    {
        type = QExtPEVariantPropertyManager::enumTypeId();
    }
    else if (qobject_cast<QExtPEBoolPropertyManager *>(internPropertyManager))
    {
        type = QVariant::Bool;
    }
    else if (qobject_cast<QExtPEDoublePropertyManager *>(internPropertyManager))
    {
        type = QVariant::Double;
    }
    return type;
}

QExtPEVariantProperty *QExtPEVariantPropertyManagerPrivate::createSubProperty(QExtPEVariantProperty *parent,
                                                                          QExtPEVariantProperty *after,
                                                                          QExtPEProperty *internal)
{
    int type = internalPropertyToType(internal);
    if (!type)
    {
        return QEXT_NULLPTR;
    }

    bool wasCreatingSubProperties = m_creatingSubProperties;
    m_creatingSubProperties = true;

    QExtPEVariantProperty *varChild = q_ptr->addProperty(type, internal->propertyName());

    m_creatingSubProperties = wasCreatingSubProperties;

    varChild->setPropertyName(internal->propertyName());
    varChild->setToolTip(internal->toolTip());
    varChild->setStatusTip(internal->statusTip());
    varChild->setWhatsThis(internal->whatsThis());

    m_internalToProperty[internal] = varChild;
    propertyToWrappedProperty()->insert(varChild, internal);

    parent->insertSubProperty(varChild, after);
    return varChild;
}

void QExtPEVariantPropertyManagerPrivate::removeSubProperty(QExtPEVariantProperty *property)
{
    QExtPEProperty *internChild = wrappedProperty(property);
    bool wasDestroyingSubProperties = m_destroyingSubProperties;
    m_destroyingSubProperties = true;
    delete property;
    m_destroyingSubProperties = wasDestroyingSubProperties;
    m_internalToProperty.remove(internChild);
    propertyToWrappedProperty()->remove(property);
}

void QExtPEVariantPropertyManagerPrivate::slotPropertyInserted(QExtPEProperty *property, QExtPEProperty *parent,
                                                             QExtPEProperty *after)
{
    if (m_creatingProperty)
    {
        return;
    }

    QExtPEVariantProperty *varParent = m_internalToProperty.value(parent, QEXT_NULLPTR);
    if (!varParent)
    {
        return;
    }

    QExtPEVariantProperty *varAfter = QEXT_NULLPTR;
    if (after)
    {
        varAfter = m_internalToProperty.value(after, QEXT_NULLPTR);
        if (!varAfter)
        {
            return;
        }
    }

    this->createSubProperty(varParent, varAfter, property);
}

void QExtPEVariantPropertyManagerPrivate::slotPropertyRemoved(QExtPEProperty *property, QExtPEProperty *parent)
{
    Q_UNUSED(parent)

    QExtPEVariantProperty *varProperty = m_internalToProperty.value(property, QEXT_NULLPTR);
    if (!varProperty)
    {
        return;
    }

    this->removeSubProperty(varProperty);
}

void QExtPEVariantPropertyManagerPrivate::valueChanged(QExtPEProperty *property, const QVariant &val)
{
    QExtPEVariantProperty *varProp = m_internalToProperty.value(property, QEXT_NULLPTR);
    if (!varProp)
    {
        return;
    }
    emit q_ptr->valueChanged(varProp, val);
    emit q_ptr->propertyChanged(varProp);
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, int val)
{
    this->valueChanged(property, QVariant(val));
}

void QExtPEVariantPropertyManagerPrivate::slotRangeChanged(QExtPEProperty *property, int min, int max)
{
    if (QExtPEVariantProperty *varProp = m_internalToProperty.value(property, QEXT_NULLPTR))
    {
        emit q_ptr->attributeChanged(varProp, m_minimumAttribute, QVariant(min));
        emit q_ptr->attributeChanged(varProp, m_maximumAttribute, QVariant(max));
    }
}

void QExtPEVariantPropertyManagerPrivate::slotSingleStepChanged(QExtPEProperty *property, int step)
{
    if (QExtPEVariantProperty *varProp = m_internalToProperty.value(property, QEXT_NULLPTR))
    {
        emit q_ptr->attributeChanged(varProp, m_singleStepAttribute, QVariant(step));
    }
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, double val)
{
    this->valueChanged(property, QVariant(val));
}

void QExtPEVariantPropertyManagerPrivate::slotRangeChanged(QExtPEProperty *property, double min, double max)
{
    if (QExtPEVariantProperty *varProp = m_internalToProperty.value(property, QEXT_NULLPTR))
    {
        emit q_ptr->attributeChanged(varProp, m_minimumAttribute, QVariant(min));
        emit q_ptr->attributeChanged(varProp, m_maximumAttribute, QVariant(max));
    }
}

void QExtPEVariantPropertyManagerPrivate::slotSingleStepChanged(QExtPEProperty *property, double step)
{
    if (QExtPEVariantProperty *varProp = m_internalToProperty.value(property, QEXT_NULLPTR))
    {
        emit q_ptr->attributeChanged(varProp, m_singleStepAttribute, QVariant(step));
    }
}

void QExtPEVariantPropertyManagerPrivate::slotDecimalsChanged(QExtPEProperty *property, int prec)
{
    if (QExtPEVariantProperty *varProp = m_internalToProperty.value(property, QEXT_NULLPTR))
    {
        emit q_ptr->attributeChanged(varProp, m_decimalsAttribute, QVariant(prec));
    }
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, bool val)
{
    this->valueChanged(property, QVariant(val));
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, const QString &val)
{
    this->valueChanged(property, QVariant(val));
}

void QExtPEVariantPropertyManagerPrivate::slotRegExpChanged(QExtPEProperty *property, const QRegExp &regExp)
{
    if (QExtPEVariantProperty *varProp = m_internalToProperty.value(property, QEXT_NULLPTR))
    {
        emit q_ptr->attributeChanged(varProp, m_regExpAttribute, QVariant(regExp));
    }
}

void QExtPEVariantPropertyManagerPrivate::slotEchoModeChanged(QExtPEProperty *property, int mode)
{
    if (QExtPEVariantProperty *varProp = m_internalToProperty.value(property, QEXT_NULLPTR))
    {
        emit q_ptr->attributeChanged(varProp, m_echoModeAttribute, QVariant(mode));
    }
}

void QExtPEVariantPropertyManagerPrivate::slotReadOnlyChanged(QExtPEProperty *property, bool readOnly)
{
    if (QExtPEVariantProperty *varProp = m_internalToProperty.value(property, QEXT_NULLPTR))
    {
        emit q_ptr->attributeChanged(varProp, m_readOnlyAttribute, QVariant(readOnly));
    }
}

void QExtPEVariantPropertyManagerPrivate::slotTextVisibleChanged(QExtPEProperty *property, bool textVisible)
{
    if (QExtPEVariantProperty *varProp = m_internalToProperty.value(property, QEXT_NULLPTR))
    {
        emit q_ptr->attributeChanged(varProp, m_textVisibleAttribute, QVariant(textVisible));
    }
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, const QDate &val)
{
    this->valueChanged(property, QVariant(val));
}

void QExtPEVariantPropertyManagerPrivate::slotRangeChanged(QExtPEProperty *property, const QDate &min, const QDate &max)
{
    if (QExtPEVariantProperty *varProp = m_internalToProperty.value(property, QEXT_NULLPTR))
    {
        emit q_ptr->attributeChanged(varProp, m_minimumAttribute, QVariant(min));
        emit q_ptr->attributeChanged(varProp, m_maximumAttribute, QVariant(max));
    }
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, const QTime &val)
{
    this->valueChanged(property, QVariant(val));
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, const QDateTime &val)
{
    this->valueChanged(property, QVariant(val));
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, const QKeySequence &val)
{
    QVariant v;
    qVariantSetValue(v, val);
    this->valueChanged(property, v);
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, const QChar &val)
{
    this->valueChanged(property, QVariant(val));
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, const QLocale &val)
{
    this->valueChanged(property, QVariant(val));
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, const QPoint &val)
{
    this->valueChanged(property, QVariant(val));
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, const QPointF &val)
{
    this->valueChanged(property, QVariant(val));
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, const QSize &val)
{
    this->valueChanged(property, QVariant(val));
}

void QExtPEVariantPropertyManagerPrivate::slotRangeChanged(QExtPEProperty *property, const QSize &min, const QSize &max)
{
    if (QExtPEVariantProperty *varProp = m_internalToProperty.value(property, QEXT_NULLPTR))
    {
        emit q_ptr->attributeChanged(varProp, m_minimumAttribute, QVariant(min));
        emit q_ptr->attributeChanged(varProp, m_maximumAttribute, QVariant(max));
    }
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, const QSizeF &val)
{
    this->valueChanged(property, QVariant(val));
}

void QExtPEVariantPropertyManagerPrivate::slotRangeChanged(QExtPEProperty *property, const QSizeF &min, const QSizeF &max)
{
    if (QExtPEVariantProperty *varProp = m_internalToProperty.value(property, QEXT_NULLPTR))
    {
        emit q_ptr->attributeChanged(varProp, m_minimumAttribute, QVariant(min));
        emit q_ptr->attributeChanged(varProp, m_maximumAttribute, QVariant(max));
    }
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, const QRect &val)
{
    this->valueChanged(property, QVariant(val));
}

void QExtPEVariantPropertyManagerPrivate::slotConstraintChanged(QExtPEProperty *property, const QRect &constraint)
{
    if (QExtPEVariantProperty *varProp = m_internalToProperty.value(property, QEXT_NULLPTR))
    {
        emit q_ptr->attributeChanged(varProp, m_constraintAttribute, QVariant(constraint));
    }
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, const QRectF &val)
{
    this->valueChanged(property, QVariant(val));
}

void QExtPEVariantPropertyManagerPrivate::slotConstraintChanged(QExtPEProperty *property, const QRectF &constraint)
{
    if (QExtPEVariantProperty *varProp = m_internalToProperty.value(property, QEXT_NULLPTR))
    {
        emit q_ptr->attributeChanged(varProp, m_constraintAttribute, QVariant(constraint));
    }
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, const QColor &val)
{
    this->valueChanged(property, QVariant(val));
}

void QExtPEVariantPropertyManagerPrivate::slotEnumNamesChanged(QExtPEProperty *property, const QStringList &enumNames)
{
    if (QExtPEVariantProperty *varProp = m_internalToProperty.value(property, QEXT_NULLPTR))
    {
        emit q_ptr->attributeChanged(varProp, m_enumNamesAttribute, QVariant(enumNames));
    }
}

void QExtPEVariantPropertyManagerPrivate::slotEnumIconsChanged(QExtPEProperty *property, const QMap<int, QIcon> &enumIcons)
{
    if (QExtPEVariantProperty *varProp = m_internalToProperty.value(property, QEXT_NULLPTR))
    {
        QVariant v;
        qVariantSetValue(v, enumIcons);
        emit q_ptr->attributeChanged(varProp, m_enumIconsAttribute, v);
    }
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, const QSizePolicy &val)
{
    this->valueChanged(property, QVariant(val));
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, const QFont &val)
{
    this->valueChanged(property, QVariant(val));
}

void QExtPEVariantPropertyManagerPrivate::slotValueChanged(QExtPEProperty *property, const QCursor &val)
{
#ifndef QT_NO_CURSOR
    this->valueChanged(property, QVariant(val));
#endif
}

void QExtPEVariantPropertyManagerPrivate::slotFlagNamesChanged(QExtPEProperty *property, const QStringList &flagNames)
{
    if (QExtPEVariantProperty *varProp = m_internalToProperty.value(property, QEXT_NULLPTR))
    {
        emit q_ptr->attributeChanged(varProp, m_flagNamesAttribute, QVariant(flagNames));
    }
}


QExtPEVariantPropertyManager::QExtPEVariantPropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPEVariantPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_creatingProperty = false;
    d_ptr->m_creatingSubProperties = false;
    d_ptr->m_destroyingSubProperties = false;
    d_ptr->m_propertyType = 0;

    // IntPropertyManager
    QExtPEIntPropertyManager *intPropertyManager = new QExtPEIntPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Int] = intPropertyManager;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Int][d_ptr->m_minimumAttribute] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Int][d_ptr->m_maximumAttribute] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Int][d_ptr->m_singleStepAttribute] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Int][d_ptr->m_readOnlyAttribute] = QVariant::Bool;
    d_ptr->m_typeToValueType[QVariant::Int] = QVariant::Int;
    connect(intPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotValueChanged(QExtPEProperty *, int)));
    connect(intPropertyManager, SIGNAL(rangeChanged(QExtPEProperty *, int, int)),
            this, SLOT(slotRangeChanged(QExtPEProperty *, int, int)));
    connect(intPropertyManager, SIGNAL(singleStepChanged(QExtPEProperty *, int)),
            this, SLOT(slotSingleStepChanged(QExtPEProperty *, int)));
    // DoublePropertyManager
    QExtPEDoublePropertyManager *doublePropertyManager = new QExtPEDoublePropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Double] = doublePropertyManager;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Double][d_ptr->m_minimumAttribute] = QVariant::Double;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Double][d_ptr->m_maximumAttribute] = QVariant::Double;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Double][d_ptr->m_singleStepAttribute] = QVariant::Double;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Double][d_ptr->m_decimalsAttribute] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Double][d_ptr->m_readOnlyAttribute] = QVariant::Bool;
    d_ptr->m_typeToValueType[QVariant::Double] = QVariant::Double;
    connect(doublePropertyManager, SIGNAL(valueChanged(QExtPEProperty *, double)),
            this, SLOT(slotValueChanged(QExtPEProperty *, double)));
    connect(doublePropertyManager, SIGNAL(rangeChanged(QExtPEProperty *, double, double)),
            this, SLOT(slotRangeChanged(QExtPEProperty *, double, double)));
    connect(doublePropertyManager, SIGNAL(singleStepChanged(QExtPEProperty *, double)),
            this, SLOT(slotSingleStepChanged(QExtPEProperty *, double)));
    connect(doublePropertyManager, SIGNAL(decimalsChanged(QExtPEProperty *, int)),
            this, SLOT(slotDecimalsChanged(QExtPEProperty *, int)));
    // BoolPropertyManager
    QExtPEBoolPropertyManager *boolPropertyManager = new QExtPEBoolPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Bool] = boolPropertyManager;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Bool][d_ptr->m_textVisibleAttribute] = QVariant::Bool;
    d_ptr->m_typeToValueType[QVariant::Bool] = QVariant::Bool;
    connect(boolPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, bool)),
            this, SLOT(slotValueChanged(QExtPEProperty *, bool)));
    connect(boolPropertyManager, SIGNAL(textVisibleChanged(QExtPEProperty*, bool)),
            this, SLOT(slotTextVisibleChanged(QExtPEProperty*, bool)));
    // StringPropertyManager
    QExtPEStringPropertyManager *stringPropertyManager = new QExtPEStringPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::String] = stringPropertyManager;
    d_ptr->m_typeToValueType[QVariant::String] = QVariant::String;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::String][d_ptr->m_regExpAttribute] = QVariant::RegExp;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::String][d_ptr->m_echoModeAttribute] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::String][d_ptr->m_readOnlyAttribute] = QVariant::Bool;

    connect(stringPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, const QString &)),
            this, SLOT(slotValueChanged(QExtPEProperty *, const QString &)));
    connect(stringPropertyManager, SIGNAL(regExpChanged(QExtPEProperty *, const QRegExp &)),
            this, SLOT(slotRegExpChanged(QExtPEProperty *, const QRegExp &)));
    connect(stringPropertyManager, SIGNAL(echoModeChanged(QExtPEProperty*,int)),
            this, SLOT(slotEchoModeChanged(QExtPEProperty*, int)));
    connect(stringPropertyManager, SIGNAL(readOnlyChanged(QExtPEProperty*, bool)),
            this, SLOT(slotReadOnlyChanged(QExtPEProperty*, bool)));

    // DatePropertyManager
    QExtPEDatePropertyManager *datePropertyManager = new QExtPEDatePropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Date] = datePropertyManager;
    d_ptr->m_typeToValueType[QVariant::Date] = QVariant::Date;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Date][d_ptr->m_minimumAttribute] = QVariant::Date;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Date][d_ptr->m_maximumAttribute] = QVariant::Date;
    connect(datePropertyManager, SIGNAL(valueChanged(QExtPEProperty *, const QDate &)),
            this, SLOT(slotValueChanged(QExtPEProperty *, const QDate &)));
    connect(datePropertyManager, SIGNAL(rangeChanged(QExtPEProperty *, const QDate &, const QDate &)),
            this, SLOT(slotRangeChanged(QExtPEProperty *, const QDate &, const QDate &)));
    // TimePropertyManager
    QExtPETimePropertyManager *timePropertyManager = new QExtPETimePropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Time] = timePropertyManager;
    d_ptr->m_typeToValueType[QVariant::Time] = QVariant::Time;
    connect(timePropertyManager, SIGNAL(valueChanged(QExtPEProperty *, const QTime &)),
            this, SLOT(slotValueChanged(QExtPEProperty *, const QTime &)));
    // DateTimePropertyManager
    QExtPEDateTimePropertyManager *dateTimePropertyManager = new QExtPEDateTimePropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::DateTime] = dateTimePropertyManager;
    d_ptr->m_typeToValueType[QVariant::DateTime] = QVariant::DateTime;
    connect(dateTimePropertyManager, SIGNAL(valueChanged(QExtPEProperty *, const QDateTime &)),
            this, SLOT(slotValueChanged(QExtPEProperty *, const QDateTime &)));
    // KeySequencePropertyManager
    QExtPEKeySequencePropertyManager *keySequencePropertyManager = new QExtPEKeySequencePropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::KeySequence] = keySequencePropertyManager;
    d_ptr->m_typeToValueType[QVariant::KeySequence] = QVariant::KeySequence;
    connect(keySequencePropertyManager, SIGNAL(valueChanged(QExtPEProperty *, const QKeySequence &)),
            this, SLOT(slotValueChanged(QExtPEProperty *, const QKeySequence &)));
    // CharPropertyManager
    QExtPECharPropertyManager *charPropertyManager = new QExtPECharPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Char] = charPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Char] = QVariant::Char;
    connect(charPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, const QChar &)),
            this, SLOT(slotValueChanged(QExtPEProperty *, const QChar &)));
    // LocalePropertyManager
    QExtPELocalePropertyManager *localePropertyManager = new QExtPELocalePropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Locale] = localePropertyManager;
    d_ptr->m_typeToValueType[QVariant::Locale] = QVariant::Locale;
    connect(localePropertyManager, SIGNAL(valueChanged(QExtPEProperty *, const QLocale &)),
            this, SLOT(slotValueChanged(QExtPEProperty *, const QLocale &)));
    connect(localePropertyManager->subEnumPropertyManager(), SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotValueChanged(QExtPEProperty *, int)));
    connect(localePropertyManager, SIGNAL(propertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)));
    connect(localePropertyManager, SIGNAL(propertyRemoved(QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyRemoved(QExtPEProperty *, QExtPEProperty *)));
    // PointPropertyManager
    QExtPEPointPropertyManager *pointPropertyManager = new QExtPEPointPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Point] = pointPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Point] = QVariant::Point;
    connect(pointPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, const QPoint &)),
            this, SLOT(slotValueChanged(QExtPEProperty *, const QPoint &)));
    connect(pointPropertyManager->subIntPropertyManager(), SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotValueChanged(QExtPEProperty *, int)));
    connect(pointPropertyManager, SIGNAL(propertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)));
    connect(pointPropertyManager, SIGNAL(propertyRemoved(QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyRemoved(QExtPEProperty *, QExtPEProperty *)));
    // PointFPropertyManager
    QExtPEPointFPropertyManager *pointFPropertyManager = new QExtPEPointFPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::PointF] = pointFPropertyManager;
    d_ptr->m_typeToValueType[QVariant::PointF] = QVariant::PointF;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::PointF][d_ptr->m_decimalsAttribute] = QVariant::Int;
    connect(pointFPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, const QPointF &)),
            this, SLOT(slotValueChanged(QExtPEProperty *, const QPointF &)));
    connect(pointFPropertyManager, SIGNAL(decimalsChanged(QExtPEProperty *, int)),
            this, SLOT(slotDecimalsChanged(QExtPEProperty *, int)));
    connect(pointFPropertyManager->subDoublePropertyManager(), SIGNAL(valueChanged(QExtPEProperty *, double)),
            this, SLOT(slotValueChanged(QExtPEProperty *, double)));
    connect(pointFPropertyManager, SIGNAL(propertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)));
    connect(pointFPropertyManager, SIGNAL(propertyRemoved(QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyRemoved(QExtPEProperty *, QExtPEProperty *)));
    // SizePropertyManager
    QExtPESizePropertyManager *sizePropertyManager = new QExtPESizePropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Size] = sizePropertyManager;
    d_ptr->m_typeToValueType[QVariant::Size] = QVariant::Size;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Size][d_ptr->m_minimumAttribute] = QVariant::Size;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Size][d_ptr->m_maximumAttribute] = QVariant::Size;
    connect(sizePropertyManager, SIGNAL(valueChanged(QExtPEProperty *, const QSize &)),
            this, SLOT(slotValueChanged(QExtPEProperty *, const QSize &)));
    connect(sizePropertyManager, SIGNAL(rangeChanged(QExtPEProperty *, const QSize &, const QSize &)),
            this, SLOT(slotRangeChanged(QExtPEProperty *, const QSize &, const QSize &)));
    connect(sizePropertyManager->subIntPropertyManager(), SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotValueChanged(QExtPEProperty *, int)));
    connect(sizePropertyManager->subIntPropertyManager(), SIGNAL(rangeChanged(QExtPEProperty *, int, int)),
            this, SLOT(slotRangeChanged(QExtPEProperty *, int, int)));
    connect(sizePropertyManager, SIGNAL(propertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)));
    connect(sizePropertyManager, SIGNAL(propertyRemoved(QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyRemoved(QExtPEProperty *, QExtPEProperty *)));
    // SizeFPropertyManager
    QExtPESizeFPropertyManager *sizeFPropertyManager = new QExtPESizeFPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::SizeF] = sizeFPropertyManager;
    d_ptr->m_typeToValueType[QVariant::SizeF] = QVariant::SizeF;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::SizeF][d_ptr->m_minimumAttribute] = QVariant::SizeF;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::SizeF][d_ptr->m_maximumAttribute] = QVariant::SizeF;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::SizeF][d_ptr->m_decimalsAttribute] = QVariant::Int;
    connect(sizeFPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, const QSizeF &)),
            this, SLOT(slotValueChanged(QExtPEProperty *, const QSizeF &)));
    connect(sizeFPropertyManager, SIGNAL(rangeChanged(QExtPEProperty *, const QSizeF &, const QSizeF &)),
            this, SLOT(slotRangeChanged(QExtPEProperty *, const QSizeF &, const QSizeF &)));
    connect(sizeFPropertyManager, SIGNAL(decimalsChanged(QExtPEProperty *, int)),
            this, SLOT(slotDecimalsChanged(QExtPEProperty *, int)));
    connect(sizeFPropertyManager->subDoublePropertyManager(), SIGNAL(valueChanged(QExtPEProperty *, double)),
            this, SLOT(slotValueChanged(QExtPEProperty *, double)));
    connect(sizeFPropertyManager->subDoublePropertyManager(), SIGNAL(rangeChanged(QExtPEProperty *, double, double)),
            this, SLOT(slotRangeChanged(QExtPEProperty *, double, double)));
    connect(sizeFPropertyManager, SIGNAL(propertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)));
    connect(sizeFPropertyManager, SIGNAL(propertyRemoved(QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyRemoved(QExtPEProperty *, QExtPEProperty *)));
    // RectPropertyManager
    QExtPERectPropertyManager *rectPropertyManager = new QExtPERectPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Rect] = rectPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Rect] = QVariant::Rect;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Rect][d_ptr->m_constraintAttribute] = QVariant::Rect;
    connect(rectPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, const QRect &)),
            this, SLOT(slotValueChanged(QExtPEProperty *, const QRect &)));
    connect(rectPropertyManager, SIGNAL(constraintChanged(QExtPEProperty *, const QRect &)),
            this, SLOT(slotConstraintChanged(QExtPEProperty *, const QRect &)));
    connect(rectPropertyManager->subIntPropertyManager(), SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotValueChanged(QExtPEProperty *, int)));
    connect(rectPropertyManager->subIntPropertyManager(), SIGNAL(rangeChanged(QExtPEProperty *, int, int)),
            this, SLOT(slotRangeChanged(QExtPEProperty *, int, int)));
    connect(rectPropertyManager, SIGNAL(propertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)));
    connect(rectPropertyManager, SIGNAL(propertyRemoved(QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyRemoved(QExtPEProperty *, QExtPEProperty *)));
    // RectFPropertyManager
    QExtPERectFPropertyManager *rectFPropertyManager = new QExtPERectFPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::RectF] = rectFPropertyManager;
    d_ptr->m_typeToValueType[QVariant::RectF] = QVariant::RectF;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::RectF][d_ptr->m_constraintAttribute] = QVariant::RectF;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::RectF][d_ptr->m_decimalsAttribute] = QVariant::Int;
    connect(rectFPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, const QRectF &)),
            this, SLOT(slotValueChanged(QExtPEProperty *, const QRectF &)));
    connect(rectFPropertyManager, SIGNAL(constraintChanged(QExtPEProperty *, const QRectF &)),
            this, SLOT(slotConstraintChanged(QExtPEProperty *, const QRectF &)));
    connect(rectFPropertyManager, SIGNAL(decimalsChanged(QExtPEProperty *, int)),
            this, SLOT(slotDecimalsChanged(QExtPEProperty *, int)));
    connect(rectFPropertyManager->subDoublePropertyManager(), SIGNAL(valueChanged(QExtPEProperty *, double)),
            this, SLOT(slotValueChanged(QExtPEProperty *, double)));
    connect(rectFPropertyManager->subDoublePropertyManager(), SIGNAL(rangeChanged(QExtPEProperty *, double, double)),
            this, SLOT(slotRangeChanged(QExtPEProperty *, double, double)));
    connect(rectFPropertyManager, SIGNAL(propertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)));
    connect(rectFPropertyManager, SIGNAL(propertyRemoved(QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyRemoved(QExtPEProperty *, QExtPEProperty *)));
    // ColorPropertyManager
    QExtPEColorPropertyManager *colorPropertyManager = new QExtPEColorPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Color] = colorPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Color] = QVariant::Color;
    connect(colorPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, const QColor &)),
            this, SLOT(slotValueChanged(QExtPEProperty *, const QColor &)));
    connect(colorPropertyManager->subIntPropertyManager(), SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotValueChanged(QExtPEProperty *, int)));
    connect(colorPropertyManager, SIGNAL(propertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)));
    connect(colorPropertyManager, SIGNAL(propertyRemoved(QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyRemoved(QExtPEProperty *, QExtPEProperty *)));
    // EnumPropertyManager
    int enumId = enumTypeId();
    QExtPEEnumPropertyManager *enumPropertyManager = new QExtPEEnumPropertyManager(this);
    d_ptr->m_typeToPropertyManager[enumId] = enumPropertyManager;
    d_ptr->m_typeToValueType[enumId] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[enumId][d_ptr->m_enumNamesAttribute] = QVariant::StringList;
    d_ptr->m_typeToAttributeToAttributeType[enumId][d_ptr->m_enumIconsAttribute] = iconMapTypeId();
    connect(enumPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotValueChanged(QExtPEProperty *, int)));
    connect(enumPropertyManager, SIGNAL(enumNamesChanged(QExtPEProperty *, const QStringList &)),
            this, SLOT(slotEnumNamesChanged(QExtPEProperty *, const QStringList &)));
    connect(enumPropertyManager, SIGNAL(enumIconsChanged(QExtPEProperty *, const QMap<int, QIcon> &)),
            this, SLOT(slotEnumIconsChanged(QExtPEProperty *, const QMap<int, QIcon> &)));
    // SizePolicyPropertyManager
    QExtPESizePolicyPropertyManager *sizePolicyPropertyManager = new QExtPESizePolicyPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::SizePolicy] = sizePolicyPropertyManager;
    d_ptr->m_typeToValueType[QVariant::SizePolicy] = QVariant::SizePolicy;
    connect(sizePolicyPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, const QSizePolicy &)),
            this, SLOT(slotValueChanged(QExtPEProperty *, const QSizePolicy &)));
    connect(sizePolicyPropertyManager->subIntPropertyManager(), SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotValueChanged(QExtPEProperty *, int)));
    connect(sizePolicyPropertyManager->subIntPropertyManager(), SIGNAL(rangeChanged(QExtPEProperty *, int, int)),
            this, SLOT(slotRangeChanged(QExtPEProperty *, int, int)));
    connect(sizePolicyPropertyManager->subEnumPropertyManager(), SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotValueChanged(QExtPEProperty *, int)));
    connect(sizePolicyPropertyManager->subEnumPropertyManager(),
            SIGNAL(enumNamesChanged(QExtPEProperty *, const QStringList &)),
            this, SLOT(slotEnumNamesChanged(QExtPEProperty *, const QStringList &)));
    connect(sizePolicyPropertyManager, SIGNAL(propertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)));
    connect(sizePolicyPropertyManager, SIGNAL(propertyRemoved(QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyRemoved(QExtPEProperty *, QExtPEProperty *)));
    // FontPropertyManager
    QExtPEFontPropertyManager *fontPropertyManager = new QExtPEFontPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Font] = fontPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Font] = QVariant::Font;
    connect(fontPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, const QFont &)),
            this, SLOT(slotValueChanged(QExtPEProperty *, const QFont &)));
    connect(fontPropertyManager->subIntPropertyManager(), SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotValueChanged(QExtPEProperty *, int)));
    connect(fontPropertyManager->subIntPropertyManager(), SIGNAL(rangeChanged(QExtPEProperty *, int, int)),
            this, SLOT(slotRangeChanged(QExtPEProperty *, int, int)));
    connect(fontPropertyManager->subEnumPropertyManager(), SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotValueChanged(QExtPEProperty *, int)));
    connect(fontPropertyManager->subEnumPropertyManager(),
            SIGNAL(enumNamesChanged(QExtPEProperty *, const QStringList &)),
            this, SLOT(slotEnumNamesChanged(QExtPEProperty *, const QStringList &)));
    connect(fontPropertyManager->subBoolPropertyManager(), SIGNAL(valueChanged(QExtPEProperty *, bool)),
            this, SLOT(slotValueChanged(QExtPEProperty *, bool)));
    connect(fontPropertyManager, SIGNAL(propertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)));
    connect(fontPropertyManager, SIGNAL(propertyRemoved(QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyRemoved(QExtPEProperty *, QExtPEProperty *)));
    // CursorPropertyManager
    QExtPECursorPropertyManager *cursorPropertyManager = new QExtPECursorPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Cursor] = cursorPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Cursor] = QVariant::Cursor;
    connect(cursorPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, const QCursor &)),
            this, SLOT(slotValueChanged(QExtPEProperty *, const QCursor &)));
    // FlagPropertyManager
    int flagId = flagTypeId();
    QExtPEFlagPropertyManager *flagPropertyManager = new QExtPEFlagPropertyManager(this);
    d_ptr->m_typeToPropertyManager[flagId] = flagPropertyManager;
    d_ptr->m_typeToValueType[flagId] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[flagId][d_ptr->m_flagNamesAttribute] = QVariant::StringList;
    connect(flagPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotValueChanged(QExtPEProperty *, int)));
    connect(flagPropertyManager, SIGNAL(flagNamesChanged(QExtPEProperty *, const QStringList &)),
            this, SLOT(slotFlagNamesChanged(QExtPEProperty *, const QStringList &)));
    connect(flagPropertyManager->subBoolPropertyManager(), SIGNAL(valueChanged(QExtPEProperty *, bool)),
            this, SLOT(slotValueChanged(QExtPEProperty *, bool)));
    connect(flagPropertyManager, SIGNAL(propertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyInserted(QExtPEProperty *, QExtPEProperty *, QExtPEProperty *)));
    connect(flagPropertyManager, SIGNAL(propertyRemoved(QExtPEProperty *, QExtPEProperty *)),
            this, SLOT(slotPropertyRemoved(QExtPEProperty *, QExtPEProperty *)));
    // FlagPropertyManager
    int groupId = groupTypeId();
    QExtPEGroupPropertyManager *groupPropertyManager = new QExtPEGroupPropertyManager(this);
    d_ptr->m_typeToPropertyManager[groupId] = groupPropertyManager;
    d_ptr->m_typeToValueType[groupId] = QVariant::Invalid;
}

QExtPEVariantPropertyManager::~QExtPEVariantPropertyManager()
{
    this->clear();
    delete d_ptr;
}

QExtPEVariantProperty *QExtPEVariantPropertyManager::variantProperty(const QExtPEProperty *property) const
{
    const QMap<const QExtPEProperty *, QPair<QExtPEVariantProperty *, int> >::const_iterator it
        = d_ptr->m_propertyToType.constFind(property);
    if (it == d_ptr->m_propertyToType.constEnd())
    {
        return QEXT_NULLPTR;
    }
    return it.value().first;
}

bool QExtPEVariantPropertyManager::isPropertyTypeSupported(int propertyType) const
{
    if (d_ptr->m_typeToValueType.contains(propertyType))
    {
        return true;
    }
    return false;
}

QExtPEVariantProperty *QExtPEVariantPropertyManager::addProperty(int propertyType, const QString &name)
{
    if (!isPropertyTypeSupported(propertyType))
    {
        return QEXT_NULLPTR;
    }

    bool wasCreating = d_ptr->m_creatingProperty;
    d_ptr->m_creatingProperty = true;
    d_ptr->m_propertyType = propertyType;
    QExtPEProperty *property = QExtPEAbstractPropertyManager::addProperty(name);
    d_ptr->m_creatingProperty = wasCreating;
    d_ptr->m_propertyType = 0;

    if (!property)
    {
        return QEXT_NULLPTR;
    }

    return variantProperty(property);
}

QVariant QExtPEVariantPropertyManager::value(const QExtPEProperty *property) const
{
    QExtPEProperty *internProp = propertyToWrappedProperty()->value(property, QEXT_NULLPTR);
    if (internProp == QEXT_NULLPTR)
    {
        return QVariant();
    }

    QExtPEAbstractPropertyManager *manager = internProp->propertyManager();
    if (QExtPEIntPropertyManager *intManager = qobject_cast<QExtPEIntPropertyManager *>(manager))
    {
        return intManager->value(internProp);
    }
    else if (QExtPEDoublePropertyManager *doubleManager = qobject_cast<QExtPEDoublePropertyManager *>(manager))
    {
        return doubleManager->value(internProp);
    }
    else if (QExtPEBoolPropertyManager *boolManager = qobject_cast<QExtPEBoolPropertyManager *>(manager))
    {
        return boolManager->value(internProp);
    }
    else if (QExtPEStringPropertyManager *stringManager = qobject_cast<QExtPEStringPropertyManager *>(manager))
    {
        return stringManager->value(internProp);
    }
    else if (QExtPEDatePropertyManager *dateManager = qobject_cast<QExtPEDatePropertyManager *>(manager))
    {
        return dateManager->value(internProp);
    }
    else if (QExtPETimePropertyManager *timeManager = qobject_cast<QExtPETimePropertyManager *>(manager))
    {
        return timeManager->value(internProp);
    }
    else if (QExtPEDateTimePropertyManager *dateTimeManager = qobject_cast<QExtPEDateTimePropertyManager *>(manager))
    {
        return dateTimeManager->value(internProp);
    }
    else if (QExtPEKeySequencePropertyManager *keySequenceManager = qobject_cast<QExtPEKeySequencePropertyManager *>(manager))
    {
#if QT_VERSION < 0x050000
        return keySequenceManager->value(internProp);
#else
        return QVariant::fromValue(keySequenceManager->value(internProp));
#endif
    }
    else if (QExtPECharPropertyManager *charManager = qobject_cast<QExtPECharPropertyManager *>(manager))
    {
        return charManager->value(internProp);
    }
    else if (QExtPELocalePropertyManager *localeManager = qobject_cast<QExtPELocalePropertyManager *>(manager))
    {
        return localeManager->value(internProp);
    }
    else if (QExtPEPointPropertyManager *pointManager = qobject_cast<QExtPEPointPropertyManager *>(manager))
    {
        return pointManager->value(internProp);
    }
    else if (QExtPEPointFPropertyManager *pointFManager = qobject_cast<QExtPEPointFPropertyManager *>(manager))
    {
        return pointFManager->value(internProp);
    }
    else if (QExtPESizePropertyManager *sizeManager = qobject_cast<QExtPESizePropertyManager *>(manager))
    {
        return sizeManager->value(internProp);
    }
    else if (QExtPESizeFPropertyManager *sizeFManager = qobject_cast<QExtPESizeFPropertyManager *>(manager))
    {
        return sizeFManager->value(internProp);
    }
    else if (QExtPERectPropertyManager *rectManager = qobject_cast<QExtPERectPropertyManager *>(manager))
    {
        return rectManager->value(internProp);
    }
    else if (QExtPERectFPropertyManager *rectFManager = qobject_cast<QExtPERectFPropertyManager *>(manager))
    {
        return rectFManager->value(internProp);
    }
    else if (QExtPEColorPropertyManager *colorManager = qobject_cast<QExtPEColorPropertyManager *>(manager))
    {
        return colorManager->value(internProp);
    }
    else if (QExtPEEnumPropertyManager *enumManager = qobject_cast<QExtPEEnumPropertyManager *>(manager))
    {
        return enumManager->value(internProp);
    }
    else if (QExtPESizePolicyPropertyManager *sizePolicyManager = qobject_cast<QExtPESizePolicyPropertyManager *>(manager))
    {
        return sizePolicyManager->value(internProp);
    }
    else if (QExtPEFontPropertyManager *fontManager = qobject_cast<QExtPEFontPropertyManager *>(manager))
    {
        return fontManager->value(internProp);
#ifndef QT_NO_CURSOR
    }
    else if (QExtPECursorPropertyManager *cursorManager = qobject_cast<QExtPECursorPropertyManager *>(manager))
    {
        return cursorManager->value(internProp);
#endif
    }
    else if (QExtPEFlagPropertyManager *flagManager = qobject_cast<QExtPEFlagPropertyManager *>(manager))
    {
        return flagManager->value(internProp);
    }
    return QVariant();
}

int QExtPEVariantPropertyManager::valueType(const QExtPEProperty *property) const
{
    int propType = propertyType(property);
    return this->valueType(propType);
}

int QExtPEVariantPropertyManager::valueType(int propertyType) const
{
    if (d_ptr->m_typeToValueType.contains(propertyType))
    {
        return d_ptr->m_typeToValueType[propertyType];
    }
    return 0;
}

int QExtPEVariantPropertyManager::propertyType(const QExtPEProperty *property) const
{
    const QMap<const QExtPEProperty *, QPair<QExtPEVariantProperty *, int> >::const_iterator it =
        d_ptr->m_propertyToType.constFind(property);
    if (it == d_ptr->m_propertyToType.constEnd())
    {
        return 0;
    }
    return it.value().second;
}

QVariant QExtPEVariantPropertyManager::attributeValue(const QExtPEProperty *property, const QString &attribute) const
{
    int propType = propertyType(property);
    if (!propType)
    {
        return QVariant();
    }

    QMap<int, QMap<QString, int> >::ConstIterator it = d_ptr->m_typeToAttributeToAttributeType.find(propType);
    if (it == d_ptr->m_typeToAttributeToAttributeType.constEnd())
    {
        return QVariant();
    }

    QMap<QString, int> attributes = it.value();
    QMap<QString, int>::ConstIterator itAttr = attributes.find(attribute);
    if (itAttr == attributes.constEnd())
    {
        return QVariant();
    }

    QExtPEProperty *internProp = propertyToWrappedProperty()->value(property, QEXT_NULLPTR);
    if (internProp == QEXT_NULLPTR)
    {
        return QVariant();
    }

    QExtPEAbstractPropertyManager *manager = internProp->propertyManager();
    if (QExtPEIntPropertyManager *intManager = qobject_cast<QExtPEIntPropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_maximumAttribute)
        {
            return intManager->maximum(internProp);
        }
        if (attribute == d_ptr->m_minimumAttribute)
        {
            return intManager->minimum(internProp);
        }
        if (attribute == d_ptr->m_singleStepAttribute)
        {
            return intManager->singleStep(internProp);
        }
        if (attribute == d_ptr->m_readOnlyAttribute)
        {
            return intManager->isReadOnly(internProp);
        }
        return QVariant();
    }
    else if (QExtPEDoublePropertyManager *doubleManager = qobject_cast<QExtPEDoublePropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_maximumAttribute)
        {
            return doubleManager->maximum(internProp);
        }
        if (attribute == d_ptr->m_minimumAttribute)
        {
            return doubleManager->minimum(internProp);
        }
        if (attribute == d_ptr->m_singleStepAttribute)
        {
            return doubleManager->singleStep(internProp);
        }
        if (attribute == d_ptr->m_decimalsAttribute)
        {
            return doubleManager->decimals(internProp);
        }
        if (attribute == d_ptr->m_readOnlyAttribute)
        {
            return doubleManager->isReadOnly(internProp);
        }
        return QVariant();
    }
    else if (QExtPEBoolPropertyManager *boolManager = qobject_cast<QExtPEBoolPropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_textVisibleAttribute)
        {
            return boolManager->textVisible(internProp);
        }
        return QVariant();
    }
    else if (QExtPEStringPropertyManager *stringManager = qobject_cast<QExtPEStringPropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_regExpAttribute)
        {
            return stringManager->regExp(internProp);
        }
        if (attribute == d_ptr->m_echoModeAttribute)
        {
            return stringManager->echoMode(internProp);
        }
        if (attribute == d_ptr->m_readOnlyAttribute)
        {
            return stringManager->isReadOnly(internProp);
        }
        return QVariant();
    }
    else if (QExtPEDatePropertyManager *dateManager = qobject_cast<QExtPEDatePropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_maximumAttribute)
        {
            return dateManager->maximum(internProp);
        }
        if (attribute == d_ptr->m_minimumAttribute)
        {
            return dateManager->minimum(internProp);
        }
        return QVariant();
    }
    else if (QExtPEPointFPropertyManager *pointFManager = qobject_cast<QExtPEPointFPropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_decimalsAttribute)
        {
            return pointFManager->decimals(internProp);
        }
        return QVariant();
    }
    else if (QExtPESizePropertyManager *sizeManager = qobject_cast<QExtPESizePropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_maximumAttribute)
        {
            return sizeManager->maximum(internProp);
        }
        if (attribute == d_ptr->m_minimumAttribute)
        {
            return sizeManager->minimum(internProp);
        }
        return QVariant();
    }
    else if (QExtPESizeFPropertyManager *sizeFManager = qobject_cast<QExtPESizeFPropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_maximumAttribute)
        {
            return sizeFManager->maximum(internProp);
        }
        if (attribute == d_ptr->m_minimumAttribute)
        {
            return sizeFManager->minimum(internProp);
        }
        if (attribute == d_ptr->m_decimalsAttribute)
        {
            return sizeFManager->decimals(internProp);
        }
        return QVariant();
    }
    else if (QExtPERectPropertyManager *rectManager = qobject_cast<QExtPERectPropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_constraintAttribute)
        {
            return rectManager->constraint(internProp);
        }
        return QVariant();
    }
    else if (QExtPERectFPropertyManager *rectFManager = qobject_cast<QExtPERectFPropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_constraintAttribute)
        {
            return rectFManager->constraint(internProp);
        }
        if (attribute == d_ptr->m_decimalsAttribute)
        {
            return rectFManager->decimals(internProp);
        }
        return QVariant();
    }
    else if (QExtPEEnumPropertyManager *enumManager = qobject_cast<QExtPEEnumPropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_enumNamesAttribute)
        {
            return enumManager->enumNames(internProp);
        }
        if (attribute == d_ptr->m_enumIconsAttribute)
        {
            QVariant v;
            qVariantSetValue(v, enumManager->enumIcons(internProp));
            return v;
        }
        return QVariant();
    }
    else if (QExtPEFlagPropertyManager *flagManager = qobject_cast<QExtPEFlagPropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_flagNamesAttribute)
        {
            return flagManager->flagNames(internProp);
        }
        return QVariant();
    }
    return QVariant();
}

QStringList QExtPEVariantPropertyManager::attributes(int propertyType) const
{
    QMap<int, QMap<QString, int> >::ConstIterator it = d_ptr->m_typeToAttributeToAttributeType.find(propertyType);
    if (it == d_ptr->m_typeToAttributeToAttributeType.constEnd())
    {
        return QStringList();
    }
    return it.value().keys();
}

int QExtPEVariantPropertyManager::attributeType(int propertyType, const QString &attribute) const
{
    QMap<int, QMap<QString, int> >::ConstIterator it = d_ptr->m_typeToAttributeToAttributeType.find(propertyType);
    if (it == d_ptr->m_typeToAttributeToAttributeType.constEnd())
    {
        return 0;
    }

    QMap<QString, int> attributes = it.value();
    QMap<QString, int>::ConstIterator itAttr = attributes.find(attribute);
    if (itAttr == attributes.constEnd())
    {
        return 0;
    }
    return itAttr.value();
}

void QExtPEVariantPropertyManager::setValue(QExtPEProperty *property, const QVariant &val)
{
    int propType = val.userType();
    if (!propType)
    {
        return;
    }

    int valType = this->valueType(property);
    if (propType != valType && !val.canConvert(static_cast<QVariant::Type>(valType)))
    {
        return;
    }

    QExtPEProperty *internProp = propertyToWrappedProperty()->value(property, QEXT_NULLPTR);
    if (!internProp)
    {
        return;
    }

    QExtPEAbstractPropertyManager *manager = internProp->propertyManager();
    if (QExtPEIntPropertyManager *intManager = qobject_cast<QExtPEIntPropertyManager *>(manager))
    {
        intManager->setValue(internProp, qextVariantValue<int>(val));
        return;
    }
    else if (QExtPEDoublePropertyManager *doubleManager = qobject_cast<QExtPEDoublePropertyManager *>(manager))
    {
        doubleManager->setValue(internProp, qextVariantValue<double>(val));
        return;
    }
    else if (QExtPEBoolPropertyManager *boolManager = qobject_cast<QExtPEBoolPropertyManager *>(manager))
    {
        boolManager->setValue(internProp, qextVariantValue<bool>(val));
        return;
    }
    else if (QExtPEStringPropertyManager *stringManager = qobject_cast<QExtPEStringPropertyManager *>(manager))
    {
        stringManager->setValue(internProp, qextVariantValue<QString>(val));
        return;
    }
    else if (QExtPEDatePropertyManager *dateManager = qobject_cast<QExtPEDatePropertyManager *>(manager))
    {
        dateManager->setValue(internProp, qextVariantValue<QDate>(val));
        return;
    }
    else if (QExtPETimePropertyManager *timeManager = qobject_cast<QExtPETimePropertyManager *>(manager))
    {
        timeManager->setValue(internProp, qextVariantValue<QTime>(val));
        return;
    }
    else if (QExtPEDateTimePropertyManager *dateTimeManager = qobject_cast<QExtPEDateTimePropertyManager *>(manager))
    {
        dateTimeManager->setValue(internProp, qextVariantValue<QDateTime>(val));
        return;
    }
    else if (QExtPEKeySequencePropertyManager *keySequenceManager = qobject_cast<QExtPEKeySequencePropertyManager *>(manager))
    {
        keySequenceManager->setValue(internProp, qextVariantValue<QKeySequence>(val));
        return;
    }
    else if (QExtPECharPropertyManager *charManager = qobject_cast<QExtPECharPropertyManager *>(manager))
    {
        charManager->setValue(internProp, qextVariantValue<QChar>(val));
        return;
    }
    else if (QExtPELocalePropertyManager *localeManager = qobject_cast<QExtPELocalePropertyManager *>(manager))
    {
        localeManager->setValue(internProp, qextVariantValue<QLocale>(val));
        return;
    }
    else if (QExtPEPointPropertyManager *pointManager = qobject_cast<QExtPEPointPropertyManager *>(manager))
    {
        pointManager->setValue(internProp, qextVariantValue<QPoint>(val));
        return;
    }
    else if (QExtPEPointFPropertyManager *pointFManager = qobject_cast<QExtPEPointFPropertyManager *>(manager))
    {
        pointFManager->setValue(internProp, qextVariantValue<QPointF>(val));
        return;
    }
    else if (QExtPESizePropertyManager *sizeManager = qobject_cast<QExtPESizePropertyManager *>(manager))
    {
        sizeManager->setValue(internProp, qextVariantValue<QSize>(val));
        return;
    }
    else if (QExtPESizeFPropertyManager *sizeFManager = qobject_cast<QExtPESizeFPropertyManager *>(manager))
    {
        sizeFManager->setValue(internProp, qextVariantValue<QSizeF>(val));
        return;
    }
    else if (QExtPERectPropertyManager *rectManager = qobject_cast<QExtPERectPropertyManager *>(manager))
    {
        rectManager->setValue(internProp, qextVariantValue<QRect>(val));
        return;
    }
    else if (QExtPERectFPropertyManager *rectFManager = qobject_cast<QExtPERectFPropertyManager *>(manager))
    {
        rectFManager->setValue(internProp, qextVariantValue<QRectF>(val));
        return;
    }
    else if (QExtPEColorPropertyManager *colorManager = qobject_cast<QExtPEColorPropertyManager *>(manager))
    {
        colorManager->setValue(internProp, qextVariantValue<QColor>(val));
        return;
    }
    else if (QExtPEEnumPropertyManager *enumManager = qobject_cast<QExtPEEnumPropertyManager *>(manager))
    {
        enumManager->setValue(internProp, qextVariantValue<int>(val));
        return;
    }
    else if (QExtPESizePolicyPropertyManager *sizePolicyManager = qobject_cast<QExtPESizePolicyPropertyManager *>(manager))
    {
        sizePolicyManager->setValue(internProp, qextVariantValue<QSizePolicy>(val));
        return;
    }
    else if (QExtPEFontPropertyManager *fontManager = qobject_cast<QExtPEFontPropertyManager *>(manager))
    {
        fontManager->setValue(internProp, qextVariantValue<QFont>(val));
        return;
#ifndef QT_NO_CURSOR
    }
    else if (QExtPECursorPropertyManager *cursorManager = qobject_cast<QExtPECursorPropertyManager *>(manager))
    {
        cursorManager->setValue(internProp, qextVariantValue<QCursor>(val));
        return;
#endif
    }
    else if (QExtPEFlagPropertyManager *flagManager = qobject_cast<QExtPEFlagPropertyManager *>(manager))
    {
        flagManager->setValue(internProp, qextVariantValue<int>(val));
        return;
    }
}

void QExtPEVariantPropertyManager::setAttribute(QExtPEProperty *property, const QString &attribute, const QVariant &value)
{
    QVariant oldAttr = attributeValue(property, attribute);
    if (!oldAttr.isValid())
    {
        return;
    }

    int attrType = value.userType();
    if (!attrType)
    {
        return;
    }

    if (attrType != attributeType(propertyType(property), attribute) && !value.canConvert((QVariant::Type)attrType))
    {
        return;
    }

    QExtPEProperty *internProp = propertyToWrappedProperty()->value(property, QEXT_NULLPTR);
    if (internProp == QEXT_NULLPTR)
    {
        return;
    }

    QExtPEAbstractPropertyManager *manager = internProp->propertyManager();
    if (QExtPEIntPropertyManager *intManager = qobject_cast<QExtPEIntPropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_maximumAttribute)
        {
            intManager->setMaximum(internProp, qextVariantValue<int>(value));
        }
        else if (attribute == d_ptr->m_minimumAttribute)
        {
            intManager->setMinimum(internProp, qextVariantValue<int>(value));
        }
        else if (attribute == d_ptr->m_singleStepAttribute)
        {
            intManager->setSingleStep(internProp, qextVariantValue<int>(value));
        }
        else if (attribute == d_ptr->m_readOnlyAttribute)
        {
            intManager->setReadOnly(internProp, qextVariantValue<bool>(value));
        }
        return;
    }
    else if (QExtPEDoublePropertyManager *doubleManager = qobject_cast<QExtPEDoublePropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_maximumAttribute)
        {
            doubleManager->setMaximum(internProp, qextVariantValue<double>(value));
        }
        if (attribute == d_ptr->m_minimumAttribute)
        {
            doubleManager->setMinimum(internProp, qextVariantValue<double>(value));
        }
        if (attribute == d_ptr->m_singleStepAttribute)
        {
            doubleManager->setSingleStep(internProp, qextVariantValue<double>(value));
        }
        if (attribute == d_ptr->m_decimalsAttribute)
        {
            doubleManager->setDecimals(internProp, qextVariantValue<int>(value));
        }
        if (attribute == d_ptr->m_readOnlyAttribute)
        {
            doubleManager->setReadOnly(internProp, qextVariantValue<bool>(value));
        }
        return;
    }
    else if (QExtPEBoolPropertyManager *boolManager = qobject_cast<QExtPEBoolPropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_textVisibleAttribute)
        {
            boolManager->setTextVisible(internProp, qextVariantValue<bool>(value));
        }
        return;
    }
    else if (QExtPEStringPropertyManager *stringManager = qobject_cast<QExtPEStringPropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_regExpAttribute)
        {
            stringManager->setRegExp(internProp, qextVariantValue<QExtRegExp>(value));
        }
        if (attribute == d_ptr->m_echoModeAttribute)
        {
            stringManager->setEchoMode(internProp, (EchoMode)qextVariantValue<int>(value));
        }
        if (attribute == d_ptr->m_readOnlyAttribute)
        {
            stringManager->setReadOnly(internProp, (EchoMode)qextVariantValue<bool>(value));
        }
        return;
    }
    else if (QExtPEDatePropertyManager *dateManager = qobject_cast<QExtPEDatePropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_maximumAttribute)
        {
            dateManager->setMaximum(internProp, qextVariantValue<QDate>(value));
        }
        if (attribute == d_ptr->m_minimumAttribute)
        {
            dateManager->setMinimum(internProp, qextVariantValue<QDate>(value));
        }
        return;
    }
    else if (QExtPEPointFPropertyManager *pointFManager = qobject_cast<QExtPEPointFPropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_decimalsAttribute)
        {
            pointFManager->setDecimals(internProp, qextVariantValue<int>(value));
        }
        return;
    }
    else if (QExtPESizePropertyManager *sizeManager = qobject_cast<QExtPESizePropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_maximumAttribute)
        {
            sizeManager->setMaximum(internProp, qextVariantValue<QSize>(value));
        }
        if (attribute == d_ptr->m_minimumAttribute)
        {
            sizeManager->setMinimum(internProp, qextVariantValue<QSize>(value));
        }
        return;
    }
    else if (QExtPESizeFPropertyManager *sizeFManager = qobject_cast<QExtPESizeFPropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_maximumAttribute)
        {
            sizeFManager->setMaximum(internProp, qextVariantValue<QSizeF>(value));
        }
        if (attribute == d_ptr->m_minimumAttribute)
        {
            sizeFManager->setMinimum(internProp, qextVariantValue<QSizeF>(value));
        }
        if (attribute == d_ptr->m_decimalsAttribute)
        {
            sizeFManager->setDecimals(internProp, qextVariantValue<int>(value));
        }
        return;
    }
    else if (QExtPERectPropertyManager *rectManager = qobject_cast<QExtPERectPropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_constraintAttribute)
        {
            rectManager->setConstraint(internProp, qextVariantValue<QRect>(value));
        }
        return;
    }
    else if (QExtPERectFPropertyManager *rectFManager = qobject_cast<QExtPERectFPropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_constraintAttribute)
        {
            rectFManager->setConstraint(internProp, qextVariantValue<QRectF>(value));
        }
        if (attribute == d_ptr->m_decimalsAttribute)
        {
            rectFManager->setDecimals(internProp, qextVariantValue<int>(value));
        }
        return;
    }
    else if (QExtPEEnumPropertyManager *enumManager = qobject_cast<QExtPEEnumPropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_enumNamesAttribute)
        {
            enumManager->setEnumNames(internProp, qextVariantValue<QStringList>(value));
        }
        if (attribute == d_ptr->m_enumIconsAttribute)
        {
            enumManager->setEnumIcons(internProp, qextVariantValue<QExtPEIconMap>(value));
        }
        return;
    }
    else if (QExtPEFlagPropertyManager *flagManager = qobject_cast<QExtPEFlagPropertyManager *>(manager))
    {
        if (attribute == d_ptr->m_flagNamesAttribute)
        {
            flagManager->setFlagNames(internProp, qextVariantValue<QStringList>(value));
        }
        return;
    }
}

bool QExtPEVariantPropertyManager::hasValue(const QExtPEProperty *property) const
{
    if (this->propertyType(property) == this->groupTypeId())
    {
        return false;
    }
    return true;
}

QString QExtPEVariantPropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPEProperty *internProp = propertyToWrappedProperty()->value(property, QEXT_NULLPTR);
    return internProp ? !internProp->displayText().isEmpty() ? internProp->displayText() : internProp->valueText() : QString();
}

QIcon QExtPEVariantPropertyManager::valueIcon(const QExtPEProperty *property) const
{
    QIcon icon;
    QExtPEProperty *internProp = propertyToWrappedProperty()->value(property, QEXT_NULLPTR);
    if (internProp)
    {
        bool styleChanged = internProp->isStyleChanged();
        internProp->setStyleChanged(property->isStyleChanged());
        icon = internProp->valueIcon();
        internProp->setStyleChanged(styleChanged);
    }
    return icon;
}

void QExtPEVariantPropertyManager::initializeProperty(QExtPEProperty *property)
{
    QExtPEVariantProperty *varProp = this->variantProperty(property);
    if (!varProp)
    {
        return;
    }

    QMap<int, QExtPEAbstractPropertyManager *>::ConstIterator it = d_ptr->m_typeToPropertyManager.find(d_ptr->m_propertyType);
    if (it != d_ptr->m_typeToPropertyManager.constEnd())
    {
        QExtPEProperty *internProp = QEXT_NULLPTR;
        if (!d_ptr->m_creatingSubProperties)
        {
            QExtPEAbstractPropertyManager *manager = it.value();
            internProp = manager->addProperty();
            d_ptr->m_internalToProperty[internProp] = varProp;
        }
        propertyToWrappedProperty()->insert(varProp, internProp);
        if (internProp)
        {
            QList<QExtPEProperty *> children = internProp->subProperties();
            QListIterator<QExtPEProperty *> itChild(children);
            QExtPEVariantProperty *lastProperty = QEXT_NULLPTR;
            while (itChild.hasNext())
            {
                QExtPEVariantProperty *prop = d_ptr->createSubProperty(varProp, lastProperty, itChild.next());
                lastProperty = prop ? prop : lastProperty;
            }
        }
    }
}

void QExtPEVariantPropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    const QMap<const QExtPEProperty *, QPair<QExtPEVariantProperty *, int> >::iterator type_it = d_ptr->m_propertyToType.find(property);
    if (type_it == d_ptr->m_propertyToType.end())
    {
        return;
    }

    PropertyMap::iterator it = propertyToWrappedProperty()->find(property);
    if (it != propertyToWrappedProperty()->end())
    {
        QExtPEProperty *internProp = it.value();
        if (internProp)
        {
            d_ptr->m_internalToProperty.remove(internProp);
            if (!d_ptr->m_destroyingSubProperties)
            {
                delete internProp;
            }
        }
        propertyToWrappedProperty()->erase(it);
    }
    d_ptr->m_propertyToType.erase(type_it);
}

QExtPEProperty *QExtPEVariantPropertyManager::createProperty()
{
    if (!d_ptr->m_creatingProperty)
    {
        return QEXT_NULLPTR;
    }

    QExtPEVariantProperty *property = new QExtPEVariantProperty(this);
    d_ptr->m_propertyToType.insert(property, qMakePair(property, d_ptr->m_propertyType));

    return property;
}



/***********************************************************************************************************************
** QExtPEVariantEditorFactory
***********************************************************************************************************************/

QExtPEVariantEditorFactory::QExtPEVariantEditorFactory(QObject *parent)
    : QExtPEAbstractWidgetFactory<QExtPEVariantPropertyManager>(parent)
{
    d_ptr = new QExtPEVariantEditorFactoryPrivate();
    d_ptr->q_ptr = this;

    d_ptr->m_spinBoxFactory = new QExtPESpinBoxFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_spinBoxFactory] = QVariant::Int;
    d_ptr->m_typeToFactory[QVariant::Int] = d_ptr->m_spinBoxFactory;

    d_ptr->m_doubleSpinBoxFactory = new QExtPEDoubleSpinBoxFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_doubleSpinBoxFactory] = QVariant::Double;
    d_ptr->m_typeToFactory[QVariant::Double] = d_ptr->m_doubleSpinBoxFactory;

    d_ptr->m_checkBoxFactory = new QExtPECheckBoxFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_checkBoxFactory] = QVariant::Bool;
    d_ptr->m_typeToFactory[QVariant::Bool] = d_ptr->m_checkBoxFactory;

    d_ptr->m_lineEditFactory = new QExtPELineEditFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_lineEditFactory] = QVariant::String;
    d_ptr->m_typeToFactory[QVariant::String] = d_ptr->m_lineEditFactory;

    d_ptr->m_dateEditFactory = new QExtPEDateEditFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_dateEditFactory] = QVariant::Date;
    d_ptr->m_typeToFactory[QVariant::Date] = d_ptr->m_dateEditFactory;

    d_ptr->m_timeEditFactory = new QExtPETimeEditFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_timeEditFactory] = QVariant::Time;
    d_ptr->m_typeToFactory[QVariant::Time] = d_ptr->m_timeEditFactory;

    d_ptr->m_dateTimeEditFactory = new QExtPEDateTimeEditFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_dateTimeEditFactory] = QVariant::DateTime;
    d_ptr->m_typeToFactory[QVariant::DateTime] = d_ptr->m_dateTimeEditFactory;

    d_ptr->m_keySequenceEditorFactory = new QExtPEKeySequenceEditorFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_keySequenceEditorFactory] = QVariant::KeySequence;
    d_ptr->m_typeToFactory[QVariant::KeySequence] = d_ptr->m_keySequenceEditorFactory;

    d_ptr->m_charEditorFactory = new QExtPECharEditorFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_charEditorFactory] = QVariant::Char;
    d_ptr->m_typeToFactory[QVariant::Char] = d_ptr->m_charEditorFactory;

    d_ptr->m_cursorEditorFactory = new QExtPECursorEditorFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_cursorEditorFactory] = QVariant::Cursor;
    d_ptr->m_typeToFactory[QVariant::Cursor] = d_ptr->m_cursorEditorFactory;

    d_ptr->m_colorEditorFactory = new QExtPEColorEditorFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_colorEditorFactory] = QVariant::Color;
    d_ptr->m_typeToFactory[QVariant::Color] = d_ptr->m_colorEditorFactory;

    d_ptr->m_fontEditorFactory = new QExtPEFontEditorFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_fontEditorFactory] = QVariant::Font;
    d_ptr->m_typeToFactory[QVariant::Font] = d_ptr->m_fontEditorFactory;

    d_ptr->m_comboBoxFactory = new QExtPEEnumEditorFactory(this);
    const int enumId = QExtPEVariantPropertyManager::enumTypeId();
    d_ptr->m_factoryToType[d_ptr->m_comboBoxFactory] = enumId;
    d_ptr->m_typeToFactory[enumId] = d_ptr->m_comboBoxFactory;
}

QExtPEVariantEditorFactory::~QExtPEVariantEditorFactory()
{
    delete d_ptr;
}

void QExtPEVariantEditorFactory::connectPropertyManager(QExtPEVariantPropertyManager *manager)
{
    QList<QExtPEIntPropertyManager *> intPropertyManagers = qextFindChildren<QExtPEIntPropertyManager *>(manager);
    QListIterator<QExtPEIntPropertyManager *> itInt(intPropertyManagers);
    while (itInt.hasNext())
    {
        d_ptr->m_spinBoxFactory->addPropertyManager(itInt.next());
    }

    QList<QExtPEDoublePropertyManager *> doublePropertyManagers = qextFindChildren<QExtPEDoublePropertyManager *>(manager);
    QListIterator<QExtPEDoublePropertyManager *> itDouble(doublePropertyManagers);
    while (itDouble.hasNext())
    {
        d_ptr->m_doubleSpinBoxFactory->addPropertyManager(itDouble.next());
    }

    QList<QExtPEBoolPropertyManager *> boolPropertyManagers = qextFindChildren<QExtPEBoolPropertyManager *>(manager);
    QListIterator<QExtPEBoolPropertyManager *> itBool(boolPropertyManagers);
    while (itBool.hasNext())
    {
        d_ptr->m_checkBoxFactory->addPropertyManager(itBool.next());
    }

    QList<QExtPEStringPropertyManager *> stringPropertyManagers = qextFindChildren<QExtPEStringPropertyManager *>(manager);
    QListIterator<QExtPEStringPropertyManager *> itString(stringPropertyManagers);
    while (itString.hasNext())
    {
        d_ptr->m_lineEditFactory->addPropertyManager(itString.next());
    }

    QList<QExtPEDatePropertyManager *> datePropertyManagers = qextFindChildren<QExtPEDatePropertyManager *>(manager);
    QListIterator<QExtPEDatePropertyManager *> itDate(datePropertyManagers);
    while (itDate.hasNext())
    {
        d_ptr->m_dateEditFactory->addPropertyManager(itDate.next());
    }

    QList<QExtPETimePropertyManager *> timePropertyManagers = qextFindChildren<QExtPETimePropertyManager *>(manager);
    QListIterator<QExtPETimePropertyManager *> itTime(timePropertyManagers);
    while (itTime.hasNext())
    {
        d_ptr->m_timeEditFactory->addPropertyManager(itTime.next());
    }

    QList<QExtPEDateTimePropertyManager *> dateTimePropertyManagers = qextFindChildren<QExtPEDateTimePropertyManager *>(manager);
    QListIterator<QExtPEDateTimePropertyManager *> itDateTime(dateTimePropertyManagers);
    while (itDateTime.hasNext())
    {
        d_ptr->m_dateTimeEditFactory->addPropertyManager(itDateTime.next());
    }

    QList<QExtPEKeySequencePropertyManager *> keySequencePropertyManagers = qextFindChildren<QExtPEKeySequencePropertyManager *>(manager);
    QListIterator<QExtPEKeySequencePropertyManager *> itKeySequence(keySequencePropertyManagers);
    while (itKeySequence.hasNext())
    {
        d_ptr->m_keySequenceEditorFactory->addPropertyManager(itKeySequence.next());
    }

    QList<QExtPECharPropertyManager *> charPropertyManagers = qextFindChildren<QExtPECharPropertyManager *>(manager);
    QListIterator<QExtPECharPropertyManager *> itChar(charPropertyManagers);
    while (itChar.hasNext())
    {
        d_ptr->m_charEditorFactory->addPropertyManager(itChar.next());
    }

    QList<QExtPELocalePropertyManager *> localePropertyManagers = qextFindChildren<QExtPELocalePropertyManager *>(manager);
    QListIterator<QExtPELocalePropertyManager *> itLocale(localePropertyManagers);
    while (itLocale.hasNext())
    {
        d_ptr->m_comboBoxFactory->addPropertyManager(itLocale.next()->subEnumPropertyManager());
    }

    QList<QExtPEPointPropertyManager *> pointPropertyManagers = qextFindChildren<QExtPEPointPropertyManager *>(manager);
    QListIterator<QExtPEPointPropertyManager *> itPoint(pointPropertyManagers);
    while (itPoint.hasNext())
    {
        d_ptr->m_spinBoxFactory->addPropertyManager(itPoint.next()->subIntPropertyManager());
    }

    QList<QExtPEPointFPropertyManager *> pointFPropertyManagers = qextFindChildren<QExtPEPointFPropertyManager *>(manager);
    QListIterator<QExtPEPointFPropertyManager *> itPointF(pointFPropertyManagers);
    while (itPointF.hasNext())
    {
        d_ptr->m_doubleSpinBoxFactory->addPropertyManager(itPointF.next()->subDoublePropertyManager());
    }

    QList<QExtPESizePropertyManager *> sizePropertyManagers = qextFindChildren<QExtPESizePropertyManager *>(manager);
    QListIterator<QExtPESizePropertyManager *> itSize(sizePropertyManagers);
    while (itSize.hasNext())
    {
        d_ptr->m_spinBoxFactory->addPropertyManager(itSize.next()->subIntPropertyManager());
    }

    QList<QExtPESizeFPropertyManager *> sizeFPropertyManagers = qextFindChildren<QExtPESizeFPropertyManager *>(manager);
    QListIterator<QExtPESizeFPropertyManager *> itSizeF(sizeFPropertyManagers);
    while (itSizeF.hasNext())
    {
        d_ptr->m_doubleSpinBoxFactory->addPropertyManager(itSizeF.next()->subDoublePropertyManager());
    }

    QList<QExtPERectPropertyManager *> rectPropertyManagers = qextFindChildren<QExtPERectPropertyManager *>(manager);
    QListIterator<QExtPERectPropertyManager *> itRect(rectPropertyManagers);
    while (itRect.hasNext())
    {
        d_ptr->m_spinBoxFactory->addPropertyManager(itRect.next()->subIntPropertyManager());
    }

    QList<QExtPERectFPropertyManager *> rectFPropertyManagers = qextFindChildren<QExtPERectFPropertyManager *>(manager);
    QListIterator<QExtPERectFPropertyManager *> itRectF(rectFPropertyManagers);
    while (itRectF.hasNext())
    {
        d_ptr->m_doubleSpinBoxFactory->addPropertyManager(itRectF.next()->subDoublePropertyManager());
    }

    QList<QExtPEColorPropertyManager *> colorPropertyManagers = qextFindChildren<QExtPEColorPropertyManager *>(manager);
    QListIterator<QExtPEColorPropertyManager *> itColor(colorPropertyManagers);
    while (itColor.hasNext())
    {
        QExtPEColorPropertyManager *manager = itColor.next();
        d_ptr->m_colorEditorFactory->addPropertyManager(manager);
        d_ptr->m_spinBoxFactory->addPropertyManager(manager->subIntPropertyManager());
    }

    QList<QExtPEEnumPropertyManager *> enumPropertyManagers = qextFindChildren<QExtPEEnumPropertyManager *>(manager);
    QListIterator<QExtPEEnumPropertyManager *> itEnum(enumPropertyManagers);
    while (itEnum.hasNext())
    {
        d_ptr->m_comboBoxFactory->addPropertyManager(itEnum.next());
    }

    QList<QExtPESizePolicyPropertyManager *> sizePolicyPropertyManagers = qextFindChildren<QExtPESizePolicyPropertyManager *>(manager);
    QListIterator<QExtPESizePolicyPropertyManager *> itSizePolicy(sizePolicyPropertyManagers);
    while (itSizePolicy.hasNext())
    {
        QExtPESizePolicyPropertyManager *manager = itSizePolicy.next();
        d_ptr->m_spinBoxFactory->addPropertyManager(manager->subIntPropertyManager());
        d_ptr->m_comboBoxFactory->addPropertyManager(manager->subEnumPropertyManager());
    }

    QList<QExtPEFontPropertyManager *> fontPropertyManagers = qextFindChildren<QExtPEFontPropertyManager *>(manager);
    QListIterator<QExtPEFontPropertyManager *> itFont(fontPropertyManagers);
    while (itFont.hasNext())
    {
        QExtPEFontPropertyManager *manager = itFont.next();
        d_ptr->m_fontEditorFactory->addPropertyManager(manager);
        d_ptr->m_spinBoxFactory->addPropertyManager(manager->subIntPropertyManager());
        d_ptr->m_comboBoxFactory->addPropertyManager(manager->subEnumPropertyManager());
        d_ptr->m_checkBoxFactory->addPropertyManager(manager->subBoolPropertyManager());
    }

    QList<QExtPECursorPropertyManager *> cursorPropertyManagers = qextFindChildren<QExtPECursorPropertyManager *>(manager);
    QListIterator<QExtPECursorPropertyManager *> itCursor(cursorPropertyManagers);
    while (itCursor.hasNext())
    {
        d_ptr->m_cursorEditorFactory->addPropertyManager(itCursor.next());
    }

    QList<QExtPEFlagPropertyManager *> flagPropertyManagers = qextFindChildren<QExtPEFlagPropertyManager *>(manager);
    QListIterator<QExtPEFlagPropertyManager *> itFlag(flagPropertyManagers);
    while (itFlag.hasNext())
    {
        d_ptr->m_checkBoxFactory->addPropertyManager(itFlag.next()->subBoolPropertyManager());
    }
}

QWidget *QExtPEVariantEditorFactory::createEditor(QExtPEVariantPropertyManager *manager, QExtPEProperty *property,
                                                QWidget *parent)
{
    const int propType = manager->propertyType(property);
    QExtPEAbstractWidgetFactoryBase *factory = d_ptr->m_typeToFactory.value(propType, QEXT_NULLPTR);
    if (!factory)
    {
        return QEXT_NULLPTR;
    }
    return factory->createEditor(wrappedProperty(property), parent);
}

void QExtPEVariantEditorFactory::disconnectPropertyManager(QExtPEVariantPropertyManager *manager)
{
    QList<QExtPEIntPropertyManager *> intPropertyManagers = qextFindChildren<QExtPEIntPropertyManager *>(manager);
    QListIterator<QExtPEIntPropertyManager *> itInt(intPropertyManagers);
    while (itInt.hasNext())
    {
        d_ptr->m_spinBoxFactory->removePropertyManager(itInt.next());
    }

    QList<QExtPEDoublePropertyManager *> doublePropertyManagers = qextFindChildren<QExtPEDoublePropertyManager *>(manager);
    QListIterator<QExtPEDoublePropertyManager *> itDouble(doublePropertyManagers);
    while (itDouble.hasNext())
    {
        d_ptr->m_doubleSpinBoxFactory->removePropertyManager(itDouble.next());
    }

    QList<QExtPEBoolPropertyManager *> boolPropertyManagers = qextFindChildren<QExtPEBoolPropertyManager *>(manager);
    QListIterator<QExtPEBoolPropertyManager *> itBool(boolPropertyManagers);
    while (itBool.hasNext())
    {
        d_ptr->m_checkBoxFactory->removePropertyManager(itBool.next());
    }

    QList<QExtPEStringPropertyManager *> stringPropertyManagers = qextFindChildren<QExtPEStringPropertyManager *>(manager);
    QListIterator<QExtPEStringPropertyManager *> itString(stringPropertyManagers);
    while (itString.hasNext())
    {
        d_ptr->m_lineEditFactory->removePropertyManager(itString.next());
    }

    QList<QExtPEDatePropertyManager *> datePropertyManagers = qextFindChildren<QExtPEDatePropertyManager *>(manager);
    QListIterator<QExtPEDatePropertyManager *> itDate(datePropertyManagers);
    while (itDate.hasNext())
    {
        d_ptr->m_dateEditFactory->removePropertyManager(itDate.next());
    }

    QList<QExtPETimePropertyManager *> timePropertyManagers = qextFindChildren<QExtPETimePropertyManager *>(manager);
    QListIterator<QExtPETimePropertyManager *> itTime(timePropertyManagers);
    while (itTime.hasNext())
    {
        d_ptr->m_timeEditFactory->removePropertyManager(itTime.next());
    }

    QList<QExtPEDateTimePropertyManager *> dateTimePropertyManagers = qextFindChildren<QExtPEDateTimePropertyManager *>(manager);
    QListIterator<QExtPEDateTimePropertyManager *> itDateTime(dateTimePropertyManagers);
    while (itDateTime.hasNext())
    {
        d_ptr->m_dateTimeEditFactory->removePropertyManager(itDateTime.next());
    }

    QList<QExtPEKeySequencePropertyManager *> keySequencePropertyManagers = qextFindChildren<QExtPEKeySequencePropertyManager *>(manager);
    QListIterator<QExtPEKeySequencePropertyManager *> itKeySequence(keySequencePropertyManagers);
    while (itKeySequence.hasNext())
    {
        d_ptr->m_keySequenceEditorFactory->removePropertyManager(itKeySequence.next());
    }

    QList<QExtPECharPropertyManager *> charPropertyManagers = qextFindChildren<QExtPECharPropertyManager *>(manager);
    QListIterator<QExtPECharPropertyManager *> itChar(charPropertyManagers);
    while (itChar.hasNext())
    {
        d_ptr->m_charEditorFactory->removePropertyManager(itChar.next());
    }

    QList<QExtPELocalePropertyManager *> localePropertyManagers = qextFindChildren<QExtPELocalePropertyManager *>(manager);
    QListIterator<QExtPELocalePropertyManager *> itLocale(localePropertyManagers);
    while (itLocale.hasNext())
    {
        d_ptr->m_comboBoxFactory->removePropertyManager(itLocale.next()->subEnumPropertyManager());
    }

    QList<QExtPEPointPropertyManager *> pointPropertyManagers = qextFindChildren<QExtPEPointPropertyManager *>(manager);
    QListIterator<QExtPEPointPropertyManager *> itPoint(pointPropertyManagers);
    while (itPoint.hasNext())
    {
        d_ptr->m_spinBoxFactory->removePropertyManager(itPoint.next()->subIntPropertyManager());
    }

    QList<QExtPEPointFPropertyManager *> pointFPropertyManagers = qextFindChildren<QExtPEPointFPropertyManager *>(manager);
    QListIterator<QExtPEPointFPropertyManager *> itPointF(pointFPropertyManagers);
    while (itPointF.hasNext())
    {
        d_ptr->m_doubleSpinBoxFactory->removePropertyManager(itPointF.next()->subDoublePropertyManager());
    }

    QList<QExtPESizePropertyManager *> sizePropertyManagers = qextFindChildren<QExtPESizePropertyManager *>(manager);
    QListIterator<QExtPESizePropertyManager *> itSize(sizePropertyManagers);
    while (itSize.hasNext())
    {
        d_ptr->m_spinBoxFactory->removePropertyManager(itSize.next()->subIntPropertyManager());
    }

    QList<QExtPESizeFPropertyManager *> sizeFPropertyManagers = qextFindChildren<QExtPESizeFPropertyManager *>(manager);
    QListIterator<QExtPESizeFPropertyManager *> itSizeF(sizeFPropertyManagers);
    while (itSizeF.hasNext())
    {
        d_ptr->m_doubleSpinBoxFactory->removePropertyManager(itSizeF.next()->subDoublePropertyManager());
    }

    QList<QExtPERectPropertyManager *> rectPropertyManagers = qextFindChildren<QExtPERectPropertyManager *>(manager);
    QListIterator<QExtPERectPropertyManager *> itRect(rectPropertyManagers);
    while (itRect.hasNext())
    {
        d_ptr->m_spinBoxFactory->removePropertyManager(itRect.next()->subIntPropertyManager());
    }

    QList<QExtPERectFPropertyManager *> rectFPropertyManagers = qextFindChildren<QExtPERectFPropertyManager *>(manager);
    QListIterator<QExtPERectFPropertyManager *> itRectF(rectFPropertyManagers);
    while (itRectF.hasNext())
    {
        d_ptr->m_doubleSpinBoxFactory->removePropertyManager(itRectF.next()->subDoublePropertyManager());
    }

    QList<QExtPEColorPropertyManager *> colorPropertyManagers = qextFindChildren<QExtPEColorPropertyManager *>(manager);
    QListIterator<QExtPEColorPropertyManager *> itColor(colorPropertyManagers);
    while (itColor.hasNext())
    {
        QExtPEColorPropertyManager *manager = itColor.next();
        d_ptr->m_colorEditorFactory->removePropertyManager(manager);
        d_ptr->m_spinBoxFactory->removePropertyManager(manager->subIntPropertyManager());
    }

    QList<QExtPEEnumPropertyManager *> enumPropertyManagers = qextFindChildren<QExtPEEnumPropertyManager *>(manager);
    QListIterator<QExtPEEnumPropertyManager *> itEnum(enumPropertyManagers);
    while (itEnum.hasNext())
    {
        d_ptr->m_comboBoxFactory->removePropertyManager(itEnum.next());
    }

    QList<QExtPESizePolicyPropertyManager *> sizePolicyPropertyManagers = qextFindChildren<QExtPESizePolicyPropertyManager *>(manager);
    QListIterator<QExtPESizePolicyPropertyManager *> itSizePolicy(sizePolicyPropertyManagers);
    while (itSizePolicy.hasNext())
    {
        QExtPESizePolicyPropertyManager *manager = itSizePolicy.next();
        d_ptr->m_spinBoxFactory->removePropertyManager(manager->subIntPropertyManager());
        d_ptr->m_comboBoxFactory->removePropertyManager(manager->subEnumPropertyManager());
    }

    QList<QExtPEFontPropertyManager *> fontPropertyManagers = qextFindChildren<QExtPEFontPropertyManager *>(manager);
    QListIterator<QExtPEFontPropertyManager *> itFont(fontPropertyManagers);
    while (itFont.hasNext())
    {
        QExtPEFontPropertyManager *manager = itFont.next();
        d_ptr->m_fontEditorFactory->removePropertyManager(manager);
        d_ptr->m_spinBoxFactory->removePropertyManager(manager->subIntPropertyManager());
        d_ptr->m_comboBoxFactory->removePropertyManager(manager->subEnumPropertyManager());
        d_ptr->m_checkBoxFactory->removePropertyManager(manager->subBoolPropertyManager());
    }

    QList<QExtPECursorPropertyManager *> cursorPropertyManagers = qextFindChildren<QExtPECursorPropertyManager *>(manager);
    QListIterator<QExtPECursorPropertyManager *> itCursor(cursorPropertyManagers);
    while (itCursor.hasNext())
    {
        d_ptr->m_cursorEditorFactory->removePropertyManager(itCursor.next());
    }

    QList<QExtPEFlagPropertyManager *> flagPropertyManagers = qextFindChildren<QExtPEFlagPropertyManager *>(manager);
    QListIterator<QExtPEFlagPropertyManager *> itFlag(flagPropertyManagers);
    while (itFlag.hasNext())
    {
        d_ptr->m_checkBoxFactory->removePropertyManager(itFlag.next()->subBoolPropertyManager());
    }
}


#include <moc_qextPEVariantProperty.cpp>
