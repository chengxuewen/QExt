#include <qextMvvmCustomEditor.h>



QEXTMvvmCustomEditor::QEXTMvvmCustomEditor(QWidget* parent) : QWidget(parent) {}

QVariant QEXTMvvmCustomEditor::data() const
{
    return m_data;
}

//! Returns true if editor should remains alive after editing finished.

bool QEXTMvvmCustomEditor::isPersistent() const
{
    return false;
}

//! Sets the data from model to editor.

void QEXTMvvmCustomEditor::setData(const QVariant& data)
{
    m_data = data;
    updateComponents();
}

//! Saves the data as given by editor's internal components and notifies the model.

void QEXTMvvmCustomEditor::setDataIntern(const QVariant& data)
{
    m_data = data;
    dataChanged(m_data);
}
