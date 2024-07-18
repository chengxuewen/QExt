#ifndef _QEXTBPQUUIDSTDHASH_H
#define _QEXTBPQUUIDSTDHASH_H


#include <functional>

#include <QtCore/QUuid>
#include <QtCore/QVariant>

namespace std {
template<>
struct hash<QUuid>
{
    inline std::size_t operator()(const QUuid &uid) const { return qHash(uid); }
};

} // namespace std

#endif // _QEXTBPQUUIDSTDHASH_H
