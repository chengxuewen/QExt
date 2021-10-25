#ifndef _QEXTMVVMSELECTABLECOMBOBOXEDITOR_H
#define _QEXTMVVMSELECTABLECOMBOBOXEDITOR_H

#include <qextMvvmGlobal.h>
#include <qextMvvmCustomEditor.h>
#include <qextMvvmCustomEventFilters.h>

#include <QComboBox>
#include <QStandardItemModel>

class QEXT_MVVM_API QEXTMvvmSelectableComboBoxEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT
public:
    explicit QEXTMvvmSelectableComboBoxEditor(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTMvvmSelectableComboBoxEditor();

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

    bool isPersistent() const QEXT_DECL_OVERRIDE;

protected slots:
    void onModelDataChanged(const QModelIndex &topLeft, const QModelIndex &, const QVector<int> &roles);
    void onClickedList(const QModelIndex &index);
    void deselectLineEdit();

protected:
    void updateComponents() QEXT_DECL_OVERRIDE;

private:
    bool eventFilter(QObject *obj, QEvent *event) QEXT_DECL_OVERRIDE;
    void setConnected(bool isConnected);
    void updateBoxLabel();

    bool isClickToSelect(QObject *obj, QEvent *event) const;
    bool isClickToExpand(QObject *obj, QEvent *event) const;

    QComboBox *m_box;
    QStandardItemModel *m_model;
    QEXTMvvmWheelEventFilter *m_wheelEventFilter;
};

#endif // _QEXTMVVMSELECTABLECOMBOBOXEDITOR_H
