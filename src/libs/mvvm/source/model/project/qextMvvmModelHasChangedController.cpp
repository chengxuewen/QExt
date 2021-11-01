// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <project/qextMvvmModelHasChangedController.h>

using namespace ModelView;

//! Constructor of QEXTMvvmModelHasChangedController.
//! Acccept 'model' to listen, and a 'callback' to report about changes in a model.

QEXTMvvmModelHasChangedController::QEXTMvvmModelHasChangedController(QEXTMvvmSessionModel* model, callback_t callback)
    : QEXTMvvmModelListener(model), m_callback(callback)
{
    setOnDataChange([this](auto, auto) { process_change(); });
    setOnItemInserted([this](auto, auto) { process_change(); });
    setOnItemRemoved([this](auto, auto) { process_change(); });
    setOnModelReset([this](auto) { process_change(); });
}

//! Returns true if the model was changed since last call of resetChanged.

bool QEXTMvvmModelHasChangedController::hasChanged() const
{
    return m_has_changed;
}

//! Reset has_changed flag.

void QEXTMvvmModelHasChangedController::resetChanged()
{
    m_has_changed = false;
}

//! Sets 'has_changed' flag and reports back to client.

void QEXTMvvmModelHasChangedController::process_change()
{
    m_has_changed = true;
    if (m_callback)
        m_callback();
}
