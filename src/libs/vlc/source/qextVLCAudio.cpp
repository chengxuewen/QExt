/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2015 Tadej Novak <tadej@tano.si>
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

#include <vlc/vlc.h>
#include <vlc_common.h>
#include <vlc_variables.h>

#include "qextVLCAudio.h"
#include "qextVLCError.h"
#include <qextVLCMediaPlayer.h>

/*!
    \private
*/
class QEXTVLCAudioCallbackHelper
{
public:
    static int volumeCallback(vlc_object_t *obj,
                              const char *name,
                              vlc_value_t oldVal,
                              vlc_value_t newVal,
                              void *data)
    {
        Q_UNUSED(obj)
        Q_UNUSED(name)
        Q_UNUSED(oldVal)

        QEXTVLCAudio *core = static_cast<QEXTVLCAudio *>(data);
        emit core->volumeChangedF(newVal.f_float);
        int vol = newVal.f_float < 0 ? -1 : qRound(newVal.f_float * 100.f);
        emit core->volumeChanged(vol);
        return VLC_SUCCESS;
    }

    static int muteCallback(vlc_object_t *obj,
                            const char *name,
                            vlc_value_t oldVal,
                            vlc_value_t newVal,
                            void *data)
    {
        Q_UNUSED(obj);
        Q_UNUSED(name);
        Q_UNUSED(oldVal);

        QEXTVLCAudio *core = static_cast<QEXTVLCAudio *>(data);
        emit core->muteChanged(newVal.b_bool);
        return VLC_SUCCESS;
    }
};

QEXTVLCAudio::QEXTVLCAudio(QEXTVLCMediaPlayer *player)
    : QObject(player),
      _vlcMediaPlayer(player->core())
{
    var_AddCallback((vlc_object_t *)_vlcMediaPlayer, "volume", QEXTVLCAudioCallbackHelper::volumeCallback, this);
    var_AddCallback((vlc_object_t *)_vlcMediaPlayer, "mute", QEXTVLCAudioCallbackHelper::muteCallback, this);
}

QEXTVLCAudio::~QEXTVLCAudio()
{
    var_DelCallback((vlc_object_t *)_vlcMediaPlayer, "volume", QEXTVLCAudioCallbackHelper::volumeCallback, this);
    var_DelCallback((vlc_object_t *)_vlcMediaPlayer, "mute", QEXTVLCAudioCallbackHelper::muteCallback, this);
}

bool QEXTVLCAudio::getMute() const
{
    bool mute = false;
    if (_vlcMediaPlayer) {
        mute = libvlc_audio_get_mute(_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();
    }

    return mute;
}

void QEXTVLCAudio::setVolume(int volume)
{
    if (_vlcMediaPlayer) {
        // Don't change if volume is the same
        if (volume != QEXTVLCAudio::volume()) {
            libvlc_audio_set_volume(_vlcMediaPlayer, volume);
            QEXTVLCError::showErrMsg();
        }
    }
}

void QEXTVLCAudio::setTrack(int track)
{
    if (_vlcMediaPlayer) {
        libvlc_audio_set_track(_vlcMediaPlayer, track);
        QEXTVLCError::showErrMsg();
    }
}

bool QEXTVLCAudio::toggleMute() const
{
    if (_vlcMediaPlayer) {
        libvlc_audio_toggle_mute(_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();
    }

    return getMute();
}

void QEXTVLCAudio::setMute(bool mute) const
{
    if (_vlcMediaPlayer && mute != getMute()) {
        libvlc_audio_set_mute(_vlcMediaPlayer, mute);
        QEXTVLCError::showErrMsg();
    }
}

int QEXTVLCAudio::track() const
{
    int track = -1;
    if (_vlcMediaPlayer) {
        track = libvlc_audio_get_track(_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();
    }

    return track;
}

int QEXTVLCAudio::trackCount() const
{
    int count = -1;
    if (_vlcMediaPlayer) {
        count = libvlc_audio_get_track_count(_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();
    }

    return count;
}

QStringList QEXTVLCAudio::trackDescription() const
{
    QStringList descriptions;

    if (_vlcMediaPlayer) {
        libvlc_track_description_t *desc;
        desc = libvlc_audio_get_track_description(_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();

        descriptions << QString().fromUtf8(desc->psz_name);
        if (trackCount() > 1) {
            for (int i = 1; i < trackCount(); i++) {
                desc = desc->p_next;
                descriptions << QString().fromUtf8(desc->psz_name);
            }
        }
    }

    return descriptions;
}

QList<int> QEXTVLCAudio::trackIds() const
{
    QList<int> ids;

    if (_vlcMediaPlayer) {
        libvlc_track_description_t *desc;
        desc = libvlc_audio_get_track_description(_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();

        ids << desc->i_id;
        if (trackCount() > 1) {
            for (int i = 1; i < trackCount(); i++) {
                desc = desc->p_next;
                ids << desc->i_id;
            }
        }
    }

    return ids;
}

QMap<int, QString> QEXTVLCAudio::tracks() const
{
    QMap<int, QString> tracks;

    if (_vlcMediaPlayer) {
        libvlc_track_description_t *desc, *first;
        first = desc = libvlc_audio_get_track_description(_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();

        if (desc != NULL) {
            tracks.insert(desc->i_id, QString().fromUtf8(desc->psz_name));
            if (trackCount() > 1) {
                for (int i = 1; i < trackCount(); i++) {
                    desc = desc->p_next;
                    tracks.insert(desc->i_id, QString().fromUtf8(desc->psz_name));
                }
            }
            libvlc_track_description_list_release(first);
        }
    }

    return tracks;
}

int QEXTVLCAudio::volume() const
{
    int volume = -1;
    if (_vlcMediaPlayer) {
        volume = libvlc_audio_get_volume(_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();
    }

    return volume;
}

QEXTVLC::AudioChannelType QEXTVLCAudio::channel() const
{
    QEXTVLC::AudioChannelType channel = QEXTVLC::AudioChannel_Error;
    if (_vlcMediaPlayer) {
        channel = QEXTVLC::AudioChannelType(libvlc_audio_get_channel(_vlcMediaPlayer));
        QEXTVLCError::showErrMsg();
    }

    return channel;
}

void QEXTVLCAudio::setChannel(QEXTVLC::AudioChannelType channel)
{
    if (_vlcMediaPlayer) {
        // Don't change if channel is the same
        if (channel != QEXTVLCAudio::channel()) {
            libvlc_audio_set_channel(_vlcMediaPlayer, channel);
            QEXTVLCError::showErrMsg();
        }
    }
}
