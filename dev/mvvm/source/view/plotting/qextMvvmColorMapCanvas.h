// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_COLORMAPCANVAS_H
#define MVVM_PLOTTING_COLORMAPCANVAS_H

#include <qextMvvmGlobal.h>
#include <QWidget>
#include <memory>

namespace ModelView {

class QExtMvvmColorMapViewportItem;
class QExtMvvmSceneAdapterInterface;

//! Widget to show 2D data as color map.
//! Contains embedded QCustomPlot widget, shows content of QExtMvvmColorMapViewportItem.

class QEXT_MVVM_API QExtMvvmColorMapCanvas : public QWidget {
    Q_OBJECT

public:
    explicit QExtMvvmColorMapCanvas(QWidget* parent = nullptr);
    ~QExtMvvmColorMapCanvas() override;

    void setItem(QExtMvvmColorMapViewportItem* viewport_item);

    QExtUniquePointer<QExtMvvmSceneAdapterInterface> createSceneAdapter() const;

private:
    struct ColorMapCanvasImpl;
    QExtUniquePointer<ColorMapCanvasImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_COLORMAPCANVAS_H
