#include <private/qextGraphicsView_p.h>
#include <qextGraphicsScene.h>

#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QSvgGenerator>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <qmath.h>

//http://www.w3.org/TR/SVG/Overview.html

#define MINIMUM_INCR   5

typedef struct
{
    double ruler_scale[16];
    int subdivide[5];
}SPRulerMetric;

// Ruler metric for general use.
static SPRulerMetric const ruler_metric_general = {
    { 1, 2, 5, 10, 25, 50, 100, 250, 500, 1000, 2500, 5000, 10000, 25000, 50000, 100000 },
    { 1, 5, 10, 50, 100 }
};

// Ruler metric for inch scales.
static SPRulerMetric const ruler_metric_inches = {
    { 1, 2, 4,  8, 16, 32,  64, 128, 256,  512, 1024, 2048, 4096, 8192, 16384, 32768 },
    { 1, 2,  4,  8,  16 }
};



QExtGraphicsViewRuleBarPrivate::QExtGraphicsViewRuleBarPrivate(QExtGraphicsViewRuleBar *q)
    : q_ptr(q)
    , m_faceColor(0xFF, 0xFF, 0xFF)
{
}

QExtGraphicsViewRuleBarPrivate::~QExtGraphicsViewRuleBarPrivate()
{

}

QExtGraphicsViewRuleBar::QExtGraphicsViewRuleBar(Qt::Orientation direction, QGraphicsView * view, QWidget *parent)
    : QWidget(parent)
    , dd_ptr(new QExtGraphicsViewRuleBarPrivate(this))
{
    Q_D(QExtGraphicsViewRuleBar);
    d->m_view = view;
    d->m_lower = d->m_upper = d->m_maxsize = 0;
    d->m_lastPos = QPoint(0,0);
    d->m_direction   = direction;

    QFont f(font());
    f.setBold(false);
    f.setPixelSize(10);
    this->setFont(f);
}

QExtGraphicsViewRuleBar::~QExtGraphicsViewRuleBar()
{

}

void QExtGraphicsViewRuleBar::setRange(double lower, double upper, double maxSize)
{
    Q_D(QExtGraphicsViewRuleBar);
    d->m_lower = lower;
    d->m_upper = upper;
    d->m_maxsize = maxSize;
}

void QExtGraphicsViewRuleBar::updatePosition(const QPoint &pos)
{
    Q_D(QExtGraphicsViewRuleBar);
    d->m_lastPos = pos;
    this->update();
}

void QExtGraphicsViewRuleBar::paintEvent(QPaintEvent *event)
{
    Q_D(QExtGraphicsViewRuleBar);
    Q_UNUSED(event);
    QPainter painter(this);
    QRect rulerRect = rect();
    painter.fillRect(rulerRect, d->m_faceColor);

    if (d->m_direction == Qt::Horizontal)
    {
        painter.drawLine(rulerRect.bottomLeft(), rulerRect.bottomRight());
    }
    else
    {
        painter.drawLine(rulerRect.topRight(), rulerRect.bottomRight());
    }

    this->drawTicker(&painter);
    this->drawPos(&painter);
}

void QExtGraphicsViewRuleBar::drawTicker(QPainter *painter)
{
    Q_D(QExtGraphicsViewRuleBar);
    int i;
    int width, height;
    int length, ideal_length;
    double lower = d->m_lower;
    double upper = d->m_upper; /* Upper and lower limits, in ruler units */
    double increment;    /* Number of pixels per unit */
    uint scale;        /* Number of units per major unit */
    double start, end, cur;
    char unit_str[32];
    char digit_str[2] = { '\0', '\0' };
    int digit_height;
    int digit_offset;
    int text_size;
    int pos;
    double max_size = d->m_maxsize;
    SPRulerMetric ruler_metric = ruler_metric_general; /* The metric to use for this unit system */
    QRect allocation = this->rect();
    QFontMetrics fm(this->font());
    digit_height = fm.height();
    digit_offset = 0;
    if (d->m_direction==Qt::Horizontal)
    {
        width = allocation.width();
        height = allocation.height();
    }
    else
    {
        width = allocation.height();
        height = allocation.width();
    }
    if ((upper - lower) == 0)
    {
        return;
    }
    increment = (double)width / (upper - lower);

    scale = qCeil(max_size);
    sprintf(unit_str, "%d", scale);
    text_size = strlen(unit_str) * digit_height + 1;
    for (scale = 0; scale < sizeof (ruler_metric.ruler_scale) / sizeof(ruler_metric.ruler_scale[0]); scale++)
    {
        if (ruler_metric.ruler_scale[scale] * qFabs(increment) > 2 * text_size)
        {
            break;
        }
    }
    if (scale == sizeof (ruler_metric.ruler_scale))
    {
        scale = sizeof (ruler_metric.ruler_scale) - 1;
    }
    length = 0;

    for (i = sizeof (ruler_metric.subdivide) / sizeof( ruler_metric.subdivide[0] ) - 1; i >= 0; i--)
    {
        double subd_incr;
        if (scale == 1 && i == 1)
        {
            subd_incr = 1.0 ;
        }
        else
        {
            subd_incr = ((double)ruler_metric.ruler_scale[scale] / (double)ruler_metric.subdivide[i]);
        }
        if (subd_incr * qFabs(increment) <= MINIMUM_INCR)
        {
            continue;
        }

        ideal_length = height / (i + 1) - 1;

        if (ideal_length > ++length)
        {
            length = ideal_length;
        }
        if (lower < upper)
        {
            start = qFloor(lower / subd_incr) * subd_incr;
            end   = qCeil(upper / subd_incr) * subd_incr;
        }
        else
        {
            start = qFloor(upper / subd_incr) * subd_incr;
            end   = qCeil(lower / subd_incr) * subd_incr;
        }
        int tick_index = 0;
        for (cur = start; cur <= end; cur += subd_incr)
        {
            pos = int(qRound((cur - lower) * increment + 1e-12));
            if (d->m_direction == Qt::Horizontal)
            {
                QRect rt(pos,height - length,1,length);
                painter->drawLine(rt.topLeft(), rt.bottomLeft());
            }
            else
            {
                QRect rt(height - length, pos, length,1);
                painter->drawLine(rt.topLeft(), rt.topRight());
            }
            double label_spacing_px = fabs(increment * (double)ruler_metric.ruler_scale[scale] / ruler_metric.subdivide[i]);
            if (i == 0 && (label_spacing_px > 6 * digit_height || tick_index % 2 == 0 || cur == 0) &&
                (label_spacing_px > 3 * digit_height || tick_index % 4 == 0 || cur == 0))
            {
                if (qAbs((int)cur) >= 2000 && (((int) cur)/1000)*1000 == ((int) cur))
                {
                    sprintf (unit_str, "%dk", ((int) cur)/1000);
                }
                else
                {
                    sprintf (unit_str, "%d", (int) cur);
                }
                if (d->m_direction == Qt::Horizontal)
                {
                    int w = fm.width(unit_str);
                    painter->drawText(pos + 2, allocation.top(), w, RULER_SIZE, Qt::AlignLeft|Qt::AlignTop,unit_str);
                }
                else
                {
#if 0
                   int w = fm.width("u") + 2;
                   int start = cur < 0 ? 1 : 0 ;
                   if ( start == 1 ){
                       QRect textRect(-w/2,-digit_height/2,w,digit_height);
                       painter->save();
                       painter->translate(4, pos + w/2 + 2 );
                       painter->rotate(90);
                       painter->drawText(textRect,
                                         Qt::AlignRight,QString(unit_str[0]));
                       painter->restore();
                   }
                   for (int j = start; j < (int) strlen (unit_str); j++){
                       digit_str[0] = unit_str[j];
                       painter->drawText(1,
                                         pos + digit_height * j,
                                         w,
                                         digit_height,
                                         Qt::AlignLeft|Qt::AlignTop,QString(digit_str[0]));
                   }
#else
                    int w = fm.width(unit_str);
                    QRect textRect(-w / 2, -RULER_SIZE / 2, w, RULER_SIZE);
                    painter->save();
                    painter->translate(8, pos + w / 2 + 2);
                    painter->rotate(-90);
                    painter->drawText(textRect, Qt::AlignRight, unit_str);
                    painter->restore();
#endif
                }
            }
            tick_index++;
        }
    }
}

void QExtGraphicsViewRuleBar::drawPos(QPainter *painter)
{
    Q_D(QExtGraphicsViewRuleBar);
    int x, y;
    int width, height;
    int bs_width, bs_height;
    QRect allocation = this->rect();
    double position;
    double lower = d->m_lower;
    double upper = d->m_upper;
    if (d->m_direction == Qt::Horizontal)
    {
        width = allocation.width();
        height = allocation.height();
        bs_width = height / 2 + 2 ;
        bs_width |= 1;  /* make sure it's odd */
        bs_height = bs_width / 2 + 1;
        position = lower + (upper - lower) * d->m_lastPos.x() / allocation.width();
    }
    else
    {
        width = allocation.height();
        height = allocation.width();
        bs_height = width / 2 + 2 ;
        bs_height |= 1;  /* make sure it's odd */
        bs_width = bs_height / 2 + 1;
        position = lower + (upper - lower) *  d->m_lastPos.y() / allocation.height() ;
    }
    if ((bs_width > 0) && (bs_height > 0))
    {
        double increment;
        if (d->m_direction == Qt::Horizontal)
        {
            increment = (double)width / (upper - lower);
            x = qRound((position - lower) * increment) + bs_width / 2 - 1;
            y = (height + bs_height) / 2;
            painter->drawLine(d->m_lastPos.x(), 0, d->m_lastPos.x(), height);
        }
        else
        {
            increment = (double)height / (upper - lower);
            x = (width + bs_width) / 2 ;
            y = qRound((position - lower) * increment) + (bs_height) / 2 - 1;
            painter->drawLine(0, d->m_lastPos.y(), width, d->m_lastPos.y());
        }
    }
}

QExtGraphicsViewCornerBox::QExtGraphicsViewCornerBox(QWidget *parent)
    : QWidget(parent)
{
}

QExtGraphicsViewCornerBox::~QExtGraphicsViewCornerBox()
{

}

void QExtGraphicsViewCornerBox::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0xFF, 0xFF, 0xFF));

    painter.setPen(Qt::DashLine);
    painter.drawLine(rect().center().x(),rect().top(),rect().center().x(),rect().bottom());
    painter.drawLine(rect().left(),rect().center().y(),rect().right(),rect().center().y());

    painter.drawLine(rect().topRight(),rect().bottomRight());
    painter.drawLine(rect().bottomLeft(),rect().bottomRight());
}



QExtGraphicsViewPrivate::QExtGraphicsViewPrivate(QExtGraphicsView *q)
    : q_ptr(q)
    , m_hRulerBar(new QExtGraphicsViewRuleBar(Qt::Horizontal, q, q))
    , m_vRulerBar(new QExtGraphicsViewRuleBar(Qt::Vertical, q, q))
    , m_cornerBox(new QExtGraphicsViewCornerBox(q))
    , m_modified(false)
    , m_untitled(true)
{

}

QExtGraphicsViewPrivate::~QExtGraphicsViewPrivate()
{

}

bool QExtGraphicsViewPrivate::maybeSave()
{
    Q_Q(QExtGraphicsView);
    if (m_modified)
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(q, QObject::tr("MDI"),
                                   QObject::tr("'%1' has been modified.\nDo you want to save your changes?").
                                   arg(q->userFriendlyCurrentFile()),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
        {
            return q->save();
        }
        else if (ret == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}

void QExtGraphicsViewPrivate::loadCanvas(QXmlStreamReader *xml)
{
    Q_Q(QExtGraphicsView);
    Q_ASSERT(xml->isStartElement() && xml->name() == "canvas");

    while (xml->readNextStartElement())
    {
        QExtGraphicsAbstractShapeItem * item = NULL;
        if (xml->name() == QObject::tr("rect"))
        {
            item = new QExtGraphicsRectItem(QRect(0,0,1,1));
        }
        else if (xml->name() == QObject::tr("roundrect"))
        {
            item = new QExtGraphicsRectItem(QRect(0,0,1,1),true);
        }
        else if (xml->name() == QObject::tr("ellipse"))
        {
            item = new QExtGraphicsEllipseItem(QRect(0,0,1,1));
        }
        else if (xml->name()== QObject::tr("polygon"))
        {
            item = new QExtGraphicsPolygonItem();
        }
        else if (xml->name()== QObject::tr("bezier"))
        {
            item = new QExtGraphicsBezierItem();
        }
        else if (xml->name() == QObject::tr("polyline"))
        {
            item = new QExtGraphicsBezierItem(false);
        }
        else if (xml->name() == QObject::tr("line"))
        {
            item = new QExtGraphicsLineItem();
        }
        else if (xml->name() == QObject::tr("group"))
        {
            item =qgraphicsitem_cast<QExtGraphicsAbstractShapeItem*>(this->loadGroupFromXML(xml));
        }
        else
        {
            xml->skipCurrentElement();
        }

        if (item && item->loadFromXml(xml))
        {
            q->scene()->addItem(item);
        }
        else if (item)
        {
            delete item;
        }
    }
}

void QExtGraphicsViewPrivate::setCurrentFile(const QString &fileName)
{
    Q_Q(QExtGraphicsView);
    m_curFile = QFileInfo(fileName).canonicalFilePath();
    m_untitled = false;
    q->setModified(false);
    q->setWindowModified(false);
    q->setWindowTitle(q->userFriendlyCurrentFile() + "[*]");
}

QString QExtGraphicsViewPrivate::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

QExtGraphicsItemGroup *QExtGraphicsViewPrivate::loadGroupFromXML(QXmlStreamReader *xml)
{
    Q_Q(QExtGraphicsView);
    QList<QGraphicsItem *> items;
    qreal angle = xml->attributes().value(QObject::tr("rotate")).toDouble();
    while (xml->readNextStartElement())
    {
        QExtGraphicsAbstractShapeItem *item = QEXT_NULLPTR;
        if (xml->name() == QObject::tr("rect"))
        {
            item = new QExtGraphicsRectItem(QRect(0, 0, 1, 1));
        }
        else if (xml->name() == QObject::tr("roundrect"))
        {
            item = new QExtGraphicsRectItem(QRect(0, 0, 1, 1), true);
        }
        else if (xml->name() == QObject::tr("ellipse"))
        {
            item = new QExtGraphicsEllipseItem(QRect(0,0,1,1));
        }
        else if (xml->name()== QObject::tr("polygon"))
        {
            item = new QExtGraphicsPolygonItem();
        }
        else if (xml->name()== QObject::tr("bezier"))
        {
            item = new QExtGraphicsBezierItem();
        }
        else if (xml->name() == QObject::tr("polyline"))
        {
            item = new QExtGraphicsBezierItem(false);
        }
        else if (xml->name() == QObject::tr("line"))
        {
            item = new QExtGraphicsLineItem();
        }
        else if (xml->name() == QObject::tr("group"))
        {
            item = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem*>(this->loadGroupFromXML(xml));
        }
        else
        {
            xml->skipCurrentElement();
        }
        if (item && item->loadFromXml(xml))
        {
            q->scene()->addItem(item);
            items.append(item);
        }
        else if (item)
        {
            delete item;
        }
    }

    if (items.count() > 0)
    {
        QExtGraphicsScene *s = dynamic_cast<QExtGraphicsScene*>(q->scene());
        QExtGraphicsItemGroup *group = s->createGroup(items, false);
        if (group)
        {
            group->setRotation(angle);
            group->updateCoordinate();
            //qDebug()<<"angle:" <<angle;
        }
        return group;
    }
    return QEXT_NULLPTR;
}


QExtGraphicsView::QExtGraphicsView(QGraphicsScene *scene)
    : QGraphicsView(scene)
    , dd_ptr(new QExtGraphicsViewPrivate(this))
{
    this->setViewport(new QWidget);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

QExtGraphicsView::~QExtGraphicsView()
{

}

void QExtGraphicsView::zoomIn()
{
    this->scale(1.2,1.2);
    this->updateRuler();
}

void QExtGraphicsView::zoomOut()
{
    this->scale(1 / 1.2, 1 / 1.2);
    this->updateRuler();
}

void QExtGraphicsView::newFile()
{
    Q_D(QExtGraphicsView);
    static int sequenceNumber = 1;
    d->m_untitled = true;
    d->m_curFile = tr("drawing%1.xml").arg(sequenceNumber++);
    this->setWindowTitle(d->m_curFile + "[*]");
}

bool QExtGraphicsView::loadFile(const QString &fileName)
{
    Q_D(QExtGraphicsView);
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Qt Drawing"),
                             tr("Cannot read file %1:\n%2.").arg(fileName).arg(file.errorString()));
        return false;
    }

    QXmlStreamReader xml(&file);
    if (xml.readNextStartElement())
    {
        if (xml.name() == tr("canvas"))
        {
            int width = xml.attributes().value(tr("width")).toInt();
            int height = xml.attributes().value(tr("height")).toInt();
            scene()->setSceneRect(0, 0, width, height);
            d->loadCanvas(&xml);
        }
    }

    d->setCurrentFile(fileName);
    qDebug() << xml.errorString();
    return !xml.error();
}

bool QExtGraphicsView::save()
{
    Q_D(QExtGraphicsView);
    if (d->m_untitled)
    {
        return this->saveAs();
    }
    else
    {
        return this->saveFile(d->m_curFile);
    }
}

bool QExtGraphicsView::saveAs()
{
    Q_D(QExtGraphicsView);
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), d->m_curFile);
    if (fileName.isEmpty())
    {
        return false;
    }

    return this->saveFile(fileName);
}

bool QExtGraphicsView::saveFile(const QString &fileName)
{
    Q_D(QExtGraphicsView);
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Qt Drawing"),
                             tr("Cannot write file %1:\n%2.").arg(fileName).arg(file.errorString()));
        return false;
    }

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeDTD("<!DOCTYPE qdraw>");
    xml.writeStartElement("canvas");
    xml.writeAttribute("width",QString("%1").arg(this->scene()->width()));
    xml.writeAttribute("height",QString("%1").arg(this->scene()->height()));

    foreach (QGraphicsItem *item, scene()->items())
    {
        QExtGraphicsAbstractShapeItem *ab = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem*>(item);
        QGraphicsItemGroup *g = dynamic_cast<QGraphicsItemGroup*>(item->parentItem());
        if (ab &&!qgraphicsitem_cast<QExtGraphicsSizeHandle *>(ab) && !g)
        {
            ab->saveToXml(&xml);
        }
    }
    xml.writeEndElement();
    xml.writeEndDocument();
#if 0
    QSvgGenerator generator;
    generator.setFileName(fileName);
    generator.setSize(QSize(800, 600));
    generator.setTitle(tr("SVG Generator Example Drawing"));
    generator.setDescription(tr("An SVG drawing created by the SVG Generator "
                                "Example provided with Qt."));
//![configure SVG generator]
//![begin painting]
    QPainter painter;
    painter.begin(&generator);
//![begin painting]
//!
    scene()->clearSelection();
    scene()->render(&painter);
//![end painting]
    painter.end();
//![end painting]
#endif
    d->setCurrentFile(fileName);
    return true;
}

QString QExtGraphicsView::userFriendlyCurrentFile()
{
    Q_D(QExtGraphicsView);
    return d->strippedName(d->m_curFile);
}

QString QExtGraphicsView::currentFile() const
{
    Q_D(const QExtGraphicsView);
    return d->m_curFile;
}

bool QExtGraphicsView::isModified() const
{
    Q_D(const QExtGraphicsView);
    return d->m_modified;
}

void QExtGraphicsView::setModified(bool value)
{
    Q_D(QExtGraphicsView);
    if (value != d->m_modified)
    {
        d->m_modified = value;
    }
}

void QExtGraphicsView::closeEvent(QCloseEvent *event)
{
    Q_D(QExtGraphicsView);
    if (d->maybeSave())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void QExtGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(QExtGraphicsView);
    QPointF pt = this->mapToScene(event->pos());
    d->m_hRulerBar->updatePosition(event->pos());
    d->m_vRulerBar->updatePosition(event->pos());
    emit this->positionChanged(pt.x(), pt.y());
    QGraphicsView::mouseMoveEvent(event);
}

void QExtGraphicsView::resizeEvent(QResizeEvent *event)
{
    Q_D(QExtGraphicsView);
    QGraphicsView::resizeEvent(event);

    this->setViewportMargins(RULER_SIZE - 1, RULER_SIZE - 1, 0, 0);
    d->m_hRulerBar->resize(this->size().width()- RULER_SIZE - 1, RULER_SIZE);
    d->m_hRulerBar->move(RULER_SIZE, 0);
    d->m_vRulerBar->resize(RULER_SIZE, this->size().height() - RULER_SIZE - 1);
    d->m_vRulerBar->move(0, RULER_SIZE);

    d->m_cornerBox->resize(RULER_SIZE, RULER_SIZE);
    d->m_cornerBox->move(0, 0);
    this->updateRuler();
}

void QExtGraphicsView::scrollContentsBy(int dx, int dy)
{
    QGraphicsView::scrollContentsBy(dx, dy);
    this->updateRuler();
}

void QExtGraphicsView::updateRuler()
{
    Q_D(QExtGraphicsView);
    if (this->scene() == 0)
    {
        return;
    }
    QRectF viewbox = this->rect();
    QPointF offset = this->mapFromScene(this->scene()->sceneRect().topLeft());
    double factor = 1.0 / transform().m11();
    double lower_x = factor * (viewbox.left() - offset.x());
    double upper_x = factor * (viewbox.right() - RULER_SIZE - offset.x());
    d->m_hRulerBar->setRange(lower_x, upper_x, upper_x - lower_x);
    d->m_hRulerBar->update();

    double lower_y = factor * (viewbox.top() - offset.y()) * -1;
    double upper_y = factor * (viewbox.bottom() - RULER_SIZE - offset.y()) * -1;

    d->m_vRulerBar->setRange(lower_y,upper_y,upper_y - lower_y);
    d->m_vRulerBar->update();

    //    qDebug()<<viewbox<<QPoint(lower_x,upper_x) << QPoint(lower_y,upper_y) << offset;
}
