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

#ifndef _QEXTVLCWIDGETVIDEO_H
#define _QEXTVLCWIDGETVIDEO_H

#include <qextVLC.h>
#include <qextVLCVideoDelegate.h>
#include <qextVLCGlobal.h>

#include <QtCore/QTimer>

#if QT_VERSION >= 0x050000
    #include <QtWidgets/QFrame>
#else
    #include <QtGui/QFrame>
#endif

class QEXTVLCMediaPlayer;

/*!
    \defgroup QEXTVLC
    \brief Widget classes for faster media player developement
 */

/*!
    \class QEXTVLCWidgetVideo qextVLCWidgetVideo.h
    \brief Video widget

    This is one of VLC-Qt GUI classes.
    It provides video display and mouse control.
*/
class QEXT_VLC_API QEXTVLCWidgetVideo : public QFrame, public QEXTVLCVideoDelegate
{
    Q_OBJECT
public:
    /*!
        \brief QEXTVLCWidgetVideo constructor
        \param player media player
        \param parent video widget's parent GUI widget
    */
    explicit QEXTVLCWidgetVideo(QEXTVLCMediaPlayer *player, QWidget *parent = 0);

    /*!
        \brief QEXTVLCWidgetVideo constructor
        \param parent video widget's parent GUI widget
    */
    explicit QEXTVLCWidgetVideo(QWidget *parent = 0);

    /*!
        \brief QEXTVLCWidgetVideo destructor
    */
    ~QEXTVLCWidgetVideo();

    /*!
        \brief Get current aspect ratio setting
        \return current aspect ratio
    */
    inline QEXTVLC::RatioType currentAspectRatio() const
    {
        return m_currentAspectRatio;
    }

    /*!
        \brief Get default aspect ratio setting
        \return default aspect ratio
    */
    inline QEXTVLC::RatioType defaultAspectRatio() const
    {
        return m_defaultAspectRatio;
    }

    /*!
        \brief Set current aspect ratio setting
        \param ratio current aspect ratio
    */
    void setCurrentAspectRatio(const QEXTVLC::RatioType &ratio);

    /*!
        \brief Set default aspect ratio setting
        \param ratio default aspect ratio
    */
    void setDefaultAspectRatio(const QEXTVLC::RatioType &ratio);

    /*!
        \brief Get current crop ratio setting
        \return current crop ratio
    */
    inline QEXTVLC::RatioType currentCropRatio() const
    {
        return m_currentCropRatio;
    }

    /*!
        \brief Get default crop ratio setting
        \return default crop ratio
    */
    inline QEXTVLC::RatioType defaultCropRatio() const
    {
        return m_defaultCropRatio;
    }

    /*!
        \brief Set current crop ratio setting
        \param ratio current crop ratio
    */
    void setCurrentCropRatio(const QEXTVLC::RatioType &ratio);

    /*!
        \brief Set default crop ratio setting
        \param ratio default crop ratio
    */
    void setDefaultCropRatio(const QEXTVLC::RatioType &ratio);

    /*!
        \brief Get current deinterlacing filter setting
        \return current deinterlacing filter
    */
    inline QEXTVLC::DeinterlacingType currentDeinterlacing() const
    {
        return m_currentDeinterlacing;
    }

    /*!
        \brief Get default deinterlacing filter setting
        \return current deinterlacing filter
    */
    inline QEXTVLC::DeinterlacingType defaultDeinterlacing() const
    {
        return m_defaultDeinterlacing;
    }

    /*!
        \brief Set current deinterlacing filter setting
        \param deinterlacing current deinterlacing filter
    */
    void setCurrentDeinterlacing(const QEXTVLC::DeinterlacingType &deinterlacing);

    /*!
        \brief Set default deinterlacing filter setting
        \param deinterlacing default deinterlacing filter
    */
    void setDefaultDeinterlacing(const QEXTVLC::DeinterlacingType &deinterlacing);

    /*!
        \brief Get current scale ratio setting
        \return current scale ratio
    */
    inline QEXTVLC::ScaleType currentScale() const
    {
        return m_currentScale;
    }

    /*!
        \brief Get default scale ratio setting
        \return default scale ratio
    */
    inline QEXTVLC::ScaleType defaultScale() const
    {
        return m_defaultScale;
    }

    /*!
        \brief Set current scale ratio setting
        \param scale current scale ratio
    */
    void setCurrentScale(const QEXTVLC::ScaleType &scale);

    /*!
        \brief Set default scale ratio setting
        \param scale default scale ratio
    */
    void setDefaultScale(const QEXTVLC::ScaleType &scale);

    /*!
        \brief Set media player if initialised without it
        \param player media player
    */
    void setMediaPlayer(QEXTVLCMediaPlayer *player);

    /*!
        \brief Request new video frame.

        Request new video frame and its widget ID to set it in the instance.
        \return widget ID
        \sa QEXTVLCMediaPlayer::QEXTVLCMediaPlayer()
    */
    WId request();

    /*!
        \brief Release current video frame.
    */
    void release();

public slots:
    /*!
        \brief Enable default video settings

        crop, ratio, deinterlacing filter, scale
    */
    void enableDefaultSettings();

    /*!
        \brief Enable previous video settings

        crop, ratio, deinterlacing filter, scale
    */
    void enablePreviousSettings();

    /*!
        \brief Initialize default video settings

        Set but not apply crop, ratio, deinterlacing filter, scale
    */
    void initDefaultSettings();

    /*!
        \brief Set aspect ratio
        \param ratio aspect ratio
    */
    void setAspectRatio(const QEXTVLC::RatioType &ratio);

    /*!
        \brief Set crop ratio
        \param ratio crop ratio
    */
    void setCropRatio(const QEXTVLC::RatioType &ratio);

    /*!
        \brief Set deinterlace filter
        \param deinterlacing deinterlacing filter
    */
    void setDeinterlacing(const QEXTVLC::DeinterlacingType &deinterlacing);

    /*!
        \brief Set scale ratio
        \param scale scale ratio
    */
    void setScale(const QEXTVLC::ScaleType &scale);

private slots:
    void applyPreviousSettings();

private:
    void initWidgetVideo();
    void sync();

    QEXTVLCMediaPlayer *m_vlcMediaPlayer;

    QWidget *m_video;
    QLayout *m_layout;

    bool m_enableSettings;

    QEXTVLC::RatioType m_defaultAspectRatio;
    QEXTVLC::RatioType m_defaultCropRatio;
    QEXTVLC::DeinterlacingType m_defaultDeinterlacing;
    QEXTVLC::ScaleType m_defaultScale;

    QEXTVLC::RatioType m_currentAspectRatio;
    QEXTVLC::RatioType m_currentCropRatio;
    QEXTVLC::DeinterlacingType m_currentDeinterlacing;
    QEXTVLC::ScaleType m_currentScale;
};

#endif // _QEXTVLCWIDGETVIDEO_H
