#pragma once

#include <QtCore/QJsonObject>
#include <QtCore/QPointF>
#include <QtCore/QSize>

#include <QExtBlueprint>

/**
 * The class implements a bare minimum required to demonstrate a model-based
 * graph.
 */
class SimpleGraphModel : public QExtBPAbstractGraphModel
{
    Q_OBJECT
public:
    struct NodeGeometryData
    {
        QSize size;
        QPointF pos;
    };

public:
    SimpleGraphModel();

    ~SimpleGraphModel() override;

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

    /// @brief Creates a new node based on the informatoin in `nodeJson`.
    /**
   * @param nodeJson conains a `NodeId`, node's position, internal node
   * information.
   */
    void loadNode(QJsonObject const &nodeJson) override;

private:
    QExtBPTypes::NodeId newNodeId() override { return _nextNodeId++; }

private:
    std::unordered_set<QExtBPTypes::NodeId> _nodeIds;

    /// [Important] This is a user defined data structure backing your model.
    /// In your case it could be anything else representing a graph, for example, a
    /// table. Or a collection of structs with pointers to each other. Or an
    /// abstract syntax tree, you name it.
    ///
    /// This data structure contains the graph connectivity information in both
    /// directions, i.e. from Node1 to Node2 and from Node2 to Node1.
    std::unordered_set<QExtBPTypes::ConnectionId> _connectivity;

    mutable std::unordered_map<QExtBPTypes::NodeId, NodeGeometryData> _nodeGeometryData;

    /// A convenience variable needed for generating unique node ids.
    unsigned int _nextNodeId;
};
