// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmCommands.h>
#include <qextMvvmCommandUtils.h>
// #include "model/commands/copyitemcommand.h"
// #include "model/commands/commandutils.h"
// #include "model/commands/commandutils.h"
#include "model/interfaces/itembackupstrategy.h"
#include "model/interfaces/itemcopystrategy.h"
// #include "model/core/variant.h"
#include "model/model/sessionitem.h"
#include "model/interfaces/itembackupstrategy.h"
#include "model/model/sessionitem.h"
#include "model/model/itemutils.h"
#include "model/model/path.h"
#include "model/model/sessionitem.h"

#include <stdexcept>
#include <sstream>

using namespace ModelView;

namespace detail
{
std::string generate_description(const char *category, const std::string& modelType, const QExtMvvmTagRow& tagrow)
{
    std::ostringstream ostr;
    ostr << category << " '" << modelType << "' tag:'" << tagrow.tag << "', row:" << tagrow.row;
    return ostr.str();
}
std::string generate_description(const char *category, const QExtMvvmTagRow& tagrow)
{
    std::ostringstream ostr;
    ostr << category << " '" << tagrow.tag << "', row " << tagrow.row;
    return ostr.str();
}
std::string generate_description(const std::string& str, int role)
{
    std::ostringstream ostr;
    ostr << "Set value: " << str << ", role:" << role;
    return ostr.str();
}
void check_input_data(const QExtMvvmSessionItem* item, const QExtMvvmSessionItem* parent)
{
    if (!item || !item->model())
        throw std::runtime_error("QExtMvvmMoveItemCommand::QExtMvvmMoveItemCommand() -> Invalid input item");

    if (!parent || !parent->model())
        throw std::runtime_error("QExtMvvmMoveItemCommand::QExtMvvmMoveItemCommand() -> Invalid parent item");

    if (item->model() != parent->model())
        throw std::runtime_error(
            "QExtMvvmMoveItemCommand::QExtMvvmMoveItemCommand() -> Items belong to different models");

    if (!item->parent())
        throw std::runtime_error(
            "QExtMvvmMoveItemCommand::QExtMvvmMoveItemCommand() -> Item doesn't have a parent");
}
} // namespace


// namespace {
// std::string generate_description(const std::string& modelType, const QExtMvvmTagRow& tagrow);
// } // namespace

struct QExtMvvmCopyItemCommand::CopyItemCommandImpl {
    QExtMvvmTagRow tagrow;
    QExtUniquePointer<QExtMvvmItemBackupStrategy> backup_strategy;
    QExtMvvmPath item_path;
    CopyItemCommandImpl(QExtMvvmTagRow tagrow) : tagrow(std::move(tagrow)) {}
};

QExtMvvmCopyItemCommand::QExtMvvmCopyItemCommand(const QExtMvvmSessionItem* item, QExtMvvmSessionItem* parent, QExtMvvmTagRow tagrow)
    : QExtMvvmAbstractItemCommand(parent), p_impl(qextMakeUnique<CopyItemCommandImpl>(std::move(tagrow)))
{
    setResult(nullptr);

    setDescription(detail::generate_description("Copy item", item->modelType(), p_impl->tagrow));
    p_impl->backup_strategy = qextMvvmCreateItemBackupStrategy(parent->model());
    p_impl->item_path = pathFromItem(parent);

    auto copy_strategy = qextMvvmCreateItemCopyStrategy(parent->model()); // to modify id's
    auto item_copy = copy_strategy->createCopy(item);

    p_impl->backup_strategy->saveItem(item_copy.get());
}

QExtMvvmCopyItemCommand::~QExtMvvmCopyItemCommand() = default;

void QExtMvvmCopyItemCommand::undo_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    parent->takeItem(p_impl->tagrow);
    setResult(nullptr);
}

void QExtMvvmCopyItemCommand::execute_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    auto item = parent->insertItem(p_impl->backup_strategy->restoreItem(), p_impl->tagrow);
    // FIXME revise behaviour in the case of invalid operation. Catch or not here?
    setResult(item);
    setObsolete(!item); // command is osbolete if insertion failed
}

// namespace {
// std::string generate_description(const std::string& modelType, const QExtMvvmTagRow& tagrow)
// {
//     std::ostringstream ostr;
//     ostr << "Copy item'" << modelType << "' tag:'" << tagrow.tag << "', row:" << tagrow.row;
//     return ostr.str();
// }
// } // namespace



// namespace {
// std::string generate_description(const std::string& modelType, const QExtMvvmTagRow& tagrow);
// } // namespace

struct QExtMvvmInsertNewItemCommand::InsertNewItemCommandImpl {
    QExtMvvmItemFactoryFunc factory_func;
    QExtMvvmTagRow tagrow;
    QExtMvvmPath item_path;
    std::string initial_identifier;
    InsertNewItemCommandImpl(QExtMvvmItemFactoryFunc func, QExtMvvmTagRow tagrow)
        : factory_func(std::move(func)), tagrow(std::move(tagrow))
    {
    }
};

QExtMvvmInsertNewItemCommand::QExtMvvmInsertNewItemCommand(QExtMvvmItemFactoryFunc func, QExtMvvmSessionItem* parent,
                                                           const QExtMvvmTagRow& tagrow)
    : QExtMvvmAbstractItemCommand(parent), p_impl(qextMakeUnique<InsertNewItemCommandImpl>(func, tagrow))
{
    setResult(nullptr);
    p_impl->item_path = pathFromItem(parent);
}

QExtMvvmInsertNewItemCommand::~QExtMvvmInsertNewItemCommand() = default;

void QExtMvvmInsertNewItemCommand::undo_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    auto item = parent->takeItem(p_impl->tagrow);
    // saving identifier for later redo
    if (p_impl->initial_identifier.empty())
        p_impl->initial_identifier = item->identifier();
    setResult(nullptr);
}

void QExtMvvmInsertNewItemCommand::execute_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    auto child = p_impl->factory_func().release();
    // here we restore original identifier to get exactly same item on consequitive undo/redo
    if (!p_impl->initial_identifier.empty())
        child->setData(QVariant::fromValue(p_impl->initial_identifier), ItemDataRole::IDENTIFIER,
                       /*direct*/ true);

    setDescription(detail::generate_description("New item type", child->modelType(), p_impl->tagrow));
    if (parent->insertItem(child, p_impl->tagrow)) {
        setResult(child);
    }
    else {
        delete child;
        setObsolete(true);
    }
}

// namespace {
// std::string generate_description(const std::string& modelType, const QExtMvvmTagRow& tagrow)
// {
//     std::ostringstream ostr;
//     ostr << "New item type '" << modelType << "' tag:'" << tagrow.tag << "', row:" << tagrow.row;
//     return ostr.str();
// }
// } // namespace




// namespace {
// void check_input_data(const QExtMvvmSessionItem* item, const QExtMvvmSessionItem* parent);
// std::string generate_description(const QExtMvvmTagRow& tagrow);
// } // namespace

struct QExtMvvmMoveItemCommand::MoveItemCommandImpl {
    QExtMvvmTagRow target_tagrow;
    QExtMvvmPath target_parent_path;
    QExtMvvmPath original_parent_path;
    QExtMvvmTagRow original_tagrow;
    MoveItemCommandImpl(QExtMvvmTagRow tagrow) : target_tagrow(std::move(tagrow))
    {
        if (target_tagrow.row < 0)
            throw std::runtime_error("QExtMvvmMoveItemCommand() -> Error. Uninitialized target row");
    }
};

QExtMvvmMoveItemCommand::QExtMvvmMoveItemCommand(QExtMvvmSessionItem* item, QExtMvvmSessionItem* new_parent, QExtMvvmTagRow tagrow)
    : QExtMvvmAbstractItemCommand(new_parent), p_impl(qextMakeUnique<MoveItemCommandImpl>(tagrow))
{
    setResult(true);

    detail::check_input_data(item, new_parent);
    setDescription(detail::generate_description("Move item to tag", p_impl->target_tagrow));

    p_impl->target_parent_path = pathFromItem(new_parent);
    p_impl->original_parent_path = pathFromItem(item->parent());
    p_impl->original_tagrow = item->tagRow();

    if (Utils::IsSinglePropertyTag(*item->parent(), p_impl->original_tagrow.tag))
        throw std::runtime_error("QExtMvvmMoveItemCommand::QExtMvvmMoveItemCommand() -> Single property tag.");

    if (Utils::IsSinglePropertyTag(*new_parent, p_impl->target_tagrow.tag))
        throw std::runtime_error("QExtMvvmMoveItemCommand::QExtMvvmMoveItemCommand() -> Single property tag.");

    if (item->parent() == new_parent) {
        if (p_impl->target_tagrow.row >= new_parent->itemCount(p_impl->target_tagrow.tag))
            throw std::runtime_error(
                "MoveCommand::MoveCommand() -> move index exceeds number of items in a tag");
    }
}

QExtMvvmMoveItemCommand::~QExtMvvmMoveItemCommand() = default;

void QExtMvvmMoveItemCommand::undo_command()
{
    // first find items
    auto current_parent = itemFromPath(p_impl->target_parent_path);
    auto target_parent = itemFromPath(p_impl->original_parent_path);

    // then make manipulations
    auto taken = current_parent->takeItem(p_impl->target_tagrow);
    target_parent->insertItem(std::move(taken), p_impl->original_tagrow);

    // adjusting new addresses
    p_impl->target_parent_path = pathFromItem(current_parent);
    p_impl->original_parent_path = pathFromItem(target_parent);
}

void QExtMvvmMoveItemCommand::execute_command()
{
    // first find items
    auto original_parent = itemFromPath(p_impl->original_parent_path);
    auto target_parent = itemFromPath(p_impl->target_parent_path);

    // then make manipulations
    auto taken = original_parent->takeItem(p_impl->original_tagrow);

    if (!taken)
        throw std::runtime_error("QExtMvvmMoveItemCommand::execute() -> Can't take an item.");

    if (!target_parent->insertItem(std::move(taken), p_impl->target_tagrow))
        throw std::runtime_error("QExtMvvmMoveItemCommand::execute() -> Can't insert item.");

    // adjusting new addresses
    p_impl->target_parent_path = pathFromItem(target_parent);
    p_impl->original_parent_path = pathFromItem(original_parent);
}

// namespace {
// void check_input_data(const QExtMvvmSessionItem* item, const QExtMvvmSessionItem* parent)
// {
//     if (!item || !item->model())
//         throw std::runtime_error("QExtMvvmMoveItemCommand::QExtMvvmMoveItemCommand() -> Invalid input item");

//     if (!parent || !parent->model())
//         throw std::runtime_error("QExtMvvmMoveItemCommand::QExtMvvmMoveItemCommand() -> Invalid parent item");

//     if (item->model() != parent->model())
//         throw std::runtime_error(
//             "QExtMvvmMoveItemCommand::QExtMvvmMoveItemCommand() -> Items belong to different models");

//     if (!item->parent())
//         throw std::runtime_error(
//             "QExtMvvmMoveItemCommand::QExtMvvmMoveItemCommand() -> Item doesn't have a parent");
// }

// std::string generate_description(const QExtMvvmTagRow& tagrow)
// {
//     std::ostringstream ostr;
//     ostr << "Move item to tag '" << tagrow.tag << "', row:" << tagrow.row;
//     return ostr.str();
// }
// } // namespace





// namespace {
// std::string generate_description(const QExtMvvmTagRow& tagrow);
// } // namespace

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

    setDescription(detail::generate_description("Remove item from tag", p_impl->tagrow));
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

// namespace {
// std::string generate_description(const QExtMvvmTagRow& tagrow)
// {
//     std::ostringstream ostr;
//     ostr << "Remove item from tag '" << tagrow.tag << "', row " << tagrow.row;
//     return ostr.str();
// }
// } // namespace






// namespace {
// std::string generate_description(const std::string& str, int role);
// } // namespace

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

    setDescription(detail::generate_description(p_impl->m_value.toString().toStdString(), role));
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

// namespace {
// std::string generate_description(const std::string& str, int role)
// {
//     std::ostringstream ostr;
//     ostr << "Set value: " << str << ", role:" << role;
//     return ostr.str();
// }
// } // namespace


