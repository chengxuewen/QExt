// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_COLOREDITOR_H
#define MVVM_EDITORS_COLOREDITOR_H

#include "viewmodel/editors/customeditor.h"

class QLabel;

namespace ModelView {

class QExtMvvmLostFocusFilter;

//! Custom editor for QVariant based on QColor.

class QEXT_MVVM_API QExtMvvmColorEditor : public QExtMvvmCustomEditor {
    Q_OBJECT

public:
    explicit QExtMvvmColorEditor(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    QColor currentColor() const;

    void update_components() override;
    QLabel* m_textLabel{nullptr};
    QLabel* m_pixmapLabel{nullptr};
    QExtMvvmLostFocusFilter* m_focusFilter;
};

} // namespace ModelView

#endif // MVVM_EDITORS_COLOREDITOR_H
