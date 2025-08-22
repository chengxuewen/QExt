#ifndef _RPGLOBAL_H
#define _RPGLOBAL_H

#include <QObject>
#include <QPointer>
#include <QWeakPointer>
#include <QScopedPointer>
#include <QSharedPointer>

#define RP_DECL_PTR(class_name) \
    using Ptr = QPointer<class_name>;

#define RP_DECL_PTRS(class_name) \
    using SharedPtr = QSharedPointer<class_name>; \
    using WeakPtr = QWeakPointer<class_name>; \
    using Ptr = QPointer<class_name>;

#endif // _RPGLOBAL_H
