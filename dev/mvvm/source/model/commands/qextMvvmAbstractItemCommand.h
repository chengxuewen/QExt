#ifndef _QEXT_MVVM_COMMANDS_ABSTRACTITEMCOMMAND_H
#define _QEXT_MVVM_COMMANDS_ABSTRACTITEMCOMMAND_H

#include <qextMemory.h>
#include <qextMvvmGlobal.h>
#include <qextMvvmCommandUtils.h>
#include <qextMvvmCommandResult.h>

#include <string>

namespace ModelView {

class QExtMvvmPath;
class QExtMvvmSessionItem;
class QExtMvvmSessionModel;

//! Abstract command interface to manipulate QExtMvvmSessionItem in model context.

class QEXT_MVVM_API QExtMvvmAbstractItemCommand
{
public:
    explicit QExtMvvmAbstractItemCommand(QExtMvvmSessionItem* receiver);
    virtual ~QExtMvvmAbstractItemCommand();

    QExtMvvmAbstractItemCommand(const QExtMvvmAbstractItemCommand& other) = delete;
    QExtMvvmAbstractItemCommand& operator=(const QExtMvvmAbstractItemCommand& other) = delete;

    void execute();

    void undo();

    bool isObsolete() const;

    std::string description() const;

    QExtMvvmCommandResult result() const;

protected:
    void setObsolete(bool flag);
    void setDescription(const std::string& text);
    QExtMvvmPath pathFromItem(QExtMvvmSessionItem* item) const;
    QExtMvvmSessionItem* itemFromPath(const QExtMvvmPath& path) const;
    QExtMvvmSessionModel* model() const;
    void setResult(const QExtMvvmCommandResult& command_result);

private:
    virtual void execute_command() = 0;
    virtual void undo_command() = 0;

    struct AbstractItemCommandImpl;
    QExtUniquePointer<AbstractItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXT_MVVM_COMMANDS_ABSTRACTITEMCOMMAND_H
