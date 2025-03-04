// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/commands/insertnewitemcommand.h"
#include "model/model/path.h"
#include "model/model/sessionitem.h"
#include <sstream>

using namespace ModelView;

namespace {
std::string generate_description(const std::string& modelType, const QExtMvvmTagRow& tagrow);
} // namespace

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

    setDescription(generate_description(child->modelType(), p_impl->tagrow));
    if (parent->insertItem(child, p_impl->tagrow)) {
        setResult(child);
    }
    else {
        delete child;
        setObsolete(true);
    }
}

namespace {
std::string generate_description(const std::string& modelType, const QExtMvvmTagRow& tagrow)
{
    std::ostringstream ostr;
    ostr << "New item type '" << modelType << "' tag:'" << tagrow.tag << "', row:" << tagrow.row;
    return ostr.str();
}
} // namespace
