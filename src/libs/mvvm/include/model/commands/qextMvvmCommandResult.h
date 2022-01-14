#ifndef _QEXTMVVMCOMMANDSCOMMANDRESULT_H
#define _QEXTMVVMCOMMANDSCOMMANDRESULT_H

#include <QObject>

namespace ModelView
{

class QEXTMvvmSessionItem;

//! Results of command execution.
//using QEXTMvvmCommandResult = std::variant<bool, ModelView::QEXTMvvmSessionItem*>;
class QEXTMvvmCommandResult
{
public:
    QEXTMvvmCommandResult() : m_item(nullptr), m_success(false) {}
    QEXTMvvmCommandResult(ModelView::QEXTMvvmSessionItem *item) : m_item(item), m_success(false) {}
    QEXTMvvmCommandResult(bool success) : m_item(nullptr), m_success(success) {}

    ModelView::QEXTMvvmSessionItem *item() const { return m_item; }
    bool success() const { return m_success; }

private:
    ModelView::QEXTMvvmSessionItem *m_item;
    bool m_success;
};

} // namespace ModelView

#endif // _QEXTMVVMCOMMANDSCOMMANDRESULT_H
