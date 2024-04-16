#ifndef _QEXTJSON_H
#define _QEXTJSON_H

#include <qextGlobal.h>

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
        Type_Number = 0x2,
        Type_String = 0x3,
        Type_Array = 0x4,
        Type_Object = 0x5,
        Type_Undefined = 0x80
    };

    QExtJsonValue();
    QExtJsonValue(bool boolean);
    QExtJsonValue(double number);
    QExtJsonValue(int number);
    QExtJsonValue(qint64 number);
    QExtJsonValue(QLatin1String string);
    QExtJsonValue(const QString &string);
    QExtJsonValue(const std::string &string);
    QExtJsonValue(const QExtJsonArray &array);
    QExtJsonValue(const QExtJsonObject &object);
    virtual ~QExtJsonValue();

    QExtJsonValue(const QExtJsonValue &other);
    QExtJsonValue &operator =(const QExtJsonValue &other);

    // void swap(QExtJsonValue &other) noexcept;

    static QExtJsonValue fromVariant(const QVariant &variant);
    QVariant toVariant() const;

    TypeEnum type() const;
    inline bool isNull() const { return type() == Type_Null; }
    inline bool isBool() const { return type() == Type_Bool; }
    inline bool isNumber() const { return type() == Type_Number; }
    inline bool isString() const { return type() == Type_String; }
    inline bool isArray() const { return type() == Type_Array; }
    inline bool isObject() const { return type() == Type_Object; }
    inline bool isUndefined() const { return type() == Type_Undefined; }

    bool toBool(bool defaultValue = false) const;
    int toInt(int defaultValue = 0) const;
    double toDouble(double defaultValue = 0) const;
    QString toString() const;
    QString toString(const QString &defaultValue) const;
    QExtJsonArray toArray() const;
    QExtJsonArray toArray(const QExtJsonArray &defaultValue) const;
    QExtJsonObject toObject() const;
    QExtJsonObject toObject(const QExtJsonObject &defaultValue) const;

    const QExtJsonValue operator[](const QString &key) const;
    const QExtJsonValue operator[](QStringView key) const;
    const QExtJsonValue operator[](QLatin1String key) const;
    const QExtJsonValue operator[](int index) const;

    bool operator==(const QExtJsonValue &other) const;
    bool operator!=(const QExtJsonValue &other) const;

protected:
    QScopedPointer<QExtJsonValuePrivate> dd_ptr;

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

    QVariant toVariant() const;
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

class QExtJsonObjectPrivate;
class QEXT_CORE_API QExtJsonObject
{
public:
    QExtJsonObject();
    QExtJsonObject(const QExtJsonObject &other);
    QExtJsonObject(const QList<QExtJsonValue> &args);
    virtual ~QExtJsonObject();

    QExtJsonObject &operator =(const QExtJsonObject &other);
    // void swap(QExtJsonObject &other) noexcept;

    static QExtJsonObject fromVariantMap(const QVariantMap &map);
    QVariantMap toVariantMap() const;
    static QExtJsonObject fromVariantHash(const QVariantHash &map);
    QVariantHash toVariantHash() const;

    QStringList keys() const;
    int size() const;
    inline int count() const { return size(); }
    inline int length() const { return size(); }
    bool isEmpty() const;

    QExtJsonValue value(const QString &key) const;
    QExtJsonValue value(QStringView key) const;
    QExtJsonValue operator[] (const QString &key) const;
    QExtJsonValueRef operator[] (const QString &key);

    void remove(const QString &key);
    void remove(QStringView key);
    QExtJsonValue take(const QString &key);
    QExtJsonValue take(QStringView key);
    bool contains(const QString &key) const;
    bool contains(QStringView key) const;

    bool operator==(const QExtJsonObject &other) const;
    bool operator!=(const QExtJsonObject &other) const;

    class const_iterator;

    class iterator
    {
        friend class const_iterator;
        friend class QExtJsonObject;
        QExtJsonObject *o;
        int i;

    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef int difference_type;
        typedef QExtJsonValue value_type;
        typedef QExtJsonValueRef reference;
        typedef QExtJsonValuePtr pointer;

        Q_DECL_CONSTEXPR inline iterator() : o(nullptr), i(0) {}
        Q_DECL_CONSTEXPR inline iterator(QExtJsonObject *obj, int index) : o(obj), i(index) {}

        inline QString key() const { return o->keyAt(i); }
        inline QExtJsonValueRef value() const { return QExtJsonValueRef(o, i); }
        inline QExtJsonValueRef operator*() const { return QExtJsonValueRef(o, i); }
        inline QExtJsonValueRefPtr operator->() const { return QExtJsonValueRefPtr(o, i); }
        const QExtJsonValueRef operator[](int j) { return QExtJsonValueRef(o, i + j); }

        inline bool operator==(const iterator &other) const { return i == other.i; }
        inline bool operator!=(const iterator &other) const { return i != other.i; }
        bool operator<(const iterator& other) const { return i < other.i; }
        bool operator<=(const iterator& other) const { return i <= other.i; }
        bool operator>(const iterator& other) const { return i > other.i; }
        bool operator>=(const iterator& other) const { return i >= other.i; }

        inline iterator &operator++() { ++i; return *this; }
        inline iterator operator++(int) { iterator r = *this; ++i; return r; }
        inline iterator &operator--() { --i; return *this; }
        inline iterator operator--(int) { iterator r = *this; --i; return r; }
        inline iterator operator+(int j) const { iterator r = *this; r.i += j; return r; }
        inline iterator operator-(int j) const { return operator+(-j); }
        inline iterator &operator+=(int j) { i += j; return *this; }
        inline iterator &operator-=(int j) { i -= j; return *this; }
        int operator-(iterator j) const { return i - j.i; }

    public:
        inline bool operator==(const const_iterator &other) const { return i == other.i; }
        inline bool operator!=(const const_iterator &other) const { return i != other.i; }
        bool operator<(const const_iterator& other) const { return i < other.i; }
        bool operator<=(const const_iterator& other) const { return i <= other.i; }
        bool operator>(const const_iterator& other) const { return i > other.i; }
        bool operator>=(const const_iterator& other) const { return i >= other.i; }
    };
    friend class iterator;

    class const_iterator
    {
        friend class iterator;
        const QExtJsonObject *o;
        int i;

    public:
        typedef std::random_access_iterator_tag iterator_category;
        typedef int difference_type;
        typedef QExtJsonValue value_type;
        typedef QExtJsonValue reference;
        typedef QExtJsonValuePtr pointer;

        Q_DECL_CONSTEXPR inline const_iterator() : o(nullptr), i(0) {}
        Q_DECL_CONSTEXPR inline const_iterator(const QExtJsonObject *obj, int index) : o(obj), i(index) {}
        inline const_iterator(const iterator &other) : o(other.o), i(other.i) {}

        inline QString key() const { return o->keyAt(i); }
        inline QExtJsonValue value() const { return o->valueAt(i); }
        inline QExtJsonValue operator*() const { return o->valueAt(i); }
        inline QExtJsonValuePtr operator->() const { return QExtJsonValuePtr(o->valueAt(i)); }
        const QExtJsonValue operator[](int j) { return o->valueAt(i + j); }

        inline bool operator==(const const_iterator &other) const { return i == other.i; }
        inline bool operator!=(const const_iterator &other) const { return i != other.i; }
        bool operator<(const const_iterator& other) const { return i < other.i; }
        bool operator<=(const const_iterator& other) const { return i <= other.i; }
        bool operator>(const const_iterator& other) const { return i > other.i; }
        bool operator>=(const const_iterator& other) const { return i >= other.i; }

        inline const_iterator &operator++() { ++i; return *this; }
        inline const_iterator operator++(int) { const_iterator r = *this; ++i; return r; }
        inline const_iterator &operator--() { --i; return *this; }
        inline const_iterator operator--(int) { const_iterator r = *this; --i; return r; }
        inline const_iterator operator+(int j) const
        { const_iterator r = *this; r.i += j; return r; }
        inline const_iterator operator-(int j) const { return operator+(-j); }
        inline const_iterator &operator+=(int j) { i += j; return *this; }
        inline const_iterator &operator-=(int j) { i -= j; return *this; }
        int operator-(const_iterator j) const { return i - j.i; }

        inline bool operator==(const iterator &other) const { return i == other.i; }
        inline bool operator!=(const iterator &other) const { return i != other.i; }
        bool operator<(const iterator& other) const { return i < other.i; }
        bool operator<=(const iterator& other) const { return i <= other.i; }
        bool operator>(const iterator& other) const { return i > other.i; }
        bool operator>=(const iterator& other) const { return i >= other.i; }
    };
    friend class const_iterator;

    // STL style
    inline iterator begin() { detach2(); return iterator(this, 0); }
    inline const_iterator begin() const { return const_iterator(this, 0); }
    inline const_iterator constBegin() const { return const_iterator(this, 0); }
    inline iterator end() { detach2(); return iterator(this, size()); }
    inline const_iterator end() const { return const_iterator(this, size()); }
    inline const_iterator constEnd() const { return const_iterator(this, size()); }
    iterator erase(iterator it);

    // more Qt
    typedef iterator Iterator;
    typedef const_iterator ConstIterator;
#if QT_STRINGVIEW_LEVEL < 2
    iterator find(const QString &key);
    const_iterator find(const QString &key) const { return constFind(key); }
    const_iterator constFind(const QString &key) const;
    iterator insert(const QString &key, const QExtJsonValue &value);
#endif
    iterator find(QStringView key);
    iterator find(QLatin1String key);
    const_iterator find(QStringView key) const { return constFind(key); }
    const_iterator find(QLatin1String key) const { return constFind(key); }
    const_iterator constFind(QStringView key) const;
    const_iterator constFind(QLatin1String key) const;
    iterator insert(QStringView key, const QExtJsonValue &value);
    iterator insert(QLatin1String key, const QExtJsonValue &value);

    // STL compatibility
    typedef QExtJsonValue mapped_type;
    typedef QString key_type;
    typedef int size_type;

    inline bool empty() const { return isEmpty(); }

protected:
    QScopedPointer<QExtJsonObjectPrivate> dd_ptr;

    bool detach2(uint reserve = 0);
    void compact();

    template <typename T>
    QExtJsonValue valueImpl(T key) const
    {

    }
    template <typename T>
    QExtJsonValueRef atImpl(T key)
    {

    }
    template <typename T>
    void removeImpl(T key)
    {

    }
    template <typename T>
    QExtJsonValue takeImpl(T key)
    {

    }
    template <typename T>
    bool containsImpl(T key) const
    {

    }
    template <typename T>
    iterator findImpl(T key)
    {

    }
    template <typename T>
    const_iterator constFindImpl(T key) const
    {

    }
    template <typename T>
    iterator insertImpl(T key, const QExtJsonValue &value)
    {

    }
    template <typename T>
    iterator insertAt(int i, T key, const QExtJsonValue &val, bool exists)
    {

    }

    QString keyAt(int index) const;
    QExtJsonValue valueAt(int index) const;
    void setValueAt(int index, const QExtJsonValue &val);
    void removeAt(int index);

private:
    friend class QExtJsonValue;
    friend class QExtJsonValueRef;
    friend class QExtJsonDocument;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtJsonObject)
};

/***********************************************************************************************************************
 * QExtJsonArray
***********************************************************************************************************************/
class QExtJsonArrayPrivate;
class QEXT_CORE_API QExtJsonArray
{
public:
    QExtJsonArray();
    QExtJsonArray(const QExtJsonArray &other);
    QExtJsonArray(const QList<QExtJsonValue> &args);
    virtual ~QExtJsonArray();

    QExtJsonArray &operator =(const QExtJsonArray &other);
    // void swap(QExtJsonArray &other) noexcept;

    static QExtJsonArray fromStringList(const QStringList &list);
    static QExtJsonArray fromVariantList(const QVariantList &list);
    QVariantList toVariantList() const;

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

#if 0
    class const_iterator;

    class iterator
    {
    public:
        QExtJsonArray *a;
        int i;
        typedef std::random_access_iterator_tag  iterator_category;
        typedef int difference_type;
        typedef QExtJsonValue value_type;
        typedef QExtJsonValueRef reference;
        typedef QExtJsonValueRefPtr pointer;

        inline iterator() : a(nullptr), i(0) { }
        explicit inline iterator(QExtJsonArray *array, int index) : a(array), i(index) { }

        inline QExtJsonValueRef operator*() const { return QExtJsonValueRef(a, i); }
        inline QExtJsonValueRefPtr operator->() const { return QExtJsonValueRefPtr(a, i); }

        inline QExtJsonValueRef operator[](int j) const { return QExtJsonValueRef(a, i + j); }

        inline bool operator==(const iterator &o) const { return i == o.i; }
        inline bool operator!=(const iterator &o) const { return i != o.i; }
        inline bool operator<(const iterator& other) const { return i < other.i; }
        inline bool operator<=(const iterator& other) const { return i <= other.i; }
        inline bool operator>(const iterator& other) const { return i > other.i; }
        inline bool operator>=(const iterator& other) const { return i >= other.i; }
        inline bool operator==(const const_iterator &o) const { return i == o.i; }
        inline bool operator!=(const const_iterator &o) const { return i != o.i; }
        inline bool operator<(const const_iterator& other) const { return i < other.i; }
        inline bool operator<=(const const_iterator& other) const { return i <= other.i; }
        inline bool operator>(const const_iterator& other) const { return i > other.i; }
        inline bool operator>=(const const_iterator& other) const { return i >= other.i; }
        inline iterator &operator++() { ++i; return *this; }
        inline iterator operator++(int) { iterator n = *this; ++i; return n; }
        inline iterator &operator--() { i--; return *this; }
        inline iterator operator--(int) { iterator n = *this; i--; return n; }
        inline iterator &operator+=(int j) { i+=j; return *this; }
        inline iterator &operator-=(int j) { i-=j; return *this; }
        inline iterator operator+(int j) const { return iterator(a, i+j); }
        inline iterator operator-(int j) const { return iterator(a, i-j); }
        inline int operator-(iterator j) const { return i - j.i; }
    };
    friend class iterator;

    class const_iterator
    {
    public:
        const QExtJsonArray *a;
        int i;
        typedef std::random_access_iterator_tag  iterator_category;
        typedef qptrdiff difference_type;
        typedef QExtJsonValue value_type;
        typedef QExtJsonValue reference;
        typedef QExtJsonValuePtr pointer;

        inline const_iterator() : a(nullptr), i(0) { }
        explicit inline const_iterator(const QExtJsonArray *array, int index) : a(array), i(index) { }
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        inline const_iterator(const const_iterator &o) : a(o.a), i(o.i) {} // ### Qt 6: Removed so class can be trivially-copyable
#endif
        inline const_iterator(const iterator &o) : a(o.a), i(o.i) {}

        inline QExtJsonValue operator*() const { return a->at(i); }
        inline QExtJsonValuePtr operator->() const { return QExtJsonValuePtr(a->at(i)); }

        inline QExtJsonValue operator[](int j) const { return a->at(i+j); }
        inline bool operator==(const const_iterator &o) const { return i == o.i; }
        inline bool operator!=(const const_iterator &o) const { return i != o.i; }
        inline bool operator<(const const_iterator& other) const { return i < other.i; }
        inline bool operator<=(const const_iterator& other) const { return i <= other.i; }
        inline bool operator>(const const_iterator& other) const { return i > other.i; }
        inline bool operator>=(const const_iterator& other) const { return i >= other.i; }
        inline const_iterator &operator++() { ++i; return *this; }
        inline const_iterator operator++(int) { const_iterator n = *this; ++i; return n; }
        inline const_iterator &operator--() { i--; return *this; }
        inline const_iterator operator--(int) { const_iterator n = *this; i--; return n; }
        inline const_iterator &operator+=(int j) { i+=j; return *this; }
        inline const_iterator &operator-=(int j) { i-=j; return *this; }
        inline const_iterator operator+(int j) const { return const_iterator(a, i+j); }
        inline const_iterator operator-(int j) const { return const_iterator(a, i-j); }
        inline int operator-(const_iterator j) const { return i - j.i; }
    };
    friend class const_iterator;

    // stl style
    inline iterator begin() { detach2(); return iterator(this, 0); }
    inline const_iterator begin() const { return const_iterator(this, 0); }
    inline const_iterator constBegin() const { return const_iterator(this, 0); }
    inline const_iterator cbegin() const { return const_iterator(this, 0); }
    inline iterator end() { detach2(); return iterator(this, size()); }
    inline const_iterator end() const { return const_iterator(this, size()); }
    inline const_iterator constEnd() const { return const_iterator(this, size()); }
    inline const_iterator cend() const { return const_iterator(this, size()); }
    iterator insert(iterator before, const QExtJsonValue &value) { insert(before.i, value); return before; }
    iterator erase(iterator it) { removeAt(it.i); return it; }

    // more Qt
    typedef iterator Iterator;
    typedef const_iterator ConstIterator;
#endif

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
    typedef int size_type;
    typedef QExtJsonValue value_type;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef QExtJsonValueRef reference;
    typedef QExtJsonValue const_reference;
    typedef int difference_type;

protected:
    QScopedPointer<QExtJsonArrayPrivate> dd_ptr;

    // friend Q_CORE_EXPORT QDebug operator<<(QDebug, const QExtJsonArray &);

    // bool detach2(uint reserve = 0);
    // void initialize();
    // void compact();

private:
    friend class QExtJsonValue;
    friend class QExtJsonDocument;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtJsonArray)
};


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

    static QExtJsonDocument fromVariant(const QVariant &variant);
    QVariant toVariant() const;

    static QExtJsonDocument fromJson(const QByteArray &json, QString *error = QEXT_NULLPTR);
    QByteArray toJson() const;

    bool isEmpty() const;
    bool isArray() const;
    bool isObject() const;

    QExtJsonObject object() const;
    QExtJsonArray array() const;

    void setObject(const QExtJsonObject &object);
    void setArray(const QExtJsonArray &array);

    const QExtJsonValue operator[](QStringView key) const;
    const QExtJsonValue operator[](QLatin1String key) const;
    const QExtJsonValue operator[](int index) const;

    bool operator==(const QExtJsonDocument &other) const;
    bool operator!=(const QExtJsonDocument &other) const;

    bool isNull() const;

protected:
    QScopedPointer<QExtJsonDocumentPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtJsonDocument)
};

#endif // _QEXTJSON_H
