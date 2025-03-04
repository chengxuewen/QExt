// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_SELECTABLECOMBOBOXEDITOR_H
#define MVVM_EDITORS_SELECTABLECOMBOBOXEDITOR_H

#include "viewmodel/editors/customeditor.h"

class QComboBox;
class QStandardItemModel;

namespace ModelView {

class QExtMvvmWheelEventFilter;

//! Adds multi-selection capabilities to QComboBox.

class QEXT_MVVM_API QExtMvvmSelectableComboBoxEditor : public QExtMvvmCustomEditor {
    Q_OBJECT

public:
    explicit QExtMvvmSelectableComboBoxEditor(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    bool is_persistent() const override;

protected slots:
    void onModelDataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>&);

    void onClickedList(const QModelIndex& index);

protected:
    void update_components() override;

private:
    bool eventFilter(QObject* obj, QEvent* event) override;
    void setConnected(bool isConnected);
    void updateBoxLabel();

    bool isClickToSelect(QObject* obj, QEvent* event) const;
    bool isClickToExpand(QObject* obj, QEvent* event) const;

    QComboBox* m_box{nullptr};
    QExtMvvmWheelEventFilter* m_wheelEventFilter{nullptr};
    QStandardItemModel* m_model{nullptr};
};

} // namespace ModelView

#endif // MVVM_EDITORS_SELECTABLECOMBOBOXEDITOR_H
