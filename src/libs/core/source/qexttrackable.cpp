#include "qexttrackable.h"

#include <QDebug>

namespace qextinternal {

QEXTTrackableCallbackList::~QEXTTrackableCallbackList()
{
    m_clearing = true;
    for (CallbackList::iterator iter = m_callbacks.begin(); iter != m_callbacks.end(); ++iter) {
        if ((*iter).func) {
            (*iter).func((*iter).data);
        }
    }
    m_callbacks.clear();
}

void QEXTTrackableCallbackList::addCallback(void *data, QEXTDestroyNotifyFunctionType func)
{
    // TODO: Is it okay to silently ignore attempts to add dependencies when the list is being cleared?
    //       I'd consider this a serious application bug, since the app is likely to segfault.
    //       But then, how should we handle it? Throw an exception?
    if (!m_clearing) {
        m_callbacks.append(QEXTTrackableCallback(data, func));
    }
}

void QEXTTrackableCallbackList::removeCallback(void *data)
{
    if (!m_callbacks.isEmpty()) {
        for (CallbackList::iterator iter = m_callbacks.begin(); iter != m_callbacks.end(); ++iter) {
            if ((*iter).data == data && (*iter).func != QEXT_NULLPTR) {
                //Don't remove a list element while the list is being cleared.
                //It could invalidate the iterator in ~trackable_callback_list() or clear().
                if (m_clearing) {
                    (*iter).func = QEXT_NULLPTR;
                } else {
                    m_callbacks.erase(iter);
                    return;
                }
            }
        }
    }
}

void QEXTTrackableCallbackList::clear()
{
    m_clearing = true;
    for (CallbackList::iterator iter = m_callbacks.begin(); iter != m_callbacks.end(); ++iter) {
        if ((*iter).func) {
            (*iter).func((*iter).data);
        }
    }
    m_callbacks.clear();
    m_clearing = false;
}

} // namespace qextinternal


QEXTTrackable::QEXTTrackable()
    : m_callbackList(QEXT_NULLPTR)
{

}

/** Don't copy the notification list.
 * The objects watching src don't need to be notified when the new object dies.
 */
QEXTTrackable::QEXTTrackable(const QEXTTrackable &src)
    : m_callbackList(QEXT_NULLPTR)
{

}

QEXTTrackable::~QEXTTrackable()
{
    this->notifyCallbacks();
}

QEXTTrackable &QEXTTrackable::operator=(const QEXTTrackable &src)
{
    if(this != &src) {
        this->notifyCallbacks(); //Make sure that we have finished with existing stuff before replacing it.
    }
    return *this;
}

void QEXTTrackable::addDestroyNotifyCallback(void *data, QEXTTrackable::DestroyNotifyFunc func) const
{
    this->callbackList()->addCallback(data, func);
}

void QEXTTrackable::removeDestroyNotifyCallback(void *data) const
{
    this->callbackList()->removeCallback(data);
}

void QEXTTrackable::notifyCallbacks()
{
    if (m_callbackList) {
        delete m_callbackList; //This invokes all of the callbacks.
    }
    m_callbackList = QEXT_NULLPTR;
}

qextinternal::QEXTTrackableCallbackList *QEXTTrackable::callbackList() const
{
    if (!m_callbackList) {
        m_callbackList = new qextinternal::QEXTTrackableCallbackList;
    }
    return m_callbackList;
}
