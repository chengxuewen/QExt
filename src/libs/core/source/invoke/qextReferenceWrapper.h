/****************************************************************************************************************************
**
** Library: QExt
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
****************************************************************************************************************************/

#ifndef _QEXTREFERENCEWRAPPER_H
#define _QEXTREFERENCEWRAPPER_H

#include <qextGlobal.h>

/**
 * @brief Reference wrapper.
 * Use qextReferenceWrapper() to create a reference wrapper.
 */
template <class T>
struct QExtReferenceWrapper
{
    explicit QExtReferenceWrapper(T &value) : mValue(value)  {}

    operator T &() const { return mValue; }

    T &mValue;
};

/**
 * @brief Const reference wrapper.
 * Use qextReferenceWrapper() to create a const reference wrapper.
 */
template <class T>
struct QExtConstReferenceWrapper
{
    explicit QExtConstReferenceWrapper(const T &value) : mValue(value)  {}

    operator const T &() const { return mValue; }

    const T &mValue;
};

/**
 * @brief Creates a reference wrapper.
 * Passing an object throught qextReferenceWrapper() makes adaptors like, e.g.,
 * QExtBindFunctor store references to the object instead of copies.
 * If the object type inherits from QObject this will ensure automatic invalidation of the adaptors when the object
 * is deleted or overwritten.
 *
 * @param value Reference to store.
 * @return A reference wrapper.
 */
template <class T>
QExtReferenceWrapper<T> qextReferenceWrapper(T &value)
{
    return QExtReferenceWrapper<T>(value);
}

/**
 * @brief Creates a const reference wrapper.
 * Passing an object throught qextReferenceWrapper() makes adaptors like, e.g.,
 * QExtBindFunctor store references to the object instead of copies.
 * If the object type inherits from QObject this will ensure automatic invalidation of the adaptors when the object
 * is deleted or overwritten.
 *
 * @param value Reference to store.
 * @return A reference wrapper.
 */
template <class T>
QExtConstReferenceWrapper<T> qextReferenceWrapper(const T &value)
{
    return QExtConstReferenceWrapper<T>(value);
}

template <class T>
struct QExtUnwrapReference
{
    typedef T Type;
};

template <class T>
struct QExtUnwrapReference<QExtReferenceWrapper<T> >
{
    typedef T &Type;
};

template <class T>
struct QExtUnwrapReference<QExtConstReferenceWrapper<T> >
{
    typedef const T &Type;
};

template <typename T>
T &qextUnwrapReference(const QExtReferenceWrapper<T> &value)
{
    return value;
}

template <typename T>
const T &qextUnwrapReference(const QExtConstReferenceWrapper<T> &value)
{
    return value;
}



#endif // _QEXTREFERENCEWRAPPER_H
