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

#include "qextMVVMGlobal.h"
#include <QStyledItemDelegate>
#include <memory>

namespace ModelView {

class EditorFactoryInterface;
class CellDecoratorInterface;

//! Model delegate to provide editing/painting for custom variants.

class QEXT_MVVM_API ViewModelDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit ViewModelDelegate(QObject* parent = nullptr);
    ~ViewModelDelegate() override;

    void setEditorFactory(QExtUniquePointer<EditorFactoryInterface> editor_factory);
    void setCellDecoration(QExtUniquePointer<CellDecoratorInterface> cell_decoration);

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

    QExtUniquePointer<EditorFactoryInterface> m_editor_factory;
    QExtUniquePointer<CellDecoratorInterface> m_cell_decoration;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_VIEWMODELDELEGATE_H
