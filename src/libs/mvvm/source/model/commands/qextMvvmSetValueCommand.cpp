#include <qextMvvmSetValueCommand.h>
#include <qextMvvmSetValueCommand_p.h>

#include <qextMvvmTypes.h>
#include <qextMvvmPath.h>
#include <qextMvvmItem.h>
#include <qextMvvmUtils.h>
#include <sstream>

namespace
{
    QString qextMvvmGenerateDescription(const QString &str, int role)
    {
        QString string = QString("Set value: %1, role:%2").arg(str).arg(role);
        return string;
    }
} // namespace

QEXTMvvmSetValueCommandPrivate::QEXTMvvmSetValueCommandPrivate(QEXTMvvmSetValueCommand *q)
    : QEXTMvvmAbstractItemCommandPrivate(q)
{

}

QEXTMvvmSetValueCommandPrivate::~QEXTMvvmSetValueCommandPrivate()
{

}



QEXTMvvmSetValueCommand::QEXTMvvmSetValueCommand(QEXTMvvmItem *parent, QVariant value, int role)
    : QEXTMvvmAbstractItemCommand(new QEXTMvvmSetValueCommandPrivate(this), parent)
{
    QEXT_DECL_D(QEXTMvvmSetValueCommand);
    d->m_value = value;
    d->m_role = role;
    this->setResult(QEXTMvvmCommandResult(false));
    this->setDescription(qextMvvmGenerateDescription(d->m_value.toString(), role));
    d->m_itemPath = this->pathFromItem(parent);
}

QEXTMvvmSetValueCommand::~QEXTMvvmSetValueCommand()
{

}

void QEXTMvvmSetValueCommand::undoCommand()
{
    this->swapValues();
}

void QEXTMvvmSetValueCommand::executeCommand()
{
    this->swapValues();
}

void QEXTMvvmSetValueCommand::swapValues()
{
    QEXT_DECL_D(QEXTMvvmSetValueCommand);
    QEXTMvvmItem *item = this->itemFromPath(d->m_itemPath);
    QVariant old = item->data<QVariant>(d->m_role);
    bool result = item->setDataIntern(d->m_value, d->m_role);
    this->setResult(QEXTMvvmCommandResult(result));
    this->setObsolete(!result);
    d->m_value = old;
}
