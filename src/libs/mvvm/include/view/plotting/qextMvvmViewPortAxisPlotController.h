#ifndef _QEXTMVVMVIEWPORTAXISPLOTCONTROLLER_H
#define _QEXTMVVMVIEWPORTAXISPLOTCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <QScopedPointer>

class QCPAxis;

class QEXTMvvmViewportAxisItem;

//! Establishes communication between QCPAxis and QEXTMvvmViewportAxisItem.
//! Provide mutual update of axis parameters (min, max, title) for two axes representations.

class QEXT_MVVM_API QEXTMvvmViewportAxisPlotController : public QEXTMvvmItemListener<QEXTMvvmViewportAxisItem>
{
public:
    explicit QEXTMvvmViewportAxisPlotController(QCPAxis* axis);
    ~QEXTMvvmViewportAxisPlotController() QEXT_DECL_OVERRIDE;

protected:
    void subscribe() QEXT_DECL_OVERRIDE;
    void unsubscribe() QEXT_DECL_OVERRIDE;

public:
    struct AxesPlotControllerImpl;
    QScopedPointer<AxesPlotControllerImpl> p_impl;
};

#endif // _QEXTMVVMVIEWPORTAXISPLOTCONTROLLER_H
