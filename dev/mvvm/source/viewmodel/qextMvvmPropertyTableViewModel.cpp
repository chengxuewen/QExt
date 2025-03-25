// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmPropertyTableViewModel.h>
#include <qextMvvmStandardViewModelControllers.h>
#include <qextMvvmViewItem.h>

using namespace ModelView;

QExtMvvmPropertyTableViewModel::QExtMvvmPropertyTableViewModel(QExtMvvmSessionModel* model, QObject* parent)
    : QExtMvvmViewModel(qextMakeUnique<QExtMvvmPropertyTableViewModelController>(model, this), parent)
{
}

void QExtMvvmPropertyTableViewModel::insertRow(QExtMvvmViewItem* parent, int row,
                                       std::vector<QExtUniquePointer<QExtMvvmViewItem>> items)
{
    // The code below is used to inform QTableView about layout change if the number
    // of columns before the insertion doesn't coincide with the length of `items` vector to insert.
    // This happens when QExtMvvmPropertyTableViewModel is looking on empty QExtMvvmSessionModel.
    int prevColumnCount = parent->columnCount();
    QExtMvvmViewModel::insertRow(parent, row, std::move(items));
    if (parent->columnCount() != prevColumnCount)
        emit layoutChanged();
}
