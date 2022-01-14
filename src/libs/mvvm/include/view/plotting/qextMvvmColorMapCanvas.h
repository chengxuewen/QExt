#ifndef _QEXTMVVMPLOTTINGCOLORMAPCANVAS_H
#define _QEXTMVVMPLOTTINGCOLORMAPCANVAS_H

#include <qextMvvmGlobal.h>

#include <QWidget>

#include <memory>

namespace ModelView
{

class QEXTMvvmColorMapViewportItem;
class QEXTMvvmSceneAdapterInterface;

//! Widget to show 2D data as color map.
//! Contains embedded QCustomPlot widget, shows content of ColorMapViewportItem.

class QEXT_MVVM_API QEXTMvvmColorMapCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit QEXTMvvmColorMapCanvas(QWidget* parent = nullptr);
    ~QEXTMvvmColorMapCanvas() override;

    void setItem(QEXTMvvmColorMapViewportItem* viewport_item);

    std::unique_ptr<QEXTMvvmSceneAdapterInterface> createSceneAdapter() const;

private:
    struct ColorMapCanvasImpl;
    std::unique_ptr<ColorMapCanvasImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGCOLORMAPCANVAS_H
