#ifndef _QEXTMVVMCELLDECORATORINTERFACE_H
#define _QEXTMVVMCELLDECORATORINTERFACE_H

#include <qextMvvmGlobal.h>
#include <string>

class QModelIndex;
class QStyleOptionViewItem;

//! Interface class to generate cell decorations (i.e. text) in Qt trees and tables.

class QEXT_MVVM_API QEXTMvvmCellDecoratorInterface
{
public:
    virtual ~QEXTMvvmCellDecoratorInterface() = default;

    virtual bool hasCustomDecoration(const QModelIndex& index) const = 0;
    virtual void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) = 0;
};


#endif // _QEXTMVVMCELLDECORATORINTERFACE_H
