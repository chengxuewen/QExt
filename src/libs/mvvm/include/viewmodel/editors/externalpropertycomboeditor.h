// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef EXTERNALPROPERTYCOMBOEDITOR_H
#define EXTERNALPROPERTYCOMBOEDITOR_H

#include <functional>
#include <editors/customeditor.h>
#include <vector>

class QComboBox;
class QStandardItemModel;

namespace ModelView
{

class QEXTMvvmExternalProperty;

//! Custom editor for table/tree cells to select QEXTMvvmExternalProperty from the list of
//! external properties. Uses callbacks to retrieve vector of possible properties.

class QEXT_MVVM_API ExternalPropertyComboEditor : public CustomEditor
{
    Q_OBJECT

public:
    using callback_t = std::function<std::vector<ModelView::QEXTMvvmExternalProperty>()>;

    ExternalPropertyComboEditor(callback_t callback, QWidget* parent = nullptr);

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

#endif // EXTERNALPROPERTYCOMBOEDITOR_H
