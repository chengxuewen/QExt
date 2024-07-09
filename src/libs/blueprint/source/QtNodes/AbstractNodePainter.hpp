#pragma once

#include <QPainter>

#include <qextBlueprintGlobal.h>

class QPainter;

class QExtBPNodeGraphicsObject;

/// Class enables custom painting.
class QEXT_BLUEPRINT_API QExtBPAbstractNodePainter
{
public:
    virtual ~QExtBPAbstractNodePainter() = default;

    /**
   * Reimplement this function in order to have a custom painting.
   *
   * Useful functions:
   * `NodeGraphicsObject::nodeScene()->nodeGeometry()`
   * `NodeGraphicsObject::graphModel()`
   */
    virtual void paint(QPainter *painter, QExtBPNodeGraphicsObject &ngo) const = 0;
};
