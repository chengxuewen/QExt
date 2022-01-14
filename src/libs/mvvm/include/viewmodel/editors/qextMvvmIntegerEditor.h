#ifndef _QEXTMVVMEDITORSINTEGEREDITOR_H
#define _QEXTMVVMEDITORSINTEGEREDITOR_H

#include <qextMvvmCustomEditor.h>

class QSpinBox;

namespace ModelView
{

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
    void update_components() override;
    QSpinBox* m_intEditor;
};

} // namespace ModelView

#endif // _QEXTMVVMEDITORSINTEGEREDITOR_H
