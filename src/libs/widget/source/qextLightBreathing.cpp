#pragma execution_character_set("utf-8")

#include <qextLightBreathing.h>
#include <qextLightBreathing_p.h>

#include <QDebug>
#include <QPainter>
#include <QTimer>


QEXTLightBreathingPrivate::QEXTLightBreathingPrivate(QEXTLightBreathing *qq)
    : QEXTObjectPrivate(qq)
{
    m_step = 10;
    m_interval = 100;
    m_backgroundColor = QColor(255, 0, 0);
    m_offset = 0;
    m_isAdd = true;
}

QEXTLightBreathingPrivate::~QEXTLightBreathingPrivate()
{
    if (m_timer->isActive())
    {
        m_timer->stop();
    }
}


QEXTLightBreathing::QEXTLightBreathing(QWidget *parent)
    : QWidget(parent), QEXTObject(*(new QEXTLightBreathingPrivate(this)))
{
    QEXT_DECL_D(QEXTLightBreathing);
    d->m_timer.reset(new QTimer);
    connect(d->m_timer.data(), SIGNAL(timeout()), this, SLOT(update()));
    d->m_timer->start(100);
}

QEXTLightBreathing::~QEXTLightBreathing()
{

}


int QEXTLightBreathing::step() const
{
    QEXT_DECL_DC(QEXTLightBreathing);
    return d->m_step;
}

int QEXTLightBreathing::interval() const
{
    QEXT_DECL_DC(QEXTLightBreathing);
    return d->m_interval;
}

QColor QEXTLightBreathing::backgroundColor() const
{
    QEXT_DECL_DC(QEXTLightBreathing);
    return d->m_backgroundColor;
}

QSize QEXTLightBreathing::sizeHint() const
{
    return QSize(100, 100);
}

QSize QEXTLightBreathing::minimumSizeHint() const
{
    return QSize(5, 5);
}

void QEXTLightBreathing::setStep(const int &step)
{
    QEXT_DECL_D(QEXTLightBreathing);
    if (step <= 0) {
        qCritical() << "QEXTLightBreathing::setStep():iStep must be greate than zero!";
        return;
    }
    if (step != d->m_step) {
        d->m_step = step;
        this->update();
    }
}

void QEXTLightBreathing::setInterval(const int &interval)
{
    QEXT_DECL_D(QEXTLightBreathing);
    if (interval <= 0) {
        qCritical() << "QEXTLightBreathing::setInterval():iInterval must be greate than zero!";
        return;
    }
    if (interval != d->m_interval) {
        d->m_interval = interval;
        this->update();
    }
}

void QEXTLightBreathing::setBackgroundColor(const QColor &color)
{
    QEXT_DECL_D(QEXTLightBreathing);
    if (color != d->m_backgroundColor) {
        d->m_backgroundColor = color;
        this->update();
    }
}

void QEXTLightBreathing::paintEvent(QPaintEvent *)
{
    QEXT_DECL_D(QEXTLightBreathing);
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制背景
    this->drawBackground(&painter);
}

void QEXTLightBreathing::drawBackground(QPainter *painter)
{
    QEXT_DECL_D(QEXTLightBreathing);
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
