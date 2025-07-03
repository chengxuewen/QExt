/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2025~Present ChengXueWen. Contact: 1398831004@qq.com.
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#ifndef _QEXTOBJECTSHAREDPOINTER_H
#define _QEXTOBJECTSHAREDPOINTER_H

#include <QSharedPointer>
#include <QObject>

#include <type_traits>

template<typename T>
class QExtObjectSharedPointer : public QSharedPointer<T>
{
public:
    QExtObjectSharedPointer(T *ptr)
        : QSharedPointer<T>(ptr, &T::deleteLater)
    {
        static_assert(std::is_base_of<QObject, T>::value, "Need a QObject derived class here");
    }

    QExtObjectSharedPointer() : QSharedPointer<T>() { }
    QExtObjectSharedPointer(const QSharedPointer<T> &other) : QSharedPointer<T>(other) { }
    QExtObjectSharedPointer(const QWeakPointer<T> &other) : QSharedPointer<T>(other) { }
};

#endif // _QEXTOBJECTSHAREDPOINTER_H
