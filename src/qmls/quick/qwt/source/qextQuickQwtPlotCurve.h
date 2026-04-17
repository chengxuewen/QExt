#ifndef _QEXTQUICKQWTPLOTCURVE_H
#define _QEXTQUICKQWTPLOTCURVE_H

#include <qextQuickQwtSeriesStore.h>
#include <qextQmlPenInfo.h>

#include <QObject>

class QExtQuickQwtPlot;
class QExtQuickQwtPlotCurvePrivate;
class QEXT_QUICKQWT_API QExtQuickQwtPlotCurve : public QObject, public QExtQuickQwtSeriesStore<QPointF>
{
    Q_OBJECT
    Q_PROPERTY(QExtQmlPenInfo* pen READ pen)
    Q_PROPERTY(QExtQuickQwtPlot* plot READ plot WRITE setPlot NOTIFY plotChanged)
    Q_PROPERTY(QExtQuickQwtPlot* plot READ plot WRITE setPlot NOTIFY plotChanged)

    Q_PROPERTY(Style style READ style WRITE setStyle NOTIFY styleChanged)
    Q_PROPERTY(bool antialiasing READ antialiasing WRITE setAntialiasing NOTIFY antialiasingChanged)
public:
    enum class Style
    {
        /*! Don't draw a curve. Note: This doesn't affect the symbols. */
        NoCurve = -1,
        /*! Connect the points with straight lines. The lines might be interpolated depending on the 'Fitted' attribute.
         *  Curve fitting can be configured using setCurveFitter(). */
        Lines,
        /*! Draw vertical or horizontal sticks ( depending on the orientation() ) from a baseline which is defined by
         *  setBaseline(). */
        Sticks,
        /*! Connect the points with a step function. The step function is drawn from the left to the right or vice versa,
         *  depending on the Inverted attribute. */
        Steps,
        /*! Draw dots at the locations of the data points.
         *  Note: This is different from a dotted line (see setPen()), and faster as a curve in NoStyle style and
         *  a symbol painting a point. */
        Dots,
        /*! Styles >= UserCurve are reserved for derived classes of QwtPlotCurve that overload drawCurve() with
         *  additional application specific curve types. */
        UserCurve = 100
    };
    Q_ENUM(Style)

    enum class Attribute
    {
        /*! For Style::Steps only. Draws a step function from the right to the left. */
        Inverted = 0x01,
        /*! Only in combination with Style::Lines A CurveFitter tries to interpolate/smooth the curve, before it is
         *  painted.
         *  \note Curve fitting requires temporary memory for calculating coefficients and additional points.
         *  If painting in Attribute::Fitted mode is slow it might be better to fit the points, before they are
         *  passed to QwtPlotCurve.
         */
        Fitted = 0x02
    };
    Q_ENUM(Attribute)

    enum class RenderHint
    {
        //! Enable antialiasing
        Antialiasing = 0x1
    };
    Q_ENUM(RenderHint)

    explicit QExtQuickQwtPlotCurve(QObject *parent = nullptr);
    QExtQuickQwtPlotCurve(const QString& title, QObject *parent = nullptr);
    QExtQuickQwtPlotCurve(QExtQuickQwtPlotCurvePrivate *d, QObject* parent = nullptr);
    ~QExtQuickQwtPlotCurve() override;

    QExtQuickQwtPlot *plot() const;
    void setPlot(QExtQuickQwtPlot *plot);

    void detach() { this->setPlot(nullptr); }
    void attach(QExtQuickQwtPlot *plot) { this->setPlot(plot); }

    QExtQmlPenInfo *pen();
    const QExtQmlPenInfo *pen() const;

    QColor penColor() const;
    void setPenColor(const QColor &color);

    Style style() const;
    void setStyle(Style style);

    bool antialiasing() const;
    void setAntialiasing(bool on = true);

    QExtQuickQwtSeriesData<QPointF>* seriesData() { return this->data(); }
    void setSeriesData(QExtQuickQwtSeriesData<QPointF>* series) { this->setData(series); }

    Q_INVOKABLE bool testRenderHint(RenderHint hint) const;
    Q_INVOKABLE void setRenderHint(RenderHint hint, bool on = true);

    Q_INVOKABLE bool testAttribute(Attribute attribute) const;
    Q_INVOKABLE void setAttribute(Attribute attribute, bool on = true);

Q_SIGNALS:
    void styleChanged(Style style);
    void antialiasingChanged(bool on);
    void plotChanged(QExtQuickQwtPlot *plot);
    void penChanged(const QExtQmlPenInfo &pen);
    void renderHintChanged(RenderHint hint, bool on);
    void attributeChanged(Attribute attribute, bool on);
    void seriesDataChanged(QExtQuickQwtSeriesData<QPointF>* series);

protected:
    void onDataChanged() override;

    QScopedPointer<QExtQuickQwtPlotCurvePrivate> dd_ptr;

private:
    QEXT_QML_ELEMENT()
    friend class QExtQuickQwtPlot;
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtQuickQwtPlotCurve)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQuickQwtPlotCurve)
};

#endif // _QEXTQUICKQWTPLOTCURVE_H
