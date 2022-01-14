#ifndef _QEXTMVVMFACTORIESSTANDARDITEMCATALOGUE_H
#define _QEXTMVVMFACTORIESSTANDARDITEMCATALOGUE_H

#include <qextMvvmItemCatalogue.h>

namespace ModelView
{

//! Creates a catalog of items supported by SessionModel out-of-the-box.
QEXT_MVVM_API std::unique_ptr<QEXTMvvmItemCatalogue> CreateStandardItemCatalogue();

} // namespace ModelView

#endif // _QEXTMVVMFACTORIESSTANDARDITEMCATALOGUE_H
