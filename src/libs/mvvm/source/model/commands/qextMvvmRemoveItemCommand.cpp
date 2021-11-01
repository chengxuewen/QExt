#include <qextMvvmRemoveItemCommand.h>
#include <qextMvvmCommandUtils.h>

#include <qextMvvmItemBackupStrategy.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>
#include <sstream>

using namespace ModelView;

namespace
{
std::string generate_description(const QEXTMvvmTagRow& tagrow);
} // namespace

struct QEXTRemoveItemCommand::RemoveItemCommandImpl {
    QEXTMvvmTagRow tagrow;
    std::unique_ptr<QEXTMvvmItemBackupStrategy> backup_strategy;
    QEXTMvvmPath item_path;
    RemoveItemCommandImpl(QEXTMvvmTagRow tagrow) : tagrow(std::move(tagrow)) {}
};

QEXTRemoveItemCommand::QEXTRemoveItemCommand(QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow)
    : QEXTAbstractItemCommand(parent)
    , p_impl(std::make_unique<RemoveItemCommandImpl>(std::move(tagrow)))
{
    setResult(false);

    setDescription(generate_description(p_impl->tagrow));
    p_impl->backup_strategy = CreateItemBackupStrategy(parent->model());
    p_impl->item_path = pathFromItem(parent);
}

QEXTRemoveItemCommand::~QEXTRemoveItemCommand() = default;

void QEXTRemoveItemCommand::undo_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    auto reco_item = p_impl->backup_strategy->restoreItem();
    parent->insertItem(reco_item.release(), p_impl->tagrow);
}

void QEXTRemoveItemCommand::execute_command()
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
std::string generate_description(const QEXTMvvmTagRow& tagrow)
{
    std::ostringstream ostr;
    ostr << "Remove item from tag '" << tagrow.tag << "', row " << tagrow.row;
    return ostr.str();
}
} // namespace
