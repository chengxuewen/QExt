#ifndef _QEXTPLOT_H
#define _QEXTPLOT_H

#include <qextPlotGlobal.h>
#include <qextSerializable.h>

#include <qwt_plot.h>

class QExtPlotPrivate;
class QEXT_PLOT_API QExtPlot : public QwtPlot, public QExtSerializable
{
    Q_OBJECT
public:
    explicit QExtPlot(QWidget *parent = QEXT_NULLPTR);
    explicit QExtPlot(QExtPlotPrivate *d, QWidget *parent = QEXT_NULLPTR);
    explicit QExtPlot(const QwtText &title, QWidget *parent = QEXT_NULLPTR);
    ~QExtPlot() QEXT_OVERRIDE;

    void serializeLoad(const SerializedItems &items) QEXT_OVERRIDE;
    SerializedItems serializeSave() const QEXT_OVERRIDE;

protected:
    QScopedPointer<QExtPlotPrivate> dd_ptr;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtPlot)
    QEXT_DISABLE_COPY_MOVE(QExtPlot)
};

#endif //_QEXTPLOT_H
