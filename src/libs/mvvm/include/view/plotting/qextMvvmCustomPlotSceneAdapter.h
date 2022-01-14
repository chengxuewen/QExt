#ifndef _QEXTMVVMPLOTTINGCUSTOMPLOTSCENEADAPTER_H
#define _QEXTMVVMPLOTTINGCUSTOMPLOTSCENEADAPTER_H

#include <qextMvvmSceneAdapterInterface.h>

#include <memory>

class QCustomPlot;

namespace ModelView
{

//! Converts QGraphicsScene coordinates in the coordinates of local system of QCustomPlot
//! and vice versa.

class QEXT_MVVM_API QEXTMvvmCustomPlotSceneAdapter : public QEXTMvvmSceneAdapterInterface
{
public:
    explicit QEXTMvvmCustomPlotSceneAdapter(QCustomPlot* custom_plot);
    ~QEXTMvvmCustomPlotSceneAdapter() override;

    double toSceneX(double customplot_x) const override;

    double toSceneY(double customplot_y) const override;

    double fromSceneX(double scene_x) const override;

    double fromSceneY(double scene_y) const override;

    QRectF viewportRectangle() const override;

private:
    struct CustomPlotSceneAdapterImpl;
    std::unique_ptr<CustomPlotSceneAdapterImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGCUSTOMPLOTSCENEADAPTER_H
