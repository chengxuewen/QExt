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

namespace QExtPrivate
{

    template<typename T>
    struct QExtInPlaceTypeTag
    {
    };

    template<std::size_t K>
    struct QExtInPlaceIndexTag
    {
    };

} // namespace QExtPrivate

struct QExtInPlaceT
{
};

template<typename T>
inline QExtInPlaceT qextInPlace(QExtPrivate::QExtInPlaceTypeTag<T> = QExtPrivate::QExtInPlaceTypeTag<T>())
{
    return QExtInPlaceT();
}

template<std::size_t K>
inline QExtInPlaceT qextInPlace(QExtPrivate::QExtInPlaceIndexTag<K> = QExtPrivate::QExtInPlaceIndexTag<K>())
{
    return QExtInPlaceT();
}

template<typename T>
inline QExtInPlaceT qextInPlaceType(QExtPrivate::QExtInPlaceTypeTag<T> = QExtPrivate::QExtInPlaceTypeTag<T>())
{
    return QExtInPlaceT();
}

template<std::size_t K>
inline QExtInPlaceT qextInPlaceIndex(QExtPrivate::QExtInPlaceIndexTag<K> = QExtPrivate::QExtInPlaceIndexTag<K>())
{
    return QExtInPlaceT();
}


#define QEXT_IN_PLACE_T(T)  QExtInPlaceT(&)( QExtPrivate::QExtInPlaceTypeTag<T >  )
#define QEXT_IN_PLACE_TYPE_T(T)  QExtInPlaceT(&)( QExtPrivate::QExtInPlaceTypeTag<T >  )
#define QEXT_IN_PLACE_INDEX_T(K)  QExtInPlaceT(&)( QExtPrivate::QExtInPlaceIndexTag<K > )

#define QEXT_IN_PLACE(T)    qextInPlaceType<T >
#define QEXT_IN_PLACE_TYPE(T)    qextInPlaceType<T >
#define QEXT_IN_PLACE_INDEX(K)    qextInPlaceIndex<K >

#endif

#endif // _QEXTINPLACE_H
