#ifndef _QEXTMVVMPLOTTINGPENCONTROLLER_H
#define _QEXTMVVMPLOTTINGPENCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <memory>

class QCPGraph;

namespace ModelView
{

class QEXTMvvmPenItem;

//! Establishes communication between QCPGraph and PenItem.
//! Provides update of QCPGraph's color, line style and width when PenItem is changed.

class QEXT_MVVM_API QEXTMvvmPenController : public QEXTMvvmItemListener<QEXTMvvmPenItem>
{
public:
    explicit QEXTMvvmPenController(QCPGraph* graph);
    ~QEXTMvvmPenController() override;

protected:
    void subscribe() override;

private:
    struct PenControllerImpl;
    std::unique_ptr<PenControllerImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMPLOTTINGPENCONTROLLER_H
