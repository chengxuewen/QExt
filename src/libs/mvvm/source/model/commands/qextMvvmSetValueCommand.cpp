#include <qextMvvmSetValueCommand.h>

#include <qextMvvmVariant.h>
#include <qextMvvmPath.h>
#include <qextMvvmSessionItem.h>
#include <model/qextMvvmModelUtils.h>
#include <sstream>

namespace
{
std::string generate_description(const std::string& str, int role);
} // namespace

using namespace ModelView;

struct QEXTSetValueCommand::SetValueCommandImpl {
    QEXTMvvmVariant m_value; //! Value to set as a result of command execution.
    int m_role;
    QEXTMvvmPath m_item_path;
    SetValueCommandImpl(QEXTMvvmVariant value, int role) : m_value(std::move(value)), m_role(role) {}
};

// ----------------------------------------------------------------------------

QEXTSetValueCommand::QEXTSetValueCommand(QEXTMvvmSessionItem* item, QEXTMvvmVariant value, int role)
    : QEXTAbstractItemCommand(item)
    , p_impl(std::make_unique<SetValueCommandImpl>(std::move(value), role))
{
    setResult(false);

    setDescription(generate_description(p_impl->m_value.toString().toStdString(), role));
    p_impl->m_item_path = pathFromItem(item);
}

QEXTSetValueCommand::~QEXTSetValueCommand() = default;

void QEXTSetValueCommand::undo_command()
{
    swap_values();
}

void QEXTSetValueCommand::execute_command()
{
    swap_values();
}

void QEXTSetValueCommand::swap_values()
{
    auto item = itemFromPath(p_impl->m_item_path);
    auto old = item->data<QEXTMvvmVariant>(p_impl->m_role);
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
