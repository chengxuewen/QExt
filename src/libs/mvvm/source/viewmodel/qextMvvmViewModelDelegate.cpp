#include <QApplication>
#include <qextMvvmCustomEditor.h>
#include <qextMvvmDefaultEditorFactory.h>
#include <qextMvvmComboProperty.h>
#include <qextMvvmDefaultCellDecorator.h>
#include <qextMvvmViewModelDelegate.h>

namespace
{
const double scale_default_height_factor{1.2};
}



QEXTMvvmViewModelDelegate::QEXTMvvmViewModelDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
    , m_editor_factory(new QEXTMvvmDefaultEditorFactory)
    , m_cell_decoration(new QEXTMvvmDefaultCellDecorator)
{
}

QEXTMvvmViewModelDelegate::~QEXTMvvmViewModelDelegate()
{

}

void QEXTMvvmViewModelDelegate::setEditorFactory(QEXTMvvmEditorFactoryInterface *editor_factory)
{
    m_editor_factory.reset(editor_factory);
}

void QEXTMvvmViewModelDelegate::setCellDecoration(QEXTMvvmCellDecoratorInterface *cell_decoration)
{
    m_cell_decoration.reset(cell_decoration);
}

QWidget* QEXTMvvmViewModelDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                                         const QModelIndex& index) const
{
    QEXTMvvmCustomEditor *editor = m_editor_factory->createEditor(index);
    if (editor) {
        editor->setParent(parent);
        connect(editor, &QEXTMvvmCustomEditor::dataChanged, this, &QEXTMvvmViewModelDelegate::onCustomEditorDataChanged);
        return editor;
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void QEXTMvvmViewModelDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (!index.isValid())
        return;

    if (auto customEditor = dynamic_cast<QEXTMvvmCustomEditor*>(editor))
        customEditor->setData(index.data());
    else
        QStyledItemDelegate::setEditorData(editor, index);
}

void QEXTMvvmViewModelDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
                                     const QModelIndex& index) const
{
    if (!index.isValid())
        return;

    if (auto customEditor = dynamic_cast<QEXTMvvmCustomEditor*>(editor)) {
        model->setData(index, customEditor->data());
    } else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

//! Increases height of the row by 20% wrt the default.

QSize QEXTMvvmViewModelDelegate::sizeHint(const QStyleOptionViewItem& option,
                                  const QModelIndex& index) const
{
    QSize result = QStyledItemDelegate::sizeHint(option, index);
    result.setHeight(static_cast<int>(result.height() * scale_default_height_factor));
    return result;
}

//! Makes an editor occupying whole available space in a cell. If cell contains an icon
//! as a decoration (i.e. icon of material property), it will be hidden as soon as editor
//! up and running.

void QEXTMvvmViewModelDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                                             const QModelIndex& index) const
{
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
    editor->setGeometry(option.rect);
}

void QEXTMvvmViewModelDelegate::onCustomEditorDataChanged()
{
    auto editor = qobject_cast<QEXTMvvmCustomEditor*>(sender());
    emit commitData(editor);
    if (!editor->isPersistent())
        emit closeEditor(editor);
}

void QEXTMvvmViewModelDelegate::initStyleOption(QStyleOptionViewItem* option,
                                        const QModelIndex& index) const
{
    QStyledItemDelegate::initStyleOption(option, index);

    if (m_cell_decoration && m_cell_decoration->hasCustomDecoration(index))
        m_cell_decoration->initStyleOption(option, index);
}
