#include <qextBPDefaultVerticalNodeGeometry.h>
#include <private/qextBPAbstractNodeGeometry_p.h>
#include <qextBPAbstractGraphModel.h>
#include <qextBPNodeData.h>

#include <QPoint>
#include <QRect>
#include <QWidget>

class QExtBPDefaultVerticalNodeGeometryPrivate : public QExtBPAbstractNodeGeometryPrivate
{
public:
    QExtBPDefaultVerticalNodeGeometryPrivate(QExtBPDefaultVerticalNodeGeometry *q, QExtBPAbstractGraphModel &graphModel);
    ~QExtBPDefaultVerticalNodeGeometryPrivate() QEXT_OVERRIDE;

    unsigned int m_portSpasing;
    /**
     * Some variables are mutable because we need to change drawing metrics corresponding to fontMetrics but this
     * doesn't change constness of the Node.
     */
    mutable unsigned int m_portSize;
    mutable QFontMetrics m_fontMetrics;
    mutable QFontMetrics m_boldFontMetrics;

private:
    QEXT_DECL_PUBLIC(QExtBPDefaultVerticalNodeGeometry)
    QEXT_DISABLE_COPY_MOVE(QExtBPDefaultVerticalNodeGeometryPrivate)
};

QExtBPDefaultVerticalNodeGeometryPrivate::QExtBPDefaultVerticalNodeGeometryPrivate(QExtBPDefaultVerticalNodeGeometry *q,
                                                                                   QExtBPAbstractGraphModel &graphModel)
    : QExtBPAbstractNodeGeometryPrivate(q, graphModel)
    , m_portSpasing(10)
    , m_portSize(20)
    , m_fontMetrics(QFont())
    , m_boldFontMetrics(QFont())
{
}

QExtBPDefaultVerticalNodeGeometryPrivate::~QExtBPDefaultVerticalNodeGeometryPrivate()
{
}

QExtBPDefaultVerticalNodeGeometry::QExtBPDefaultVerticalNodeGeometry(QExtBPAbstractGraphModel &graphModel)
    : QExtBPAbstractNodeGeometry(new QExtBPDefaultVerticalNodeGeometryPrivate(this, graphModel))
{
    Q_D(QExtBPDefaultVerticalNodeGeometry);
    QFont f;
    f.setBold(true);
    d->m_boldFontMetrics = QFontMetrics(f);
    d->m_portSize = d->m_fontMetrics.height();
}

QSize QExtBPDefaultVerticalNodeGeometry::size(const QExtBPTypes::NodeId nodeId) const
{
    Q_D(const QExtBPDefaultVerticalNodeGeometry);
    return d->m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);
}

void QExtBPDefaultVerticalNodeGeometry::recomputeSize(const QExtBPTypes::NodeId nodeId) const
{
    Q_D(const QExtBPDefaultVerticalNodeGeometry);
    unsigned int height = d->m_portSpasing; // maxHorizontalPortsExtent(nodeId);

    if (auto w = d->m_graphModel.nodeData<QWidget *>(nodeId, QExtBPTypes::NodeRole_Widget))
    {
        height = std::max(height, static_cast<unsigned int>(w->height()));
    }

    QRectF const capRect = captionRect(nodeId);

    height += capRect.height();

    height += d->m_portSpasing;
    height += d->m_portSpasing;

    QExtBPTypes::PortCount nInPorts = d->m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_InPortCount);
    QExtBPTypes::PortCount nOutPorts = d->m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_OutPortCount);

    // Adding double step (top and bottom) to reserve space for port captions.

    height += portCaptionsHeight(nodeId, QExtBPTypes::PortType_In);
    height += portCaptionsHeight(nodeId, QExtBPTypes::PortType_Out);

    unsigned int inPortWidth = maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_In);
    unsigned int outPortWidth = maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_Out);

    unsigned int totalInPortsWidth = nInPorts > 0
                                         ? inPortWidth * nInPorts + d->m_portSpasing * (nInPorts - 1)
                                         : 0;

    unsigned int totalOutPortsWidth = nOutPorts > 0 ? outPortWidth * nOutPorts
                                                          + d->m_portSpasing * (nOutPorts - 1)
                                                    : 0;

    unsigned int width = std::max(totalInPortsWidth, totalOutPortsWidth);

    if (auto w = d->m_graphModel.nodeData<QWidget *>(nodeId, QExtBPTypes::NodeRole_Widget))
    {
        width = std::max(width, static_cast<unsigned int>(w->width()));
    }

    width = std::max(width, static_cast<unsigned int>(capRect.width()));

    width += d->m_portSpasing;
    width += d->m_portSpasing;

    QSize size(width, height);

    d->m_graphModel.setNodeData(nodeId, QExtBPTypes::NodeRole_Size, size);
}

QPointF QExtBPDefaultVerticalNodeGeometry::portPosition(const QExtBPTypes::NodeId nodeId,
                                                        const QExtBPTypes::PortTypeEnum portType,
                                                        const QExtBPTypes::PortIndex portIndex) const
{
    Q_D(const QExtBPDefaultVerticalNodeGeometry);
    QPointF result;

    QSize size = d->m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);

    switch (portType)
    {
    case QExtBPTypes::PortType_In:
    {
        unsigned int inPortWidth = maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_In) + d->m_portSpasing;

        QExtBPTypes::PortCount nInPorts = d->m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_InPortCount);

        double x = (size.width() - (nInPorts - 1) * inPortWidth) / 2.0 + portIndex * inPortWidth;

        double y = 0.0;

        result = QPointF(x, y);

        break;
    }
    case QExtBPTypes::PortType_Out:
    {
        unsigned int outPortWidth = maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_Out) + d->m_portSpasing;
        QExtBPTypes::PortCount nOutPorts = d->m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_OutPortCount);

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
    Q_D(const QExtBPDefaultVerticalNodeGeometry);
    QPointF p = this->portPosition(nodeId, portType, portIndex);
    QRectF rect = this->portTextRect(nodeId, portType, portIndex);

    p.setX(p.x() - rect.width() / 2.0);

    QSize size = d->m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);

    switch (portType)
    {
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
    Q_D(const QExtBPDefaultVerticalNodeGeometry);
    if (!d->m_graphModel.nodeData<bool>(nodeId, QExtBPTypes::NodeRole_CaptionVisible))
    {
        return QRect();
    }

    QString name = d->m_graphModel.nodeData<QString>(nodeId, QExtBPTypes::NodeRole_Caption);
    return d->m_boldFontMetrics.boundingRect(name);
}

QPointF QExtBPDefaultVerticalNodeGeometry::captionPosition(const QExtBPTypes::NodeId nodeId) const
{
    Q_D(const QExtBPDefaultVerticalNodeGeometry);
    QSize size = d->m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);

    unsigned int step = portCaptionsHeight(nodeId, QExtBPTypes::PortType_In);
    step += d->m_portSpasing;

    auto rect = this->captionRect(nodeId);
    return QPointF(0.5 * (size.width() - rect.width()), step + rect.height());
}

QPointF QExtBPDefaultVerticalNodeGeometry::widgetPosition(const QExtBPTypes::NodeId nodeId) const
{
    Q_D(const QExtBPDefaultVerticalNodeGeometry);
    QSize size = d->m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);

    unsigned int captionHeight = this->captionRect(nodeId).height();

    if (auto w = d->m_graphModel.nodeData<QWidget *>(nodeId, QExtBPTypes::NodeRole_Widget))
    {
        // If the widget wants to use as much vertical space as possible,
        // place it immediately after the caption.
        if (w->sizePolicy().verticalPolicy() & QSizePolicy::ExpandFlag)
        {
            return QPointF(d->m_portSpasing + maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_In), captionHeight);
        }
        else
        {
            return QPointF(d->m_portSpasing + maxPortsTextAdvance(nodeId, QExtBPTypes::PortType_In),
                           (captionHeight + size.height() - w->height()) / 2.0);
        }
    }
    return QPointF();
}

QRect QExtBPDefaultVerticalNodeGeometry::resizeHandleRect(const QExtBPTypes::NodeId nodeId) const
{
    Q_D(const QExtBPDefaultVerticalNodeGeometry);
    QSize size = d->m_graphModel.nodeData<QSize>(nodeId, QExtBPTypes::NodeRole_Size);

    unsigned int rectSize = 7;
    return QRect(size.width() - rectSize, size.height() - rectSize, rectSize, rectSize);
}

QRectF QExtBPDefaultVerticalNodeGeometry::portTextRect(const QExtBPTypes::NodeId nodeId,
                                                       const QExtBPTypes::PortTypeEnum portType,
                                                       const QExtBPTypes::PortIndex portIndex) const
{
    Q_D(const QExtBPDefaultVerticalNodeGeometry);
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

unsigned int QExtBPDefaultVerticalNodeGeometry::maxHorizontalPortsExtent(const QExtBPTypes::NodeId nodeId) const
{
    Q_D(const QExtBPDefaultVerticalNodeGeometry);
    QExtBPTypes::PortCount nInPorts = d->m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_InPortCount);

    QExtBPTypes::PortCount nOutPorts = d->m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_OutPortCount);

    unsigned int maxNumOfEntries = std::max(nInPorts, nOutPorts);
    unsigned int step = d->m_portSize + d->m_portSpasing;
    return step * maxNumOfEntries;
}

unsigned int QExtBPDefaultVerticalNodeGeometry::maxPortsTextAdvance(const QExtBPTypes::NodeId nodeId,
                                                                    const QExtBPTypes::PortTypeEnum portType) const
{
    Q_D(const QExtBPDefaultVerticalNodeGeometry);
    unsigned int width = 0;

    size_t const n = d->m_graphModel
                         .nodeData(nodeId,
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

unsigned int QExtBPDefaultVerticalNodeGeometry::portCaptionsHeight(const QExtBPTypes::NodeId nodeId,
                                                                   const QExtBPTypes::PortTypeEnum portType) const
{
    Q_D(const QExtBPDefaultVerticalNodeGeometry);
    unsigned int h = 0;

    switch (portType)
    {
    case QExtBPTypes::PortType_In:
    {
        QExtBPTypes::PortCount nInPorts = d->m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_InPortCount);
        for (QExtBPTypes::PortIndex i = 0; i < nInPorts; ++i)
        {
            if (d->m_graphModel.portData<bool>(nodeId, QExtBPTypes::PortType_In, i, QExtBPTypes::PortRole_CaptionVisible))
            {
                h += d->m_portSpasing;
                break;
            }
        }
        break;
    }
    case QExtBPTypes::PortType_Out:
    {
        QExtBPTypes::PortCount nOutPorts = d->m_graphModel.nodeData<QExtBPTypes::PortCount>(nodeId, QExtBPTypes::NodeRole_OutPortCount);
        for (QExtBPTypes::PortIndex i = 0; i < nOutPorts; ++i)
        {
            if (d->m_graphModel.portData<bool>(nodeId, QExtBPTypes::PortType_Out, i, QExtBPTypes::PortRole_CaptionVisible))
            {
                h += d->m_portSpasing;
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
