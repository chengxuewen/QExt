#include <qextMvvmModelListenerBase.h>
#include <qextMvvmModelMapper.h>
#include <qextMvvmModel.h>

#include <stdexcept>

QEXTMvvmModelListenerBase::QEXTMvvmModelListenerBase(QEXTMvvmModel *model)
    : m_model(model)
{
    if (!m_model)
    {
        throw std::runtime_error("Error in QEXTMvvmModelListenerBase: no model defined");
    }
    this->addModelDestroyedListener([this](QEXTMvvmModel *) { m_model = QEXT_DECL_NULLPTR; });
}

QEXTMvvmModelListenerBase::~QEXTMvvmModelListenerBase()
{
    this->removeListener();
}

QEXTConnection QEXTMvvmModelListenerBase::addItemAboutToBeInsertedListener(QEXTMvvmItemTagRowFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_model->mapper()->addItemAboutToBeInsertedListener(function, this);
}

QEXTConnection QEXTMvvmModelListenerBase::addItemInsertedListener(QEXTMvvmItemTagRowFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_model->mapper()->addItemInsertedListener(function, this);
}

QEXTConnection QEXTMvvmModelListenerBase::addItemAboutToBeRemovedListener(QEXTMvvmItemTagRowFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_model->mapper()->addItemAboutToBeRemovedListener(function, this);
}

QEXTConnection QEXTMvvmModelListenerBase::addItemRemovedListener(QEXTMvvmItemTagRowFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_model->mapper()->addItemRemovedListener(function, this);
}

QEXTConnection QEXTMvvmModelListenerBase::addItemDataAboutToBeChangedListener(QEXTMvvmItemRoleFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_model->mapper()->addItemDataAboutToBeChangedListener(function, this);
}

QEXTConnection QEXTMvvmModelListenerBase::addItemDataChangedListener(QEXTMvvmItemRoleFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_model->mapper()->addItemDataChangedListener(function, this);
}

QEXTConnection QEXTMvvmModelListenerBase::addItemAboutToBeDestroyedListener(QEXTMvvmItemFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_model->mapper()->addItemAboutToBeDestroyedListener(function, this);
}

QEXTConnection QEXTMvvmModelListenerBase::addItemDestroyedListener(QEXTMvvmItemFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_model->mapper()->addItemDestroyedListener(function, this);
}

QEXTConnection QEXTMvvmModelListenerBase::addModelAboutToBeDestroyedListener(QEXTMvvmModelFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_model->mapper()->addModelAboutToBeDestroyedListener(function, this);
}

QEXTConnection QEXTMvvmModelListenerBase::addModelDestroyedListener(QEXTMvvmModelFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_model->mapper()->addModelDestroyedListener(function, this);
}

QEXTConnection QEXTMvvmModelListenerBase::addModelAboutToBeResetedListener(QEXTMvvmModelFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_model->mapper()->addModelAboutToBeResetedListener(function, this);
}

QEXTConnection QEXTMvvmModelListenerBase::addModelResetedListener(QEXTMvvmModelFunction function, void *listener)
{
    Q_UNUSED(listener);
    return m_model->mapper()->addModelResetedListener(function, this);
}

void QEXTMvvmModelListenerBase::removeListener(void *listener)
{
    Q_UNUSED(listener);
    m_model->mapper()->removeListener(this);
}
