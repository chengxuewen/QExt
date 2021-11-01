#ifndef QTKEABROKENBARRIEREXCEPTION_P_H
#define QTKEABROKENBARRIEREXCEPTION_P_H

#include <QTKCore/QTKException>

QTK_CORE_USE_NAMESPACE

class QTKEABrokenBarrierException : public QTKRuntimeException
{
public:
    QTKEABrokenBarrierException(int iIndex, const QString &strMessage = QString());
    ~QTKEABrokenBarrierException() throw();

    const char *name() const throw();

    QTKEABrokenBarrierException *clone() const;

    void rethrow() const;

    const int m_iIndex;
};

#endif // QTKEABROKENBARRIEREXCEPTION_P_H
