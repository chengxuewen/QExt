#ifndef _QEXTMVVMINTEGEREDITOR_H
#define _QEXTMVVMINTEGEREDITOR_H

#include <qextMvvmCustomEditor.h>

class QSpinBox;


//! Custom editor for QVariant based on integer with possibility to set limits.

class QEXT_MVVM_API QEXTMvvmIntegerEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT

public:
    explicit QEXTMvvmIntegerEditor(QWidget* parent = nullptr);

    void setRange(int minimum, int maximum);

private slots:
    void onEditingFinished();

private:
    void updateComponents() QEXT_DECL_OVERRIDE;
    QSpinBox* m_intEditor;
};

#endif // _QEXTMVVMINTEGEREDITOR_H
