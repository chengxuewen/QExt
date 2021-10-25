#ifndef _QEXTMVVMSCIENTIFICSPINBOXEDITOR_H
#define _QEXTMVVMSCIENTIFICSPINBOXEDITOR_H

#include <qextMvvmGlobal.h>
#include <qextMvvmCustomEditor.h>

class QEXTMvvmScientificSpinBox;
class QEXT_MVVM_API QEXTMvvmScientificSpinBoxEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT
public:
    explicit QEXTMvvmScientificSpinBoxEditor(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTMvvmScientificSpinBoxEditor();

    void setRange(double minimum, double maximum);
    void setDecimals(int decimals);
    void setSingleStep(double step);

    bool isPersistent() const QEXT_DECL_OVERRIDE;

private slots:
    void onEditingFinished();

private:
    void updateComponents() QEXT_DECL_OVERRIDE;

    QEXTMvvmScientificSpinBox *m_doubleEditor;
};

#endif // _QEXTMVVMSCIENTIFICSPINBOXEDITOR_H
