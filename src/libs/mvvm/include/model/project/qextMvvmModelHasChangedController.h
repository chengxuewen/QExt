#ifndef _QEXTMVVMMODELHASCHANGEDCONTROLLER_H
#define _QEXTMVVMMODELHASCHANGEDCONTROLLER_H

#include <functional>
#include <qextMvvmModelListener.h>

namespace ModelView
{

//! Tracks changes in the model.
//! Allows to check if model has been changed (e.g. modified, inserted or removed items) since last
//! call of ::resetChanged().

class QEXT_MVVM_API QEXTMvvmModelHasChangedController : public QEXTMvvmModelListener<QEXTMvvmSessionModel>
{
public:
    using callback_t = std::function<void()>;
    QEXTMvvmModelHasChangedController(QEXTMvvmSessionModel* model, callback_t callback = {});

    bool hasChanged() const;

    void resetChanged();

private:
    void process_change();
    bool m_has_changed{false};
    callback_t m_callback; //! informs the user about change in the model
};

} // namespace ModelView

#endif // _QEXTMVVMMODELHASCHANGEDCONTROLLER_H
