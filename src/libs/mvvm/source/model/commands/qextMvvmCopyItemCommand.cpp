#include <qextMvvmCopyItemCommand.h>
#include <qextMvvmCopyItemCommand_p.h>
#include <qextMvvmCommandUtils.h>

#include <qextMvvmItemBackupStrategy.h>
#include <qextMvvmItemCopyStrategy.h>
#include <qextMvvmPath.h>
#include <qextMvvmItem.h>
#include <qextMvvmModel.h>
#include <sstream>


namespace
{
QString qextMvvmGenerateDescription(const QString &modelType, const QEXTMvvmTagRow &tagrow)
{
    QString str = QString("Copy item'%1' tag:'%2', row:%3").arg(modelType).arg(tagrow.tag).arg(tagrow.row);
    return str;
}
} // namespace

QEXTMvvmCopyItemCommandPrivate::QEXTMvvmCopyItemCommandPrivate(QEXTMvvmCopyItemCommand *q)
    : QEXTMvvmAbstractItemCommandPrivate(q)
{

}

QEXTMvvmCopyItemCommandPrivate::~QEXTMvvmCopyItemCommandPrivate()
{

}



QEXTMvvmCopyItemCommand::QEXTMvvmCopyItemCommand(QEXTMvvmItem *item, QEXTMvvmItem *parent, QEXTMvvmTagRow tagrow)
    : QEXTMvvmAbstractItemCommand(new QEXTMvvmCopyItemCommandPrivate(this), parent)
{
    QEXT_DECL_D(QEXTMvvmCopyItemCommand);
    this->setResult(QEXTMvvmCommandResult());

    d->m_tagrow = tagrow;
    this->setDescription(qextMvvmGenerateDescription(item->modelType(), d->m_tagrow));
//    d->m_itemBackupStrategy.reset(QEXTMvvmCommandUtils::createItemBackupStrategy(parent->model()));
    d->m_itempath = this->pathFromItem(parent);

    QEXTMvvmItemCopyStrategy *copyStrategy = QEXTMvvmCommandUtils::createItemCopyStrategy(parent->model()); // to modify id's
    QEXTMvvmItem *itemCopy = copyStrategy->createCopy(item);
    d->m_itemBackupStrategy->saveItem(itemCopy); //NOTICE LIFECYCLE
}

QEXTMvvmCopyItemCommand::~QEXTMvvmCopyItemCommand()
{

}

void QEXTMvvmCopyItemCommand::undoCommand()
{
    QEXT_DECL_D(QEXTMvvmCopyItemCommand);
    QEXTMvvmItem *parent = this->itemFromPath(d->m_itempath);
    delete parent->takeItem(d->m_tagrow);
    this->setResult(QEXTMvvmCommandResult());
}

void QEXTMvvmCopyItemCommand::executeCommand()
{
    QEXT_DECL_D(QEXTMvvmCopyItemCommand);
    QEXTMvvmItem *parent = this->itemFromPath(d->m_itempath);
    QEXTMvvmItem *item = d->m_itemBackupStrategy->restoreItem();
    if (parent->insertItem(item, d->m_tagrow))
    {
        //        auto result = item.release();//NOTICE LIFECYCLE
        this->setResult(QEXTMvvmCommandResult(item));
    }
    else
    {
        this->setResult(QEXTMvvmCommandResult());
        this->setObsolete(true);
    }
}
