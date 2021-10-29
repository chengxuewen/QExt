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

    QRectF childrenRect();

    bool clip() const;
    void setClip(bool clip);

    qreal baselineOffset() const;
    void setBaselineOffset(qreal offset);

    //    QEXTGuiListProperty<QGraphicsTransform> transform();

    qreal width() const;
    void setWidth(qreal width);
    void resetWidth();
    qreal implicitWidth() const;

    qreal height() const;
    void setHeight(qreal height);
    void resetHeight();
    qreal implicitHeight() const;

    void setSize(const QSizeF &size);

    TransformOrigin transformOrigin() const;
    void setTransformOrigin(TransformOrigin origin);

    bool smooth() const;
    void setSmooth(bool smooth);

    bool hasActiveFocus() const;
    bool hasFocus() const;
    void setFocus(bool focus);

    bool keepMouseGrab() const;
    void setKeepMouseGrab(bool keep);

    void forceActiveFocus();
    QEXTGuiGVItem *childAt(qreal x, qreal y) const;

    QRectF boundingRect() const QEXT_DECL_OVERRIDE;

    virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

    //    QScriptValue mapFromItem(const QScriptValue &item, qreal x, qreal y) const;
    //    QScriptValue mapToItem(const QScriptValue &item, qreal x, qreal y) const;

    static QEXTGuiGVItemPrivate *getPrivate(QEXTGuiGVItem *item);

Q_SIGNALS:
    void childrenRectChanged(const QRectF &);
    void baselineOffsetChanged(qreal);
    void stateChanged(const QString &);
    void focusChanged(bool);
    void activeFocusChanged(bool);
    void parentChanged(QEXTGuiGVItem *);
    void transformOriginChanged(TransformOrigin);
    void smoothChanged(bool);
    void clipChanged(bool);

    void implicitWidthChanged();
    void implicitHeightChanged();

protected:
    QEXTGuiGVItem(QEXTGuiGVItemPrivate *d, QEXTGuiGVItem *parent = QEXT_DECL_NULLPTR);

    bool isComponentComplete() const;
    void setImplicitWidth(qreal width);
    bool widthValid() const; // ### better name?
    void setImplicitHeight(qreal height);
    bool heightValid() const; // ### better name?

    void keyPressPreHandler(QKeyEvent *event);
    void keyReleasePreHandler(QKeyEvent *event);
    void inputMethodPreHandler(QInputMethodEvent *event);

    bool sceneEvent(QEvent *) QEXT_DECL_OVERRIDE;
    bool event(QEvent *event) QEXT_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) QEXT_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) QEXT_DECL_OVERRIDE;
    void inputMethodEvent(QInputMethodEvent *) QEXT_DECL_OVERRIDE;
    QVariant inputMethodQuery(Qt::InputMethodQuery query) const QEXT_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) QEXT_DECL_OVERRIDE;

    virtual void classBegin();
    virtual void componentComplete();
    virtual void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

    QScopedPointer<QEXTGuiGVItemPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QEXTGuiGVItem)
    Q_DECLARE_PRIVATE(QEXTGuiGVItem)
};

#endif // _QEXTGUIGVITEM_H
