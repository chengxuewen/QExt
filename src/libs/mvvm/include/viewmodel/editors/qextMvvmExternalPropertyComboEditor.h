#ifndef _QEXTMVVMEXTERNALPROPERTYCOMBOEDITOR_H
#define _QEXTMVVMEXTERNALPROPERTYCOMBOEDITOR_H

#include <qextMvvmGlobal.h>
#include <qextMvvmCustomEditor.h>

#include <cfMvvmExternalProperty.h>
#include <cfSlot.h>

#include <QComboBox>
#include <QStandardItemModel>

#include <vector>

CF_USE_NAMESPACE

class QEXT_MVVM_API QEXTMvvmExternalPropertyComboEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT
public:
    typedef CFSlot<std::vector<CFMvvmExternalProperty> > Callback;

    explicit QEXTMvvmExternalPropertyComboEditor(Callback callback, QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTMvvmExternalPropertyComboEditor();

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

protected slots:
    virtual void onIndexChanged(int index);

private:
    void updateComponents() QEXT_DECL_OVERRIDE;

    int internIndex();
    void setConnected(bool isConnected);

    Callback m_getPropertiesCallback;
    QComboBox *m_box;
    QStandardItemModel *m_comboModel;
};

#endif // _QEXTMVVMEXTERNALPROPERTYCOMBOEDITOR_H
