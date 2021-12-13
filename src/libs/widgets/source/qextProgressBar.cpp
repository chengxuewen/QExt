#include <qextProgressBar.h>
#include <qextProgressBar_p.h>
#include <QPainter>
#include <QTimer>
#include <QDebug>

QEXTProgressBarPrivate::QEXTProgressBarPrivate(QEXTProgressBar *q)
    : q_ptr(q)
{
    m_minValue = 0;
    m_maxValue = 100;
    m_value = 0;

    m_precision = 0;
    m_step = 0;
    m_space = 5;
    m_radius = 5;

    m_backgroundStartColor = QColor(100, 100, 100);
    m_backgroundEndColor = QColor(60, 60, 60);

    m_lineColor = QColor(230, 230, 230);
    m_textColor = QColor(0, 0, 0);

    m_barBackgroundColor = QColor(250, 250, 250);
    m_barColor = QColor(100, 184, 255);
}

QEXTProgressBarPrivate::~QEXTProgressBarPrivate()
{

}



QEXTProgressBar::QEXTProgressBar(QWidget *parent)
    : QWidget(parent)
    , dd_ptr(new QEXTProgressBarPrivate(this))
{    
    this->setFont(QFont("Arial", 8));
}

QEXTProgressBar::~QEXTProgressBar()
{

}

void QEXTProgressBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    this->drawBar(&painter);
}

void QEXTProgressBar::drawBackground(QPainter *painter)
{
    Q_D(QEXTProgressBar);
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPointF(0, 0), QPointF(0, height()));
    bgGradient.setColorAt(0.0, d->m_backgroundStartColor);
    bgGradient.setColorAt(1.0, d->m_backgroundEndColor);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void QEXTProgressBar::drawBar(QPainter *painter)
{
    Q_D(QEXTProgressBar);
    painter->save();

    QFont font;
    font.setPixelSize((width() / 10) * 0.35);
    painter->setFont(font);

    double currentValue = (double)(d->m_value - d->m_minValue) * 100 / (d->m_maxValue - d->m_minValue);
    QString strValue = QString("%1%").arg(currentValue, 0, 'f', d->m_precision);
    QString strMaxValue = QString("%1%").arg(d->m_maxValue, 0, 'f', d->m_precision);

    int textWidth = painter->fontMetrics().width(strMaxValue) + 10;

    QPointF textTopLeft(width() - d->m_space - textWidth, d->m_space);
    QPointF textBottomRight(width() - d->m_space, height() - d->m_space);
    QRectF textRect(textTopLeft, textBottomRight);
    painter->setPen(d->m_barBackgroundColor);
    painter->setBrush(d->m_barBackgroundColor);
    painter->drawRoundedRect(textRect, d->m_radius, d->m_radius);

    painter->setPen(d->m_textColor);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    QRectF barBgRect(QPointF(d->m_space, d->m_space), QPointF(width() - d->m_space * 2 - textWidth, height() - d->m_space));
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_barBackgroundColor);
    painter->drawRoundedRect(barBgRect, d->m_radius, d->m_radius);

    double length = width() - d->m_space  - d->m_space * 2 - textWidth;

    double increment = length / (d->m_maxValue - d->m_minValue);
    QRectF barRect(QPointF(d->m_space, d->m_space), QPointF(d->m_space + increment * (d->m_value - d->m_minValue), height() - d->m_space));
    painter->setBrush(d->m_barColor);
    painter->drawRoundedRect(barRect, d->m_radius, d->m_radius);

    painter->setPen(d->m_lineColor);
    int initX = 5;
    int lineCount = barBgRect.width() / d->m_step;
    double lineX = (double)barBgRect.width() / lineCount;

    while (lineCount > 0) {
        QPointF topPot(initX + lineX, d->m_space + 1);
        QPointF bottomPot(initX + lineX, height() - d->m_space - 1);
        painter->drawLine(topPot, bottomPot);
        initX += lineX;
        lineCount--;
    }

    painter->restore();
}

double QEXTProgressBar::minValue() const
{
    Q_D(const QEXTProgressBar);
    return d->m_minValue;
}

double QEXTProgressBar::maxValue() const
{
    Q_D(const QEXTProgressBar);
    return d->m_maxValue;
}

double QEXTProgressBar::value() const
{
    Q_D(const QEXTProgressBar);
    return d->m_value;
}

int QEXTProgressBar::precision() const
{
    Q_D(const QEXTProgressBar);
    return d->m_precision;
}

int QEXTProgressBar::step() const
{
    Q_D(const QEXTProgressBar);
    return d->m_step;
}

int QEXTProgressBar::space() const
{
    Q_D(const QEXTProgressBar);
    return d->m_space;
}

int QEXTProgressBar::radius() const
{
    Q_D(const QEXTProgressBar);
    return d->m_radius;
}

QColor QEXTProgressBar::backgroundStartColor() const
{
    Q_D(const QEXTProgressBar);
    return d->m_backgroundStartColor;
}

QColor QEXTProgressBar::backgroundEndColor() const
{
    Q_D(const QEXTProgressBar);
    return d->m_backgroundEndColor;
}

QColor QEXTProgressBar::lineColor() const
{
    Q_D(const QEXTProgressBar);
    return d->m_lineColor;
}

QColor QEXTProgressBar::textColor() const
{
    Q_D(const QEXTProgressBar);
    return d->m_textColor;
}

QColor QEXTProgressBar::barBackgroundColor() const
{
    Q_D(const QEXTProgressBar);
    return d->m_barBackgroundColor;
}

QColor QEXTProgressBar::barColor() const
{
    Q_D(const QEXTProgressBar);
    return d->m_barColor;
}

QSize QEXTProgressBar::sizeHint() const
{
    return QSize(300, 30);
}

QSize QEXTProgressBar::minimumSizeHint() const
{
    return QSize(50, 20);
}

void QEXTProgressBar::setRange(double minValue, double maxValue)
{
    Q_D(QEXTProgressBar);
    if (minValue >= maxValue) {
        return;
    }

    d->m_minValue = minValue;
    d->m_maxValue = maxValue;

    if (d->m_value < minValue || d->m_value > maxValue) {
        this->setValue(d->m_value);
    }

    this->update();
}

void QEXTProgressBar::setRange(int minValue, int maxValue)
{
    this->setRange((double)minValue, (double)maxValue);
}

void QEXTProgressBar::setMinValue(double minValue)
{
    Q_D(QEXTProgressBar);
    this->setRange(minValue, d->m_maxValue);
}

void QEXTProgressBar::setMaxValue(double maxValue)
{
    Q_D(QEXTProgressBar);
    this->setRange(d->m_minValue, maxValue);
}

void QEXTProgressBar::setValue(double value)
{
    Q_D(QEXTProgressBar);
    if (value == d->m_value) {
        return;
    }

    if (value < d->m_minValue) {
        value = d->m_minValue;
    } else if (value > d->m_maxValue) {
        value = d->m_maxValue;
    }

    d->m_value = value;
    emit this->valueChanged(value);
    this->update();
}

void QEXTProgressBar::setValue(int value)
{
    this->setValue((double)value);
}

void QEXTProgressBar::setPrecision(int precision)
{
    Q_D(QEXTProgressBar);
    if (precision <= 3 && d->m_precision != precision) {
        d->m_precision = precision;
        this->update();
    }
}

void QEXTProgressBar::setStep(int step)
{
    Q_D(QEXTProgressBar);
    if (d->m_step != step) {
        d->m_step = step;
        this->update();
    }
}

void QEXTProgressBar::setSpace(int space)
{
    Q_D(QEXTProgressBar);
    if (d->m_space != space) {
        d->m_space = space;
        this->update();
    }
}

void QEXTProgressBar::setRadius(int radius)
{
    Q_D(QEXTProgressBar);
    if (d->m_radius != radius) {
        d->m_radius = radius;
        this->update();
    }
}

void QEXTProgressBar::setBgColorStart(const QColor &color)
{
    Q_D(QEXTProgressBar);
    if (d->m_backgroundStartColor != color) {
        d->m_backgroundStartColor = color;
        this->update();
    }
}

void QEXTProgressBar::setBgColorEnd(const QColor &color)
{
    Q_D(QEXTProgressBar);
    if (d->m_backgroundEndColor != color) {
        d->m_backgroundEndColor = color;
        this->update();
    }
}

void QEXTProgressBar::setLineColor(const QColor &color)
{
    Q_D(QEXTProgressBar);
    if (d->m_lineColor != color) {
        d->m_lineColor = color;
        this->update();
    }
}

void QEXTProgressBar::setTextColor(const QColor &color)
{
    Q_D(QEXTProgressBar);
    if (d->m_textColor != color) {
        d->m_textColor = color;
        this->update();
    }
}

void QEXTProgressBar::setBarBgColor(const QColor &color)
{
    Q_D(QEXTProgressBar);
    if (d->m_barBackgroundColor != color) {
        d->m_barBackgroundColor = color;
        this->update();
    }
}

void QEXTProgressBar::setBarColor(const QColor &color)
{
    Q_D(QEXTProgressBar);
    if (d->m_barColor != color) {
        d->m_barColor = color;
        this->update();
    }
}
