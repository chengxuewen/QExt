#pragma once

#include <QtCore/QPointF>
#include <QtGui/QTransform>

class QGraphicsScene;

class QExtBPNodeGraphicsObject;

QExtBPNodeGraphicsObject *locateNodeAt(QPointF scenePoint,
                                       QGraphicsScene &scene,
                                       QTransform const &viewTransform);

