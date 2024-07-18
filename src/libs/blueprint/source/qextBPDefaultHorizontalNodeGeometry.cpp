#include <qextBPDefaultHorizontalNodeGeometry.h>
#include <qextBPAbstractGraphModel.h>
#include <qextBPNodeData.h>

#include <QRect>
#include <QPoint>
#include <QWidget>

QExtBPDefaultHorizontalNodeGeometry::QExtBPDefaultHorizontalNodeGeometry(QExtBPAbstractGraphModel &graphModel)
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

QSize QExtBPDefaultHorizontalNodeGeometry::size(const QExtBPTypes::NodeId nodeId) const
{
    return m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);
}

void QExtBPDefaultHorizontalNodeGeometry::recomputeSize(const QExtBPTypes::NodeId nodeId) const
{
    unsigned int height = maxVerticalPortsExtent(nodeId);

    if (auto w = m_graphModel.nodeData<QWidget *>(nodeId, QExtBPTypes::NodeRole_Widget)) {
        height = std::max(height, static_cast<unsigned int>(w->height()));
    }

    QRectF const capRect = captionRect(nodeId);

    height += capRect.height();

    height += _portSpasing; // space above caption
    height += _portSpasing; // space below caption

    unsigned int inPortWidth = maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_In);
    unsigned int outPortWidth = maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_Out);

    unsigned int width = inPortWidth + outPortWidth + 4 * _portSpasing;

    if (auto w = m_graphModel.nodeData<QWidget *>(nodeId, QExtBPTypes::NodeRole_Widget)) {
        width += w->width();
    }

    width = std::max(width, static_cast<unsigned int>(capRect.width()) + 2 * _portSpasing);

    QSize size(width, height);

    m_graphModel.setNodeData(nodeId, QExtBPTypes::NodeRole_Size, size);
}

QPointF QExtBPDefaultHorizontalNodeGeometry::portPosition(const QExtBPTypes::NodeId nodeId,
                                                          const QExtBPTypes::PortTypeEnum portType,
                                                          const QExtBPTypes::PortIndex portIndex) const
{
    unsigned int const step = _portSize + _portSpasing;

    QPointF result;

    double totalHeight = 0.0;

    totalHeight += captionRect(nodeId).height();
    totalHeight += _portSpasing;

    totalHeight += step * portIndex;
    totalHeight += step / 2.0;

    QSize size = m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);

    switch (portType) {
    case QExtBPTypes::PortType_In: {
        double x = 0.0;

        result = QPointF(x, totalHeight);
        break;
    }

    case QExtBPTypes::PortType_Out: {
        double x = size.width();

        result = QPointF(x, totalHeight);
        break;
    }

    default:
        break;
    }

    return result;
}

QPointF QExtBPDefaultHorizontalNodeGeometry::portTextPosition(const QExtBPTypes::NodeId nodeId,
                                                              const QExtBPTypes::PortTypeEnum portType,
                                                              const QExtBPTypes::PortIndex portIndex) const
{
    QPointF p = portPosition(nodeId, portType, portIndex);

    QRectF rect = portTextRect(nodeId, portType, portIndex);

    p.setY(p.y() + rect.height() / 4.0);

    QSize size = m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);

    switch (portType) {
    case QExtBPTypes::PortType_In:
        p.setX(_portSpasing);
        break;

    case QExtBPTypes::PortType_Out:
        p.setX(size.width() - _portSpasing - rect.width());
        break;

    default:
        break;
    }

    return p;
}

QRectF QExtBPDefaultHorizontalNodeGeometry::captionRect(const QExtBPTypes::NodeId nodeId) const
{
    if (!m_graphModel.nodeData<bool>(nodeId, QExtBPTypes::NodeRole_CaptionVisible))
        return QRect();

    QString name = m_graphModel.nodeData<QString>(nodeId, QExtBPTypes::NodeRole_Caption);

    return _boldFontMetrics.boundingRect(name);
}

QPointF QExtBPDefaultHorizontalNodeGeometry::captionPosition(const QExtBPTypes::NodeId nodeId) const
{
    QSize size = m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);
    return QPointF(0.5 * (size.width() - captionRect(nodeId).width()),
                   0.5 * _portSpasing + captionRect(nodeId).height());
}

QPointF QExtBPDefaultHorizontalNodeGeometry::widgetPosition(const QExtBPTypes::NodeId nodeId) const
{
    QSize size = m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);

    unsigned int captionHeight = captionRect(nodeId).height();

    if (auto w = m_graphModel.nodeData<QWidget *>(nodeId, QExtBPTypes::NodeRole_Widget)) {
        // If the widget wants to use as much vertical space as possible,
        // place it immediately after the caption.
        if (w->sizePolicy().verticalPolicy() & QSizePolicy::ExpandFlag) {
            return QPointF(2.0 * _portSpasing + maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_In),
                           captionHeight);
        } else {
            return QPointF(2.0 * _portSpasing + maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_In),
                           (captionHeight + size.height() - w->height()) / 2.0);
        }
    }
    return QPointF();
}

QRect QExtBPDefaultHorizontalNodeGeometry::resizeHandleRect(const QExtBPTypes::NodeId nodeId) const
{
    QSize size = m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);

    unsigned int rectSize = 7;

    return QRect(size.width() - _portSpasing, size.height() - _portSpasing, rectSize, rectSize);
}

QRectF QExtBPDefaultHorizontalNodeGeometry::portTextRect(const QExtBPTypes::NodeId nodeId,
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

unsigned int QExtBPDefaultHorizontalNodeGeometry::maxVerticalPortsExtent(const QExtBPTypes::NodeId nodeId) const
{
    QExtBPTypes::PortCount nInPorts = m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_InPortCount);

    QExtBPTypes::PortCount nOutPorts = m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_OutPortCount);

    unsigned int maxNumOfEntries = std::max(nInPorts, nOutPorts);
    unsigned int step = _portSize + _portSpasing;

    return step * maxNumOfEntries;
}

unsigned int QExtBPDefaultHorizontalNodeGeometry::maxPortsTextAdvance(const QExtBPTypes::NodeId nodeId,
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
