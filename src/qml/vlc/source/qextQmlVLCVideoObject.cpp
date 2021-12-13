#include <qextQmlVLCVideoObject.h>
#include <qextQmlVLCGLSLPainter.h>
#include <qextVLCMediaPlayer.h>

QEXTQmlVLCVideoObject::QEXTQmlVLCVideoObject(QQuickItem *parent)
    : QQuickPaintedItem(parent),
      m_player(0),
      m_geometry(0, 0, 640, 480),
      m_boundingRect(0, 0, 0, 0),
      m_frameSize(0, 0),
      m_graphicsPainter(0),
      m_paintedOnce(false),
      m_gotSize(false),
      m_aspectRatio(QEXTVLC::Ratio_Original),
      m_cropRatio(QEXTVLC::Ratio_Original)
{
    this->setRenderTarget(InvertedYFramebufferObject);
    this->setFlag(ItemHasContents, true);
}

QEXTQmlVLCVideoObject::~QEXTQmlVLCVideoObject()
{
    if (m_graphicsPainter)
    {
        delete m_graphicsPainter;
    }
}

QRectF QEXTQmlVLCVideoObject::boundingRect() const
{
    return m_boundingRect;
}

void QEXTQmlVLCVideoObject::updateBoundingRect()
{
    m_boundingRect = QRectF(0, 0, m_frameSize.width(), m_frameSize.height());

    updateAspectRatio();

    QSizeF scaledFrameSize = m_boundingRect.size();
    if (m_aspectRatio == QEXTVLC::Ratio_Ignore)
    {
        scaledFrameSize.scale(m_geometry.size(), Qt::IgnoreAspectRatio);
    }
    else
    {
        scaledFrameSize.scale(m_geometry.size(), Qt::KeepAspectRatio);
    }
    m_boundingRect.setSize( scaledFrameSize );

    updateCropRatio();

    m_boundingRect.moveCenter(m_geometry.center());
}

void QEXTQmlVLCVideoObject::updateAspectRatio()
{
    QSizeF ar = QEXTVLC::ratioSize( m_aspectRatio );

    if( ar.width() != 0 && ar.height() != 0)
    {
        qreal ratio = qMin( m_boundingRect.width() / ar.width(), m_boundingRect.height() / ar.height() );
        m_boundingRect.setWidth( (qreal) ratio * ar.width() );
        m_boundingRect.setHeight( (qreal) ratio * ar.height() );
    }
}

void QEXTQmlVLCVideoObject::updateCropRatio()
{
    QSizeF ar = QEXTVLC::ratioSize( m_cropRatio );

    if( ar.width() != 0 && ar.height() != 0)
    {
        QRectF cropRect = m_boundingRect;
        qreal ratio = qMin( cropRect.width() / ar.width(), cropRect.height() / ar.height() );
        cropRect.setWidth( (qreal) ratio * ar.width() );
        cropRect.setHeight( (qreal) ratio * ar.height() );

        QSizeF scaledFrameSize = cropRect.size();
        scaledFrameSize.scale(m_geometry.size(), Qt::KeepAspectRatio);


        m_boundingRect.setWidth( m_boundingRect.width() * ( scaledFrameSize.width() / cropRect.width() ) );
        m_boundingRect.setHeight( m_boundingRect.height() * ( scaledFrameSize.height() / cropRect.height() ) );
    }
}

QEXTVLC::RatioType QEXTQmlVLCVideoObject::cropRatio() const
{
    return m_cropRatio;
}

void QEXTQmlVLCVideoObject::setCropRatio(const QEXTVLC::RatioType &cropRatio)
{
    m_cropRatio = cropRatio;
    updateBoundingRect();
}

QEXTVLC::RatioType QEXTQmlVLCVideoObject::aspectRatio() const
{
    return m_aspectRatio;
}

void QEXTQmlVLCVideoObject::setAspectRatio(const QEXTVLC::RatioType &aspectRatio)
{
    m_aspectRatio = aspectRatio;
    updateBoundingRect();
}

void QEXTQmlVLCVideoObject::paint(QPainter *painter)
{
    lock();
    if( m_frame.inited )
    {
        if (!m_graphicsPainter)
        {
            m_graphicsPainter = new QEXTQmlVLCGLSLPainter;
        }

        Q_ASSERT(m_graphicsPainter);

        if (!m_gotSize || m_frameSize.isNull())
        {
            // TODO: do scaling ourselfs?
            m_gotSize = true;
            m_frameSize = QSize(m_frame.width, m_frame.height);
            updateBoundingRect();
        }

        if (!m_paintedOnce)
        {
            painter->fillRect(m_boundingRect, Qt::black);
            m_paintedOnce = true;
        }
        else
        {
            Q_ASSERT(m_graphicsPainter);
            m_graphicsPainter->setFrame(&m_frame);
            if (!m_graphicsPainter->inited())
            {
                m_graphicsPainter->init();
            }
            m_graphicsPainter->paint(painter, m_boundingRect, this);
        }
    }

    unlock();
}

void QEXTQmlVLCVideoObject::geometryChanged(const QRectF &newGeometry,
                                        const QRectF &oldGeometry)
{
    m_geometry = newGeometry;
    updateBoundingRect();

    QQuickPaintedItem::geometryChanged(newGeometry, oldGeometry);
}

void QEXTQmlVLCVideoObject::frameReady()
{
    update();
}

void QEXTQmlVLCVideoObject::reset()
{
    // Do not reset the spyFormats as they will not change.
    m_paintedOnce = false;
    m_gotSize = false;

    // The painter is reset because the backend may choose another format for
    // another file (better conversion for some codec etc.)
    if (m_graphicsPainter)
    {
        delete m_graphicsPainter;
        m_graphicsPainter = 0;
    }
}

void QEXTQmlVLCVideoObject::connectToMediaPlayer(QEXTVLCMediaPlayer *player)
{
    setCallbacks(player);
}

void QEXTQmlVLCVideoObject::disconnectFromMediaPlayer(QEXTVLCMediaPlayer *player)
{
    // Try to prevent callbacks called after this object is being deleted
    if (player)
    {
        player->stop();
    }

    unsetCallbacks(player);
}

void QEXTQmlVLCVideoObject::lock()
{
    m_mutex.lock();
}

bool QEXTQmlVLCVideoObject::tryLock()
{
    return m_mutex.tryLock();
}

void QEXTQmlVLCVideoObject::unlock()
{
    m_mutex.unlock();
}

void *QEXTQmlVLCVideoObject::lockCallback(void **planes)
{
    lock();

    for (unsigned int i = 0; i < m_frame.planeCount; ++i)
    {
        planes[i] = reinterpret_cast<void *>(m_frame.plane[i].data());
    }

    return 0; // There is only one buffer, so no need to identify it.
}

void QEXTQmlVLCVideoObject::unlockCallback(void *picture, void *const *planes)
{
    Q_UNUSED(picture);
    Q_UNUSED(planes);
    unlock();
    // To avoid thread polution do not call frameReady directly, but via the
    // event loop.
    QMetaObject::invokeMethod(this, "frameReady", Qt::QueuedConnection);
}

void QEXTQmlVLCVideoObject::displayCallback(void *picture)
{
    if( !m_frame.inited )
    {
        float sar = m_player->sampleAspectRatio();
        if( sar > 0.0 )
        {
            m_frame.height *= sar;
            m_frame.inited = true;
        }
    }
    Q_UNUSED(picture); // There is only one buffer.
}

unsigned int QEXTQmlVLCVideoObject::formatCallback(char *chroma,
                                               unsigned *width, unsigned *height,
                                               unsigned *pitches, unsigned *lines)
{
    qDebug() << "Format:"
             << "chroma:" << chroma
             << "width:" << *width
             << "height:" << *height
             << "pitches:" << *pitches
             << "lines:" << *lines;

    if (!m_graphicsPainter)
    {
        m_graphicsPainter = new QEXTQmlVLCGLSLPainter;
    }

    qstrcpy(chroma, "YV12");
    const vlc_chroma_description_t *chromaDesc = vlc_fourcc_GetChromaDescription(VLC_CODEC_YV12);

    Q_ASSERT(chromaDesc);

    m_frame.width = *width;
    m_frame.height = *height;
    m_frame.planeCount = chromaDesc->plane_count;

    qDebug() << chroma << chromaDesc->plane_count << *lines;

    const unsigned int bufferSize = setPitchAndLines(chromaDesc,
                                                     *width, *height,
                                                     pitches, lines,
                                                     (unsigned *) &m_frame.visiblePitch, (unsigned *)&m_frame.visibleLines);
    for (unsigned int i = 0; i < m_frame.planeCount; ++i)
    {
        m_frame.pitch[i] = pitches[i];
        m_frame.lines[i] = lines[i];
        m_frame.plane[i].resize(pitches[i] * lines[i]);
    }

    return bufferSize;
}

void QEXTQmlVLCVideoObject::formatCleanUpCallback()
{
    m_frame.inited = false;
    // To avoid thread polution do not call reset directly but via the event loop.
    QMetaObject::invokeMethod(this, "reset", Qt::QueuedConnection);
}
