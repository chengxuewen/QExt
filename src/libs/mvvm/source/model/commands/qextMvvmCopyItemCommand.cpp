// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <commands/qextMvvmCommandUtils.h>
#include <commands/qextMvvmCopyItemCommand.h>
#include <qextMvvmItemBackupStrategy.h>
#include <qextMvvmItemCopyStrategy.h>
#include <qextMvvmPath.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>
#include <sstream>

using namespace ModelView;

namespace
{
std::string generate_description(const std::string& modelType, const QEXTMvvmTagRow& tagrow);
} // namespace

struct QEXTMvvmCopyItemCommand::CopyItemCommandImpl {
    QEXTMvvmTagRow tagrow;
    std::unique_ptr<QEXTMvvmItemBackupStrategy> backup_strategy;
    QEXTMvvmPath item_path;
    CopyItemCommandImpl(QEXTMvvmTagRow tagrow) : tagrow(std::move(tagrow)) {}
};

QEXTMvvmCopyItemCommand::QEXTMvvmCopyItemCommand(const QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* parent, QEXTMvvmTagRow tagrow)
    : QEXTMvvmItemCommand(parent), p_impl(make_unique<CopyItemCommandImpl>(std::move(tagrow)))
{
    setResult(nullptr);

    setDescription(generate_description(item->modelType(), p_impl->tagrow));
    p_impl->backup_strategy = CreateItemBackupStrategy(parent->model());
    p_impl->item_path = pathFromItem(parent);

    auto copy_strategy = CreateItemCopyStrategy(parent->model()); // to modify id's
    auto item_copy = copy_strategy->createCopy(item);

    p_impl->backup_strategy->saveItem(item_copy.get());
}

QEXTMvvmCopyItemCommand::~QEXTMvvmCopyItemCommand() = default;

void QEXTMvvmCopyItemCommand::undo_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    delete parent->takeItem(p_impl->tagrow);
    setResult(nullptr);
}

void QEXTMvvmCopyItemCommand::execute_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    auto item = p_impl->backup_strategy->restoreItem();
    if (parent->insertItem(item.get(), p_impl->tagrow)) {
        auto result = item.release();
        setResult(result);
    } else {
        setResult(nullptr);
        setObsolete(true);
    }
}

namespace
{
std::string generate_description(const std::string& modelType, const QEXTMvvmTagRow& tagrow)
{
    std::ostringstream ostr;
    ostr << "Copy item'" << modelType << "' tag:'" << tagrow.tag << "', row:" << tagrow.row;
    return ostr.str();
}
} // namespace
