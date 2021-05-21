#ifndef QEXTTRACKABLE_H
#define QEXTTRACKABLE_H

#include <qextglobal.h>

#include <list>

namespace qextinternal {

typedef void *(*QEXTDestroyNotifyFunctionType)(void *data);

struct QEXT_CORE_API QEXTTrackableCallback
{
    QEXTTrackableCallback(void *data, QEXTDestroyNotifyFunctionType funcArg) : data(data), func(funcArg) {}

    void *data;
    QEXTDestroyNotifyFunctionType func;
};

struct QEXT_CORE_API QEXTTrackableCallbackList
{
    QEXTTrackableCallbackList() : m_clearing(false) {}
    ~QEXTTrackableCallbackList();

    void addCallback(void *data, QEXTDestroyNotifyFunctionType func);
    void removeCallback(void *data);
    void clear();

private:
    typedef std::list<QEXTTrackableCallback> CallbackList;

    CallbackList m_callbacks;
    bool m_clearing;
};

} // namespace qextinternal



class QEXT_CORE_API QEXTTrackable
{
public:
    typedef qextinternal::QEXTDestroyNotifyFunctionType DestroyNotifyFunc;

    QEXTTrackable();
    QEXTTrackable(const QEXTTrackable &src);
    virtual ~QEXTTrackable();

    QEXTTrackable& operator=(const QEXTTrackable &src);

    void addDestroyNotifyCallback(void *data, DestroyNotifyFunc func) const;
    void removeDestroyNotifyCallback(void *data) const;
    void notifyCallbacks();

private:
    qextinternal::QEXTTrackableCallbackList *callbackList() const;

    mutable qextinternal::QEXTTrackableCallbackList *m_callbackList;
};

#endif // QEXTTRACKABLE_H
