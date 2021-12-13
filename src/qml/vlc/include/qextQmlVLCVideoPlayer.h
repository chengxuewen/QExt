/*************************************************************************************
*
* Library: QEXT
*
* Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
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

#ifndef _QEXTQMLVLCVIDEOPLAYER_H
#define _QEXTQMLVLCVIDEOPLAYER_H

#include <qextQmlVLCVideoObject.h>
#include <qextQmlVLCGlobal.h>
#include <qextVLCTrackModel.h>

#include <QtQuick/QQuickItem>

class QEXTVLCAudio;
class QEXTVLCInstance;
class QEXTVLCMedia;
class QEXTVLCMediaPlayer;
class QEXTVLCVideo;

/*!
    \class QEXTQmlVLCVideoPlayer qextQmlVLCVideoPlayer.h
    \ingroup QEXTQmlVLC
    \brief QML video player (deprecated)

    A simple QML video player that can be used standalone and directly inside QML.

    @deprecated Deprecated since QEXT 0.11.1, will be removed in 2.0
 */
class Q_DECL_DEPRECATED QEXT_QMLVLC_API QEXTQmlVLCVideoPlayer : public QEXTQmlVLCVideoObject
{
    Q_OBJECT

    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(QString aspectRatio READ aspectRatio WRITE setAspectRatio NOTIFY aspectRatioChanged)
    Q_PROPERTY(QString cropRatio READ cropRatio WRITE setCropRatio NOTIFY cropRatioChanged)
    Q_PROPERTY(QString deinterlacing READ deinterlacing WRITE setDeinterlacing NOTIFY deinterlacingChanged)
    Q_PROPERTY(QUrl url READ url WRITE setUrl)
    Q_PROPERTY(bool autoplay READ autoplay WRITE setAutoplay)
    Q_PROPERTY(int state READ state NOTIFY stateChanged)
    Q_PROPERTY(bool seekable READ seekable NOTIFY seekableChanged)
    Q_PROPERTY(int length READ length NOTIFY lengthChanged)
    Q_PROPERTY(int time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(float position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(int audioTrack READ audioTrack WRITE setAudioTrack NOTIFY audioTrackChanged)
    Q_PROPERTY(QEXTVLCTrackModel *audioTrackModel READ audioTrackModel CONSTANT)
    Q_PROPERTY(QStringList audioPreferredLanguages READ audioPreferredLanguages WRITE setAudioPreferredLanguages NOTIFY audioPreferredLanguagesChanged)
    Q_PROPERTY(int subtitleTrack READ subtitleTrack WRITE setSubtitleTrack NOTIFY subtitleTrackChanged)
    Q_PROPERTY(QEXTVLCTrackModel *subtitleTrackModel READ subtitleTrackModel CONSTANT)
    Q_PROPERTY(QStringList subtitlePreferredLanguages READ subtitlePreferredLanguages WRITE setSubtitlePreferredLanguages NOTIFY subtitlePreferredLanguagesChanged)
    Q_PROPERTY(int videoTrack READ videoTrack WRITE setVideoTrack NOTIFY videoTrackChanged)
    Q_PROPERTY(QEXTVLCTrackModel *videoTrackModel READ videoTrackModel CONSTANT)

public:
    /*!
        \brief QEXTQmlVLCVideoPlayer constructor.
        \param parent parent item (QQuickItem *)
     */
    explicit QEXTQmlVLCVideoPlayer(QQuickItem *parent = 0);

    /*!
        QEXTVLCMediaPlayer destructor
     */
    ~QEXTQmlVLCVideoPlayer();


    /*!
        \brief Register QML plugin as VLCQt.QEXTVLCVideoPlayer

        Include into QML file as
        import VLCQt VERSION_MAJOR.VERSION_MINOR

        Object name: QEXTVLCVideoPlayer
     */
    static void registerPlugin();

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
        \brief Get current aspect ratio
        \return current aspect ratio

        Used as property in QML.
     */
    QString aspectRatio() const;

    /*!
        \brief Set aspect ratio
        \param aspectRatio new aspect ratio

        Used as property in QML.
     */
    void setAspectRatio(const QString &aspectRatio);

    /*!
        \brief Get current crop ratio
        \return current crop ratio

        Used as property in QML.
     */
    QString cropRatio() const;

    /*!
        \brief Set crop ratio
        \param cropRatio new crop ratio

        Used as property in QML.
     */
    void setCropRatio(const QString &cropRatio);

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
        \brief Get current deinterlacing() mode
        \return current deinterlacing mode

        Used as property in QML.
     */
    QString deinterlacing() const;

    /*!
        \brief Set deinterlacing mode
        \param deinterlacing new deinterlacing mode

        Used as property in QML.
     */
    void setDeinterlacing(const QString &deinterlacing);

    /*!
        \brief Get current state
        \return current state

        Used as property in QML.
     */
    int state() const;

    /*!
        \brief Get current seekable status
        \return current seekable status

        Used as property in QML.
     */
    bool seekable() const;

    /*!
        \brief Get current media length
        \return current media length

        Used as property in QML.
     */
    int length() const;

    /*!
        \brief Get current media time
        \return current media time

        Used as property in QML.
     */
    int time() const;

    /*!
        \brief Set current media time
        \param time current media time

        Used as property in QML.
     */
    void setTime(int time);

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
        \brief Get current audio track.
        \return the id of current audio track, or -1 if none (const int)

        Used as property in QML.

        \since QEXT 0.11.1
     */
    int audioTrack() const;

    /*!
        \brief Set current audio track.
        \param audioTrack new audio track (int)

        Used as property in QML.

        \since QEXT 0.11.1
     */
    void setAudioTrack(int audioTrack);

    /*!
        \brief Get audio track model
        \return audio track model poiner

        Used as property in QML.

        \since QEXT 0.11.1
     */
    QEXTVLCTrackModel *audioTrackModel() const;

    /*!
        \brief Get preferred audio languages
        \return preferred languages

        Used as property in QML.

        \since QEXT 0.11.1
     */
    QStringList audioPreferredLanguages() const;

    /*!
        \brief Set preferred audio language
        \param audioPreferredLanguages preferred languages

        Used as property in QML.

        \since QEXT 0.11.1
     */
    void setAudioPreferredLanguages(const QStringList &audioPreferredLanguages);

    /*!
        \brief Get current subtitle track.
        \return the id of current subtitle track, or -1 if none (const int)

        Used as property in QML.

        \since QEXT 0.11.1
     */
    int subtitleTrack() const;

    /*!
        \brief Set current subtitle track.
        \param subtitleTrack new subtitle track (int)

        Used as property in QML.

        \since QEXT 0.11.1
     */
    void setSubtitleTrack(int subtitleTrack);

    /*!
        \brief Get subtitle track model
        \return subtitle track model poiner

        Used as property in QML.

        \since QEXT 0.11.1
     */
    QEXTVLCTrackModel *subtitleTrackModel() const;

    /*!
        \brief Get preferred subtitle languages
        \return preferred languages

        Used as property in QML.

        \since QEXT 0.11.1
     */
    QStringList subtitlePreferredLanguages() const;

    /*!
        \brief Set preferred subtitle languages
        \param subtitlePreferredLanguages preferred languages, empty if disabled

        Used as property in QML.

        \since QEXT 0.11.1
     */
    void setSubtitlePreferredLanguages(const QStringList &subtitlePreferredLanguages);

    /*!
        \brief Get current video track.
        \return the id of current video track, or -1 if none (const int)

        Used as property in QML.

        \since QEXT 0.11.1
     */
    int videoTrack() const;

    /*!
        \brief Set current video track.
        \param videoTrack new video track (int)

        Used as property in QML.

        \since QEXT 0.11.1
     */
    void setVideoTrack(int videoTrack);

    /*!
        \brief Get video track model
        \return video track model poiner

        Used as property in QML.

        \since QEXT 0.11.1
     */
    QEXTVLCTrackModel *videoTrackModel() const;

signals:
    /*!
        \brief Volume changed signal
    */
    void volumeChanged();

    /*!
        \brief Aspect ratio changed signal
        \since QEXT 0.11.1
    */
    void aspectRatioChanged();

    /*!
        \brief Crop ratio changed signal
        \since QEXT 0.11.1
    */
    void cropRatioChanged();

    /*!
        \brief Deinterlacing changed signal
        \since QEXT 0.11.1
    */
    void deinterlacingChanged();

    /*!
        \brief State changed signal
    */
    void stateChanged();

    /*!
        \brief Seekable status changed signal
    */
    void seekableChanged();

    /*!
        \brief Length changed signal
    */
    void lengthChanged();

    /*!
        \brief Time changed signal
    */
    void timeChanged();

    /*!
        \brief Position changed signal
    */
    void positionChanged();

    /*!
        \brief Audio track changed signal
        \since QEXT 0.11.1
    */
    void audioTrackChanged();

    /*!
        \brief Audio preferred languages changed signal
        \since QEXT 0.11.1
    */
    void audioPreferredLanguagesChanged();

    /*!
        \brief Subtitle track changed signal
        \since QEXT 0.11.1
    */
    void subtitleTrackChanged();

    /*!
        \brief Subtitle preferred languages changed signal
        \since QEXT 0.11.1
    */
    void subtitlePreferredLanguagesChanged();

    /*!
        \brief Video track changed signal
        \since QEXT 0.11.1
    */
    void videoTrackChanged();

private slots:
    void seekableChangedPrivate(bool);
    void mediaParsed(bool);
    void mediaPlayerVout(int);
private:
    void openInternal();
    int preferredAudioTrackId();
    int preferredSubtitleTrackId();

    QEXTVLCInstance *m_instance;
    QEXTVLCMedia *m_media;

    QEXTVLCAudio *m_audioManager;
    QEXTVLCVideo *m_videoManager;

    QEXTVLC::DeinterlacingType m_deinterlacing;

    bool m_hasMedia;
    bool m_autoplay;
    bool m_seekable;

    QEXTVLCTrackModel *m_audioTrackModel;
    QEXTVLCTrackModel *m_subtitleTrackModel;
    QEXTVLCTrackModel *m_videoTrackModel;

    QStringList m_audioPreferredLanguages;
    QStringList m_subtitlePreferredLanguages;
};

#endif // _QEXTQMLVLCVIDEOPLAYER_H
