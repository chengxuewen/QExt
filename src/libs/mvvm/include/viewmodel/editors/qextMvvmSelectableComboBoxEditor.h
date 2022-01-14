#ifndef _QEXTMVVMEDITORSSELECTABLECOMBOBOXEDITOR_H
#define _QEXTMVVMEDITORSSELECTABLECOMBOBOXEDITOR_H

#include <qextMvvmCustomEditor.h>

class QComboBox;
class QStandardItemModel;

namespace ModelView
{

class QEXTMvvmWheelEventFilter;

//! Adds multi-selection capabilities to QComboBox.

class QEXT_MVVM_API QEXTMvvmSelectableComboBoxEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT

public:
    explicit QEXTMvvmSelectableComboBoxEditor(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    bool is_persistent() const override;

protected slots:
    void onModelDataChanged(const QModelIndex &topLeft, const QModelIndex &, const QVector<int> &roles);

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
    QEXTMvvmWheelEventFilter* m_wheelEventFilter{nullptr};
    QStandardItemModel* m_model{nullptr};
};

} // namespace ModelView

#endif // _QEXTMVVMEDITORSSELECTABLECOMBOBOXEDITOR_H
