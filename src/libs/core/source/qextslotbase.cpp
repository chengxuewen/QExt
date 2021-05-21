#include "qextslotbase.h"


namespace qextinternal {

QEXTSlotRepresentation::QEXTSlotRepresentation(HookFunctionType call, HookFunctionType destroy, HookFunctionType deepCopy)
    : m_call(call), m_destroy(destroy), m_deepCopy(deepCopy), m_cleanup(QEXT_NULLPTR), m_parent(QEXT_NULLPTR)
{

}

QEXTSlotRepresentation::~QEXTSlotRepresentation()
{
    this->destroy();
}

#ifdef Q_CC_MSVC
void *QEXTSlotRepresentation::operator new(size_t size)
{
    return malloc(size);
}

void QEXTSlotRepresentation::operator delete(void *p)
{
    free(p);
}
#endif

void QEXTSlotRepresentation::destroy()
{
    if (m_destroy) {
        (*m_destroy)(this);
    }
}

QEXTSlotRepresentation *QEXTSlotRepresentation::deepCopy() const
{
    return reinterpret_cast<QEXTSlotRepresentation*>((*m_deepCopy)(const_cast<QEXTSlotRepresentation*>(this)));
}

void QEXTSlotRepresentation::setParent(void *parent, HookFunctionType cleanup)
{
    m_parent = parent;
    m_cleanup = cleanup;
}

void QEXTSlotRepresentation::disconnect()
{
    if (m_parent) {
        m_call = QEXT_NULLPTR;          // Invalidate the slot.
        // _Must_ be done here because parent_ might defer the actual
        // destruction of the slot_rep and try to invoke it before that point.
        void *data = m_parent;
        m_parent = QEXT_NULLPTR;        // Just a precaution.
        (m_cleanup)(data);  // Notify the parent (might lead to destruction of this!).
    } else {
        m_call = QEXT_NULLPTR;
    }
}

void *QEXTSlotRepresentation::notify(void *data)
{
    struct DestroyNotifyStruct
    {
        DestroyNotifyStruct() : m_deleted(false) { }

        static void *notify(void *data) {
            DestroyNotifyStruct *self = reinterpret_cast<DestroyNotifyStruct*>(data);
            self->m_deleted = true;
            return QEXT_NULLPTR;
        }

        bool m_deleted;
    };

    QEXTSlotRepresentation *self = reinterpret_cast<QEXTSlotRepresentation *>(data);
    self->m_call = QEXT_NULLPTR; // Invalidate the slot.

    // Make sure we are notified if disconnect() deletes m_self, which is trackable.
    DestroyNotifyStruct notifier;
    self->addDestroyNotifyCallback(&notifier, DestroyNotifyStruct::notify);
    self->disconnect(); // Disconnect the slot (might lead to deletion of m_self!).
    // If m_self has been deleted, the destructor has called destroy().
    if (!notifier.m_deleted) {
        self->removeDestroyNotifyCallback(&notifier);
        self->destroy(); // Detach the stored functor from the other referred trackables and destroy it.
        // destroy() might lead to deletion of m_self. Bug #564005.
    }
    return QEXT_NULLPTR;
}



} //namespace qextinternal



QEXTSlotBase::QEXTSlotBase()
    : m_slotRep(QEXT_NULLPTR),
      m_blocked(false)
{

}

QEXTSlotBase::QEXTSlotBase(QEXTSlotBase::SlotRepType *rep)
    : m_slotRep(rep),
      m_blocked(false)
{

}

QEXTSlotBase::QEXTSlotBase(const QEXTSlotBase &src)
    : m_slotRep(QEXT_NULLPTR),
      m_blocked(src.m_blocked)
{
    if (src.m_slotRep) {
        //Check call_ so we can ignore invalidated slots.
        //Otherwise, destroyed bound reference parameters (whose destruction caused the slot's invalidation) may be used during dup().
        //Note: I'd prefer to check somewhere during dup(). murrayc.
        if (src.m_slotRep->m_call) {
            m_slotRep = src.m_slotRep->deepCopy();
        } else {
            *this = QEXTSlotBase(); //Return the default invalid slot.
        }
    }
}

QEXTSlotBase::~QEXTSlotBase()
{
    if (m_slotRep) {
        delete m_slotRep;
    }
}

QEXTSlotBase::operator bool() const
{
    return QEXT_NULLPTR != m_slotRep;
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
    if (m_slotRep) {             // Silently exchange the slot_rep.
        newSlotRep->setParent(m_slotRep->m_parent, m_slotRep->m_cleanup);
        delete m_slotRep;
    }
    m_slotRep = newSlotRep;
    return *this;
}

void QEXTSlotBase::setParent(void *parent, void *(*cleanup)(void *)) const
{
    if (m_slotRep) {
        m_slotRep->setParent(parent, cleanup);
    }
}

void QEXTSlotBase::addDestroyNotifyCallback(void *data, QEXTSlotBase::DestroyNotifyFunc func) const
{
    if (m_slotRep) {
        m_slotRep->addDestroyNotifyCallback(data, func);
    }
}

void QEXTSlotBase::removeDestroyNotifyCallback(void *data) const
{
    if (m_slotRep) {
        m_slotRep->removeDestroyNotifyCallback(data);
    }
}

bool QEXTSlotBase::isEmpty() const
{
    return (!m_slotRep || !m_slotRep->m_call);
}

bool QEXTSlotBase::blocked() const
{
    return m_blocked;
}

bool QEXTSlotBase::block(bool shouldBlock)
{
    bool old = m_blocked;
    m_blocked = shouldBlock;
    return old;
}

bool QEXTSlotBase::unblock()
{
    return this->block(false);
}

void QEXTSlotBase::disconnect()
{
    if (m_slotRep) {
        m_slotRep->disconnect();
    }
}
