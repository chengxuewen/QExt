#ifndef _QEXTBPABSTRACTNODEGEOMETRY_H
#define _QEXTBPABSTRACTNODEGEOMETRY_H

#include <qextBlueprintGlobal.h>
#include <qextBPTypes.h>

#include <QSize>
#include <QRectF>
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
    virtual QRectF boundingRect(const QExtBPTypes::NodeId nodeId) const;

    /// A direct rectangle defining the borders of the node's rectangle.
    virtual QSize size(const QExtBPTypes::NodeId nodeId) const = 0;

    /**
   * The function is triggeren when a nuber of ports is changed or when an
   * embedded widget needs an update.
   */
    virtual void recomputeSize(const QExtBPTypes::NodeId nodeId) const = 0;

    /// Port position in node's coordinate system.
    virtual QPointF portPosition(const QExtBPTypes::NodeId nodeId,
                                 const QExtBPTypes::PortTypeEnum portType,
                                 const QExtBPTypes::PortIndex index) const
    = 0;

    /// A convenience function using the `portPosition` and a given transformation.
    virtual QPointF portScenePosition(const QExtBPTypes::NodeId nodeId,
                                      const QExtBPTypes::PortTypeEnum portType,
                                      const QExtBPTypes::PortIndex index,
                                      const QTransform &t) const;

    /// Defines where to draw port label. The point corresponds to a font baseline.
    virtual QPointF portTextPosition(const QExtBPTypes::NodeId nodeId,
                                     const QExtBPTypes::PortTypeEnum portType,
                                     const QExtBPTypes::PortIndex portIndex) const
    = 0;

    /**
   * Defines where to start drawing the caption. The point corresponds to a font
   * baseline.
   */
    virtual QPointF captionPosition(const QExtBPTypes::NodeId nodeId) const = 0;

    /// Caption rect is needed for estimating the total node size.
    virtual QRectF captionRect(const QExtBPTypes::NodeId nodeId) const = 0;

    /// Position for an embedded widget. Return any value if you don't embed.
    virtual QPointF widgetPosition(const QExtBPTypes::NodeId nodeId) const = 0;

    virtual QExtBPTypes::PortIndex checkPortHit(const QExtBPTypes::NodeId nodeId,
                                                const QExtBPTypes::PortTypeEnum portType,
                                                const QPointF nodePoint) const;

    virtual QRect resizeHandleRect(const QExtBPTypes::NodeId nodeId) const = 0;

protected:
    QExtBPAbstractGraphModel &m_graphModel;
};

#endif // _QEXTBPABSTRACTNODEGEOMETRY_H
