#ifndef _QEXTMVVMMODELLISTENER_H
#define _QEXTMVVMMODELLISTENER_H

#include <qextMvvmModelListenerBase.h>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Templated class for all objects willing to listen for changes in concrete QEXTMvvmSessionModel.

template <typename T> class QEXTMvvmModelListener : public QEXTMvvmModelListenerBase
{
public:
    QEXTMvvmModelListener(T* session_model) : QEXTMvvmModelListenerBase(session_model) {}

    T* model() const { return static_cast<T*>(m_model); }
};

} // namespace ModelView

#endif // _QEXTMVVMMODELLISTENER_H
