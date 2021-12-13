#include <qextQmlVLCPlayer.h>
#include <qextQmlVLCSource.h>

#include <qextVLCAudio.h>
#include <qextVLCCommon.h>
#include <qextVLCInstance.h>
#include <qextVLCMediaPlayer.h>
#include <qextVLCMedia.h>
#include <qextVLCTrackModel.h>
#include <qextVLCVideo.h>

QEXTQmlVLCPlayer::QEXTQmlVLCPlayer(QObject *parent)
    : QEXTQmlVLCSource(parent)
    , m_media(0)
    , m_autoplay(true)
    , m_deinterlacing(QEXTVLC::Deinterlacing_Disabled)
    , m_audioPreferredLanguages(QStringList())
    , m_subtitlePreferredLanguages(QStringList())
{
    m_instance = new QEXTVLCInstance(QEXTVLCCommon::args(), this);
    m_player = new QEXTVLCMediaPlayer(m_instance);

    m_audioTrackModel = new QEXTVLCTrackModel(this);
    m_subtitleTrackModel = new QEXTVLCTrackModel(this);
    m_videoTrackModel = new QEXTVLCTrackModel(this);

    connect(m_player, &QEXTVLCMediaPlayer::lengthChanged, this, &QEXTQmlVLCPlayer::lengthChanged);
    connect(m_player, &QEXTVLCMediaPlayer::positionChanged, this, &QEXTQmlVLCPlayer::positionChanged);
    connect(m_player, &QEXTVLCMediaPlayer::seekableChanged, this, &QEXTQmlVLCPlayer::seekableChanged);
    connect(m_player, &QEXTVLCMediaPlayer::stateChanged, this, &QEXTQmlVLCPlayer::stateChanged);
    connect(m_player, &QEXTVLCMediaPlayer::timeChanged, this, &QEXTQmlVLCPlayer::timeChanged);
    connect(m_player, &QEXTVLCMediaPlayer::vout, this, &QEXTQmlVLCPlayer::mediaPlayerVout);

    this->setPlayer(m_player);
}

QEXTQmlVLCPlayer::~QEXTQmlVLCPlayer()
{
    m_player->stop();
    removePlayer();

    if (m_media)
    {
        delete m_media;
    }

    delete m_player;
    delete m_instance;
}

void QEXTQmlVLCPlayer::pause()
{
    m_player->pause();
}

void QEXTQmlVLCPlayer::play()
{
    m_player->play();
}

void QEXTQmlVLCPlayer::stop()
{
    m_player->stop();
}

bool QEXTQmlVLCPlayer::autoplay() const
{
    return m_autoplay;
}

void QEXTQmlVLCPlayer::setAutoplay(bool autoplay)
{
    if (m_autoplay == autoplay)
    {
        return;
    }

    m_autoplay = autoplay;
    emit autoplayChanged();
}

int QEXTQmlVLCPlayer::deinterlacing() const
{
    return m_deinterlacing;
}

void QEXTQmlVLCPlayer::setDeinterlacing(int deinterlacing)
{
    if (m_deinterlacing == deinterlacing)
    {
        return;
    }

    m_deinterlacing = QEXTVLC::DeinterlacingType(deinterlacing);
    m_player->video()->setDeinterlace(m_deinterlacing);
    emit deinterlacingChanged();
}

qint64 QEXTQmlVLCPlayer::length() const
{
    return m_player->length();
}

int QEXTQmlVLCPlayer::logLevel() const
{
    return m_instance->logLevel();
}

void QEXTQmlVLCPlayer::setLogLevel(int level)
{
    if (level == logLevel())
    {
        return;
    }

    m_instance->setLogLevel(QEXTVLC::LogLevelType(level));
    emit logLevelChanged();
}

bool QEXTQmlVLCPlayer::seekable() const
{
    return m_player->seekable();
}

int QEXTQmlVLCPlayer::state() const
{
    return m_player->state();
}

float QEXTQmlVLCPlayer::position() const
{
    return m_player->position();
}

void QEXTQmlVLCPlayer::setPosition(float position)
{
    m_player->setPosition(position);
}

qint64 QEXTQmlVLCPlayer::time() const
{
    return m_player->time();
}

void QEXTQmlVLCPlayer::setTime(qint64 time)
{
    m_player->setTime(time);
}

QUrl QEXTQmlVLCPlayer::url() const
{
    if (m_media)
    {
        return QUrl(m_media->currentLocation());
    }
    else
    {
        return QUrl();
    }
}

void QEXTQmlVLCPlayer::setUrl(const QUrl &url)
{
    if (url == QEXTQmlVLCPlayer::url())
    {
        return;
    }

    m_player->stop();

    if (m_media)
    {
        m_media->deleteLater();
    }

    if (url.isLocalFile())
    {
        m_media = new QEXTVLCMedia(url.toLocalFile(), true, m_instance);
    }
    else
    {
        m_media = new QEXTVLCMedia(url.toString(QUrl::FullyEncoded), false, m_instance);
    }

    connect(m_media, static_cast<void (QEXTVLCMedia::*)(bool)>(&QEXTVLCMedia::parsedChanged), this, &QEXTQmlVLCPlayer::mediaParsed);

    this->openInternal();

    emit this->urlChanged();
}

int QEXTQmlVLCPlayer::volume() const
{
    return m_player->audio()->volume();
}

void QEXTQmlVLCPlayer::setVolume(int volume)
{
    if (volume == QEXTQmlVLCPlayer::volume())
    {
        return;
    }

    m_player->audio()->setVolume(volume);
    emit volumeChanged();
}

QEXTVLCTrackModel *QEXTQmlVLCPlayer::audioTrackModel() const
{
    return m_audioTrackModel;
}

int QEXTQmlVLCPlayer::audioTrack() const
{
    return m_player->audio()->track();
}

void QEXTQmlVLCPlayer::setAudioTrack(int audioTrack)
{
    if (audioTrack == QEXTQmlVLCPlayer::audioTrack())
    {
        return;
    }

    m_player->audio()->setTrack(audioTrack);
    emit this->audioTrackChanged();
}

QStringList QEXTQmlVLCPlayer::audioPreferredLanguages() const
{
    return m_audioPreferredLanguages;
}

void QEXTQmlVLCPlayer::setAudioPreferredLanguages(const QStringList &audioPreferredLanguages)
{
    if (m_audioPreferredLanguages == audioPreferredLanguages)
    {
        return;
    }

    m_audioPreferredLanguages = audioPreferredLanguages;
    emit this->audioPreferredLanguagesChanged();
}

QEXTVLCTrackModel *QEXTQmlVLCPlayer::subtitleTrackModel() const
{
    return m_subtitleTrackModel;
}

int QEXTQmlVLCPlayer::subtitleTrack() const
{
    return m_player->video()->subtitle();
}

void QEXTQmlVLCPlayer::setSubtitleTrack(int subtitleTrack)
{
    if (subtitleTrack == QEXTQmlVLCPlayer::subtitleTrack())
    {
        return;
    }

    m_player->video()->setSubtitle(subtitleTrack);
    emit this->subtitleTrackChanged();
}

QStringList QEXTQmlVLCPlayer::subtitlePreferredLanguages() const
{
    return m_subtitlePreferredLanguages;
}

void QEXTQmlVLCPlayer::setSubtitlePreferredLanguages(const QStringList &subtitlePreferredLanguages)
{
    if (m_subtitlePreferredLanguages == subtitlePreferredLanguages)
    {
        return;
    }

    m_subtitlePreferredLanguages = subtitlePreferredLanguages;
    emit this->subtitlePreferredLanguagesChanged();
}

QEXTVLCTrackModel *QEXTQmlVLCPlayer::videoTrackModel() const
{
    return m_videoTrackModel;
}

int QEXTQmlVLCPlayer::videoTrack() const
{
    return m_player->video()->track();
}

void QEXTQmlVLCPlayer::setVideoTrack(int videoTrack)
{
    if (videoTrack == QEXTQmlVLCPlayer::videoTrack())
    {
        return;
    }

    m_player->video()->setTrack(videoTrack);
    emit this->videoTrackChanged();
}

void QEXTQmlVLCPlayer::mediaParsed(bool parsed)
{
    if (parsed)
    {
        m_audioTrackModel->clear();
        m_audioTrackModel->load(m_player->audio()->tracks());

        this->setAudioTrack(preferredAudioTrackId());
    }
}

void QEXTQmlVLCPlayer::mediaPlayerVout(int)
{
    m_subtitleTrackModel->clear();
    m_subtitleTrackModel->load(m_player->video()->subtitles());

    this->setSubtitleTrack(preferredSubtitleTrackId());

    m_videoTrackModel->clear();
    m_videoTrackModel->load(m_player->video()->tracks());

    this->setVideoTrack(m_player->video()->track());
}

void QEXTQmlVLCPlayer::openInternal()
{
    if (m_autoplay)
    {
        m_player->open(m_media);
    }
    else
    {
        m_player->openOnly(m_media);
    }
}

int QEXTQmlVLCPlayer::preferredAudioTrackId()
{
    int currentTrackId = m_player->audio()->track();
    if (m_audioTrackModel->count() && m_audioPreferredLanguages.count())
    {
        bool found = false;
        for (int j = 0; !found && j < m_audioPreferredLanguages.count(); j++)
        {
            for (int i = 0; !found && i < m_audioTrackModel->count(); i++)
            {
                QString trackTitle = m_audioTrackModel->data(i, QEXTVLCTrackModel::TitleRole).toString();
                if (trackTitle.contains(m_audioPreferredLanguages.at(j)))
                {
                    currentTrackId = m_audioTrackModel->data(i, QEXTVLCTrackModel::IdRole).toInt();
                    found = true;
                }
            }
        }
    }

    return currentTrackId;
}

int QEXTQmlVLCPlayer::preferredSubtitleTrackId()
{
    int currentTrackId = m_player->video()->subtitle();
    if (m_subtitleTrackModel->count())
    {
        bool found = false;
        for (int j = 0; !found && j < m_subtitlePreferredLanguages.count(); j++)
        {
            for (int i = 0; !found && i < m_subtitleTrackModel->count(); i++)
            {
                QString trackTitle = m_subtitleTrackModel->data(i, QEXTVLCTrackModel::TitleRole).toString();
                if (trackTitle.contains(m_subtitlePreferredLanguages.at(j)))
                {
                    currentTrackId = m_subtitleTrackModel->data(i, QEXTVLCTrackModel::IdRole).toInt();
                    found = true;
                }
            }
        }
    }

    return currentTrackId;
}
