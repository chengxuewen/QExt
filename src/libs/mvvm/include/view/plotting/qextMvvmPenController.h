#ifndef _QEXTMVVMPENCONTROLLER_H
#define _QEXTMVVMPENCONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <QScopedPointer>

class QCPGraph;

class QEXTMvvmPenItem;

//! Establishes communication between QCPGraph and QEXTMvvmPenItem.
//! Provides update of QCPGraph's color, line style and width when QEXTMvvmPenItem is changed.

class QEXT_MVVM_API QEXTMvvmPenController : public QEXTMvvmItemListener<QEXTMvvmPenItem>
{
public:
    explicit QEXTMvvmPenController(QCPGraph* graph);
    ~QEXTMvvmPenController() QEXT_DECL_OVERRIDE;

protected:
    void subscribe() QEXT_DECL_OVERRIDE;

private:
    struct PenControllerImpl;
    QScopedPointer<PenControllerImpl> p_impl;
};

#endif // _QEXTMVVMPENCONTROLLER_H
