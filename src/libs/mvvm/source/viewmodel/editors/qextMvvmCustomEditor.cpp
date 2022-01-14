// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmCustomEditor.h>

using namespace ModelView;

QEXTMvvmCustomEditor::QEXTMvvmCustomEditor(QWidget* parent) : QWidget(parent) {}

QVariant QEXTMvvmCustomEditor::data() const
{
    return m_data;
}

//! Returns true if editor should remains alive after editing finished.

bool QEXTMvvmCustomEditor::is_persistent() const
{
    return false;
}

//! Sets the data from model to editor.

void QEXTMvvmCustomEditor::setData(const QVariant& data)
{
    m_data = data;
    update_components();
}

//! Saves the data as given by editor's internal components and notifies the model.

void QEXTMvvmCustomEditor::setDataIntern(const QVariant& data)
{
    m_data = data;
    dataChanged(m_data);
}
