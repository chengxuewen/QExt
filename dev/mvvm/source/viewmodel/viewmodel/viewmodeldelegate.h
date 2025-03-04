// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_VIEWMODELDELEGATE_H
#define MVVM_VIEWMODEL_VIEWMODELDELEGATE_H

#include <qextMvvmGlobal.h>
#include <QStyledItemDelegate>
#include <memory>

namespace ModelView {

class QExtMvvmEditorFactoryInterface;
class QExtMvvmCellDecoratorInterface;

//! Model delegate to provide editing/painting for custom variants.

class QEXT_MVVM_API QExtMvvmViewModelDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit QExtMvvmViewModelDelegate(QObject* parent = nullptr);
    ~QExtMvvmViewModelDelegate() override;

    void setEditorFactory(QExtUniquePointer<QExtMvvmEditorFactoryInterface> editor_factory);
    void setCellDecoration(QExtUniquePointer<QExtMvvmCellDecoratorInterface> cell_decoration);

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

    QExtUniquePointer<QExtMvvmEditorFactoryInterface> m_editor_factory;
    QExtUniquePointer<QExtMvvmCellDecoratorInterface> m_cell_decoration;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_VIEWMODELDELEGATE_H
