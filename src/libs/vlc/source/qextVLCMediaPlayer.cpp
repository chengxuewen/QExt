#include <qextVLCAudio.h>
#include <qextVLCError.h>
#include <qextVLCInstance.h>
#include <qextVLCMedia.h>
#include <qextVLCMediaPlayer.h>
#include <qextVLCVideo.h>
#include <qextVLCVideoDelegate.h>

#if QEXT_LIBVLC_VERSION >= 3
#include <qextVLCEqualizer.h>
#endif

#include <qextVLCThread.h>

class QEXTVLCMediaPlayerPrivate
{
public:
    explicit QEXTVLCMediaPlayerPrivate(QEXTVLCMediaPlayer *q);
    virtual ~QEXTVLCMediaPlayerPrivate();

    QEXTVLCMediaPlayer * const q_ptr;

    libvlc_media_player_t *m_vlcMediaPlayer;
    libvlc_event_manager_t *m_vlcEvents;

    QEXTVLCMedia *m_media;

    QEXTVLCAudio *m_vlcAudio;
    QEXTVLCVideo *m_vlcVideo;
#if QEXT_LIBVLC_VERSION >= 3
    QEXTVLCEqualizer *m_vlcEqualizer;
#endif

    QEXTVLCVideoDelegate *m_videoWidget;
    WId m_currentWId;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTVLCMediaPlayerPrivate)
    QEXT_DECL_PUBLIC(QEXTVLCMediaPlayer)
};

QEXTVLCMediaPlayerPrivate::QEXTVLCMediaPlayerPrivate(QEXTVLCMediaPlayer *q)
    : q_ptr(q)
{

}

QEXTVLCMediaPlayerPrivate::~QEXTVLCMediaPlayerPrivate()
{

}



QEXTVLCMediaPlayer::QEXTVLCMediaPlayer(QEXTVLCInstance *instance)
    : QObject(instance)
    , dd_ptr(new QEXTVLCMediaPlayerPrivate(this))
{
    Q_D(QEXTVLCMediaPlayer);
    d->m_vlcMediaPlayer = libvlc_media_player_new(instance->core());
    d->m_vlcEvents = libvlc_media_player_event_manager(d->m_vlcMediaPlayer);

    /* Disable mouse and keyboard events */
    libvlc_video_set_key_input(d->m_vlcMediaPlayer, false);
    libvlc_video_set_mouse_input(d->m_vlcMediaPlayer, false);

    QEXTVLCError::showErrMsg();

    d->m_vlcAudio = new QEXTVLCAudio(this);
    d->m_vlcVideo = new QEXTVLCVideo(this);
#if QEXT_LIBVLC_VERSION >= 3
    d->m_vlcEqualizer = new QEXTVLCEqualizer(this);
#endif

    d->m_videoWidget = 0;
    d->m_media = 0;

    createCoreConnections();

    QEXTVLCError::showErrMsg();
}

QEXTVLCMediaPlayer::~QEXTVLCMediaPlayer()
{
    Q_D(QEXTVLCMediaPlayer);
    this->removeCoreConnections();

    delete d->m_vlcAudio;
    delete d->m_vlcVideo;
#if QEXT_LIBVLC_VERSION >= 3
    delete d->m_vlcEqualizer;
#endif

    libvlc_media_player_release(d->m_vlcMediaPlayer);

    QEXTVLCError::showErrMsg();
}

libvlc_media_player_t *QEXTVLCMediaPlayer::core() const
{
    Q_D(const QEXTVLCMediaPlayer);
    return d->m_vlcMediaPlayer;
}

QEXTVLCAudio *QEXTVLCMediaPlayer::audio() const
{
    Q_D(const QEXTVLCMediaPlayer);
    return d->m_vlcAudio;
}

QEXTVLCVideo *QEXTVLCMediaPlayer::video() const
{
    Q_D(const QEXTVLCMediaPlayer);
    return d->m_vlcVideo;
}

#if QEXT_LIBVLC_VERSION >= 3
QEXTVLCEqualizer *QEXTVLCMediaPlayer::equalizer() const
{
    Q_D(const QEXTVLCMediaPlayer);
    return d->m_vlcEqualizer;
}
#endif

void QEXTVLCMediaPlayer::createCoreConnections()
{
    Q_D(QEXTVLCMediaPlayer);
    QList<libvlc_event_e> list;
    list << libvlc_MediaPlayerMediaChanged
         << libvlc_MediaPlayerNothingSpecial
         << libvlc_MediaPlayerOpening
         << libvlc_MediaPlayerBuffering
         << libvlc_MediaPlayerPlaying
         << libvlc_MediaPlayerPaused
         << libvlc_MediaPlayerStopped
         << libvlc_MediaPlayerForward
         << libvlc_MediaPlayerBackward
         << libvlc_MediaPlayerEndReached
         << libvlc_MediaPlayerEncounteredError
         << libvlc_MediaPlayerTimeChanged
         << libvlc_MediaPlayerPositionChanged
         << libvlc_MediaPlayerSeekableChanged
         << libvlc_MediaPlayerPausableChanged
         << libvlc_MediaPlayerTitleChanged
         << libvlc_MediaPlayerSnapshotTaken
         << libvlc_MediaPlayerLengthChanged
         << libvlc_MediaPlayerVout;

    foreach (const libvlc_event_e &event, list)
    {
        libvlc_event_attach(d->m_vlcEvents, event, libVLCCallback, this);
    }
}

void QEXTVLCMediaPlayer::removeCoreConnections()
{
    Q_D(QEXTVLCMediaPlayer);
    QList<libvlc_event_e> list;
    list << libvlc_MediaPlayerMediaChanged
         << libvlc_MediaPlayerNothingSpecial
         << libvlc_MediaPlayerOpening
         << libvlc_MediaPlayerBuffering
         << libvlc_MediaPlayerPlaying
         << libvlc_MediaPlayerPaused
         << libvlc_MediaPlayerStopped
         << libvlc_MediaPlayerForward
         << libvlc_MediaPlayerBackward
         << libvlc_MediaPlayerEndReached
         << libvlc_MediaPlayerEncounteredError
         << libvlc_MediaPlayerTimeChanged
         << libvlc_MediaPlayerPositionChanged
         << libvlc_MediaPlayerSeekableChanged
         << libvlc_MediaPlayerPausableChanged
         << libvlc_MediaPlayerTitleChanged
         << libvlc_MediaPlayerSnapshotTaken
         << libvlc_MediaPlayerLengthChanged
         << libvlc_MediaPlayerVout;

    foreach (const libvlc_event_e &event, list)
    {
        libvlc_event_detach(d->m_vlcEvents, event, libVLCCallback, this);
    }
}

bool QEXTVLCMediaPlayer::hasVout() const
{
    Q_D(const QEXTVLCMediaPlayer);
    bool status = false;
    if (d->m_vlcMediaPlayer)
    {
        status = libvlc_media_player_has_vout(d->m_vlcMediaPlayer);
    }

    return status;
}

int QEXTVLCMediaPlayer::length() const
{
    Q_D(const QEXTVLCMediaPlayer);
    libvlc_time_t length = libvlc_media_player_get_length(d->m_vlcMediaPlayer);

    QEXTVLCError::showErrMsg();

    return length;
}

QEXTVLCMedia *QEXTVLCMediaPlayer::currentMedia() const
{
    Q_D(const QEXTVLCMediaPlayer);
    return d->m_media;
}

libvlc_media_t *QEXTVLCMediaPlayer::currentMediaCore()
{
    Q_D(QEXTVLCMediaPlayer);
    libvlc_media_t *media = libvlc_media_player_get_media(d->m_vlcMediaPlayer);

    QEXTVLCError::showErrMsg();

    return media;
}

void QEXTVLCMediaPlayer::open(QEXTVLCMedia *media)
{
    Q_D(QEXTVLCMediaPlayer);
    d->m_media = media;
    libvlc_media_player_set_media(d->m_vlcMediaPlayer, media->core());

    QEXTVLCError::showErrMsg();

    play();
}

void QEXTVLCMediaPlayer::openOnly(QEXTVLCMedia *media)
{
    Q_D(QEXTVLCMediaPlayer);
    d->m_media = media;
    libvlc_media_player_set_media(d->m_vlcMediaPlayer, media->core());

    QEXTVLCError::showErrMsg();
}

void QEXTVLCMediaPlayer::play()
{
    Q_D(QEXTVLCMediaPlayer);
    if (!d->m_vlcMediaPlayer)
    {
        return;
    }

    if (d->m_videoWidget)
    {
        d->m_currentWId = d->m_videoWidget->request();
    }
    else
    {
        d->m_currentWId = 0;
    }

    /* Get our media instance to use our window */
    if (d->m_currentWId)
    {
#if defined(Q_OS_WIN32)
        libvlc_media_player_set_hwnd(d->m_vlcMediaPlayer, (void *)d->m_currentWId);
#elif defined(Q_OS_DARWIN)
        libvlc_media_player_set_nsobject(d->m_vlcMediaPlayer, (void *)d->m_currentWId);
#elif defined(Q_OS_UNIX)
        libvlc_media_player_set_xwindow(d->m_vlcMediaPlayer, d->m_currentWId);
#endif
    }

    libvlc_media_player_play(d->m_vlcMediaPlayer);

    QEXTVLCError::showErrMsg();
}

void QEXTVLCMediaPlayer::pause()
{
    Q_D(QEXTVLCMediaPlayer);
    if (!d->m_vlcMediaPlayer)
    {
        return;
    }

    if (libvlc_media_player_can_pause(d->m_vlcMediaPlayer))
    {
        libvlc_media_player_set_pause(d->m_vlcMediaPlayer, true);
    }

    QEXTVLCError::showErrMsg();
}

void QEXTVLCMediaPlayer::togglePause()
{
    Q_D(QEXTVLCMediaPlayer);
    if (!d->m_vlcMediaPlayer)
    {
        return;
    }

    if (libvlc_media_player_can_pause(d->m_vlcMediaPlayer))
    {
        libvlc_media_player_pause(d->m_vlcMediaPlayer);
    }

    QEXTVLCError::showErrMsg();
}

void QEXTVLCMediaPlayer::resume()
{
    Q_D(QEXTVLCMediaPlayer);
    if (!d->m_vlcMediaPlayer)
    {
        return;
    }

    if (libvlc_media_player_can_pause(d->m_vlcMediaPlayer))
    {
        libvlc_media_player_set_pause(d->m_vlcMediaPlayer, false);
    }

    QEXTVLCError::showErrMsg();
}

void QEXTVLCMediaPlayer::setTime(int time)
{
    Q_D(QEXTVLCMediaPlayer);
    if (!(state() == QEXTVLC::State_Buffering || state() == QEXTVLC::State_Playing || state() == QEXTVLC::State_Paused))
    {
        return;
    }

    libvlc_media_player_set_time(d->m_vlcMediaPlayer, time);

    if (state() == QEXTVLC::State_Paused)
    {
        emit timeChanged(time);
    }

    QEXTVLCError::showErrMsg();
}

void QEXTVLCMediaPlayer::setVideoWidget(QEXTVLCVideoDelegate *widget)
{
    Q_D(QEXTVLCMediaPlayer);
    d->m_videoWidget = widget;
}

bool QEXTVLCMediaPlayer::seekable() const
{
    Q_D(const QEXTVLCMediaPlayer);
    if (!libvlc_media_player_get_media(d->m_vlcMediaPlayer))
    {
        return false;
    }

    bool seekable = libvlc_media_player_is_seekable(d->m_vlcMediaPlayer);

    QEXTVLCError::showErrMsg();

    return seekable;
}

QEXTVLC::StateType QEXTVLCMediaPlayer::state() const
{
    Q_D(const QEXTVLCMediaPlayer);
    // It's possible that the vlc doesn't play anything
    // so check before
    if (!libvlc_media_player_get_media(d->m_vlcMediaPlayer))
    {
        return QEXTVLC::State_Idle;
    }

    libvlc_state_t state;
    state = libvlc_media_player_get_state(d->m_vlcMediaPlayer);

    QEXTVLCError::showErrMsg();

    return QEXTVLC::StateType(state);
}

void QEXTVLCMediaPlayer::stop()
{
    Q_D(QEXTVLCMediaPlayer);
    if (!d->m_vlcMediaPlayer)
    {
        return;
    }

    if (d->m_videoWidget)
    {
        d->m_videoWidget->release();
    }
    d->m_currentWId = 0;

    libvlc_media_player_stop(d->m_vlcMediaPlayer);

    QEXTVLCError::showErrMsg();
}

int QEXTVLCMediaPlayer::time() const
{
    Q_D(const QEXTVLCMediaPlayer);
    libvlc_time_t time = libvlc_media_player_get_time(d->m_vlcMediaPlayer);

    QEXTVLCError::showErrMsg();

    return time;
}

QEXTVLCVideoDelegate *QEXTVLCMediaPlayer::videoWidget() const
{
    Q_D(const QEXTVLCMediaPlayer);
    return d->m_videoWidget;
}

void QEXTVLCMediaPlayer::libVLCCallback(const libvlc_event_t *event, void *data)
{
    QEXTVLCMediaPlayer *core = static_cast<QEXTVLCMediaPlayer *>(data);

    switch (event->type)
    {
    case libvlc_MediaPlayerMediaChanged:
        emit core->mediaChanged(event->u.media_player_media_changed.new_media);
        break;
    case libvlc_MediaPlayerNothingSpecial:
        emit core->nothingSpecial();
        break;
    case libvlc_MediaPlayerOpening:
        emit core->opening();
        break;
    case libvlc_MediaPlayerBuffering:
        emit core->buffering(event->u.media_player_buffering.new_cache);
        emit core->buffering(qRound(event->u.media_player_buffering.new_cache));
        break;
    case libvlc_MediaPlayerPlaying:
        emit core->playing();
        break;
    case libvlc_MediaPlayerPaused:
        emit core->paused();
        break;
    case libvlc_MediaPlayerStopped:
        emit core->stopped();
        break;
    case libvlc_MediaPlayerForward:
        emit core->forward();
        break;
    case libvlc_MediaPlayerBackward:
        emit core->backward();
        break;
    case libvlc_MediaPlayerEndReached:
        emit core->end();
        break;
    case libvlc_MediaPlayerEncounteredError:
        emit core->error();
        break;
    case libvlc_MediaPlayerTimeChanged:
        emit core->timeChanged(event->u.media_player_time_changed.new_time);
        break;
    case libvlc_MediaPlayerPositionChanged:
        emit core->positionChanged(event->u.media_player_position_changed.new_position);
        break;
    case libvlc_MediaPlayerSeekableChanged:
        emit core->seekableChanged(event->u.media_player_seekable_changed.new_seekable);
        break;
    case libvlc_MediaPlayerPausableChanged:
        emit core->pausableChanged(event->u.media_player_pausable_changed.new_pausable);
        break;
    case libvlc_MediaPlayerTitleChanged:
        emit core->titleChanged(event->u.media_player_title_changed.new_title);
        break;
    case libvlc_MediaPlayerSnapshotTaken:
        emit core->snapshotTaken(event->u.media_player_snapshot_taken.psz_filename);
        break;
    case libvlc_MediaPlayerLengthChanged:
        emit core->lengthChanged(event->u.media_player_length_changed.new_length);
        break;
    case libvlc_MediaPlayerVout:
        emit core->vout(event->u.media_player_vout.new_count);
        break;
    default:
        break;
    }

    if (event->type >= libvlc_MediaPlayerNothingSpecial && event->type <= libvlc_MediaPlayerEncounteredError)
    {
        emit core->stateChanged();
    }
}

float QEXTVLCMediaPlayer::position()
{
    Q_D(QEXTVLCMediaPlayer);
    if (!d->m_vlcMediaPlayer)
    {
        return -1;
    }

    return libvlc_media_player_get_position(d->m_vlcMediaPlayer);
}

float QEXTVLCMediaPlayer::sampleAspectRatio()
{
    Q_D(QEXTVLCMediaPlayer);
    if (!d->m_vlcMediaPlayer)
    {
        return 0.0;
    }
#if QEXT_LIBVLC_VERSION >= 3
    float sar = 0.0;

    libvlc_media_track_t **tracks;
    unsigned tracksCount;
    tracksCount = libvlc_media_tracks_get(d->m_media->core(), &tracks);
    if (tracksCount > 0)
    {
        for (unsigned i = 0; i < tracksCount; i++)
        {
            libvlc_media_track_t *track = tracks[i];
            if (track->i_type == libvlc_track_video && track->i_id == 0)
            {
                libvlc_video_track_t *videoTrack = track->video;
                if (videoTrack->i_sar_num > 0)
                {
                    sar = (float)videoTrack->i_sar_den / (float)videoTrack->i_sar_num;
                }
            }
        }
        libvlc_media_tracks_release(tracks, tracksCount);
    }

    return sar;
#else
    return 1.0;
#endif // QEXT_LIBVLC_VERSION >= 3
}

void QEXTVLCMediaPlayer::setPosition(float pos)
{
    Q_D(QEXTVLCMediaPlayer);
    libvlc_media_player_set_position(d->m_vlcMediaPlayer, pos);

    QEXTVLCError::showErrMsg();
}

void QEXTVLCMediaPlayer::setPlaybackRate(float rate)
{
    Q_D(QEXTVLCMediaPlayer);
    libvlc_media_player_set_rate(d->m_vlcMediaPlayer, rate);

    QEXTVLCError::showErrMsg();
}

float QEXTVLCMediaPlayer::playbackRate()
{
    Q_D(QEXTVLCMediaPlayer);
    if (!d->m_vlcMediaPlayer)
    {
        return -1;
    }

    return libvlc_media_player_get_rate(d->m_vlcMediaPlayer);
}
