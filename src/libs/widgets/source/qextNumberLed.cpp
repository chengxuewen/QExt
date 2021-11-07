#pragma execution_character_set("utf-8")

#include <qextNumberLed.h>
#include <qextNumberLed_p.h>

#include <QDebug>
#include <QColor>
#include <QPainter>

QEXTNumberLedPrivate::QEXTNumberLedPrivate(QEXTNumberLed *q)
    : q_ptr(q)
{
    m_number = 0;
    m_space = 20;

    m_backgroundStartColor = QColor(100, 100, 100);
    m_backgroundEndColor = QColor(60, 60, 60);

    m_numberStartColor = QColor(100, 184, 255);
    m_numberEndColor = QColor(79, 148, 205);

    m_symbol = QEXTNumberLed::Symbol_None;

    m_dotVisiable = false;
    m_colonVisiable = false;
}

QEXTNumberLedPrivate::~QEXTNumberLedPrivate()
{

}


QEXTNumberLed::QEXTNumberLed(QWidget *parent)
    : QWidget(parent), d_ptr(new QEXTNumberLedPrivate(this))
{

}

QEXTNumberLed::~QEXTNumberLed()
{

}

int QEXTNumberLed::number() const
{
    QEXT_DECL_DC(QEXTNumberLed);
    return d->m_number;
}

int QEXTNumberLed::space() const
{
    QEXT_DECL_DC(QEXTNumberLed);
    return d->m_space;
}

QColor QEXTNumberLed::backgroundStartColor() const
{
    QEXT_DECL_DC(QEXTNumberLed);
    return d->m_backgroundStartColor;
}

QColor QEXTNumberLed::backgroundEndColor() const
{
    QEXT_DECL_DC(QEXTNumberLed);
    return d->m_backgroundEndColor;
}

QColor QEXTNumberLed::numberStartColor() const
{
    QEXT_DECL_DC(QEXTNumberLed);
    return d->m_numberStartColor;
}

QColor QEXTNumberLed::numberEndColor() const
{
    QEXT_DECL_DC(QEXTNumberLed);
    return d->m_numberEndColor;
}

QEXTNumberLed::Symbol QEXTNumberLed::symbolType() const
{
    QEXT_DECL_DC(QEXTNumberLed);
    return d->m_symbol;
}

QSize QEXTNumberLed::sizeHint() const
{
    return QSize(150, 200);
}

QSize QEXTNumberLed::minimumSizeHint() const
{
    return QSize(20, 30);
}

void QEXTNumberLed::setNumber(int number)
{
    QEXT_DECL_D(QEXTNumberLed);
    if (number < 0 || number > 9)
    {
        qCritical() << "QEXTNumberLed::setNumber():iNumber must be in range of 0~9!";
        return;
    }
    if (number != d->m_number) {
        d->m_number = number;
        this->update();
    }
}

void QEXTNumberLed::setSpace(int space)
{
    QEXT_DECL_D(QEXTNumberLed);
    if (space < 0) {
        qCritical() << "QEXTNumberLed::setNumber():iNumber must br greate than zero!";
        return;
    }
    if (space != d->m_space) {
        d->m_space = space;
        this->update();
    }
}

void QEXTNumberLed::setBackgroundStartColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNumberLed);
    if (color != d->m_backgroundStartColor) {
        d->m_backgroundStartColor = color;
        this->update();
    }
}

void QEXTNumberLed::setBackgroundEndColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNumberLed);
    if (color != d->m_backgroundEndColor) {
        d->m_backgroundEndColor = color;
        this->update();
    }
}

void QEXTNumberLed::setNumberStartColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNumberLed);
    if (color != d->m_numberStartColor) {
        d->m_numberStartColor = color;
        this->update();
    }
}

void QEXTNumberLed::setNumberEndColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNumberLed);
    if (color != d->m_numberEndColor) {
        d->m_numberEndColor = color;
        this->update();
    }
}

void QEXTNumberLed::setSymbolType(const QEXTNumberLed::Symbol &type)
{
    QEXT_DECL_D(QEXTNumberLed);
    if (type != d->m_symbol) {
        d->m_symbol = type;
        this->update();
    }
}

void QEXTNumberLed::paintEvent(QPaintEvent *)
{
    QEXT_DECL_D(QEXTNumberLed);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    this->drawBackground(&painter);
    //绘制数字
    this->drawNumber(&painter);
}

void QEXTNumberLed::drawBackground(QPainter *painter)
{
    QEXT_DECL_D(QEXTNumberLed);
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPointF(0, 0), QPointF(0, this->height()));
    bgGradient.setColorAt(0.0, d->m_backgroundStartColor);
    bgGradient.setColorAt(1.0, d->m_backgroundEndColor);
    painter->setBrush(bgGradient);
    painter->drawRect(this->rect());
    painter->restore();
}

void QEXTNumberLed::drawNumber(QPainter *painter)
{
    QEXT_DECL_D(QEXTNumberLed);
    painter->save();
    painter->setPen(Qt::NoPen);

    //形状宽度及凸起部分高度
    double recWidth = this->width() / 10;
    double recHeight = this->height() / 30;
    double recRadius = qMin(recWidth, recHeight) * 2;
    double recSpace = this->width() / 30;
    double margin = qMax(recWidth, recHeight);

    //找出六个对应点
    QPointF topLeft(margin, margin);
    QPointF topRight(this->width() - margin * 2 - recRadius, margin);
    QPointF midLeft(margin, this->height() / 2);
    QPointF midRight(this->width() - margin * 2 - recRadius, this->height() / 2);
    QPointF bottomLeft(margin, this->height() - margin);
    QPointF bottomRight(this->width() - margin * 2 - recRadius, this->height() - margin);

    //逐个将每个形状的点集合添加,每个数码管都有7个形状,每个形状有4-6个点

    //左侧上部分形状坐标集合
    QVector<QPointF> topLeftRectVec;
    topLeftRectVec.append(QPointF(topLeft.x(), topLeft.y()));
    topLeftRectVec.append(QPointF(topLeft.x() + recWidth, topLeft.y() + recHeight * 2));
    topLeftRectVec.append(QPointF(midLeft.x() + recWidth, midLeft.y() - recHeight - recSpace));
    topLeftRectVec.append(QPointF(midLeft.x() + recWidth / 2, midLeft.y() - recSpace));
    topLeftRectVec.append(QPointF(midLeft.x(), midLeft.y() - recHeight - recSpace));

    //顶部形状坐标集合
    QVector<QPointF> topRectVec;
    topRectVec.append(QPointF(topLeft.x() + recSpace, topLeft.y()));
    topRectVec.append(QPointF(topLeft.x() + recWidth + recSpace, topLeft.y() + recHeight * 2));
    topRectVec.append(QPointF(topRight.x() - recWidth - recSpace, topRight.y() + recHeight * 2));
    topRectVec.append(QPointF(topRight.x() - recSpace, topRight.y()));

    //右侧上部分形状坐标集合
    QVector<QPointF> topRightRectVec;
    topRightRectVec.append(QPointF(topRight.x() - recWidth, topRight.y() + recHeight * 2));
    topRightRectVec.append(QPointF(topRight.x(), topRight.y()));
    topRightRectVec.append(QPointF(midRight.x(), midRight.y() - recHeight - recSpace));
    topRightRectVec.append(QPointF(midRight.x() - recWidth / 2, midRight.y() - recSpace));
    topRightRectVec.append(QPointF(midRight.x() - recWidth, midRight.y() - recHeight - recSpace));

    //中间部分形状坐标集合
    QVector<QPointF> midRectVec;
    midRectVec.append(QPointF(midLeft.x() + recWidth / 2, midLeft.y()));
    midRectVec.append(QPointF(midLeft.x() + recWidth, midLeft.y() - recHeight));
    midRectVec.append(QPointF(midRight.x() - recWidth, midRight.y() - recHeight));
    midRectVec.append(QPointF(midRight.x() - recWidth / 2, midRight.y()));
    midRectVec.append(QPointF(midRight.x() - recWidth, midRight.y() + recHeight));
    midRectVec.append(QPointF(midLeft.x() + recWidth, midRight.y() + recHeight));

    //左侧下部分形状坐标集合
    QVector<QPointF> bottomLeftRectVec;
    bottomLeftRectVec.append(QPointF(midLeft.x(), midLeft.y() + recHeight + recSpace));
    bottomLeftRectVec.append(QPointF(midLeft.x() + recWidth / 2, midLeft.y() + recSpace));
    bottomLeftRectVec.append(QPointF(midLeft.x() + recWidth, midLeft.y() + recHeight + recSpace));
    bottomLeftRectVec.append(QPointF(bottomLeft.x() + recWidth, bottomLeft.y() - recHeight * 2));
    bottomLeftRectVec.append(QPointF(bottomLeft.x(), bottomLeft.y()));

    //底部形状坐标集合
    QVector<QPointF> bottomRectVec;
    bottomRectVec.append(QPointF(bottomLeft.x() + recSpace, bottomLeft.y()));
    bottomRectVec.append(QPointF(bottomLeft.x() + recWidth + recSpace, bottomRight.y() - recHeight * 2));
    bottomRectVec.append(QPointF(bottomRight.x() - recWidth - recSpace, bottomRight.y() - recHeight * 2));
    bottomRectVec.append(QPointF(bottomRight.x() - recSpace, bottomRight.y()));

    //右侧下部分形状坐标集合
    QVector<QPointF> bottomRightRectVec;
    bottomRightRectVec.append(QPointF(midRight.x() - recWidth, midRight.y() + recHeight + recSpace));
    bottomRightRectVec.append(QPointF(midRight.x() - recWidth / 2, midRight.y() + recSpace));
    bottomRightRectVec.append(QPointF(midRight.x(), midRight.y() + recHeight + recSpace));
    bottomRightRectVec.append(QPointF(bottomRight.x(), bottomRight.y()));
    bottomRightRectVec.append(QPointF(bottomRight.x() - recWidth, bottomRight.y() - recHeight * 2));

    //颜色渐变
    QLinearGradient numberGradient(QPointF(0, 0), QPointF(0, this->height()));
    numberGradient.setColorAt(0.0, d->m_numberStartColor);
    numberGradient.setColorAt(1.0, d->m_numberEndColor);
    painter->setBrush(numberGradient);

    //根据值绘制形状
    switch (d->m_number) {
    case 0:
        painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        //painter->drawPolygon(midRectVec);
        painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;
    case 1:
        //painter->drawPolygon(topLeftRectVec);
        //painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        //painter->drawPolygon(midRectVec);
        //painter->drawPolygon(bottomLeftRectVec);
        //painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;
    case 2:
        //painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        //painter->drawPolygon(bottomRightRectVec);
        break;
    case 3:
        //painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        //painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;
    case 4:
        painter->drawPolygon(topLeftRectVec);
        //painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        //painter->drawPolygon(bottomLeftRectVec);
        //painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;
    case 5:
        painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        //painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        //painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;
    case 6:
        painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        //painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;
    case 7:
        //painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        //painter->drawPolygon(midRectVec);
        //painter->drawPolygon(bottomLeftRectVec);
        //painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;
    case 8:
        painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;
    case 9:
        painter->drawPolygon(topLeftRectVec);
        painter->drawPolygon(topRectVec);
        painter->drawPolygon(topRightRectVec);
        painter->drawPolygon(midRectVec);
        //painter->drawPolygon(bottomLeftRectVec);
        painter->drawPolygon(bottomRectVec);
        painter->drawPolygon(bottomRightRectVec);
        break;
    default:
        break;
    }

    switch (d->m_symbol) {
    case QEXTNumberLed::Symbol_Dot:
    {
        painter->drawEllipse(bottomRight.x() + margin, bottomRight.y() - recHeight - recRadius / 2, recRadius, recRadius);
        break;
    }
    case QEXTNumberLed::Symbol_Colon:
    {
        int iHeight = this->height() / 3;
        painter->drawEllipse(bottomRight.x() + margin, iHeight, recRadius, recRadius);
        painter->drawEllipse(bottomRight.x() + margin, iHeight * 2, recRadius, recRadius);
        break;
    }
    case QEXTNumberLed::Symbol_Line:
    {
        QVector<QPointF> lineRectVec;
        lineRectVec.append(QPointF(midRight.x() + recRadius, midRight.y() - recHeight));
        lineRectVec.append(QPointF(this->width() - recSpace, midRight.y() - recHeight));
        lineRectVec.append(QPointF(this->width() - recSpace, midRight.y() + recHeight));
        lineRectVec.append(QPointF(midRight.x() + recRadius, midRight.y() + recHeight));
        painter->drawPolygon(lineRectVec);
        break;
    }
    default:
        break;
    }

    painter->restore();
}

