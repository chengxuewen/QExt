// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QTreeView>
#include <QVBoxLayout>
#include <qextMvvmViewModel.h>
#include <qextMvvmViewModelDelegate.h>
#include <qextMvvmItemsTreeView.h>



QEXTMvvmItemsTreeView::QEXTMvvmItemsTreeView(QWidget* parent)
    : QWidget(parent)
    , m_treeView(new QTreeView)
    , m_delegate(new QEXTMvvmViewModelDelegate)
    , m_block_selection(false)
{
    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_treeView);
    setLayout(layout);
}

QEXTMvvmItemsTreeView::~QEXTMvvmItemsTreeView()
{

}

void QEXTMvvmItemsTreeView::setViewModel(QEXTMvvmViewModel *viewModel)
{
    m_viewModel.reset(viewModel);
    m_treeView->setItemDelegate(m_delegate.get());
    m_treeView->setModel(m_viewModel.get());
    m_treeView->expandAll();
    m_treeView->resizeColumnToContents(0);
    set_connected(true);
}

void QEXTMvvmItemsTreeView::setViewModelDelegate(QEXTMvvmViewModelDelegate *delegate)
{
    m_delegate.reset(delegate);
}

//! Make given item selected in QTreeView.

void QEXTMvvmItemsTreeView::setSelected(QEXTMvvmItem *item)
{
    if (!m_viewModel)
        return;

    auto indexes = m_viewModel->indexOfItem(item);
    if (!indexes.empty())
        selectionModel()->select(indexes.at(0), QItemSelectionModel::SelectCurrent);
}

void QEXTMvvmItemsTreeView::setRootSessionItem(QEXTMvvmItem* item)
{
    m_viewModel->setRootItem(item);
    m_treeView->expandAll();
}

QEXTMvvmViewModel* QEXTMvvmItemsTreeView::viewModel() const
{
    return m_viewModel.get();
}

//! Processes selections in QTreeView. Finds QEXTMvvmItem corresponding to selected indexes
//! and emit itemSelected signal.

void QEXTMvvmItemsTreeView::onSelectionChanged(const QItemSelection&, const QItemSelection&)
{
    if (m_block_selection)
        return;

    auto indexes = m_treeView->selectionModel()->selectedIndexes();
    if (!indexes.empty()) {
        auto item = m_viewModel->itemFromIndex(indexes.at(0));
        m_block_selection = true;
        itemSelected(item);
        m_block_selection = false;
    }
}

void QEXTMvvmItemsTreeView::set_connected(bool flag)
{
    Q_ASSERT(selectionModel());

    if (flag)
        connect(selectionModel(), &QItemSelectionModel::selectionChanged, this,
                &QEXTMvvmItemsTreeView::onSelectionChanged);
    else
        disconnect(selectionModel(), &QItemSelectionModel::selectionChanged, this,
                   &QEXTMvvmItemsTreeView::onSelectionChanged);
}

QTreeView* QEXTMvvmItemsTreeView::treeView()
{
    return m_treeView;
}

QItemSelectionModel* QEXTMvvmItemsTreeView::selectionModel()
{
    return m_treeView->selectionModel();
}
