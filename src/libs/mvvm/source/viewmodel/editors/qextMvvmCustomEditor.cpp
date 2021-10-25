#include <qextMvvmCustomEditor.h>

QEXTMvvmCustomEditor::QEXTMvvmCustomEditor(QWidget *parent)
    : QWidget(parent)
{

}

QEXTMvvmCustomEditor::~QEXTMvvmCustomEditor()
{

}

QVariant QEXTMvvmCustomEditor::data() const
{
    return m_data;
}

bool QEXTMvvmCustomEditor::isPersistent() const
{
    return false;
}

void QEXTMvvmCustomEditor::setData(const QVariant &data)
{
    m_data = data;
    this->updateComponents();
}

void QEXTMvvmCustomEditor::setDataIntern(const QVariant &data)
{
    m_data = data;
    emit this->dataChanged(m_data);
}
