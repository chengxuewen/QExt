#ifndef _QEXTQUICKQWTPLOT_P_H
#define _QEXTQUICKQWTPLOT_P_H

#include <qextQuickQwtPlot.h>
#include <qextQuickQwtPlotCurve.h>

#include <qwt_plot.h>

#include <QPainter>

class QExtQuickQwtPlotPrivate
{
public:
//    class QuickQwtPlot : public QwtPlot
//    {
//    public:
//        QuickQwtPlot(QWidget *parent = nullptr) : QwtPlot(parent) {}

//    protected:
//        void drawContents(QPainter *painter) override
//        {
//            painter->setRenderHint(QPainter::Antialiasing);
//            // 设置背景透明
//            painter->setOpacity(0.0); // 设置为完全透明
//            painter->fillRect(rect(), Qt::transparent); // 用透明背景填充矩形区域
//            QwtPlot::drawContents(painter); // 调用基类绘制
//        }
//    };

    explicit QExtQuickQwtPlotPrivate(QExtQuickQwtPlot *q);
    virtual ~QExtQuickQwtPlotPrivate();

    static QExtQuickQwtPlot::AxisEnum fromQwt(QwtPlot::Axis axis);
    static QwtPlot::Axis toQwt(QExtQuickQwtPlot::AxisEnum axis);

    /* avoid QWidget: Cannot create a QWidget without QApplication error while qmlplugindump */
    QwtPlot *qwtPlot();
    const QwtPlot *qwtPlot() const;

    QScopedPointer<QwtPlot> mQwtPlot{nullptr};

protected:
    QExtQuickQwtPlot * const q_ptr;
    Q_DECLARE_PUBLIC(QExtQuickQwtPlot)
    Q_DISABLE_COPY(QExtQuickQwtPlotPrivate)
};

#endif // _QEXTQUICKQWTPLOT_P_H
