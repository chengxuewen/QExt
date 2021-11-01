#include "qtkeainterruptedexception_p.h"

QTKEAInterruptedException::QTKEAInterruptedException()
    : QTKRuntimeException("")
{

}

QTKEAInterruptedException::~QTKEAInterruptedException() throw()
{
}

const char *QTKEAInterruptedException::name() const throw()
{
    return "QTKEAInterruptedException";
}

QTKEAInterruptedException *QTKEAInterruptedException::clone() const
{
    return new QTKEAInterruptedException(*this);
}

void QTKEAInterruptedException::rethrow() const
{
    throw *this;
}
