#include <qextGuiGVItem.h>
#include <qextGuiGVItem_p.h>

#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QGraphicsScene>

QEXTGuiGVItemKeyFilter::QEXTGuiGVItemKeyFilter(QEXTGuiGVItem *item)
    : m_processPost(false)
    , m_next(QEXT_DECL_NULLPTR)
{
    QEXTGuiGVItemPrivate *itemPrivate = item ? QEXTGuiGVItem::getPrivate(item) : QEXT_DECL_NULLPTR;
    if (itemPrivate)
    {
        m_next = itemPrivate->m_keyHandler;
        itemPrivate->m_keyHandler = this;
    }
}

QEXTGuiGVItemKeyFilter::~QEXTGuiGVItemKeyFilter()
{

}

void QEXTGuiGVItemKeyFilter::keyPressed(QKeyEvent *event, bool post)
{
    if (m_next)
    {
        m_next->keyPressed(event, post);
    }
}

void QEXTGuiGVItemKeyFilter::keyReleased(QKeyEvent *event, bool post)
{
    if (m_next)
    {
        m_next->keyReleased(event, post);
    }
}

void QEXTGuiGVItemKeyFilter::inputMethodEvent(QInputMethodEvent *event, bool post)
{
    if (m_next)
    {
        m_next->inputMethodEvent(event, post);
    }
}

QVariant QEXTGuiGVItemKeyFilter::inputMethodQuery(Qt::InputMethodQuery query) const
{
    if (m_next)
    {
        return m_next->inputMethodQuery(query);
    }
    return QVariant();
}

void QEXTGuiGVItemKeyFilter::componentComplete()
{
    if (m_next)
    {
        m_next->componentComplete();
    }
}



QEXTGuiGVItemPrivate::QEXTGuiGVItemPrivate(QEXTGuiGVItem *q)
    : q_ptr(q)
    , m_anchors(QEXT_DECL_NULLPTR)
    , m_contents(QEXT_DECL_NULLPTR)
    , m_baselineOffset(0)
    //    , m_anchorLines(0)
    //    , m_stateGroup(0)
    , m_origin(QEXTGuiGVItem::Center)
    , m_widthValid(false)
    , m_heightValid(false)
    , m_componentComplete(true)
    , m_keepMouse(false)
    , m_smooth(false)
    , m_transformOriginDirty(true)
    , m_doneEventPreHandler(false)
    , m_inheritedLayoutMirror(false)
    , m_effectiveLayoutMirror(false)
    , m_isMirrorImplicit(true)
    , m_inheritMirrorFromParent(false)
    , m_inheritMirrorFromItem(false)
    , m_hadFocus(false)
    , m_hadActiveFocus(false)
    , m_keyHandler(QEXT_DECL_NULLPTR)
    , m_width(0)
    , m_height(0)
    , m_implicitWidth(0)
    , m_implicitHeight(0)
    //    , attachedLayoutDirection(0)
{

}

QEXTGuiGVItemPrivate::~QEXTGuiGVItemPrivate()
{

}

QEXTGuiAnchors *QEXTGuiGVItemPrivate::anchors()
{
    if (!m_anchors)
    {
        Q_Q(QEXTGuiGVItem);
        m_anchors = new QEXTGuiAnchors(q);
        if (!m_componentComplete)
        {
            m_anchors->classBegin();
        }
    }
    return m_anchors;
}

qreal QEXTGuiGVItemPrivate::width() const
{
    return m_width;
}

void QEXTGuiGVItemPrivate::setWidth(qreal width)
{
    Q_Q(QEXTGuiGVItem);
    if (qIsNaN(width))
    {
        return;
    }

    m_widthValid = true;
    if (m_width != width)
    {
        qreal oldWidth = m_width;
        q->prepareGeometryChange();
        m_width = width;
        q->geometryChanged(QRectF(q->x(), q->y(), this->width(), this->height()),
                           QRectF(q->x(), q->y(), oldWidth, this->height()));
    }
}

void QEXTGuiGVItemPrivate::resetWidth()
{
    Q_Q(QEXTGuiGVItem);
    m_widthValid = false;
    q->setImplicitWidth(q->implicitWidth());
}

qreal QEXTGuiGVItemPrivate::height() const
{
    return m_height;
}

void QEXTGuiGVItemPrivate::setHeight(qreal height)
{
    Q_Q(QEXTGuiGVItem);
    if (qIsNaN(height))
    {
        return;
    }

    m_heightValid = true;
    if (m_height != height)
    {
        qreal oldHeight = m_height;
        q->prepareGeometryChange();
        m_height = height;
        q->geometryChanged(QRectF(q->x(), q->y(), this->width(), this->height()),
                           QRectF(q->x(), q->y(), this->width(), oldHeight));
    }
}

void QEXTGuiGVItemPrivate::resetHeight()
{
    Q_Q(QEXTGuiGVItem);
    m_heightValid = false;
    q->setImplicitHeight(q->implicitHeight());
}

void QEXTGuiGVItemPrivate::resolveLayoutMirror()
{
    Q_Q(QEXTGuiGVItem);
    if (QEXTGuiGVItem *parentItem = q->parentItem())
    {
        QEXTGuiGVItemPrivate *parentPrivate = QEXTGuiGVItem::getPrivate(parentItem);
        this->setImplicitLayoutMirror(parentPrivate->m_inheritedLayoutMirror, parentPrivate->m_inheritMirrorFromItem);
    }
    else
    {
        this->setImplicitLayoutMirror(m_isMirrorImplicit ? false : m_effectiveLayoutMirror, m_inheritMirrorFromItem);
    }
}

void QEXTGuiGVItemPrivate::setImplicitLayoutMirror(bool mirror, bool inherit)
{
    Q_Q(QEXTGuiGVItem);
    inherit = (inherit || m_inheritMirrorFromItem);
    if (!m_isMirrorImplicit && m_inheritMirrorFromItem)
    {
        mirror = m_effectiveLayoutMirror;
    }
    if (mirror == m_inheritedLayoutMirror && inherit == m_inheritMirrorFromParent)
    {
        return;
    }

    m_inheritMirrorFromParent = inherit;
    m_inheritedLayoutMirror = m_inheritMirrorFromParent ? mirror : false;

    if (m_isMirrorImplicit)
    {
        this->setLayoutMirror(inherit ? m_inheritedLayoutMirror : false);
    }

    const QList<QGraphicsItem *> children = q->childItems();
    for (int i = 0; i < children.count(); ++i)
    {
        if (QEXTGuiGVItem *child = dynamic_cast<QEXTGuiGVItem *>(children.at(i)))
        {
            QEXTGuiGVItemPrivate *childPrivate = QEXTGuiGVItem::getPrivate(child);
            childPrivate->setImplicitLayoutMirror(m_inheritedLayoutMirror, m_inheritMirrorFromParent);
        }
    }
}

void QEXTGuiGVItemPrivate::setLayoutMirror(bool mirror)
{
    if (mirror != m_effectiveLayoutMirror)
    {
        m_effectiveLayoutMirror = mirror;
        //        if (m_anchors)
        //        {
        //            m_anchors->d_func()->fillChanged();
        //            m_anchors->d_func()->centerInChanged();
        //            m_anchors->d_func()->updateHorizontalAnchors();
        //        }
        //        this->mirrorChange();
        //        if (m_attachedLayoutDirection)
        //        {
        //            emit attachedLayoutDirection->enabledChanged();
        //        }
    }
}

qreal QEXTGuiGVItemPrivate::implicitWidth() const
{
    return m_implicitWidth;
}

qreal QEXTGuiGVItemPrivate::implicitHeight() const
{
    return m_implicitHeight;
}

void QEXTGuiGVItemPrivate::implicitWidthChanged()
{
    Q_Q(QEXTGuiGVItem);
    emit q->implicitWidthChanged();
}

void QEXTGuiGVItemPrivate::implicitHeightChanged()
{
    Q_Q(QEXTGuiGVItem);
    emit q->implicitHeightChanged();
}

void QEXTGuiGVItemPrivate::focusChanged(bool flag)
{
    Q_Q(QEXTGuiGVItem);

    if (m_hadActiveFocus != flag)
    {
        m_hadActiveFocus = flag;
        emit q->activeFocusChanged(flag);
    }

    QEXTGuiGVItem *focusItem = q;
    for (QEXTGuiGVItem *parent = q->parentItem(); QEXT_DECL_NULLPTR != parent; parent = parent->parentItem())
    {
        if (parent->flags() & QGraphicsItem::ItemIsFocusScope)
        {
            if (!flag && parent->focusScopeItem() != focusItem)
            {
                break;
            }
            if (parent->d_func()->m_hadActiveFocus != flag)
            {
                parent->d_func()->m_hadActiveFocus = flag;
                emit parent->activeFocusChanged(flag);
            }
            focusItem = parent;
        }
    }

    // For all but the top most focus scope/item this will be called for us by QGraphicsItem.
    focusItem->d_func()->focusScopeItemChange(flag);
}

void QEXTGuiGVItemPrivate::focusScopeItemChange(bool isSubFocusItem)
{
    if (m_hadFocus != isSubFocusItem)
    {
        m_hadFocus = isSubFocusItem;
        emit q_func()->focusChanged(isSubFocusItem);
    }
}



QEXTGuiGVItem::QEXTGuiGVItem(QEXTGuiGVItem *parent)
    : QGraphicsObject(parent), d_ptr(new QEXTGuiGVItemPrivate(this))
{

}

QEXTGuiGVItem::~QEXTGuiGVItem()
{

}

QEXTGuiGVItem *QEXTGuiGVItem::parentItem() const
{
    return qobject_cast<QEXTGuiGVItem *>(QGraphicsObject::parentObject());
}

void QEXTGuiGVItem::setParentItem(QEXTGuiGVItem *parent)
{
    QGraphicsObject::setParentItem(parent);
}

QRectF QEXTGuiGVItem::childrenRect()
{
    Q_D(QEXTGuiGVItem);
    if (!d->m_contents)
    {
        d->m_contents = new QEXTGuiContents(this);
        if (d->m_componentComplete)
        {
            d->m_contents->complete();
        }
    }
    return d->m_contents->rectF();
}

bool QEXTGuiGVItem::clip() const
{
    return this->flags() & ItemClipsChildrenToShape;
}

void QEXTGuiGVItem::setClip(bool clip)
{
    if (this->clip() == clip)
    {
        return;
    }
    this->setFlag(ItemClipsChildrenToShape, clip);
    emit this->clipChanged(clip);
}

qreal QEXTGuiGVItem::baselineOffset() const
{
    Q_D(const QEXTGuiGVItem);
    if (!d->m_baselineOffset.isValid())
    {
        return 0.0;
    }
    else
    {
        return d->m_baselineOffset;
    }
}

void QEXTGuiGVItem::setBaselineOffset(qreal offset)
{
    Q_D(QEXTGuiGVItem);
    if (offset == d->m_baselineOffset)
    {
        return;
    }

    d->m_baselineOffset = offset;

    //    for(int ii = 0; ii < d->changeListeners.count(); ++ii)
    //    {
    //        const QDeclarativeItemPrivate::ChangeListener &change = d->changeListeners.at(ii);
    //        if (change.types & QDeclarativeItemPrivate::Geometry)
    //        {
    //            QDeclarativeAnchorsPrivate *anchor = change.listener->anchorPrivate();
    //            if (anchor)
    //            {
    //                anchor->updateVerticalAnchors();
    //            }
    //        }
    //    }

    emit this->baselineOffsetChanged(offset);
}

qreal QEXTGuiGVItem::width() const
{
    Q_D(const QEXTGuiGVItem);
    return d->width();
}

void QEXTGuiGVItem::setWidth(qreal width)
{
    Q_D(QEXTGuiGVItem);
    d->setWidth(width);
}

void QEXTGuiGVItem::resetWidth()
{
    Q_D(QEXTGuiGVItem);
    d->resetWidth();
}

qreal QEXTGuiGVItem::implicitWidth() const
{
    Q_D(const QEXTGuiGVItem);
    return d->implicitWidth();
}

qreal QEXTGuiGVItem::height() const
{
    Q_D(const QEXTGuiGVItem);
    return d->height();
}

void QEXTGuiGVItem::setHeight(qreal height)
{
    Q_D(QEXTGuiGVItem);
    d->setHeight(height);
}

void QEXTGuiGVItem::resetHeight()
{
    Q_D(QEXTGuiGVItem);
    d->resetHeight();
}

qreal QEXTGuiGVItem::implicitHeight() const
{
    Q_D(const QEXTGuiGVItem);
    return d->implicitHeight();
}

void QEXTGuiGVItem::setSize(const QSizeF &size)
{
    Q_D(QEXTGuiGVItem);
    d->m_heightValid = true;
    d->m_widthValid = true;

    if (d->height() == size.height() && d->width() == size.width())
    {
        return;
    }

    qreal oldHeight = d->height();
    qreal oldWidth = d->width();

    this->prepareGeometryChange();
    d->setHeight(size.height());
    d->setWidth(size.width());

    this->geometryChanged(QRectF(x(), y(), this->width(), this->height()),
                          QRectF(x(), y(), oldWidth, oldHeight));
}

QEXTGuiGVItem::TransformOrigin QEXTGuiGVItem::transformOrigin() const
{
    Q_D(const QEXTGuiGVItem);
    return d->m_origin;
}

void QEXTGuiGVItem::setTransformOrigin(QEXTGuiGVItem::TransformOrigin origin)
{
    Q_D(QEXTGuiGVItem);
    if (origin != d->m_origin)
    {
        d->m_origin = origin;
        //        if (d->transformData)
        //        {
        //            QGraphicsItem::setTransformOriginPoint(d->computeTransformOrigin());
        //        }
        //        else
        //        {
        //            d->transformOriginDirty = true;
        //        }
        emit this->transformOriginChanged(d->m_origin);
    }
}

bool QEXTGuiGVItem::smooth() const
{
    Q_D(const QEXTGuiGVItem);
    return d->m_smooth;
}

void QEXTGuiGVItem::setSmooth(bool smooth)
{
    Q_D(QEXTGuiGVItem);
    if (d->m_smooth != smooth)
    {
        d->m_smooth = smooth;
        this->update();
        emit this->smoothChanged(smooth);
    }
}

bool QEXTGuiGVItem::hasActiveFocus() const
{
    Q_D(const QEXTGuiGVItem);
    QGraphicsItem *focusItem = this->focusItem();
    QGraphicsScene *scene = this->scene();
    bool hasOrWillGainFocus = focusItem && focusItem->isVisible() && (!scene || scene->focusItem() == focusItem);
    bool isOrIsScopeOfFocusItem = (focusItem == this || (this->flags() & QGraphicsItem::ItemIsFocusScope));
    return hasOrWillGainFocus && isOrIsScopeOfFocusItem;
}

bool QEXTGuiGVItem::hasFocus() const
{
    Q_D(const QEXTGuiGVItem);
    QEXTGuiGVItem *parent = this->parentItem();
    while (parent)
    {
        if (parent->flags() & QGraphicsItem::ItemIsFocusScope)
        {
            return parent->focusScopeItem() == this;
        }
        parent = parent->parentItem();
    }

    return this->hasActiveFocus();
}

void QEXTGuiGVItem::setFocus(bool focus)
{
    if (focus)
    {
        QGraphicsItem::setFocus(Qt::OtherFocusReason);
    }
    else
    {
        QGraphicsItem::clearFocus();
    }
}

bool QEXTGuiGVItem::keepMouseGrab() const
{
    Q_D(const QEXTGuiGVItem);
    return d->m_keepMouse;
}

void QEXTGuiGVItem::setKeepMouseGrab(bool keep)
{
    Q_D(QEXTGuiGVItem);
    d->m_keepMouse = keep;
}

void QEXTGuiGVItem::forceActiveFocus()
{
    this->setFocus(true);
    QGraphicsItem *parent = this->parentItem();
    while (parent)
    {
        if (parent->flags() & QGraphicsItem::ItemIsFocusScope)
        {
            parent->setFocus(Qt::OtherFocusReason);
        }
        parent = parent->parentItem();
    }
}

QEXTGuiGVItem *QEXTGuiGVItem::childAt(qreal x, qreal y) const
{
    const QList<QGraphicsItem *> children = this->childItems();
    for (int i = children.count() - 1; i >= 0; --i)
    {
        if (QEXTGuiGVItem *child = dynamic_cast<QEXTGuiGVItem *>(children.at(i)))
        {
            if (child->isVisible() && child->x() <= x
                    && child->x() + child->width() >= x
                    && child->y() <= y
                    && child->y() + child->height() >= y)
            {
                return child;
            }
        }
    }
    return QEXT_DECL_NULLPTR;
}

QRectF QEXTGuiGVItem::boundingRect() const
{
    Q_D(const QEXTGuiGVItem);
    return QRectF(0, 0, d->m_width, d->m_height);
}

void QEXTGuiGVItem::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{

}

QEXTGuiGVItemPrivate *QEXTGuiGVItem::getPrivate(QEXTGuiGVItem *item)
{
    return item->d_func();
}

QEXTGuiGVItem::QEXTGuiGVItem(QEXTGuiGVItemPrivate *d, QEXTGuiGVItem *parent)
    : QGraphicsObject(parent), d_ptr(d)
{

}

bool QEXTGuiGVItem::isComponentComplete() const
{
    Q_D(const QEXTGuiGVItem);
    return d->m_componentComplete;
}

void QEXTGuiGVItem::setImplicitWidth(qreal width)
{
    Q_D(QEXTGuiGVItem);
    bool changed = (width != d->m_implicitWidth);
    d->m_implicitWidth = width;
    if (d->m_width == width || this->widthValid())
    {
        if (changed)
        {
            d->implicitWidthChanged();
        }
        return;
    }

    qreal oldWidth = d->m_width;
    this->prepareGeometryChange();
    d->m_width = width;

    this->geometryChanged(QRectF(x(), y(), this->width(), this->height()),
                          QRectF(x(), y(), oldWidth, this->height()));

    if (changed)
    {
        d->implicitWidthChanged();
    }
}

bool QEXTGuiGVItem::widthValid() const
{
    Q_D(const QEXTGuiGVItem);
    return d->m_widthValid;
}

void QEXTGuiGVItem::setImplicitHeight(qreal height)
{
    Q_D(QEXTGuiGVItem);
    bool changed = (height != d->m_implicitHeight);
    d->m_implicitHeight = height;
    if (d->m_height == height || this->heightValid())
    {
        if (changed)
        {
            d->implicitHeightChanged();
        }
        return;
    }

    qreal oldHeight = d->m_height;

    this->prepareGeometryChange();
    d->m_height = height;

    this->geometryChanged(QRectF(x(), y(), this->width(), this->height()),
                          QRectF(x(), y(), this->width(), oldHeight));

    if (changed)
    {
        d->implicitHeightChanged();
    }
}

bool QEXTGuiGVItem::heightValid() const
{
    Q_D(const QEXTGuiGVItem);
    return d->m_heightValid;
}

void QEXTGuiGVItem::keyPressPreHandler(QKeyEvent *event)
{
    Q_D(QEXTGuiGVItem);
    if (d->m_keyHandler && !d->m_doneEventPreHandler)
    {
        d->m_keyHandler->keyPressed(event, false);
    }
    else
    {
        event->ignore();
    }
    d->m_doneEventPreHandler = true;
}

void QEXTGuiGVItem::keyReleasePreHandler(QKeyEvent *event)
{
    Q_D(QEXTGuiGVItem);
    if (d->m_keyHandler && !d->m_doneEventPreHandler)
    {
        d->m_keyHandler->keyReleased(event, false);
    }
    else
    {
        event->ignore();
    }
    d->m_doneEventPreHandler = true;
}

void QEXTGuiGVItem::inputMethodPreHandler(QInputMethodEvent *event)
{
    Q_D(QEXTGuiGVItem);
    if (d->m_keyHandler && !d->m_doneEventPreHandler)
    {
        d->m_keyHandler->inputMethodEvent(event, false);
    }
    else
    {
        event->ignore();
    }
    d->m_doneEventPreHandler = true;
}

bool QEXTGuiGVItem::sceneEvent(QEvent *event)
{
    Q_D(QEXTGuiGVItem);
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if ((keyEvent->key() == Qt::Key_Tab || keyEvent->key() == Qt::Key_Backtab) &&
                !(keyEvent->modifiers() & (Qt::ControlModifier | Qt::AltModifier)))
        {
            this->keyPressEvent(static_cast<QKeyEvent *>(event));
            if (!event->isAccepted())
            {
                return QGraphicsItem::sceneEvent(event);
            }
            else
            {
                return true;
            }
        }
        else
        {
            return QGraphicsItem::sceneEvent(event);
        }
    }
    else
    {
        bool rv = QGraphicsItem::sceneEvent(event);

        if (event->type() == QEvent::FocusIn || event->type() == QEvent::FocusOut)
        {
            d->focusChanged(this->hasActiveFocus());
        }
        return rv;
    }
}

bool QEXTGuiGVItem::event(QEvent *event)
{
    Q_D(QEXTGuiGVItem);
    switch (event->type())
    {
    case QEvent::KeyPress:
    case QEvent::KeyRelease:
    case QEvent::InputMethod:
        d->m_doneEventPreHandler = false;
        break;
    default:
        break;
    }

    return QGraphicsObject::event(event);
}

void QEXTGuiGVItem::keyPressEvent(QKeyEvent *event)
{
    Q_D(QEXTGuiGVItem);
    this->keyPressPreHandler(event);
    if (event->isAccepted())
    {
        return;
    }

    if (d->m_keyHandler)
    {
        d->m_keyHandler->keyPressed(event, true);
    }
    else
    {
        event->ignore();
    }
}

void QEXTGuiGVItem::keyReleaseEvent(QKeyEvent *event)
{
    Q_D(QEXTGuiGVItem);
    this->keyReleasePreHandler(event);
    if (event->isAccepted())
    {
        return;
    }
    if (d->m_keyHandler)
    {
        d->m_keyHandler->keyReleased(event, true);
    }
    else
    {
        event->ignore();
    }
}

void QEXTGuiGVItem::inputMethodEvent(QInputMethodEvent *event)
{
    Q_D(QEXTGuiGVItem);
    this->inputMethodPreHandler(event);
    if (event->isAccepted())
    {
        return;
    }
    if (d->m_keyHandler)
    {
        d->m_keyHandler->inputMethodEvent(event, true);
    }
    else
    {
        event->ignore();
    }
}

QVariant QEXTGuiGVItem::inputMethodQuery(Qt::InputMethodQuery query) const
{
    Q_D(const QEXTGuiGVItem);
    QVariant variant;
    if (d->m_keyHandler)
    {
        variant = d->m_keyHandler->inputMethodQuery(query);
    }

    if (!variant.isValid())
    {
        variant = QGraphicsObject::inputMethodQuery(query);
    }

    return variant;
}

QVariant QEXTGuiGVItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    Q_D(QEXTGuiGVItem);
    switch (change)
    {
    case ItemParentHasChanged:
    {
        d->resolveLayoutMirror();
        emit this->parentChanged(this->parentItem());
        //        d->m_parentNotifier.notify();
        break;
    }
    case ItemVisibleHasChanged:
    {
        //        for(int ii = 0; ii < d->m_changeListeners.count(); ++ii)
        //        {
        //            const QDeclarativeItemPrivate::ChangeListener &change = d->changeListeners.at(ii);
        //            if (change.types & QDeclarativeItemPrivate::Visibility)
        //            {
        //                change.listener->itemVisibilityChanged(this);
        //            }
        //        }
        break;
    }
    case ItemOpacityHasChanged:
    {
        //        for(int ii = 0; ii < d->changeListeners.count(); ++ii)
        //        {
        //            const QDeclarativeItemPrivate::ChangeListener &change = d->changeListeners.at(ii);
        //            if (change.types & QDeclarativeItemPrivate::Opacity)
        //            {
        //                change.listener->itemOpacityChanged(this);
        //            }
        //        }
        //        break;
    }
    case ItemChildAddedChange:
    {
        //        if (d->m_contents && d->m_componentComplete)
        //            d->m_contents->childAdded(qobject_cast<QDeclarativeItem *>(
        //                                         value.value<QGraphicsItem *>()));
        //        break;
    }
    case ItemChildRemovedChange:
        //        if (d->m_contents && d->m_componentComplete)
        //        {
        //            d->m_contents->childRemoved(qobject_cast<QDeclarativeItem *>(value.value<QGraphicsItem *>()));
        //        }
        break;
    default:
        break;
    }

    return QGraphicsItem::itemChange(change, value);
}

void QEXTGuiGVItem::classBegin()
{
    Q_D(QEXTGuiGVItem);
    d->m_componentComplete = false;
//    if (d->m_stateGroup)
//    {
//        d->m_stateGroup->classBegin();
//    }
    if (d->m_anchors)
    {
        d->m_anchors->classBegin();
    }
}

void QEXTGuiGVItem::componentComplete()
{
    Q_D(QEXTGuiGVItem);
    d->m_componentComplete = true;
    //    if (d->m_stateGroup)
    //    {
    //        d->m_stateGroup->componentComplete();
    //    }
    if (d->m_anchors)
    {
        d->m_anchors->componentComplete();
//        d->m_anchors->d_func()->updateOnComplete();
    }
    if (d->m_keyHandler)
    {
        d->m_keyHandler->componentComplete();
    }
    if (d->m_contents)
    {
        d->m_contents->complete();
    }
}

void QEXTGuiGVItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    Q_D(QEXTGuiGVItem);
    if (d->m_anchors)
    {
//        d->m_anchors->d_func()->updateMe();
    }

    if (this->transformOrigin() != QEXTGuiGVItem::TopLeft
            && (newGeometry.width() != oldGeometry.width() || newGeometry.height() != oldGeometry.height())) {
        //        if (d->transformData) {
        //            QPointF origin = d->computeTransformOrigin();
        //            if (transformOriginPoint() != origin)
        //                setTransformOriginPoint(origin);
        //        } else {
        //            d->transformOriginDirty = true;
        //        }
    }

    for(int ii = 0; ii < d->m_changeListeners.count(); ++ii)
    {
        const QEXTGuiGVItemPrivate::ChangeListener &change = d->m_changeListeners.at(ii);
        if (change.types & QEXTGuiGVItemPrivate::Geometry)
        {
            change.listener->itemGeometryChanged(this, newGeometry, oldGeometry);
        }
    }

    if (newGeometry.width() != oldGeometry.width())
    {
        emit this->widthChanged();
    }
    if (newGeometry.height() != oldGeometry.height())
    {
        emit this->heightChanged();
    }
}
