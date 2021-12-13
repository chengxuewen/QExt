/*************************************************************************************
**
** Library: QEXT
**
** Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
** Copyright 2002, The libsigc++ Development Team
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
*************************************************************************************/

#ifndef _QEXTREFERENCEWRAPPER_H
#define _QEXTREFERENCEWRAPPER_H

#include <qextGlobal.h>



/** Reference wrapper.
 * Use qextReferenceWrapper() to create a reference wrapper.
 */
template <typename T_type>
struct QEXTReferenceWrapper
{
    explicit QEXTReferenceWrapper(T_type &value) : m_value(value)  {}

    operator T_type &() const
    {
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

    operator const T_type &() const
    {
        return m_value;
    }

    const T_type &m_value;
};

/** Creates a reference wrapper.
 * Passing an object throught qextReferenceWrapper() makes adaptors
 * like, e.g., QEXTBindFunctor store references to the object instead of copies.
 * If the object type inherits from QObject this will ensure
 * automatic invalidation of the adaptors when the object is deleted
 * or overwritten.
 *
 * \param v Reference to store.
 * \return A reference wrapper.
 */
template <typename T_type>
QEXTReferenceWrapper<T_type> qextReferenceWrapper(T_type &value)
{
    return QEXTReferenceWrapper<T_type>(value);
}

/** Creates a const reference wrapper.
 * Passing an object throught qextReferenceWrapper() makes adaptors
 * like, e.g., QEXTBindFunctor store references to the object instead of copies.
 * If the object type inherits from QObject this will ensure
 * automatic invalidation of the adaptors when the object is deleted
 * or overwritten.
 *
 * \param value Reference to store.
 * \return A reference wrapper.
 */
template <typename T_type>
QEXTConstReferenceWrapper<T_type> qextReferenceWrapper(const T_type &value)
{
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
T_type &qextUnwrapReference(const QEXTReferenceWrapper<T_type> &value)
{
    return value;
}

template <typename T_type>
const T_type &qextUnwrapReference(const QEXTConstReferenceWrapper<T_type> &value)
{
    return value;
}



#endif // _QEXTREFERENCEWRAPPER_H
