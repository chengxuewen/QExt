#include <qextMvvmStandardViewItems.h>
#include <qextMvvmUtils.h>

#include <cfMvvmExternalProperty.h>

#include <QVariant>
#include <QColor>

Q_DECLARE_METATYPE(CFMvvmExternalProperty)

QEXTMvvmRootViewItem::QEXTMvvmRootViewItem(CFMvvmItem *item)
    : CFMvvmViewItem(item, CFMvvmItem::Role_Data)
{

}

QEXTMvvmViewEmptyItem::QEXTMvvmViewEmptyItem()
    : CFMvvmViewItem(QEXT_DECL_NULLPTR, CFMvvmItem::Role_Identifier)
{

}

CFAny QEXTMvvmViewEmptyItem::data(int role) const
{
    if (this->item())
    {
        // use item's display role
        if (CFMvvmItem::Role_Display == role || CFMvvmItem::Role_Editor == role)
        {
            return CFAny(item()->displayName());
        }
    }
    return QEXTMvvmViewEmptyItem::data(role);
}

QEXTMvvmViewLabelItem::QEXTMvvmViewLabelItem(CFMvvmItem *item)
    : CFMvvmViewItem(item, CFMvvmItem::Role_Display)
{

}

CFAny QEXTMvvmViewLabelItem::data(int role) const
{
    CFMvvmItem *item = this->item();
    if (item)
    {
        // use item's display role
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            return CFAny(QString::fromStdString(item->displayName()));
        }
    }

    return CFMvvmViewItem::data(role);
}

QEXTMvvmViewDataItem::QEXTMvvmViewDataItem(CFMvvmItem *item)
    : CFMvvmViewItem(item, CFMvvmItem::Role_Data)
{

}

CFMvvmViewItem::ItemFlags QEXTMvvmViewDataItem::itemFlags() const
{
    CFMvvmViewItem::ItemFlags result = CFMvvmViewItem::itemFlags();
    CFMvvmItem *item = this->item();
    if (item && item->isEditable() && item->isEnabled())
    {
        result |= CFMvvmViewItem::Item_Editable;
    }
    return result;
}

CFAny QEXTMvvmViewDataItem::data(int role) const
{
    CFMvvmItem *item = this->item();
    if (item)
    {
        if (role == Qt::DecorationRole)
        {
            CFAny value = item->anyData();
            if (value.canConvert<QVariant>())
            {
                return value;
            }
            else if (value.canConvert<std::string>())
            {
                return CFAny(QColor(QString::fromStdString(*(value.toPtr<std::string>()))));
            }
            else if (value.canConvert<CFMvvmExternalProperty>())
            {
                return CFAny(QColor(QString::fromStdString(value.toPtr<CFMvvmExternalProperty>()->color())));
            }
            else
            {
                return CFAny();
            }
        }
        else if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            return item->anyData();
        }
        else if (role == Qt::CheckStateRole)
        {
            CFAny value = item->anyData();
            if (value.canConvert<bool>())
            {
                return CFAny(*(value.toPtr<bool>()) ? Qt::Checked : Qt::Unchecked);
            }
            return value;
        }
    }

    int itemRole = QEXTMvvmUtils::qtItemDataRoleToViewItemRole(role);
    return CFMvvmViewItem::data(itemRole);
}
