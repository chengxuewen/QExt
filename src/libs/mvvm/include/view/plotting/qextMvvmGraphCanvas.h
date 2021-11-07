#ifndef _QEXTMVVMGRAPHCANVAS_H
#define _QEXTMVVMGRAPHCANVAS_H

#include <QWidget>
#include <QScopedPointer>
#include <qextMvvmGlobal.h>

class QEXTMvvmGraphViewportItem;
class QEXTMvvmSceneAdapterInterface;

//! Widget to show scientific figure with multiple 1D graphs.
//! Contains embedded QCustomPlot widget, shows content of QEXTMvvmGraphViewportItem.

class QEXT_MVVM_API QEXTMvvmGraphCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit QEXTMvvmGraphCanvas(QWidget* parent = nullptr);
    ~QEXTMvvmGraphCanvas() QEXT_DECL_OVERRIDE;

    void setItem(QEXTMvvmGraphViewportItem* viewport_item);

    QEXTMvvmSceneAdapterInterface *createSceneAdapter() const;

    void setViewportToContent(double left, double top, double right, double bottom);

    void setViewportToContent();

    void setAxisMargins(int left, int top, int right, int bottom);

signals:
    void axisMarginsChanged(int left, int top, int right, int bottom);

private:
    struct QEXTMvvmGraphCanvasImpl;
    QScopedPointer<QEXTMvvmGraphCanvasImpl> p_impl;
};

#endif // _QEXTMVVMGRAPHCANVAS_H
