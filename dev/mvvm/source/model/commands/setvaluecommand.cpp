// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/commands/setvaluecommand.h"
#include "model/core/variant.h"
#include "model/model/path.h"
#include "model/model/sessionitem.h"
#include <sstream>

namespace {
std::string generate_description(const std::string& str, int role);
} // namespace

using namespace ModelView;

struct QExtMvvmSetValueCommand::SetValueCommandImpl {
    QVariant m_value; //! Value to set as a result of command execution.
    int m_role;
    QExtMvvmPath m_item_path;
    SetValueCommandImpl(QVariant value, int role) : m_value(std::move(value)), m_role(role) {}
};

// ----------------------------------------------------------------------------

QExtMvvmSetValueCommand::QExtMvvmSetValueCommand(QExtMvvmSessionItem* item, QVariant value, int role)
    : QExtMvvmAbstractItemCommand(item)
    , p_impl(qextMakeUnique<SetValueCommandImpl>(std::move(value), role))
{
    setResult(false);

    setDescription(generate_description(p_impl->m_value.toString().toStdString(), role));
    p_impl->m_item_path = pathFromItem(item);
}

QExtMvvmSetValueCommand::~QExtMvvmSetValueCommand() = default;

void QExtMvvmSetValueCommand::undo_command()
{
    swap_values();
}

void QExtMvvmSetValueCommand::execute_command()
{
    swap_values();
}

void QExtMvvmSetValueCommand::swap_values()
{
    auto item = itemFromPath(p_impl->m_item_path);
    auto old = item->data<QVariant>(p_impl->m_role);
    auto result = item->setData(p_impl->m_value, p_impl->m_role, /*direct*/ true);
    setResult(result);
    setObsolete(!result);
    p_impl->m_value = old;
}

namespace {
std::string generate_description(const std::string& str, int role)
{
    std::ostringstream ostr;
    ostr << "Set value: " << str << ", role:" << role;
    return ostr.str();
}
} // namespace
