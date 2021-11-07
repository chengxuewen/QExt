#ifndef _QEXTMVVMCOLOREDITOR_H
#define _QEXTMVVMCOLOREDITOR_H

#include <qextMvvmCustomEditor.h>

class QLabel;

class QEXTMvvmLostFocusFilter;

//! Custom editor for QVariant based on QColor.

class QEXT_MVVM_API QEXTMvvmColorEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT

public:
    explicit QEXTMvvmColorEditor(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) QEXT_DECL_OVERRIDE;

private:
    QColor currentColor() const;

    void updateComponents() QEXT_DECL_OVERRIDE;
    QLabel* m_textLabel{nullptr};
    QLabel* m_pixmapLabel{nullptr};
    QEXTMvvmLostFocusFilter* m_focusFilter;
};

#endif // _QEXTMVVMCOLOREDITOR_H
