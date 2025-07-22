/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2024 ChengXueWen.
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

#ifndef _QEXTCONTAINERUTILS_H
#define _QEXTCONTAINERUTILS_H

#include <qextGlobal.h>
#include <qextCompiler.h>
#include <qextTypeTrait.h>

#include <memory>

namespace QExtContainerUtils
{

template <typename T> struct isUniquePtr : public QExtFalseType { };
#if QEXT_CC_CPP11_OR_GREATER
template <typename T, typename D> struct isUniquePtr<std::unique_ptr<T, D>> : public QExtFalseType { };
#endif

/**
 * @brief Returns index corresponding to the first occurance of the item in the container.
 * If item doesn't exist, will return -1. Works with containers containing unique_ptr.
 */
// template <typename It, typename T>
// int indexOfItem(It begin, It end, const T &item)
// {
//     It pos;
//     if (isUniquePtr<typename std::iterator_traits<It>::value_type>::value)
//     {
//         pos = find_if(begin, end, [&item](const auto& x) { return x.get() == item; });
//     }
//     else
//     {
//         pos = find_if(begin, end, [&item](const auto& x) { return x == item; });
//     }
//     return pos == end ? -1 : static_cast<int>(std::distance(begin, pos));
// }

/**
 * @brief Returns index corresponding to the first occurance of the item in the container.
 * If item doesn't exist, will return -1. Works with containers containing unique_ptr.
 */
template <typename C, typename T>
int IndexOfItem(const C &container, const T &item)
{
    return IndexOfItem(container.begin(), container.end(), item);
}

/**
 * @brief Returns true if container contains a given element.
 */
template <typename A, typename B>
bool contains(const A &container, const B &element)
{
    return std::find(container.begin(), container.end(), element) != container.end();
}

};

#endif // _QEXTCONTAINERUTILS_H
