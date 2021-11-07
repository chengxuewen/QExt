// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "sampleeditorwidget.h"
#include <QBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QTreeView>
#include <QUndoView>
#include <qextMvvmUndoStack.h>
#include <qextMvvmItem.h>
#include <qextMvvmModel.h>
#include <qextMvvmDefaultViewModel.h>
#include <qextMvvmTopItemsViewModel.h>
#include <qextMvvmViewItem.h>
#include <qextMvvmStandardTreeViews.h>



namespace TreeViews
{

SampleEditorWdiget::SampleEditorWdiget(QEXTMvvmModel* model, QWidget* parent)
    : QWidget(parent)
    , m_undoView(new QUndoView)
    , m_defaultTreeView(new QEXTMvvmAllItemsTreeView(model))
    , m_topItemView(new QEXTMvvmTopItemsTreeView(model))
    , m_subsetTreeView(new QEXTMvvmAllItemsTreeView(model))
    , m_propertyTreeView(new QEXTMvvmPropertyTreeView)
    , m_sessionModel(model)
{
    auto layout = new QHBoxLayout;
    layout->addLayout(createLeftLayout());
    layout->addLayout(createMiddleLayout());
    layout->addLayout(createRightLayout());
    setLayout(layout);

    connect_views();

    m_sessionModel->setUndoRedoEnabled(true);
    m_undoView->setStack(QEXTMvvmUndoStack::qtUndoStack(m_sessionModel->undoStack()));
}

SampleEditorWdiget::~SampleEditorWdiget() = default;

void SampleEditorWdiget::onContextMenuRequest(const QPoint& point)
{
    auto treeView = qobject_cast<QTreeView*>(sender());

    auto item = item_from_view(treeView, point);
    auto tagrow = item->tagRow();

    QMenu menu;

    // inserting item of same type after given item
    auto addItemAction = menu.addAction("Add item");
    auto add_item = [&]() {
        m_sessionModel->insertNewItem(item->modelType(), item->parent(), tagrow.next());
    };
    connect(addItemAction, &QAction::triggered, add_item);

    // removing item under the mouse
    auto removeItemAction = menu.addAction("Remove item");
    auto remove_item = [&]() { m_sessionModel->removeItem(item->parent(), tagrow); };
    connect(removeItemAction, &QAction::triggered, remove_item);

    menu.exec(treeView->mapToGlobal(point));
}

//! Returns QEXTMvvmItem corresponding to given coordinate in a view.

QEXTMvvmItem* SampleEditorWdiget::item_from_view(QTreeView* view, const QPoint& point)
{
    QModelIndex index = view->indexAt(point);
    QEXTMvvmViewItem *viewItem = m_defaultTreeView->viewModel()->viewItemFromIndex(index);
    return viewItem->item();
}

//! Connect tree views to provide mutual item selection.

void SampleEditorWdiget::connect_views()
{
    // select items in other views when selection in m_defaultTreeView has changed
    auto on_item_selected = [this](QEXTMvvmItem* item) {
        m_subsetTreeView->setRootSessionItem(item);
        m_propertyTreeView->setItem(item);
        m_topItemView->setSelected(item);
    };
    connect(m_defaultTreeView, &QEXTMvvmAllItemsTreeView::itemSelected, on_item_selected);

    m_defaultTreeView->treeView()->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_defaultTreeView->treeView(), &QTreeView::customContextMenuRequested, this,
            &SampleEditorWdiget::onContextMenuRequest);

    // will notify m_defaultTreeView
    auto on_top_item_selected = [this](QEXTMvvmItem* item) { m_defaultTreeView->setSelected(item); };
    connect(m_topItemView, &QEXTMvvmTopItemsTreeView::itemSelected, on_top_item_selected);
}

QBoxLayout* SampleEditorWdiget::createLeftLayout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_defaultTreeView);
    return result;
}

QBoxLayout* SampleEditorWdiget::createMiddleLayout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_topItemView);
    result->addWidget(m_subsetTreeView);
    return result;
}

QBoxLayout* SampleEditorWdiget::createRightLayout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_undoView);
    result->addWidget(m_propertyTreeView);
    return result;
}

} // namespace TreeViews
