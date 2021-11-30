#include <qextSwitchButton.h>
#include <qextSwitchButton_p.h>

#include <QDebug>
#include <QEvent>
#include <QPainter>
#include <QTimer>

QEXTSwitchButtonPrivate::QEXTSwitchButtonPrivate(QEXTSwitchButton *q)
    : q_ptr(q)
{
    m_space = 2;
    m_rectRadius = 5;
    m_checked = false;
    m_textVisiable = true;
    m_circleVisiable = false;
    m_animationEnable = false;

    m_buttonStyle	= QEXTSwitchButton::Style_CircleIn;

    m_backgroundOffColor = QColor(111, 122, 126);
    m_backgroundOnColor = QColor(21, 156, 119);

    m_sliderOffColor = QColor(255, 255, 255);
    m_sliderOnColor = QColor(255, 255, 255);

    m_offTextColor = QColor(250, 250, 250);
    m_onTextColor = QColor(255, 255, 255);

    m_offText = "Off";
    m_onText = "On";

    m_step = 0;
    m_startX = 0;
    m_endX = 0;
}

QEXTSwitchButtonPrivate::~QEXTSwitchButtonPrivate()
{
    if (m_timer->isActive())
    {
        m_timer->stop();
    }
}


QEXTSwitchButton::QEXTSwitchButton(QWidget *parent)
    : QWidget(parent), dd_ptr(new QEXTSwitchButtonPrivate(this))
{
    Q_D(QEXTSwitchButton);
    d->m_step = this->width() / 50;
    d->m_timer.reset(new QTimer);
    d->m_timer->setInterval(30);
    connect(d->m_timer.data(), SIGNAL(timeout()), this, SLOT(updateValue()));
    this->setFont(QFont("Microsoft Yahei", 10));
}

QEXTSwitchButton::~QEXTSwitchButton()
{
}

void QEXTSwitchButton::mousePressEvent(QMouseEvent *)
{
    Q_D(QEXTSwitchButton);
    d->m_checked = !d->m_checked;
    emit checkedChanged(d->m_checked);

    d->m_step = width() / 7;

    if (d->m_checked) {
        if (d->m_buttonStyle == Style_Rect) {
            d->m_endX = width() - width() / 2;
        } else if (d->m_buttonStyle == Style_CircleIn) {
            d->m_endX = width() - height();
        } else if (d->m_buttonStyle == Style_CircleOut) {
            d->m_endX = width() - height();
        }
    } else {
        d->m_endX = 0;
    }

    if (d->m_animationEnable) {
        d->m_timer->start();
    } else {
        d->m_startX = d->m_endX;
        this->update();
    }
}

void QEXTSwitchButton::resizeEvent(QResizeEvent *)
{
    Q_D(QEXTSwitchButton);
    d->m_step = width() / 50;

    if (d->m_checked) {
        if (d->m_buttonStyle == Style_Rect) {
            d->m_startX = width() - width() / 2;
        } else if (d->m_buttonStyle == Style_CircleIn) {
            d->m_startX = width() - height();
        } else if (d->m_buttonStyle == Style_CircleOut) {
            d->m_startX = width() - height();
        }
    } else {
        d->m_startX = 0;
    }

    this->update();
}

void QEXTSwitchButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    this->drawBackground(&painter);
    this->drawSlider(&painter);
}

void QEXTSwitchButton::drawBackground(QPainter *painter)
{
    Q_D(QEXTSwitchButton);
    painter->save();
    painter->setPen(Qt::NoPen);

    QColor bgColor = d->m_checked ? d->m_backgroundOnColor : d->m_backgroundOffColor;
    if (!this->isEnabled()) {
        bgColor.setAlpha(60);
    }

    painter->setBrush(bgColor);

    if (d->m_buttonStyle == Style_Rect) {
        painter->drawRoundedRect(rect(), d->m_rectRadius, d->m_rectRadius);
    } else if (d->m_buttonStyle == Style_CircleIn) {
        QRect rect(0, 0, width(), height());
        int side = qMin(rect.width(), rect.height());

        QPainterPath path1;
        path1.addEllipse(rect.x(), rect.y(), side, side);

        QPainterPath path2;
        path2.addEllipse(rect.width() - side, rect.y(), side, side);

        QPainterPath path3;
        path3.addRect(rect.x() + side / 2, rect.y(), rect.width() - side, rect.height());

        QPainterPath path;
        path = path3 + path1 + path2;
        painter->drawPath(path);
    } else if (d->m_buttonStyle == Style_CircleOut) {
        QRect rect(height() / 2, d->m_space, width() - height(), height() - d->m_space * 2);
        painter->drawRoundedRect(rect, d->m_rectRadius, d->m_rectRadius);
    }

    if (d->m_buttonStyle == Style_Rect || d->m_buttonStyle == Style_CircleIn) {
        if (d->m_textVisiable) {
            int sliderWidth = qMin(width(), height()) - d->m_space * 2;
            if (d->m_buttonStyle == Style_Rect) {
                sliderWidth = width() / 2 - 5;
            } else if (d->m_buttonStyle == Style_CircleIn) {
                sliderWidth -= 5;
            }

            if (d->m_checked) {
                QRect textRect(0, 0, width() - sliderWidth, height());
                painter->setPen(d->m_onTextColor);
                painter->drawText(textRect, Qt::AlignCenter, d->m_onText);
            } else {
                QRect textRect(sliderWidth, 0, width() - sliderWidth, height());
                painter->setPen(d->m_offTextColor);
                painter->drawText(textRect, Qt::AlignCenter, d->m_offText);
            }
        } else if (d->m_circleVisiable) {
            int side = qMin(width(), height()) / 2;
            int y = (height() - side) / 2;

            if (d->m_checked) {
                QRect circleRect(side / 2, y, side, side);
                QPen pen(d->m_onTextColor, 2);
                painter->setPen(pen);
                painter->setBrush(Qt::NoBrush);
                painter->drawEllipse(circleRect);
            } else {
                QRect circleRect(width() - (side * 1.5), y, side, side);
                QPen pen(d->m_offTextColor, 2);
                painter->setPen(pen);
                painter->setBrush(Qt::NoBrush);
                painter->drawEllipse(circleRect);
            }
        }
    }

    painter->restore();
}

void QEXTSwitchButton::drawSlider(QPainter *painter)
{
    Q_D(QEXTSwitchButton);
    painter->save();
    painter->setPen(Qt::NoPen);

    if (!d->m_checked) {
        painter->setBrush(d->m_sliderOffColor);
    } else {
        painter->setBrush(d->m_sliderOnColor);
    }

    if (d->m_buttonStyle == Style_Rect) {
        int sliderWidth = width() / 2 - d->m_space * 2;
        int sliderHeight = height() - d->m_space * 2;
        QRect sliderRect(d->m_startX + d->m_space, d->m_space, sliderWidth , sliderHeight);
        painter->drawRoundedRect(sliderRect, d->m_rectRadius, d->m_rectRadius);
    } else if (d->m_buttonStyle == Style_CircleIn) {
        QRect rect(0, 0, width(), height());
        int sliderWidth = qMin(rect.width(), rect.height()) - d->m_space * 2;
        QRect sliderRect(d->m_startX + d->m_space, d->m_space, sliderWidth, sliderWidth);
        painter->drawEllipse(sliderRect);
    } else if (d->m_buttonStyle == Style_CircleOut) {
        int sliderWidth = this->height();
        QRect sliderRect(d->m_startX, 0, sliderWidth, sliderWidth);

        QColor color1 = (d->m_checked ? Qt::white : d->m_backgroundOffColor);
        QColor color2 = (d->m_checked ? d->m_sliderOnColor : d->m_sliderOffColor);

        QRadialGradient radialGradient(sliderRect.center(), sliderWidth / 2);
        radialGradient.setColorAt(0, d->m_checked ? color1 : color2);
        radialGradient.setColorAt(0.5, d->m_checked ? color1 : color2);
        radialGradient.setColorAt(0.6, d->m_checked ? color2 : color1);
        radialGradient.setColorAt(1.0, d->m_checked ? color2 : color1);
        painter->setBrush(radialGradient);

        painter->drawEllipse(sliderRect);
    }

    painter->restore();
}

void QEXTSwitchButton::change()
{
    mousePressEvent(QEXT_DECL_NULLPTR);
}

void QEXTSwitchButton::updateValue()
{
    Q_D(QEXTSwitchButton);
    if (d->m_checked) {
        if (d->m_startX < d->m_endX) {
            d->m_startX = d->m_startX + d->m_step;
        } else {
            d->m_startX = d->m_endX;
            d->m_timer->stop();
        }
    } else {
        if (d->m_startX > d->m_endX) {
            d->m_startX = d->m_startX - d->m_step;
        } else {
            d->m_startX = d->m_endX;
            d->m_timer->stop();
        }
    }

    this->update();
}

int QEXTSwitchButton::space() const
{
    Q_D(const QEXTSwitchButton);
    return d->m_space;
}

int QEXTSwitchButton::rectRadius() const
{
    Q_D(const QEXTSwitchButton);
    return d->m_rectRadius;
}

bool QEXTSwitchButton::checked() const
{
    Q_D(const QEXTSwitchButton);
    return d->m_checked;
}

bool QEXTSwitchButton::isTextVisiable() const
{
    Q_D(const QEXTSwitchButton);
    return d->m_textVisiable;
}

bool QEXTSwitchButton::isCircleVisiable() const
{
    Q_D(const QEXTSwitchButton);
    return d->m_circleVisiable;
}

bool QEXTSwitchButton::isAnimationEnable() const
{
    Q_D(const QEXTSwitchButton);
    return d->m_animationEnable;
}

QEXTSwitchButton::Style QEXTSwitchButton::styleType() const
{
    Q_D(const QEXTSwitchButton);
    return d->m_buttonStyle;
}

QColor QEXTSwitchButton::backgroundOffColor() const
{
    Q_D(const QEXTSwitchButton);
    return d->m_backgroundOffColor;
}

QColor QEXTSwitchButton::backgroundOnColor() const
{
    Q_D(const QEXTSwitchButton);
    return d->m_backgroundOnColor;
}

QColor QEXTSwitchButton::sliderOffColor() const
{
    Q_D(const QEXTSwitchButton);
    return d->m_sliderOffColor;
}

QColor QEXTSwitchButton::sliderOnColor() const
{
    Q_D(const QEXTSwitchButton);
    return d->m_sliderOnColor;
}

QColor QEXTSwitchButton::textOffColor() const
{
    Q_D(const QEXTSwitchButton);
    return d->m_offTextColor;
}

QColor QEXTSwitchButton::textOnColor() const
{
    Q_D(const QEXTSwitchButton);
    return d->m_onTextColor;
}

QString QEXTSwitchButton::offText() const
{
    Q_D(const QEXTSwitchButton);
    return d->m_offText;
}

QString QEXTSwitchButton::onText() const
{
    Q_D(const QEXTSwitchButton);
    return d->m_onText;
}

QSize QEXTSwitchButton::sizeHint() const
{
    return QSize(60, 30);
}

QSize QEXTSwitchButton::minimumSizeHint() const
{
    return QSize(10, 5);
}

void QEXTSwitchButton::setSpace(int space)
{
    Q_D(QEXTSwitchButton);
    if (space != d->m_space) {
        d->m_space = space;
        this->update();
    }
}

void QEXTSwitchButton::setRectRadius(int radius)
{
    Q_D(QEXTSwitchButton);
    if (d->m_rectRadius != radius) {
        d->m_rectRadius = radius;
        this->update();
    }
}

void QEXTSwitchButton::setChecked(bool checked)
{
    Q_D(QEXTSwitchButton);
    if (d->m_checked != checked) {
        if (d->m_step == 0) {
            QTimer::singleShot(10, this, SLOT(change()));
        } else {
            mousePressEvent(NULL);
        }
    }
}

void QEXTSwitchButton::setTextVisiable(bool visiable)
{
    Q_D(QEXTSwitchButton);
    if (d->m_textVisiable != visiable) {
        d->m_textVisiable = visiable;
        this->update();
    }
}

void QEXTSwitchButton::setCircleVisiable(bool visiable)
{
    Q_D(QEXTSwitchButton);
    if (d->m_circleVisiable != visiable) {
        d->m_circleVisiable = visiable;
        this->update();
    }
}

void QEXTSwitchButton::setAnimationEnable(bool enable)
{
    Q_D(QEXTSwitchButton);
    if (d->m_animationEnable != enable) {
        d->m_animationEnable = enable;
        this->update();
    }
}

void QEXTSwitchButton::setStyleType(const QEXTSwitchButton::Style &style)
{
    Q_D(QEXTSwitchButton);
    if (d->m_buttonStyle != style) {
        d->m_buttonStyle = style;
        this->update();
    }
}

void QEXTSwitchButton::setOffBackgroundColor(const QColor &color)
{
    Q_D(QEXTSwitchButton);
    if (d->m_backgroundOffColor != color) {
        d->m_backgroundOffColor = color;
        this->update();
    }
}

void QEXTSwitchButton::setOnBackgroundColor(const QColor &color)
{
    Q_D(QEXTSwitchButton);
    if (d->m_backgroundOnColor != color) {
        d->m_backgroundOnColor = color;
        this->update();
    }
}

void QEXTSwitchButton::setOffSliderColor(const QColor &color)
{
    Q_D(QEXTSwitchButton);
    if (d->m_sliderOffColor != color) {
        d->m_sliderOffColor = color;
        this->update();
    }
}

void QEXTSwitchButton::setOnSliderColor(const QColor &color)
{
    Q_D(QEXTSwitchButton);
    if (d->m_sliderOnColor != color) {
        d->m_sliderOnColor = color;
        this->update();
    }
}

void QEXTSwitchButton::setOffTextColor(const QColor &color)
{
    Q_D(QEXTSwitchButton);
    if (d->m_offTextColor != color) {
        d->m_offTextColor = color;
        this->update();
    }
}

void QEXTSwitchButton::setOnTextColor(const QColor &color)
{
    Q_D(QEXTSwitchButton);
    if (d->m_onTextColor != color) {
        d->m_onTextColor = color;
        this->update();
    }
}

void QEXTSwitchButton::setOffText(const QString &text)
{
    Q_D(QEXTSwitchButton);
    if (text != d->m_offText) {
        d->m_offText = text;
        this->update();
    }
}

void QEXTSwitchButton::setOnText(const QString &text)
{
    Q_D(QEXTSwitchButton);
    if (d->m_onText != text) {
        d->m_onText = text;
        this->update();
    }
}
