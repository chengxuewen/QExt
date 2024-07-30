#include <qextBPDefaultNodePainter.h>
#include <qextBPConnectionGraphicsObject.h>
#include <qextBPAbstractNodeGeometry.h>
#include <qextBPAbstractGraphModel.h>
#include <qextBPBasicGraphicsScene.h>
#include <qextBPNodeGraphicsObject.h>
#include <qextBPStyleCollection.h>
#include <qextBPNodeState.h>
#include <qextBPUtils.h>

#include <cmath>

#include <QtCore/QMargins>

void QExtBPDefaultNodePainter::paint(QPainter *painter, QExtBPNodeGraphicsObject &ngo) const
{
    // TODO?
    //AbstractNodeGeometry & geometry = ngo.nodeScene()->nodeGeometry();
    //geometry.recomputeSizeIfFontChanged(painter->font());

    drawNodeRect(painter, ngo);

    drawConnectionPoints(painter, ngo);

    drawFilledConnectionPoints(painter, ngo);

    drawNodeCaption(painter, ngo);

    drawEntryLabels(painter, ngo);

    drawResizeRect(painter, ngo);
}

void QExtBPDefaultNodePainter::drawNodeRect(QPainter *painter, QExtBPNodeGraphicsObject &ngo) const
{
    QExtBPAbstractGraphModel &model = ngo.graphModel();

    const QExtBPTypes::NodeId nodeId = ngo.nodeId();

    QExtBPAbstractNodeGeometry &geometry = ngo.nodeScene()->nodeGeometry();

    QSize size = geometry.size(nodeId);

    QJsonDocument json = QJsonDocument::fromVariant(model.nodeData(nodeId, QExtBPTypes::NodeRole_Style));

    QExtBPNodeStyle nodeStyle(json.object());

    auto color = ngo.isSelected() ? nodeStyle.SelectedBoundaryColor : nodeStyle.NormalBoundaryColor;

    if (ngo.nodeState().hovered())
    {
        QPen p(color, nodeStyle.HoveredPenWidth);
        painter->setPen(p);
    }
    else
    {
        QPen p(color, nodeStyle.PenWidth);
        painter->setPen(p);
    }

    QLinearGradient gradient(QPointF(0.0, 0.0), QPointF(2.0, size.height()));

    gradient.setColorAt(0.0, nodeStyle.GradientColor0);
    gradient.setColorAt(0.10, nodeStyle.GradientColor1);
    gradient.setColorAt(0.90, nodeStyle.GradientColor2);
    gradient.setColorAt(1.0, nodeStyle.GradientColor3);

    painter->setBrush(gradient);

    QRectF boundary(0, 0, size.width(), size.height());

    double const radius = 3.0;

    painter->drawRoundedRect(boundary, radius, radius);
}

void QExtBPDefaultNodePainter::drawConnectionPoints(QPainter *painter, QExtBPNodeGraphicsObject &ngo) const
{
    QExtBPAbstractGraphModel &model = ngo.graphModel();
    const QExtBPTypes::NodeId nodeId = ngo.nodeId();
    QExtBPAbstractNodeGeometry &geometry = ngo.nodeScene()->nodeGeometry();

    QJsonDocument json = QJsonDocument::fromVariant(model.nodeData(nodeId, QExtBPTypes::NodeRole_Style));
    QExtBPNodeStyle nodeStyle(json.object());

    const auto &connectionStyle = QExtBPStyleCollection::connectionStyle();

    float diameter = nodeStyle.ConnectionPointDiameter;
    auto reducedDiameter = diameter * 0.6;

    for (QExtBPTypes::PortTypeEnum portType : {QExtBPTypes::PortType_Out, QExtBPTypes::PortType_In})
    {
        size_t const n = model
                .nodeData(nodeId,
                          (portType == QExtBPTypes::PortType_Out) ? QExtBPTypes::NodeRole_OutPortCount
                                                                  : QExtBPTypes::NodeRole_InPortCount)
                .toUInt();

        for (QExtBPTypes::PortIndex portIndex = 0; portIndex < n; ++portIndex)
        {
            QPointF p = geometry.portPosition(nodeId, portType, portIndex);

            const auto &dataType = model.portData(nodeId, portType, portIndex,
                                                  QExtBPTypes::PortRole_DataType).value<QExtBPNodeDataType>();

            double r = 1.0;

            const QExtBPNodeState &state = ngo.nodeState();

            if (auto const *cgo = state.connectionForReaction())
            {
                QExtBPTypes::PortTypeEnum requiredPort = cgo->connectionState().requiredPort();

                if (requiredPort == portType)
                {
                    QExtBPTypes::ConnectionId possibleConnectionId = QExtBPUtils::makeCompleteConnectionId(cgo->connectionId(),
                                                                                                           nodeId,
                                                                                                           portIndex);

                    bool const possible = model.connectionPossible(possibleConnectionId);

                    auto cp = cgo->sceneTransform().map(cgo->endPoint(requiredPort));
                    cp = ngo.sceneTransform().inverted().map(cp);

                    auto diff = cp - p;
                    double dist = std::sqrt(QPointF::dotProduct(diff, diff));

                    if (possible)
                    {
                        double const thres = 40.0;
                        r = (dist < thres) ? (2.0 - dist / thres) : 1.0;
                    }
                    else
                    {
                        double const thres = 80.0;
                        r = (dist < thres) ? (dist / thres) : 1.0;
                    }
                }
            }

            if (connectionStyle.useDataDefinedColors())
            {
                painter->setBrush(connectionStyle.normalColor(dataType.id));
            }
            else
            {
                painter->setBrush(nodeStyle.ConnectionPointColor);
            }

            painter->drawEllipse(p, reducedDiameter * r, reducedDiameter * r);
        }
    }

    if (ngo.nodeState().connectionForReaction())
    {
        ngo.nodeState().resetConnectionForReaction();
    }
}

void QExtBPDefaultNodePainter::drawFilledConnectionPoints(QPainter *painter, QExtBPNodeGraphicsObject &ngo) const
{
    QExtBPAbstractGraphModel &model = ngo.graphModel();
    const QExtBPTypes::NodeId nodeId = ngo.nodeId();
    QExtBPAbstractNodeGeometry &geometry = ngo.nodeScene()->nodeGeometry();

    QJsonDocument json = QJsonDocument::fromVariant(model.nodeData(nodeId, QExtBPTypes::NodeRole_Style));
    QExtBPNodeStyle nodeStyle(json.object());

    auto diameter = nodeStyle.ConnectionPointDiameter;

    for (QExtBPTypes::PortTypeEnum portType : {QExtBPTypes::PortType_Out, QExtBPTypes::PortType_In})
    {
        size_t const n = model
                .nodeData(nodeId,
                          (portType == QExtBPTypes::PortType_Out) ? QExtBPTypes::NodeRole_OutPortCount
                                                                  : QExtBPTypes::NodeRole_InPortCount)
                .toUInt();

        for (QExtBPTypes::PortIndex portIndex = 0; portIndex < n; ++portIndex)
        {
            QPointF p = geometry.portPosition(nodeId, portType, portIndex);

            const auto &connected = model.connections(nodeId, portType, portIndex);

            if (!connected.empty())
            {
                const auto &dataType = model
                        .portData(nodeId, portType, portIndex, QExtBPTypes::PortRole_DataType)
                        .value<QExtBPNodeDataType>();

                const auto &connectionStyle = QExtBPStyleCollection::connectionStyle();
                if (connectionStyle.useDataDefinedColors())
                {
                    QColor const c = connectionStyle.normalColor(dataType.id);
                    painter->setPen(c);
                    painter->setBrush(c);
                }
                else
                {
                    painter->setPen(nodeStyle.FilledConnectionPointColor);
                    painter->setBrush(nodeStyle.FilledConnectionPointColor);
                }

                painter->drawEllipse(p, diameter * 0.4, diameter * 0.4);
            }
        }
    }
}

void QExtBPDefaultNodePainter::drawNodeCaption(QPainter *painter, QExtBPNodeGraphicsObject &ngo) const
{
    QExtBPAbstractGraphModel &model = ngo.graphModel();
    const QExtBPTypes::NodeId nodeId = ngo.nodeId();
    QExtBPAbstractNodeGeometry &geometry = ngo.nodeScene()->nodeGeometry();

    if (!model.nodeData(nodeId, QExtBPTypes::NodeRole_CaptionVisible).toBool())
    {
        return;
    }

    QString const name = model.nodeData(nodeId, QExtBPTypes::NodeRole_Caption).toString();

    QFont f = painter->font();
    f.setBold(true);

    QPointF position = geometry.captionPosition(nodeId);

    QJsonDocument json = QJsonDocument::fromVariant(model.nodeData(nodeId, QExtBPTypes::NodeRole_Style));
    QExtBPNodeStyle nodeStyle(json.object());

    painter->setFont(f);
    painter->setPen(nodeStyle.FontColor);
    painter->drawText(position, name);

    f.setBold(false);
    painter->setFont(f);
}

void QExtBPDefaultNodePainter::drawEntryLabels(QPainter *painter, QExtBPNodeGraphicsObject &ngo) const
{
    QExtBPAbstractGraphModel &model = ngo.graphModel();
    const QExtBPTypes::NodeId nodeId = ngo.nodeId();
    QExtBPAbstractNodeGeometry &geometry = ngo.nodeScene()->nodeGeometry();

    QJsonDocument json = QJsonDocument::fromVariant(model.nodeData(nodeId, QExtBPTypes::NodeRole_Style));
    QExtBPNodeStyle nodeStyle(json.object());

    for (QExtBPTypes::PortTypeEnum portType : {QExtBPTypes::PortType_Out, QExtBPTypes::PortType_In})
    {
        unsigned int n = model.nodeData<unsigned int>(nodeId,
                                                      (portType == QExtBPTypes::PortType_Out)
                                                      ? QExtBPTypes::NodeRole_OutPortCount
                                                      : QExtBPTypes::NodeRole_InPortCount);

        for (QExtBPTypes::PortIndex portIndex = 0; portIndex < n; ++portIndex)
        {
            const auto &connected = model.connections(nodeId, portType, portIndex);

            QPointF p = geometry.portTextPosition(nodeId, portType, portIndex);

            if (connected.empty())
            {
                painter->setPen(nodeStyle.FontColorFaded);
            }
            else
            {
                painter->setPen(nodeStyle.FontColor);
            }

            QString s;

            if (model.portData<bool>(nodeId, portType, portIndex, QExtBPTypes::PortRole_CaptionVisible))
            {
                s = model.portData<QString>(nodeId, portType, portIndex, QExtBPTypes::PortRole_Caption);
            }
            else
            {
                auto portData = model.portData(nodeId, portType, portIndex, QExtBPTypes::PortRole_DataType);

                s = portData.value<QExtBPNodeDataType>().name;
            }

            painter->drawText(p, s);
        }
    }
}

void QExtBPDefaultNodePainter::drawResizeRect(QPainter *painter, QExtBPNodeGraphicsObject &ngo) const
{
    QExtBPAbstractGraphModel &model = ngo.graphModel();
    const QExtBPTypes::NodeId nodeId = ngo.nodeId();
    QExtBPAbstractNodeGeometry &geometry = ngo.nodeScene()->nodeGeometry();

    if (model.nodeFlags(nodeId) & QExtBPTypes::NodeFlag_Resizable)
    {
        painter->setBrush(Qt::gray);

        painter->drawEllipse(geometry.resizeHandleRect(nodeId));
    }
}
