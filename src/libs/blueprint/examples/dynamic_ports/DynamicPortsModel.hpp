#pragma once

#include <QtCore/QJsonObject>
#include <QtCore/QPointF>
#include <QtCore/QSize>

// #include <QtNodes/AbstractGraphModel>
// #include <QtNodes/StyleCollection>
#include <qextBlueprintNode.h>

//using QExtBPTypes::ConnectionId = QExtBPTypes::ConnectionId;
//using QExtBPTypes::ConnectionPolicyEnum = QtNodes::ConnectionPolicy;
//using QExtBPTypes::NodeFlagEnum = QtNodes::NodeFlag;
//using QExtBPTypes::NodeId = QExtBPTypes::NodeId;
//usi QExtBPTypes::NodeRoleEnum e = QtNodes::NodeRole;
//using QExtBPTypes::PortIndex = QExtBPTypes::PortIndex;
//using QExtBPTypes::PortRoleEnum = QtNodes::PortRole;
//using QExtBPTypes::PortTypeEnum = QExtBPTypes::PortTypeEnum;
//using StyleCollection = QtNodes::QExtBPStyleCollection;
//using QtNodes::InvalidNodeId;

class PortAddRemoveWidget;

/**
 * The class implements a bare minimum required to demonstrate a model-based
 * graph.
 */
class DynamicPortsModel : public QExtBPAbstractGraphModel
{
    Q_OBJECT
public:
    struct NodeGeometryData
    {
        QSize size;
        QPointF pos;
    };

public:
    DynamicPortsModel();

    ~DynamicPortsModel() override;

    std::unordered_set<QExtBPTypes::NodeId> allNodeIds() const override;

    std::unordered_set<QExtBPTypes::ConnectionId> allConnectionIds(QExtBPTypes::NodeId const nodeId) const override;

    std::unordered_set<QExtBPTypes::ConnectionId> connections(QExtBPTypes::NodeId nodeId,
                                                 QExtBPTypes::PortTypeEnum portType,
                                                 QExtBPTypes::PortIndex portIndex) const override;

    bool connectionExists(QExtBPTypes::ConnectionId const connectionId) const override;

    QExtBPTypes::NodeId addNode(QString const nodeType = QString()) override;

    /**
   * Connection is possible when graph contains no connectivity data
   * in both directions `Out -> In` and `In -> Out`.
   */
    bool connectionPossible(QExtBPTypes::ConnectionId const connectionId) const override;

    void addConnection(QExtBPTypes::ConnectionId const connectionId) override;

    bool nodeExists(QExtBPTypes::NodeId const nodeId) const override;

    QVariant nodeData(QExtBPTypes::NodeId nodeId, QExtBPTypes::NodeRoleEnum role) const override;

    bool setNodeData(QExtBPTypes::NodeId nodeId, QExtBPTypes::NodeRoleEnum role, QVariant value) override;

    QVariant portData(QExtBPTypes::NodeId nodeId,
                      QExtBPTypes::PortTypeEnum portType,
                      QExtBPTypes::PortIndex portIndex,
                      QExtBPTypes::PortRoleEnum role) const override;

    bool setPortData(QExtBPTypes::NodeId nodeId,
                     QExtBPTypes::PortTypeEnum portType,
                     QExtBPTypes::PortIndex portIndex,
                     QVariant const &value,
                     QExtBPTypes::PortRoleEnum role = QExtBPTypes::PortRole_Data) override;

    bool deleteConnection(QExtBPTypes::ConnectionId const connectionId) override;

    bool deleteNode(QExtBPTypes::NodeId const nodeId) override;

    QJsonObject saveNode(QExtBPTypes::NodeId const) const override;

    QJsonObject save() const;

    /// @brief Creates a new node based on the informatoin in `nodeJson`.
    /**
   * @param nodeJson conains a `NodeId`, node's position, internal node
   * information.
   */
    void loadNode(QJsonObject const &nodeJson) override;

    void load(QJsonObject const &jsonDocument);

    void addPort(QExtBPTypes::NodeId nodeId, QExtBPTypes::PortTypeEnum portType, QExtBPTypes::PortIndex portIndex);

    void removePort(QExtBPTypes::NodeId nodeId, QExtBPTypes::PortTypeEnum portType, QExtBPTypes::PortIndex first);

    QExtBPTypes::NodeId newNodeId() override { return _nextNodeId++; }

private:
    std::unordered_set<QExtBPTypes::NodeId> _nodeIds;

    /// [Important] This is a user defined data structure backing your model.
    /// In your case it could be anything else representing a graph, for example, a
    /// table. Or a collection of structs with pointers to each other. Or an
    /// abstract syntax tree, you name it.
    std::unordered_set<QExtBPTypes::ConnectionId> _connectivity;

    mutable std::unordered_map<QExtBPTypes::NodeId, NodeGeometryData> _nodeGeometryData;

    struct NodePortCount
    {
        unsigned int in = 0;
        unsigned int out = 0;
    };

    PortAddRemoveWidget *widget(QExtBPTypes::NodeId) const;

    mutable std::unordered_map<QExtBPTypes::NodeId, NodePortCount> _nodePortCounts;
    mutable std::unordered_map<QExtBPTypes::NodeId, PortAddRemoveWidget *> _nodeWidgets;

    /// A convenience variable needed for generating unique node ids.
    unsigned int _nextNodeId;
};
