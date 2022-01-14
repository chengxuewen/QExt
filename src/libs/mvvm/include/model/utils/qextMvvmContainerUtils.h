#ifndef _QEXTMVVMUTILSCONTAINERUTILS_H
#define _QEXTMVVMUTILSCONTAINERUTILS_H

#include <qextMvvmGlobal.h>

#include <algorithm>
#include <complex>
#include <iterator>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <vector>

namespace ModelView
{

namespace QEXTMvvmUtils
{

template <class T> struct is_unique_ptr : std::false_type {
};

template <class T, class D> struct is_unique_ptr<std::unique_ptr<T, D>> : std::true_type {
};

//! Returns index corresponding to the first occurance of the item in the container.
//! If item doesn't exist, will return -1. Works with containers containing unique_ptr.

template <typename It, typename T> int IndexOfItem(It begin, It end, const T& item)
{
    It pos;
    if (is_unique_ptr<typename std::iterator_traits<It>::value_type>::value)
//        pos = find_if(begin, end, [&item](const T& x) { return x.get() == item; });
        assert(false);
    else
        pos = find_if(begin, end, [&item](const T& x) { return x == item; });

    return pos == end ? -1 : static_cast<int>(std::distance(begin, pos));
}

//! Returns index corresponding to the first occurance of the item in the container.
//! If item doesn't exist, will return -1. Works with containers containing unique_ptr.

template <typename C, typename T> int IndexOfItem(const C& container, const T& item)
{
    return IndexOfItem(container.begin(), container.end(), item);
}

//! Returns vector containing results of elemntwise unary function application.

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
    return Apply(std::begin(container), std::end(container),
                 [](const double& x) { return std::real(x); });
}

//! Returns vector with imag part of complex numbers.

template <typename C> std::vector<double> Imag(const C& container)
{
    return Apply(std::begin(container), std::end(container),
                 [](const double& x) { return std::imag(x); });
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

} // namespace Utils

} // namespace ModelView

#endif // _QEXTMVVMUTILSCONTAINERUTILS_H
