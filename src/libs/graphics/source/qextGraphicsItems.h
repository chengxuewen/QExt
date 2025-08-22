#ifndef _QEXTGRAPHICSITEMS_H
#define _QEXTGRAPHICSITEMS_H

#include <qextGraphicsHandles.h>

#include <QList>
#include <QCursor>
#include <QObject>
#include <QVector>
#include <QMimeData>
#include <QXmlStreamReader>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include <vector>

class QEXT_GRAPHICS_API QExtGraphicsShapeMimeData : public QMimeData
{
    Q_OBJECT
public:
    QExtGraphicsShapeMimeData(QList<QGraphicsItem *> items);
    ~QExtGraphicsShapeMimeData() QEXT_OVERRIDE;

    QList<QGraphicsItem *> items() const;

protected:
    QList<QGraphicsItem *> m_items;
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtGraphicsShapeMimeData)
};

template <typename BaseType = QGraphicsItem>
class QExtGraphicsAbstractShape : public BaseType
{
public:
    typedef std::vector<QExtGraphicsSizeHandle *> Handles;

    explicit QExtGraphicsAbstractShape(QGraphicsItem *parent = QEXT_NULLPTR)
        : BaseType(parent)
    {
        m_pen = QPen(Qt::NoPen);
        m_brush = QBrush(QColor(rand() % 32 * 8, rand() % 32 * 8, rand() % 32 * 8));
        m_width = m_height = 0;
    }
    virtual ~QExtGraphicsAbstractShape() {}

    virtual QString displayName () const { return QString("AbstractType"); }

    virtual void control(int dir, const QPointF &delta) { Q_UNUSED(dir); Q_UNUSED(delta); }
    virtual void stretch(int, double, double, const QPointF &) {}
    virtual QRectF rect() const { return m_localRect; }
    virtual void updateCoordinate() {}
    virtual void move(const QPointF &point) { Q_UNUSED(point); }
    virtual QGraphicsItem *duplicate() const { return QEXT_NULLPTR; }
    virtual int handleCount() const { return m_handles.size(); }

    virtual bool loadFromXml(QXmlStreamReader *xml) = 0;
    virtual bool saveToXml(QXmlStreamWriter *xml) = 0;

    int collidesWithHandle(const QPointF &point) const
    {
        const Handles::const_reverse_iterator hend =  m_handles.rend();
        for (Handles::const_reverse_iterator it = m_handles.rbegin(); it != hend; ++it)
        {
            QPointF pt = (*it)->mapFromScene(point);
            if ((*it)->contains(pt))
            {
                return (*it)->dir();
            }
        }
        return QExtGraphicsSizeHandle::Handle_None;
    }
    virtual QPointF handlePos(int handle) const
    {
        const Handles::const_reverse_iterator hend =  m_handles.rend();
        for (Handles::const_reverse_iterator it = m_handles.rbegin(); it != hend; ++it)
        {
            if ((*it)->dir() == handle)
            {
                return (*it)->pos();
            }
        }
        return QPointF();
    }
    int swapHandle(int handle, const QPointF &scale) const
    {
        int dir = QExtGraphicsSizeHandle::Handle_None;
        if (scale.x() < 0 || scale.y() < 0)
        {
            switch (handle)
            {
            case QExtGraphicsSizeHandle::Handle_RightTop:
            {
                if (scale.x() < 0 && scale.y() < 0)
                {
                    dir = QExtGraphicsSizeHandle::Handle_LeftBottom;
                }
                else if (scale.x() > 0 && scale.y() < 0)
                {
                    dir = QExtGraphicsSizeHandle::Handle_RightBottom;
                }
                else
                {
                    dir = QExtGraphicsSizeHandle::Handle_LeftTop;
                }
                break;
            }
            case QExtGraphicsSizeHandle::Handle_RightBottom:
            {
                if (scale.x() < 0 && scale.y() < 0)
                {
                    dir = QExtGraphicsSizeHandle::Handle_LeftTop;
                }
                else if (scale.x() > 0 && scale.y() < 0)
                {
                    dir = QExtGraphicsSizeHandle::Handle_RightTop;
                }
                else
                {
                    dir = QExtGraphicsSizeHandle::Handle_LeftBottom;
                }
                break;
            }
            case QExtGraphicsSizeHandle::Handle_LeftBottom:
            {
                if (scale.x() < 0 && scale.y() < 0)
                {
                    dir = QExtGraphicsSizeHandle::Handle_RightTop;
                }
                else if (scale.x() > 0 && scale.y() < 0)
                {
                    dir = QExtGraphicsSizeHandle::Handle_LeftTop;
                }
                else
                {
                    dir = QExtGraphicsSizeHandle::Handle_RightBottom;
                }
                break;
            }
            case QExtGraphicsSizeHandle::Handle_LeftTop:
            {
                if (scale.x() < 0 && scale.y() < 0)
                {
                    dir = QExtGraphicsSizeHandle::Handle_RightBottom;
                }
                else if (scale.x() > 0 && scale.y() < 0)
                {
                    dir = QExtGraphicsSizeHandle::Handle_LeftBottom;
                }
                else
                {
                    dir = QExtGraphicsSizeHandle::Handle_RightTop;
                }
                break;
            }
            case QExtGraphicsSizeHandle::Handle_Right:
            {
                if (scale.x() < 0)
                {
                    dir = QExtGraphicsSizeHandle::Handle_Left;
                }
                break;
            }
            case QExtGraphicsSizeHandle::Handle_Left:
            {
                if (scale.x() < 0)
                {
                    dir = QExtGraphicsSizeHandle::Handle_Right;
                }
                break;
            }
            case QExtGraphicsSizeHandle::Handle_Top:
            {
                if (scale.y() < 0)
                {
                    dir = QExtGraphicsSizeHandle::Handle_Bottom;
                }
                break;
            }
            case QExtGraphicsSizeHandle::Handle_Bottom:
            {
                if (scale.y() < 0)
                {
                    dir = QExtGraphicsSizeHandle::Handle_Top;
                }
                break;
            }
            }
        }
        return dir;
    }
    virtual QPointF opposite(int handle)
    {
        QPointF pt;
        switch (handle)
        {
        case QExtGraphicsSizeHandle::Handle_Right:
        {
            pt = m_handles.at(QExtGraphicsSizeHandle::Handle_Left - 1)->pos();
            break;
        }
        case QExtGraphicsSizeHandle::Handle_RightTop:
        {
            pt = m_handles[QExtGraphicsSizeHandle::Handle_LeftBottom - 1]->pos();
            break;
        }
        case QExtGraphicsSizeHandle::Handle_RightBottom:
        {
            pt = m_handles[QExtGraphicsSizeHandle::Handle_LeftTop - 1]->pos();
            break;
        }
        case QExtGraphicsSizeHandle::Handle_LeftBottom:
        {
            pt = m_handles[QExtGraphicsSizeHandle::Handle_RightTop - 1]->pos();
            break;
        }
        case QExtGraphicsSizeHandle::Handle_Bottom:
        {
            pt = m_handles[QExtGraphicsSizeHandle::Handle_Top - 1]->pos();
            break;
        }
        case QExtGraphicsSizeHandle::Handle_LeftTop:
        {
            pt = m_handles[QExtGraphicsSizeHandle::Handle_RightBottom - 1]->pos();
            break;
        }
        case QExtGraphicsSizeHandle::Handle_Left:
        {
            pt = m_handles[QExtGraphicsSizeHandle::Handle_Right - 1]->pos();
            break;
        }
        case QExtGraphicsSizeHandle::Handle_Top:
        {
            pt = m_handles[QExtGraphicsSizeHandle::Handle_Bottom - 1]->pos();
            break;
        }
        }
        return pt;
    }

    QBrush brush() const { return m_brush; }
    QColor brushColor() const { return m_brush.color(); }
    void setBrush(const QBrush &brush)
    {
        m_brush = brush;
        emit this->onBrushColorChanged(brush.color());
    }
    void setBrushColor(const QColor &color)
    {
        if (color != m_brush.color())
        {
            m_brush.setColor(color);
            emit this->onBrushColorChanged(color);
        }
    }

    QPen pen() const { return m_pen; }
    QColor penColor() const { return m_pen.color(); }
    void setPen(const QPen &pen)
    {
        m_pen = pen;
        emit this->onPenColorChanged(pen.color());
    }
    void setPenColor(const QColor &color)
    {
        if (color != m_pen.color())
        {
            m_pen.setColor(color);
            emit this->onPenColorChanged(color);
        }
    }

    qreal width() const { return m_width; }
    void setWidth(qreal width)
    {
        if (width != m_width)
        {
            m_width = width;
            this->updateCoordinate();
            this->onWidthChanged(width);
        }
    }

    qreal height() const { return m_height; }
    void setHeight(qreal height)
    {
        if (height != m_height)
        {
            m_height = height;
            this->updateCoordinate();
            this->onHeightChanged(height);
        }
    }

protected:
    virtual void onPenColorChanged(const QColor &color) {}
    virtual void onBrushColorChanged(const QColor &color) {}

    virtual void onWidthChanged(qreal width) {}
    virtual void onHeightChanged(qreal height) {}
    virtual void onPositionChanged(const QPointF &position) {}

    virtual void updatehandles() {}

    void setState(SelectionHandleState st)
    {
        const Handles::iterator hend = m_handles.end();
        for (Handles::iterator it = m_handles.begin(); it != hend; ++it)
        {
            (*it)->setState(st);
        }
    }

    QPen m_pen;
    QBrush m_brush;
    qreal m_width;
    qreal m_height;
    Handles m_handles;
    QRectF m_localRect;
};
typedef QExtGraphicsAbstractShape<QGraphicsItem> QExtGraphicsAbstractShapeItem;

class QEXT_GRAPHICS_API QExtGraphicsItem : public QObject, public QExtGraphicsAbstractShape<QGraphicsItem>
{
    Q_OBJECT
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor NOTIFY penColorChanged)
    Q_PROPERTY(QColor brushColor READ brushColor WRITE setBrushColor NOTIFY brushColorChanged)

    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(QPointF position READ pos WRITE setPos NOTIFY positionChanged)

public:
    enum { Type = UserType + 1 };

    explicit QExtGraphicsItem(QGraphicsItem *parent);

    int type() const QEXT_OVERRIDE { return Type; }

    virtual QPixmap image();

signals:
    void penColorChanged(const QColor &color);
    void brushColorChanged(const QColor &color);

    void widthChanged(qreal width);
    void heightChanged(qreal height);
    void positionChanged(const QPointF &position);

    void selectedChange(QGraphicsItem *item);

protected:
    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) QEXT_OVERRIDE;

    void onPenColorChanged(const QColor &color) QEXT_OVERRIDE { emit this->penColorChanged(color); }
    void onBrushColorChanged(const QColor &color) QEXT_OVERRIDE { emit this->brushColorChanged(color); }

    void onWidthChanged(qreal width) QEXT_OVERRIDE { emit this->widthChanged(width); }
    void onHeightChanged(qreal height) QEXT_OVERRIDE { emit this->heightChanged(height); }
    void onPositionChanged(const QPointF &position) QEXT_OVERRIDE { emit this->positionChanged(position); }

    void updatehandles() QEXT_OVERRIDE;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) QEXT_OVERRIDE;

    bool readBaseAttributes(QXmlStreamReader *xml);
    bool writeBaseAttributes( QXmlStreamWriter *xml);
};

class QEXT_GRAPHICS_API QExtGraphicsRectItem : public QExtGraphicsItem
{
    Q_OBJECT
public:
    QExtGraphicsRectItem(const QRect &rect, bool isRound = false, QGraphicsItem *parent = QEXT_NULLPTR);

    void move(const QPointF &point) QEXT_OVERRIDE;
    void control(int dir, const QPointF &delta) QEXT_OVERRIDE;
    void stretch(int handle, double sx , double sy, const QPointF &origin) QEXT_OVERRIDE;
    void updateCoordinate() QEXT_OVERRIDE;

    QPainterPath shape() const QEXT_OVERRIDE;
    QRectF boundingRect() const QEXT_OVERRIDE;
    QGraphicsItem *duplicate() const QEXT_OVERRIDE;
    QRectF rect() const QEXT_OVERRIDE { return m_localRect; }
    QString displayName() const QEXT_OVERRIDE { return tr("rectangle"); }

    bool loadFromXml(QXmlStreamReader *xml) QEXT_OVERRIDE;
    bool saveToXml( QXmlStreamWriter *xml) QEXT_OVERRIDE;

protected:
    void updatehandles() QEXT_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) QEXT_OVERRIDE;

    bool m_isRound;
    qreal m_fRatioX;
    qreal m_fRatioY;
    QPointF m_opposite;
    QRectF m_initialRect;
    QPointF m_originPoint;
};

class QEXT_GRAPHICS_API QExtGraphicsEllipseItem :public QExtGraphicsRectItem
{
    Q_OBJECT
public:
    QExtGraphicsEllipseItem(const QRect & rect , QGraphicsItem * parent = 0);

    void control(int dir, const QPointF &delta) QEXT_OVERRIDE;

    QPainterPath shape() const QEXT_OVERRIDE;
    QRectF boundingRect() const QEXT_OVERRIDE;
    QGraphicsItem *duplicate() const QEXT_OVERRIDE;
    QString displayName() const QEXT_OVERRIDE { return tr("ellipse"); }

    bool loadFromXml(QXmlStreamReader *xml) QEXT_OVERRIDE;
    bool saveToXml(QXmlStreamWriter *xml) QEXT_OVERRIDE;

protected:
    void updatehandles() QEXT_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) QEXT_OVERRIDE;

    int m_spanAngle;
    int m_startAngle;
};

class QEXT_GRAPHICS_API QExtGraphicsItemGroup : public QObject, public QExtGraphicsAbstractShape<QGraphicsItemGroup>
{
    Q_OBJECT
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor NOTIFY penColorChanged)
    Q_PROPERTY(QColor brushColor READ brushColor WRITE setBrushColor NOTIFY brushColorChanged)

    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(QPointF position READ pos WRITE setPos NOTIFY positionChanged)

public:
    enum { Type = UserType + 2 };

    explicit QExtGraphicsItemGroup(QGraphicsItem *parent = QEXT_NULLPTR);

    QRectF boundingRect() const QEXT_OVERRIDE;
    ~QExtGraphicsItemGroup() QEXT_OVERRIDE;

    int type() const QEXT_OVERRIDE { return Type; }

    QGraphicsItem *duplicate () const QEXT_OVERRIDE;
    QString displayName() const QEXT_OVERRIDE { return tr("group"); }

    void control(int dir, const QPointF &delta) QEXT_OVERRIDE;
    void stretch(int handle, double sx, double sy, const QPointF &origin) QEXT_OVERRIDE;
    void updateCoordinate() QEXT_OVERRIDE;

    bool loadFromXml(QXmlStreamReader *xml) QEXT_OVERRIDE;
    bool saveToXml(QXmlStreamWriter *xml) QEXT_OVERRIDE;

signals:
    void penColorChanged(const QColor &color);
    void brushColorChanged(const QColor &color);

    void widthChanged(qreal width);
    void heightChanged(qreal height);
    void positionChanged(const QPointF &position);

    void selectedChange(QGraphicsItem *item);

protected:
    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) QEXT_OVERRIDE;

    void onPenColorChanged(const QColor &color) QEXT_OVERRIDE { emit this->penColorChanged(color); }
    void onBrushColorChanged(const QColor &color) QEXT_OVERRIDE { emit this->brushColorChanged(color); }

    void onWidthChanged(qreal width) QEXT_OVERRIDE { emit this->widthChanged(width); }
    void onHeightChanged(qreal height) QEXT_OVERRIDE { emit this->heightChanged(height); }
    void onPositionChanged(const QPointF &position) QEXT_OVERRIDE { emit this->positionChanged(position); }

    void updatehandles() QEXT_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = QEXT_NULLPTR) QEXT_OVERRIDE;

    QList<QGraphicsItem *> duplicateItems() const;
    QExtGraphicsItemGroup *createGroup(const QList<QGraphicsItem *> &items) const;

    QRectF m_initialRect;
    QGraphicsItem *m_parent;
    QRectF m_itemsBoundingRect;
};

class QEXT_GRAPHICS_API QExtGraphicsPolygonItem : public QExtGraphicsItem
{
    Q_OBJECT
public:
    QExtGraphicsPolygonItem(QGraphicsItem *parent = QEXT_NULLPTR);

    QPainterPath shape() const QEXT_OVERRIDE;
    QRectF boundingRect() const QEXT_OVERRIDE;
    QGraphicsItem *duplicate() const QEXT_OVERRIDE;
    QString displayName() const QEXT_OVERRIDE { return tr("polygon"); }

    void control(int dir, const QPointF &delta) QEXT_OVERRIDE;
    void stretch(int handle, double sx, double sy, const QPointF &origin) QEXT_OVERRIDE;
    void updateCoordinate() QEXT_OVERRIDE;

    bool loadFromXml(QXmlStreamReader *xml) QEXT_OVERRIDE;
    bool saveToXml(QXmlStreamWriter *xml) QEXT_OVERRIDE;

    virtual void addPoint(const QPointF &point);
    virtual void endPoint(const QPointF &point);


protected:
    void updatehandles() QEXT_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) QEXT_OVERRIDE;

    QPolygonF m_points;
    QPolygonF m_initialPoints;
};

class QEXT_GRAPHICS_API QExtGraphicsLineItem : public QExtGraphicsPolygonItem
{
    Q_OBJECT
public:
    QExtGraphicsLineItem(QGraphicsItem *parent = QEXT_NULLPTR);

    QPainterPath shape() const QEXT_OVERRIDE;
    QGraphicsItem *duplicate() const QEXT_OVERRIDE;
    QString displayName() const QEXT_OVERRIDE { return tr("line"); }

    void addPoint(const QPointF &point) QEXT_OVERRIDE;
    void endPoint(const QPointF &point) QEXT_OVERRIDE;

    void updateCoordinate() QEXT_OVERRIDE { m_initialPoints = m_points; }
    int handleCount() const QEXT_OVERRIDE { return m_handles.size() + QExtGraphicsSizeHandle::Handle_Left; }
    void stretch(int handle, double sx, double sy, const QPointF &origin) QEXT_OVERRIDE;

    QPointF opposite(int handle) QEXT_OVERRIDE;
    bool loadFromXml(QXmlStreamReader *xml) QEXT_OVERRIDE;
    bool saveToXml(QXmlStreamWriter *xml) QEXT_OVERRIDE;

protected:
    void updatehandles() QEXT_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) QEXT_OVERRIDE;
};

class QEXT_GRAPHICS_API QExtGraphicsBezierItem : public QExtGraphicsPolygonItem
{
    Q_OBJECT
public:
    QExtGraphicsBezierItem(bool bbezier = true, QGraphicsItem *parent = QEXT_NULLPTR);

    QPainterPath shape() const QEXT_OVERRIDE;
    QGraphicsItem *duplicate() const QEXT_OVERRIDE;
    QString displayName() const QEXT_OVERRIDE{ return tr("bezier"); }

    bool loadFromXml(QXmlStreamReader *xml) QEXT_OVERRIDE;
    bool saveToXml(QXmlStreamWriter *xml) QEXT_OVERRIDE;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) QEXT_OVERRIDE;

private:
    bool m_isBezier;
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtGraphicsBezierItem)
};

#endif // _QEXTGRAPHICSITEMS_H
