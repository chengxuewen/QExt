// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmModelDocumentFactory.h>
#include <qextMvvmJsonDocument.h>
#include <qextMvvmTypes.h>

namespace ModelView
{

std::unique_ptr<QEXTMVVMModelDocumentInterface> CreateJsonDocument(const std::vector<QEXTMvvmSessionModel*>& models)
{
    return make_unique<QEXTMvvmJsonDocument>(models);
}

} // namespace ModelView
