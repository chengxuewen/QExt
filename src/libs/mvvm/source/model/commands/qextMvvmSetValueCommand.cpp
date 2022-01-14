// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmSetValueCommand.h>
#include <qextMvvmPath.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmModelUtils.h>
#include <sstream>

namespace
{
std::string generate_description(const std::string& str, int role);
} // namespace

using namespace ModelView;

struct QEXTMvvmSetValueCommand::SetValueCommandImpl {
    QVariant m_value; //! Value to set as a result of command execution.
    int m_role;
    QEXTMvvmPath m_item_path;
    SetValueCommandImpl(QVariant value, int role) : m_value(std::move(value)), m_role(role) {}
};

// ----------------------------------------------------------------------------

QEXTMvvmSetValueCommand::QEXTMvvmSetValueCommand(QEXTMvvmSessionItem* item, QVariant value, int role)
    : QEXTMvvmItemCommand(item)
    , p_impl(make_unique<SetValueCommandImpl>(std::move(value), role))
{
    setResult(false);

    setDescription(generate_description(p_impl->m_value.toString().toStdString(), role));
    p_impl->m_item_path = pathFromItem(item);
}

QEXTMvvmSetValueCommand::~QEXTMvvmSetValueCommand() = default;

void QEXTMvvmSetValueCommand::undo_command()
{
    swap_values();
}

void QEXTMvvmSetValueCommand::execute_command()
{
    swap_values();
}

void QEXTMvvmSetValueCommand::swap_values()
{
    auto item = itemFromPath(p_impl->m_item_path);
    auto old = item->data<QVariant>(p_impl->m_role);
    auto result = item->setDataIntern(p_impl->m_value, p_impl->m_role);
    setResult(result);
    setObsolete(!result);
    p_impl->m_value = old;
}

namespace
{
std::string generate_description(const std::string& str, int role)
{
    std::ostringstream ostr;
    ostr << "Set value: " << str << ", role:" << role;
    return ostr.str();
}
} // namespace
