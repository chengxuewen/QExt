#ifndef _QEXTBPABSTRACTNODEGEOMETRY_H
#define _QEXTBPABSTRACTNODEGEOMETRY_H

#include <qextBlueprintGlobal.h>
#include <qextBPTypes.h>

#include <QSize>
#include <QRectF>
#include <QTransform>

class QExtBPAbstractGraphModel;
class QExtBPAbstractNodeGeometryPrivate;
class QEXT_BLUEPRINT_API QExtBPAbstractNodeGeometry
{
public:
    explicit QExtBPAbstractNodeGeometry(QExtBPAbstractGraphModel &graphModel);
    QExtBPAbstractNodeGeometry(QExtBPAbstractNodeGeometryPrivate *d);
    virtual ~QExtBPAbstractNodeGeometry();

    /**
     * @brief The node's size plus some additional margin around it to account for drawing
     * effects (for example shadows) or node's parts outside the size rectangle
     * (for example port points).
     *
     * The default implementation returns QSize + 20 percent of width and heights
     * at each side of the rectangle.
     */
    virtual QRectF boundingRect(const QExtBPTypes::NodeId nodeId) const;

    /**
     * @brief A direct rectangle defining the borders of the node's rectangle.
     */
    virtual QSize size(const QExtBPTypes::NodeId nodeId) const = 0;

    /**
     * @brief The function is triggeren when a nuber of ports is changed or when an embedded widget needs an update.
     */
    virtual void recomputeSize(const QExtBPTypes::NodeId nodeId) const = 0;

    /**
     * @brief Port position in node's coordinate system.
     */
    virtual QPointF portPosition(const QExtBPTypes::NodeId nodeId,
                                 const QExtBPTypes::PortTypeEnum portType,
                                 const QExtBPTypes::PortIndex index) const = 0;

    /**
     * @brief A convenience function using the `portPosition` and a given transformation.
     */
    virtual QPointF portScenePosition(const QExtBPTypes::NodeId nodeId,
                                      const QExtBPTypes::PortTypeEnum portType,
                                      const QExtBPTypes::PortIndex index,
                                      const QTransform &t) const;

    /**
     * @brief Defines where to draw port label. The point corresponds to a font baseline.
     */
    virtual QPointF portTextPosition(const QExtBPTypes::NodeId nodeId,
                                     const QExtBPTypes::PortTypeEnum portType,
                                     const QExtBPTypes::PortIndex portIndex) const = 0;

    /**
     * @brief Defines where to start drawing the caption. The point corresponds to a font baseline.
     */
    virtual QPointF captionPosition(const QExtBPTypes::NodeId nodeId) const = 0;

    /**
     * @brief Caption rect is needed for estimating the total node size.
     */
    virtual QRectF captionRect(const QExtBPTypes::NodeId nodeId) const = 0;

    /**
     * @brief Position for an embedded widget. Return any value if you don't embed.
     */
    virtual QPointF widgetPosition(const QExtBPTypes::NodeId nodeId) const = 0;

    virtual QExtBPTypes::PortIndex checkPortHit(const QExtBPTypes::NodeId nodeId,
                                                const QExtBPTypes::PortTypeEnum portType,
                                                const QPointF nodePoint) const;

    virtual QRect resizeHandleRect(const QExtBPTypes::NodeId nodeId) const = 0;

protected:
    QScopedPointer<QExtBPAbstractNodeGeometryPrivate> dd_ptr;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtBPAbstractNodeGeometry)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtBPAbstractNodeGeometry)
};

#endif // _QEXTBPABSTRACTNODEGEOMETRY_H
