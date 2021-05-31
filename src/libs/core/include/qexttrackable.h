#ifndef QEXTTRACKABLE_H
#define QEXTTRACKABLE_H

#include <qextglobal.h>

#include <QMutex>
#include <QList>

namespace qextinternal {

typedef void *(*QEXTDestroyNotifyFunctionType)(void *data);

/** Destroy notification callback.
 * A destroy notification callback consists of a data pointer and a
 * function pointer. The function is executed from the owning callback
 * list (of type QEXTTrackableCallbackList) when its parent
 * object (of type QEXTTrackable) is destroyed or overwritten.
 */
struct QEXT_CORE_API QEXTTrackableCallback
{
    QEXTTrackableCallback(void *data, QEXTDestroyNotifyFunctionType funcArg) : data(data), func(funcArg) {}

    void *data;
    QEXTDestroyNotifyFunctionType func;
};

/** Callback list.
 * A callback list holds an list of callbacks of type
 * QEXTTrackableCallback. Callbacks are added and removed with
 * addCallback(), removeCallback() and clear(). The callbacks
 * are invoked from clear() and from the destructor.
 */
struct QEXT_CORE_API QEXTTrackableCallbackList
{
    QEXTTrackableCallbackList() : m_clearing(false) {}

    /** This invokes all of the callback functions.
     */
    ~QEXTTrackableCallbackList();

    /** Add a callback function.
     * @param data Data that will be sent as a parameter to teh callback function.
     * @param func The callback function.
     */
    void addCallback(void *data, QEXTDestroyNotifyFunctionType func);

    /** Remove the callback which has this data associated with it.
     * @param data The data that was given as a parameter to addCallback().
     */
    void removeCallback(void *data);

    /** This invokes all of the callback functions.
     */
    void clear();

private:
    typedef QList<QEXTTrackableCallback> CallbackList;

    CallbackList m_callbacks;
    bool m_clearing;
};

} // namespace qextinternal


/** Base class for objects with auto-disconnection.
 * trackable must be inherited when objects shall automatically
 * invalidate slots referring to them on destruction.
 * A slot built from a member function of a trackable derived
 * type installs a callback that is invoked when the trackable object
 * is destroyed or overwritten.
 *
 * addDestroyNotifyCallback() and removeDestroyNotifyCallback()
 * can be used to manually install and remove callbacks when
 * notification of the object dying is needed.
 *
 * notifyCallbacks() invokes and removes all previously installed
 * callbacks and can therefore be used to disconnect from all signals.
 *
 * Note that there is no virtual destructor. Don't use @p trackable*
 * as pointer type for managing your data or the destructors of
 * your derived types won't be called when deleting your objects.
 *
 * @ingroup signal
 */
class QEXT_CORE_API QEXTTrackable
{
public:
    typedef qextinternal::QEXTDestroyNotifyFunctionType DestroyNotifyFunc;

    QEXTTrackable();
    QEXTTrackable(const QEXTTrackable &src);
    virtual ~QEXTTrackable();

    QEXTTrackable& operator=(const QEXTTrackable &src);

    /** Add a callback that is executed (notified) when the trackable object is detroyed.
     * @param data Passed into func upon notification.
     * @param func Callback executed upon destruction of the object.
     */
    void addDestroyNotifyCallback(void *data, DestroyNotifyFunc func) const;

    /** Remove a callback previously installed with addDestroyNotifyCallback().
     * The callback is not executed.
     * @param data Parameter passed into previous call to addDestroyNotifyCallback().
     */
    void removeDestroyNotifyCallback(void *data) const;

    /** Execute and remove all previously installed callbacks.
     */
    void notifyCallbacks();

private:
    /** The callbacks are held in a list of type trackable_callback_list.
     * This list is allocated dynamically when the first callback is added.
     */
    qextinternal::QEXTTrackableCallbackList *callbackList() const;

    mutable qextinternal::QEXTTrackableCallbackList *m_callbackList;
};

#endif // QEXTTRACKABLE_H
