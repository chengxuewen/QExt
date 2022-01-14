#ifndef _QEXTMVVMFACTORIESMODELDOCUMENTFACTORY_H
#define _QEXTMVVMFACTORIESMODELDOCUMENTFACTORY_H

#include <qextMvvmModelDocumentInterface.h>

#include <memory>
#include <vector>

namespace ModelView
{

class QEXTMvvmSessionModel;

//! Creates JsonDocument to save and load models.
QEXT_MVVM_API std::unique_ptr<QEXTMVVMModelDocumentInterface>
CreateJsonDocument(const std::vector<QEXTMvvmSessionModel*>& models);

} // namespace ModelView

#endif // _QEXTMVVMFACTORIESMODELDOCUMENTFACTORY_H
