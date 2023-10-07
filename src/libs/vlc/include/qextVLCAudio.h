/*************************************************************************************
*
* Library: QExt
*
* Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
* Copyright (C) 2015 Tadej Novak <tadej@tano.si>
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

#ifndef _QEXTVLCAUDIO_H
#define _QEXTVLCAUDIO_H

#include <qextVLC.h>
#include <qextVLCGlobal.h>

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QMap>

class QEXTVLCMediaPlayer;

struct libvlc_media_player_t;

/*!
    \class QEXTVLCAudio qextVLCAudio.h
    \ingroup QEXTVLC
    \brief Audio controls

    A group of audio controls functions.
*/
class QEXT_VLC_API QEXTVLCAudio : public QObject
{
    Q_OBJECT
    friend class QEXTVLCAudioCallbackHelper;

public:
    /*!
        \brief QEXTVLCAudio constructor.

        This constructor creates a new audio manager.

        \param player media player (QEXTVLCMediaPlayer *)
    */
    explicit QEXTVLCAudio(QEXTVLCMediaPlayer *player);

    /*!
        \brief QEXTVLCAudio destructor
    */
    ~QEXTVLCAudio();

    /*!
        \brief Get current mute state.
        \return current mute state (const bool)
    */
    bool getMute() const;

public slots:
    /*!
        \brief Set current audio level.
        \param volume new audio level (int)
    */
    void setVolume(int volume);

    /*!
        \brief Set current audio track.
        \param track new audio track (int)
    */
    void setTrack(int track);

    /*!
        \brief Toggle mute state.
        \return new mute state (const bool)
    */
    bool toggleMute() const;

    /*!
        \brief Set audio channel.
        \param channel new audio channel
    */
    void setChannel(QEXTVLC::AudioChannelType channel);

    /*!
        \brief Set mute state.
        \param mute mute state (bool)
    */
    void setMute(bool mute) const;

public:
    /*!
        \brief Get current audio track.
        \return the number of current audio track, or -1 if none (const int)
    */
    int track() const;

    /*!
        \brief Get number of available audio tracks.
        \return the number of available audio tracks, or -1 if unavailable (const int)
    */
    int trackCount() const;

    /*!
        \brief Get the description of available audio tracks.
        \return list with description of available audio tracks (const QStringList)
    */
    QStringList trackDescription() const;

    /*!
        \brief Get the ids of available audio tracks.
        \return list with ids of available audio tracks (const QList<int>)
    */
    QList<int> trackIds() const;

    /*!
        \brief Get available audio tracks.
        \return dictionary with available audio tracks (const QMap<int, QString>)
        \since QExt 0.11.1
    */
    QMap<int, QString> tracks() const;

    /*!
        \brief Get current audio level.
        \return current audio level, -1 if media is not playing (const int)
    */
    int volume() const;

    /*!
        \brief Get audio channel.
        \return current audio channel, -1 if error
    */
    QEXTVLC::AudioChannelType channel() const;

signals:
    /*!
        \brief Signal sent when volume has changed.
        \param volume new volume (float)
    */
    void volumeChangedF(float volume);

    /*!
        \brief Signal sent when volume has changed.
        \param volume new volume (int)
    */
    void volumeChanged(int volume);

    /*!
        \brief Signal sent when mute has changed.
        \param mute new mute state (bool)
    */
    void muteChanged(bool mute);

private:
    libvlc_media_player_t *_vlcMediaPlayer;
};

#endif // _QEXTVLCAUDIO_H
