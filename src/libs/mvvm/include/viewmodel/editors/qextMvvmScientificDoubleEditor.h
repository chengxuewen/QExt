#ifndef _QEXTMVVMSCIENTIFICDOUBLEEDITOR_H
#define _QEXTMVVMSCIENTIFICDOUBLEEDITOR_H

#include <qextMvvmGlobal.h>
#include <qextMvvmCustomEditor.h>

#include <QLineEdit>
#include <QDoubleValidator>

class QEXT_MVVM_API QEXTMvvmScientificDoubleEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT
public:
    explicit QEXTMvvmScientificDoubleEditor(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTMvvmScientificDoubleEditor();

    void setRange(double minimum, double maximum);

private slots:
    void onEditingFinished();

private:
    void updateComponents() QEXT_DECL_OVERRIDE;

    QLineEdit *m_lineEdit;
    QDoubleValidator *m_validator;
};

#endif // _QEXTMVVMSCIENTIFICDOUBLEEDITOR_H
