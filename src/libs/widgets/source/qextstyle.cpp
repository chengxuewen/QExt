#include "qextstyle.h"
#include "qextstyleoption.h"

#include <QStyleOption>
#include <QTextLayout>
#include <QPaintEngine>
#include <QPaintDevice>
#include <QTextLine>
#include <QPixmapCache>
#include <QApplication>
#include <QPalette>
#include <QAbstractItemView>

#include <qmath.h>
//#include <private/qfixed_p.h>
//#include <private/qtextengine_p.h>
//#include <private/qicon_p.h>

#include <math.h>


static QImage dropShadow(const QPixmap &px, qreal radius, const QColor &color)
{
    if (px.isNull())
        return QImage();

    QImage tmp(px.size() + QSize(radius * 2, radius * 2), QImage::Format_ARGB32_Premultiplied);
    tmp.fill(0);
    QPainter tmpPainter(&tmp);
    tmpPainter.setCompositionMode(QPainter::CompositionMode_Source);
    tmpPainter.drawPixmap(QPoint(radius, radius), px);
    tmpPainter.end();

    // blur the alpha channel
    QImage blurred(tmp.size(), QImage::Format_ARGB32_Premultiplied);
    blurred.fill(0);
    QPainter blurPainter(&blurred);
    //    qt_blurImage(&blurPainter, tmp, radius, false, true);
    blurPainter.end();

    if (color == QColor(Qt::black))
        return blurred;

    tmp = blurred;

    // blacken the image...
    tmpPainter.begin(&tmp);
    tmpPainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    tmpPainter.fillRect(tmp.rect(), color);
    tmpPainter.end();

    return tmp;
}

static QList<QRect> sudokuByRect(const QRect &rect, QMargins borders)
{
    QList<QRect> list;

    //    qreal border_width = borders.left() + borders.right();

    //    if ( border_width > rect.width()) {
    //        borders.setLeft(borders.left() / border_width * rect.width());
    //        borders.setRight(rect.width() - borders.left());
    //    }

    //    qreal border_height = borders.top() + borders.bottom();

    //    if (border_height > rect.height()) {
    //        borders.setTop(borders.top()/ border_height * rect.height());
    //        borders.setBottom(rect.height() - borders.top());
    //    }

    //    const QRect &contentsRect = rect - borders;

    //    list << QRect(0, 0, borders.left(), borders.top());
    //    list << QRect(list.at(0).topRight(), QSize(contentsRect.width(), borders.top())).translated(1, 0);
    //    list << QRect(list.at(1).topRight(), QSize(borders.right(), borders.top())).translated(1, 0);
    //    list << QRect(list.at(0).bottomLeft(), QSize(borders.left(), contentsRect.height())).translated(0, 1);
    //    list << contentsRect;
    //    list << QRect(contentsRect.topRight(), QSize(borders.right(), contentsRect.height())).translated(1, 0);
    //    list << QRect(list.at(3).bottomLeft(), QSize(borders.left(), borders.bottom())).translated(0, 1);
    //    list << QRect(contentsRect.bottomLeft(), QSize(contentsRect.width(), borders.bottom())).translated(0, 1);
    //    list << QRect(contentsRect.bottomRight(), QSize(borders.left(), borders.bottom())).translated(1, 1);

    return list;
}

static QImage borderImage(const QPixmap &px, const QMargins &borders, const QSize &size, QImage::Format format)
{
    QImage image(size, format);
    QPainter pa(&image);

    const QList<QRect> sudoku_src = sudokuByRect(px.rect(), borders);
    const QList<QRect> sudoku_tar = sudokuByRect(QRect(QPoint(0, 0), size), borders);

    pa.setCompositionMode(QPainter::CompositionMode_Source);  //设置组合模式

    for (int i = 0; i < 9; ++i) {
        pa.drawPixmap(sudoku_tar[i], px, sudoku_src[i]);
    }

    pa.end();

    return image;
}


void QEXTDrawUtils::drawShadow(QPainter *pa, const QRect &rect, qreal xRadius, qreal yRadius, const QColor &sc, qreal radius, const QPoint &offset)
{
    QPixmap shadow;
    //    qreal scale = pa->paintEngine()->paintDevice()->devicePixelRatioF();
    //    QRect shadow_rect = rect;

    //    shadow_rect.setTopLeft(shadow_rect.topLeft() + offset);

    //    xRadius *= scale;
    //    yRadius *= scale;
    //    radius *= scale;

    //    const QString &key = QString("dtk-shadow-%1x%2-%3-%4").arg(xRadius).arg(yRadius).arg(sc.name()).arg(radius);

    //    if (!QPixmapCache::find(key, shadow)) {
    //        QImage shadow_base(QSize(xRadius * 3, yRadius * 3), QImage::Format_ARGB32_Premultiplied);
    //        shadow_base.fill(0);
    //        QPainter pa(&shadow_base);

    //        pa.setBrush(sc);
    //        pa.setPen(Qt::NoPen);
    //        pa.drawRoundedRect(shadow_base.rect(), xRadius, yRadius);
    //        pa.end();

    //        shadow_base = dropShadow(QPixmap::fromImage(shadow_base), radius, sc);
    //        shadow = QPixmap::fromImage(shadow_base);
    //        QPixmapCache::insert(key, shadow);
    //    }

    //    const QMargins margins(xRadius + radius, yRadius + radius, xRadius + radius, yRadius + radius);
    //    QImage new_shadow = borderImage(shadow, margins, shadow_rect.size() * scale, QImage::Format_ARGB32_Premultiplied);
    //    QPainter pa_shadow(&new_shadow);
    //    pa_shadow.setCompositionMode(QPainter::CompositionMode_Clear);
    //    pa_shadow.setPen(Qt::NoPen);
    //    pa_shadow.setBrush(Qt::transparent);
    //    pa_shadow.setRenderHint(QPainter::Antialiasing);
    //    pa_shadow.drawRoundedRect((new_shadow.rect() - QMargins(radius, radius, radius, radius)).translated(-offset), xRadius, yRadius);
    //    pa_shadow.end();
    //    new_shadow.setDevicePixelRatio(scale);
    //    pa->drawImage(shadow_rect.topLeft(), new_shadow);
}

void QEXTDrawUtils::drawShadow(QPainter *pa, const QRect &rect, const QPainterPath &path, const QColor &sc, int radius, const QPoint &offset)
{
    QPixmap shadow;
    //    qreal scale = pa->paintEngine()->paintDevice()->devicePixelRatioF();
    //    QRect shadow_rect = rect;

    //    shadow_rect.setTopLeft(rect.topLeft() + offset);
    //    radius *= scale;

    //    QImage shadow_base(shadow_rect.size() * scale, QImage::Format_ARGB32_Premultiplied);
    //    shadow_base.fill(0);
    //    shadow_base.setDevicePixelRatio(scale);

    //    QPainter paTmp(&shadow_base);
    //    paTmp.setBrush(sc);
    //    paTmp.setPen(Qt::NoPen);
    //    paTmp.drawPath(path);
    //    paTmp.end();
    //    shadow_base = dropShadow(QPixmap::fromImage(shadow_base), radius, sc);
    //    shadow = QPixmap::fromImage(shadow_base);
    //    shadow.setDevicePixelRatio(scale);

    //    pa->drawPixmap(shadow_rect, shadow);
}

void QEXTDrawUtils::drawRoundedRect(QPainter *pa, const QRect &rect, qreal xRadius, qreal yRadius, Corners corners, Qt::SizeMode mode)
{
    QRectF r = rect.normalized();

    if (r.isNull())
        return;

    if (mode == Qt::AbsoluteSize) {
        qreal w = r.width() / 2;
        qreal h = r.height() / 2;

        if (w == 0) {
            xRadius = 0;
        } else {
            xRadius = 100 * qMin(xRadius, w) / w;
        }
        if (h == 0) {
            yRadius = 0;
        } else {
            yRadius = 100 * qMin(yRadius, h) / h;
        }
    } else {
        if (xRadius > 100)                          // fix ranges
            xRadius = 100;

        if (yRadius > 100)
            yRadius = 100;
    }

    if (xRadius <= 0 || yRadius <= 0) {             // add normal rectangle
        pa->drawRect(r);
        return;
    }

    QPainterPath path;
    qreal x = r.x();
    qreal y = r.y();
    qreal w = r.width();
    qreal h = r.height();
    qreal rxx2 = w * xRadius / 100;
    qreal ryy2 = h * yRadius / 100;

    path.arcMoveTo(x, y, rxx2, ryy2, 180);

    if (corners & TopLeftCorner) {
        path.arcTo(x, y, rxx2, ryy2, 180, -90);
    } else {
        path.lineTo(r.topLeft());
    }

    if (corners & TopRightCorner) {
        path.arcTo(x + w - rxx2, y, rxx2, ryy2, 90, -90);
    } else {
        path.lineTo(r.topRight());
    }

    if (corners & BottomRightCorner) {
        path.arcTo(x + w - rxx2, y + h - ryy2, rxx2, ryy2, 0, -90);
    } else {
        path.lineTo(r.bottomRight());
    }

    if (corners & BottomLeftCorner) {
        path.arcTo(x, y + h - ryy2, rxx2, ryy2, 270, -90);
    } else {
        path.lineTo(r.bottomLeft());
    }

    path.closeSubpath();
    pa->drawPath(path);
}

void QEXTDrawUtils::drawFork(QPainter *pa, const QRectF &rect, const QColor &color, int width)
{
    QPen pen;
    pen.setWidth(width);
    pen.setColor(color);

    pa->setRenderHint(QPainter::Antialiasing, true);
    pa->setPen(pen);
    pa->setBrush(Qt::NoBrush);

    drawForkElement(pa, rect);
}

void QEXTDrawUtils::drawMark(QPainter *pa, const QRectF &rect, const QColor &boxInside, const QColor &boxOutside, const int penWidth, const int outLineLeng)
{
    QPen pen(boxInside);
    pen.setWidth(penWidth);
    pa->setPen(pen);
    pen.setJoinStyle(Qt::RoundJoin);
    pa->setRenderHint(QPainter::Antialiasing, true);

    drawMarkElement(pa, rect);

    if (outLineLeng == 0)
        return;

    double xWide = (rect.width() / 2.0);
    int yHigh = rect.height();
    double length = sqrt(pow(xWide, 2) + pow(yHigh, 2));
    double x = rect.right() + (outLineLeng / length) * xWide;
    double y = rect.y() - (outLineLeng / length) * yHigh;

    pen.setColor(boxOutside);
    pa->setPen(pen);
    pa->drawLine(QPointF(rect.topRight()), QPointF(x, y));
}

void QEXTDrawUtils::drawBorder(QPainter *pa, const QRectF &rect, const QBrush &brush, int borderWidth, int radius)
{
    pa->setPen(QPen(brush, borderWidth, Qt::SolidLine));
    pa->setBrush(Qt::NoBrush);
    pa->setRenderHint(QPainter::Antialiasing);
    pa->drawRoundedRect(rect.adjusted(1, 1, -1, -1), radius, radius) ;
}

void QEXTDrawUtils::drawArrow(QPainter *pa, const QRectF &rect, const QColor &color, Qt::ArrowType arrow, int width)
{
    QPen pen;
    pen.setWidth(width);
    pen.setColor(color);
    pa->setRenderHint(QPainter::Antialiasing, true);
    pa->setPen(pen);
    pa->setBrush(Qt::NoBrush);

    drawArrowElement(arrow, pa, rect);
}

void QEXTDrawUtils::drawPlus(QPainter *painter, const QRectF &rect, const QColor &color, qreal width)
{
    QPen pen = color;
    pen.setWidthF(width);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    drawIncreaseElement(painter, rect);
}

void QEXTDrawUtils::drawSubtract(QPainter *painter, const QRectF &rect, const QColor &color, qreal width)
{
    QPen pen = color;
    pen.setWidthF(width);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    drawDecreaseElement(painter, rect);
}

void QEXTDrawUtils::drawForkElement(QPainter *pa, const QRectF &rect)
{
    pa->drawLine(rect.topLeft(), rect.bottomRight());
    pa->drawLine(rect.bottomLeft(), rect.topRight());
}

void QEXTDrawUtils::drawArrowElement(Qt::ArrowType arrow, QPainter *pa, const QRectF &rect)
{
    const QPointF center = rect.center();

    switch (arrow) {
    case Qt::UpArrow: {
        pa->drawLine(QPointF(center.x(), rect.y()), rect.bottomLeft());
        pa->drawLine(QPointF(center.x(), rect.y()), rect.bottomRight());
        break;
    }
    case Qt::LeftArrow: {
        pa->drawLine(QPointF(rect.x(), center.y()), rect.bottomRight());
        pa->drawLine(QPointF(rect.x(), center.y()), rect.topRight());
        break;
    }
    case Qt::DownArrow: {
        pa->drawLine(QPointF(center.x(), rect.bottom()), rect.topLeft());
        pa->drawLine(QPointF(center.x(), rect.bottom()), rect.topRight());
        break;
    }
    case Qt::RightArrow: {
        pa->drawLine(QPointF(rect.right(), center.y()), rect.topLeft());
        pa->drawLine(QPointF(rect.right(), center.y()), rect.bottomLeft());
        break;
    }
    default:
        break;
    }
}

void QEXTDrawUtils::drawDecreaseElement(QPainter *pa, const QRectF &rect)
{
    qreal centerY = rect.center().y();

    pa->drawLine(QPointF(rect.left(), centerY), QPointF(rect.right(), centerY));
}

void QEXTDrawUtils::drawIncreaseElement(QPainter *pa, const QRectF &rect)
{
    qreal centerX = rect.center().x();
    qreal centerY = rect.center().y();

    pa->drawLine(QPointF(rect.x(), centerY), QPointF(rect.right(), centerY));
    pa->drawLine(QPointF(centerX, rect.y()), QPointF(centerX, rect.bottom()));
}

void QEXTDrawUtils::drawMarkElement(QPainter *pa, const QRectF &rect)
{
    pa->drawLine(rect.x(), rect.center().y(), rect.center().x(), rect.bottom());
    pa->drawLine(rect.center().x(), rect.bottom(), rect.right(), rect.y());
}

void QEXTDrawUtils::drawSelectElement(QPainter *pa, const QRectF &rect)
{
    qreal radius = rect.width() / 15.0;
    QPointF pointff = rect.center();

    pa->setBrush(QBrush(pa->pen().color()));
    pa->drawEllipse(pointff, radius, radius);
    pa->drawEllipse(pointff - QPointF(radius * 3.5, 0), radius, radius);
    pa->drawEllipse(pointff + QPointF(radius * 3.5, 0), radius, radius);
}

void QEXTDrawUtils::drawEditElement(QPainter *pa, const QRectF &rect)
{

}

void QEXTDrawUtils::drawExpandElement(QPainter *pa, const QRectF &rect)
{
    drawArrowUp(pa, rect);
}

void QEXTDrawUtils::drawReduceElement(QPainter *pa, const QRectF &rect)
{
    drawArrowDown(pa, rect);
}

void QEXTDrawUtils::drawLockElement(QPainter *pa, const QRectF &rect)
{
    qreal width = rect.width() / 5.0;
    qreal height = rect.height() / 5.0;
    qreal y = rect.y();
    qreal x = rect.x();

    QRectF topRect(x + width, y, width * 3, height * 3);
    QRectF bottomRect(x, y + height * 2, rect.width(), rect.height() - height * 2);
    QPainterPath path;

    path.arcMoveTo(topRect, 0);
    path.arcTo(topRect, 0, 180);

    path.addRect(bottomRect);
    pa->drawPath(path);
}

void QEXTDrawUtils::drawUnlockElement(QPainter *pa, const QRectF &rect)
{
    qreal width = rect.width() / 5.0;
    qreal height = rect.height() / 5.0;
    qreal y = rect.y();
    qreal x = rect.x();

    QRectF topRect(x + width * 3, y, rect.width() - width * 3, height * 3);
    QRectF bottomRect(x + width, y + height * 2, rect.width() - width * 2, rect.height() - height * 2);
    QPainterPath path;

    path.arcMoveTo(topRect, 0);
    path.arcTo(topRect, 0, 180);
    path.addRect(bottomRect);
    pa->drawPath(path);
}

void QEXTDrawUtils::drawMediaVolumeElement(QPainter *pa, const QRectF &rect)
{

}

void QEXTDrawUtils::drawMediaVolumeFullElement(QPainter *pa, const QRectF &rect)
{

}

void QEXTDrawUtils::drawMediaVolumeMutedElement(QPainter *pa, const QRectF &rect)
{

}

void QEXTDrawUtils::drawMediaVolumeLeftElement(QPainter *pa, const QRectF &rect)
{

}

void QEXTDrawUtils::drawMediaVolumeRightElement(QPainter *pa, const QRectF &rect)
{

}

void QEXTDrawUtils::drawArrowEnter(QPainter *pa, const QRectF &rect)
{
    drawArrowRight(pa, rect);
}

void QEXTDrawUtils::drawArrowLeave(QPainter *pa, const QRectF &rect)
{
    drawArrowLeft(pa, rect);
}

void QEXTDrawUtils::drawArrowNext(QPainter *pa, const QRectF &rect)
{
    QRectF content_rect(rect.x() + rect.width() / 2, rect.y(), rect.width() / 2, rect.height());
    qreal y = rect.center().y();

    drawArrowElement(Qt::RightArrow, pa, content_rect);
    pa->drawLine(rect.x(), y, rect.bottom(), y);
}

void QEXTDrawUtils::drawArrowPrev(QPainter *pa, const QRectF &rect)
{
    QRectF content_rect(rect.x(), rect.y(), rect.width() / 2, rect.height());
    qreal y = rect.center().y();

    drawArrowElement(Qt::LeftArrow, pa, content_rect);
    pa->drawLine(rect.x(), y, rect.bottom(), y);
}

void QEXTDrawUtils::drawShowPassword(QPainter *pa, const QRectF &rect)
{

}

void QEXTDrawUtils::drawHidePassword(QPainter *pa, const QRectF &rect)
{

}

void QEXTDrawUtils::drawCloseButton(QPainter *pa, const QRectF &rect)
{
    pa->setRenderHint(QPainter::Antialiasing);
    QPen pen = pa->pen();
    QPen new_pen = pa->pen();
    QColor border_color = pen.color();
    border_color.setAlphaF(0.1);
    new_pen.setColor(border_color);
    pa->setPen(new_pen);
    qreal pen_extent = pen.widthF() / 2;
    pa->drawEllipse(rect.adjusted(pen_extent, pen_extent, -pen_extent, -pen_extent));
    QRectF content_rect(0, 0, rect.width() / 3, rect.height() / 3);
    content_rect.moveCenter(rect.center());
    pa->setPen(pen);
    drawForkElement(pa, content_rect);
}

void QEXTDrawUtils::drawIndicatorMajuscule(QPainter *pa, const QRectF &rect)
{

}

void QEXTDrawUtils::drawIndicatorUnchecked(QPainter *pa, const QRectF &rect)
{
    pa->drawEllipse(rect);
}

void QEXTDrawUtils::drawIndicatorChecked(QPainter *pa, const QRectF &rect)
{
    QRectF mark(0, 0, rect.width() / 2, rect.height() / 2);
    mark.moveCenter(rect.center());
    QStyleOption opt;
    QColor brush = opt.palette.color(QEXTPalette::Highlight);
    pa->setPen(Qt::NoPen);
    pa->setBrush(brush);

    pa->drawEllipse(rect);
    drawMark(pa, mark, opt.palette.color(QEXTPalette::Window), opt.palette.color(QEXTPalette::Window), 2, 0);
}

void QEXTDrawUtils::drawDeleteButton(QPainter *pa, const QRectF &rect)
{
    const QPen pen = pa->pen();
    pa->setPen(Qt::NoPen);

    QPainterPath path;
    path.addEllipse(rect);

    QRectF hRect(rect.x(), rect.y(), rect.width() / 2, 1);

    hRect.moveCenter(rect.center());

    path.addRect(hRect);

    pa->fillPath(path, QColor("#ff6a6a"));
}

void QEXTDrawUtils::drawAddButton(QPainter *pa, const QRectF &rect)
{
    const QPen pen = pa->pen();
    pa->setPen(Qt::NoPen);

    QPainterPath path;
    path.addEllipse(rect);

    QRectF hRect(rect.x(), rect.y(), rect.width() / 2, 1);
    QRectF vRect(rect.x(), rect.y(), 1, rect.height() / 2);

    hRect.moveCenter(rect.center());
    vRect.moveCenter(rect.center());

    path.addRect(hRect);
    path.addRect(vRect);

    QRectF center(0, 0, 1, 1);
    center.moveCenter(rect.center());
    path.addEllipse(center);

    pa->fillPath(path, QColor("#48bf00"));
}

void QEXTDrawUtils::drawTitleBarMenuButton(QPainter *pa, const QRectF &rect)
{
    //    const QPen pen = pa->pen();
    //    pa->setPen(Qt::NoPen);
    //    pa->drawRect(rect);
    //    QRect content_rect(0, 0, rect.width() / 5, rect.height() / 5);
    //    content_rect.moveCenter(rect.center().toPoint());
    //    pa->setPen(pen);

    //    pa->setRenderHint(QPainter::Antialiasing, pa->device()->devicePixelRatioF() > 1.0);
    //    pa->drawLine(content_rect.x(), content_rect.y(), content_rect.topRight().x() - 2, content_rect.topRight().y());
    //    pa->drawLine(content_rect.bottomLeft(), content_rect.bottomRight());

    //    qreal y = content_rect.center().y();
    //    pa->drawLine(content_rect.x(), y, content_rect.topRight().x(), y);
}

void QEXTDrawUtils::drawTitleBarMinButton(QPainter *pa, const QRectF &rect)
{
    //    const QPen pen = pa->pen();
    //    pa->setPen(Qt::NoPen);
    //    pa->drawRect(rect);
    //    QRect content_rect(0, 0, rect.width() / 5, rect.height() / 5);
    //    content_rect.moveCenter(rect.center().toPoint());
    //    pa->setPen(pen);
    //    pa->setRenderHint(QPainter::Antialiasing, pa->device()->devicePixelRatioF() > 1.0);
    //    drawDecreaseElement(pa, content_rect);
}

void QEXTDrawUtils::drawTitleBarMaxButton(QPainter *pa, const QRectF &rect)
{
    //    const QPen pen = pa->pen();
    //    pa->setPen(Qt::NoPen);
    //    pa->drawRect(rect);
    //    QRect content_rect(0, 0, rect.width() / 5, rect.height() / 6);
    //    content_rect.moveCenter(rect.center().toPoint());
    //    pa->setPen(pen);
    //    pa->setRenderHint(QPainter::Antialiasing, pa->device()->devicePixelRatioF() > 1.0);
    //    pa->drawRect(content_rect);
}


void QEXTDrawUtils::drawTitleBarCloseButton(QPainter *pa, const QRectF &rect)
{
    //    const QPen pen = pa->pen();
    //    pa->setPen(Qt::NoPen);
    //    pa->drawRect(rect);
    //    QRectF content_rect(0, 0, rect.width() / 5, rect.height() / 5);
    //    content_rect.moveCenter(rect.center());
    //    pa->setPen(pen);
    //    pa->setRenderHint(QPainter::Antialiasing, pa->device()->devicePixelRatioF() > 1.0);
    //    drawForkElement(pa, content_rect);
}


void QEXTDrawUtils::drawTitleBarNormalButton(QPainter *pa, const QRectF &rect)
{
    //    const QPen pen = pa->pen();
    //    pa->setPen(Qt::NoPen);
    //    pa->drawRect(rect);
    //    QRect content_rect(0, 0, rect.width() / 5, rect.height() / 5);
    //    content_rect.moveCenter(rect.center().toPoint());
    //    pa->setPen(pen);

    //    pa->setRenderHint(QPainter::Antialiasing, pa->device()->devicePixelRatioF() > 1.0);
    //    pa->drawRect(content_rect.x(), content_rect.y() + 2, content_rect.width() - 2, content_rect.height() - 2);
    //    pa->drawLine(content_rect.x() + 2, content_rect.y(), content_rect.right(), content_rect.y());
    //    pa->drawLine(content_rect.right() + 1, content_rect.y(), content_rect.right() + 1, content_rect.bottom() - 2);
}

void QEXTDrawUtils::drawArrowUp(QPainter *pa, const QRectF &rect)
{
    QRectF ar(0, 0, rect.width(), rect.height() / 2);
    ar.moveCenter(rect.center());
    drawArrowElement(Qt::UpArrow, pa, ar);
}

void QEXTDrawUtils::drawArrowDown(QPainter *pa, const QRectF &rect)
{
    QRectF ar(0, 0, rect.width(), rect.height() / 2);
    ar.moveCenter(rect.center());
    drawArrowElement(Qt::DownArrow, pa, ar);
}

void QEXTDrawUtils::drawArrowLeft(QPainter *pa, const QRectF &rect)
{
    QRectF ar(0, 0, rect.width() / 2, rect.height());
    ar.moveCenter(rect.center());
    drawArrowElement(Qt::LeftArrow, pa, ar);
}

void QEXTDrawUtils::drawArrowRight(QPainter *pa, const QRectF &rect)
{
    QRectF ar(0, 0, rect.width() / 2, rect.height());
    ar.moveCenter(rect.center());
    drawArrowElement(Qt::RightArrow, pa, ar);
}

void QEXTDrawUtils::drawArrowBack(QPainter *pa, const QRectF &rect)
{
    drawArrowLeft(pa, rect);
}

void QEXTDrawUtils::drawArrowForward(QPainter *pa, const QRectF &rect)
{
    drawArrowRight(pa, rect);
}

void QEXTDrawUtils::drawLineEditClearButton(QPainter *pa, const QRectF &rect)
{
    drawCloseButton(pa, rect);
}




/*!
 * \~chinese \class QEXTStyle
 * \~chinese \brief QEXTStyle提供了一个修改风格的类
 * \~chinese \sa QCommonStyle()
 */

/*!
 * \~chinese \enum QEXTStyle::PrimitiveElement
 * \~chinese \sa QEXTStyle::PrimitiveElement QStyle::PrimitiveElement
 *
 * \~chinese \var QEXTStyle::PrimitiveElement QEXTStyle::PE_ItemBackground
 * \~chinese item背景颜色
 *
 * \~chinese \var QEXTStyle::PrimitiveElement QEXTStyle::PE_IconButtonPanel
 * \~chinese DIconButton 面板
 *
 * \~chinese \var QEXTStyle::PrimitiveElement QEXTStyle::PE_IconButtonIcon
 * \~chinese DIconButton 不同状态下的背景颜色
 *
 * \~chinese \var QEXTStyle::PrimitiveElement QEXTStyle::PE_Icon
 * \~chinese DIconButton
 *
 * \~chinese \var QEXTStyle::PrimitiveElement QEXTStyle::PE_SwitchButtonGroove
 * \~chinese DSwitchButton 面板
 *
 * \~chinese \var QEXTStyle::PrimitiveElement QEXTStyle::PE_SwitchButtonHandle
 * \~chinese DSwitchButton 滑块面板
 *
 * \~chinese \var QEXTStyle::PrimitiveElement QEXTStyle::PE_FloatingWidget
 * \~chinese DFloatingWidget 面板
*/

/*!
 * \~chinese \enum QEXTStyle::StyleState
 * \~chinese \sa QEXTStyle::StyleState 记录控件状态的值
 *
 * \~chinese \var QEXTStyle::StyleState QEXTStyle::SS_NormalState
 * \~chinese 正常状态
 *
 * \~chinese \var QEXTStyle::StyleState QEXTStyle::SS_HoverState
 * \~chinese 悬停状态
 *
 * \~chinese \var QEXTStyle::StyleState QEXTStyle::SS_PressState
 * \~chinese 按下状态
 *
 *\~chinese \var QEXTStyle::StyleState QEXTStyle::SS_StateCustomBase
 * \~chinese 自定义子元素的基值
 *
 * \~chinese \var QEXTStyle::StyleState QEXTStyle::StyleState_Mask
 * \~chinese 状态掩码
 *
 * \~chinese \var QEXTStyle::StyleState QEXTStyle::SS_CheckedFlag
 * \~chinese 选定标志
 *
 * \~chinese \var QEXTStyle::StyleState QEXTStyle::SS_SelectedFlag
 * \~chinese 选中状态
 *
 *  * \~chinese \var QEXTStyle::StyleState QEXTStyle::SS_FocusFlag
 * \~chinese 焦点状态
 *
 * \~chinese \var QEXTStyle::StyleState QEXTStyle::SS_FlagCustomBase
 * \~chinese 自定义子元素的基值
*/

/*!
 * \~chinese \enum QEXTStyle::PixelMetric
 * \~chinese \sa QEXTStyle::PixelMetric QStyle::PixelMetric
 *
 * \~chinese \var QEXTStyle::PixelMetric QEXTStyle::PM_FocusBorderWidth
 * \~chinese 控件焦点状态的边框宽度
 *
 * \~chinese \var QEXTStyle::PixelMetric QEXTStyle::PM_FocusBorderSpacing
 * \~chinese 控件内容和border之间的间隔
 *
 * \~chinese \var QEXTStyle::PixelMetric QEXTStyle::PM_FrameRadius
 * \~chinese 控件的圆角大小
 *
 * \~chinese \var QEXTStyle::PixelMetric QEXTStyle::PM_ShadowRadius
 * \~chinese 控件阴影效果的半径
 *
 * \~chinese \var QEXTStyle::PixelMetric QEXTStyle::PM_ShadowHOffset
 * \~chinese 阴影在水平方向的偏移
 *
 * \~chinese \var QEXTStyle::PixelMetric QEXTStyle::PM_ShadowVOffset
 * \~chinese 阴影在竖直方向的偏移
 *
 * \~chinese \var QEXTStyle::PixelMetric QEXTStyle::PM_FrameMargins
 * \~chinese 控件的margins区域，控件内容 = 控件大小 - FrameMargins
 *
 * \~chinese \var QEXTStyle::PixelMetric QEXTStyle::PM_IconButtonIconSize
 * \~chinese 控件大小
 *
 * \~chinese \var QEXTStyle::PixelMetric QEXTStyle::PM_TopLevelWindowRadius
 * \~chinese 窗口的圆角大小
 *
 * \~chinese \var QEXTStyle::PixelMetric QEXTStyle::PM_SwitchButtonHandleWidth
 * \~chinese 控件开关的宽度
 *
 * \~chinese \var QEXTStyle::PixelMetric QEXTStyle::PM_SwithcButtonHandleHeight
 * \~chinese 控件开关的高度
 *
 * \~chinese \var QEXTStyle::PixelMetric QEXTStyle::PM_FloatingWidgetRadius
 * \~chinese (基类)的圆角半径:控件内容-Radius < 控件内容 < 控件显示大小
 *
 * \~chinese \var QEXTStyle::PixelMetric QEXTStyle::PM_FloatingWidgetShadowRadius
 * \~chinese (基类)的阴影Radius区域:控件内容 < 控件内容+阴影margins < 控件内容+阴影margins+阴影Radius = 控件显示大小
 *
 * \~chinese \var QEXTStyle::PixelMetric QEXTStyle::PM_FloatingWidgetShadowMargins
 * \~chinese (基类)阴影的宽度 = 控件显示大小 - 阴影Radius - 控件内容
 *
 * \~chinese \var QEXTStyle::PixelMetric QEXTStyle::PM_FloatingWidgetShadowHOffset
 * \~chinese (基类)的阴影水平偏移
 *
 * \~chinese \var QEXTStyle::PixelMetric QEXTStyle::PM_ContentsMargins
 * \~chinese (基类)内容的边距（一般只用于左右边距）
 *
 * \~chinese \var QEXTStyle::PixelMetric QEXTStyle::PM_ContentsSpacing
 * \~chinese 内容的间距（可用于列表项中每一项的距离）
 *
 * \~chinese \var QEXTStyle::PixelMetric QEXTStyle::PM_ButtonMinimizedSize
 * \~chinese 按钮控件的最小大小
*/

/*!
 * \~chinese \enum QEXTStyle::StandardPixmap
 * \~chinese \sa QEXTStyle::StandardPixmap QStyle::StandardPixmap
 *
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::P_DecreaseElement
 * \~chinese 减少（-）
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_IncreaseElement
 * \~chinese 增加（+）
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_MarkElement
 * \~chinese 对勾
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_SelectElement
 * \~chinese 选择（...）
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_EditElement
 * \~chinese 编辑
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_ExpandElement
 * \~chinese 展开
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_ReduceElement
 * \~chinese 收缩
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_LockElement
 * \~chinese 锁定
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_UnlockElement
 * \~chinese 解锁
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_MediaVolumeLowElement
 * \~chinese 音量
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_MediaVolumeHighElement
 * \~chinese 满音量
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_MediaVolumeMutedElement
 * \~chinese 静音
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_MediaVolumeLeftElement
 * \~chinese 左声道
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_MediaVolumeRightElement
 * \~chinese 右声道
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_ArrowEnter
 * \~chinese 进入
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_ArrowLeave
 * \~chinese 离开
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_ArrowNext
 * \~chinese 下一页
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_ArrowPrev
 * \~chinese 上一页
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_ShowPassword
 * \~chinese 显示密码
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_HidePassword
 * \~chinese 隐藏密码
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_CloseButton
 * \~chinese 关闭按钮（X）
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_IndicatorMajuscule
 * \~chinese 大写标识
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_IndicatorSearch
 * \~chinese 搜索标识（放大镜）
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_IndicatorUnchecked
 * \~chinese 搜索标识（对应对勾的选中状态）
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_IndicatorChecked
 * \~chinese 搜索标识（对勾）
 *
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_DeleteButton
 * \~chinese 删除按钮
 *
 * \~chinese \var QEXTStyle::StandardPixmap QEXTStyle::SP_AddButton
 * \~chinese 新增按钮
*/


QT_BEGIN_NAMESPACE
//extern Q_WIDGETS_EXPORT void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed = 0);
extern QEXT_WIDGETS_API void qt_blurImage(QPainter *p, QImage &blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0);
QT_END_NAMESPACE

static Qt::TextFormat textFormat = Qt::AutoText;

/*!
 * \~chinese \brief QEXTStyle::QEXTStyle
 */
QEXTStyle::QEXTStyle()
{

}

/*!
 * \~chinese \brief QEXTStyle::adjustColor调整颜色
 * \~chinese \sa DGuiApplicationHelper::adjustColor()
 */
QColor QEXTStyle::adjustColor(const QColor &base, qint8 hueFloat, qint8 saturationFloat, qint8 lightnessFloat, qint8 redFloat, qint8 greenFloat, qint8 blueFloat, qint8 alphaFloat)
{
    //    return DGuiApplicationHelper::adjustColor(base, hueFloat, saturationFloat, lightnessFloat, redFloat, greenFloat, blueFloat, alphaFloat);
    return QColor();
}

/*!
 * \~chinese \brief QEXTStyle::blendColor混合颜色
 * \~chinese \sa DGuiApplicationHelper::blendColor()
 */
QColor QEXTStyle::blendColor(const QColor &substrate, const QColor &superstratum)
{
    //    return DGuiApplicationHelper::blendColor(substrate, superstratum);
    return  QColor();
}

/*!
 * \~chinese \brief QEXTStyle::toIconModeState 根据option中的QStyle::State返回图标应有
 * \~chinese 的模式和状态
 */
QPair<QIcon::Mode, QIcon::State> QEXTStyle::toIconModeState(const QStyleOption *option)
{
    QIcon::Mode mode = QIcon::Normal;
    QIcon::State state = option->state & State_On ? QIcon::On : QIcon::Off;

    if (option->state & QStyle::State_Enabled) {
        if (option->state & (State_Sunken | State_Selected)) {
            mode = QIcon::Selected;
        } else if (option->state & State_MouseOver) {
            mode = QIcon::Active;
        }
    } else {
        mode = QIcon::Disabled;
    }

    return qMakePair(mode, state);
}

/*!
 * \~chinese \brief QEXTStyle::setTooltipTextFormat 设置 tooltip 文本格式
 * \~chinese \sa Qt::TextFormat
 */
void QEXTStyle::setTooltipTextFormat(Qt::TextFormat format)
{
    textFormat = format;
}

/*!
 * \~chinese \brief QEXTStyle::tooltipTextFormat 获取 tooltip 文本格式
 * \~chinese \sa Qt::TextFormat
 */
Qt::TextFormat QEXTStyle::tooltipTextFormat()
{
    return textFormat;
}

QEXTStyle::StyleState QEXTStyle::getState(const QStyleOption *option)
{
    QEXTStyle::StyleState state = QEXTStyle::SS_NormalState;

    if (!option->state.testFlag(QEXTStyle::State_Enabled)) {
        return QEXTStyle::SS_NormalState;
    }

    if (option->state.testFlag(QEXTStyle::State_Sunken)) {
        state = QEXTStyle::SS_PressState;
    } else if (option->state.testFlag(QEXTStyle::State_MouseOver)) {
        state = QEXTStyle::SS_HoverState;
    }

    return state;
}

void QEXTStyle::setFocusRectVisible(QWidget *widget, bool visible)
{
    widget->setProperty("_d_dtk_noFocusRect", !visible);
}

void QEXTStyle::setFrameRadius(QWidget *widget, int radius)
{
    widget->setProperty("_d_dtk_frameRadius", radius);
}

/*!
 * \~chinese \brief QEXTStyle::drawPrimitive
 * \~chinese QStyle::drawPrimitive()
 */
void QEXTStyle::drawPrimitive(const QStyle *style, QEXTStyle::PrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w)
{

}

/*!
 * \~chinese \brief QEXTStyle::drawControl
 * \~chinese \sa QStyle::drawControl()
 */
void QEXTStyle::drawControl(const QStyle *style, QEXTStyle::ControlElement ce, const QStyleOption *opt, QPainter *p, const QWidget *w)
{

}

/*!
 * \~chinese \brief QEXTStyle::pixelMetric
 * \~chinese \sa QStyle::pixelMetric()
 */
int QEXTStyle::pixelMetric(const QStyle *style, QEXTStyle::PixelMetric m, const QStyleOption *opt, const QWidget *widget)
{
    return 0;
}

/*!
 * \~chinese \brief QEXTStyle::subElementRect
 * \~chinese \sa QStyle::subElementRect()
 */
QRect QEXTStyle::subElementRect(const QStyle *style, QEXTStyle::SubElement r, const QStyleOption *opt, const QWidget *widget)
{
    return QRect();
}

/*!
 * \~chinese \brief QEXTStyle::sizeFromContents
 * \~chinese \sa QStyle::sizeFromContents()
 */
QSize QEXTStyle::sizeFromContents(const QStyle *style, QEXTStyle::ContentsType ct, const QStyleOption *opt, const QSize &contentsSize, const QWidget *widget)
{
    return QSize();
}

/*!
 * \~chinese \brief QEXTStyle::standardIcon
 * \~chinese \sa QStyle::standardIcon()
 */
QIcon QEXTStyle::standardIcon(const QStyle *style, QEXTStyle::StandardPixmap st, const QStyleOption *opt, const QWidget *widget)
{
    Q_UNUSED(opt)
    Q_UNUSED(style)
    Q_UNUSED(widget)
    return QIcon();
}

void QEXTStyle::drawPrimitive(QStyle::PrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w) const
{
    this->proxy()->drawPrimitive(static_cast<QStyle::PrimitiveElement>(pe), opt, p, w);
}

void QEXTStyle::drawControl(QStyle::ControlElement ce, const QStyleOption *opt, QPainter *p, const QWidget *w) const
{
    this->proxy()->drawControl(static_cast<QStyle::ControlElement>(ce), opt, p, w);
}

int QEXTStyle::pixelMetric(QStyle::PixelMetric m, const QStyleOption *opt, const QWidget *widget) const
{
    return this->proxy()->pixelMetric(static_cast<QStyle::PixelMetric>(m), opt, widget);
}

/*!
 * \~chinese \brief QEXTStyle::styleHint
 * \~chinese \sa QStyle::styleHint()
 */
int QEXTStyle::styleHint(QStyle::StyleHint sh, const QStyleOption *opt, const QWidget *w, QStyleHintReturn *shret) const
{
    switch (sh) {
    case SH_ScrollBar_MiddleClickAbsolutePosition:
    case SH_FontDialog_SelectAssociatedText:
    case SH_Menu_KeyboardSearch:
    case SH_Menu_Scrollable:
    case SH_Menu_SloppySubMenus:
    case SH_ComboBox_ListMouseTracking:
    case SH_Menu_MouseTracking:
    case SH_MenuBar_MouseTracking:
    case SH_Menu_FillScreenWithScroll:
    case SH_ItemView_ChangeHighlightOnFocus:
    case SH_TabBar_PreferNoArrows:
    case SH_ComboBox_Popup:
    case SH_Slider_StopMouseOverSlider:
    case SH_SpinBox_AnimateButton:
    case SH_SpinControls_DisableOnBounds:
    case SH_Menu_FadeOutOnHide:
    case SH_ItemView_ShowDecorationSelected:
        //    case SH_ScrollBar_Transient:
        //    case SH_TitleBar_ShowToolTipsOnButtons:
        return true;
        //    case SH_SpinBox_ButtonsInsideFrame:
    case SH_ScrollBar_LeftClickAbsolutePosition:
    case SH_Slider_SnapToValue:
    case SH_Menu_AllowActiveAndDisabled:
    case SH_BlinkCursorWhenTextSelected:
    case SH_UnderlineShortcut:
    case SH_ItemView_PaintAlternatingRowColorsForEmptyArea:
        //    case SH_ComboBox_AllowWheelScrolling:
        return false;
    case SH_Header_ArrowAlignment:
        return Qt::AlignVCenter | Qt::AlignRight;
    case SH_Menu_SubMenuPopupDelay:
        return 100;
    case SH_ToolTipLabel_Opacity:
        return 255;
    case SH_RequestSoftwareInputPanel:
        return RSIP_OnMouseClickAndAlreadyFocused;
        //    case SH_ItemView_ScrollMode:
        return QAbstractItemView::ScrollPerPixel;
        //    case SH_Widget_Animation_Duration:
        return 300;
    case SH_Button_FocusPolicy:
        return Qt::TabFocus;
    case SH_ScrollView_FrameOnlyAroundContents:
        return false;
    case SH_LineEdit_PasswordCharacter:
        return 0x25CF;
    default:
        break;
    }

    return QCommonStyle::styleHint(sh, opt, w, shret);
}

QRect QEXTStyle::subElementRect(QStyle::SubElement r, const QStyleOption *opt, const QWidget *widget) const
{
    return this->proxy()->subElementRect(static_cast<QStyle::SubElement>(r), opt, widget);
}

QSize QEXTStyle::sizeFromContents(QStyle::ContentsType ct, const QStyleOption *opt, const QSize &contentsSize, const QWidget *widget) const
{
    return this->proxy()->sizeFromContents(static_cast<QStyle::ContentsType>(ct), opt, contentsSize, widget);
}

QIcon QEXTStyle::standardIcon(QStyle::StandardPixmap st, const QStyleOption *opt, const QWidget *widget) const
{
    return this->proxy()->standardIcon(static_cast<QStyle::StandardPixmap>(st), opt, widget);
}

/*!
 * \~chinese \brief QEXTStyle::standardPalette 获取标准调色板
 * \~chinese \return 调色板
 */
QPalette QEXTStyle::standardPalette() const
{
    //    QPalette pa = DGuiApplicationHelper::instance()->standardPalette(DGuiApplicationHelper::LightType);
    // 将无效的颜色fallback到QCommonStyle提供的palette，且在resolve操作中将detach pa对象
    // 防止在QApplication initSystemPalette的setSystemPalette中获取到一个和 QGuiApplicationPrivate::platformTheme()->palette()
    // 一样的QPalette对象，这样将导致QApplicationPrivate::setPalette_helper中将 app_pal 和新的QPalette对比时认为他们没有变化
    //    return pa.resolve(QCommonStyle::standardPalette());
    return QPalette();
}

QPixmap QEXTStyle::generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap, const QStyleOption *opt) const
{
    Q_UNUSED(opt)

    if (iconMode == QIcon::Active) {
        QImage image = pixmap.toImage();
        QPainter pa(&image);

        if (!pa.isActive())
            return QCommonStyle::generatedIconPixmap(iconMode, pixmap, opt);

        pa.setCompositionMode(QPainter::CompositionMode_SourceAtop);

        //        if (DGuiApplicationHelper::toColorType(opt->palette) == DGuiApplicationHelper::DarkType) {
        //            pa.fillRect(image.rect(), QColor(255, 255, 255, 0.1 * 255));
        //        } else {
        //            pa.fillRect(image.rect(), QColor(0, 0, 0, 0.1 * 255));
        //        }

        return QPixmap::fromImage(image);
    } else if (iconMode == QIcon::Disabled) {
        QImage image = pixmap.toImage();
        QPainter pa(&image);

        if (!pa.isActive())
            return QCommonStyle::generatedIconPixmap(iconMode, pixmap, opt);

        pa.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        pa.fillRect(image.rect(), QColor(0, 0, 0, 255 * 0.4));

        return QPixmap::fromImage(image);
    }

    return QCommonStyle::generatedIconPixmap(iconMode, pixmap, opt);
}

/*!
 * \~chinese \brief QEXTStyle::generatedBrush获取一个加工后的画刷
 * \~chinese \param \sa option QStyleOption
 * \~chinese \param base 画刷
 * \~chinese \param \sa cg QPalette::ColorGroup
 * \~chinese \param \sa role QPalette::ColorRole
 * \~chinese \return 加工后的画刷
*/
QBrush QEXTStyle::generatedBrush(const QStyleOption *option, const QBrush &base, QPalette::ColorGroup cg, QPalette::ColorRole role) const
{
    return generatedBrush(getState(option), option, base, cg, role);
}

/*!
 * \~chinese \brief QEXTStyle::generatedBrush获取一个加工后的画刷
 * \~chinese \param \sa state QEXTStyle::StyleState
 * \~chinese \param \sa option QStyleOption
 * \~chinese \param base 画刷
 * \~chinese \param \sa cg QPalette::ColorGroup
 * \~chinese \param \sa role QPalette::ColorRole
 * \~chinese \return 加工后的画刷
 */
QBrush QEXTStyle::generatedBrush(QEXTStyle::StyleState state, const QStyleOption *option, const QBrush &base, QPalette::ColorGroup cg, QPalette::ColorRole role) const
{
    //    if (auto proxy = qobject_cast<const QEXTStyle *>(this->proxy())) {
    //        return proxy->generatedBrush(getFlags(option) | state, base, cg, role, option);
    //    }

    //    return generatedBrush(getFlags(option) | state, base, cg, role, option);
    return QBrush();
}

/*!
 * \~chinese \brief QEXTStyle::generatedBrush获取一个加工后的画刷
 * \~chinese \param \sa flags QEXTStyle::StateFlags
 * \~chinese \param base 画刷
 * \~chinese \param \sa cg QPalette::ColorGroup
 * \~chinese \param \sa role QPalette::ColorRole
 * \~chinese \param \sa option QStyleOption
 * \~chinese \return 加工后的画刷
 */
QBrush QEXTStyle::generatedBrush(StateFlags flags, const QBrush &base, QPalette::ColorGroup cg, QPalette::ColorRole role, const QStyleOption *option) const
{
    Q_UNUSED(cg)

    QColor colorNew = base.color();

    if (!colorNew.isValid())
        return base;

    if ((flags & StyleState_Mask)  == SS_HoverState) {
        switch (role) {
        case QPalette::Button:
        case QPalette::Light:
        case QPalette::Dark:
            colorNew = adjustColor(colorNew, 0, 0, -10, 0, 0, 0, 0);
            break;
        case QPalette::Highlight:
            colorNew = adjustColor(colorNew, 0, 0, +20);
            break;
        case QPalette::ButtonText: {
            //            DGuiApplicationHelper::ColorType type = DGuiApplicationHelper::toColorType(option->palette);
            //            colorNew = adjustColor(colorNew, 0, 0, type == DGuiApplicationHelper::DarkType ? 20 : -50);
            break;
        }
        case QPalette::HighlightedText:
            colorNew = adjustColor(colorNew, 0, 0, 20);
            break;
        default:
            break;
        }

        return colorNew;
    } else if ((flags & StyleState_Mask) == SS_PressState) {
        QColor hightColor = option->palette.highlight().color();
        hightColor.setAlphaF(0.1);

        switch (role) {
        case QPalette::Button:
        case QPalette::Light: {
            colorNew = adjustColor(colorNew, 0, 0, -20, 0, 0, +20, 0);
            colorNew = blendColor(colorNew, hightColor);
            break;
        }
        case QPalette::Dark: {
            colorNew = adjustColor(colorNew, 0, 0, -15, 0, 0, +20, 0);
            colorNew = blendColor(colorNew, hightColor);
            break;
        }
        case QPalette::Highlight:
            colorNew = adjustColor(colorNew, 0, 0, -10);
            break;
        case QPalette::ButtonText:
            return option->palette.highlight();
        case QPalette::HighlightedText:
            colorNew = adjustColor(colorNew, 0, 0, 0, 0, 0, 0, -40);
            break;
        default:
            break;
        }

        return colorNew;
    }

    return base;
}

/*!
 * \~chinese \brief QEXTStyle::generatedBrush获取一个加工后的画刷
 * \~chinese \param \sa option QStyleOption
 * \~chinese \param base 画刷
 * \~chinese \param \sa cg QPalette::ColorGroup
 * \~chinese \param \sa type QEXTPalette::ColorType
 * \~chinese \return 加工后的画刷
 */
QBrush QEXTStyle::generatedBrush(const QStyleOption *option, const QBrush &base, QPalette::ColorGroup cg, QEXTPalette::ColorType type) const
{
    return generatedBrush(getState(option), option, base, cg, type);
}

/*!
 * \~chinese \brief QEXTStyle::generatedBrush获取一个加工后的画刷
 * \~chinese \param \sa state QEXTStyle::StyleState
 * \~chinese \param \sa option QStyleOption
 * \~chinese \param base 画刷
 * \~chinese \param \sa cg QPalette::ColorGroup
 * \~chinese \param \sa type QEXTPalette::ColorType
 * \~chinese \return 加工后的画刷
 */
QBrush QEXTStyle::generatedBrush(QEXTStyle::StyleState state, const QStyleOption *option, const QBrush &base, QPalette::ColorGroup cg, QEXTPalette::ColorType type) const
{
    //    if (auto proxy = qobject_cast<const QEXTStyle *>(this->proxy())) {
    //        return proxy->generatedBrush(getFlags(option) | state, base, cg, type, option);
    //    }

    //    return generatedBrush(getFlags(option) | state, base, cg, type, option);
    return QBrush();
}

/*!
 * \~chinese \brief QEXTStyle::generatedBrush获取一个加工后的画刷
 * \~chinese \param \sa flags QEXTStyle::StateFlags
 * \~chinese \param base画刷
 * \~chinese \param \sa cg QPalette::ColorGroup
 * \~chinese \param \sa type QEXTPalette::ColorType
 * \~chinese \param \sa option QStyleOption()
 * \~chinese \return 加工后的画刷
 */
QBrush QEXTStyle::generatedBrush(StateFlags flags, const QBrush &base, QPalette::ColorGroup cg, QEXTPalette::ColorType type, const QStyleOption *option) const
{
    Q_UNUSED(cg)
    Q_UNUSED(option)

    QColor colorNew = base.color();

    if (!colorNew.isValid())
        return base;

    if ((flags & StyleState_Mask)  == SS_HoverState) {
        switch (type) {
        case QEXTPalette::LightLively:
            colorNew = adjustColor(colorNew, 0, 0, +30, 0, 0, 0, 0);
            break;
        case QEXTPalette::DarkLively:
            colorNew = adjustColor(colorNew, 0, 0, +10, 0, 0, 0, 0);
            break;
        case QEXTPalette::ItemBackground: {
            //            DGuiApplicationHelper::ColorType ct = DGuiApplicationHelper::toColorType(colorNew);
            //            colorNew = ct == DGuiApplicationHelper::LightType ? adjustColor(colorNew, 0, 0, -10, 0, 0, 0, +10)
            //                                                              : adjustColor(colorNew, 0, 0, +10, 0, 0, 0, +10);
            break;
        }
        case QEXTPalette::TextWarning: {
            colorNew = adjustColor(colorNew, 0, 0, -10);
            break;
        }
        default:
            break;
        }

        return colorNew;
    } else if ((flags & StyleState_Mask) == SS_PressState) {
        switch (type) {
        case QEXTPalette::LightLively:
            colorNew = adjustColor(colorNew, 0, 0, -30, 0, 0, 0, 0);
            break;
        case QEXTPalette::DarkLively:
            colorNew = adjustColor(colorNew, 0, 0, -20, 0, 0, 0, 0);
            break;
        case QEXTPalette::TextWarning: {
            colorNew = adjustColor(colorNew, 0, 0, -30);
            break;
        }
        default:
            break;
        }

        return colorNew;
    } else if ((flags & StyleState_Mask) == SS_NormalState) {
        switch (type) {
        case QEXTPalette::LightLively:
            colorNew = adjustColor(colorNew, 0, 0, +40, 0, 0, 0, 0);
            break;
        case QEXTPalette::DarkLively:
            colorNew = adjustColor(colorNew, 0, 0, +20, 0, 0, 0, 0);
            break;
        default:
            break;
        }

        return colorNew;
    }

    return base;
}

/*!
 * \~chinese \class QEXTStyledIconEngine
 * \~chinese \brief QEXTStyledIconEngine一个修改的 QIconEngine 类
*/
void QEXTStyledIconEngine::drawIcon(const QIcon &icon, QPainter *pa, const QRectF &rect)
{
    icon.paint(pa, rect.toRect());
}

/*!
 * \~chinese \brief QEXTStyledIconEngine::QEXTStyledIconEngine
 * \~chinese \param drawFun
 * \~chinese \param iconName
 */
QEXTStyledIconEngine::QEXTStyledIconEngine(const QString &iconName)
    : QIconEngine(),
      //      m_drawFun(drawFun),
      m_iconName(iconName)
{
    m_painterRole = QEXTPalette::NoRole;
    m_widget = QEXT_NULLPTR;
}

/*!
 * \~chinese \brief QEXTStyledIconEngine::bindDrawFun活页夹
 * \~chinese \param drawFun
 */
//void QEXTStyledIconEngine::bindDrawFun(QEXTStyledIconEngine::DrawFun drawFun)
//{
//    m_drawFun = drawFun;
//}

/*!
 * \~chinese \brief QEXTStyledIconEngine::setIconName设置icon名称
 * \~chinese \param name 名称
 */
void QEXTStyledIconEngine::setIconName(const QString &name)
{
    m_iconName = name;
}

/*!
 * \~chinese \brief QEXTStyledIconEngine::pixmap
 * \~chinese \sa QIconEngine::pixmap()
 */
QPixmap QEXTStyledIconEngine::pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state)
{
    QImage image(size, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);
    QPainter pa(&image);
    paint(&pa, QRect(QPoint(0, 0), size), mode, state);
    pa.end();

    return QPixmap::fromImage(image);
}

/*!
 * \~chinese \brief QEXTStyledIconEngine::paint 重载paint
 * \~chinese \param painter画家
 * \~chinese \param palette调色板
 * \~chinese \param \sa rect QIconEngine::paint()
 */
void QEXTStyledIconEngine::paint(QPainter *painter, const QPalette &palette, const QRectF &rect)
{
    //    if (!m_drawFun)
    //        return;

    //    painter->setBrush(palette.background());
    //    painter->setPen(QPen(palette.foreground(), painter->pen().widthF()));

    //    m_drawFun(painter, rect);
}

/*!
 * \~chinese \brief QEXTStyledIconEngine::paint
 * \~chinese \sa QIconEngine::paint()
 */
void QEXTStyledIconEngine::paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state)
{
    Q_UNUSED(mode)
    Q_UNUSED(state)

    if (m_painterRole != QPalette::NoRole) {
        if (m_widget) {
            painter->setPen(m_widget->palette().brush(m_painterRole).color());
            painter->setBrush(m_widget->palette().brush(m_painterRole));
        } else {
            painter->setPen(qApp->palette().brush(m_painterRole).color());
            painter->setBrush(qApp->palette().brush(m_painterRole));
        }
    }

    //    m_drawFun(painter, rect);
}

/*!
 * \~chinese \brief QEXTStyledIconEngine::clone
 * \~chinese \sa QIconEngine::clone()
 */
//QIconEngine *QEXTStyledIconEngine::clone() const
//{
//    return new QEXTStyledIconEngine(m_drawFun, m_iconName);
//}

void QEXTStyledIconEngine::setFrontRole(const QWidget *widget, QPalette::ColorRole role)
{
    m_painterRole = role;
    m_widget = widget;
}

//void QEXTStyledIconEngine::virtual_hook(int id, void *data)
//{
//    if (id == IconNameHook) {
//        *reinterpret_cast<QString *>(data) = m_iconName;
//    } else if (id == IsNullHook) {
//        *reinterpret_cast<bool *>(data) = !m_drawFun;
//    }

//    return QIconEngine::virtual_hook(id, data);
//}
