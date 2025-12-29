#include <qextJson.h>
#include <qextNumeric.h>
#include <qextTagId.h>

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

#if QEXT_FEATURE_USE_CJSON_BACKEND
#   include <cjson/cJSON.h>
#endif
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#   include <QJsonValue>
#   include <QJsonArray>
#   include <QJsonObject>
#   include <QJsonDocument>
#endif

class QEXT_CORE_API QExtJsonValuePrivate
{
public:
    explicit QExtJsonValuePrivate(QExtJsonValue *q);
    virtual ~QExtJsonValuePrivate();

    QExtJsonValue * const q_ptr;

#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON *mCJSON;
#else
    QJsonValue mValue;
#endif

private:
    QEXT_DECLARE_PUBLIC(QExtJsonValue)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtJsonValuePrivate)
};

class QEXT_CORE_API QExtJsonObjectPrivate
{
public:
    explicit QExtJsonObjectPrivate(QExtJsonObject *q);
    virtual ~QExtJsonObjectPrivate();

    QExtJsonObject * const q_ptr;

#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON *mCJSON;
#else
    QJsonObject mObject;
#endif

private:
    QEXT_DECLARE_PUBLIC(QExtJsonObject)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtJsonObjectPrivate)
};

class QEXT_CORE_API QExtJsonArrayPrivate
{
public:
    explicit QExtJsonArrayPrivate(QExtJsonArray *q);
    virtual ~QExtJsonArrayPrivate();

    QExtJsonArray * const q_ptr;

#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON *mCJSON;
#else
    QJsonArray mArray;
#endif

private:
    QEXT_DECLARE_PUBLIC(QExtJsonArray)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtJsonArrayPrivate)
};

class QEXT_CORE_API QExtJsonDocumentPrivate
{
public:
    explicit QExtJsonDocumentPrivate(QExtJsonDocument *q);
    virtual ~QExtJsonDocumentPrivate();

    QExtJsonDocument * const q_ptr;

#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON *mCJSON;
#else
    QJsonDocument mDocument;
#endif

private:
    QEXT_DECLARE_PUBLIC(QExtJsonDocument)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtJsonDocumentPrivate)
};

/***********************************************************************************************************************
 * QExtJsonValue
***********************************************************************************************************************/
QExtJsonValuePrivate::QExtJsonValuePrivate(QExtJsonValue *q)
    : q_ptr(q)
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    mCJSON = QEXT_NULLPTR;
#endif
}

QExtJsonValuePrivate::~QExtJsonValuePrivate()
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (mCJSON)
    {
        cJSON_Delete(mCJSON);
        mCJSON = QEXT_NULLPTR;
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
        d->mCJSON = cJSON_CreateNull();
        break;
    case Type_Bool:
        d->mCJSON = cJSON_CreateBool(false);
        break;
    case Type_Number:
        d->mCJSON = cJSON_CreateNumber(0);
        break;
    case Type_String:
        d->mCJSON = cJSON_CreateString("");
        break;
    case Type_Array:
        d->mCJSON = cJSON_CreateArray();
        break;
    case Type_Object:
        d->mCJSON = cJSON_CreateObject();
        break;
    default:
        d->mCJSON = cJSON_CreateRaw("");
        break;
    }
#else
    switch (type)
    {
    case Type_Null:
        d->mValue = QJsonValue::Null;
        break;
    case Type_Bool:
        d->mValue = QJsonValue::Bool;
        break;
    case Type_Number:
        d->mValue = QJsonValue::Double;
        break;
    case Type_String:
        d->mValue = QJsonValue::String;
        break;
    case Type_Array:
        d->mValue = QJsonValue::Array;
        break;
    case Type_Object:
        d->mValue = QJsonValue::Object;
        break;
    case Type_Undefined:
        d->mValue = QJsonValue::Undefined;
        break;
    }
#endif
}

QExtJsonValue::QExtJsonValue(bool boolean)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_CreateBool(boolean);
#else
    d->mValue = boolean;
#endif
}

QExtJsonValue::QExtJsonValue(double number)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_CreateNumber(number);
#else
    d->mValue = number;
#endif
}

QExtJsonValue::QExtJsonValue(int number)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_CreateNumber((double)number);
#else
    d->mValue = number;
#endif
}

QExtJsonValue::QExtJsonValue(qint64 number)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_CreateNumber((double)number);
#else
    d->mValue = double(number);
#endif
}

QExtJsonValue::QExtJsonValue(const char *string)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_CreateString(string);
#else
    d->mValue = string;
#endif
}

QExtJsonValue::QExtJsonValue(const QString &string)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_CreateString(string.toLatin1().data());
#else
    d->mValue = string;
#endif
}

QExtJsonValue::QExtJsonValue(const std::string &string)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_CreateString(string.c_str());
#else
    d->mValue = string.c_str();
#endif
}

QExtJsonValue::QExtJsonValue(const QExtJsonArray &array)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_Duplicate(array.dd_ptr->mCJSON, true);
#else
    d->mValue = array.dd_ptr->mArray;
#endif
}

QExtJsonValue::QExtJsonValue(const QExtJsonObject &object)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_Duplicate(object.dd_ptr->mCJSON, true);
#else
    d->mValue = object.dd_ptr->mObject;
#endif
}

QExtJsonValue::QExtJsonValue(const QString &key, const QExtJsonValue &value)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_CreateObject();
    cJSON_AddItemToObject(d->mCJSON, key.toLatin1().data(), cJSON_Duplicate(value.dd_ptr->mCJSON, true));
#else
    QJsonObject object;
    object.insert(key, value.dd_ptr->mValue);
    d->mValue = object;
#endif
}

QExtJsonValue::QExtJsonValue(const QExtJsonValue &other)
    : dd_ptr(new QExtJsonValuePrivate(this))
{
    Q_D(QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_Duplicate(other.dd_ptr->mCJSON, true);
#else
    d->mValue = other.dd_ptr->mValue;
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
        cJSON_Delete(d->mCJSON);
        d->mCJSON = cJSON_Duplicate(other.dd_ptr->mCJSON, true);
#else
        d->mValue = other.dd_ptr->mValue;
#endif
    }
    return *this;
}

//QExtJsonValue QExtJsonValue::fromVariant(const QVariant &variant)
//{
//    QExtJsonValue value;
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    value.dd_ptr->mValue = QJsonValue::fromVariant(variant);
//#endif
//    return value;
//}

//QVariant QExtJsonValue::toVariant() const
//{
//    Q_D(const QExtJsonValue);
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    return d->mValue.toVariant();
//#endif
//}

QExtJsonValue::TypeEnum QExtJsonValue::type() const
{
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (cJSON_IsNull(d->mCJSON))
    {
        return Type_Null;
    }
    else if (cJSON_IsBool(d->mCJSON))
    {
        return Type_Bool;
    }
    else if (cJSON_IsNumber(d->mCJSON))
    {
        return Type_Number;
    }
    else if (cJSON_IsString(d->mCJSON))
    {
        return Type_String;
    }
    else if (cJSON_IsArray(d->mCJSON))
    {
        return Type_Array;
    }
    else if (cJSON_IsObject(d->mCJSON))
    {
        return Type_Object;
    }
    else
    {
        return Type_Undefined;
    }
#else
    switch (d->mValue.type())
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
    if (cJSON_IsBool(d->mCJSON))
    {
        return cJSON_IsTrue(d->mCJSON);
    }
    return defaultValue;
#else
    return d->mValue.toBool(defaultValue);
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
    if (cJSON_IsNumber(d->mCJSON))
    {
        return cJSON_GetNumberValue(d->mCJSON);
    }
    return defaultValue;
#else
    return d->mValue.toDouble(defaultValue);
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
    if (cJSON_IsString(d->mCJSON))
    {
        return cJSON_GetStringValue(d->mCJSON);
    }
    return defaultValue;
#else
    return d->mValue.toString(defaultValue);
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
    cJSON_Delete(array.dd_ptr->mCJSON);
    array.dd_ptr->mCJSON = cJSON_Duplicate(cJSON_IsArray(d->mCJSON) ? d->mCJSON : defaultValue.dd_ptr->mCJSON, true);
#else
    array.dd_ptr->mArray = d->mValue.toArray(defaultValue.dd_ptr->mArray);
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
    cJSON_Delete(object.dd_ptr->mCJSON);
    object.dd_ptr->mCJSON = cJSON_Duplicate(cJSON_IsObject(d->mCJSON) ? d->mCJSON : defaultValue.dd_ptr->mCJSON, true);
#else
    object.dd_ptr->mObject = d->mValue.toObject(defaultValue.dd_ptr->mObject);
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
    if (cJSON_IsObject(d->mCJSON))
    {
        cJSON *item = cJSON_GetObjectItem(d->mCJSON, key);
        if (item)
        {
            cJSON_Delete(value.dd_ptr->mCJSON);
            value.dd_ptr->mCJSON = cJSON_Duplicate(item, true);
        }
    }
#else
    value.dd_ptr->mValue = d->mValue[key];
#endif
    return value;
}

const QExtJsonValue QExtJsonValue::operator[](int index) const
{
    QExtJsonValue value;
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (cJSON_IsArray(d->mCJSON))
    {
        cJSON *item = cJSON_GetArrayItem(d->mCJSON, index);
        if (item)
        {
            cJSON_Delete(value.dd_ptr->mCJSON);
            value.dd_ptr->mCJSON = cJSON_Duplicate(item, true);
        }
    }
#else
    value.dd_ptr->mValue = d->mValue[index];
#endif
    return value;
}

bool QExtJsonValue::operator==(const QExtJsonValue &other) const
{
    Q_D(const QExtJsonValue);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return cJSON_Compare(d->mCJSON, other.dd_ptr->mCJSON, true);
#else
    return d->mValue == other.dd_ptr->mValue;
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
        o->insert(QExtTagId(index).name().data(), val);
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
        o->insert(QExtTagId(index).name().data(), val.toValue());
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
    return is_object ? o->value(QExtTagId(index).name()) : a->at(index);
}


uint qHash(const QExtJsonValue &value, uint seed)
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    switch (value.type())
    {
    case QExtJsonValue::Type_Null:
        return qHash(value.dd_ptr->mCJSON, seed);
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
    return qHash(value.dd_ptr->mValue);
#endif
}

/* securely comparison of floating-point variables */
//static bool compare_double(double a, double b)
//{
//    double maxVal = fabs(a) > fabs(b) ? fabs(a) : fabs(b);
//    return (fabs(a - b) <= maxVal * DBL_EPSILON);
//}
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
    //    dbg << o.dd_ptr->mValue;
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
    mCJSON = QEXT_NULLPTR;
#endif
}

QExtJsonObjectPrivate::~QExtJsonObjectPrivate()
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (mCJSON)
    {
        cJSON_Delete(mCJSON);
        mCJSON = QEXT_NULLPTR;
    }
#endif
}

QExtJsonObject::QExtJsonObject()
    : dd_ptr(new QExtJsonObjectPrivate(this))
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    Q_D(QExtJsonObject);
    d->mCJSON = cJSON_CreateObject();
#endif
}

QExtJsonObject::QExtJsonObject(const QExtJsonObject &other)
    : dd_ptr(new QExtJsonObjectPrivate(this))
{
    Q_D(QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_Duplicate(other.dd_ptr->mCJSON, true);
#else
    d->mObject = other.dd_ptr->mObject;
#endif
}

QExtJsonObject::QExtJsonObject(const InitArgList &args)
    : dd_ptr(new QExtJsonObjectPrivate(this))
{
    Q_D(QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_CreateObject();
    InitArgList::ConstIterator iter;
    for (iter = args.begin(); iter != args.end(); ++iter)
    {
        const InitArg &arg = *iter;
        cJSON_AddItemToObject(d->mCJSON, arg.first.toLatin1().data(), cJSON_Duplicate(arg.second.dd_ptr->mCJSON, true));
    }
#else
    InitArgList::ConstIterator iter;
    for (iter = args.begin(); iter != args.end(); ++iter)
    {
        d->mObject.insert((*iter).first, (*iter).second.dd_ptr->mValue);
    }
#endif
}

QExtJsonObject::QExtJsonObject(const QString &key, const QExtJsonValue &value)
    : dd_ptr(new QExtJsonObjectPrivate(this))
{
    Q_D(QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_CreateObject();
    cJSON_AddItemToObject(d->mCJSON, key.toLatin1().data(), cJSON_Duplicate(value.dd_ptr->mCJSON, true));
#else
    d->mObject.insert(key, value.dd_ptr->mValue);
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
        cJSON_Delete(d->mCJSON);
        d->mCJSON = cJSON_Duplicate(other.dd_ptr->mCJSON, true);
#else
        d->mObject = other.dd_ptr->mObject;
#endif
    }
    return *this;
}

//QExtJsonObject QExtJsonObject::fromVariantMap(const QVariantMap &map)
//{
//    QExtJsonObject object;
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    object.dd_ptr->mObject = QJsonObject::fromVariantMap(map);
//#endif
//    return object;
//}

//QVariantMap QExtJsonObject::toVariantMap() const
//{
//    Q_D(const QExtJsonObject);
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    return d->mObject.toVariantMap();
//#endif
//}

//QExtJsonObject QExtJsonObject::fromVariantHash(const QVariantHash &map)
//{
//    QExtJsonObject object;
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    object.dd_ptr->mObject = QJsonObject::fromVariantHash(map);
//#endif
//    return object;
//}

//QVariantHash QExtJsonObject::toVariantHash() const
//{
//    Q_D(const QExtJsonObject);
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    return d->mObject.toVariantHash();
//#endif
//}

QStringList QExtJsonObject::keys() const
{
    Q_D(const QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    QStringList keys;
    cJSON *item = d->mCJSON->child;
    while (item != NULL)
    {
        keys.append(item->string);
        item = item->next;
    }
    qSort(keys.begin(), keys.end());
    return keys;
#else
    return d->mObject.keys();
#endif
}

int QExtJsonObject::size() const
{
    Q_D(const QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    int size = 0;
    cJSON *child = d->mCJSON->child;
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
    return d->mObject.size();
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
    cJSON *item = cJSON_GetObjectItem(d->mCJSON, key.toLatin1().data());
    if (item)
    {
        cJSON_Delete(value.dd_ptr->mCJSON);
        value.dd_ptr->mCJSON = cJSON_Duplicate(item, true);
    }
#else
    value.dd_ptr->mValue = d->mObject.value(key);
#endif
    return value;
}

QExtJsonValue QExtJsonObject::operator[](const QString &key) const
{
    return this->value(key);
}

QExtJsonValueRef QExtJsonObject::operator[](const QString &key)
{
    return QExtJsonValueRef(this, QExtTagId(key).id());
}

void QExtJsonObject::remove(const QString &key)
{
    Q_D(QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON_DeleteItemFromObjectCaseSensitive(d->mCJSON, key.toLatin1().data());
#else
    d->mObject.remove(key);
#endif
}

QExtJsonValue QExtJsonObject::take(const QString &key)
{
    Q_D(QExtJsonObject);
    QExtJsonValue value(QExtJsonValue::Type_Undefined);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON *item = cJSON_DetachItemFromObjectCaseSensitive(d->mCJSON, key.toLatin1().data());
    if (item)
    {
        cJSON_Delete(value.dd_ptr->mCJSON);
        value.dd_ptr->mCJSON = item;
    }
#else
    value.dd_ptr->mValue = d->mObject.take(key);
#endif
    return value;
}

bool QExtJsonObject::contains(const QString &key) const
{
    Q_D(const QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return cJSON_HasObjectItem(d->mCJSON, key.toLatin1().data());
#else
    return d->mObject.contains(key);
#endif
}

void QExtJsonObject::insert(const char *key, const QExtJsonValue &value)
{
    Q_D(QExtJsonObject);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (cJSON_HasObjectItem(d->mCJSON, key))
    {
        cJSON_ReplaceItemInObjectCaseSensitive(d->mCJSON, key, cJSON_Duplicate(value.dd_ptr->mCJSON, true));
    }
    else
    {
        cJSON_AddItemToObject(d->mCJSON, key, cJSON_Duplicate(value.dd_ptr->mCJSON, true));
    }
#else
    d->mObject.insert(key, value.dd_ptr->mValue);
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
    return cJSON_Compare(d->mCJSON, other.dd_ptr->mCJSON, true);
#else
    return d->mObject == other.dd_ptr->mObject;
#endif
}

bool QExtJsonObject::operator!=(const QExtJsonObject &other) const
{
    return !(*this == other);
}

uint qHash(const QExtJsonObject &object, uint seed)
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return (qulonglong)object.dd_ptr->mCJSON;
#else
    return qHash(object.dd_ptr->mObject);
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
    mCJSON = QEXT_NULLPTR;
#endif
}

QExtJsonArrayPrivate::~QExtJsonArrayPrivate()
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (mCJSON)
    {
        cJSON_Delete(mCJSON);
        mCJSON = QEXT_NULLPTR;
    }
#endif
}

QExtJsonArray::QExtJsonArray()
    : dd_ptr(new QExtJsonArrayPrivate(this))
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    Q_D(QExtJsonArray);
    d->mCJSON = cJSON_CreateArray();
#endif
}

QExtJsonArray::QExtJsonArray(const QExtJsonArray::InitArgList &args)
    : dd_ptr(new QExtJsonArrayPrivate(this))
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_CreateArray();
    QList<QExtJsonValue>::ConstIterator iter;
    for (iter = args.begin(); iter < args.end(); ++iter)
    {
        cJSON_AddItemToArray(d->mCJSON, cJSON_Duplicate((*iter).dd_ptr->mCJSON, true));
    }
#else
    QList<QExtJsonValue>::ConstIterator iter;
    for (iter = args.begin(); iter < args.end(); ++iter)
    {
        d->mArray.append((*iter).dd_ptr->mValue);
    }
#endif
}

QExtJsonArray::QExtJsonArray(const QExtJsonValue &arg)
    : dd_ptr(new QExtJsonArrayPrivate(this))
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_CreateArray();
    cJSON_AddItemToArray(d->mCJSON, cJSON_Duplicate(arg.dd_ptr->mCJSON, true));
#else
    d->mArray.append(arg.dd_ptr->mValue);
#endif
}

QExtJsonArray::QExtJsonArray(const QExtJsonArray &other)
    : dd_ptr(new QExtJsonArrayPrivate(this))
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_Duplicate(other.dd_ptr->mCJSON, true);
#else
    d->mArray = other.dd_ptr->mArray;
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
        cJSON_Delete(d->mCJSON);
        d->mCJSON = cJSON_Duplicate(other.dd_ptr->mCJSON, true);
#else
        d->mArray = other.dd_ptr->mArray;
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
        cJSON_AddItemToArray(array.dd_ptr->mCJSON, cJSON_CreateString(string.toLatin1().data()));
    }
#else
    array.dd_ptr->mArray = QJsonArray::fromStringList(list);
#endif
    return array;
}

//QExtJsonArray QExtJsonArray::fromVariantList(const QVariantList &list)
//{
//    QExtJsonArray array;
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    array.dd_ptr->mArray = QJsonArray::fromVariantList(list);
//#endif
//    return array;
//}

//QVariantList QExtJsonArray::toVariantList() const
//{
//    Q_D(const QExtJsonArray);
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    return d->mArray.toVariantList();
//#endif
//}

int QExtJsonArray::size() const
{
    Q_D(const QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return cJSON_GetArraySize(d->mCJSON);
#else
    return d->mArray.size();
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
    cJSON *item = cJSON_GetArrayItem(d->mCJSON, index);
    if (item)
    {
        cJSON_Delete(value.dd_ptr->mCJSON);
        value.dd_ptr->mCJSON = cJSON_Duplicate(item, true);
    }
#else
    value.dd_ptr->mValue = d->mArray.at(index);
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
    cJSON_InsertItemInArray(d->mCJSON, 0, cJSON_Duplicate(value.dd_ptr->mCJSON, true));
#else
    d->mArray.prepend(value.dd_ptr->mValue);
#endif
}

void QExtJsonArray::append(const QExtJsonValue &value)
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON *newItem = value.isUndefined() ? cJSON_CreateNull() : cJSON_Duplicate(value.dd_ptr->mCJSON, true);
    cJSON_AddItemToArray(d->mCJSON, newItem);
#else
    d->mArray.append(value.dd_ptr->mValue);
#endif
}

void QExtJsonArray::removeAt(int index)
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON_DeleteItemFromArray(d->mCJSON, index);
#else
    d->mArray.removeAt(index);
#endif
}

QExtJsonValue QExtJsonArray::takeAt(int index)
{
    QExtJsonValue value(QExtJsonValue::Type_Undefined);
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON *item = cJSON_DetachItemFromArray(d->mCJSON, index);
    if (item)
    {
        cJSON_Delete(value.dd_ptr->mCJSON);
        value.dd_ptr->mCJSON = item;
    }
#else
    value.dd_ptr->mValue = d->mArray.takeAt(index);
#endif
    return value;
}

void QExtJsonArray::insert(int index, const QExtJsonValue &value)
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON_InsertItemInArray(d->mCJSON, index, cJSON_Duplicate(value.dd_ptr->mCJSON, true));
#else
    d->mArray.insert(index, value.dd_ptr->mValue);
#endif
}

void QExtJsonArray::replace(int index, const QExtJsonValue &value)
{
    Q_D(QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON_ReplaceItemInArray(d->mCJSON, index, cJSON_Duplicate(value.dd_ptr->mCJSON, true));
#else
    d->mArray.replace(index, value.dd_ptr->mValue);
#endif
}

bool QExtJsonArray::contains(const QExtJsonValue &element) const
{
    Q_D(const QExtJsonArray);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    for (int i = 0; i < cJSON_GetArraySize(d->mCJSON); ++i)
    {
        cJSON *item = cJSON_GetArrayItem(d->mCJSON, i);
        if (item && cJSON_Compare(item, element.dd_ptr->mCJSON, true))
        {
            return true;
        }
    }
    return false;
#else
    return d->mArray.contains(element.dd_ptr->mValue);
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
    return cJSON_Compare(d->mCJSON, other.dd_ptr->mCJSON, true);
#else
    return d->mArray == other.dd_ptr->mArray;
#endif
}

bool QExtJsonArray::operator!=(const QExtJsonArray &other) const
{
    return !(*this == other);
}


uint qHash(const QExtJsonArray &array, uint seed)
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return (qulonglong)array.dd_ptr->mCJSON;
#else
    return qHash(array.dd_ptr->mArray);
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
    mCJSON = QEXT_NULLPTR;
#endif
}

QExtJsonDocumentPrivate::~QExtJsonDocumentPrivate()
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (mCJSON)
    {
        cJSON_Delete(mCJSON);
        mCJSON = QEXT_NULLPTR;
    }
#endif
}

QExtJsonDocument::QExtJsonDocument()
    : dd_ptr(new QExtJsonDocumentPrivate(this))
{
#if QEXT_FEATURE_USE_CJSON_BACKEND
    Q_D(QExtJsonDocument);
    d->mCJSON = cJSON_CreateRaw("");
#endif
}

QExtJsonDocument::QExtJsonDocument(const QExtJsonObject &object)
    : dd_ptr(new QExtJsonDocumentPrivate(this))
{
    Q_D(QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_Duplicate(object.dd_ptr->mCJSON, true);
#else
    d->mDocument = QJsonDocument(object.dd_ptr->mObject);
#endif
}

QExtJsonDocument::QExtJsonDocument(const QExtJsonArray &array)
    : dd_ptr(new QExtJsonDocumentPrivate(this))
{
    Q_D(QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_Duplicate(array.dd_ptr->mCJSON, true);
#else
    d->mDocument = QJsonDocument(array.dd_ptr->mArray);
#endif
}

QExtJsonDocument::QExtJsonDocument(const QExtJsonDocument &other)
    : dd_ptr(new QExtJsonDocumentPrivate(this))
{
    Q_D(QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    d->mCJSON = cJSON_Duplicate(other.dd_ptr->mCJSON, true);
#else
    d->mDocument = other.dd_ptr->mDocument;
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
        cJSON_Delete(d->mCJSON);
        d->mCJSON = cJSON_Duplicate(other.dd_ptr->mCJSON, true);
#else
        d->mDocument = other.dd_ptr->mDocument;
#endif
    }
    return *this;
}

//QExtJsonDocument QExtJsonDocument::fromVariant(const QVariant &variant)
//{
//    QExtJsonDocument document;
//#if QEXT_FEATURE_USE_CJSON_BACKEND

//#else
//    document.dd_ptr->mDocument = QJsonDocument::fromVariant(variant);
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
        cJSON_Delete(document.dd_ptr->mCJSON);
        document.dd_ptr->mCJSON = cJson;
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
        document.dd_ptr->mDocument = jsonDoc;
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
    char *jsonString = formatted ? cJSON_Print(d->mCJSON) : cJSON_PrintUnformatted(d->mCJSON);
    QByteArray json(jsonString);
    free(jsonString);
    return json;
#else
    return d->mDocument.toJson(formatted ? QJsonDocument::Indented : QJsonDocument::Compact);
#endif
}

bool QExtJsonDocument::isEmpty() const
{
    Q_D(const QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (cJSON_IsObject(d->mCJSON) || cJSON_IsArray(d->mCJSON))
    {
        return false;
    }
    return !d->mCJSON->string || strlen(d->mCJSON->string) <= 0;
#else
    return d->mDocument.isEmpty();
#endif
}

bool QExtJsonDocument::isArray() const
{
    Q_D(const QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return cJSON_IsArray(d->mCJSON);
#else
    return d->mDocument.isArray();
#endif
}

bool QExtJsonDocument::isObject() const
{
    Q_D(const QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return cJSON_IsObject(d->mCJSON);
#else
    return d->mDocument.isObject();
#endif
}

QExtJsonObject QExtJsonDocument::object() const
{
    Q_D(const QExtJsonDocument);
    QExtJsonObject object;
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (this->isObject())
    {
        cJSON_Delete(object.dd_ptr->mCJSON);
        object.dd_ptr->mCJSON = cJSON_Duplicate(d->mCJSON, true);
    }
#else
    object.dd_ptr->mObject =  d->mDocument.object();
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
        cJSON_Delete(array.dd_ptr->mCJSON);
        array.dd_ptr->mCJSON = cJSON_Duplicate(d->mCJSON, true);
    }
#else
    array.dd_ptr->mArray = d->mDocument.array();
#endif
    return array;
}

void QExtJsonDocument::setObject(const QExtJsonObject &object)
{
    Q_D(QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON_Delete(d->mCJSON);
    d->mCJSON = cJSON_Duplicate(object.dd_ptr->mCJSON, true);
#else
    d->mDocument.setObject(object.dd_ptr->mObject);
#endif
}

void QExtJsonDocument::setArray(const QExtJsonArray &array)
{
    Q_D(QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON_Delete(d->mCJSON);
    d->mCJSON = cJSON_Duplicate(array.dd_ptr->mCJSON, true);
#else
    d->mDocument.setArray(array.dd_ptr->mArray);
#endif
}

const QExtJsonValue QExtJsonDocument::operator[](const char *key) const
{
    Q_D(const QExtJsonDocument);
    QExtJsonValue value;
#if QEXT_FEATURE_USE_CJSON_BACKEND
    if (this->isObject())
    {
        cJSON *item = cJSON_GetObjectItem(d->mCJSON, key);
        if (item)
        {
            cJSON_Delete(value.dd_ptr->mCJSON);
            value.dd_ptr->mCJSON = cJSON_Duplicate(item, true);
        }
    }
#else
    value.dd_ptr->mValue = d->mDocument[key];
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
        cJSON *item = cJSON_GetArrayItem(d->mCJSON, index);
        if (item)
        {
            cJSON_Delete(value.dd_ptr->mCJSON);
            value.dd_ptr->mCJSON = cJSON_Duplicate(item, true);
        }
    }
#else
    value.dd_ptr->mValue = d->mDocument[index];
#endif
    return value;
}

bool QExtJsonDocument::operator==(const QExtJsonDocument &other) const
{
    Q_D(const QExtJsonDocument);
#if QEXT_FEATURE_USE_CJSON_BACKEND
    return cJSON_Compare(d->mCJSON, other.dd_ptr->mCJSON, true);
#else
    return d->mDocument == other.dd_ptr->mDocument;
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
    return cJSON_IsNull(d->mCJSON);
#else
    return d->mDocument.isNull();
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
