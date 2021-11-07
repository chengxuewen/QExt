#ifndef _QEXTMVVMMVVMEXTERNALPROPERTYEDITOR_H
#define _QEXTMVVMMVVMEXTERNALPROPERTYEDITOR_H

#include <qextFunction.h>
#include <qextMvvmCustomEditor.h>

class QLabel;

class QEXTMvvmLostFocusFilter;

//! Custom editor for QVariant based on QEXTMvvmExternalProperty.
//! Contains icon, label and button to call external dialog via callback mechanism.

class QEXT_MVVM_API QEXTMvvmExternalPropertyEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT

public:
    explicit QEXTMvvmExternalPropertyEditor(QWidget* parent = nullptr);

    void setCallback(QEXTFunction<void, const QVariant &> callback);

private slots:
    void buttonClicked();

private:
    void updateComponents() QEXT_DECL_OVERRIDE;
    QLabel* m_textLabel;
    QLabel* m_pixmapLabel;
    QEXTMvvmLostFocusFilter* m_focusFilter;
    QEXTFunction<void, const QVariant &> m_callback; //! actions to take on clicked button
};


#endif // _QEXTMVVMMVVMEXTERNALPROPERTYEDITOR_H
