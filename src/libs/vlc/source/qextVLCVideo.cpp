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

#include <vlc/vlc.h>

#include "qextVLCError.h"
#include <qextVLCMediaPlayer.h>
#include "qextVLCVideo.h"

QEXTVLCVideo::QEXTVLCVideo(QEXTVLCMediaPlayer *player)
    : QObject(player),
      m_vlcMediaPlayer(player->core()) {}

QEXTVLCVideo::~QEXTVLCVideo() {}

QEXTVLC::RatioType QEXTVLCVideo::aspectRatio() const
{
    QString ratio = "";
    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        ratio = libvlc_video_get_aspect_ratio(m_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();
    }

    return QEXTVLC::RatioType(QEXTVLC::ratio().indexOf(ratio));
}

QEXTVLC::RatioType QEXTVLCVideo::cropGeometry() const
{
    QString crop = "";
    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        crop = libvlc_video_get_crop_geometry(m_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();
    }

    return QEXTVLC::RatioType(QEXTVLC::ratio().indexOf(crop));
}

void QEXTVLCVideo::hideLogo()
{
    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        libvlc_video_set_logo_int(m_vlcMediaPlayer, libvlc_logo_enable, 0);
        QEXTVLCError::showErrMsg();
    }
}

void QEXTVLCVideo::hideMarquee()
{
    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        libvlc_video_set_marquee_int(m_vlcMediaPlayer, libvlc_marquee_Enable, 0);
        QEXTVLCError::showErrMsg();
    }
}

QEXTVLC::ScaleType QEXTVLCVideo::scale() const
{
    float scale = 0;
    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        scale = libvlc_video_get_scale(m_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();
    }

    return QEXTVLC::ScaleType(QEXTVLC::scale().indexOf(scale));
}

void QEXTVLCVideo::setAspectRatio(const QEXTVLC::RatioType &ratio)
{
    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        QString ratioOut = ratio == QEXTVLC::Ratio_Ignore ? "" : QEXTVLC::ratio()[ratio];
        libvlc_video_set_aspect_ratio(m_vlcMediaPlayer, ratioOut.toUtf8().data());
        QEXTVLCError::showErrMsg();
    }
}

void QEXTVLCVideo::setCropGeometry(const QEXTVLC::RatioType &ratio)
{
    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        QString ratioOut = ratio == QEXTVLC::Ratio_Ignore ? "" : QEXTVLC::ratio()[ratio];
        libvlc_video_set_crop_geometry(m_vlcMediaPlayer, ratioOut.toUtf8().data());
        QEXTVLCError::showErrMsg();
    }
}

void QEXTVLCVideo::setDeinterlace(const QEXTVLC::DeinterlacingType &filter)
{
    if (m_vlcMediaPlayer) {
        libvlc_video_set_deinterlace(m_vlcMediaPlayer, QEXTVLC::deinterlacing()[filter].toUtf8().data());
        QEXTVLCError::showErrMsg();
    }
}

void QEXTVLCVideo::setScale(const QEXTVLC::ScaleType &scale)
{
    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        libvlc_video_set_scale(m_vlcMediaPlayer, QEXTVLC::scale()[scale]);
        QEXTVLCError::showErrMsg();
    }
}

void QEXTVLCVideo::setSubtitle(int subtitle)
{
    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        libvlc_video_set_spu(m_vlcMediaPlayer, subtitle);
        QEXTVLCError::showErrMsg();
    }
}

void QEXTVLCVideo::setSubtitleFile(const QString &subtitle)
{
    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        libvlc_video_set_subtitle_file(m_vlcMediaPlayer, subtitle.toUtf8().data());
        QEXTVLCError::showErrMsg();
    }
}

void QEXTVLCVideo::setTeletextPage(int page)
{
    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        libvlc_video_set_teletext(m_vlcMediaPlayer, page);
        QEXTVLCError::showErrMsg();
    }
}

void QEXTVLCVideo::setTrack(int track)
{
    if (m_vlcMediaPlayer) {
        libvlc_video_set_track(m_vlcMediaPlayer, track);
        QEXTVLCError::showErrMsg();
    }
}

void QEXTVLCVideo::showLogo(const QString &file,
                        int x,
                        int y,
                        int opacity)
{
    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        libvlc_video_set_logo_string(m_vlcMediaPlayer, libvlc_logo_file, file.toUtf8().data());
        libvlc_video_set_logo_int(m_vlcMediaPlayer, libvlc_logo_x, x);
        libvlc_video_set_logo_int(m_vlcMediaPlayer, libvlc_logo_y, y);
        libvlc_video_set_logo_int(m_vlcMediaPlayer, libvlc_logo_opacity, opacity);

        libvlc_video_set_logo_int(m_vlcMediaPlayer, libvlc_logo_enable, 1);
    }
}

void QEXTVLCVideo::showMarquee(const QString &text,
                           int x,
                           int y,
                           int timeout,
                           int opacity,
                           int size,
                           int color,
                           int refresh)
{
    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        libvlc_video_set_marquee_string(m_vlcMediaPlayer, libvlc_marquee_Text, text.toUtf8().data());
        libvlc_video_set_marquee_int(m_vlcMediaPlayer, libvlc_marquee_X, x);
        libvlc_video_set_marquee_int(m_vlcMediaPlayer, libvlc_marquee_Y, y);
        libvlc_video_set_marquee_int(m_vlcMediaPlayer, libvlc_marquee_Timeout, timeout);
        libvlc_video_set_marquee_int(m_vlcMediaPlayer, libvlc_marquee_Opacity, opacity);
        libvlc_video_set_marquee_int(m_vlcMediaPlayer, libvlc_marquee_Size, size);
        libvlc_video_set_marquee_int(m_vlcMediaPlayer, libvlc_marquee_Color, color);
        libvlc_video_set_marquee_int(m_vlcMediaPlayer, libvlc_marquee_Refresh, refresh);

        libvlc_video_set_marquee_int(m_vlcMediaPlayer, libvlc_marquee_Enable, 1);
    }
}

QSize QEXTVLCVideo::size() const
{
    unsigned x = 640;
    unsigned y = 480;

    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        libvlc_video_get_size(m_vlcMediaPlayer, 0, &x, &y);
        QEXTVLCError::showErrMsg();
    }

    return QSize(x, y);
}

int QEXTVLCVideo::subtitle() const
{
    int subtitle = -1;
    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        subtitle = libvlc_video_get_spu(m_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();
    }

    return subtitle;
}

int QEXTVLCVideo::subtitleCount() const
{
    int count = -1;
    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        count = libvlc_video_get_spu_count(m_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();
    }

    return count;
}

QStringList QEXTVLCVideo::subtitleDescription() const
{
    QStringList descriptions;

    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        libvlc_track_description_t *desc;
        desc = libvlc_video_get_spu_description(m_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();

        descriptions << QString().fromUtf8(desc->psz_name);
        if (subtitleCount() > 1) {
            for (int i = 1; i < subtitleCount(); i++) {
                desc = desc->p_next;
                descriptions << QString().fromUtf8(desc->psz_name);
            }
        }
    }

    return descriptions;
}

QList<int> QEXTVLCVideo::subtitleIds() const
{
    QList<int> ids;

    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        libvlc_track_description_t *desc;
        desc = libvlc_video_get_spu_description(m_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();

        ids << desc->i_id;
        if (subtitleCount() > 1) {
            for (int i = 1; i < subtitleCount(); i++) {
                desc = desc->p_next;
                ids << desc->i_id;
            }
        }
    }

    return ids;
}

QMap<int, QString> QEXTVLCVideo::subtitles() const
{
    QMap<int, QString> tracks;

    if (m_vlcMediaPlayer) {
        libvlc_track_description_t *desc, *first;
        first = desc = libvlc_video_get_spu_description(m_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();

        if (desc != NULL) {
            tracks.insert(desc->i_id, QString().fromUtf8(desc->psz_name));
            if (subtitleCount() > 1) {
                for (int i = 1; i < subtitleCount(); i++) {
                    desc = desc->p_next;
                    tracks.insert(desc->i_id, QString().fromUtf8(desc->psz_name));
                }
            }
            libvlc_track_description_list_release(first);
        }
    }

    return tracks;
}

bool QEXTVLCVideo::takeSnapshot(const QString &path) const
{
    bool success = false;
    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        success = libvlc_video_take_snapshot(m_vlcMediaPlayer, 0, path.toUtf8().data(), 0, 0) + 1;
        QEXTVLCError::showErrMsg();
    }

    return success;
}

int QEXTVLCVideo::teletextPage() const
{
    int page = -1;
    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        page = libvlc_video_get_teletext(m_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();
    }

    return page;
}

void QEXTVLCVideo::toggleTeletextTransparency()
{
    if (m_vlcMediaPlayer && libvlc_media_player_has_vout(m_vlcMediaPlayer)) {
        libvlc_toggle_teletext(m_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();
    }
}

int QEXTVLCVideo::track() const
{
    int track = -1;
    if (m_vlcMediaPlayer) {
        track = libvlc_video_get_track(m_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();
    }

    return track;
}

int QEXTVLCVideo::trackCount() const
{
    int count = -1;
    if (m_vlcMediaPlayer) {
        count = libvlc_video_get_track_count(m_vlcMediaPlayer);
        QEXTVLCError::showErrMsg();
    }

    return count;
}

QStringList QEXTVLCVideo::trackDescription() const
{
    QStringList descriptions;

    if (m_vlcMediaPlayer) {
        libvlc_track_description_t *desc;
        desc = libvlc_video_get_track_description(m_vlcMediaPlayer);
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

QList<int> QEXTVLCVideo::trackIds() const
{
    QList<int> ids;

    if (m_vlcMediaPlayer) {
        libvlc_track_description_t *desc;
        desc = libvlc_video_get_track_description(m_vlcMediaPlayer);
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

QMap<int, QString> QEXTVLCVideo::tracks() const
{
    QMap<int, QString> tracks;

    if (m_vlcMediaPlayer) {
        libvlc_track_description_t *desc, *first;
        first = desc = libvlc_video_get_track_description(m_vlcMediaPlayer);
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
