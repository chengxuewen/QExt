#ifndef QTKEATIMEOUTEXCEPTION_P_H
#define QTKEATIMEOUTEXCEPTION_P_H

#include <QTKCore/QTKException>

QTK_CORE_USE_NAMESPACE

class QTKEATimeoutException : public QTKRuntimeException
{
public:
    QTKEATimeoutException(long lTime, const QString &strMessage = QString());

    ~QTKEATimeoutException() throw();

    const char *name() const throw();

    QTKEATimeoutException *clone() const;

    void rethrow() const;

    const long m_lDuration;
};

#endif // QTKEATIMEOUTEXCEPTION_P_H
