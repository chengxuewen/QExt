#include <qextMvvmModelHasChangedController.h>



//! Constructor of QEXTMvvmModelHasChangedController.
//! Acccept 'model' to listen, and a 'callback' to report about changes in a model.

QEXTMvvmModelHasChangedController::QEXTMvvmModelHasChangedController(QEXTMvvmModel *model, Callback callback)
    : QEXTMvvmModelListener(model), m_callback(callback)
{
    this->addItemDataChangedListener(QEXTMvvmItemRoleFunction(this, &QEXTMvvmModelHasChangedController::onDataChange));
    this->addItemInsertedListener(QEXTMvvmItemTagRowFunction(this, &QEXTMvvmModelHasChangedController::onItemInserted));
    this->addItemRemovedListener(QEXTMvvmItemTagRowFunction(this, &QEXTMvvmModelHasChangedController::onItemRemoved));
    this->addModelResetedListener(QEXTMvvmModelFunction(this, &QEXTMvvmModelHasChangedController::onModelReset));
}

//! Returns true if the model was changed since last call of resetChanged.

bool QEXTMvvmModelHasChangedController::hasChanged() const
{
    return m_hasChanged;
}

//! Reset has_changed flag.

void QEXTMvvmModelHasChangedController::resetChanged()
{
    m_hasChanged = false;
}

//! Sets 'has_changed' flag and reports back to client.

void QEXTMvvmModelHasChangedController::onDataChange(QEXTMvvmItem *, int)
{
    this->processChange();
}

void QEXTMvvmModelHasChangedController::onItemInserted(QEXTMvvmItem *, QEXTMvvmTagRow)
{
    this->processChange();
}

void QEXTMvvmModelHasChangedController::onItemRemoved(QEXTMvvmItem *, QEXTMvvmTagRow)
{
    this->processChange();
}

void QEXTMvvmModelHasChangedController::onModelReset(QEXTMvvmModel *)
{
    this->processChange();
}

void QEXTMvvmModelHasChangedController::processChange()
{
    m_hasChanged = true;
    if (m_callback.isValid())
    {
        m_callback();
    }
}
