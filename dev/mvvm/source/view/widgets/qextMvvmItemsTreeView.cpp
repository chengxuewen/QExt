// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmItemsTreeView.h>
#include <qextMvvmViewModel.h>
#include <qextMvvmViewModelDelegate.h>
#include <QTreeView>
#include <QVBoxLayout>

using namespace ModelView;

QExtMvvmItemsTreeView::QExtMvvmItemsTreeView(QWidget* parent)
    : QWidget(parent)
    , m_treeView(new QTreeView)
    , m_delegate(qextMakeUnique<QExtMvvmViewModelDelegate>())
    , m_block_selection(false)
{
    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(m_treeView);
    setLayout(layout);
}

QExtMvvmItemsTreeView::~QExtMvvmItemsTreeView() = default;

void QExtMvvmItemsTreeView::setViewModel(QExtUniquePointer<QExtMvvmViewModel> viewModel)
{
    m_viewModel = std::move(viewModel);
    m_treeView->setItemDelegate(m_delegate.get());
    m_treeView->setModel(m_viewModel.get());
    m_treeView->expandAll();
    m_treeView->resizeColumnToContents(0);
    set_connected(true);
}

void QExtMvvmItemsTreeView::setViewModelDelegate(QExtUniquePointer<QExtMvvmViewModelDelegate> delegate)
{
    m_delegate = std::move(delegate);
}

//! Make given item selected in QTreeView.

void QExtMvvmItemsTreeView::setSelected(QExtMvvmSessionItem* item)
{
    // Provide possibility to clear selection when item == nullptr. Provide unit tests.
    // Make sure it works when QExtMvvmSessionModel is already destroyed.
    if (!m_viewModel || !item)
        return;

    auto indexes = m_viewModel->indexOfSessionItem(item);
    if (!indexes.empty())
        selectionModel()->select(indexes.at(0), QItemSelectionModel::SelectCurrent);
}

void QExtMvvmItemsTreeView::setRootSessionItem(QExtMvvmSessionItem* item)
{
    m_viewModel->setRootSessionItem(item);
    m_treeView->expandAll();
}

QExtMvvmViewModel* QExtMvvmItemsTreeView::viewModel() const
{
    return m_viewModel.get();
}

//! Processes selections in QTreeView. Finds QExtMvvmSessionItem corresponding to selected indexes
//! and emit itemSelected signal.

void QExtMvvmItemsTreeView::onSelectionChanged(const QItemSelection&, const QItemSelection&)
{
    if (m_block_selection)
        return;

    auto indexes = m_treeView->selectionModel()->selectedIndexes();
    if (!indexes.empty()) {
        auto item = m_viewModel->sessionItemFromIndex(indexes.at(0));
        m_block_selection = true;
        emit itemSelected(item);
        m_block_selection = false;
    }
}

void QExtMvvmItemsTreeView::set_connected(bool flag)
{
    if (flag)
        connect(selectionModel(), &QItemSelectionModel::selectionChanged, this,
                &QExtMvvmItemsTreeView::onSelectionChanged);
    else
        disconnect(selectionModel(), &QItemSelectionModel::selectionChanged, this,
                   &QExtMvvmItemsTreeView::onSelectionChanged);
}

QTreeView* QExtMvvmItemsTreeView::treeView()
{
    return m_treeView;
}

QItemSelectionModel* QExtMvvmItemsTreeView::selectionModel()
{
    return m_treeView->selectionModel();
}
