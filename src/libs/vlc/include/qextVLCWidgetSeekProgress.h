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

#ifndef _QEXTVLCWIDGETSEEKPROGRESS_H
#define _QEXTVLCWIDGETSEEKPROGRESS_H

#include <qextVLCWidgetSeek.h>

class QProgressBar;

/*!
    \class QEXTVLCWidgetSeekProgress qextVLCWidgetSeekProgress.h
    \brief Seek widget

    This is one of VLC-Qt GUI classes.
    It provides a display of elapsed time and full time of the media using a progress bar.
*/
class QEXT_VLC_API QEXTVLCWidgetSeekProgress : public QEXTVLCWidgetSeek
{
    Q_OBJECT
public:
    /*!
        \brief QEXTVLCWidgetSeekProgress constructor
        \param player media player
        \param parent seek widget's parent GUI widget
    */
    explicit QEXTVLCWidgetSeekProgress(QEXTVLCMediaPlayer *player, QWidget *parent = 0);

    /*!
        \brief QEXTVLCWidgetSeekProgress constructor
        \param parent seek widget's parent GUI widget
    */
    explicit QEXTVLCWidgetSeekProgress(QWidget *parent = 0);

    /*!
        \brief QEXTVLCWidgetSeekProgress destructor
    */
    ~QEXTVLCWidgetSeekProgress();

protected:
    /*!
        \brief Mouse move event override
        \param event mouse event
    */
    void mouseMoveEvent(QMouseEvent *event);

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

    /*!
        \brief Mouse wheel event override
        \param event mouse event
    */
    void wheelEvent(QWheelEvent *event);

private slots:
    virtual void updateCurrentTime(int time);
    virtual void updateFullTime(int time);

private:
    virtual void setSliderWidget(QWidget *slider, bool updateSlider = true);

    void updateEvent(const QPoint &pos);

    void lock();
    void unlock();

    bool m_lock;
};

#endif // _QEXTVLCWIDGETSEEKPROGRESS_H
