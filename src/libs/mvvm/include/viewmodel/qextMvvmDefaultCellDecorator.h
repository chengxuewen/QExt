#ifndef _QEXTMVVMDEFAULTCELLDECORATOR_H
#define _QEXTMVVMDEFAULTCELLDECORATOR_H

#include <qextMvvmCellDecoratorInterface.h>


//! Generates default cell decorations for Qt trees and tables.

class QEXT_MVVM_API QEXTMvvmDefaultCellDecorator : public QEXTMvvmCellDecoratorInterface
{
public:
    bool hasCustomDecoration(const QModelIndex& index) const QEXT_DECL_OVERRIDE;
    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) QEXT_DECL_OVERRIDE;

protected:
    virtual QString cellText(const QModelIndex& index) const;
};


#endif // _QEXTMVVMDEFAULTCELLDECORATOR_H
