#include <qextGraphicsView.h>
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

//http://www.w3.org/TR/SVG/Overview.html

#define MINIMUM_INCR   5

typedef struct
{
    double ruler_scale[16];
    int    subdivide[5];
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


QtRuleBar::QtRuleBar(Qt::Orientation direction, QGraphicsView * view, QWidget *parent)
    :QWidget(parent),
    m_view(view),
    m_faceColor(0xFF, 0xFF, 0xFF)
{
    m_lower = m_upper = m_maxsize = 0;
    m_lastPos = QPoint(0,0);
    m_direction   = direction;
    QFont f(font());
    f.setBold(false);
    f.setPixelSize(10);
    setFont(f);
}

void QtRuleBar::setRange(double lower, double upper, double max_size)
{
    m_lower = lower;
    m_upper = upper;
    m_maxsize = max_size;
}

void QtRuleBar::updatePosition(const QPoint &pos)
{
    m_lastPos = pos;
    update();
}

void QtRuleBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QRect rulerRect = rect();
    painter.fillRect(rulerRect,m_faceColor);

    if ( m_direction == Qt::Horizontal ){
        painter.drawLine(rulerRect.bottomLeft(),rulerRect.bottomRight());
    }
    else{
        painter.drawLine(rulerRect.topRight(),rulerRect.bottomRight());
    }

    drawTicker(&painter);
    drawPos(&painter);
}

void QtRuleBar::drawTicker(QPainter *painter)
{
    int             i;
    int             width, height;
    int             length, ideal_length;
    double          lower = m_lower , upper = m_upper; /* Upper and lower limits, in ruler units */
    double          increment;    /* Number of pixels per unit */
    uint            scale;        /* Number of units per major unit */
    double          start, end, cur;
    char            unit_str[32];
    char            digit_str[2] = { '\0', '\0' };
    int             digit_height;
    int             digit_offset;
    int             text_size;
    int             pos;
    double          max_size = m_maxsize;
    SPRulerMetric    ruler_metric = ruler_metric_general; /* The metric to use for this unit system */
    QRect allocation = this->rect();
    QFontMetrics fm(font());
    digit_height = fm.height();
    digit_offset = 0;
    if (m_direction==Qt::Horizontal){
        width = allocation.width();
        height = allocation.height();
    }else{
        width = allocation.height();
        height = allocation.width();
    }
    if ( (upper - lower) == 0 ) return ;
    increment = (double) width / (upper - lower);

    scale = ceil (max_size);
    sprintf (unit_str, "%d", scale);
    text_size = strlen (unit_str) * digit_height + 1;
    for (scale = 0; scale < sizeof (ruler_metric.ruler_scale) /
                                sizeof(ruler_metric.ruler_scale[0]); scale++)
        if (ruler_metric.ruler_scale[scale] * fabs (increment) > 2 * text_size)
            break;
    if (scale == sizeof (ruler_metric.ruler_scale))
        scale = sizeof (ruler_metric.ruler_scale) - 1;
    length = 0;

    for (i = sizeof (ruler_metric.subdivide) /
                 sizeof( ruler_metric.subdivide[0] ) - 1; i >= 0; i--){
        double subd_incr;
        if (scale == 1 && i == 1 )
            subd_incr = 1.0 ;
        else
            subd_incr = ((double)ruler_metric.ruler_scale[scale] /
                         (double)ruler_metric.subdivide[i]);
        if (subd_incr * fabs (increment) <= MINIMUM_INCR)
            continue;

        ideal_length = height / (i + 1) - 1;

        if (ideal_length > ++length)
            length = ideal_length;
        if (lower < upper){
            start = floor (lower / subd_incr) * subd_incr;
            end   = ceil  (upper / subd_incr) * subd_incr;
        }else
        {
            start = floor (upper / subd_incr) * subd_incr;
            end   = ceil  (lower / subd_incr) * subd_incr;
        }
        int tick_index = 0;
        for (cur = start; cur <= end; cur += subd_incr){
            pos = int(qRound((cur - lower) * increment + 1e-12));
            if (m_direction==Qt::Horizontal){
                QRect rt(pos,height-length,1,length);
                painter->drawLine(rt.topLeft(),rt.bottomLeft());
            }else{
                QRect rt(height-length,pos,length,1);
                painter->drawLine(rt.topLeft(),rt.topRight());
            }
            double label_spacing_px = fabs(increment*(double)ruler_metric.ruler_scale[scale]/ruler_metric.subdivide[i]);
            if (i == 0 &&
                (label_spacing_px > 6*digit_height || tick_index%2 == 0 || cur == 0) &&
                (label_spacing_px > 3*digit_height || tick_index%4 == 0 || cur == 0))
            {
                if (qAbs((int)cur) >= 2000 && (((int) cur)/1000)*1000 == ((int) cur))
                    sprintf (unit_str, "%dk", ((int) cur)/1000);
                else
                    sprintf (unit_str, "%d", (int) cur);
                if (m_direction==Qt::Horizontal){
                    int w = fm.width(unit_str);
                    painter->drawText(pos + 2,
                                      allocation.top(),
                                      w,
                                      RULER_SIZE,
                                      Qt::AlignLeft|Qt::AlignTop,unit_str);
                } else{
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
                    QRect textRect(-w/2,-RULER_SIZE/2,w,RULER_SIZE);
                    painter->save();
                    painter->translate(8, pos + w/2+2);
                    painter->rotate(-90);
                    painter->drawText(textRect,Qt::AlignRight,unit_str);
                    painter->restore();
#endif
                }
            }
            tick_index++;
        }
    }
}

void QtRuleBar::drawPos(QPainter *painter)
{
    int  x, y;
    int  width, height;
    int  bs_width, bs_height;
    QRect allocation = this->rect();
    double position;
    double lower = m_lower;
    double upper = m_upper;
    if (m_direction==Qt::Horizontal){
        width = allocation.width();
        height = allocation.height();
        bs_width = height / 2 + 2 ;
        bs_width |= 1;  /* make sure it's odd */
        bs_height = bs_width / 2 + 1;
        position = lower + (upper - lower) * m_lastPos.x() / allocation.width();
    }else{
        width = allocation.height();
        height = allocation.width();
        bs_height = width / 2 + 2 ;
        bs_height |= 1;  /* make sure it's odd */
        bs_width = bs_height / 2 + 1;
        position = lower + (upper - lower) *  m_lastPos.y() / allocation.height() ;
    }
    if ((bs_width > 0) && (bs_height > 0)){
        double increment;
        if (m_direction==Qt::Horizontal){
            increment = (double) width / (upper - lower);
            x = qRound ((position - lower) * increment) + bs_width / 2 - 1;
            y = (height + bs_height) / 2 ;
            painter->drawLine(m_lastPos.x(),0, m_lastPos.x() , height);
        }else{
            increment = (double) height / (upper - lower);
            x = (width + bs_width) / 2 ;
            y = qRound ((position - lower) * increment) + (bs_height) / 2 - 1;
            painter->drawLine(0 , m_lastPos.y() , width , m_lastPos.y());
        }
    }
}

QtCornerBox::QtCornerBox(QWidget *parent)
    :QWidget(parent)
{
}

void QtCornerBox::paintEvent(QPaintEvent *e)
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



DrawView::DrawView(QGraphicsScene *scene)
    :QGraphicsView(scene)
{
    m_hruler = new QtRuleBar(Qt::Horizontal,this,this);
    m_vruler = new QtRuleBar(Qt::Vertical,this,this);
    box = new QtCornerBox(this);
    setViewport(new QWidget);
    setAttribute(Qt::WA_DeleteOnClose);
    isUntitled = true;

    modified = false;
}

void DrawView::zoomIn()
{
    scale(1.2,1.2);
    updateRuler();
}

void DrawView::zoomOut()
{
    scale(1 / 1.2, 1 / 1.2);
    updateRuler();
}

void DrawView::newFile()
{
    static int sequenceNumber = 1;

    isUntitled = true;
    curFile = tr("drawing%1.xml").arg(sequenceNumber++);
    setWindowTitle(curFile + "[*]");
}

bool DrawView::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Qt Drawing"),
                             tr("Cannot read file %1:\n%2.")
                                 .arg(fileName)
                                 .arg(file.errorString()));
        return false;
    }

    QXmlStreamReader xml(&file);
    if (xml.readNextStartElement()) {
        if ( xml.name() == tr("canvas"))
        {
            int width = xml.attributes().value(tr("width")).toInt();
            int height = xml.attributes().value(tr("height")).toInt();
            scene()->setSceneRect(0,0,width,height);
            loadCanvas(&xml);
        }
    }

    setCurrentFile(fileName);
    qDebug()<<xml.errorString();
    return !xml.error();
}

bool DrawView::save()
{
    if (isUntitled) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool DrawView::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    curFile);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);

}

bool DrawView::saveFile(const QString &fileName)
{

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Qt Drawing"),
                             tr("Cannot write file %1:\n%2.")
                                 .arg(fileName)
                                 .arg(file.errorString()));
        return false;
    }

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeDTD("<!DOCTYPE qdraw>");
    xml.writeStartElement("canvas");
    xml.writeAttribute("width",QString("%1").arg(scene()->width()));
    xml.writeAttribute("height",QString("%1").arg(scene()->height()));

    foreach (QGraphicsItem *item , scene()->items()) {
        QExtGraphicsAbstractShapeItem * ab = qgraphicsitem_cast<QExtGraphicsAbstractShapeItem*>(item);
        QGraphicsItemGroup *g = dynamic_cast<QGraphicsItemGroup*>(item->parentItem());
        if ( ab &&!qgraphicsitem_cast<QExtGraphicsSizeHandle *>(ab) && !g ){
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
    setCurrentFile(fileName);
    return true;
}

QString DrawView::userFriendlyCurrentFile()
{
    return strippedName(curFile);
}

void DrawView::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void DrawView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pt =mapToScene(event->pos());
    m_hruler->updatePosition(event->pos());
    m_vruler->updatePosition(event->pos());
    emit positionChanged( pt.x() , pt.y() );
    QGraphicsView::mouseMoveEvent(event);
}

void DrawView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);

    this->setViewportMargins(RULER_SIZE-1,RULER_SIZE-1,0,0);
    m_hruler->resize(this->size().width()- RULER_SIZE - 1,RULER_SIZE);
    m_hruler->move(RULER_SIZE,0);
    m_vruler->resize(RULER_SIZE,this->size().height() - RULER_SIZE - 1);
    m_vruler->move(0,RULER_SIZE);

    box->resize(RULER_SIZE,RULER_SIZE);
    box->move(0,0);
    updateRuler();
}

void DrawView::scrollContentsBy(int dx, int dy)
{
    QGraphicsView::scrollContentsBy(dx,dy);
    updateRuler();
}

void DrawView::updateRuler()
{
    if ( scene() == 0) return;
    QRectF viewbox = this->rect();
    QPointF offset = mapFromScene(scene()->sceneRect().topLeft());
    double factor =  1./transform().m11();
    double lower_x = factor * ( viewbox.left()  - offset.x() );
    double upper_x = factor * ( viewbox.right() -RULER_SIZE- offset.x()  );
    m_hruler->setRange(lower_x,upper_x,upper_x - lower_x );
    m_hruler->update();

    double lower_y = factor * ( viewbox.top() - offset.y()) *-1;
    double upper_y = factor * ( viewbox.bottom() - RULER_SIZE - offset.y()) *-1;

    m_vruler->setRange(lower_y,upper_y,upper_y - lower_y);
    m_vruler->update();

    //    qDebug()<<viewbox<<QPoint(lower_x,upper_x) << QPoint(lower_y,upper_y) << offset;
}

bool DrawView::maybeSave()
{
    if (isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("MDI"),
                                   tr("'%1' has been modified.\n"
                                      "Do you want to save your changes?")
                                       .arg(userFriendlyCurrentFile()),
                                   QMessageBox::Save | QMessageBox::Discard
                                       | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void DrawView::setCurrentFile(const QString &fileName)
{
    curFile = QFileInfo(fileName).canonicalFilePath();
    isUntitled = false;
    setModified(false);
    setWindowModified(false);
    setWindowTitle(userFriendlyCurrentFile() + "[*]");
}

QString DrawView::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();

}

void DrawView::loadCanvas( QXmlStreamReader *xml)
{
    Q_ASSERT(xml->isStartElement() && xml->name() == "canvas");

    while (xml->readNextStartElement()) {
        QExtGraphicsAbstractShapeItem * item = NULL;
        if (xml->name() == tr("rect")){
            item = new QExtGraphicsRectItem(QRect(0,0,1,1));
        }else if (xml->name() == tr("roundrect")){
            item = new QExtGraphicsRectItem(QRect(0,0,1,1),true);
        }else if (xml->name() == tr("ellipse"))
            item = new QExtGraphicsEllipseItem(QRect(0,0,1,1));
        else if (xml->name()==tr("polygon"))
            item = new QExtGraphicsPolygonItem();
        else if ( xml->name()==tr("bezier"))
            item = new QExtGraphicsBezierItem();
        else if ( xml->name() == tr("polyline"))
            item = new QExtGraphicsBezierItem(false);
        else if ( xml->name() == tr("line"))
            item = new QExtGraphicsLineItem();
        else if ( xml->name() == tr("group"))
            item =qgraphicsitem_cast<QExtGraphicsAbstractShapeItem*>(loadGroupFromXML(xml));
        else
            xml->skipCurrentElement();

        if (item && item->loadFromXml(xml))
            scene()->addItem(item);
        else if ( item )
            delete item;
    }
}

QExtGraphicsItemGroup *DrawView::loadGroupFromXML(QXmlStreamReader *xml)
{
    QList<QGraphicsItem*> items;
    qreal angle = xml->attributes().value(tr("rotate")).toDouble();
    while (xml->readNextStartElement()) {
        QExtGraphicsAbstractShapeItem * item = NULL;
        if (xml->name() == tr("rect")){
            item = new QExtGraphicsRectItem(QRect(0,0,1,1));
        }else if (xml->name() == tr("roundrect")){
            item = new QExtGraphicsRectItem(QRect(0,0,1,1),true);
        }else if (xml->name() == tr("ellipse"))
            item = new QExtGraphicsEllipseItem(QRect(0,0,1,1));
        else if (xml->name()==tr("polygon"))
            item = new QExtGraphicsPolygonItem();
        else if ( xml->name()==tr("bezier"))
            item = new QExtGraphicsBezierItem();
        else if ( xml->name() == tr("polyline"))
            item = new QExtGraphicsBezierItem(false);
        else if ( xml->name() == tr("line"))
            item = new QExtGraphicsLineItem();
        else if ( xml->name() == tr("group"))
            item =qgraphicsitem_cast<QExtGraphicsAbstractShapeItem*>(loadGroupFromXML(xml));
        else
            xml->skipCurrentElement();
        if (item && item->loadFromXml(xml)){
            scene()->addItem(item);
            items.append(item);
        }else if ( item )
            delete item;
    }

    if ( items.count() > 0 ){
        QExtGraphicsScene * s = dynamic_cast<QExtGraphicsScene*>(scene());
        QExtGraphicsItemGroup * group = s->createGroup(items,false);
        if (group){
            group->setRotation(angle);
            group->updateCoordinate();
            //qDebug()<<"angle:" <<angle;
        }
        return group;
    }
    return 0;
}

