#ifndef _QEXTEXTERNALPROPERTYCOMBOEDITOR_H
#define _QEXTEXTERNALPROPERTYCOMBOEDITOR_H

#include <qextMvvmCustomEditor.h>

#include <functional>
#include <vector>

class QComboBox;
class QStandardItemModel;

namespace ModelView
{

class QEXTMvvmExternalProperty;

//! Custom editor for table/tree cells to select ExternalProperty from the list of
//! external properties. Uses callbacks to retrieve vector of possible properties.

class QEXT_MVVM_API QEXTMvvmExternalPropertyComboEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT

public:
    using callback_t = std::function<std::vector<ModelView::QEXTMvvmExternalProperty>()>;

    QEXTMvvmExternalPropertyComboEditor(callback_t callback, QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected slots:
    virtual void onIndexChanged(int index);

private:
    int internIndex();
    void setConnected(bool isConnected);
    void update_components() override;

    callback_t m_getPropertiesCallback;
    QComboBox* m_box{nullptr};
    QStandardItemModel* m_comboModel{nullptr};
};

} // namespace ModelView

#endif // _QEXTEXTERNALPROPERTYCOMBOEDITOR_H
