#ifndef _QEXTMVVMFUNCTIONTYPES_H
#define _QEXTMVVMFUNCTIONTYPES_H

#include <qextConnection.h>
#include <qextFunction.h>

class QEXTMvvmItem;
class QEXTMvvmModel;
class QEXTMvvmTagRow;

typedef QEXTFunction<void, QEXTMvvmItem *, QEXTMvvmTagRow>  QEXTMvvmItemTagRowFunction;
typedef QEXTFunction<void, QEXTMvvmItem *, int>             QEXTMvvmItemRoleFunction;
typedef QEXTFunction<void, QEXTMvvmItem *, QString>         QEXTMvvmItemPropertyFunction;
typedef QEXTFunction<void, QEXTMvvmItem *>                  QEXTMvvmItemFunction;
typedef QEXTFunction<void, QEXTMvvmModel *>                 QEXTMvvmModelFunction;

#endif // _QEXTMVVMFUNCTIONTYPES_H
