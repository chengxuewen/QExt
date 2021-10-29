#include <qextGuiAnchors.h>
#include <qextGuiAnchors_p.h>


QEXTGuiAnchorsPrivate::QEXTGuiAnchorsPrivate(QEXTGuiAnchors *q)
    : q_ptr(q)
    , m_componentComplete(true)
    , m_updatingMe(false)
    , m_updatingHorizontalAnchor(0)
    , m_updatingVerticalAnchor(0)
    , m_updatingFill(0)
    , m_updatingCenterIn(0)
    , m_item(QEXT_DECL_NULLPTR)
    , m_usedAnchors(0)
    , m_fill(QEXT_DECL_NULLPTR)
    , m_centerIn(QEXT_DECL_NULLPTR)
    , m_leftMargin(0)
    , m_rightMargin(0)
    , m_topMargin(0)
    , m_bottomMargin(0)
    , m_margins(0)
    , m_vCenterOffset(0)
    , m_hCenterOffset(0)
    , m_baselineOffset(0)
{

}

QEXTGuiAnchorsPrivate::~QEXTGuiAnchorsPrivate()
{

}

void QEXTGuiAnchorsPrivate::clearItem(QGraphicsObject *)
{

}

void QEXTGuiAnchorsPrivate::addDepend(QGraphicsObject *)
{

}

void QEXTGuiAnchorsPrivate::remDepend(QGraphicsObject *)
{

}

bool QEXTGuiAnchorsPrivate::isItemComplete() const
{

}

void QEXTGuiAnchorsPrivate::setItemHeight(qreal)
{

}

void QEXTGuiAnchorsPrivate::setItemWidth(qreal)
{

}

void QEXTGuiAnchorsPrivate::setItemX(qreal)
{

}

void QEXTGuiAnchorsPrivate::setItemY(qreal)
{

}

void QEXTGuiAnchorsPrivate::setItemPos(const QPointF &)
{

}

void QEXTGuiAnchorsPrivate::setItemSize(const QSizeF &)
{

}

void QEXTGuiAnchorsPrivate::updateOnComplete()
{

}

void QEXTGuiAnchorsPrivate::updateMe()
{

}

void QEXTGuiAnchorsPrivate::itemGeometryChanged(QEXTGuiGVItem *, const QRectF &, const QRectF &)
{

}

void QEXTGuiAnchorsPrivate::widgetDestroyed(QObject *)
{

}

void QEXTGuiAnchorsPrivate::widgetGeometryChanged()
{

}

bool QEXTGuiAnchorsPrivate::checkHValid() const
{

}

bool QEXTGuiAnchorsPrivate::checkVValid() const
{

}

bool QEXTGuiAnchorsPrivate::checkHAnchorValid(QEXTGuiAnchorLine anchor) const
{

}

bool QEXTGuiAnchorsPrivate::checkVAnchorValid(QEXTGuiAnchorLine anchor) const
{

}

bool QEXTGuiAnchorsPrivate::calcStretch(const QEXTGuiAnchorLine &edge1, const QEXTGuiAnchorLine &edge2,
                                        qreal offset1, qreal offset2, QEXTGuiAnchorLine::AnchorLineType line, qreal &stretch)
{

}

bool QEXTGuiAnchorsPrivate::isMirrored() const
{

}

void QEXTGuiAnchorsPrivate::updateHorizontalAnchors()
{

}

void QEXTGuiAnchorsPrivate::updateVerticalAnchors()
{

}

void QEXTGuiAnchorsPrivate::fillChanged()
{

}

void QEXTGuiAnchorsPrivate::centerInChanged()
{

}



QEXTGuiAnchors::QEXTGuiAnchors(QObject *parent)
    : QObject(parent), d_ptr(new QEXTGuiAnchorsPrivate(this))
{

}

QEXTGuiAnchors::QEXTGuiAnchors(QGraphicsObject *item, QObject *parent)
    : QObject(parent), d_ptr(new QEXTGuiAnchorsPrivate(this))
{

}

QEXTGuiAnchors::~QEXTGuiAnchors()
{

}

QEXTGuiAnchorLine QEXTGuiAnchors::left() const
{

}

void QEXTGuiAnchors::setLeft(const QEXTGuiAnchorLine &edge)
{

}

void QEXTGuiAnchors::resetLeft()
{

}

QEXTGuiAnchorLine QEXTGuiAnchors::right() const
{

}

void QEXTGuiAnchors::setRight(const QEXTGuiAnchorLine &edge)
{

}

void QEXTGuiAnchors::resetRight()
{

}

QEXTGuiAnchorLine QEXTGuiAnchors::horizontalCenter() const
{

}

void QEXTGuiAnchors::setHorizontalCenter(const QEXTGuiAnchorLine &edge)
{

}

void QEXTGuiAnchors::resetHorizontalCenter()
{

}

QEXTGuiAnchorLine QEXTGuiAnchors::top() const
{

}

void QEXTGuiAnchors::setTop(const QEXTGuiAnchorLine &edge)
{

}

void QEXTGuiAnchors::resetTop()
{

}

QEXTGuiAnchorLine QEXTGuiAnchors::bottom() const
{

}

void QEXTGuiAnchors::setBottom(const QEXTGuiAnchorLine &edge)
{

}

void QEXTGuiAnchors::resetBottom()
{

}

QEXTGuiAnchorLine QEXTGuiAnchors::verticalCenter() const
{

}

void QEXTGuiAnchors::setVerticalCenter(const QEXTGuiAnchorLine &edge)
{

}

void QEXTGuiAnchors::resetVerticalCenter()
{

}

QEXTGuiAnchorLine QEXTGuiAnchors::baseline() const
{

}

void QEXTGuiAnchors::setBaseline(const QEXTGuiAnchorLine &edge)
{

}

void QEXTGuiAnchors::resetBaseline()
{

}

qreal QEXTGuiAnchors::leftMargin() const
{

}

void QEXTGuiAnchors::setLeftMargin(qreal)
{

}

qreal QEXTGuiAnchors::rightMargin() const
{

}

void QEXTGuiAnchors::setRightMargin(qreal)
{

}

qreal QEXTGuiAnchors::horizontalCenterOffset() const
{

}

void QEXTGuiAnchors::setHorizontalCenterOffset(qreal)
{

}

qreal QEXTGuiAnchors::topMargin() const
{

}

void QEXTGuiAnchors::setTopMargin(qreal)
{

}

qreal QEXTGuiAnchors::bottomMargin() const
{

}

void QEXTGuiAnchors::setBottomMargin(qreal)
{

}

qreal QEXTGuiAnchors::margins() const
{

}

void QEXTGuiAnchors::setMargins(qreal)
{

}

qreal QEXTGuiAnchors::verticalCenterOffset() const
{

}

void QEXTGuiAnchors::setVerticalCenterOffset(qreal)
{

}

qreal QEXTGuiAnchors::baselineOffset() const
{

}

void QEXTGuiAnchors::setBaselineOffset(qreal)
{

}

QGraphicsObject *QEXTGuiAnchors::fill() const
{

}

void QEXTGuiAnchors::setFill(QGraphicsObject *)
{

}

void QEXTGuiAnchors::resetFill()
{

}

QGraphicsObject *QEXTGuiAnchors::centerIn() const
{

}

void QEXTGuiAnchors::setCenterIn(QGraphicsObject *)
{

}

void QEXTGuiAnchors::resetCenterIn()
{

}

QEXTGuiAnchors::AnchorTypes QEXTGuiAnchors::usedAnchors() const
{

}

void QEXTGuiAnchors::classBegin()
{

}

void QEXTGuiAnchors::componentComplete()
{

}

bool QEXTGuiAnchors::mirrored()
{

}

void QEXTGuiAnchors::onWidgetGeometryChanged()
{

}

void QEXTGuiAnchors::onWidgetDestroyed(QObject *obj)
{

}
