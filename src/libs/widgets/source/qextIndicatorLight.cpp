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

#include <private/qextIndicatorLight_p.h>

#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QPainterPath>


QExtIndicatorLightPrivate::QExtIndicatorLightPrivate(QExtIndicatorLight *q)
    : q_ptr(q)
{
    m_text = "";
    m_style = QExtIndicatorLight::Style_Red;
    m_shape = QExtIndicatorLight::Shape_Circle;
    m_lightTextColor = QColor(255, 255, 255);
    m_normalTextColor = QColor(255, 255, 255);
    m_lightBackgroundColor = QColor(255, 0, 0);
    m_normalBackgroundColor = QColor(175, 175, 175);
    m_fontPixelSize = 80;

    m_outBorderStartColor = QColor(255, 255, 255);
    m_outBorderEndColor = QColor(166, 166, 166);
    m_inBorderStartColor = QColor(166, 166, 166);
    m_inBorderEndColor = QColor(255, 255, 255);

    m_moveEnable = false;
    m_overlayVisible = true;
    m_overlayColor = QColor(255, 255, 255);

    m_lightState = false;
}

QExtIndicatorLightPrivate::~QExtIndicatorLightPrivate()
{
    if (m_flickerTimer->isActive()) {
        m_flickerTimer->stop();
    }
}


QExtIndicatorLight::QExtIndicatorLight(QWidget *parent)
    : QWidget(parent), dd_ptr(new QExtIndicatorLightPrivate(this))
{
    Q_D(QExtIndicatorLight);
    d->m_flickerTimer.reset(new QTimer);
    connect(d->m_flickerTimer.data(), SIGNAL(timeout()), this, SLOT(flicker()));
    d->m_flickerTimer->setInterval(500);
    this->installEventFilter(this);
    this->setFont(QFont("Arial", 4));
}

QExtIndicatorLight::~QExtIndicatorLight()
{

}


QString QExtIndicatorLight::text() const
{
    Q_D(const QExtIndicatorLight);
    return d->m_text;
}

QColor QExtIndicatorLight::lightTextColor() const
{
    Q_D(const QExtIndicatorLight);
    return d->m_lightTextColor;
}

QColor QExtIndicatorLight::normalTextColor() const
{
    Q_D(const QExtIndicatorLight);
    return d->m_normalTextColor;
}

QColor QExtIndicatorLight::lightBackgroundColor() const
{
    Q_D(const QExtIndicatorLight);
    return d->m_lightBackgroundColor;
}

QColor QExtIndicatorLight::normalBackgroundColor() const
{
    Q_D(const QExtIndicatorLight);
    return d->m_normalBackgroundColor;
}

int QExtIndicatorLight::fontPixelSize() const
{
    Q_D(const QExtIndicatorLight);
    return d->m_fontPixelSize;
}

QColor QExtIndicatorLight::outBorderStartColor() const
{
    Q_D(const QExtIndicatorLight);
    return d->m_outBorderStartColor;
}

QColor QExtIndicatorLight::outBorderEndColor() const
{
    Q_D(const QExtIndicatorLight);
    return d->m_outBorderEndColor;
}

QColor QExtIndicatorLight::inBorderStartColor() const
{
    Q_D(const QExtIndicatorLight);
    return d->m_inBorderStartColor;
}

QColor QExtIndicatorLight::inBorderEndColor() const
{
    Q_D(const QExtIndicatorLight);
    return d->m_inBorderEndColor;
}

bool QExtIndicatorLight::isMoveEnable() const
{
    Q_D(const QExtIndicatorLight);
    return d->m_moveEnable;
}

bool QExtIndicatorLight::isOverlayVisible() const
{
    Q_D(const QExtIndicatorLight);
    return d->m_overlayVisible;
}

QColor QExtIndicatorLight::overlayColor() const
{
    Q_D(const QExtIndicatorLight);
    return d->m_overlayColor;
}

QExtIndicatorLight::Style QExtIndicatorLight::styleType() const
{
    Q_D(const QExtIndicatorLight);
    return d->m_style;
}

QExtIndicatorLight::Shape QExtIndicatorLight::shapeType() const
{
    Q_D(const QExtIndicatorLight);
    return d->m_shape;
}

bool QExtIndicatorLight::lightState() const
{
    Q_D(const QExtIndicatorLight);
    return d->m_lightState;
}

bool QExtIndicatorLight::flickerState() const
{
    Q_D(const QExtIndicatorLight);
    return d->m_flickerTimer->isActive();
}

int QExtIndicatorLight::flickerInterval() const
{
    Q_D(const QExtIndicatorLight);
    return d->m_flickerTimer->interval();
}

QSize QExtIndicatorLight::sizeHint() const
{
    return QSize(100, 100);
}

QSize QExtIndicatorLight::minimumSizeHint() const
{
    return QSize(10, 10);
}

void QExtIndicatorLight::setText(const QString &text)
{
    Q_D(QExtIndicatorLight);
    if (text != d->m_text) {
        d->m_text = text;
        this->update();
    }
}

void QExtIndicatorLight::setTextLightColor(const QColor &color)
{
    Q_D(QExtIndicatorLight);
    if (color != d->m_lightTextColor) {
        d->m_lightTextColor = color;
        this->update();
    }
}

void QExtIndicatorLight::setTextNormalColor(const QColor &color)
{
    Q_D(QExtIndicatorLight);
    if (color != d->m_normalTextColor) {
        d->m_normalTextColor = color;
        this->update();
    }
}

void QExtIndicatorLight::setBackgroundLightColor(const QColor &color)
{
    Q_D(QExtIndicatorLight);
    if (color != d->m_lightBackgroundColor) {
        d->m_lightBackgroundColor = color;
        this->update();
    }
}

void QExtIndicatorLight::setBackgroundNormalColor(const QColor &color)
{
    Q_D(QExtIndicatorLight);
    if (color != d->m_normalBackgroundColor) {
        d->m_normalBackgroundColor = color;
        this->update();
    }
}

void QExtIndicatorLight::setFontPixelSize(const int &size)
{
    Q_D(QExtIndicatorLight);
    if (size <= 0) {
        qCritical() << "QEXTLightButton::setFontPixelSize():iSize must be greater than zero!";
        return;
    }
    if (size != d->m_fontPixelSize) {
        d->m_fontPixelSize = size;
        this->update();
    }
}

void QExtIndicatorLight::setBorderOutStartColor(const QColor &color)
{
    Q_D(QExtIndicatorLight);
    if (color != d->m_outBorderStartColor) {
        d->m_outBorderStartColor = color;
        this->update();
    }
}

void QExtIndicatorLight::setBorderOutEndColor(const QColor &color)
{
    Q_D(QExtIndicatorLight);
    if (color != d->m_outBorderEndColor) {
        d->m_outBorderEndColor = color;
        this->update();
    }
}

void QExtIndicatorLight::setBorderInStartColor(const QColor &color)
{
    Q_D(QExtIndicatorLight);
    if (color != d->m_inBorderStartColor) {
        d->m_inBorderStartColor = color;
        this->update();
    }
}

void QExtIndicatorLight::setBorderInEndColor(const QColor &color)
{
    Q_D(QExtIndicatorLight);
    if (color != d->m_inBorderEndColor) {
        d->m_inBorderEndColor = color;
        this->update();
    }
}

void QExtIndicatorLight::setMoveEnable(const bool &enable)
{
    Q_D(QExtIndicatorLight);
    if (enable != d->m_moveEnable) {
        d->m_moveEnable = enable;
        this->update();
    }
}

void QExtIndicatorLight::setOverlayVisible(const bool &visiable)
{
    Q_D(QExtIndicatorLight);
    if (visiable != d->m_overlayVisible) {
        d->m_overlayVisible = visiable;
        this->update();
    }
}

void QExtIndicatorLight::setOverlayColor(const QColor &color)
{
    Q_D(QExtIndicatorLight);
    if (color != d->m_overlayColor) {
        d->m_overlayColor = color;
        this->update();
    }
}

void QExtIndicatorLight::setStyleType(const QExtIndicatorLight::Style &type)
{
    Q_D(QExtIndicatorLight);
    if (type != d->m_style) {
        d->m_style = type;
        switch (type) {
        case Style_Green:
        {
            d->m_lightBackgroundColor = QColor(0, 166, 0);
            break;
        }
        case Style_Red:
        {
            d->m_lightBackgroundColor = QColor(255, 0, 0);
            break;
        }
        case Style_Yellow:
        {
            d->m_lightBackgroundColor = QColor(238, 238, 0);
            break;
        }
        case Style_Black:
        {
            d->m_lightBackgroundColor = QColor(10, 10, 10);
            break;
        }
        case Style_Gray:
        {
            d->m_lightBackgroundColor = QColor(129, 129, 129);
            break;
        }
        case Style_Blue:
        {
            d->m_lightBackgroundColor = QColor(0, 0, 166);
            break;
        }
        case Style_LightBlue:
        {
            d->m_lightBackgroundColor = QColor(100, 184, 255);
            break;
        }
        case Style_LightRed:
        {
            d->m_lightBackgroundColor = QColor(255, 107, 107);
            break;
        }
        case Style_LightGreen:
        {
            d->m_lightBackgroundColor = QColor(24, 189, 155);
            break;
        }
        default:
            break;
        }
        this->update();
    }
}

void QExtIndicatorLight::setShapeType(const QExtIndicatorLight::Shape &type)
{
    Q_D(QExtIndicatorLight);
    if (type != d->m_shape) {
        d->m_shape = type;
        this->update();
    }
}

void QExtIndicatorLight::setLightState(const bool &state)
{
    Q_D(QExtIndicatorLight);
    if (state != d->m_lightState) {
        d->m_lightState = state;
        this->update();
    }
}

void QExtIndicatorLight::setFlickerState(const bool &state)
{
    if (state) {
        this->startFlicker();
    } else {
        this->stopFlicker();
    }
}

void QExtIndicatorLight::setFlickerInterval(const int &interval)
{
    Q_D(QExtIndicatorLight);
    if (interval <= 0) {
        qCritical() << "QEXTLightButton::setFlickerInterval():interval must be greate than zero!";
        return;
    }
    if (d->m_flickerTimer->isActive()) {
        d->m_flickerTimer->stop();
        d->m_flickerTimer->setInterval(interval);
        d->m_flickerTimer->start();
    } else {
        d->m_flickerTimer->setInterval(interval);
    }
}

void QExtIndicatorLight::startFlicker()
{
    Q_D(QExtIndicatorLight);
    if (!d->m_flickerTimer->isActive()) {
        d->m_flickerTimer->start();
    }
}

void QExtIndicatorLight::stopFlicker()
{
    Q_D(QExtIndicatorLight);
    if (d->m_flickerTimer->isActive()) {
        d->m_flickerTimer->stop();
        d->m_lightState = false;
        this->update();
    }
}

bool QExtIndicatorLight::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(QExtIndicatorLight);
    if (d->m_moveEnable) {
        static QPoint lastPnt;
        static bool pressed = false;
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

        if (mouseEvent->type() == QEvent::MouseButtonPress) {
            if (this->rect().contains(mouseEvent->pos()) && (mouseEvent->button() == Qt::LeftButton)) {
                lastPnt = mouseEvent->pos();
                pressed = true;
            }
        } else if (mouseEvent->type() == QEvent::MouseMove && pressed) {
            int posX = mouseEvent->pos().x() - lastPnt.x();
            int posY = mouseEvent->pos().y() - lastPnt.y();
            this->move(this->x() + posX , this->y() + posY);
        } else if (mouseEvent->type() == QEvent::MouseButtonRelease && pressed) {
            pressed = false;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void QExtIndicatorLight::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    this->drawBorderOut(&painter);
    this->drawBorderIn(&painter);
    this->drawBackground(&painter);
    this->drawText(&painter);
    this->drawOverlay(&painter);
}

void QExtIndicatorLight::drawBorderOut(QPainter *painter)
{
    Q_D(QExtIndicatorLight);
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0, -radius, 0, radius);
    borderGradient.setColorAt(0, d->m_outBorderStartColor);
    borderGradient.setColorAt(1, d->m_outBorderEndColor);
    painter->setBrush(borderGradient);
    switch (d->m_shape) {
    case QExtIndicatorLight::Shape_Circle:
    {
        painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
        break;
    }
    case QExtIndicatorLight::Shape_Square:
    {
        painter->drawRect(-radius, -radius, radius * 2, radius * 2);
        break;
    }
    case QExtIndicatorLight::Shape_Triangle:
    {
        QPointF points[3] = {QPoint(0, -radius), QPoint(-radius, radius), QPoint(radius, radius)};
        painter->drawPolygon(points, 3);
        break;
    }
    case QExtIndicatorLight::Shape_Rounded:
    {
        painter->drawRoundedRect(-radius, -radius, radius * 2, radius * 2, radius / 2, radius / 2);
        break;
    }
    default:
        break;
    }
    painter->restore();
}

void QExtIndicatorLight::drawBorderIn(QPainter *painter)
{
    Q_D(QExtIndicatorLight);
    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0, -radius, 0, radius);
    borderGradient.setColorAt(0, d->m_inBorderStartColor);
    borderGradient.setColorAt(1, d->m_inBorderEndColor);
    painter->setBrush(borderGradient);
    switch (d->m_shape) {
    case QExtIndicatorLight::Shape_Circle:
    {
        painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
        break;
    }
    case QExtIndicatorLight::Shape_Square:
    {
        painter->drawRect(-radius, -radius, radius * 2, radius * 2);
        break;
    }
    case QExtIndicatorLight::Shape_Triangle:
    {
        QPointF points[3] = {QPoint(0, -radius), QPoint(-radius, radius), QPoint(radius, radius)};
        painter->drawPolygon(points, 3);
        break;
    }
    case QExtIndicatorLight::Shape_Rounded:
    {
        painter->drawRoundedRect(-radius, -radius, radius * 2, radius * 2, radius / 2, radius / 2);
        break;
    }
    default:
        break;
    }
    painter->restore();
}

void QExtIndicatorLight::drawBackground(QPainter *painter)
{
    Q_D(QExtIndicatorLight);
    int radius = 80;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_lightState ? d->m_lightBackgroundColor : d->m_normalBackgroundColor);
    switch (d->m_shape) {
    case QExtIndicatorLight::Shape_Circle:
    {
        painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
        break;
    }
    case QExtIndicatorLight::Shape_Square:
    {
        painter->drawRect(-radius, -radius, radius * 2, radius * 2);
        break;
    }
    case QExtIndicatorLight::Shape_Triangle:
    {
        QPointF points[3] = {QPoint(0, -radius), QPoint(-radius, radius), QPoint(radius, radius)};
        painter->drawPolygon(points, 3);
        break;
    }
    case QExtIndicatorLight::Shape_Rounded:
    {
        painter->drawRoundedRect(-radius, -radius, radius * 2, radius * 2, radius / 2, radius / 2);
        break;
    }
    default:
        break;
    }
    painter->restore();
}

void QExtIndicatorLight::drawText(QPainter *painter)
{
    Q_D(QExtIndicatorLight);
    if (d->m_text.isEmpty()) {
        return;
    }

    int radius = 100;
    painter->save();

    QFont font = this->font();
    font.setPixelSize(d->m_fontPixelSize);
    painter->setFont(font);
    painter->setPen(d->m_lightState ? d->m_lightTextColor : d->m_normalTextColor);
    QRect rect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(rect, Qt::AlignCenter, d->m_text);
    painter->restore();
}

void QExtIndicatorLight::drawOverlay(QPainter *painter)
{
    Q_D(QExtIndicatorLight);
    if (!d->m_overlayVisible) {
        return;
    }

    int radius = 80;
    painter->save();
    painter->setPen(Qt::NoPen);

    QPainterPath smallCircle;
    QPainterPath bigCircle;
    switch (d->m_shape) {
    case QExtIndicatorLight::Shape_Circle:
    {
        radius -= 1;
        smallCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);
        radius *= 2;
        bigCircle.addEllipse(-radius + 30, -radius + 140, radius * 2, radius * 2);
        break;
    }
    case QExtIndicatorLight::Shape_Square:
    {
        radius -= 1;
        smallCircle.addRect(-radius, -radius, radius * 2, radius * 2);
        radius *= 2;
        bigCircle.addEllipse(-radius + 30, -radius + 140, radius * 2, radius * 2);
        break;
    }
    case QExtIndicatorLight::Shape_Triangle:
    {
        radius -= 1;
        QPolygonF smallPolygonF;
        smallPolygonF << QPointF(0, -radius) << QPointF(-radius, radius) << QPointF(radius, radius);
        smallCircle.addPolygon(smallPolygonF);
        radius *= 2;
        bigCircle.addEllipse(-radius + 30, -radius + 170, radius * 2, radius * 2);
        break;
    }
    case QExtIndicatorLight::Shape_Rounded:
    {
        radius -= 1;
        smallCircle.addRoundedRect(-radius, -radius, radius * 2, radius * 2, 25, 25);
        radius *= 2;
        bigCircle.addEllipse(-radius + 30, -radius + 140, radius * 2, radius * 2);
        break;
    }
    default:
        break;
    }
    QPainterPath highlight = smallCircle - bigCircle;

    QLinearGradient linearGradient(0, -radius / 2, 0, 0);
    d->m_overlayColor.setAlpha(100);
    linearGradient.setColorAt(0.0, d->m_overlayColor);
    d->m_overlayColor.setAlpha(30);
    linearGradient.setColorAt(1.0, d->m_overlayColor);
    painter->setBrush(linearGradient);
    painter->drawPath(highlight);

    painter->restore();
}

void QExtIndicatorLight::flicker()
{
    Q_D(QExtIndicatorLight);
    d->m_lightState = !d->m_lightState;
    this->update();
}
