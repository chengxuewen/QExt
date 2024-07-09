#ifndef _QEXTBPTYPES_H
#define _QEXTBPTYPES_H

#include <qextBlueprintGlobal.h>

#include <QObject>

#include <limits>

/**
 * @file
 * Important definitions used throughout the library.
 */

class QExtBPTypes : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constants used for fetching QVariant data from GraphModel.
     */
    enum NodeRoleEnum
    {
        NodeRole_Type = 0,           ///< Type of the current node, usually a string.
        NodeRole_Position = 1,       ///< `QPointF` positon of the node on the scene.
        NodeRole_Size = 2,           ///< `QSize` for resizable nodes.
        NodeRole_CaptionVisible = 3, ///< `bool` for caption visibility.
        NodeRole_Caption = 4,        ///< `QString` for node caption.
        NodeRole_Style = 5,          ///< Custom NodeStyle as QJsonDocument
        NodeRole_InternalData = 6,   ///< Node-stecific user data as QJsonObject
        NodeRole_InPortCount = 7,    ///< `unsigned int`
        NodeRole_OutPortCount = 9,   ///< `unsigned int`
        NodeRole_Widget = 10,        ///< Optional `QWidget*` or `nullptr`
    };
    Q_ENUMS(NodeRoleEnum)

    /**
     * @brief Specific flags regulating node features and appeaarence.
     */
    enum NodeFlagEnum
    {
        NodeFlag_NoFlags = 0x0,   ///< Default NodeFlag
        NodeFlag_Resizable = 0x1, ///< Lets the node be resizable
        NodeFlag_Locked = 0x2
    };

    Q_DECLARE_FLAGS(NodeFlagEnums, NodeFlagEnum)
    Q_FLAGS(NodeFlagEnums)
    //    Q_DECLARE_OPERATORS_FOR_FLAGS(NodeFlagEnums)

    /**
     * @brief Constants for fetching port-related information from the GraphModel.
     */
    enum PortRoleEnum
    {
        PortRole_Data = 0,                 ///< `std::shared_ptr<NodeData>`.
        PortRole_DataType = 1,             ///< `QString` describing the port data type.
        PortRole_ConnectionPolicyRole = 2, ///< `enum` ConnectionPolicyRole
        PortRole_CaptionVisible = 3,       ///< `bool` for caption visibility.
        PortRole_Caption = 4,              ///< `QString` for port caption.
    };
    Q_ENUMS(PortRoleEnum)

    /**
     * @brief Defines how many connections are possible to attach to ports.
     * The values are fetched using QExtBPTypes::PortRole_ConnectionPolicy.
     */
    enum ConnectionPolicyEnum
    {
        ConnectionPolicy_One,  ///< Just one connection for each port.
        ConnectionPolicy_Many, ///< Any number of connections possible for the port.
    };
    Q_ENUMS(ConnectionPolicyEnum)

    /**
     * Used for distinguishing input and output node ports.
     */
    enum PortTypeEnum
    {
        PortType_In = 0,  ///< Input node port (from the left).
        PortType_Out = 1, ///< Output node port (from the right).
        PortType_None = 2
    };
    Q_ENUMS(PortTypeEnum)

    using PortCount = unsigned int;

    /// ports are consecutively numbered starting from zero.
    using PortIndex = unsigned int;
    static constexpr PortIndex InvalidPortIndex = std::numeric_limits<PortIndex>::max();

    /// Unique Id associated with each node in the GraphModel.
    using NodeId = unsigned int;
    static constexpr NodeId InvalidNodeId = std::numeric_limits<NodeId>::max();

    /**
     * A unique connection identificator that stores out `NodeId`, out `PortIndex`, in `NodeId`, in `PortIndex`
     */
    struct ConnectionId
    {
        NodeId outNodeId;
        PortIndex outPortIndex;
        NodeId inNodeId;
        PortIndex inPortIndex;
    };

    friend inline bool operator==(QExtBPTypes::ConnectionId const &a, QExtBPTypes::ConnectionId const &b)
    {
        return a.outNodeId == b.outNodeId && a.outPortIndex == b.outPortIndex
                && a.inNodeId == b.inNodeId && a.inPortIndex == b.inPortIndex;
    }

    friend inline bool operator!=(QExtBPTypes::ConnectionId const &a, QExtBPTypes::ConnectionId const &b)
    {
        return !(a == b);
    }

    friend inline void invertConnection(QExtBPTypes::ConnectionId &id)
    {
        std::swap(id.outNodeId, id.inNodeId);
        std::swap(id.outPortIndex, id.inPortIndex);
    }

    QExtBPTypes(QObject *parent = QEXT_NULLPTR) : QObject(parent) {}
    ~QExtBPTypes() QEXT_OVERRIDE {}
};
Q_DECLARE_METATYPE(QExtBPTypes::ConnectionPolicyEnum)

#endif // _QEXTBPTYPES_H
