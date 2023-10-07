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

#ifndef _QEXTVLCMEDIA_H
#define _QEXTVLCMEDIA_H

#include <qextVLC.h>
#include <qextVLCGlobal.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>

class QEXTVLCInstance;
struct QEXTVLCStats;

struct libvlc_event_t;
struct libvlc_event_manager_t;
struct libvlc_media_t;

/*!
    \class QEXTVLCMedia qextVLCMedia.h
    \ingroup QEXTVLC
    \brief Media item

    An abstract representation of a playable media.
    It consists of a media location and various optional meta data.
*/
class QEXT_VLC_API QEXTVLCMedia : public QObject
{
    Q_OBJECT
public:
    /*!
        \brief QEXTVLCMedia constructor.

        This constructor creates a new media instance from a media location.

        \param location location of the media (QString)
        \param localFile true, if media is local file (bool)
        \param instance main libvlc instance (QEXTVLCInstance *)
    */
    explicit QEXTVLCMedia(const QString &location, bool localFile, QEXTVLCInstance *instance);

    /*!
        \brief QEXTVLCMedia constructor.

        This constructor creates a new media instance from a remote media location.
        Provided for convenience.

        \param location remote location of the media (QString)
        \param instance main libvlc instance (QEXTVLCInstance *)
    */
    explicit QEXTVLCMedia(const QString &location, QEXTVLCInstance *instance);

    /*!
        \brief QEXTVLCMedia constructor.

        This constructor creates a new media instance from an existing one.

        \param media libvlc media item (libvlc_media_t *)
    */
    QEXTVLCMedia(libvlc_media_t *media);

    /*!
        \brief QEXTVLCMedia destructor
    */
    ~QEXTVLCMedia();

    /*!
        \brief libvlc media item
        \return libvlc media item (libvlc_media_t *)
    */
    libvlc_media_t *core();

    /*!
        \brief Get parsed status

        Know when it is OK to read metadata and track information

        \return parsed status (const bool)
        \since QExt 0.11.1
    */
    bool parsed() const;

    /*!
        \brief Parse media information

        Parse media information: metadata and track information.
        This call is async.

        \see parsedChanged
        \since QExt 0.11.1
    */
    void parse();

    /*!
        \brief Current media location

        \return QString media location
    */
    QString currentLocation() const;

    /*!
        \brief Get media stats

        \return QEXTVLCStats media stats object
    */
    QEXTVLCStats *getStats();

    /*!
        \brief Get media state
        \return current media state
        \since QExt 0.11.1
    */
    QEXTVLC::StateType state() const;

    /*!
        \brief Get media duration
        \return duration
        \since QExt 0.11.1
    */
    qint64 duration() const;

    /*!
        \brief Duplicate (provided for convenience)

        Apply duplicate options with desired mux but without transcoding.

        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (QEXTVLC::Mux)
        \return QString output file
        \sa record()
    */
    QString duplicate(const QString &name, const QString &path, const QEXTVLC::MuxType &mux);

    /*!
        \brief Duplicate (provided for convenience)

        Apply duplicate options with desired mux and transcoding (experimental).

        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (QEXTVLC::Mux)
        \param audioCodec audio codec (QEXTVLC::AudioCodec)
        \param videoCodec video codec (QEXTVLC::VideoCodec)
        \return QString output file
        \sa record()
    */
    QString duplicate(const QString &name, const QString &path, const QEXTVLC::MuxType &mux,
                      const QEXTVLC::AudioCodecType &audioCodec, const QEXTVLC::VideoCodecType &videoCodec);

    /*!
        \brief Duplicate (provided for convenience)

        Apply duplicate options with desired mux, transcoding
        and some other options (experimental).

        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (QEXTVLC::Mux)
        \param audioCodec audio codec (QEXTVLC::AudioCodec)
        \param videoCodec video codec (QEXTVLC::VideoCodec)
        \param bitrate video bitrate (int)
        \param fps frames per second (int)
        \param scale video scale (int)
        \return QString output file
        \sa record()
    */
    QString duplicate(const QString &name,
                      const QString &path,
                      const QEXTVLC::MuxType &mux,
                      const QEXTVLC::AudioCodecType &audioCodec,
                      const QEXTVLC::VideoCodecType &videoCodec,
                      int bitrate,
                      int fps,
                      int scale);

    /*!
        \brief Merge

        Apply merge options with desired mux but without transcoding.

        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (QEXTVLC::Mux)
        \return QString output file
    */
    QString merge(const QString &name,
                  const QString &path,
                  const QEXTVLC::MuxType &mux);

    /*!
        \brief Record

        Apply recording options with desired mux but without transcoding.

        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (QEXTVLC::Mux)
        \param duplicate also duplicate on screen (bool)
        \return QString output file
    */
    QString record(const QString &name,
                   const QString &path,
                   const QEXTVLC::MuxType &mux,
                   bool duplicate = false);

    /*!
        \brief Record

        Apply recording options with desired mux and transcoding (experimental).

        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (QEXTVLC::Mux)
        \param audioCodec audio codec (QEXTVLC::AudioCodec)
        \param videoCodec video codec (QEXTVLC::VideoCodec)
        \param duplicate also duplicate on screen (bool)
        \return QString output file
    */
    QString record(const QString &name,
                   const QString &path,
                   const QEXTVLC::MuxType &mux,
                   const QEXTVLC::AudioCodecType &audioCodec,
                   const QEXTVLC::VideoCodecType &videoCodec,
                   bool duplicate = false);

    /*!
        \brief Record

        Apply recording options with desired mux, transcoding
        and some other options (experimental).

        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (QEXTVLC::Mux)
        \param audioCodec audio codec (QEXTVLC::AudioCodec)
        \param videoCodec video codec (QEXTVLC::VideoCodec)
        \param bitrate video bitrate (int)
        \param fps frames per second (int)
        \param scale video scale (int)
        \param duplicate also duplicate on screen (bool)
        \return QString output file
    */
    QString record(const QString &name,
                   const QString &path,
                   const QEXTVLC::MuxType &mux,
                   const QEXTVLC::AudioCodecType &audioCodec,
                   const QEXTVLC::VideoCodecType &videoCodec,
                   int bitrate,
                   int fps,
                   int scale,
                   bool duplicate = false);

    /*!
        \brief Set program
        \param program program PID (int)
    */
    void setProgram(int program);

    /*!
        \brief Set media option
        \param option media option (QString)
    */
    void setOption(const QString &option);

    /*!
        \brief Set media options
        \param options media options (QStringList)
    */
    void setOptions(const QStringList &options);

signals:
    /*!
        \brief Signal sent on meta change
        \param meta new meta
    */
    void metaChanged(const QEXTVLC::MetaType &meta);

    /*!
        \brief Signal sent on subitem added
        \param subitem subitem that was added
    */
    void subitemAdded(libvlc_media_t *subitem);

    /*!
        \brief Signal sent on duration change
        \param duration new duration
    */
    void durationChanged(int duration);

    /*!
        \brief Signal sent on parsed change
        \param status new parsed status
        @deprecated Deprecated since QExt 0.11.1, will be removed in 2.0
    */
    Q_DECL_DEPRECATED void parsedChanged(int status);

    /*!
        \brief Signal sent on parsed change
        \param status new parsed status
    */
    void parsedChanged(bool status);

    /*!
        \brief Signal sent on freed
        \param media freed libvlc_media_t object
    */
    void freed(libvlc_media_t *media);

    /*!
        \brief Signal sent on state change
        \param state new state
    */
    void stateChanged(const QEXTVLC::StateType &state);

private:
    void initMedia(const QString &location,
                   bool localFile,
                   QEXTVLCInstance *instance);

    static void libvlc_callback(const libvlc_event_t *event,
                                void *data);

    void createCoreConnections();
    void removeCoreConnections();

    libvlc_media_t *m_vlcMedia;
    libvlc_event_manager_t *m_vlcEvents;

    QString m_currentLocation;
};

#endif // _QEXTVLCMEDIA_H
