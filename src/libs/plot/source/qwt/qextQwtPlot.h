#ifndef _QEXTQWTPLOT_H
#define _QEXTQWTPLOT_H

#include <qextPlot.h>

#include <qwt_plot.h>

class QExtQwtPlotPrivate;
class QEXT_PLOT_API QExtQwtPlot : public QExtPlot
{
public:
    // enum SymbolsModeEnum
    // {
    //     SymbolsMode_Auto = 0,
    //     SymbolsMode_Show,
    //     SymbolsMode_Hide
    // };

    explicit QExtQwtPlot(QWidget *parent = QEXT_NULLPTR) {}
    explicit QExtQwtPlot(QExtQwtPlotPrivate *d, QWidget *parent = QEXT_NULLPTR) {}
    explicit QExtQwtPlot(const QwtText &title, QWidget *parent = QEXT_NULLPTR) {}
    ~QExtQwtPlot() QEXT_OVERRIDE {}


};

#endif // _QEXTQWTPLOT_H
