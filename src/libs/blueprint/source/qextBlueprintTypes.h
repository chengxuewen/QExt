#ifndef _QEXTBLUEPRINTTYPES_H
#define _QEXTBLUEPRINTTYPES_H

#include <qextBlueprintGlobal.h>

#include <QObject>

class QEXT_BLUEPRINT_API QExtBlueprintTypes : public QObject
{
    Q_OBJECT
public:
    typedef quint64 NodeId;
    typedef quint64 PortCount;
    typedef quint64 PortIndex;

    /**
     * Specific flags regulating node features and appeaarence.
     */
    enum NodeFlag
    {
        NoFlags = 0x0,   ///< Default NodeFlag
        Resizable = 0x1, ///< Lets the node be resizable
        Locked = 0x2
    };
    Q_ENUMS(NodeFlags)
    Q_DECLARE_FLAGS(NodeFlags, NodeFlag)

    /**
     * Used for distinguishing input and output node ports.
     */
    enum PortType
    {
        In = 0,  ///< Input node port (from the left).
        Out = 1, ///< Output node port (from the right).
        None = 2
    };
    Q_ENUMS(PortType)


    /**
     * A unique connection identificator that stores
     * out `NodeId`, out `PortIndex`, in `NodeId`, in `PortIndex`
     */
    struct ConnectionId
    {
        NodeId outNodeId;
        PortIndex outPortIndex;
        NodeId inNodeId;
        PortIndex inPortIndex;
    };

    explicit QExtBlueprintTypes(QObject *parent = QEXT_NULLPTR);
};

inline bool operator==(QExtBlueprintTypes::ConnectionId const &a, QExtBlueprintTypes::ConnectionId const &b)
{
    return a.outNodeId == b.outNodeId && a.outPortIndex == b.outPortIndex
            && a.inNodeId == b.inNodeId && a.inPortIndex == b.inPortIndex;
}

inline bool operator!=(QExtBlueprintTypes::ConnectionId const &a, QExtBlueprintTypes::ConnectionId const &b)
{
    return !(a == b);
}

inline void invertConnection(QExtBlueprintTypes::ConnectionId &id)
{
    std::swap(id.outNodeId, id.inNodeId);
    std::swap(id.outPortIndex, id.inPortIndex);
}

#endif // _QEXTBLUEPRINTTYPES_H
