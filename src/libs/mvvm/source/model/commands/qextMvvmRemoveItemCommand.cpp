// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <commands/qextMvvmRemoveItemCommand.h>
#include <commands/qextMvvmCommandUtils.h>
#include <qextMvvmItemBackupStrategy.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>
#include <sstream>

using namespace ModelView;

namespace
{
std::string generate_description(const TagRow& tagrow);
} // namespace

struct QEXTMvvmRemoveItemCommand::RemoveItemCommandImpl {
    TagRow tagrow;
    std::unique_ptr<QEXTMvvmItemBackupStrategy> backup_strategy;
    Path item_path;
    RemoveItemCommandImpl(TagRow tagrow) : tagrow(std::move(tagrow)) {}
};

QEXTMvvmRemoveItemCommand::QEXTMvvmRemoveItemCommand(QEXTMvvmSessionItem* parent, TagRow tagrow)
    : QEXTMvvmItemCommand(parent)
    , p_impl(std::make_unique<RemoveItemCommandImpl>(std::move(tagrow)))
{
    setResult(false);

    setDescription(generate_description(p_impl->tagrow));
    p_impl->backup_strategy = CreateItemBackupStrategy(parent->model());
    p_impl->item_path = pathFromItem(parent);
}

QEXTMvvmRemoveItemCommand::~QEXTMvvmRemoveItemCommand() = default;

void QEXTMvvmRemoveItemCommand::undo_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    auto reco_item = p_impl->backup_strategy->restoreItem();
    parent->insertItem(reco_item.release(), p_impl->tagrow);
}

void QEXTMvvmRemoveItemCommand::execute_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    if (auto child = parent->takeItem(p_impl->tagrow); child) {
        p_impl->backup_strategy->saveItem(child);
        delete child;
        setResult(true);
    } else {
        setResult(false);
        setObsolete(true);
    }
}

namespace
{
std::string generate_description(const TagRow& tagrow)
{
    std::ostringstream ostr;
    ostr << "Remove item from tag '" << tagrow.tag << "', row " << tagrow.row;
    return ostr.str();
}
} // namespace
