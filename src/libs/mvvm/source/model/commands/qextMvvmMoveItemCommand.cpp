#include <qextMvvmMoveItemCommand.h>

#include <qextMvvmPath.h>
#include <qextMvvmSessionItem.h>
#include <sstream>
#include <stdexcept>

using namespace ModelView;

namespace
{
void check_input_data(const QEXTMvvmSessionItem* item, const QEXTMvvmSessionItem* parent);
std::string generate_description(const QEXTMvvmTagRow& tagrow);
} // namespace

struct QEXTMoveItemCommand::MoveItemCommandImpl {
    QEXTMvvmTagRow target_tagrow;
    QEXTMvvmPath target_parent_path;
    QEXTMvvmPath original_parent_path;
    QEXTMvvmTagRow original_tagrow;
    MoveItemCommandImpl(QEXTMvvmTagRow tagrow) : target_tagrow(std::move(tagrow))
    {
        if (target_tagrow.row < 0)
            throw std::runtime_error("QEXTMoveItemCommand() -> Error. Uninitialized target row");
    }
};

QEXTMoveItemCommand::QEXTMoveItemCommand(QEXTMvvmSessionItem* item, QEXTMvvmSessionItem* new_parent, QEXTMvvmTagRow tagrow)
    : QEXTAbstractItemCommand(new_parent), p_impl(std::make_unique<MoveItemCommandImpl>(tagrow))
{
    setResult(true);

    check_input_data(item, new_parent);
    setDescription(generate_description(p_impl->target_tagrow));

    p_impl->target_parent_path = pathFromItem(new_parent);
    p_impl->original_parent_path = pathFromItem(item->parent());
    p_impl->original_tagrow = item->tagRow();

    if (item->parent()->isSinglePropertyTag(p_impl->original_tagrow.tag))
        throw std::runtime_error("QEXTMoveItemCommand::QEXTMoveItemCommand() -> Single property tag.");

    if (new_parent->isSinglePropertyTag(p_impl->target_tagrow.tag))
        throw std::runtime_error("QEXTMoveItemCommand::QEXTMoveItemCommand() -> Single property tag.");

    if (item->parent() == new_parent) {
        if (p_impl->target_tagrow.row >= new_parent->itemCount(p_impl->target_tagrow.tag))
            throw std::runtime_error(
                "MoveCommand::MoveCommand() -> move index exceeds number of items in a tag");
    }
}

QEXTMoveItemCommand::~QEXTMoveItemCommand() = default;

void QEXTMoveItemCommand::undo_command()
{
    // first find items
    auto current_parent = itemFromPath(p_impl->target_parent_path);
    auto target_parent = itemFromPath(p_impl->original_parent_path);

    // then make manipulations
    auto taken = current_parent->takeItem(p_impl->target_tagrow);
    target_parent->insertItem(taken, p_impl->original_tagrow);

    // adjusting new addresses
    p_impl->target_parent_path = pathFromItem(current_parent);
    p_impl->original_parent_path = pathFromItem(target_parent);
}

void QEXTMoveItemCommand::execute_command()
{
    // first find items
    auto original_parent = itemFromPath(p_impl->original_parent_path);
    auto target_parent = itemFromPath(p_impl->target_parent_path);

    // then make manipulations
    auto taken = original_parent->takeItem(p_impl->original_tagrow);

    if (!taken)
        throw std::runtime_error("QEXTMoveItemCommand::execute() -> Can't take an item.");

    bool succeeded = target_parent->insertItem(taken, p_impl->target_tagrow);
    if (!succeeded)
        throw std::runtime_error("QEXTMoveItemCommand::execute() -> Can't insert item.");

    // adjusting new addresses
    p_impl->target_parent_path = pathFromItem(target_parent);
    p_impl->original_parent_path = pathFromItem(original_parent);
}

namespace
{
void check_input_data(const QEXTMvvmSessionItem* item, const QEXTMvvmSessionItem* parent)
{
    if (!item || !item->model())
        throw std::runtime_error("QEXTMoveItemCommand::QEXTMoveItemCommand() -> Invalid input item");

    if (!parent || !parent->model())
        throw std::runtime_error("QEXTMoveItemCommand::QEXTMoveItemCommand() -> Invalid parent item");

    if (item->model() != parent->model())
        throw std::runtime_error(
            "QEXTMoveItemCommand::QEXTMoveItemCommand() -> Items belong to different models");

    if (!item->parent())
        throw std::runtime_error(
            "QEXTMoveItemCommand::QEXTMoveItemCommand() -> Item doesn't have a parent");
}

std::string generate_description(const QEXTMvvmTagRow& tagrow)
{
    std::ostringstream ostr;
    ostr << "Move item to tag '" << tagrow.tag << "', row:" << tagrow.row;
    return ostr.str();
}
} // namespace
