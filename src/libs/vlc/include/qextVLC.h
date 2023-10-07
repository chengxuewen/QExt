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

#ifndef _QEXTVLC_H
#define _QEXTVLC_H

#include <qextVLCGlobal.h>

#include <QtCore/QObject>
#include <QtCore/QSizeF>
#include <QtCore/QStringList>

/*!
    \class QEXTVLC Enums.h QEXTVLC/Enums.h
    \ingroup QEXTVLC
    \brief Common enumerations
*/
class QEXT_VLC_API QEXTVLC : public QObject
{
    Q_OBJECT

public:
    /*!
        \enum LogLevel
        \brief libVLC log levels
        \since QExt 0.11.1
    */
    enum LogLevelType
    {
        LogLevel_Debug = 0,
        LogLevel_Notice = 2,
        LogLevel_Warning = 3,
        LogLevel_Error = 4,
        LogLevel_Disabled = 5
    };
    Q_ENUMS(LogLevelType)

    /*!
        \enum RenderFormat
        \brief Frame format used for custom rendering
        \since QExt 0.11.1
    */
    enum RenderFormatType
    {
        YUVFormat
    };

    /*!
        \enum ActionsType
        \brief Actions types identifiers
    */
    enum ActionsType
    {
        Actions_AudioTrack,
        Actions_Subtitles,
        Actions_VideoTrack,
        Actions_Other
    };
    Q_ENUMS(ActionsType)

    /*!
        \enum AudioChannel
        \brief Audio channel options
    */
    enum AudioChannelType
    {
        AudioChannel_Error = -1,
        AudioChannel_Stereo = 1,
        AudioChannel_RStereo = 2,
        AudioChannel_Left = 3,
        AudioChannel_Right = 4,
        AudioChannel_Dolbys = 5
    };
    Q_ENUMS(AudioChannelType)

    /*!
        \enum AudioCodec
        \brief Audio codecs list
    */
    enum AudioCodecType
    {
        AudioCodec_None,
        AudioCodec_MPEG2,
        AudioCodec_MP3,
        AudioCodec_MPEG4,
        AudioCodec_Vorbis,
        AudioCodec_Flac
    };
    Q_ENUMS(AudioCodecType)

    /*!
        \enum AudioOutput
        \brief Audio outputs list
    */
    enum AudioOutputType
    {
        AudioOutput_Default
    };
    Q_ENUMS(AudioOutputType)

    /*!
        \enum Deinterlacing
        \brief Supported deinterlacing modes
    */
    enum DeinterlacingType
    {
        Deinterlacing_Disabled,
        Deinterlacing_Discard,
        Deinterlacing_Blend,
        Deinterlacing_Mean,
        Deinterlacing_Bob,
        Deinterlacing_Linear,
        Deinterlacing_X,
        Deinterlacing_Yadif,
        Deinterlacing_Yadif2x,
        Deinterlacing_Phospor,
        Deinterlacing_IVTC
    };
    Q_ENUMS(DeinterlacingType)

    /*!
        \enum FillMode
        \brief Supported fill modes (QML only)
    */
    enum FillMode
    {
        Fill_PreserveAspectFit = Qt::KeepAspectRatio,
        Fill_PreserveAspectCrop = Qt::KeepAspectRatioByExpanding,
        Fill_Stretch = Qt::IgnoreAspectRatio
    };
    Q_ENUMS(FillMode)

    /*!
        \enum Meta
        \brief Supported meta types
    */
    enum MetaType
    {
        Meta_Title,
        Meta_Artist,
        Meta_Genre,
        Meta_Copyright,
        Meta_Album,
        Meta_TrackNumber,
        Meta_Description,
        Meta_Rating,
        Meta_Date,
        Meta_Setting,
        Meta_URL,
        Meta_Language,
        Meta_NowPlaying,
        Meta_Publisher,
        Meta_EncodedBy,
        Meta_ArtworkURL,
        Meta_TrackID
    };
    Q_ENUMS(MetaType)

    /*!
        \enum Mux
        \brief Recording output file mux
    */
    enum MuxType
    {
        Mux_TS,
        Mux_PS,
        Mux_MP4,
        Mux_OGG,
        Mux_AVI
    };
    Q_ENUMS(MuxType)

    /*!
        \enum PlaybackMode
        \brief Playlist playback mode
    */
    enum PlaybackMode
    {
        Playback_Default,
        Playback_Loop,
        Playback_Repeat
    };
    Q_ENUMS(PlaybackMode)

    /*!
        \enum Ratio
        \brief Supported aspect and crop ratios
    */
    enum RatioType
    {
        Ratio_Original,
        Ratio_Ignore, /*!< QML aspect ratio only */
        Ratio_16_9,
        Ratio_16_10,
        Ratio_185_100,
        Ratio_221_100,
        Ratio_235_100,
        Ratio_239_100,
        Ratio_4_3,
        Ratio_5_4,
        Ratio_5_3,
        Ratio_1_1
    };
    Q_ENUMS(RatioType)

    /*!
        \enum Scale
        \brief Supported scales
    */
    enum ScaleType
    {
        Scale_None,
        Scale_1_05,
        Scale_1_1,
        Scale_1_2,
        Scale_1_3,
        Scale_1_4,
        Scale_1_5,
        Scale_1_6,
        Scale_1_7,
        Scale_1_8,
        Scale_1_9,
        Scale_2_0
    };
    Q_ENUMS(ScaleType)

    /*!
        \enum State
        \brief VLC-Qt playback states
    */
    enum StateType
    {
        State_Idle,
        State_Opening,
        State_Buffering,
        State_Playing,
        State_Paused,
        State_Stopped,
        State_Ended,
        State_Error
    };
    Q_ENUMS(StateType)

    /*!
        \enum VideoCodec
        \brief Video codecs list
    */
    enum VideoCodecType
    {
        VideoCodec_None,
        VideoCodec_MPEG2,
        VideoCodec_MPEG4,
        VideoCodec_H264,
        VideoCodec_Theora
    };
    Q_ENUMS(VideoCodecType)

    /*!
        \enum VideoOutput
        \brief Video outputs list
    */
    enum VideoOutputType
    {
#if defined(Q_OS_LINUX)
        VideoOutput_X11,
        VideoOutput_XVideo,
        VideoOutput_GLX,
#elif defined(Q_OS_WIN32)
        VideoOutput_DirectX,
        VideoOutput_Direct3D,
        VideoOutput_OpenGL,
#endif
        VideoOutput_Default
    };
    Q_ENUMS(VideoOutputType)

    /*!
        \brief Dummy enums constructor.

        This constructor creates a new dummy enums object.

        \param parent object parent (QObject *)
    */
    explicit QEXTVLC(QObject *parent = QEXT_DECL_NULLPTR);


    /*!
        \brief Log level strings
        \return log level strings (QStringList)
    */
    static QStringList logLevel();

    /*!
        \brief Audio codecs strings
        \return audio codecs strings (QStringList)
    */
    static QStringList audioCodec();

    /*!
        \brief Audio outputs strings
        \return audio outputs strings (QStringList)
    */
    static QStringList audioOutput();

    /*!
        \brief Audio outputs strings in readable form
        \return audio outputs strings (QStringList)
    */
    static QStringList audioOutputHuman();

    /*!
        \brief Deinterlacing modes strings
        \return deinterlacing strings (QStringList)
    */
    static QStringList deinterlacing();

    /*!
        \brief Mux strings
        \return mux strings (QStringList)
    */
    static QStringList mux();

    /*!
        \brief Aspect and crop ratios strings
        \return ratios strings (QStringList)
    */
    static QStringList ratio();

    /*!
        \brief Aspect and crop ratios strings in readable form
        \return ratios strings (QStringList)
    */
    static QStringList ratioHuman();

    /*!
        \brief Aspect and crop ratios converter to QSizeF
        \param ratio aspect or crop ratio (QEXTVLC::Ratio)
        \return two-dimensional object using floating point precision (QSizeF)
    */
    static QSizeF ratioSize(const QEXTVLC::RatioType &ratio);

    /*!
        \brief Scale floats
        \return scale floats (QList<float>)
    */
    static QList<float> scale();

    /*!
        \brief Video codecs strings
        \return video codecs strings (QStringList)
    */
    static QStringList videoCodec();

    /*!
        \brief Video outputs strings
        \return video outputs strings (QStringList)
    */
    static QStringList videoOutput();

    /*!
        \brief Video outputs strings in readable form
        \return video outputs strings (QStringList)
    */
    static QStringList videoOutputHuman();
};

#endif // _QEXTVLC_H
