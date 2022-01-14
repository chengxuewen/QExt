#ifndef _QEXTMVVMEDITORSDOUBLEEDITOR_H
#define _QEXTMVVMEDITORSDOUBLEEDITOR_H

#include <qextMvvmCustomEditor.h>

class QDoubleSpinBox;

namespace ModelView
{

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
    void update_components() override;
    QDoubleSpinBox* m_doubleEditor;
};

} // namespace ModelView

#endif // _QEXTMVVMEDITORSDOUBLEEDITOR_H
