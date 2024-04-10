#ifndef _QEXTBLUEPRINTGLOBAL_H
#define _QEXTBLUEPRINTGLOBAL_H

#include <qextGlobal.h>

/***********************************************************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
***********************************************************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
#   ifdef QEXT_BUILD_BLUEPRINT_LIB // defined if we are building the lib
#       define QEXT_BLUEPRINT_API Q_DECL_EXPORT
#   else
#       define QEXT_BLUEPRINT_API Q_DECL_IMPORT
#   endif
#   define QEXT_BLUEPRINT_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
#   define QEXT_BLUEPRINT_API
#   define QEXT_BLUEPRINT_HIDDEN
#endif

namespace QExtBlueprint
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
QEXT_BLUEPRINT_API Q_NAMESPACE
#else
Q_NAMESPACE_EXPORT(QEXT_BLUEPRINT_API)
#endif

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
Q_DECLARE_FLAGS(NodeFlags, NodeFlag)
Q_FLAG_NS(NodeFlags)
Q_DECLARE_OPERATORS_FOR_FLAGS(NodeFlags)

/**
 * Used for distinguishing input and output node ports.
 */
enum class PortType
{
    In = 0,  ///< Input node port (from the left).
    Out = 1, ///< Output node port (from the right).
    None = 2
};
Q_ENUM_NS(PortType)


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

inline bool operator==(ConnectionId const &a, ConnectionId const &b)
{
    return a.outNodeId == b.outNodeId && a.outPortIndex == b.outPortIndex
           && a.inNodeId == b.inNodeId && a.inPortIndex == b.inPortIndex;
}

inline bool operator!=(ConnectionId const &a, ConnectionId const &b)
{
    return !(a == b);
}

inline void invertConnection(ConnectionId &id)
{
    std::swap(id.outNodeId, id.inNodeId);
    std::swap(id.outPortIndex, id.inPortIndex);
}

} // namespace QExtBlueprint

#endif // _QEXTBLUEPRINTGLOBAL_H
