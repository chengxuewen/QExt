#ifndef _QEXTMVVMSELECTABLECOMBOBOXEDITOR_H
#define _QEXTMVVMSELECTABLECOMBOBOXEDITOR_H

#include <qextMvvmCustomEditor.h>

class QComboBox;
class QStandardItemModel;


class QEXTMvvmWheelEventFilter;

//! Adds multi-selection capabilities to QComboBox.

class QEXT_MVVM_API QEXTMvvmSelectableComboBoxEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT

public:
    explicit QEXTMvvmSelectableComboBoxEditor(QWidget* parent = nullptr);

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

    bool isPersistent() const QEXT_DECL_OVERRIDE;

protected slots:
    void onModelDataChanged(const QModelIndex &topLeft, const QModelIndex &, const QVector<int> &roles);

    void onClickedList(const QModelIndex& index);

protected:
    void updateComponents() QEXT_DECL_OVERRIDE;

private:
    bool eventFilter(QObject* obj, QEvent* event) QEXT_DECL_OVERRIDE;
    void setConnected(bool isConnected);
    void updateBoxLabel();

    bool isClickToSelect(QObject* obj, QEvent* event) const;
    bool isClickToExpand(QObject* obj, QEvent* event) const;

    QComboBox* m_box{nullptr};
    QEXTMvvmWheelEventFilter* m_wheelEventFilter{nullptr};
    QStandardItemModel* m_model{nullptr};
};


#endif // _QEXTMVVMSELECTABLECOMBOBOXEDITOR_H
