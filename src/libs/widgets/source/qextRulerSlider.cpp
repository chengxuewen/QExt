#include <private/qextRulerSlider_p.h>

#include <QPainter>
#include <QMouseEvent>
#include <QEvent>
#include <QTimer>
#include <QDebug>


QEXTRulerSliderPrivate::QEXTRulerSliderPrivate(QEXTRulerSlider *q)
    : q_ptr(q)
{
    m_minValue = 0.0;
    m_maxValue = 100.0;
    m_value = 0.0;

    m_precision = 0;
    m_longStep = 10;
    m_shortStep = 1;
    m_space = 20;

    m_backgroundStartColor = QColor(100, 100, 100);
    m_backgroundEndColor = QColor(60, 60, 60);
    m_lineColor = QColor(255, 255, 255);

    m_sliderTopColor = QColor(100, 184, 255);
    m_sliderBottomColor = QColor(235, 235, 235);

    m_tipBackgroundColor = QColor(255, 255, 255);
    m_tipTextColor = QColor(50, 50, 50);

    m_pressed = false;
    m_currentValue = 0;
    m_sliderLastPot = QPointF(m_space, m_longLineHeight / 2);
}

QEXTRulerSliderPrivate::~QEXTRulerSliderPrivate()
{

}



QEXTRulerSlider::QEXTRulerSlider(QWidget *parent)
    : QWidget(parent)
    , dd_ptr(new QEXTRulerSliderPrivate(this))
{    
    this->setFont(QFont("Arial", 8));
}

QEXTRulerSlider::~QEXTRulerSlider()
{

}

void QEXTRulerSlider::resizeEvent(QResizeEvent *)
{
    Q_D(QEXTRulerSlider);
    d->m_longLineHeight = height() / 5;
    d->m_shortLineHeight = height() / 7;
    d->m_sliderTopHeight = height() / 7;
    d->m_sliderBottomHeight = height() / 6;

    if (this->isVisible()) {
        this->setValue(d->m_currentValue);
    }
}

void QEXTRulerSlider::showEvent(QShowEvent *)
{
    this->resizeEvent(NULL);
}

void QEXTRulerSlider::wheelEvent(QWheelEvent *event)
{
    Q_D(QEXTRulerSlider);
    QPoint numDegrees = event->angleDelta() / 8;
    QPoint numSteps = numDegrees / 15;

    if (!numSteps.isNull()) {
        double value = d->m_currentValue - numSteps.y();

        if (numSteps.y() > 0) {
            if (value > d->m_minValue) {
                this->setValue(value);
            } else {
                this->setValue(d->m_minValue);
            }
        } else {
            if (value < d->m_maxValue) {
                this->setValue(value);
            } else {
                this->setValue(d->m_maxValue);
            }
        }
    }
}

void QEXTRulerSlider::mousePressEvent(QMouseEvent *e)
{
    Q_D(QEXTRulerSlider);
    if (e->button() & Qt::LeftButton) {
        if (d->m_sliderRect.contains(e->pos())) {
            d->m_pressed = true;
            this->update();
        }
    }
}

void QEXTRulerSlider::mouseReleaseEvent(QMouseEvent *e)
{
    Q_D(QEXTRulerSlider);
    d->m_pressed = false;
    this->update();
}

void QEXTRulerSlider::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(QEXTRulerSlider);
    if (d->m_pressed) {
        if (e->pos().x() >= d->m_lineLeftPot.x() && e->pos().x() <= d->m_lineRightPot.x()) {
            double totalLineWidth = d->m_lineRightPot.x() - d->m_lineLeftPot.x();
            double dx = e->pos().x() - d->m_lineLeftPot.x();
            double ratio = (double)dx / totalLineWidth;
            d->m_sliderLastPot = QPointF(e->pos().x(), d->m_sliderTopPot.y());

            d->m_currentValue = (d->m_maxValue - d->m_minValue) * ratio + d->m_minValue;
            d->m_value = d->m_currentValue;
            emit this->valueChanged(d->m_currentValue);
            this->update();
        }
    }
}

void QEXTRulerSlider::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    this->drawBackground(&painter);
    this->drawRule(&painter);
    this->drawSlider(&painter);
    this->drawTip(&painter);
}

void QEXTRulerSlider::drawBackground(QPainter *painter)
{
    Q_D(QEXTRulerSlider);
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(0, 0, 0, height());
    bgGradient.setColorAt(0.0, d->m_backgroundStartColor);
    bgGradient.setColorAt(1.0, d->m_backgroundEndColor);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void QEXTRulerSlider::drawRule(QPainter *painter)
{
    Q_D(QEXTRulerSlider);
    painter->save();
    painter->setPen(d->m_lineColor);

    double initX = d->m_space;
    double initY = (double)height() / 2;
    d->m_lineLeftPot = QPointF(initX, initY);
    d->m_lineRightPot = QPointF(width() - initX, initY);
    painter->drawLine(d->m_lineLeftPot, d->m_lineRightPot);

    double length = width() - 2 * d->m_space;
    double increment = length / (d->m_maxValue - d->m_minValue);

    for (int i = d->m_minValue; i <= d->m_maxValue; i = i + d->m_shortStep) {
        if (i % d->m_longStep == 0) {
            QPointF topPot(initX, initY - d->m_longLineHeight);
            QPointF bottomPot(initX, initY);
            painter->drawLine(topPot, bottomPot);

            QString strValue = QString("%1").arg((double)i, 0, 'f', d->m_precision);
            double textWidth = fontMetrics().width(strValue);
            double textHeight = fontMetrics().height();
            QPointF textPot(initX - textWidth / 2, initY + textHeight);
            painter->drawText(textPot, strValue);
        } else {
            QPointF topPot(initX, initY - d->m_shortLineHeight);
            QPointF bottomPot(initX, initY);
            painter->drawLine(topPot, bottomPot);
        }

        initX += increment * d->m_shortStep;
    }

    painter->restore();
}

void QEXTRulerSlider::drawSlider(QPainter *painter)
{
    Q_D(QEXTRulerSlider);
    painter->save();

    d->m_sliderTopPot = QPointF(d->m_sliderLastPot.x(), d->m_lineLeftPot.y() - d->m_longLineHeight / 4);
    d->m_sliderLeftPot = QPointF(d->m_sliderTopPot.x() - width() / 100, d->m_sliderTopPot.y() + d->m_sliderTopHeight);
    d->m_sliderRightPot = QPointF(d->m_sliderTopPot.x() + width() / 100, d->m_sliderTopPot.y() + d->m_sliderTopHeight);

    painter->setPen(d->m_sliderTopColor);
    painter->setBrush(d->m_sliderTopColor);

    QVector<QPointF> potVec;
    potVec.append(d->m_sliderTopPot);
    potVec.append(d->m_sliderLeftPot);
    potVec.append(d->m_sliderRightPot);
    painter->drawPolygon(potVec);

    double indicatorLength = d->m_sliderRightPot.x() - d->m_sliderLeftPot.x();

    QPointF handleBottomRightPot(d->m_sliderLeftPot.x() + indicatorLength, d->m_sliderLeftPot.y() + d->m_sliderBottomHeight);
    d->m_sliderRect = QRectF(d->m_sliderLeftPot, handleBottomRightPot);

    QPointF tipRectTopLeftPot(d->m_sliderRect.topRight().x() + 2, d->m_sliderRect.topRight().y());
    QString strValue = QString("%1").arg(d->m_currentValue, 0, 'f', d->m_precision);

    double textLength = fontMetrics().width(strValue);
    double textHeight = fontMetrics().height();
    QPointF tipRectBottomRightPot(tipRectTopLeftPot.x() + textLength + 10, tipRectTopLeftPot.y() + textHeight + 5);
    d->m_tipRect = QRectF(tipRectTopLeftPot, tipRectBottomRightPot);

    painter->setPen(d->m_sliderBottomColor);
    painter->setBrush(d->m_sliderBottomColor);
    painter->drawRect(d->m_sliderRect);
    painter->restore();
}

void QEXTRulerSlider::drawTip(QPainter *painter)
{
    Q_D(QEXTRulerSlider);
    if (!d->m_pressed) {
        return;
    }

    painter->save();
    painter->setPen(d->m_tipTextColor);
    painter->setBrush(d->m_tipBackgroundColor);
    painter->drawRect(d->m_tipRect);
    QString strValue = QString("%1").arg(d->m_currentValue, 0, 'f', d->m_precision);
    painter->drawText(d->m_tipRect, Qt::AlignCenter, strValue);
    painter->restore();
}

double QEXTRulerSlider::minValue() const
{
    Q_D(const QEXTRulerSlider);
    return d->m_minValue;
}

double QEXTRulerSlider::maxValue() const
{
    Q_D(const QEXTRulerSlider);
    return d->m_maxValue;
}

double QEXTRulerSlider::value() const
{
    Q_D(const QEXTRulerSlider);
    return d->m_value;
}

int QEXTRulerSlider::precision() const
{
    Q_D(const QEXTRulerSlider);
    return d->m_precision;
}

int QEXTRulerSlider::longStep() const
{
    Q_D(const QEXTRulerSlider);
    return d->m_longStep;
}

int QEXTRulerSlider::shortStep() const
{
    Q_D(const QEXTRulerSlider);
    return d->m_shortStep;
}

int QEXTRulerSlider::space() const
{
    Q_D(const QEXTRulerSlider);
    return d->m_space;
}

QColor QEXTRulerSlider::backgroundStartColor() const
{
    Q_D(const QEXTRulerSlider);
    return d->m_backgroundStartColor;
}

QColor QEXTRulerSlider::backgroundEndColor() const
{
    Q_D(const QEXTRulerSlider);
    return d->m_backgroundEndColor;
}

QColor QEXTRulerSlider::lineColor() const
{
    Q_D(const QEXTRulerSlider);
    return d->m_lineColor;
}

QColor QEXTRulerSlider::sliderTopColor() const
{
    Q_D(const QEXTRulerSlider);
    return d->m_sliderTopColor;
}

QColor QEXTRulerSlider::sliderBottomColor() const
{
    Q_D(const QEXTRulerSlider);
    return d->m_sliderBottomColor;
}

QColor QEXTRulerSlider::tipBackgroundColor() const
{
    Q_D(const QEXTRulerSlider);
    return d->m_tipBackgroundColor;
}

QColor QEXTRulerSlider::tipTextColor() const
{
    Q_D(const QEXTRulerSlider);
    return d->m_tipTextColor;
}

QSize QEXTRulerSlider::sizeHint() const
{
    return QSize(500, 70);
}

QSize QEXTRulerSlider::minimumSizeHint() const
{
    return QSize(50, 50);
}

void QEXTRulerSlider::setRange(double minValue, double maxValue)
{
    Q_D(QEXTRulerSlider);
    if (minValue >= maxValue) {
        return;
    }

    d->m_minValue = minValue;
    d->m_maxValue = maxValue;
    this->setValue(minValue);
}

void QEXTRulerSlider::setRange(int minValue, int maxValue)
{
    this->setRange((double)minValue, (double)maxValue);
}

void QEXTRulerSlider::setMinValue(double minValue)
{
    Q_D(QEXTRulerSlider);
    this->setRange(minValue, d->m_maxValue);
}

void QEXTRulerSlider::setMaxValue(double maxValue)
{
    Q_D(QEXTRulerSlider);
    this->setRange(d->m_minValue, maxValue);
}

void QEXTRulerSlider::setValue(double value)
{
    Q_D(QEXTRulerSlider);
    if (value == d->m_value) {
        return;
    }

    if (value < d->m_minValue) {
        value = d->m_minValue;
    } else if (value > d->m_maxValue) {
        value = d->m_maxValue;
    }

    double lineWidth = width() - 2 * d->m_space;
    double ratio = (double)(value - d->m_minValue) / (d->m_maxValue - d->m_minValue);
    double x = lineWidth * ratio;
    double newX = x + d->m_space;
    double y = d->m_space + d->m_longLineHeight - 10;
    d->m_sliderLastPot = QPointF(newX, y);

    d->m_value = value;
    d->m_currentValue = value;
    emit this->valueChanged(value);
    this->update();
}

void QEXTRulerSlider::setValue(int value)
{
    this->setValue((double)value);
}

void QEXTRulerSlider::setPrecision(int precision)
{
    Q_D(QEXTRulerSlider);
    if (precision <= 3 && d->m_precision != precision) {
        d->m_precision = precision;
        this->update();
    }
}

void QEXTRulerSlider::setLongStep(int longStep)
{
    Q_D(QEXTRulerSlider);
    if (longStep < d->m_shortStep) {
        return;
    }

    if (d->m_longStep != longStep) {
        d->m_longStep = longStep;
        this->update();
    }
}

void QEXTRulerSlider::setShortStep(int shortStep)
{
    Q_D(QEXTRulerSlider);
    if (d->m_longStep < shortStep) {
        return;
    }

    if (d->m_shortStep != shortStep) {
        d->m_shortStep = shortStep;
        this->update();
    }
}

void QEXTRulerSlider::setSpace(int space)
{
    Q_D(QEXTRulerSlider);
    if (d->m_space != space) {
        d->m_space = space;
        this->update();
    }
}

void QEXTRulerSlider::setBackgroundStartColor(const QColor &color)
{
    Q_D(QEXTRulerSlider);
    if (d->m_backgroundStartColor != color) {
        d->m_backgroundStartColor = color;
        this->update();
    }
}

void QEXTRulerSlider::setBackgroundEndColor(const QColor &color)
{
    Q_D(QEXTRulerSlider);
    if (d->m_backgroundEndColor != color) {
        d->m_backgroundEndColor = color;
        this->update();
    }
}

void QEXTRulerSlider::setLineColor(const QColor &color)
{
    Q_D(QEXTRulerSlider);
    if (d->m_lineColor != color) {
        d->m_lineColor = color;
        this->update();
    }
}

void QEXTRulerSlider::setSliderTopColor(const QColor &color)
{
    Q_D(QEXTRulerSlider);
    if (d->m_sliderTopColor != color) {
        d->m_sliderTopColor = color;
        this->update();
    }
}

void QEXTRulerSlider::setSliderBottomColor(const QColor &color)
{
    Q_D(QEXTRulerSlider);
    if (d->m_sliderBottomColor != color) {
        d->m_sliderBottomColor = color;
        this->update();
    }
}

void QEXTRulerSlider::setTipBackgroundColor(const QColor &color)
{
    Q_D(QEXTRulerSlider);
    if (d->m_tipBackgroundColor != color) {
        d->m_tipBackgroundColor = color;
        this->update();
    }
}

void QEXTRulerSlider::setTipTextColor(const QColor &color)
{
    Q_D(QEXTRulerSlider);
    if (d->m_tipTextColor != color) {
        d->m_tipTextColor = color;
        this->update();
    }
}
