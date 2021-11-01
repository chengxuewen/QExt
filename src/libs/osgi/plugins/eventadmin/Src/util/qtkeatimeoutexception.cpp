#include "qtkeatimeoutexception_p.h"

QTKEATimeoutException::QTKEATimeoutException(long lTime, const QString &strMessage)
    : QTKRuntimeException(strMessage),
      m_lDuration(lTime)
{

}

QTKEATimeoutException::~QTKEATimeoutException() throw()
{
}

const char *QTKEATimeoutException::name() const throw()
{
    return "QTKEATimeoutException";
}

QTKEATimeoutException *QTKEATimeoutException::clone() const
{
    return new QTKEATimeoutException(*this);
}

void QTKEATimeoutException::rethrow() const
{
    throw *this;
}
