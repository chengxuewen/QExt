#ifndef _QEXTMVVMEDITORSSCIENTIFICSPINBOXEDITOR_H
#define _QEXTMVVMEDITORSSCIENTIFICSPINBOXEDITOR_H

#include <qextMvvmCustomEditor.h>

namespace ModelView
{

class QEXTMvvmScientificSpinBox;

//! Custom editor for QVariant based on double with scientific notation support.

class QEXT_MVVM_API QEXTMvvmScientificSpinBoxEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT

public:
    explicit QEXTMvvmScientificSpinBoxEditor(QWidget* parent = nullptr);

    void setRange(double minimum, double maximum);
    void setDecimals(int decimals);
    void setSingleStep(double step);

    bool is_persistent() const override;

private slots:
    void onEditingFinished();

private:
    void update_components() override;
    QEXTMvvmScientificSpinBox* m_doubleEditor;
};

} // namespace ModelView

#endif // _QEXTMVVMEDITORSSCIENTIFICSPINBOXEDITOR_H
