#include <qextVLCWidgetVolumeSlider.h>
#include <qextVLCAudio.h>
#include <qextVLCError.h>
#include <qextVLCMediaPlayer.h>

#include <QtCore/QTimer>
#include <QtGui/QMouseEvent>

#if QT_VERSION >= 0x050000
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#else
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#endif

QEXTVLCWidgetVolumeSlider::QEXTVLCWidgetVolumeSlider(QEXTVLCMediaPlayer *player, QWidget *parent)
    : QSlider(parent)
    , m_vlcAudio(player->audio())
    , m_vlcMediaPlayer(player)
{
    initWidgetVolumeSlider();
}

QEXTVLCWidgetVolumeSlider::QEXTVLCWidgetVolumeSlider(QWidget *parent)
    : QSlider(parent)
    , m_vlcAudio(0)
    , m_vlcMediaPlayer(0)
{
    initWidgetVolumeSlider();
}

QEXTVLCWidgetVolumeSlider::~QEXTVLCWidgetVolumeSlider()
{
    delete m_timer;
}

void QEXTVLCWidgetVolumeSlider::initWidgetVolumeSlider()
{
    m_lock = false;

    m_timer = new QTimer(this);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateVolume()));
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(setVolume(int)));
}

void QEXTVLCWidgetVolumeSlider::mousePressEvent(QMouseEvent *event)
{
    event->ignore();

    lock();
}

void QEXTVLCWidgetVolumeSlider::mouseReleaseEvent(QMouseEvent *event)
{
    event->ignore();

    unlock();
}

void QEXTVLCWidgetVolumeSlider::setMediaPlayer(QEXTVLCMediaPlayer *player)
{
    m_vlcAudio = player->audio();
    m_vlcMediaPlayer = player;

    m_timer->start(100);
}

bool QEXTVLCWidgetVolumeSlider::mute() const
{
    if (!(m_vlcMediaPlayer->state() == QEXTVLC::State_Buffering
          || m_vlcMediaPlayer->state() == QEXTVLC::State_Playing
          || m_vlcMediaPlayer->state() == QEXTVLC::State_Paused))
        return false;
    else
        return m_vlcAudio->getMute();
}

void QEXTVLCWidgetVolumeSlider::setMute(bool enabled)
{
    if (!(m_vlcMediaPlayer->state() == QEXTVLC::State_Buffering
          || m_vlcMediaPlayer->state() == QEXTVLC::State_Playing
          || m_vlcMediaPlayer->state() == QEXTVLC::State_Paused))
        return;

    if (!enabled) {
        m_timer->start(100);
        setDisabled(false);
    } else {
        m_timer->stop();
        setDisabled(true);
    }

    m_vlcAudio->toggleMute();
}

void QEXTVLCWidgetVolumeSlider::setVolume(int volume)
{
    if (m_currentVolume == volume)
        return;

    lock();

    m_currentVolume = volume;
    setValue(m_currentVolume);

    emit newVolume(m_currentVolume);

    unlock();
}

void QEXTVLCWidgetVolumeSlider::updateVolume()
{
    if (m_lock)
        return;

    if (!m_vlcMediaPlayer)
        return;

    if (m_vlcMediaPlayer->state() == QEXTVLC::State_Buffering
        || m_vlcMediaPlayer->state() == QEXTVLC::State_Playing
        || m_vlcMediaPlayer->state() == QEXTVLC::State_Paused)
        m_vlcAudio->setVolume(m_currentVolume);
}

int QEXTVLCWidgetVolumeSlider::volume() const
{
    return m_currentVolume;
}

void QEXTVLCWidgetVolumeSlider::volumeControl(bool up)
{
    if (up) {
        if (m_currentVolume != 200) {
            setVolume(m_currentVolume + 1);
        }
    } else {
        if (m_currentVolume != 0) {
            setVolume(m_currentVolume - 1);
        }
    }
}

void QEXTVLCWidgetVolumeSlider::lock()
{
    m_lock = true;
}

void QEXTVLCWidgetVolumeSlider::unlock()
{
    m_lock = false;
}
