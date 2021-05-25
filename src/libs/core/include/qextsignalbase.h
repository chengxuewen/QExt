#ifndef QEXTSIGNALBASE_H
#define QEXTSIGNALBASE_H

#include <qextglobal.h>
#include <qexttypetrait.h>
#include <qexttrackable.h>
#include <qextslot.h>
#include <qextmemberfunctor.h>

#include <list>
#include <cstddef>

namespace qextinternal
{

struct QEXT_CORE_API  QEXTSignalImpl
{
    typedef std::size_t SizeType;
    typedef std::list<QEXTSlotBase>  SlotList;
    typedef SlotList::iterator       IteratorType;
    typedef SlotList::const_iterator ConstIteratorType;

    QEXTSignalImpl();

    // only MSVC needs this to guarantee that all new/delete are executed from the DLL module
#ifdef Q_CC_MSVC
    void* operator new(size_t size);
    void operator delete(void *p);
#endif

    inline void reference() {
        ++m_refCount;
    }

    inline void referenceExec() {
        ++m_refCount;
        ++m_execCount;
    }

    inline void unreference() {
        if (!(--m_refCount)) {
            delete this;
        }
    }

    inline void unreferenceExec() {
        if (!(--m_refCount)) {
            delete this;
        } else if (!(--m_execCount) && m_deferred) {
            sweep();
        }
    }

    inline bool empty() const {
        return m_slotList.empty();
    }

    void clear();

    SizeType size() const;

    bool isBlocked() const;

    void block(bool shouldBlock = true);

    IteratorType connect(const QEXTSlotBase &slot);
    IteratorType insert(IteratorType iter, const QEXTSlotBase &slot);
    IteratorType erase(IteratorType iter);

    void sweep();

    static void* notify(void *d);

    short m_refCount;
    short m_execCount;
    bool m_deferred;
    std::list<QEXTSlotBase> m_slotList;
};


struct QEXT_CORE_API QEXTSignalExec
{
    inline QEXTSignalExec(const QEXTSignalImpl *signal)
        : m_signal(const_cast<QEXTSignalImpl*>(signal)) {
        m_signal->referenceExec();
    }

    inline ~QEXTSignalExec() {
        m_signal->unreferenceExec();
    }

    QEXTSignalImpl *m_signal;
};

struct QEXT_CORE_API QEXTTempSlotList
{
    typedef QEXTSignalImpl::SlotList SlotList;
    typedef QEXTSignalImpl::IteratorType iterator;
    typedef QEXTSignalImpl::ConstIteratorType const_iterator;

    QEXTTempSlotList(SlotList &slotList) : m_slots(slotList) {
        placeholder = m_slots.insert(m_slots.end(), QEXTSlotBase());
    }

    ~QEXTTempSlotList()
    {
        m_slots.erase(placeholder);
    }

    iterator begin() { return m_slots.begin(); }
    iterator end() { return placeholder; }
    const_iterator begin() const { return m_slots.begin(); }
    const_iterator end() const { return placeholder; }

private:
    SlotList &m_slots;
    SlotList::iterator placeholder;
};

} // namespace qextInternal


struct QEXT_CORE_API QEXTSignalBase : public QEXTTrackable
{
    typedef std::size_t SizeType;

    QEXTSignalBase();
    QEXTSignalBase(const QEXTSignalBase &src);
    ~QEXTSignalBase();

    QEXTSignalBase& operator = (const QEXTSignalBase &src);


    inline bool empty() const {
        return (!m_impl || m_impl->empty());
    }

    void clear();

    SizeType size() const;

    bool isBlocked() const;
    void block(bool shouldBlock = true);
    void unblock();

protected:
    typedef qextinternal::QEXTSignalImpl::IteratorType IteratorType;

    IteratorType connect(const QEXTSlotBase &slot);
    IteratorType insert(IteratorType iter, const QEXTSlotBase &slot);
    IteratorType erase(IteratorType iter);
    qextinternal::QEXTSignalImpl *impl() const;

    mutable qextinternal::QEXTSignalImpl *m_impl;
};

#endif // QEXTSIGNALBASE_H
