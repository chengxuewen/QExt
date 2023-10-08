#include <private/qextLed_p.h>

#include <QPainter>
#include <QPainterPath>
#include <QRadialGradient>


QEXTLedPrivate::QEXTLedPrivate(QEXTLed *q)
    : q_ptr(q)
{
    m_color = QColor(107, 223, 51);
    m_on = true;
}

QEXTLedPrivate::~QEXTLedPrivate()
{

}



QEXTLed::QEXTLed(QWidget *parent)
    : QWidget(parent), dd_ptr(new QEXTLedPrivate(this))
{

}

QEXTLed::~QEXTLed()
{

}

QColor QEXTLed::color() const
{
    Q_D(const QEXTLed);
    return d->m_color;
}

QSize QEXTLed::sizeHint() const
{
    return QSize(20,20);
}

QSize QEXTLed::minimumSizeHint() const
{
    return QSize(10, 10);
}

void QEXTLed::setColor(const QColor &color)
{
    Q_D(QEXTLed);
    if (d->m_color != color)
    {
        d->m_color = color;
        this->update();
        emit this->colorChanged(d->m_color);
    }
}

bool QEXTLed::isOn() const
{
    Q_D(const QEXTLed);
    return d->m_on;
}

void QEXTLed::setOn(bool on)
{
    Q_D(QEXTLed);
    if (on != d->m_on)
    {
        d->m_on = on;
        this->update();
        emit this->stateChanged(on);
    }
}

void QEXTLed::turnOn()
{
    setOn(true);
}

void QEXTLed::turnOff()
{
    this->setOn(false);
}

void QEXTLed::toggle()
{
    Q_D(QEXTLed);
    this->setOn(!d->m_on);
}

void QEXTLed::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    Q_D(QEXTLed);
    const qreal r = std::min(width(), height()) / 2; // maximum radius including glow
    const qreal glowOffset = std::max(2., r/5.);
    const qreal borderOffset = std::max(1., r/10.);
    const qreal shineOffset = std::max(1., r/20.);
    const QPointF center(width()/2, height()/2);

    const qreal gr = r;
    const qreal br = gr - glowOffset;   // border shape radius
    const qreal ir = br - borderOffset; // inner fill radius
    const qreal sr = ir - shineOffset;

    QColor borderColor(130,130,130);
    QColor shineColor(255, 255, 255, d->m_on ? 200 : 50);
    QColor fillColor(d->m_color);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    // draw border
    painter.setPen(Qt::NoPen);
    painter.setBrush(borderColor);
    painter.drawEllipse(center, br, br);

    // draw infill
    if (!d->m_on) fillColor = fillColor.darker();
    painter.setBrush(fillColor);
    painter.drawEllipse(center, ir, ir);

    // draw glow
    if (d->m_on)
    {
        QColor glowColor(d->m_color);
        glowColor.setAlphaF(0.5);
        QRadialGradient glowGradient(center, gr, center);
        glowGradient.setColorAt(0, glowColor);
        glowGradient.setColorAt((r-glowOffset)/r, glowColor);
        glowGradient.setColorAt(1, Qt::transparent);
        painter.setBrush(glowGradient);
        painter.drawEllipse(center, gr, gr);
    }

    // draw shine
    QRadialGradient shineGradient(center, sr, center-QPoint(sr/2,sr/2));
    shineGradient.setColorAt(0, shineColor);
    shineGradient.setColorAt(1, Qt::transparent);
    painter.setBrush(shineGradient);
    painter.drawEllipse(center, sr, sr);
}
