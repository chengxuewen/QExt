#ifndef _QEXTMVVMCOMMANDSSETVALUECOMMAND_H
#define _QEXTMVVMCOMMANDSSETVALUECOMMAND_H

#include <qextMvvmItemCommand.h>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Command for unddo/redo framework to set the data of QEXTMvvmSessionItem.

class QEXT_MVVM_API QEXTMvvmSetValueCommand : public QEXTMvvmItemCommand
{
public:
    QEXTMvvmSetValueCommand(QEXTMvvmSessionItem* item, QVariant value, int role);
    ~QEXTMvvmSetValueCommand() override;

private:
    void undo_command() override;
    void execute_command() override;
    void swap_values();

    struct SetValueCommandImpl;
    std::unique_ptr<SetValueCommandImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMCOMMANDSSETVALUECOMMAND_H
