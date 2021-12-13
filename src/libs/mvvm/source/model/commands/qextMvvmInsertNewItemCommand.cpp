// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <commands/qextMvvmInsertNewItemCommand.h>
#include <qextMvvmPath.h>
#include <qextMvvmSessionItem.h>
#include <sstream>

using namespace ModelView;

namespace
{
std::string generate_description(const std::string& modelType, const TagRow& tagrow);
} // namespace

struct QEXTMvvmInsertNewItemCommand::InsertNewItemCommandImpl {
    item_factory_func_t factory_func;
    TagRow tagrow;
    Path item_path;
    std::string initial_identifier;
    InsertNewItemCommandImpl(item_factory_func_t func, TagRow tagrow)
        : factory_func(std::move(func)), tagrow(std::move(tagrow))
    {
    }
};

QEXTMvvmInsertNewItemCommand::QEXTMvvmInsertNewItemCommand(item_factory_func_t func, QEXTMvvmSessionItem* parent,
                                           const TagRow& tagrow)
    : QEXTMvvmItemCommand(parent), p_impl(std::make_unique<InsertNewItemCommandImpl>(func, tagrow))
{
    setResult(nullptr);
    p_impl->item_path = pathFromItem(parent);
}

QEXTMvvmInsertNewItemCommand::~QEXTMvvmInsertNewItemCommand() = default;

void QEXTMvvmInsertNewItemCommand::undo_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    auto item = parent->takeItem(p_impl->tagrow);
    // saving identifier for later redo
    if (p_impl->initial_identifier.empty())
        p_impl->initial_identifier = item->identifier();
    delete item;
    setResult(nullptr);
}

void QEXTMvvmInsertNewItemCommand::execute_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    auto child = p_impl->factory_func().release();
    // here we restore original identifier to get exactly same item on consequitive undo/redo
    if (!p_impl->initial_identifier.empty())
        child->setDataIntern(QVariant::fromValue(p_impl->initial_identifier),
                             ItemDataRole::IDENTIFIER);

    setDescription(generate_description(child->modelType(), p_impl->tagrow));
    if (parent->insertItem(child, p_impl->tagrow)) {
        setResult(child);
    } else {
        delete child;
        setObsolete(true);
    }
}

namespace
{
std::string generate_description(const std::string& modelType, const TagRow& tagrow)
{
    std::ostringstream ostr;
    ostr << "New item type '" << modelType << "' tag:'" << tagrow.tag << "', row:" << tagrow.row;
    return ostr.str();
}
} // namespace
