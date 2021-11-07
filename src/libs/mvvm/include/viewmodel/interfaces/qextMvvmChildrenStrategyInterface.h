#ifndef _QEXTMVVMCHILDRENSTRATEGYINTERFACE_H
#define _QEXTMVVMCHILDRENSTRATEGYINTERFACE_H

#include <qextMvvmGlobal.h>
#include <QVector>

class QEXTMvvmItem;

//! Base class for strategies to find children, actual of fictional, of given item.

//! Reported vector of children might be different from actual children of given item.
//! The strategy is used in context of AbstractViewModel while exposing QEXTMvvmModel to Qt.
//! Thanks to this strategy QEXTMvvmViewModel decides which items to visit.

class QEXT_MVVM_API QEXTMvvmChildrenStrategyInterface
{
public:
    virtual ~QEXTMvvmChildrenStrategyInterface() = default;

    //! Returns vector of children of given item.
    virtual QVector<QEXTMvvmItem *> children(const QEXTMvvmItem* item) const = 0;
};


#endif // _QEXTMVVMCHILDRENSTRATEGYINTERFACE_H
