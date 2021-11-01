#include <qextMvvmAbstractItemCommand.h>
#include <qextMvvmCommandAdapter.h>

using namespace ModelView;

QEXTCommandAdapter::QEXTCommandAdapter(std::shared_ptr<QEXTAbstractItemCommand> command)
    : m_command(std::move(command))
{
}

QEXTCommandAdapter::~QEXTCommandAdapter() = default;

void QEXTCommandAdapter::undo()
{
    m_command->undo();
}

void QEXTCommandAdapter::redo()
{
    m_command->execute();
    setObsolete(m_command->isObsolete());
    setText(QString::fromStdString(m_command->description()));
}
