#ifndef _QEXTMVVMVIEWMODELDELEGATE_H
#define _QEXTMVVMVIEWMODELDELEGATE_H

#include <qextMvvmGlobal.h>
#include <qextMvvmEditorFactoryInterface.h>
#include <qextMvvmCellDecoratorInterface.h>

#include <cfUniquePointer.h>

#include <QStyledItemDelegate>

CF_BEGIN_NAMESPACE

class QEXT_MVVM_API QEXTMvvmViewModelDelegate : public QStyledItemDelegate
{
public:
    explicit QEXTMvvmViewModelDelegate(QObject* parent = QEXT_DECL_NULLPTR);
    ~QEXTMvvmViewModelDelegate();

    void setEditorFactory(QEXTMvvmEditorFactoryInterface *editorFactory);
    void setCellDecoration(QEXTMvvmCellDecoratorInterface *cellDecoration);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const QEXT_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const QEXT_DECL_OVERRIDE;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_DECL_OVERRIDE;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_DECL_OVERRIDE;

public slots:
    void onCustomEditorDataChanged();

protected:
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const QEXT_DECL_OVERRIDE;

    CFUniquePointer<QEXTMvvmEditorFactoryInterface> m_editorFactory;
    CFUniquePointer<QEXTMvvmCellDecoratorInterface> m_cellDecoration;

};

CF_END_NAMESPACE

#endif // _QEXTMVVMVIEWMODELDELEGATE_H
