#ifndef _QEXTMVVMLABELDATAROWSTRATEGY_H
#define _QEXTMVVMLABELDATAROWSTRATEGY_H

#include <qextMvvmGlobal.h>

#include <cfMvvmRowStrategyInterface.h>

CF_USE_NAMESPACE

class QEXT_MVVM_API QEXTMvvmLabelDataRowStrategy : public CFMvvmRowStrategyInterface
{
public:
    std::list<std::string> horizontalHeaderLabels() const QEXT_DECL_OVERRIDE;

    std::list<CFMvvmViewItem *> constructRow(CFMvvmItem *item) QEXT_DECL_OVERRIDE;
};

#endif // _QEXTMVVMLABELDATAROWSTRATEGY_H
