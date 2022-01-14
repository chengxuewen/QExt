#ifndef _QEXTMVVMINTERFACESCHILDRENSTRATEGYINTERFACE_H
#define _QEXTMVVMINTERFACESCHILDRENSTRATEGYINTERFACE_H

#include <qextMvvmGlobal.h>

#include <vector>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Base class for strategies to find children, actual of fictional, of given item.

//! Reported vector of children might be different from actual children of given item.
//! The strategy is used in context of AbstractViewModel while exposing SessionModel to Qt.
//! Thanks to this strategy ViewModel decides which items to visit.

class QEXT_MVVM_API QEXTMvvmChildrenStrategyInterface
{
public:
    virtual ~QEXTMvvmChildrenStrategyInterface() = default;

    //! Returns vector of children of given item.
    virtual std::vector<QEXTMvvmSessionItem*> children(const QEXTMvvmSessionItem* item) const = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMINTERFACESCHILDRENSTRATEGYINTERFACE_H
