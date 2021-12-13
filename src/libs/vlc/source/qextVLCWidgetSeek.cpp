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

#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>

#if QT_VERSION >= 0x050000
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QProgressBar>
#else
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QProgressBar>
#endif

#include "qextVLCError.h"
#include <qextVLCMediaPlayer.h>

#include "qextVLCWidgetSeek.h"

QEXTVLCWidgetSeek::QEXTVLCWidgetSeek(QEXTVLCMediaPlayer *player,
                             QWidget *slider,
                             bool connectSlider,
                             QWidget *parent)
    : QWidget(parent),
      m_vlcMediaPlayer(player),
      m_progress(0),
      m_slider(0),
      m_connectSlider(connectSlider),
      m_labelElapsed(0),
      m_labelFull(0)
{
    initWidgetSeek(slider);
}

QEXTVLCWidgetSeek::QEXTVLCWidgetSeek(QWidget *slider,
                             bool connectSlider,
                             QWidget *parent)
    : QWidget(parent),
      m_vlcMediaPlayer(0),
      m_progress(0),
      m_slider(0),
      m_connectSlider(connectSlider),
      m_labelElapsed(0),
      m_labelFull(0)
{
    initWidgetSeek(slider);
}

QEXTVLCWidgetSeek::QEXTVLCWidgetSeek(QWidget *parent)
    : QWidget(parent),
      m_vlcMediaPlayer(0),
      m_progress(0),
      m_slider(0),
      m_connectSlider(true),
      m_labelElapsed(0),
      m_labelFull(0)
{
    initWidgetSeek(0);
}

QEXTVLCWidgetSeek::~QEXTVLCWidgetSeek() {}

void QEXTVLCWidgetSeek::initWidgetSeek(QWidget *slider)
{
    m_autoHide = false;

    if (slider == 0)
        slider = new QSlider();

    QAbstractSlider *sl = qobject_cast<QAbstractSlider *>(slider);
    m_slider = sl;
    if (sl != 0 && m_connectSlider) {
        sl->setOrientation(Qt::Horizontal);
        sl->setMaximum(1);
        if (m_vlcMediaPlayer != 0) {
            connect(sl, SIGNAL(valueChanged(int)), m_vlcMediaPlayer, SLOT(setTime(int)));
            connect(m_vlcMediaPlayer, SIGNAL(seekableChanged(bool)), sl, SLOT(setEnabled(bool)));
        }
    }
    QProgressBar *bar = qobject_cast<QProgressBar *>(slider);
    m_progress = bar;
    if (bar != 0 && m_connectSlider) {
        bar->setOrientation(Qt::Horizontal);
        bar->setMaximum(1);
        bar->setTextVisible(false);
    }

    if (m_labelElapsed == 0)
        m_labelElapsed = new QLabel(this);
    m_labelElapsed->setText("--:--");

    if (m_labelFull == 0)
        m_labelFull = new QLabel(this);
    m_labelFull->setText("--:--");

    delete layout();
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(m_labelElapsed);
    layout->addWidget(slider);
    layout->addWidget(m_labelFull);
    setLayout(layout);
}

void QEXTVLCWidgetSeek::setAutoHide(bool autoHide)
{
    m_autoHide = autoHide;

    setVisible(!m_autoHide);
}

void QEXTVLCWidgetSeek::setMediaPlayer(QEXTVLCMediaPlayer *player)
{
    if (m_vlcMediaPlayer) {
        disconnect(m_vlcMediaPlayer, SIGNAL(lengthChanged(int)), this, SLOT(updateFullTime(int)));
        disconnect(m_vlcMediaPlayer, SIGNAL(timeChanged(int)), this, SLOT(updateCurrentTime(int)));
        disconnect(m_vlcMediaPlayer, SIGNAL(end()), this, SLOT(end()));
        disconnect(m_vlcMediaPlayer, SIGNAL(stopped()), this, SLOT(end()));
        if (m_slider != 0) {
            disconnect(m_slider, SIGNAL(valueChanged(int)), m_vlcMediaPlayer, SLOT(setTime(int)));
            disconnect(m_vlcMediaPlayer, SIGNAL(seekableChanged(bool)), m_slider, SLOT(setEnabled(bool)));
        }
    }

    m_vlcMediaPlayer = player;
    if (player == 0)
        return;

    connect(m_vlcMediaPlayer, SIGNAL(lengthChanged(int)), this, SLOT(updateFullTime(int)));
    connect(m_vlcMediaPlayer, SIGNAL(timeChanged(int)), this, SLOT(updateCurrentTime(int)));
    connect(m_vlcMediaPlayer, SIGNAL(end()), this, SLOT(end()));
    connect(m_vlcMediaPlayer, SIGNAL(stopped()), this, SLOT(end()));
    if (m_slider != 0 && m_connectSlider) {
        m_slider->setOrientation(Qt::Horizontal);
        m_slider->setMaximum(1);
        connect(m_slider, SIGNAL(valueChanged(int)), m_vlcMediaPlayer, SLOT(setTime(int)));
        connect(m_vlcMediaPlayer, SIGNAL(seekableChanged(bool)), m_slider, SLOT(setEnabled(bool)));
    } else if (m_progress != 0 && m_connectSlider) {
        m_progress->setOrientation(Qt::Horizontal);
        m_progress->setMaximum(1);
        m_progress->setTextVisible(false);
    }
}

void QEXTVLCWidgetSeek::setSliderWidget(QWidget *slider,
                                    bool updateSlider)
{
    m_connectSlider = updateSlider;
    if (slider == 0)
        return;
    if (slider == m_slider || slider == m_progress)
        return;
    delete m_slider;
    delete m_progress;
    initWidgetSeek(slider);
}

void QEXTVLCWidgetSeek::end()
{
    m_labelElapsed->setText("--:--");
    m_labelFull->setText("--:--");
    if (m_slider != 0 && m_connectSlider) {
        m_slider->setMaximum(1);
        m_slider->setValue(0);
    } else if (m_progress != 0 && m_connectSlider) {
        m_progress->setMaximum(1);
        m_progress->setValue(0);
    }
}

void QEXTVLCWidgetSeek::updateCurrentTime(int time)
{
    QTime currentTime = QTime(0, 0);
    currentTime = currentTime.addMSecs(time);

    QString display = "mm:ss";
    if (currentTime.hour() > 0)
        display = "hh:mm:ss";

    m_labelElapsed->setText(currentTime.toString(display));
    if (m_slider && m_connectSlider) {
        m_slider->blockSignals(true);
        m_slider->setValue(time);
        m_slider->blockSignals(false);
    } else if (m_progress && m_connectSlider) {
        m_progress->setValue(time);
    }
}

void QEXTVLCWidgetSeek::updateFullTime(int time)
{
    if (time == 0) {
        m_labelFull->setText("--:--");
    } else {
        QTime fullTime = QTime(0, 0);
        fullTime = fullTime.addMSecs(time);

        QString display = "mm:ss";
        if (fullTime.hour() > 0)
            display = "hh:mm:ss";

        m_labelFull->setText(fullTime.toString(display));
    }

    if (!time) {
        if (m_slider && m_connectSlider)
            m_slider->setMaximum(1);
        else if (m_progress && m_connectSlider)
            m_progress->setMaximum(1);
        setVisible(!m_autoHide);
    } else {
        if (m_slider && m_connectSlider) {
            m_slider->setMaximum(time);
            m_slider->setSingleStep(1000);
            m_slider->setPageStep(time / 100);
        }
        if (m_progress && m_connectSlider)
            m_progress->setMaximum(time);
        setVisible(true);
    }
}
