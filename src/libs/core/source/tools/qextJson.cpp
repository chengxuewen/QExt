#include <private/qextJson_p.h>
#include <qextNumeric.h>
#include <qextTag.h>

#include <QThreadStorage>

#include <cfloat>

namespace detail
{
QThreadStorage<QString> &qextJsonBackendTls()
{
    static QThreadStorage<QString> backendString;
    return backendString;
}
}

/***********************************************************************************************************************
 * QExtJsonValue
***********************************************************************************************************************/
QExtJsonValuePrivate::QExtJsonValuePrivate(QExtJsonValue *q)
    : q_ptr(q)
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    m_cJson = QEXT_NULLPTR;
#endif
}

QExtJsonValuePrivate::~QExtJsonValuePrivate()
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (m_cJson)
    {
        cJSON_Delete(m_cJson);
        m_cJson = QEXT_NULLPTR;
    }
#endif
}


QExtJsonValue::QExtJsonValue(TypeEnum type)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    switch (type)
    {
    case Type_Null:
        d->m_cJson = cJSON_CreateNull();
        break;
    case Type_Bool:
        d->m_cJson = cJSON_CreateBool(false);
        break;
    case Type_Number:
        d->m_cJson = cJSON_CreateNumber(0);
        break;
    case Type_String:
        d->m_cJson = cJSON_CreateString("");
        break;
    case Type_Array:
        d->m_cJson = cJSON_CreateArray();
        break;
    case Type_Object:
        d->m_cJson = cJSON_CreateObject();
        break;
    default:
        d->m_cJson = cJSON_CreateRaw("");
        break;
    }
#else
    switch (type)
    {
    case Type_Null:
        d->m_value = QJsonValue::Null;
        break;
    case Type_Bool:
        d->m_value = QJsonValue::Bool;
        break;
    case Type_Number:
        d->m_value = QJsonValue::Double;
        break;
    case Type_String:
        d->m_value = QJsonValue::String;
        break;
    case Type_Array:
        d->m_value = QJsonValue::Array;
        break;
    case Type_Object:
        d->m_value = QJsonValue::Object;
        break;
    case Type_Undefined:
        d->m_value = QJsonValue::Undefined;
        break;
    }
#endif
}

QExtJsonValue::QExtJsonValue(bool boolean)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_CreateBool(boolean);
#else
    d->m_value = boolean;
#endif
}

QExtJsonValue::QExtJsonValue(double number)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_CreateNumber(number);
#else
    d->m_value = number;
#endif
}

QExtJsonValue::QExtJsonValue(int number)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_CreateNumber((double)number);
#else
    d->m_value = number;
#endif
}

QExtJsonValue::QExtJsonValue(qint64 number)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_CreateNumber((double)number);
#else
    d->m_value = double(number);
#endif
}

QExtJsonValue::QExtJsonValue(const char *string)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_CreateString(string);
#else
    d->m_value = string;
#endif
}

QExtJsonValue::QExtJsonValue(const QString &string)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_CreateString(string.toLatin1().data());
#else
    d->m_value = string;
#endif
}

QExtJsonValue::QExtJsonValue(const std::string &string)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_CreateString(string.c_str());
#else
    d->m_value = string.c_str();
#endif
}

QExtJsonValue::QExtJsonValue(const QExtJsonArray &array)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_Duplicate(array.dd_ptr->m_cJson, true);
#else
    d->m_value = array.dd_ptr->m_array;
#endif
}

QExtJsonValue::QExtJsonValue(const QExtJsonObject &object)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_Duplicate(object.dd_ptr->m_cJson, true);
#else
    d->m_value = object.dd_ptr->m_object;
#endif
}

QExtJsonValue::QExtJsonValue(const QString &key, const QExtJsonValue &value)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_CreateObject();
    cJSON_AddItemToObject(d->m_cJson, key.toLatin1().data(), cJSON_Duplicate(value.dd_ptr->m_cJson, true));
#else
    QJsonObject object;
    object.insert(key, value.dd_ptr->m_value);
    d->m_value = object;
#endif
}

QExtJsonValue::QExtJsonValue(const QExtJsonValue &other)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_Duplicate(other.dd_ptr->m_cJson, true);
#else
    d->m_value = other.dd_ptr->m_value;
#endif
}

QExtJsonValue::~QExtJsonValue()
{
    delete dd_ptr;
    dd_ptr = QEXT_NULLPTR;
}

QExtJsonValue &QExtJsonValue::operator =(const QExtJsonValue &other)
{
    if (this != &other)
    {
        Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
        cJSON_Delete(d->m_cJson);
        d->m_cJson = cJSON_Duplicate(other.dd_ptr->m_cJson, true);
#else
        d->m_value = other.dd_ptr->m_value;
#endif
    }
    return *this;
}

//QExtJsonValue QExtJsonValue::fromVariant(const QVariant &variant)
//{
//    QExtJsonValue value;
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    value.dd_ptr->m_value = QJsonValue::fromVariant(variant);
//#endif
//    return value;
//}

//QVariant QExtJsonValue::toVariant() const
//{
//    Q_D(const QExtJsonValue);
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    return d->m_value.toVariant();
//#endif
//}

QExtJsonValue::TypeEnum QExtJsonValue::type() const
{
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (cJSON_IsNull(d->m_cJson))
    {
        return Type_Null;
    }
    else if (cJSON_IsBool(d->m_cJson))
    {
        return Type_Bool;
    }
    else if (cJSON_IsNumber(d->m_cJson))
    {
        return Type_Number;
    }
    else if (cJSON_IsString(d->m_cJson))
    {
        return Type_String;
    }
    else if (cJSON_IsArray(d->m_cJson))
    {
        return Type_Array;
    }
    else if (cJSON_IsObject(d->m_cJson))
    {
        return Type_Object;
    }
    else
    {
        return Type_Undefined;
    }
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
    if (cJSON_IsBool(d->m_cJson))
    {
        return cJSON_IsTrue(d->m_cJson);
    }
    return defaultValue;
#else
    return d->m_value.toBool(defaultValue);
#endif
}

int QExtJsonValue::toInt(int defaultValue) const
{
    Q_D(const QExtJsonValue);
    if (this->isNumber())
    {
        const qint64 integer = this->toInteger();
        if (qint64(int(integer)) == integer)
        {
            return int(integer);
        }
    }
    return defaultValue;
}

double QExtJsonValue::toDouble(double defaultValue) const
{
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (cJSON_IsNumber(d->m_cJson))
    {
        return cJSON_GetNumberValue(d->m_cJson);
    }
    return defaultValue;
#else
    return d->m_value.toDouble(defaultValue);
#endif
}

qint64 QExtJsonValue::toInteger(qint64 defaultValue) const
{
    Q_D(const QExtJsonValue);
    if (this->isNumber())
    {
        return (qint64)this->toDouble();
    }
    return defaultValue;
}

QString QExtJsonValue::toString(const QString &defaultValue) const
{
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (cJSON_IsString(d->m_cJson))
    {
        return cJSON_GetStringValue(d->m_cJson);
    }
    return defaultValue;
#else
    return d->m_value.toString(defaultValue);
#endif
}

QExtJsonArray QExtJsonValue::toArray() const
{
    return this->toArray(QExtJsonArray());
}

QExtJsonArray QExtJsonValue::toArray(const QExtJsonArray &defaultValue) const
{
    QExtJsonArray array;
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON_Delete(array.dd_ptr->m_cJson);
    array.dd_ptr->m_cJson = cJSON_Duplicate(cJSON_IsArray(d->m_cJson) ? d->m_cJson : defaultValue.dd_ptr->m_cJson, true);
#else
    array.dd_ptr->m_array = d->m_value.toArray(defaultValue.dd_ptr->m_array);
#endif
    return array;
}

QExtJsonObject QExtJsonValue::toObject() const
{
    return this->toObject(QExtJsonObject());
}

QExtJsonObject QExtJsonValue::toObject(const QExtJsonObject &defaultValue) const
{
    QExtJsonObject object;
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON_Delete(object.dd_ptr->m_cJson);
    object.dd_ptr->m_cJson = cJSON_Duplicate(cJSON_IsObject(d->m_cJson) ? d->m_cJson : defaultValue.dd_ptr->m_cJson, true);
#else
    object.dd_ptr->m_object = d->m_value.toObject(defaultValue.dd_ptr->m_object);
#endif
    return object;
}

const QExtJsonValue QExtJsonValue::operator[](const QString &key) const
{
    return (*this)[key.toLatin1().data()];
}

const QExtJsonValue QExtJsonValue::operator[](const char *key) const
{
    QExtJsonValue value;
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (cJSON_IsObject(d->m_cJson))
    {
        cJSON *item = cJSON_GetObjectItem(d->m_cJson, key);
        if (item)
        {
            cJSON_Delete(value.dd_ptr->m_cJson);
            value.dd_ptr->m_cJson = cJSON_Duplicate(item, true);
        }
    }
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
    if (cJSON_IsArray(d->m_cJson))
    {
        cJSON *item = cJSON_GetArrayItem(d->m_cJson, index);
        if (item)
        {
            cJSON_Delete(value.dd_ptr->m_cJson);
            value.dd_ptr->m_cJson = cJSON_Duplicate(item, true);
        }
    }
#else
    value.dd_ptr->m_value = d->m_value[index];
#endif
    return value;
}

bool QExtJsonValue::operator==(const QExtJsonValue &other) const
{
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return cJSON_Compare(d->m_cJson, other.dd_ptr->m_cJson, true);
#else
    return d->m_value == other.dd_ptr->m_value;
#endif
}

bool QExtJsonValue::operator!=(const QExtJsonValue &other) const
{
    return !(*this == other);
}

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
        o->insert(QExtTag(index).name().data(), val);
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
        o->insert(QExtTag(index).name().data(), val.toValue());
    }
    else
    {
        a->replace(index, val);
    }
    return *this;
}

//QVariant QExtJsonValueRef::toVariant() const
//{
//    return this->toValue().toVariant();
//}

QExtJsonArray QExtJsonValueRef::toArray() const
{
    return this->toValue().toArray();
}

QExtJsonObject QExtJsonValueRef::toObject() const
{
    return this->toValue().toObject();
}

QExtJsonValue QExtJsonValueRef::toValue() const
{
    return is_object ? o->value(QExtTag(index).name()) : a->at(index);
}


uint qHash(const QExtJsonValue &value, uint seed)
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    switch (value.type())
    {
    case QExtJsonValue::Type_Null:
        return qHash(value.dd_ptr->m_cJson, seed);
    case QExtJsonValue::Type_Bool:
        return qHash(value.toBool(), seed);
    case QExtJsonValue::Type_Number:
        return qHash(value.toDouble(), seed);
    case QExtJsonValue::Type_String:
        return qHash(value.toString(), seed);
    case QExtJsonValue::Type_Array:
        return qHash(value.toArray(), seed);
    case QExtJsonValue::Type_Object:
        return qHash(value.toObject(), seed);
    case QExtJsonValue::Type_Undefined:
        return seed;
    }
    qFatal("UNREACHABLE");
    return 0;
#else
    return qHash(value.dd_ptr->m_value);
#endif
}

/* securely comparison of floating-point variables */
static bool compare_double(double a, double b)
{
    double maxVal = fabs(a) > fabs(b) ? fabs(a) : fabs(b);
    return (fabs(a - b) <= maxVal * DBL_EPSILON);
}
#if !defined(QT_NO_DEBUG_STREAM) && !defined(QT_JSON_READONLY)
QDebug operator<<(QDebug dbg, const QExtJsonValue &o)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))
    QDebugStateSaver saver(dbg);
#endif
    switch (o.type())
    {
    case QExtJsonValue::Type_Undefined:
        dbg << "QExtJsonValue(undefined)";
        break;
    case QExtJsonValue::Type_Null:
        dbg << "QExtJsonValue(null)";
        break;
    case QExtJsonValue::Type_Bool:
        dbg.nospace() << "QExtJsonValue(bool, " << o.toBool() << ')';
        break;
    case QExtJsonValue::Type_Number:
    {
        dbg.nospace() << "QExtJsonValue(double, " << o.toDouble() << ')';
        break;
    }
    case QExtJsonValue::Type_String:
        dbg.nospace() << "QExtJsonValue(string, " << o.toString() << ')';
        break;
    case QExtJsonValue::Type_Array:
        dbg.nospace() << "QExtJsonValue(array, ";
        dbg << o.toArray();
        dbg << ')';
        break;
    case QExtJsonValue::Type_Object:
        dbg.nospace() << "QExtJsonValue(object, ";
        dbg << o.toObject();
        dbg << ')';
        break;
    }
    //    dbg << o.dd_ptr->m_value;
    return dbg;
}
#endif

#ifndef QT_NO_DATASTREAM
QDataStream &operator<<(QDataStream &stream, const QExtJsonValue &v)
{
    quint8 type = v.type();
    stream << type;
    switch (type)
    {
    case QExtJsonValue::Type_Undefined:
    case QExtJsonValue::Type_Null:
        break;
    case QExtJsonValue::Type_Bool:
        stream << v.toBool();
        break;
    case QExtJsonValue::Type_Number:
        stream << v.toDouble();
        break;
    case QExtJsonValue::Type_String:
        stream << v.toString();
        break;
    case QExtJsonValue::Type_Array:
        stream << v.toArray();
        break;
    case QExtJsonValue::Type_Object:
        stream << v.toObject();
        break;
    }
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QExtJsonValue &v)
{
    quint8 type;
    stream >> type;
    switch (type)
    {
    case QExtJsonValue::Type_Undefined:
    case QExtJsonValue::Type_Null:
    {
        v = QExtJsonValue::TypeEnum(type);
        break;
    }
    case QExtJsonValue::Type_Bool:
    {
        bool b;
        stream >> b;
        v = QExtJsonValue(b);
        break;
    }
    case QExtJsonValue::Type_Number:
    {
        double d;
        stream >> d;
        v = QExtJsonValue(d);
        break;
    }
    case QExtJsonValue::Type_String:
    {
        QString s;
        stream >> s;
        v = QExtJsonValue(s);
        break;
    }
    case QExtJsonValue::Type_Array:
    {
        QExtJsonArray a;
        stream >> a;
        v = QExtJsonValue(a);
        break;
    }
    case QExtJsonValue::Type_Object:
    {
        QExtJsonObject o;
        stream >> o;
        v = QExtJsonValue(o);
        break;
    }
    default:
    {
        stream.setStatus(QDataStream::ReadCorruptData);
        v = QExtJsonValue(QExtJsonValue::Type_Undefined);
    }
    }
    return stream;
}
#endif


/***********************************************************************************************************************
 * QExtJsonObject
***********************************************************************************************************************/
QExtJsonObjectPrivate::QExtJsonObjectPrivate(QExtJsonObject *q)
    : q_ptr(q)
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    m_cJson = QEXT_NULLPTR;
#endif
}

QExtJsonObjectPrivate::~QExtJsonObjectPrivate()
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (m_cJson)
    {
        cJSON_Delete(m_cJson);
        m_cJson = QEXT_NULLPTR;
    }
#endif
}

QExtJsonObject::QExtJsonObject()
    : dd_ptr(new QExtJsonObjectPrivate(this))
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    Q_D(QExtJsonObject);
    d->m_cJson = cJSON_CreateObject();
#endif
}

QExtJsonObject::QExtJsonObject(const QExtJsonObject &other)
    : dd_ptr(new QExtJsonObjectPrivate(this))
{
    Q_D(QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_Duplicate(other.dd_ptr->m_cJson, true);
#else
    d->m_object = other.dd_ptr->m_object;
#endif
}

QExtJsonObject::QExtJsonObject(const InitArgList &args)
    : dd_ptr(new QExtJsonObjectPrivate(this))
{
    Q_D(QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_CreateObject();
    InitArgList::ConstIterator iter;
    for (iter = args.begin(); iter != args.end(); ++iter)
    {
        const InitArg &arg = *iter;
        cJSON_AddItemToObject(d->m_cJson, arg.first.toLatin1().data(), cJSON_Duplicate(arg.second.dd_ptr->m_cJson, true));
    }
#else
    InitArgList::ConstIterator iter;
    for (iter = args.begin(); iter != args.end(); ++iter)
    {
        d->m_object.insert((*iter).first, (*iter).second.dd_ptr->m_value);
    }
#endif
}

QExtJsonObject::QExtJsonObject(const QString &key, const QExtJsonValue &value)
    : dd_ptr(new QExtJsonObjectPrivate(this))
{
    Q_D(QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_CreateObject();
    cJSON_AddItemToObject(d->m_cJson, key.toLatin1().data(), cJSON_Duplicate(value.dd_ptr->m_cJson, true));
#else
    d->m_object.insert(key, value.dd_ptr->m_value);
#endif
}

QExtJsonObject::~QExtJsonObject()
{
    delete dd_ptr;
    dd_ptr = QEXT_NULLPTR;
}

QExtJsonObject &QExtJsonObject::operator =(const QExtJsonObject &other)
{
    if (this != &other)
    {
        Q_D(QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND
        cJSON_Delete(d->m_cJson);
        d->m_cJson = cJSON_Duplicate(other.dd_ptr->m_cJson, true);
#else
        d->m_object = other.dd_ptr->m_object;
#endif
    }
    return *this;
}

//QExtJsonObject QExtJsonObject::fromVariantMap(const QVariantMap &map)
//{
//    QExtJsonObject object;
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    object.dd_ptr->m_object = QJsonObject::fromVariantMap(map);
//#endif
//    return object;
//}

//QVariantMap QExtJsonObject::toVariantMap() const
//{
//    Q_D(const QExtJsonObject);
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    return d->m_object.toVariantMap();
//#endif
//}

//QExtJsonObject QExtJsonObject::fromVariantHash(const QVariantHash &map)
//{
//    QExtJsonObject object;
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    object.dd_ptr->m_object = QJsonObject::fromVariantHash(map);
//#endif
//    return object;
//}

//QVariantHash QExtJsonObject::toVariantHash() const
//{
//    Q_D(const QExtJsonObject);
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    return d->m_object.toVariantHash();
//#endif
//}

QStringList QExtJsonObject::keys() const
{
    Q_D(const QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    QStringList keys;
    cJSON *item = d->m_cJson->child;
    while (item != NULL)
    {
        keys.append(item->string);
        item = item->next;
    }
    qSort(keys.begin(), keys.end());
    return keys;
#else
    return d->m_object.keys();
#endif
}

int QExtJsonObject::size() const
{
    Q_D(const QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    int size = 0;
    cJSON *child = d->m_cJson->child;
    while (NULL != child)
    {
        if (!cJSON_IsInvalid(child) && !cJSON_IsRaw(child))
        {
            size++;
        }
        child = child->next;
    }
    return size;
#else
    return d->m_object.size();
#endif
}

bool QExtJsonObject::isEmpty() const
{
    return this->size() <= 0;
}

QExtJsonValue QExtJsonObject::value(const QString &key) const
{
    Q_D(const QExtJsonObject);
    QExtJsonValue value(QExtJsonValue::Type_Undefined);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON *item = cJSON_GetObjectItem(d->m_cJson, key.toLatin1().data());
    if (item)
    {
        cJSON_Delete(value.dd_ptr->m_cJson);
        value.dd_ptr->m_cJson = cJSON_Duplicate(item, true);
    }
#else
    value.dd_ptr->m_value = d->m_object.value(key);
#endif
    return value;
}

QExtJsonValue QExtJsonObject::operator[](const QString &key) const
{
    return this->value(key);
}

QExtJsonValueRef QExtJsonObject::operator[](const QString &key)
{
    return QExtJsonValueRef(this, QExtTag(key).id());
}

void QExtJsonObject::remove(const QString &key)
{
    Q_D(QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON_DeleteItemFromObjectCaseSensitive(d->m_cJson, key.toLatin1().data());
#else
    d->m_object.remove(key);
#endif
}

QExtJsonValue QExtJsonObject::take(const QString &key)
{
    Q_D(QExtJsonObject);
    QExtJsonValue value(QExtJsonValue::Type_Undefined);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON *item = cJSON_DetachItemFromObjectCaseSensitive(d->m_cJson, key.toLatin1().data());
    if (item)
    {
        cJSON_Delete(value.dd_ptr->m_cJson);
        value.dd_ptr->m_cJson = item;
    }
#else
    value.dd_ptr->m_value = d->m_object.take(key);
#endif
    return value;
}

bool QExtJsonObject::contains(const QString &key) const
{
    Q_D(const QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return cJSON_HasObjectItem(d->m_cJson, key.toLatin1().data());
#else
    return d->m_object.contains(key);
#endif
}

void QExtJsonObject::insert(const char *key, const QExtJsonValue &value)
{
    Q_D(QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (cJSON_HasObjectItem(d->m_cJson, key))
    {
        cJSON_ReplaceItemInObjectCaseSensitive(d->m_cJson, key, cJSON_Duplicate(value.dd_ptr->m_cJson, true));
    }
    else
    {
        cJSON_AddItemToObject(d->m_cJson, key, cJSON_Duplicate(value.dd_ptr->m_cJson, true));
    }
#else
    d->m_object.insert(key, value.dd_ptr->m_value);
#endif
}

void QExtJsonObject::insert(const QString &key, const QExtJsonValue &value)
{
    this->insert(key.toLatin1().data(), value);
}

bool QExtJsonObject::operator==(const QExtJsonObject &other) const
{
    Q_D(const QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return cJSON_Compare(d->m_cJson, other.dd_ptr->m_cJson, true);
#else
    return d->m_object == other.dd_ptr->m_object;
#endif
}

bool QExtJsonObject::operator!=(const QExtJsonObject &other) const
{
    return !(*this == other);
}

uint qHash(const QExtJsonObject &object, uint seed)
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return (qulonglong)object.dd_ptr->m_cJson;
#else
    return qHash(object.dd_ptr->m_object);
#endif
}

#if !defined(QT_NO_DEBUG_STREAM) && !defined(QT_JSON_READONLY)
QDebug operator<<(QDebug dbg, const QExtJsonObject &object)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))
    QDebugStateSaver saver(dbg);
#endif
    if (object.isEmpty())
    {
        dbg << "QExtJsonObject()";
        return dbg;
    }
    QExtJsonDocument doc(object);
    // print as utf-8 string without extra quotation marks
    dbg.nospace() << "QExtJsonObject(" << doc.toJson(false).constData() << ")";
    return dbg;
}
#endif

#ifndef QT_NO_DATASTREAM
QDataStream &operator<<(QDataStream &stream, const QExtJsonObject &object)
{
    QExtJsonDocument doc(object);
    stream << doc.toJson(false);
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QExtJsonObject &object)
{
    QExtJsonDocument doc;
    stream >> doc;
    object = doc.object();
    return stream;
}
#endif


/***********************************************************************************************************************
 * QExtJsonArray
***********************************************************************************************************************/
QExtJsonArrayPrivate::QExtJsonArrayPrivate(QExtJsonArray *q)
    : q_ptr(q)
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    m_cJson = QEXT_NULLPTR;
#endif
}

QExtJsonArrayPrivate::~QExtJsonArrayPrivate()
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (m_cJson)
    {
        cJSON_Delete(m_cJson);
        m_cJson = QEXT_NULLPTR;
    }
#endif
}

QExtJsonArray::QExtJsonArray()
    : dd_ptr(new QExtJsonArrayPrivate(this))
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    Q_D(QExtJsonArray);
    d->m_cJson = cJSON_CreateArray();
#endif
}

QExtJsonArray::QExtJsonArray(const QExtJsonArray::InitArgList &args)
    : dd_ptr(new QExtJsonArrayPrivate(this))
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_CreateArray();
    QList<QExtJsonValue>::ConstIterator iter;
    for (iter = args.begin(); iter < args.end(); ++iter)
    {
        cJSON_AddItemToArray(d->m_cJson, cJSON_Duplicate((*iter).dd_ptr->m_cJson, true));
    }
#else
    QList<QExtJsonValue>::ConstIterator iter;
    for (iter = args.begin(); iter < args.end(); ++iter)
    {
        d->m_array.append((*iter).dd_ptr->m_value);
    }
#endif
}

QExtJsonArray::QExtJsonArray(const QExtJsonValue &arg)
    : dd_ptr(new QExtJsonArrayPrivate(this))
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_CreateArray();
    cJSON_AddItemToArray(d->m_cJson, cJSON_Duplicate(arg.dd_ptr->m_cJson, true));
#else
    d->m_array.append(arg.dd_ptr->m_value);
#endif
}

QExtJsonArray::QExtJsonArray(const QExtJsonArray &other)
    : dd_ptr(new QExtJsonArrayPrivate(this))
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_Duplicate(other.dd_ptr->m_cJson, true);
#else
    d->m_array = other.dd_ptr->m_array;
#endif
}

QExtJsonArray::~QExtJsonArray()
{
    delete dd_ptr;
    dd_ptr = QEXT_NULLPTR;
}

QExtJsonArray &QExtJsonArray::operator =(const QExtJsonArray &other)
{
    if (this != &other)
    {
        Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
        cJSON_Delete(d->m_cJson);
        d->m_cJson = cJSON_Duplicate(other.dd_ptr->m_cJson, true);
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
    QStringList::ConstIterator iter;
    for (iter = list.begin(); iter != list.end(); ++iter)
    {
        const QString &string = *iter;
        cJSON_AddItemToArray(array.dd_ptr->m_cJson, cJSON_CreateString(string.toLatin1().data()));
    }
#else
    array.dd_ptr->m_array = QJsonArray::fromStringList(list);
#endif
    return array;
}

//QExtJsonArray QExtJsonArray::fromVariantList(const QVariantList &list)
//{
//    QExtJsonArray array;
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    array.dd_ptr->m_array = QJsonArray::fromVariantList(list);
//#endif
//    return array;
//}

//QVariantList QExtJsonArray::toVariantList() const
//{
//    Q_D(const QExtJsonArray);
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    return d->m_array.toVariantList();
//#endif
//}

int QExtJsonArray::size() const
{
    Q_D(const QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return cJSON_GetArraySize(d->m_cJson);
#else
    return d->m_array.size();
#endif
}

bool QExtJsonArray::isEmpty() const
{
    return this->size() <= 0;
}

QExtJsonValue QExtJsonArray::at(int index) const
{
    QExtJsonValue value(QExtJsonValue::Type_Undefined);
    Q_D(const QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON *item = cJSON_GetArrayItem(d->m_cJson, index);
    if (item)
    {
        cJSON_Delete(value.dd_ptr->m_cJson);
        value.dd_ptr->m_cJson = cJSON_Duplicate(item, true);
    }
#else
    value.dd_ptr->m_value = d->m_array.at(index);
#endif
    return value;
}

QExtJsonValue QExtJsonArray::first() const
{
    return this->at(0);
}

QExtJsonValue QExtJsonArray::last() const
{
    return this->at(this->size() - 1);
}

void QExtJsonArray::prepend(const QExtJsonValue &value)
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON_InsertItemInArray(d->m_cJson, 0, cJSON_Duplicate(value.dd_ptr->m_cJson, true));
#else
    d->m_array.prepend(value.dd_ptr->m_value);
#endif
}

void QExtJsonArray::append(const QExtJsonValue &value)
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON *newItem = value.isUndefined() ? cJSON_CreateNull() : cJSON_Duplicate(value.dd_ptr->m_cJson, true);
    cJSON_AddItemToArray(d->m_cJson, newItem);
#else
    d->m_array.append(value.dd_ptr->m_value);
#endif
}

void QExtJsonArray::removeAt(int index)
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON_DeleteItemFromArray(d->m_cJson, index);
#else
    d->m_array.removeAt(index);
#endif
}

QExtJsonValue QExtJsonArray::takeAt(int index)
{
    QExtJsonValue value(QExtJsonValue::Type_Undefined);
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON *item = cJSON_DetachItemFromArray(d->m_cJson, index);
    if (item)
    {
        cJSON_Delete(value.dd_ptr->m_cJson);
        value.dd_ptr->m_cJson = item;
    }
#else
    value.dd_ptr->m_value = d->m_array.takeAt(index);
#endif
    return value;
}

void QExtJsonArray::insert(int index, const QExtJsonValue &value)
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON_InsertItemInArray(d->m_cJson, index, cJSON_Duplicate(value.dd_ptr->m_cJson, true));
#else
    d->m_array.insert(index, value.dd_ptr->m_value);
#endif
}

void QExtJsonArray::replace(int index, const QExtJsonValue &value)
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON_ReplaceItemInArray(d->m_cJson, index, cJSON_Duplicate(value.dd_ptr->m_cJson, true));
#else
    d->m_array.replace(index, value.dd_ptr->m_value);
#endif
}

bool QExtJsonArray::contains(const QExtJsonValue &element) const
{
    Q_D(const QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    for (int i = 0; i < cJSON_GetArraySize(d->m_cJson); ++i)
    {
        cJSON *item = cJSON_GetArrayItem(d->m_cJson, i);
        if (item && cJSON_Compare(item, element.dd_ptr->m_cJson, true))
        {
            return true;
        }
    }
    return false;
#else
    return d->m_array.contains(element.dd_ptr->m_value);
#endif
}

QExtJsonValueRef QExtJsonArray::operator[](int index)
{
    Q_ASSERT(!this->isEmpty() && index >= 0 && index < this->size());
    return QExtJsonValueRef(this, index);
}

QExtJsonValue QExtJsonArray::operator[](int index) const
{
    return this->at(index);
}

bool QExtJsonArray::operator==(const QExtJsonArray &other) const
{
    Q_D(const QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return cJSON_Compare(d->m_cJson, other.dd_ptr->m_cJson, true);
#else
    return d->m_array == other.dd_ptr->m_array;
#endif
}

bool QExtJsonArray::operator!=(const QExtJsonArray &other) const
{
    return !(*this == other);
}


uint qHash(const QExtJsonArray &array, uint seed)
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return (qulonglong)array.dd_ptr->m_cJson;
#else
    return qHash(array.dd_ptr->m_array);
#endif
}

#if !defined(QT_NO_DEBUG_STREAM) && !defined(QT_JSON_READONLY)
QDebug operator<<(QDebug dbg, const QExtJsonArray &array)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))
    QDebugStateSaver saver(dbg);
#endif
    if (array.isEmpty())
    {
        dbg << "QExtJsonArray()";
        return dbg;
    }
    QExtJsonDocument doc(array);
    // print as utf-8 string without extra quotation marks
    dbg.nospace() << "QExtJsonArray(" << doc.toJson(false).constData() << ")";
    return dbg;
}
#endif

#ifndef QT_NO_DATASTREAM
QDataStream &operator<<(QDataStream &stream, const QExtJsonArray &array)
{
    QExtJsonDocument doc(array);
    stream << doc.toJson(false);
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QExtJsonArray &array)
{
    QExtJsonDocument doc;
    stream >> doc;
    array = doc.array();
    return stream;
}
#endif


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
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (m_cJson)
    {
        cJSON_Delete(m_cJson);
        m_cJson = QEXT_NULLPTR;
    }
#endif
}

QExtJsonDocument::QExtJsonDocument()
    : dd_ptr(new QExtJsonDocumentPrivate(this))
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    Q_D(QExtJsonDocument);
    d->m_cJson = cJSON_CreateRaw("");
#endif
}

QExtJsonDocument::QExtJsonDocument(const QExtJsonObject &object)
    : dd_ptr(new QExtJsonDocumentPrivate(this))
{
    Q_D(QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_Duplicate(object.dd_ptr->m_cJson, true);
#else
    d->m_document = QJsonDocument(object.dd_ptr->m_object);
#endif
}

QExtJsonDocument::QExtJsonDocument(const QExtJsonArray &array)
    : dd_ptr(new QExtJsonDocumentPrivate(this))
{
    Q_D(QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_Duplicate(array.dd_ptr->m_cJson, true);
#else
    d->m_document = QJsonDocument(array.dd_ptr->m_array);
#endif
}

QExtJsonDocument::QExtJsonDocument(const QExtJsonDocument &other)
    : dd_ptr(new QExtJsonDocumentPrivate(this))
{
    Q_D(QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->m_cJson = cJSON_Duplicate(other.dd_ptr->m_cJson, true);
#else
    d->m_document = other.dd_ptr->m_document;
#endif
}

QExtJsonDocument::~QExtJsonDocument()
{
    delete dd_ptr;
    dd_ptr = QEXT_NULLPTR;
}

QExtJsonDocument &QExtJsonDocument::operator =(const QExtJsonDocument &other)
{
    Q_D(QExtJsonDocument);
    if (this != &other)
    {
#if QEXT_FEATURE_USE_CJSON_BACKEND
        cJSON_Delete(d->m_cJson);
        d->m_cJson = cJSON_Duplicate(other.dd_ptr->m_cJson, true);
#else
        d->m_document = other.dd_ptr->m_document;
#endif
    }
    return *this;
}

//QExtJsonDocument QExtJsonDocument::fromVariant(const QVariant &variant)
//{
//    QExtJsonDocument document;
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    document.dd_ptr->m_document = QJsonDocument::fromVariant(variant);
//#endif
//    return document;
//}

//QVariant QExtJsonDocument::toVariant() const
//{
//    Q_D(const QExtJsonDocument);
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    return QVariant::fromValue(this);
//#endif
//}

QExtJsonDocument QExtJsonDocument::fromJson(const QByteArray &json, QString *error)
{
    if (error)
    {
        *error = "";
    }
    QExtJsonDocument document;
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON *cJson = cJSON_ParseWithLength(json.data(), json.length());
    if (cJson)
    {
        cJSON_Delete(document.dd_ptr->m_cJson);
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

QByteArray QExtJsonDocument::toJson(bool formatted) const
{
    Q_D(const QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    char *jsonString = formatted ? cJSON_Print(d->m_cJson) : cJSON_PrintUnformatted(d->m_cJson);
    QByteArray json(jsonString);
    free(jsonString);
    return json;
#else
    return d->m_document.toJson(formatted ? QJsonDocument::Indented : QJsonDocument::Compact);
#endif
}

bool QExtJsonDocument::isEmpty() const
{
    Q_D(const QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (cJSON_IsObject(d->m_cJson) || cJSON_IsArray(d->m_cJson))
    {
        return false;
    }
    return !d->m_cJson->string || strlen(d->m_cJson->string) <= 0;
#else
    return d->m_document.isEmpty();
#endif
}

bool QExtJsonDocument::isArray() const
{
    Q_D(const QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return cJSON_IsArray(d->m_cJson);
#else
    return d->m_document.isArray();
#endif
}

bool QExtJsonDocument::isObject() const
{
    Q_D(const QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return cJSON_IsObject(d->m_cJson);
#else
    return d->m_document.isObject();
#endif
}

QExtJsonObject QExtJsonDocument::object() const
{
    Q_D(const QExtJsonDocument);
    QExtJsonObject object;
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (this->isObject())
    {
        cJSON_Delete(object.dd_ptr->m_cJson);
        object.dd_ptr->m_cJson = cJSON_Duplicate(d->m_cJson, true);
    }
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
    if (this->isArray())
    {
        cJSON_Delete(array.dd_ptr->m_cJson);
        array.dd_ptr->m_cJson = cJSON_Duplicate(d->m_cJson, true);
    }
#else
    array.dd_ptr->m_array = d->m_document.array();
#endif
    return array;
}

void QExtJsonDocument::setObject(const QExtJsonObject &object)
{
    Q_D(QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON_Delete(d->m_cJson);
    d->m_cJson = cJSON_Duplicate(object.dd_ptr->m_cJson, true);
#else
    d->m_document.setObject(object.dd_ptr->m_object);
#endif
}

void QExtJsonDocument::setArray(const QExtJsonArray &array)
{
    Q_D(QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON_Delete(d->m_cJson);
    d->m_cJson = cJSON_Duplicate(array.dd_ptr->m_cJson, true);
#else
    d->m_document.setArray(array.dd_ptr->m_array);
#endif
}

const QExtJsonValue QExtJsonDocument::operator[](const char *key) const
{
    Q_D(const QExtJsonDocument);
    QExtJsonValue value;
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (this->isObject())
    {
        cJSON *item = cJSON_GetObjectItem(d->m_cJson, key);
        if (item)
        {
            cJSON_Delete(value.dd_ptr->m_cJson);
            value.dd_ptr->m_cJson = cJSON_Duplicate(item, true);
        }
    }
#else
    value.dd_ptr->m_value = d->m_document[key];
#endif
    return value;
}

const QExtJsonValue QExtJsonDocument::operator[](QString key) const
{
    return (*this)[key.toLatin1().data()];
}

const QExtJsonValue QExtJsonDocument::operator[](int index) const
{
    Q_D(const QExtJsonDocument);
    QExtJsonValue value;
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (this->isArray())
    {
        cJSON *item = cJSON_GetArrayItem(d->m_cJson, index);
        if (item)
        {
            cJSON_Delete(value.dd_ptr->m_cJson);
            value.dd_ptr->m_cJson = cJSON_Duplicate(item, true);
        }
    }
#else
    value.dd_ptr->m_value = d->m_document[index];
#endif
    return value;
}

bool QExtJsonDocument::operator==(const QExtJsonDocument &other) const
{
    Q_D(const QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return cJSON_Compare(d->m_cJson, other.dd_ptr->m_cJson, true);
#else
    return d->m_document == other.dd_ptr->m_document;
#endif
}

bool QExtJsonDocument::operator!=(const QExtJsonDocument &other) const
{
    return !(*this == other);
}

bool QExtJsonDocument::isNull() const
{
    Q_D(const QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return cJSON_IsNull(d->m_cJson);
#else
    return d->m_document.isNull();
#endif
}


#if !defined(QT_NO_DEBUG_STREAM) && !defined(QT_JSON_READONLY)
QDebug operator<<(QDebug dbg, const QExtJsonDocument &doc)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))
    QDebugStateSaver saver(dbg);
#endif
    if (doc.isNull())
    {
        dbg << "QExtJsonDocument()";
        return dbg;
    }
    // print as utf-8 string without extra quotation marks
    dbg.nospace() << "QExtJsonDocument(" << doc.toJson(false).constData() << ')';
    return dbg;
}
#endif

#ifndef QT_NO_DATASTREAM
QDataStream &operator<<(QDataStream &stream, const QExtJsonDocument &doc)
{
    stream << doc.toJson(false);
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QExtJsonDocument &doc)
{
    QByteArray buffer;
    stream >> buffer;
    QString parseError;
    doc = QExtJsonDocument::fromJson(buffer, &parseError);
    if (!parseError.isEmpty() && !buffer.isEmpty())
    {
        stream.setStatus(QDataStream::ReadCorruptData);
    }
    return stream;
}
#endif

