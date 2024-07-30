#ifndef _QEXTBPABSTRACTNODEPAINTER_H
#define _QEXTBPABSTRACTNODEPAINTER_H

#include <qextBlueprintGlobal.h>

#include <QPainter>

class QExtBPNodeGraphicsObject;

/**
 * @brief Class enables custom painting.
 */
class QEXT_BLUEPRINT_API QExtBPAbstractNodePainter
{
public:
    virtual ~QExtBPAbstractNodePainter() {}

    /**
     * @brief Reimplement this function in order to have a custom painting.
     * Useful functions:
     *  `NodeGraphicsObject::nodeScene()->nodeGeometry()`
     *  `NodeGraphicsObject::graphModel()`
     */
    virtual void paint(QPainter *painter, QExtBPNodeGraphicsObject &object) const = 0;
};

#endif // _QEXTBPABSTRACTNODEPAINTER_H
