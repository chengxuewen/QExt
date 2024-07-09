#pragma once

#include "qextBPTypes.h"
#include <qextBlueprintGlobal.h>

#include <QRectF>
#include <QSize>
#include <QTransform>

class QExtBPAbstractGraphModel;

class QEXT_BLUEPRINT_API QExtBPAbstractNodeGeometry
{
public:
    QExtBPAbstractNodeGeometry(QExtBPAbstractGraphModel &);
    virtual ~QExtBPAbstractNodeGeometry() {}

    /**
   * The node's size plus some additional margin around it to account for drawing
   * effects (for example shadows) or node's parts outside the size rectangle
   * (for example port points).
   *
   * The default implementation returns QSize + 20 percent of width and heights
   * at each side of the rectangle.
   */
    virtual QRectF boundingRect(QExtBPTypes::NodeId const nodeId) const;

    /// A direct rectangle defining the borders of the node's rectangle.
    virtual QSize size(QExtBPTypes::NodeId const nodeId) const = 0;

    /**
   * The function is triggeren when a nuber of ports is changed or when an
   * embedded widget needs an update.
   */
    virtual void recomputeSize(QExtBPTypes::NodeId const nodeId) const = 0;

    /// Port position in node's coordinate system.
    virtual QPointF portPosition(QExtBPTypes::NodeId const nodeId,
                                 QExtBPTypes::PortTypeEnum const portType,
                                 QExtBPTypes::PortIndex const index) const
    = 0;

    /// A convenience function using the `portPosition` and a given transformation.
    virtual QPointF portScenePosition(QExtBPTypes::NodeId const nodeId,
                                      QExtBPTypes::PortTypeEnum const portType,
                                      QExtBPTypes::PortIndex const index,
                                      QTransform const &t) const;

    /// Defines where to draw port label. The point corresponds to a font baseline.
    virtual QPointF portTextPosition(QExtBPTypes::NodeId const nodeId,
                                     QExtBPTypes::PortTypeEnum const portType,
                                     QExtBPTypes::PortIndex const portIndex) const
    = 0;

    /**
   * Defines where to start drawing the caption. The point corresponds to a font
   * baseline.
   */
    virtual QPointF captionPosition(QExtBPTypes::NodeId const nodeId) const = 0;

    /// Caption rect is needed for estimating the total node size.
    virtual QRectF captionRect(QExtBPTypes::NodeId const nodeId) const = 0;

    /// Position for an embedded widget. Return any value if you don't embed.
    virtual QPointF widgetPosition(QExtBPTypes::NodeId const nodeId) const = 0;

    virtual QExtBPTypes::PortIndex checkPortHit(QExtBPTypes::NodeId const nodeId,
                                                QExtBPTypes::PortTypeEnum const portType,
                                                QPointF const nodePoint) const;

    virtual QRect resizeHandleRect(QExtBPTypes::NodeId const nodeId) const = 0;

protected:
    QExtBPAbstractGraphModel &_graphModel;
};

