#ifndef _QEXTMVVMCUSTOMPLOTSCENEADAPTER_H
#define _QEXTMVVMCUSTOMPLOTSCENEADAPTER_H

#include <qextMvvmSceneAdapterInterface.h>

#include <QScopedPointer>

class QCustomPlot;

//! Converts QGraphicsScene coordinates in the coordinates of local system of QCustomPlot
//! and vice versa.

class QEXT_MVVM_API QEXTMvvmCustomPlotSceneAdapter : public QEXTMvvmSceneAdapterInterface
{
public:
    explicit QEXTMvvmCustomPlotSceneAdapter(QCustomPlot* custom_plot);
    ~QEXTMvvmCustomPlotSceneAdapter() QEXT_DECL_OVERRIDE;

    double toSceneX(double customplot_x) const QEXT_DECL_OVERRIDE;

    double toSceneY(double customplot_y) const QEXT_DECL_OVERRIDE;

    double fromSceneX(double scene_x) const QEXT_DECL_OVERRIDE;

    double fromSceneY(double scene_y) const QEXT_DECL_OVERRIDE;

    QRectF viewportRectangle() const QEXT_DECL_OVERRIDE;

private:
    struct CustomPlotSceneAdapterImpl;
    QScopedPointer<CustomPlotSceneAdapterImpl> p_impl;
};

#endif // _QEXTMVVMCUSTOMPLOTSCENEADAPTER_H
