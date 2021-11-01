#include <qextMvvmInsertNewItemCommand.h>

#include <qextMvvmPath.h>
#include <qextMvvmSessionItem.h>
#include <sstream>

using namespace ModelView;

namespace
{
std::string generate_description(const std::string& modelType, const QEXTMvvmTagRow& tagrow);
} // namespace

struct QEXTInsertNewItemCommand::InsertNewItemCommandImpl {
    item_factory_func_t factory_func;
    QEXTMvvmTagRow tagrow;
    QEXTMvvmPath item_path;
    std::string initial_identifier;
    InsertNewItemCommandImpl(item_factory_func_t func, QEXTMvvmTagRow tagrow)
        : factory_func(std::move(func)), tagrow(std::move(tagrow))
    {
    }
};

QEXTInsertNewItemCommand::QEXTInsertNewItemCommand(item_factory_func_t func, QEXTMvvmSessionItem* parent,
                                           const QEXTMvvmTagRow& tagrow)
    : QEXTAbstractItemCommand(parent), p_impl(std::make_unique<InsertNewItemCommandImpl>(func, tagrow))
{
    setResult(nullptr);
    p_impl->item_path = pathFromItem(parent);
}

QEXTInsertNewItemCommand::~QEXTInsertNewItemCommand() = default;

void QEXTInsertNewItemCommand::undo_command()
{
    auto parent = itemFromPath(p_impl->item_path);
    auto item = parent->takeItem(p_impl->tagrow);
    // saving identifier for later redo
    if (p_impl->initial_identifier.empty())
        p_impl->initial_identifier = item->identifier();
    delete item;
    setResult(nullptr);
}

void QEXTInsertNewItemCommand::execute_command()
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
std::string generate_description(const std::string& modelType, const QEXTMvvmTagRow& tagrow)
{
    std::ostringstream ostr;
    ostr << "New item type '" << modelType << "' tag:'" << tagrow.tag << "', row:" << tagrow.row;
    return ostr.str();
}
} // namespace
