#ifndef _QEXTQWTPLOTZOOMER_H
#define _QEXTQWTPLOTZOOMER_H

#include <qextQwtPlotScrollZoomer.h>

class QExtPlotZoomer;
typedef void(*QExtPlotZoomerValueDrawFunc)(const QExtPlotZoomer *zoomer, QPainter *painter);

class QExtPlotZoomerPrivate;
class QEXT_PLOT_API QExtPlotZoomer : public QExtPlotScrollZoomer
{
    Q_OBJECT
public:
    explicit QExtPlotZoomer(QwtPlot *plot);
    ~QExtPlotZoomer() QEXT_OVERRIDE;

    int valueResolution() const;
    void setValueResolution(int value);

    bool isPressDragEnable() const;
    void setPressDragEnable(bool enable);

    bool isDrawValuesEnable() const;
    void setDrawValuesEnable(bool enable);

    void zoom(int up) QEXT_OVERRIDE;
    void zoom(const QRectF &) QEXT_OVERRIDE;

    /// Set displayed channels for value tracking (can be null)
    // void setDispChannels(QVector< const MVChannel * > channels);
    // void setValueDrawFunc(QExtPlotZoomerValueDrawFunc func);

    void drawScaleOverlay(QPainter *painter); // called from QwtWidgetOverlay

    QPoint transToPos( const QPointF &point) const;
    QPointF transToValue( const QPoint &point) const;

Q_SIGNALS:
    void unzoomed();

protected:
    /// Re-implemented to display selection size in the tracker text.
    QwtText trackerTextF(const QPointF &pos) const QEXT_OVERRIDE;
    /// Re-implemented for sample value tracker
    QRect trackerRect(const QFont &) const QEXT_OVERRIDE;
    /// Re-implemented for alpha background
    void drawRubberBand(QPainter *painter) const QEXT_OVERRIDE;
    /// Re-implemented to draw sample values
    void drawTracker(QPainter *painter) const QEXT_OVERRIDE;
    /// Re-implemented for alpha background (masking is basically disabled)
    QRegion rubberBandMask() const QEXT_OVERRIDE;

    /// Overloaded for panning
    void widgetMousePressEvent(QMouseEvent *mouseEvent) QEXT_OVERRIDE;
    void widgetMouseReleaseEvent(QMouseEvent *mouseEvent) QEXT_OVERRIDE;
    void widgetMouseMoveEvent(QMouseEvent *mouseEvent) QEXT_OVERRIDE;
    void widgetMouseDoubleClickEvent(QMouseEvent * mouseEvent) QEXT_OVERRIDE;

    void widgetKeyPressEvent(QKeyEvent *keyEvent) QEXT_OVERRIDE;
    void widgetKeyReleaseEvent(QKeyEvent *keyEvent) QEXT_OVERRIDE;

    void updateCursor();

private:
    /// Get a list of visible channels
    // QList< const MVChannel * > visChannels() const;
    /// Draw sample values
    void drawValues(QPainter *painter) const;
    /// Returns trackerRect for value tracker
    QRect valueTrackerRect(const QFont &font) const;

private:
    QScopedPointer<QExtPlotZoomerPrivate> dd_ptr;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtPlotZoomer)
    QEXT_DISABLE_COPY_MOVE(QExtPlotZoomer)
};

#endif // _QEXTQWTPLOTZOOMER_H
