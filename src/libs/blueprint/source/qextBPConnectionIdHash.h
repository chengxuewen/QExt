#ifndef _QEXTBPCONNECTIONIDHASH_H
#define _QEXTBPCONNECTIONIDHASH_H

#include <qextBPTypes.h>

#include <functional>

inline void hash_combine(std::size_t &seed)
{
    Q_UNUSED(seed);
}

template<typename T, typename... Rest>
inline void hash_combine(std::size_t &seed, const T &v, Rest... rest)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    hash_combine(seed, rest...);
}

namespace std
{
template<>
struct hash<QExtBPTypes::ConnectionId>
{
    inline std::size_t operator()(const QExtBPTypes::ConnectionId &id) const
    {
        std::size_t h = 0;
        hash_combine(h, id.outNodeId, id.outPortIndex, id.inNodeId, id.inPortIndex);
        return h;
    }
};

template<>
struct hash<std::pair<QExtBPTypes::NodeId, QExtBPTypes::PortIndex>>
{
    inline std::size_t operator()(std::pair<QExtBPTypes::NodeId, const QExtBPTypes::PortIndex> &nodePort) const
    {
        std::size_t h = 0;
        hash_combine(h, nodePort.first, nodePort.second);
        return h;
    }
};

template<>
struct hash<std::tuple<QExtBPTypes::NodeId, QExtBPTypes::PortTypeEnum, QExtBPTypes::PortIndex>>
{
    using Key = std::tuple<QExtBPTypes::NodeId, QExtBPTypes::PortTypeEnum, QExtBPTypes::PortIndex>;

    inline std::size_t operator()(const Key &key) const
    {
        std::size_t h = 0;
        hash_combine(h, std::get<0>(key), std::get<1>(key), std::get<2>(key));
        return h;
    }
};
} // namespace std

// uint qHash(const QExtBPTypes::ConnectionId &cid)
// {
//     return key.cx + key.cy;
// }

#endif // _QEXTBPCONNECTIONIDHASH_H
