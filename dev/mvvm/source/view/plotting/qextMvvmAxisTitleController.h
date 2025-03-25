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

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>
#include <memory>

class QCPAxis;

namespace ModelView {

class QExtMvvmTextItem;

//! Propagates title settings from QExtMvvmTextItem to QCPAxis.

class QEXT_MVVM_API QExtMvvmAxisTitleController : public QExtMvvmItemListener<QExtMvvmTextItem> {
public:
    explicit QExtMvvmAxisTitleController(QCPAxis* axis);
    ~QExtMvvmAxisTitleController() override;

protected:
    void subscribe() override;

public:
    struct AxisTitleControllerImpl;
    QExtUniquePointer<AxisTitleControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_AXISTITLECONTROLLER_H
