#ifndef _QEXTQUICKWORLD_P_H
#define _QEXTQUICKWORLD_P_H

#include <qextquickglobal.h>

#include <qextObject_p.h>



class QEXTQuickWorld;
class QEXT_QUICK_API QEXTQuickWorldPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTQuickWorldPrivate(QEXTQuickWorld *qq);
    ~QEXTQuickWorldPrivate();

private:
    QEXT_DECL_PUBLIC(QEXTQuickWorld)
    QEXT_DISABLE_COPY_MOVE(QEXTQuickWorldPrivate)
};



#endif // _QEXTQUICKWORLD_P_H
