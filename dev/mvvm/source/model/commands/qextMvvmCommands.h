// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_COMMANDS_COPYITEMCOMMAND_H
#define MVVM_COMMANDS_COPYITEMCOMMAND_H

#include <qextMvvmAbstractItemCommand.h>
#include <qextMvvmFunctionTypes.h>

namespace ModelView {

class QExtMvvmSessionItem;
class QExtMvvmTagRow;

//! Command to copy an item.

class QEXT_MVVM_API QExtMvvmCopyItemCommand : public QExtMvvmAbstractItemCommand {
public:
    QExtMvvmCopyItemCommand(const QExtMvvmSessionItem* item, QExtMvvmSessionItem* parent, QExtMvvmTagRow tagrow);
    ~QExtMvvmCopyItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct CopyItemCommandImpl;
    QExtUniquePointer<CopyItemCommandImpl> p_impl;
};

class QExtMvvmSessionItem;
class QExtMvvmTagRow;

//! Command for unddo/redo to insert new item.

class QEXT_MVVM_API QExtMvvmInsertNewItemCommand : public QExtMvvmAbstractItemCommand {
public:
    QExtMvvmInsertNewItemCommand(QExtMvvmItemFactoryFunc func, QExtMvvmSessionItem* parent, const QExtMvvmTagRow& tagrow);
    ~QExtMvvmInsertNewItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct InsertNewItemCommandImpl;
    QExtUniquePointer<InsertNewItemCommandImpl> p_impl;
};



class QExtMvvmSessionItem;
class QExtMvvmTagRow;

//! Command for unddo/redo framework to move item from one parent to another.

class QEXT_MVVM_API QExtMvvmMoveItemCommand : public QExtMvvmAbstractItemCommand {
public:
    QExtMvvmMoveItemCommand(QExtMvvmSessionItem* item, QExtMvvmSessionItem* new_parent, QExtMvvmTagRow tagrow);
    ~QExtMvvmMoveItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct MoveItemCommandImpl;
    QExtUniquePointer<MoveItemCommandImpl> p_impl;
};



class QExtMvvmSessionItem;
class QExtMvvmTagRow;

//! Command for unddo/redo framework to remove item from a model using child's tag and row.

class QEXT_MVVM_API RemoveItemCommand : public QExtMvvmAbstractItemCommand {
public:
    RemoveItemCommand(QExtMvvmSessionItem* parent, QExtMvvmTagRow tagrow);
    ~RemoveItemCommand() override;

private:
    void undo_command() override;
    void execute_command() override;

    struct RemoveItemCommandImpl;
    QExtUniquePointer<RemoveItemCommandImpl> p_impl;
};




class QExtMvvmSessionItem;

//! Command for unddo/redo framework to set the data of QExtMvvmSessionItem.

class QEXT_MVVM_API QExtMvvmSetValueCommand : public QExtMvvmAbstractItemCommand {
public:
    QExtMvvmSetValueCommand(QExtMvvmSessionItem* item, QVariant value, int role);
    ~QExtMvvmSetValueCommand() override;

private:
    void undo_command() override;
    void execute_command() override;
    void swap_values();

    struct SetValueCommandImpl;
    QExtUniquePointer<SetValueCommandImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_COMMANDS_COPYITEMCOMMAND_H
