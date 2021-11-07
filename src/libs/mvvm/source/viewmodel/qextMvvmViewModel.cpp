#include <qextMvvmItem.h>
#include <qextMvvmModel.h>
#include <qextMvvmStandardViewItems.h>
#include <qextMvvmViewModel.h>
#include <qextMvvmViewModelController.h>



QEXTMvvmViewModel::QEXTMvvmViewModel(QEXTMvvmViewModelController *controller, QObject* parent)
    : QEXTMvvmViewModelBase(parent), m_controller(controller)
{
    m_controller->setViewModel(this);
    m_controller->setRootSessionItem(model()->rootItem());
}

QEXTMvvmViewModel::~QEXTMvvmViewModel()
{

}

QVariant QEXTMvvmViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        auto data = m_controller->horizontalHeaderLabels();
        if (section < data.size())
            return data.at(section);
    }
    return QVariant();
}

QEXTMvvmModel* QEXTMvvmViewModel::model() const
{
    return m_controller->sessionModel();
}

QEXTMvvmItem* QEXTMvvmViewModel::rootItem()
{
    return m_controller->rootItem();
}

void QEXTMvvmViewModel::setRootItem(QEXTMvvmItem *item)
{
    if (!item)
        throw std::runtime_error("Error in QEXTMvvmViewModel: atttemp to set nulptr as root item");
    m_controller->setRootSessionItem(item);
}

QEXTMvvmItem *QEXTMvvmViewModel::itemFromIndex(const QModelIndex &index) const
{
    return index.isValid() ? this->viewItemFromIndex(index)->item() : m_controller->rootItem();
}

QEXTMvvmViewItem *QEXTMvvmViewModel::viewItemFromIndex(const QModelIndex &index) const
{
    return index.isValid() ? static_cast<QEXTMvvmViewItem *>(index.internalPointer()) : QEXT_DECL_NULLPTR;
}

//! Returns list of model indices representing given QEXTMvvmItem.

QModelIndexList QEXTMvvmViewModel::indexOfItem(const QEXTMvvmItem* item) const
{
    QModelIndexList result;
    for (auto view : m_controller->findViews(item))
        result.push_back(indexFromItem(view));
    return result;
}

//! Returns vector of all QEXTMvvmViewItem's representing given QEXTMvvmItem.

QVector<QEXTMvvmViewItem*> QEXTMvvmViewModel::findViews(const QEXTMvvmItem* item) const
{
    return m_controller->findViews(item);
}
