#ifndef _QEXTQMLWORLD_P_H
#define _QEXTQMLWORLD_P_H

#include <qextQmlWorld.h>

class QEXT_QML_API QExtQmlWorldPrivate
{
    Q_DISABLE_COPY(QExtQmlWorldPrivate)
    Q_DECLARE_PUBLIC(QExtQmlWorld)
public:
    explicit QExtQmlWorldPrivate(QExtQmlWorld *q);
    virtual ~QExtQmlWorldPrivate();

    QExtQmlWorld * const q_ptr;
};

#endif // _QEXTQMLWORLD_P_H
