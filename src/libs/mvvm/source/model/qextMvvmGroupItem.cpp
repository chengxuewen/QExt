#include <qextMvvmComboProperty.h>
#include <qextMvvmGroupItem.h>
#include <qextMvvmTagInfo.h>
#include <qextMvvmUtils.h>
#include <stdexcept>



QEXTMvvmGroupItem::~QEXTMvvmGroupItem() = default;

QEXTMvvmGroupItem::QEXTMvvmGroupItem(QString modelType)
    : QEXTMvvmItem(modelType)
    , m_catalogue(new QEXTMvvmItemCatalogue)
    , m_defaultSelectedIndex(0)
{
    registerTag(QEXTMvvmTagInfo::universalTag(T_GROUP_ITEMS), /*set_as_default*/ true);
    setData(QEXTMvvmComboProperty());
}

int QEXTMvvmGroupItem::currentIndex() const
{
    return data<QEXTMvvmComboProperty>().currentIndex();
}

//! Returns currently selected item.

const QEXTMvvmItem* QEXTMvvmGroupItem::currentItem() const
{
    return this->isValidIndex() ? this->item("", currentIndex()) : QEXT_DECL_NULLPTR;
}

QEXTMvvmItem* QEXTMvvmGroupItem::currentItem()
{
    return const_cast<QEXTMvvmItem*>(static_cast<const QEXTMvvmGroupItem*>(this)->currentItem());
}

QString QEXTMvvmGroupItem::currentType() const
{
    return isValidIndex() ? m_catalogue->modelTypes()[static_cast<size_t>(currentIndex())] : "";
}

//! Sets item corresponding to given model type.

void QEXTMvvmGroupItem::setCurrentType(const QString &modelType)
{
    QVector<QString> modelTypes = m_catalogue->modelTypes();
    int index = modelTypes.indexOf(modelType);
    if (index == -1)
    {
        throw std::runtime_error("QEXTMvvmGroupItem::setCurrentType() -> Model type '" + modelType.toStdString()
                                 + "' doesn't belong to the group");
    }

    this->setCurrentIndex(index);
}

void QEXTMvvmGroupItem::setCurrentIndex(int index)
{
    QEXTMvvmComboProperty combo = this->data<QEXTMvvmComboProperty>();
    combo.setCurrentIndex(index);
    this->setData(combo, QEXTMvvmItem::Role_Data);
}

bool QEXTMvvmGroupItem::isValidIndex() const
{
    return this->currentIndex() != -1;
}

//! Inits group item by creating all registered items and constructing combo property
//! for switching between items.

void QEXTMvvmGroupItem::initGroup()
{
    QEXTMvvmComboProperty combo;
    combo.setValues(m_catalogue->labels());
    combo.setCurrentIndex(m_defaultSelectedIndex);
    this->setData(combo, QEXTMvvmItem::Role_Data);
    QVector<QString> modelTypes = m_catalogue->modelTypes();
    for (int i = 0; i < modelTypes.size(); ++i)
    {
        QString modelType = modelTypes.at(i);
        this->insertItem(m_catalogue->create(modelType), QEXTMvvmTagRow::append(T_GROUP_ITEMS));
    }
}
