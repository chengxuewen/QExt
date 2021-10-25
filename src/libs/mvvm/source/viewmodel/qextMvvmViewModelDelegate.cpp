#include <qextMvvmViewModelDelegate.h>
#include <qextMvvmDefaultEditorFactory.h>
#include <qextMvvmDefaultCellDecorator.h>

CF_BEGIN_NAMESPACE

QEXTMvvmViewModelDelegate::QEXTMvvmViewModelDelegate(QObject *parent)
    : QStyledItemDelegate(parent),
      m_editorFactory(new QEXTMvvmDefaultEditorFactory),
      m_cellDecoration(new QEXTMvvmDefaultCellDecorator)
{

}

QEXTMvvmViewModelDelegate::~QEXTMvvmViewModelDelegate()
{

}

void QEXTMvvmViewModelDelegate::setEditorFactory(QEXTMvvmEditorFactoryInterface *editorFactory)
{
    m_editorFactory.reset(editorFactory);
}

void QEXTMvvmViewModelDelegate::setCellDecoration(QEXTMvvmCellDecoratorInterface *cellDecoration)
{
    m_cellDecoration.reset(cellDecoration);
}

QWidget *QEXTMvvmViewModelDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    CFUniquePointer<QEXTMvvmCustomEditor> editor = m_editorFactory->createEditor(index);
    if (!editor.isNull())
    {
        editor->setParent(parent);
        connect(editor.data(), SIGNAL(dataChanged(QVariant)), this,SLOT(onCustomEditorDataChanged()));
        return editor.take();
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void QEXTMvvmViewModelDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.isValid())
    {
        QEXTMvvmCustomEditor *customEditor = dynamic_cast<QEXTMvvmCustomEditor *>(editor);
        if (customEditor)
        {
            customEditor->setData(index.data());
        }
    }
    QStyledItemDelegate::setEditorData(editor, index);
}

void QEXTMvvmViewModelDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.isValid())
    {
        QEXTMvvmCustomEditor *customEditor = dynamic_cast<QEXTMvvmCustomEditor *>(editor);
        if (customEditor)
        {
            model->setData(index, customEditor->data());
        }
    }
    QStyledItemDelegate::setModelData(editor, model, index);
}

QSize QEXTMvvmViewModelDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize result = QStyledItemDelegate::sizeHint(option, index);
    result.setHeight(static_cast<int>(result.height() * 1.2));
    return result;
}

void QEXTMvvmViewModelDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
    editor->setGeometry(option.rect);
}

void QEXTMvvmViewModelDelegate::onCustomEditorDataChanged()
{
    QEXTMvvmCustomEditor *customEditor = qobject_cast<QEXTMvvmCustomEditor *>(this->sender());
    emit this->commitData(customEditor);
    if (!customEditor->isPersistent())
    {
        emit this->closeEditor(customEditor);
    }
}

void QEXTMvvmViewModelDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
    QStyledItemDelegate::initStyleOption(option, index);
    if (!m_cellDecoration.isNull() && m_cellDecoration->hasCustomDecoration(index))
    {
        m_cellDecoration->initStyleOption(option, index);
    }
}

CF_END_NAMESPACE
