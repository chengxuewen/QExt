#include <private/qextJson_p.h>

/***********************************************************************************************************************
 * QExtJsonValue
***********************************************************************************************************************/
QExtJsonValuePrivate::QExtJsonValuePrivate(QExtJsonValue *q)
    : q_ptr(q)
{

}

QExtJsonValuePrivate::~QExtJsonValuePrivate()
{

}


QExtJsonValue::QExtJsonValue()
    : dd_ptr(new QExtJsonValuePrivate(this))
{

}

QExtJsonValue::QExtJsonValue(bool boolean)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_value = boolean;
#endif
}

QExtJsonValue::QExtJsonValue(double number)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_value = number;
#endif
}

QExtJsonValue::QExtJsonValue(int number)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_value = number;
#endif
}

QExtJsonValue::QExtJsonValue(qint64 number)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_value = number;
#endif
}

QExtJsonValue::QExtJsonValue(QLatin1String string)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_value = string;
#endif
}

QExtJsonValue::QExtJsonValue(const QString &string)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_value = string;
#endif
}

QExtJsonValue::QExtJsonValue(const std::string &string)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_value = string.c_str();
#endif
}

QExtJsonValue::QExtJsonValue(const QExtJsonArray &array)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_value = array.dd_ptr->m_array;
#endif
}

QExtJsonValue::QExtJsonValue(const QExtJsonObject &object)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_value = object.dd_ptr->m_object;
#endif
}

QExtJsonValue::~QExtJsonValue()
{

}

QExtJsonValue::QExtJsonValue(const QExtJsonValue &other)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_value = other.dd_ptr->m_value;
#endif
}

QExtJsonValue &QExtJsonValue::operator =(const QExtJsonValue &other)
{
    if (this != &other)
    {
        Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
        d->m_value = other.dd_ptr->m_value;
#endif
    }
    return *this;
}

QExtJsonValue QExtJsonValue::fromVariant(const QVariant &variant)
{
    QExtJsonValue value;
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    value.dd_ptr->m_value = QJsonValue::fromVariant(variant);
#endif
    return value;
}

QVariant QExtJsonValue::toVariant() const
{
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_value.toVariant();
#endif
}

QExtJsonValue::TypeEnum QExtJsonValue::type() const
{
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    switch (d->m_value.type())
    {
    case QJsonValue::Null: return Type_Null;
    case QJsonValue::Bool: return Type_Bool;
    case QJsonValue::Double: return Type_Number;
    case QJsonValue::String: return Type_String;
    case QJsonValue::Array: return Type_Array;
    case QJsonValue::Object: return Type_Object;
    case QJsonValue::Undefined: return Type_Undefined;
    default: return Type_Undefined;
    }
#endif
}

bool QExtJsonValue::toBool(bool defaultValue) const
{
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_value.toBool(defaultValue);
#endif
}

int QExtJsonValue::toInt(int defaultValue) const
{
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_value.toInt(defaultValue);
#endif
}

double QExtJsonValue::toDouble(double defaultValue) const
{
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_value.toDouble(defaultValue);
#endif
}

QString QExtJsonValue::toString() const
{
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_value.toString();
#endif
}

QString QExtJsonValue::toString(const QString &defaultValue) const
{
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_value.toString(defaultValue);
#endif
}

QExtJsonArray QExtJsonValue::toArray() const
{
    QExtJsonArray array;
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    array.dd_ptr->m_array = d->m_value.toArray();
#endif
    return array;
}

QExtJsonArray QExtJsonValue::toArray(const QExtJsonArray &defaultValue) const
{
    QExtJsonArray array;
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    array.dd_ptr->m_array = d->m_value.toArray(defaultValue.dd_ptr->m_array);
#endif
    return array;
}

QExtJsonObject QExtJsonValue::toObject() const
{
    QExtJsonObject object;
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    object.dd_ptr->m_object = d->m_value.toObject();
#endif
    return object;
}

QExtJsonObject QExtJsonValue::toObject(const QExtJsonObject &defaultValue) const
{
    QExtJsonObject object;
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    object.dd_ptr->m_object = d->m_value.toObject(defaultValue.dd_ptr->m_object);
#endif
    return object;
}

const QExtJsonValue QExtJsonValue::operator[](const QString &key) const
{
    QExtJsonValue value;
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    value.dd_ptr->m_value = d->m_value[key];
#endif
    return value;
}

const QExtJsonValue QExtJsonValue::operator[](QLatin1String key) const
{
    QExtJsonValue value;
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    value.dd_ptr->m_value = d->m_value[key];
#endif
    return value;
}

const QExtJsonValue QExtJsonValue::operator[](int index) const
{
    QExtJsonValue value;
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    value.dd_ptr->m_value = d->m_value[index];
#endif
    return value;
}

bool QExtJsonValue::operator==(const QExtJsonValue &other) const
{
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    Q_D(const QExtJsonValue);
    return d->m_value == other.dd_ptr->m_value;
#endif
}

bool QExtJsonValue::operator!=(const QExtJsonValue &other) const
{
    return !(*this == other);
}


/***********************************************************************************************************************
    QExt force inline macro declare
***********************************************************************************************************************/
QExtJsonValueRef::QExtJsonValueRef(const QExtJsonValueRef &other)
{
    *this = other;
}

QExtJsonValueRef::QExtJsonValueRef(const QExtJsonValue &value)
{
    *this = value;
}

QExtJsonValueRef &QExtJsonValueRef::operator =(const QExtJsonValue &val)
{
    if (is_object)
    {
        o->setValueAt(index, val);
    }
    else
    {
        a->replace(index, val);
    }
    return *this;
}

QExtJsonValueRef &QExtJsonValueRef::operator =(const QExtJsonValueRef &val)
{
    if (is_object)
    {
        o->setValueAt(index, val);
    }
    else
    {
        a->replace(index, val);
    }
    return *this;
}

QVariant QExtJsonValueRef::toVariant() const
{
    return toValue().toVariant();
}

QExtJsonArray QExtJsonValueRef::toArray() const
{
    return toValue().toArray();
}

QExtJsonObject QExtJsonValueRef::toObject() const
{
    return toValue().toObject();
}

QExtJsonValue QExtJsonValueRef::toValue() const
{
    return toValue();
}


/***********************************************************************************************************************
 * QExtJsonObject
***********************************************************************************************************************/
QExtJsonObjectPrivate::QExtJsonObjectPrivate(QExtJsonObject *q)
    : q_ptr(q)
{

}

QExtJsonObjectPrivate::~QExtJsonObjectPrivate()
{

}

QExtJsonObject::QExtJsonObject()
    : dd_ptr(new QExtJsonObjectPrivate(this))
{

}

QExtJsonObject::QExtJsonObject(const QExtJsonObject &other)
    : dd_ptr(new QExtJsonObjectPrivate(this))
{
    Q_D(QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_object = other.dd_ptr->m_object;
#endif
}

QExtJsonObject::QExtJsonObject(const QList<QExtJsonValue> &args)
    : dd_ptr(new QExtJsonObjectPrivate(this))
{

}

QExtJsonObject::~QExtJsonObject()
{

}

QExtJsonObject &QExtJsonObject::operator =(const QExtJsonObject &other)
{
    if (this != &other)
    {
        Q_D(QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
        d->m_object = other.dd_ptr->m_object;
#endif
    }
    return *this;
}

QExtJsonObject QExtJsonObject::fromVariantMap(const QVariantMap &map)
{
    QExtJsonObject object;
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    object.dd_ptr->m_object = QJsonObject::fromVariantMap(map);
#endif
    return object;
}

QVariantMap QExtJsonObject::toVariantMap() const
{
    Q_D(const QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_object.toVariantMap();
#endif
}

QExtJsonObject QExtJsonObject::fromVariantHash(const QVariantHash &map)
{
    QExtJsonObject object;
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    object.dd_ptr->m_object = QJsonObject::fromVariantHash(map);
#endif
    return object;
}

QVariantHash QExtJsonObject::toVariantHash() const
{
    Q_D(const QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_object.toVariantHash();
#endif
}

QStringList QExtJsonObject::keys() const
{
    Q_D(const QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_object.keys();
#endif
}

int QExtJsonObject::size() const
{
    Q_D(const QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_object.size();
#endif
}

bool QExtJsonObject::isEmpty() const
{
    Q_D(const QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_object.isEmpty();
#endif
}

QExtJsonValue QExtJsonObject::value(const QString &key) const
{
    QExtJsonValue value;
    Q_D(const QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    value.dd_ptr->m_value = d->m_object.value(key);
#endif
    return value;
}

QExtJsonValue QExtJsonObject::operator[](const QString &key) const
{
    QExtJsonValue value;
    Q_D(const QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    value.dd_ptr->m_value = d->m_object[key];
#endif
    return value;
}

QExtJsonValueRef QExtJsonObject::operator[](const QString &key)
{
    QExtJsonValue value;
    Q_D(const QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    value.dd_ptr->m_value = d->m_object[key];
#endif
    return value;
}

void QExtJsonObject::remove(const QString &key)
{
    Q_D(QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_object.remove(key);
#endif
}

QExtJsonValue QExtJsonObject::take(const QString &key)
{
    QExtJsonValue value;
    Q_D(QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    value.dd_ptr->m_value = d->m_object.take(key);
#endif
    return value;
}

bool QExtJsonObject::contains(const QString &key) const
{
    Q_D(const QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_object.contains(key);
#endif
}

bool QExtJsonObject::operator==(const QExtJsonObject &other) const
{
    Q_D(const QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_object == other.dd_ptr->m_object;
#endif
}

bool QExtJsonObject::operator!=(const QExtJsonObject &other) const
{
    return !(*this != other);
}

QExtJsonObject::iterator QExtJsonObject::erase(iterator it)
{
    Q_D(QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else

#endif
}

QExtJsonObject::iterator QExtJsonObject::find(const QString &key)
{

}

QExtJsonObject::const_iterator QExtJsonObject::constFind(const QString &key) const
{

}

QExtJsonObject::iterator QExtJsonObject::insert(const QString &key, const QExtJsonValue &value)
{

}

QExtJsonObject::iterator QExtJsonObject::find(QLatin1String key)
{

}

QExtJsonObject::const_iterator QExtJsonObject::constFind(QLatin1String key) const
{

}

QExtJsonObject::iterator QExtJsonObject::insert(QLatin1String key, const QExtJsonValue &value)
{

}

bool QExtJsonObject::detach2(uint reserve)
{

}

void QExtJsonObject::compact()
{

}

QString QExtJsonObject::keyAt(int index) const
{

}

QExtJsonValue QExtJsonObject::valueAt(int index) const
{

}

void QExtJsonObject::setValueAt(int index, const QExtJsonValue &val)
{

}

void QExtJsonObject::removeAt(int index)
{

}


/***********************************************************************************************************************
 * QExtJsonArray
***********************************************************************************************************************/
QExtJsonArrayPrivate::QExtJsonArrayPrivate(QExtJsonArray *q)
    : q_ptr(q)
{

}

QExtJsonArrayPrivate::~QExtJsonArrayPrivate()
{

}

QExtJsonArray::QExtJsonArray()
    : dd_ptr(new QExtJsonArrayPrivate(this))
{

}

QExtJsonArray::~QExtJsonArray()
{

}

QExtJsonArray::QExtJsonArray(const QExtJsonArray &other)
    : dd_ptr(new QExtJsonArrayPrivate(this))
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_array = other.dd_ptr->m_array;
#endif
}

QExtJsonArray::QExtJsonArray(const QList<QExtJsonValue> &args)
    : dd_ptr(new QExtJsonArrayPrivate(this))
{

}

QExtJsonArray &QExtJsonArray::operator =(const QExtJsonArray &other)
{
    if (this != &other)
    {
        Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
        d->m_array = other.dd_ptr->m_array;
#endif
    }
    return *this;
}

QExtJsonArray QExtJsonArray::fromStringList(const QStringList &list)
{
    QExtJsonArray array;
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    array.dd_ptr->m_array = QJsonArray::fromStringList(list);
#endif
    return array;
}

QExtJsonArray QExtJsonArray::fromVariantList(const QVariantList &list)
{
    QExtJsonArray array;
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    array.dd_ptr->m_array = QJsonArray::fromVariantList(list);
#endif
    return array;
}

QVariantList QExtJsonArray::toVariantList() const
{
    Q_D(const QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_array.toVariantList();
#endif
}

int QExtJsonArray::size() const
{
    Q_D(const QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_array.size();
#endif
}

bool QExtJsonArray::isEmpty() const
{
    Q_D(const QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_array.isEmpty();
#endif
}

QExtJsonValue QExtJsonArray::at(int index) const
{
    QExtJsonValue value;
    Q_D(const QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    value.dd_ptr->m_value = d->m_array.at(index);
#endif
    return value;
}

QExtJsonValue QExtJsonArray::first() const
{
    QExtJsonValue value;
    Q_D(const QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    value.dd_ptr->m_value = d->m_array.first();
#endif
    return value;
}

QExtJsonValue QExtJsonArray::last() const
{
    QExtJsonValue value;
    Q_D(const QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    value.dd_ptr->m_value = d->m_array.last();
#endif
    return value;
}

void QExtJsonArray::prepend(const QExtJsonValue &value)
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_array.prepend(value.dd_ptr->m_value);
#endif
}

void QExtJsonArray::append(const QExtJsonValue &value)
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_array.append(value.dd_ptr->m_value);
#endif
}

void QExtJsonArray::removeAt(int index)
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_array.removeAt(index);
#endif
}

QExtJsonValue QExtJsonArray::takeAt(int index)
{
    QExtJsonValue value;
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    value.dd_ptr->m_value = d->m_array.takeAt(index);
#endif
    return value;
}

void QExtJsonArray::insert(int index, const QExtJsonValue &value)
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_array.insert(index, value.dd_ptr->m_value);
#endif
}

void QExtJsonArray::replace(int index, const QExtJsonValue &value)
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_array.replace(index, value.dd_ptr->m_value);
#endif
}

bool QExtJsonArray::contains(const QExtJsonValue &element) const
{
    Q_D(const QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_array.contains(element.dd_ptr->m_value);
#endif
}

QExtJsonValueRef QExtJsonArray::operator[](int index)
{
    QExtJsonValue value;
    Q_D(const QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    value.dd_ptr->m_value = d->m_array[index];
#endif
    return value;
}

QExtJsonValue QExtJsonArray::operator[](int index) const
{
    QExtJsonValue value;
    Q_D(const QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    value.dd_ptr->m_value = d->m_array[index];
#endif
    return value;
}

bool QExtJsonArray::operator==(const QExtJsonArray &other) const
{
    Q_D(const QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_array == other.dd_ptr->m_array;
#endif
}

bool QExtJsonArray::operator!=(const QExtJsonArray &other) const
{
    return !(*this == other);
}

// bool QExtJsonArray::detach2(uint reserve)
// {

// }

// void QExtJsonArray::initialize()
// {

// }

// void QExtJsonArray::compact()
// {

// }


/***********************************************************************************************************************
 * QExtJsonDocument
***********************************************************************************************************************/
QExtJsonDocumentPrivate::QExtJsonDocumentPrivate(QExtJsonDocument *q)
    : q_ptr(q)
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    m_cJson = QEXT_NULLPTR;
#endif
}

QExtJsonDocumentPrivate::~QExtJsonDocumentPrivate()
{
}



QExtJsonDocument::QExtJsonDocument()
    : dd_ptr(new QExtJsonDocumentPrivate(this))
{

}

QExtJsonDocument::QExtJsonDocument(const QExtJsonObject &object)
    : dd_ptr(new QExtJsonDocumentPrivate(this))
{

}

QExtJsonDocument::QExtJsonDocument(const QExtJsonArray &array)
    : dd_ptr(new QExtJsonDocumentPrivate(this))
{

}

QExtJsonDocument::~QExtJsonDocument()
{
#if QEXT_FEATURE_USE_CJSON_BACKEND

#endif
}

QExtJsonDocument::QExtJsonDocument(const QExtJsonDocument &other)
    : dd_ptr(new QExtJsonDocumentPrivate(this))
{
    Q_D(QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_document = other.dd_ptr->m_document;
#endif
}

QExtJsonDocument &QExtJsonDocument::operator =(const QExtJsonDocument &other)
{
    Q_D(QExtJsonDocument);
    if (this != &other)
    {
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
        d->m_document = other.dd_ptr->m_document;
#endif
    }
    return *this;
}

QExtJsonDocument QExtJsonDocument::fromVariant(const QVariant &variant)
{
    QExtJsonDocument document;
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    document.dd_ptr->m_document = QJsonDocument::fromVariant(variant);
#endif
    return document;
}

QVariant QExtJsonDocument::toVariant() const
{
    Q_D(const QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_document.toVariant();
#endif
}

QExtJsonDocument QExtJsonDocument::fromJson(const QByteArray &json, QString *error)
{
    QExtJsonDocument document;
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON *cJson = cJSON_ParseWithLength(json.data(), json.length());
    if (cJson)
    {
        document.dd_ptr->m_cJson = cJson;
    }
    else if (error)
    {
        *error = cJSON_GetErrorPtr();
    }
#else
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(json, &parseError);
    if (!jsonDoc.isNull())
    {
        document.dd_ptr->m_document = jsonDoc;
    }
    else if (error)
    {
        *error = parseError.errorString();
    }
#endif
    return document;
}

QByteArray QExtJsonDocument::toJson() const
{
    Q_D(const QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_document.toJson();
#endif
}

bool QExtJsonDocument::isEmpty() const
{
    Q_D(const QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_document.isEmpty();
#endif
}

bool QExtJsonDocument::isArray() const
{
    Q_D(const QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_document.isArray();
#endif
}

bool QExtJsonDocument::isObject() const
{
    Q_D(const QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_document.isObject();
#endif
}

QExtJsonObject QExtJsonDocument::object() const
{
    Q_D(const QExtJsonDocument);
    QExtJsonObject object;
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    object.dd_ptr->m_object =  d->m_document.object();
#endif
    return object;
}

QExtJsonArray QExtJsonDocument::array() const
{
    Q_D(const QExtJsonDocument);
    QExtJsonArray array;
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    array.dd_ptr->m_array = d->m_document.array();
#endif
    return array;
}

void QExtJsonDocument::setObject(const QExtJsonObject &object)
{
    Q_D(QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_document.setObject(object.dd_ptr->m_object);
#endif
}

void QExtJsonDocument::setArray(const QExtJsonArray &array)
{
    Q_D(QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    d->m_document.setArray(array.dd_ptr->m_array);
#endif
}

const QExtJsonValue QExtJsonDocument::operator[](QLatin1String key) const
{
    Q_D(const QExtJsonDocument);
    QExtJsonValue value;
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    value.dd_ptr->m_value = d->m_document[key];
#endif
    return value;
}

const QExtJsonValue QExtJsonDocument::operator[](int index) const
{
    Q_D(const QExtJsonDocument);
    QExtJsonValue value;
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    value.dd_ptr->m_value = d->m_document[index];
#endif
    return value;
}

bool QExtJsonDocument::operator==(const QExtJsonDocument &other) const
{
    Q_D(const QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_document == other.dd_ptr->m_document;
#endif
}

bool QExtJsonDocument::isNull() const
{
    Q_D(const QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND

#else
    return d->m_document.isNull();
#endif
}

