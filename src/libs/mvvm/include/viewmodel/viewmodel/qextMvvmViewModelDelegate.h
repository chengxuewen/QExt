#ifndef _QEXTMVVMVIEWMODELVIEWMODELDELEGATE_H
#define _QEXTMVVMVIEWMODELVIEWMODELDELEGATE_H

#include <qextMvvmGlobal.h>

#include <QStyledItemDelegate>

#include <memory>

namespace ModelView
{

class QEXTMvvmEditorFactoryInterface;
class QEXTMvvmCellDecoratorInterface;

//! Model delegate to provide editing/painting for custom variants.

class QEXT_MVVM_API QEXTMvvmViewModelDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit QEXTMvvmViewModelDelegate(QObject* parent = nullptr);
    ~QEXTMvvmViewModelDelegate();

    void setEditorFactory(std::unique_ptr<QEXTMvvmEditorFactoryInterface> editor_factory);
    void setCellDecoration(std::unique_ptr<QEXTMvvmCellDecoratorInterface> cell_decoration);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const override;

    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model,
                      const QModelIndex& index) const override;

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                              const QModelIndex& index) const override;

public slots:
    void onCustomEditorDataChanged();

protected:
    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const override;

    std::unique_ptr<QEXTMvvmEditorFactoryInterface> m_editor_factory;
    std::unique_ptr<QEXTMvvmCellDecoratorInterface> m_cell_decoration;
};

} // namespace ModelView

#endif // _QEXTMVVMVIEWMODELVIEWMODELDELEGATE_H
