// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/project/modelhaschangedcontroller.h"

using namespace ModelView;

//! Constructor of QExtMvvmModelHasChangedController.
//! Acccept 'model' to listen, and a 'callback' to report about changes in a model.

QExtMvvmModelHasChangedController::QExtMvvmModelHasChangedController(QExtMvvmSessionModel* model, callback_t callback)
    : QExtMvvmModelListener(model), m_callback(callback)
{
    setOnDataChange([this](QExtMvvmSessionItem*, int) { process_change(); });
    setOnItemInserted([this](QExtMvvmSessionItem*, QExtMvvmTagRow) { process_change(); });
    setOnItemRemoved([this](QExtMvvmSessionItem*, QExtMvvmTagRow) { process_change(); });
    setOnModelReset([this](QExtMvvmSessionModel*) { process_change(); });
}

//! Returns true if the model was changed since last call of resetChanged.

bool QExtMvvmModelHasChangedController::hasChanged() const
{
    return m_has_changed;
}

//! Reset has_changed flag.

void QExtMvvmModelHasChangedController::resetChanged()
{
    m_has_changed = false;
}

//! Sets 'has_changed' flag and reports back to client.

void QExtMvvmModelHasChangedController::process_change()
{
    m_has_changed = true;
    if (m_callback)
        m_callback();
}
