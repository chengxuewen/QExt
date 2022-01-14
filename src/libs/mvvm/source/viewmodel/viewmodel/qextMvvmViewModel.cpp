// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>
#include <viewmodel/qextMvvmStandardViewItems.h>
#include <viewmodel/qextMvvmViewModel.h>
#include <viewmodel/qextMvvmViewModelController.h>

using namespace ModelView;

QEXTMvvmViewModel::QEXTMvvmViewModel(std::unique_ptr<QEXTMvvmViewModelController> controller, QObject* parent)
    : QEXTMvvmViewModelBase(parent), m_controller(std::move(controller))
{
    m_controller->setViewModel(this);
    m_controller->setRootSessionItem(sessionModel()->rootItem());
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

QEXTMvvmSessionModel* QEXTMvvmViewModel::sessionModel() const
{
    return m_controller->sessionModel();
}

QEXTMvvmSessionItem* QEXTMvvmViewModel::rootSessionItem()
{
    return m_controller->rootSessionItem();
}

QEXTMvvmViewModel::~QEXTMvvmViewModel() = default;

void QEXTMvvmViewModel::setRootSessionItem(QEXTMvvmSessionItem* item)
{
    if (!item)
        throw std::runtime_error("Error in ViewModel: atttemp to set nulptr as root item");
    m_controller->setRootSessionItem(item);
}

QEXTMvvmSessionItem* QEXTMvvmViewModel::sessionItemFromIndex(const QModelIndex& index) const
{
    return index.isValid() ? itemFromIndex(index)->item() : m_controller->rootSessionItem();
}

QEXTMvvmViewItem* QEXTMvvmViewModel::viewItemFromIndex(const QModelIndex& index) const
{
    return itemFromIndex(index);
}

//! Returns list of model indices representing given QEXTMvvmSessionItem.

QModelIndexList QEXTMvvmViewModel::indexOfSessionItem(const QEXTMvvmSessionItem* item) const
{
    QModelIndexList result;
    for (auto view : m_controller->findViews(item))
        result.push_back(indexFromItem(view));
    return result;
}

//! Returns vector of all ViewItem's representing given QEXTMvvmSessionItem.

std::vector<QEXTMvvmViewItem*> QEXTMvvmViewModel::findViews(const QEXTMvvmSessionItem* item) const
{
    return m_controller->findViews(item);
}
