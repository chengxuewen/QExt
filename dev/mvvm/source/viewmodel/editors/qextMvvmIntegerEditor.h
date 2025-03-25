// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_INTEGEREDITOR_H
#define MVVM_EDITORS_INTEGEREDITOR_H

#include <qextMvvmCustomEditor.h>

class QSpinBox;

namespace ModelView {

//! Custom editor for QVariant based on integer with possibility to set limits.

class QEXT_MVVM_API QExtMvvmIntegerEditor : public QExtMvvmCustomEditor {
    Q_OBJECT

public:
    explicit QExtMvvmIntegerEditor(QWidget* parent = nullptr);

    void setRange(int minimum, int maximum);

private slots:
    void onEditingFinished();

private:
    void update_components() override;
    QSpinBox* m_intEditor;
};

} // namespace ModelView

#endif // MVVM_EDITORS_INTEGEREDITOR_H
