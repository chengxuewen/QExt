#ifndef _QEXTGUIANCHORS_P_H
#define _QEXTGUIANCHORS_P_H

#include <qextGuiGlobal.h>
#include <qextGuiAnchors.h>
#include <qextGuiItemChangeListener.h>

#include <QGraphicsObject>
#include <QObject>
#include <QPointF>
#include <QSizeF>


class QEXTGuiGVItem;
class QEXTGuiAnchors;
class QEXT_GUI_API QEXTGuiAnchorsPrivate : public QDeclarativeItemChangeListener
{
public:
    explicit QEXTGuiAnchorsPrivate(QEXTGuiAnchors *q);
    virtual ~QEXTGuiAnchorsPrivate();

    void clearItem(QGraphicsObject *);

    void addDepend(QGraphicsObject *);
    void remDepend(QGraphicsObject *);
    bool isItemComplete() const;

    void setItemHeight(qreal);
    void setItemWidth(qreal);
    void setItemX(qreal);
    void setItemY(qreal);
    void setItemPos(const QPointF &);
    void setItemSize(const QSizeF &);

    void updateOnComplete();
    void updateMe();

    // QDeclarativeItemGeometryListener interface
    void itemGeometryChanged(QEXTGuiGVItem *, const QRectF &, const QRectF &);

    void widgetDestroyed(QObject *);
    void widgetGeometryChanged();
    QEXTGuiAnchorsPrivate *anchorPrivate() { return this; }

    bool checkHValid() const;
    bool checkVValid() const;
    bool checkHAnchorValid(QEXTGuiAnchorLine anchor) const;
    bool checkVAnchorValid(QEXTGuiAnchorLine anchor) const;
    bool calcStretch(const QEXTGuiAnchorLine &edge1, const QEXTGuiAnchorLine &edge2,
                     qreal offset1, qreal offset2, QEXTGuiAnchorLine::AnchorLineType line, qreal &stretch);

    bool isMirrored() const;
    void updateHorizontalAnchors();
    void updateVerticalAnchors();
    void fillChanged();
    void centerInChanged();

    QEXTGuiAnchors * const q_ptr;

    bool m_componentComplete:1;
    bool m_updatingMe:1;
    uint m_updatingHorizontalAnchor:2;
    uint m_updatingVerticalAnchor:2;
    uint m_updatingFill:2;
    uint m_updatingCenterIn:2;

    QGraphicsObject *m_item;
    QEXTGuiAnchors::AnchorTypes m_usedAnchors;

    QGraphicsObject *m_fill;
    QGraphicsObject *m_centerIn;

    QEXTGuiAnchorLine m_left;
    QEXTGuiAnchorLine m_right;
    QEXTGuiAnchorLine m_top;
    QEXTGuiAnchorLine m_bottom;
    QEXTGuiAnchorLine m_vCenter;
    QEXTGuiAnchorLine m_hCenter;
    QEXTGuiAnchorLine m_baseline;

    qreal m_leftMargin;
    qreal m_rightMargin;
    qreal m_topMargin;
    qreal m_bottomMargin;
    qreal m_margins;
    qreal m_vCenterOffset;
    qreal m_hCenterOffset;
    qreal m_baselineOffset;

private:
    Q_DISABLE_COPY(QEXTGuiAnchorsPrivate)
    Q_DECLARE_PUBLIC(QEXTGuiAnchors)
};

#endif // _QEXTGUIANCHORS_P_H
