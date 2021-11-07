#ifndef _QEXTMVVMAXISTITLECONTROLLER_H
#define _QEXTMVVMAXISTITLECONTROLLER_H

#include <qextMvvmItemListener.h>
#include <qextMvvmGlobal.h>

#include <QScopedPointer>

class QCPAxis;


class QEXTMvvmTextItem;

//! Propagates title settings from QEXTMvvmTextItem to QCPAxis.

class QEXT_MVVM_API QEXTMvvmAxisTitleController : public QEXTMvvmItemListener<QEXTMvvmTextItem>
{
public:
    explicit QEXTMvvmAxisTitleController(QCPAxis* axis);
    ~QEXTMvvmAxisTitleController() QEXT_DECL_OVERRIDE;

protected:
    void subscribe() QEXT_DECL_OVERRIDE;

public:
    struct AxisTitleControllerImpl;
    QScopedPointer<AxisTitleControllerImpl> p_impl;
};


#endif // _QEXTMVVMAXISTITLECONTROLLER_H
