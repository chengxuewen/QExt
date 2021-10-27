#pragma execution_character_set("utf-8")

#include <qextIndicatorLight.h>
#include <qextIndicatorLight_p.h>

#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>


QEXTIndicatorLightPrivate::QEXTIndicatorLightPrivate(QEXTIndicatorLight *q)
    : q_ptr(q)
{
    m_text = "";
    m_style = QEXTIndicatorLight::Style_Red;
    m_shape = QEXTIndicatorLight::Shape_Circle;
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
    m_overlayVisiable = true;
    m_overlayColor = QColor(255, 255, 255);

    m_lightState = false;
}

QEXTIndicatorLightPrivate::~QEXTIndicatorLightPrivate()
{
    if (m_flickerTimer->isActive()) {
        m_flickerTimer->stop();
    }
}


QEXTIndicatorLight::QEXTIndicatorLight(QWidget *parent)
    : QWidget(parent), d_ptr(new QEXTIndicatorLightPrivate(this))
{
    QEXT_DECL_D(QEXTIndicatorLight);
    d->m_flickerTimer.reset(new QTimer);
    connect(d->m_flickerTimer.data(), SIGNAL(timeout()), this, SLOT(flicker()));
    d->m_flickerTimer->setInterval(500);
    this->installEventFilter(this);
    this->setFont(QFont("Arial", 4));
}

QEXTIndicatorLight::~QEXTIndicatorLight()
{

}


QString QEXTIndicatorLight::text() const
{
    QEXT_DECL_DC(QEXTIndicatorLight);
    return d->m_text;
}

QColor QEXTIndicatorLight::lightTextColor() const
{
    QEXT_DECL_DC(QEXTIndicatorLight);
    return d->m_lightTextColor;
}

QColor QEXTIndicatorLight::normalTextColor() const
{
    QEXT_DECL_DC(QEXTIndicatorLight);
    return d->m_normalTextColor;
}

QColor QEXTIndicatorLight::lightBackgroundColor() const
{
    QEXT_DECL_DC(QEXTIndicatorLight);
    return d->m_lightBackgroundColor;
}

QColor QEXTIndicatorLight::normalBackgroundColor() const
{
    QEXT_DECL_DC(QEXTIndicatorLight);
    return d->m_normalBackgroundColor;
}

int QEXTIndicatorLight::fontPixelSize() const
{
    QEXT_DECL_DC(QEXTIndicatorLight);
    return d->m_fontPixelSize;
}

QColor QEXTIndicatorLight::outBorderStartColor() const
{
    QEXT_DECL_DC(QEXTIndicatorLight);
    return d->m_outBorderStartColor;
}

QColor QEXTIndicatorLight::outBorderEndColor() const
{
    QEXT_DECL_DC(QEXTIndicatorLight);
    return d->m_outBorderEndColor;
}

QColor QEXTIndicatorLight::inBorderStartColor() const
{
    QEXT_DECL_DC(QEXTIndicatorLight);
    return d->m_inBorderStartColor;
}

QColor QEXTIndicatorLight::inBorderEndColor() const
{
    QEXT_DECL_DC(QEXTIndicatorLight);
    return d->m_inBorderEndColor;
}

bool QEXTIndicatorLight::isMoveEnable() const
{
    QEXT_DECL_DC(QEXTIndicatorLight);
    return d->m_moveEnable;
}

bool QEXTIndicatorLight::isOverlayVisiable() const
{
    QEXT_DECL_DC(QEXTIndicatorLight);
    return d->m_overlayVisiable;
}

QColor QEXTIndicatorLight::overlayColor() const
{
    QEXT_DECL_DC(QEXTIndicatorLight);
    return d->m_overlayColor;
}

QEXTIndicatorLight::Style QEXTIndicatorLight::styleType() const
{
    QEXT_DECL_DC(QEXTIndicatorLight);
    return d->m_style;
}

QEXTIndicatorLight::Shape QEXTIndicatorLight::shapeType() const
{
    QEXT_DECL_DC(QEXTIndicatorLight);
    return d->m_shape;
}

bool QEXTIndicatorLight::lightState() const
{
    QEXT_DECL_DC(QEXTIndicatorLight);
    return d->m_lightState;
}

bool QEXTIndicatorLight::flickerState() const
{
    QEXT_DECL_DC(QEXTIndicatorLight);
    return d->m_flickerTimer->isActive();
}

int QEXTIndicatorLight::flickerInterval() const
{
    QEXT_DECL_DC(QEXTIndicatorLight);
    return d->m_flickerTimer->interval();
}

QSize QEXTIndicatorLight::sizeHint() const
{
    return QSize(100, 100);
}

QSize QEXTIndicatorLight::minimumSizeHint() const
{
    return QSize(10, 10);
}

void QEXTIndicatorLight::setText(const QString &text)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (text != d->m_text) {
        d->m_text = text;
        this->update();
    }
}

void QEXTIndicatorLight::setTextLightColor(const QColor &color)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (color != d->m_lightTextColor) {
        d->m_lightTextColor = color;
        this->update();
    }
}

void QEXTIndicatorLight::setTextNormalColor(const QColor &color)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (color != d->m_normalTextColor) {
        d->m_normalTextColor = color;
        this->update();
    }
}

void QEXTIndicatorLight::setBackgroundLightColor(const QColor &color)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (color != d->m_lightBackgroundColor) {
        d->m_lightBackgroundColor = color;
        this->update();
    }
}

void QEXTIndicatorLight::setBackgroundNormalColor(const QColor &color)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (color != d->m_normalBackgroundColor) {
        d->m_normalBackgroundColor = color;
        this->update();
    }
}

void QEXTIndicatorLight::setFontPixelSize(const int &size)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (size <= 0) {
        qCritical() << "QEXTLightButton::setFontPixelSize():iSize must be greater than zero!";
        return;
    }
    if (size != d->m_fontPixelSize) {
        d->m_fontPixelSize = size;
        this->update();
    }
}

void QEXTIndicatorLight::setBorderOutStartColor(const QColor &color)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (color != d->m_outBorderStartColor) {
        d->m_outBorderStartColor = color;
        this->update();
    }
}

void QEXTIndicatorLight::setBorderOutEndColor(const QColor &color)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (color != d->m_outBorderEndColor) {
        d->m_outBorderEndColor = color;
        this->update();
    }
}

void QEXTIndicatorLight::setBorderInStartColor(const QColor &color)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (color != d->m_inBorderStartColor) {
        d->m_inBorderStartColor = color;
        this->update();
    }
}

void QEXTIndicatorLight::setBorderInEndColor(const QColor &color)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (color != d->m_inBorderEndColor) {
        d->m_inBorderEndColor = color;
        this->update();
    }
}

void QEXTIndicatorLight::setMoveEnable(const bool &enable)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (enable != d->m_moveEnable) {
        d->m_moveEnable = enable;
        this->update();
    }
}

void QEXTIndicatorLight::setOverlayVisiable(const bool &visiable)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (visiable != d->m_overlayVisiable) {
        d->m_overlayVisiable = visiable;
        this->update();
    }
}

void QEXTIndicatorLight::setOverlayColor(const QColor &color)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (color != d->m_overlayColor) {
        d->m_overlayColor = color;
        this->update();
    }
}

void QEXTIndicatorLight::setStyleType(const QEXTIndicatorLight::Style &type)
{
    QEXT_DECL_D(QEXTIndicatorLight);
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

void QEXTIndicatorLight::setShapeType(const QEXTIndicatorLight::Shape &type)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (type != d->m_shape) {
        d->m_shape = type;
        this->update();
    }
}

void QEXTIndicatorLight::setLightState(const bool &state)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (state != d->m_lightState) {
        d->m_lightState = state;
        this->update();
    }
}

void QEXTIndicatorLight::setFlickerState(const bool &state)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (state) {
        this->startFlicker();
    } else {
        this->stopFlicker();
    }
}

void QEXTIndicatorLight::setFlickerInterval(const int &interval)
{
    QEXT_DECL_D(QEXTIndicatorLight);
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

void QEXTIndicatorLight::startFlicker()
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (!d->m_flickerTimer->isActive()) {
        d->m_flickerTimer->start();
    }
}

void QEXTIndicatorLight::stopFlicker()
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (d->m_flickerTimer->isActive()) {
        d->m_flickerTimer->stop();
        d->m_lightState = false;
        this->update();
    }
}

bool QEXTIndicatorLight::eventFilter(QObject *watched, QEvent *event)
{
    QEXT_DECL_D(QEXTIndicatorLight);
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

void QEXTIndicatorLight::paintEvent(QPaintEvent *)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    //绘制外边框
    this->drawBorderOut(&painter);
    //绘制内边框
    this->drawBorderIn(&painter);
    //绘制内部指示颜色
    this->drawBackground(&painter);
    //绘制居中文字
    this->drawText(&painter);
    //绘制遮罩层
    this->drawOverlay(&painter);
}

void QEXTIndicatorLight::drawBorderOut(QPainter *painter)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0, -radius, 0, radius);
    borderGradient.setColorAt(0, d->m_outBorderStartColor);
    borderGradient.setColorAt(1, d->m_outBorderEndColor);
    painter->setBrush(borderGradient);
    switch (d->m_shape) {
    case QEXTIndicatorLight::Shape_Circle:
    {
        painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
        break;
    }
    case QEXTIndicatorLight::Shape_Square:
    {
        painter->drawRect(-radius, -radius, radius * 2, radius * 2);
        break;
    }
    case QEXTIndicatorLight::Shape_Triangle:
    {
        QPointF points[3] = {QPoint(0, -radius), QPoint(-radius, radius), QPoint(radius, radius)};
        painter->drawPolygon(points, 3);
        break;
    }
    case QEXTIndicatorLight::Shape_Rounded:
    {
        painter->drawRoundRect(-radius, -radius, radius * 2, radius * 2);
        break;
    }
    default:
        break;
    }
    painter->restore();
}

void QEXTIndicatorLight::drawBorderIn(QPainter *painter)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0, -radius, 0, radius);
    borderGradient.setColorAt(0, d->m_inBorderStartColor);
    borderGradient.setColorAt(1, d->m_inBorderEndColor);
    painter->setBrush(borderGradient);
    switch (d->m_shape) {
    case QEXTIndicatorLight::Shape_Circle:
    {
        painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
        break;
    }
    case QEXTIndicatorLight::Shape_Square:
    {
        painter->drawRect(-radius, -radius, radius * 2, radius * 2);
        break;
    }
    case QEXTIndicatorLight::Shape_Triangle:
    {
        QPointF points[3] = {QPoint(0, -radius), QPoint(-radius, radius), QPoint(radius, radius)};
        painter->drawPolygon(points, 3);
        break;
    }
    case QEXTIndicatorLight::Shape_Rounded:
    {
        painter->drawRoundRect(-radius, -radius, radius * 2, radius * 2);
        break;
    }
    default:
        break;
    }
    painter->restore();
}

void QEXTIndicatorLight::drawBackground(QPainter *painter)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    int radius = 80;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->m_lightState ? d->m_lightBackgroundColor : d->m_normalBackgroundColor);
    switch (d->m_shape) {
    case QEXTIndicatorLight::Shape_Circle:
    {
        painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
        break;
    }
    case QEXTIndicatorLight::Shape_Square:
    {
        painter->drawRect(-radius, -radius, radius * 2, radius * 2);
        break;
    }
    case QEXTIndicatorLight::Shape_Triangle:
    {
        QPointF points[3] = {QPoint(0, -radius), QPoint(-radius, radius), QPoint(radius, radius)};
        painter->drawPolygon(points, 3);
        break;
    }
    case QEXTIndicatorLight::Shape_Rounded:
    {
        painter->drawRoundRect(-radius, -radius, radius * 2, radius * 2);
        break;
    }
    default:
        break;
    }
    painter->restore();
}

void QEXTIndicatorLight::drawText(QPainter *painter)
{
    QEXT_DECL_D(QEXTIndicatorLight);
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

void QEXTIndicatorLight::drawOverlay(QPainter *painter)
{
    QEXT_DECL_D(QEXTIndicatorLight);
    if (!d->m_overlayVisiable) {
        return;
    }

    int radius = 80;
    painter->save();
    painter->setPen(Qt::NoPen);

    QPainterPath smallCircle;
    QPainterPath bigCircle;
    switch (d->m_shape) {
    case QEXTIndicatorLight::Shape_Circle:
    {
        radius -= 1;
        smallCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);
        radius *= 2;
        bigCircle.addEllipse(-radius + 30, -radius + 140, radius * 2, radius * 2);
        break;
    }
    case QEXTIndicatorLight::Shape_Square:
    {
        radius -= 1;
        smallCircle.addRect(-radius, -radius, radius * 2, radius * 2);
        radius *= 2;
        bigCircle.addEllipse(-radius + 30, -radius + 140, radius * 2, radius * 2);
        break;
    }
    case QEXTIndicatorLight::Shape_Triangle:
    {
        radius -= 1;
        QPolygonF smallPolygonF;
        smallPolygonF << QPointF(0, -radius) << QPointF(-radius, radius) << QPointF(radius, radius);
        smallCircle.addPolygon(smallPolygonF);
        radius *= 2;
        bigCircle.addEllipse(-radius + 30, -radius + 170, radius * 2, radius * 2);
        break;
    }
    case QEXTIndicatorLight::Shape_Rounded:
    {
        radius -= 1;
        smallCircle.addRoundRect(-radius, -radius, radius * 2, radius * 2, 25, 25);
        radius *= 2;
        bigCircle.addEllipse(-radius + 30, -radius + 140, radius * 2, radius * 2);
        break;
    }
    default:
        break;
    }
    //高光的形状为小圆扣掉大圆的部分
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

void QEXTIndicatorLight::flicker()
{
    QEXT_DECL_D(QEXTIndicatorLight);
    d->m_lightState = !d->m_lightState;
    this->update();
}
