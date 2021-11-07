#ifndef _QEXTMVVMCOLORSCALEPLOTCONTROLLER_H
#define _QEXTMVVMCOLORSCALEPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <QScopedPointer>

class QCPColorScale;

class QEXTMvvmViewportAxisItem;

//! Establishes communication between QCPColorScale and QEXTMvvmViewportAxisItem.

class QEXT_MVVM_API QEXTMvvmColorScalePlotController : public QEXTMvvmItemListener<QEXTMvvmViewportAxisItem>
{
public:
    explicit QEXTMvvmColorScalePlotController(QCPColorScale* color_scale);
    ~QEXTMvvmColorScalePlotController() QEXT_DECL_OVERRIDE;

protected:
    void subscribe() QEXT_DECL_OVERRIDE;

public:
    struct ColorScalePlotControllerImpl;
    QScopedPointer<ColorScalePlotControllerImpl> p_impl;
};

#endif // _QEXTMVVMCOLORSCALEPLOTCONTROLLER_H
