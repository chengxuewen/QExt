#ifndef _QEXTMVVMDEFAULTCELLDECORATOR_H
#define _QEXTMVVMDEFAULTCELLDECORATOR_H

#include <qextMvvmGlobal.h>
#include <qextMvvmCellDecoratorInterface.h>

#include <QStyleOptionViewItem>

#include <string>

class QEXT_MVVM_API QEXTMvvmDefaultCellDecorator : public QEXTMvvmCellDecoratorInterface
{
public:
    bool hasCustomDecoration(const QModelIndex &index) const QEXT_DECL_OVERRIDE;
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) QEXT_DECL_OVERRIDE;

protected:
    virtual std::string cellText(const QModelIndex &index) const;
};

#endif // _QEXTMVVMDEFAULTCELLDECORATOR_H
