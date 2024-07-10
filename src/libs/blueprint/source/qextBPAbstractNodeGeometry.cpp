#include <qextBPAbstractNodeGeometry.h>
#include <qextBPAbstractGraphModel.h>
#include <qextBPStyleCollection.h>

#include <QMargins>

#include <cmath>

QExtBPAbstractNodeGeometry::QExtBPAbstractNodeGeometry(QExtBPAbstractGraphModel &graphModel)
    : _graphModel(graphModel)
{
    //
}

QRectF QExtBPAbstractNodeGeometry::boundingRect(QExtBPTypes::NodeId const nodeId) const
{
    QSize s = size(nodeId);

    double ratio = 0.20;

    int widthMargin = s.width() * ratio;
    int heightMargin = s.height() * ratio;

    QMargins margins(widthMargin, heightMargin, widthMargin, heightMargin);

    QRectF r(QPointF(0, 0), s);

    return r.marginsAdded(margins);
}

QPointF QExtBPAbstractNodeGeometry::portScenePosition(QExtBPTypes::NodeId const nodeId,
                                                      QExtBPTypes::PortTypeEnum const portType,
                                                      QExtBPTypes::PortIndex const index,
                                                      QTransform const &t) const
{
    QPointF result = portPosition(nodeId, portType, index);

    return t.map(result);
}

QExtBPTypes::PortIndex QExtBPAbstractNodeGeometry::checkPortHit(QExtBPTypes::NodeId const nodeId,
                                                                QExtBPTypes::PortTypeEnum const portType,
                                                                QPointF const nodePoint) const
{
    auto const &nodeStyle = QExtBPStyleCollection::nodeStyle();

    QExtBPTypes::PortIndex result = QExtBPTypes::InvalidPortIndex;

    if (portType == QExtBPTypes::PortType_None)
        return result;

    double const tolerance = 2.0 * nodeStyle.ConnectionPointDiameter;

    size_t const n = _graphModel.nodeData<unsigned int>(nodeId,
                                                        (portType == QExtBPTypes::PortType_Out)
                                                        ? QExtBPTypes::NodeRole_OutPortCount
                                                        : QExtBPTypes::NodeRole_InPortCount);

    for (unsigned int portIndex = 0; portIndex < n; ++portIndex) {
        auto pp = portPosition(nodeId, portType, portIndex);

        QPointF p = pp - nodePoint;
        auto distance = std::sqrt(QPointF::dotProduct(p, p));

        if (distance < tolerance) {
            result = portIndex;
            break;
        }
    }

    return result;
}
