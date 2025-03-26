// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_UTILS_CONTAINERUTILS_H
#define MVVM_UTILS_CONTAINERUTILS_H

#include <vector>
#include <complex>
#include <iterator>
#include <algorithm>
#include <type_traits>
#include <unordered_set>

#include <qextMemory.h>
#include <qextGlobal.h>

namespace ModelView
{
namespace Utils
{

template <class T> struct is_unique_ptr : std::false_type {};
template <class T, class D> struct is_unique_ptr<QExtUniquePointer<T, D>> : std::true_type {};

template <typename T> static inline const T &qextGet(const T &p) { return p; }
template <typename T> static inline T *qextGet(const QExtUniquePointer<T> &p) { return p.get(); }

//! Returns index corresponding to the first occurance of the item in the container.
//! If item doesn't exist, will return -1. Works with containers containing unique_ptr.

template <typename It, typename T>
int IndexOfItem(It begin, It end, const T& item)
{
    It pos;
    // if QEXT_IF_CONSTEXPR (is_unique_ptr<typename std::iterator_traits<It>::value_type>::value)
        // pos = find_if(begin, end, [&item](const typename std::iterator_traits<It>::value_type &x) { return x.get() == item; });
    // else
        // pos = find_if(begin, end, [&item](const typename std::iterator_traits<It>::value_type &x) { return x == item; });

    pos = find_if(begin, end, [&item](const typename std::iterator_traits<It>::value_type &x) { return qextGet(x) == item; });


    return pos == end ? -1 : static_cast<int>(std::distance(begin, pos));
}

//! Returns index corresponding to the first occurance of the item in the container.
//! If item doesn't exist, will return -1. Works with containers containing unique_ptr.

template <typename C, typename T>
int IndexOfItem(const C& container, const T& item)
{
    return IndexOfItem(container.begin(), container.end(), item);
}

//! Returns vector containing results of elementwise unary function application.

template <typename It, typename UnaryFunction>
std::vector<double> Apply(It begin, It end, UnaryFunction func)
{
    std::vector<double> result;
    std::transform(begin, end, std::back_inserter(result), func);
    return result;
}

//! Returns vector with real part of complex numbers.

template <typename C> std::vector<double> Real(const C& container)
{
    return Apply(std::begin(container), std::end(container), [](const typename C::value_type& x) { return std::real(x); });
}

//! Returns vector with imag part of complex numbers.

template <typename C> std::vector<double> Imag(const C& container)
{
    return Apply(std::begin(container), std::end(container), [](const typename C::value_type& x) { return std::imag(x); });
}

//! Returns copy of container with all duplicated elements filtered our. The order is preserved.

template <typename C> C UniqueWithOrder(const C& container)
{
    C result;

    using valueType = typename C::value_type;
    std::unordered_set<valueType> unique;

    std::copy_if(container.begin(), container.end(), std::back_inserter(result),
                 [&unique](valueType x) { return unique.insert(x).second; });

    return result;
}

//! Returns true if container contains a given element.

template <typename A, typename B> bool Contains(const A& container, const B& element)
{
    return std::find(container.begin(), container.end(), element) != container.end();
}
}

} // namespace ModelView::Utils

#endif // MVVM_UTILS_CONTAINERUTILS_H
