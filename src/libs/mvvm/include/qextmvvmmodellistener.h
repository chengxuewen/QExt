#ifndef QEXTMVVMMODELLISTENER_H
#define QEXTMVVMMODELLISTENER_H

#include <qextmvvmglobal.h>
#include <qextmvvmabstractmodellistener.h>



template <typename T>
class QEXTMvvmModelListener : public QEXTMvvmAbstractModelListener
{
public:
    QEXTMvvmModelListener(T *model) : QEXTMvvmAbstractModelListener(model) {}

    T* model() const { return static_cast<T*>(m_model); }
};



#endif // QEXTMVVMMODELLISTENER_H
