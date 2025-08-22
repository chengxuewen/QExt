#ifndef _QEXTBPDEFAULTVERTICALNODEGEOMETRY_H
#define _QEXTBPDEFAULTVERTICALNODEGEOMETRY_H

#include <qextBPAbstractNodeGeometry.h>

#include <QFontMetrics>

class QExtBPAbstractGraphModel;
class QExtBPBasicGraphicsScene;
class QExtBPDefaultVerticalNodeGeometryPrivate;
class QEXT_BLUEPRINT_API QExtBPDefaultVerticalNodeGeometry : public QExtBPAbstractNodeGeometry
{
public:
    QExtBPDefaultVerticalNodeGeometry(QExtBPAbstractGraphModel &graphModel);


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
    /// Finds
    unsigned int maxHorizontalPortsExtent(const QExtBPTypes::NodeId nodeId) const;

    unsigned int maxPortsTextAdvance(const QExtBPTypes::NodeId nodeId, const QExtBPTypes::PortTypeEnum portType) const;

    unsigned int portCaptionsHeight(const QExtBPTypes::NodeId nodeId, const QExtBPTypes::PortTypeEnum portType) const;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtBPDefaultVerticalNodeGeometry)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtBPDefaultVerticalNodeGeometry)
};

#endif // _QEXTBPDEFAULTVERTICALNODEGEOMETRY_H
