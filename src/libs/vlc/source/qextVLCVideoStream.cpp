#include <qextVLCVideoStream.h>
#include <qextVLCYUVVideoFrame.h>

QEXTVLCVideoStream::QEXTVLCVideoStream(QEXTVLC::RenderFormatType format, QObject *parent)
    : QObject(parent)
    , m_format(format)
{

}

QEXTVLCVideoStream::~QEXTVLCVideoStream()
{
    if (m_player)
    {
        unsetCallbacks(m_player);
    }
}

void QEXTVLCVideoStream::init(QEXTVLCMediaPlayer *player)
{
    m_player = player;

    this->setCallbacks(m_player);
}

void QEXTVLCVideoStream::deinit()
{
    unsetCallbacks(m_player);

    m_player = 0;
}

unsigned QEXTVLCVideoStream::formatCallback(char *chroma, unsigned *width, unsigned *height,
                                            unsigned *pitches, unsigned *lines)
{
    switch (m_format) {
    case QEXTVLC::YUVFormat:
    {
        qstrcpy(chroma, "I420");
        m_framesQueue.append(QSharedPointer<QEXTVLCAbstractVideoFrame>(new QEXTVLCYUVVideoFrame(width, height, pitches, lines)));
        return 3;
    }
    default:
        break;
    }

    return -1; // LCOV_EXCL_LINE
}

void QEXTVLCVideoStream::formatCleanUpCallback()
{
    m_renderFrame.reset();
    m_lockedFramesList.clear();
    m_framesQueue.clear();

    QMetaObject::invokeMethod(this, "frameUpdated");
}

void *QEXTVLCVideoStream::lockCallback(void **planes)
{
//    QQueue<QSharedPointer<QEXTVLCAbstractVideoFrame> >::iterator iter;
    //    auto frameIt = m_framesQueue.begin();
    //    for (iter = m_framesQueue.begin(); iter != m_framesQueue.end() && (*iter)->use_count() > 1; ++frameIt)
    //        ;

    //    if (frameIt == m_framesQueue.end())
    //    {
    //        frameIt = m_framesQueue.emplace(m_framesQueue.end(), this->cloneFrame(m_framesQueue.front()));
    //    }

    //    QSharedPointer<QEXTVLCAbstractVideoFrame> frame = *iter;

    QSharedPointer<QEXTVLCAbstractVideoFrame> frame = this->cloneFrame(m_framesQueue.front());
    for (int i = 0; i < frame->planes.size(); i++)
    {
        planes[i] = frame->planes[i];
    }
    m_lockedFramesList.append(frame);

//    return reinterpret_cast<void *>(frameIt - m_framesQueue.begin());
    return 0;
}

void QEXTVLCVideoStream::unlockCallback(void *picture, void *const *planes)
{
    Q_UNUSED(planes)
    int frameNo = reinterpret_cast<long long>(picture);
    if (frameNo >= m_framesQueue.size())
    {
        return; // LCOV_EXCL_LINE
    }

    QSharedPointer<QEXTVLCAbstractVideoFrame> frame = m_framesQueue[frameNo];
    m_lockedFramesList.removeOne(frame);
}

void QEXTVLCVideoStream::displayCallback(void *picture)
{
    int frameNo = reinterpret_cast<long long>(picture);
    if (frameNo >= m_framesQueue.size())
    {
        Q_ASSERT(false);
        return; // LCOV_EXCL_LINE
    }

    QSharedPointer<QEXTVLCAbstractVideoFrame> frame = m_framesQueue[frameNo];
    m_renderFrame = frame;
    QMetaObject::invokeMethod(this, "frameUpdated");
}

QSharedPointer<QEXTVLCAbstractVideoFrame> QEXTVLCVideoStream::cloneFrame(const QSharedPointer<QEXTVLCAbstractVideoFrame> &frame)
{
    switch (m_format) {
    case QEXTVLC::YUVFormat:
    {
        QSharedPointer<QEXTVLCYUVVideoFrame> from = frame.dynamicCast<QEXTVLCYUVVideoFrame>();
        return from;
    }
    default:
        break;
    }

    return QSharedPointer<QEXTVLCAbstractVideoFrame>(); // LCOV_EXCL_LINE
}
