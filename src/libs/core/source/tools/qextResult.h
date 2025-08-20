#ifndef _QEXTRESULT_H
#define _QEXTRESULT_H

#include <qextAny.h>
#include <qextOptional.h>

template<typename T, typename E>
class Result
{
    typedef QExtOptional<T> TStorage;
    typedef QExtOptional<E> EStorage;
public:
    typedef QExtAny Storage;
    using ValueType = T;
    using ErrorType = E;


    constexpr Result() {}
    constexpr Result(const Result& other)
    {
        if (this != &other)
        {
            mStorage = other.mStorage;
        }
    }
    constexpr Result(Result&& other)
    {
        // if (this != &other)
        // {
        //     mStorage = other.mStorage;
        // }
    }
    constexpr Result(const T &value) : mStorage(value) { }

    // template<typename U, typename G>
    // explicit Result(Result<U, G> const & other)
    // {
    //     if()
    // }

    constexpr ValueType const * operator ->() const
    {
        return &this->value();
    }

    ValueType * operator ->()
    {
        return &this->value();
    }

    constexpr ValueType const & operator *() const &
    {
        return this->value();
    }

    ValueType & operator *() &
    {
        return this->value();
    }

    // constexpr ValueType const && operator *() const &&
    // {
    //     return std::move(this->value());
    // }

    // constexpr ValueType && operator *() &&
    // {
    //     return std::move(this->value());
    // }


    constexpr explicit operator bool() const noexcept
    {
        return this->hasValue();
    }

    constexpr bool hasValue() const noexcept
    {
        return mStorage.has_value() && typeid(ValueType) == mStorage.type();
    }


    // constexpr ValueType const & value() const &
    // {
    //     return this->hasValue() ? *qextAnyCast<ValueType>(&mStorage)
    //                             : ( error_traits<error_type>::rethrow( contained.error() ), contained.value() );
    // }

    // ValueType & value() &
    // {
    //     return has_value()
    //                ? ( contained.value() )
    //                : ( error_traits<error_type>::rethrow( contained.error() ), contained.value() );
    // }


    // constexpr ValueType const && value() const &&
    // {
    //     return std::move( has_value()
    //                          ? ( contained.value() )
    //                          : ( error_traits<error_type>::rethrow( contained.error() ), contained.value() ) );
    // }

    // constexpr ValueType && value() &&
    // {
    //     return std::move( has_value()
    //                          ? ( contained.value() )
    //                          : ( error_traits<error_type>::rethrow( contained.error() ), contained.value() ) );
    // }

    // constexpr ErrorType const & error() const &
    // {
    //     return assert( ! has_value() ), contained.error();
    // }

    // ErrorType & error()
    // {
    //     return assert( ! has_value() ), contained.error();
    // }


private:
    Storage mStorage;
};

template<typename E>
class Result<void, E>
{
public:
    typedef QExtAny Storage;

    constexpr Result(const Result& other) = default;


private:
    Storage mStorage;
};

#endif // _QEXTRESULT_H
