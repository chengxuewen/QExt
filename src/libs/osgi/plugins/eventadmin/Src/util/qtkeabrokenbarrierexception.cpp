#include "qtkeabrokenbarrierexception_p.h"

QTKEABrokenBarrierException::QTKEABrokenBarrierException(int iIndex, const QString &strMessage)
    : QTKRuntimeException(strMessage),
      m_iIndex(iIndex)
{

}

QTKEABrokenBarrierException::~QTKEABrokenBarrierException() throw()
{
}

const char *QTKEABrokenBarrierException::name() const throw()
{
    return "QTKEABrokenBarrierException";
}

QTKEABrokenBarrierException *QTKEABrokenBarrierException::clone() const
{
    return new QTKEABrokenBarrierException(*this);
}

void QTKEABrokenBarrierException::rethrow() const
{
    throw *this;
}
