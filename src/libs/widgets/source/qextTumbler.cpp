#include <qextTumbler.h>
#include <qextTumbler_p.h>

#include <QPainter>
#include <QEvent>
#include <QWheelEvent>
#include <QDebug>

QEXTTumblerPrivate::QEXTTumblerPrivate(QEXTTumbler *q)
    : q_ptr(q)
{
    m_currentIndex = 0;
    m_currentValue = "1";

    for (int i = 1; i <= 12; i++)
    {
        m_valueList.append(QString::number(i));
    }

    m_foregroundColor = QColor(140, 140, 140);
    m_backgroundColor = QColor(40, 40, 40);
    m_lineColor = QColor(46, 142, 180, 200);
    m_textColor = QColor(255, 255, 255);

    m_isHorizontal = false;

    m_percent = 3;
    m_offset = 0;
    m_pressed = 0;
    m_pressedPos = 0;
    m_currentPos = 0;
}

QEXTTumblerPrivate::~QEXTTumblerPrivate()
{

}



QEXTTumbler::QEXTTumbler(QWidget *parent)
    : QWidget(parent), dd_ptr(new QEXTTumblerPrivate(this))
{
    this->setFont(QFont("Arial", 8));
}

QEXTTumbler::~QEXTTumbler()
{

}

void QEXTTumbler::wheelEvent(QWheelEvent *e)
{
    Q_D(QEXTTumbler);
    int degrees = e->delta() / 8;

    int steps = degrees / 15;

    if (e->orientation() == Qt::Vertical)
    {
        int index = d->m_currentIndex - steps;

        if (steps > 0)
        {
            if (index > 0)
            {
                this->setCurrentIndex(index);
            }
            else
            {
                this->setCurrentIndex(0);
            }
        }
        else
        {
            if (index < d->m_valueList.count() - 1)
            {
                this->setCurrentIndex(index);
            }
            else
            {
                this->setCurrentIndex(d->m_valueList.count() - 1);
            }
        }
    }
}

void QEXTTumbler::mousePressEvent(QMouseEvent *e)
{
    Q_D(QEXTTumbler);
    d->m_pressed = true;
    int target = e->pos().x();

    if (!d->m_isHorizontal)
    {
        target = e->pos().y();
    }

    d->m_pressedPos = target;
}

void QEXTTumbler::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(QEXTTumbler);
    int count = d->m_valueList.count();

    if (count <= 1)
    {
        return;
    }

    int pos = e->pos().x();
    int target = this->width();

    if (!d->m_isHorizontal)
    {
        pos = e->pos().y();
        target = this->height();
    }

    int index = d->m_valueList.indexOf(d->m_currentValue);

    if (d->m_pressed)
    {
        if ((index == 0 && pos >= d->m_pressedPos) || (index == count - 1 && pos <= d->m_pressedPos))
        {
            return;
        }

        d->m_offset = pos - d->m_pressedPos;

        if (d->m_offset > target / d->m_percent)
        {
            d->m_offset = target / d->m_percent;
        }
        else if (d->m_offset < -target / d->m_percent)
        {
            d->m_offset = -target / d->m_percent;
        }

        static int oldIndex = -1;

        if (oldIndex != index)
        {
            emit this->currentIndexChanged(index);
            emit this->currentValueChanged(d->m_valueList.at(index));
            oldIndex = index;
        }

        this->update();
    }
}

void QEXTTumbler::mouseReleaseEvent(QMouseEvent *)
{
    Q_D(QEXTTumbler);
    if (d->m_pressed)
    {
        d->m_pressed = false;
        this->checkPosition();
    }
}

void QEXTTumbler::paintEvent(QPaintEvent *)
{
    Q_D(QEXTTumbler);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    int count = d->m_valueList.count();

    if (count <= 1)
    {
        return;
    }

    int target = this->width();

    if (!d->m_isHorizontal)
    {
        target = this->height();
    }

    int index = d->m_valueList.indexOf(d->m_currentValue);

    if (d->m_offset >= target / d->m_percent && index > 0)
    {
        d->m_pressedPos += target / d->m_percent;
        d->m_offset -= target / d->m_percent;
        index -= 1;
    }

    if (d->m_offset <= -target / d->m_percent && index < count - 1)
    {
        d->m_pressedPos -= target / d->m_percent;
        d->m_offset += target / d->m_percent;
        index += 1;
    }

    d->m_currentIndex = index;
    d->m_currentValue = d->m_valueList.at(index);

    this->drawBackground(&painter);

    this->drawLine(&painter);

    painter.setPen(d->m_textColor);
    this->drawText(&painter, index, d->m_offset);
    painter.setPen(d->m_foregroundColor);

    if (index != 0)
    {
        this->drawText(&painter, index - 1, d->m_offset - target / d->m_percent);
    }

    if (index != count - 1)
    {
        this->drawText(&painter, index + 1, d->m_offset + target / d->m_percent);
    }
}

void QEXTTumbler::drawBackground(QPainter *painter)
{
    Q_D(QEXTTumbler);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_backgroundColor);
    painter->drawRect(rect());
    painter->restore();
}

void QEXTTumbler::drawLine(QPainter *painter)
{
    Q_D(QEXTTumbler);
    int offset = 10;
    int width = this->width();
    int height = this->height();

    painter->save();
    painter->setBrush(Qt::NoBrush);

    QPen pen;
    pen.setWidth(3);
    pen.setColor(d->m_lineColor);
    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);

    if (d->m_isHorizontal)
    {
        painter->drawLine(width / 3 * 1, offset, width / 3 * 1, height - offset);
        painter->drawLine(width / 3 * 2, offset, width / 3 * 2, height - offset);
    }
    else
    {
        painter->drawLine(offset, height / 3 * 1, width - offset,  height / 3 * 1);
        painter->drawLine(offset, height / 3 * 2, width - offset,  height / 3 * 2);
    }

    painter->restore();
}

void QEXTTumbler::drawText(QPainter *painter, int index, int offset)
{
    Q_D(QEXTTumbler);
    painter->save();

    int width = this->width();
    int height = this->height();
    QString strValue = d->m_valueList.at(index);

    int target = width;

    if (!d->m_isHorizontal)
    {
        target = height;
    }

    QFont font = painter->font();
    font.setPixelSize((target - qAbs(offset)) / 8);
    painter->setFont(font);

    if (d->m_isHorizontal)
    {
        int textWidth = painter->fontMetrics().width(strValue);
        int initX = width / 2 + offset - textWidth / 2;
        painter->drawText(QRect(initX, 0, textWidth, height), Qt::AlignCenter, strValue);

        if (index == d->m_currentIndex)
        {
            d->m_currentPos = initX;
        }
    }
    else
    {
        int textHeight = painter->fontMetrics().height();
        int initY = height / 2 + offset - textHeight / 2;
        painter->drawText(QRect(0, initY, width, textHeight), Qt::AlignCenter, strValue);

        if (index == d->m_currentIndex)
        {
            d->m_currentPos = initY;
        }
    }

    painter->restore();
}

void QEXTTumbler::checkPosition()
{
    Q_D(QEXTTumbler);
    int target = this->width();

    if (!d->m_isHorizontal)
    {
        target = this->height();
    }

    if (d->m_offset < 0)
    {
        if (d->m_currentPos < target / 2)
        {
            d->m_offset = 0;
            this->setCurrentIndex(d->m_currentIndex + 1);
        }
    }
    else
    {
        if (d->m_currentPos > target / 2)
        {
            d->m_offset = 0;
            this->setCurrentIndex(d->m_currentIndex - 1);
        }
    }
}

QStringList QEXTTumbler::valueList() const
{
    Q_D(const QEXTTumbler);
    return d->m_valueList;
}

int QEXTTumbler::currentIndex() const
{
    Q_D(const QEXTTumbler);
    return d->m_currentIndex;
}

QString QEXTTumbler::currentValue() const
{
    Q_D(const QEXTTumbler);
    return d->m_currentValue;
}

bool QEXTTumbler::isHorizontal() const
{
    Q_D(const QEXTTumbler);
    return d->m_isHorizontal;
}

QColor QEXTTumbler::foregroundColor() const
{
    Q_D(const QEXTTumbler);
    return d->m_foregroundColor;
}

QColor QEXTTumbler::backgroundColor() const
{
    Q_D(const QEXTTumbler);
    return d->m_backgroundColor;
}

QColor QEXTTumbler::lineColor() const
{
    Q_D(const QEXTTumbler);
    return d->m_lineColor;
}

QColor QEXTTumbler::textColor() const
{
    Q_D(const QEXTTumbler);
    return d->m_textColor;
}

QSize QEXTTumbler::sizeHint() const
{
    return QSize(50, 150);
}

QSize QEXTTumbler::minimumSizeHint() const
{
    return QSize(10, 10);
}

void QEXTTumbler::setValueList(const QStringList &values)
{
    Q_D(QEXTTumbler);
    if (values.count() > 0)
    {
        d->m_valueList = values;
        this->setCurrentIndex(0);
        this->setCurrentValue(values.at(0));
        this->update();
    }
}

void QEXTTumbler::setCurrentIndex(int index)
{
    Q_D(QEXTTumbler);
    if (index >= 0)
    {
        d->m_currentIndex = index;
        d->m_currentValue = d->m_valueList.at(index);
        emit this->currentIndexChanged(d->m_currentIndex);
        emit this->currentValueChanged(d->m_currentValue);
        this->update();
    }
}

void QEXTTumbler::setCurrentValue(const QString &value)
{
    Q_D(QEXTTumbler);
    if (d->m_valueList.contains(value))
    {
        d->m_currentValue = value;
        d->m_currentIndex = d->m_valueList.indexOf(value);
        emit this->currentIndexChanged(d->m_currentIndex);
        emit this->currentValueChanged(d->m_currentValue);
        this->update();
    }
}

void QEXTTumbler::setHorizontal(bool horizontal)
{
    Q_D(QEXTTumbler);
    if (d->m_isHorizontal != horizontal)
    {
        d->m_isHorizontal = horizontal;
        this->update();
    }
}

void QEXTTumbler::setForegroundColor(const QColor &color)
{
    Q_D(QEXTTumbler);
    if (d->m_foregroundColor != color)
    {
        d->m_foregroundColor = color;
        this->update();
    }
}

void QEXTTumbler::setBackgroundColor(const QColor &color)
{
    Q_D(QEXTTumbler);
    if (d->m_backgroundColor != color)
    {
        d->m_backgroundColor = color;
        this->update();
    }
}

void QEXTTumbler::setLineColor(const QColor &color)
{
    Q_D(QEXTTumbler);
    if (d->m_lineColor != color)
    {
        d->m_lineColor = color;
        this->update();
    }
}

void QEXTTumbler::setTextColor(const QColor &color)
{
    Q_D(QEXTTumbler);
    if (d->m_textColor != color)
    {
        d->m_textColor = color;
        this->update();
    }
}
