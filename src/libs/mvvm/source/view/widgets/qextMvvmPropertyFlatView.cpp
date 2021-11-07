#include <qextMvvmPropertyFlatView.h>
#include <qextMvvmPropertyFlatView_p.h>
#include <qextMvvmViewModelFactory.h>

#include <QDataWidgetMapper>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QGridLayout>
#include <QDebug>
#include <QLabel>
#include <QMap>

QEXTMvvmPropertyFlatViewPrivate::QEXTMvvmPropertyFlatViewPrivate(QEXTMvvmPropertyFlatView *q)
    : q_ptr(q)
    , m_delegate(new QEXTMvvmViewModelDelegate)
    , m_editorFactory(new QEXTMvvmDefaultEditorFactory)
    , m_gridLayout(new QGridLayout)
{

}

QEXTMvvmPropertyFlatViewPrivate::~QEXTMvvmPropertyFlatViewPrivate()
{

}

QLabel *QEXTMvvmPropertyFlatViewPrivate::createLabel(QEXTMvvmViewItem *viewItem)
{
    QLabel *result = new QLabel(viewItem->data(Qt::DisplayRole).toString());
    result->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed));
    result->setEnabled(viewItem->item()->isEnabled());
    return result;
}

QEXTMvvmCustomEditor *QEXTMvvmPropertyFlatViewPrivate::createEditor(const QModelIndex &index)
{
    QEXTMvvmCustomEditor *editor = m_editorFactory->createEditor(index);
    m_delegate->setEditorData(editor, index);
    QObject::connect(editor, SIGNAL(dataChanged(QVariant)), m_delegate.data(), SLOT(onCustomEditorDataChanged()));
    editor->setEnabled(m_viewModel->itemFromIndex(index)->isEnabled());
    return editor;
}

void QEXTMvvmPropertyFlatViewPrivate::connectModel()
{
    QObject::connect(m_viewModel.data(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
                     q_ptr, SLOT(onDataChange(QModelIndex,QModelIndex,QVector<int>)));
    QObject::connect(m_viewModel.data(), SIGNAL(rowsInserted(QModelIndex,int,int)),
                     q_ptr, SLOT(onRowInserted(QModelIndex,int,int)));
    QObject::connect(m_viewModel.data(), SIGNAL(rowsRemoved(QModelIndex,int,int)),
                     q_ptr, SLOT(onRowRemoved(QModelIndex,int,int)));
}

QWidget *QEXTMvvmPropertyFlatViewPrivate::createWidget(const QModelIndex &index)
{
    QEXTMvvmViewItem *viewItem = m_viewModel->viewItemFromIndex(index);
    QEXTMvvmViewLabelItem *labelItem = dynamic_cast<QEXTMvvmViewLabelItem *>(viewItem);
    if (labelItem)
    {
        return this->createLabel(labelItem);
    }
    return this->createEditor(index);
}

void QEXTMvvmPropertyFlatViewPrivate::updateGridLayout()
{
    LayoutUtils::clearGridLayout(m_gridLayout, true);

    this->updateMappers();
    m_itemToWidget.clear();
    for (int row = 0; row < m_viewModel->rowCount(); ++row)
    {
        for (int column = 0; column < m_viewModel->columnCount(); ++column)
        {
            QModelIndex index = m_viewModel->index(row, column);
            QWidget *widget = this->createWidget(index);
            m_itemToWidget[m_viewModel->viewItemFromIndex(index)] = widget;
            m_widgetMappers[row]->addMapping(widget, column);
            m_gridLayout->addWidget(widget, row, column);
        }
    }
}

void QEXTMvvmPropertyFlatViewPrivate::updateMappers()
{
    m_widgetMappers.clear();
    for (int row = 0; row < m_viewModel->rowCount(); ++row)
    {
        QSharedPointer<QDataWidgetMapper> mapper(new QDataWidgetMapper);
        mapper->setModel(m_viewModel.data());
        mapper->setItemDelegate(m_delegate.data());
        mapper->setRootIndex(QModelIndex());
        mapper->setCurrentModelIndex(m_viewModel->index(row, 0));
        m_widgetMappers.append(mapper);
    }
}



QEXTMvvmPropertyFlatView::QEXTMvvmPropertyFlatView(QWidget* parent)
    : QWidget(parent), d_ptr(new QEXTMvvmPropertyFlatViewPrivate(this))
{
    QEXT_DECL_D(QEXTMvvmPropertyFlatView);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    d->m_gridLayout->setSpacing(6);
    layout->addLayout(d->m_gridLayout);
    layout->addStretch(1);

    this->setLayout(layout);
}

QEXTMvvmPropertyFlatView::~QEXTMvvmPropertyFlatView()
{

}

void QEXTMvvmPropertyFlatView::setItem(QEXTMvvmItem* item)
{
    QEXT_DECL_D(QEXTMvvmPropertyFlatView);
    d->m_viewModel.reset(QEXTMvvmViewModelFactory::createPropertyFlatViewModel(item->model()));
    d->m_viewModel->setRootItem(item);
    d->connectModel();
    d->updateGridLayout();
}

void QEXTMvvmPropertyFlatView::onDataChange(const QModelIndex &topLeft, const QModelIndex &, const QVector<int> &roles)
{
    QEXT_DECL_D(QEXTMvvmPropertyFlatView);
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    QVector<int> expectedRoles = {Qt::ForegroundRole};
#else
    QVector<int> expectedRoles = {Qt::TextColorRole};
#endif
    if (roles == expectedRoles)
    {
        QEXTMvvmViewItem *viewItem = d->m_viewModel->viewItemFromIndex(topLeft);
        if (d->m_itemToWidget.contains(viewItem))
        {
            d->m_itemToWidget.value(viewItem)->setEnabled(viewItem->item()->isEnabled());
        }
    }
}

void QEXTMvvmPropertyFlatView::onRowInserted(const QModelIndex &, int, int)
{
    QEXT_DECL_D(QEXTMvvmPropertyFlatView);
    d->updateGridLayout();
}

void QEXTMvvmPropertyFlatView::onRowRemoved(const QModelIndex &, int, int)
{
    QEXT_DECL_D(QEXTMvvmPropertyFlatView);
    d->updateGridLayout();
}
