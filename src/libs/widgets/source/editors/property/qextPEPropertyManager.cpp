#include <private/qextPEAbstractPropertyEditor_p.h>
#include <private/qextPEPropertyManager_p.h>
#include <private/qextPEWidgetFactory_p.h>
#include <qextLimits.h>

#include <QTimer>
#include <QFontDatabase>

template <class SizeValue>
static SizeValue qBoundSize(const SizeValue &minVal, const SizeValue &val, const SizeValue &maxVal)
{
    SizeValue croppedVal = val;
    if (minVal.width() > val.width())
    {
        croppedVal.setWidth(minVal.width());
    }
    else if (maxVal.width() < val.width())
    {
        croppedVal.setWidth(maxVal.width());
    }

    if (minVal.height() > val.height())
    {
        croppedVal.setHeight(minVal.height());
    }
    else if (maxVal.height() < val.height())
    {
        croppedVal.setHeight(maxVal.height());
    }

    return croppedVal;
}

// Match the exact signature of qBound for VS 6.
QSize qBound(QSize minVal, QSize val, QSize maxVal)
{
    return qBoundSize(minVal, val, maxVal);
}

QSizeF qBound(QSizeF minVal, QSizeF val, QSizeF maxVal)
{
    return qBoundSize(minVal, val, maxVal);
}

namespace
{

namespace
{
template <class Value>
void orderBorders(Value &minVal, Value &maxVal)
{
    if (minVal > maxVal)
    {
        qSwap(minVal, maxVal);
    }
}

template <class Value>
static void orderSizeBorders(Value &minVal, Value &maxVal)
{
    Value fromSize = minVal;
    Value toSize = maxVal;
    if (fromSize.width() > toSize.width())
    {
        fromSize.setWidth(maxVal.width());
        toSize.setWidth(minVal.width());
    }
    if (fromSize.height() > toSize.height())
    {
        fromSize.setHeight(maxVal.height());
        toSize.setHeight(minVal.height());
    }
    minVal = fromSize;
    maxVal = toSize;
}

void orderBorders(QSize &minVal, QSize &maxVal)
{
    orderSizeBorders(minVal, maxVal);
}

void orderBorders(QSizeF &minVal, QSizeF &maxVal)
{
    orderSizeBorders(minVal, maxVal);
}

}
}


template <class Value, class PrivateData>
static Value getData(const QMap<const QExtPEProperty *, PrivateData> &propertyMap, Value PrivateData::*data,
                     const QExtPEProperty *property, const Value &defaultValue = Value())
{
    typedef QMap<const QExtPEProperty *, PrivateData> PropertyToData;
    typedef typename PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = propertyMap.constFind(property);
    if (it == propertyMap.constEnd())
    {
        return defaultValue;
    }
    return it.value().*data;
}

template <class Value, class PrivateData>
static Value getValue(const QMap<const QExtPEProperty *, PrivateData> &propertyMap,
                      const QExtPEProperty *property, const Value &defaultValue = Value())
{
    return getData<Value>(propertyMap, &PrivateData::val, property, defaultValue);
}

template <class Value, class PrivateData>
static Value getMinimum(const QMap<const QExtPEProperty *, PrivateData> &propertyMap,
                        const QExtPEProperty *property, const Value &defaultValue = Value())
{
    return getData<Value>(propertyMap, &PrivateData::minVal, property, defaultValue);
}

template <class Value, class PrivateData>
static Value getMaximum(const QMap<const QExtPEProperty *, PrivateData> &propertyMap,
                        const QExtPEProperty *property, const Value &defaultValue = Value())
{
    return getData<Value>(propertyMap, &PrivateData::maxVal, property, defaultValue);
}

template <class ValueChangeParameter, class Value, class PropertyManager>
static void setSimpleValue(QMap<const QExtPEProperty *, Value> &propertyMap, PropertyManager *manager,
                           void (PropertyManager::*propertyChangedSignal)(QExtPEProperty *),
                           void (PropertyManager::*valueChangedSignal)(QExtPEProperty *, ValueChangeParameter),
                           QExtPEProperty *property, const Value &val)
{
    typedef QMap<const QExtPEProperty *, Value> PropertyToData;
    typedef typename PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = propertyMap.find(property);
    if (it == propertyMap.end())
    {
        return;
    }

    if (it.value() == val)
    {
        return;
    }

    it.value() = val;

    emit (manager->*propertyChangedSignal)(property);
    emit (manager->*valueChangedSignal)(property, val);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value>
static void setValueInRange(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
                            void (PropertyManager::*propertyChangedSignal)(QExtPEProperty *),
                            void (PropertyManager::*valueChangedSignal)(QExtPEProperty *, ValueChangeParameter),
                            QExtPEProperty *property, const Value &val,
                            void (PropertyManagerPrivate::*setSubPropertyValue)(QExtPEProperty *, ValueChangeParameter))
{
    typedef typename PropertyManagerPrivate::Data PrivateData;
    typedef QMap<const QExtPEProperty *, PrivateData> PropertyToData;
    typedef typename PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = managerPrivate->m_values.find(property);
    if (it == managerPrivate->m_values.end())
    {
        return;
    }

    PrivateData &data = it.value();

    if (data.val == val)
    {
        return;
    }

    const Value oldVal = data.val;

    data.val = qBound(data.minVal, val, data.maxVal);

    if (data.val == oldVal)
    {
        return;
    }

    if (setSubPropertyValue)
    {
        (managerPrivate->*setSubPropertyValue)(property, data.val);
    }

    emit (manager->*propertyChangedSignal)(property);
    emit (manager->*valueChangedSignal)(property, data.val);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value>
static void setBorderValues(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
                            void (PropertyManager::*propertyChangedSignal)(QExtPEProperty *),
                            void (PropertyManager::*valueChangedSignal)(QExtPEProperty *, ValueChangeParameter),
                            void (PropertyManager::*rangeChangedSignal)(QExtPEProperty *, ValueChangeParameter, ValueChangeParameter),
                            QExtPEProperty *property, const Value &minVal, const Value &maxVal,
                            void (PropertyManagerPrivate::*setSubPropertyRange)(QExtPEProperty *,
                                                                                ValueChangeParameter, ValueChangeParameter, ValueChangeParameter))
{
    typedef typename PropertyManagerPrivate::Data PrivateData;
    typedef QMap<const QExtPEProperty *, PrivateData> PropertyToData;
    typedef typename PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = managerPrivate->m_values.find(property);
    if (it == managerPrivate->m_values.end())
    {
        return;
    }

    Value fromVal = minVal;
    Value toVal = maxVal;
    orderBorders(fromVal, toVal);

    PrivateData &data = it.value();

    if (data.minVal == fromVal && data.maxVal == toVal)
    {
        return;
    }

    const Value oldVal = data.val;

    data.setMinimumValue(fromVal);
    data.setMaximumValue(toVal);

    emit (manager->*rangeChangedSignal)(property, data.minVal, data.maxVal);

    if (setSubPropertyRange)
    {
        (managerPrivate->*setSubPropertyRange)(property, data.minVal, data.maxVal, data.val);
    }

    if (data.val == oldVal)
    {
        return;
    }

    emit (manager->*propertyChangedSignal)(property);
    emit (manager->*valueChangedSignal)(property, data.val);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value, class PrivateData>
static void setBorderValue(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
                           void (PropertyManager::*propertyChangedSignal)(QExtPEProperty *),
                           void (PropertyManager::*valueChangedSignal)(QExtPEProperty *, ValueChangeParameter),
                           void (PropertyManager::*rangeChangedSignal)(QExtPEProperty *, ValueChangeParameter, ValueChangeParameter),
                           QExtPEProperty *property,
                           Value (PrivateData::*getRangeVal)() const,
                           void (PrivateData::*setRangeVal)(ValueChangeParameter), const Value &borderVal,
                           void (PropertyManagerPrivate::*setSubPropertyRange)(QExtPEProperty *,
                                                                               ValueChangeParameter, ValueChangeParameter, ValueChangeParameter))
{
    typedef QMap<const QExtPEProperty *, PrivateData> PropertyToData;
    typedef typename PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = managerPrivate->m_values.find(property);
    if (it == managerPrivate->m_values.end())
    {
        return;
    }

    PrivateData &data = it.value();

    if ((data.*getRangeVal)() == borderVal)
    {
        return;
    }

    const Value oldVal = data.val;

    (data.*setRangeVal)(borderVal);

    emit (manager->*rangeChangedSignal)(property, data.minVal, data.maxVal);

    if (setSubPropertyRange)
    {
        (managerPrivate->*setSubPropertyRange)(property, data.minVal, data.maxVal, data.val);
    }

    if (data.val == oldVal)
    {
        return;
    }

    emit (manager->*propertyChangedSignal)(property);
    emit (manager->*valueChangedSignal)(property, data.val);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value, class PrivateData>
static void setMinimumValue(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
                            void (PropertyManager::*propertyChangedSignal)(QExtPEProperty *),
                            void (PropertyManager::*valueChangedSignal)(QExtPEProperty *, ValueChangeParameter),
                            void (PropertyManager::*rangeChangedSignal)(QExtPEProperty *, ValueChangeParameter, ValueChangeParameter),
                            QExtPEProperty *property, const Value &minVal)
{
    void (PropertyManagerPrivate::*setSubPropertyRange)(QExtPEProperty *,
                                                        ValueChangeParameter, ValueChangeParameter, ValueChangeParameter) = QEXT_NULLPTR;
    setBorderValue<ValueChangeParameter, PropertyManagerPrivate, PropertyManager, Value, PrivateData>
        (manager, managerPrivate,
         propertyChangedSignal, valueChangedSignal, rangeChangedSignal,
         property, &PropertyManagerPrivate::Data::minimumValue, &PropertyManagerPrivate::Data::setMinimumValue, minVal, setSubPropertyRange);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value, class PrivateData>
static void setMaximumValue(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
                            void (PropertyManager::*propertyChangedSignal)(QExtPEProperty *),
                            void (PropertyManager::*valueChangedSignal)(QExtPEProperty *, ValueChangeParameter),
                            void (PropertyManager::*rangeChangedSignal)(QExtPEProperty *, ValueChangeParameter, ValueChangeParameter),
                            QExtPEProperty *property, const Value &maxVal)
{
    void (PropertyManagerPrivate::*setSubPropertyRange)(QExtPEProperty *,
                                                        ValueChangeParameter, ValueChangeParameter, ValueChangeParameter) = QEXT_NULLPTR;
    setBorderValue<ValueChangeParameter, PropertyManagerPrivate, PropertyManager, Value, PrivateData>
        (manager, managerPrivate,
         propertyChangedSignal, valueChangedSignal, rangeChangedSignal,
         property, &PropertyManagerPrivate::Data::maximumValue, &PropertyManagerPrivate::Data::setMaximumValue, maxVal, setSubPropertyRange);
}


/***********************************************************************************************************************
 * QExtPEAbstractPropertyManager
***********************************************************************************************************************/
QExtPEAbstractPropertyManagerPrivate::QExtPEAbstractPropertyManagerPrivate(QExtPEAbstractPropertyManager *q)
    : q_ptr(q)
{
}

void QExtPEAbstractPropertyManagerPrivate::propertyDestroyed(QExtPEProperty *property)
{
    Q_Q(QExtPEAbstractPropertyManager);
    if (mProperties.contains(property))
    {
        emit q->propertyDestroyed(property);
        q->uninitializeProperty(property);
        mProperties.remove(property);
    }
}

void QExtPEAbstractPropertyManagerPrivate::propertyChanged(QExtPEProperty *property)
{
    Q_Q(QExtPEAbstractPropertyManager);
    emit q->propertyChanged(property);
}

void QExtPEAbstractPropertyManagerPrivate::propertyRemoved(QExtPEProperty *property,
                                                           QExtPEProperty *parentProperty)
{
    Q_Q(QExtPEAbstractPropertyManager);
    emit q->propertyRemoved(property, parentProperty);
}

void QExtPEAbstractPropertyManagerPrivate::propertyInserted(QExtPEProperty *property,
                                                            QExtPEProperty *parentProperty,
                                                            QExtPEProperty *afterProperty)
{
    Q_Q(QExtPEAbstractPropertyManager);
    emit q->propertyInserted(property, parentProperty, afterProperty);
}


QExtPEAbstractPropertyManager::QExtPEAbstractPropertyManager(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtPEAbstractPropertyManagerPrivate(this))
{
}

QExtPEAbstractPropertyManager::~QExtPEAbstractPropertyManager()
{
    this->clear();
}

void QExtPEAbstractPropertyManager::clear() const
{
    while (!properties().isEmpty())
    {
        QSetIterator<QExtPEProperty *> itProperty(properties());
        QExtPEProperty *prop = itProperty.next();
        delete prop;
    }
}

QSet<QExtPEProperty *> QExtPEAbstractPropertyManager::properties() const
{
    Q_D(const QExtPEAbstractPropertyManager);
    return d->mProperties;
}

bool QExtPEAbstractPropertyManager::hasValue(const QExtPEProperty *property) const
{
    Q_UNUSED(property)
    return true;
}

QIcon QExtPEAbstractPropertyManager::valueIcon(const QExtPEProperty *property) const
{
    Q_UNUSED(property)
    return QIcon();
}

QString QExtPEAbstractPropertyManager::valueText(const QExtPEProperty *property) const
{
    Q_UNUSED(property)
    return QString();
}

QString QExtPEAbstractPropertyManager::displayText(const QExtPEProperty *property) const
{
    Q_UNUSED(property)
    return QString();
}

EchoMode QExtPEAbstractPropertyManager::echoMode(const QExtPEProperty *property) const
{
    Q_UNUSED(property)
    return QLineEdit::Normal;
}

QExtPEProperty *QExtPEAbstractPropertyManager::addProperty(const QString &name)
{
    Q_D(QExtPEAbstractPropertyManager);
    QExtPEProperty *property = this->createProperty();
    if (property)
    {
        property->setPropertyName(name);
        d->mProperties.insert(property);
        this->initializeProperty(property);
    }
    return property;
}

QExtPEProperty *QExtPEAbstractPropertyManager::createProperty()
{
    return new QExtPEProperty(this);
}

void QExtPEAbstractPropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    Q_UNUSED(property)
}


/***********************************************************************************************************************
 * QExtPEGroupPropertyManager
***********************************************************************************************************************/
QExtPEGroupPropertyManager::QExtPEGroupPropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
}

QExtPEGroupPropertyManager::~QExtPEGroupPropertyManager()
{
}

bool QExtPEGroupPropertyManager::hasValue(const QExtPEProperty *property) const
{
    Q_UNUSED(property)
    return false;
}

void QExtPEGroupPropertyManager::initializeProperty(QExtPEProperty *property)
{
    Q_UNUSED(property)
}

void QExtPEGroupPropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    Q_UNUSED(property)
}


/***********************************************************************************************************************
 * QExtPEIntPropertyManager
***********************************************************************************************************************/
QExtPEIntPropertyManager::QExtPEIntPropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPEIntPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

QExtPEIntPropertyManager::~QExtPEIntPropertyManager()
{
    this->clear();
    delete d_ptr;
}

int QExtPEIntPropertyManager::value(const QExtPEProperty *property) const
{
    return getValue<int>(d_ptr->m_values, property, 0);
}

int QExtPEIntPropertyManager::minimum(const QExtPEProperty *property) const
{
    return getMinimum<int>(d_ptr->m_values, property, 0);
}

int QExtPEIntPropertyManager::maximum(const QExtPEProperty *property) const
{
    return getMaximum<int>(d_ptr->m_values, property, 0);
}

int QExtPEIntPropertyManager::singleStep(const QExtPEProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QExtPEIntPropertyManagerPrivate::Data::singleStep, property, 0);
}

bool QExtPEIntPropertyManager::isReadOnly(const QExtPEProperty *property) const
{
    return getData<bool>(d_ptr->m_values, &QExtPEIntPropertyManagerPrivate::Data::readOnly, property, false);
}

QString QExtPEIntPropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPEIntPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }
    return QString::number(it.value().val);
}

void QExtPEIntPropertyManager::setValue(QExtPEProperty *property, int val)
{
    void (QExtPEIntPropertyManagerPrivate::*setSubPropertyValue)(QExtPEProperty *, int) = QEXT_NULLPTR;
    setValueInRange<int, QExtPEIntPropertyManagerPrivate, QExtPEIntPropertyManager, int>(this, d_ptr,
                                                                                     &QExtPEIntPropertyManager::propertyChanged,
                                                                                     &QExtPEIntPropertyManager::valueChanged,
                                                                                     property, val, setSubPropertyValue);
}

void QExtPEIntPropertyManager::setMinimum(QExtPEProperty *property, int minVal)
{
    setMinimumValue<int, QExtPEIntPropertyManagerPrivate, QExtPEIntPropertyManager, int, QExtPEIntPropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                          &QExtPEIntPropertyManager::propertyChanged,
                                                                                                                          &QExtPEIntPropertyManager::valueChanged,
                                                                                                                          &QExtPEIntPropertyManager::rangeChanged,
                                                                                                                          property, minVal);
}

void QExtPEIntPropertyManager::setMaximum(QExtPEProperty *property, int maxVal)
{
    setMaximumValue<int, QExtPEIntPropertyManagerPrivate, QExtPEIntPropertyManager, int, QExtPEIntPropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                          &QExtPEIntPropertyManager::propertyChanged,
                                                                                                                          &QExtPEIntPropertyManager::valueChanged,
                                                                                                                          &QExtPEIntPropertyManager::rangeChanged,
                                                                                                                          property, maxVal);
}

void QExtPEIntPropertyManager::setRange(QExtPEProperty *property, int minVal, int maxVal)
{
    void (QExtPEIntPropertyManagerPrivate::*setSubPropertyRange)(QExtPEProperty *, int, int, int) = QEXT_NULLPTR;
    setBorderValues<int, QExtPEIntPropertyManagerPrivate, QExtPEIntPropertyManager, int>(this, d_ptr,
                                                                                     &QExtPEIntPropertyManager::propertyChanged,
                                                                                     &QExtPEIntPropertyManager::valueChanged,
                                                                                     &QExtPEIntPropertyManager::rangeChanged,
                                                                                     property, minVal, maxVal, setSubPropertyRange);
}

void QExtPEIntPropertyManager::setSingleStep(QExtPEProperty *property, int step)
{
    const QExtPEIntPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPEIntPropertyManagerPrivate::Data data = it.value();

    if (step < 0)
    {
        step = 0;
    }

    if (data.singleStep == step)
    {
        return;
    }

    data.singleStep = step;

    it.value() = data;

    emit this->singleStepChanged(property, data.singleStep);
}

void QExtPEIntPropertyManager::setReadOnly(QExtPEProperty *property, bool readOnly)
{
    const QExtPEIntPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPEIntPropertyManagerPrivate::Data data = it.value();

    if (data.readOnly == readOnly)
    {
        return;
    }

    data.readOnly = readOnly;
    it.value() = data;

    emit this->propertyChanged(property);
    emit this->readOnlyChanged(property, data.readOnly);
}

void QExtPEIntPropertyManager::initializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values[property] = QExtPEIntPropertyManagerPrivate::Data();
}

void QExtPEIntPropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPEDoublePropertyManager
***********************************************************************************************************************/
QExtPEDoublePropertyManager::QExtPEDoublePropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPEDoublePropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

QExtPEDoublePropertyManager::~QExtPEDoublePropertyManager()
{
    this->clear();
    delete d_ptr;
}

double QExtPEDoublePropertyManager::value(const QExtPEProperty *property) const
{
    return getValue<double>(d_ptr->m_values, property, 0.0);
}

double QExtPEDoublePropertyManager::minimum(const QExtPEProperty *property) const
{
    return getMinimum<double>(d_ptr->m_values, property, 0.0);
}

double QExtPEDoublePropertyManager::maximum(const QExtPEProperty *property) const
{
    return getMaximum<double>(d_ptr->m_values, property, 0.0);
}

double QExtPEDoublePropertyManager::singleStep(const QExtPEProperty *property) const
{
    return getData<double>(d_ptr->m_values, &QExtPEDoublePropertyManagerPrivate::Data::singleStep, property, 0);
}

int QExtPEDoublePropertyManager::decimals(const QExtPEProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QExtPEDoublePropertyManagerPrivate::Data::decimals, property, 0);
}

bool QExtPEDoublePropertyManager::isReadOnly(const QExtPEProperty *property) const
{
    return getData<bool>(d_ptr->m_values, &QExtPEDoublePropertyManagerPrivate::Data::readOnly, property, false);
}

QString QExtPEDoublePropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPEDoublePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }
    return QLocale::system().toString(it.value().val, 'f', it.value().decimals);
}

void QExtPEDoublePropertyManager::setValue(QExtPEProperty *property, double val)
{
    void (QExtPEDoublePropertyManagerPrivate::*setSubPropertyValue)(QExtPEProperty *, double) = QEXT_NULLPTR;
    setValueInRange<double, QExtPEDoublePropertyManagerPrivate, QExtPEDoublePropertyManager, double>(this, d_ptr,
                                                                                                 &QExtPEDoublePropertyManager::propertyChanged,
                                                                                                 &QExtPEDoublePropertyManager::valueChanged,
                                                                                                 property, val, setSubPropertyValue);
}

void QExtPEDoublePropertyManager::setSingleStep(QExtPEProperty *property, double step)
{
    const QExtPEDoublePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPEDoublePropertyManagerPrivate::Data data = it.value();

    if (step < 0)
    {
        step = 0;
    }

    if (data.singleStep == step)
    {
        return;
    }

    data.singleStep = step;

    it.value() = data;

    emit this->singleStepChanged(property, data.singleStep);
}

void QExtPEDoublePropertyManager::setReadOnly(QExtPEProperty *property, bool readOnly)
{
    const QExtPEDoublePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);

    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPEDoublePropertyManagerPrivate::Data data = it.value();

    if (data.readOnly == readOnly)
    {
        return;
    }

    data.readOnly = readOnly;
    it.value() = data;

    emit this->propertyChanged(property);
    emit this->readOnlyChanged(property, data.readOnly);
}

void QExtPEDoublePropertyManager::setDecimals(QExtPEProperty *property, int prec)
{
    const QExtPEDoublePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPEDoublePropertyManagerPrivate::Data data = it.value();

    if (prec > 13)
    {
        prec = 13;
    }
    else if (prec < 0)
    {
        prec = 0;
    }

    if (data.decimals == prec)
    {
        return;
    }

    data.decimals = prec;

    it.value() = data;

    emit this->decimalsChanged(property, data.decimals);
}

void QExtPEDoublePropertyManager::setMinimum(QExtPEProperty *property, double minVal)
{
    setMinimumValue<double, QExtPEDoublePropertyManagerPrivate, QExtPEDoublePropertyManager, double, QExtPEDoublePropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                                         &QExtPEDoublePropertyManager::propertyChanged,
                                                                                                                                         &QExtPEDoublePropertyManager::valueChanged,
                                                                                                                                         &QExtPEDoublePropertyManager::rangeChanged,
                                                                                                                                         property, minVal);
}

void QExtPEDoublePropertyManager::setMaximum(QExtPEProperty *property, double maxVal)
{
    setMaximumValue<double, QExtPEDoublePropertyManagerPrivate, QExtPEDoublePropertyManager, double, QExtPEDoublePropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                                         &QExtPEDoublePropertyManager::propertyChanged,
                                                                                                                                         &QExtPEDoublePropertyManager::valueChanged,
                                                                                                                                         &QExtPEDoublePropertyManager::rangeChanged,
                                                                                                                                         property, maxVal);
}

void QExtPEDoublePropertyManager::setRange(QExtPEProperty *property, double minVal, double maxVal)
{
    void (QExtPEDoublePropertyManagerPrivate::*setSubPropertyRange)(QExtPEProperty *, double, double, double) = QEXT_NULLPTR;
    setBorderValues<double, QExtPEDoublePropertyManagerPrivate, QExtPEDoublePropertyManager, double>(this, d_ptr,
                                                                                                 &QExtPEDoublePropertyManager::propertyChanged,
                                                                                                 &QExtPEDoublePropertyManager::valueChanged,
                                                                                                 &QExtPEDoublePropertyManager::rangeChanged,
                                                                                                 property, minVal, maxVal, setSubPropertyRange);
}

void QExtPEDoublePropertyManager::initializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values[property] = QExtPEDoublePropertyManagerPrivate::Data();
}

void QExtPEDoublePropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPEStringPropertyManager
***********************************************************************************************************************/
QExtPEStringPropertyManager::QExtPEStringPropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPEStringPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

QExtPEStringPropertyManager::~QExtPEStringPropertyManager()
{
    this->clear();
    delete d_ptr;
}

QString QExtPEStringPropertyManager::value(const QExtPEProperty *property) const
{
    return getValue<QString>(d_ptr->m_values, property);
}

QRegExp QExtPEStringPropertyManager::regExp(const QExtPEProperty *property) const
{
    return getData<QRegExp>(d_ptr->m_values, &QExtPEStringPropertyManagerPrivate::Data::regExp, property, QRegExp());
}

EchoMode QExtPEStringPropertyManager::echoMode(const QExtPEProperty *property) const
{
    return (EchoMode)getData<int>(d_ptr->m_values, &QExtPEStringPropertyManagerPrivate::Data::echoMode, property, 0);
}

bool QExtPEStringPropertyManager::isReadOnly(const QExtPEProperty *property) const
{
    return getData<bool>(d_ptr->m_values, &QExtPEStringPropertyManagerPrivate::Data::readOnly, property, false);
}

QString QExtPEStringPropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPEStringPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }

    return it.value().val;
}

QString QExtPEStringPropertyManager::displayText(const QExtPEProperty *property) const
{
    const QExtPEStringPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }

    QLineEdit edit;
    edit.setEchoMode((EchoMode)it.value().echoMode);
    edit.setText(it.value().val);
    return edit.displayText();
}

/*!
    \fn void QExtPEStringPropertyManager::setValue(QExtPEProperty *property, const QString &value)

    Sets the value of the given \a property to \a value.

    If the specified \a value doesn't match the given \a property's
    regular expression, this function does nothing.

    \sa value(), setRegExp(), valueChanged()
*/
void QExtPEStringPropertyManager::setValue(QExtPEProperty *property, const QString &val)
{
    const QExtPEStringPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPEStringPropertyManagerPrivate::Data data = it.value();

    if (data.val == val)
    {
        return;
    }

    if (data.regExp.isValid() && !data.regExp.exactMatch(val))
    {
        return;
    }

    data.val = val;

    it.value() = data;

    emit this->propertyChanged(property);
    emit this->valueChanged(property, data.val);
}

/*!
    Sets the regular expression of the given \a property to \a regExp.

    \sa regExp(), setValue(), regExpChanged()
*/
void QExtPEStringPropertyManager::setRegExp(QExtPEProperty *property, const QRegExp &regExp)
{
    const QExtPEStringPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPEStringPropertyManagerPrivate::Data data = it.value() ;

    if (data.regExp == regExp)
    {
        return;
    }

    data.regExp = regExp;

    it.value() = data;

    emit this->regExpChanged(property, data.regExp);
}


void QExtPEStringPropertyManager::setEchoMode(QExtPEProperty *property, EchoMode echoMode)
{
    const QExtPEStringPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPEStringPropertyManagerPrivate::Data data = it.value();

    if (data.echoMode == echoMode)
    {
        return;
    }

    data.echoMode = echoMode;
    it.value() = data;

    emit this->propertyChanged(property);
    emit this->echoModeChanged(property, data.echoMode);
}

void QExtPEStringPropertyManager::setReadOnly(QExtPEProperty *property, bool readOnly)
{
    const QExtPEStringPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPEStringPropertyManagerPrivate::Data data = it.value();

    if (data.readOnly == readOnly)
    {
        return;
    }

    data.readOnly = readOnly;
    it.value() = data;

    emit this->propertyChanged(property);
    emit this->readOnlyChanged(property, data.readOnly);
}

void QExtPEStringPropertyManager::initializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values[property] = QExtPEStringPropertyManagerPrivate::Data();
}

void QExtPEStringPropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPEBoolPropertyManager
***********************************************************************************************************************/
QExtPEBoolPropertyManagerPrivate::QExtPEBoolPropertyManagerPrivate()
    : m_checkedIcon(drawCheckBox(true))
    , m_uncheckedIcon(drawCheckBox(false))
{
}



QExtPEBoolPropertyManager::QExtPEBoolPropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPEBoolPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

QExtPEBoolPropertyManager::~QExtPEBoolPropertyManager()
{
    this->clear();
    delete d_ptr;
}

bool QExtPEBoolPropertyManager::value(const QExtPEProperty *property) const
{
    return getValue<bool>(d_ptr->m_values, property, false);
}

bool QExtPEBoolPropertyManager::textVisible(const QExtPEProperty *property) const
{
    return getData<bool>(d_ptr->m_values, &QExtPEBoolPropertyManagerPrivate::Data::textVisible, property, false);
}

QString QExtPEBoolPropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPEBoolPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }

    const QExtPEBoolPropertyManagerPrivate::Data &data = it.value();
    if (!data.textVisible)
    {
        return QString();
    }

    static const QString trueText = tr("True");
    static const QString falseText = tr("False");
    return data.val ? trueText : falseText;
}

QIcon QExtPEBoolPropertyManager::valueIcon(const QExtPEProperty *property) const
{
    const QExtPEBoolPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QIcon();
    }

    if (property->isStyleChanged())
    {
        d_ptr->m_checkedIcon = drawCheckBox(true);
        d_ptr->m_uncheckedIcon = drawCheckBox(false);
    }
    return it.value().val ? d_ptr->m_checkedIcon : d_ptr->m_uncheckedIcon;
}

void QExtPEBoolPropertyManager::setValue(QExtPEProperty *property, bool val)
{
    const QExtPEBoolPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPEBoolPropertyManagerPrivate::Data data = it.value();

    if (data.val == val)
    {
        return;
    }

    data.val = val;
    it.value() = data;

    emit this->propertyChanged(property);
    emit this->valueChanged(property, data.val);
}

void QExtPEBoolPropertyManager::setTextVisible(QExtPEProperty *property, bool textVisible)
{
    const QExtPEBoolPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPEBoolPropertyManagerPrivate::Data data = it.value();
    if (data.textVisible == textVisible)
    {
        return;
    }

    data.textVisible = textVisible;
    it.value() = data;

    emit this->propertyChanged(property);
    emit this->textVisibleChanged(property, data.textVisible);
}

void QExtPEBoolPropertyManager::initializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values[property] = QExtPEBoolPropertyManagerPrivate::Data();
}

void QExtPEBoolPropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPEDatePropertyManager
***********************************************************************************************************************/
QExtPEDatePropertyManager::QExtPEDatePropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPEDatePropertyManagerPrivate;
    d_ptr->q_ptr = this;

    QLocale loc;
    d_ptr->m_format = loc.dateFormat(QLocale::ShortFormat);
}

QExtPEDatePropertyManager::~QExtPEDatePropertyManager()
{
    this->clear();
    delete d_ptr;
}

QDate QExtPEDatePropertyManager::value(const QExtPEProperty *property) const
{
    return getValue<QDate>(d_ptr->m_values, property);
}

QDate QExtPEDatePropertyManager::minimum(const QExtPEProperty *property) const
{
    return getMinimum<QDate>(d_ptr->m_values, property);
}

QDate QExtPEDatePropertyManager::maximum(const QExtPEProperty *property) const
{
    return getMaximum<QDate>(d_ptr->m_values, property);
}

QString QExtPEDatePropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPEDatePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }
    return it.value().val.toString(d_ptr->m_format);
}

void QExtPEDatePropertyManager::setValue(QExtPEProperty *property, const QDate &val)
{
    void (QExtPEDatePropertyManagerPrivate::*setSubPropertyValue)(QExtPEProperty *, const QDate &) = QEXT_NULLPTR;
    setValueInRange<const QDate &, QExtPEDatePropertyManagerPrivate, QExtPEDatePropertyManager, const QDate>(this, d_ptr,
                                                                                                         &QExtPEDatePropertyManager::propertyChanged,
                                                                                                         &QExtPEDatePropertyManager::valueChanged,
                                                                                                         property, val, setSubPropertyValue);
}

void QExtPEDatePropertyManager::setMinimum(QExtPEProperty *property, const QDate &minVal)
{
    setMinimumValue<const QDate &, QExtPEDatePropertyManagerPrivate, QExtPEDatePropertyManager, QDate, QExtPEDatePropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                                         &QExtPEDatePropertyManager::propertyChanged,
                                                                                                                                         &QExtPEDatePropertyManager::valueChanged,
                                                                                                                                         &QExtPEDatePropertyManager::rangeChanged,
                                                                                                                                         property, minVal);
}

void QExtPEDatePropertyManager::setMaximum(QExtPEProperty *property, const QDate &maxVal)
{
    setMaximumValue<const QDate &, QExtPEDatePropertyManagerPrivate, QExtPEDatePropertyManager, QDate, QExtPEDatePropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                                         &QExtPEDatePropertyManager::propertyChanged,
                                                                                                                                         &QExtPEDatePropertyManager::valueChanged,
                                                                                                                                         &QExtPEDatePropertyManager::rangeChanged,
                                                                                                                                         property, maxVal);
}

void QExtPEDatePropertyManager::setRange(QExtPEProperty *property, const QDate &minVal, const QDate &maxVal)
{
    void (QExtPEDatePropertyManagerPrivate::*setSubPropertyRange)(QExtPEProperty *, const QDate &,
                                                                const QDate &, const QDate &) = QEXT_NULLPTR;
    setBorderValues<const QDate &, QExtPEDatePropertyManagerPrivate, QExtPEDatePropertyManager, QDate>(this, d_ptr,
                                                                                                   &QExtPEDatePropertyManager::propertyChanged,
                                                                                                   &QExtPEDatePropertyManager::valueChanged,
                                                                                                   &QExtPEDatePropertyManager::rangeChanged,
                                                                                                   property, minVal, maxVal, setSubPropertyRange);
}

void QExtPEDatePropertyManager::initializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values[property] = QExtPEDatePropertyManagerPrivate::Data();
}

void QExtPEDatePropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPETimePropertyManager
***********************************************************************************************************************/
QExtPETimePropertyManager::QExtPETimePropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPETimePropertyManagerPrivate;
    d_ptr->q_ptr = this;

    QLocale loc;
    d_ptr->m_format = loc.timeFormat(QLocale::ShortFormat);
}

QExtPETimePropertyManager::~QExtPETimePropertyManager()
{
    this->clear();
    delete d_ptr;
}

QTime QExtPETimePropertyManager::value(const QExtPEProperty *property) const
{
    return d_ptr->m_values.value(property, QTime());
}

QString QExtPETimePropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPETimePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }
    return it.value().toString(d_ptr->m_format);
}

void QExtPETimePropertyManager::setValue(QExtPEProperty *property, const QTime &val)
{
    setSimpleValue<const QTime &, QTime, QExtPETimePropertyManager>(d_ptr->m_values, this,
                                                                  &QExtPETimePropertyManager::propertyChanged,
                                                                  &QExtPETimePropertyManager::valueChanged,
                                                                  property, val);
}

void QExtPETimePropertyManager::initializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values[property] = QTime::currentTime();
}

void QExtPETimePropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPEDateTimePropertyManager
***********************************************************************************************************************/
QExtPEDateTimePropertyManager::QExtPEDateTimePropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPEDateTimePropertyManagerPrivate;
    d_ptr->q_ptr = this;

    QLocale loc;
    d_ptr->m_format = loc.dateFormat(QLocale::ShortFormat);
    d_ptr->m_format += QLatin1Char(' ');
    d_ptr->m_format += loc.timeFormat(QLocale::ShortFormat);
}

QExtPEDateTimePropertyManager::~QExtPEDateTimePropertyManager()
{
    this->clear();
    delete d_ptr;
}

QDateTime QExtPEDateTimePropertyManager::value(const QExtPEProperty *property) const
{
    return d_ptr->m_values.value(property, QDateTime());
}

QString QExtPEDateTimePropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPEDateTimePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }
    return it.value().toString(d_ptr->m_format);
}

void QExtPEDateTimePropertyManager::setValue(QExtPEProperty *property, const QDateTime &val)
{
    setSimpleValue<const QDateTime &, QDateTime, QExtPEDateTimePropertyManager>(d_ptr->m_values, this,
                                                                              &QExtPEDateTimePropertyManager::propertyChanged,
                                                                              &QExtPEDateTimePropertyManager::valueChanged,
                                                                              property, val);
}

void QExtPEDateTimePropertyManager::initializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values[property] = QDateTime::currentDateTime();
}

void QExtPEDateTimePropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPEKeySequencePropertyManager
***********************************************************************************************************************/
QExtPEKeySequencePropertyManager::QExtPEKeySequencePropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPEKeySequencePropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

QExtPEKeySequencePropertyManager::~QExtPEKeySequencePropertyManager()
{
    this->clear();
    delete d_ptr;
}

QKeySequence QExtPEKeySequencePropertyManager::value(const QExtPEProperty *property) const
{
    return d_ptr->m_values.value(property, QKeySequence());
}

QString QExtPEKeySequencePropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPEKeySequencePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }
    return it.value().toString(QKeySequence::NativeText);
}

void QExtPEKeySequencePropertyManager::setValue(QExtPEProperty *property, const QKeySequence &val)
{
    setSimpleValue<const QKeySequence &, QKeySequence, QExtPEKeySequencePropertyManager>(d_ptr->m_values, this,
                                                                                       &QExtPEKeySequencePropertyManager::propertyChanged,
                                                                                       &QExtPEKeySequencePropertyManager::valueChanged,
                                                                                       property, val);
}

void QExtPEKeySequencePropertyManager::initializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values[property] = QKeySequence();
}

void QExtPEKeySequencePropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPECharPropertyManager
***********************************************************************************************************************/
QExtPECharPropertyManager::QExtPECharPropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPECharPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

QExtPECharPropertyManager::~QExtPECharPropertyManager()
{
    clear();
    delete d_ptr;
}

QChar QExtPECharPropertyManager::value(const QExtPEProperty *property) const
{
    return d_ptr->m_values.value(property, QChar());
}

QString QExtPECharPropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPECharPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }
    const QChar c = it.value();
    return c.isNull() ? QString() : QString(c);
}

void QExtPECharPropertyManager::setValue(QExtPEProperty *property, const QChar &val)
{
    setSimpleValue<const QChar &, QChar, QExtPECharPropertyManager>(d_ptr->m_values, this,
                                                                  &QExtPECharPropertyManager::propertyChanged,
                                                                  &QExtPECharPropertyManager::valueChanged,
                                                                  property, val);
}

void QExtPECharPropertyManager::initializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values[property] = QChar();
}

void QExtPECharPropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values.remove(property);
}



/***********************************************************************************************************************
 * QExtPELocalePropertyManager
***********************************************************************************************************************/
Q_GLOBAL_STATIC(QExtPEMetaEnumProvider, sgMetaEnumProvider)

QExtPELocalePropertyManagerPrivate::QExtPELocalePropertyManagerPrivate()
{
}

void QExtPELocalePropertyManagerPrivate::slotEnumChanged(QExtPEProperty *property, int value)
{
    if (QExtPEProperty *prop = m_languageToProperty.value(property, QEXT_NULLPTR))
    {
        const QLocale loc = m_values[prop];
        QLocale::Language newLanguage = loc.language();
        QLocale::Country newCountry = loc.country();
        sgMetaEnumProvider()->indexToLocale(value, 0, &newLanguage, QEXT_NULLPTR);
        QLocale newLoc(newLanguage, newCountry);
        q_ptr->setValue(prop, newLoc);
    }
    else if (QExtPEProperty *prop = m_countryToProperty.value(property, QEXT_NULLPTR))
    {
        const QLocale loc = m_values[prop];
        QLocale::Language newLanguage = loc.language();
        QLocale::Country newCountry = loc.country();
        sgMetaEnumProvider()->indexToLocale(m_enumPropertyManager->value(m_propertyToLanguage.value(prop)), value, &newLanguage, &newCountry);
        QLocale newLoc(newLanguage, newCountry);
        q_ptr->setValue(prop, newLoc);
    }
}

void QExtPELocalePropertyManagerPrivate::slotPropertyDestroyed(QExtPEProperty *property)
{
    if (QExtPEProperty *subProp = m_languageToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToLanguage[subProp] = QEXT_NULLPTR;
        m_languageToProperty.remove(property);
    }
    else if (QExtPEProperty *subProp = m_countryToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToCountry[subProp] = QEXT_NULLPTR;
        m_countryToProperty.remove(property);
    }
}



QExtPELocalePropertyManager::QExtPELocalePropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPELocalePropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_enumPropertyManager = new QExtPEEnumPropertyManager(this);
    connect(d_ptr->m_enumPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotEnumChanged(QExtPEProperty *, int)));

    connect(d_ptr->m_enumPropertyManager, SIGNAL(propertyDestroyed(QExtPEProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtPEProperty *)));
}

QExtPELocalePropertyManager::~QExtPELocalePropertyManager()
{
    this->clear();
    delete d_ptr;
}

QExtPEEnumPropertyManager *QExtPELocalePropertyManager::subEnumPropertyManager() const
{
    return d_ptr->m_enumPropertyManager;
}

QLocale QExtPELocalePropertyManager::value(const QExtPEProperty *property) const
{
    return d_ptr->m_values.value(property, QLocale());
}

QString QExtPELocalePropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPELocalePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }

    QLocale loc = it.value();

    int langIdx = 0;
    int countryIdx = 0;
    sgMetaEnumProvider()->localeToIndex(loc.language(), loc.country(), &langIdx, &countryIdx);
    QString str = tr("%1, %2").arg(sgMetaEnumProvider()->languageEnumNames().at(langIdx))
                      .arg(sgMetaEnumProvider()->countryEnumNames(loc.language()).at(countryIdx));
    return str;
}

void QExtPELocalePropertyManager::setValue(QExtPEProperty *property, const QLocale &val)
{
    const QExtPELocalePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    const QLocale loc = it.value();
    if (loc == val)
    {
        return;
    }

    it.value() = val;

    int langIdx = 0;
    int countryIdx = 0;
    sgMetaEnumProvider()->localeToIndex(val.language(), val.country(), &langIdx, &countryIdx);
    if (loc.language() != val.language())
    {
        d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToLanguage.value(property), langIdx);
        d_ptr->m_enumPropertyManager->setEnumNames(d_ptr->m_propertyToCountry.value(property),
                                                   sgMetaEnumProvider()->countryEnumNames(val.language()));
    }
    d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToCountry.value(property), countryIdx);

    emit this->propertyChanged(property);
    emit this->valueChanged(property, val);
}

void QExtPELocalePropertyManager::initializeProperty(QExtPEProperty *property)
{
    QLocale val;
    d_ptr->m_values[property] = val;

    int langIdx = 0;
    int countryIdx = 0;
    sgMetaEnumProvider()->localeToIndex(val.language(), val.country(), &langIdx, &countryIdx);

    QExtPEProperty *languageProp = d_ptr->m_enumPropertyManager->addProperty();
    languageProp->setPropertyName(tr("Language"));
    d_ptr->m_enumPropertyManager->setEnumNames(languageProp, sgMetaEnumProvider()->languageEnumNames());
    d_ptr->m_enumPropertyManager->setValue(languageProp, langIdx);
    d_ptr->m_propertyToLanguage[property] = languageProp;
    d_ptr->m_languageToProperty[languageProp] = property;
    property->addSubProperty(languageProp);

    QExtPEProperty *countryProp = d_ptr->m_enumPropertyManager->addProperty();
    countryProp->setPropertyName(tr("Country"));
    d_ptr->m_enumPropertyManager->setEnumNames(countryProp, sgMetaEnumProvider()->countryEnumNames(val.language()));
    d_ptr->m_enumPropertyManager->setValue(countryProp, countryIdx);
    d_ptr->m_propertyToCountry[property] = countryProp;
    d_ptr->m_countryToProperty[countryProp] = property;
    property->addSubProperty(countryProp);
}

void QExtPELocalePropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    QExtPEProperty *languageProp = d_ptr->m_propertyToLanguage[property];
    if (languageProp)
    {
        d_ptr->m_languageToProperty.remove(languageProp);
        delete languageProp;
    }
    d_ptr->m_propertyToLanguage.remove(property);

    QExtPEProperty *countryProp = d_ptr->m_propertyToCountry[property];
    if (countryProp)
    {
        d_ptr->m_countryToProperty.remove(countryProp);
        delete countryProp;
    }
    d_ptr->m_propertyToCountry.remove(property);

    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPEPointPropertyManager
***********************************************************************************************************************/
void QExtPEPointPropertyManagerPrivate::slotIntChanged(QExtPEProperty *property, int value)
{
    if (QExtPEProperty *xprop = m_xToProperty.value(property, QEXT_NULLPTR))
    {
        QPoint p = m_values[xprop];
        p.setX(value);
        q_ptr->setValue(xprop, p);
    }
    else if (QExtPEProperty *yprop = m_yToProperty.value(property, QEXT_NULLPTR))
    {
        QPoint p = m_values[yprop];
        p.setY(value);
        q_ptr->setValue(yprop, p);
    }
}

void QExtPEPointPropertyManagerPrivate::slotPropertyDestroyed(QExtPEProperty *property)
{
    if (QExtPEProperty *pointProp = m_xToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToX[pointProp] = QEXT_NULLPTR;
        m_xToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_yToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToY[pointProp] = QEXT_NULLPTR;
        m_yToProperty.remove(property);
    }
}



QExtPEPointPropertyManager::QExtPEPointPropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPEPointPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new QExtPEIntPropertyManager(this);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotIntChanged(QExtPEProperty *, int)));
    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(QExtPEProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtPEProperty *)));
}

QExtPEPointPropertyManager::~QExtPEPointPropertyManager()
{
    this->clear();
    delete d_ptr;
}

QExtPEIntPropertyManager *QExtPEPointPropertyManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

QPoint QExtPEPointPropertyManager::value(const QExtPEProperty *property) const
{
    return d_ptr->m_values.value(property, QPoint());
}

QString QExtPEPointPropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPEPointPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }
    const QPoint v = it.value();
    return QString(tr("(%1, %2)").arg(QString::number(v.x())).arg(QString::number(v.y())));
}

void QExtPEPointPropertyManager::setValue(QExtPEProperty *property, const QPoint &val)
{
    const QExtPEPointPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    if (it.value() == val)
    {
        return;
    }

    it.value() = val;
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToX[property], val.x());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToY[property], val.y());

    emit this->propertyChanged(property);
    emit this->valueChanged(property, val);
}

void QExtPEPointPropertyManager::initializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values[property] = QPoint(0, 0);

    QExtPEProperty *xProp = d_ptr->m_intPropertyManager->addProperty();
    xProp->setPropertyName(tr("X"));
    d_ptr->m_intPropertyManager->setValue(xProp, 0);
    d_ptr->m_propertyToX[property] = xProp;
    d_ptr->m_xToProperty[xProp] = property;
    property->addSubProperty(xProp);

    QExtPEProperty *yProp = d_ptr->m_intPropertyManager->addProperty();
    yProp->setPropertyName(tr("Y"));
    d_ptr->m_intPropertyManager->setValue(yProp, 0);
    d_ptr->m_propertyToY[property] = yProp;
    d_ptr->m_yToProperty[yProp] = property;
    property->addSubProperty(yProp);
}

void QExtPEPointPropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    QExtPEProperty *xProp = d_ptr->m_propertyToX[property];
    if (xProp)
    {
        d_ptr->m_xToProperty.remove(xProp);
        delete xProp;
    }
    d_ptr->m_propertyToX.remove(property);

    QExtPEProperty *yProp = d_ptr->m_propertyToY[property];
    if (yProp)
    {
        d_ptr->m_yToProperty.remove(yProp);
        delete yProp;
    }
    d_ptr->m_propertyToY.remove(property);

    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPEPointFPropertyManager
***********************************************************************************************************************/
void QExtPEPointFPropertyManagerPrivate::slotDoubleChanged(QExtPEProperty *property, double value)
{
    if (QExtPEProperty *prop = m_xToProperty.value(property, QEXT_NULLPTR))
    {
        QPointF p = m_values[prop].val;
        p.setX(value);
        q_ptr->setValue(prop, p);
    }
    else if (QExtPEProperty *prop = m_yToProperty.value(property, QEXT_NULLPTR))
    {
        QPointF p = m_values[prop].val;
        p.setY(value);
        q_ptr->setValue(prop, p);
    }
}

void QExtPEPointFPropertyManagerPrivate::slotPropertyDestroyed(QExtPEProperty *property)
{
    if (QExtPEProperty *pointProp  = m_xToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToX[pointProp] = QEXT_NULLPTR;
        m_xToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_yToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToY[pointProp] = QEXT_NULLPTR;
        m_yToProperty.remove(property);
    }
}


QExtPEPointFPropertyManager::QExtPEPointFPropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPEPointFPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_doublePropertyManager = new QExtPEDoublePropertyManager(this);
    connect(d_ptr->m_doublePropertyManager, SIGNAL(valueChanged(QExtPEProperty *, double)),
            this, SLOT(slotDoubleChanged(QExtPEProperty *, double)));
    connect(d_ptr->m_doublePropertyManager, SIGNAL(propertyDestroyed(QExtPEProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtPEProperty *)));
}

QExtPEPointFPropertyManager::~QExtPEPointFPropertyManager()
{
    this->clear();
    delete d_ptr;
}

QExtPEDoublePropertyManager *QExtPEPointFPropertyManager::subDoublePropertyManager() const
{
    return d_ptr->m_doublePropertyManager;
}

QPointF QExtPEPointFPropertyManager::value(const QExtPEProperty *property) const
{
    return getValue<QPointF>(d_ptr->m_values, property);
}

int QExtPEPointFPropertyManager::decimals(const QExtPEProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QExtPEPointFPropertyManagerPrivate::Data::decimals, property, 0);
}

QString QExtPEPointFPropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPEPointFPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }
    const QPointF v = it.value().val;
    const int dec =  it.value().decimals;
    return QString(tr("(%1, %2)").arg(QString::number(v.x(), 'f', dec)).arg(QString::number(v.y(), 'f', dec)));
}

void QExtPEPointFPropertyManager::setValue(QExtPEProperty *property, const QPointF &val)
{
    const QExtPEPointFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    if (it.value().val == val)
    {
        return;
    }

    it.value().val = val;
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToX[property], val.x());
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToY[property], val.y());

    emit this->propertyChanged(property);
    emit this->valueChanged(property, val);
}

void QExtPEPointFPropertyManager::setDecimals(QExtPEProperty *property, int prec)
{
    const QExtPEPointFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPEPointFPropertyManagerPrivate::Data data = it.value();

    if (prec > 13)
    {
        prec = 13;
    }
    else if (prec < 0)
    {
        prec = 0;
    }

    if (data.decimals == prec)
    {
        return;
    }

    data.decimals = prec;
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToX[property], prec);
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToY[property], prec);

    it.value() = data;

    emit this->decimalsChanged(property, data.decimals);
}

void QExtPEPointFPropertyManager::initializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values[property] = QExtPEPointFPropertyManagerPrivate::Data();

    QExtPEProperty *xProp = d_ptr->m_doublePropertyManager->addProperty();
    xProp->setPropertyName(tr("X"));
    d_ptr->m_doublePropertyManager->setDecimals(xProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(xProp, 0);
    d_ptr->m_propertyToX[property] = xProp;
    d_ptr->m_xToProperty[xProp] = property;
    property->addSubProperty(xProp);

    QExtPEProperty *yProp = d_ptr->m_doublePropertyManager->addProperty();
    yProp->setPropertyName(tr("Y"));
    d_ptr->m_doublePropertyManager->setDecimals(yProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(yProp, 0);
    d_ptr->m_propertyToY[property] = yProp;
    d_ptr->m_yToProperty[yProp] = property;
    property->addSubProperty(yProp);
}

void QExtPEPointFPropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    QExtPEProperty *xProp = d_ptr->m_propertyToX[property];
    if (xProp)
    {
        d_ptr->m_xToProperty.remove(xProp);
        delete xProp;
    }
    d_ptr->m_propertyToX.remove(property);

    QExtPEProperty *yProp = d_ptr->m_propertyToY[property];
    if (yProp)
    {
        d_ptr->m_yToProperty.remove(yProp);
        delete yProp;
    }
    d_ptr->m_propertyToY.remove(property);

    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPESizePropertyManager
***********************************************************************************************************************/
void QExtPESizePropertyManagerPrivate::slotIntChanged(QExtPEProperty *property, int value)
{
    if (QExtPEProperty *prop = m_wToProperty.value(property, QEXT_NULLPTR))
    {
        QSize s = m_values[prop].val;
        s.setWidth(value);
        q_ptr->setValue(prop, s);
    }
    else if (QExtPEProperty *prop = m_hToProperty.value(property, QEXT_NULLPTR))
    {
        QSize s = m_values[prop].val;
        s.setHeight(value);
        q_ptr->setValue(prop, s);
    }
}

void QExtPESizePropertyManagerPrivate::slotPropertyDestroyed(QExtPEProperty *property)
{
    if (QExtPEProperty *pointProp = m_wToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToW[pointProp] = QEXT_NULLPTR;
        m_wToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_hToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToH[pointProp] = QEXT_NULLPTR;
        m_hToProperty.remove(property);
    }
}

void QExtPESizePropertyManagerPrivate::setValue(QExtPEProperty *property, const QSize &val)
{
    m_intPropertyManager->setValue(m_propertyToW.value(property), val.width());
    m_intPropertyManager->setValue(m_propertyToH.value(property), val.height());
}

void QExtPESizePropertyManagerPrivate::setRange(QExtPEProperty *property,
                                              const QSize &minVal, const QSize &maxVal, const QSize &val)
{
    QExtPEProperty *wProperty = m_propertyToW.value(property);
    QExtPEProperty *hProperty = m_propertyToH.value(property);
    m_intPropertyManager->setRange(wProperty, minVal.width(), maxVal.width());
    m_intPropertyManager->setValue(wProperty, val.width());
    m_intPropertyManager->setRange(hProperty, minVal.height(), maxVal.height());
    m_intPropertyManager->setValue(hProperty, val.height());
}


QExtPESizePropertyManager::QExtPESizePropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPESizePropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new QExtPEIntPropertyManager(this);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotIntChanged(QExtPEProperty *, int)));
    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(QExtPEProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtPEProperty *)));
}

QExtPESizePropertyManager::~QExtPESizePropertyManager()
{
    this->clear();
    delete d_ptr;
}

QExtPEIntPropertyManager *QExtPESizePropertyManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

QSize QExtPESizePropertyManager::value(const QExtPEProperty *property) const
{
    return getValue<QSize>(d_ptr->m_values, property);
}

QSize QExtPESizePropertyManager::minimum(const QExtPEProperty *property) const
{
    return getMinimum<QSize>(d_ptr->m_values, property);
}

QSize QExtPESizePropertyManager::maximum(const QExtPEProperty *property) const
{
    return getMaximum<QSize>(d_ptr->m_values, property);
}

QString QExtPESizePropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPESizePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }
    const QSize v = it.value().val;
    return QString(tr("%1 x %2").arg(QString::number(v.width())).arg(QString::number(v.height())));
}

void QExtPESizePropertyManager::setValue(QExtPEProperty *property, const QSize &val)
{
    setValueInRange<const QSize &, QExtPESizePropertyManagerPrivate, QExtPESizePropertyManager, const QSize>(this, d_ptr,
                                                                                                         &QExtPESizePropertyManager::propertyChanged,
                                                                                                         &QExtPESizePropertyManager::valueChanged,
                                                                                                         property, val, &QExtPESizePropertyManagerPrivate::setValue);
}

void QExtPESizePropertyManager::setMinimum(QExtPEProperty *property, const QSize &minVal)
{
    setBorderValue<const QSize &, QExtPESizePropertyManagerPrivate, QExtPESizePropertyManager, QSize, QExtPESizePropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                                        &QExtPESizePropertyManager::propertyChanged,
                                                                                                                                        &QExtPESizePropertyManager::valueChanged,
                                                                                                                                        &QExtPESizePropertyManager::rangeChanged,
                                                                                                                                        property,
                                                                                                                                        &QExtPESizePropertyManagerPrivate::Data::minimumValue,
                                                                                                                                        &QExtPESizePropertyManagerPrivate::Data::setMinimumValue,
                                                                                                                                        minVal, &QExtPESizePropertyManagerPrivate::setRange);
}

void QExtPESizePropertyManager::setMaximum(QExtPEProperty *property, const QSize &maxVal)
{
    setBorderValue<const QSize &, QExtPESizePropertyManagerPrivate, QExtPESizePropertyManager, QSize, QExtPESizePropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                                        &QExtPESizePropertyManager::propertyChanged,
                                                                                                                                        &QExtPESizePropertyManager::valueChanged,
                                                                                                                                        &QExtPESizePropertyManager::rangeChanged,
                                                                                                                                        property,
                                                                                                                                        &QExtPESizePropertyManagerPrivate::Data::maximumValue,
                                                                                                                                        &QExtPESizePropertyManagerPrivate::Data::setMaximumValue,
                                                                                                                                        maxVal, &QExtPESizePropertyManagerPrivate::setRange);
}

void QExtPESizePropertyManager::setRange(QExtPEProperty *property, const QSize &minVal, const QSize &maxVal)
{
    setBorderValues<const QSize &, QExtPESizePropertyManagerPrivate, QExtPESizePropertyManager, QSize>(this, d_ptr,
                                                                                                   &QExtPESizePropertyManager::propertyChanged,
                                                                                                   &QExtPESizePropertyManager::valueChanged,
                                                                                                   &QExtPESizePropertyManager::rangeChanged,
                                                                                                   property, minVal, maxVal, &QExtPESizePropertyManagerPrivate::setRange);
}

void QExtPESizePropertyManager::initializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values[property] = QExtPESizePropertyManagerPrivate::Data();

    QExtPEProperty *wProp = d_ptr->m_intPropertyManager->addProperty();
    wProp->setPropertyName(tr("Width"));
    d_ptr->m_intPropertyManager->setValue(wProp, 0);
    d_ptr->m_intPropertyManager->setMinimum(wProp, 0);
    d_ptr->m_propertyToW[property] = wProp;
    d_ptr->m_wToProperty[wProp] = property;
    property->addSubProperty(wProp);

    QExtPEProperty *hProp = d_ptr->m_intPropertyManager->addProperty();
    hProp->setPropertyName(tr("Height"));
    d_ptr->m_intPropertyManager->setValue(hProp, 0);
    d_ptr->m_intPropertyManager->setMinimum(hProp, 0);
    d_ptr->m_propertyToH[property] = hProp;
    d_ptr->m_hToProperty[hProp] = property;
    property->addSubProperty(hProp);
}

void QExtPESizePropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    QExtPEProperty *wProp = d_ptr->m_propertyToW[property];
    if (wProp)
    {
        d_ptr->m_wToProperty.remove(wProp);
        delete wProp;
    }
    d_ptr->m_propertyToW.remove(property);

    QExtPEProperty *hProp = d_ptr->m_propertyToH[property];
    if (hProp)
    {
        d_ptr->m_hToProperty.remove(hProp);
        delete hProp;
    }
    d_ptr->m_propertyToH.remove(property);

    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPESizeFPropertyManager
***********************************************************************************************************************/
void QExtPESizeFPropertyManagerPrivate::slotDoubleChanged(QExtPEProperty *property, double value)
{
    if (QExtPEProperty *prop = m_wToProperty.value(property, QEXT_NULLPTR))
    {
        QSizeF s = m_values[prop].val;
        s.setWidth(value);
        q_ptr->setValue(prop, s);
    }
    else if (QExtPEProperty *prop = m_hToProperty.value(property, QEXT_NULLPTR))
    {
        QSizeF s = m_values[prop].val;
        s.setHeight(value);
        q_ptr->setValue(prop, s);
    }
}

void QExtPESizeFPropertyManagerPrivate::slotPropertyDestroyed(QExtPEProperty *property)
{
    if (QExtPEProperty *pointProp = m_wToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToW[pointProp] = QEXT_NULLPTR;
        m_wToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_hToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToH[pointProp] = QEXT_NULLPTR;
        m_hToProperty.remove(property);
    }
}

void QExtPESizeFPropertyManagerPrivate::setValue(QExtPEProperty *property, const QSizeF &val)
{
    m_doublePropertyManager->setValue(m_propertyToW.value(property), val.width());
    m_doublePropertyManager->setValue(m_propertyToH.value(property), val.height());
}

void QExtPESizeFPropertyManagerPrivate::setRange(QExtPEProperty *property, const QSizeF &minVal, const QSizeF &maxVal,
                                               const QSizeF &val)
{
    m_doublePropertyManager->setRange(m_propertyToW[property], minVal.width(), maxVal.width());
    m_doublePropertyManager->setValue(m_propertyToW[property], val.width());
    m_doublePropertyManager->setRange(m_propertyToH[property], minVal.height(), maxVal.height());
    m_doublePropertyManager->setValue(m_propertyToH[property], val.height());
}




QExtPESizeFPropertyManager::QExtPESizeFPropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPESizeFPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_doublePropertyManager = new QExtPEDoublePropertyManager(this);
    connect(d_ptr->m_doublePropertyManager, SIGNAL(valueChanged(QExtPEProperty *, double)),
            this, SLOT(slotDoubleChanged(QExtPEProperty *, double)));
    connect(d_ptr->m_doublePropertyManager, SIGNAL(propertyDestroyed(QExtPEProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtPEProperty *)));
}

QExtPESizeFPropertyManager::~QExtPESizeFPropertyManager()
{
    this->clear();
    delete d_ptr;
}

QExtPEDoublePropertyManager *QExtPESizeFPropertyManager::subDoublePropertyManager() const
{
    return d_ptr->m_doublePropertyManager;
}

QSizeF QExtPESizeFPropertyManager::value(const QExtPEProperty *property) const
{
    return getValue<QSizeF>(d_ptr->m_values, property);
}

int QExtPESizeFPropertyManager::decimals(const QExtPEProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QExtPESizeFPropertyManagerPrivate::Data::decimals, property, 0);
}

QSizeF QExtPESizeFPropertyManager::minimum(const QExtPEProperty *property) const
{
    return getMinimum<QSizeF>(d_ptr->m_values, property);
}

QSizeF QExtPESizeFPropertyManager::maximum(const QExtPEProperty *property) const
{
    return getMaximum<QSizeF>(d_ptr->m_values, property);
}

QString QExtPESizeFPropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPESizeFPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }
    const QSizeF v = it.value().val;
    const int dec = it.value().decimals;
    return QString(tr("%1 x %2").arg(QString::number(v.width(), 'f', dec)).arg(QString::number(v.height(), 'f', dec)));
}

void QExtPESizeFPropertyManager::setValue(QExtPEProperty *property, const QSizeF &val)
{
    setValueInRange<const QSizeF &, QExtPESizeFPropertyManagerPrivate, QExtPESizeFPropertyManager, QSizeF>(this, d_ptr,
                                                                                                       &QExtPESizeFPropertyManager::propertyChanged,
                                                                                                       &QExtPESizeFPropertyManager::valueChanged,
                                                                                                       property, val, &QExtPESizeFPropertyManagerPrivate::setValue);
}

void QExtPESizeFPropertyManager::setDecimals(QExtPEProperty *property, int prec)
{
    const QExtPESizeFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPESizeFPropertyManagerPrivate::Data data = it.value();

    if (prec > 13)
    {
        prec = 13;
    }
    else if (prec < 0)
    {
        prec = 0;
    }

    if (data.decimals == prec)
    {
        return;
    }

    data.decimals = prec;
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToW[property], prec);
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToH[property], prec);

    it.value() = data;

    emit this->decimalsChanged(property, data.decimals);
}

void QExtPESizeFPropertyManager::setMinimum(QExtPEProperty *property, const QSizeF &minVal)
{
    setBorderValue<const QSizeF &, QExtPESizeFPropertyManagerPrivate, QExtPESizeFPropertyManager, QSizeF, QExtPESizeFPropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                                             &QExtPESizeFPropertyManager::propertyChanged,
                                                                                                                                             &QExtPESizeFPropertyManager::valueChanged,
                                                                                                                                             &QExtPESizeFPropertyManager::rangeChanged,
                                                                                                                                             property,
                                                                                                                                             &QExtPESizeFPropertyManagerPrivate::Data::minimumValue,
                                                                                                                                             &QExtPESizeFPropertyManagerPrivate::Data::setMinimumValue,
                                                                                                                                             minVal, &QExtPESizeFPropertyManagerPrivate::setRange);
}

void QExtPESizeFPropertyManager::setMaximum(QExtPEProperty *property, const QSizeF &maxVal)
{
    setBorderValue<const QSizeF &, QExtPESizeFPropertyManagerPrivate, QExtPESizeFPropertyManager, QSizeF, QExtPESizeFPropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                                             &QExtPESizeFPropertyManager::propertyChanged,
                                                                                                                                             &QExtPESizeFPropertyManager::valueChanged,
                                                                                                                                             &QExtPESizeFPropertyManager::rangeChanged,
                                                                                                                                             property,
                                                                                                                                             &QExtPESizeFPropertyManagerPrivate::Data::maximumValue,
                                                                                                                                             &QExtPESizeFPropertyManagerPrivate::Data::setMaximumValue,
                                                                                                                                             maxVal, &QExtPESizeFPropertyManagerPrivate::setRange);
}

void QExtPESizeFPropertyManager::setRange(QExtPEProperty *property, const QSizeF &minVal, const QSizeF &maxVal)
{
    setBorderValues<const QSizeF &, QExtPESizeFPropertyManagerPrivate, QExtPESizeFPropertyManager, QSizeF>(this, d_ptr,
                                                                                                       &QExtPESizeFPropertyManager::propertyChanged,
                                                                                                       &QExtPESizeFPropertyManager::valueChanged,
                                                                                                       &QExtPESizeFPropertyManager::rangeChanged,
                                                                                                       property, minVal, maxVal, &QExtPESizeFPropertyManagerPrivate::setRange);
}

void QExtPESizeFPropertyManager::initializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values[property] = QExtPESizeFPropertyManagerPrivate::Data();

    QExtPEProperty *wProp = d_ptr->m_doublePropertyManager->addProperty();
    wProp->setPropertyName(tr("Width"));
    d_ptr->m_doublePropertyManager->setDecimals(wProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(wProp, 0);
    d_ptr->m_doublePropertyManager->setMinimum(wProp, 0);
    d_ptr->m_propertyToW[property] = wProp;
    d_ptr->m_wToProperty[wProp] = property;
    property->addSubProperty(wProp);

    QExtPEProperty *hProp = d_ptr->m_doublePropertyManager->addProperty();
    hProp->setPropertyName(tr("Height"));
    d_ptr->m_doublePropertyManager->setDecimals(hProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(hProp, 0);
    d_ptr->m_doublePropertyManager->setMinimum(hProp, 0);
    d_ptr->m_propertyToH[property] = hProp;
    d_ptr->m_hToProperty[hProp] = property;
    property->addSubProperty(hProp);
}

void QExtPESizeFPropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    QExtPEProperty *wProp = d_ptr->m_propertyToW[property];
    if (wProp)
    {
        d_ptr->m_wToProperty.remove(wProp);
        delete wProp;
    }
    d_ptr->m_propertyToW.remove(property);

    QExtPEProperty *hProp = d_ptr->m_propertyToH[property];
    if (hProp)
    {
        d_ptr->m_hToProperty.remove(hProp);
        delete hProp;
    }
    d_ptr->m_propertyToH.remove(property);

    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPERectPropertyManager
***********************************************************************************************************************/
void QExtPERectPropertyManagerPrivate::slotIntChanged(QExtPEProperty *property, int value)
{
    if (QExtPEProperty *prop = m_xToProperty.value(property, QEXT_NULLPTR))
    {
        QRect r = m_values[prop].val;
        r.moveLeft(value);
        q_ptr->setValue(prop, r);
    }
    else if (QExtPEProperty *prop = m_yToProperty.value(property))
    {
        QRect r = m_values[prop].val;
        r.moveTop(value);
        q_ptr->setValue(prop, r);
    }
    else if (QExtPEProperty *prop = m_wToProperty.value(property, QEXT_NULLPTR))
    {
        Data data = m_values[prop];
        QRect r = data.val;
        r.setWidth(value);
        if (!data.constraint.isNull() && data.constraint.x() + data.constraint.width() < r.x() + r.width())
        {
            r.moveLeft(data.constraint.left() + data.constraint.width() - r.width());
        }
        q_ptr->setValue(prop, r);
    }
    else if (QExtPEProperty *prop = m_hToProperty.value(property, QEXT_NULLPTR))
    {
        Data data = m_values[prop];
        QRect r = data.val;
        r.setHeight(value);
        if (!data.constraint.isNull() && data.constraint.y() + data.constraint.height() < r.y() + r.height())
        {
            r.moveTop(data.constraint.top() + data.constraint.height() - r.height());
        }
        q_ptr->setValue(prop, r);
    }
}

void QExtPERectPropertyManagerPrivate::slotPropertyDestroyed(QExtPEProperty *property)
{
    if (QExtPEProperty *pointProp = m_xToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToX[pointProp] = QEXT_NULLPTR;
        m_xToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_yToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToY[pointProp] = QEXT_NULLPTR;
        m_yToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_wToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToW[pointProp] = QEXT_NULLPTR;
        m_wToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_hToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToH[pointProp] = QEXT_NULLPTR;
        m_hToProperty.remove(property);
    }
}

void QExtPERectPropertyManagerPrivate::setConstraint(QExtPEProperty *property, const QRect &constraint, const QRect &val)
{
    const bool isNull = constraint.isNull();
    const int left   = isNull ? INT_MIN : constraint.left();
    const int right  = isNull ? INT_MAX : constraint.left() + constraint.width();
    const int top    = isNull ? INT_MIN : constraint.top();
    const int bottom = isNull ? INT_MAX : constraint.top() + constraint.height();
    const int width  = isNull ? INT_MAX : constraint.width();
    const int height = isNull ? INT_MAX : constraint.height();

    m_intPropertyManager->setRange(m_propertyToX[property], left, right);
    m_intPropertyManager->setRange(m_propertyToY[property], top, bottom);
    m_intPropertyManager->setRange(m_propertyToW[property], 0, width);
    m_intPropertyManager->setRange(m_propertyToH[property], 0, height);

    m_intPropertyManager->setValue(m_propertyToX[property], val.x());
    m_intPropertyManager->setValue(m_propertyToY[property], val.y());
    m_intPropertyManager->setValue(m_propertyToW[property], val.width());
    m_intPropertyManager->setValue(m_propertyToH[property], val.height());
}



QExtPERectPropertyManager::QExtPERectPropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPERectPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new QExtPEIntPropertyManager(this);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotIntChanged(QExtPEProperty *, int)));
    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(QExtPEProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtPEProperty *)));
}

QExtPERectPropertyManager::~QExtPERectPropertyManager()
{
    this->clear();
    delete d_ptr;
}

QExtPEIntPropertyManager *QExtPERectPropertyManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

QRect QExtPERectPropertyManager::value(const QExtPEProperty *property) const
{
    return getValue<QRect>(d_ptr->m_values, property);
}

QRect QExtPERectPropertyManager::constraint(const QExtPEProperty *property) const
{
    return getData<QRect>(d_ptr->m_values, &QExtPERectPropertyManagerPrivate::Data::constraint, property, QRect());
}

QString QExtPERectPropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPERectPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }
    const QRect v = it.value().val;
    return QString(tr("[(%1, %2), %3 x %4]").arg(QString::number(v.x()))
                       .arg(QString::number(v.y()))
                       .arg(QString::number(v.width()))
                       .arg(QString::number(v.height())));
}

void QExtPERectPropertyManager::setValue(QExtPEProperty *property, const QRect &val)
{
    const QExtPERectPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPERectPropertyManagerPrivate::Data data = it.value();

    QRect newRect = val.normalized();
    if (!data.constraint.isNull() && !data.constraint.contains(newRect))
    {
        const QRect r1 = data.constraint;
        const QRect r2 = newRect;
        newRect.setLeft(qMax(r1.left(), r2.left()));
        newRect.setRight(qMin(r1.right(), r2.right()));
        newRect.setTop(qMax(r1.top(), r2.top()));
        newRect.setBottom(qMin(r1.bottom(), r2.bottom()));
        if (newRect.width() < 0 || newRect.height() < 0)
        {
            return;
        }
    }

    if (data.val == newRect)
    {
        return;
    }

    data.val = newRect;

    it.value() = data;
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToX[property], newRect.x());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToY[property], newRect.y());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToW[property], newRect.width());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToH[property], newRect.height());

    emit this->propertyChanged(property);
    emit this->valueChanged(property, data.val);
}

void QExtPERectPropertyManager::setConstraint(QExtPEProperty *property, const QRect &constraint)
{
    const QExtPERectPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPERectPropertyManagerPrivate::Data data = it.value();

    QRect newConstraint = constraint.normalized();
    if (data.constraint == newConstraint)
    {
        return;
    }

    const QRect oldVal = data.val;

    data.constraint = newConstraint;

    if (!data.constraint.isNull() && !data.constraint.contains(oldVal))
    {
        QRect r1 = data.constraint;
        QRect r2 = data.val;

        if (r2.width() > r1.width())
        {
            r2.setWidth(r1.width());
        }
        if (r2.height() > r1.height())
        {
            r2.setHeight(r1.height());
        }
        if (r2.left() < r1.left())
        {
            r2.moveLeft(r1.left());
        }
        else if (r2.right() > r1.right())
        {
            r2.moveRight(r1.right());
        }
        if (r2.top() < r1.top())
        {
            r2.moveTop(r1.top());
        }
        else if (r2.bottom() > r1.bottom())
        {
            r2.moveBottom(r1.bottom());
        }

        data.val = r2;
    }

    it.value() = data;

    emit this->constraintChanged(property, data.constraint);

    d_ptr->setConstraint(property, data.constraint, data.val);

    if (data.val == oldVal)
    {
        return;
    }

    emit this->propertyChanged(property);
    emit this->valueChanged(property, data.val);
}

void QExtPERectPropertyManager::initializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values[property] = QExtPERectPropertyManagerPrivate::Data();

    QExtPEProperty *xProp = d_ptr->m_intPropertyManager->addProperty();
    xProp->setPropertyName(tr("X"));
    d_ptr->m_intPropertyManager->setValue(xProp, 0);
    d_ptr->m_propertyToX[property] = xProp;
    d_ptr->m_xToProperty[xProp] = property;
    property->addSubProperty(xProp);

    QExtPEProperty *yProp = d_ptr->m_intPropertyManager->addProperty();
    yProp->setPropertyName(tr("Y"));
    d_ptr->m_intPropertyManager->setValue(yProp, 0);
    d_ptr->m_propertyToY[property] = yProp;
    d_ptr->m_yToProperty[yProp] = property;
    property->addSubProperty(yProp);

    QExtPEProperty *wProp = d_ptr->m_intPropertyManager->addProperty();
    wProp->setPropertyName(tr("Width"));
    d_ptr->m_intPropertyManager->setValue(wProp, 0);
    d_ptr->m_intPropertyManager->setMinimum(wProp, 0);
    d_ptr->m_propertyToW[property] = wProp;
    d_ptr->m_wToProperty[wProp] = property;
    property->addSubProperty(wProp);

    QExtPEProperty *hProp = d_ptr->m_intPropertyManager->addProperty();
    hProp->setPropertyName(tr("Height"));
    d_ptr->m_intPropertyManager->setValue(hProp, 0);
    d_ptr->m_intPropertyManager->setMinimum(hProp, 0);
    d_ptr->m_propertyToH[property] = hProp;
    d_ptr->m_hToProperty[hProp] = property;
    property->addSubProperty(hProp);
}

void QExtPERectPropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    QExtPEProperty *xProp = d_ptr->m_propertyToX[property];
    if (xProp)
    {
        d_ptr->m_xToProperty.remove(xProp);
        delete xProp;
    }
    d_ptr->m_propertyToX.remove(property);

    QExtPEProperty *yProp = d_ptr->m_propertyToY[property];
    if (yProp)
    {
        d_ptr->m_yToProperty.remove(yProp);
        delete yProp;
    }
    d_ptr->m_propertyToY.remove(property);

    QExtPEProperty *wProp = d_ptr->m_propertyToW[property];
    if (wProp)
    {
        d_ptr->m_wToProperty.remove(wProp);
        delete wProp;
    }
    d_ptr->m_propertyToW.remove(property);

    QExtPEProperty *hProp = d_ptr->m_propertyToH[property];
    if (hProp)
    {
        d_ptr->m_hToProperty.remove(hProp);
        delete hProp;
    }
    d_ptr->m_propertyToH.remove(property);

    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPERectFPropertyManager
***********************************************************************************************************************/
void QExtPERectFPropertyManagerPrivate::slotDoubleChanged(QExtPEProperty *property, double value)
{
    if (QExtPEProperty *prop = m_xToProperty.value(property, QEXT_NULLPTR))
    {
        QRectF r = m_values[prop].val;
        r.moveLeft(value);
        q_ptr->setValue(prop, r);
    }
    else if (QExtPEProperty *prop = m_yToProperty.value(property, QEXT_NULLPTR))
    {
        QRectF r = m_values[prop].val;
        r.moveTop(value);
        q_ptr->setValue(prop, r);
    }
    else if (QExtPEProperty *prop = m_wToProperty.value(property, QEXT_NULLPTR))
    {
        Data data = m_values[prop];
        QRectF r = data.val;
        r.setWidth(value);
        if (!data.constraint.isNull() && data.constraint.x() + data.constraint.width() < r.x() + r.width())
        {
            r.moveLeft(data.constraint.left() + data.constraint.width() - r.width());
        }
        q_ptr->setValue(prop, r);
    }
    else if (QExtPEProperty *prop = m_hToProperty.value(property, QEXT_NULLPTR))
    {
        Data data = m_values[prop];
        QRectF r = data.val;
        r.setHeight(value);
        if (!data.constraint.isNull() && data.constraint.y() + data.constraint.height() < r.y() + r.height())
        {
            r.moveTop(data.constraint.top() + data.constraint.height() - r.height());
        }
        q_ptr->setValue(prop, r);
    }
}

void QExtPERectFPropertyManagerPrivate::slotPropertyDestroyed(QExtPEProperty *property)
{
    if (QExtPEProperty *pointProp = m_xToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToX[pointProp] = QEXT_NULLPTR;
        m_xToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_yToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToY[pointProp] = QEXT_NULLPTR;
        m_yToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_wToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToW[pointProp] = QEXT_NULLPTR;
        m_wToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_hToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToH[pointProp] = QEXT_NULLPTR;
        m_hToProperty.remove(property);
    }
}

void QExtPERectFPropertyManagerPrivate::setConstraint(QExtPEProperty *property, const QRectF &constraint, const QRectF &val)
{
    const bool isNull = constraint.isNull();
    const float left   = isNull ? QEXT_FLOAT_MIN : constraint.left();
    const float right  = isNull ? QEXT_FLOAT_MAX : constraint.left() + constraint.width();
    const float top    = isNull ? QEXT_FLOAT_MIN : constraint.top();
    const float bottom = isNull ? QEXT_FLOAT_MAX : constraint.top() + constraint.height();
    const float width  = isNull ? QEXT_FLOAT_MAX : constraint.width();
    const float height = isNull ? QEXT_FLOAT_MAX : constraint.height();

    m_doublePropertyManager->setRange(m_propertyToX[property], left, right);
    m_doublePropertyManager->setRange(m_propertyToY[property], top, bottom);
    m_doublePropertyManager->setRange(m_propertyToW[property], 0, width);
    m_doublePropertyManager->setRange(m_propertyToH[property], 0, height);

    m_doublePropertyManager->setValue(m_propertyToX[property], val.x());
    m_doublePropertyManager->setValue(m_propertyToY[property], val.y());
    m_doublePropertyManager->setValue(m_propertyToW[property], val.width());
    m_doublePropertyManager->setValue(m_propertyToH[property], val.height());
}



QExtPERectFPropertyManager::QExtPERectFPropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPERectFPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_doublePropertyManager = new QExtPEDoublePropertyManager(this);
    connect(d_ptr->m_doublePropertyManager, SIGNAL(valueChanged(QExtPEProperty *, double)),
            this, SLOT(slotDoubleChanged(QExtPEProperty *, double)));
    connect(d_ptr->m_doublePropertyManager, SIGNAL(propertyDestroyed(QExtPEProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtPEProperty *)));
}

QExtPERectFPropertyManager::~QExtPERectFPropertyManager()
{
    this->clear();
    delete d_ptr;
}

QExtPEDoublePropertyManager *QExtPERectFPropertyManager::subDoublePropertyManager() const
{
    return d_ptr->m_doublePropertyManager;
}

QRectF QExtPERectFPropertyManager::value(const QExtPEProperty *property) const
{
    return getValue<QRectF>(d_ptr->m_values, property);
}

int QExtPERectFPropertyManager::decimals(const QExtPEProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QExtPERectFPropertyManagerPrivate::Data::decimals, property, 0);
}

QRectF QExtPERectFPropertyManager::constraint(const QExtPEProperty *property) const
{
    return getData<QRectF>(d_ptr->m_values, &QExtPERectFPropertyManagerPrivate::Data::constraint, property, QRect());
}

QString QExtPERectFPropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPERectFPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }
    const QRectF v = it.value().val;
    const int dec = it.value().decimals;
    return QString(tr("[(%1, %2), %3 x %4]").arg(QString::number(v.x(), 'f', dec))
                       .arg(QString::number(v.y(), 'f', dec))
                       .arg(QString::number(v.width(), 'f', dec))
                       .arg(QString::number(v.height(), 'f', dec)));
}

void QExtPERectFPropertyManager::setValue(QExtPEProperty *property, const QRectF &val)
{
    const QExtPERectFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPERectFPropertyManagerPrivate::Data data = it.value();

    QRectF newRect = val.normalized();
    if (!data.constraint.isNull() && !data.constraint.contains(newRect))
    {
        const QRectF r1 = data.constraint;
        const QRectF r2 = newRect;
        newRect.setLeft(qMax(r1.left(), r2.left()));
        newRect.setRight(qMin(r1.right(), r2.right()));
        newRect.setTop(qMax(r1.top(), r2.top()));
        newRect.setBottom(qMin(r1.bottom(), r2.bottom()));
        if (newRect.width() < 0 || newRect.height() < 0)
        {
            return;
        }
    }

    if (data.val == newRect)
    {
        return;
    }

    data.val = newRect;

    it.value() = data;
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToX[property], newRect.x());
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToY[property], newRect.y());
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToW[property], newRect.width());
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToH[property], newRect.height());

    emit this->propertyChanged(property);
    emit this->valueChanged(property, data.val);
}

void QExtPERectFPropertyManager::setConstraint(QExtPEProperty *property, const QRectF &constraint)
{
    const QExtPERectFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPERectFPropertyManagerPrivate::Data data = it.value();
    QRectF newConstraint = constraint.normalized();
    if (data.constraint == newConstraint)
    {
        return;
    }

    const QRectF oldVal = data.val;

    data.constraint = newConstraint;
    if (!data.constraint.isNull() && !data.constraint.contains(oldVal))
    {
        QRectF r1 = data.constraint;
        QRectF r2 = data.val;

        if (r2.width() > r1.width())
        {
            r2.setWidth(r1.width());
        }
        if (r2.height() > r1.height())
        {
            r2.setHeight(r1.height());
        }
        if (r2.left() < r1.left())
        {
            r2.moveLeft(r1.left());
        }
        else if (r2.right() > r1.right())
        {
            r2.moveRight(r1.right());
        }
        if (r2.top() < r1.top())
        {
            r2.moveTop(r1.top());
        }
        else if (r2.bottom() > r1.bottom())
        {
            r2.moveBottom(r1.bottom());
        }

        data.val = r2;
    }

    it.value() = data;

    emit this->constraintChanged(property, data.constraint);

    d_ptr->setConstraint(property, data.constraint, data.val);

    if (data.val == oldVal)
    {
        return;
    }

    emit this->propertyChanged(property);
    emit this->valueChanged(property, data.val);
}

void QExtPERectFPropertyManager::setDecimals(QExtPEProperty *property, int prec)
{
    const QExtPERectFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPERectFPropertyManagerPrivate::Data data = it.value();

    if (prec > 13)
    {
        prec = 13;
    }
    else if (prec < 0)
    {
        prec = 0;
    }

    if (data.decimals == prec)
    {
        return;
    }

    data.decimals = prec;
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToX[property], prec);
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToY[property], prec);
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToW[property], prec);
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToH[property], prec);

    it.value() = data;

    emit this->decimalsChanged(property, data.decimals);
}

void QExtPERectFPropertyManager::initializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values[property] = QExtPERectFPropertyManagerPrivate::Data();

    QExtPEProperty *xProp = d_ptr->m_doublePropertyManager->addProperty();
    xProp->setPropertyName(tr("X"));
    d_ptr->m_doublePropertyManager->setDecimals(xProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(xProp, 0);
    d_ptr->m_propertyToX[property] = xProp;
    d_ptr->m_xToProperty[xProp] = property;
    property->addSubProperty(xProp);

    QExtPEProperty *yProp = d_ptr->m_doublePropertyManager->addProperty();
    yProp->setPropertyName(tr("Y"));
    d_ptr->m_doublePropertyManager->setDecimals(yProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(yProp, 0);
    d_ptr->m_propertyToY[property] = yProp;
    d_ptr->m_yToProperty[yProp] = property;
    property->addSubProperty(yProp);

    QExtPEProperty *wProp = d_ptr->m_doublePropertyManager->addProperty();
    wProp->setPropertyName(tr("Width"));
    d_ptr->m_doublePropertyManager->setDecimals(wProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(wProp, 0);
    d_ptr->m_doublePropertyManager->setMinimum(wProp, 0);
    d_ptr->m_propertyToW[property] = wProp;
    d_ptr->m_wToProperty[wProp] = property;
    property->addSubProperty(wProp);

    QExtPEProperty *hProp = d_ptr->m_doublePropertyManager->addProperty();
    hProp->setPropertyName(tr("Height"));
    d_ptr->m_doublePropertyManager->setDecimals(hProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(hProp, 0);
    d_ptr->m_doublePropertyManager->setMinimum(hProp, 0);
    d_ptr->m_propertyToH[property] = hProp;
    d_ptr->m_hToProperty[hProp] = property;
    property->addSubProperty(hProp);
}

void QExtPERectFPropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    QExtPEProperty *xProp = d_ptr->m_propertyToX[property];
    if (xProp)
    {
        d_ptr->m_xToProperty.remove(xProp);
        delete xProp;
    }
    d_ptr->m_propertyToX.remove(property);

    QExtPEProperty *yProp = d_ptr->m_propertyToY[property];
    if (yProp)
    {
        d_ptr->m_yToProperty.remove(yProp);
        delete yProp;
    }
    d_ptr->m_propertyToY.remove(property);

    QExtPEProperty *wProp = d_ptr->m_propertyToW[property];
    if (wProp)
    {
        d_ptr->m_wToProperty.remove(wProp);
        delete wProp;
    }
    d_ptr->m_propertyToW.remove(property);

    QExtPEProperty *hProp = d_ptr->m_propertyToH[property];
    if (hProp)
    {
        d_ptr->m_hToProperty.remove(hProp);
        delete hProp;
    }
    d_ptr->m_propertyToH.remove(property);

    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPEEnumPropertyManager
***********************************************************************************************************************/
QExtPEEnumPropertyManager::QExtPEEnumPropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPEEnumPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

QExtPEEnumPropertyManager::~QExtPEEnumPropertyManager()
{
    this->clear();
    delete d_ptr;
}

int QExtPEEnumPropertyManager::value(const QExtPEProperty *property) const
{
    return getValue<int>(d_ptr->m_values, property, -1);
}

QStringList QExtPEEnumPropertyManager::enumNames(const QExtPEProperty *property) const
{
    return getData<QStringList>(d_ptr->m_values, &QExtPEEnumPropertyManagerPrivate::Data::enumNames, property, QStringList());
}

QMap<int, QIcon> QExtPEEnumPropertyManager::enumIcons(const QExtPEProperty *property) const
{
    return getData<QMap<int, QIcon> >(d_ptr->m_values, &QExtPEEnumPropertyManagerPrivate::Data::enumIcons, property, QMap<int, QIcon>());
}

QString QExtPEEnumPropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPEEnumPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }

    const QExtPEEnumPropertyManagerPrivate::Data &data = it.value();

    const int v = data.val;
    if (v >= 0 && v < data.enumNames.count())
    {
        return data.enumNames.at(v);
    }
    return QString();
}

QIcon QExtPEEnumPropertyManager::valueIcon(const QExtPEProperty *property) const
{
    const QExtPEEnumPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QIcon();
    }

    const QExtPEEnumPropertyManagerPrivate::Data &data = it.value();

    const int v = data.val;
    return data.enumIcons.value(v);
}

void QExtPEEnumPropertyManager::setValue(QExtPEProperty *property, int val)
{
    const QExtPEEnumPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPEEnumPropertyManagerPrivate::Data data = it.value();

    if (val >= data.enumNames.count())
    {
        return;
    }

    if (val < 0 && data.enumNames.count() > 0)
    {
        return;
    }

    if (val < 0)
    {
        val = -1;
    }

    if (data.val == val)
    {
        return;
    }

    data.val = val;

    it.value() = data;

    emit this->propertyChanged(property);
    emit this->valueChanged(property, data.val);
}

void QExtPEEnumPropertyManager::setEnumNames(QExtPEProperty *property, const QStringList &enumNames)
{
    const QExtPEEnumPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPEEnumPropertyManagerPrivate::Data data = it.value();

    if (data.enumNames == enumNames)
    {
        return;
    }

    data.enumNames = enumNames;

    data.val = -1;

    if (enumNames.count() > 0)
    {
        data.val = 0;
    }

    it.value() = data;

    emit this->enumNamesChanged(property, data.enumNames);
    emit this->propertyChanged(property);
    emit this->valueChanged(property, data.val);
}

void QExtPEEnumPropertyManager::setEnumIcons(QExtPEProperty *property, const QMap<int, QIcon> &enumIcons)
{
    const QExtPEEnumPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    it.value().enumIcons = enumIcons;

    emit this->enumIconsChanged(property, it.value().enumIcons);
    emit this->propertyChanged(property);
}

void QExtPEEnumPropertyManager::initializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values[property] = QExtPEEnumPropertyManagerPrivate::Data();
}

void QExtPEEnumPropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPEFlagPropertyManager
***********************************************************************************************************************/
void QExtPEFlagPropertyManagerPrivate::slotBoolChanged(QExtPEProperty *property, bool value)
{
    QExtPEProperty *prop = m_flagToProperty.value(property, QEXT_NULLPTR);
    if (!prop)
    {
        return;
    }

    QListIterator<QExtPEProperty *> itProp(m_propertyToFlags[prop]);
    int level = 0;
    while (itProp.hasNext())
    {
        QExtPEProperty *p = itProp.next();
        if (p == property)
        {
            int v = m_values[prop].val;
            if (value)
            {
                v |= (1 << level);
            }
            else
            {
                v &= ~(1 << level);
            }
            q_ptr->setValue(prop, v);
            return;
        }
        level++;
    }
}

void QExtPEFlagPropertyManagerPrivate::slotPropertyDestroyed(QExtPEProperty *property)
{
    QExtPEProperty *flagProperty = m_flagToProperty.value(property, QEXT_NULLPTR);
    if (!flagProperty)
    {
        return;
    }

    m_propertyToFlags[flagProperty].replace(m_propertyToFlags[flagProperty].indexOf(property), 0);
    m_flagToProperty.remove(property);
}



QExtPEFlagPropertyManager::QExtPEFlagPropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPEFlagPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_boolPropertyManager = new QExtPEBoolPropertyManager(this);
    connect(d_ptr->m_boolPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, bool)),
            this, SLOT(slotBoolChanged(QExtPEProperty *, bool)));
    connect(d_ptr->m_boolPropertyManager, SIGNAL(propertyDestroyed(QExtPEProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtPEProperty *)));
}

QExtPEFlagPropertyManager::~QExtPEFlagPropertyManager()
{
    this->clear();
    delete d_ptr;
}

QExtPEBoolPropertyManager *QExtPEFlagPropertyManager::subBoolPropertyManager() const
{
    return d_ptr->m_boolPropertyManager;
}

int QExtPEFlagPropertyManager::value(const QExtPEProperty *property) const
{
    return getValue<int>(d_ptr->m_values, property, 0);
}

QStringList QExtPEFlagPropertyManager::flagNames(const QExtPEProperty *property) const
{
    return getData<QStringList>(d_ptr->m_values, &QExtPEFlagPropertyManagerPrivate::Data::flagNames, property, QStringList());
}

QString QExtPEFlagPropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPEFlagPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }

    const QExtPEFlagPropertyManagerPrivate::Data &data = it.value();

    QString str;
    int level = 0;
    const QChar bar = QLatin1Char('|');
    const QStringList::const_iterator fncend = data.flagNames.constEnd();
    for (QStringList::const_iterator it =  data.flagNames.constBegin(); it != fncend; ++it)
    {
        if (data.val & (1 << level))
        {
            if (!str.isEmpty())
            {
                str += bar;
            }
            str += *it;
        }
        level++;
    }
    return str;
}

void QExtPEFlagPropertyManager::setValue(QExtPEProperty *property, int val)
{
    const QExtPEFlagPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPEFlagPropertyManagerPrivate::Data data = it.value();

    if (data.val == val)
    {
        return;
    }

    if (val > (1 << data.flagNames.count()) - 1)
    {
        return;
    }

    if (val < 0)
    {
        return;
    }

    data.val = val;

    it.value() = data;

    QListIterator<QExtPEProperty *> itProp(d_ptr->m_propertyToFlags[property]);
    int level = 0;
    while (itProp.hasNext())
    {
        QExtPEProperty *prop = itProp.next();
        if (prop)
        {
            d_ptr->m_boolPropertyManager->setValue(prop, val & (1 << level));
        }
        level++;
    }

    emit this->propertyChanged(property);
    emit this->valueChanged(property, data.val);
}

void QExtPEFlagPropertyManager::setFlagNames(QExtPEProperty *property, const QStringList &flagNames)
{
    const QExtPEFlagPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtPEFlagPropertyManagerPrivate::Data data = it.value();
    if (data.flagNames == flagNames)
    {
        return;
    }

    data.flagNames = flagNames;
    data.val = 0;

    it.value() = data;

    QListIterator<QExtPEProperty *> itProp(d_ptr->m_propertyToFlags[property]);
    while (itProp.hasNext())
    {
        QExtPEProperty *prop = itProp.next();
        if (prop)
        {
            d_ptr->m_flagToProperty.remove(prop);
            delete prop;
        }
    }
    d_ptr->m_propertyToFlags[property].clear();

    QStringListIterator itFlag(flagNames);
    while (itFlag.hasNext())
    {
        const QString flagName = itFlag.next();
        QExtPEProperty *prop = d_ptr->m_boolPropertyManager->addProperty();
        prop->setPropertyName(flagName);
        property->addSubProperty(prop);
        d_ptr->m_propertyToFlags[property].append(prop);
        d_ptr->m_flagToProperty[prop] = property;
    }

    emit this->flagNamesChanged(property, data.flagNames);
    emit this->propertyChanged(property);
    emit this->valueChanged(property, data.val);
}

void QExtPEFlagPropertyManager::initializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values[property] = QExtPEFlagPropertyManagerPrivate::Data();
    d_ptr->m_propertyToFlags[property] = QList<QExtPEProperty *>();
}

void QExtPEFlagPropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    QListIterator<QExtPEProperty *> itProp(d_ptr->m_propertyToFlags[property]);
    while (itProp.hasNext())
    {
        QExtPEProperty *prop = itProp.next();
        if (prop)
        {
            d_ptr->m_flagToProperty.remove(prop);
            delete prop;
        }
    }
    d_ptr->m_propertyToFlags.remove(property);
    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPESizePolicyPropertyManager
***********************************************************************************************************************/
QExtPESizePolicyPropertyManagerPrivate::QExtPESizePolicyPropertyManagerPrivate()
{
}

void QExtPESizePolicyPropertyManagerPrivate::slotIntChanged(QExtPEProperty *property, int value)
{
    if (QExtPEProperty *prop = m_hStretchToProperty.value(property, QEXT_NULLPTR))
    {
        QSizePolicy sp = m_values[prop];
        sp.setHorizontalStretch(value);
        q_ptr->setValue(prop, sp);
    }
    else if (QExtPEProperty *prop = m_vStretchToProperty.value(property, QEXT_NULLPTR))
    {
        QSizePolicy sp = m_values[prop];
        sp.setVerticalStretch(value);
        q_ptr->setValue(prop, sp);
    }
}

void QExtPESizePolicyPropertyManagerPrivate::slotEnumChanged(QExtPEProperty *property, int value)
{
    if (QExtPEProperty *prop = m_hPolicyToProperty.value(property, QEXT_NULLPTR))
    {
        QSizePolicy sp = m_values[prop];
        sp.setHorizontalPolicy(sgMetaEnumProvider()->indexToSizePolicy(value));
        q_ptr->setValue(prop, sp);
    }
    else if (QExtPEProperty *prop = m_vPolicyToProperty.value(property, QEXT_NULLPTR))
    {
        QSizePolicy sp = m_values[prop];
        sp.setVerticalPolicy(sgMetaEnumProvider()->indexToSizePolicy(value));
        q_ptr->setValue(prop, sp);
    }
}

void QExtPESizePolicyPropertyManagerPrivate::slotPropertyDestroyed(QExtPEProperty *property)
{
    if (QExtPEProperty *pointProp = m_hStretchToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToHStretch[pointProp] = QEXT_NULLPTR;
        m_hStretchToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_vStretchToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToVStretch[pointProp] = QEXT_NULLPTR;
        m_vStretchToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_hPolicyToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToHPolicy[pointProp] = QEXT_NULLPTR;
        m_hPolicyToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_vPolicyToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToVPolicy[pointProp] = QEXT_NULLPTR;
        m_vPolicyToProperty.remove(property);
    }
}



QExtPESizePolicyPropertyManager::QExtPESizePolicyPropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPESizePolicyPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new QExtPEIntPropertyManager(this);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotIntChanged(QExtPEProperty *, int)));
    d_ptr->m_enumPropertyManager = new QExtPEEnumPropertyManager(this);
    connect(d_ptr->m_enumPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotEnumChanged(QExtPEProperty *, int)));

    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(QExtPEProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtPEProperty *)));
    connect(d_ptr->m_enumPropertyManager, SIGNAL(propertyDestroyed(QExtPEProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtPEProperty *)));
}

QExtPESizePolicyPropertyManager::~QExtPESizePolicyPropertyManager()
{
    this->clear();
    delete d_ptr;
}

QExtPEIntPropertyManager *QExtPESizePolicyPropertyManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

QExtPEEnumPropertyManager *QExtPESizePolicyPropertyManager::subEnumPropertyManager() const
{
    return d_ptr->m_enumPropertyManager;
}

QSizePolicy QExtPESizePolicyPropertyManager::value(const QExtPEProperty *property) const
{
    return d_ptr->m_values.value(property, QSizePolicy());
}

QString QExtPESizePolicyPropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPESizePolicyPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }

    const QSizePolicy sp = it.value();
    const QExtPEMetaEnumProvider *mep = sgMetaEnumProvider();
    const int hIndex = mep->sizePolicyToIndex(sp.horizontalPolicy());
    const int vIndex = mep->sizePolicyToIndex(sp.verticalPolicy());
    //! Unknown size policy on reading invalid uic3 files
    const QString hPolicy = hIndex != -1 ? mep->policyEnumNames().at(hIndex) : tr("<Invalid>");
    const QString vPolicy = vIndex != -1 ? mep->policyEnumNames().at(vIndex) : tr("<Invalid>");
    const QString str = tr("[%1, %2, %3, %4]").arg(hPolicy, vPolicy).arg(sp.horizontalStretch()).arg(sp.verticalStretch());
    return str;
}

void QExtPESizePolicyPropertyManager::setValue(QExtPEProperty *property, const QSizePolicy &val)
{
    const QExtPESizePolicyPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    if (it.value() == val)
    {
        return;
    }

    it.value() = val;

    d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToHPolicy[property],
                                           sgMetaEnumProvider()->sizePolicyToIndex(val.horizontalPolicy()));
    d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToVPolicy[property],
                                           sgMetaEnumProvider()->sizePolicyToIndex(val.verticalPolicy()));
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToHStretch[property],
                                          val.horizontalStretch());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToVStretch[property],
                                          val.verticalStretch());

    emit this->propertyChanged(property);
    emit this->valueChanged(property, val);
}

void QExtPESizePolicyPropertyManager::initializeProperty(QExtPEProperty *property)
{
    QSizePolicy val;
    d_ptr->m_values[property] = val;

    QExtPEProperty *hPolicyProp = d_ptr->m_enumPropertyManager->addProperty();
    hPolicyProp->setPropertyName(tr("Horizontal Policy"));
    d_ptr->m_enumPropertyManager->setEnumNames(hPolicyProp, sgMetaEnumProvider()->policyEnumNames());
    d_ptr->m_enumPropertyManager->setValue(hPolicyProp, sgMetaEnumProvider()->sizePolicyToIndex(val.horizontalPolicy()));
    d_ptr->m_propertyToHPolicy[property] = hPolicyProp;
    d_ptr->m_hPolicyToProperty[hPolicyProp] = property;
    property->addSubProperty(hPolicyProp);

    QExtPEProperty *vPolicyProp = d_ptr->m_enumPropertyManager->addProperty();
    vPolicyProp->setPropertyName(tr("Vertical Policy"));
    d_ptr->m_enumPropertyManager->setEnumNames(vPolicyProp, sgMetaEnumProvider()->policyEnumNames());
    d_ptr->m_enumPropertyManager->setValue(vPolicyProp, sgMetaEnumProvider()->sizePolicyToIndex(val.verticalPolicy()));
    d_ptr->m_propertyToVPolicy[property] = vPolicyProp;
    d_ptr->m_vPolicyToProperty[vPolicyProp] = property;
    property->addSubProperty(vPolicyProp);

    QExtPEProperty *hStretchProp = d_ptr->m_intPropertyManager->addProperty();
    hStretchProp->setPropertyName(tr("Horizontal Stretch"));
    d_ptr->m_intPropertyManager->setValue(hStretchProp, val.horizontalStretch());
    d_ptr->m_intPropertyManager->setRange(hStretchProp, 0, 0xff);
    d_ptr->m_propertyToHStretch[property] = hStretchProp;
    d_ptr->m_hStretchToProperty[hStretchProp] = property;
    property->addSubProperty(hStretchProp);

    QExtPEProperty *vStretchProp = d_ptr->m_intPropertyManager->addProperty();
    vStretchProp->setPropertyName(tr("Vertical Stretch"));
    d_ptr->m_intPropertyManager->setValue(vStretchProp, val.verticalStretch());
    d_ptr->m_intPropertyManager->setRange(vStretchProp, 0, 0xff);
    d_ptr->m_propertyToVStretch[property] = vStretchProp;
    d_ptr->m_vStretchToProperty[vStretchProp] = property;
    property->addSubProperty(vStretchProp);

}

void QExtPESizePolicyPropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    QExtPEProperty *hPolicyProp = d_ptr->m_propertyToHPolicy[property];
    if (hPolicyProp)
    {
        d_ptr->m_hPolicyToProperty.remove(hPolicyProp);
        delete hPolicyProp;
    }
    d_ptr->m_propertyToHPolicy.remove(property);

    QExtPEProperty *vPolicyProp = d_ptr->m_propertyToVPolicy[property];
    if (vPolicyProp)
    {
        d_ptr->m_vPolicyToProperty.remove(vPolicyProp);
        delete vPolicyProp;
    }
    d_ptr->m_propertyToVPolicy.remove(property);

    QExtPEProperty *hStretchProp = d_ptr->m_propertyToHStretch[property];
    if (hStretchProp)
    {
        d_ptr->m_hStretchToProperty.remove(hStretchProp);
        delete hStretchProp;
    }
    d_ptr->m_propertyToHStretch.remove(property);

    QExtPEProperty *vStretchProp = d_ptr->m_propertyToVStretch[property];
    if (vStretchProp)
    {
        d_ptr->m_vStretchToProperty.remove(vStretchProp);
        delete vStretchProp;
    }
    d_ptr->m_propertyToVStretch.remove(property);

    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPEFontPropertyManager
***********************************************************************************************************************/
/**
 * QExtPEFontPropertyManagerPrivate has a mechanism for reacting to QApplication::fontDatabaseChanged() [4.5],
 * which is emitted when someone loads an application font. The signals are compressed using a timer with interval 0,
 * which then causes the family enumeration manager to re-set its strings and index values for each property.
 */
Q_GLOBAL_STATIC(QFontDatabase, fontDatabase)


QExtPEFontPropertyManagerPrivate::QExtPEFontPropertyManagerPrivate()
    : m_settingValue(false)
    , m_fontDatabaseChangeTimer(QEXT_NULLPTR)
{
}

void QExtPEFontPropertyManagerPrivate::slotIntChanged(QExtPEProperty *property, int value)
{
    if (m_settingValue)
    {
        return;
    }
    if (QExtPEProperty *prop = m_pointSizeToProperty.value(property, QEXT_NULLPTR))
    {
        QFont f = m_values[prop];
        f.setPointSize(value);
        q_ptr->setValue(prop, f);
    }
}

void QExtPEFontPropertyManagerPrivate::slotEnumChanged(QExtPEProperty *property, int value)
{
    if (m_settingValue)
    {
        return;
    }
    if (QExtPEProperty *prop = m_familyToProperty.value(property, QEXT_NULLPTR))
    {
        QFont f = m_values[prop];
        f.setFamily(m_familyNames.at(value));
        q_ptr->setValue(prop, f);
    }
}

void QExtPEFontPropertyManagerPrivate::slotBoolChanged(QExtPEProperty *property, bool value)
{
    if (m_settingValue)
    {
        return;
    }
    if (QExtPEProperty *prop = m_boldToProperty.value(property, QEXT_NULLPTR))
    {
        QFont f = m_values[prop];
        f.setBold(value);
        q_ptr->setValue(prop, f);
    }
    else if (QExtPEProperty *prop = m_italicToProperty.value(property, QEXT_NULLPTR))
    {
        QFont f = m_values[prop];
        f.setItalic(value);
        q_ptr->setValue(prop, f);
    }
    else if (QExtPEProperty *prop = m_underlineToProperty.value(property, QEXT_NULLPTR))
    {
        QFont f = m_values[prop];
        f.setUnderline(value);
        q_ptr->setValue(prop, f);
    }
    else if (QExtPEProperty *prop = m_strikeOutToProperty.value(property, QEXT_NULLPTR))
    {
        QFont f = m_values[prop];
        f.setStrikeOut(value);
        q_ptr->setValue(prop, f);
    }
    else if (QExtPEProperty *prop = m_kerningToProperty.value(property, QEXT_NULLPTR))
    {
        QFont f = m_values[prop];
        f.setKerning(value);
        q_ptr->setValue(prop, f);
    }
}

void QExtPEFontPropertyManagerPrivate::slotPropertyDestroyed(QExtPEProperty *property)
{
    if (QExtPEProperty *pointProp = m_pointSizeToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToPointSize[pointProp] = QEXT_NULLPTR;
        m_pointSizeToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_familyToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToFamily[pointProp] = QEXT_NULLPTR;
        m_familyToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_boldToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToBold[pointProp] = QEXT_NULLPTR;
        m_boldToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_italicToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToItalic[pointProp] = QEXT_NULLPTR;
        m_italicToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_underlineToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToUnderline[pointProp] = QEXT_NULLPTR;
        m_underlineToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_strikeOutToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToStrikeOut[pointProp] = QEXT_NULLPTR;
        m_strikeOutToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_kerningToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToKerning[pointProp] = QEXT_NULLPTR;
        m_kerningToProperty.remove(property);
    }
}

void  QExtPEFontPropertyManagerPrivate::slotFontDatabaseChanged()
{
    if (!m_fontDatabaseChangeTimer)
    {
        m_fontDatabaseChangeTimer = new QTimer(q_ptr);
        m_fontDatabaseChangeTimer->setInterval(0);
        m_fontDatabaseChangeTimer->setSingleShot(true);
        QObject::connect(m_fontDatabaseChangeTimer, SIGNAL(timeout()), q_ptr, SLOT(slotFontDatabaseDelayedChange()));
    }
    if (!m_fontDatabaseChangeTimer->isActive())
    {
        m_fontDatabaseChangeTimer->start();
    }
}

void QExtPEFontPropertyManagerPrivate::slotFontDatabaseDelayedChange()
{
    typedef QMap<const QExtPEProperty *, QExtPEProperty *> PropertyPropertyMap;
    // rescan available font names
    const QStringList oldFamilies = m_familyNames;
    m_familyNames = fontDatabase()->families();

    // Adapt all existing properties
    if (!m_propertyToFamily.empty())
    {
        PropertyPropertyMap::const_iterator cend = m_propertyToFamily.constEnd();
        for (PropertyPropertyMap::const_iterator it = m_propertyToFamily.constBegin(); it != cend; ++it)
        {
            QExtPEProperty *familyProp = it.value();
            const int oldIdx = m_enumPropertyManager->value(familyProp);
            int newIdx = m_familyNames.indexOf(oldFamilies.at(oldIdx));
            if (newIdx < 0)
            {
                newIdx = 0;
            }
            m_enumPropertyManager->setEnumNames(familyProp, m_familyNames);
            m_enumPropertyManager->setValue(familyProp, newIdx);
        }
    }
}



QExtPEFontPropertyManager::QExtPEFontPropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPEFontPropertyManagerPrivate;
    d_ptr->q_ptr = this;
#if QT_VERSION >= 0x040500
    QObject::connect(qApp, SIGNAL(fontDatabaseChanged()), this, SLOT(slotFontDatabaseChanged()));
#endif

    d_ptr->m_intPropertyManager = new QExtPEIntPropertyManager(this);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotIntChanged(QExtPEProperty *, int)));
    d_ptr->m_enumPropertyManager = new QExtPEEnumPropertyManager(this);
    connect(d_ptr->m_enumPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotEnumChanged(QExtPEProperty *, int)));
    d_ptr->m_boolPropertyManager = new QExtPEBoolPropertyManager(this);
    connect(d_ptr->m_boolPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, bool)),
            this, SLOT(slotBoolChanged(QExtPEProperty *, bool)));

    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(QExtPEProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtPEProperty *)));
    connect(d_ptr->m_enumPropertyManager, SIGNAL(propertyDestroyed(QExtPEProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtPEProperty *)));
    connect(d_ptr->m_boolPropertyManager, SIGNAL(propertyDestroyed(QExtPEProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtPEProperty *)));
}

QExtPEFontPropertyManager::~QExtPEFontPropertyManager()
{
    this->clear();
    delete d_ptr;
}

QExtPEIntPropertyManager *QExtPEFontPropertyManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

QExtPEEnumPropertyManager *QExtPEFontPropertyManager::subEnumPropertyManager() const
{
    return d_ptr->m_enumPropertyManager;
}

QExtPEBoolPropertyManager *QExtPEFontPropertyManager::subBoolPropertyManager() const
{
    return d_ptr->m_boolPropertyManager;
}

QFont QExtPEFontPropertyManager::value(const QExtPEProperty *property) const
{
    return d_ptr->m_values.value(property, QFont());
}

QString QExtPEFontPropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPEFontPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }

    return QExtPropertyBrowserUtils::fontValueText(it.value());
}

QIcon QExtPEFontPropertyManager::valueIcon(const QExtPEProperty *property) const
{
    const QExtPEFontPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QIcon();
    }

    return QExtPropertyBrowserUtils::fontValueIcon(it.value());
}

void QExtPEFontPropertyManager::setValue(QExtPEProperty *property, const QFont &val)
{
    const QExtPEFontPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    const QFont oldVal = it.value();
    if (oldVal == val && oldVal.resolve() == val.resolve())
    {
        return;
    }

    it.value() = val;

    int idx = d_ptr->m_familyNames.indexOf(val.family());
    if (idx == -1)
    {
        idx = 0;
    }
    bool settingValue = d_ptr->m_settingValue;
    d_ptr->m_settingValue = true;
    d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToFamily[property], idx);
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToPointSize[property], val.pointSize());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToBold[property], val.bold());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToItalic[property], val.italic());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToUnderline[property], val.underline());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToStrikeOut[property], val.strikeOut());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToKerning[property], val.kerning());
    d_ptr->m_settingValue = settingValue;

    emit this->propertyChanged(property);
    emit this->valueChanged(property, val);
}

void QExtPEFontPropertyManager::initializeProperty(QExtPEProperty *property)
{
    QFont val;
    d_ptr->m_values[property] = val;

    QExtPEProperty *familyProp = d_ptr->m_enumPropertyManager->addProperty();
    familyProp->setPropertyName(tr("Family"));
    if (d_ptr->m_familyNames.empty())
    {
        d_ptr->m_familyNames = fontDatabase()->families();
    }
    d_ptr->m_enumPropertyManager->setEnumNames(familyProp, d_ptr->m_familyNames);
    int idx = d_ptr->m_familyNames.indexOf(val.family());
    if (idx == -1)
    {
        idx = 0;
    }
    d_ptr->m_enumPropertyManager->setValue(familyProp, idx);
    d_ptr->m_propertyToFamily[property] = familyProp;
    d_ptr->m_familyToProperty[familyProp] = property;
    property->addSubProperty(familyProp);

    QExtPEProperty *pointSizeProp = d_ptr->m_intPropertyManager->addProperty();
    pointSizeProp->setPropertyName(tr("Point Size"));
    d_ptr->m_intPropertyManager->setValue(pointSizeProp, val.pointSize());
    d_ptr->m_intPropertyManager->setMinimum(pointSizeProp, 1);
    d_ptr->m_propertyToPointSize[property] = pointSizeProp;
    d_ptr->m_pointSizeToProperty[pointSizeProp] = property;
    property->addSubProperty(pointSizeProp);

    QExtPEProperty *boldProp = d_ptr->m_boolPropertyManager->addProperty();
    boldProp->setPropertyName(tr("Bold"));
    d_ptr->m_boolPropertyManager->setValue(boldProp, val.bold());
    d_ptr->m_propertyToBold[property] = boldProp;
    d_ptr->m_boldToProperty[boldProp] = property;
    property->addSubProperty(boldProp);

    QExtPEProperty *italicProp = d_ptr->m_boolPropertyManager->addProperty();
    italicProp->setPropertyName(tr("Italic"));
    d_ptr->m_boolPropertyManager->setValue(italicProp, val.italic());
    d_ptr->m_propertyToItalic[property] = italicProp;
    d_ptr->m_italicToProperty[italicProp] = property;
    property->addSubProperty(italicProp);

    QExtPEProperty *underlineProp = d_ptr->m_boolPropertyManager->addProperty();
    underlineProp->setPropertyName(tr("Underline"));
    d_ptr->m_boolPropertyManager->setValue(underlineProp, val.underline());
    d_ptr->m_propertyToUnderline[property] = underlineProp;
    d_ptr->m_underlineToProperty[underlineProp] = property;
    property->addSubProperty(underlineProp);

    QExtPEProperty *strikeOutProp = d_ptr->m_boolPropertyManager->addProperty();
    strikeOutProp->setPropertyName(tr("Strikeout"));
    d_ptr->m_boolPropertyManager->setValue(strikeOutProp, val.strikeOut());
    d_ptr->m_propertyToStrikeOut[property] = strikeOutProp;
    d_ptr->m_strikeOutToProperty[strikeOutProp] = property;
    property->addSubProperty(strikeOutProp);

    QExtPEProperty *kerningProp = d_ptr->m_boolPropertyManager->addProperty();
    kerningProp->setPropertyName(tr("Kerning"));
    d_ptr->m_boolPropertyManager->setValue(kerningProp, val.kerning());
    d_ptr->m_propertyToKerning[property] = kerningProp;
    d_ptr->m_kerningToProperty[kerningProp] = property;
    property->addSubProperty(kerningProp);
}

void QExtPEFontPropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    QExtPEProperty *familyProp = d_ptr->m_propertyToFamily[property];
    if (familyProp)
    {
        d_ptr->m_familyToProperty.remove(familyProp);
        delete familyProp;
    }
    d_ptr->m_propertyToFamily.remove(property);

    QExtPEProperty *pointSizeProp = d_ptr->m_propertyToPointSize[property];
    if (pointSizeProp)
    {
        d_ptr->m_pointSizeToProperty.remove(pointSizeProp);
        delete pointSizeProp;
    }
    d_ptr->m_propertyToPointSize.remove(property);

    QExtPEProperty *boldProp = d_ptr->m_propertyToBold[property];
    if (boldProp)
    {
        d_ptr->m_boldToProperty.remove(boldProp);
        delete boldProp;
    }
    d_ptr->m_propertyToBold.remove(property);

    QExtPEProperty *italicProp = d_ptr->m_propertyToItalic[property];
    if (italicProp)
    {
        d_ptr->m_italicToProperty.remove(italicProp);
        delete italicProp;
    }
    d_ptr->m_propertyToItalic.remove(property);

    QExtPEProperty *underlineProp = d_ptr->m_propertyToUnderline[property];
    if (underlineProp)
    {
        d_ptr->m_underlineToProperty.remove(underlineProp);
        delete underlineProp;
    }
    d_ptr->m_propertyToUnderline.remove(property);

    QExtPEProperty *strikeOutProp = d_ptr->m_propertyToStrikeOut[property];
    if (strikeOutProp)
    {
        d_ptr->m_strikeOutToProperty.remove(strikeOutProp);
        delete strikeOutProp;
    }
    d_ptr->m_propertyToStrikeOut.remove(property);

    QExtPEProperty *kerningProp = d_ptr->m_propertyToKerning[property];
    if (kerningProp)
    {
        d_ptr->m_kerningToProperty.remove(kerningProp);
        delete kerningProp;
    }
    d_ptr->m_propertyToKerning.remove(property);

    d_ptr->m_values.remove(property);
}



/***********************************************************************************************************************
 * QExtPEColorPropertyManager
***********************************************************************************************************************/
void QExtPEColorPropertyManagerPrivate::slotIntChanged(QExtPEProperty *property, int value)
{
    if (QExtPEProperty *prop = m_rToProperty.value(property, QEXT_NULLPTR))
    {
        QColor c = m_values[prop];
        c.setRed(value);
        q_ptr->setValue(prop, c);
    }
    else if (QExtPEProperty *prop = m_gToProperty.value(property, QEXT_NULLPTR))
    {
        QColor c = m_values[prop];
        c.setGreen(value);
        q_ptr->setValue(prop, c);
    }
    else if (QExtPEProperty *prop = m_bToProperty.value(property, QEXT_NULLPTR))
    {
        QColor c = m_values[prop];
        c.setBlue(value);
        q_ptr->setValue(prop, c);
    }
    else if (QExtPEProperty *prop = m_aToProperty.value(property, QEXT_NULLPTR))
    {
        QColor c = m_values[prop];
        c.setAlpha(value);
        q_ptr->setValue(prop, c);
    }
}

void QExtPEColorPropertyManagerPrivate::slotPropertyDestroyed(QExtPEProperty *property)
{
    if (QExtPEProperty *pointProp = m_rToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToR[pointProp] = QEXT_NULLPTR;
        m_rToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_gToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToG[pointProp] = QEXT_NULLPTR;
        m_gToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_bToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToB[pointProp] = QEXT_NULLPTR;
        m_bToProperty.remove(property);
    }
    else if (QExtPEProperty *pointProp = m_aToProperty.value(property, QEXT_NULLPTR))
    {
        m_propertyToA[pointProp] = QEXT_NULLPTR;
        m_aToProperty.remove(property);
    }
}


QExtPEColorPropertyManager::QExtPEColorPropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPEColorPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new QExtPEIntPropertyManager(this);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotIntChanged(QExtPEProperty *, int)));

    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(QExtPEProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtPEProperty *)));
}

QExtPEColorPropertyManager::~QExtPEColorPropertyManager()
{
    this->clear();
    delete d_ptr;
}

QExtPEIntPropertyManager *QExtPEColorPropertyManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

QColor QExtPEColorPropertyManager::value(const QExtPEProperty *property) const
{
    return d_ptr->m_values.value(property, QColor());
}

QString QExtPEColorPropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPEColorPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }

    return QExtPropertyBrowserUtils::colorValueText(it.value());
}

QIcon QExtPEColorPropertyManager::valueIcon(const QExtPEProperty *property) const
{
    const QExtPEColorPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QIcon();
    }
    return QExtPropertyBrowserUtils::brushValueIcon(QBrush(it.value()));
}

void QExtPEColorPropertyManager::setValue(QExtPEProperty *property, const QColor &val)
{
    const QExtPEColorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    if (it.value() == val)
    {
        return;
    }

    it.value() = val;

    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToR[property], val.red());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToG[property], val.green());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToB[property], val.blue());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToA[property], val.alpha());

    emit this->propertyChanged(property);
    emit this->valueChanged(property, val);
}

void QExtPEColorPropertyManager::initializeProperty(QExtPEProperty *property)
{
    QColor val;
    d_ptr->m_values[property] = val;

    QExtPEProperty *rProp = d_ptr->m_intPropertyManager->addProperty();
    rProp->setPropertyName(tr("Red"));
    d_ptr->m_intPropertyManager->setValue(rProp, val.red());
    d_ptr->m_intPropertyManager->setRange(rProp, 0, 0xFF);
    d_ptr->m_propertyToR[property] = rProp;
    d_ptr->m_rToProperty[rProp] = property;
    property->addSubProperty(rProp);

    QExtPEProperty *gProp = d_ptr->m_intPropertyManager->addProperty();
    gProp->setPropertyName(tr("Green"));
    d_ptr->m_intPropertyManager->setValue(gProp, val.green());
    d_ptr->m_intPropertyManager->setRange(gProp, 0, 0xFF);
    d_ptr->m_propertyToG[property] = gProp;
    d_ptr->m_gToProperty[gProp] = property;
    property->addSubProperty(gProp);

    QExtPEProperty *bProp = d_ptr->m_intPropertyManager->addProperty();
    bProp->setPropertyName(tr("Blue"));
    d_ptr->m_intPropertyManager->setValue(bProp, val.blue());
    d_ptr->m_intPropertyManager->setRange(bProp, 0, 0xFF);
    d_ptr->m_propertyToB[property] = bProp;
    d_ptr->m_bToProperty[bProp] = property;
    property->addSubProperty(bProp);

    QExtPEProperty *aProp = d_ptr->m_intPropertyManager->addProperty();
    aProp->setPropertyName(tr("Alpha"));
    d_ptr->m_intPropertyManager->setValue(aProp, val.alpha());
    d_ptr->m_intPropertyManager->setRange(aProp, 0, 0xFF);
    d_ptr->m_propertyToA[property] = aProp;
    d_ptr->m_aToProperty[aProp] = property;
    property->addSubProperty(aProp);
}

void QExtPEColorPropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    QExtPEProperty *rProp = d_ptr->m_propertyToR[property];
    if (rProp)
    {
        d_ptr->m_rToProperty.remove(rProp);
        delete rProp;
    }
    d_ptr->m_propertyToR.remove(property);

    QExtPEProperty *gProp = d_ptr->m_propertyToG[property];
    if (gProp)
    {
        d_ptr->m_gToProperty.remove(gProp);
        delete gProp;
    }
    d_ptr->m_propertyToG.remove(property);

    QExtPEProperty *bProp = d_ptr->m_propertyToB[property];
    if (bProp)
    {
        d_ptr->m_bToProperty.remove(bProp);
        delete bProp;
    }
    d_ptr->m_propertyToB.remove(property);

    QExtPEProperty *aProp = d_ptr->m_propertyToA[property];
    if (aProp)
    {
        d_ptr->m_aToProperty.remove(aProp);
        delete aProp;
    }
    d_ptr->m_propertyToA.remove(property);

    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
 * QExtPECursorPropertyManager
***********************************************************************************************************************/
// Make sure icons are removed as soon as QApplication is destroyed, otherwise, handles are leaked on X11.
static void clearCursorDatabase();
namespace
{
struct CursorDatabase : public QExtCursorDatabase
{
    CursorDatabase()
    {
        qAddPostRoutine(clearCursorDatabase);
    }
};
}
Q_GLOBAL_STATIC(QExtCursorDatabase, cursorDatabase)

static void clearCursorDatabase()
{
    cursorDatabase()->clear();
}


QExtPECursorPropertyManager::QExtPECursorPropertyManager(QObject *parent)
    : QExtPEAbstractPropertyManager(parent)
{
    d_ptr = new QExtPECursorPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

QExtPECursorPropertyManager::~QExtPECursorPropertyManager()
{
    this->clear();
    delete d_ptr;
}

#ifndef QT_NO_CURSOR
QCursor QExtPECursorPropertyManager::value(const QExtPEProperty *property) const
{
    return d_ptr->m_values.value(property, QCursor());
}
#endif

QString QExtPECursorPropertyManager::valueText(const QExtPEProperty *property) const
{
    const QExtPECursorPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }

    return cursorDatabase()->cursorToShapeName(it.value());
}

QIcon QExtPECursorPropertyManager::valueIcon(const QExtPEProperty *property) const
{
    const QExtPECursorPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QIcon();
    }

    return cursorDatabase()->cursorToShapeIcon(it.value());
}

void QExtPECursorPropertyManager::setValue(QExtPEProperty *property, const QCursor &value)
{
#ifndef QT_NO_CURSOR
    const QExtPECursorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    if (it.value().shape() == value.shape() && value.shape() != Qt::BitmapCursor)
    {
        return;
    }

    it.value() = value;

    emit this->propertyChanged(property);
    emit this->valueChanged(property, value);
#endif
}

void QExtPECursorPropertyManager::initializeProperty(QExtPEProperty *property)
{
#ifndef QT_NO_CURSOR
    d_ptr->m_values[property] = QCursor();
#endif
}

void QExtPECursorPropertyManager::uninitializeProperty(QExtPEProperty *property)
{
    d_ptr->m_values.remove(property);
}


#include "moc_qextPEPropertyManager.cpp"
