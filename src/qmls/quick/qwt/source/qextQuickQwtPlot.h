#ifndef _QEXTQUICKQWTPLOT_H
#define _QEXTQUICKQWTPLOT_H

#include <qextQmlRegistration.h>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>

#include <QQuickPaintedItem>

class QExtQuickQwtPlot : public QQuickPaintedItem
{
    Q_OBJECT
    QEXT_QML_ELEMENT()
public:
    QExtQuickQwtPlot(QQuickItem* parent = nullptr);
    virtual ~QExtQuickQwtPlot();

    void paint(QPainter* painter);

    Q_INVOKABLE void initQwtPlot();

protected:
    void routeMouseEvents(QMouseEvent* event);
    void routeWheelEvents(QWheelEvent* event);

    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent *event);

    virtual void timerEvent(QTimerEvent *event);

private:
    QwtPlot*         m_qwtPlot;
    QwtPlotCurve*    m_curve1;
    QVector<QPointF> m_curve1_data;
    int              m_timerId;

    void replotAndUpdate();

private slots:
    void updatePlotSize();

};

#endif // _QEXTQUICKQWTPLOT_H
