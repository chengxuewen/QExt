#ifndef _QEXTMVVMVIEWMODELDEFAULTCELLDECORATOR_H
#define _QEXTMVVMVIEWMODELDEFAULTCELLDECORATOR_H

#include <qextMvvmCellDecoratorInterface.h>

#include <QVariant>

namespace ModelView
{

//! Generates default cell decorations for Qt trees and tables.

class QEXT_MVVM_API QEXTMvvmDefaultCellDecorator : public QEXTMvvmCellDecoratorInterface
{
public:
    bool hasCustomDecoration(const QModelIndex& index) const override;
    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) override;

protected:
    virtual QVariant cellText(const QModelIndex& index) const;
};

} // namespace ModelView

#endif // _QEXTMVVMVIEWMODELDEFAULTCELLDECORATOR_H
