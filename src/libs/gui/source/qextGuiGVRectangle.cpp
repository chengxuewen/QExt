#include <qextGuiGVRectangle.h>
#include <qextGuiGVRectangle_p.h>

#include <QDebug>
#include <QPainter>
#include <QTileRules>
#include <QPixmapCache>
#include <qmath.h>

int QEXTGuiGVRectanglePrivate::sm_doUpdateSlotIdx = -1;

QEXTGuiGVRectanglePrivate::QEXTGuiGVRectanglePrivate(QEXTGuiGVRectangle *q)
    : QEXTGuiGVItemPrivate(q)
    , m_color(Qt::white)
    , m_gradient(QEXT_DECL_NULLPTR)
    , m_pen(QEXT_DECL_NULLPTR)
    , m_radius(0)
    , m_paintmargin(0)
{

}

QEXTGuiGVRectanglePrivate::~QEXTGuiGVRectanglePrivate()
{
    delete m_pen;
}

QEXTGuiPen *QEXTGuiGVRectanglePrivate::pen()
{
    if (!m_pen)
    {
        Q_Q(QEXTGuiGVRectangle);
        m_pen = new QEXTGuiPen;
        static int penChangedSignalIdx = -1;
        if (penChangedSignalIdx < 0)
        {
            penChangedSignalIdx = QEXTGuiPen::staticMetaObject.indexOfSignal("penChanged()");
        }
        if (sm_doUpdateSlotIdx < 0)
        {
            sm_doUpdateSlotIdx = QEXTGuiGVRectangle::staticMetaObject.indexOfSlot("doUpdate()");
        }
        QMetaObject::connect(m_pen, penChangedSignalIdx, q, sm_doUpdateSlotIdx);
    }
    return m_pen;
}

void QEXTGuiGVRectanglePrivate::setPaintMargin(qreal margin)
{
    Q_Q(QEXTGuiGVRectangle);
    if (margin != m_paintmargin)
    {
        q->prepareGeometryChange();
        m_paintmargin = margin;
    }
}



QEXTGuiGVRectangle::QEXTGuiGVRectangle(QEXTGuiGVItem *parent)
    : QEXTGuiGVItem(new QEXTGuiGVRectanglePrivate(this), parent)
{

}

QEXTGuiGVRectangle::~QEXTGuiGVRectangle()
{

}

QColor QEXTGuiGVRectangle::color() const
{
    Q_D(const QEXTGuiGVRectangle);
    return d->m_color;
}

void QEXTGuiGVRectangle::setColor(const QColor &color)
{
    Q_D(QEXTGuiGVRectangle);
    if (d->m_color != color)
    {
        d->m_color = color;
        d->m_rectImage = QPixmap();
        this->update();
        emit this->colorChanged();
    }
}

QEXTGuiPen *QEXTGuiGVRectangle::border()
{
    Q_D(QEXTGuiGVRectangle);
    return d->pen();
}

QEXTGuiGradient *QEXTGuiGVRectangle::gradient() const
{
    Q_D(const QEXTGuiGVRectangle);
    return d->m_gradient;
}

void QEXTGuiGVRectangle::setGradient(QEXTGuiGradient *gradient)
{
    Q_D(QEXTGuiGVRectangle);
    if (d->m_gradient != gradient)
    {
        static int updatedSignalIdx = -1;
        if (updatedSignalIdx < 0)
        {
            updatedSignalIdx = QEXTGuiGradient::staticMetaObject.indexOfSignal("updated()");
        }
        if (d->sm_doUpdateSlotIdx < 0)
        {
            d->sm_doUpdateSlotIdx = QEXTGuiGVRectangle::staticMetaObject.indexOfSlot("doUpdate()");
        }
        if (d->m_gradient)
        {
            QMetaObject::disconnect(d->m_gradient, updatedSignalIdx, this, d->sm_doUpdateSlotIdx);
        }
        d->m_gradient = gradient;
        if (d->m_gradient)
        {
            QMetaObject::connect(d->m_gradient, updatedSignalIdx, this, d->sm_doUpdateSlotIdx);
        }
        this->update();
    }
}

qreal QEXTGuiGVRectangle::radius() const
{
    Q_D(const QEXTGuiGVRectangle);
    return d->m_radius;
}

void QEXTGuiGVRectangle::setRadius(qreal radius)
{
    Q_D(QEXTGuiGVRectangle);
    if (d->m_radius != radius)
    {
        d->m_radius = radius;
        d->m_rectImage = QPixmap();
        this->update();
        emit this->radiusChanged();
    }
}

QRectF QEXTGuiGVRectangle::boundingRect() const
{
    Q_D(const QEXTGuiGVRectangle);
    return QRectF(-d->m_paintmargin, -d->m_paintmargin,
                  d->m_width + d->m_paintmargin * 2,
                  d->m_height + d->m_paintmargin * 2);
}

void QEXTGuiGVRectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    Q_D(QEXTGuiGVRectangle);
//    QRectF rect(0, 0, this->width(), this->height());
//    painter->setPen(d->m_color);
//    painter->setBrush(d->m_color);
//    painter->setRenderHints(QPainter::Antialiasing, true);
//    painter->drawRoundedRect(rect, 5, 5);
//    return;

    if (this->width() <= 0 || this->height() <= 0)
    {
        return;
    }

    if (d->m_radius > 0 || (d->m_pen && d->m_pen->isValid()) || (d->m_gradient && d->m_gradient->gradient()) )
    {
        this->drawRect(*painter);
    }
    else
    {
        bool oldAA = painter->testRenderHint(QPainter::Antialiasing);

        if (d->m_smooth)
        {
            painter->setRenderHints(QPainter::Antialiasing, true);
        }
        painter->fillRect(QRectF(0, 0, this->width(), this->height()), d->m_color);
        if (d->m_smooth)
        {
            painter->setRenderHint(QPainter::Antialiasing, oldAA);
        }
    }
}

void QEXTGuiGVRectangle::doUpdate()
{
    Q_D(QEXTGuiGVRectangle);
    d->m_rectImage = QPixmap();
    const int pw = (d->m_pen && d->m_pen->isValid()) ? d->m_pen->width() : 0;
    d->setPaintMargin((pw + 1) / 2);
    this->update();
}

void QEXTGuiGVRectangle::generateRoundedRect()
{
    Q_D(QEXTGuiGVRectangle);
    if (d->m_rectImage.isNull())
    {
        const int penWidth = (d->m_pen && d->m_pen->isValid()) ? d->m_pen->width() : 0;
        const int radius = qCeil(d->m_radius);    //ensure odd numbered width/height so we get 1-pixel center

        QString key = QLatin1String("q_") + QString::number(penWidth) + d->m_color.name();
        key += QString::number(d->m_color.alpha(), 16) + QLatin1Char('_') + QString::number(radius);
        if (d->m_pen && d->m_pen->isValid())
        {
            key += d->m_pen->color().name() + QString::number(d->m_pen->color().alpha(), 16);
        }

        if (!QPixmapCache::find(key, &d->m_rectImage))
        {
            d->m_rectImage = QPixmap(radius * 2 + 3 + penWidth * 2, radius * 2 + 3 + penWidth * 2);
            d->m_rectImage.fill(Qt::transparent);
            QPainter painter(&(d->m_rectImage));
            painter.setRenderHint(QPainter::Antialiasing);
            if (d->m_pen && d->m_pen->isValid())
            {
                QPen pen(QColor(d->m_pen->color()), d->m_pen->width());
                painter.setPen(pen);
            }
            else
            {
                painter.setPen(Qt::NoPen);
            }
            painter.setBrush(d->m_color);
            if (penWidth % 2)
            {
                QRectF rect(qreal(penWidth) / 2 + 1, qreal(penWidth) / 2 + 1, d->m_rectImage.width() - (penWidth + 1), d->m_rectImage.height() - (penWidth + 1));
                painter.drawRoundedRect(rect, d->m_radius, d->m_radius);
            }
            else
            {
                QRectF rect(qreal(penWidth) / 2, qreal(penWidth) / 2, d->m_rectImage.width() - penWidth, d->m_rectImage.height() - penWidth);
                painter.drawRoundedRect(rect, d->m_radius, d->m_radius);
            }

            // end painting before inserting pixmap
            // to pixmap cache to avoid a deep copy
            painter.end();
            QPixmapCache::insert(key, d->m_rectImage);
        }
    }
}

void QEXTGuiGVRectangle::generateBorderedRect()
{
    Q_D(QEXTGuiGVRectangle);
    if (d->m_rectImage.isNull())
    {
        const int penWidth = d->m_pen && d->m_pen->isValid() ? d->m_pen->width() : 0;

        QString key = QLatin1String("q_") + QString::number(penWidth) + d->m_color.name() + QString::number(d->m_color.alpha(), 16);
        if (d->m_pen && d->m_pen->isValid())
        {
            key += d->m_pen->color().name() + QString::number(d->m_pen->color().alpha(), 16);
        }

        if (!QPixmapCache::find(key, &d->m_rectImage))
        {
            // Adding 5 here makes qDrawBorderPixmap() paint correctly with smooth: true
            d->m_rectImage = QPixmap(penWidth * 2 + 5, penWidth * 2 + 5);
            d->m_rectImage.fill(Qt::transparent);
            QPainter painter(&(d->m_rectImage));
            painter.setRenderHint(QPainter::Antialiasing);
            if (d->m_pen && d->m_pen->isValid())
            {
                QPen pen(QColor(d->m_pen->color()), d->m_pen->width());
                pen.setJoinStyle(Qt::MiterJoin);
                painter.setPen(pen);
            }
            else
            {
                painter.setPen(Qt::NoPen);
            }
            painter.setBrush(d->m_color);
            if (penWidth % 2)
            {
                painter.drawRect(QRectF(qreal(penWidth) / 2 + 1, qreal(penWidth) / 2 + 1, d->m_rectImage.width() - (penWidth + 1), d->m_rectImage.height() - (penWidth + 1)));
            }
            else
            {
                painter.drawRect(QRectF(qreal(penWidth) / 2, qreal(penWidth) / 2, d->m_rectImage.width() - penWidth, d->m_rectImage.height() - penWidth));
            }

            // end painting before inserting pixmap
            // to pixmap cache to avoid a deep copy
            painter.end();
            QPixmapCache::insert(key, d->m_rectImage);
        }
    }
}

void QEXTGuiGVRectangle::drawRect(QPainter &painter)
{
    Q_D(QEXTGuiGVRectangle);
    if ((d->m_gradient && d->m_gradient->gradient())
            || d->m_radius > this->width() / 2 || d->m_radius > this->height() / 2
            || this->width() < 3 || this->height() < 3)
    {
        // XXX This path is still slower than the image path
        // Image path won't work for gradients or invalid radius though
        bool oldAA = painter.testRenderHint(QPainter::Antialiasing);
        if (d->m_smooth)
        {
            painter.setRenderHint(QPainter::Antialiasing);
            //            painter.setRenderHint(QPainter::HighQualityAntialiasing);
//            painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing |
//                                   QPainter::SmoothPixmapTransform | QPainter::Qt4CompatiblePainting);
        }
        if (d->m_pen && d->m_pen->isValid())
        {
            QPen pen(QColor(d->m_pen->color()), d->m_pen->width());
            pen.setJoinStyle(Qt::MiterJoin);
            painter.setPen(pen);
        }
        else
        {
            painter.setPen(Qt::NoPen);
        }
        if (d->m_gradient && d->m_gradient->gradient())
        {
            painter.setBrush(*d->m_gradient->gradient());
        }
        else
        {
            painter.setBrush(d->m_color);
        }
        const int penWidth = d->m_pen && d->m_pen->isValid() ? d->m_pen->width() : 0;
        QRectF rect;
        if (penWidth % 2)
        {
            rect = QRectF(0.5, 0.5, this->width() - 1, this->height() - 1);
        }
        else
        {
            rect = QRectF(0, 0, this->width(), this->height());
        }
        qreal radius = d->m_radius;
        if (radius > this->width() / 2 || radius > this->height() / 2)
        {
            radius = qMin(this->width() / 2, this->height() / 2);
        }
        if (radius > 0.)
        {
            painter.drawRoundedRect(rect, radius, radius);
        }
        else
        {
            painter.drawRect(rect);
        }
        if (d->m_smooth)
        {
            painter.setRenderHint(QPainter::Antialiasing, oldAA);
        }
    }
    else
    {
        bool oldAA = painter.testRenderHint(QPainter::Antialiasing);
        bool oldSmooth = painter.testRenderHint(QPainter::SmoothPixmapTransform);
        if (d->m_smooth)
        {
            painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform, d->m_smooth);
        }

        const int penWidth = d->m_pen && d->m_pen->isValid() ? (d->m_pen->width() + 1) / 2 * 2 : 0;

        if (d->m_radius > 0)
        {
            this->generateRoundedRect();
        }
        else
        {
            this->generateBorderedRect();
        }

        int xOffset = (d->m_rectImage.width() - 1) / 2;
        int yOffset = (d->m_rectImage.height() - 1) / 2;
        Q_ASSERT(d->m_rectImage.width() == 2 * xOffset + 1);
        Q_ASSERT(d->m_rectImage.height() == 2 * yOffset + 1);

        // check whether we've eliminated the center completely
        if (2 * xOffset > this->width() + penWidth)
        {
            xOffset = (this->width() + penWidth) / 2;
        }
        if (2 * yOffset > this->height() + penWidth)
        {
            yOffset = (this->height() + penWidth) / 2;
        }

        QMargins margins(xOffset, yOffset, xOffset, yOffset);
        QTileRules rules(Qt::StretchTile, Qt::StretchTile);
        //NOTE: even though our item may have qreal-based width and height, qDrawBorderPixmap only supports QRects
        QRect rect(-penWidth / 2, -penWidth / 2, width() + penWidth, height() + penWidth);
        qDrawBorderPixmap(&painter, rect, margins, d->m_rectImage, d->m_rectImage.rect(), margins, rules);

        if (d->m_smooth)
        {
            painter.setRenderHint(QPainter::Antialiasing, oldAA);
            painter.setRenderHint(QPainter::SmoothPixmapTransform, oldSmooth);
        }
    }
}
