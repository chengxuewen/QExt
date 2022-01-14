#ifndef _QEXTMVVMPLOTTINGAXISTITLECONTROLLER_H
#define _QEXTMVVMPLOTTINGAXISTITLECONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <memory>

class QCPAxis;

namespace ModelView
{

class QEXTMvvmTextItem;

//! Propagates title settings from TextItem to QCPAxis.

class QEXT_MVVM_API QEXTMvvmAxisTitleController : public QEXTMvvmItemListener<QEXTMvvmTextItem>
{
public:
    explicit QEXTMvvmAxisTitleController(QCPAxis* axis);
    ~QEXTMvvmAxisTitleController() override;

protected:
    void subscribe() override;

public:
    struct AxisTitleControllerImpl;
    std::unique_ptr<AxisTitleControllerImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGAXISTITLECONTROLLER_H
