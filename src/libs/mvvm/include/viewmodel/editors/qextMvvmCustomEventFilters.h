#ifndef _QEXTMVVMCUSTOMEVENTFILTERS_H
#define _QEXTMVVMCUSTOMEVENTFILTERS_H

#include <qextMvvmGlobal.h>

#include <QObject>

//! Event filter to prevent loss of the focus.
//! Can be used in the context of QTreeView and similar widgets to call external editor. Such an
//! editor is created by clicking on a cell of a tree and it appears as  modal window on top of a
//! tree.
class QEXT_MVVM_API QEXTMvvmLostFocusFilter : public QObject
{
    Q_OBJECT
public:
    QEXTMvvmLostFocusFilter(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTMvvmLostFocusFilter();

protected:
    bool eventFilter(QObject *obj, QEvent *event) QEXT_DECL_OVERRIDE;
};

//! Event filter to install on combo boxes and spin boxes to ignore wheel events during scrolling.
//! Helpful than the spin box is a child of some larger scroll area.
class QEXT_MVVM_API QEXTMvvmWheelEventFilter : public QObject
{
    Q_OBJECT
public:
    QEXTMvvmWheelEventFilter(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTMvvmWheelEventFilter();

protected:
    bool eventFilter(QObject *obj, QEvent *event) QEXT_DECL_OVERRIDE;
};

#endif // _QEXTMVVMCUSTOMEVENTFILTERS_H
