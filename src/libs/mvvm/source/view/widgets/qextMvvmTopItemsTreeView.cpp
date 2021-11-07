#include <qextMvvmTopItemsTreeView.h>
#include <qextMvvmViewModelFactory.h>
#include <qextMvvmViewModel.h>

QEXTMvvmTopItemsTreeView::QEXTMvvmTopItemsTreeView(QEXTMvvmModel *model, QWidget *parent)
    : QEXTMvvmItemsTreeView(parent)
{
    this->setViewModel(QEXTMvvmViewModelFactory::createTopItemsViewModel(model));
}

QEXTMvvmTopItemsTreeView::~QEXTMvvmTopItemsTreeView()
{

}
