/*************************************************************************************
*
* Library: QEXT
*
* Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
*
* License: MIT License
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*************************************************************************************/

#ifndef _QEXTQMLVLCPLAYER_H
#define _QEXTQMLVLCPLAYER_H

#include <QtCore/QUrl>

#include <qextVLC.h>

class QEXTVLCInstance;
class QEXTVLCMedia;
class QEXTVLCMediaPlayer;
class QEXTVLCTrackModel;

#include <qextQmlVLCSource.h>

/*!
    \class QEXTQmlVLCPlayer qextQmlVLCPlayer.h
    \ingroup QEXTQmlVLC
    \brief QML player

    A QML media player that can play multimedia files inside QML interface.
    You need QEXTQmlVLCVideoOutput to display video.

    \see QEXTQmlVLCVideoOutput
    \since QEXT 0.11.1
 */
class QEXTQmlVLCPlayer : public QEXTQmlVLCSource
{
    Q_OBJECT

    Q_PROPERTY(bool autoplay READ autoplay WRITE setAutoplay NOTIFY autoplayChanged)
    Q_PROPERTY(int deinterlacing READ deinterlacing WRITE setDeinterlacing NOTIFY deinterlacingChanged)
    Q_PROPERTY(qint64 length READ length NOTIFY lengthChanged)
    Q_PROPERTY(int logLevel READ logLevel WRITE setLogLevel NOTIFY logLevelChanged)
    Q_PROPERTY(float position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(bool seekable READ seekable NOTIFY seekableChanged)
    Q_PROPERTY(int state READ state NOTIFY stateChanged)
    Q_PROPERTY(qint64 time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(QEXTVLCTrackModel *audioTrackModel READ audioTrackModel CONSTANT)
    Q_PROPERTY(int audioTrack READ audioTrack WRITE setAudioTrack NOTIFY audioTrackChanged)
    Q_PROPERTY(QStringList audioPreferredLanguages READ audioPreferredLanguages WRITE setAudioPreferredLanguages NOTIFY audioPreferredLanguagesChanged)
    Q_PROPERTY(QEXTVLCTrackModel *subtitleTrackModel READ subtitleTrackModel CONSTANT)
    Q_PROPERTY(int subtitleTrack READ subtitleTrack WRITE setSubtitleTrack NOTIFY subtitleTrackChanged)
    Q_PROPERTY(QStringList subtitlePreferredLanguages READ subtitlePreferredLanguages WRITE setSubtitlePreferredLanguages NOTIFY subtitlePreferredLanguagesChanged)
    Q_PROPERTY(QEXTVLCTrackModel *videoTrackModel READ videoTrackModel CONSTANT)
    Q_PROPERTY(int videoTrack READ videoTrack WRITE setVideoTrack NOTIFY videoTrackChanged)

public:
    /*!
        \brief QEXTQmlVLCPlayer constructor
        \param parent parent object
     */
    explicit QEXTQmlVLCPlayer(QObject *parent = 0);
    ~QEXTQmlVLCPlayer();

    /*!
        \brief Pause current playback

        Invokable from QML.
     */
    Q_INVOKABLE void pause();

    /*!
        \brief Play current playback

        Invokable from QML.
     */
    Q_INVOKABLE void play();

    /*!
        \brief Stop current playback

        Invokable from QML.
     */
    Q_INVOKABLE void stop();

    /*!
        \brief Get current autoplay setting
        \return current autoplay setting

        Used as property in QML.
     */
    bool autoplay() const;

    /*!
        \brief Set autoplay setting
        \param autoplay new autoplay setting

        Used as property in QML.
     */
    void setAutoplay(bool autoplay);

    /*!
        \brief Get current deinterlacing mode
        \return current deinterlacing mode

        Used as property in QML.
     */
    int deinterlacing() const;

    /*!
        \brief Set deinterlacing mode
        \param deinterlacing new deinterlacing mode

        Used as property in QML.
     */
    void setDeinterlacing(int deinterlacing);

    /*!
        \brief Get current media length
        \return current media length

        Used as property in QML.
     */
    qint64 length() const;

    /*!
        \brief Get current log level
        \return current log level

        Used as property in QML.
     */
    int logLevel() const;

    /*!
        \brief Set log level
        \param level log level

        Used as property in QML.
     */
    void setLogLevel(int level);

    /*!
        \brief Get current media position
        \return current media position from 0 to 1

        Used as property in QML.
     */
    float position() const;

    /*!
        \brief Set current media position
        \param position media position from 0 to 1

        Used as property in QML.
     */
    void setPosition(float position);

    /*!
        \brief Get current seekable status
        \return current seekable status

        Used as property in QML.
     */
    bool seekable() const;

    /*!
        \brief Get current state
        \return current state

        Used as property in QML.
     */
    int state() const;

    /*!
        \brief Get current media time
        \return current media time

        Used as property in QML.
     */
    qint64 time() const;

    /*!
        \brief Set current media time
        \param time current media time

        Used as property in QML.
     */
    void setTime(qint64 time);

    /*!
        \brief Get current media URL
        \return current media URL

        Used as property in QML.
     */
    QUrl url() const;

    /*!
        \brief Set media URL
        \param url new media URL

        Used as property in QML.
     */
    void setUrl(const QUrl &url);

    /*!
        \brief Get current volume
        \return current volume (int)

        Used as property in QML.
     */
    int volume() const;

    /*!
        \brief Set volume
        \param volume new volume

        Used as property in QML.
     */
    void setVolume(int volume);

    /*!
        \brief Get audio track model
        \return audio track model poiner

        Used as property in QML.
     */
    QEXTVLCTrackModel *audioTrackModel() const;

    /*!
        \brief Get current audio track
        \return the id of current audio track, or -1 if none

        Used as property in QML.
     */
    int audioTrack() const;

    /*!
        \brief Set current audio track
        \param audioTrack new audio track

        Used as property in QML.
     */
    void setAudioTrack(int audioTrack);

    /*!
        \brief Get preferred audio languages
        \return preferred languages

        Used as property in QML.
     */
    QStringList audioPreferredLanguages() const;

    /*!
        \brief Set preferred audio language
        \param audioPreferredLanguages preferred languages

        Used as property in QML.
     */
    void setAudioPreferredLanguages(const QStringList &audioPreferredLanguages);

    /*!
        \brief Get subtitle track model
        \return subtitle track model poiner

        Used as property in QML.
     */
    QEXTVLCTrackModel *subtitleTrackModel() const;

    /*!
        \brief Get current subtitle track
        \return the id of current subtitle track, or -1 if none

        Used as property in QML.
     */
    int subtitleTrack() const;

    /*!
        \brief Set current subtitle track
        \param subtitleTrack new subtitle track

        Used as property in QML.
     */
    void setSubtitleTrack(int subtitleTrack);

    /*!
        \brief Get preferred subtitle languages
        \return preferred languages

        Used as property in QML.
     */
    QStringList subtitlePreferredLanguages() const;

    /*!
        \brief Set preferred subtitle languages
        \param subtitlePreferredLanguages preferred languages, empty if disabled

        Used as property in QML.
     */
    void setSubtitlePreferredLanguages(const QStringList &subtitlePreferredLanguages);

    /*!
        \brief Get video track model
        \return video track model poiner

        Used as property in QML.
     */
    QEXTVLCTrackModel *videoTrackModel() const;

    /*!
        \brief Get current video track
        \return the id of current video track, or -1 if none

        Used as property in QML.
     */
    int videoTrack() const;

    /*!
        \brief Set current video track
        \param videoTrack new video track

        Used as property in QML.
     */
    void setVideoTrack(int videoTrack);

signals:
    /*!
        \brief Autoplay changed signal
    */
    void autoplayChanged();

    /*!
        \brief Deinterlacing changed signal
    */
    void deinterlacingChanged();

    /*!
        \brief Length changed signal
    */
    void lengthChanged();

    /*!
        \brief Log level changed signal
    */
    void logLevelChanged();

    /*!
        \brief Position changed signal
    */
    void positionChanged();

    /*!
        \brief Seekable changed signal
    */
    void seekableChanged();

    /*!
        \brief State changed signal
    */
    void stateChanged();

    /*!
        \brief Time changed signal
    */
    void timeChanged();

    /*!
        \brief URL changed signal
    */
    void urlChanged();

    /*!
        \brief Volume changed signal
    */
    void volumeChanged();

    /*!
        \brief Audio track changed signal
    */
    void audioTrackChanged();

    /*!
        \brief Audio preferred languages changed signal
    */
    void audioPreferredLanguagesChanged();

    /*!
        \brief Subtitle track changed signal
    */
    void subtitleTrackChanged();

    /*!
        \brief Subtitle preferred languages changed signal
    */
    void subtitlePreferredLanguagesChanged();

    /*!
        \brief Video track changed signal
    */
    void videoTrackChanged();

private slots:
    void mediaParsed(bool parsed);
    void mediaPlayerVout(int count);

private:
    void openInternal();
    int preferredAudioTrackId();
    int preferredSubtitleTrackId();

    QEXTVLCInstance *m_instance;
    QEXTVLCMedia *m_media;
    QEXTVLCMediaPlayer *m_player;

    bool m_autoplay;
    QEXTVLC::DeinterlacingType m_deinterlacing;

    QEXTVLCTrackModel *m_audioTrackModel;
    QEXTVLCTrackModel *m_subtitleTrackModel;
    QEXTVLCTrackModel *m_videoTrackModel;

    QStringList m_audioPreferredLanguages;
    QStringList m_subtitlePreferredLanguages;
};

#endif // _QEXTQMLVLCPLAYER_H
