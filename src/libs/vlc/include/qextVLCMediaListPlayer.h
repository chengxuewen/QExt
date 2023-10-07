/*************************************************************************************
*
* Library: QExt
*
* Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
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

#ifndef _QEXTVLCMEDIALISTPLAYER_H
#define _QEXTVLCMEDIALISTPLAYER_H

#include <qextVLC.h>
#include <qextVLCGlobal.h>

#include <QtCore/QObject>
#include <QtCore/QString>

class QEXTVLCInstance;
class QEXTVLCMediaList;
class QEXTVLCMediaPlayer;

struct libvlc_event_t;
struct libvlc_event_manager_t;
struct libvlc_media_t;
struct libvlc_media_list_player_t;

/*!
    \class QEXTVLCMediaListPlayer qextVLCMediaListPlayer.h
    \ingroup QEXTVLC
    \brief Media List Player

    A basic MediaListPlayer manager for VLC-Qt library.
    It provides internal playlist support.
    Requires a valid QEXTVLCMediaPlayer.
*/
class QEXT_VLC_API QEXTVLCMediaListPlayer : public QObject
{
    Q_OBJECT
public:
    /*!
        \brief QEXTVLCMediaListPlayer constructor.

        Create QEXTVLCMediaListPlayer without new core.

        \param instance instance object
    */
    explicit QEXTVLCMediaListPlayer(QEXTVLCInstance *instance);

    /*!
        \brief QEXTVLCMediaListPlayer constructor.

        Create QEXTVLCMediaListPlayer with specific QEXTVLCMediaPlayer core.

        \param player player object
        \param instance instance object
    */
    explicit QEXTVLCMediaListPlayer(QEXTVLCMediaPlayer *player, QEXTVLCInstance *instance);

    /*!
        QEXTVLCMediaListPlayer destructor
    */
    ~QEXTVLCMediaListPlayer();

    /*!
        \brief Returns libvlc media list player object.
        \return libvlc media list player (libvlc_media_list_player_t *)
    */
    libvlc_media_list_player_t *core();

    /*!
        \brief Get current media list
        \return current media list (QEXTVLCMediaList *)
    */
    QEXTVLCMediaList *currentMediaList();

    /*!
        \brief Get media player core
        \return media player core (QEXTVLCMediaPlayer *)
    */
    QEXTVLCMediaPlayer *mediaPlayer();

    /*!
        \brief Get playback mode
        \return playback mode
    */
    QEXTVLC::PlaybackMode playbackMode() const;

    /*!
        \brief Set media list to play
        \param list media list object (QEXTVLCMediaList *)
    */
    void setMediaList(QEXTVLCMediaList *list);

    /*!
        \brief Set playback mode
        \param mode playback mode
    */
    void setPlaybackMode(const QEXTVLC::PlaybackMode &mode);

public slots:
    /*!
        \brief Starts playing item at specific position.
        \param index item position
    */
    void itemAt(int index);

    /*!
        \brief Starts playing next item in the list.
    */
    void next();

    /*!
        \brief Starts playing media list.
    */
    void play();

    /*!
        \brief Starts playing previous item in the list.
    */
    void previous();

    /*!
        \brief Stops playing
    */
    void stop();

signals:
    /*!
        \brief Signal sent when played
    */
    void played();

    /*!
        \brief Signal sent on next item set
        \param media next media item
        \since QExt 0.11.1
    */
    void nextItemSet(QEXTVLCMedia *media);

    /*!
        \brief Signal sent on next item set
        \param media next media item
    */
    void nextItemSet(libvlc_media_t *media);

    /*!
        \brief Signal sent when stopped
    */
    void stopped();

private:
    static void libvlc_callback(const libvlc_event_t *event, void *data);

    void createCoreConnections();
    void removeCoreConnections();

    libvlc_media_list_player_t *m_vlcMediaListPlayer;
    libvlc_event_manager_t *m_vlcEvents;

    QEXTVLCMediaList *m_list;
    QEXTVLCMediaPlayer *m_player;

    QEXTVLC::PlaybackMode m_mode;
};

#endif // _QEXTVLCMEDIALISTPLAYER_H
