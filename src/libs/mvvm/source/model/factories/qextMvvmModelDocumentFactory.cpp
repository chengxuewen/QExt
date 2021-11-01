#include <qextMvvmModeIDocumentFactory.h>
#include <qextMvvmJsonDocument.h>

namespace ModelView
{

std::unique_ptr<QEXTMvvmModelDocumentInterface> CreateJsonDocument(const std::vector<QEXTMvvmSessionModel*>& models)
{
    return std::make_unique<QEXTMvvmJsonDocument>(models);
}

} // namespace ModelView
