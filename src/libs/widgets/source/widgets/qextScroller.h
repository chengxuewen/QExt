#ifndef _QEXTSCROLLER_H
#define _QEXTSCROLLER_H

#include <QSizeF>
#include <QRectF>
#include <QEvent>
#include <QObject>
#include <QPointF>

#include <qextWidgetGlobal.h>

//#define QT_NO_GESTURES

/***********************************************************************************************************************
** QExtScrollerProperties
***********************************************************************************************************************/
class QExtScroller;
class QExtScrollerPrivate;
class QExtScrollerPropertiesPrivate;
class QEXT_WIDGETS_API QExtScrollerProperties
{
public:
    QExtScrollerProperties();
    QExtScrollerProperties(const QExtScrollerProperties &sp);
    QExtScrollerProperties &operator=(const QExtScrollerProperties &sp);
    virtual ~QExtScrollerProperties();

    bool operator==(const QExtScrollerProperties &sp) const;
    bool operator!=(const QExtScrollerProperties &sp) const;

    static void setDefaultScrollerProperties(const QExtScrollerProperties &sp);
    static void unsetDefaultScrollerProperties();

    enum OvershootPolicy
    {
        OvershootWhenScrollable,
        OvershootAlwaysOff,
        OvershootAlwaysOn
    };

    enum FrameRates
    {
        Standard,
        Fps60,
        Fps30,
        Fps20
    };

    enum ScrollMetric
    {
        MousePressEventDelay,                    // qreal [s]
        DragStartDistance,                       // qreal [m]
        DragVelocitySmoothingFactor,             // qreal [0..1/s]  (complex calculation involving time) v = v_new* DASF + v_old * (1-DASF)
        AxisLockThreshold,                       // qreal [0..1] atan(|min(dx,dy)|/|max(dx,dy)|)

        ScrollingCurve,                          // QEasingCurve
        DecelerationFactor,                      // slope of the curve

        MinimumVelocity,                         // qreal [m/s]
        MaximumVelocity,                         // qreal [m/s]
        MaximumClickThroughVelocity,             // qreal [m/s]

        AcceleratingFlickMaximumTime,            // qreal [s]
        AcceleratingFlickSpeedupFactor,          // qreal [1..]

        SnapPositionRatio,                       // qreal [0..1]
        SnapTime,                                // qreal [s]

        OvershootDragResistanceFactor,           // qreal [0..1]
        OvershootDragDistanceFactor,             // qreal [0..1]
        OvershootScrollDistanceFactor,           // qreal [0..1]
        OvershootScrollTime,                     // qreal [s]

        HorizontalOvershootPolicy,               // enum OvershootPolicy
        VerticalOvershootPolicy,                 // enum OvershootPolicy
        FrameRate,                               // enum FrameRates

        ScrollMetricCount
    };

    QVariant scrollMetric(ScrollMetric metric) const;
    void setScrollMetric(ScrollMetric metric, const QVariant &value);

protected:
    QScopedPointer<QExtScrollerPropertiesPrivate> dd_ptr;

private:
    friend class QExtScroller;
    friend class QExtScrollerPrivate;
    friend class QExtScrollerPropertiesPrivate;
    QExtScrollerProperties(QExtScrollerPropertiesPrivate &dd);
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtScrollerProperties)
};
Q_DECLARE_METATYPE(QExtScrollerProperties::OvershootPolicy)
Q_DECLARE_METATYPE(QExtScrollerProperties::FrameRates)


/***********************************************************************************************************************
** QExtScroller
***********************************************************************************************************************/
class QWidget;
class QExtScrollerPrivate;
class QExtScrollerProperties;
#ifndef QT_NO_GESTURES
class QExtFlickGestureRecognizer;
#endif
class QEXT_WIDGETS_API QExtScroller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(QExtScrollerProperties scrollerProperties READ scrollerProperties WRITE setScrollerProperties NOTIFY scrollerPropertiesChanged)

public:
    enum State
    {
        Inactive,
        Pressed,
        Dragging,
        Scrolling
    };
    Q_ENUMS(State)

    enum ScrollerGestureType
    {
        TouchGesture,
        LeftMouseButtonGesture,
        RightMouseButtonGesture,
        MiddleMouseButtonGesture
    };

    enum Input
    {
        InputPress = 1,
        InputMove,
        InputRelease
    };

    static bool hasScroller(QObject *target);

    static QExtScroller *scroller(QObject *target);
    static const QExtScroller *scroller(const QObject *target);

#ifndef QT_NO_GESTURES
    static Qt::GestureType grabGesture(QObject *target, ScrollerGestureType gestureType = TouchGesture);
    static Qt::GestureType grabbedGesture(QObject *target);
    static void ungrabGesture(QObject *target);
#endif

    static QList<QExtScroller *> activeScrollers();

    QObject *target() const;

    State state() const;

    bool handleInput(Input input, const QPointF &position, qint64 timestamp = 0);

    void stop();
    QPointF velocity() const;
    QPointF finalPosition() const;
    QPointF pixelPerMeter() const;

    QExtScrollerProperties scrollerProperties() const;

    void setSnapPositionsX(const QList<qreal> &positions);
    void setSnapPositionsX(qreal first, qreal interval);
    void setSnapPositionsY(const QList<qreal> &positions);
    void setSnapPositionsY(qreal first, qreal interval);

public Q_SLOTS:
    void setScrollerProperties(const QExtScrollerProperties &prop);
    void scrollTo(const QPointF &pos);
    void scrollTo(const QPointF &pos, int scrollTime);
    void ensureVisible(const QRectF &rect, qreal xmargin, qreal ymargin);
    void ensureVisible(const QRectF &rect, qreal xmargin, qreal ymargin, int scrollTime);
    void resendPrepareEvent();

Q_SIGNALS:
    void stateChanged(QExtScroller::State newstate);
    void scrollerPropertiesChanged(const QExtScrollerProperties &);

private:
    QExtScrollerPrivate *dd_ptr;

    QExtScroller(QObject *target);
    virtual ~QExtScroller();

    QEXT_DECL_PRIVATE_D(dd_ptr, QExtScroller)
    QEXT_DISABLE_COPY_MOVE(QExtScroller)

#ifndef QT_NO_GESTURES
    friend class QExtFlickGestureRecognizer;
#endif
};

#endif // _QEXTSCROLLER_H
