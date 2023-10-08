#include <private/qextOvenTimer_p.h>

#include <QPainter>
#include <QEvent>
#include <QTimer>
#include <QMouseEvent>
#include <QDateTime>
#include <QPixmap>
#include <QDebug>
#include <qmath.h>

const double DegreesPerMinute = 7.0;
const double DegreesPerSecond = DegreesPerMinute / 60;
const int MaxMinutes = 45;
const int MaxSeconds = MaxMinutes * 60;
const int UpdateInterval = 1;

QEXTOvenTimerPrivate::QEXTOvenTimerPrivate(QEXTOvenTimer *q)
    : q_ptr(q)
{

}

QEXTOvenTimerPrivate::~QEXTOvenTimerPrivate()
{
    if (m_updateTimer->isActive()) {
        m_updateTimer->stop();
    }

    if (m_finishTimer->isActive()) {
        m_finishTimer->stop();
    }
}



QEXTOvenTimer::QEXTOvenTimer(QWidget *parent)
    : QWidget(parent)
    , dd_ptr(new QEXTOvenTimerPrivate(this))
{
    Q_D(QEXTOvenTimer);
    d->m_finishTime = QDateTime::currentDateTime();

    d->m_updateTimer = new QTimer(this);
    connect(d->m_updateTimer, SIGNAL(timeout()), this, SLOT(update()));

    d->m_finishTimer = new QTimer(this);
    d->m_finishTimer->setSingleShot(true);
    connect(d->m_finishTimer, SIGNAL(timeout()), this, SIGNAL(timeout()));
    connect(d->m_finishTimer, SIGNAL(timeout()), d->m_updateTimer, SLOT(stop()));

    setFont(QFont("Arial", 8));
}

QEXTOvenTimer::~QEXTOvenTimer()
{

}

void QEXTOvenTimer::mousePressEvent(QMouseEvent *event)
{
    QPointF point = event->pos() - rect().center();
    double theta = qAtan2(-point.x(), point.y()) * 180.0 / M_PI;
    this->setDuration(duration() + int(theta / DegreesPerSecond));
}

void QEXTOvenTimer::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setViewport((width - side) / 2, (height - side) / 2, side, side);
    painter.setWindow(-50, -50, 100, 100);
    this->draw(&painter);
}

void QEXTOvenTimer::draw(QPainter *painter)
{
    static const int triangle[3][2] = {
        {-2, -49}, {+2, -49}, {0, -47}
    };

    QPen thickPen(palette().windowText(), 1.5);
    QPen thinPen(palette().windowText(), 0.5);

    painter->setPen(thinPen);
    painter->setBrush(palette().windowText());
    painter->drawPolygon(QPolygon(3, &triangle[0][0]));

    QConicalGradient coneGradient(0, 0, -90.0);
    coneGradient.setColorAt(0.0, Qt::darkGray);
    coneGradient.setColorAt(0.5, Qt::white);
    coneGradient.setColorAt(1.0, Qt::darkGray);

    painter->setBrush(coneGradient);
    painter->drawEllipse(-46, -46, 92, 92);

    QRadialGradient haloGradient(0, 0, 20, 0, 0);
    haloGradient.setColorAt(0.0, Qt::lightGray);
    haloGradient.setColorAt(0.8, Qt::darkGray);
    haloGradient.setColorAt(0.9, Qt::white);
    haloGradient.setColorAt(1.0, Qt::black);

    painter->setPen(Qt::NoPen);
    painter->setBrush(haloGradient);
    painter->drawEllipse(-20, -20, 40, 40);

    QLinearGradient knobGradient(-7, -25, 7, -25);
    knobGradient.setColorAt(0.0, Qt::black);
    knobGradient.setColorAt(0.3, Qt::lightGray);
    knobGradient.setColorAt(0.8, Qt::white);
    knobGradient.setColorAt(1.0, Qt::black);

    painter->setPen(Qt::NoPen);
    painter->setBrush(knobGradient);
    painter->rotate(duration()*DegreesPerSecond);
    painter->drawRoundedRect(-7, -25, 14, 50, 10, 10);

    for (int i = 0; i <= MaxMinutes; ++i) {
        painter->save();
        painter->rotate(-i * DegreesPerMinute);

        if (i % 5 == 0) {
            painter->setPen(thickPen);
            painter->drawLine(0, -41, 0, -44);
            painter->drawText(-15, -41, 30, 30, Qt::AlignHCenter | Qt::AlignTop, QString::number(i));
        } else {
            painter->setPen(thinPen);
            painter->drawLine(0, -42, 0, -44);
        }

        painter->restore();
    }
}

int QEXTOvenTimer::duration() const
{
    Q_D(const QEXTOvenTimer);
    int secs = QDateTime::currentDateTime().secsTo(d->m_finishTime);
    if (secs < 0) {
        secs = 0;
    }
    return secs;
}

QSize QEXTOvenTimer::sizeHint() const
{
    return QSize(200, 200);
}

QSize QEXTOvenTimer::minimumSizeHint() const
{
    return QSize(50, 50);
}

void QEXTOvenTimer::setDuration(int secs)
{
    Q_D(QEXTOvenTimer);
    secs = qBound(0, secs, MaxSeconds);

    d->m_finishTime = QDateTime::currentDateTime().addSecs(secs);
    if (secs > 0) {
        d->m_updateTimer->start(UpdateInterval * 1000);
        d->m_finishTimer->start(secs * 1000);
    } else {
        d->m_updateTimer->stop();
        d->m_finishTimer->stop();
    }

    update();
}
