#ifndef _QEXTQWTPLOTSCROLLZOOMER_H
#define _QEXTQWTPLOTSCROLLZOOMER_H

#include <qextPlotGlobal.h>
#include <qextQwtPlotScrollBar.h>

#include <qwt_plot_zoomer.h>

#include <QObject>

class QExtPlotScrollZoomerPrivate;
class QEXT_PLOT_API QExtPlotScrollZoomer : public QwtPlotZoomer
{
    Q_OBJECT
public:
    enum ScrollBarPosition
    {
        AttachedToScale,
        OppositeToScale
    };

    explicit QExtPlotScrollZoomer(QWidget *canvas);
    ~QExtPlotScrollZoomer() QEXT_OVERRIDE;

    QExtPlotScrollBar *horizontalScrollBar() const;
    QExtPlotScrollBar *verticalScrollBar() const;

    void setHScrollBarMode(Qt::ScrollBarPolicy mode);
    void setVScrollBarMode(Qt::ScrollBarPolicy mode);

    Qt::ScrollBarPolicy vScrollBarMode() const;
    Qt::ScrollBarPolicy hScrollBarMode() const;

    void setHScrollBarPosition(ScrollBarPosition pos);
    void setVScrollBarPosition(ScrollBarPosition pos);

    ScrollBarPosition hScrollBarPosition() const;
    ScrollBarPosition vScrollBarPosition() const;

    QWidget *cornerWidget() const;
    virtual void setCornerWidget(QWidget *widget);

    void setHViewSize(double size);
    void setXLimits(double min, double max);

    virtual void rescale();
    virtual void setZoomBase(bool doReplot = true);

public Q_SLOTS:
    virtual void moveTo(const QPointF &pos);

private Q_SLOTS:
    void scrollBarMoved(Qt::Orientation orientation, double min, double max);

protected:
    bool eventFilter(QObject *object, QEvent *event) QEXT_OVERRIDE;

    virtual QExtPlotScrollBar *scrollBar(Qt::Orientation orientation);

    virtual void layoutScrollBars(const QRect &rect);
    virtual void updateScrollBars();

private:
    bool needScrollBar(Qt::Orientation orientation) const;
    int oppositeAxis(int axis) const;

protected:
    QScopedPointer<QExtPlotScrollZoomerPrivate> dd_ptr;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtPlotScrollZoomer)
    QEXT_DISABLE_COPY_MOVE(QExtPlotScrollZoomer)
};

#endif // _QEXTQWTPLOTSCROLLZOOMER_H
