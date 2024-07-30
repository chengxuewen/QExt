#ifndef _QEXTBPNODECONNECTIONINTERACTION_H
#define _QEXTBPNODECONNECTIONINTERACTION_H

#include <qextBPTypes.h>

#include <QtCore/QPointF>

class QExtBPConnectionGraphicsObject;
class QExtBPNodeGraphicsObject;
class QExtBPBasicGraphicsScene;

/// Class wraps conecting and disconnecting checks.
/**
 * An instance should be created on the stack and destroyed
 * automatically when the operation is completed
 */
class QExtBPNodeConnectionInteraction
{
public:
    QExtBPNodeConnectionInteraction(QExtBPNodeGraphicsObject &ngo,
                                    QExtBPConnectionGraphicsObject &cgo,
                                    QExtBPBasicGraphicsScene &scene);

    /**
   * Can connect when following conditions are met:
   * 1. Connection 'requires' a port.
   * 2. Connection loose end is above the node port.
   * 3. Source and target `nodeId`s are different.
   * 4. GraphModel permits connection.
   */
    bool canConnect(QExtBPTypes::PortIndex *portIndex) const;

    /// Creates a new connectino if possible.
    /**
   * 1. Check conditions from 'canConnect'.
   * 2. Creates new connection with `GraphModel::addConnection`.
   * 3. Adjust connection geometry.
   */
    bool tryConnect() const;

    /**
   * 1. Delete connection with `GraphModel::deleteConnection`.
   * 2. Create a "draft" connection with incomplete `ConnectionId`.
   * 3. Repaint both previously connected nodes.
   */
    bool disconnect(QExtBPTypes::PortTypeEnum portToDisconnect) const;

private:
    QExtBPTypes::PortTypeEnum connectionRequiredPort() const;

    QPointF connectionEndScenePosition(QExtBPTypes::PortTypeEnum) const;

    QPointF nodePortScenePosition(QExtBPTypes::PortTypeEnum portType, QExtBPTypes::PortIndex portIndex) const;

    QExtBPTypes::PortIndex nodePortIndexUnderScenePoint(QExtBPTypes::PortTypeEnum portType, const QPointF &p) const;

private:
    QExtBPNodeGraphicsObject &_ngo;

    QExtBPConnectionGraphicsObject &_cgo;

    QExtBPBasicGraphicsScene &_scene;
};

#endif // _QEXTBPNODECONNECTIONINTERACTION_H
