#ifndef _QEXTGUIGVITEM_H
#define _QEXTGUIGVITEM_H

#include <qextGuiGlobal.h>

#include <QGraphicsObject>

class QEXTGuiGVItemPrivate;
class QEXT_GUI_API QEXTGuiGVItem : public QGraphicsObject
{
    Q_OBJECT
public:
    enum TransformOrigin
    {
        TopLeft,
        Top,
        TopRight,
        Left,
        Center,
        Right,
        BottomLeft,
        Bottom,
        BottomRight
    };

    explicit QEXTGuiGVItem(QEXTGuiGVItem *parent = QEXT_DECL_NULLPTR);
    ~QEXTGuiGVItem();

    QEXTGuiGVItem *parentItem() const;
    void setParentItem(QEXTGuiGVItem *parent);

//    QRectF childrenRect();

//    bool clip() const;
//    void setClip(bool);

//    qreal baselineOffset() const;
//    void setBaselineOffset(qreal);

////    QDeclarativeListProperty<QGraphicsTransform> transform();

//    qreal width() const;
//    void setWidth(qreal);
//    void resetWidth();
//    qreal implicitWidth() const;

//    qreal height() const;
//    void setHeight(qreal);
//    void resetHeight();
//    qreal implicitHeight() const;

//    void setSize(const QSizeF &size);

//    TransformOrigin transformOrigin() const;
//    void setTransformOrigin(TransformOrigin);

//    bool smooth() const;
//    void setSmooth(bool);

//    bool hasActiveFocus() const;
//    bool hasFocus() const;
//    void setFocus(bool);

//    bool keepMouseGrab() const;
//    void setKeepMouseGrab(bool);

//    QRectF boundingRect() const;
//    virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

protected:
    QScopedPointer<QEXTGuiGVItemPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QEXTGuiGVItem)
    Q_DECLARE_PRIVATE(QEXTGuiGVItem)
};

#endif // _QEXTGUIGVITEM_H
