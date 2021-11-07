#ifndef _QEXTMVVMCOMBOPROPERTYEDITOR_H
#define _QEXTMVVMCOMBOPROPERTYEDITOR_H

#include <qextMvvmCustomEditor.h>

class QComboBox;


//! Custom editor for QVariant based on QEXTMvvmComboProperty.

class QEXT_MVVM_API QEXTMvvmComboPropertyEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT

public:
    explicit QEXTMvvmComboPropertyEditor(QWidget* parent = nullptr);

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

    bool isPersistent() const QEXT_DECL_OVERRIDE;

protected slots:
    virtual void onIndexChanged(int index);

private:
    QVector<QString> internLabels();
    int internIndex();
    void setConnected(bool isConnected);
    void updateComponents() QEXT_DECL_OVERRIDE;
    QComboBox* m_box;
};

#endif // _QEXTMVVMCOMBOPROPERTYEDITOR_H
