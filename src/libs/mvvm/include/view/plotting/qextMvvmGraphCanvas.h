#ifndef _QEXTMVVMPLOTTINGGRAPHCANVAS_H
#define _QEXTMVVMPLOTTINGGRAPHCANVAS_H

#include <qextMvvmGlobal.h>

#include <QWidget>

#include <memory>

namespace ModelView
{

class QEXTMvvmGraphViewportItem;
class QEXTMvvmSceneAdapterInterface;

//! Widget to show scientific figure with multiple 1D graphs.
//! Contains embedded QCustomPlot widget, shows content of GraphViewportItem.

class QEXT_MVVM_API QEXTMvvmGraphCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit QEXTMvvmGraphCanvas(QWidget* parent = nullptr);
    ~QEXTMvvmGraphCanvas() override;

    void setItem(QEXTMvvmGraphViewportItem* viewport_item);

    std::unique_ptr<QEXTMvvmSceneAdapterInterface> createSceneAdapter() const;

    void setViewportToContent(double left, double top, double right, double bottom);

    void setViewportToContent();

    void setAxisMargins(int left, int top, int right, int bottom);

signals:
    void axisMarginsChanged(int left, int top, int right, int bottom);

private:
    struct GraphCanvasImpl;
    std::unique_ptr<GraphCanvasImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGGRAPHCANVAS_H
