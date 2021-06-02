#include "qextslotbase.h"


namespace qextinternal {

QEXTSlotRep::QEXTSlotRep(HookFunctionType call, HookFunctionType destroy, HookFunctionType deepCopy)
    : m_call(call), m_destroy(destroy), m_deepCopy(deepCopy), m_cleanup(QEXT_NULLPTR), m_parent(QEXT_NULLPTR)
{

}

QEXTSlotRep::~QEXTSlotRep()
{
    this->destroy();
}

#ifdef Q_CC_MSVC
void *QEXTSlotRep::operator new(size_t size)
{
    return malloc(size);
}

void QEXTSlotRep::operator delete(void *p)
{
    free(p);
}
#endif

void QEXTSlotRep::destroy()
{
    if (m_destroy) {
        (*m_destroy)(this);
    }
}

QEXTSlotRep *QEXTSlotRep::deepCopy() const
{
    return reinterpret_cast<QEXTSlotRep*>((*m_deepCopy)(const_cast<QEXTSlotRep*>(this)));
}

void QEXTSlotRep::setParent(void *parent, HookFunctionType cleanup)
{
    m_parent = parent;
    m_cleanup = cleanup;
}

void QEXTSlotRep::disconnect()
{
    if (m_parent) {
        // Invalidate the slot.
        // Must be done here because m_parent might defer the actual
        // destruction of the QEXTSlotRep and try to invoke it before that point.
        m_call = QEXT_NULLPTR;
        void *data = m_parent;
        m_parent = QEXT_NULLPTR;    // Just a precaution.
        (m_cleanup)(data);          // Notify the parent (might lead to destruction of this!).
    } else {
        m_call = QEXT_NULLPTR;
    }
}

void *QEXTSlotRep::notify(void *data)
{
    struct DestroyNotify
    {
        DestroyNotify() : m_deleted(false) { }

        static void *notify(void *data) {
            DestroyNotify *self = reinterpret_cast<DestroyNotify*>(data);
            self->m_deleted = true;
            return QEXT_NULLPTR;
        }

        bool m_deleted;
    };

    QEXTSlotRep *self = reinterpret_cast<QEXTSlotRep *>(data);
    self->m_call = QEXT_NULLPTR; // Invalidate the slot.

    // Make sure we are notified if disconnect() deletes m_self, which is trackable.
    DestroyNotify notifier;
    self->addDestroyNotifyCallback(&notifier, DestroyNotify::notify);
    self->disconnect(); // Disconnect the slot (might lead to deletion of m_self!).
    // If self has been deleted, the destructor has called destroy().
    if (!notifier.m_deleted) {
        self->removeDestroyNotifyCallback(&notifier);
        self->destroy(); // Detach the stored functor from the other referred trackables and destroy it.
    }
    return QEXT_NULLPTR;
}



} //namespace qextinternal



QEXTSlotBase::QEXTSlotBase()
    : m_blocked(false)
{

}

QEXTSlotBase::QEXTSlotBase(QEXTSlotBase::SlotRepType *rep)
    : m_blocked(false),
      m_slotRep(rep)
{

}

QEXTSlotBase::QEXTSlotBase(const QEXTSlotBase &src)
    : m_blocked(src.m_blocked)
{
    if (!src.m_slotRep.isNull()) {
        //Check call_ so we can ignore invalidated slots.
        //Otherwise, destroyed bound reference parameters (whose destruction caused the slot's invalidation) may be used during dup().
        //Note: I'd prefer to check somewhere during dup(). murrayc.
        if (src.m_slotRep->m_call) {
            m_slotRep.reset(src.m_slotRep->deepCopy());
        } else {
            *this = QEXTSlotBase(); //Return the default invalid slot.
        }
    }
}

QEXTSlotBase::~QEXTSlotBase()
{

}

QEXTSlotBase::operator bool() const
{
    return !m_slotRep.isNull();
}

QEXTSlotBase &QEXTSlotBase::operator=(const QEXTSlotBase &src)
{
    if (src.m_slotRep == m_slotRep) {
        return *this;
    }
    if (src.isEmpty()) {
        this->disconnect();
        return *this;
    }

    SlotRepType *newSlotRep = src.m_slotRep->deepCopy();
    // Silently exchange the QEXTSlotRep.
    if (!m_slotRep.isNull()) {
        newSlotRep->setParent(m_slotRep->m_parent, m_slotRep->m_cleanup);
        m_slotRep.reset(QEXT_NULLPTR);
    }
    m_slotRep.reset(newSlotRep);
    return *this;
}

void QEXTSlotBase::setParent(void *parent, void *(*cleanup)(void *)) const
{
    if (!m_slotRep.isNull()) {
        m_slotRep->setParent(parent, cleanup);
    }
}

void QEXTSlotBase::addDestroyNotifyCallback(void *data, QEXTSlotBase::DestroyNotifyFunc func) const
{
    if (!m_slotRep.isNull()) {
        m_slotRep->addDestroyNotifyCallback(data, func);
    }
}

void QEXTSlotBase::removeDestroyNotifyCallback(void *data) const
{
    if (!m_slotRep.isNull()) {
        m_slotRep->removeDestroyNotifyCallback(data);
    }
}

bool QEXTSlotBase::isEmpty() const
{
    return m_slotRep.isNull() || (QEXT_NULLPTR == m_slotRep->m_call);
}

bool QEXTSlotBase::isBlocked() const
{
    return m_blocked;
}

bool QEXTSlotBase::setBlock(bool block)
{
    bool old = m_blocked;
    m_blocked = block;
    return old;
}

bool QEXTSlotBase::unblock()
{
    return this->setBlock(false);
}

void QEXTSlotBase::disconnect()
{
    if (!m_slotRep.isNull()) {
        m_slotRep->disconnect();
    }
}
