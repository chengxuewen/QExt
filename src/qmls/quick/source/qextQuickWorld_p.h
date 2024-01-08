#ifndef _QEXTQUICKWORLD_P_H
#define _QEXTQUICKWORLD_P_H

#include <qextQuickWorld.h>

class QEXT_QUICK_API QExtQuickWorldPrivate
{
    Q_DISABLE_COPY(QExtQuickWorldPrivate)
    Q_DECLARE_PUBLIC(QExtQuickWorld)
public:
    explicit QExtQuickWorldPrivate(QExtQuickWorld *q);
    virtual ~QExtQuickWorldPrivate();

    QExtQuickWorld * const q_ptr;
};

#endif // _QEXTQUICKWORLD_P_H
