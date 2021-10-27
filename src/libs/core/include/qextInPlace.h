#ifndef _QEXTINPLACE_H
#define _QEXTINPLACE_H

#include <qextGlobal.h>

#if QEXT_CC_STD_17

#include <utility>

using std::in_place;
using std::in_place_type;
using std::in_place_index;
using std::in_place_t;
using std::in_place_type_t;
using std::in_place_index_t;

#define QEXT_IN_PLACE_T(      T)  std::in_place_t
#define QEXT_IN_PLACE_TYPE_T( T)  std::in_place_type_t<T>
#define QEXT_IN_PLACE_INDEX_T(K)  std::in_place_index_t<K>

#define QEXT_IN_PLACE(      T)    std::in_place_t{}
#define QEXT_IN_PLACE_TYPE( T)    std::in_place_type_t<T>{}
#define QEXT_IN_PLACE_INDEX(K)    std::in_place_index_t<K>{}

#else

#include <cstddef>

namespace qextPrivate
{

    template<typename T>
    struct QEXTInPlaceTypeTag {};

    template<std::size_t K>
    struct QEXTInPlaceIndexTag {};

} // namespace qextPrivate

struct QEXTInPlaceT {};

template<typename T>
inline QEXTInPlaceT qextInPlace(qextPrivate::QEXTInPlaceTypeTag<T> = qextPrivate::QEXTInPlaceTypeTag<T>())
{
    return QEXTInPlaceT();
}

template<std::size_t K>
inline QEXTInPlaceT qextInPlace(qextPrivate::QEXTInPlaceIndexTag<K> = qextPrivate::QEXTInPlaceIndexTag<K>())
{
    return QEXTInPlaceT();
}

template<typename T>
inline QEXTInPlaceT qextInPlaceType(qextPrivate::QEXTInPlaceTypeTag<T> = qextPrivate::QEXTInPlaceTypeTag<T>())
{
    return QEXTInPlaceT();
}

template< std::size_t K >
inline QEXTInPlaceT qextInPlaceIndex(qextPrivate::QEXTInPlaceIndexTag<K> = qextPrivate::QEXTInPlaceIndexTag<K>())
{
    return QEXTInPlaceT();
}


#define QEXT_IN_PLACE_T(      T)  QEXTInPlaceT(&)( qextPrivate::QEXTInPlaceTypeTag<T >  )
#define QEXT_IN_PLACE_TYPE_T( T)  QEXTInPlaceT(&)( qextPrivate::QEXTInPlaceTypeTag<T >  )
#define QEXT_IN_PLACE_INDEX_T(K)  QEXTInPlaceT(&)( qextPrivate::QEXTInPlaceIndexTag<K > )

#define QEXT_IN_PLACE(      T)    qextInPlaceType<T >
#define QEXT_IN_PLACE_TYPE( T)    qextInPlaceType<T >
#define QEXT_IN_PLACE_INDEX(K)    qextInPlaceIndex<K >

#endif

#endif // _QEXTINPLACE_H
