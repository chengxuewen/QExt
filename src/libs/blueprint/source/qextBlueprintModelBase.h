#ifndef _QEXTBLUEPRINTMODELBASE_H
#define _QEXTBLUEPRINTMODELBASE_H

#include <QSet>
#include <QObject>

#include <qextBlueprintGlobal.h>
#include <qextBlueprintTypes.h>

class QEXT_BLUEPRINT_API QExtBlueprintModelBase : public QObject
{
    Q_OBJECT
public:
    explicit QExtBlueprintModelBase(QObject *parent = QEXT_NULLPTR);
    ~QExtBlueprintModelBase() QEXT_OVERRIDE;

    /**
     * @brief Generates a new unique NodeId.
     */
    virtual QExtBlueprintTypes::NodeId newNodeId() = 0;

    /**
     * @brief Returns the full set of unique Node Ids.
     * Model creator is responsible for generating unique `unsigned int` Ids for all the nodes in the graph.
     * From an Id it should be possible to trace back to the model's internal representation of the node.
     */
    virtual QSet<QExtBlueprintTypes::NodeId> allNodeIds() const = 0;

    /**
     * @brief A collection of all input and output connections for the given `nodeId`.
     */
    virtual QSet<QExtBlueprintTypes::ConnectionId> allConnectionIds(QExtBlueprintTypes::NodeId const nodeId) const = 0;

    /**
     * @brief Returns all connected Node Ids for given port.
     * @param The returned set of nodes and port indices correspond to the type opposite to the given `portType`.
     */
    virtual QSet<QExtBlueprintTypes::ConnectionId> connections(QExtBlueprintTypes::NodeId nodeId,
                                                               QExtBlueprintTypes::PortType portType,
                                                               QExtBlueprintTypes::PortIndex index) const = 0;

    /**
     * @brief Checks if two nodes with the given `connectionId` are connected.
     */
    virtual bool connectionExists(QExtBlueprintTypes::ConnectionId const connectionId) const = 0;

    /**
     * @brief Creates a new node instance in the derived class.
     * @param The model is responsible for generating a unique `NodeId`.
     * @param[in] nodeType is free to be used and interpreted by the model on its own, it helps to distinguish between
     * possible node types and create a correct instance inside.
     */
    virtual QExtBlueprintTypes::NodeId addNode(QString const nodeType = QString()) = 0;

Q_SIGNALS:
    void connectionCreated(QExtBlueprintTypes::ConnectionId const connectionId);

    void connectionDeleted(QExtBlueprintTypes::ConnectionId const connectionId);

    void nodeCreated(QExtBlueprintTypes::NodeId const nodeId);

    void nodeDeleted(QExtBlueprintTypes::NodeId const nodeId);

    void nodeUpdated(QExtBlueprintTypes::NodeId const nodeId);

    void nodeFlagsUpdated(QExtBlueprintTypes::NodeId const nodeId);

    void nodePositionUpdated(QExtBlueprintTypes::NodeId const nodeId);

    void modelReset();
};

#endif // _QEXTBLUEPRINTMODELBASE_H
