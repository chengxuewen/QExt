// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "viewmodel/editors/customeditor.h"

using namespace ModelView;

QExtMvvmCustomEditor::QExtMvvmCustomEditor(QWidget* parent) : QWidget(parent) {}

QVariant QExtMvvmCustomEditor::data() const
{
    return m_data;
}

//! Returns true if editor should remains alive after editing finished.

bool QExtMvvmCustomEditor::is_persistent() const
{
    return false;
}

//! Sets the data from model to editor.

void QExtMvvmCustomEditor::setData(const QVariant& data)
{
    m_data = data;
    update_components();
}

//! Saves the data as given by editor's internal components and notifies the model.

void QExtMvvmCustomEditor::setDataIntern(const QVariant& data)
{
    m_data = data;
    dataChanged(m_data);
}
