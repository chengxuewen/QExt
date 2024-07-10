#ifndef _QEXTBPDEFAULTVERTICALNODEGEOMETRY_H
#define _QEXTBPDEFAULTVERTICALNODEGEOMETRY_H

#include <qextBPAbstractNodeGeometry.h>

#include <QFontMetrics>

class QExtBPAbstractGraphModel;
class QExtBPBasicGraphicsScene;

class QEXT_BLUEPRINT_API QExtBPDefaultVerticalNodeGeometry : public QExtBPAbstractNodeGeometry
{
public:
    QExtBPDefaultVerticalNodeGeometry(QExtBPAbstractGraphModel &graphModel);

public:
    QSize size(QExtBPTypes::NodeId const nodeId) const override;

    void recomputeSize(QExtBPTypes::NodeId const nodeId) const override;

    QPointF portPosition(QExtBPTypes::NodeId const nodeId,
                         QExtBPTypes::PortTypeEnum const portType,
                         QExtBPTypes::PortIndex const index) const override;

    QPointF portTextPosition(QExtBPTypes::NodeId const nodeId,
                             QExtBPTypes::PortTypeEnum const portType,
                             QExtBPTypes::PortIndex const portIndex) const override;

    QPointF captionPosition(QExtBPTypes::NodeId const nodeId) const override;

    QRectF captionRect(QExtBPTypes::NodeId const nodeId) const override;

    QPointF widgetPosition(QExtBPTypes::NodeId const nodeId) const override;

    QRect resizeHandleRect(QExtBPTypes::NodeId const nodeId) const override;

private:
    QRectF portTextRect(QExtBPTypes::NodeId const nodeId,
                        QExtBPTypes::PortTypeEnum const portType,
                        QExtBPTypes::PortIndex const portIndex) const;
    /// Finds
    unsigned int maxHorizontalPortsExtent(QExtBPTypes::NodeId const nodeId) const;

    unsigned int maxPortsTextAdvance(QExtBPTypes::NodeId const nodeId, QExtBPTypes::PortTypeEnum const portType) const;

    unsigned int portCaptionsHeight(QExtBPTypes::NodeId const nodeId, QExtBPTypes::PortTypeEnum const portType) const;

private:
    // Some variables are mutable because we need to change drawing
    // metrics corresponding to fontMetrics but this doesn't change
    // constness of the Node.

    mutable unsigned int _portSize;
    unsigned int _portSpasing;
    mutable QFontMetrics _fontMetrics;
    mutable QFontMetrics _boldFontMetrics;
};

#endif // _QEXTBPDEFAULTVERTICALNODEGEOMETRY_H
