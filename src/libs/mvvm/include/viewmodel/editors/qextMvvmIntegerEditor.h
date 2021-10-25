#ifndef _QEXTMVVMINTEGEREDITOR_H
#define _QEXTMVVMINTEGEREDITOR_H

#include <qextMvvmGlobal.h>
#include <qextMvvmCustomEditor.h>

#include <QSpinBox>

class QEXT_MVVM_API QEXTMvvmIntegerEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT
public:
    explicit QEXTMvvmIntegerEditor(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTMvvmIntegerEditor();

    void setRange(int minimum, int maximum);

private slots:
    void onEditingFinished();

private:
    void updateComponents() QEXT_DECL_OVERRIDE;

    QSpinBox *m_intEditor;
};

#endif // _QEXTMVVMINTEGEREDITOR_H
