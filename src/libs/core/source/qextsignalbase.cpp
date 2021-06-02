#include <qextsignalbase.h>

#include <QSharedPointer>

#include <stdlib.h>
#include <memory.h>

namespace qextinternal {

// Data sent from QEXTSignalImpl::insert() to QEXTSlotRep::setParent() when a slot is
// connected, and then sent from QEXTSlotRep::disconnect() to QEXTSignalImpl::notify() when the slot is disconnected.
struct QEXTSelfIter
{
    QEXTSignalImpl *m_self;
    QEXTSignalImpl::IteratorType m_iter;

    QEXTSelfIter(QEXTSignalImpl *self, QEXTSignalImpl::IteratorType iter)
        : m_self(self), m_iter(iter) {}
};

QEXTSignalImpl::QEXTSignalImpl()
    : m_refCount(0), m_execCount(0), m_deferred(0) {}

// only MSVC needs this to guarantee that all new/delete are executed from the DLL module
#ifdef Q_CC_MSVC
void* QEXTSignalImpl::operator new(size_t size)
{
    return malloc(size);
}

void QEXTSignalImpl::operator delete(void *p)
{
    free(p);
}
#endif

void QEXTSignalImpl::clear()
{
    // Don't let QEXTSignalImpl::notify() erase the slots. It would invalidate the
    // iterator in the following loop.
    const bool saved_deferred = m_deferred;
    QEXTSignalExec exec(this);

    // Disconnect all connected slots before they are deleted.
    // QEXTSignalImpl::notify() will be called and delete the QEXTSelfIter structs.
    for (IteratorType iter = m_slotList.begin(); iter != m_slotList.end(); ++iter) {
        iter->disconnect();
    }
    m_deferred = saved_deferred;
    m_slotList.clear();
}

QEXTSignalImpl::SizeType QEXTSignalImpl::size() const
{
    return m_slotList.size();
}

bool QEXTSignalImpl::isBlocked() const
{
    for (ConstIteratorType iter = m_slotList.begin(); iter != m_slotList.end(); ++iter) {
        if (!iter->isBlocked()) {
            return false;
        }
    }
    return true;
}

void QEXTSignalImpl::setBlock(bool block)
{
    for (IteratorType iter = m_slotList.begin(); iter != m_slotList.end(); ++iter) {
        iter->setBlock(block);
    }
}

QEXTSignalImpl::IteratorType QEXTSignalImpl::connect(const QEXTSlotBase &slot)
{
    return this->insert(m_slotList.end(), slot);
}

QEXTSignalImpl::IteratorType QEXTSignalImpl::erase(IteratorType iter)
{
    // Don't let QEXTSignalImpl::notify() erase the slot. It would be more
    // difficult to get the correct return value from QEXTSignalImpl::erase().
    const bool saved_deferred = m_deferred;
    QEXTSignalExec exec(this);

    // Disconnect the slot before it is deleted.
    // QEXTSignalImpl::notify() will be called and delete the QEXTSelfIter struct.
    iter->disconnect();

    m_deferred = saved_deferred;
    return m_slotList.erase(iter);
}

QEXTSignalImpl::IteratorType QEXTSignalImpl::insert(QEXTSignalImpl::IteratorType iter, const QEXTSlotBase &slot)
{
    IteratorType temp = m_slotList.insert(iter, slot);
    QEXTSelfIter *selfIter = new QEXTSelfIter(this, temp);
    temp->setParent(selfIter, &notify);
    return temp;
}

void QEXTSignalImpl::sweep()
{
    // The deletion of a slot may cause the deletion of a QEXTSignalBase,
    // a decrementation of m_refCount, and the deletion of this.
    // In that case, the deletion of this is deferred to ~QEXTSignalExec().
    QEXTSignalExec exec(this);

    m_deferred = false;
    IteratorType iter = m_slotList.begin();
    while (iter != m_slotList.end()) {
        if ((*iter).isEmpty()) {
            iter = m_slotList.erase(iter);
        } else {
            ++iter;
        }
    }
}

//static
void* QEXTSignalImpl::notify(void *data)
{
    QSharedPointer<QEXTSelfIter> selfIter(static_cast<QEXTSelfIter*>(data));

    if (selfIter->m_self->m_execCount == 0) {
        // The deletion of a slot may cause the deletion of a QEXTSignalBase,
        // a decrementation of si->m_self->m_refCount, and the deletion of si->m_self.
        // In that case, the deletion of si->m_self is deferred to ~QEXTSignalExec().
        QEXTSignalExec exec(selfIter->m_self);
        selfIter->m_self->m_slotList.erase(selfIter->m_iter);
    } else {                           // This is occuring during signal emission or slot erasure.
        selfIter->m_self->m_deferred = true; // => sweep() will be called from ~QEXTSignalExec() after signal emission.
    }
    return QEXT_NULLPTR;                      // This is safer because we don't have to care about our
    // iterators in send(), clear(), and erase().
}

} /* namespace qextInternal */

QEXTSignalBase::QEXTSignalBase()
    : m_impl(QEXT_NULLPTR) {}

QEXTSignalBase::QEXTSignalBase(const QEXTSignalBase& src)
    : QEXTTrackable(src), m_impl(src.impl())
{
    m_impl->reference();
}

QEXTSignalBase::~QEXTSignalBase()
{
    if (m_impl) {
        // Disconnect all slots before m_impl is deleted.
        // TODO: Move the QEXTSignalImpl::clear() call to ~QEXTSignalImpl() when ABI can be broken.
        if (m_impl->m_refCount == 1) {
            m_impl->clear();
        }
        m_impl->unreference();
    }
}

void QEXTSignalBase::clear()
{
    if (m_impl) {
        m_impl->clear();
    }
}

QEXTSignalBase::SizeType QEXTSignalBase::size() const
{
    return (m_impl ? m_impl->size() : 0);
}

bool QEXTSignalBase::isBlocked() const
{
    return (m_impl ? m_impl->isBlocked() : true);
}

void QEXTSignalBase::setBlock(bool block)
{
    if (m_impl) {
        m_impl->setBlock(block);
    }
}

void QEXTSignalBase::unblock()
{
    if (m_impl) {
        m_impl->setBlock(false);
    }
}

QEXTSignalBase::IteratorType QEXTSignalBase::connect(const QEXTSlotBase &slot)
{
    return impl()->connect(slot);
}

QEXTSignalBase::IteratorType QEXTSignalBase::insert(IteratorType iter, const QEXTSlotBase &slot)
{
    return impl()->insert(iter, slot);
}

QEXTSignalBase::IteratorType QEXTSignalBase::erase(IteratorType iter)
{
    return impl()->erase(iter);
}

QEXTSignalBase& QEXTSignalBase::operator = (const QEXTSignalBase &src)
{
    if (src.m_impl == m_impl) {
        return *this;
    }

    if (m_impl) {
        // Disconnect all slots before m_impl is deleted.
        // TODO: Move the QEXTSignalImpl::clear() call to ~QEXTSignalImpl() when ABI can be broken.
        if (m_impl->m_refCount == 1) {
            m_impl->clear();
        }
        m_impl->unreference();
    }
    m_impl = src.impl();
    m_impl->reference();
    return *this;
}

qextinternal::QEXTSignalImpl* QEXTSignalBase::impl() const
{
    if (!m_impl) {
        m_impl = new qextinternal::QEXTSignalImpl;
        m_impl->reference();  // start with a reference count of 1
    }
    return m_impl;
}
