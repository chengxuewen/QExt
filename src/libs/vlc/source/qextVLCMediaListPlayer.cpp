/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include <QtCore/QDebug>

#include <qextVLCHeaders.h>

#include "qextVLCError.h"
#include "qextVLCInstance.h"
#include "qextVLCMediaList.h"
#include "qextVLCMediaListPlayer.h"
#include <qextVLCMediaPlayer.h>

QEXTVLCMediaListPlayer::QEXTVLCMediaListPlayer(QEXTVLCInstance *instance)
    : QObject(instance),
      m_list(0),
      m_mode(QEXTVLC::Playback_Default)
{
    m_player = new QEXTVLCMediaPlayer(instance);

    m_vlcMediaListPlayer = libvlc_media_list_player_new(instance->core());
    m_vlcEvents = libvlc_media_list_player_event_manager(m_vlcMediaListPlayer);
    libvlc_media_list_player_set_media_player(m_vlcMediaListPlayer, m_player->core());

    createCoreConnections();

    QEXTVLCError::showErrMsg();
}

QEXTVLCMediaListPlayer::QEXTVLCMediaListPlayer(QEXTVLCMediaPlayer *player,
                                       QEXTVLCInstance *instance)
    : QObject(instance),
      m_list(0),
      m_mode(QEXTVLC::Playback_Default)
{
    m_player = player;

    m_vlcMediaListPlayer = libvlc_media_list_player_new(instance->core());
    m_vlcEvents = libvlc_media_list_player_event_manager(m_vlcMediaListPlayer);
    libvlc_media_list_player_set_media_player(m_vlcMediaListPlayer, m_player->core());

    createCoreConnections();

    QEXTVLCError::showErrMsg();
}

QEXTVLCMediaListPlayer::~QEXTVLCMediaListPlayer()
{
    removeCoreConnections();

    libvlc_media_list_player_release(m_vlcMediaListPlayer);

    QEXTVLCError::showErrMsg();
}

libvlc_media_list_player_t *QEXTVLCMediaListPlayer::core()
{
    return m_vlcMediaListPlayer;
}

QEXTVLCMediaList *QEXTVLCMediaListPlayer::currentMediaList()
{
    return m_list;
}

QEXTVLCMediaPlayer *QEXTVLCMediaListPlayer::mediaPlayer()
{
    return m_player;
}

void QEXTVLCMediaListPlayer::createCoreConnections()
{
    QList<libvlc_event_e> list;
    list << libvlc_MediaListPlayerPlayed
         << libvlc_MediaListPlayerNextItemSet
         << libvlc_MediaListPlayerStopped;

    foreach (const libvlc_event_e &event, list)
    {
        libvlc_event_attach(m_vlcEvents, event, libvlc_callback, this);
    }
}

void QEXTVLCMediaListPlayer::removeCoreConnections()
{
    QList<libvlc_event_e> list;
    list << libvlc_MediaListPlayerPlayed
         << libvlc_MediaListPlayerNextItemSet
         << libvlc_MediaListPlayerStopped;

    foreach (const libvlc_event_e &event, list)
    {
        libvlc_event_detach(m_vlcEvents, event, libvlc_callback, this);
    }
}

void QEXTVLCMediaListPlayer::itemAt(int index)
{
    libvlc_media_list_player_play_item_at_index(m_vlcMediaListPlayer, index);

    QEXTVLCError::showErrMsg();
}

void QEXTVLCMediaListPlayer::next()
{
    libvlc_media_list_player_next(m_vlcMediaListPlayer);

    QEXTVLCError::showErrMsg();
}

void QEXTVLCMediaListPlayer::play()
{
    libvlc_media_list_player_play(m_vlcMediaListPlayer);

    QEXTVLCError::showErrMsg();
}

QEXTVLC::PlaybackMode QEXTVLCMediaListPlayer::playbackMode() const
{
    return m_mode;
}

void QEXTVLCMediaListPlayer::previous()
{
    libvlc_media_list_player_previous(m_vlcMediaListPlayer);

    QEXTVLCError::showErrMsg();
}

void QEXTVLCMediaListPlayer::stop()
{
    libvlc_media_list_player_stop(m_vlcMediaListPlayer);

    QEXTVLCError::showErrMsg();
}

void QEXTVLCMediaListPlayer::setMediaList(QEXTVLCMediaList *list)
{
    m_list = list;
    libvlc_media_list_player_set_media_list(m_vlcMediaListPlayer, list->core());

    QEXTVLCError::showErrMsg();
}

void QEXTVLCMediaListPlayer::setPlaybackMode(const QEXTVLC::PlaybackMode &mode)
{
    m_mode = mode;
    libvlc_media_list_player_set_playback_mode(m_vlcMediaListPlayer, libvlc_playback_mode_t(mode));
}

void QEXTVLCMediaListPlayer::libvlc_callback(const libvlc_event_t *event,
        void *data)
{
    QEXTVLCMediaListPlayer *core = static_cast<QEXTVLCMediaListPlayer *>(data);

    switch (event->type)
    {
        case libvlc_MediaListPlayerPlayed:
            emit core->played();
            break;
        case libvlc_MediaListPlayerNextItemSet:
            emit core->nextItemSet(event->u.media_list_player_next_item_set.item);
            emit core->nextItemSet(core->currentMediaList()->at(core->currentMediaList()->indexOf(event->u.media_list_player_next_item_set.item)));
            break;
        case libvlc_MediaListPlayerStopped:
            emit core->stopped();
            break;
        default:
            break; // LCOV_EXCL_LINE
    }
}
