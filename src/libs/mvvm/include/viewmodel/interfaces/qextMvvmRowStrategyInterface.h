#ifndef _QEXTMVVMROWSTRATEGYINTERFACE_H
#define _QEXTMVVMROWSTRATEGYINTERFACE_H

#include <qextMvvmGlobal.h>

#include <QVector>
#include <QSharedPointer>
#include <QStringList>

class QEXTMvvmItem;
class QEXTMvvmViewItem;

//! Base class to construct row of QEXTMvvmViewItem's from given QEXTMvvmItem.
//! Used in context of AbstractViewModel while exposing QEXTMvvmModel to Qt.

class QEXT_MVVM_API QEXTMvvmRowStrategyInterface
{
public:
    virtual ~QEXTMvvmRowStrategyInterface() { }

    virtual QStringList horizontalHeaderLabels() const = 0;

    virtual QVector<QEXTMvvmViewItem *> constructRow(QEXTMvvmItem *) = 0;
};

#endif // _QEXTMVVMROWSTRATEGYINTERFACE_H
