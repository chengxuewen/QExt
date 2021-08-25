#ifndef QEXTQUICKWORLD_P_H
#define QEXTQUICKWORLD_P_H

#include <qextquickglobal.h>

#include <qextobject_p.h>



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



#endif // QEXTQUICKWORLD_P_H
