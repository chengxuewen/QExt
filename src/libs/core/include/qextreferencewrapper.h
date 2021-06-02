#ifndef QEXTREFERENCEWRAPPER_H
#define QEXTREFERENCEWRAPPER_H

/** Reference wrapper.
 * Use qextReferenceWrapper() to create a reference wrapper.
 */
template <typename T_type>
struct QEXTReferenceWrapper
{
    explicit QEXTReferenceWrapper(T_type &value) : m_value(value)  {}

    operator T_type& () const {
        return m_value;
    }

    T_type &m_value;
};

/** Const reference wrapper.
 * Use qextReferenceWrapper() to create a const reference wrapper.
 */
template <typename T_type>
struct QEXTConstReferenceWrapper
{
    explicit QEXTConstReferenceWrapper(const T_type &value) : m_value(value)  {}

    operator const T_type& () const {
        return m_value;
    }

    const T_type &m_value;
};

/** Creates a reference wrapper.
 * Passing an object throught qextReferenceWrapper() makes adaptors
 * like, e.g., QEXTBindFunctor store references to the object instead of copies.
 * If the object type inherits from QEXTTrackable this will ensure
 * automatic invalidation of the adaptors when the object is deleted
 * or overwritten.
 *
 * @param v Reference to store.
 * @return A reference wrapper.
 */
template <typename T_type>
QEXTReferenceWrapper<T_type> qextReferenceWrapper(T_type &value) {
    return QEXTReferenceWrapper<T_type>(value);
}

/** Creates a const reference wrapper.
 * Passing an object throught qextReferenceWrapper() makes adaptors
 * like, e.g., QEXTBindFunctor store references to the object instead of copies.
 * If the object type inherits from QEXTTrackable this will ensure
 * automatic invalidation of the adaptors when the object is deleted
 * or overwritten.
 *
 * @param value Reference to store.
 * @return A reference wrapper.
 */
template <typename T_type>
QEXTConstReferenceWrapper<T_type> qextReferenceWrapper(const T_type &value) {
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
