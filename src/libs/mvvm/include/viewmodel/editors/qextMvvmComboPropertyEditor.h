#ifndef _QEXTMVVMCOMBOPROPERTYEDITOR_H
#define _QEXTMVVMCOMBOPROPERTYEDITOR_H

#include <qextMvvmGlobal.h>
#include <qextMvvmCustomEditor.h>

#include <cfMvvmComboProperty.h>

#include <QComboBox>

#include <string>

CF_USE_NAMESPACE

class QEXT_MVVM_API QEXTMvvmComboPropertyEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT
public:
    explicit QEXTMvvmComboPropertyEditor(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTMvvmComboPropertyEditor();

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

    bool isPersistent() const QEXT_DECL_OVERRIDE;

protected slots:
    virtual void onIndexChanged(int index);

    void updateComponents() QEXT_DECL_OVERRIDE;

private:
    std::vector<std::string> internLabels();
    int internIndex();
    void setConnected(bool isConnected);

    QComboBox *m_box;
};

#endif // _QEXTMVVMCOMBOPROPERTYEDITOR_H
