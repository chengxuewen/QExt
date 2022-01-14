#ifndef _QEXTMVVMEDITORSCOLOREDITOR_H
#define _QEXTMVVMEDITORSCOLOREDITOR_H

#include <qextMvvmCustomEditor.h>

class QLabel;

namespace ModelView
{

class QEXTMvvmLostFocusFilter;

//! Custom editor for QVariant based on QColor.

class QEXT_MVVM_API QEXTMvvmColorEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT

public:
    explicit QEXTMvvmColorEditor(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    QColor currentColor() const;

    void update_components() override;
    QLabel* m_textLabel{nullptr};
    QLabel* m_pixmapLabel{nullptr};
    QEXTMvvmLostFocusFilter* m_focusFilter;
};

} // namespace ModelView

#endif // _QEXTMVVMEDITORSCOLOREDITOR_H
