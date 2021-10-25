#include <qextMvvmLabelDataRowStrategy.h>
#include <qextMvvmStandardViewItems.h>

std::list<std::string> QEXTMvvmLabelDataRowStrategy::horizontalHeaderLabels() const
{
    std::list<std::string> labels;
    labels.push_back("Name");
    labels.push_back("Value");
    return labels;
}

std::list<CFMvvmViewItem *> QEXTMvvmLabelDataRowStrategy::constructRow(CFMvvmItem *item)
{
    std::list<CFMvvmViewItem *> result;
    if (item)
    {
        result.push_back(new QEXTMvvmViewLabelItem(item));
        result.push_back(new QEXTMvvmViewDataItem(item));
    }
    return result;
}
