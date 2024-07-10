#ifndef _QEXTBPLOCATENODE_H
#define _QEXTBPLOCATENODE_H

#include <QtCore/QPointF>
#include <QtGui/QTransform>

class QGraphicsScene;

class QExtBPNodeGraphicsObject;

QExtBPNodeGraphicsObject *locateNodeAt(QPointF scenePoint,
                                       QGraphicsScene &scene,
                                       QTransform const &viewTransform);

#endif // _QEXTBPLOCATENODE_H

