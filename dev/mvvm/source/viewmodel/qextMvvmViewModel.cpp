// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmViewModel.h>
#include <qextMvvmSessionModel.h>
#include <qextMvvmStandardViewItems.h>
#include <qextMvvmViewModelController.h>

using namespace ModelView;

QExtMvvmViewModel::QExtMvvmViewModel(QExtUniquePointer<QExtMvvmViewModelController> controller, QObject* parent)
    : QExtMvvmViewModelBase(parent), m_controller(std::move(controller))
{
    m_controller->setViewModel(this);
    m_controller->setRootSessionItem(sessionModel()->rootItem());
}

QVariant QExtMvvmViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        auto data = m_controller->horizontalHeaderLabels();
        if (section < data.size())
            return data.at(section);
    }
    return QVariant();
}

QExtMvvmSessionModel* QExtMvvmViewModel::sessionModel() const
{
    return m_controller->sessionModel();
}

QExtMvvmSessionItem* QExtMvvmViewModel::rootSessionItem()
{
    return m_controller->rootSessionItem();
}

QExtMvvmViewModel::~QExtMvvmViewModel() = default;

void QExtMvvmViewModel::setRootSessionItem(QExtMvvmSessionItem* item)
{
    if (!item)
        throw std::runtime_error("Error in QExtMvvmViewModel: atttemp to set nulptr as root item");
    m_controller->setRootSessionItem(item);
}

QExtMvvmSessionItem* QExtMvvmViewModel::sessionItemFromIndex(const QModelIndex& index) const
{
    return index.isValid() ? itemFromIndex(index)->item() : m_controller->rootSessionItem();
}

QExtMvvmViewItem* QExtMvvmViewModel::viewItemFromIndex(const QModelIndex& index) const
{
    return itemFromIndex(index);
}

//! Returns list of model indices representing given QExtMvvmSessionItem.

QModelIndexList QExtMvvmViewModel::indexOfSessionItem(const QExtMvvmSessionItem* item) const
{
    QModelIndexList result;
    for (auto view : m_controller->findViews(item))
        result.push_back(indexFromItem(view));
    return result;
}

//! Returns vector of all QExtMvvmViewItem's representing given QExtMvvmSessionItem.

std::vector<QExtMvvmViewItem*> QExtMvvmViewModel::findViews(const QExtMvvmSessionItem* item) const
{
    return m_controller->findViews(item);
}
