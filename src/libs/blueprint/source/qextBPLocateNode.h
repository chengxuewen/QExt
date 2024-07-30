#ifndef _QEXTBPLOCATENODE_H
#define _QEXTBPLOCATENODE_H

#include <qextBlueprintGlobal.h>

#include <QtCore/QPointF>
#include <QtGui/QTransform>

class QGraphicsScene;

class QExtBPNodeGraphicsObject;

class QEXT_BLUEPRINT_API QExtBPLocateNode
{
public:
    QExtBPLocateNode() {}
    virtual ~QExtBPLocateNode() {}

    static QExtBPNodeGraphicsObject *locateNodeAt(QPointF scenePoint,
                                                  QGraphicsScene &scene,
                                                  const QTransform &viewTransform);
};

#endif // _QEXTBPLOCATENODE_H

