#include <qextMvvmRemoveItemCommand.h>
#include <qextMvvmRemoveItemCommand_p.h>
#include <qextMvvmCommandUtils.h>

#include <qextMvvmItemBackupStrategy.h>
#include <qextMvvmItem.h>
#include <qextMvvmModel.h>
#include <sstream>

namespace
{
    QString qextMvvmGenerateDescription(const QEXTMvvmTagRow &tagrow)
    {
        QString str = QString("Remove item from tag '%1', row %2").arg(tagrow.tag).arg(tagrow.row);
        return str;
    }
} // namespace

QEXTMvvmRemoveItemCommandPrivate::QEXTMvvmRemoveItemCommandPrivate(QEXTMvvmRemoveItemCommand *q)
    : QEXTMvvmAbstractItemCommandPrivate(q)
{

}

QEXTMvvmRemoveItemCommandPrivate::~QEXTMvvmRemoveItemCommandPrivate()
{

}



QEXTMvvmRemoveItemCommand::QEXTMvvmRemoveItemCommand(QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow)
    : QEXTMvvmAbstractItemCommand(new QEXTMvvmRemoveItemCommandPrivate(this), parent)
{
    QEXT_DECL_D(QEXTMvvmRemoveItemCommand);
    d->m_tagrow = tagrow;
    this->setResult(QEXTMvvmCommandResult(false));
    this->setDescription(qextMvvmGenerateDescription(d->m_tagrow));
    d->m_backupStrategy.reset(QEXTMvvmCommandUtils::createItemBackupStrategy(parent->model()));
    d->m_itemPath = this->pathFromItem(parent);
}

QEXTMvvmRemoveItemCommand::~QEXTMvvmRemoveItemCommand()
{

}

void QEXTMvvmRemoveItemCommand::undoCommand()
{
    QEXT_DECL_D(QEXTMvvmRemoveItemCommand);
    QEXTMvvmItem *parent = this->itemFromPath(d->m_itemPath);
    QEXTMvvmItem *recoItem = d->m_backupStrategy->restoreItem();
    parent->insertItem(recoItem, d->m_tagrow);
}

void QEXTMvvmRemoveItemCommand::executeCommand()
{
    QEXT_DECL_D(QEXTMvvmRemoveItemCommand);
    QEXTMvvmItem *parent = this->itemFromPath(d->m_itemPath);
    QEXTMvvmItem *child = parent->takeItem(d->m_tagrow);
    if (child)
    {
        d->m_backupStrategy->saveItem(child);
        delete child;
        this->setResult(QEXTMvvmCommandResult(true));
    }
    else
    {
        this->setResult(QEXTMvvmCommandResult(false));
        this->setObsolete(true);
    }
}


