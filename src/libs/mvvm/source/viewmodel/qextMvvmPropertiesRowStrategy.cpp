#include <qextMvvmPropertiesRowStrategy.h>
#include <qextMvvmStandardViewItems.h>
#include <qextMvvmUtils.h>

QEXTMvvmPropertiesRowStrategy::QEXTMvvmPropertiesRowStrategy(const std::list<std::string> &labels)
    : m_userDefinedColumnLabels(labels)
{

}

std::list<std::string> QEXTMvvmPropertiesRowStrategy::horizontalHeaderLabels() const
{
    return m_userDefinedColumnLabels.empty() ? m_currentColumnLabels : m_userDefinedColumnLabels;;
}

std::list<CFMvvmViewItem *> QEXTMvvmPropertiesRowStrategy::constructRow(CFMvvmItem *item)
{
    std::list<CFMvvmViewItem *> result;
    if (item)
    {
        std::list<CFMvvmItem *> itemsInRow = QEXTMvvmUtils::singlePropertyItems(item);
        if (m_userDefinedColumnLabels.empty())
        {
            this->updateColumnLabels(itemsInRow);
        }
        std::list<CFMvvmItem *>::iterator iter;
        for (iter = itemsInRow.begin(); iter != itemsInRow.end(); ++iter)
        {
            CFMvvmItem *child = *iter;
            if (child->hasData())
            {
                result.push_back(new QEXTMvvmViewDataItem(child));
            }
            else
            {
                result.push_back(new QEXTMvvmViewLabelItem(child));
            }
        }
    }
    return result;
}

void QEXTMvvmPropertiesRowStrategy::updateColumnLabels(const std::list<CFMvvmItem *> &items)
{
    m_currentColumnLabels.clear();
    std::list<CFMvvmItem *>::const_iterator iter;
    for (iter = items.begin(); iter != items.end(); ++iter)
    {
        CFMvvmItem *item = *iter;
        m_currentColumnLabels.push_back(item->displayName());
    }
}
