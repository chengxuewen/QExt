// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_AXISTITLECONTROLLER_H
#define MVVM_PLOTTING_AXISTITLECONTROLLER_H

#include <memory>
#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

class QCPAxis;

namespace ModelView
{

class QEXTMvvmTextItem;

//! Propagates title settings from QEXTMvvmTextItem to QCPAxis.

class QEXT_MVVM_API AxisTitleController : public QEXTMvvmItemListener<QEXTMvvmTextItem>
{
public:
    explicit AxisTitleController(QCPAxis* axis);
    ~AxisTitleController() override;

protected:
    void subscribe() override;

public:
    struct AxisTitleControllerImpl;
    std::unique_ptr<AxisTitleControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_AXISTITLECONTROLLER_H
