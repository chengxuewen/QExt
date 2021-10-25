#ifndef _QEXTMVVMBOOLEDITOR_H
#define _QEXTMVVMBOOLEDITOR_H

#include <qextMvvmGlobal.h>
#include <qextMvvmCustomEditor.h>

#include <QCheckBox>

class QEXT_MVVM_API QEXTMvvmBoolEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT
public:
    explicit QEXTMvvmBoolEditor(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTMvvmBoolEditor();

    bool isPersistent() const QEXT_DECL_OVERRIDE;

private slots:
    void onCheckBoxChange(bool value);

private:
    void updateComponents() QEXT_DECL_OVERRIDE;

    QCheckBox *m_checkBox;
};

#endif // _QEXTMVVMBOOLEDITOR_H
