#pragma once

#include <QtCore/QJsonObject>
#include <QtCore/QPointF>
#include <QtCore/QSize>

#include <QExtBlueprint>

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

    std::unordered_set<QExtBPTypes::ConnectionId> allConnectionIds(const QExtBPTypes::NodeId nodeId) const override;

    std::unordered_set<QExtBPTypes::ConnectionId> connections(QExtBPTypes::NodeId nodeId,
                                                              QExtBPTypes::PortTypeEnum portType,
                                                              QExtBPTypes::PortIndex portIndex) const override;

    bool connectionExists(const QExtBPTypes::ConnectionId connectionId) const override;

    QExtBPTypes::NodeId addNode(QString const nodeType = QString()) override;

    /**
   * Connection is possible when graph contains no connectivity data
   * in both directions `Out -> In` and `In -> Out`.
   */
    bool connectionPossible(const QExtBPTypes::ConnectionId connectionId) const override;

    void addConnection(const QExtBPTypes::ConnectionId connectionId) override;

    bool nodeExists(const QExtBPTypes::NodeId nodeId) const override;

    QVariant nodeData(QExtBPTypes::NodeId nodeId, QExtBPTypes::NodeRoleEnum role) const override;

    bool setNodeData(QExtBPTypes::NodeId nodeId, QExtBPTypes::NodeRoleEnum role, QVariant value) override;

    QVariant portData(QExtBPTypes::NodeId nodeId,
                      QExtBPTypes::PortTypeEnum portType,
                      QExtBPTypes::PortIndex portIndex,
                      QExtBPTypes::PortRoleEnum role) const override;

    bool setPortData(QExtBPTypes::NodeId nodeId,
                     QExtBPTypes::PortTypeEnum portType,
                     QExtBPTypes::PortIndex portIndex,
                     const QVariant &value,
                     QExtBPTypes::PortRoleEnum role = QExtBPTypes::PortRole_Data) override;

    bool deleteConnection(const QExtBPTypes::ConnectionId connectionId) override;

    bool deleteNode(const QExtBPTypes::NodeId nodeId) override;

    QJsonObject saveNode(const QExtBPTypes::NodeId) const override;

    QJsonObject save() const;

    /// @brief Creates a new node based on the informatoin in `nodeJson`.
    /**
   * @param nodeJson conains a `NodeId`, node's position, internal node
   * information.
   */
    void loadNode(const QJsonObject &nodeJson) override;

    void load(const QJsonObject &jsonDocument);

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
