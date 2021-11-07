#ifndef _QEXTMVVMEXTERNALPROPERTYCOMBOEDITOR_H
#define _QEXTMVVMEXTERNALPROPERTYCOMBOEDITOR_H

#include <qextFunction.h>
#include <qextMvvmCustomEditor.h>

#include <QVector>

class QComboBox;
class QStandardItemModel;


class QEXTMvvmExternalProperty;

//! Custom editor for table/tree cells to select QEXTMvvmExternalProperty from the list of
//! external properties. Uses callbacks to retrieve vector of possible properties.

class QEXT_MVVM_API QEXTMvvmExternalPropertyComboEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT

public:
    typedef QEXTFunction<QVector<QEXTMvvmExternalProperty> > callback_t;

    QEXTMvvmExternalPropertyComboEditor(callback_t callback, QWidget* parent = nullptr);

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

protected slots:
    virtual void onIndexChanged(int index);

private:
    int internIndex();
    void setConnected(bool isConnected);
    void updateComponents() QEXT_DECL_OVERRIDE;

    callback_t m_getPropertiesCallback;
    QComboBox* m_box{nullptr};
    QStandardItemModel* m_comboModel{nullptr};
};


#endif // _QEXTMVVMEXTERNALPROPERTYCOMBOEDITOR_H
