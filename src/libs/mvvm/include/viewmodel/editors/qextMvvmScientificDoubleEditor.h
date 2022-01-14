#ifndef _QEXTMVVMEDITORSSCIENTIFICDOUBLEEDITOR_H
#define _QEXTMVVMEDITORSSCIENTIFICDOUBLEEDITOR_H

#include <qextMvvmCustomEditor.h>

class QLineEdit;
class QDoubleValidator;

namespace ModelView
{

//! Custom editor for QVariant based on double with scientific notation support.

class QEXT_MVVM_API QEXTMvvmScientificDoubleEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT

public:
    explicit QEXTMvvmScientificDoubleEditor(QWidget* parent = nullptr);

    void setRange(double minimum, double maximum);

private slots:
    void onEditingFinished();

private:
    void update_components() override;
    QLineEdit* m_lineEdit;
    QDoubleValidator* m_validator{nullptr};
};

} // namespace ModelView

#endif // _QEXTMVVMEDITORSSCIENTIFICDOUBLEEDITOR_H
