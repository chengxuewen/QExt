#ifndef _QEXTQMLQUICKWORLD_P_H
#define _QEXTQMLQUICKWORLD_P_H

#include <qextQmlQuickGlobal.h>

class QEXTQmlQuickWorld;
class QEXT_QUICK_API QEXTQmlQuickWorldPrivate
{
    Q_DISABLE_COPY(QEXTQmlQuickWorldPrivate)
    Q_DECLARE_PUBLIC(QEXTQmlQuickWorld)
public:
    explicit QEXTQmlQuickWorldPrivate(QEXTQmlQuickWorld *q);
    virtual ~QEXTQmlQuickWorldPrivate();

    QEXTQmlQuickWorld * const q_ptr;
};

#endif // _QEXTQMLQUICKWORLD_P_H
