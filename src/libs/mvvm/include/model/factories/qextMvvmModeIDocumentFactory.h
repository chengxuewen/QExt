#ifndef _QEXTMVVMMODELDOCUMENTFACTORY_H
#define _QEXTMVVMMODELDOCUMENTFACTORY_H

#include <memory>
#include <qextMvvmModelDocumentInterface.h>
#include <vector>

namespace ModelView
{

class QEXTMvvmSessionModel;

//! Creates QEXTMvvmJsonDocument to save and load models.
QEXT_MVVM_API std::unique_ptr<QEXTMvvmModelDocumentInterface>
CreateJsonDocument(const std::vector<QEXTMvvmSessionModel*>& models);

} // namespace ModelView

#endif // _QEXTMVVMMODELDOCUMENTFACTORY_H
