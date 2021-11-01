#ifndef _QEXTMVVMITEMCATALOGUEFACTORY_H
#define _QEXTMVVMITEMCATALOGUEFACTORY_H

#include <qextMvvmItemCatalogue.h>

namespace ModelView
{

//! Creates a catalog of items supported by QEXTMvvmSessionModel out-of-the-box.
QEXT_MVVM_API std::unique_ptr<QEXTMvvmItemCatalogue> CreateStandardItemCatalogue();

} // namespace ModelView

#endif // _QEXTMVVMITEMCATALOGUEFACTORY_H
