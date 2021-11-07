#ifndef _QEXTMVVMMODELLISTENER_H
#define _QEXTMVVMMODELLISTENER_H

#include <qextMvvmModelListenerBase.h>

//! Templated class for all objects willing to listen for changes in concrete QEXTMvvmModel.

template <typename T>
class QEXTMvvmModelListener : public QEXTMvvmModelListenerBase
{
public:
    QEXTMvvmModelListener(T* model) : QEXTMvvmModelListenerBase(model) {}

    T* model() const { return static_cast<T*>(m_model); }
};

#endif // _QEXTMVVMMODELLISTENER_H
