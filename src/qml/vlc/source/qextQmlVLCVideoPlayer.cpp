#include <qextQmlVLCVideoPlayer.h>

#include <qextVLCVideo.h>
#include <qextVLCAudio.h>
#include <qextVLCCommon.h>
#include <qextVLCInstance.h>
#include <qextVLCMedia.h>
#include <qextVLCMediaPlayer.h>
#include <qextVLCTrackModel.h>

#include <QtCore/QDebug>
#include <QtQml/QQmlEngine>

//#include "Config.h"

QEXTQmlVLCVideoPlayer::QEXTQmlVLCVideoPlayer(QQuickItem *parent)
    : QEXTQmlVLCVideoObject(parent)
    , m_instance(0)
    , m_media(0)
    , m_audioManager(0)
    , m_videoManager(0)
    , m_deinterlacing(QEXTVLC::Deinterlacing_Disabled)
    , m_hasMedia(false)
    , m_autoplay(true)
    , m_seekable(true)
{
    m_instance = new QEXTVLCInstance(QEXTVLCCommon::args(), this);
    m_instance->setUserAgent(qApp->applicationName(), qApp->applicationVersion());
    m_player = new QEXTVLCMediaPlayer(m_instance);
    m_audioManager = new QEXTVLCAudio(m_player);
    m_videoManager = new QEXTVLCVideo(m_player);

    connect(m_player, SIGNAL(stateChanged()), this, SIGNAL(stateChanged()));
    connect(m_player, SIGNAL(seekableChanged(bool)), this, SLOT(seekableChangedPrivate(bool)));
    connect(m_player, SIGNAL(lengthChanged(int)), this, SIGNAL(lengthChanged()));
    connect(m_player, SIGNAL(timeChanged(int)), this, SIGNAL(timeChanged()));
    connect(m_player, SIGNAL(positionChanged(float)), this, SIGNAL(positionChanged()));
    connect(m_player, SIGNAL(vout(int)), this, SLOT(mediaPlayerVout(int)));

    m_audioTrackModel = new QEXTVLCTrackModel(this);
    m_subtitleTrackModel = new QEXTVLCTrackModel(this);
    m_videoTrackModel = new QEXTVLCTrackModel(this);
}

QEXTQmlVLCVideoPlayer::~QEXTQmlVLCVideoPlayer()
{
    m_player->stop();

    delete m_audioManager;
    delete m_videoManager;
    delete m_media;
    delete m_player;
    delete m_instance;
}

void QEXTQmlVLCVideoPlayer::registerPlugin()
{
    qmlRegisterType<QEXTQmlVLCVideoPlayer>("VLCQt", 1, 0, "QEXTVLCVideoPlayer");
}

void QEXTQmlVLCVideoPlayer::openInternal()
{
    if(m_autoplay)
        m_player->open(m_media);
    else
        m_player->openOnly(m_media);

    connectToMediaPlayer(m_player);

    m_hasMedia = true;
}

int QEXTQmlVLCVideoPlayer::preferredAudioTrackId()
{
    int currentTrackId = m_player->audio()->track();
    if (m_audioTrackModel->count() && m_audioPreferredLanguages.count()) {
        bool found = false;
        for (int j = 0; !found && j < m_audioPreferredLanguages.count(); j++) {
            for (int i = 0; !found && i < m_audioTrackModel->count(); i++) {
                QString trackTitle = m_audioTrackModel->data(i, QEXTVLCTrackModel::TitleRole).toString();
                if (trackTitle.contains(m_audioPreferredLanguages.at(j))) {
                    currentTrackId = m_audioTrackModel->data(i, QEXTVLCTrackModel::IdRole).toInt();
                    found = true;
                }
            }
        }
    }

    return currentTrackId;
}

int QEXTQmlVLCVideoPlayer::preferredSubtitleTrackId()
{
    int currentTrackId = m_player->video()->subtitle();
    if (m_subtitleTrackModel->count()) {
        bool found = false;
        for (int j = 0; !found && j < m_subtitlePreferredLanguages.count(); j++) {
            for (int i = 0; !found && i < m_subtitleTrackModel->count(); i++) {
                QString trackTitle = m_subtitleTrackModel->data(i, QEXTVLCTrackModel::TitleRole).toString();
                if (trackTitle.contains(m_subtitlePreferredLanguages.at(j))) {
                    currentTrackId = m_subtitleTrackModel->data(i, QEXTVLCTrackModel::IdRole).toInt();
                    found = true;
                }
            }
        }
    }

    return currentTrackId;
}

QEXTVLCTrackModel *QEXTQmlVLCVideoPlayer::audioTrackModel() const
{
    return m_audioTrackModel;
}

int QEXTQmlVLCVideoPlayer::audioTrack() const
{
    return m_audioManager->track();
}

void QEXTQmlVLCVideoPlayer::setAudioTrack(int audioTrack)
{
    m_audioManager->setTrack(audioTrack);
    emit audioTrackChanged();
}

QStringList QEXTQmlVLCVideoPlayer::audioPreferredLanguages() const
{
    return m_audioPreferredLanguages;
}

void QEXTQmlVLCVideoPlayer::setAudioPreferredLanguages(const QStringList &audioPreferredLanguages)
{
    m_audioPreferredLanguages = audioPreferredLanguages;
    emit audioPreferredLanguagesChanged();
}

int QEXTQmlVLCVideoPlayer::subtitleTrack() const
{
    return m_videoManager->subtitle();
}

void QEXTQmlVLCVideoPlayer::setSubtitleTrack(int subtitleTrack)
{
    m_videoManager->setSubtitle(subtitleTrack);
    emit subtitleTrackChanged();
}

QStringList QEXTQmlVLCVideoPlayer::subtitlePreferredLanguages() const
{
    return m_subtitlePreferredLanguages;
}

void QEXTQmlVLCVideoPlayer::setSubtitlePreferredLanguages(const QStringList &subtitlePreferredLanguages)
{
    m_subtitlePreferredLanguages = subtitlePreferredLanguages;
    emit subtitlePreferredLanguagesChanged();
}

QEXTVLCTrackModel *QEXTQmlVLCVideoPlayer::subtitleTrackModel() const
{
    return m_subtitleTrackModel;
}

int QEXTQmlVLCVideoPlayer::videoTrack() const
{
    return m_videoManager->track();
}

void QEXTQmlVLCVideoPlayer::setVideoTrack(int videoTrack)
{
    m_videoManager->setTrack(videoTrack);
    emit videoTrackChanged();
}

QEXTVLCTrackModel *QEXTQmlVLCVideoPlayer::videoTrackModel() const
{
    return m_videoTrackModel;
}

QString QEXTQmlVLCVideoPlayer::deinterlacing() const
{
    return QEXTVLC::deinterlacing()[m_deinterlacing];
}

void QEXTQmlVLCVideoPlayer::setDeinterlacing(const QString &deinterlacing)
{
    m_deinterlacing = (QEXTVLC::DeinterlacingType) QEXTVLC::deinterlacing().indexOf(deinterlacing);
    m_player->video()->setDeinterlace(m_deinterlacing);
    emit deinterlacingChanged();
}

int QEXTQmlVLCVideoPlayer::state() const
{
    return (int)m_player->state();
}

bool QEXTQmlVLCVideoPlayer::seekable() const
{
    return m_seekable;
}

int QEXTQmlVLCVideoPlayer::length() const
{
    return m_player->length();
}

int QEXTQmlVLCVideoPlayer::time() const
{
    return m_player->time();
}

void QEXTQmlVLCVideoPlayer::setTime(int time)
{
    m_player->setTime( time );
}

float QEXTQmlVLCVideoPlayer::position() const
{
    return m_player->position();
}

void QEXTQmlVLCVideoPlayer::setPosition(float position)
{
    m_player->setPosition( position );
}

void QEXTQmlVLCVideoPlayer::seekableChangedPrivate(bool seekable)
{
    m_seekable = seekable;
    emit seekableChanged();
}

void QEXTQmlVLCVideoPlayer::mediaParsed(bool parsed)
{
    if(parsed == 1)
    {
        m_audioTrackModel->clear();
        m_audioTrackModel->load(m_audioManager->tracks());

        setAudioTrack(preferredAudioTrackId());
    }
}

void QEXTQmlVLCVideoPlayer::mediaPlayerVout(int)
{
    m_subtitleTrackModel->clear();
    m_subtitleTrackModel->load(m_videoManager->subtitles());

    setSubtitleTrack(preferredSubtitleTrackId());

    m_videoTrackModel->clear();
    m_videoTrackModel->load(m_videoManager->tracks());

    setVideoTrack(m_videoManager->track());
}

bool QEXTQmlVLCVideoPlayer::autoplay() const
{
    return m_autoplay;
}

void QEXTQmlVLCVideoPlayer::setAutoplay(bool autoplay)
{
    m_autoplay = autoplay;
}

QUrl QEXTQmlVLCVideoPlayer::url() const
{
    if (m_media)
        return QUrl(m_media->currentLocation());
    else
        return QUrl();
}

void QEXTQmlVLCVideoPlayer::setUrl(const QUrl &url)
{
    m_player->stop();

    if (m_media)
        m_media->deleteLater();

    if(url.isLocalFile()) {
        m_media = new QEXTVLCMedia(url.toLocalFile(), true, m_instance);
    } else {
        m_media = new QEXTVLCMedia(url.toString(QUrl::FullyEncoded), false, m_instance);
    }

    connect(m_media, static_cast<void (QEXTVLCMedia::*)(bool)>(&QEXTVLCMedia::parsedChanged), this, &QEXTQmlVLCVideoPlayer::mediaParsed);

    openInternal();
}

void QEXTQmlVLCVideoPlayer::pause()
{
    m_player->pause();
}

void QEXTQmlVLCVideoPlayer::play()
{
    m_player->play();
}

void QEXTQmlVLCVideoPlayer::stop()
{
    m_player->stop();
    disconnectFromMediaPlayer(m_player);
}

int QEXTQmlVLCVideoPlayer::volume() const
{
    return m_audioManager->volume();
}

void QEXTQmlVLCVideoPlayer::setVolume(int volume)
{
    m_audioManager->setVolume(volume);
    emit volumeChanged();
}

QString QEXTQmlVLCVideoPlayer::aspectRatio() const
{
    return QEXTVLC::ratio()[QEXTQmlVLCVideoObject::aspectRatio()];
}

void QEXTQmlVLCVideoPlayer::setAspectRatio(const QString &aspectRatio)
{
    QEXTQmlVLCVideoObject::setAspectRatio( (QEXTVLC::RatioType) QEXTVLC::ratio().indexOf(aspectRatio) );
    emit aspectRatioChanged();
}

QString QEXTQmlVLCVideoPlayer::cropRatio() const
{
    return QEXTVLC::ratio()[QEXTQmlVLCVideoObject::cropRatio()];
}

void QEXTQmlVLCVideoPlayer::setCropRatio(const QString &cropRatio)
{
    QEXTQmlVLCVideoObject::setCropRatio( (QEXTVLC::RatioType) QEXTVLC::ratio().indexOf(cropRatio) );
    emit cropRatioChanged();
}
