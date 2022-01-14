#ifndef _QEXTMVVMEDITORSCOMBOPROPERTYEDITOR_H
#define _QEXTMVVMEDITORSCOMBOPROPERTYEDITOR_H

#include <qextMvvmCustomEditor.h>

class QComboBox;

namespace ModelView
{

//! Custom editor for QVariant based on ComboProperty.

class QEXT_MVVM_API QEXTMvvmComboPropertyEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT

public:
    explicit QEXTMvvmComboPropertyEditor(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    bool is_persistent() const override;

protected slots:
    virtual void onIndexChanged(int index);

private:
    std::vector<std::string> internLabels();
    int internIndex();
    void setConnected(bool isConnected);
    void update_components() override;
    QComboBox* m_box;
};

} // namespace ModelView

#endif // _QEXTMVVMEDITORSCOMBOPROPERTYEDITOR_H
