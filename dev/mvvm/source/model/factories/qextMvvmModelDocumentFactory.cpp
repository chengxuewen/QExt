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

namespace ModelView {

QExtUniquePointer<QExtMvvmModelDocumentInterface> qextMvvmCreateJsonDocument(const std::vector<QExtMvvmSessionModel*>& models)
{
    return qextMakeUnique<QExtMvvmJsonDocument>(models);
}

} // namespace ModelView
