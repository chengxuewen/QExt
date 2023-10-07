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

#ifndef _QEXTVLCVIDEO_H
#define _QEXTVLCVIDEO_H

#include <qextVLC.h>
#include <qextVLCGlobal.h>

#include <QtCore/QList>
#include <QtCore/QSize>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QMap>

class QEXTVLCMediaPlayer;

struct libvlc_media_player_t;

/*!
    \class QEXTVLCVideo qextVLCVideo.h
    \ingroup QEXTVLC
    \brief Video controls

    A group of video controls functions.
*/
class QEXT_VLC_API QEXTVLCVideo : public QObject
{
    Q_OBJECT
public:
    /*!
        \brief QEXTVLCVideo constructor.

        This constructor creates a new video manager.

        \param player media player (QEXTVLCMediaPlayer *)
    */
    explicit QEXTVLCVideo(QEXTVLCMediaPlayer *player);

    /*!
        \brief QEXTVLCVideo destructor
    */
    ~QEXTVLCVideo();

    /*!
        \brief Get current video aspect ratio.
        \return current video aspect-ratio or NULL if not specified (const QEXTVLC::Ratio)
    */
    QEXTVLC::RatioType aspectRatio() const;

    /*!
        \brief Get current crop filter geometry.
        \return current crop filter geometry or NULL if not specified (const QEXTVLC::Ratio)
    */
    QEXTVLC::RatioType cropGeometry() const;

    /*!
        \brief Hide logo.
    */
    void hideLogo();

    /*!
        \brief Hide marquee.
    */
    void hideMarquee();

    /*!
        \brief Get current scale ratio.
        \return current scale ratio or NULL if not specified (const QEXTVLC::Scale)
    */
    QEXTVLC::ScaleType scale() const;

    /*!
        \brief Set new video aspect ratio.
        \param ratio new video aspect-ratio or NULL to reset to default (QEXTVLC::Ratio)
    */
    void setAspectRatio(const QEXTVLC::RatioType &ratio);

    /*!
        \brief Set new crop filter geometry.
        \param ratio new crop filter geometry or NULL to reset to default (QEXTVLC::Ratio)
    */
    void setCropGeometry(const QEXTVLC::RatioType &ratio);

    /*!
        \brief Enable or disable deinterlace filter.
        \param filter type of deinterlace filter or NULL to reset to default (QEXTVLC::Deinterlacing)
    */
    void setDeinterlace(const QEXTVLC::DeinterlacingType &filter);

    /*!
        \brief Set new scale ratio.
        \param scale scale ratio or NULL to reset to default (QEXTVLC::Scale)
    */
    void setScale(const QEXTVLC::ScaleType &scale);

    /*!
        \brief Set current video subtitle.
        \param subtitle new video subtitle (int)
    */
    void setSubtitle(int subtitle);

    /*!
        \brief Set new video subtitle file.
        \param subtitle new video subtitle file (QString)
    */
    void setSubtitleFile(const QString &subtitle);

    /*!
        \brief Set new teletext page to retrieve.
        \param page new teletext page number (int)
    */
    void setTeletextPage(int page);

    /*!
        \brief Set current video track.
        \param track new video track (int)
    */
    void setTrack(int track);

    /*!
        \brief Show logo.
        \param file logo file (QString)
        \param x x-coordinate (int)
        \param y y-coordinate (int)
        \param opacity logo opacity (int)
    */
    void showLogo(const QString &file,
                  int x,
                  int y,
                  int opacity = 255);

    /*!
        \brief Show logo.
        \param text text to display (QString)
        \param x x-coordinate (int)
        \param y y-coordinate (int)
        \param timeout marquee timeout
        \param opacity opacity from 0 to 255 (int)
        \param size size (int)
        \param color color in base 16 int (int)
        \param refresh refresh rate (int)
    */
    void showMarquee(const QString &text,
                     int x,
                     int y,
                     int timeout = 0,
                     int opacity = 255,
                     int size = -1,
                     int color = 0xFFFFFF,
                     int refresh = 0);

    /*!
        \brief Get current video size. (currently primary only)
        \return size of the video (QSize)
    */
    QSize size() const;

    /*!
        \brief Get current video subtitle.
        \return the number of current video subtitle, or -1 if none (const int)
    */
    int subtitle() const;

    /*!
        \brief Get number of available video subtitles.
        \return the number of available video subtitles, or -1 if unavailable (const int)
    */
    int subtitleCount() const;

    /*!
        \brief Get the descriptions of available video subtitles.
        \return list with descriptions of available video subtitles (const QStringList)
    */
    QStringList subtitleDescription() const;

    /*!
        \brief Get the ids of available video subtitles.
        \return list with ids of available video subtitles (const QList<int>)
    */
    QList<int> subtitleIds() const;

    /*!
        \brief Get available video subtitles.
        \return dictionary with available video subtitles (const QMap<int, QString>)
        \since QExt 0.11.1
    */
    QMap<int, QString> subtitles() const;

    /*!
        \brief Take a snapshot of current video (currently primary only)
        \param path output path (QString)
        \return true if successfull (bool)
    */
    bool takeSnapshot(const QString &path) const;

    /*!
        \brief Get current teletext page requested.
        \return current teletext page number (int)
    */
    int teletextPage() const;

    /*!
        \brief Toggle teletext transparent status on video output.
    */
    void toggleTeletextTransparency();

    /*!
        \brief Get current video track.
        \return the number of current video track, or -1 if none (const int)
    */
    int track() const;

    /*!
        \brief Get number of available video tracks.
        \return the number of available video tracks, or -1 if unavailable (const int)
    */
    int trackCount() const;

    /*!
        \brief Get the description of available video tracks.
        \return list with description of available video tracks (const QStringList)
    */
    QStringList trackDescription() const;

    /*!
        \brief Get the ids of available video tracks.
        \return list with ids of available video tracks (const QList<int>)
    */
    QList<int> trackIds() const;

    /*!
        \brief Get available video tracks.
        \return dictionary with available video tracks (const QMap<int, QString>)
        \since QExt 0.11.1
    */
    QMap<int, QString> tracks() const;

private:
    libvlc_media_player_t *m_vlcMediaPlayer;
};

#endif // _QEXTVLCVIDEO_H
