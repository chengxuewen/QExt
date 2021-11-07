#ifndef _QEXTMVVMDOUBLEEDITOR_H
#define _QEXTMVVMDOUBLEEDITOR_H

#include <qextMvvmCustomEditor.h>

class QDoubleSpinBox;


//! Custom editor for QVariant based on double with possibility to set limits.

class QEXT_MVVM_API QEXTMvvmDoubleEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT

public:
    explicit QEXTMvvmDoubleEditor(QWidget* parent = nullptr);

    void setRange(double minimum, double maximum);

    void setDecimals(int decimals);

    void setSingleStep(double value);

private slots:
    void onEditingFinished();

private:
    void updateComponents() QEXT_DECL_OVERRIDE;
    QDoubleSpinBox* m_doubleEditor;
};

#endif // _QEXTMVVMDOUBLEEDITOR_H
