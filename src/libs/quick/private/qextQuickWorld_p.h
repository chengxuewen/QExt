#ifndef _QEXTQUICKWORLD_P_H
#define _QEXTQUICKWORLD_P_H

#include <qextQuickGlobal.h>

class QEXTQuickWorld;
class QEXT_QUICK_API QEXTQuickWorldPrivate
{
    Q_DISABLE_COPY(QEXTQuickWorldPrivate)
    Q_DECLARE_PUBLIC(QEXTQuickWorld)
public:
    explicit QEXTQuickWorldPrivate(QEXTQuickWorld *q);
    virtual ~QEXTQuickWorldPrivate();

    QEXTQuickWorld * const q_ptr;
};

#endif // _QEXTQUICKWORLD_P_H
