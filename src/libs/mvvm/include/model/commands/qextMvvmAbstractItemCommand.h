#ifndef _QEXTMVVMABSTRACTITEMCOMMAND_H
#define _QEXTMVVMABSTRACTITEMCOMMAND_H

#include <qextMvvmCommandResult.h>
#include <qextMvvmGlobal.h>

#include <QScopedPointer>

#include <memory>
#include <string>


class QEXTMvvmItem;
class QEXTMvvmModel;
class QEXTMvvmPath;

//! Abstract command interface to manipulate QEXTMvvmItem in model context.
class QEXTMvvmAbstractItemCommandPrivate;
class QEXT_MVVM_API QEXTMvvmAbstractItemCommand
{
public:
    explicit QEXTMvvmAbstractItemCommand(QEXTMvvmItem *receiver);
    virtual ~QEXTMvvmAbstractItemCommand();

    void execute();
    void undo();
    bool isObsolete() const;
    QString description() const;
    QEXTMvvmCommandResult result() const;

protected:
    QEXTMvvmAbstractItemCommand(QEXTMvvmAbstractItemCommandPrivate *d, QEXTMvvmItem *receiver);

    void setObsolete(bool flag);
    void setDescription(const QString &text);
    void setResult(const QEXTMvvmCommandResult &result);

    QEXTMvvmPath pathFromItem(QEXTMvvmItem *item) const;
    QEXTMvvmItem *itemFromPath(const QEXTMvvmPath &path) const;
    QEXTMvvmModel *model() const;

    QScopedPointer<QEXTMvvmAbstractItemCommandPrivate> d_ptr;

    virtual void executeCommand() = 0;
    virtual void undoCommand() = 0;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmAbstractItemCommand)
    QEXT_DECL_PRIVATE(QEXTMvvmAbstractItemCommand)
};


#endif // _QEXTMVVMABSTRACTITEMCOMMAND_H
