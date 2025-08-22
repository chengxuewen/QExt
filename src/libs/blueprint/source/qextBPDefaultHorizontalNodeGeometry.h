#ifndef _QEXTBPDEFAULTHORIZONTALNODEGEOMETRY_H
#define _QEXTBPDEFAULTHORIZONTALNODEGEOMETRY_H

#include <qextBPAbstractNodeGeometry.h>

#include <QtGui/QFontMetrics>

class QExtBPAbstractGraphModel;
class QExtBPBasicGraphicsScene;

class QExtBPDefaultHorizontalNodeGeometryPrivate;
class QEXT_BLUEPRINT_API QExtBPDefaultHorizontalNodeGeometry : public QExtBPAbstractNodeGeometry
{
public:
    QExtBPDefaultHorizontalNodeGeometry(QExtBPAbstractGraphModel &graphModel);
    ~QExtBPDefaultHorizontalNodeGeometry() QEXT_OVERRIDE;

    QSize size(const QExtBPTypes::NodeId nodeId) const override;

    void recomputeSize(const QExtBPTypes::NodeId nodeId) const override;

    QPointF portPosition(const QExtBPTypes::NodeId nodeId,
                         const QExtBPTypes::PortTypeEnum portType,
                         const QExtBPTypes::PortIndex index) const override;

    QPointF portTextPosition(const QExtBPTypes::NodeId nodeId,
                             const QExtBPTypes::PortTypeEnum portType,
                             const QExtBPTypes::PortIndex portIndex) const override;
    QPointF captionPosition(const QExtBPTypes::NodeId nodeId) const override;

    QRectF captionRect(const QExtBPTypes::NodeId nodeId) const override;

    QPointF widgetPosition(const QExtBPTypes::NodeId nodeId) const override;

    QRect resizeHandleRect(const QExtBPTypes::NodeId nodeId) const override;

private:
    QRectF portTextRect(const QExtBPTypes::NodeId nodeId,
                        const QExtBPTypes::PortTypeEnum portType,
                        const QExtBPTypes::PortIndex portIndex) const;

    /// Finds max number of ports and multiplies by (a port height + interval)
    unsigned int maxVerticalPortsExtent(const QExtBPTypes::NodeId nodeId) const;

    unsigned int maxPortsTextAdvance(const QExtBPTypes::NodeId nodeId, const QExtBPTypes::PortTypeEnum portType) const;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtBPDefaultHorizontalNodeGeometry)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtBPDefaultHorizontalNodeGeometry)
};

#endif // _QEXTBPDEFAULTHORIZONTALNODEGEOMETRY_H
