#include <qextVLCAbstractVideoStream.h>
#include <qextVLCMediaPlayer.h>

#include <vlc/vlc.h>

static inline QEXTVLCAbstractVideoStream *p_this(void *opaque)
{
    return static_cast<QEXTVLCAbstractVideoStream *>(opaque);
}
static inline QEXTVLCAbstractVideoStream *p_this(void **opaque)
{
    return static_cast<QEXTVLCAbstractVideoStream *>(*opaque);
}
#define P_THIS p_this(opaque)

QEXTVLCAbstractVideoStream::QEXTVLCAbstractVideoStream()
{
}

QEXTVLCAbstractVideoStream::~QEXTVLCAbstractVideoStream() {}

void QEXTVLCAbstractVideoStream::setCallbacks(QEXTVLCMediaPlayer *player)
{
    libvlc_video_set_callbacks(player->core(),
                               lockCallbackInternal,
                               unlockCallbackInternal,
                               displayCallbackInternal,
                               this);
    libvlc_video_set_format_callbacks(player->core(),
                                      formatCallbackInternal,
                                      formatCleanUpCallbackInternal);
}

void QEXTVLCAbstractVideoStream::unsetCallbacks(QEXTVLCMediaPlayer *player)
{
    if (player)
    {
        libvlc_video_set_callbacks(player->core(), 0, 0, 0, 0);
        libvlc_video_set_format_callbacks(player->core(), 0, 0);
    }
}

void *QEXTVLCAbstractVideoStream::lockCallbackInternal(void *opaque, void **planes)
{
    return P_THIS->lockCallback(planes);
}

void QEXTVLCAbstractVideoStream::unlockCallbackInternal(void *opaque, void *picture, void *const *planes)
{
    P_THIS->unlockCallback(picture, planes);
}

void QEXTVLCAbstractVideoStream::displayCallbackInternal(void *opaque,
                                                         void *picture)
{
    P_THIS->displayCallback(picture);
}

unsigned QEXTVLCAbstractVideoStream::formatCallbackInternal(void **opaque, char *chroma,
                                                            unsigned *width, unsigned *height,
                                                            unsigned *pitches, unsigned *lines)
{
    return P_THIS->formatCallback(chroma, width, height, pitches, lines);
}

void QEXTVLCAbstractVideoStream::formatCleanUpCallbackInternal(void *opaque)
{
    P_THIS->formatCleanUpCallback();
}
