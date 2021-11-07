#ifndef _QEXTMVVMMODELHASCHANGEDCONTROLLER_H
#define _QEXTMVVMMODELHASCHANGEDCONTROLLER_H

#include <qextMvvmModelListener.h>
#include <qextMvvmTagRow.h>

#include <qextFunction.h>

//! Tracks changes in the model.
//! Allows to check if model has been changed (e.g. modified, inserted or removed items) since last
//! call of ::resetChanged().

class QEXT_MVVM_API QEXTMvvmModelHasChangedController : public QEXTMvvmModelListener<QEXTMvvmModel>
{
public:
    typedef QEXTFunction<void> Callback;

    QEXTMvvmModelHasChangedController(QEXTMvvmModel *model, Callback callback = Callback());

    bool hasChanged() const;

    void resetChanged();

private:
    void onDataChange(QEXTMvvmItem *, int);
    void onItemInserted(QEXTMvvmItem *, QEXTMvvmTagRow);
    void onItemRemoved(QEXTMvvmItem *, QEXTMvvmTagRow);
    void onModelReset(QEXTMvvmModel *);

    void processChange();
    bool m_hasChanged{false};
    Callback m_callback; //! informs the user about change in the model
};


#endif // _QEXTMVVMMODELHASCHANGEDCONTROLLER_H
