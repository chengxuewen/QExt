#include <qextMvvmUtils.h>
#include <qextMvvmItem.h>
#include <qextMvvmPropertiesRowStrategy.h>
#include <qextMvvmStandardViewItems.h>



QEXTMvvmPropertiesRowStrategy::QEXTMvvmPropertiesRowStrategy(QVector<QString> labels)
    : m_userDefinedColumnLabels(labels)
{
}

QStringList QEXTMvvmPropertiesRowStrategy::horizontalHeaderLabels() const
{
    QStringList result;
    auto labels =
        m_userDefinedColumnLabels.empty() ? m_currentColumnLabels : m_userDefinedColumnLabels;
    std::transform(labels.begin(), labels.end(), std::back_inserter(result),
                   [](const QString& str) { return str; });
    return result;
}

QVector<QEXTMvvmViewItem *> QEXTMvvmPropertiesRowStrategy::constructRow(QEXTMvvmItem* item)
{
    QVector<QEXTMvvmViewItem *> result;

    if (!item)
        return result;

    auto items_in_row = QEXTMvvmUtils::singlePropertyItems(*item);
    if (m_userDefinedColumnLabels.empty())
        updateColumnLabels(items_in_row);

    for (auto child : items_in_row) {
        if (child->hasData())
            result.append(new QEXTMvvmViewDataItem(child));
        else
            result.append(new QEXTMvvmViewLabelItem(child));
    }

    return result;
}

//! Updates current column labels.

void QEXTMvvmPropertiesRowStrategy::updateColumnLabels(QVector<QEXTMvvmItem*> items)
{
    m_currentColumnLabels.clear();
    std::transform(items.begin(), items.end(), std::back_inserter(m_currentColumnLabels),
                   [](const QEXTMvvmItem* item) { return item->displayName(); });
}
