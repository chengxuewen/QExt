#include <qextBPNodeConnectionInteraction.h>
#include <qextBPConnectionGraphicsObject.h>
#include <qextBPAbstractNodeGeometry.h>
#include <qextBPBasicGraphicsScene.h>
#include <qextBPNodeGraphicsObject.h>
#include <qextBPUndoCommands.h>
#include <qextBPUtils.h>

#include <QtCore/QDebug>

#include <QUndoStack>

QExtBPNodeConnectionInteraction::QExtBPNodeConnectionInteraction(QExtBPNodeGraphicsObject &ngo,
                                                                 QExtBPConnectionGraphicsObject &cgo,
                                                                 QExtBPBasicGraphicsScene &scene)
    : _ngo(ngo)
    , _cgo(cgo)
    , _scene(scene)
{}

bool QExtBPNodeConnectionInteraction::canConnect(QExtBPTypes::PortIndex *portIndex) const
{
    // 1. Connection requires a port.

    QExtBPTypes::PortTypeEnum requiredPort = _cgo.connectionState().requiredPort();

    if (requiredPort == QExtBPTypes::PortType_None) {
        return false;
    }

    QExtBPTypes::NodeId connectedNodeId = QExtBPUtils::getNodeId(QExtBPUtils::oppositePort(requiredPort), _cgo.connectionId());

    // 2. Forbid connecting the node to itself.

    if (_ngo.nodeId() == connectedNodeId)
        return false;

    // 3. Connection loose end is above the node port.

    QPointF connectionPoint = _cgo.sceneTransform().map(_cgo.endPoint(requiredPort));

    *portIndex = nodePortIndexUnderScenePoint(requiredPort, connectionPoint);

    if (*portIndex == QExtBPTypes::InvalidPortIndex) {
        return false;
    }

    // 4. Model allows connection.

    QExtBPAbstractGraphModel &model = _ngo.nodeScene()->graphModel();

    QExtBPTypes::ConnectionId connectionId = QExtBPUtils::makeCompleteConnectionId(_cgo.connectionId(), // incomplete
                                                                                   _ngo.nodeId(),       // missing node id
                                                                                   *portIndex);         // missing port index

    return model.connectionPossible(connectionId);
}

bool QExtBPNodeConnectionInteraction::tryConnect() const
{
    // 1. Check conditions from 'canConnect'.

    QExtBPTypes::PortIndex targetPortIndex = QExtBPTypes::InvalidPortIndex;
    if (!canConnect(&targetPortIndex)) {
        return false;
    }

    // 2. Create new connection.

    QExtBPTypes::ConnectionId incompleteConnectionId = _cgo.connectionId();

    QExtBPTypes::ConnectionId newConnectionId = QExtBPUtils::makeCompleteConnectionId(incompleteConnectionId,
                                                                                      _ngo.nodeId(),
                                                                                      targetPortIndex);

    _ngo.nodeScene()->resetDraftConnection();

    _ngo.nodeScene()->undoStack().push(new ConnectCommand(_ngo.nodeScene(), newConnectionId));

    return true;
}

bool QExtBPNodeConnectionInteraction::disconnect(QExtBPTypes::PortTypeEnum portToDisconnect) const
{
    QExtBPTypes::ConnectionId connectionId = _cgo.connectionId();

    _scene.undoStack().push(new QExtBPDisconnectCommand(&_scene, connectionId));

    QExtBPAbstractNodeGeometry &geometry = _scene.nodeGeometry();

    QPointF scenePos = geometry.portScenePosition(_ngo.nodeId(),
                                                  portToDisconnect,
                                                  QExtBPUtils::getPortIndex(portToDisconnect, connectionId),
                                                  _ngo.sceneTransform());

    // Converted to "draft" connection with the new incomplete id.
    QExtBPTypes::ConnectionId incompleteConnectionId = QExtBPUtils::makeIncompleteConnectionId(connectionId, portToDisconnect);

    // Grabs the mouse
    const auto &draftConnection = _scene.makeDraftConnection(incompleteConnectionId);

    const QPointF looseEndPos = draftConnection->mapFromScene(scenePos);
    draftConnection->setEndPoint(portToDisconnect, looseEndPos);

    // Repaint connection points.
    QExtBPTypes::NodeId connectedNodeId = QExtBPUtils::getNodeId(QExtBPUtils::oppositePort(portToDisconnect), connectionId);
    _scene.nodeGraphicsObject(connectedNodeId)->update();

    QExtBPTypes::NodeId disconnectedNodeId = QExtBPUtils::getNodeId(portToDisconnect, connectionId);
    _scene.nodeGraphicsObject(disconnectedNodeId)->update();

    return true;
}

// ------------------ util functions below

QExtBPTypes::PortTypeEnum QExtBPNodeConnectionInteraction::connectionRequiredPort() const
{
    const auto &state = _cgo.connectionState();

    return state.requiredPort();
}

QPointF QExtBPNodeConnectionInteraction::nodePortScenePosition(QExtBPTypes::PortTypeEnum portType,
                                                               QExtBPTypes::PortIndex portIndex) const
{
    QExtBPAbstractNodeGeometry &geometry = _scene.nodeGeometry();

    QPointF p = geometry.portScenePosition(_ngo.nodeId(),
                                           portType,
                                           portIndex,
                                           _ngo.sceneTransform());

    return p;
}

QExtBPTypes::PortIndex QExtBPNodeConnectionInteraction::nodePortIndexUnderScenePoint(QExtBPTypes::PortTypeEnum portType,
                                                                                     const QPointF &scenePoint) const
{
    QExtBPAbstractNodeGeometry &geometry = _scene.nodeGeometry();

    QTransform sceneTransform = _ngo.sceneTransform();

    QPointF nodePoint = sceneTransform.inverted().map(scenePoint);

    return geometry.checkPortHit(_ngo.nodeId(), portType, nodePoint);
}
