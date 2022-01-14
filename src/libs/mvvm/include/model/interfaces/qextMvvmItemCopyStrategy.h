#ifndef _QEXTMVVMSERIALIZATIONITEMCOPYSTRATEGY_H
#define _QEXTMVVMSERIALIZATIONITEMCOPYSTRATEGY_H

#include <qextMvvmGlobal.h>

#include <memory>

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

#endif // _QEXTMVVMSERIALIZATIONITEMCOPYSTRATEGY_H
