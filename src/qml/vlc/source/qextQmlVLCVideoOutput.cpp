#include <qextVLCYUVVideoFrame.h>
#include <qextQmlVLCSource.h>
#include <qextQmlVLCVideoOutput.h>
#include <qextQmlVLCVideoNode.h>

QEXTQmlVLCVideoOutput::QEXTQmlVLCVideoOutput()
    : m_fillMode(QEXTVLC::Fill_PreserveAspectFit)
    , m_source(0)
    , m_frameUpdated(false)
{
    setFlag(QQuickItem::ItemHasContents, true);
}

QEXTQmlVLCVideoOutput::~QEXTQmlVLCVideoOutput()
{
    setSource(0);
}

QEXTQmlVLCSource *QEXTQmlVLCVideoOutput::source() const
{
    return m_source;
}

void QEXTQmlVLCVideoOutput::setSource(QEXTQmlVLCSource *source)
{
    if (source == m_source)
    {
        return;
    }

    if (m_source)
    {
        m_source->deregisterVideoOutput(this);
    }

    m_source = source;

    if (m_source)
    {
        m_source->registerVideoOutput(this);
    }

    emit sourceChanged();
}

int QEXTQmlVLCVideoOutput::fillMode() const
{
    return m_fillMode;
}

void QEXTQmlVLCVideoOutput::setFillMode(int mode)
{
    if (m_fillMode == mode)
    {
        return;
    }

    m_fillMode = QEXTVLC::FillMode(mode);

    update();

    emit fillModeChanged();
}

int QEXTQmlVLCVideoOutput::aspectRatio() const
{
    return m_aspectRatio;
}

void QEXTQmlVLCVideoOutput::setAspectRatio(int aspectRatio)
{
    if (m_aspectRatio == aspectRatio)
    {
        return;
    }

    m_aspectRatio = QEXTVLC::RatioType(aspectRatio);

    update();

    emit aspectRatioChanged();
}

int QEXTQmlVLCVideoOutput::cropRatio() const
{
    return m_cropRatio;
}

void QEXTQmlVLCVideoOutput::setCropRatio(int cropRatio)
{
    if (m_cropRatio == cropRatio)
    {
        return;
    }

    m_cropRatio = QEXTVLC::RatioType(cropRatio);

    this->update();
    emit this->cropRatioChanged();
}

QSGNode *QEXTQmlVLCVideoOutput::updatePaintNode(QSGNode *oldNode,
        UpdatePaintNodeData *data)
{
    Q_UNUSED(data)

    QEXTQmlVLCVideoNode *node = static_cast<QEXTQmlVLCVideoNode *>(oldNode);
    if (!m_frame)
    {
        delete node;
        return 0;
    }

    if (!node)
    {
        node = new QEXTQmlVLCVideoNode;
    }

    QRectF outRect(0, 0, width(), height());
    QRectF srcRect(0, 0, 1., 1.);

    if (fillMode() != QEXTVLC::Fill_Stretch)
    {
        const uint16_t fw = m_frame->width;
        const uint16_t fh = m_frame->height;

        qreal frameAspectTmp = qreal(fw) / fh;
        QSizeF aspectRatioSize = QEXTVLC::ratioSize(m_aspectRatio);
        if (aspectRatioSize.width() != 0 && aspectRatioSize.height() != 0)
        {
            frameAspectTmp = aspectRatioSize.width() / aspectRatioSize.height();
        }
        QSizeF cropRatioSize = QEXTVLC::ratioSize(m_cropRatio);
        if (cropRatioSize.width() != 0 && cropRatioSize.height() != 0)
        {
            const qreal cropAspect = cropRatioSize.width() / cropRatioSize.height();

            if (frameAspectTmp > cropAspect)
            {
                srcRect.setX((1. - cropAspect / frameAspectTmp) / 2);
                srcRect.setWidth(1. - srcRect.x() - srcRect.x());
            }
            else if (frameAspectTmp < cropAspect)
            {
                srcRect.setY((1. - frameAspectTmp / cropAspect) / 2);
                srcRect.setHeight(1. - srcRect.y() - srcRect.y());
            }

            frameAspectTmp = cropAspect;
        }
        const qreal itemAspect = width() / height();
        const qreal frameAspect = frameAspectTmp;

        if (fillMode() == QEXTVLC::Fill_PreserveAspectFit)
        {
            qreal outWidth = width();
            qreal outHeight = height();
            if (frameAspect > itemAspect)
            {
                outHeight = outWidth / frameAspect;
            }
            else if (frameAspect < itemAspect)
            {
                outWidth = outHeight * frameAspect;
            }

            outRect = QRectF((width() - outWidth) / 2, (height() - outHeight) / 2,
                             outWidth, outHeight);
        }
        else if (fillMode() == QEXTVLC::Fill_PreserveAspectCrop)
        {
            if (frameAspect > itemAspect)
            {
                srcRect.setX((1. - itemAspect / frameAspect) / 2);
                srcRect.setWidth(1. - srcRect.x() - srcRect.x());
            }
            else if (frameAspect < itemAspect)
            {
                srcRect.setY((1. - frameAspect / itemAspect) / 2);
                srcRect.setHeight(1. - srcRect.y() - srcRect.y());
            }
        }
    }

    if (m_frameUpdated)
    {
        node->setFrame(m_frame);
        m_frameUpdated = false;
    }
    node->setRect(outRect, srcRect);

    return node;
}

void QEXTQmlVLCVideoOutput::presentFrame(const QSharedPointer<const QEXTVLCYUVVideoFrame> &frame)
{
    m_frame = frame;
    m_frameUpdated = true;
    this->update();
}
