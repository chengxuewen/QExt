// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmCommandAdapter.h>
#include <qextMvvmAbstractItemCommand.h>
// #include "model/commands/abstractitemcommand.h"

using namespace ModelView;

QExtMvvmCommandAdapter::QExtMvvmCommandAdapter(std::shared_ptr<QExtMvvmAbstractItemCommand> command)
    : m_command(std::move(command))
{
}

QExtMvvmCommandAdapter::~QExtMvvmCommandAdapter() = default;

void QExtMvvmCommandAdapter::undo()
{
    m_command->undo();
}

void QExtMvvmCommandAdapter::redo()
{
    m_command->execute();
    setObsolete(m_command->isObsolete());
    setText(QString::fromStdString(m_command->description()));
}
