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

#include <qextMvvmModelDocumentInterface.h>
#include <memory>
#include <vector>

namespace ModelView {

class QExtMvvmSessionModel;

//! Creates QExtMvvmJsonDocument to save and load models.
QEXT_MVVM_API QExtUniquePointer<QExtMvvmModelDocumentInterface>
qextMvvmCreateJsonDocument(const std::vector<QExtMvvmSessionModel*>& models);

} // namespace ModelView

#endif // MVVM_FACTORIES_MODELDOCUMENTFACTORY_H
