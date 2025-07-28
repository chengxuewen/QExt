#ifndef _QEXTQWTPLOTSCALEPICKER_H
#define _QEXTQWTPLOTSCALEPICKER_H

#include <qextPlotGlobal.h>

#include <qwt_scale_widget.h>

#include <QMouseEvent>
#include <QObject>
#include <QWidget>
#include <QList>
#include <QPen>
#include <QMap>

class QExtPlotScalePickerPrivate;
class QEXT_PLOT_API QExtPlotScalePicker : public QObject
{
    Q_OBJECT
public:
    QExtPlotScalePicker(QwtScaleWidget *scaleWidget, QWidget *canvas);
    ~QExtPlotScalePicker() QEXT_OVERRIDE;

    int valueResolution() const;
    void setValueResolution(int value);

    void drawPlotOverlay(QPainter *painter); // called from QwtWidgetOverlay
    void drawScaleOverlay(QPainter *painter); // called from QwtWidgetOverlay
    void setPen(QPen pen);

Q_SIGNALS:
    void picked(double firstPos, double lastPos);

protected:
    bool eventFilter(QObject *, QEvent *) QEXT_OVERRIDE;

    double position(double) const; // returns the axis mouse position relative to plot coordinates
    int positionPx(QMouseEvent *); // returns the axis mouse position in pixels
    double posCanvasPx(double pos) const; // returns the given position in canvas coordinates


    void drawTriangle(QPainter *painter, int position);

    QwtText trackerText() const;
    QRectF trackerTextRect(QPainter *painter, int posPx, QSizeF textSize) const;
    QRectF pickTrackerTextRect(QPainter *painter, QRect pickRect, QSizeF textSize) const;

private Q_SLOTS:
    void updateSnapPoints();

private:
    QScopedPointer<QExtPlotScalePickerPrivate> dd_ptr;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtPlotScalePicker)
    QEXT_DISABLE_COPY_MOVE(QExtPlotScalePicker)
};

#endif // _QEXTQWTPLOTSCALEPICKER_H
