#include <qextMvvmAbstractItemCommand.h>
#include <qextMvvmCommandAdapter.h>



QEXTCommandAdapter::QEXTCommandAdapter(const QSharedPointer<QEXTMvvmAbstractItemCommand> &command)
    : m_command(command)
{
}

QEXTCommandAdapter::~QEXTCommandAdapter()
{

}

void QEXTCommandAdapter::undo()
{
    m_command->undo();
}

void QEXTCommandAdapter::redo()
{
    m_command->execute();
    this->setObsolete(m_command->isObsolete());
    this->setText(m_command->description());
}
