#ifndef _QEXTMVVMPROPERTIESROWSTRATEGY_H
#define _QEXTMVVMPROPERTIESROWSTRATEGY_H

#include <qextMvvmGlobal.h>

#include <cfMvvmRowStrategyInterface.h>

CF_USE_NAMESPACE

class QEXT_MVVM_API QEXTMvvmPropertiesRowStrategy : public CFMvvmRowStrategyInterface
{
public:
    QEXTMvvmPropertiesRowStrategy(const std::list<std::string> &labels = std::list<std::string>());

    std::list<std::string> horizontalHeaderLabels() const QEXT_DECL_OVERRIDE;

    std::list<CFMvvmViewItem *> constructRow(CFMvvmItem *item) QEXT_DECL_OVERRIDE;

private:
    void updateColumnLabels(const std::list<CFMvvmItem *> &items);

    std::list<std::string> m_currentColumnLabels;
    std::list<std::string> m_userDefinedColumnLabels;
};

#endif // _QEXTMVVMPROPERTIESROWSTRATEGY_H
