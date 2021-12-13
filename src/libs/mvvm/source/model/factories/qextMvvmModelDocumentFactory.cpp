// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmModelDocumentFactory.h>
#include <serialization/qextMvvmJsonDocument.h>

namespace ModelView
{

std::unique_ptr<ModelDocumentInterface> CreateJsonDocument(const std::vector<SessionModel*>& models)
{
    return std::make_unique<JsonDocument>(models);
}

} // namespace ModelView
