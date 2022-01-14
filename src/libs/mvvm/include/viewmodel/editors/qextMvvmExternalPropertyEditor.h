#ifndef _QEXTMVVMEDITORSEXTERNALPROPERTYEDITOR_H
#define _QEXTMVVMEDITORSEXTERNALPROPERTYEDITOR_H

#include <qextMvvmCustomEditor.h>

#include <functional>

class QLabel;

namespace ModelView
{

class QEXTMvvmLostFocusFilter;

//! Custom editor for QVariant based on ExternalProperty.
//! Contains icon, label and button to call external dialog via callback mechanism.

class QEXT_MVVM_API QEXTMvvmExternalPropertyEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT

public:
    explicit QEXTMvvmExternalPropertyEditor(QWidget* parent = nullptr);

    void setCallback(std::function<void(const QVariant&)> callback);

private slots:
    void buttonClicked();

private:
    void update_components() override;
    QLabel* m_textLabel;
    QLabel* m_pixmapLabel;
    QEXTMvvmLostFocusFilter* m_focusFilter;
    std::function<void(const QVariant&)> m_callback; //! actions to take on clicked button
};

} // namespace ModelView

#endif // _QEXTMVVMEDITORSEXTERNALPROPERTYEDITOR_H
