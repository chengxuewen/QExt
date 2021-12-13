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

#ifndef _QEXTVLCWIDGETVOLUMESLIDER_H
#define _QEXTVLCWIDGETVOLUMESLIDER_H

#include <qextVLCGlobal.h>

#include <QSlider>

class QTimer;

class QEXTVLCAudio;
class QEXTVLCMediaPlayer;

/*!
    \class QEXTVLCWidgetVolumeSlider qextVLCWidgetVolumeSlider.h
    \ingroup QEXTVLC
    \brief Volume slider widget

    This is one of VLC-Qt GUI classes.
    It provides graphical volume control and also visual display of current volume.
*/
class QEXT_VLC_API QEXTVLCWidgetVolumeSlider : public QSlider
{
    Q_OBJECT
public:
    /*!
        \brief QEXTVLCWidgetVolumeSlider constructor

        \param player media player
        \param parent volume slider's parent GUI widget
    */
    explicit QEXTVLCWidgetVolumeSlider(QEXTVLCMediaPlayer *player, QWidget *parent = 0);

    /*!
        \brief QEXTVLCWidgetVolumeSlider constructor
        \param parent volume slider's parent GUI widget
    */
    explicit QEXTVLCWidgetVolumeSlider(QWidget *parent = 0);

    /*!
        \brief QEXTVLCWidgetVolumeSlider destructor
    */
    ~QEXTVLCWidgetVolumeSlider();

    /*!
        \brief Set media player if initialised without it
        \param player media player
    */
    void setMediaPlayer(QEXTVLCMediaPlayer *player);

public slots:
    /*!
        \brief Mute status
        \return bool current mute status
    */
    bool mute() const;

    /*!
        \brief Toggle mute
        \param enabled new mutte status
    */
    void setMute(bool enabled);

    /*!
        \brief Set volume for current media
        \param volume number from 0 to 200
    */
    void setVolume(int volume);

    /*!
        \brief Get volume for current media
        \return volume number from 0 to 200
    */
    int volume() const;

    /*!
        \brief Decreases or increases volume for 1, depending on the parameter.

        Limits from 0 to 200 apply to this function.

        \param up if true increases the volume
    */
    void volumeControl(bool up);

    /*!
        \brief Decreases volume for 1.

        This function is provided for convenience.

        \sa volumeControl()
    */
    void volumeDown()
    {
        volumeControl(false);
    }

    /*!
        \brief Increases volume for 1.

        This function is provided for convenience.

        \sa volumeControl()
    */
    void volumeUp()
    {
        volumeControl(true);
    }

signals:
    /*!
        \brief Signal for new volume
        \param volume new volume
    */
    void newVolume(int volume);

protected:
    /*!
        \brief Mouse press event override
        \param event mouse event
    */
    void mousePressEvent(QMouseEvent *event);

    /*!
        \brief Mouse release event override
        \param event mouse event
    */
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void updateVolume();

private:
    void initWidgetVolumeSlider();
    void lock();
    void unlock();

    bool m_lock;
    QEXTVLCAudio *m_vlcAudio;
    QEXTVLCMediaPlayer *m_vlcMediaPlayer;
    int m_currentVolume;
    QTimer *m_timer;
};

#endif // _QEXTVLCWIDGETVOLUMESLIDER_H
