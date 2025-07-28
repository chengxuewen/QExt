#ifndef _QEXTQWTPLOTCURVE_H
#define _QEXTQWTPLOTCURVE_H

#include <qextPlotGlobal.h>

#include <qwt_plot.h>
#include <qwt_scale_map.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_zoomer.h>
#include <qwt_scale_widget.h>

#include <QPointer>

class QEXT_PLOT_API QExtPlotCurve : public QwtPlotCurve
{
public:
    // class SymbolHandler
    // {
    // public:
    //     enum ModeEnum
    //     {
    //         Mode_Auto = 0,
    //         Mode_Show,
    //         Mode_Hide
    //     };

    //     SymbolHandler(QwtPlotCurve *curve, QwtPlot *plot, QwtPlotZoomer *zoomer = QEXT_NULLPTR);
    //     virtual ~SymbolHandler() {}

    //     int maxSymbolSize() const { return mMaxSymbolSize; }
    //     void setMaxSymbolSize(int size)
    //     {
    //         if (size != mMaxSymbolSize)
    //         {
    //             this->updateSymbolSize();
    //             this->updateSymbols();
    //         }
    //     }

    //     ModeEnum mode() const { return mMode; }
    //     void setMode(ModeEnum mode)
    //     {
    //         if (mode != mMode)
    //         {
    //             this->updateSymbolSize();
    //             this->updateSymbols();
    //         }
    //     }

    //     virtual void updateSymbols()
    //     {

    //     }
    //     virtual void updateSymbolSize()
    //     {
    //         if (mPlot.isNull())
    //         {
    //             QwtScaleWidget *scaleWidget = mPlot->axisWidget(QwtPlot::xBottom);
    //             double paintDist = scaleWidget->scaleDraw()->scaleMap().pDist();
    //             double scaleDist = scaleWidget->scaleDraw()->scaleMap().sDist();
    //             auto fullScaleDist = d->mZoomer->zoomBase().width();
    //             auto zoomRate = fullScaleDist / scaleDist;
    //             float plotWidthNumSamp = std::abs(d->mSampleCount * mPlot->width() / (d->mXMax - d->mXMin));
    //             float samplesInView = plotWidthNumSamp / zoomRate;
    //             int symDisPx = round(paintDist / samplesInView);

    //             if (symDisPx < SYMBOL_SHOW_AT_WIDTH)
    //             {
    //                 d->mSymbolSize = 0;
    //             }
    //             else
    //             {
    //                 d->mSymbolSize = std::min(SYMBOL_SIZE_MAX, symDisPx - SYMBOL_SHOW_AT_WIDTH + 1);
    //             }
    //         }
    //     }

    // private:
    //     ModeEnum mMode;
    //     int mMaxSymbolSize;
    //     QwtPlotCurve *mCurve;
    //     QPointer<QwtPlot> mPlot;
    //     QPointer<QwtPlotZoomer> mZoomer;
    // };

    explicit QExtPlotCurve(const QString &title = QString());
    explicit QExtPlotCurve(const QwtText &title );
    ~QExtPlotCurve() QEXT_OVERRIDE;

private:
    QEXT_DISABLE_COPY_MOVE(QExtPlotCurve)
};

#endif // _QEXTQWTPLOTCURVE_H
