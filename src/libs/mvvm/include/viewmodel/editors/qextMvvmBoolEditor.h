#ifndef _QEXTMVVMEDITORSBOOLEDITOR_H
#define _QEXTMVVMEDITORSBOOLEDITOR_H

#include <qextMvvmCustomEditor.h>

class QCheckBox;

namespace ModelView
{

//! Custom editor for QVariant based on bool values.

class QEXT_MVVM_API QEXTMvvmBoolEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT

public:
    explicit QEXTMvvmBoolEditor(QWidget* parent = nullptr);

    bool is_persistent() const override;

private slots:
    void onCheckBoxChange(bool value);

private:
    void update_components() override;
    QCheckBox* m_checkBox;
};

} // namespace ModelView

#endif // _QEXTMVVMEDITORSBOOLEDITOR_H
