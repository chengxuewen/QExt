#include <qextMvvmMoveItemCommand.h>
#include <qextMvvmMoveItemCommand_p.h>

#include <qextMvvmPath.h>
#include <qextMvvmItem.h>
#include <sstream>
#include <stdexcept>

namespace
{
    void qextMvvmCheckInputData(const QEXTMvvmItem *item, const QEXTMvvmItem *parent)
    {
        if (!item || !item->model())
        {
            throw std::runtime_error("QEXTMvvmMoveItemCommand::QEXTMvvmMoveItemCommand() -> Invalid input item");
        }

        if (!parent || !parent->model())
        {
            throw std::runtime_error("QEXTMvvmMoveItemCommand::QEXTMvvmMoveItemCommand() -> Invalid parent item");
        }

        if (item->model() != parent->model())
        {
            throw std::runtime_error("QEXTMvvmMoveItemCommand::QEXTMvvmMoveItemCommand() -> Items belong to different models");
        }

        if (!item->parent())
        {
            throw std::runtime_error("QEXTMvvmMoveItemCommand::QEXTMvvmMoveItemCommand() -> Item doesn't have a parent");
        }
    }

    QString qextMvvmGenerateDescription(const QEXTMvvmTagRow &tagrow)
    {
        QString str;
        str.append("Move item to tag '");
        str.append(tagrow.tag);
        str.append("', row:");
        str.append(tagrow.row);
        return str;
    }
} // namespace


QEXTMvvmMoveItemCommandPrivate::QEXTMvvmMoveItemCommandPrivate(QEXTMvvmMoveItemCommand *q)
    : QEXTMvvmAbstractItemCommandPrivate(q)
{

}

QEXTMvvmMoveItemCommandPrivate::~QEXTMvvmMoveItemCommandPrivate()
{

}



QEXTMvvmMoveItemCommand::QEXTMvvmMoveItemCommand(QEXTMvvmItem *item, QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow)
    : QEXTMvvmAbstractItemCommand(new QEXTMvvmMoveItemCommandPrivate(this), parent)
{
    QEXT_DECL_D(QEXTMvvmMoveItemCommand);
    d->m_targetTagRow = tagrow;
    if (d->m_targetTagRow.row < 0)
    {
        throw std::runtime_error("QEXTMvvmAbstractItemCommand() -> Error. Uninitialized target row");
    }
    this->setResult(QEXTMvvmCommandResult(true));

    qextMvvmCheckInputData(item, parent);
    setDescription(qextMvvmGenerateDescription(d->m_targetTagRow));

    d->m_targetParentPath = this->pathFromItem(parent);
    d->m_originalParentPath = this->pathFromItem(item->parent());
    d->m_originalTagRow = item->tagRow();

    if (item->parent()->isSinglePropertyTag(d->m_originalTagRow.tag))
    {
        throw std::runtime_error("QEXTMvvmMoveItemCommand::QEXTMvvmMoveItemCommand() -> Single property tag.");
    }

    if (parent->isSinglePropertyTag(d->m_targetTagRow.tag))
    {
        throw std::runtime_error("QEXTMvvmMoveItemCommand::QEXTMvvmMoveItemCommand() -> Single property tag.");
    }

    if (item->parent() == parent)
    {
        if (d->m_targetTagRow.row >= parent->itemCount(d->m_targetTagRow.tag))
        {
            throw std::runtime_error("MoveCommand::MoveCommand() -> move index exceeds number of items in a tag");
        }
    }
}

QEXTMvvmMoveItemCommand::~QEXTMvvmMoveItemCommand()
{

}

void QEXTMvvmMoveItemCommand::undoCommand()
{
    QEXT_DECL_D(QEXTMvvmMoveItemCommand);
    // first find items
    QEXTMvvmItem *currentParent = this->itemFromPath(d->m_targetParentPath);
    QEXTMvvmItem *targetParent = this->itemFromPath(d->m_originalParentPath);

    // then make manipulations
    QEXTMvvmItem *taken = currentParent->takeItem(d->m_targetTagRow);
    targetParent->insertItem(taken, d->m_originalTagRow);

    // adjusting new addresses
    d->m_targetParentPath = this->pathFromItem(currentParent);
    d->m_originalParentPath = this->pathFromItem(targetParent);
}

void QEXTMvvmMoveItemCommand::executeCommand()
{
    QEXT_DECL_D(QEXTMvvmMoveItemCommand);
    // first find items
    QEXTMvvmItem *originalparent = this->itemFromPath(d->m_originalParentPath);
    QEXTMvvmItem *targetParent = this->itemFromPath(d->m_targetParentPath);

    // then make manipulations
    QEXTMvvmItem *taken = originalparent->takeItem(d->m_originalTagRow);

    if (!taken)
    {
        throw std::runtime_error("QEXTMvvmMoveItemCommand::executeCommand() -> Can't take an item.");
    }

    bool success = targetParent->insertItem(taken, d->m_targetTagRow);
    if (!success)
    {
        throw std::runtime_error("QEXTMvvmMoveItemCommand::executeCommand() -> Can't insert item.");
    }

    // adjusting new addresses
    d->m_targetParentPath = this->pathFromItem(targetParent);
    d->m_originalParentPath = this->pathFromItem(originalparent);
}
