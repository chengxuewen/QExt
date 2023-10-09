/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2019 feiyangqingyun. Contact: QQ:517216493
** Copyright (C) 2021~Present ChengXueWen. Contact: 1398831004@qq.com
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#include <private/qextBreathingLight_p.h>

#include <QDebug>
#include <QPainter>
#include <QTimer>

QExtBreathingLightPrivate::QExtBreathingLightPrivate(QExtBreathingLight *q)
    : q_ptr(q)
{
    m_step = 10;
    m_interval = 100;
    m_backgroundColor = QColor(255, 0, 0);
    m_offset = 0;
    m_isAdd = true;
}

QExtBreathingLightPrivate::~QExtBreathingLightPrivate()
{
    if (m_timer->isActive())
    {
        m_timer->stop();
    }
}


QExtBreathingLight::QExtBreathingLight(QWidget *parent)
    : QWidget(parent), dd_ptr(new QExtBreathingLightPrivate(this))
{
    Q_D(QExtBreathingLight);
    d->m_timer.reset(new QTimer);
    connect(d->m_timer.data(), SIGNAL(timeout()), this, SLOT(update()));
    d->m_timer->start(100);
}

QExtBreathingLight::~QExtBreathingLight()
{

}


int QExtBreathingLight::step() const
{
    Q_D(const QExtBreathingLight);
    return d->m_step;
}

int QExtBreathingLight::interval() const
{
    Q_D(const QExtBreathingLight);
    return d->m_interval;
}

QColor QExtBreathingLight::backgroundColor() const
{
    Q_D(const QExtBreathingLight);
    return d->m_backgroundColor;
}

QSize QExtBreathingLight::sizeHint() const
{
    return QSize(100, 100);
}

QSize QExtBreathingLight::minimumSizeHint() const
{
    return QSize(5, 5);
}

void QExtBreathingLight::setStep(const int &step)
{
    Q_D(QExtBreathingLight);
    if (step <= 0) {
        qCritical() << "QExtBreathingLight::setStep():iStep must be greate than zero!";
        return;
    }
    if (step != d->m_step) {
        d->m_step = step;
        this->update();
    }
}

void QExtBreathingLight::setInterval(const int &interval)
{
    Q_D(QExtBreathingLight);
    if (interval <= 0) {
        qCritical() << "QExtBreathingLight::setInterval():iInterval must be greate than zero!";
        return;
    }
    if (interval != d->m_interval) {
        d->m_interval = interval;
        this->update();
    }
}

void QExtBreathingLight::setBackgroundColor(const QColor &color)
{
    Q_D(QExtBreathingLight);
    if (color != d->m_backgroundColor) {
        d->m_backgroundColor = color;
        this->update();
    }
}

void QExtBreathingLight::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    this->drawBackground(&painter);
}

void QExtBreathingLight::drawBackground(QPainter *painter)
{
    Q_D(QExtBreathingLight);
    painter->save();

    int radius = 99;
    QRadialGradient gradient(QPoint(0, 0), radius);

    (d->m_offset < 70 && d->m_isAdd) ? (d->m_offset += d->m_step) : (d->m_isAdd = false);
    (d->m_offset > 0 && !d->m_isAdd) ? (d->m_offset -= d->m_step) : (d->m_isAdd = true);

    d->m_backgroundColor.setAlpha(255);
    gradient.setColorAt(0.1, d->m_backgroundColor);
    d->m_backgroundColor.setAlpha(100 + d->m_offset);
    gradient.setColorAt(0.3, d->m_backgroundColor);
    d->m_backgroundColor.setAlpha(50 + d->m_offset);
    gradient.setColorAt(0.6, d->m_backgroundColor);
    d->m_backgroundColor.setAlpha(0);
    gradient.setColorAt(1.0, d->m_backgroundColor);

    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    painter->restore();
}
