#ifndef QEXTREFERENCEWRAPPER_H
#define QEXTREFERENCEWRAPPER_H

template <typename T_type>
struct QEXTReferenceWrapper
{
    explicit QEXTReferenceWrapper(T_type &value) : m_value(value)  {}

    operator T_type& () const {
        return m_value;
    }

    T_type &m_value;
};

template <typename T_type>
struct QEXTConstReferenceWrapper
{
    explicit QEXTConstReferenceWrapper(const T_type &value) : m_value(value)  {}

    operator const T_type& () const {
        return m_value;
    }

    const T_type &m_value;
};

template <typename T_type>
QEXTReferenceWrapper<T_type> qextCreateReferenceWrapper(T_type &value) {
    return QEXTReferenceWrapper<T_type>(value);
}

template <typename T_type>
QEXTConstReferenceWrapper<T_type> qextCreateReferenceWrapper(const T_type &value) {
    return QEXTConstReferenceWrapper<T_type>(value);
}

template <typename T_type>
struct QEXTUnwrapReference
{
    typedef T_type Type;
};

template <typename T_type>
struct QEXTUnwrapReference<QEXTReferenceWrapper<T_type> >
{
    typedef T_type &Type;
};

template <typename T_type>
struct QEXTUnwrapReference<QEXTConstReferenceWrapper<T_type> >
{
    typedef const T_type &Type;
};

template <typename T_type>
T_type& qextUnwrapReference(const QEXTReferenceWrapper<T_type>& value) {
    return value;
}

template <typename T_type>
const T_type& qextUnwrapReference(const QEXTConstReferenceWrapper<T_type> &value) {
    return value;
}


#endif // QEXTREFERENCEWRAPPER_H
