#ifndef _QEXTPLOT_P_H
#define _QEXTPLOT_P_H

#include <qextPlot.h>
#include <qextOnceFlag.h>
#include <qextQwtPlotZoomer.h>
#include <qextQwtPlotScaleZoomer.h>

#include <qwt_text.h>
#include <qwt_symbol.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_shapeitem.h>
#include <qwt_plot_textlabel.h>

#include <QTimer>

class QExtPlotLayout : public QwtPlotLayout
{
public:
    QExtPlotLayout() : mAxisMinimumSize{0} {}

    double axisMinimumSize(int axisId) const
    {
        if (axisId >= 0 && axisId < QwtPlot::axisCnt)
        {
            return mAxisMinimumSize[axisId];
        }
        return -1;
    }
    void setAxisMinimumSize(int axisId, double size)
    {
        if (axisId >= 0 && axisId < QwtPlot::axisCnt)
        {
            mAxisMinimumSize[axisId] = size;
        }
    }


    void activate(const QwtPlot *plot, const QRectF &plotRect, Options options = 0x00) QEXT_OVERRIDE
    {
        QwtPlotLayout::activate(plot, plotRect, options);
        auto canvasRect = this->canvasRect();
        for (int i = 0; i < QwtPlot::axisCnt; ++i)
        {
            if (plot->axisEnabled(i))
            {
                switch (i)
                {
                case QwtPlot::yLeft:
                {
                    auto diff = mAxisMinimumSize[i] - this->scaleRect(i).width();
                    canvasRect.setX(canvasRect.x() + (diff > 0 ? diff : 0));
                    break;
                }
                case QwtPlot::yRight:
                {
                    auto diff = mAxisMinimumSize[i] - this->scaleRect(i).width();
                    canvasRect.setWidth(canvasRect.width() - (diff > 0 ? diff : 0));
                    break;
                }
                case QwtPlot::xTop:
                {
                    auto diff = mAxisMinimumSize[i] - this->scaleRect(i).height();
                    canvasRect.setY(canvasRect.y() + (diff > 0 ? diff : 0));
                    break;
                }
                case QwtPlot::xBottom:
                {
                    auto diff = mAxisMinimumSize[i] - this->scaleRect(i).height();
                    canvasRect.setHeight(canvasRect.height() - (diff > 0 ? diff : 0));
                    break;
                }
                default:
                    break;
                }
            }
        }
        this->setCanvasRect(canvasRect);
        for (int i = 0; i < QwtPlot::axisCnt; ++i)
        {
            if (plot->axisEnabled(i))
            {
                switch (i)
                {
                case QwtPlot::yLeft:
                {
                    auto scaleRect = this->scaleRect(i);
                    scaleRect.setTop(canvasRect.top());
                    scaleRect.setBottom(canvasRect.bottom());
                    scaleRect.setRight(canvasRect.left());
                    scaleRect.setWidth(qMax(scaleRect.width(), mAxisMinimumSize[i]));
                    this->setScaleRect(i, scaleRect);
                    break;
                }
                case QwtPlot::yRight:
                {
                    auto scaleRect = this->scaleRect(i);
                    scaleRect.setTop(canvasRect.top());
                    scaleRect.setBottom(canvasRect.bottom());
                    scaleRect.setLeft(canvasRect.right());
                    scaleRect.setWidth(qMax(scaleRect.width(), mAxisMinimumSize[i]));
                    this->setScaleRect(i, scaleRect);
                    break;
                }
                case QwtPlot::xTop:
                {
                    auto scaleRect = this->scaleRect(i);
                    scaleRect.setLeft(canvasRect.left());
                    scaleRect.setRight(canvasRect.right());
                    scaleRect.setBottom(canvasRect.top());
                    scaleRect.setHeight(qMax(scaleRect.height(), mAxisMinimumSize[i]));
                    this->setScaleRect(i, scaleRect);
                    break;
                }
                case QwtPlot::xBottom:
                {
                    auto scaleRect = this->scaleRect(i);
                    scaleRect.setLeft(canvasRect.left());
                    scaleRect.setRight(canvasRect.right());
                    scaleRect.setTop(canvasRect.bottom());
                    scaleRect.setHeight(qMax(scaleRect.height(), mAxisMinimumSize[i]));
                    this->setScaleRect(i, scaleRect);
                    break;
                }
                default:
                    break;
                }
            }
        }
    }

private:
    double mAxisMinimumSize[QwtPlot::axisCnt];
};


class QExtPlotPrivate
{
    qint64 mId;
    QString mName;
    QString mGroupName;
    QExtPlot * const q_ptr;
    QEXT_DECL_PUBLIC(QExtPlot)
    QEXT_DISABLE_COPY_MOVE(QExtPlotPrivate)
public:
    explicit QExtPlotPrivate(QExtPlot *q);
    virtual ~QExtPlotPrivate();

    double mXMin;
    double mXMax;
    double mYMin;
    double mYMax;
    double mPlotWidth;
    bool mPlotVisible;

    QScopedPointer<QExtPlotAutoRangeUpdater> mXAxisAutoRangeUpdater;
    QScopedPointer<QExtPlotAutoRangeUpdater> mYAxisAutoRangeUpdater;

    QwtPlotGrid mGrid;
    QExtPlotZoomer *mZoomer;
    QExtPlotLayout *mLayout;
    QExtPlotScaleZoomer *mScaleZoomer;

    QTimer mReplotTimer;
    QExtOnceFlag mInitOnceFlag;

    QScopedPointer<QExtPropertyModel> mPropertyModel;
};

#endif // _QEXTPLOT_P_H
