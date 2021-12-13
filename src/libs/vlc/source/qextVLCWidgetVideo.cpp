/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
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

#include <QtGlobal>

#if QT_VERSION >= 0x050000
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolBar>
#else
#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QToolBar>
#endif

#if defined(Q_WS_X11)
#include <X11/Xlib.h>
#include <qx11info_x11.h>
#endif

#include "qextVLCError.h"
#include <qextVLCMediaPlayer.h>
#include "qextVLCVideo.h"

#include "qextVLCWidgetVideo.h"

QEXTVLCWidgetVideo::QEXTVLCWidgetVideo(QEXTVLCMediaPlayer *player,
                               QWidget *parent)
    : QFrame(parent)
{
    m_vlcMediaPlayer = player;

    connect(m_vlcMediaPlayer, SIGNAL(vout(int)), this, SLOT(applyPreviousSettings()));

    initWidgetVideo();
}

QEXTVLCWidgetVideo::QEXTVLCWidgetVideo(QWidget *parent)
    : QFrame(parent),
      m_vlcMediaPlayer(0)
{
    initWidgetVideo();
}

QEXTVLCWidgetVideo::~QEXTVLCWidgetVideo()
{
    release();
}

void QEXTVLCWidgetVideo::initWidgetVideo()
{
    m_enableSettings = false;
    m_defaultAspectRatio = QEXTVLC::Ratio_Original;
    m_defaultCropRatio = QEXTVLC::Ratio_Original;
    m_defaultDeinterlacing = QEXTVLC::Deinterlacing_Disabled;
    m_defaultScale = QEXTVLC::Scale_None;
    m_currentAspectRatio = QEXTVLC::Ratio_Original;
    m_currentCropRatio = QEXTVLC::Ratio_Original;
    m_currentDeinterlacing = QEXTVLC::Deinterlacing_Disabled;
    m_currentScale = QEXTVLC::Scale_None;

    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_video = 0;

    QPalette plt = palette();
    plt.setColor(QPalette::Window, Qt::black);
    setPalette(plt);
}

void QEXTVLCWidgetVideo::setMediaPlayer(QEXTVLCMediaPlayer *player)
{
    m_vlcMediaPlayer = player;

    connect(m_vlcMediaPlayer, SIGNAL(vout(int)), this, SLOT(applyPreviousSettings()));
}

void QEXTVLCWidgetVideo::setCurrentAspectRatio(const QEXTVLC::RatioType &ratio)
{
    m_currentAspectRatio = ratio;
}

void QEXTVLCWidgetVideo::setCurrentCropRatio(const QEXTVLC::RatioType &ratio)
{
    m_currentCropRatio = ratio;
}

void QEXTVLCWidgetVideo::setCurrentDeinterlacing(const QEXTVLC::DeinterlacingType &deinterlacing)
{
    m_currentDeinterlacing = deinterlacing;
}

void QEXTVLCWidgetVideo::setCurrentScale(const QEXTVLC::ScaleType &scale)
{
    m_currentScale = scale;
}

void QEXTVLCWidgetVideo::setDefaultAspectRatio(const QEXTVLC::RatioType &ratio)
{
    m_defaultAspectRatio = ratio;
}

void QEXTVLCWidgetVideo::setDefaultCropRatio(const QEXTVLC::RatioType &ratio)
{
    m_defaultCropRatio = ratio;
}

void QEXTVLCWidgetVideo::setDefaultDeinterlacing(const QEXTVLC::DeinterlacingType &deinterlacing)
{
    m_defaultDeinterlacing = deinterlacing;
}

void QEXTVLCWidgetVideo::setDefaultScale(const QEXTVLC::ScaleType &scale)
{
    m_defaultScale = scale;
}

void QEXTVLCWidgetVideo::enableDefaultSettings()
{
    initDefaultSettings();

    enablePreviousSettings();
}

void QEXTVLCWidgetVideo::enablePreviousSettings()
{
    m_enableSettings = true;
}

void QEXTVLCWidgetVideo::initDefaultSettings()
{
    m_currentAspectRatio = defaultAspectRatio();
    m_currentCropRatio = defaultCropRatio();
    m_currentDeinterlacing = defaultDeinterlacing();
    m_currentScale = defaultScale();
}

void QEXTVLCWidgetVideo::applyPreviousSettings()
{
    if (!m_enableSettings)
        return;

    if (!m_vlcMediaPlayer)
        return;

    m_vlcMediaPlayer->video()->setAspectRatio(m_currentAspectRatio);
    m_vlcMediaPlayer->video()->setCropGeometry(m_currentCropRatio);
    m_vlcMediaPlayer->video()->setScale(m_currentScale);
    m_vlcMediaPlayer->video()->setDeinterlace(m_currentDeinterlacing);

    m_enableSettings = false;
}

void QEXTVLCWidgetVideo::setAspectRatio(const QEXTVLC::RatioType &ratio)
{
    if (m_vlcMediaPlayer) {
        m_currentAspectRatio = ratio;
        m_vlcMediaPlayer->video()->setAspectRatio(ratio);
    }
}

void QEXTVLCWidgetVideo::setCropRatio(const QEXTVLC::RatioType &ratio)
{
    if (m_vlcMediaPlayer) {
        m_currentCropRatio = ratio;
        m_vlcMediaPlayer->video()->setCropGeometry(ratio);
    }
}

void QEXTVLCWidgetVideo::setDeinterlacing(const QEXTVLC::DeinterlacingType &deinterlacing)
{
    if (m_vlcMediaPlayer) {
        m_currentDeinterlacing = deinterlacing;
        m_vlcMediaPlayer->video()->setDeinterlace(deinterlacing);
    }
}

void QEXTVLCWidgetVideo::setScale(const QEXTVLC::ScaleType &scale)
{
    if (m_vlcMediaPlayer) {
        m_currentScale = scale;
        m_vlcMediaPlayer->video()->setScale(scale);
    }
}

void QEXTVLCWidgetVideo::sync()
{
#if defined(Q_WS_X11)
    /* Make sure the X server has processed all requests.
     * This protects other threads using distinct connections from getting
     * the video widget window in an inconsistent states. */
    XSync(QX11Info::display(), False);
#endif
}

WId QEXTVLCWidgetVideo::request()
{
    if (m_video)
        return 0;

    m_video = new QWidget();
    QPalette plt = palette();
    plt.setColor(QPalette::Window, Qt::black);
    m_video->setPalette(plt);
    m_video->setAutoFillBackground(true);
    m_video->setMouseTracking(true);
/* Indicates that the widget wants to draw directly onto the screen.
       Widgets with this attribute set do not participate in composition
       management */
/* This is currently disabled on X11 as it does not seem to improve
     * performance, but causes the video widget to be transparent... */
#if QT_VERSION < 0x050000 && !defined(Q_WS_X11)
    _video->setAttribute(Qt::WA_PaintOnScreen, true);
#endif

    m_layout->addWidget(m_video);

    sync();
    return m_video->winId();
}

void QEXTVLCWidgetVideo::release()
{
    if (m_video) {
        m_layout->removeWidget(m_video);
        m_video->deleteLater();
        m_video = NULL;
    }

    updateGeometry();
}
