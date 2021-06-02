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

/** Implementation of the signal interface.
 * QEXTSignalImpl manages a list of slots. When a slot becomes
 * invalid (because some referred object dies), notify() is executed.
 * notify() either calls m_slotList.erase() directly or defers the execution of
 * erase() to sweep() when the signal is being emitted. sweep() removes all
 * invalid slots from the list.
 */
struct QEXT_CORE_API  QEXTSignalImpl
{
    typedef std::size_t                 SizeType;
    typedef std::list<QEXTSlotBase>     SlotList;
    typedef SlotList::iterator          IteratorType;
    typedef SlotList::const_iterator    ConstIteratorType;

    QEXTSignalImpl();

    // only MSVC needs this to guarantee that all new/delete are executed from the DLL module
#ifdef Q_CC_MSVC
    void* operator new(size_t size);
    void operator delete(void *p);
#endif

    // Increments the reference counter.
    inline void reference() {
        ++m_referenceCount;
    }

    // Increments the reference and execution counter.
    inline void referenceExecution() {
        ++m_referenceCount;
        ++m_executionCount;
    }

    /** Decrements the reference counter.
     * The object is deleted when the reference counter reaches zero.
     */
    inline void unreference() {
        if (!(--m_referenceCount)) {
            delete this;
        }
    }

    /** Decrements the reference and execution counter.
     * Invokes sweep() if the execution counter reaches zero and the
     * removal of one or more slots has been deferred.
     */
    inline void unreferenceExecution() {
        if (!(--m_referenceCount)) {
            delete this;
        } else if (!(--m_executionCount) && m_deferred) {
            this->sweep();
        }
    }

    /** Returns whether the list of slots is empty.
     * @return @p true if the list of slots is empty.
     */
    inline bool empty() const {
        return m_slotList.empty();
    }

    // Empties the list of slots.
    void clear();

    /** Returns the number of slots in the list.
     * @return The number of slots in the list.
     */
    SizeType size() const;


    /** Returns whether all slots in the list are blocked.
     * @return @p true if all slots are blocked or the list is empty.
     */
    bool isBlocked() const;

    /** Sets the blocking state of all slots in the list.
     * If @e block is @p true then the blocking state is set.
     * Subsequent emissions of the signal don't invoke the functors
     * contained in the slots until setBlock() with @e block = @p false is called.
     * QEXTSlotBase::setBlock() and QEXTSlotBase::unblock() can change the
     * blocking state of individual slots.
     * @param block Indicates whether the blocking state should be set or unset.
     */
    void setBlock(bool block = true);

    /** Adds a slot at the bottom of the list of slots.
     * @param slot The slot to add to the list of slots.
     * @return An iterator pointing to the new slot in the list.
     */
    IteratorType connect(const QEXTSlotBase &slot);

    /** Adds a slot at the given position into the list of slots.
     * @param iter An iterator indicating the position where @p slot should be inserted.
     * @param slot The slot to add to the list of slots.
     * @return An iterator pointing to the new slot in the list.
     */
    IteratorType insert(IteratorType iter, const QEXTSlotBase &slot);

    /** Removes the slot at the given position from the list of slots.
     * @param iter An iterator pointing to the slot to be removed.
     * @return An iterator pointing to the slot in the list after the one removed.
     */
    IteratorType erase(IteratorType iter);

    /** Removes invalid slots from the list of slots.
     */
    void sweep();

    /** Callback that is executed when some slot becomes invalid.
     * This callback is registered in every slot when inserted into
     * the list of slots. It is executed when a slot becomes invalid
     * because of some referred object being destroyed.
     * It either calls m_slotList.erase() directly or defers the execution of
     * erase() to sweep() when the signal is being sended.
     * @param data A local structure, created in insert().
     */
    static void* notify(void *data);

    short m_referenceCount;     // Reference counter. The object is destroyed when @em m_refCount reaches zero.
    short m_executionCount;     // Execution counter. Indicates whether the signal is being sended.
    bool m_deferred;            // Indicates whether the execution of sweep() is being deferred.
    std::list<QEXTSlotBase> m_slotList; // // The list of slots.
};

// Exception safe sweeper for cleaning up invalid slots on the slot list.
struct QEXT_CORE_API QEXTSignalExecution
{
    /** Increments the reference and execution counter of the parent QEXTSignalImpl object.
     * @param sig The parent QEXTSignalImpl object.
     */
    QEXTSignalExecution(const QEXTSignalImpl *signal)
        : m_signal(const_cast<QEXTSignalImpl*>(signal)) {
        m_signal->referenceExecution();
    }
    // Decrements the reference and execution counter of the parent QEXTSignalImpl object.
    ~QEXTSignalExecution() {
        m_signal->unreferenceExecution();
    }

    // The parent QEXTSignalImpl object.
    QEXTSignalImpl *m_signal;
};

/** Temporary slot list used during signal send.
 *  Through evolution this class is slightly misnamed.  It is now
 *  an index into the slot_list passed into it.  It simply keeps track
 *  of where the end of this list was at construction, and pretends that's
 *  the end of your list.  This way you may connect during send without
 *  inadvertently entering an infinite loop, as well as make other
 *  modifications to the slot_list at your own risk.
 */
struct QEXT_CORE_API QEXTTempSlotList
{
    typedef QEXTSignalImpl::SlotList            SlotList;
    typedef QEXTSignalImpl::IteratorType        Iterator;
    typedef QEXTSignalImpl::ConstIteratorType   ConstIterator;

    QEXTTempSlotList(SlotList &slotList) : m_slots(slotList) {
        placeholder = m_slots.insert(m_slots.end(), QEXTSlotBase());
    }

    ~QEXTTempSlotList() {
        m_slots.erase(placeholder);
    }

    Iterator begin() { return m_slots.begin(); }
    Iterator end() { return placeholder; }
    ConstIterator begin() const { return m_slots.begin(); }
    ConstIterator end() const { return placeholder; }

private:
    SlotList &m_slots;
    SlotList::iterator placeholder;
};

} // namespace qextInternal


/** @defgroup signal Signals
 * Use QEXTSignal::connect() with qextMemberFunctor() and qextPointerFunctor() to connect a method or function with a signal.
 *
 * @code
 * signal_clicked.connect( qextMemberFunctor(*this, &MyWindow::on_clicked) );
 * @endcode
 *
 * When the signal is emitted your method will be called.
 *
 * QEXTSignal::connect() returns a connection, which you can later use to disconnect your method.
 * If the type of your object inherits from QEXTTrackable the method is disconnected
 * automatically when your object is destroyed.
 *
 * When signals are copied they share the underlying information,
 * so you can have a protected/private QEXTSignal member and a public accessor method.
 * A QEXTSignal is a kind of reference-counting pointer. It's similar to
 * std::shared_ptr<>, although QEXTSignal is restricted to holding a pointer to
 * a QEXTSignalImpl object that contains the implementation of the signal.
 *
 * @code
 * class MyClass
 * {
 * public:
 *   typedef QEXTSignal<void> MySignalType;
 *   MySignalType get_my_signal() { return m_my_signal; }
 * private:
 *   MySignalType m_my_signal;
 * };
 * @endcode
 *
 * signal and slot objects provide the core functionality of this
 * library. A slot is a container for an arbitrary functor.
 * A signal is a list of slots that are executed on send.
 * For compile time type safety a list of template arguments
 * must be provided for the signal template that determines the
 * parameter list for send. Functors and closures are converted
 * into slots implicitly on connection, triggering compiler errors
 * if the given functor or closure cannot be invoked with the
 * parameter list of the signal to connect to.
 *
 * Almost any functor with the correct signature can be converted to a QEXTSlot
 * and connected to a signal. See @ref slot "Slots" and QEXTSignal::connect().
 */

/** Base class for the QEXTSignal# templates.
 * QEXTSignalBase integrates most of the interface of the derived QEXTSignal#
 * templates. The implementation, however, resides in QEXTSignalImpl.
 * A QEXTSignalImpl object is dynamically allocated from signal_base
 * when first connecting a slot to the signal. This ensures that empty signals
 * don't waste memory.
 *
 * QEXTSignalImpl is reference-counted. When a QEXTSignal# object
 * is copied, the reference count of its QEXTSignalImpl object is
 * incremented. Both QEXTSignal# objects then refer to the same
 * QEXTSignalImpl object.
 *
 * @ingroup signal
 */
struct QEXT_CORE_API QEXTSignalBase : public QEXTTrackable
{
    typedef std::size_t     SizeType;

    QEXTSignalBase();
    QEXTSignalBase(const QEXTSignalBase &src);
    ~QEXTSignalBase();

    QEXTSignalBase& operator = (const QEXTSignalBase &src);

    /** Returns whether the list of slots is empty.
     * @return @p true if the list of slots is empty.
     */
    bool isEmpty() const {
        return (!m_impl || m_impl->empty());
    }

    // Empties the list of slots.
    void clear();

    /** Returns the number of slots in the list.
     * @return The number of slots in the list.
     */
    SizeType size() const;

    /** Returns whether all slots in the list are blocked.
     * @return @p true if all slots are blocked or the list is empty.
     */
    bool isBlocked() const;

    /** Sets the blocking state of all slots in the list.
     * If @e should_block is @p true then the blocking state is set.
     * Subsequent emissions of the signal don't invoke the functors
     * contained in the slots until unblock() or block() with
     * @e should_block = @p false is called.
     * QEXTSlotBase::setBlock() and QEXTSlotBase::unblock() can change the
     * blocking state of individual slots.
     * @param block Indicates whether the blocking state should be set or unset.
     */
    void setBlock(bool block = true);

    /** Unsets the blocking state of all slots in the list.
     */
    void unblock();

protected:
    typedef qextinternal::QEXTSignalImpl::IteratorType IteratorType;

    /** Adds a slot at the end of the list of slots.
     * With connect(), slots can also be added during signal send.
     * In this case, they won't be executed until the next send occurs.
     * @param slot_ The slot to add to the list of slots.
     * @return An iterator pointing to the new slot in the list.
     */
    IteratorType connect(const QEXTSlotBase &slot);
    /** Adds a slot at the given position into the list of slots.
     * Note that this function does not work during signal send!
     * @param iter An iterator indicating the position where @e slot should be inserted.
     * @param slot The slot to add to the list of slots.
     * @return An iterator pointing to the new slot in the list.
     */
    IteratorType insert(IteratorType iter, const QEXTSlotBase &slot);
    /** Removes the slot at the given position from the list of slots.
     * Note that this function does not work during signal send!
     * @param iter An iterator pointing to the slot to be removed.
     * @return An iterator pointing to the slot in the list after the one removed.
     */
    IteratorType erase(IteratorType iter);
    /** Returns the QEXTSignalImpl object encapsulating the list of slots.
     * @return The QEXTSignalImpl object encapsulating the list of slots.
     */
    qextinternal::QEXTSignalImpl *impl() const;

    // The QEXTSignalImpl object encapsulating the slot list.
    mutable qextinternal::QEXTSignalImpl *m_impl;
};

#endif // QEXTSIGNALBASE_H
