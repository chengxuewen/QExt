#include <map>
#include <qextMvvmChildrenStrategyInterface.h>
#include <qextMvvmRowStrategyInterface.h>
#include <qextMvvmUtils.h>
#include <qextMvvmItem.h>
#include <qextMvvmModel.h>
#include <qextMvvmUtils.h>
#include <qextMvvmStandardViewItems.h>
#include <qextMvvmViewModelBase.h>
#include <qextMvvmViewModelController.h>
#include <qextMvvmViewModelUtils.h>
#include <stdexcept>



namespace
{

//! Returns true if given QEXTMvvmItem role is valid for view
bool isValidItemRole(const QEXTMvvmViewItem* view, int item_role)
{
    if (view->itemRole() == item_role)
        return true;

    if (item_role == QEXTMvvmItem::Role_Appearance || item_role == QEXTMvvmItem::Role_ToolTip)
        return true;
    return false;
}

} // namespace

struct QEXTMvvmViewModelController::ViewModelControllerImpl
{
    QEXTMvvmViewModelController *m_controller;
    QEXTMvvmViewModelBase *m_viewModel{nullptr};
    QScopedPointer<QEXTMvvmChildrenStrategyInterface> m_childrenStrategy;
    QScopedPointer<QEXTMvvmRowStrategyInterface> m_rowStrategy;
    QMap<QEXTMvvmItem *, QEXTMvvmViewItem *> m_itemToView; //! correspondence of item and its view
    QEXTMvvmPath m_rootItemPath;

    ViewModelControllerImpl(QEXTMvvmViewModelController* controller, QEXTMvvmViewModelBase* view_model)
        : m_controller(controller), m_viewModel(view_model)
    {
    }

    void check_initialization()
    {
        const QString msg("Error in QEXTMvvmViewModelController: ");
        if (!m_viewModel)
            throw std::runtime_error(msg.toStdString() + "QEXTMvvmViewModel is not defined");

        if (!m_rowStrategy)
            throw std::runtime_error(msg.toStdString() + "RowStrategy is not defined");

        if (!m_childrenStrategy)
            throw std::runtime_error(msg.toStdString() + "Children is not defined");
    }

    void init_view_model()
    {
        check_initialization();
        m_itemToView.clear();
        m_itemToView[m_controller->rootItem()] = m_viewModel->rootItem();
        iterate(m_controller->rootItem(), m_viewModel->rootItem());
    }

    void iterate(const QEXTMvvmItem* item, QEXTMvvmViewItem* parent)
    {
        QEXTMvvmViewItem* origParent(parent);
        for (auto child : m_childrenStrategy->children(item)) {
            QVector<QEXTMvvmViewItem *> row = m_rowStrategy->constructRow(child);
            if (!row.isEmpty())
            {
                QEXTMvvmViewItem *nextparent = row.at(0);
                m_viewModel->appendRow(parent, row);
                m_itemToView[child] = nextparent;
                parent = nextparent; // labelItem
                iterate(child, parent);
            }
            parent = origParent;
        }
    }

    //! Remove row of QEXTMvvmViewItem's corresponding to given item.

    void removeRowOfViews(QEXTMvvmItem *item)
    {
        if (m_itemToView.contains(item))
        {
            QEXTMvvmViewItem *view = m_itemToView.value(item);
            m_viewModel->removeRow(view->parent(), view->row());
            m_itemToView.remove(item);
        }
    }

    void removeChildrenOfView(QEXTMvvmViewItem* view)
    {
        QVector<QEXTMvvmViewItem *> children = view->children();
        for (int i = 0; i < children.size(); ++i)
        {
            QEXTMvvmViewItem *child = children.at(i);
            if (m_itemToView.values().contains(child))
            {
                QEXTMvvmItem *key = m_itemToView.key(child);
                m_itemToView.remove(key);
            }
        }
        m_viewModel->clearRows(view);
    }

    void insertView(QEXTMvvmItem* parent, const QEXTMvvmTagRow& tagrow)
    {
        auto child = parent->item(tagrow.tag, tagrow.row);
        auto children = m_childrenStrategy->children(parent);
        auto index = children.indexOf(child);
        if (index == -1)
            return;

        if (!m_itemToView.contains(parent))
        {
            return;
        }

        QEXTMvvmViewItem *parent_view = m_itemToView.value(parent);

        QVector<QEXTMvvmViewItem *> row = m_rowStrategy->constructRow(child);
        if (!row.isEmpty()) {
            QEXTMvvmViewItem *nextParent = row.at(0);
            m_viewModel->insertRow(parent_view, index, row);
            m_itemToView[child] = nextParent;
            parent_view = nextParent; // labelItem
            iterate(child, parent_view);
        }
    }

    QVector<QEXTMvvmViewItem*> findViews(const QEXTMvvmItem* item) const
    {
        if (item == m_viewModel->rootItem()->item())
            return {m_viewModel->rootItem()};

        QVector<QEXTMvvmViewItem*> result;
        auto on_index = [&](const QModelIndex& index) {
            auto view_item = m_viewModel->itemFromIndex(index);
            if (view_item->item() == item)
                result.push_back(view_item);
        };
        QEXTMvvmViewModelUtils::iterate_model(m_viewModel, QModelIndex(), on_index);
        return result;
    }

    void setRootSessionItemIntern(QEXTMvvmItem* item)
    {
        m_rootItemPath = m_controller->model()->pathFromItem(item);
        m_viewModel->setRootViewItem(new QEXTMvvmRootViewItem(item));
        init_view_model();
    }
};

QEXTMvvmViewModelController::QEXTMvvmViewModelController(QEXTMvvmModel *model, QEXTMvvmViewModelBase *viewModel)
    : QEXTMvvmModelListener(model)
    , d(new ViewModelControllerImpl(this, viewModel))
{
    auto on_data_change = [this](QEXTMvvmItem* item, int role) { onDataChange(item, role); };
    addItemDataChangedListener(on_data_change);

    auto on_item_inserted = [this](QEXTMvvmItem* item, QEXTMvvmTagRow tagrow) {
        onItemInserted(item, tagrow);
    };
    addItemInsertedListener(on_item_inserted);

    auto on_item_removed = [this](QEXTMvvmItem* item, QEXTMvvmTagRow tagrow) {
        onItemRemoved(item, tagrow);
    };
    addItemRemovedListener(on_item_removed);

    auto on_about_to_remove = [this](QEXTMvvmItem* item, QEXTMvvmTagRow tagrow) {
        onAboutToRemoveItem(item, tagrow);
    };
    addItemAboutToBeRemovedListener(on_about_to_remove);

    auto on_model_destroyed = [this](auto) {
        d->m_viewModel->setRootViewItem(new QEXTMvvmRootViewItem(nullptr));
    };
    addModelDestroyedListener(on_model_destroyed);

    auto on_model_reset = [this](auto) {
        QEXTMvvmItem *rootItem = this->model()->itemFromPath(d->m_rootItemPath);
        d->setRootSessionItemIntern(rootItem ? rootItem : this->model()->rootItem());
        d->m_viewModel->endResetModel();
    };
    addModelResetedListener(on_model_reset);

    auto on_model_about_to_be_reset = [this](auto) { d->m_viewModel->beginResetModel(); };
    addModelAboutToBeResetedListener(on_model_about_to_be_reset);
}

QEXTMvvmViewModelController::~QEXTMvvmViewModelController()
{

}

void QEXTMvvmViewModelController::setViewModel(QEXTMvvmViewModelBase *viewModel)
{
    d->m_viewModel = viewModel;
}

void QEXTMvvmViewModelController::setChildrenStrategy(QEXTMvvmChildrenStrategyInterface *childrenStrategy)
{
    d->m_childrenStrategy.reset(childrenStrategy);
}

void QEXTMvvmViewModelController::setRowStrategy(QEXTMvvmRowStrategyInterface *rowStrategy)
{
    d->m_rowStrategy.reset(rowStrategy);
}

//! Returns QEXTMvvmModel handled by this controller.

QEXTMvvmModel* QEXTMvvmViewModelController::sessionModel() const
{
    return model();
}

void QEXTMvvmViewModelController::setRootSessionItem(QEXTMvvmItem* item)
{
    if (!item)
        throw std::runtime_error(
            "Error in QEXTMvvmViewModelController: atttemp to set nulptr as root item");

    if (item->model() != model())
        throw std::runtime_error(
            "Error in QEXTMvvmViewModelController: atttemp to use item from alien model as new root.");

    d->m_viewModel->beginResetModel();
    d->setRootSessionItemIntern(item);
    d->m_viewModel->endResetModel();
}

QEXTMvvmItem* QEXTMvvmViewModelController::rootItem() const
{
    return d->m_viewModel->rootItem()->item();
}

//! Returns all QEXTMvvmViewItem's displaying given QEXTMvvmItem.

QVector<QEXTMvvmViewItem*> QEXTMvvmViewModelController::findViews(const QEXTMvvmItem* item) const
{
    return d->findViews(item);
}

QStringList QEXTMvvmViewModelController::horizontalHeaderLabels() const
{
    return d->m_rowStrategy->horizontalHeaderLabels();
}

void QEXTMvvmViewModelController::onDataChange(QEXTMvvmItem* item, int role)
{
    for (auto view : findViews(item)) {
        // inform corresponding LabelView and DataView
        if (isValidItemRole(view, role)) {
            auto index = d->m_viewModel->indexFromItem(view);
            d->m_viewModel->dataChanged(index, index, QEXTMvvmViewModelUtils::ItemRoleToQtRole(role));
        }
    }
}

void QEXTMvvmViewModelController::onItemInserted(QEXTMvvmItem* parent, QEXTMvvmTagRow tagrow)
{
    d->insertView(parent, tagrow);
}

void QEXTMvvmViewModelController::onItemRemoved(QEXTMvvmItem*, QEXTMvvmTagRow) {}

void QEXTMvvmViewModelController::onAboutToRemoveItem(QEXTMvvmItem* parent, QEXTMvvmTagRow tagrow)
{
    auto item_to_remove = parent->item(tagrow.tag, tagrow.row);
    if (item_to_remove == rootItem()
        || QEXTMvvmUtils::isItemAncestor(rootItem(), item_to_remove)) {
        // special case when user removes QEXTMvvmItem which is one of ancestors of our root item
        // or root item iteslf
        d->m_viewModel->beginResetModel();
        d->m_viewModel->setRootViewItem(new QEXTMvvmRootViewItem(nullptr));
        d->m_itemToView.clear();
        d->m_rootItemPath = {};
        d->m_viewModel->endResetModel();
    } else {
        d->removeRowOfViews(item_to_remove);
    }
}

void QEXTMvvmViewModelController::updateBranch(const QEXTMvvmItem* item)
{
    auto views = findViews(item);
    if (views.empty())
        return;

    for (auto view : views)
        d->removeChildrenOfView(view);

    d->iterate(item, views.at(0));
}
