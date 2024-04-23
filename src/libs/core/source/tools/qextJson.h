#ifndef _QEXTJSON_H
#define _QEXTJSON_H

#include <qextGlobal.h>

#include <QDebug>
#include <QDataStream>
#include <QStringList>

/***********************************************************************************************************************
 * QExtJsonValue
***********************************************************************************************************************/
class QExtJsonArray;
class QExtJsonObject;
class QExtJsonValuePrivate;
class QEXT_CORE_API QExtJsonValue
{
public:
    enum TypeEnum
    {
        Type_Null =  0x0,
        Type_Bool = 0x1,
        Type_Number = 0x2, // max 17 decimal places of precision
        Type_String = 0x3,
        Type_Array = 0x4,
        Type_Object = 0x5,
        Type_Undefined = 0x80
    };

    enum
    {
        NumberMin = -9007199254740992, // -2^53
        NumberMax = +9007199254740992  // +2^53
    };

    QExtJsonValue(TypeEnum type = Type_Null);
    QExtJsonValue(bool boolean);
    QExtJsonValue(double number);
    QExtJsonValue(int number);
    QExtJsonValue(qint64 number);
    QExtJsonValue(const char *string);
    QExtJsonValue(const QString &string);
    QExtJsonValue(const std::string &string);
    QExtJsonValue(const QExtJsonArray &array);
    QExtJsonValue(const QExtJsonObject &object);
    QExtJsonValue(const QString &key, const QExtJsonValue &value);
    virtual ~QExtJsonValue();

    QExtJsonValue(const QExtJsonValue &other);
    QExtJsonValue &operator =(const QExtJsonValue &other);

    // void swap(QExtJsonValue &other) noexcept;

//    static QExtJsonValue fromVariant(const QVariant &variant);
//    QVariant toVariant() const;

    TypeEnum type() const;
    inline bool isNull() const { return type() == Type_Null; }
    inline bool isBool() const { return type() == Type_Bool; }
    inline bool isNumber() const { return type() == Type_Number; }
    inline bool isString() const { return type() == Type_String; }
    inline bool isArray() const { return type() == Type_Array; }
    inline bool isObject() const { return type() == Type_Object; }
    inline bool isUndefined() const { return type() == Type_Undefined; }

    int toInt(int defaultValue = 0) const;
    bool toBool(bool defaultValue = false) const;
    double toDouble(double defaultValue = 0) const;
    qint64 toInteger(qint64 defaultValue = 0) const;
    QString toString() const { return this->toString(QString()); }
    QString toString(const QString &defaultValue) const;
    QExtJsonArray toArray() const;
    QExtJsonArray toArray(const QExtJsonArray &defaultValue) const;
    QExtJsonObject toObject() const;
    QExtJsonObject toObject(const QExtJsonObject &defaultValue) const;

    const QExtJsonValue operator[](const QString &key) const;
    const QExtJsonValue operator[](const char *key) const;
    const QExtJsonValue operator[](int index) const;

    bool operator==(const QExtJsonValue &other) const;
    bool operator!=(const QExtJsonValue &other) const;

protected:
    QExtJsonValuePrivate *dd_ptr;

    friend QEXT_CORE_API uint qHash(const QExtJsonValue &value, uint seed);
    friend QEXT_CORE_API QDebug operator<<(QDebug, const QExtJsonValue &);

private:
    friend class QExtJsonArray;
    friend class QExtJsonObject;
    friend class QExtJsonDocument;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtJsonValue)
};

class QEXT_CORE_API QExtJsonValueRef
{
public:
    QExtJsonValueRef(QExtJsonArray *array, int idx) : a(array), is_object(false), index(static_cast<uint>(idx)) {}
    QExtJsonValueRef(QExtJsonObject *object, int idx) : o(object), is_object(true), index(static_cast<uint>(idx)) {}
    QExtJsonValueRef(const QExtJsonValueRef &other);
    QExtJsonValueRef(const QExtJsonValue &value);

    inline operator QExtJsonValue() const { return toValue(); }
    QExtJsonValueRef &operator = (const QExtJsonValue &val);
    QExtJsonValueRef &operator = (const QExtJsonValueRef &val);

//    QVariant toVariant() const;
    inline QExtJsonValue::TypeEnum type() const { return toValue().type(); }
    inline bool isNull() const { return type() == QExtJsonValue::Type_Null; }
    inline bool isBool() const { return type() == QExtJsonValue::Type_Bool; }
    inline bool isDouble() const { return type() == QExtJsonValue::Type_Null; }
    inline bool isString() const { return type() == QExtJsonValue::Type_String; }
    inline bool isArray() const { return type() == QExtJsonValue::Type_Array; }
    inline bool isObject() const { return type() == QExtJsonValue::Type_Object; }
    inline bool isUndefined() const { return type() == QExtJsonValue::Type_Undefined; }

    inline bool toBool() const { return toValue().toBool(); }
    inline int toInt() const { return toValue().toInt(); }
    inline double toDouble() const { return toValue().toDouble(); }
    inline QString toString() const { return toValue().toString(); }
    QExtJsonArray toArray() const;
    QExtJsonObject toObject() const;

    inline bool toBool(bool defaultValue) const { return toValue().toBool(defaultValue); }
    inline int toInt(int defaultValue) const { return toValue().toInt(defaultValue); }
    inline double toDouble(double defaultValue) const { return toValue().toDouble(defaultValue); }
    inline QString toString(const QString &defaultValue) const { return toValue().toString(defaultValue); }

    inline bool operator==(const QExtJsonValue &other) const { return toValue() == other; }
    inline bool operator!=(const QExtJsonValue &other) const { return toValue() != other; }

private:
    QExtJsonValue toValue() const;

    union
    {
        QExtJsonArray *a;
        QExtJsonObject *o;
    };
    uint is_object : 1;
    uint index : 31;
};

class QExtJsonValuePtr
{
    QExtJsonValue value;
public:
    explicit QExtJsonValuePtr(const QExtJsonValue& val) : value(val) {}

    QExtJsonValue& operator*() { return value; }
    QExtJsonValue* operator->() { return &value; }
};

class QExtJsonValueRefPtr
{
    QExtJsonValueRef valueRef;
public:
    QExtJsonValueRefPtr(QExtJsonArray *array, int idx) : valueRef(array, idx) {}
    QExtJsonValueRefPtr(QExtJsonObject *object, int idx) : valueRef(object, idx)  {}

    QExtJsonValueRef& operator*() { return valueRef; }
    QExtJsonValueRef* operator->() { return &valueRef; }
};

Q_DECLARE_METATYPE(QExtJsonValue)

QEXT_CORE_API uint qHash(const QExtJsonValue &value, uint seed = 0);

#if !defined(QT_NO_DEBUG_STREAM) && !defined(QT_JSON_READONLY)
QEXT_CORE_API QDebug operator<<(QDebug, const QExtJsonValue &);
#endif

#ifndef QT_NO_DATASTREAM
QEXT_CORE_API QDataStream &operator<<(QDataStream &, const QExtJsonValue &);
QEXT_CORE_API QDataStream &operator>>(QDataStream &, QExtJsonValue &);
#endif


/***********************************************************************************************************************
 * QExtJsonObject
***********************************************************************************************************************/
class QExtJsonObjectPrivate;
class QEXT_CORE_API QExtJsonObject
{
public:
    typedef QPair<QString, QExtJsonValue> InitArg;
    typedef QList<InitArg> InitArgList;

    QExtJsonObject();
    QExtJsonObject(const QExtJsonObject &other);
    QExtJsonObject(const InitArgList &args);
    QExtJsonObject(const QString &key, const QExtJsonValue &value);
    virtual ~QExtJsonObject();

    QExtJsonObject &operator =(const QExtJsonObject &other);
    // void swap(QExtJsonObject &other) noexcept;

//    static QExtJsonObject fromVariantMap(const QVariantMap &map);
//    QVariantMap toVariantMap() const;
//    static QExtJsonObject fromVariantHash(const QVariantHash &map);
//    QVariantHash toVariantHash() const;

    QStringList keys() const;
    int size() const;
    inline int count() const { return size(); }
    inline int length() const { return size(); }
    bool isEmpty() const;

    QExtJsonValue value(const QString &key) const;
    QExtJsonValue operator[] (const QString &key) const;
    QExtJsonValueRef operator[] (const QString &key);

    void remove(const QString &key);
    QExtJsonValue take(const QString &key);
    bool contains(const QString &key) const;
    void insert(const char *key, const QExtJsonValue &value);
    void insert(const QString &key, const QExtJsonValue &value);

    bool operator==(const QExtJsonObject &other) const;
    bool operator!=(const QExtJsonObject &other) const;

    inline bool empty() const { return this->isEmpty(); }

protected:
    QExtJsonObjectPrivate *dd_ptr;

    friend QEXT_CORE_API uint qHash(const QExtJsonObject &object, uint seed);

private:
    friend class QExtJsonValue;
    friend class QExtJsonValueRef;
    friend class QExtJsonDocument;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtJsonObject)
};
Q_DECLARE_METATYPE(QExtJsonObject)

QEXT_CORE_API uint qHash(const QExtJsonObject &object, uint seed = 0);

#if !defined(QT_NO_DEBUG_STREAM)
QEXT_CORE_API QDebug operator<<(QDebug, const QExtJsonObject &);
#endif

#ifndef QT_NO_DATASTREAM
QEXT_CORE_API QDataStream &operator<<(QDataStream &, const QExtJsonObject &);
QEXT_CORE_API QDataStream &operator>>(QDataStream &, QExtJsonObject &);
#endif

/***********************************************************************************************************************
 * QExtJsonArray
***********************************************************************************************************************/
class QExtJsonArrayPrivate;
class QEXT_CORE_API QExtJsonArray
{
public:
    typedef QList<QExtJsonValue> InitArgList;

    QExtJsonArray();
    QExtJsonArray(const InitArgList &args);
    QExtJsonArray(const QExtJsonValue &arg);
    QExtJsonArray(const QExtJsonArray &other);
    virtual ~QExtJsonArray();

    QExtJsonArray &operator =(const QExtJsonArray &other);
    // void swap(QExtJsonArray &other) noexcept;

    static QExtJsonArray fromStringList(const QStringList &list);
//    static QExtJsonArray fromVariantList(const QVariantList &list);
//    QVariantList toVariantList() const;

    int size() const;
    inline int count() const { return this->size(); }

    bool isEmpty() const;
    QExtJsonValue at(int index) const;
    QExtJsonValue first() const;
    QExtJsonValue last() const;

    void prepend(const QExtJsonValue &value);
    void append(const QExtJsonValue &value);
    void removeAt(int index);
    QExtJsonValue takeAt(int index);
    inline void removeFirst() { this->removeAt(0); }
    inline void removeLast() { this->removeAt(this->size() - 1); }

    void insert(int index, const QExtJsonValue &value);
    void replace(int index, const QExtJsonValue &value);

    bool contains(const QExtJsonValue &element) const;
    QExtJsonValueRef operator[](int index);
    QExtJsonValue operator[](int index) const;

    bool operator==(const QExtJsonArray &other) const;
    bool operator!=(const QExtJsonArray &other) const;

    // convenience
    inline QExtJsonArray operator+(const QExtJsonValue &v) const
    { QExtJsonArray n = *this; n += v; return n; }
    inline QExtJsonArray &operator+=(const QExtJsonValue &v)
    { append(v); return *this; }
    inline QExtJsonArray &operator<< (const QExtJsonValue &v)
    { append(v); return *this; }

    // stl compatibility
    inline void push_back(const QExtJsonValue &t) { append(t); }
    inline void push_front(const QExtJsonValue &t) { prepend(t); }
    inline void pop_front() { removeFirst(); }
    inline void pop_back() { removeLast(); }
    inline bool empty() const { return isEmpty(); }

protected:
    QExtJsonArrayPrivate *dd_ptr;

    friend QEXT_CORE_API uint qHash(const QExtJsonArray &array, uint seed);

private:
    friend class QExtJsonValue;
    friend class QExtJsonDocument;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtJsonArray)
};
Q_DECLARE_METATYPE(QExtJsonArray)

QEXT_CORE_API uint qHash(const QExtJsonArray &array, uint seed = 0);

#if !defined(QT_NO_DEBUG_STREAM) && !defined(QT_JSON_READONLY)
QEXT_CORE_API QDebug operator<<(QDebug, const QExtJsonArray &);
#endif

#ifndef QT_NO_DATASTREAM
QEXT_CORE_API QDataStream &operator<<(QDataStream &, const QExtJsonArray &);
QEXT_CORE_API QDataStream &operator>>(QDataStream &, QExtJsonArray &);
#endif

/***********************************************************************************************************************
 * QExtJsonDocument
***********************************************************************************************************************/
class QExtJsonDocumentPrivate;
class QEXT_CORE_API QExtJsonDocument
{
public:
    QExtJsonDocument();
    explicit QExtJsonDocument(const QExtJsonObject &object);
    explicit QExtJsonDocument(const QExtJsonArray &array);
    virtual ~QExtJsonDocument();

    QExtJsonDocument(const QExtJsonDocument &other);
    QExtJsonDocument &operator =(const QExtJsonDocument &other);

    // void swap(QExtJsonDocument &other) noexcept;

//    static QExtJsonDocument fromVariant(const QVariant &variant);
//    QVariant toVariant() const;

    static QExtJsonDocument fromJson(const QByteArray &json, QString *error = QEXT_NULLPTR);
    QByteArray toJson(bool formatted = true) const;

    bool isEmpty() const;
    bool isArray() const;
    bool isObject() const;

    QExtJsonObject object() const;
    QExtJsonArray array() const;

    void setObject(const QExtJsonObject &object);
    void setArray(const QExtJsonArray &array);

    const QExtJsonValue operator[](const char *key) const;
    const QExtJsonValue operator[](QString key) const;
    const QExtJsonValue operator[](int index) const;

    bool operator==(const QExtJsonDocument &other) const;
    bool operator!=(const QExtJsonDocument &other) const;

    bool isNull() const;

protected:
    QExtJsonDocumentPrivate *dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtJsonDocument)
};
Q_DECLARE_METATYPE(QExtJsonDocument)

#if !defined(QT_NO_DEBUG_STREAM) && !defined(QT_JSON_READONLY)
QEXT_CORE_API QDebug operator<<(QDebug, const QExtJsonDocument &);
#endif

#ifndef QT_NO_DATASTREAM
QEXT_CORE_API QDataStream &operator<<(QDataStream &, const QExtJsonDocument &);
QEXT_CORE_API QDataStream &operator>>(QDataStream &, QExtJsonDocument &);
#endif

#endif // _QEXTJSON_H
