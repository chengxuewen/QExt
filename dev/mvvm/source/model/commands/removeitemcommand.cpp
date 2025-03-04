// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/commands/removeitemcommand.h"
#include "model/commands/commandutils.h"
#include "model/interfaces/itembackupstrategy.h"
#include "model/model/path.h"
#include "model/model/sessionitem.h"
#include <sstream>

using namespace ModelView;

namespace {
std::string generate_description(const QExtMvvmTagRow& tagrow);
} // namespace

struct RemoveItemCommand::RemoveItemCommandImpl {
    QExtMvvmTagRow tagrow;
    QExtUniquePointer<QExtMvvmItemBackupStrategy> backup_strategy;
    QExtMvvmPath item_path;
    RemoveItemCommandImpl(QExtMvvmTagRow tagrow) : tagrow(std::move(tagrow)) {}
};

RemoveItemCommand::RemoveItemCommand(QExtMvvmSessionItem* parent, QExtMvvmTagRow tagrow)
    : QExtMvvmAbstractItemCommand(parent)
    , p_impl(qextMakeUnique<RemoveItemCommandImpl>(std::move(tagrow)))
{
    setResult(false);

    setDescription(generate_description(p_impl->tagrow));
    p_impl->backup_strategy = qextMvvmCreateItemBackupStrategy(parent->model());
    p_impl->item_path = pathFromItem(parent);
}

RemoveItemCommand::~RemoveItemCommand() = default;

void RemoveItemCommand::undo_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    parent->insertItem(p_impl->backup_strategy->restoreItem(), p_impl->tagrow);
}

void RemoveItemCommand::execute_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    if (auto child = parent->takeItem(p_impl->tagrow); child) {
        p_impl->backup_strategy->saveItem(child.get());
        setResult(true);
    } else {
        setResult(false);
        setObsolete(true);
    }
}

namespace {
std::string generate_description(const QExtMvvmTagRow& tagrow)
{
    std::ostringstream ostr;
    ostr << "Remove item from tag '" << tagrow.tag << "', row " << tagrow.row;
    return ostr.str();
}
} // namespace
