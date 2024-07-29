#ifndef _QEXTBPBASICGRAPHICSSCENE_H
#define _QEXTBPBASICGRAPHICSSCENE_H

#include <qextBPAbstractNodeGeometry.h>
#include <qextBlueprintGlobal.h>
#include <qextBPTypes.h>

#include <QUuid>
#include <QMenu>
#include <QGraphicsScene>

#include <unordered_map>
#include <functional>
#include <memory>
#include <tuple>

class QUndoStack;

class QExtBPNodeStyle;
class QExtBPNodeGraphicsObject;
class QExtBPAbstractGraphModel;
class QExtBPAbstractNodePainter;
class QExtBPConnectionGraphicsObject;

/// An instance of QGraphicsScene, holds connections and nodes.
class QExtBPBasicGraphicsScenePrivate;
class QEXT_BLUEPRINT_API QExtBPBasicGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    QExtBPBasicGraphicsScene(QExtBPAbstractGraphModel &graphModel, QObject *parent = QEXT_NULLPTR);
    QExtBPBasicGraphicsScene(QExtBPBasicGraphicsScenePrivate *d, QObject *parent = QEXT_NULLPTR);
    ~QExtBPBasicGraphicsScene() QEXT_OVERRIDE;

    /**
     * @brief graphModel
     * @return associated AbstractGraphModel.
     */
    const QExtBPAbstractGraphModel &graphModel() const;

    QExtBPAbstractGraphModel &graphModel();

    QExtBPAbstractNodeGeometry &nodeGeometry();

    QExtBPAbstractNodePainter &nodePainter();

    void setNodePainter(QScopedPointer<QExtBPAbstractNodePainter> newPainter);

    QUndoStack &undoStack();

    /**
     * @brief Creates a "draft" instance of ConnectionGraphicsObject.
     * The scene caches a "draft" connection which has one loose end.
     * After attachment the "draft" instance is deleted and instead a normal "full" connection is created.
     * @param newConnectionId
     * @return Return the "draft" instance for further geometry manipulations.
     */
    const QScopedPointer<QExtBPConnectionGraphicsObject> &makeDraftConnection(const QExtBPTypes::ConnectionId newConnectionId);

    /**
     * @brief Deletes "draft" connection.
     * The function is called when user releases the mouse button during the construction of the new connection without
     * attaching it to any node.
     */
    void resetDraftConnection();

    /**
     * @brief Deletes all the nodes. Connections are removed automatically.
     */
    void clearScene();

    /**
     * @brief Get NodeGraphicsObject associated with the given nodeId.
     * @param nodeId
     * @return QEXT_NULLPTR when the object is not found.
     */
    QExtBPNodeGraphicsObject *nodeGraphicsObject(QExtBPTypes::NodeId nodeId);

    /**
     * @brief Get ConnectionGraphicsObject corresponding to `connectionId`.
     * @param connectionId
     * @return `QEXT_NULLPTR` when the object is not found.
     */
    QExtBPConnectionGraphicsObject *connectionGraphicsObject(QExtBPTypes::ConnectionId connectionId);

    Qt::Orientation orientation() const;

    void setOrientation(Qt::Orientation const orientation);

    /**
     * @brief Get an instance of the scene context menu in subclass.
     * Default implementation returns `QEXT_NULLPTR`.
     * @param scenePos
     * @return
     */
    virtual QMenu *createSceneMenu(const QPointF scenePos);

Q_SIGNALS:
    void nodeMoved(const QExtBPTypes::NodeId nodeId, const QPointF &newLocation);

    void nodeClicked(const QExtBPTypes::NodeId nodeId);

    void nodeSelected(const QExtBPTypes::NodeId nodeId);

    void nodeDoubleClicked(const QExtBPTypes::NodeId nodeId);

    void nodeHovered(const QExtBPTypes::NodeId nodeId, QPoint const screenPos);

    void nodeHoverLeft(const QExtBPTypes::NodeId nodeId);

    void connectionHovered(const QExtBPTypes::ConnectionId connectionId, QPoint const screenPos);

    void connectionHoverLeft(const QExtBPTypes::ConnectionId connectionId);

    /**
     * @brief Signal allows showing custom context menu upon clicking a node.
     */
    void nodeContextMenu(const QExtBPTypes::NodeId nodeId, const QPointF pos);

public Q_SLOTS:
    /**
     * @brief Slot called when the `connectionId` is erased form the AbstractGraphModel.
     */
    void onConnectionDeleted(const QExtBPTypes::ConnectionId connectionId);

    /**
     * @brief Slot called when the `connectionId` is created in the AbstractGraphModel.
     */
    void onConnectionCreated(const QExtBPTypes::ConnectionId connectionId);

    void onNodeDeleted(const QExtBPTypes::NodeId nodeId);

    void onNodeCreated(const QExtBPTypes::NodeId nodeId);

    void onNodePositionUpdated(const QExtBPTypes::NodeId nodeId);

    void onNodeUpdated(const QExtBPTypes::NodeId nodeId);

    void onNodeClicked(const QExtBPTypes::NodeId nodeId);

    void onModelReset();

protected:
    QScopedPointer<QExtBPBasicGraphicsScenePrivate> dd_ptr;

    /**
     * @brief Creates Node and Connection graphics objects.
     * Function is used to populate an empty scene in the constructor.
     * We perform depth-first AbstractGraphModel traversal.
     * The connections are created by checking non-empty node `Out` ports.
     */
    void traverseGraphAndPopulateGraphicsObjects();

    /**
     * @brief Redraws adjacent nodes for given `connectionId`
     */
    void updateAttachedNodes(const QExtBPTypes::ConnectionId connectionId, const QExtBPTypes::PortTypeEnum portType);

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtBPBasicGraphicsScene)
    QEXT_DISABLE_COPY_MOVE(QExtBPBasicGraphicsScene)
};

#endif // _QEXTBPBASICGRAPHICSSCENE_H
