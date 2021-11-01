#ifndef _QEXTMVVMITEMCOPYSTRATEGY_H
#define _QEXTMVVMITEMCOPYSTRATEGY_H

#include <memory>
#include <qextMvvmGlobal.h>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Interface for deep item copying.

class QEXT_MVVM_API QEXTMvvmItemCopyStrategy
{
public:
    virtual ~QEXTMvvmItemCopyStrategy() = default;

    //! Creates item copy by deep copying all children. QEXTMvvmSessionItem identifiers will be regenerated.
    virtual std::unique_ptr<QEXTMvvmSessionItem> createCopy(const QEXTMvvmSessionItem* item) const = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMITEMCOPYSTRATEGY_H
