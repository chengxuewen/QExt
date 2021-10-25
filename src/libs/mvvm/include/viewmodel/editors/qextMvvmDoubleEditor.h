#ifndef _QEXTMVVMDOUBLEEDITOR_H
#define _QEXTMVVMDOUBLEEDITOR_H

#include <qextMvvmGlobal.h>
#include <qextMvvmCustomEditor.h>

#include <QDoubleSpinBox>

class QEXT_MVVM_API QEXTMvvmDoubleEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT
public:
    explicit QEXTMvvmDoubleEditor(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTMvvmDoubleEditor();

    void setRange(double minimum, double maximum);

    void setDecimals(int decimals);

    void setSingleStep(double value);

private slots:
    void onEditingFinished();

private:
    void updateComponents() QEXT_DECL_OVERRIDE;

    QDoubleSpinBox *m_doubleEditor;
};

#endif // _QEXTMVVMDOUBLEEDITOR_H
