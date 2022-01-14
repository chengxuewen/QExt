#ifndef _QEXTMVVMEDITORSCUSTOMEVENTFILTERS_H
#define _QEXTMVVMEDITORSCUSTOMEVENTFILTERS_H

#include <qextMvvmGlobal.h>

#include <QObject>

namespace ModelView
{

//! Event filter to prevent loss of the focus.
//! Can be used in the context of QTreeView and similar widgets to call external editor. Such an
//! editor is created by clicking on a cell of a tree and it appears as  modal window on top of a
//! tree.

class QEXT_MVVM_API QEXTMvvmLostFocusFilter : public QObject
{
    Q_OBJECT

public:
    QEXTMvvmLostFocusFilter(QObject* parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};

//! Event filter to install on combo boxes and spin boxes to ignore wheel events during scrolling.
//! Helpful than the spin box is a child of some larger scroll area.

class QEXT_MVVM_API QEXTMvvmWheelEventFilter : public QObject
{
    Q_OBJECT

public:
    QEXTMvvmWheelEventFilter(QObject* parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

} // namespace ModelView

#endif // _QEXTMVVMEDITORSCUSTOMEVENTFILTERS_H
