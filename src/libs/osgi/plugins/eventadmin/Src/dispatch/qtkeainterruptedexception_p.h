#ifndef QTKEAINTERRUPTEDEXCEPTION_P_H
#define QTKEAINTERRUPTEDEXCEPTION_P_H

#include <QTKCore/QTKException>

QTK_CORE_USE_NAMESPACE

class QTKEAInterruptedException : public QTKRuntimeException
{
public:
    QTKEAInterruptedException();
    ~QTKEAInterruptedException() throw();

    const char *name() const throw();

    QTKEAInterruptedException *clone() const;

    void rethrow() const;
};

#endif // QTKEAINTERRUPTEDEXCEPTION_P_H
