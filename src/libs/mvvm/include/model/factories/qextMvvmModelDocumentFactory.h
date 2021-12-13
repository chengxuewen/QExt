// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_FACTORIES_MODELDOCUMENTFACTORY_H
#define MVVM_FACTORIES_MODELDOCUMENTFACTORY_H

#include <memory>
#include <qextMvvmModelDocumentInterface.h>
#include <vector>

namespace ModelView
{

class SessionModel;

//! Creates JsonDocument to save and load models.
QEXT_MVVM_API std::unique_ptr<QEXTMVVMModelDocumentInterface>
CreateJsonDocument(const std::vector<SessionModel*>& models);

} // namespace ModelView

#endif // MVVM_FACTORIES_MODELDOCUMENTFACTORY_H
