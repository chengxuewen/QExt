// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SIGNALS_MODELLISTENER_H
#define MVVM_SIGNALS_MODELLISTENER_H

#include "model/signals/modellistenerbase.h"

namespace ModelView {

class QExtMvvmSessionItem;

//! Templated class for all objects willing to listen for changes in concrete QExtMvvmSessionModel.

template <typename T> class QExtMvvmModelListener : public ModelListenerBase {
public:
    QExtMvvmModelListener(T* session_model) : ModelListenerBase(session_model) {}

    T* model() const { return static_cast<T*>(m_model); }
};

} // namespace ModelView

#endif // MVVM_SIGNALS_MODELLISTENER_H
