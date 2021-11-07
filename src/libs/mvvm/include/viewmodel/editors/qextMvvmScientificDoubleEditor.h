#ifndef _QEXTMVVMSCIENTIFICDOUBLEEDITOR_H
#define _QEXTMVVMSCIENTIFICDOUBLEEDITOR_H

#include <qextMvvmCustomEditor.h>

class QLineEdit;
class QDoubleValidator;

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
    void updateComponents() QEXT_DECL_OVERRIDE;
    QLineEdit* m_lineEdit;
    QDoubleValidator* m_validator{nullptr};
};


#endif // _QEXTMVVMSCIENTIFICDOUBLEEDITOR_H
