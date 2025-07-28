#ifndef _QEXTQWTPLOTSCALEZOOMER_H
#define _QEXTQWTPLOTSCALEZOOMER_H

#include <qextQwtPlotScalePicker.h>

#include <qwt_plot_zoomer.h>
#include <qwt_plot.h>

class QExtPlotScaleZoomerPrivate;
class QEXT_PLOT_API QExtPlotScaleZoomer : public QObject
{
    Q_OBJECT
public:
    QExtPlotScaleZoomer(QwtPlot *plot, QwtPlotZoomer *zoomer);
    ~QExtPlotScaleZoomer() QEXT_OVERRIDE;

    void setPickerPen(QPen pen);
    void setLeftPickerValueResolution(int value);
    void setBottomPickerValueResolution(int value);

private Q_SLOTS:
    void leftPicked(double firstPos, double lastPos);
    void bottomPicked(double firstPos, double lastPos);

private:
    QScopedPointer<QExtPlotScaleZoomerPrivate> dd_ptr;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtPlotScaleZoomer)
    QEXT_DISABLE_COPY_MOVE(QExtPlotScaleZoomer)
};

#endif // _QEXTQWTPLOTSCALEZOOMER_H
