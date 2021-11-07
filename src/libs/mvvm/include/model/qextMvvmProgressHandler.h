#ifndef _QEXTMVVMPROGRESSHANDLER_H
#define _QEXTMVVMPROGRESSHANDLER_H

#include <qextFunction.h>
#include <qextMvvmGlobal.h>

#include <QMutex>

//! Maintain information about progress of a computation.
//! Initialized with callback function to report progress and retrieve interruption request status.

class QEXT_MVVM_API QEXTMvvmProgressHandler
{
public:
    typedef QEXTFunction<bool, size_t> callback_t;

    QEXTMvvmProgressHandler() = default;
    QEXTMvvmProgressHandler(callback_t callback, size_t max_ticks_count);

    QEXTMvvmProgressHandler(const QEXTMvvmProgressHandler& other) = delete;
    QEXTMvvmProgressHandler& operator=(const QEXTMvvmProgressHandler& other) = delete;

    void subscribe(callback_t callback);

    void setMaxTicksCount(size_t value);

    bool has_interrupt_request() const;

    void setCompletedTicks(size_t value);

    void reset();

private:
    QMutex m_mutex;
    callback_t runner_callback;
    size_t max_ticks_count{0};
    size_t completed_ticks{0};
    bool interrupt_request{false};
};


#endif // _QEXTMVVMPROGRESSHANDLER_H
