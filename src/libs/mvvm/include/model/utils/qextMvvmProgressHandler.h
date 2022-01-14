#ifndef _QEXTMVVMUTILSPROGRESSHANDLER_H
#define _QEXTMVVMUTILSPROGRESSHANDLER_H

#include <functional>
#include <mutex>
#include <qextMvvmGlobal.h>

namespace ModelView
{

//! Maintain information about progress of a computation.
//! Initialized with callback function to report progress and retrieve interruption request status.

class QEXT_MVVM_API QEXTMvvmProgressHandler
{
public:
    using callback_t = std::function<bool(size_t)>;

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
    std::mutex mutex;
    callback_t runner_callback;
    size_t max_ticks_count{0};
    size_t completed_ticks{0};
    bool interrupt_request{false};
};

} // namespace ModelView

#endif // _QEXTMVVMUTILSPROGRESSHANDLER_H
