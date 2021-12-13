// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <commands/qextMvvmItemCommand.h>
#include <commands/qextMvvmCommandAdapter.h>

using namespace ModelView;

QEXTMvvmCommandAdapter::QEXTMvvmCommandAdapter(std::shared_ptr<QEXTMvvmItemCommand> command)
    : m_command(std::move(command))
{
}

QEXTMvvmCommandAdapter::~QEXTMvvmCommandAdapter() = default;

void QEXTMvvmCommandAdapter::undo()
{
    m_command->undo();
}

void QEXTMvvmCommandAdapter::redo()
{
    m_command->execute();
    setObsolete(m_command->isObsolete());
    setText(QString::fromStdString(m_command->description()));
}
