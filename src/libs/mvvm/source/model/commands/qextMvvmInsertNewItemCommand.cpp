#include <qextMvvmInsertNewItemCommand.h>
#include <qextMvvmInsertNewItemCommand_p.h>
#include <qextMvvmItem.h>
#include <qextMvvmPath.h>

#include <sstream>

namespace
{
    QString qextMvvmGenerateDescription(const QString &modelType, const QEXTMvvmTagRow &m_tagrow)
    {
        return QString("New item type '%1' tag:'%2', row:%3").arg(modelType).arg(m_tagrow.tag).arg(m_tagrow.row);
    }
} // namespace

QEXTMvvmInsertNewItemCommandPrivate::QEXTMvvmInsertNewItemCommandPrivate(QEXTMvvmInsertNewItemCommand *q)
    : QEXTMvvmAbstractItemCommandPrivate(q)
{

}

QEXTMvvmInsertNewItemCommandPrivate::~QEXTMvvmInsertNewItemCommandPrivate()
{

}



QEXTMvvmInsertNewItemCommand::QEXTMvvmInsertNewItemCommand(QEXTMvvmItemFactoryFunction func,
        QEXTMvvmItem *parent,
        const QEXTMvvmTagRow &m_tagrow)
    : QEXTMvvmAbstractItemCommand(new QEXTMvvmInsertNewItemCommandPrivate(this), parent)
{
    QEXT_DECL_D(QEXTMvvmInsertNewItemCommand);
    d->m_factoryFunc = func;
    d->m_tagrow = m_tagrow;
    this->setResult(QEXTMvvmCommandResult());
    d->m_itemPath = this->pathFromItem(parent);
}

QEXTMvvmInsertNewItemCommand::~QEXTMvvmInsertNewItemCommand()
{

}

void QEXTMvvmInsertNewItemCommand::undoCommand()
{
    QEXT_DECL_D(QEXTMvvmInsertNewItemCommand);
    QEXTMvvmItem *parent = this->itemFromPath(d->m_itemPath);
    QEXTMvvmItem *item = parent->takeItem(d->m_tagrow);
    // saving identifier for later redo
    if (d->m_initialIdentifier.isEmpty())
    {
        d->m_initialIdentifier = item->identifier();
    }
    delete item;
    this->setResult(QEXTMvvmCommandResult());
}

void QEXTMvvmInsertNewItemCommand::executeCommand()
{
    QEXT_DECL_D(QEXTMvvmInsertNewItemCommand);
    QEXTMvvmItem *parent = this->itemFromPath(d->m_itemPath);
    QEXTMvvmItem *child = d->m_factoryFunc();
    // here we restore original identifier to get exactly same item on consequitive undo/redo
    if (!d->m_initialIdentifier.isEmpty())
    {
        child->setDataIntern(d->m_initialIdentifier, QEXTMvvmItem::Role_Identifier);
    }

    this->setDescription(qextMvvmGenerateDescription(child->modelType(), d->m_tagrow));
    if (parent->insertItem(child, d->m_tagrow))
    {
        this->setResult(child);
    }
    else
    {
        delete child;
        this->setObsolete(true);
    }
}

