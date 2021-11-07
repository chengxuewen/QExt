// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmViewModel.h>
#include <qextMvvmViewModelFactory.h>
#include <qextMvvmAllItemsTreeView.h>


QEXTMvvmAllItemsTreeView::QEXTMvvmAllItemsTreeView(QEXTMvvmModel* model, QWidget* parent) : QEXTMvvmItemsTreeView(parent)
{
    setViewModel(QEXTMvvmViewModelFactory::createDefaultViewModel(model));
}

QEXTMvvmAllItemsTreeView::~QEXTMvvmAllItemsTreeView()
{

}
