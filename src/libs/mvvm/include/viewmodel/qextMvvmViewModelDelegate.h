#ifndef _QEXTMVVMVIEWMODELDELEGATE_H
#define _QEXTMVVMVIEWMODELDELEGATE_H

#include <QStyledItemDelegate>
#include <memory>
#include <qextMvvmGlobal.h>


class QEXTMvvmEditorFactoryInterface;
class QEXTMvvmCellDecoratorInterface;

//! Model delegate to provide editing/painting for custom variants.

class QEXT_MVVM_API QEXTMvvmViewModelDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit QEXTMvvmViewModelDelegate(QObject* parent = nullptr);
    ~QEXTMvvmViewModelDelegate() QEXT_DECL_OVERRIDE;

    void setEditorFactory(QEXTMvvmEditorFactoryInterface *editor_factory);
    void setCellDecoration(QEXTMvvmCellDecoratorInterface *cell_decoration);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const QEXT_DECL_OVERRIDE;

    void setEditorData(QWidget* editor, const QModelIndex& index) const QEXT_DECL_OVERRIDE;
    void setModelData(QWidget* editor, QAbstractItemModel* model,
                      const QModelIndex& index) const QEXT_DECL_OVERRIDE;

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const QEXT_DECL_OVERRIDE;

    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                              const QModelIndex& index) const QEXT_DECL_OVERRIDE;

public slots:
    void onCustomEditorDataChanged();

protected:
    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const QEXT_DECL_OVERRIDE;

    QScopedPointer<QEXTMvvmEditorFactoryInterface> m_editor_factory;
    QScopedPointer<QEXTMvvmCellDecoratorInterface> m_cell_decoration;
};


#endif // _QEXTMVVMVIEWMODELDELEGATE_H
