#include <qextBPDefaultVerticalNodeGeometry.h>
#include <qextBPAbstractGraphModel.h>
#include <qextBPNodeData.h>

#include <QPoint>
#include <QRect>
#include <QWidget>

QExtBPDefaultVerticalNodeGeometry::QExtBPDefaultVerticalNodeGeometry(QExtBPAbstractGraphModel &graphModel)
    : QExtBPAbstractNodeGeometry(graphModel)
    , _portSize(20)
    , _portSpasing(10)
    , _fontMetrics(QFont())
    , _boldFontMetrics(QFont())
{
    QFont f;
    f.setBold(true);
    _boldFontMetrics = QFontMetrics(f);

    _portSize = _fontMetrics.height();
}

QSize QExtBPDefaultVerticalNodeGeometry::size(const QExtBPTypes::NodeId nodeId) const
{
    return m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);
}

void QExtBPDefaultVerticalNodeGeometry::recomputeSize(const QExtBPTypes::NodeId nodeId) const
{
    unsigned int height = _portSpasing; // maxHorizontalPortsExtent(nodeId);

    if (auto w = m_graphModel.nodeData<QWidget *>(nodeId, QExtBPTypes::NodeRole_Widget)) {
        height = std::max(height, static_cast<unsigned int>(w->height()));
    }

    QRectF const capRect = captionRect(nodeId);

    height += capRect.height();

    height += _portSpasing;
    height += _portSpasing;

    QExtBPTypes::PortCount nInPorts = m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_InPortCount);
    QExtBPTypes::PortCount nOutPorts = m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_OutPortCount);

    // Adding double step (top and bottom) to reserve space for port captions.

    height += portCaptionsHeight(nodeId, QExtBPTypes::PortType_In);
    height += portCaptionsHeight(nodeId, QExtBPTypes::PortType_Out);

    unsigned int inPortWidth = maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_In);
    unsigned int outPortWidth = maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_Out);

    unsigned int totalInPortsWidth = nInPorts > 0
            ? inPortWidth * nInPorts + _portSpasing * (nInPorts - 1)
            : 0;

    unsigned int totalOutPortsWidth = nOutPorts > 0 ? outPortWidth * nOutPorts
                                                      + _portSpasing * (nOutPorts - 1)
                                                    : 0;

    unsigned int width = std::max(totalInPortsWidth, totalOutPortsWidth);

    if (auto w = m_graphModel.nodeData<QWidget *>(nodeId, QExtBPTypes::NodeRole_Widget)) {
        width = std::max(width, static_cast<unsigned int>(w->width()));
    }

    width = std::max(width, static_cast<unsigned int>(capRect.width()));

    width += _portSpasing;
    width += _portSpasing;

    QSize size(width, height);

    m_graphModel.setNodeData(nodeId, QExtBPTypes::NodeRole_Size, size);
}

QPointF QExtBPDefaultVerticalNodeGeometry::portPosition(const QExtBPTypes::NodeId nodeId,
                                                        const QExtBPTypes::PortTypeEnum portType,
                                                        const QExtBPTypes::PortIndex portIndex) const
{
    QPointF result;

    QSize size = m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);

    switch (portType) {
    case QExtBPTypes::PortType_In: {
        unsigned int inPortWidth = maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_In) + _portSpasing;

        QExtBPTypes::PortCount nInPorts = m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_InPortCount);

        double x = (size.width() - (nInPorts - 1) * inPortWidth) / 2.0 + portIndex * inPortWidth;

        double y = 0.0;

        result = QPointF(x, y);

        break;
    }

    case QExtBPTypes::PortType_Out: {
        unsigned int outPortWidth = maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_Out) + _portSpasing;
        QExtBPTypes::PortCount nOutPorts = m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_OutPortCount);

        double x = (size.width() - (nOutPorts - 1) * outPortWidth) / 2.0 + portIndex * outPortWidth;

        double y = size.height();

        result = QPointF(x, y);

        break;
    }

    default:
        break;
    }

    return result;
}

QPointF QExtBPDefaultVerticalNodeGeometry::portTextPosition(const QExtBPTypes::NodeId nodeId,
                                                            const QExtBPTypes::PortTypeEnum portType,
                                                            const QExtBPTypes::PortIndex portIndex) const
{
    QPointF p = portPosition(nodeId, portType, portIndex);

    QRectF rect = portTextRect(nodeId, portType, portIndex);

    p.setX(p.x() - rect.width() / 2.0);

    QSize size = m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);

    switch (portType) {
    case QExtBPTypes::PortType_In:
        p.setY(5.0 + rect.height());
        break;

    case QExtBPTypes::PortType_Out:
        p.setY(size.height() - 5.0);
        break;

    default:
        break;
    }

    return p;
}

QRectF QExtBPDefaultVerticalNodeGeometry::captionRect(const QExtBPTypes::NodeId nodeId) const
{
    if (!m_graphModel.nodeData<bool>(nodeId, QExtBPTypes::NodeRole_CaptionVisible))
        return QRect();

    QString name = m_graphModel.nodeData<QString>(nodeId, QExtBPTypes::NodeRole_Caption);

    return _boldFontMetrics.boundingRect(name);
}

QPointF QExtBPDefaultVerticalNodeGeometry::captionPosition(const QExtBPTypes::NodeId nodeId) const
{
    QSize size = m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);

    unsigned int step = portCaptionsHeight(nodeId, QExtBPTypes::PortType_In);
    step += _portSpasing;

    auto rect = captionRect(nodeId);

    return QPointF(0.5 * (size.width() - rect.width()), step + rect.height());
}

QPointF QExtBPDefaultVerticalNodeGeometry::widgetPosition(const QExtBPTypes::NodeId nodeId) const
{
    QSize size = m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);

    unsigned int captionHeight = captionRect(nodeId).height();

    if (auto w = m_graphModel.nodeData<QWidget *>(nodeId, QExtBPTypes::NodeRole_Widget)) {
        // If the widget wants to use as much vertical space as possible,
        // place it immediately after the caption.
        if (w->sizePolicy().verticalPolicy() & QSizePolicy::ExpandFlag) {
            return QPointF(_portSpasing + maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_In), captionHeight);
        } else {
            return QPointF(_portSpasing + maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_In),
                           (captionHeight + size.height() - w->height()) / 2.0);
        }
    }
    return QPointF();
}

QRect QExtBPDefaultVerticalNodeGeometry::resizeHandleRect(const QExtBPTypes::NodeId nodeId) const
{
    QSize size = m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);

    unsigned int rectSize = 7;

    return QRect(size.width() - rectSize, size.height() - rectSize, rectSize, rectSize);
}

QRectF QExtBPDefaultVerticalNodeGeometry::portTextRect(const QExtBPTypes::NodeId nodeId,
                                                       const QExtBPTypes::PortTypeEnum portType,
                                                       const QExtBPTypes::PortIndex portIndex) const
{
    QString s;
    if (m_graphModel.portData<bool>(nodeId, portType, portIndex, QExtBPTypes::PortRole_CaptionVisible)) {
        s = m_graphModel.portData<QString>(nodeId, portType, portIndex, QExtBPTypes::PortRole_Caption);
    } else {
        auto portData = m_graphModel.portData(nodeId, portType, portIndex, QExtBPTypes::PortRole_DataType);

        s = portData.value<QExtBPNodeDataType>().name;
    }

    return _fontMetrics.boundingRect(s);
}

unsigned int QExtBPDefaultVerticalNodeGeometry::maxHorizontalPortsExtent(const QExtBPTypes::NodeId nodeId) const
{
    QExtBPTypes::PortCount nInPorts = m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_InPortCount);

    QExtBPTypes::PortCount nOutPorts = m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_OutPortCount);

    unsigned int maxNumOfEntries = std::max(nInPorts, nOutPorts);
    unsigned int step = _portSize + _portSpasing;

    return step * maxNumOfEntries;
}

unsigned int QExtBPDefaultVerticalNodeGeometry::maxPortsTextAdvance(const QExtBPTypes::NodeId nodeId,
                                                                    const QExtBPTypes::PortTypeEnum portType) const
{
    unsigned int width = 0;

    size_t const n = m_graphModel
            .nodeData(nodeId,
                      (portType == QExtBPTypes::PortType_Out) ? QExtBPTypes::NodeRole_OutPortCount
                                                              : QExtBPTypes::NodeRole_InPortCount)
            .toUInt();

    for (QExtBPTypes::PortIndex portIndex = 0ul; portIndex < n; ++portIndex) {
        QString name;

        if (m_graphModel.portData<bool>(nodeId, portType, portIndex, QExtBPTypes::PortRole_CaptionVisible)) {
            name = m_graphModel.portData<QString>(nodeId, portType, portIndex, QExtBPTypes::PortRole_Caption);
        } else {
            QExtBPNodeDataType portData = m_graphModel.portData<QExtBPNodeDataType>(nodeId,
                                                                                   portType,
                                                                                   portIndex,
                                                                                   QExtBPTypes::PortRole_DataType);

            name = portData.name;
        }

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
        width = std::max(unsigned(_fontMetrics.horizontalAdvance(name)), width);
#else
        width = std::max(unsigned(_fontMetrics.width(name)), width);
#endif
    }

    return width;
}

unsigned int QExtBPDefaultVerticalNodeGeometry::portCaptionsHeight(const QExtBPTypes::NodeId nodeId,
                                                                   const QExtBPTypes::PortTypeEnum portType) const
{
    unsigned int h = 0;

    switch (portType) {
    case QExtBPTypes::PortType_In: {
        QExtBPTypes::PortCount nInPorts = m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_InPortCount);
        for (QExtBPTypes::PortIndex i = 0; i < nInPorts; ++i) {
            if (m_graphModel.portData<bool>(nodeId, QExtBPTypes::PortType_In, i, QExtBPTypes::PortRole_CaptionVisible)) {
                h += _portSpasing;
                break;
            }
        }
        break;
    }

    case QExtBPTypes::PortType_Out: {
        QExtBPTypes::PortCount nOutPorts = m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_OutPortCount);
        for (QExtBPTypes::PortIndex i = 0; i < nOutPorts; ++i) {
            if (m_graphModel.portData<bool>(nodeId, QExtBPTypes::PortType_Out, i, QExtBPTypes::PortRole_CaptionVisible)) {
                h += _portSpasing;
                break;
            }
        }
        break;
    }

    default:
        break;
    }

    return h;
}
