/*************************************************************************************
*
* Library: QEXT
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

#ifndef _QEXTVLCWIDGETSEEK_H
#define _QEXTVLCWIDGETSEEK_H

#include <qextVLCGlobal.h>

#if QT_VERSION >= 0x050000
    #include <QtWidgets/QWidget>
#else
    #include <QWidget>
#endif

class QAbstractSlider;
class QLabel;
class QProgressBar;
class QTimer;

class QEXTVLCMediaPlayer;

/*!
    \class QEXTVLCWidgetSeek qextVLCWidgetSeek.h
    \ingroup QEXTVLC
    \brief Seek widget

    This is one of VLC-Qt GUI classes.
    It provides a display of elapsed time and full time of the media.
*/
class QEXT_VLC_API QEXTVLCWidgetSeek : public QWidget
{
    Q_OBJECT
public:
    /*!
        \brief QEXTVLCWidgetSeek constructor
        \param player media player
        \param slider widget to be used as slider
        \param connectSlider connect the slider to relevant sigals, set to false if you want to handle everything yourself
        \param parent seek widget's parent GUI widget
    */
    explicit QEXTVLCWidgetSeek(QEXTVLCMediaPlayer *player,
                               QWidget *slider = 0,
                               bool connectSlider = true,
                               QWidget *parent = 0);

    /*!
        \brief QEXTVLCWidgetSeek constructor
        \param slider widget to be used as slider
        \param connectSlider connect the slider to relevant sigals, set to false if you want to handle everything yourself
        \param parent seek widget's parent GUI widget
    */
    explicit QEXTVLCWidgetSeek(QWidget *slider,
                               bool connectSlider,
                               QWidget *parent = 0);

    /*!
        \brief QEXTVLCWidgetSeek constructor
        \param parent seek widget's parent GUI widget
    */
    explicit QEXTVLCWidgetSeek(QWidget *parent = 0);

    /*!
        \brief QEXTVLCWidgetSeek destructor
    */
    ~QEXTVLCWidgetSeek();

    /*!
        \brief Get auto-hide option.
        \return auto-hide option status, true if enabled
    */
    bool autoHide() const
    {
        return m_autoHide;
    }

    /*!
        \brief Set auto-hide option

        This option will automatically hide seek widget, if enabled.

        \param autoHide new auto-hide option
    */
    void setAutoHide(bool autoHide);

    /*!
        \brief Set media player if initialised without it
        \param player media player
    */
    virtual void setMediaPlayer(QEXTVLCMediaPlayer *player);

    /*!
        \brief Set slider widget
        \param slider widget to be used as slider
        \param updateSlider connect the slider to relevant sigals, set to false if you want to handle everything yourself
    */
    virtual void setSliderWidget(QWidget *slider,
                                 bool updateSlider = true);

protected slots:
    /*!
        \brief Update turrent time callback
        \param time current time
    */
    virtual void updateCurrentTime(int time);

    /*!
        \brief Update full time callback
        \param time full time
    */
    virtual void updateFullTime(int time);

protected:
    /*!
     * \brief Media player
     */
    QEXTVLCMediaPlayer *m_vlcMediaPlayer;

    /*!
     * \brief Progress bar
     */
    QProgressBar *m_progress;

private slots:
    void end();

private:
    void initWidgetSeek(QWidget *slider);

    bool m_autoHide;
    QAbstractSlider *m_slider;
    bool m_connectSlider;
    QLabel *m_labelElapsed;
    QLabel *m_labelFull;
};

#endif // _QEXTVLCWIDGETSEEK_H
