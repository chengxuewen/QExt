#include <qextBPDefaultHorizontalNodeGeometry.h>
#include <private/qextBPAbstractNodeGeometry_p.h>
#include <qextBPAbstractGraphModel.h>
#include <qextBPNodeData.h>

#include <QRect>
#include <QPoint>
#include <QWidget>

class QExtBPDefaultHorizontalNodeGeometryPrivate : public QExtBPAbstractNodeGeometryPrivate
{
public:
    QExtBPDefaultHorizontalNodeGeometryPrivate(QExtBPDefaultHorizontalNodeGeometry *q,
                                               QExtBPAbstractGraphModel &graphModel);
    ~QExtBPDefaultHorizontalNodeGeometryPrivate() QEXT_OVERRIDE;

    unsigned int m_portSpasing;
    /**
     * Some variables are mutable because we need to change drawing metrics corresponding to fontMetrics but this
     * doesn't change constness of the Node.
     */
    mutable unsigned int m_portSize;
    mutable QFontMetrics m_fontMetrics;
    mutable QFontMetrics m_boldFontMetrics;

private:
    QEXT_DECL_PUBLIC(QExtBPDefaultHorizontalNodeGeometry)
    QEXT_DISABLE_COPY_MOVE(QExtBPDefaultHorizontalNodeGeometryPrivate)
};

QExtBPDefaultHorizontalNodeGeometryPrivate::QExtBPDefaultHorizontalNodeGeometryPrivate(QExtBPDefaultHorizontalNodeGeometry *q,
                                                                                       QExtBPAbstractGraphModel &graphModel)
    : QExtBPAbstractNodeGeometryPrivate(q, graphModel)
    , m_portSize(20)
    , m_portSpasing(10)
    , m_fontMetrics(QFont())
    , m_boldFontMetrics(QFont())
{
}

QExtBPDefaultHorizontalNodeGeometryPrivate::~QExtBPDefaultHorizontalNodeGeometryPrivate()
{
}

QExtBPDefaultHorizontalNodeGeometry::QExtBPDefaultHorizontalNodeGeometry(QExtBPAbstractGraphModel &graphModel)
    : QExtBPAbstractNodeGeometry(new QExtBPDefaultHorizontalNodeGeometryPrivate(this, graphModel))
{
    Q_D(QExtBPDefaultHorizontalNodeGeometry);
    QFont f;
    f.setBold(true);
    d->m_boldFontMetrics = QFontMetrics(f);
    d->m_portSize = d->m_fontMetrics.height();
}

QExtBPDefaultHorizontalNodeGeometry::~QExtBPDefaultHorizontalNodeGeometry()
{

}

QSize QExtBPDefaultHorizontalNodeGeometry::size(const QExtBPTypes::NodeId nodeId) const
{
    Q_D(const QExtBPDefaultHorizontalNodeGeometry);
    return d->m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);
}

void QExtBPDefaultHorizontalNodeGeometry::recomputeSize(const QExtBPTypes::NodeId nodeId) const
{
    Q_D(const QExtBPDefaultHorizontalNodeGeometry);
    unsigned int height = maxVerticalPortsExtent(nodeId);

    if (auto w = d->m_graphModel.nodeData<QWidget *>(nodeId, QExtBPTypes::NodeRole_Widget))
    {
        height = std::max(height, static_cast<unsigned int>(w->height()));
    }

    QRectF const capRect = captionRect(nodeId);

    height += capRect.height();

    height += d->m_portSpasing; // space above caption
    height += d->m_portSpasing; // space below caption

    unsigned int inPortWidth = maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_In);
    unsigned int outPortWidth = maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_Out);

    unsigned int width = inPortWidth + outPortWidth + 4 * d->m_portSpasing;

    if (auto w = d->m_graphModel.nodeData<QWidget *>(nodeId, QExtBPTypes::NodeRole_Widget))
    {
        width += w->width();
    }

    width = std::max(width, static_cast<unsigned int>(capRect.width()) + 2 * d->m_portSpasing);

    QSize size(width, height);

    d->m_graphModel.setNodeData(nodeId, QExtBPTypes::NodeRole_Size, size);
}

QPointF QExtBPDefaultHorizontalNodeGeometry::portPosition(const QExtBPTypes::NodeId nodeId,
                                                          const QExtBPTypes::PortTypeEnum portType,
                                                          const QExtBPTypes::PortIndex portIndex) const
{
    Q_D(const QExtBPDefaultHorizontalNodeGeometry);
    unsigned int const step = d->m_portSize + d->m_portSpasing;

    QPointF result;

    double totalHeight = 0.0;

    totalHeight += this->captionRect(nodeId).height();
    totalHeight += d->m_portSpasing;

    totalHeight += step * portIndex;
    totalHeight += step / 2.0;

    QSize size = d->m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);

    switch (portType)
    {
    case QExtBPTypes::PortType_In:
    {
        double x = 0.0;
        result = QPointF(x, totalHeight);
        break;
    }
    case QExtBPTypes::PortType_Out:
    {
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
    Q_D(const QExtBPDefaultHorizontalNodeGeometry);
    QPointF p = this->portPosition(nodeId, portType, portIndex);

    QRectF rect = this->portTextRect(nodeId, portType, portIndex);

    p.setY(p.y() + rect.height() / 4.0);

    QSize size = d->m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);

    switch (portType)
    {
    case QExtBPTypes::PortType_In:
        p.setX(d->m_portSpasing);
        break;
    case QExtBPTypes::PortType_Out:
        p.setX(size.width() - d->m_portSpasing - rect.width());
        break;
    default:
        break;
    }

    return p;
}

QRectF QExtBPDefaultHorizontalNodeGeometry::captionRect(const QExtBPTypes::NodeId nodeId) const
{
    Q_D(const QExtBPDefaultHorizontalNodeGeometry);
    if (!d->m_graphModel.nodeData<bool>(nodeId, QExtBPTypes::NodeRole_CaptionVisible))
    {
        return QRect();
    }

    QString name = d->m_graphModel.nodeData<QString>(nodeId, QExtBPTypes::NodeRole_Caption);
    return d->m_boldFontMetrics.boundingRect(name);
}

QPointF QExtBPDefaultHorizontalNodeGeometry::captionPosition(const QExtBPTypes::NodeId nodeId) const
{
    Q_D(const QExtBPDefaultHorizontalNodeGeometry);
    QSize size = d->m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);
    return QPointF(0.5 * (size.width() - captionRect(nodeId).width()),
                   0.5 * d-> m_portSpasing + captionRect(nodeId).height());
}

QPointF QExtBPDefaultHorizontalNodeGeometry::widgetPosition(const QExtBPTypes::NodeId nodeId) const
{
    Q_D(const QExtBPDefaultHorizontalNodeGeometry);
    QSize size = d->m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);

    unsigned int captionHeight = this->captionRect(nodeId).height();

    if (auto w = d->m_graphModel.nodeData<QWidget *>(nodeId, QExtBPTypes::NodeRole_Widget))
    {
        // If the widget wants to use as much vertical space as possible,
        // place it immediately after the caption.
        if (w->sizePolicy().verticalPolicy() & QSizePolicy::ExpandFlag)
        {
            return QPointF(2.0 * d->m_portSpasing + maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_In),
                           captionHeight);
        }
        else
        {
            return QPointF(2.0 * d->m_portSpasing + maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_In),
                           (captionHeight + size.height() - w->height()) / 2.0);
        }
    }
    return QPointF();
}

QRect QExtBPDefaultHorizontalNodeGeometry::resizeHandleRect(const QExtBPTypes::NodeId nodeId) const
{
    Q_D(const QExtBPDefaultHorizontalNodeGeometry);
    QSize size = d->m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);

    unsigned int rectSize = 7;
    return QRect(size.width() - d->m_portSpasing, size.height() - d->m_portSpasing, rectSize, rectSize);
}

QRectF QExtBPDefaultHorizontalNodeGeometry::portTextRect(const QExtBPTypes::NodeId nodeId,
                                                         const QExtBPTypes::PortTypeEnum portType,
                                                         const QExtBPTypes::PortIndex portIndex) const
{
    Q_D(const QExtBPDefaultHorizontalNodeGeometry);
    QString s;
    if (d->m_graphModel.portData<bool>(nodeId, portType, portIndex, QExtBPTypes::PortRole_CaptionVisible))
    {
        s = d->m_graphModel.portData<QString>(nodeId, portType, portIndex, QExtBPTypes::PortRole_Caption);
    }
    else
    {
        auto portData = d->m_graphModel.portData(nodeId, portType, portIndex, QExtBPTypes::PortRole_DataType);
        s = portData.value<QExtBPNodeDataType>().name;
    }

    return d->m_fontMetrics.boundingRect(s);
}

unsigned int QExtBPDefaultHorizontalNodeGeometry::maxVerticalPortsExtent(const QExtBPTypes::NodeId nodeId) const
{
    Q_D(const QExtBPDefaultHorizontalNodeGeometry);
    QExtBPTypes::PortCount nInPorts = d->m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_InPortCount);

    QExtBPTypes::PortCount nOutPorts = d->m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_OutPortCount);

    unsigned int maxNumOfEntries = std::max(nInPorts, nOutPorts);
    unsigned int step = d->m_portSize + d->m_portSpasing;
    return step * maxNumOfEntries;
}

unsigned int QExtBPDefaultHorizontalNodeGeometry::maxPortsTextAdvance(const QExtBPTypes::NodeId nodeId,
                                                                      const QExtBPTypes::PortTypeEnum portType) const
{
    Q_D(const QExtBPDefaultHorizontalNodeGeometry);
    unsigned int width = 0;
    size_t const n = d->m_graphModel.nodeData(nodeId,
                                              (portType == QExtBPTypes::PortType_Out) ? QExtBPTypes::NodeRole_OutPortCount
                                                                                      : QExtBPTypes::NodeRole_InPortCount)
                         .toUInt();

    for (QExtBPTypes::PortIndex portIndex = 0ul; portIndex < n; ++portIndex)
    {
        QString name;

        if (d->m_graphModel.portData<bool>(nodeId, portType, portIndex, QExtBPTypes::PortRole_CaptionVisible))
        {
            name = d->m_graphModel.portData<QString>(nodeId, portType, portIndex, QExtBPTypes::PortRole_Caption);
        }
        else
        {
            QExtBPNodeDataType portData = d->m_graphModel.portData<QExtBPNodeDataType>(nodeId,
                                                                                       portType,
                                                                                       portIndex,
                                                                                       QExtBPTypes::PortRole_DataType);

            name = portData.name;
        }

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
        width = std::max(unsigned(d->m_fontMetrics.horizontalAdvance(name)), width);
#else
        width = std::max(unsigned(d->m_fontMetrics.width(name)), width);
#endif
    }

    return width;
}
