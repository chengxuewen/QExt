#ifndef _QEXTSCROLLER_P_H
#define _QEXTSCROLLER_P_H

#include <qextScroller.h>

#include <QSet>
#include <QQueue>
#include <QSizeF>
#include <QRectF>
#include <QObject>
#include <QPointF>
#include <QWidget>
#include <QGesture>
#include <QPointer>
#include <QEasingCurve>
#include <QElapsedTimer>
#include <QGestureRecognizer>
#include <QAbstractAnimation>


class PressDelayHandler;
class QEXT_WIDGETS_API QExtFlickGesture : public QGesture
{
    Q_OBJECT
public:
    QExtFlickGesture(QObject *receiver, Qt::MouseButton button, QObject *parent = 0);
    ~QExtFlickGesture();

    QObject *receiver() const { return m_receiver.data(); }
    QExtScroller *receiverScroller() const { return m_receiverScroller; }

    bool macIgnoreWheel() const { return m_macIgnoreWheel; }
    void setMacIgnoreWheel(bool ignore) { m_macIgnoreWheel = ignore; }

private:
    friend class QExtFlickGestureRecognizer;
    QPointer<QObject> m_receiver;
    QExtScroller *m_receiverScroller;
    Qt::MouseButton m_button; // NoButton == Touch
    bool m_macIgnoreWheel;
    static PressDelayHandler *sm_pressDelayHandler;
};


class QEXT_WIDGETS_API QExtFlickGestureRecognizer : public QGestureRecognizer
{
public:
    QExtFlickGestureRecognizer(Qt::MouseButton button);

    QGesture *create(QObject *target);
    QGestureRecognizer::Result recognize(QGesture *state, QObject *watched, QEvent *event);
    void reset(QGesture *state);

private:
    Qt::MouseButton m_button; // NoButton == Touch
};


class QEXT_WIDGETS_API QExtScrollerPropertiesPrivate
{
public:
    static QExtScrollerPropertiesPrivate *defaults();

    bool operator==(const QExtScrollerPropertiesPrivate &) const;

    qreal m_mousePressEventDelay;
    qreal m_dragStartDistance;
    qreal m_dragVelocitySmoothingFactor;
    qreal m_axisLockThreshold;
    QEasingCurve m_scrollingCurve;
    qreal m_decelerationFactor;
    qreal m_minimumVelocity;
    qreal m_maximumVelocity;
    qreal m_maximumClickThroughVelocity;
    qreal m_acceleratingFlickMaximumTime;
    qreal m_acceleratingFlickSpeedupFactor;
    qreal m_snapPositionRatio;
    qreal m_snapTime;
    qreal m_overshootDragResistanceFactor;
    qreal m_overshootDragDistanceFactor;
    qreal m_overshootScrollDistanceFactor;
    qreal m_overshootScrollTime;
    QExtScrollerProperties::OvershootPolicy m_hOvershootPolicy;
    QExtScrollerProperties::OvershootPolicy m_vOvershootPolicy;
    QExtScrollerProperties::FrameRates m_frameRate;
};

#ifndef QT_NO_GESTURES
class QExtFlickGestureRecognizer;
#endif

#ifndef QT_NO_ANIMATION
class QScrollTimer;
#endif
class QEXT_WIDGETS_API QExtScrollerPrivate : public QObject
{
    Q_OBJECT
    QEXT_DECL_PUBLIC(QExtScroller)

public:
    QExtScrollerPrivate(QExtScroller *q, QObject *target);
    void init();

    void sendEvent(QObject *o, QEvent *e);

    void setState(QExtScroller::State s);

    enum ScrollType
    {
        ScrollTypeFlick = 0,
        ScrollTypeScrollTo,
        ScrollTypeOvershoot
    };

    struct ScrollSegment
    {
        qint64 startTime;
        qint64 deltaTime;
        qreal startPos;
        qreal deltaPos;
        QEasingCurve curve;
        qreal stopProgress; // whatever is..
        qreal stopPos;      // ..reached first
        ScrollType type;
    };

    bool pressWhileInactive(const QPointF &position, qint64 timestamp);
    bool moveWhilePressed(const QPointF &position, qint64 timestamp);
    bool releaseWhilePressed(const QPointF &position, qint64 timestamp);
    bool moveWhileDragging(const QPointF &position, qint64 timestamp);
    bool releaseWhileDragging(const QPointF &position, qint64 timestamp);
    bool pressWhileScrolling(const QPointF &position, qint64 timestamp);

    void timerTick();
    void timerEventWhileDragging();
    void timerEventWhileScrolling();

    bool prepareScrolling(const QPointF &position);
    void handleDrag(const QPointF &position, qint64 timestamp);

    QPointF realDpi(int screen);
    QPointF dpi() const;
    void setDpi(const QPointF &dpi);
    void setDpiFromWidget(QWidget *widget);

    void updateVelocity(const QPointF &deltaPixelRaw, qint64 deltaTime);
    void pushSegment(ScrollType type, qreal deltaTime, qreal stopProgress, qreal startPos, qreal deltaPos, qreal stopPos, QEasingCurve::Type curve, Qt::Orientation orientation);
    void recalcScrollingSegments(bool forceRecalc = false);
    qreal scrollingSegmentsEndPos(Qt::Orientation orientation) const;
    bool scrollingSegmentsValid(Qt::Orientation orientation);
    void createScrollToSegments(qreal v, qreal deltaTime, qreal endPos, Qt::Orientation orientation, ScrollType type);
    void createScrollingSegments(qreal v, qreal startPos,
                                 qreal deltaTime, qreal deltaPos,
                                 Qt::Orientation orientation);
    void createScrollingSegments(const QPointF &v, const QPointF &startPos, const QPointF &ppm);

    void setContentPositionHelperDragging(const QPointF &deltaPos);
    void setContentPositionHelperScrolling();

    /**
     * @brief Returns the next snap point in direction.
     * If @a direction >0 it will return the next snap point that is larger than the current position.
     * If @a direction <0 it will return the next snap point that is smaller than the current position.
     * If @a direction ==0 it will return the nearest snap point (or the current position if we are already on a snap point.
     * @param p
     * @param dir
     * @param orientation
     * @return Returns the nearest snap position or NaN if no such point could be found.
     */
    qreal nextSnapPos(qreal p, int dir, Qt::Orientation orientation);
    static qreal nextSegmentPosition(QQueue<ScrollSegment> &segments, qint64 now, qreal oldPos);

    inline int frameRateSkip() const { return m_properties.dd_ptr.data()->m_frameRate; }

    static const char *stateName(QExtScroller::State state);
    static const char *inputName(QExtScroller::Input input);

public slots:
    void targetDestroyed();

public:
    // non static
    QObject *m_target;
    QExtScrollerProperties m_properties;
#ifndef QT_NO_GESTURES
    QExtFlickGestureRecognizer *m_recognizer;
    Qt::GestureType m_recognizerType;
#endif

    // scroller state:
    QSizeF m_viewportSize;
    QRectF m_contentPosRange;
    QPointF m_contentPosition;
    QPointF m_overshootPosition; // the number of pixels we are overshooting (before overshootDragResistanceFactor)

    // state
    bool m_enabled;
    QExtScroller::State m_state;
    bool m_firstScroll; // true if we haven't already send a scroll event

    QPointF m_oldVelocity; // the release velocity of the last drag

    QPointF m_pressPosition;
    QPointF m_lastPosition;
    qint64  m_pressTimestamp;
    qint64  m_lastTimestamp;

    QPointF m_dragDistance; // the distance we should move during the next drag timer event

    QQueue<ScrollSegment> m_xSegments;
    QQueue<ScrollSegment> m_ySegments;

    // snap positions
    QList<qreal> m_snapPositionsX;
    qreal m_snapFirstX;
    qreal m_snapIntervalX;
    QList<qreal> m_snapPositionsY;
    qreal m_snapFirstY;
    qreal m_snapIntervalY;

    QPointF m_pixelPerMeter;

    QElapsedTimer m_monotonicTimer;

    QPointF m_releaseVelocity; // the starting velocity of the scrolling state
#ifndef QT_NO_ANIMATION
    QScrollTimer *m_scrollTimer;
#endif

    QExtScroller *q_ptr;
};
template <>
class QTypeInfo<QExtScrollerPrivate::ScrollSegment>
    : public QTypeInfoMerger<QExtScrollerPrivate::ScrollSegment, QEasingCurve> {};


#endif // _QEXTSCROLLER_P_H
