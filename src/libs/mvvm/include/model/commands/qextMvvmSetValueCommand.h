#ifndef _QEXTMVVMSETVALUECOMMAND_H
#define _QEXTMVVMSETVALUECOMMAND_H

#include <qextMvvmAbstractItemCommand.h>
#include <qextMvvmVariant.h>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Command for unddo/redo framework to set the data of QEXTMvvmSessionItem.

class QEXT_MVVM_API QEXTSetValueCommand : public QEXTAbstractItemCommand
{
public:
    QEXTSetValueCommand(QEXTMvvmSessionItem* item, QEXTMvvmVariant value, int role);
    ~QEXTSetValueCommand() override;

private:
    void undo_command() override;
    void execute_command() override;
    void swap_values();

    struct SetValueCommandImpl;
    std::unique_ptr<SetValueCommandImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMSETVALUECOMMAND_H
