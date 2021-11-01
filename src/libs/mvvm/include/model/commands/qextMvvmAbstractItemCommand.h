#ifndef _QEXTMVVMABSTRACTITEMCOMMAND_H
#define _QEXTMVVMABSTRACTITEMCOMMAND_H

#include <qextMvvmCommandResult.h>
#include <qextMvvmGlobal.h>

#include <memory>
#include <string>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmSessionModel;
class QEXTMvvmPath;

//! Abstract command interface to manipulate QEXTMvvmSessionItem in model context.

class QEXT_MVVM_API QEXTAbstractItemCommand
{
public:
    explicit QEXTAbstractItemCommand(QEXTMvvmSessionItem* receiver);
    virtual ~QEXTAbstractItemCommand();

    QEXTAbstractItemCommand(const QEXTAbstractItemCommand& other) = delete;
    QEXTAbstractItemCommand& operator=(const QEXTAbstractItemCommand& other) = delete;

    void execute();

    void undo();

    bool isObsolete() const;

    std::string description() const;

    QEXTCommandResult result() const;

protected:
    void setObsolete(bool flag);
    void setDescription(const std::string& text);
    QEXTMvvmPath pathFromItem(QEXTMvvmSessionItem* item) const;
    QEXTMvvmSessionItem* itemFromPath(const QEXTMvvmPath& path) const;
    QEXTMvvmSessionModel* model() const;
    void setResult(const QEXTCommandResult& command_result);

private:
    virtual void execute_command() = 0;
    virtual void undo_command() = 0;

    struct AbstractItemCommandImpl;
    std::unique_ptr<AbstractItemCommandImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMABSTRACTITEMCOMMAND_H
