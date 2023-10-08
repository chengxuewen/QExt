#include <private/qextBreathingLight_p.h>

#include <QDebug>
#include <QPainter>
#include <QTimer>

QEXTBreathingLightPrivate::QEXTBreathingLightPrivate(QEXTBreathingLight *q)
    : q_ptr(q)
{
    m_step = 10;
    m_interval = 100;
    m_backgroundColor = QColor(255, 0, 0);
    m_offset = 0;
    m_isAdd = true;
}

QEXTBreathingLightPrivate::~QEXTBreathingLightPrivate()
{
    if (m_timer->isActive())
    {
        m_timer->stop();
    }
}


QEXTBreathingLight::QEXTBreathingLight(QWidget *parent)
    : QWidget(parent), dd_ptr(new QEXTBreathingLightPrivate(this))
{
    Q_D(QEXTBreathingLight);
    d->m_timer.reset(new QTimer);
    connect(d->m_timer.data(), SIGNAL(timeout()), this, SLOT(update()));
    d->m_timer->start(100);
}

QEXTBreathingLight::~QEXTBreathingLight()
{

}


int QEXTBreathingLight::step() const
{
    Q_D(const QEXTBreathingLight);
    return d->m_step;
}

int QEXTBreathingLight::interval() const
{
    Q_D(const QEXTBreathingLight);
    return d->m_interval;
}

QColor QEXTBreathingLight::backgroundColor() const
{
    Q_D(const QEXTBreathingLight);
    return d->m_backgroundColor;
}

QSize QEXTBreathingLight::sizeHint() const
{
    return QSize(100, 100);
}

QSize QEXTBreathingLight::minimumSizeHint() const
{
    return QSize(5, 5);
}

void QEXTBreathingLight::setStep(const int &step)
{
    Q_D(QEXTBreathingLight);
    if (step <= 0) {
        qCritical() << "QEXTBreathingLight::setStep():iStep must be greate than zero!";
        return;
    }
    if (step != d->m_step) {
        d->m_step = step;
        this->update();
    }
}

void QEXTBreathingLight::setInterval(const int &interval)
{
    Q_D(QEXTBreathingLight);
    if (interval <= 0) {
        qCritical() << "QEXTBreathingLight::setInterval():iInterval must be greate than zero!";
        return;
    }
    if (interval != d->m_interval) {
        d->m_interval = interval;
        this->update();
    }
}

void QEXTBreathingLight::setBackgroundColor(const QColor &color)
{
    Q_D(QEXTBreathingLight);
    if (color != d->m_backgroundColor) {
        d->m_backgroundColor = color;
        this->update();
    }
}

void QEXTBreathingLight::paintEvent(QPaintEvent *)
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

void QEXTBreathingLight::drawBackground(QPainter *painter)
{
    Q_D(QEXTBreathingLight);
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
