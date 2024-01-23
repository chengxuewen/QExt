#include <private/qextScroller_p.h>

#include <QMap>
#include <QTime>
#include <QEvent>
#include <QDebug>
#include <QObject>
#include <QPointer>
#include <QApplication>
#include <QElapsedTimer>
#include <QGraphicsView>
#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QGuiApplication>
#include <QGestureRecognizer>
#include <QAbstractScrollArea>
#include <QGraphicsSceneMouseEvent>
#include <QVector2D>
#include <qmath.h>
#include <qnumeric.h>
#ifdef Q_DEAD_CODE_FROM_QT4_WIN
#   include <QLibrary>
#endif

//#define QFLICKGESTURE_DEBUG

#ifdef QFLICKGESTURE_DEBUG
#  define qFGDebug  qDebug
#else
#  define qFGDebug  while (false) qDebug
#endif

#ifdef QT_SHARED // avoid conflict with symbol in static lib
bool qt_sendSpontaneousEvent(QObject *o, QEvent *e)
{
    return QCoreApplication::sendSpontaneousEvent(o, e);
}
#else
bool qt_sendSpontaneousEvent(QObject *receiver, QEvent *event);
#endif

static QMouseEvent *copyMouseEvent(QEvent *e)
{
    switch (e->type())
    {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove:
    {
        QMouseEvent *me = static_cast<QMouseEvent *>(e);
        QMouseEvent *cme = new QMouseEvent(me->type(), QPoint(0, 0), me->windowPos(), me->screenPos(),
                                           me->button(), me->buttons(), me->modifiers(), me->source());
        return cme;
    }
#ifndef QT_NO_GRAPHICSVIEW
    case QEvent::GraphicsSceneMousePress:
    case QEvent::GraphicsSceneMouseRelease:
    case QEvent::GraphicsSceneMouseMove:
    {
        QGraphicsSceneMouseEvent *me = static_cast<QGraphicsSceneMouseEvent *>(e);
#if 1
        QEvent::Type met = me->type() == QEvent::GraphicsSceneMousePress ? QEvent::MouseButtonPress :
                               (me->type() == QEvent::GraphicsSceneMouseRelease ? QEvent::MouseButtonRelease : QEvent::MouseMove);
        QMouseEvent *cme = new QMouseEvent(met, QPoint(0, 0), QPoint(0, 0), me->screenPos(),
                                           me->button(), me->buttons(), me->modifiers(), me->source());
        return cme;
#else
        QGraphicsSceneMouseEvent *copy = new QGraphicsSceneMouseEvent(me->type());
        copy->setPos(me->pos());
        copy->setScenePos(me->scenePos());
        copy->setScreenPos(me->screenPos());
        for (int i = 0x1; i <= 0x10; i <<= 1)
        {
            Qt::MouseButton button = Qt::MouseButton(i);
            copy->setButtonDownPos(button, me->buttonDownPos(button));
            copy->setButtonDownScenePos(button, me->buttonDownScenePos(button));
            copy->setButtonDownScreenPos(button, me->buttonDownScreenPos(button));
        }
        copy->setLastPos(me->lastPos());
        copy->setLastScenePos(me->lastScenePos());
        copy->setLastScreenPos(me->lastScreenPos());
        copy->setButtons(me->buttons());
        copy->setButton(me->button());
        copy->setModifiers(me->modifiers());
        copy->setSource(me->source());
        copy->setFlags(me->flags());
        return copy;
#endif
    }
#endif // QT_NO_GRAPHICSVIEW
    default:
        return 0;
    }
}

class PressDelayHandler : public QObject
{
private:
    PressDelayHandler(QObject *parent = 0)
        : QObject(parent)
        , pressDelayTimer(0)
        , sendingEvent(false)
        , mouseButton(Qt::NoButton)
        , mouseTarget(0)
        , mouseEventSource(Qt::MouseEventNotSynthesized)
    { }

    static PressDelayHandler *inst;

public:
    enum
    {
        UngrabMouseBefore = 1,
        RegrabMouseAfterwards = 2
    };

    static PressDelayHandler *instance()
    {
        static PressDelayHandler *inst = 0;
        if (!inst)
        {
            inst = new PressDelayHandler(QCoreApplication::instance());
        }
        return inst;
    }

    bool shouldEventBeIgnored(QEvent *) const
    {
        return sendingEvent;
    }

    bool isDelaying() const
    {
        return !pressDelayEvent.isNull();
    }

    void pressed(QEvent *e, int delay)
    {
        if (!pressDelayEvent)
        {
            pressDelayEvent.reset(copyMouseEvent(e));
            pressDelayTimer = startTimer(delay);
            mouseTarget = QApplication::widgetAt(pressDelayEvent->globalPos());
            mouseButton = pressDelayEvent->button();
            mouseEventSource = pressDelayEvent->source();
            qFGDebug("QFG: consuming/delaying mouse press");
        }
        else
        {
            qFGDebug("QFG: NOT consuming/delaying mouse press");
        }
        e->setAccepted(true);
    }

    bool released(QEvent *e, bool scrollerWasActive, bool scrollerIsActive)
    {
        // consume this event if the scroller was or is active
        bool result = scrollerWasActive || scrollerIsActive;

        // stop the timer
        if (pressDelayTimer)
        {
            killTimer(pressDelayTimer);
            pressDelayTimer = 0;
        }
        // we still haven't even sent the press, so do it now
        if (pressDelayEvent && mouseTarget && !scrollerIsActive)
        {
            QScopedPointer<QMouseEvent> releaseEvent(copyMouseEvent(e));

            qFGDebug() << "QFG: re-sending mouse press (due to release) for " << mouseTarget;
            sendMouseEvent(pressDelayEvent.data(), UngrabMouseBefore);

            qFGDebug() << "QFG: faking mouse release (due to release) for " << mouseTarget;
            sendMouseEvent(releaseEvent.data());

            result = true; // consume this event
        }
        else if (mouseTarget && scrollerIsActive)
        {
            // we grabbed the mouse expicitly when the scroller became active, so undo that now
            sendMouseEvent(0, UngrabMouseBefore);
        }
        pressDelayEvent.reset(0);
        mouseTarget = 0;
        return result;
    }

    void scrollerWasIntercepted()
    {
        qFGDebug("QFG: deleting delayed mouse press, since scroller was only intercepted");
        if (pressDelayEvent)
        {
            // we still haven't even sent the press, so just throw it away now
            if (pressDelayTimer)
            {
                killTimer(pressDelayTimer);
                pressDelayTimer = 0;
            }
            pressDelayEvent.reset(0);
        }
        mouseTarget = 0;
    }

    void scrollerBecameActive()
    {
        if (pressDelayEvent)
        {
            // we still haven't even sent the press, so just throw it away now
            qFGDebug("QFG: deleting delayed mouse press, since scroller is active now");
            if (pressDelayTimer)
            {
                killTimer(pressDelayTimer);
                pressDelayTimer = 0;
            }
            pressDelayEvent.reset(0);
            mouseTarget = 0;
        }
        else if (mouseTarget)
        {
            // we did send a press, so we need to fake a release now

            // release all pressed mouse buttons
            /* Qt::MouseButtons mouseButtons = QApplication::mouseButtons();
            for (int i = 0; i < 32; ++i) {
                if (mouseButtons & (1 << i)) {
                    Qt::MouseButton b = static_cast<Qt::MouseButton>(1 << i);
                    mouseButtons &= ~b;
                    QPoint farFarAway(-QWIDGETSIZE_MAX, -QWIDGETSIZE_MAX);

                    qFGDebug() << "QFG: sending a fake mouse release at far-far-away to " << mouseTarget;
                    QMouseEvent re(QEvent::MouseButtonRelease, QPoint(), farFarAway,
                                   b, mouseButtons, QApplication::keyboardModifiers());
                    sendMouseEvent(&re);
                }
            }*/

            QPoint farFarAway(-QWIDGETSIZE_MAX, -QWIDGETSIZE_MAX);

            qFGDebug() << "QFG: sending a fake mouse release at far-far-away to " << mouseTarget;
            QMouseEvent re(QEvent::MouseButtonRelease, QPoint(), farFarAway, farFarAway,
                           mouseButton, QApplication::mouseButtons() & ~mouseButton,
                           QApplication::keyboardModifiers(), mouseEventSource);
            sendMouseEvent(&re, RegrabMouseAfterwards);
            // don't clear the mouseTarget just yet, since we need to explicitly ungrab the mouse on release!
        }
    }

protected:
    void timerEvent(QTimerEvent *e) QEXT_OVERRIDE
    {
        if (e->timerId() == pressDelayTimer)
        {
            if (pressDelayEvent && mouseTarget)
            {
                qFGDebug() << "QFG: timer event: re-sending mouse press to " << mouseTarget;
                sendMouseEvent(pressDelayEvent.data(), UngrabMouseBefore);
            }
            pressDelayEvent.reset(0);

            if (pressDelayTimer)
            {
                killTimer(pressDelayTimer);
                pressDelayTimer = 0;
            }
        }
    }

    void sendMouseEvent(QMouseEvent *me, int flags = 0)
    {
        if (mouseTarget)
        {
            sendingEvent = true;

#ifndef QT_NO_GRAPHICSVIEW
            QGraphicsItem *grabber = 0;
            if (mouseTarget->parentWidget())
            {
                if (QGraphicsView *gv = qobject_cast<QGraphicsView *>(mouseTarget->parentWidget()))
                {
                    if (gv->scene())
                    {
                        grabber = gv->scene()->mouseGrabberItem();
                    }
                }
            }

            if (grabber && (flags & UngrabMouseBefore))
            {
                // GraphicsView Mouse Handling Workaround #1:
                // we need to ungrab the mouse before re-sending the press,
                // since the scene had already set the mouse grabber to the
                // original (and consumed) event's receiver
                qFGDebug() << "QFG: ungrabbing" << grabber;
                grabber->ungrabMouse();
            }
#endif // QT_NO_GRAPHICSVIEW

            if (me)
            {
                QMouseEvent copy(me->type(), mouseTarget->mapFromGlobal(me->globalPos()),
                                 mouseTarget->topLevelWidget()->mapFromGlobal(me->globalPos()), me->screenPos(),
                                 me->button(), me->buttons(), me->modifiers(), me->source());
                qt_sendSpontaneousEvent(mouseTarget, &copy);
            }

#ifndef QT_NO_GRAPHICSVIEW
            if (grabber && (flags & RegrabMouseAfterwards))
            {
                // GraphicsView Mouse Handling Workaround #2:
                // we need to re-grab the mouse after sending a faked mouse
                // release, since we still need the mouse moves for the gesture
                // (the scene will clear the item's mouse grabber status on
                // release).
                qFGDebug() << "QFG: re-grabbing" << grabber;
                grabber->grabMouse();
            }
#endif
            sendingEvent = false;
        }
    }


private:
    int pressDelayTimer;
    QScopedPointer<QMouseEvent> pressDelayEvent;
    bool sendingEvent;
    Qt::MouseButton mouseButton;
    QPointer<QWidget> mouseTarget;
    Qt::MouseEventSource mouseEventSource;
};


/*!
    \internal
    \class QExtFlickGesture
    \since 4.8
    \brief The QExtFlickGesture class describes a flicking gesture made by the user.
    \ingroup gestures
    The QExtFlickGesture is more complex than the QPanGesture that uses QExtScroller and QExtScrollerProperties
    to decide if it is triggered.
    This gesture is reacting on touch event as compared to the QMouseFlickGesture.

    \sa {Gestures in Widgets and Graphics View}, QExtScroller, QExtScrollerProperties, QMouseFlickGesture
*/

/*!
    \internal
*/
QExtFlickGesture::QExtFlickGesture(QObject *receiver, Qt::MouseButton button, QObject *parent)
    : QGesture(parent)
{
    m_receiver = receiver;
    m_receiverScroller = (receiver && QExtScroller::hasScroller(receiver)) ? QExtScroller::scroller(receiver) : 0;
    m_button = button;
    m_macIgnoreWheel = false;
}

QExtFlickGesture::~QExtFlickGesture() { }

QExtFlickGestureRecognizer::QExtFlickGestureRecognizer(Qt::MouseButton button)
{
    this->m_button = button;
}

QGesture *QExtFlickGestureRecognizer::create(QObject *target)
{
#ifndef QT_NO_GRAPHICSVIEW
    QGraphicsObject *go = qobject_cast<QGraphicsObject*>(target);
    if (go && m_button == Qt::NoButton)
    {
        go->setAcceptTouchEvents(true);
    }
#endif
    return new QExtFlickGesture(target, m_button);
}

/*! \internal
    The recognize function detects a touch event suitable to start the attached QExtScroller.
    The QExtFlickGesture will be triggered as soon as the scroller is no longer in the state
    QExtScroller::Inactive or QExtScroller::Pressed. It will be finished or canceled
    at the next QEvent::TouchEnd.
    Note that the QExtScroller might continue scrolling (kinetically) at this point.
 */
QGestureRecognizer::Result QExtFlickGestureRecognizer::recognize(QGesture *state,
                                                                 QObject *watched,
                                                                 QEvent *event)
{
    Q_UNUSED(watched);

    static QElapsedTimer monotonicTimer;
    if (!monotonicTimer.isValid())
        monotonicTimer.start();

    QExtFlickGesture *q = static_cast<QExtFlickGesture *>(state);
    QExtScroller *scroller = q->receiverScroller();
    if (!scroller)
    {
        return Ignore; // nothing to do without a scroller?
    }

    QWidget *receiverWidget = qobject_cast<QWidget *>(q->receiver());
#ifndef QT_NO_GRAPHICSVIEW
    QGraphicsObject *receiverGraphicsObject = qobject_cast<QGraphicsObject *>(q->receiver());
#endif

    // this is only set for events that we inject into the event loop via sendEvent()
    if (PressDelayHandler::instance()->shouldEventBeIgnored(event))
    {
        //qFGDebug() << state << "QFG: ignored event: " << event->type();
        return Ignore;
    }

    const QMouseEvent *me = 0;
#ifndef QT_NO_GRAPHICSVIEW
    const QGraphicsSceneMouseEvent *gsme = 0;
#endif
    const QTouchEvent *te = 0;
    QPoint globalPos;

    // qFGDebug() << "FlickGesture "<<state<<"watched:"<<watched<<"receiver"<<d->receiver<<"event"<<event->type()<<"button"<<button;

    switch (event->type())
    {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove:
        if (!receiverWidget)
        {
            return Ignore;
        }
        if (m_button != Qt::NoButton)
        {
            me = static_cast<const QMouseEvent *>(event);
            globalPos = me->globalPos();
        }
        break;
#ifndef QT_NO_GRAPHICSVIEW
    case QEvent::GraphicsSceneMousePress:
    case QEvent::GraphicsSceneMouseRelease:
    case QEvent::GraphicsSceneMouseMove:
        if (!receiverGraphicsObject)
        {
            return Ignore;
        }
        if (m_button != Qt::NoButton)
        {
            gsme = static_cast<const QGraphicsSceneMouseEvent *>(event);
            globalPos = gsme->screenPos();
        }
        break;
#endif
    case QEvent::TouchBegin:
    case QEvent::TouchEnd:
    case QEvent::TouchUpdate:
        if (m_button == Qt::NoButton)
        {
            te = static_cast<const QTouchEvent *>(event);
            if (!te->touchPoints().isEmpty())
            {
                globalPos = te->touchPoints().at(0).screenPos().toPoint();
            }
        }
        break;

#if defined(Q_DEAD_CODE_FROM_QT4_MAC)
        // the only way to distinguish between real mouse wheels and wheel
        // events generated by the native 2 finger swipe gesture is to listen
        // for these events (according to Apple's Cocoa Event-Handling Guide)

    case QEvent::NativeGesture:
    {
        QNativeGestureEvent *nge = static_cast<QNativeGestureEvent *>(event);
        if (nge->gestureType == QNativeGestureEvent::GestureBegin)
        {
            q->setMacIgnoreWheel(true);
        }
        else if (nge->gestureType == QNativeGestureEvent::GestureEnd)
        {
            q->setMacIgnoreWheel(false);
        }
        break;
    }
#endif

        // consume all wheel events if the scroller is active
    case QEvent::Wheel:
        if (q->macIgnoreWheel() || (scroller->state() != QExtScroller::Inactive))
        {
            return Ignore | ConsumeEventHint;
        }
        break;
        // consume all dbl click events if the scroller is active
    case QEvent::MouseButtonDblClick:
        if (scroller->state() != QExtScroller::Inactive)
        {
            return Ignore | ConsumeEventHint;
        }
        break;
    default:
        break;
    }

    if (!me
#ifndef QT_NO_GRAPHICSVIEW
        && !gsme
#endif
        && !te) // Neither mouse nor touch
    {
        return Ignore;
    }

    // get the current pointer position in local coordinates.
    QPointF point;
    QExtScroller::Input inputType = (QExtScroller::Input) 0;

    switch (event->type())
    {
    case QEvent::MouseButtonPress:
        if (me && me->button() == m_button && me->buttons() == m_button)
        {
            point = me->globalPos();
            inputType = QExtScroller::InputPress;
        }
        else if (me)
        {
            scroller->stop();
            return CancelGesture;
        }
        break;
    case QEvent::MouseButtonRelease:
        if (me && me->button() == m_button)
        {
            point = me->globalPos();
            inputType = QExtScroller::InputRelease;
        }
        break;
    case QEvent::MouseMove:
        if (me && me->buttons() == m_button)
        {
            point = me->globalPos();
            inputType = QExtScroller::InputMove;
        }
        break;

#ifndef QT_NO_GRAPHICSVIEW
    case QEvent::GraphicsSceneMousePress:
        if (gsme && gsme->button() == m_button && gsme->buttons() == m_button)
        {
            point = gsme->scenePos();
            inputType = QExtScroller::InputPress;
        }
        else if (gsme)
        {
            scroller->stop();
            return CancelGesture;
        }
        break;
    case QEvent::GraphicsSceneMouseRelease:
        if (gsme && gsme->button() == m_button)
        {
            point = gsme->scenePos();
            inputType = QExtScroller::InputRelease;
        }
        break;
    case QEvent::GraphicsSceneMouseMove:
        if (gsme && gsme->buttons() == m_button)
        {
            point = gsme->scenePos();
            inputType = QExtScroller::InputMove;
        }
        break;
#endif

    case QEvent::TouchBegin:
        inputType = QExtScroller::InputPress;
        // fall through
    case QEvent::TouchEnd:
        if (!inputType)
        {
            inputType = QExtScroller::InputRelease;
        }
        // fallthrough
    case QEvent::TouchUpdate:
        if (!inputType)
        {
            inputType = QExtScroller::InputMove;
        }

        if (te->device()->type() == QTouchDevice::TouchPad)
        {
            if (te->touchPoints().count() != 2)  // 2 fingers on pad
            {
                return Ignore;
            }

            point = te->touchPoints().at(0).startScenePos() +
                    ((te->touchPoints().at(0).scenePos() - te->touchPoints().at(0).startScenePos()) +
                     (te->touchPoints().at(1).scenePos() - te->touchPoints().at(1).startScenePos())) / 2;
        }
        else
        { // TouchScreen
            if (te->touchPoints().count() != 1) // 1 finger on screen
            {
                return Ignore;
            }

            point = te->touchPoints().at(0).scenePos();
        }
        break;

    default:
        break;
    }

    // Check for an active scroller at globalPos
    if (inputType == QExtScroller::InputPress)
    {
        foreach (QExtScroller *as, QExtScroller::activeScrollers())
        {
            if (as != scroller)
            {
                QRegion scrollerRegion;

                if (QWidget *w = qobject_cast<QWidget *>(as->target()))
                {
                    scrollerRegion = QRect(w->mapToGlobal(QPoint(0, 0)), w->size());
#ifndef QT_NO_GRAPHICSVIEW
                }
                else if (QGraphicsObject *go = qobject_cast<QGraphicsObject *>(as->target()))
                {
                    if (go->scene() && !go->scene()->views().isEmpty())
                    {
                        foreach (QGraphicsView *gv, go->scene()->views())
                        {
                            scrollerRegion |= gv->mapFromScene(go->mapToScene(go->boundingRect()))
                                                  .translated(gv->mapToGlobal(QPoint(0, 0)));
                        }
                    }
#endif
                }
                // active scrollers always have priority
                if (scrollerRegion.contains(globalPos))
                {
                    return Ignore;
                }
            }
        }
    }

    bool scrollerWasDragging = (scroller->state() == QExtScroller::Dragging);
    bool scrollerWasScrolling = (scroller->state() == QExtScroller::Scrolling);

    if (inputType)
    {
        if (QWidget *w = qobject_cast<QWidget *>(q->receiver()))
        {
            point = w->mapFromGlobal(point.toPoint());
        }
#ifndef QT_NO_GRAPHICSVIEW
        else if (QGraphicsObject *go = qobject_cast<QGraphicsObject *>(q->receiver()))
        {
            point = go->mapFromScene(point);
        }
#endif

        // inform the scroller about the new event
        scroller->handleInput(inputType, point, monotonicTimer.elapsed());
    }

    // depending on the scroller state return the gesture state
    Result result(0);
    bool scrollerIsActive = (scroller->state() == QExtScroller::Dragging ||
                             scroller->state() == QExtScroller::Scrolling);

    // Consume all mouse events while dragging or scrolling to avoid nasty
    // side effects with Qt's standard widgets.
    if ((me
#ifndef QT_NO_GRAPHICSVIEW
         || gsme
#endif
         ) && scrollerIsActive)
    {
        result |= ConsumeEventHint;
    }

    // The only problem with this approach is that we consume the
    // MouseRelease when we start the scrolling with a flick gesture, so we
    // have to fake a MouseRelease "somewhere" to not mess with the internal
    // states of Qt's widgets (a QPushButton would stay in 'pressed' state
    // forever, if it doesn't receive a MouseRelease).
    if (me
#ifndef QT_NO_GRAPHICSVIEW
        || gsme
#endif
        )
    {
        if (!scrollerWasDragging && !scrollerWasScrolling && scrollerIsActive)
        {
            PressDelayHandler::instance()->scrollerBecameActive();
        }
        else if (scrollerWasScrolling && (scroller->state() == QExtScroller::Dragging || scroller->state() == QExtScroller::Inactive))
        {
            PressDelayHandler::instance()->scrollerWasIntercepted();
        }
    }

    if (!inputType)
    {
        result |= Ignore;
    }
    else
    {
        switch (event->type())
        {
        case QEvent::MouseButtonPress:
#ifndef QT_NO_GRAPHICSVIEW
        case QEvent::GraphicsSceneMousePress:
#endif
            if (scroller->state() == QExtScroller::Pressed)
            {
                int pressDelay = int(1000 * scroller->scrollerProperties().scrollMetric(QExtScrollerProperties::MousePressEventDelay).toReal());
                if (pressDelay > 0)
                {
                    result |= ConsumeEventHint;

                    PressDelayHandler::instance()->pressed(event, pressDelay);
                    event->accept();
                }
            }
            // fall through
        case QEvent::TouchBegin:
            q->setHotSpot(globalPos);
            result |= scrollerIsActive ? TriggerGesture : MayBeGesture;
            break;

        case QEvent::MouseMove:
#ifndef QT_NO_GRAPHICSVIEW
        case QEvent::GraphicsSceneMouseMove:
#endif
            if (PressDelayHandler::instance()->isDelaying())
            {
                result |= ConsumeEventHint;
            }
            // fall through
        case QEvent::TouchUpdate:
            result |= scrollerIsActive ? TriggerGesture : Ignore;
            break;

#ifndef QT_NO_GRAPHICSVIEW
        case QEvent::GraphicsSceneMouseRelease:
#endif
        case QEvent::MouseButtonRelease:
            if (PressDelayHandler::instance()->released(event, scrollerWasDragging || scrollerWasScrolling, scrollerIsActive))
            {
                result |= ConsumeEventHint;
            }
            // fall through
        case QEvent::TouchEnd:
            result |= scrollerIsActive ? FinishGesture : CancelGesture;
            break;

        default:
            result |= Ignore;
            break;
        }
    }
    return result;
}


/*! \reimp
 */
void QExtFlickGestureRecognizer::reset(QGesture *state)
{
    QGestureRecognizer::reset(state);
}


/***********************************************************************************************************************
** QExtScrollerProperties
***********************************************************************************************************************/
static QExtScrollerPropertiesPrivate *userDefaults = 0;
static QExtScrollerPropertiesPrivate *systemDefaults = 0;

QExtScrollerPropertiesPrivate *QExtScrollerPropertiesPrivate::defaults()
{
    if (!systemDefaults)
    {
        QExtScrollerPropertiesPrivate spp;
        spp.m_mousePressEventDelay = qreal(0.25);
        spp.m_dragStartDistance = qreal(5.0 / 1000);
        spp.m_dragVelocitySmoothingFactor = qreal(0.8);
        spp.m_axisLockThreshold = qreal(0);
        spp.m_scrollingCurve.setType(QEasingCurve::OutQuad);
        spp.m_decelerationFactor = qreal(0.125);
        spp.m_minimumVelocity = qreal(50.0 / 1000);
        spp.m_maximumVelocity = qreal(500.0 / 1000);
        spp.m_maximumClickThroughVelocity = qreal(66.5 / 1000);
        spp.m_acceleratingFlickMaximumTime = qreal(1.25);
        spp.m_acceleratingFlickSpeedupFactor = qreal(3.0);
        spp.m_snapPositionRatio = qreal(0.5);
        spp.m_snapTime = qreal(0.3);
        spp.m_overshootDragResistanceFactor = qreal(0.5);
        spp.m_overshootDragDistanceFactor = qreal(1);
        spp.m_overshootScrollDistanceFactor = qreal(0.5);
        spp.m_overshootScrollTime = qreal(0.7);
#  ifdef Q_DEAD_CODE_FROM_QT4_WIN
        if (QLibrary::resolve(QLatin1String("UxTheme"), "BeginPanningFeedback"))
        {
            spp.overshootScrollTime = qreal(0.35);
        }
#  endif
        spp.m_hOvershootPolicy = QExtScrollerProperties::OvershootWhenScrollable;
        spp.m_vOvershootPolicy = QExtScrollerProperties::OvershootWhenScrollable;
        spp.m_frameRate = QExtScrollerProperties::Standard;

        systemDefaults = new QExtScrollerPropertiesPrivate(spp);
    }
    return new QExtScrollerPropertiesPrivate(userDefaults ? *userDefaults : *systemDefaults);
}

/*!
    \class QExtScrollerProperties
    \brief The QExtScrollerProperties class stores the settings for a QExtScroller.
    \since 4.8

    \inmodule QtWidgets

    The QExtScrollerProperties class stores the parameters used by QExtScroller.

    The default settings are platform dependent so that Qt emulates the
    platform behaviour for kinetic scrolling.

    As a convention the QExtScrollerProperties are in physical units (meter,
    seconds) and are converted by QExtScroller using the current DPI.

    \sa QExtScroller
*/

/*!
    Constructs new scroller properties.
*/
QExtScrollerProperties::QExtScrollerProperties()
    : dd_ptr(QExtScrollerPropertiesPrivate::defaults())
{
}

/*!
    Constructs a copy of \a sp.
*/
QExtScrollerProperties::QExtScrollerProperties(const QExtScrollerProperties &sp)
    : dd_ptr(new QExtScrollerPropertiesPrivate(*sp.dd_ptr))
{
}

/*!
    Assigns \a sp to these scroller properties and returns a reference to these scroller properties.
*/
QExtScrollerProperties &QExtScrollerProperties::operator=(const QExtScrollerProperties &sp)
{
    *dd_ptr.data() = *sp.dd_ptr.data();
    return *this;
}

/*!
    Destroys the scroller properties.
*/
QExtScrollerProperties::~QExtScrollerProperties()
{
}

/*!
    Returns \c true if these scroller properties are equal to \a sp; otherwise returns \c false.
*/
bool QExtScrollerProperties::operator==(const QExtScrollerProperties &sp) const
{
    return *dd_ptr.data() == *sp.dd_ptr.data();
}

/*!
    Returns \c true if these scroller properties are different from \a sp; otherwise returns \c false.
*/
bool QExtScrollerProperties::operator!=(const QExtScrollerProperties &sp) const
{
    return !(*dd_ptr.data() == *sp.dd_ptr.data());
}

bool QExtScrollerPropertiesPrivate::operator==(const QExtScrollerPropertiesPrivate &p) const
{
    bool same = true;
    same &= (m_mousePressEventDelay == p.m_mousePressEventDelay);
    same &= (m_dragStartDistance == p.m_dragStartDistance);
    same &= (m_dragVelocitySmoothingFactor == p.m_dragVelocitySmoothingFactor);
    same &= (m_axisLockThreshold == p.m_axisLockThreshold);
    same &= (m_scrollingCurve == p.m_scrollingCurve);
    same &= (m_decelerationFactor == p.m_decelerationFactor);
    same &= (m_minimumVelocity == p.m_minimumVelocity);
    same &= (m_maximumVelocity == p.m_maximumVelocity);
    same &= (m_maximumClickThroughVelocity == p.m_maximumClickThroughVelocity);
    same &= (m_acceleratingFlickMaximumTime == p.m_acceleratingFlickMaximumTime);
    same &= (m_acceleratingFlickSpeedupFactor == p.m_acceleratingFlickSpeedupFactor);
    same &= (m_snapPositionRatio == p.m_snapPositionRatio);
    same &= (m_snapTime == p.m_snapTime);
    same &= (m_overshootDragResistanceFactor == p.m_overshootDragResistanceFactor);
    same &= (m_overshootDragDistanceFactor == p.m_overshootDragDistanceFactor);
    same &= (m_overshootScrollDistanceFactor == p.m_overshootScrollDistanceFactor);
    same &= (m_overshootScrollTime == p.m_overshootScrollTime);
    same &= (m_hOvershootPolicy == p.m_hOvershootPolicy);
    same &= (m_vOvershootPolicy == p.m_vOvershootPolicy);
    same &= (m_frameRate == p.m_frameRate);
    return same;
}

/*!
     Sets the scroller properties for all new QExtScrollerProperties objects to \a sp.

     Use this function to override the platform default properties returned by the default
     constructor. If you only want to change the scroller properties of a single scroller, use
     QExtScroller::setScrollerProperties()

     \note Calling this function will not change the content of already existing
     QExtScrollerProperties objects.

     \sa unsetDefaultScrollerProperties()
*/
void QExtScrollerProperties::setDefaultScrollerProperties(const QExtScrollerProperties &sp)
{
    if (!userDefaults)
    {
        userDefaults = new QExtScrollerPropertiesPrivate(*sp.dd_ptr);
    }
    else
    {
        *userDefaults = *sp.dd_ptr;
    }
}

/*!
     Sets the scroller properties returned by the default constructor back to the platform default
     properties.

     \sa setDefaultScrollerProperties()
*/
void QExtScrollerProperties::unsetDefaultScrollerProperties()
{
    delete userDefaults;
    userDefaults = 0;
}

/*!
    Query the \a metric value of the scroller properties.

    \sa setScrollMetric(), ScrollMetric
*/
QVariant QExtScrollerProperties::scrollMetric(ScrollMetric metric) const
{
    switch (metric)
    {
    case MousePressEventDelay:          return dd_ptr->m_mousePressEventDelay;
    case DragStartDistance:             return dd_ptr->m_dragStartDistance;
    case DragVelocitySmoothingFactor:   return dd_ptr->m_dragVelocitySmoothingFactor;
    case AxisLockThreshold:             return dd_ptr->m_axisLockThreshold;
    case ScrollingCurve:                return dd_ptr->m_scrollingCurve;
    case DecelerationFactor:            return dd_ptr->m_decelerationFactor;
    case MinimumVelocity:               return dd_ptr->m_minimumVelocity;
    case MaximumVelocity:               return dd_ptr->m_maximumVelocity;
    case MaximumClickThroughVelocity:   return dd_ptr->m_maximumClickThroughVelocity;
    case AcceleratingFlickMaximumTime:  return dd_ptr->m_acceleratingFlickMaximumTime;
    case AcceleratingFlickSpeedupFactor:return dd_ptr->m_acceleratingFlickSpeedupFactor;
    case SnapPositionRatio:             return dd_ptr->m_snapPositionRatio;
    case SnapTime:                      return dd_ptr->m_snapTime;
    case OvershootDragResistanceFactor: return dd_ptr->m_overshootDragResistanceFactor;
    case OvershootDragDistanceFactor:   return dd_ptr->m_overshootDragDistanceFactor;
    case OvershootScrollDistanceFactor: return dd_ptr->m_overshootScrollDistanceFactor;
    case OvershootScrollTime:           return dd_ptr->m_overshootScrollTime;
    case HorizontalOvershootPolicy:     return QVariant::fromValue(dd_ptr->m_hOvershootPolicy);
    case VerticalOvershootPolicy:       return QVariant::fromValue(dd_ptr->m_vOvershootPolicy);
    case FrameRate:                     return QVariant::fromValue(dd_ptr->m_frameRate);
    case ScrollMetricCount:             break;
    }
    return QVariant();
}

/*!
    Set a specific value of the \a metric ScrollerMetric to \a value.

    \sa scrollMetric(), ScrollMetric
*/
void QExtScrollerProperties::setScrollMetric(ScrollMetric metric, const QVariant &value)
{
    switch (metric)
    {
    case MousePressEventDelay:          dd_ptr->m_mousePressEventDelay = value.toReal(); break;
    case DragStartDistance:             dd_ptr->m_dragStartDistance = value.toReal(); break;
    case DragVelocitySmoothingFactor:   dd_ptr->m_dragVelocitySmoothingFactor = qBound(qreal(0), value.toReal(), qreal(1)); break;
    case AxisLockThreshold:             dd_ptr->m_axisLockThreshold = qBound(qreal(0), value.toReal(), qreal(1)); break;
    case ScrollingCurve:                dd_ptr->m_scrollingCurve = value.toEasingCurve(); break;
    case DecelerationFactor:            dd_ptr->m_decelerationFactor = value.toReal(); break;
    case MinimumVelocity:               dd_ptr->m_minimumVelocity = value.toReal(); break;
    case MaximumVelocity:               dd_ptr->m_maximumVelocity = value.toReal(); break;
    case MaximumClickThroughVelocity:   dd_ptr->m_maximumClickThroughVelocity = value.toReal(); break;
    case AcceleratingFlickMaximumTime:  dd_ptr->m_acceleratingFlickMaximumTime = value.toReal(); break;
    case AcceleratingFlickSpeedupFactor:dd_ptr->m_acceleratingFlickSpeedupFactor = value.toReal(); break;
    case SnapPositionRatio:             dd_ptr->m_snapPositionRatio = qBound(qreal(0), value.toReal(), qreal(1)); break;
    case SnapTime:                      dd_ptr->m_snapTime = value.toReal(); break;
    case OvershootDragResistanceFactor: dd_ptr->m_overshootDragResistanceFactor = value.toReal(); break;
    case OvershootDragDistanceFactor:   dd_ptr->m_overshootDragDistanceFactor = qBound(qreal(0), value.toReal(), qreal(1)); break;
    case OvershootScrollDistanceFactor: dd_ptr->m_overshootScrollDistanceFactor = qBound(qreal(0), value.toReal(), qreal(1)); break;
    case OvershootScrollTime:           dd_ptr->m_overshootScrollTime = value.toReal(); break;
    case HorizontalOvershootPolicy:     dd_ptr->m_hOvershootPolicy = value.value<QExtScrollerProperties::OvershootPolicy>(); break;
    case VerticalOvershootPolicy:       dd_ptr->m_vOvershootPolicy = value.value<QExtScrollerProperties::OvershootPolicy>(); break;
    case FrameRate:                     dd_ptr->m_frameRate = value.value<QExtScrollerProperties::FrameRates>(); break;
    case ScrollMetricCount:             break;
    }
}

/*!
    \enum QExtScrollerProperties::FrameRates

    This enum describes the available frame rates used while dragging or scrolling.

    \value Fps60 60 frames per second
    \value Fps30 30 frames per second
    \value Fps20 20 frames per second
    \value Standard the default value is 60 frames per second (which corresponds to QAbstractAnimation).
*/

/*!
    \enum QExtScrollerProperties::OvershootPolicy

    This enum describes the various modes of overshooting.

    \value OvershootWhenScrollable Overshooting is possible when the content is scrollable. This is the
                                   default.

    \value OvershootAlwaysOff Overshooting is never enabled, even when the content is scrollable.

    \value OvershootAlwaysOn Overshooting is always enabled, even when the content is not
                             scrollable.
*/

/*!
    \enum QExtScrollerProperties::ScrollMetric

    This enum contains the different scroll metric types. When not indicated otherwise the
    setScrollMetric function expects a QVariant of type qreal.

    See the QExtScroller documentation for further details of the concepts behind the different
    values.

    \value MousePressEventDelay This is the time a mouse press event is delayed when starting
    a flick gesture in \c{[s]}. If the gesture is triggered within that time, no mouse press or
    release is sent to the scrolled object. If it triggers after that delay the delayed
    mouse press plus a faked release event at global position \c{QPoint(-QWIDGETSIZE_MAX,
    -QWIDGETSIZE_MAX)} is sent. If the gesture is canceled, then both the delayed mouse
    press plus the real release event are delivered.

    \value DragStartDistance This is the minimum distance the touch or mouse point needs to be
    moved before the flick gesture is triggered in \c m.

    \value DragVelocitySmoothingFactor A value that describes to which extent new drag velocities are
    included in the final scrolling velocity.  This value should be in the range between \c 0 and
    \c 1.  The lower the value, the more smoothing is applied to the dragging velocity.

    \value AxisLockThreshold Restricts the movement to one axis if the movement is inside an angle
    around the axis. The threshold must be in the range \c 0 to \c 1.

    \value ScrollingCurve The QEasingCurve used when decelerating the scrolling velocity after an
    user initiated flick. Please note that this is the easing curve for the positions, \b{not}
    the velocity: the default is QEasingCurve::OutQuad, which results in a linear decrease in
    velocity (1st derivative) and a constant deceleration (2nd derivative).

    \value DecelerationFactor This factor influences how long it takes the scroller to decelerate
    to 0 velocity. The actual value depends on the chosen ScrollingCurve. For most
    types the value should be in the range from \c 0.1 to \c 2.0

    \value MinimumVelocity The minimum velocity that is needed after ending the touch or releasing
    the mouse to start scrolling in \c{m/s}.

    \value MaximumVelocity This is the maximum velocity that can be reached in \c{m/s}.

    \value MaximumClickThroughVelocity This is the maximum allowed scroll speed for a click-through
    in \c{m/s}. This means that a click on a currently (slowly) scrolling object will not only stop
    the scrolling but the click event will also be delivered to the UI control. This is
    useful when using exponential-type scrolling curves.

    \value AcceleratingFlickMaximumTime This is the maximum time in \c seconds that a flick gesture
    can take to be recognized as an accelerating flick. If set to zero no such gesture is
    detected. An "accelerating flick" is a flick gesture executed on an already scrolling object.
    In such cases the scrolling speed is multiplied by AcceleratingFlickSpeedupFactor in order to
    accelerate it.

    \value AcceleratingFlickSpeedupFactor The current speed is multiplied by this number if an
    accelerating flick is detected. Should be \c{>= 1}.

    \value SnapPositionRatio This is the distance that the user must drag the area beween two snap
    points in order to snap it to the next position. \c{0.33} means that the scroll must only
    reach one third of the distance between two snap points to snap to the next one. The ratio must
    be between \c 0 and \c 1.

    \value SnapTime This is the time factor for the scrolling curve. A lower value means that the
    scrolling will take longer. The scrolling distance is independet of this value.

    \value OvershootDragResistanceFactor This value is the factor between the mouse dragging and
    the actual scroll area movement (during overshoot). The factor must be between \c 0 and \c 1.

    \value OvershootDragDistanceFactor This is the maximum distance for overshoot movements while
    dragging. The actual overshoot distance is calculated by multiplying this value with the
    viewport size of the scrolled object. The factor must be between \c 0 and \c 1.

    \value OvershootScrollDistanceFactor This is the maximum distance for overshoot movements while
    scrolling. The actual overshoot distance is calculated by multiplying this value with the
    viewport size of the scrolled object. The factor must be between \c 0 and \c 1.

    \value OvershootScrollTime This is the time in \c seconds that is used to play the
    complete overshoot animation.

    \value HorizontalOvershootPolicy This is the horizontal overshooting policy (see OvershootPolicy).

    \value VerticalOvershootPolicy This is the horizontal overshooting policy (see OvershootPolicy).

    \value FrameRate This is the frame rate which should be used while dragging or scrolling.
    QExtScroller uses a QAbstractAnimation timer internally to sync all scrolling operations to other
    animations that might be active at the same time.  If the standard value of 60 frames per
    second is too fast, it can be lowered with this setting,
    while still being in-sync with QAbstractAnimation. Please note that only the values of the
    FrameRates enum are allowed here.

    \value ScrollMetricCount This is always the last entry.
*/




/***********************************************************************************************************************
** QExtScroller
***********************************************************************************************************************/
//#define QSCROLLER_DEBUG

#ifdef QSCROLLER_DEBUG
#  define qScrollerDebug  qDebug
#else
#  define qScrollerDebug  while (false) qDebug
#endif

QDebug &operator<<(QDebug &dbg, const QExtScrollerPrivate::ScrollSegment &s)
{
    dbg << "\n  Time: start:" << s.startTime << " duration:" << s.deltaTime << " stop progress:" << s.stopProgress;
    dbg << "\n  Pos: start:" << s.startPos << " delta:" << s.deltaPos << " stop:" << s.stopPos;
    dbg << "\n  Curve: type:" << s.curve.type() << "\n";
    return dbg;
}


// a few helper operators to make the code below a lot more readable:
// otherwise a lot of ifs would have to be multi-line to check both the x
// and y coordinate separately.

// returns true only if the abs. value of BOTH x and y are <= f
inline bool operator<=(const QPointF &p, qreal f)
{
    return (qAbs(p.x()) <= f) && (qAbs(p.y()) <= f);
}

// returns true only if the abs. value of BOTH x and y are < f
inline bool operator<(const QPointF &p, qreal f)
{
    return (qAbs(p.x()) < f) && (qAbs(p.y()) < f);
}

// returns true if the abs. value of EITHER x or y are >= f
inline bool operator>=(const QPointF &p, qreal f)
{
    return (qAbs(p.x()) >= f) || (qAbs(p.y()) >= f);
}

// returns true if the abs. value of EITHER x or y are > f
inline bool operator>(const QPointF &p, qreal f)
{
    return (qAbs(p.x()) > f) || (qAbs(p.y()) > f);
}

// returns a new point with both coordinates having the abs. value of the original one
inline QPointF qAbs(const QPointF &p)
{
    return QPointF(qAbs(p.x()), qAbs(p.y()));
}

// returns a new point with all components of p1 multiplied by the corresponding components of p2
inline QPointF operator*(const QPointF &p1, const QPointF &p2)
{
    return QPointF(p1.x() * p2.x(), p1.y() * p2.y());
}

// returns a new point with all components of p1 divided by the corresponding components of p2
inline QPointF operator/(const QPointF &p1, const QPointF &p2)
{
    return QPointF(p1.x() / p2.x(), p1.y() / p2.y());
}

inline QPointF clampToRect(const QPointF &p, const QRectF &rect)
{
    qreal x = qBound(rect.left(), p.x(), rect.right());
    qreal y = qBound(rect.top(), p.y(), rect.bottom());
    return QPointF(x, y);
}

// returns -1, 0 or +1 according to r being <0, ==0 or >0
inline int qSign(qreal r)
{
    return (r < 0) ? -1 : ((r > 0) ? 1 : 0);
}

// this version is not mathematically exact, but it just works for every
// easing curve type (even custom ones)

static qreal differentialForProgress(const QEasingCurve &curve, qreal pos)
{
    const qreal dx = 0.01;
    qreal left = (pos < qreal(0.5)) ? pos : pos - qreal(dx);
    qreal right = (pos >= qreal(0.5)) ? pos : pos + qreal(dx);
    qreal d = (curve.valueForProgress(right) - curve.valueForProgress(left)) / qreal(dx);

    //qScrollerDebug() << "differentialForProgress(type: " << curve.type() << ", pos: " << pos << ") = " << d;

    return d;
}

// this version is not mathematically exact, but it just works for every
// easing curve type (even custom ones)

static qreal progressForValue(const QEasingCurve &curve, qreal value)
{
    if (curve.type() >= QEasingCurve::InElastic && curve.type() < QEasingCurve::Custom)
    {
        qWarning("progressForValue(): QEasingCurves of type %d do not have an inverse, since they are not injective.", curve.type());
        return value;
    }
    if (value < qreal(0) || value > qreal(1))
    {
        return value;
    }

    qreal progress = value, left(0), right(1);
    for (int iterations = 6; iterations; --iterations)
    {
        qreal v = curve.valueForProgress(progress);
        if (v < value)
        {
            left = progress;
        }
        else if (v > value)
        {
            right = progress;
        }
        else
        {
            break;
        }
        progress = (left + right) / qreal(2);
    }
    return progress;
}


#ifndef QT_NO_ANIMATION
class QScrollTimer : public QAbstractAnimation
{
public:
    QScrollTimer(QExtScrollerPrivate *_d) : QAbstractAnimation(_d), d(_d), ignoreUpdate(false), skip(0) { }

    int duration() const QEXT_OVERRIDE
    {
        return -1;
    }

    void start()
    {
        // QAbstractAnimation::start() will immediately call
        // updateCurrentTime(), but our state is not set correctly yet
        ignoreUpdate = true;
        QAbstractAnimation::start();
        ignoreUpdate = false;
        skip = 0;
    }

protected:
    void updateCurrentTime(int /*currentTime*/) QEXT_OVERRIDE
    {
        if (!ignoreUpdate)
        {
            if (++skip >= d->frameRateSkip())
            {
                skip = 0;
                d->timerTick();
            }
        }
    }

private:
    QExtScrollerPrivate *d;
    bool ignoreUpdate;
    int skip;
};
#endif // QT_NO_ANIMATION

/*!
    \class QExtScroller
    \brief The QExtScroller class enables kinetic scrolling for any scrolling widget or graphics item.
    \since 5.0

    \inmodule QtWidgets

    With kinetic scrolling, the user can push the widget in a given
    direction and it will continue to scroll in this direction until it is
    stopped either by the user or by friction.  Aspects of inertia, friction
    and other physical concepts can be changed in order to fine-tune an
    intuitive user experience.

    The QExtScroller object is the object that stores the current position and
    scrolling speed and takes care of updates.
    QExtScroller can be triggered by a flick gesture

    \code
        QWidget *w = ...;
        QExtScroller::grabGesture(w, QExtScroller::LeftMouseButtonGesture);
    \endcode

    or directly like this:

    \code
        QWidget *w = ...;
        QExtScroller *scroller = QExtScroller::scroller(w);
        scroller->scrollTo(QPointF(100, 100));
    \endcode

    The scrolled QObjects receive a QExtScrollPrepareEvent whenever the scroller needs to
    update its geometry information and a QExtScrollEvent whenever the content of the object should
    actually be scrolled.

    The scroller uses the global QAbstractAnimation timer to generate its QExtScrollEvents. This
    can be changed with QExtScrollerProperties::FrameRate on a per-QExtScroller basis.

    Several examples in the \c scroller examples directory show how QExtScroller,
    QExtScrollEvent and the scroller gesture can be used.

    Even though this kinetic scroller has a large number of settings available via
    QExtScrollerProperties, we recommend that you leave them all at their default, platform optimized
    values. Before changing them you can experiment with the \c plot example in
    the \c scroller examples directory.

    \sa QExtScrollEvent, QExtScrollPrepareEvent, QExtScrollerProperties
*/

typedef QMap<QObject *, QExtScroller *> ScrollerHash;
typedef QSet<QExtScroller *> ScrollerSet;

Q_GLOBAL_STATIC(ScrollerHash, qext_allScrollers)
Q_GLOBAL_STATIC(ScrollerSet, qext_activeScrollers)

/*!
    Returns \c true if a QExtScroller object was already created for \a target; \c false otherwise.

    \sa scroller()
*/
bool QExtScroller::hasScroller(QObject *target)
{
    return (qext_allScrollers()->value(target));
}

/*!
    Returns the scroller for the given \a target.
    As long as the object exists this function will always return the same QExtScroller instance.
    If no QExtScroller exists for the \a target, one will implicitly be created.
    At no point more than one QExtScroller will be active on an object.

    \sa hasScroller(), target()
*/
QExtScroller *QExtScroller::scroller(QObject *target)
{
    if (!target)
    {
        qWarning("QExtScroller::scroller() was called with a null target.");
        return 0;
    }

    if (qext_allScrollers()->contains(target))
    {
        return qext_allScrollers()->value(target);
    }

    QExtScroller *s = new QExtScroller(target);
    qext_allScrollers()->insert(target, s);
    return s;
}

/*!
    \overload
    This is the const version of scroller().
*/
const QExtScroller *QExtScroller::scroller(const QObject *target)
{
    return scroller(const_cast<QObject*>(target));
}

/*!
    Returns an application wide list of currently active QExtScroller objects.
    Active QExtScroller objects are in a state() that is not QExtScroller::Inactive.
    This function is useful when writing your own gesture recognizer.
*/
QList<QExtScroller *> QExtScroller::activeScrollers()
{
    return qext_activeScrollers()->toList();
}

/*!
    Returns the target object of this scroller.
    \sa hasScroller(), scroller()
 */
QObject *QExtScroller::target() const
{
    Q_D(const QExtScroller);
    return d->m_target;
}

/*!
    \fn QExtScroller::scrollerPropertiesChanged(const QExtScrollerProperties &newProperties);

    QExtScroller emits this signal whenever its scroller properties change.
    \a newProperties are the new scroller properties.

    \sa scrollerProperties
*/


/*! \property QExtScroller::scrollerProperties
    \brief The scroller properties of this scroller.
    The properties are used by the QExtScroller to determine its scrolling behavior.
*/
QExtScrollerProperties QExtScroller::scrollerProperties() const
{
    Q_D(const QExtScroller);
    return d->m_properties;
}

void QExtScroller::setScrollerProperties(const QExtScrollerProperties &sp)
{
    Q_D(QExtScroller);
    if (d->m_properties != sp)
    {
        d->m_properties = sp;
        emit scrollerPropertiesChanged(sp);

        // we need to force the recalculation here, since the overshootPolicy may have changed and
        // existing segments may include an overshoot animation.
        d->recalcScrollingSegments(true);
    }
}

#ifndef QT_NO_GESTURES

/*!
    Registers a custom scroll gesture recognizer, grabs it for the \a
    target and returns the resulting gesture type.  If \a scrollGestureType is
    set to TouchGesture the gesture triggers on touch events. If it is set to
    one of LeftMouseButtonGesture, RightMouseButtonGesture or
    MiddleMouseButtonGesture it triggers on mouse events of the
    corresponding button.

    Only one scroll gesture can be active on a single object at the same
    time. If you call this function twice on the same object, it will
    ungrab the existing gesture before grabbing the new one.

    \note To avoid unwanted side-effects, mouse events are consumed while
    the gesture is triggered. Since the initial mouse press event is
    not consumed, the gesture sends a fake mouse release event
    at the global position \c{(INT_MIN, INT_MIN)}. This ensures that
    internal states of the widget that received the original mouse press
    are consistent.

    \sa ungrabGesture(), grabbedGesture()
*/
Qt::GestureType QExtScroller::grabGesture(QObject *target, ScrollerGestureType scrollGestureType)
{
    // ensure that a scroller for target is created
    QExtScroller *s = scroller(target);
    if (!s)
    {
        return Qt::GestureType(0);
    }

    QExtScrollerPrivate *sp = s->d_ptr;
    if (sp->m_recognizer)
    {
        QExtScroller::ungrabGesture(target); // ungrab the old gesture
    }

    Qt::MouseButton button;
    switch (scrollGestureType)
    {
    case LeftMouseButtonGesture  : button = Qt::LeftButton; break;
    case RightMouseButtonGesture : button = Qt::RightButton; break;
    case MiddleMouseButtonGesture: button = Qt::MiddleButton; break;
    default                      :
    case TouchGesture            : button = Qt::NoButton; break; // NoButton == Touch
    }

    sp->m_recognizer = new QExtFlickGestureRecognizer(button);
    sp->m_recognizerType = QGestureRecognizer::registerRecognizer(sp->m_recognizer);

    if (target->isWidgetType())
    {
        QWidget *widget = static_cast<QWidget *>(target);
        widget->grabGesture(sp->m_recognizerType);
        if (scrollGestureType == TouchGesture)
        {
            widget->setAttribute(Qt::WA_AcceptTouchEvents);
        }
#ifndef QT_NO_GRAPHICSVIEW
    }
    else if (QGraphicsObject *go = qobject_cast<QGraphicsObject*>(target))
    {
        if (scrollGestureType == TouchGesture)
        {
            go->setAcceptTouchEvents(true);
        }
        go->grabGesture(sp->m_recognizerType);
#endif // QT_NO_GRAPHICSVIEW
    }
    return sp->m_recognizerType;
}

/*!
    Returns the gesture type currently grabbed for the \a target or 0 if no
    gesture is grabbed.

    \sa grabGesture(), ungrabGesture()
*/
Qt::GestureType QExtScroller::grabbedGesture(QObject *target)
{
    QExtScroller *s = scroller(target);
    if (s && s->d_ptr)
    {
        return s->d_ptr->m_recognizerType;
    }
    else
    {
        return Qt::GestureType(0);
    }
}

/*!
    Ungrabs the gesture for the \a target.
    Does nothing if no gesture is grabbed.

    \sa grabGesture(), grabbedGesture()
*/
void QExtScroller::ungrabGesture(QObject *target)
{
    QExtScroller *s = scroller(target);
    if (!s)
    {
        return;
    }

    QExtScrollerPrivate *sp = s->d_ptr;
    if (!sp->m_recognizer)
    {
        return; // nothing to do
    }

    if (target->isWidgetType())
    {
        QWidget *widget = static_cast<QWidget *>(target);
        widget->ungrabGesture(sp->m_recognizerType);
#ifndef QT_NO_GRAPHICSVIEW
    }
    else if (QGraphicsObject *go = qobject_cast<QGraphicsObject*>(target))
    {
        go->ungrabGesture(sp->m_recognizerType);
#endif
    }

    QGestureRecognizer::unregisterRecognizer(sp->m_recognizerType);
    // do not delete the recognizer. The QGestureManager is doing this.
    sp->m_recognizer = 0;
}

#endif // QT_NO_GESTURES

/*!
    \internal
*/
QExtScroller::QExtScroller(QObject *target)
    : d_ptr(new QExtScrollerPrivate(this, target))
{
    Q_ASSERT(target); // you can't create a scroller without a target in any normal way
    Q_D(QExtScroller);
    d->init();
}

/*!
    \internal
*/
QExtScroller::~QExtScroller()
{
    Q_D(QExtScroller);
#ifndef QT_NO_GESTURES
    QGestureRecognizer::unregisterRecognizer(d->m_recognizerType);
    // do not delete the recognizer. The QGestureManager is doing this.
    d->m_recognizer = 0;
#endif
    qext_allScrollers()->remove(d->m_target);
    qext_activeScrollers()->remove(this);

    delete d_ptr;
}


/*!
    \fn QExtScroller::stateChanged(QExtScroller::State newState);

    QExtScroller emits this signal whenever the state changes. \a newState is the new State.

    \sa state
*/

/*!
    \property QExtScroller::state
    \brief the state of the scroller

    \sa QExtScroller::State
*/
QExtScroller::State QExtScroller::state() const
{
    Q_D(const QExtScroller);
    return d->m_state;
}

/*!
    Stops the scroller and resets its state back to Inactive.
*/
void QExtScroller::stop()
{
    Q_D(QExtScroller);
    if (d->m_state != Inactive)
    {
        QPointF here = clampToRect(d->m_contentPosition, d->m_contentPosRange);
        qreal snapX = d->nextSnapPos(here.x(), 0, Qt::Horizontal);
        qreal snapY = d->nextSnapPos(here.y(), 0, Qt::Vertical);
        QPointF snap = here;
        if (!qIsNaN(snapX))
        {
            snap.setX(snapX);
        }
        if (!qIsNaN(snapY))
        {
            snap.setY(snapY);
        }
        d->m_contentPosition = snap;
        d->m_overshootPosition = QPointF(0, 0);

        d->setState(Inactive);
    }
}

/*!
    Returns the pixel per meter metric for the scrolled widget.

    The value is reported for both the x and y axis separately by using a QPointF.

    \note Please note that this value should be physically correct. The actual DPI settings
    that Qt returns for the display may be reported wrongly on purpose by the underlying
    windowing system, for example on \macos.
*/
QPointF QExtScroller::pixelPerMeter() const
{
    Q_D(const QExtScroller);
    QPointF ppm = d->m_pixelPerMeter;

#ifndef QT_NO_GRAPHICSVIEW
    if (QGraphicsObject *go = qobject_cast<QGraphicsObject *>(d->m_target))
    {
        QTransform viewtr;
        //TODO: the first view isn't really correct - maybe use an additional field in the prepare event?
        if (go->scene() && !go->scene()->views().isEmpty())
        {
            viewtr = go->scene()->views().first()->viewportTransform();
        }
        QTransform tr = go->deviceTransform(viewtr);
        if (tr.isScaling())
        {
            QPointF p0 = tr.map(QPointF(0, 0));
            QPointF px = tr.map(QPointF(1, 0));
            QPointF py = tr.map(QPointF(0, 1));
            ppm.rx() /= QLineF(p0, px).length();
            ppm.ry() /= QLineF(p0, py).length();
        }
    }
#endif // QT_NO_GRAPHICSVIEW
    return ppm;
}

/*!
    Returns the current scrolling velocity in meter per second when the state is Scrolling or Dragging.
    Returns a zero velocity otherwise.

    The velocity is reported for both the x and y axis separately by using a QPointF.

    \sa pixelPerMeter()
*/
QPointF QExtScroller::velocity() const
{
    Q_D(const QExtScroller);
    const QExtScrollerPropertiesPrivate *sp = d->m_properties.dd_ptr.data();

    switch (state())
    {
    case Dragging:
        return d->m_releaseVelocity;
    case Scrolling:
    {
        QPointF vel;
        qint64 now = d->m_monotonicTimer.elapsed();

        if (!d->m_xSegments.isEmpty())
        {
            const QExtScrollerPrivate::ScrollSegment &s = d->m_xSegments.head();
            qreal progress = qreal(now - s.startTime) / qreal(s.deltaTime);
            qreal v = qSign(s.deltaPos) * qreal(s.deltaTime) / qreal(1000) * sp->m_decelerationFactor * qreal(0.5) *
                      differentialForProgress(s.curve, progress);
            vel.setX(v);
        }

        if (!d->m_ySegments.isEmpty())
        {
            const QExtScrollerPrivate::ScrollSegment &s = d->m_ySegments.head();
            qreal progress = qreal(now - s.startTime) / qreal(s.deltaTime);
            qreal v = qSign(s.deltaPos) * qreal(s.deltaTime) / qreal(1000) * sp->m_decelerationFactor * qreal(0.5) *
                      differentialForProgress(s.curve, progress);
            vel.setY(v);
        }
        return vel;
    }
    default:
        return QPointF(0, 0);
    }
}

/*!
    Returns the estimated final position for the current scroll movement.
    Returns the current position if the scroller state is not Scrolling.
    The result is undefined when the scroller state is Inactive.

    The target position is in pixel.

    \sa pixelPerMeter(), scrollTo()
*/
QPointF QExtScroller::finalPosition() const
{
    Q_D(const QExtScroller);
    return QPointF(d->scrollingSegmentsEndPos(Qt::Horizontal), d->scrollingSegmentsEndPos(Qt::Vertical));
}

/*!
    Starts scrolling the widget so that point \a pos is at the top-left position in
    the viewport.

    The behaviour when scrolling outside the valid scroll area is undefined.
    In this case the scroller might or might not overshoot.

    The scrolling speed will be calculated so that the given position will
    be reached after a platform-defined time span.

    \a pos is given in viewport coordinates.

    \sa ensureVisible()
*/
void QExtScroller::scrollTo(const QPointF &pos)
{
    // we could make this adjustable via QExtScrollerProperties
    scrollTo(pos, 300);
}

/*! \overload

    This version will reach its destination position in \a scrollTime milliseconds.
*/
void QExtScroller::scrollTo(const QPointF &pos, int scrollTime)
{
    Q_D(QExtScroller);

    if (d->m_state == Pressed || d->m_state == Dragging )
    {
        return;
    }

    // no need to resend a prepare event if we are already scrolling
    if (d->m_state == Inactive && !d->prepareScrolling(QPointF()))
    {
        return;
    }

    QPointF newpos = clampToRect(pos, d->m_contentPosRange);
    qreal snapX = d->nextSnapPos(newpos.x(), 0, Qt::Horizontal);
    qreal snapY = d->nextSnapPos(newpos.y(), 0, Qt::Vertical);
    if (!qIsNaN(snapX))
    {
        newpos.setX(snapX);
    }
    if (!qIsNaN(snapY))
    {
        newpos.setY(snapY);
    }

    qScrollerDebug() << "QExtScroller::scrollTo(req:" << pos << " [pix] / snap:" << newpos << ", " << scrollTime << " [ms])";

    if (newpos == d->m_contentPosition + d->m_overshootPosition)
    {
        return;
    }

    QPointF vel = velocity();

    if (scrollTime < 0)
    {
        scrollTime = 0;
    }
    qreal time = qreal(scrollTime) / 1000;

    d->createScrollToSegments(vel.x(), time, newpos.x(), Qt::Horizontal, QExtScrollerPrivate::ScrollTypeScrollTo);
    d->createScrollToSegments(vel.y(), time, newpos.y(), Qt::Vertical, QExtScrollerPrivate::ScrollTypeScrollTo);

    if (!scrollTime)
    {
        d->setContentPositionHelperScrolling();
    }
    d->setState(scrollTime ? Scrolling : Inactive);
}

/*!
    Starts scrolling so that the rectangle \a rect is visible inside the
    viewport with additional margins specified in pixels by \a xmargin and \a ymargin around
    the rect.

    In cases where it is not possible to fit the rect plus margins inside the viewport the contents
    are scrolled so that as much as possible is visible from \a rect.

    The scrolling speed is calculated so that the given position is reached after a platform-defined
    time span.

    This function performs the actual scrolling by calling scrollTo().

    \sa scrollTo()
*/
void QExtScroller::ensureVisible(const QRectF &rect, qreal xmargin, qreal ymargin)
{
    // we could make this adjustable via QExtScrollerProperties
    ensureVisible(rect, xmargin, ymargin, 1000);
}

/*! \overload

    This version will reach its destination position in \a scrollTime milliseconds.
*/
void QExtScroller::ensureVisible(const QRectF &rect, qreal xmargin, qreal ymargin, int scrollTime)
{
    Q_D(QExtScroller);

    if (d->m_state == Pressed || d->m_state == Dragging )
        return;

    if (d->m_state == Inactive && !d->prepareScrolling(QPointF()))
        return;

    // -- calculate the current pos (or the position after the current scroll)
    QPointF startPos(d->scrollingSegmentsEndPos(Qt::Horizontal), d->scrollingSegmentsEndPos(Qt::Vertical));

    QRectF marginRect(rect.x() - xmargin, rect.y() - ymargin,
                      rect.width() + 2 * xmargin, rect.height() + 2 * ymargin);

    QSizeF visible = d->m_viewportSize;
    QRectF visibleRect(startPos, visible);

    qScrollerDebug() << "QExtScroller::ensureVisible(" << rect << " [pix], "
                     << xmargin << " [pix], " << ymargin << " [pix], " << scrollTime << "[ms])";
    qScrollerDebug() << "  --> content position:" << d->m_contentPosition;

    if (visibleRect.contains(marginRect))
    {
        return;
    }

    QPointF newPos = startPos;

    if (visibleRect.width() < rect.width())
    {
        // at least try to move the rect into view
        if (rect.left() > visibleRect.left())
        {
            newPos.setX(rect.left());
        }
        else if (rect.right() < visibleRect.right())
        {
            newPos.setX(rect.right() - visible.width());
        }

    }
    else if (visibleRect.width() < marginRect.width())
    {
        newPos.setX(rect.center().x() - visibleRect.width() / 2);
    }
    else if (marginRect.left() > visibleRect.left())
    {
        newPos.setX(marginRect.left());
    }
    else if (marginRect.right() < visibleRect.right())
    {
        newPos.setX(marginRect.right() - visible.width());
    }

    if (visibleRect.height() < rect.height())
    {
        // at least try to move the rect into view
        if (rect.top() > visibleRect.top())
        {
            newPos.setX(rect.top());
        }
        else if (rect.bottom() < visibleRect.bottom())
        {
            newPos.setX(rect.bottom() - visible.height());
        }

    }
    else if (visibleRect.height() < marginRect.height())
    {
        newPos.setY(rect.center().y() - visibleRect.height() / 2);
    }
    else if (marginRect.top() > visibleRect.top())
    {
        newPos.setY(marginRect.top());
    }
    else if (marginRect.bottom() < visibleRect.bottom())
    {
        newPos.setY(marginRect.bottom() - visible.height());
    }

    // clamp to maximum content position
    newPos = clampToRect(newPos, d->m_contentPosRange);
    if (newPos == startPos)
    {
        return;
    }

    this->scrollTo(newPos, scrollTime);
}

/*! This function resends the QExtScrollPrepareEvent.
    Calling resendPrepareEvent triggers a QExtScrollPrepareEvent from the scroller.
    This allows the receiver to re-set content position and content size while
    scrolling.
    Calling this function while in the Inactive state is useless as the prepare event
    is sent again before scrolling starts.
 */
void QExtScroller::resendPrepareEvent()
{
    Q_D(QExtScroller);
    d->prepareScrolling(d->m_pressPosition);
}

/*! Set the snap positions for the horizontal axis to a list of \a positions.
    This overwrites all previously set snap positions and also a previously
    set snapping interval.
    Snapping can be deactivated by setting an empty list of positions.
 */
void QExtScroller::setSnapPositionsX(const QList<qreal> &positions)
{
    Q_D(QExtScroller);
    d->m_snapPositionsX = positions;
    d->m_snapIntervalX = 0.0;

    d->recalcScrollingSegments();
}

/*! Set the snap positions for the horizontal axis to regular spaced intervals.
    The first snap position is at \a first. The next at \a first + \a interval.
    This can be used to implement a list header.
    This overwrites all previously set snap positions and also a previously
    set snapping interval.
    Snapping can be deactivated by setting an interval of 0.0
 */
void QExtScroller::setSnapPositionsX(qreal first, qreal interval)
{
    Q_D(QExtScroller);
    d->m_snapFirstX = first;
    d->m_snapIntervalX = interval;
    d->m_snapPositionsX.clear();

    d->recalcScrollingSegments();
}

/*! Set the snap positions for the vertical axis to a list of \a positions.
    This overwrites all previously set snap positions and also a previously
    set snapping interval.
    Snapping can be deactivated by setting an empty list of positions.
 */
void QExtScroller::setSnapPositionsY(const QList<qreal> &positions)
{
    Q_D(QExtScroller);
    d->m_snapPositionsY = positions;
    d->m_snapIntervalY = 0.0;

    d->recalcScrollingSegments();
}

/*! Set the snap positions for the vertical axis to regular spaced intervals.
    The first snap position is at \a first. The next at \a first + \a interval.
    This overwrites all previously set snap positions and also a previously
    set snapping interval.
    Snapping can be deactivated by setting an interval of 0.0
 */
void QExtScroller::setSnapPositionsY(qreal first, qreal interval)
{
    Q_D(QExtScroller);
    d->m_snapFirstY = first;
    d->m_snapIntervalY = interval;
    d->m_snapPositionsY.clear();

    d->recalcScrollingSegments();
}



// -------------- private ------------

QExtScrollerPrivate::QExtScrollerPrivate(QExtScroller *q, QObject *_target)
    : m_target(_target)
#ifndef QT_NO_GESTURES
    , m_recognizer(0)
    , m_recognizerType(Qt::CustomGesture)
#endif
    , m_state(QExtScroller::Inactive)
    , m_firstScroll(true)
    , m_pressTimestamp(0)
    , m_lastTimestamp(0)
    , m_snapFirstX(-1.0)
    , m_snapIntervalX(0.0)
    , m_snapFirstY(-1.0)
    , m_snapIntervalY(0.0)
#ifndef QT_NO_ANIMATION
    , m_scrollTimer(new QScrollTimer(this))
#endif
    , q_ptr(q)
{
    connect(m_target, SIGNAL(destroyed(QObject*)), this, SLOT(targetDestroyed()));
}

void QExtScrollerPrivate::init()
{
    setDpiFromWidget(0);
    m_monotonicTimer.start();
}

void QExtScrollerPrivate::sendEvent(QObject *o, QEvent *e)
{
    qt_sendSpontaneousEvent(o, e);
}

const char *QExtScrollerPrivate::stateName(QExtScroller::State state)
{
    switch (state)
    {
    case QExtScroller::Inactive:  return "inactive";
    case QExtScroller::Pressed:   return "pressed";
    case QExtScroller::Dragging:  return "dragging";
    case QExtScroller::Scrolling: return "scrolling";
    default:                   return "(invalid)";
    }
}

const char *QExtScrollerPrivate::inputName(QExtScroller::Input input)
{
    switch (input) {
    case QExtScroller::InputPress:   return "press";
    case QExtScroller::InputMove:    return "move";
    case QExtScroller::InputRelease: return "release";
    default:                      return "(invalid)";
    }
}

void QExtScrollerPrivate::targetDestroyed()
{
#ifndef QT_NO_ANIMATION
    m_scrollTimer->stop();
#endif
    delete q_ptr;
}

void QExtScrollerPrivate::timerTick()
{
    struct timerevent
    {
        QExtScroller::State state;
        typedef void (QExtScrollerPrivate::*timerhandler_t)();
        timerhandler_t handler;
    };

    timerevent timerevents[] =
        {
         { QExtScroller::Dragging, &QExtScrollerPrivate::timerEventWhileDragging },
         { QExtScroller::Scrolling, &QExtScrollerPrivate::timerEventWhileScrolling },
         };

    for (int i = 0; i < int(sizeof(timerevents) / sizeof(*timerevents)); ++i)
    {
        timerevent *te = timerevents + i;

        if (m_state == te->state)
        {
            (this->*te->handler)();
            return;
        }
    }

#ifndef QT_NO_ANIMATION
    m_scrollTimer->stop();
#endif
}

/*!
    This function is used by gesture recognizers to inform the scroller about a new input event.
    The scroller changes its internal state() according to the input event and its attached
    scroller properties. The scroller doesn't distinguish between the kind of input device the
    event came from. Therefore the event needs to be split into the \a input type, a \a position and a
    milli-second \a timestamp.  The \a position needs to be in the target's coordinate system.

    The return value is \c true if the event should be consumed by the calling filter or \c false
    if the event should be forwarded to the control.

    \note Using grabGesture() should be sufficient for most use cases.
*/
bool QExtScroller::handleInput(Input input, const QPointF &position, qint64 timestamp)
{
    Q_D(QExtScroller);

    qScrollerDebug() << "QExtScroller::handleInput(" << input << ", " << d->stateName(d->m_state) << ", "
                     << position << ", " << timestamp << ')';
    struct statechange
    {
        State state;
        Input input;
        typedef bool (QExtScrollerPrivate::*inputhandler_t)(const QPointF &position, qint64 timestamp);
        inputhandler_t handler;
    };

    statechange statechanges[] =
        {
            { QExtScroller::Inactive,  InputPress,   &QExtScrollerPrivate::pressWhileInactive },
            { QExtScroller::Pressed,   InputMove,    &QExtScrollerPrivate::moveWhilePressed },
            { QExtScroller::Pressed,   InputRelease, &QExtScrollerPrivate::releaseWhilePressed },
            { QExtScroller::Dragging,  InputMove,    &QExtScrollerPrivate::moveWhileDragging },
            { QExtScroller::Dragging,  InputRelease, &QExtScrollerPrivate::releaseWhileDragging },
            { QExtScroller::Scrolling, InputPress,   &QExtScrollerPrivate::pressWhileScrolling }
        };

    for (int i = 0; i < int(sizeof(statechanges) / sizeof(*statechanges)); ++i)
    {
        statechange *sc = statechanges + i;

        if (d->m_state == sc->state && input == sc->input)
        {
            return (d->*sc->handler)(position - d->m_overshootPosition, timestamp);
        }
    }
    return false;
}

#if !defined(Q_DEAD_CODE_FROM_QT4_MAC)
// the Mac version is implemented in qscroller_mac.mm

QPointF QExtScrollerPrivate::realDpi(int screen)
{
#  if defined(Q_DEAD_CODE_FROM_QT4_X11) && !defined(QT_NO_XRANDR)
    if (X11 && X11->use_xrandr && X11->ptrXRRSizes && X11->ptrXRRRootToScreen)
    {
        int nsizes = 0;
        // QDesktopWidget is based on Xinerama screens, which do not always
        // correspond to RandR screens: NVidia's TwinView e.g.  will show up
        // as 2 screens in QDesktopWidget, but libXRandR will only see 1 screen.
        // (although with the combined size of the Xinerama screens).
        // Additionally, libXrandr will simply crash when calling XRRSizes
        // for (the non-existent) screen 1 in this scenario.
        Window root =  RootWindow(X11->display, screen == -1 ? X11->defaultScreen : screen);
        int randrscreen = (root != XNone) ? X11->ptrXRRRootToScreen(X11->display, root) : -1;

        XRRScreenSize *sizes = X11->ptrXRRSizes(X11->display, randrscreen == -1 ? 0 : randrscreen, &nsizes);
        if (nsizes > 0 && sizes && sizes->width && sizes->height && sizes->mwidth && sizes->mheight)
        {
            qScrollerDebug() << "XRandR DPI:" << QPointF(qreal(25.4) * qreal(sizes->width) / qreal(sizes->mwidth),
                                                         qreal(25.4) * qreal(sizes->height) / qreal(sizes->mheight));
            return QPointF(qreal(25.4) * qreal(sizes->width) / qreal(sizes->mwidth),
                           qreal(25.4) * qreal(sizes->height) / qreal(sizes->mheight));
        }
    }
#  endif

    QWidget *w = QApplication::desktop()->screen(screen);
    return QPointF(w->physicalDpiX(), w->physicalDpiY());
}

#endif // !Q_DEAD_CODE_FROM_QT4_MAC


/*! \internal
    Returns the resolution of the used screen.
*/
QPointF QExtScrollerPrivate::dpi() const
{
    return m_pixelPerMeter * qreal(0.0254);
}

/*! \internal
    Sets the resolution used for scrolling.
    This resolution is only used by the kinetic scroller. If you change this
    then the scroller will behave quite different as a lot of the values are
    given in physical distances (millimeter).
*/
void QExtScrollerPrivate::setDpi(const QPointF &dpi)
{
    m_pixelPerMeter = dpi / qreal(0.0254);
}

/*! \internal
    Sets the dpi used for scrolling to the value of the widget.
*/
void QExtScrollerPrivate::setDpiFromWidget(QWidget *widget)
{
    QDesktopWidget *dw = QApplication::desktop();
    setDpi(realDpi(widget ? dw->screenNumber(widget) : dw->primaryScreen()));
}

/*! \internal
    Updates the velocity during dragging.
    Sets releaseVelocity.
*/
void QExtScrollerPrivate::updateVelocity(const QPointF &deltaPixelRaw, qint64 deltaTime)
{
    if (deltaTime <= 0)
    {
        return;
    }

    Q_Q(QExtScroller);
    QPointF ppm = q->pixelPerMeter();
    const QExtScrollerPropertiesPrivate *sp = m_properties.dd_ptr.data();
    QPointF deltaPixel = deltaPixelRaw;

    qScrollerDebug() << "QExtScroller::updateVelocity(" << deltaPixelRaw << " [delta pix], " << deltaTime << " [delta ms])";

    // faster than 2.5mm/ms seems bogus (that would be a screen height in ~20 ms)
    if (((deltaPixelRaw / qreal(deltaTime)).manhattanLength() / ((ppm.x() + ppm.y()) / 2) * 1000) > qreal(2.5))
    {
        deltaPixel = deltaPixelRaw * qreal(2.5) * ppm / 1000 / (deltaPixelRaw / qreal(deltaTime)).manhattanLength();
    }

    QPointF newv = -deltaPixel / qreal(deltaTime) * qreal(1000) / ppm;
    // around 95% of all updates are in the [1..50] ms range, so make sure
    // to scale the smoothing factor over that range: this way a 50ms update
    // will have full impact, while 5ms update will only have a 10% impact.
    qreal smoothing = sp->m_dragVelocitySmoothingFactor * qMin(qreal(deltaTime), qreal(50)) / qreal(50);

    // only smooth if we already have a release velocity and only if the
    // user hasn't stopped to move his finger for more than 100ms
    if ((m_releaseVelocity != QPointF(0, 0)) && (deltaTime < 100))
    {
        qScrollerDebug() << "SMOOTHED from " << newv << " to " << newv * smoothing + m_releaseVelocity * (qreal(1) - smoothing);
        // smooth x or y only if the new velocity is either 0 or at least in
        // the same direction of the release velocity
        if (!newv.x() || (qSign(m_releaseVelocity.x()) == qSign(newv.x())))
        {
            newv.setX(newv.x() * smoothing + m_releaseVelocity.x() * (qreal(1) - smoothing));
        }
        if (!newv.y() || (qSign(m_releaseVelocity.y()) == qSign(newv.y())))
        {
            newv.setY(newv.y() * smoothing + m_releaseVelocity.y() * (qreal(1) - smoothing));
        }
    }
    else
    {
        qScrollerDebug() << "NO SMOOTHING to " << newv;
    }

    m_releaseVelocity.setX(qBound(-sp->m_maximumVelocity, newv.x(), sp->m_maximumVelocity));
    m_releaseVelocity.setY(qBound(-sp->m_maximumVelocity, newv.y(), sp->m_maximumVelocity));

    qScrollerDebug() << "  --> new velocity:" << m_releaseVelocity;
}

void QExtScrollerPrivate::pushSegment(ScrollType type, qreal deltaTime, qreal stopProgress, qreal startPos,
                                      qreal deltaPos, qreal stopPos, QEasingCurve::Type curve,
                                      Qt::Orientation orientation)
{
    if (startPos == stopPos || deltaPos == 0)
    {
        return;
    }

    ScrollSegment s;
    if (orientation == Qt::Horizontal && !m_xSegments.isEmpty())
    {
        s.startTime = m_xSegments.last().startTime + m_xSegments.last().deltaTime * m_xSegments.last().stopProgress;
    }
    else if (orientation == Qt::Vertical && !m_ySegments.isEmpty())
    {
        s.startTime = m_ySegments.last().startTime + m_ySegments.last().deltaTime * m_ySegments.last().stopProgress;
    }
    else
    {
        s.startTime = m_monotonicTimer.elapsed();
    }

    s.startPos = startPos;
    s.deltaPos = deltaPos;
    s.stopPos = stopPos;
    s.deltaTime = deltaTime * 1000;
    s.stopProgress = stopProgress;
    s.curve.setType(curve);
    s.type = type;

    if (orientation == Qt::Horizontal)
    {
        m_xSegments.enqueue(s);
    }
    else
    {
        m_ySegments.enqueue(s);
    }

    qScrollerDebug() << "+++ Added a new ScrollSegment: " << s;
}


/*! \internal
    Clears the old segments and recalculates them if the current segments are not longer valid
*/
void QExtScrollerPrivate::recalcScrollingSegments(bool forceRecalc)
{
    Q_Q(QExtScroller);
    QPointF ppm = q->pixelPerMeter();

    m_releaseVelocity = q->velocity();

    if (forceRecalc || !scrollingSegmentsValid(Qt::Horizontal) || !scrollingSegmentsValid(Qt::Vertical))
    {
        this->createScrollingSegments(m_releaseVelocity, m_contentPosition + m_overshootPosition, ppm);
    }
}

/*! \internal
    Returns the end position after the current scroll has finished.
*/
qreal QExtScrollerPrivate::scrollingSegmentsEndPos(Qt::Orientation orientation) const
{
    if (orientation == Qt::Horizontal)
    {
        if (m_xSegments.isEmpty())
        {
            return m_contentPosition.x() + m_overshootPosition.x();
        }
        else
        {
            return m_xSegments.last().stopPos;
        }
    }
    else
    {
        if (m_ySegments.isEmpty())
        {
            return m_contentPosition.y() + m_overshootPosition.y();
        }
        else
        {
            return m_ySegments.last().stopPos;
        }
    }
}

/*! \internal
    Checks if the scroller segment end in a valid position.
*/
bool QExtScrollerPrivate::scrollingSegmentsValid(Qt::Orientation orientation)
{
    QQueue<ScrollSegment> *segments;
    qreal minPos;
    qreal maxPos;

    if (orientation == Qt::Horizontal)
    {
        segments = &m_xSegments;
        minPos = m_contentPosRange.left();
        maxPos = m_contentPosRange.right();
    }
    else
    {
        segments = &m_ySegments;
        minPos = m_contentPosRange.top();
        maxPos = m_contentPosRange.bottom();
    }

    if (segments->isEmpty())
    {
        return true;
    }

    const ScrollSegment &last = segments->last();
    qreal stopPos = last.stopPos;

    if (last.type == ScrollTypeScrollTo)
    {
        return true; // scrollTo is always valid
    }

    if (last.type == ScrollTypeOvershoot && (stopPos != minPos && stopPos != maxPos))
    {
        return false;
    }

    if (stopPos < minPos || stopPos > maxPos)
    {
        return false;
    }

    if (stopPos == minPos || stopPos == maxPos) // the begin and the end of the list are always ok
    {
        return true;
    }

    qreal nextSnap = nextSnapPos(stopPos, 0, orientation);
    if (!qIsNaN(nextSnap) && stopPos != nextSnap)
    {
        return false;
    }

    return true;
}

/*! \internal
   Creates the sections needed to scroll to the specific \a endPos to the segments queue.
*/
void QExtScrollerPrivate::createScrollToSegments(qreal v, qreal deltaTime, qreal endPos, Qt::Orientation orientation, ScrollType type)
{
    Q_UNUSED(v);

    if (orientation == Qt::Horizontal)
    {
        m_xSegments.clear();
    }
    else
    {
        m_ySegments.clear();
    }

    qScrollerDebug() << "+++ createScrollToSegments: t:" << deltaTime << "ep:" << endPos << "o:" << int(orientation);

    const QExtScrollerPropertiesPrivate *sp = m_properties.dd_ptr.data();

    qreal startPos = (orientation == Qt::Horizontal) ? m_contentPosition.x() + m_overshootPosition.x()
                                                     : m_contentPosition.y() + m_overshootPosition.y();
    qreal deltaPos = (endPos - startPos) / 2;

    pushSegment(type, deltaTime * qreal(0.3), qreal(1.0), startPos, deltaPos, startPos + deltaPos, QEasingCurve::InQuad, orientation);
    pushSegment(type, deltaTime * qreal(0.7), qreal(1.0), startPos + deltaPos, deltaPos, endPos, sp->m_scrollingCurve.type(), orientation);
}

/*! \internal
*/
void QExtScrollerPrivate::createScrollingSegments(qreal v, qreal startPos,
                                                  qreal deltaTime, qreal deltaPos,
                                                  Qt::Orientation orientation)
{
    const QExtScrollerPropertiesPrivate *sp = m_properties.dd_ptr.data();

    QExtScrollerProperties::OvershootPolicy policy;
    qreal minPos;
    qreal maxPos;
    qreal viewSize;

    if (orientation == Qt::Horizontal)
    {
        m_xSegments.clear();
        policy = sp->m_hOvershootPolicy;
        minPos = m_contentPosRange.left();
        maxPos = m_contentPosRange.right();
        viewSize = m_viewportSize.width();
    }
    else
    {
        m_ySegments.clear();
        policy = sp->m_vOvershootPolicy;
        minPos = m_contentPosRange.top();
        maxPos = m_contentPosRange.bottom();
        viewSize = m_viewportSize.height();
    }

    bool alwaysOvershoot = (policy == QExtScrollerProperties::OvershootAlwaysOn);
    bool noOvershoot = (policy == QExtScrollerProperties::OvershootAlwaysOff) || !sp->m_overshootScrollDistanceFactor;
    bool canOvershoot = !noOvershoot && (alwaysOvershoot || maxPos);

    qScrollerDebug() << "+++ createScrollingSegments: s:" << startPos << "maxPos:" << maxPos << "o:" << int(orientation);

    qScrollerDebug() << "v = " << v << ", decelerationFactor = " << sp->m_decelerationFactor
                     << ", curveType = " << sp->m_scrollingCurve.type();

    qreal endPos = startPos + deltaPos;

    qScrollerDebug() << "  Real Delta:" << deltaPos;

    // -- check if are in overshoot and end in overshoot
    if ((startPos < minPos && endPos < minPos) || (startPos > maxPos && endPos > maxPos))
    {
        qreal stopPos = endPos < minPos ? minPos : maxPos;
        qreal oDeltaTime = sp->m_overshootScrollTime;

        pushSegment(ScrollTypeOvershoot, oDeltaTime * qreal(0.7), qreal(1.0), startPos, stopPos - startPos, stopPos,
                    sp->m_scrollingCurve.type(), orientation);
        return;
    }

    // -- determine snap points
    qreal nextSnap = nextSnapPos(endPos, 0, orientation);
    qreal lowerSnapPos = nextSnapPos(startPos, -1, orientation);
    qreal higherSnapPos = nextSnapPos(startPos, 1, orientation);

    qScrollerDebug() << "  Real Delta:" << lowerSnapPos << '-' << nextSnap << '-' <<higherSnapPos;

    // - check if we can reach another snap point
    if (nextSnap > higherSnapPos || qIsNaN(higherSnapPos))
    {
        higherSnapPos = nextSnap;
    }
    if (nextSnap < lowerSnapPos || qIsNaN(lowerSnapPos))
    {
        lowerSnapPos = nextSnap;
    }

    if (qAbs(v) < sp->m_minimumVelocity)
    {

        qScrollerDebug() << "### below minimum Vel" << orientation;

        // - no snap points or already at one
        if (qIsNaN(nextSnap) || nextSnap == startPos)
        {
            return; // nothing to do, no scrolling needed.
        }

        // - decide which point to use

        qreal snapDistance = higherSnapPos - lowerSnapPos;

        qreal pressDistance = (orientation == Qt::Horizontal) ? m_lastPosition.x() - m_pressPosition.x()
                                                              : m_lastPosition.y() - m_pressPosition.y();

        // if not dragged far enough, pick the next snap point.
        if (sp->m_snapPositionRatio == 0.0 || qAbs(pressDistance / sp->m_snapPositionRatio) > snapDistance)
        {
            endPos = nextSnap;
        }
        else if (pressDistance < 0.0)
        {
            endPos = lowerSnapPos;
        }
        else
        {
            endPos = higherSnapPos;
        }

        deltaPos = endPos - startPos;
        qreal midPos = startPos + deltaPos * qreal(0.3);
        pushSegment(ScrollTypeFlick, sp->m_snapTime * qreal(0.3), qreal(1.0), startPos, midPos - startPos, midPos, QEasingCurve::InQuad, orientation);
        pushSegment(ScrollTypeFlick, sp->m_snapTime * qreal(0.7), qreal(1.0), midPos, endPos - midPos, endPos, sp->m_scrollingCurve.type(), orientation);
        return;
    }

    // - go to the next snappoint if there is one
    if (v > 0 && !qIsNaN(higherSnapPos))
    {
        // change the time in relation to the changed end position
        if (endPos - startPos)
        {
            deltaTime *= qAbs((higherSnapPos - startPos) / (endPos - startPos));
        }
        if (deltaTime > sp->m_snapTime)
        {
            deltaTime = sp->m_snapTime;
        }
        endPos = higherSnapPos;

    } else if (v < 0 && !qIsNaN(lowerSnapPos))
    {
        // change the time in relation to the changed end position
        if (endPos - startPos)
        {
            deltaTime *= qAbs((lowerSnapPos - startPos) / (endPos - startPos));
        }
        if (deltaTime > sp->m_snapTime)
        {
            deltaTime = sp->m_snapTime;
        }
        endPos = lowerSnapPos;

        // -- check if we are overshooting
    }
    else if (endPos < minPos || endPos > maxPos)
    {
        qreal stopPos = endPos < minPos ? minPos : maxPos;

        qScrollerDebug() << "Overshoot: delta:" << (stopPos - startPos);

        qreal stopProgress = progressForValue(sp->m_scrollingCurve, qAbs((stopPos - startPos) / deltaPos));

        if (!canOvershoot)
        {
            qScrollerDebug() << "Overshoot stopp:" << stopProgress;

            pushSegment(ScrollTypeFlick, deltaTime, stopProgress, startPos, endPos, stopPos,
                        sp->m_scrollingCurve.type(), orientation);
        }
        else
        {
            qreal oDeltaTime = sp->m_overshootScrollTime;
            qreal oStopProgress = qMin(stopProgress + oDeltaTime * qreal(0.3) / deltaTime, qreal(1));
            qreal oDistance = startPos + deltaPos * sp->m_scrollingCurve.valueForProgress(oStopProgress) - stopPos;
            qreal oMaxDistance = qSign(oDistance) * (viewSize * sp->m_overshootScrollDistanceFactor);

            qScrollerDebug() << "1 oDistance:" << oDistance << "Max:" << oMaxDistance <<
                "stopP/oStopP" << stopProgress << oStopProgress;

            if (qAbs(oDistance) > qAbs(oMaxDistance))
            {
                oStopProgress = progressForValue(sp->m_scrollingCurve,
                                                 qAbs((stopPos + oMaxDistance - startPos) / deltaPos));
                oDistance = oMaxDistance;
                qScrollerDebug() << "2 oDistance:" << oDistance << "Max:" << oMaxDistance <<
                    "stopP/oStopP" << stopProgress << oStopProgress;
            }

            pushSegment(ScrollTypeFlick, deltaTime, oStopProgress, startPos, deltaPos, stopPos + oDistance,
                        sp->m_scrollingCurve.type(), orientation);
            pushSegment(ScrollTypeOvershoot, oDeltaTime * qreal(0.7), qreal(1.0), stopPos + oDistance, -oDistance,
                        stopPos, sp->m_scrollingCurve.type(), orientation);
        }
        return;
    }

    pushSegment(ScrollTypeFlick, deltaTime, qreal(1.0), startPos, deltaPos, endPos, sp->m_scrollingCurve.type(), orientation);
}


void QExtScrollerPrivate::createScrollingSegments(const QPointF &v,
                                                  const QPointF &startPos,
                                                  const QPointF &ppm)
{
    const QExtScrollerPropertiesPrivate *sp = m_properties.dd_ptr.data();

    // This is only correct for QEasingCurve::OutQuad (linear velocity,
    // constant deceleration), but the results look and feel ok for OutExpo
    // and OutSine as well

    // v(t) = deltaTime * a * 0.5 * differentialForProgress(t / deltaTime)
    // v(0) = vrelease
    // v(deltaTime) = 0
    // deltaTime = (2 * vrelease) / (a * differntial(0))

    // pos(t) = integrate(v(t)dt)
    // pos(t) = vrelease * t - 0.5 * a * t * t
    // pos(t) = deltaTime * a * 0.5 * progress(t / deltaTime) * deltaTime
    // deltaPos = pos(deltaTime)

    QVector2D vel(v);
    qreal deltaTime = (qreal(2) * vel.length()) / (sp->m_decelerationFactor * differentialForProgress(sp->m_scrollingCurve, 0));
    QPointF deltaPos = (vel.normalized() * QVector2D(ppm)).toPointF() * deltaTime * deltaTime * qreal(0.5) * sp->m_decelerationFactor;

    createScrollingSegments(v.x(), startPos.x(), deltaTime, deltaPos.x(),
                            Qt::Horizontal);
    createScrollingSegments(v.y(), startPos.y(), deltaTime, deltaPos.y(),
                            Qt::Vertical);
}

/*! \internal
    Prepares scrolling by sending a QExtScrollPrepareEvent to the receiver widget.
    Returns \c true if the scrolling was accepted and a target was returned.
*/
bool QExtScrollerPrivate::prepareScrolling(const QPointF &position)
{
    QScrollPrepareEvent spe(position);
    spe.ignore();
    sendEvent(m_target, &spe);

    qScrollerDebug() << "QExtScrollPrepareEvent returned from" << m_target << "with" << spe.isAccepted() << "mcp:" << spe.contentPosRange() << "cp:" << spe.contentPos();
    if (spe.isAccepted())
    {
        QPointF oldContentPos = m_contentPosition + m_overshootPosition;
        QPointF contentDelta = spe.contentPos() - oldContentPos;

        m_viewportSize = spe.viewportSize();
        m_contentPosRange = spe.contentPosRange();
        if (m_contentPosRange.width() < 0)
        {
            m_contentPosRange.setWidth(0);
        }
        if (m_contentPosRange.height() < 0)
        {
            m_contentPosRange.setHeight(0);
        }
        m_contentPosition = clampToRect(spe.contentPos(), m_contentPosRange);
        m_overshootPosition = spe.contentPos() - m_contentPosition;

        // - check if the content position was moved
        if (contentDelta != QPointF(0, 0))
        {
            // need to correct all segments
            for (int i = 0; i < m_xSegments.count(); i++)
            {
                m_xSegments[i].startPos -= contentDelta.x();
            }

            for (int i = 0; i < m_ySegments.count(); i++)
            {
                m_ySegments[i].startPos -= contentDelta.y();
            }
        }

        if (QWidget *w = qobject_cast<QWidget *>(m_target))
        {
            setDpiFromWidget(w);
        }
#ifndef QT_NO_GRAPHICSVIEW
        if (QGraphicsObject *go = qobject_cast<QGraphicsObject *>(m_target))
        {
            //TODO: the first view isn't really correct - maybe use an additional field in the prepare event?
            if (go->scene() && !go->scene()->views().isEmpty())
            {
                setDpiFromWidget(go->scene()->views().first());
            }
        }
#endif

        if (m_state == QExtScroller::Scrolling)
        {
            recalcScrollingSegments();
        }
        return true;
    }

    return false;
}

void QExtScrollerPrivate::handleDrag(const QPointF &position, qint64 timestamp)
{
    const QExtScrollerPropertiesPrivate *sp = m_properties.dd_ptr.data();

    QPointF deltaPixel = position - m_lastPosition;
    qint64 deltaTime = timestamp - m_lastTimestamp;

    if (sp->m_axisLockThreshold)
    {
        int dx = qAbs(deltaPixel.x());
        int dy = qAbs(deltaPixel.y());
        if (dx || dy)
        {
            bool vertical = (dy > dx);
            qreal alpha = qreal(vertical ? dx : dy) / qreal(vertical ? dy : dx);
            qScrollerDebug() << "QExtScroller::handleDrag() -- axis lock:" << alpha << " / "
                             << QExtScrollerProperties::AxisLockThreshold
                             << "- isvertical:" << vertical << "- dx:" << dx << "- dy:" << dy;
            if (alpha <= sp->m_axisLockThreshold)
            {
                if (vertical)
                {
                    deltaPixel.setX(0);
                }
                else
                {
                    deltaPixel.setY(0);
                }
            }
        }
    }

    // calculate velocity (if the user would release the mouse NOW)
    updateVelocity(deltaPixel, deltaTime);

    // restrict velocity, if content is not scrollable
    QRectF max = m_contentPosRange;
    bool canScrollX = (max.width() > 0) || (sp->m_hOvershootPolicy == QExtScrollerProperties::OvershootAlwaysOn);
    bool canScrollY = (max.height() > 0) || (sp->m_vOvershootPolicy == QExtScrollerProperties::OvershootAlwaysOn);

    if (!canScrollX)
    {
        deltaPixel.setX(0);
        m_releaseVelocity.setX(0);
    }
    if (!canScrollY)
    {
        deltaPixel.setY(0);
        m_releaseVelocity.setY(0);
    }

    //    if (firstDrag) {
    //        // Do not delay the first drag
    //        setContentPositionHelper(q->contentPosition() - overshootDistance - deltaPixel);
    //        dragDistance = QPointF(0, 0);
    //    } else {
    m_dragDistance += deltaPixel;
    //    }
    //qScrollerDebug() << "######################" << deltaPixel << position.y() << lastPosition.y();

    m_lastPosition = position;
    m_lastTimestamp = timestamp;
}

bool QExtScrollerPrivate::pressWhileInactive(const QPointF &position, qint64 timestamp)
{
    if (prepareScrolling(position))
    {
        const QExtScrollerPropertiesPrivate *sp = m_properties.dd_ptr.data();

        if (!m_contentPosRange.isNull() ||
            (sp->m_hOvershootPolicy == QExtScrollerProperties::OvershootAlwaysOn) ||
            (sp->m_vOvershootPolicy == QExtScrollerProperties::OvershootAlwaysOn))
        {

            m_lastPosition = m_pressPosition = position;
            m_lastTimestamp = m_pressTimestamp = timestamp;
            setState(QExtScroller::Pressed);
        }
    }
    return false;
}

bool QExtScrollerPrivate::releaseWhilePressed(const QPointF &, qint64)
{
    if (m_overshootPosition != QPointF(0.0, 0.0))
    {
        setState(QExtScroller::Scrolling);
        return true;
    }
    else
    {
        setState(QExtScroller::Inactive);
        return false;
    }
}

bool QExtScrollerPrivate::moveWhilePressed(const QPointF &position, qint64 timestamp)
{
    Q_Q(QExtScroller);
    const QExtScrollerPropertiesPrivate *sp = m_properties.dd_ptr.data();
    QPointF ppm = q->pixelPerMeter();

    QPointF deltaPixel = position - m_pressPosition;

    bool moveAborted = false;
    bool moveStarted = (((deltaPixel / ppm).manhattanLength()) > sp->m_dragStartDistance);

    // check the direction of the mouse drag and abort if it's too much in the wrong direction.
    if (moveStarted)
    {
        QRectF max = m_contentPosRange;
        bool canScrollX = (max.width() > 0);
        bool canScrollY = (max.height() > 0);

        if (sp->m_hOvershootPolicy == QExtScrollerProperties::OvershootAlwaysOn)
        {
            canScrollX = true;
        }
        if (sp->m_vOvershootPolicy == QExtScrollerProperties::OvershootAlwaysOn)
        {
            canScrollY = true;
        }

        if (qAbs(deltaPixel.x() / ppm.x()) < qAbs(deltaPixel.y() / ppm.y()))
        {
            if (!canScrollY)
            {
                moveAborted = true;
            }
        }
        else
        {
            if (!canScrollX)
            {
                moveAborted = true;
            }
        }
    }

    if (moveAborted)
    {
        setState(QExtScroller::Inactive);
        moveStarted = false;

    }
    else if (moveStarted)
    {
        setState(QExtScroller::Dragging);

        // subtract the dragStartDistance
        deltaPixel = deltaPixel - deltaPixel * (sp->m_dragStartDistance / deltaPixel.manhattanLength());

        if (deltaPixel != QPointF(0, 0))
        {
            // handleDrag updates lastPosition, lastTimestamp and velocity
            handleDrag(m_pressPosition + deltaPixel, timestamp);
        }
    }
    return moveStarted;
}

bool QExtScrollerPrivate::moveWhileDragging(const QPointF &position, qint64 timestamp)
{
    // handleDrag updates lastPosition, lastTimestamp and velocity
    handleDrag(position, timestamp);
    return true;
}

void QExtScrollerPrivate::timerEventWhileDragging()
{
    if (m_dragDistance != QPointF(0, 0))
    {
        qScrollerDebug() << "QExtScroller::timerEventWhileDragging() -- dragDistance:" << m_dragDistance;

        setContentPositionHelperDragging(-m_dragDistance);
        m_dragDistance = QPointF(0, 0);
    }
}

bool QExtScrollerPrivate::releaseWhileDragging(const QPointF &position, qint64 timestamp)
{
    Q_Q(QExtScroller);
    const QExtScrollerPropertiesPrivate *sp = m_properties.dd_ptr.data();

    // handleDrag updates lastPosition, lastTimestamp and velocity
    handleDrag(position, timestamp);

    // check if we moved at all - this can happen if you stop a running
    // scroller with a press and release shortly afterwards
    QPointF deltaPixel = position - m_pressPosition;
    if (((deltaPixel / q->pixelPerMeter()).manhattanLength()) > sp->m_dragStartDistance)
    {

        // handle accelerating flicks
        if ((m_oldVelocity != QPointF(0, 0)) && sp->m_acceleratingFlickMaximumTime &&
            ((timestamp - m_pressTimestamp) < qint64(sp->m_acceleratingFlickMaximumTime * 1000)))
        {

            // - determine if the direction was changed
            int signX = 0, signY = 0;
            if (m_releaseVelocity.x())
            {
                signX = (m_releaseVelocity.x() > 0) == (m_oldVelocity.x() > 0) ? 1 : -1;
            }
            if (m_releaseVelocity.y())
            {
                signY = (m_releaseVelocity.y() > 0) == (m_oldVelocity.y() > 0) ? 1 : -1;
            }

            if (signX > 0)
            {
                m_releaseVelocity.setX(qBound(-sp->m_maximumVelocity,
                                              m_oldVelocity.x() * sp->m_acceleratingFlickSpeedupFactor,
                                              sp->m_maximumVelocity));
            }
            if (signY > 0)
            {
                m_releaseVelocity.setY(qBound(-sp->m_maximumVelocity,
                                              m_oldVelocity.y() * sp->m_acceleratingFlickSpeedupFactor,
                                              sp->m_maximumVelocity));
            }
        }
    }

    QPointF ppm = q->pixelPerMeter();
    createScrollingSegments(m_releaseVelocity, m_contentPosition + m_overshootPosition, ppm);

    qScrollerDebug() << "QExtScroller::releaseWhileDragging() -- velocity:" << m_releaseVelocity
                     << "-- minimum velocity:" << sp->m_minimumVelocity << "overshoot" << m_overshootPosition;

    if (m_xSegments.isEmpty() && m_ySegments.isEmpty())
    {
        this->setState(QExtScroller::Inactive);
    }
    else
    {
        this->setState(QExtScroller::Scrolling);
    }

    return true;
}

void QExtScrollerPrivate::timerEventWhileScrolling()
{
    qScrollerDebug("QExtScroller::timerEventWhileScrolling()");

    this->setContentPositionHelperScrolling();
    if (m_xSegments.isEmpty() && m_ySegments.isEmpty())
    {
        this->setState(QExtScroller::Inactive);
    }
}

bool QExtScrollerPrivate::pressWhileScrolling(const QPointF &position, qint64 timestamp)
{
    Q_Q(QExtScroller);

    if ((q->velocity() <= m_properties.dd_ptr->m_maximumClickThroughVelocity) && (m_overshootPosition == QPointF(0.0, 0.0)))
    {
        this->setState(QExtScroller::Inactive);
        return false;
    }
    else
    {
        m_lastPosition = m_pressPosition = position;
        m_lastTimestamp = m_pressTimestamp = timestamp;
        this->setState(QExtScroller::Pressed);
        this->setState(QExtScroller::Dragging);
        return true;
    }
}

/*! \internal
    This function handles all state changes of the scroller.
*/
void QExtScrollerPrivate::setState(QExtScroller::State newstate)
{
    Q_Q(QExtScroller);
    bool sendLastScroll = false;

    if (m_state == newstate)
    {
        return;
    }

    qScrollerDebug() << q << "QExtScroller::setState(" << stateName(newstate) << ')';

    switch (newstate)
    {
    case QExtScroller::Inactive:
#ifndef QT_NO_ANIMATION
        m_scrollTimer->stop();
#endif

        // send the last scroll event (but only after the current state change was finished)
        if (!m_firstScroll)
        {
            sendLastScroll = true;
        }

        m_releaseVelocity = QPointF(0, 0);
        break;

    case QExtScroller::Pressed:
#ifndef QT_NO_ANIMATION
        m_scrollTimer->stop();
#endif

        m_oldVelocity = m_releaseVelocity;
        m_releaseVelocity = QPointF(0, 0);
        break;

    case QExtScroller::Dragging:
        m_dragDistance = QPointF(0, 0);
#ifndef QT_NO_ANIMATION
        if (m_state == QExtScroller::Pressed)
        {
            m_scrollTimer->start();
        }
#endif
        break;

    case QExtScroller::Scrolling:
#ifndef QT_NO_ANIMATION
        m_scrollTimer->start();
#endif
        break;
    }

    qSwap(m_state, newstate);

    if (sendLastScroll)
    {
        QScrollEvent se(m_contentPosition, m_overshootPosition, QScrollEvent::ScrollFinished);
        sendEvent(m_target, &se);
        m_firstScroll = true;
    }
    if (m_state == QExtScroller::Dragging || m_state == QExtScroller::Scrolling)
    {
        qext_activeScrollers()->insert(q);
    }
    else
    {
        qext_activeScrollers()->remove(q);
    }
    emit q->stateChanged(m_state);
}


/*! \internal
    Helps when setting the content position.
    It will try to move the content by the requested delta but stop in case
    when we are coming back from an overshoot or a scrollTo.
    It will also indicate a new overshooting condition by the overshootX and oversthootY flags.

    In this cases it will reset the velocity variables and other flags.

    Also keeps track of the current over-shooting value in overshootPosition.

    \a deltaPos is the amount of pixels the current content position should be moved
*/
void QExtScrollerPrivate::setContentPositionHelperDragging(const QPointF &deltaPos)
{
    const QExtScrollerPropertiesPrivate *sp = m_properties.dd_ptr.data();

    if (sp->m_overshootDragResistanceFactor)
    {
        m_overshootPosition /= sp->m_overshootDragResistanceFactor;
    }

    QPointF oldPos = m_contentPosition + m_overshootPosition;
    QPointF newPos = oldPos + deltaPos;

    qScrollerDebug() << "QExtScroller::setContentPositionHelperDragging(" << deltaPos << " [pix])";
    qScrollerDebug() << "  --> overshoot:" << m_overshootPosition << "- old pos:" << oldPos << "- new pos:" << newPos;

    QPointF oldClampedPos = clampToRect(oldPos, m_contentPosRange);
    QPointF newClampedPos = clampToRect(newPos, m_contentPosRange);

    // --- handle overshooting and stop if the coordinate is going back inside the normal area
    bool alwaysOvershootX = (sp->m_hOvershootPolicy == QExtScrollerProperties::OvershootAlwaysOn);
    bool alwaysOvershootY = (sp->m_vOvershootPolicy == QExtScrollerProperties::OvershootAlwaysOn);
    bool noOvershootX = (sp->m_hOvershootPolicy == QExtScrollerProperties::OvershootAlwaysOff) ||
                        ((m_state == QExtScroller::Dragging) && !sp->m_overshootDragResistanceFactor) ||
                        !sp->m_overshootDragDistanceFactor;
    bool noOvershootY = (sp->m_vOvershootPolicy == QExtScrollerProperties::OvershootAlwaysOff) ||
                        ((m_state == QExtScroller::Dragging) && !sp->m_overshootDragResistanceFactor) ||
                        !sp->m_overshootDragDistanceFactor;
    bool canOvershootX = !noOvershootX && (alwaysOvershootX || m_contentPosRange.width());
    bool canOvershootY = !noOvershootY && (alwaysOvershootY || m_contentPosRange.height());

    qreal oldOvershootX = (canOvershootX) ? oldPos.x() - oldClampedPos.x() : 0;
    qreal oldOvershootY = (canOvershootY) ? oldPos.y() - oldClampedPos.y() : 0;
    Q_UNUSED(oldOvershootX);
    Q_UNUSED(oldOvershootY);

    qreal newOvershootX = (canOvershootX) ? newPos.x() - newClampedPos.x() : 0;
    qreal newOvershootY = (canOvershootY) ? newPos.y() - newClampedPos.y() : 0;

    qreal maxOvershootX = m_viewportSize.width() * sp->m_overshootDragDistanceFactor;
    qreal maxOvershootY = m_viewportSize.height() * sp->m_overshootDragDistanceFactor;

    qScrollerDebug() << "  --> noOs:" << noOvershootX << "drf:" << sp->m_overshootDragResistanceFactor
                     << "mdf:" << sp->m_overshootScrollDistanceFactor << "ossP:"<<sp->m_hOvershootPolicy;
    qScrollerDebug() << "  --> canOS:" << canOvershootX << "newOS:" << newOvershootX << "maxOS:" << maxOvershootX;

    if (sp->m_overshootDragResistanceFactor)
    {
        oldOvershootX *= sp->m_overshootDragResistanceFactor;
        oldOvershootY *= sp->m_overshootDragResistanceFactor;
        newOvershootX *= sp->m_overshootDragResistanceFactor;
        newOvershootY *= sp->m_overshootDragResistanceFactor;
    }

    // -- stop at the maximum overshoot distance

    newOvershootX = qBound(-maxOvershootX, newOvershootX, maxOvershootX);
    newOvershootY = qBound(-maxOvershootY, newOvershootY, maxOvershootY);

    m_overshootPosition.setX(newOvershootX);
    m_overshootPosition.setY(newOvershootY);
    m_contentPosition = newClampedPos;

    QScrollEvent se(m_contentPosition, m_overshootPosition, m_firstScroll ? QScrollEvent::ScrollStarted : QScrollEvent::ScrollUpdated);
    sendEvent(m_target, &se);
    m_firstScroll = false;

    qScrollerDebug() << "  --> new position:" << newClampedPos << "- new overshoot:" << m_overshootPosition
                     << "- overshoot x/y?:" << m_overshootPosition;
}

qreal QExtScrollerPrivate::nextSegmentPosition(QQueue<ScrollSegment> &segments, qint64 now, qreal oldPos)
{
    qreal pos = oldPos;

    // check the X segments for new positions
    while (!segments.isEmpty())
    {
        const ScrollSegment s = segments.head();

        if ((s.startTime + s.deltaTime * s.stopProgress) <= now)
        {
            segments.dequeue();
            pos = s.stopPos;
        }
        else if (s.startTime <= now)
        {
            qreal progress = qreal(now - s.startTime) / qreal(s.deltaTime);
            pos = s.startPos + s.deltaPos * s.curve.valueForProgress(progress);
            if (s.deltaPos > 0 ? pos > s.stopPos : pos < s.stopPos)
            {
                segments.dequeue();
                pos = s.stopPos;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    return pos;
}

void QExtScrollerPrivate::setContentPositionHelperScrolling()
{
    qint64 now = m_monotonicTimer.elapsed();
    QPointF newPos = m_contentPosition + m_overshootPosition;

    newPos.setX(nextSegmentPosition(m_xSegments, now, newPos.x()));
    newPos.setY(nextSegmentPosition(m_ySegments, now, newPos.y()));

    // -- set the position and handle overshoot
    qScrollerDebug() << "QExtScroller::setContentPositionHelperScrolling()\n"
                        "  --> overshoot:" << m_overshootPosition << "- new pos:" << newPos;

    QPointF newClampedPos = clampToRect(newPos, m_contentPosRange);

    m_overshootPosition = newPos - newClampedPos;
    m_contentPosition = newClampedPos;

    QScrollEvent se(m_contentPosition, m_overshootPosition, m_firstScroll ? QScrollEvent::ScrollStarted : QScrollEvent::ScrollUpdated);
    sendEvent(m_target, &se);
    m_firstScroll = false;

    qScrollerDebug() << "  --> new position:" << newClampedPos << "- new overshoot:" << m_overshootPosition;
}

qreal QExtScrollerPrivate::nextSnapPos(qreal p, int dir, Qt::Orientation orientation)
{
    qreal bestSnapPos = Q_QNAN;
    qreal bestSnapPosDist = Q_INFINITY;

    qreal minPos;
    qreal maxPos;

    if (orientation == Qt::Horizontal)
    {
        minPos = m_contentPosRange.left();
        maxPos = m_contentPosRange.right();
    }
    else
    {
        minPos = m_contentPosRange.top();
        maxPos = m_contentPosRange.bottom();
    }

    if (orientation == Qt::Horizontal)
    {
        // the snap points in the list
        foreach (qreal snapPos, m_snapPositionsX)
        {
            qreal snapPosDist = snapPos - p;
            if ((dir > 0 && snapPosDist < 0) || (dir < 0 && snapPosDist > 0))
            {
                continue; // wrong direction
            }
            if (snapPos < minPos || snapPos > maxPos)
            {
                continue; // invalid
            }

            if (qIsNaN(bestSnapPos) || qAbs(snapPosDist) < bestSnapPosDist )
            {
                bestSnapPos = snapPos;
                bestSnapPosDist = qAbs(snapPosDist);
            }
        }

        // the snap point interval
        if (m_snapIntervalX > 0.0)
        {
            qreal first = minPos + m_snapFirstX;
            qreal snapPos;
            if (dir > 0)
            {
                snapPos = qCeil((p - first) / m_snapIntervalX) * m_snapIntervalX + first;
            }
            else if (dir < 0)
            {
                snapPos = qFloor((p - first) / m_snapIntervalX) * m_snapIntervalX + first;
            }
            else if (p <= first)
            {
                snapPos = first;
            }
            else
            {
                qreal last = qFloor((maxPos - first) / m_snapIntervalX) * m_snapIntervalX + first;
                if (p >= last)
                {
                    snapPos = last;
                }
                else
                {
                    snapPos = qRound((p - first) / m_snapIntervalX) * m_snapIntervalX + first;
                }
            }

            if (snapPos >= first && snapPos <= maxPos )
            {
                qreal snapPosDist = snapPos - p;

                if (qIsNaN(bestSnapPos) || qAbs(snapPosDist) < bestSnapPosDist )
                {
                    bestSnapPos = snapPos;
                    bestSnapPosDist = qAbs(snapPosDist);
                }
            }
        }

    }
    else
    { // (orientation == Qt::Vertical)
        // the snap points in the list
        foreach (qreal snapPos, m_snapPositionsY)
        {
            qreal snapPosDist = snapPos - p;
            if ((dir > 0 && snapPosDist < 0) || (dir < 0 && snapPosDist > 0))
            {
                continue; // wrong direction
            }
            if (snapPos < minPos || snapPos > maxPos)
            {
                continue; // invalid
            }

            if (qIsNaN(bestSnapPos) || qAbs(snapPosDist) < bestSnapPosDist)
            {
                bestSnapPos = snapPos;
                bestSnapPosDist = qAbs(snapPosDist);
            }
        }

        // the snap point interval
        if (m_snapIntervalY > 0.0)
        {
            qreal first = minPos + m_snapFirstY;
            qreal snapPos;
            if (dir > 0)
            {
                snapPos = qCeil((p - first) / m_snapIntervalY) * m_snapIntervalY + first;
            }
            else if (dir < 0)
            {
                snapPos = qFloor((p - first) / m_snapIntervalY) * m_snapIntervalY + first;
            }
            else if (p <= first)
            {
                snapPos = first;
            }
            else
            {
                qreal last = qFloor((maxPos - first) / m_snapIntervalY) * m_snapIntervalY + first;
                if (p >= last)
                {
                    snapPos = last;
                }
                else
                {
                    snapPos = qRound((p - first) / m_snapIntervalY) * m_snapIntervalY + first;
                }
            }

            if (snapPos >= first && snapPos <= maxPos )
            {
                qreal snapPosDist = snapPos - p;

                if (qIsNaN(bestSnapPos) || qAbs(snapPosDist) < bestSnapPosDist)
                {
                    bestSnapPos = snapPos;
                    bestSnapPosDist = qAbs(snapPosDist);
                }
            }
        }
    }

    return bestSnapPos;
}

/*!
    \enum QExtScroller::State

    This enum contains the different QExtScroller states.

    \value Inactive The scroller is not scrolling and nothing is pressed.
    \value Pressed A touch event was received or the mouse button was pressed but the scroll area is currently not dragged.
    \value Dragging The scroll area is currently following the touch point or mouse.
    \value Scrolling The scroll area is moving on it's own.
*/

/*!
    \enum QExtScroller::ScrollerGestureType

    This enum contains the different gesture types that are supported by the QExtScroller gesture recognizer.

    \value TouchGesture The gesture recognizer will only trigger on touch
        events.  Specifically it will react on single touch points when using a
        touch screen and dual touch points when using a touchpad.
    \value LeftMouseButtonGesture The gesture recognizer will only trigger on left mouse button events.
    \value MiddleMouseButtonGesture The gesture recognizer will only trigger on middle mouse button events.
    \value RightMouseButtonGesture The gesture recognizer will only trigger on right mouse button events.
*/

/*!
    \enum QExtScroller::Input

    This enum contains an input device agnostic view of input events that are relevant for QExtScroller.

    \value InputPress   The user pressed the input device (e.g.  QEvent::MouseButtonPress,
                        QEvent::GraphicsSceneMousePress, QEvent::TouchBegin)

    \value InputMove    The user moved the input device (e.g.  QEvent::MouseMove,
                        QEvent::GraphicsSceneMouseMove, QEvent::TouchUpdate)

    \value InputRelease The user released the input device (e.g.  QEvent::MouseButtonRelease,
                        QEvent::GraphicsSceneMouseRelease, QEvent::TouchEnd)

*/
