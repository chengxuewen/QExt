#ifndef _QEXTSIGNAL_H
#define _QEXTSIGNAL_H

#include <qextGlobal.h>
#include <qextMemberFunctor.h>
#include <qextFunction.h>
#include <qextTypeTrait.h>

#include <QAtomicInt>

#include <iostream>
#include <list>
#include <utility>
#include <cstddef>

namespace detail
{
struct QEXT_CORE_API QExtSignalData
{
    typedef std::size_t                     Size;
    typedef QList<QExtFunctionBase>         SlotList;
    typedef SlotList::iterator              Iterator;
    typedef SlotList::const_iterator        ConstIterator;
    typedef QExtSignalData                  Self;
    typedef QPair<Self *, Iterator>         SelfIterator;
    typedef QList<SelfIterator>             SelfIteratorList;

    QExtSignalData();
    virtual ~QExtSignalData();

    QExtSignalData &operator=(const QExtSignalData &other);
    bool operator==(const QExtSignalData &other) const;
    bool operator!=(const QExtSignalData &other) const;

    // Increments the reference counter.
    inline void reference()
    {
        m_referenceCount.ref();
    }

    /** Decrements the reference counter.
     * The object is deleted when the reference counter reaches zero.
     */
    inline void unreference()
    {
        if (!m_referenceCount.deref())
        {
            delete this;
        }
    }

    // Increments the reference and execution counter.
    inline void referenceExecution()
    {
        m_referenceCount.ref();
        m_executionCount.ref();
    }

    /** Decrements the reference and execution counter.
         * Invokes sweep() if the execution counter reaches zero and the
         * removal of one or more slots has been deferred.
         */
    inline void unreferenceExecution()
    {
        if (!m_referenceCount.deref())
        {
            delete this;
        }
        else if (!m_executionCount.deref() && (QEXT_ATOMIC_INT_TRUE == m_deferred))
        {
            this->sweep();
        }
    }

    /** Returns whether the list of slots is empty.
         * \return @p true if the list of slots is empty.
         */
    inline bool isEmpty() const
    {
        return m_slotList.empty();
    }

    // Empties the list of slots.
    void clear();

    /** Returns the number of slots in the list.
         * \return The number of slots in the list.
         */
    Size size() const;


    /** Returns whether all slots in the list are blocked.
         * \return @p true if all slots are blocked or the list is empty.
         */
    bool isBlocked() const;

    /** Sets the blocking state of all slots in the list.
         * If @e block is @p true then the blocking state is set.
         * Subsequent emissions of the signal don't invoke the functors
         * contained in the slots until setBlock() with @e block = @p false is called.
         * QExtFunctionBase::setBlock() and QExtFunctionBase::unblock() can change the
         * blocking state of individual slots.
         * \param block Indicates whether the blocking state should be set or unset.
         */
    void setBlock(bool block = true);

    /** Adds a slot at the bottom of the list of slots.
         * \param slot The slot to add to the list of slots.
         * \return An iterator pointing to the new slot in the list.
         */
    Iterator connect(const QExtFunctionBase &slot);
    /** Adds a slot at the given position into the list of slots.
         * \param iter An iterator indicating the position where @p slot should be inserted.
         * \param slot The slot to add to the list of slots.
         * \return An iterator pointing to the new slot in the list.
         */
    Iterator insert(Iterator iter, const QExtFunctionBase &slot);

    /** Removes the slot at the given position from the list of slots.
         * \param iter An iterator pointing to the slot to be removed.
         * \return An iterator pointing to the slot in the list after the one removed.
         */
    Iterator erase(Iterator iter);

    /** Removes invalid slots from the list of slots.
         */
    void sweep();

    /** Callback that is executed when some slot becomes invalid.
         * This callback is registered in every slot when inserted into
         * the list of slots. It is executed when a slot becomes invalid
         * because of some referred object being destroyed.
         * It either calls m_slotList.erase() directly or defers the execution of
         * erase() to sweep() when the signal is being sended.
         * \param data A local structure, created in insert().
         */
    static void *notify(void *data);

    QAtomicInt m_referenceCount;     // Reference counter. The object is destroyed when @em m_refCount reaches zero.
    QAtomicInt m_executionCount;     // Execution counter. Indicates whether the signal is being sended.
    QAtomicInt m_deferred;            // Indicates whether the execution of sweep() is being deferred.
    SlotList m_slotList;    // The list of slots.
    SelfIteratorList m_selfIteratorList;
};



struct QEXT_CORE_API QExtSignalBase : public QObject
{
    typedef detail::QExtSignalData::Iterator   Iterator;
    typedef std::size_t                         Size;

    QExtSignalBase();
    QExtSignalBase(const QExtSignalBase &other);
    virtual ~QExtSignalBase();

    QExtSignalBase &operator=(const QExtSignalBase &other);
    bool operator==(const QExtSignalBase &other) const;
    bool operator!=(const QExtSignalBase &other) const;

    /** Returns whether the list of slots is empty.
         * \return @p true if the list of slots is empty.
         */
    bool isEmpty() const
    {
        return (!m_data || m_data->isEmpty());
    }

    // Empties the list of slots.
    void clear();

    /** Returns the number of slots in the list.
         * \return The number of slots in the list.
         */
    Size size() const;

    /** Returns whether all slots in the list are blocked.
         * \return @p true if all slots are blocked or the list is empty.
         */
    bool isBlocked() const;

    /** Sets the blocking state of all slots in the list.
         * If @e should_block is @p true then the blocking state is set.
         * Subsequent emissions of the signal don't invoke the functors
         * contained in the slots until unblock() or block() with
         * @e should_block = @p false is called.
         * QExtFunctionBase::setBlock() and QExtFunctionBase::unblock() can change the
         * blocking state of individual slots.
         * \param block Indicates whether the blocking state should be set or unset.
         */
    void setBlock(bool block = true);

    /** Unsets the blocking state of all slots in the list.
         */
    void unblock();


    /** Adds a slot at the end of the list of slots.
         * With connect(), slots can also be added during signal send.
         * In this case, they won't be executed until the next send occurs.
         * \param slot_ The slot to add to the list of slots.
         * \return An iterator pointing to the new slot in the list.
         */
    Iterator connect(const QExtFunctionBase &slot);
    /** Adds a slot at the given position into the list of slots.
         * Note that this function does not work during signal send!
         * \param iter An iterator indicating the position where @e slot should be inserted.
         * \param slot The slot to add to the list of slots.
         * \return An iterator pointing to the new slot in the list.
         */
    Iterator insert(Iterator iter, const QExtFunctionBase &slot);
    /** Removes the slot at the given position from the list of slots.
         * Note that this function does not work during signal send!
         * \param iter An iterator pointing to the slot to be removed.
         * \return An iterator pointing to the slot in the list after the one removed.
         */
    Iterator erase(Iterator iter);
    /** Returns the QExtSignalData object encapsulating the list of slots.
         * \return The QExtSignalData object encapsulating the list of slots.
         */
    detail::QExtSignalData *data() const;

protected:
    // The QExtSignalData object encapsulating the slot list.
    mutable detail::QExtSignalData *m_data;
};


// Exception safe sweeper for cleaning up invalid slots on the slot list.
struct QEXT_CORE_API QExtSignalExecution
{
    /** Increments the reference and execution counter of the parent QExtSignalData object.
         * \param sig The parent QExtSignalData object.
         */
    QExtSignalExecution(const QExtSignalData *signalData);

    // Decrements the reference and execution counter of the parent QExtSignalData object.
    ~QExtSignalExecution();

    // The parent QExtSignalData object.
    QExtSignalData *m_data;
};



template < typename T_slot >
struct QExtFunctionIterator
{
    typedef std::size_t Size;
    typedef T_slot      Slot;
    typedef T_slot      Value;
    typedef T_slot     *Pointer;
    typedef T_slot     &Reference;

    typedef typename detail::QExtSignalData::Iterator Iterator;

    QExtFunctionIterator() {}
    explicit QExtFunctionIterator(const Iterator &iter) : m_iter(iter) {}

    Reference operator*() const
    {
        return static_cast< Reference >(*m_iter);
    }

    Pointer operator->() const
    {
        return &(operator*());
    }

    QExtFunctionIterator &operator++()
    {
        ++m_iter;
        return *this;
    }

    QExtFunctionIterator operator++(int)
    {
        QExtFunctionIterator tmpIter(*this);
        ++m_iter;
        return tmpIter;
    }

    QExtFunctionIterator &operator--()
    {
        --m_iter;
        return *this;
    }

    QExtFunctionIterator operator--(int)
    {
        QExtFunctionIterator tmpIter(*this);
        --m_iter;
        return tmpIter;
    }

    bool operator==(const QExtFunctionIterator &other) const
    {
        return m_iter == other.m_iter;
    }

    bool operator!=(const QExtFunctionIterator &other) const
    {
        return m_iter != other.m_iter;
    }

    Iterator m_iter;
};



template < typename T_slot >
struct QExtFunctionConstIterator
{
    typedef std::size_t     Size;
    typedef T_slot          Slot;
    typedef T_slot          Value;
    typedef const T_slot   *Pointer;
    typedef const T_slot   &Reference;

    typedef typename detail::QExtSignalData::ConstIterator Iterator;

    QExtFunctionConstIterator() {}

    explicit QExtFunctionConstIterator(const Iterator &iter) : m_iter(iter) {}

    Reference operator*() const
    {
        return static_cast< Reference >(*m_iter);
    }

    Pointer operator->() const
    {
        return &(operator*());
    }

    QExtFunctionConstIterator &operator++()
    {
        ++m_iter;
        return *this;
    }

    QExtFunctionConstIterator operator++(int)
    {
        QExtFunctionConstIterator iter(*this);
        ++m_iter;
        return iter;
    }

    QExtFunctionConstIterator &operator--()
    {
        --m_iter;
        return *this;
    }

    QExtFunctionConstIterator operator--(int)
    {
        QExtFunctionConstIterator iter(*this);
        --m_iter;
        return iter;
    }

    bool operator==(const QExtFunctionConstIterator &other) const
    {
        return m_iter == other.m_iter;
    }

    bool operator!=(const QExtFunctionConstIterator &other) const
    {
        return m_iter != other.m_iter;
    }

    Iterator m_iter;
};



/** Temporary slot list used during signal send.
     *  Through evolution this class is slightly misnamed.  It is now
     *  an index into the slot_list passed into it.  It simply keeps track
     *  of where the end of this list was at construction, and pretends that's
     *  the end of your list.  This way you may connect during send without
     *  inadvertently entering an infinite loop, as well as make other
     *  modifications to the slot_list at your own risk.
     */
struct QEXT_CORE_API QExtFunctionTemporaryList
{
    typedef QExtSignalData::SlotList          SlotList;
    typedef QExtSignalData::Iterator          Iterator;
    typedef QExtSignalData::ConstIterator     ConstIterator;

    QExtFunctionTemporaryList(SlotList &slotList) : m_slots(slotList)
    {
        placeholder = m_slots.insert(m_slots.end(), QExtFunctionBase());
    }

    ~QExtFunctionTemporaryList()
    {
        m_slots.erase(placeholder);
    }

    Iterator begin()
    {
        return m_slots.begin();
    }
    Iterator end()
    {
        return placeholder;
    }
    ConstIterator begin() const
    {
        return m_slots.begin();
    }
    ConstIterator end() const
    {
        return placeholder;
    }

private:
    SlotList &m_slots;
    Iterator placeholder;
};



/** list interface for QExtSignal#.
     * QExtFunctionList can be used to iterate over the list of slots that
     * is managed by a signal. Slots can be added or removed from
     * the list while existing iterators stay valid. A slot_list
     * object can be retrieved from the signal's slotList() function.
     *
     * \ingroup signal
     */
template < typename T_slot >
struct QExtFunctionList
{
    typedef T_slot                                  Slot;

    typedef Slot                                   &Reference;
    typedef const Slot                             &ConstReference;

    typedef QExtFunctionIterator< Slot >                  Iterator;
    typedef QExtFunctionConstIterator< Slot >             ConstIterator;

    typedef std::reverse_iterator< Iterator >       ReverseIterator;
    typedef std::reverse_iterator< ConstIterator >  ConstReverseIterator;

    QExtFunctionList() : m_list(QEXT_NULLPTR) {}

    explicit QExtFunctionList(detail::QExtSignalData *list) : m_list(list) {}

    Iterator begin()
    {
        return Iterator(m_list->m_slotList.begin());
    }

    ConstIterator begin() const
    {
        return ConstIterator(m_list->m_slotList.begin());
    }

    Iterator end()
    {
        return Iterator(m_list->m_slotList.end());
    }

    ConstIterator end() const
    {
        return ConstIterator(m_list->m_slotList.end());
    }

    ReverseIterator rbegin()
    {
        return ReverseIterator(this->end());
    }

    ConstReverseIterator rbegin() const
    {
        return ConstReverseIterator(this->end());
    }

    ReverseIterator rend()
    {
        return ReverseIterator(this->begin());
    }

    ConstReverseIterator rend() const
    {
        return ConstReverseIterator(this->begin());
    }

    Reference front()
    {
        return *this->begin();
    }

    ConstReference front() const
    {
        return *this->begin();
    }

    Reference back()
    {
        return *(--this->end());
    }

    ConstReference back() const
    {
        return *(--this->end());
    }

    Iterator insert(Iterator i, const Slot &slot)
    {
        return Iterator(m_list->insert(i.m_iter, static_cast< const QExtFunctionBase & >(slot)));
    }

    void push_front(const Slot &c)
    {
        this->insert(this->begin(), c);
    }

    void push_back(const Slot &c)
    {
        this->insert(this->end(), c);
    }

    Iterator erase(Iterator i)
    {
        return Iterator(m_list->erase(i.m_iter));
    }

    Iterator erase(Iterator first, Iterator last)
    {
        while (first != last)
        {
            first = this->erase(first);
        }
        return last;
    }

    void pop_front()
    {
        this->erase(this->begin());
    }

    void pop_back()
    {
        Iterator iter = this->end();
        this->erase(--iter);
    }

protected:
    detail::QExtSignalData *m_list;
};



/** Special iterator over QExtSignalData's slot list that holds extra data.
     * This iterators is for use in accumulators. operator*() executes
     * the slot. The return value is buffered, so that in an expression
     * like @code a = (*i) * (*i); @endcode the slot is executed only once.
     */
template < typename T_emitter, typename T_result = typename T_emitter::Return >
struct QExtFunctionIteratorBuffer
{
    typedef std::size_t                             Size;

    //These are needed just to make this a proper C++ Iterator,
    //that can be used with standard C++ algorithms.
    typedef T_result                                Value;
    typedef T_result                               &Reference;
    typedef T_result                               *Pointer;

    typedef T_emitter                               Sender;
    typedef T_result                                Return;
    typedef typename T_emitter::Slot                Slot;

    typedef QExtSignalData::ConstIterator             Iterator;

    QExtFunctionIteratorBuffer() : m_sender(QEXT_NULLPTR), m_invoked(false) {}

    QExtFunctionIteratorBuffer(const Iterator &iter, const Sender *sender) : m_iter(iter), m_sender(sender), m_invoked(false) {}

    Return operator*() const
    {
        if (m_iter->isValid() && !m_iter->isBlocked() && (QEXT_ATOMIC_INT_FALSE == m_invoked))
        {
            m_result = (*m_sender)(static_cast< const Slot & >(*m_iter));
            m_invoked = QEXT_ATOMIC_INT_TRUE;
        }
        return m_result;
    }

    QExtFunctionIteratorBuffer &operator++()
    {
        ++m_iter;
        m_invoked = QEXT_ATOMIC_INT_FALSE;
        return *this;
    }

    QExtFunctionIteratorBuffer operator++(int)
    {
        QExtFunctionIteratorBuffer iterBuffer(*this);
        ++m_iter;
        m_invoked = QEXT_ATOMIC_INT_FALSE;
        return iterBuffer;
    }

    QExtFunctionIteratorBuffer &operator--()
    {
        --m_iter;
        m_invoked = QEXT_ATOMIC_INT_FALSE;
        return *this;
    }

    QExtFunctionIteratorBuffer operator--(int)
    {
        QExtFunctionIteratorBuffer iterBuffer(*this);
        --m_iter;
        m_invoked = QEXT_ATOMIC_INT_FALSE;
        return iterBuffer;
    }

    bool operator==(const QExtFunctionIteratorBuffer &other) const
    {
        /* If '!m_sender' the iterators are empty.
             * Unfortunately, empty stl iterators are not equal.
             * We are forcing equality so that 'first==last'
             * in the accumulator's send function yields true. */
        return (!m_sender || (m_iter == other.m_iter));
    }

    bool operator!=(const QExtFunctionIteratorBuffer &other) const
    {
        return (m_sender && (m_iter != other.m_iter));
    }

private:
    Iterator m_iter;
    const Sender *m_sender;
    mutable Return m_result;
    mutable QAtomicInt m_invoked;
};

/** Template specialization of QExtFunctionIteratorBuffer for void return signals.
     */
template < typename T_emitter >
struct QExtFunctionIteratorBuffer< T_emitter, void >
{
    typedef std::size_t                         Size;

    typedef T_emitter                           Sender;
    typedef void                                Return;
    typedef typename T_emitter::Slot            Slot;

    typedef QExtSignalData::ConstIterator         Iterator;

    QExtFunctionIteratorBuffer() : m_sender(QEXT_NULLPTR), m_invoked(false) {}

    QExtFunctionIteratorBuffer(const Iterator &iter, const Sender *sender) : m_iter(iter), m_sender(sender), m_invoked(false) {}

    void operator*() const
    {
        if (m_iter->isValid() && !m_iter->isBlocked() && (QEXT_ATOMIC_INT_FALSE == m_invoked))
        {
            (*m_sender)(static_cast< const Slot & >(*m_iter));
            m_invoked = QEXT_ATOMIC_INT_TRUE;
        }
    }

    QExtFunctionIteratorBuffer &operator++()
    {
        ++m_iter;
        m_invoked = QEXT_ATOMIC_INT_FALSE;
        return *this;
    }

    QExtFunctionIteratorBuffer operator++(int)
    {
        QExtFunctionIteratorBuffer iterBuffer(*this);
        ++m_iter;
        m_invoked = QEXT_ATOMIC_INT_FALSE;
        return iterBuffer;
    }

    QExtFunctionIteratorBuffer &operator--()
    {
        --m_iter;
        m_invoked = QEXT_ATOMIC_INT_FALSE;
        return *this;
    }

    QExtFunctionIteratorBuffer operator--(int)
    {
        QExtFunctionIteratorBuffer iterBuffer(*this);
        --m_iter;
        m_invoked = QEXT_ATOMIC_INT_FALSE;
        return iterBuffer;
    }

    bool operator==(const QExtFunctionIteratorBuffer &other) const
    {
        return m_iter == other.m_iter;
    }

    bool operator!=(const QExtFunctionIteratorBuffer &other) const
    {
        return m_iter != other.m_iter;
    }

private:
    Iterator m_iter;
    const Sender *m_sender;
    mutable QAtomicInt m_invoked;
};

/** Reverse version of QExtFunctionIteratorBuffer. */
template < typename T_emitter, typename T_result = typename T_emitter::Return >
struct QExtFunctionReverseIteratorBuffer
{
    typedef std::size_t                         Size;

    //These are needed just to make this a proper C++ Iterator,
    //that can be used with standard C++ algorithms.
    typedef T_result                            Value;
    typedef T_result                           &Reference;
    typedef T_result                           *Pointer;

    typedef T_emitter                           Sender;
    typedef T_result                            Return;
    typedef typename T_emitter::Slot            Slot;

    typedef QExtSignalData::ConstIterator         Iterator;

    QExtFunctionReverseIteratorBuffer() : m_sender(QEXT_NULLPTR), m_invoked(false) {}

    QExtFunctionReverseIteratorBuffer(const Iterator &iter, const Sender *sender) : m_iter(iter), m_sender(sender), m_invoked(false) {}

    Return operator*() const
    {
        Iterator iter(m_iter);
        --iter;
        if (iter->isValid() && !iter->isBlocked() && (QEXT_ATOMIC_INT_FALSE == m_invoked))
        {
            m_result = (*m_sender)(static_cast< const Slot & >(*iter));
            m_invoked = QEXT_ATOMIC_INT_TRUE;
        }
        return m_result;
    }

    QExtFunctionReverseIteratorBuffer &operator++()
    {
        --m_iter;
        m_invoked = QEXT_ATOMIC_INT_FALSE;
        return *this;
    }

    QExtFunctionReverseIteratorBuffer operator++(int)
    {
        QExtFunctionReverseIteratorBuffer iterBuffer(*this);
        --m_iter;
        m_invoked = QEXT_ATOMIC_INT_FALSE;
        return iterBuffer;
    }

    QExtFunctionReverseIteratorBuffer &operator--()
    {
        ++m_iter;
        m_invoked = QEXT_ATOMIC_INT_FALSE;
        return *this;
    }

    QExtFunctionReverseIteratorBuffer operator--(int)
    {
        QExtFunctionReverseIteratorBuffer iterBuffer(*this);
        ++m_iter;
        m_invoked = QEXT_ATOMIC_INT_FALSE;
        return iterBuffer;
    }

    bool operator==(const QExtFunctionReverseIteratorBuffer &other) const
    {
        /* If '!m_sender' the iterators are empty.
             * Unfortunately, empty stl iterators are not equal.
             * We are forcing equality so that 'first==last'
             * in the accumulator's send function yields true. */
        return (!m_sender || (m_iter == other.m_iter));
    }

    bool operator!=(const QExtFunctionReverseIteratorBuffer &other) const
    {
        return (m_sender && (m_iter != other.m_iter));
    }

private:
    Iterator m_iter;
    const Sender *m_sender;
    mutable Return m_result;
    mutable QAtomicInt m_invoked;
};

/** Template specialization of QExtFunctionReverseIteratorBuffer for void return signals.
     */
template < typename T_emitter >
struct QExtFunctionReverseIteratorBuffer< T_emitter, void >
{
    typedef std::size_t                         Size;
    typedef T_emitter                           Sender;
    typedef void                                Return;
    typedef typename T_emitter::Slot            Slot;

    typedef QExtSignalData::ConstIterator         Iterator;

    QExtFunctionReverseIteratorBuffer() : m_sender(QEXT_NULLPTR), m_invoked(false) {}

    QExtFunctionReverseIteratorBuffer(const Iterator &iter, const Sender *sender) : m_iter(iter), m_sender(sender), m_invoked(false) {}

    void operator*() const
    {
        Iterator iter(m_iter);
        --iter;
        if (iter->isValid() && !iter->isBlocked() && (QEXT_ATOMIC_INT_FALSE == m_invoked))
        {
            (*m_sender)(static_cast< const Slot & >(*iter));
            m_invoked = QEXT_ATOMIC_INT_TRUE;
        }
    }

    QExtFunctionReverseIteratorBuffer &operator++()
    {
        --m_iter;
        m_invoked = QEXT_ATOMIC_INT_FALSE;
        return *this;
    }

    QExtFunctionReverseIteratorBuffer operator++(int)
    {
        QExtFunctionReverseIteratorBuffer iterBuffer(*this);
        --m_iter;
        m_invoked = QEXT_ATOMIC_INT_FALSE;
        return iterBuffer;
    }

    QExtFunctionReverseIteratorBuffer &operator--()
    {
        ++m_iter;
        m_invoked = QEXT_ATOMIC_INT_FALSE;
        return *this;
    }

    QExtFunctionReverseIteratorBuffer operator--(int)
    {
        QExtFunctionReverseIteratorBuffer iterBuffer(*this);
        ++m_iter;
        m_invoked = QEXT_ATOMIC_INT_FALSE;
        return iterBuffer;
    }

    bool operator==(const QExtFunctionReverseIteratorBuffer &other) const
    {
        return m_iter == other.m_iter;
    }

    bool operator!=(const QExtFunctionReverseIteratorBuffer &other) const
    {
        return m_iter != other.m_iter;
    }

private:
    Iterator m_iter;
    const Sender *m_sender;
    mutable QAtomicInt m_invoked;
};



/** Abstracts signal sender.
     * This template implements the send() function of QExtSignal0.
     * Template specializations are available to optimize signal
     * sender when no accumulator is used, for example when the template
     * argument @e T_accumulator is @p QExtNil.
     */
template < typename T_return, typename T_accumulator >
struct QExtSignalSend0
{
    typedef typename T_accumulator::Return                              Return;
    typedef QExtSignalSend0< T_return, T_accumulator >                    Self;
    typedef QExtFunction< T_return >                                          Slot;
    typedef typename Slot::CallFunction                                 CallFunction;
    typedef detail::QExtFunctionIteratorBuffer< Self, T_return >           SlotIteratorBuffer;
    typedef detail::QExtFunctionReverseIteratorBuffer< Self, T_return >    SlotReverseIteratorBuffer;
    typedef QExtSignalData::ConstIterator                                 Iterator;


    QExtSignalSend0() {}

    /** Invokes a slot.
         * \param slot Some slot to invoke.
         * \return The slot's return value.
         */
    T_return operator()(const Slot &slot) const
    {
        return (reinterpret_cast< CallFunction >(slot.m_callFunc))(slot.m_data);
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * \return The accumulated return values of the slot invocations as processed by the accumulator.
         */
    static Return send(QExtSignalData *signalData)
    {
        T_accumulator accumulator;

        if (!signalData)
        {
            return accumulator(SlotIteratorBuffer(), SlotIteratorBuffer());
        }

        QExtSignalExecution execution(signalData);
        QExtFunctionTemporaryList slotList(signalData->m_slotList);

        Self self;
        return accumulator(SlotIteratorBuffer(slotList.begin(), &self), SlotIteratorBuffer(slotList.end(), &self));
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * \return The accumulated return values of the slot invocations as processed by the accumulator.
         */
    static Return sendReverse(QExtSignalData *signalData)
    {
        T_accumulator accumulator;

        if (!signalData)
        {
            return accumulator(SlotIteratorBuffer(), SlotIteratorBuffer());
        }

        QExtSignalExecution execution(signalData);
        QExtFunctionTemporaryList slotList(signalData->m_slotList);

        Self self;
        return accumulator(SlotReverseIteratorBuffer(slotList.end(), &self), SlotReverseIteratorBuffer(slotList.begin(), &self));
    }
};

/** Abstracts signal sender.
     * This template specialization implements an optimized send()
     * function for the case that no accumulator is used.
     */
template < typename T_return >
struct QExtSignalSend0< T_return, QExtNil >
{
    typedef T_return Return;
    typedef QExtSignalSend0< T_return, QExtNil >    Self;
    typedef QExtFunction< T_return >                  Slot;
    typedef typename Slot::CallFunction         CallFunction;
    typedef QExtSignalData::ConstIterator         Iterator;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The return value of the last slot invoked is returned.
         * \return The return value of the last slot invoked.
         */
    static Return send(QExtSignalData *signalData)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return T_return();
        }

        QExtSignalExecution execution(signalData);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (Iterator iter = slotList.begin(); iter != slotList.end(); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    m_result = (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data);
                }
            }
        }

        return m_result;
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The return value of the last slot invoked is returned.
         * \param first An iterator pointing to the first slot in the list.
         * \param last An iterator pointing to the last slot in the list.
         * \return The return value of the last slot invoked.
         */
    static Return sendReverse(QExtSignalData *signalData)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return T_return();
        }

        QExtSignalExecution execution(signalData);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator< QExtSignalData::Iterator > ReverseIterator;
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (ReverseIterator iter = ReverseIterator(slotList.end()); iter != ReverseIterator(slotList.begin()); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    m_result = (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data);
                }
            }
        }

        return m_result;
    }
};

/** Abstracts signal sender.
     * This template specialization implements an optimized send()
     * function for the case that no accumulator is used and the
     * return type is @p void.
     */
template <>
struct QExtSignalSend0< void, QExtNil >
{
    typedef void                                Return;
    typedef QExtSignalSend0< void, QExtNil >    Self;
    typedef QExtSignalData::ConstIterator       Iterator;
    typedef QExtFunction< void >                    Slot;
    typedef Slot::CallFunction         CallFunction;

    static Return send(QExtSignalData *signalData)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return;
        }
        QExtSignalExecution execution(signalData);

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (Iterator iter = slotList.begin(); iter != slotList.end(); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data);
                }
            }
        }
    }

    static Return sendReverse(QExtSignalData *signalData)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return;
        }

        QExtSignalExecution execution(signalData);

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator< QExtSignalData::Iterator > ReverseIterator;
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (ReverseIterator iter = ReverseIterator(slotList.end()); iter != ReverseIterator(slotList.begin()); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data);
                }
            }
        }
    }
};

/** Abstracts signal sender.
     * This template implements the send() function of QExtSignal1.
     * Template specializations are available to optimize signal
     * sender when no accumulator is used, for example when the template
     * argument @e T_accumulator is @p QExtNil.
     */
template < typename T_return, typename T_arg1, typename T_accumulator >
struct QExtSignalSend1
{
    typedef typename T_accumulator::Return                              Return;
    typedef QExtSignalSend1< T_return, T_arg1, T_accumulator >            Self;
    typedef QExtFunction< T_return, T_arg1 >                                  Slot;
    typedef detail::QExtFunctionIteratorBuffer< Self, T_return >           SlotIteratorBuffer;
    typedef detail::QExtFunctionReverseIteratorBuffer< Self, T_return >    SlotReverseIteratorBuffer;
    typedef QExtSignalData::ConstIterator                                 Iterator;

    /** Instantiates the class.
         * The parameters are stored in member variables. operator()() passes
         * the values on to some slot.
         */
    QExtSignalSend1(typename QExtTypeTrait< T_arg1 >::Take arg1) : m_arg1(arg1) {}

    /** Invokes a slot using the buffered parameter values.
         * \param slot Some slot to invoke.
         * \return The slot's return value.
         */
    T_return operator()(const Slot &slot) const
    {
        return (reinterpret_cast< typename Slot::CallFunction >(slot.m_callFunc))(slot.m_data, m_arg1);
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are buffered in a temporary instance of QExtSignalSend1.

         * \param arg1 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations as processed by the accumulator.
         */
    static Return send(QExtSignalData *signalData, typename QExtTypeTrait< T_arg1 >::Take arg1)
    {
        T_accumulator accumulator;

        if (!signalData)
        {
            return accumulator(SlotIteratorBuffer(), SlotIteratorBuffer());
        }

        QExtSignalExecution execution(signalData);
        QExtFunctionTemporaryList slotList(signalData->m_slotList);

        Self self(arg1);
        return accumulator(SlotIteratorBuffer(slotList.begin(), &self), SlotIteratorBuffer(slotList.end(), &self));
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are buffered in a temporary instance of QExtSignalSend1.

         * \param arg1 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations as processed by the accumulator.
         */
    static Return sendReverse(QExtSignalData *signalData, typename QExtTypeTrait< T_arg1 >::Take arg1)
    {
        T_accumulator accumulator;

        if (!signalData)
        {
            return accumulator(SlotIteratorBuffer(), SlotIteratorBuffer());
        }

        QExtSignalExecution execution(signalData);
        QExtFunctionTemporaryList slotList(signalData->m_slotList);

        Self self(arg1);
        return accumulator(SlotReverseIteratorBuffer(slotList.end(), &self), SlotReverseIteratorBuffer(slotList.begin(), &self));
    }

    typename QExtTypeTrait< T_arg1 >::Take m_arg1;
};

/** Abstracts signal sender.
     * This template specialization implements an optimized send()
     * function for the case that no accumulator is used.
     */
template < typename T_return, typename T_arg1 >
struct QExtSignalSend1< T_return, T_arg1, QExtNil >
{
    typedef T_return                                    Return;
    typedef QExtSignalSend1< T_return, T_arg1, QExtNil >    Self;
    typedef QExtFunction< T_return, T_arg1 >                  Slot;
    typedef QExtSignalData::ConstIterator                 Iterator;
    typedef typename Slot::CallFunction                 CallFunction;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are passed directly on to the slots.
         * The return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \return The return value of the last valid slot invoked.
         */
    static Return send(QExtSignalData *signalData, typename QExtTypeTrait< T_arg1 >::Take arg1)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return T_return();
        }

        QExtSignalExecution execution(signalData);
        T_return result = T_return();
        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (Iterator iter = slotList.begin(); iter != slotList.end(); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    result = (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1);
                }
            }
        }

        return result;
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are passed directly on to the slots.
         * The return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \return The return value of the last slot invoked.
         */
    static Return sendReverse(QExtSignalData *signalData, typename QExtTypeTrait< T_arg1 >::Take arg1)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return T_return();
        }

        QExtSignalExecution execution(signalData);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator< QExtSignalData::Iterator > ReverseIterator;
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (ReverseIterator iter = ReverseIterator(slotList.end()); iter != ReverseIterator(slotList.begin()); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    m_result = (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1);
                }
            }
        }

        return m_result;
    }
};

/** Abstracts signal sender.
     * This template specialization implements an optimized send()
     * function for the case that no accumulator is used and the
     * return type is @p void.
     */
template < typename T_arg1 >
struct QExtSignalSend1< void, T_arg1, QExtNil >
{
    typedef void                                    Return;
    typedef QExtSignalSend1< void, T_arg1, QExtNil >    Self;
    typedef QExtFunction< void, T_arg1 >                  Slot;
    typedef QExtSignalData::ConstIterator             Iterator;
    typedef typename Slot::CallFunction             CallFunction;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are passed directly on to the slots.
         * \param arg1 Argument to be passed on to the slots.
         */
    static Return send(QExtSignalData *signalData, typename QExtTypeTrait< T_arg1 >::Take arg1)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return;
        }
        QExtSignalExecution execution(signalData);

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (Iterator iter = slotList.begin(); iter != slotList.end(); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1);
                }
            }
        }
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are passed directly on to the slots.
         * \param arg1 Argument to be passed on to the slots.
         */
    static Return sendReverse(QExtSignalData *signalData, typename QExtTypeTrait< T_arg1 >::Take arg1)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return;
        }
        QExtSignalExecution execution(signalData);

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator< QExtSignalData::Iterator > ReverseIterator;
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (ReverseIterator iter = ReverseIterator(slotList.end()); iter != ReverseIterator(slotList.begin()); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1);
                }
            }
        }
    }
};

/** Abstracts signal sender.
     * This template implements the send() function of QExtSignal2.
     * Template specializations are available to optimize signal
     * sender when no accumulator is used, for example when the template
     * argument @e T_accumulator is @p QExtNil.
     */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_accumulator >
struct QExtSignalSend2
{
    typedef typename T_accumulator::Return                              Return;
    typedef QExtSignalSend2< T_return, T_arg1, T_arg2, T_accumulator >    Self;
    typedef QExtFunction< T_return, T_arg1, T_arg2 >                          Slot;
    typedef detail::QExtFunctionIteratorBuffer< Self, T_return >           SlotIteratorBuffer;
    typedef detail::QExtFunctionReverseIteratorBuffer< Self, T_return >    SlotReverseIteratorBuffer;
    typedef QExtSignalData::ConstIterator                                 Iterator;

    /** Instantiates the class.
         * The parameters are stored in member variables. operator()() passes
         * the values on to some slot.
         */
    QExtSignalSend2(typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2) : m_arg1(arg1), m_arg2(arg2) {}

    /** Invokes a slot using the buffered parameter values.
         * \param slot Some slot to invoke.
         * \return The slot's return value.
         */
    T_return operator()(const Slot &slot) const
    {
        return (reinterpret_cast< typename Slot::CallFunction >(slot.m_slotRep->m_callFunc))(slot.m_slotRep, m_arg1, m_arg2);
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are buffered in a temporary instance of QExtSignalSend2.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations as processed by the accumulator.
         */
    static Return send(QExtSignalData *signalData, typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2)
    {
        T_accumulator accumulator;

        if (!signalData)
        {
            return accumulator(SlotIteratorBuffer(), SlotIteratorBuffer());
        }

        QExtSignalExecution execution(signalData);
        QExtFunctionTemporaryList slotList(signalData->m_slotList);

        Self self(arg1, arg2);
        return accumulator(SlotIteratorBuffer(slotList.begin(), &self), SlotIteratorBuffer(slotList.end(), &self));
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are buffered in a temporary instance of QExtSignalSend2.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations as processed by the accumulator.
         */
    static Return sendReverse(QExtSignalData *signalData, typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2)
    {
        T_accumulator accumulator;

        if (!signalData)
        {
            return accumulator(SlotIteratorBuffer(), SlotIteratorBuffer());
        }

        QExtSignalExecution execution(signalData);
        QExtFunctionTemporaryList slotList(signalData->m_slotList);

        Self self(arg1, arg2);
        return accumulator(SlotReverseIteratorBuffer(slotList.end(), &self), SlotReverseIteratorBuffer(slotList.begin(), &self));
    }

    typename QExtTypeTrait< T_arg1 >::Take m_arg1;
    typename QExtTypeTrait< T_arg2 >::Take m_arg2;
};

/** Abstracts signal sender.
     * This template specialization implements an optimized send()
     * function for the case that no accumulator is used.
     */
template < typename T_return, typename T_arg1, typename T_arg2 >
struct QExtSignalSend2< T_return, T_arg1, T_arg2, QExtNil >
{
    typedef T_return                                            Return;
    typedef QExtSignalSend2< T_return, T_arg1, T_arg2, QExtNil >    Self;
    typedef QExtFunction< T_return, T_arg1, T_arg2 >                  Slot;
    typedef QExtSignalData::ConstIterator                         Iterator;
    typedef typename Slot::CallFunction                         CallFunction;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are passed directly on to the slots.
         * The return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \return The return value of the last slot invoked.
         */
    static Return send(QExtSignalData *signalData, typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return T_return();
        }

        QExtSignalExecution execution(signalData);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (Iterator iter = slotList.begin(); iter != slotList.end(); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    m_result = (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2);
                }
            }
        }

        return m_result;
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are passed directly on to the slots.
         * The return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \return The return value of the last slot invoked.
         */
    static Return sendReverse(QExtSignalData *signalData, typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return T_return();
        }

        QExtSignalExecution execution(signalData);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator< QExtSignalData::Iterator > ReverseIterator;
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (ReverseIterator iter = ReverseIterator(slotList.end()); iter != ReverseIterator(slotList.begin()); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    m_result = (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2);
                }
            }
        }

        return m_result;
    }
};

/** Abstracts signal sender.
     * This template specialization implements an optimized send()
     * function for the case that no accumulator is used and the
     * return type is @p void.
     */
template < typename T_arg1, typename T_arg2 >
struct QExtSignalSend2< void, T_arg1, T_arg2, QExtNil >
{
    typedef void                                            Return;
    typedef QExtSignalSend2< void, T_arg1, T_arg2, QExtNil >    Self;
    typedef QExtFunction< void, T_arg1, T_arg2 >                  Slot;
    typedef QExtSignalData::ConstIterator                     Iterator;
    typedef typename Slot::CallFunction                     CallFunction;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are passed directly on to the slots.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         */
    static Return send(QExtSignalData *signalData, typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return;
        }
        QExtSignalExecution execution(signalData);

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (Iterator iter = slotList.begin(); iter != slotList.end(); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2);
                }
            }
        }
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are passed directly on to the slots.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         */
    static Return sendReverse(QExtSignalData *signalData, typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return;
        }
        QExtSignalExecution execution(signalData);

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator< QExtSignalData::Iterator > ReverseIterator;
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (ReverseIterator iter = ReverseIterator(slotList.end()); iter != ReverseIterator(slotList.begin()); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2);
                }
            }
        }
    }
};

/** Abstracts signal sender.
     * This template implements the send() function of QExtSignal3.
     * Template specializations are available to optimize signal
     * sender when no accumulator is used, for example when the template
     * argument @e T_accumulator is @p QExtNil.
     */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_accumulator >
struct QExtSignalSend3
{
    typedef typename T_accumulator::Return                                      Return;
    typedef QExtSignalSend3< T_return, T_arg1, T_arg2, T_arg3, T_accumulator >    Self;
    typedef QExtFunction< T_return, T_arg1, T_arg2, T_arg3 >                          Slot;
    typedef detail::QExtFunctionIteratorBuffer< Self, T_return >                   SlotIteratorBuffer;
    typedef detail::QExtFunctionReverseIteratorBuffer< Self, T_return >            SlotReverseIteratorBuffer;
    typedef QExtSignalData::ConstIterator                                         Iterator;

    /** Instantiates the class.
         * The parameters are stored in member variables. operator()() passes
         * the values on to some slot.
         */
    QExtSignalSend3(typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2, typename QExtTypeTrait< T_arg3 >::Take arg3)
        : m_arg1(arg1), m_arg2(arg2), m_arg3(arg3)
    {
    }

    /** Invokes a slot using the buffered parameter values.
         * \param slot Some slot to invoke.
         * \return The slot's return value.
         */
    T_return operator()(const Slot &slot) const
    {
        return (reinterpret_cast< typename Slot::CallFunction >(slot.m_callFunc))(slot.m_data, m_arg1, m_arg2, m_arg3);
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are buffered in a temporary instance of QExtSignalSend3.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations as processed by the accumulator.
         */
    static Return send(
            QExtSignalData *signalData, typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2, typename QExtTypeTrait< T_arg3 >::Take arg3)
    {
        T_accumulator accumulator;

        if (!signalData)
        {
            return accumulator(SlotIteratorBuffer(), SlotIteratorBuffer());
        }

        QExtSignalExecution execution(signalData);
        QExtFunctionTemporaryList slotList(signalData->m_slotList);

        Self self(arg1, arg2, arg3);
        return accumulator(SlotIteratorBuffer(slotList.begin(), &self), SlotIteratorBuffer(slotList.end(), &self));
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are buffered in a temporary instance of QExtSignalSend3.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations as processed by the accumulator.
         */
    static Return sendReverse(
            QExtSignalData *signalData, typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2, typename QExtTypeTrait< T_arg3 >::Take arg3)
    {
        T_accumulator accumulator;

        if (!signalData)
        {
            return accumulator(SlotIteratorBuffer(), SlotIteratorBuffer());
        }

        QExtSignalExecution execution(signalData);
        QExtFunctionTemporaryList slotList(signalData->m_slotList);

        Self self(arg1, arg2, arg3);
        return accumulator(SlotReverseIteratorBuffer(slotList.end(), &self), SlotReverseIteratorBuffer(slotList.begin(), &self));
    }

    typename QExtTypeTrait< T_arg1 >::Take m_arg1;
    typename QExtTypeTrait< T_arg2 >::Take m_arg2;
    typename QExtTypeTrait< T_arg3 >::Take m_arg3;
};

/** Abstracts signal sender.
     * This template specialization implements an optimized send()
     * function for the case that no accumulator is used.
     */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
struct QExtSignalSend3< T_return, T_arg1, T_arg2, T_arg3, QExtNil >
{
    typedef T_return                                                    Return;
    typedef QExtSignalSend3< T_return, T_arg1, T_arg2, T_arg3, QExtNil >    Self;
    typedef QExtFunction< T_return, T_arg1, T_arg2, T_arg3 >                  Slot;
    typedef QExtSignalData::ConstIterator                                 Iterator;
    typedef typename Slot::CallFunction                                 CallFunction;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are passed directly on to the slots.
         * The return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \return The return value of the last slot invoked.
         */
    static Return send(
            QExtSignalData *signalData, typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2, typename QExtTypeTrait< T_arg3 >::Take arg3)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return T_return();
        }

        QExtSignalExecution execution(signalData);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (Iterator iter = slotList.begin(); iter != slotList.end(); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    m_result = (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3);
                }
            }
        }

        return m_result;
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are passed directly on to the slots.
         * The return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \return The return value of the last slot invoked.
         */
    static Return sendReverse(
            QExtSignalData *signalData, typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2, typename QExtTypeTrait< T_arg3 >::Take arg3)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return T_return();
        }

        QExtSignalExecution execution(signalData);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator< QExtSignalData::Iterator > ReverseIterator;
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (ReverseIterator iter = ReverseIterator(slotList.end()); iter != ReverseIterator(slotList.begin()); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    m_result = (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3);
                }
            }
        }

        return m_result;
    }
};

/** Abstracts signal sender.
     * This template specialization implements an optimized send()
     * function for the case that no accumulator is used and the
     * return type is @p void.
     */
template < typename T_arg1, typename T_arg2, typename T_arg3 >
struct QExtSignalSend3< void, T_arg1, T_arg2, T_arg3, QExtNil >
{
    typedef void                                                    Return;
    typedef QExtSignalSend3< void, T_arg1, T_arg2, T_arg3, QExtNil >    Self;
    typedef QExtFunction< void, T_arg1, T_arg2, T_arg3 >                  Slot;
    typedef QExtSignalData::ConstIterator                             Iterator;
    typedef typename Slot::CallFunction                             CallFunction;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are passed directly on to the slots.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         */
    static Return send(
            QExtSignalData *signalData, typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2, typename QExtTypeTrait< T_arg3 >::Take arg3)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return;
        }

        QExtSignalExecution execution(signalData);

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (Iterator iter = slotList.begin(); iter != slotList.end(); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3);
                }
            }
        }
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are passed directly on to the slots.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         */
    static Return sendReverse(
            QExtSignalData *signalData, typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2, typename QExtTypeTrait< T_arg3 >::Take arg3)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return;
        }
        QExtSignalExecution execution(signalData);

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            typedef std::reverse_iterator< QExtSignalData::Iterator > ReverseIterator;
            for (ReverseIterator iter = ReverseIterator(slotList.end()); iter != ReverseIterator(slotList.begin()); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3);
                }
            }
        }
    }
};

/** Abstracts signal sender.
     * This template implements the send() function of QExtSignal4.
     * Template specializations are available to optimize signal
     * sender when no accumulator is used, for example when the template
     * argument @e T_accumulator is @p QExtNil.
     */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_accumulator >
struct QExtSignalSend4
{
    typedef typename T_accumulator::Return                                              Return;
    typedef QExtSignalSend4< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_accumulator >    Self;
    typedef QExtFunction< T_return, T_arg1, T_arg2, T_arg3, T_arg4 >                          Slot;
    typedef detail::QExtFunctionIteratorBuffer< Self, T_return >                           SlotIteratorBuffer;
    typedef detail::QExtFunctionReverseIteratorBuffer< Self, T_return >                    SlotReverseIteratorBuffer;
    typedef QExtSignalData::ConstIterator                                                 Iterator;

    /** Instantiates the class.
         * The parameters are stored in member variables. operator()() passes
         * the values on to some slot.
         */
    QExtSignalSend4(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4)
        : m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4)
    {
    }

    /** Invokes a slot using the buffered parameter values.
         * \param slot Some slot to invoke.
         * \return The slot's return value.
         */
    T_return operator()(const Slot &slot) const
    {
        return (reinterpret_cast< typename Slot::CallFunction >(slot.m_slotRep->m_callFunc))(slot.m_slotRep, m_arg1, m_arg2, m_arg3, m_arg4);
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are buffered in a temporary instance of QExtSignalSend4.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations as processed by the accumulator.
         */
    static Return send(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4)
    {
        T_accumulator accumulator;

        if (!signalData)
        {
            return accumulator(SlotIteratorBuffer(), SlotIteratorBuffer());
        }

        QExtSignalExecution execution(signalData);
        QExtFunctionTemporaryList slotList(signalData->m_slotList);

        Self self(arg1, arg2, arg3, arg4);
        return accumulator(SlotIteratorBuffer(slotList.begin(), &self), SlotIteratorBuffer(slotList.end(), &self));
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are buffered in a temporary instance of QExtSignalSend4.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations as processed by the accumulator.
         */
    static Return sendReverse(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4)
    {
        T_accumulator accumulator;

        if (!signalData)
        {
            return accumulator(SlotIteratorBuffer(), SlotIteratorBuffer());
        }

        QExtSignalExecution execution(signalData);
        QExtFunctionTemporaryList slotList(signalData->m_slotList);

        Self self(arg1, arg2, arg3, arg4);
        return accumulator(SlotReverseIteratorBuffer(slotList.end(), &self), SlotReverseIteratorBuffer(slotList.begin(), &self));
    }

    typename QExtTypeTrait< T_arg1 >::Take m_arg1;
    typename QExtTypeTrait< T_arg2 >::Take m_arg2;
    typename QExtTypeTrait< T_arg3 >::Take m_arg3;
    typename QExtTypeTrait< T_arg4 >::Take m_arg4;
};

/** Abstracts signal sender.
     * This template specialization implements an optimized send()
     * function for the case that no accumulator is used.
     */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
struct QExtSignalSend4< T_return, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil >
{
    typedef T_return                                                            Return;
    typedef QExtSignalSend4< T_return, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil >    Self;
    typedef QExtFunction< T_return, T_arg1, T_arg2, T_arg3, T_arg4 >                  Slot;
    typedef QExtSignalData::ConstIterator                                         Iterator;
    typedef typename Slot::CallFunction                                         CallFunction;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are passed directly on to the slots.
         * The return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \return The return value of the last slot invoked.
         */
    static Return send(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return T_return();
        }

        QExtSignalExecution execution(signalData);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (Iterator iter = slotList.begin(); iter != slotList.end(); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    m_result = (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3, arg4);
                }
            }
        }

        return m_result;
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are passed directly on to the slots.
         * The return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \return The return value of the last slot invoked.
         */
    static Return sendReverse(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return T_return();
        }

        QExtSignalExecution execution(signalData);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator< QExtSignalData::Iterator > ReverseIterator;
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (ReverseIterator iter = ReverseIterator(slotList.end()); iter != ReverseIterator(slotList.begin()); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    m_result = (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3, arg4);
                }
            }
        }

        return m_result;
    }
};

/** Abstracts signal sender.
     * This template specialization implements an optimized send()
     * function for the case that no accumulator is used and the
     * return type is @p void.
     */
template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
struct QExtSignalSend4< void, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil >
{
    typedef void                                                            Return;
    typedef QExtSignalSend4< void, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil >    Self;
    typedef QExtFunction< void, T_arg1, T_arg2, T_arg3, T_arg4 >                  Slot;
    typedef QExtSignalData::ConstIterator                                     Iterator;
    typedef typename Slot::CallFunction                                     CallFunction;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are passed directly on to the slots.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         */
    static Return send(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return;
        }
        QExtSignalExecution execution(signalData);

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (Iterator iter = slotList.begin(); iter != slotList.end(); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3, arg4);
                }
            }
        }
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are passed directly on to the slots.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         */
    static Return sendReverse(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return;
        }
        QExtSignalExecution execution(signalData);

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator< QExtSignalData::Iterator > ReverseIterator;
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (ReverseIterator iter = ReverseIterator(slotList.end()); iter != ReverseIterator(slotList.begin()); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3, arg4);
                }
            }
        }
    }
};

/** Abstracts signal sender.
     * This template implements the send() function of QExtSignal5.
     * Template specializations are available to optimize signal
     * sender when no accumulator is used, for example when the template
     * argument @e T_accumulator is @p QExtNil.
     */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_accumulator >
struct QExtSignalSend5
{
    typedef typename T_accumulator::Return                                                      Return;
    typedef QExtSignalSend5< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_accumulator >    Self;
    typedef QExtFunction< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >                          Slot;
    typedef detail::QExtFunctionIteratorBuffer< Self, T_return >                                   SlotIteratorBuffer;
    typedef detail::QExtFunctionReverseIteratorBuffer< Self, T_return >                            SlotReverseIteratorBuffer;
    typedef QExtSignalData::ConstIterator                                                         Iterator;

    /** Instantiates the class.
         * The parameters are stored in member variables. operator()() passes
         * the values on to some slot.
         */
    QExtSignalSend5(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5)
        : m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5)
    {
    }

    /** Invokes a slot using the buffered parameter values.
         * \param slot Some slot to invoke.
         * \return The slot's return value.
         */
    T_return operator()(const Slot &slot) const
    {
        return (reinterpret_cast< typename Slot::CallFunction >(slot.m_callFunc))(slot.m_data, m_arg1, m_arg2, m_arg3, m_arg4, m_arg5);
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are buffered in a temporary instance of QExtSignalSend5.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations as processed by the accumulator.
         */
    static Return send(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5)
    {
        T_accumulator accumulator;

        if (!signalData)
        {
            return accumulator(SlotIteratorBuffer(), SlotIteratorBuffer());
        }

        QExtSignalExecution execution(signalData);
        QExtFunctionTemporaryList slotList(signalData->m_slotList);

        Self self(arg1, arg2, arg3, arg4, arg5);
        return accumulator(SlotIteratorBuffer(slotList.begin(), &self), SlotIteratorBuffer(slotList.end(), &self));
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are buffered in a temporary instance of QExtSignalSend5.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations as processed by the accumulator.
         */
    static Return sendReverse(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5)
    {
        T_accumulator accumulator;

        if (!signalData)
        {
            return accumulator(SlotIteratorBuffer(), SlotIteratorBuffer());
        }

        QExtSignalExecution execution(signalData);
        QExtFunctionTemporaryList slotList(signalData->m_slotList);

        Self self(arg1, arg2, arg3, arg4, arg5);
        return accumulator(SlotReverseIteratorBuffer(slotList.end(), &self), SlotReverseIteratorBuffer(slotList.begin(), &self));
    }

    typename QExtTypeTrait< T_arg1 >::Take m_arg1;
    typename QExtTypeTrait< T_arg2 >::Take m_arg2;
    typename QExtTypeTrait< T_arg3 >::Take m_arg3;
    typename QExtTypeTrait< T_arg4 >::Take m_arg4;
    typename QExtTypeTrait< T_arg5 >::Take m_arg5;
};

/** Abstracts signal sender.
     * This template specialization implements an optimized send()
     * function for the case that no accumulator is used.
     */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
struct QExtSignalSend5< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil >
{
    typedef T_return                                                                    Return;
    typedef QExtSignalSend5< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil >    Self;
    typedef QExtFunction< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >                  Slot;
    typedef QExtSignalData::ConstIterator                                                 Iterator;
    typedef typename Slot::CallFunction                                                 CallFunction;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are passed directly on to the slots.
         * The return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \return The return value of the last slot invoked.
         */
    static Return send(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return T_return();
        }

        QExtSignalExecution execution(signalData);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (Iterator iter = slotList.begin(); iter != slotList.end(); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    m_result = (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3, arg4, arg5);
                }
            }
        }

        return m_result;
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are passed directly on to the slots.
         * The return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \return The return value of the last slot invoked.
         */
    static Return sendReverse(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return T_return();
        }

        QExtSignalExecution execution(signalData);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator< QExtSignalData::Iterator > ReverseIterator;
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (ReverseIterator iter = ReverseIterator(slotList.end()); iter != ReverseIterator(slotList.begin()); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    m_result = (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3, arg4, arg5);
                }
            }
        }

        return m_result;
    }
};

/** Abstracts signal sender.
     * This template specialization implements an optimized send()
     * function for the case that no accumulator is used and the
     * return type is @p void.
     */
template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
struct QExtSignalSend5< void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil >
{
    typedef void                                                                    Return;
    typedef QExtSignalSend5< void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil >    Self;
    typedef QExtFunction< void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >                  Slot;
    typedef QExtSignalData::ConstIterator                                             Iterator;
    typedef typename Slot::CallFunction                                             CallFunction;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are passed directly on to the slots.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         */
    static Return send(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return;
        }
        QExtSignalExecution execution(signalData);

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (Iterator iter = slotList.begin(); iter != slotList.end(); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3, arg4, arg5);
                }
            }
        }
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are passed directly on to the slots.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         */
    static Return sendReverse(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return;
        }
        QExtSignalExecution execution(signalData);

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QExtFunctionTemporaryList slotList(signalData->m_slotList);

            typedef std::reverse_iterator< QExtSignalData::Iterator > ReverseIterator;
            for (ReverseIterator iter = ReverseIterator(slotList.end()); iter != ReverseIterator(slotList.begin()); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3, arg4, arg5);
                }
            }
        }
    }
};

/** Abstracts signal sender.
     * This template implements the send() function of QExtSignal6.
     * Template specializations are available to optimize signal
     * sender when no accumulator is used, for example when the template
     * argument @e T_accumulator is @p QExtNil.
     */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_accumulator >
struct QExtSignalSend6
{
    typedef typename T_accumulator::Return                                                              Return;
    typedef QExtSignalSend6< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_accumulator >    Self;
    typedef QExtFunction< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >                          Slot;
    typedef detail::QExtFunctionIteratorBuffer< Self, T_return >                                           SlotIteratorBuffer;
    typedef detail::QExtFunctionReverseIteratorBuffer< Self, T_return >                                    SlotReverseIteratorBuffer;
    typedef QExtSignalData::ConstIterator                                                                 Iterator;

    /** Instantiates the class.
         * The parameters are stored in member variables. operator()() passes
         * the values on to some slot.
         */
    QExtSignalSend6(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6)
        : m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5), m_arg6(arg6)
    {
    }

    /** Invokes a slot using the buffered parameter values.
         * \param slot Some slot to invoke.
         * \return The slot's return value.
         */
    T_return operator()(const Slot &slot) const
    {
        return (reinterpret_cast< typename Slot::CallFunction >(slot.m_callFunc))(slot.m_data, m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6);
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are buffered in a temporary instance of QExtSignalSend6.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \param arg6 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations as processed by the accumulator.
         */
    static Return send(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6)
    {
        T_accumulator accumulator;

        if (!signalData)
        {
            return accumulator(SlotIteratorBuffer(), SlotIteratorBuffer());
        }

        QExtSignalExecution execution(signalData);
        QExtFunctionTemporaryList slotList(signalData->m_slotList);

        Self self(arg1, arg2, arg3, arg4, arg5, arg6);
        return accumulator(SlotIteratorBuffer(slotList.begin(), &self), SlotIteratorBuffer(slotList.end(), &self));
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are buffered in a temporary instance of QExtSignalSend6.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \param arg6 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations as processed by the accumulator.
         */
    static Return sendReverse(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6)
    {
        T_accumulator accumulator;

        if (!signalData)
        {
            return accumulator(SlotIteratorBuffer(), SlotIteratorBuffer());
        }

        QExtSignalExecution execution(signalData);
        QExtFunctionTemporaryList slotList(signalData->m_slotList);

        Self self(arg1, arg2, arg3, arg4, arg5, arg6);
        return accumulator(SlotReverseIteratorBuffer(slotList.end(), &self), SlotReverseIteratorBuffer(slotList.begin(), &self));
    }

    typename QExtTypeTrait< T_arg1 >::Take m_arg1;
    typename QExtTypeTrait< T_arg2 >::Take m_arg2;
    typename QExtTypeTrait< T_arg3 >::Take m_arg3;
    typename QExtTypeTrait< T_arg4 >::Take m_arg4;
    typename QExtTypeTrait< T_arg5 >::Take m_arg5;
    typename QExtTypeTrait< T_arg6 >::Take m_arg6;
};

/** Abstracts signal sender.
     * This template specialization implements an optimized send()
     * function for the case that no accumulator is used.
     */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
struct QExtSignalSend6< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil >
{
    typedef T_return                                                                            Return;
    typedef QExtSignalSend6< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil >    Self;
    typedef QExtFunction< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >                  Slot;
    typedef QExtSignalData::ConstIterator                                                         Iterator;
    typedef typename Slot::CallFunction                                                         CallFunction;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are passed directly on to the slots.
         * The return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \param arg6 Argument to be passed on to the slots.
         * \return The return value of the last slot invoked.
         */
    static Return send(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return T_return();
        }

        QExtSignalExecution execution(signalData);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (Iterator iter = slotList.begin(); iter != slotList.end(); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    m_result = (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3, arg4, arg5, arg6);
                }
            }
        }

        return m_result;
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are passed directly on to the slots.
         * The return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \param arg6 Argument to be passed on to the slots.
         * \return The return value of the last slot invoked.
         */
    static Return sendReverse(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return T_return();
        }

        QExtSignalExecution execution(signalData);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator< QExtSignalData::Iterator > ReverseIterator;

            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (ReverseIterator iter = ReverseIterator(slotList.end()); iter != ReverseIterator(slotList.begin()); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    m_result = (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3, arg4, arg5, arg6);
                }
            }
        }

        return m_result;
    }
};

/** Abstracts signal sender.
     * This template specialization implements an optimized send()
     * function for the case that no accumulator is used and the
     * return type is @p void.
     */
template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
struct QExtSignalSend6< void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil >
{
    typedef void                                                                            Return;
    typedef QExtSignalSend6< void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil >    Self;
    typedef QExtFunction< void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >                  Slot;
    typedef QExtSignalData::ConstIterator                                                     Iterator;
    typedef typename Slot::CallFunction                                                     CallFunction;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are passed directly on to the slots.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \param arg6 Argument to be passed on to the slots.
         */
    static Return send(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return;
        }
        QExtSignalExecution execution(signalData);

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (Iterator iter = slotList.begin(); iter != slotList.end(); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3, arg4, arg5, arg6);
                }
            }
        }
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are passed directly on to the slots.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \param arg6 Argument to be passed on to the slots.
         */
    static Return sendReverse(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return;
        }
        QExtSignalExecution execution(signalData);

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator< QExtSignalData::Iterator > ReverseIterator;
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (ReverseIterator iter = ReverseIterator(slotList.end()); iter != ReverseIterator(slotList.begin()); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3, arg4, arg5, arg6);
                }
            }
        }
    }
};

/** Abstracts signal sender.
     * This template implements the send() function of QExtSignal7.
     * Template specializations are available to optimize signal
     * sender when no accumulator is used, for example when the template
     * argument @e T_accumulator is @p QExtNil.
     */
template <
        typename T_return,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7,
        typename T_accumulator >
struct QExtSignalSend7
{
    typedef typename T_accumulator::Return                                                                      Return;
    typedef QExtSignalSend7< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_accumulator >    Self;
    typedef QExtFunction< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >                          Slot;
    typedef detail::QExtFunctionIteratorBuffer< Self, T_return >                                                   SlotIteratorBuffer;
    typedef detail::QExtFunctionReverseIteratorBuffer< Self, T_return >                                            SlotReverseIteratorBuffer;
    typedef QExtSignalData::ConstIterator                                                                         Iterator;

    /** Instantiates the class.
         * The parameters are stored in member variables. operator()() passes
         * the values on to some slot.
         */
    QExtSignalSend7(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6,
            typename QExtTypeTrait< T_arg7 >::Take arg7)
        : m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5), m_arg6(arg6), m_arg7(arg7)
    {
    }

    /** Invokes a slot using the buffered parameter values.
         * \param slot Some slot to invoke.
         * \return The slot's return value.
         */
    T_return operator()(const Slot &slot) const
    {
        return (reinterpret_cast< typename Slot::CallFunction >(slot.m_slotRep->m_callFunc))(
                    slot.m_slotRep, m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7);
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are buffered in a temporary instance of QExtSignalSend7.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \param arg6 Argument to be passed on to the slots.
         * \param arg7 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations as processed by the accumulator.
         */
    static Return send(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6,
            typename QExtTypeTrait< T_arg7 >::Take arg7)
    {
        T_accumulator accumulator;

        if (!signalData)
        {
            return accumulator(SlotIteratorBuffer(), SlotIteratorBuffer());
        }

        QExtSignalExecution execution(signalData);
        QExtFunctionTemporaryList slotList(signalData->m_slotList);

        Self self(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        return accumulator(SlotIteratorBuffer(slotList.begin(), &self), SlotIteratorBuffer(slotList.end(), &self));
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are buffered in a temporary instance of QExtSignalSend7.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \param arg6 Argument to be passed on to the slots.
         * \param arg7 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations as processed by the accumulator.
         */
    static Return sendReverse(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6,
            typename QExtTypeTrait< T_arg7 >::Take arg7)
    {
        T_accumulator accumulator;

        if (!signalData)
        {
            return accumulator(SlotIteratorBuffer(), SlotIteratorBuffer());
        }

        QExtSignalExecution execution(signalData);
        QExtFunctionTemporaryList slotList(signalData->m_slotList);

        Self self(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        return accumulator(SlotReverseIteratorBuffer(slotList.end(), &self), SlotReverseIteratorBuffer(slotList.begin(), &self));
    }

    typename QExtTypeTrait< T_arg1 >::Take m_arg1;
    typename QExtTypeTrait< T_arg2 >::Take m_arg2;
    typename QExtTypeTrait< T_arg3 >::Take m_arg3;
    typename QExtTypeTrait< T_arg4 >::Take m_arg4;
    typename QExtTypeTrait< T_arg5 >::Take m_arg5;
    typename QExtTypeTrait< T_arg6 >::Take m_arg6;
    typename QExtTypeTrait< T_arg7 >::Take m_arg7;
};

/** Abstracts signal sender.
     * This template specialization implements an optimized send()
     * function for the case that no accumulator is used.
     */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
struct QExtSignalSend7< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, QExtNil >
{
    typedef T_return                                                                                    Return;
    typedef QExtSignalSend7< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, QExtNil >    Self;
    typedef QExtFunction< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >                  Slot;
    typedef QExtSignalData::ConstIterator                                                                 Iterator;
    typedef typename Slot::CallFunction                                                                 CallFunction;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are passed directly on to the slots.
         * The return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \param arg6 Argument to be passed on to the slots.
         * \param arg7 Argument to be passed on to the slots.
         * \return The return value of the last slot invoked.
         */
    static Return send(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6,
            typename QExtTypeTrait< T_arg7 >::Take arg7)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return T_return();
        }

        QExtSignalExecution execution(signalData);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (Iterator iter = slotList.begin(); iter != slotList.end(); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    m_result = (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
                }
            }
        }

        return m_result;
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are passed directly on to the slots.
         * The return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \param arg6 Argument to be passed on to the slots.
         * \param arg7 Argument to be passed on to the slots.
         * \return The return value of the last slot invoked.
         */
    static Return sendReverse(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6,
            typename QExtTypeTrait< T_arg7 >::Take arg7)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return T_return();
        }

        QExtSignalExecution execution(signalData);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator< QExtSignalData::Iterator > ReverseIterator;
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (ReverseIterator iter = ReverseIterator(slotList.end()); iter != ReverseIterator(slotList.begin()); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    m_result = (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
                }
            }
        }

        return m_result;
    }
};

/** Abstracts signal sender.
     * This template specialization implements an optimized send()
     * function for the case that no accumulator is used and the
     * return type is @p void.
     */
template < typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7 >
struct QExtSignalSend7< void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, QExtNil >
{
    typedef void                                                                                    Return;
    typedef QExtSignalSend7< void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, QExtNil >    Self;
    typedef QExtFunction< void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >                  Slot;
    typedef QExtSignalData::ConstIterator                                                             Iterator;
    typedef typename Slot::CallFunction                                                             CallFunction;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
         * The arguments are passed directly on to the slots.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \param arg6 Argument to be passed on to the slots.
         * \param arg7 Argument to be passed on to the slots.
         */
    static Return send(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6,
            typename QExtTypeTrait< T_arg7 >::Take arg7)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return;
        }
        QExtSignalExecution execution(signalData);

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (Iterator iter = slotList.begin(); iter != slotList.end(); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
                }
            }
        }
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
         * The arguments are passed directly on to the slots.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \param arg6 Argument to be passed on to the slots.
         * \param arg7 Argument to be passed on to the slots.
         */
    static Return sendReverse(
            QExtSignalData *signalData,
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6,
            typename QExtTypeTrait< T_arg7 >::Take arg7)
    {
        if (!signalData || signalData->m_slotList.empty())
        {
            return;
        }
        QExtSignalExecution execution(signalData);

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator< QExtSignalData::Iterator > ReverseIterator;
            QExtFunctionTemporaryList slotList(signalData->m_slotList);
            for (ReverseIterator iter = ReverseIterator(slotList.end()); iter != ReverseIterator(slotList.begin()); ++iter)
            {
                if (!iter->isValid())
                {
                    signalData->m_deferred = QEXT_ATOMIC_INT_TRUE;
                    continue;
                }
                if (iter->isValid() && !iter->isBlocked())
                {
                    (reinterpret_cast< CallFunction >(iter->m_callFunc))(iter->m_data, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
                }
            }
        }
    }
};




/** Signal declaration.
     * QExtSignal0 can be used to connect() slots that are invoked
     * during subsequent calls to send(). Any functor or slot
     * can be passed into connect(). It is converted into a slot
      *implicitly.
     *
     * If you want to connect one signal to another, use make_slot()
     * to retrieve a functor that emits the signal when invoked.
     *
     * Be careful if you directly pass one signal into the connect()
     * method of another: a shallow copy of the signal is made and
     * the signal's slots are not disconnected until both the signal
     * and its clone are destroyed, which is probably not what you want!
     *
     * An STL-style list interface for the signal's list of slots
     * can be retrieved with slots(). This interface supports
     * iteration, insertion and removal of slots.
     *
     * The following template arguments are used:
     * - @e T_return The desired return type for the send() function (may be overridden by the accumulator).
     * - @e T_accumulator The accumulator type used for sender. The default
     * @p QExtNil means that no accumulator should be used, for example if signal
     * sender returns the return value of the last slot invoked.
     *
     * You should use the more convenient unnumbered QExtSignal template.
     *
     * \ingroup signal
     */
template < typename T_return, typename T_accumulator = QExtNil >
class QExtSignal0 : public QExtSignalBase
{
public:
    typedef detail::QExtSignalSend0< T_return, T_accumulator >     Sender;
    typedef typename Sender::Return                                     Return;
    typedef QExtFunction< T_return >                                    Slot;
    typedef QExtFunctionList< Slot >                                    SlotList;
    typedef typename SlotList::Iterator                                 Iterator;
    typedef typename SlotList::ConstIterator                            ConstIterator;

    typedef typename SlotList::ReverseIterator                          ReverseIterator;
    typedef typename SlotList::ConstReverseIterator                     ConstReverseIterator;

    /** Add a slot to the list of slots.
         * Any functor or slot may be passed into connect().
         * It will be converted into a slot implicitly.
         * The returned iterator may be stored for disconnection
         * of the slot at some later point. It stays valid until
         * the slot is removed from the list of slots. The iterator
         * can also be implicitly converted into a QExtConnection object
         * that may be used safely beyond the life time of the slot.
         *
         * std::function<> and C++11 lambda expressions are functors.
         * These are examples of functors that can be connected to a signal.
         *
         * %std::bind() creates a functor, but this functor typically has an
         * %operator()() which is a variadic template.
         * #QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE can't deduce the result type
         * of such a functor. If you first assign the return value of %std::bind()
         * to a std::function, you can connect the std::function to a signal.
         *
         * \param slot_ The slot to add to the list of slots.
         * \return An iterator pointing to the new slot in the list.
         */
    Iterator connect(const Slot &slot)
    {
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)())
    {
        QExtFunction<T_return> slot = QExtBoundMemberFunctor< T_return, T_obj >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)())
    {
        QExtFunction<T_return> slot = QExtBoundMemberFunctor< T_return, T_obj >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)() const)
    {
        QExtFunction<T_return> slot = QExtBoundMemberFunctor< T_return, T_obj >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)() const)
    {
        QExtFunction<T_return> slot = QExtBoundMemberFunctor< T_return, T_obj >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)() volatile)
    {
        QExtFunction<T_return> slot = QExtBoundMemberFunctor< T_return, T_obj >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)() volatile)
    {
        QExtFunction<T_return> slot = QExtBoundMemberFunctor< T_return, T_obj >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)() const volatile)
    {
        QExtFunction<T_return> slot = QExtBoundMemberFunctor< T_return, T_obj >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)() const volatile)
    {
        QExtFunction<T_return> slot = QExtBoundMemberFunctor< T_return, T_obj >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }

    /** Triggers the sender of the signal.
         * During signal sender all slots that have been connected
         * to the signal are invoked unless they are manually set into
         * a blocking state. The parameters are passed on to the slots.
         * If @e T_accumulated is not @p QExtNil, an accumulator of this type
         * is used to process the return values of the slot invocations.
         * Otherwise, the return value of the last slot invoked is returned.
         * \return The accumulated return values of the slot invocations.
         */
    Return send() const
    {
        return Sender::send(m_data);
    }

    /** Triggers the sender of the signal in reverse order (see send()). */
    Return sendReverse() const
    {
        return Sender::sendReverse(m_data);
    }

    /** Triggers the sender of the signal (see send()). */
    Return operator()() const
    {
        return send();
    }

    /** Creates a functor that calls send() on this signal.
         * @code
         * qextMemberFunctor(mysignal, &QExtSignal0::send)
         * @endcode
         * yields the same result.
         * \return A functor that calls send() on this signal.
         */
    QExtBoundConstMemberFunctor< Return, QExtSignal0 > makeSlot() const
    {
        return QExtBoundConstMemberFunctor< Return, QExtSignal0 >(this, &QExtSignal0::send);
    }

    /** Creates an STL-style interface for the signal's list of slots.
         * This interface supports iteration, insertion and removal of slots.
         * \return An STL-style interface for the signal's list of slots.
         */
    SlotList slotList()
    {
        return SlotList(this->data());
    }

    /** Creates an STL-style interface for the signal's list of slots.
         * This interface supports iteration, insertion and removal of slots.
         * \return An STL-style interface for the signal's list of slots.
         */
    const SlotList slotList() const
    {
        return SlotList(const_cast< QExtSignal0 * >(this)->data());
    }

    QExtSignal0() {}

    QExtSignal0(const QExtSignal0 &other) : QExtSignalBase(other) {}
};

/** Signal declaration.
     * QExtSignal1 can be used to connect() slots that are invoked
     * during subsequent calls to send(). Any functor or slot
     * can be passed into connect(). It is converted into a slot
      *implicitly.
     *
     * If you want to connect one signal to another, use make_slot()
     * to retrieve a functor that emits the signal when invoked.
     *
     * Be careful if you directly pass one signal into the connect()
     * method of another: a shallow copy of the signal is made and
     * the signal's slots are not disconnected until both the signal
     * and its clone are destroyed, which is probably not what you want!
     *
     * An STL-style list interface for the signal's list of slots
     * can be retrieved with slots(). This interface supports
     * iteration, insertion and removal of slots.
     *
     * The following template arguments are used:
     * - @e T_return The desired return type for the send() function (may be overridden by the accumulator).
     * - @e T_arg1 Argument type used in the definition of send().
     * - @e T_accumulator The accumulator type used for sender. The default
     * @p QExtNil means that no accumulator should be used, for example if signal
     * sender returns the return value of the last slot invoked.
     *
     * You should use the more convenient unnumbered QExtSignal template.
     *
     * \ingroup signal
     */
template < typename T_return, typename T_arg1, typename T_accumulator = QExtNil >
class QExtSignal1 : public QExtSignalBase
{
public:
    typedef detail::QExtSignalSend1< T_return, T_arg1, T_accumulator >     Sender;
    typedef typename Sender::Return                                             Return;
    typedef QExtFunction< T_return, T_arg1 >                                    Slot;
    typedef QExtFunctionList< Slot >                                            SlotList;
    typedef typename SlotList::Iterator                                         Iterator;
    typedef typename SlotList::ConstIterator                                    ConstIterator;
    typedef typename SlotList::ReverseIterator                                  ReverseIterator;
    typedef typename SlotList::ConstReverseIterator                             ConstReverseIterator;

    /** Add a slot to the list of slots.
         * Any functor or slot may be passed into connect().
         * It will be converted into a slot implicitly.
         * The returned iterator may be stored for disconnection
         * of the slot at some later point. It stays valid until
         * the slot is removed from the list of slots. The iterator
         * can also be implicitly converted into a QExtConnection object
         * that may be used safely beyond the life time of the slot.
         *
         * std::function<> and C++11 lambda expressions are functors.
         * These are examples of functors that can be connected to a signal.
         *
         * %std::bind() creates a functor, but this functor typically has an
         * %operator()() which is a variadic template.
         * #QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE can't deduce the result type
         * of such a functor. If you first assign the return value of %std::bind()
         * to a std::function, you can connect the std::function to a signal.
         *
         * \param slot_ The slot to add to the list of slots.
         * \return An iterator pointing to the new slot in the list.
         */
    Iterator connect(const Slot &slot)
    {
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1))
    {
        QExtFunction<T_return, T_arg1> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1))
    {
        QExtFunction<T_return, T_arg1> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1) const)
    {
        QExtFunction<T_return, T_arg1> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1) const)
    {
        QExtFunction<T_return, T_arg1> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1) volatile)
    {
        QExtFunction<T_return, T_arg1> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1) volatile)
    {
        QExtFunction<T_return, T_arg1> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1) const volatile)
    {
        QExtFunction<T_return, T_arg1> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1) const volatile)
    {
        QExtFunction<T_return, T_arg1> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }

    /** Triggers the sender of the signal.
         * During signal sender all slots that have been connected
         * to the signal are invoked unless they are manually set into
         * a blocking state. The parameters are passed on to the slots.
         * If @e T_accumulated is not @p QExtNil, an accumulator of this type
         * is used to process the return values of the slot invocations.
         * Otherwise, the return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations.
         */
    Return send(typename QExtTypeTrait< T_arg1 >::Take arg1) const
    {
        return Sender::send(m_data, arg1);
    }

    /** Triggers the sender of the signal in reverse order (see send()). */
    Return sendReverse(typename QExtTypeTrait< T_arg1 >::Take arg1) const
    {
        return Sender::sendReverse(m_data, arg1);
    }

    /** Triggers the sender of the signal (see send()). */
    Return operator()(typename QExtTypeTrait< T_arg1 >::Take arg1) const
    {
        return this->send(arg1);
    }

    /** Creates a functor that calls send() on this signal.
         * @code
         * qextMemberFunctor(mysignal, &QExtSignal1::send)
         * @endcode
         * yields the same result.
         * \return A functor that calls send() on this signal.
         */
    QExtBoundConstMemberFunctor< Return, QExtSignal1, typename QExtTypeTrait< T_arg1 >::Take > makeSlot() const
    {
        return QExtBoundConstMemberFunctor< Return, QExtSignal1, typename QExtTypeTrait< T_arg1 >::Take >(this, &QExtSignal1::send);
    }

    /** Creates an STL-style interface for the signal's list of slots.
         * This interface supports iteration, insertion and removal of slots.
         * \return An STL-style interface for the signal's list of slots.
         */
    SlotList slotList()
    {
        return SlotList(this->data());
    }

    /** Creates an STL-style interface for the signal's list of slots.
         * This interface supports iteration, insertion and removal of slots.
         * \return An STL-style interface for the signal's list of slots.
         */
    const SlotList slotList() const
    {
        return SlotList(const_cast< QExtSignal1 * >(this)->data());
    }

    QExtSignal1() {}

    QExtSignal1(const QExtSignal1 &other) : QExtSignalBase(other) {}
};

/** Signal declaration.
     * QExtSignal2 can be used to connect() slots that are invoked
     * during subsequent calls to send(). Any functor or slot
     * can be passed into connect(). It is converted into a slot
      *implicitly.
     *
     * If you want to connect one signal to another, use make_slot()
     * to retrieve a functor that emits the signal when invoked.
     *
     * Be careful if you directly pass one signal into the connect()
     * method of another: a shallow copy of the signal is made and
     * the signal's slots are not disconnected until both the signal
     * and its clone are destroyed, which is probably not what you want!
     *
     * An STL-style list interface for the signal's list of slots
     * can be retrieved with slots(). This interface supports
     * iteration, insertion and removal of slots.
     *
     * The following template arguments are used:
     * - @e T_return The desired return type for the send() function (may be overridden by the accumulator).
     * - @e T_arg1 Argument type used in the definition of send().
     * - @e T_arg2 Argument type used in the definition of send().
     * - @e T_accumulator The accumulator type used for sender. The default
     * @p QExtNil means that no accumulator should be used, for example if signal
     * sender returns the return value of the last slot invoked.
     *
     * You should use the more convenient unnumbered QExtSignal template.
     *
     * \ingroup signal
     */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_accumulator = QExtNil >
class QExtSignal2 : public QExtSignalBase
{
public:
    typedef detail::QExtSignalSend2< T_return, T_arg1, T_arg2, T_accumulator > Sender;
    typedef typename Sender::Return                                             Return;
    typedef QExtFunction< T_return, T_arg1, T_arg2 >                                  Slot;
    typedef QExtFunctionList< Slot >                                                  SlotList;
    typedef typename SlotList::Iterator                                         Iterator;
    typedef typename SlotList::ConstIterator                                    ConstIterator;
    typedef typename SlotList::ReverseIterator                                  ReverseIterator;
    typedef typename SlotList::ConstReverseIterator                             ConstReverseIterator;

    /** Add a slot to the list of slots.
         * Any functor or slot may be passed into connect().
         * It will be converted into a slot implicitly.
         * The returned iterator may be stored for disconnection
         * of the slot at some later point. It stays valid until
         * the slot is removed from the list of slots. The iterator
         * can also be implicitly converted into a QExtConnection object
         * that may be used safely beyond the life time of the slot.
         *
         * std::function<> and C++11 lambda expressions are functors.
         * These are examples of functors that can be connected to a signal.
         *
         * %std::bind() creates a functor, but this functor typically has an
         * %operator()() which is a variadic template.
         * #QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE can't deduce the result type
         * of such a functor. If you first assign the return value of %std::bind()
         * to a std::function, you can connect the std::function to a signal.
         *
         * \param slot_ The slot to add to the list of slots.
         * \return An iterator pointing to the new slot in the list.
         */
    Iterator connect(const Slot &slot)
    {
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2))
    {
        QExtFunction<T_return, T_arg1, T_arg2> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2))
    {
        QExtFunction<T_return, T_arg1, T_arg2> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2) const)
    {
        QExtFunction<T_return, T_arg1, T_arg2> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2) const)
    {
        QExtFunction<T_return, T_arg1, T_arg2> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2) volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2) volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2) const volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2) const volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }

    /** Triggers the sender of the signal.
         * During signal sender all slots that have been connected
         * to the signal are invoked unless they are manually set into
         * a blocking state. The parameters are passed on to the slots.
         * If @e T_accumulated is not @p QExtNil, an accumulator of this type
         * is used to process the return values of the slot invocations.
         * Otherwise, the return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations.
         */
    Return send(typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2) const
    {
        return Sender::send(m_data, arg1, arg2);
    }

    /** Triggers the sender of the signal in reverse order (see send()). */
    Return sendReverse(typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2) const
    {
        return Sender::sendReverse(m_data, arg1, arg2);
    }

    /** Triggers the sender of the signal (see send()). */
    Return operator()(typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2) const
    {
        return send(arg1, arg2);
    }

    /** Creates a functor that calls send() on this signal.
         * @code
         * qextMemberFunctor(mysignal, &QExtSignal2::send)
         * @endcode
         * yields the same result.
         * \return A functor that calls send() on this signal.
         */
    QExtBoundConstMemberFunctor< Return, QExtSignal2, typename QExtTypeTrait< T_arg1 >::Take, typename QExtTypeTrait< T_arg2 >::Take > makeSlot() const
    {
        return QExtBoundConstMemberFunctor <
                Return,
                QExtSignal2,
                typename QExtTypeTrait< T_arg1 >::Take,
                typename QExtTypeTrait< T_arg2 >::Take >
                (this, &QExtSignal2::send);
    }

    /** Creates an STL-style interface for the signal's list of slots.
         * This interface supports iteration, insertion and removal of slots.
         * \return An STL-style interface for the signal's list of slots.
         */
    SlotList slotList()
    {
        return SlotList(this->data());
    }

    /** Creates an STL-style interface for the signal's list of slots.
         * This interface supports iteration, insertion and removal of slots.
         * \return An STL-style interface for the signal's list of slots.
         */
    const SlotList slotList() const
    {
        return SlotList(const_cast< QExtSignal2 * >(this)->data());
    }

    QExtSignal2() {}

    QExtSignal2(const QExtSignal2 &other) : QExtSignalBase(other) {}
};

/** Signal declaration.
     * QExtSignal3 can be used to connect() slots that are invoked
     * during subsequent calls to send(). Any functor or slot
     * can be passed into connect(). It is converted into a slot
      *implicitly.
     *
     * If you want to connect one signal to another, use make_slot()
     * to retrieve a functor that emits the signal when invoked.
     *
     * Be careful if you directly pass one signal into the connect()
     * method of another: a shallow copy of the signal is made and
     * the signal's slots are not disconnected until both the signal
     * and its clone are destroyed, which is probably not what you want!
     *
     * An STL-style list interface for the signal's list of slots
     * can be retrieved with slots(). This interface supports
     * iteration, insertion and removal of slots.
     *
     * The following template arguments are used:
     * - @e T_return The desired return type for the send() function (may be overridden by the accumulator).
     * - @e T_arg1 Argument type used in the definition of send().
     * - @e T_arg2 Argument type used in the definition of send().
     * - @e T_arg3 Argument type used in the definition of send().
     * - @e T_accumulator The accumulator type used for sender. The default
     * @p QExtNil means that no accumulator should be used, for example if signal
     * sender returns the return value of the last slot invoked.
     *
     * You should use the more convenient unnumbered QExtSignal template.
     *
     * \ingroup signal
     */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_accumulator = QExtNil >
class QExtSignal3 : public QExtSignalBase
{
public:
    typedef detail::QExtSignalSend3< T_return, T_arg1, T_arg2, T_arg3, T_accumulator > Sender;
    typedef typename Sender::Return                                                     Return;
    typedef QExtFunction< T_return, T_arg1, T_arg2, T_arg3 >                                  Slot;
    typedef QExtFunctionList< Slot >                                                          SlotList;
    typedef typename SlotList::Iterator                                                 Iterator;
    typedef typename SlotList::ConstIterator                                            ConstIterator;
    typedef typename SlotList::ReverseIterator                                          ReverseIterator;
    typedef typename SlotList::ConstReverseIterator                                     ConstReverseIterator;

    /** Add a slot to the list of slots.
         * Any functor or slot may be passed into connect().
         * It will be converted into a slot implicitly.
         * The returned iterator may be stored for disconnection
         * of the slot at some later point. It stays valid until
         * the slot is removed from the list of slots. The iterator
         * can also be implicitly converted into a QExtConnection object
         * that may be used safely beyond the life time of the slot.
         *
         * std::function<> and C++11 lambda expressions are functors.
         * These are examples of functors that can be connected to a signal.
         *
         * %std::bind() creates a functor, but this functor typically has an
         * %operator()() which is a variadic template.
         * #QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE can't deduce the result type
         * of such a functor. If you first assign the return value of %std::bind()
         * to a std::function, you can connect the std::function to a signal.
         *
         * \param slot_ The slot to add to the list of slots.
         * \return An iterator pointing to the new slot in the list.
         */
    Iterator connect(const Slot &slot)
    {
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3))
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3))
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3) const volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }

    /** Triggers the sender of the signal.
         * During signal sender all slots that have been connected
         * to the signal are invoked unless they are manually set into
         * a blocking state. The parameters are passed on to the slots.
         * If @e T_accumulated is not @p QExtNil, an accumulator of this type
         * is used to process the return values of the slot invocations.
         * Otherwise, the return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations.
         */
    Return send(typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2, typename QExtTypeTrait< T_arg3 >::Take arg3) const
    {
        return Sender::send(m_data, arg1, arg2, arg3);
    }

    /** Triggers the sender of the signal in reverse order (see send()). */
    Return sendReverse(typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2, typename QExtTypeTrait< T_arg3 >::Take arg3) const
    {
        return Sender::sendReverse(m_data, arg1, arg2, arg3);
    }

    /** Triggers the sender of the signal (see send()). */
    Return operator()(typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2, typename QExtTypeTrait< T_arg3 >::Take arg3) const
    {
        return send(arg1, arg2, arg3);
    }

    /** Creates a functor that calls send() on this signal.
         * @code
         * qextMemberFunctor(mysignal, &QExtSignal3::send)
         * @endcode
         * yields the same result.
         * \return A functor that calls send() on this signal.
         */
    QExtBoundConstMemberFunctor <
    Return,
    QExtSignal3,
    typename QExtTypeTrait< T_arg1 >::Take,
    typename QExtTypeTrait< T_arg2 >::Take,
    typename QExtTypeTrait< T_arg3 >::Take >
    makeSlot() const
    {
        return QExtBoundConstMemberFunctor <
                Return,
                QExtSignal3,
                typename QExtTypeTrait< T_arg1 >::Take,
                typename QExtTypeTrait< T_arg2 >::Take,
                typename QExtTypeTrait< T_arg3 >::Take > (this, &QExtSignal3::send);
    }

    /** Creates an STL-style interface for the signal's list of slots.
         * This interface supports iteration, insertion and removal of slots.
         * \return An STL-style interface for the signal's list of slots.
         */
    SlotList slotList()
    {
        return SlotList(this->data());
    }

    /** Creates an STL-style interface for the signal's list of slots.
         * This interface supports iteration, insertion and removal of slots.
         * \return An STL-style interface for the signal's list of slots.
         */
    const SlotList slotList() const
    {
        return SlotList(const_cast< QExtSignal3 * >(this)->data());
    }

    QExtSignal3() {}

    QExtSignal3(const QExtSignal3 &other) : QExtSignalBase(other) {}
};

/** Signal declaration.
     * QExtSignal4 can be used to connect() slots that are invoked
     * during subsequent calls to send(). Any functor or slot
     * can be passed into connect(). It is converted into a slot
      *implicitly.
     *
     * If you want to connect one signal to another, use make_slot()
     * to retrieve a functor that emits the signal when invoked.
     *
     * Be careful if you directly pass one signal into the connect()
     * method of another: a shallow copy of the signal is made and
     * the signal's slots are not disconnected until both the signal
     * and its clone are destroyed, which is probably not what you want!
     *
     * An STL-style list interface for the signal's list of slots
     * can be retrieved with slots(). This interface supports
     * iteration, insertion and removal of slots.
     *
     * The following template arguments are used:
     * - @e T_return The desired return type for the send() function (may be overridden by the accumulator).
     * - @e T_arg1 Argument type used in the definition of send().
     * - @e T_arg2 Argument type used in the definition of send().
     * - @e T_arg3 Argument type used in the definition of send().
     * - @e T_arg4 Argument type used in the definition of send().
     * - @e T_accumulator The accumulator type used for sender. The default
     * @p QExtNil means that no accumulator should be used, for example if signal
     * sender returns the return value of the last slot invoked.
     *
     * You should use the more convenient unnumbered QExtSignal template.
     *
     * \ingroup signal
     */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_accumulator = QExtNil >
class QExtSignal4 : public QExtSignalBase
{
public:
    typedef detail::QExtSignalSend4< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_accumulator > Sender;
    typedef typename Sender::Return                                                             Return;
    typedef QExtFunction< T_return, T_arg1, T_arg2, T_arg3, T_arg4 >                                  Slot;
    typedef QExtFunctionList< Slot >                                                                  SlotList;
    typedef typename SlotList::Iterator                                                         Iterator;
    typedef typename SlotList::ConstIterator                                                    ConstIterator;
    typedef typename SlotList::ReverseIterator                                                  ReverseIterator;
    typedef typename SlotList::ConstReverseIterator                                             ConstReverseIterator;

    /** Add a slot to the list of slots.
         * Any functor or slot may be passed into connect().
         * It will be converted into a slot implicitly.
         * The returned iterator may be stored for disconnection
         * of the slot at some later point. It stays valid until
         * the slot is removed from the list of slots. The iterator
         * can also be implicitly converted into a QExtConnection object
         * that may be used safely beyond the life time of the slot.
         *
         * std::function<> and C++11 lambda expressions are functors.
         * These are examples of functors that can be connected to a signal.
         *
         * %std::bind() creates a functor, but this functor typically has an
         * %operator()() which is a variadic template.
         * #QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE can't deduce the result type
         * of such a functor. If you first assign the return value of %std::bind()
         * to a std::function, you can connect the std::function to a signal.
         *
         * \param slot_ The slot to add to the list of slots.
         * \return An iterator pointing to the new slot in the list.
         */
    Iterator connect(const Slot &slot)
    {
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4))
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4))
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4) const volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }

    /** Triggers the sender of the signal.
         * During signal sender all slots that have been connected
         * to the signal are invoked unless they are manually set into
         * a blocking state. The parameters are passed on to the slots.
         * If @e T_accumulated is not @p QExtNil, an accumulator of this type
         * is used to process the return values of the slot invocations.
         * Otherwise, the return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations.
         */
    Return send(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4) const
    {
        return Sender::send(m_data, arg1, arg2, arg3, arg4);
    }

    /** Triggers the sender of the signal in reverse order (see send()). */
    Return sendReverse(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4) const
    {
        return Sender::sendReverse(m_data, arg1, arg2, arg3, arg4);
    }

    /** Triggers the sender of the signal (see send()). */
    Return operator()(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4) const
    {
        return send(arg1, arg2, arg3, arg4);
    }

    /** Creates a functor that calls send() on this signal.
         * @code
         * qextMemberFunctor(mysignal, &QExtSignal4::send)
         * @endcode
         * yields the same result.
         * \return A functor that calls send() on this signal.
         */
    QExtBoundConstMemberFunctor <
    Return,
    QExtSignal4,
    typename QExtTypeTrait< T_arg1 >::Take,
    typename QExtTypeTrait< T_arg2 >::Take,
    typename QExtTypeTrait< T_arg3 >::Take,
    typename QExtTypeTrait< T_arg4 >::Take >
    makeSlot() const
    {
        return QExtBoundConstMemberFunctor <
                Return,
                QExtSignal4,
                typename QExtTypeTrait< T_arg1 >::Take,
                typename QExtTypeTrait< T_arg2 >::Take,
                typename QExtTypeTrait< T_arg3 >::Take,
                typename QExtTypeTrait< T_arg4 >::Take > (this, &QExtSignal4::send);
    }

    /** Creates an STL-style interface for the signal's list of slots.
         * This interface supports iteration, insertion and removal of slots.
         * \return An STL-style interface for the signal's list of slots.
         */
    SlotList slotList()
    {
        return SlotList(this->data());
    }

    /** Creates an STL-style interface for the signal's list of slots.
         * This interface supports iteration, insertion and removal of slots.
         * \return An STL-style interface for the signal's list of slots.
         */
    const SlotList slotList() const
    {
        return SlotList(const_cast< QExtSignal4 * >(this)->data());
    }

    QExtSignal4() {}

    QExtSignal4(const QExtSignal4 &other) : QExtSignalBase(other) {}
};

/** Signal declaration.
     * QExtSignal5 can be used to connect() slots that are invoked
     * during subsequent calls to send(). Any functor or slot
     * can be passed into connect(). It is converted into a slot
      *implicitly.
     *
     * If you want to connect one signal to another, use make_slot()
     * to retrieve a functor that emits the signal when invoked.
     *
     * Be careful if you directly pass one signal into the connect()
     * method of another: a shallow copy of the signal is made and
     * the signal's slots are not disconnected until both the signal
     * and its clone are destroyed, which is probably not what you want!
     *
     * An STL-style list interface for the signal's list of slots
     * can be retrieved with slots(). This interface supports
     * iteration, insertion and removal of slots.
     *
     * The following template arguments are used:
     * - @e T_return The desired return type for the send() function (may be overridden by the accumulator).
     * - @e T_arg1 Argument type used in the definition of send().
     * - @e T_arg2 Argument type used in the definition of send().
     * - @e T_arg3 Argument type used in the definition of send().
     * - @e T_arg4 Argument type used in the definition of send().
     * - @e T_arg5 Argument type used in the definition of send().
     * - @e T_accumulator The accumulator type used for sender. The default
     * @p QExtNil means that no accumulator should be used, for example if signal
     * sender returns the return value of the last slot invoked.
     *
     * You should use the more convenient unnumbered QExtSignal template.
     *
     * \ingroup signal
     */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_accumulator = QExtNil >
class QExtSignal5 : public QExtSignalBase
{
public:
    typedef detail::QExtSignalSend5< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_accumulator > Sender;
    typedef typename Sender::Return                                                                     Return;
    typedef QExtFunction< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >                                  Slot;
    typedef QExtFunctionList< Slot >                                                                          SlotList;
    typedef typename SlotList::Iterator                                                                 Iterator;
    typedef typename SlotList::ConstIterator                                                            ConstIterator;
    typedef typename SlotList::ReverseIterator                                                          ReverseIterator;
    typedef typename SlotList::ConstReverseIterator                                                     ConstReverseIterator;

    /** Add a slot to the list of slots.
         * Any functor or slot may be passed into connect().
         * It will be converted into a slot implicitly.
         * The returned iterator may be stored for disconnection
         * of the slot at some later point. It stays valid until
         * the slot is removed from the list of slots. The iterator
         * can also be implicitly converted into a QExtConnection object
         * that may be used safely beyond the life time of the slot.
         *
         * std::function<> and C++11 lambda expressions are functors.
         * These are examples of functors that can be connected to a signal.
         *
         * %std::bind() creates a functor, but this functor typically has an
         * %operator()() which is a variadic template.
         * #QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE can't deduce the result type
         * of such a functor. If you first assign the return value of %std::bind()
         * to a std::function, you can connect the std::function to a signal.
         *
         * \param slot_ The slot to add to the list of slots.
         * \return An iterator pointing to the new slot in the list.
         */
    Iterator connect(const Slot &slot)
    {
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5))
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5))
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5) const volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }

    /** Triggers the sender of the signal.
         * During signal sender all slots that have been connected
         * to the signal are invoked unless they are manually set into
         * a blocking state. The parameters are passed on to the slots.
         * If @e T_accumulated is not @p QExtNil, an accumulator of this type
         * is used to process the return values of the slot invocations.
         * Otherwise, the return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations.
         */
    Return send(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5) const
    {
        return Sender::send(m_data, arg1, arg2, arg3, arg4, arg5);
    }

    /** Triggers the sender of the signal in reverse order (see send()). */
    Return sendReverse(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5) const
    {
        return Sender::sendReverse(m_data, arg1, arg2, arg3, arg4, arg5);
    }

    /** Triggers the sender of the signal (see send()). */
    Return operator()(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5) const
    {
        return send(arg1, arg2, arg3, arg4, arg5);
    }

    /** Creates a functor that calls send() on this signal.
         * @code
         * qextMemberFunctor(mysignal, &QExtSignal5::send)
         * @endcode
         * yields the same result.
         * \return A functor that calls send() on this signal.
         */
    QExtBoundConstMemberFunctor <
    Return,
    QExtSignal5,
    typename QExtTypeTrait< T_arg1 >::Take,
    typename QExtTypeTrait< T_arg2 >::Take,
    typename QExtTypeTrait< T_arg3 >::Take,
    typename QExtTypeTrait< T_arg4 >::Take,
    typename QExtTypeTrait< T_arg5 >::Take >
    makeSlot() const
    {
        return QExtBoundConstMemberFunctor <
                Return,
                QExtSignal5,
                typename QExtTypeTrait< T_arg1 >::Take,
                typename QExtTypeTrait< T_arg2 >::Take,
                typename QExtTypeTrait< T_arg3 >::Take,
                typename QExtTypeTrait< T_arg4 >::Take,
                typename QExtTypeTrait< T_arg5 >::Take > (this, &QExtSignal5::send);
    }

    /** Creates an STL-style interface for the signal's list of slots.
         * This interface supports iteration, insertion and removal of slots.
         * \return An STL-style interface for the signal's list of slots.
         */
    SlotList slotList()
    {
        return SlotList(this->data());
    }

    /** Creates an STL-style interface for the signal's list of slots.
         * This interface supports iteration, insertion and removal of slots.
         * \return An STL-style interface for the signal's list of slots.
         */
    const SlotList slotList() const
    {
        return SlotList(const_cast< QExtSignal5 * >(this)->data());
    }

    QExtSignal5() {}

    QExtSignal5(const QExtSignal5 &other) : QExtSignalBase(other) {}
};

/** Signal declaration.
     * QExtSignal6 can be used to connect() slots that are invoked
     * during subsequent calls to send(). Any functor or slot
     * can be passed into connect(). It is converted into a slot
      *implicitly.
     *
     * If you want to connect one signal to another, use make_slot()
     * to retrieve a functor that emits the signal when invoked.
     *
     * Be careful if you directly pass one signal into the connect()
     * method of another: a shallow copy of the signal is made and
     * the signal's slots are not disconnected until both the signal
     * and its clone are destroyed, which is probably not what you want!
     *
     * An STL-style list interface for the signal's list of slots
     * can be retrieved with slots(). This interface supports
     * iteration, insertion and removal of slots.
     *
     * The following template arguments are used:
     * - @e T_return The desired return type for the send() function (may be overridden by the accumulator).
     * - @e T_arg1 Argument type used in the definition of send().
     * - @e T_arg2 Argument type used in the definition of send().
     * - @e T_arg3 Argument type used in the definition of send().
     * - @e T_arg4 Argument type used in the definition of send().
     * - @e T_arg5 Argument type used in the definition of send().
     * - @e T_arg6 Argument type used in the definition of send().
     * - @e T_accumulator The accumulator type used for sender. The default
     * @p QExtNil means that no accumulator should be used, for example if signal
     * sender returns the return value of the last slot invoked.
     *
     * You should use the more convenient unnumbered QExtSignal template.
     *
     * \ingroup signal
     */
template <
        typename T_return,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_accumulator = QExtNil >
class QExtSignal6 : public QExtSignalBase
{
public:
    typedef detail::QExtSignalSend6< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_accumulator > Sender;
    typedef typename Sender::Return                                                                             Return;
    typedef QExtFunction< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >                                  Slot;
    typedef QExtFunctionList< Slot >                                                                                  SlotList;
    typedef typename SlotList::Iterator                                                                         Iterator;
    typedef typename SlotList::ConstIterator                                                                    ConstIterator;
    typedef typename SlotList::ReverseIterator                                                                  ReverseIterator;
    typedef typename SlotList::ConstReverseIterator                                                             ConstReverseIterator;

    /** Add a slot to the list of slots.
         * Any functor or slot may be passed into connect().
         * It will be converted into a slot implicitly.
         * The returned iterator may be stored for disconnection
         * of the slot at some later point. It stays valid until
         * the slot is removed from the list of slots. The iterator
         * can also be implicitly converted into a QExtConnection object
         * that may be used safely beyond the life time of the slot.
         *
         * std::function<> and C++11 lambda expressions are functors.
         * These are examples of functors that can be connected to a signal.
         *
         * %std::bind() creates a functor, but this functor typically has an
         * %operator()() which is a variadic template.
         * #QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE can't deduce the result type
         * of such a functor. If you first assign the return value of %std::bind()
         * to a std::function, you can connect the std::function to a signal.
         *
         * \param slot_ The slot to add to the list of slots.
         * \return An iterator pointing to the new slot in the list.
         */
    Iterator connect(const Slot &slot)
    {
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6))
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6))
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }

    /** Triggers the sender of the signal.
         * During signal sender all slots that have been connected
         * to the signal are invoked unless they are manually set into
         * a blocking state. The parameters are passed on to the slots.
         * If @e T_accumulated is not @p QExtNil, an accumulator of this type
         * is used to process the return values of the slot invocations.
         * Otherwise, the return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \param arg6 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations.
         */
    Return send(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6) const
    {
        return Sender::send(m_data, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /** Triggers the sender of the signal in reverse order (see send()). */
    Return sendReverse(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6) const
    {
        return Sender::sendReverse(m_data, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /** Triggers the sender of the signal (see send()). */
    Return operator()(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6) const
    {
        return send(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /** Creates a functor that calls send() on this signal.
         * @code
         * qextMemberFunctor(mysignal, &QExtSignal6::send)
         * @endcode
         * yields the same result.
         * \return A functor that calls send() on this signal.
         */
    QExtBoundConstMemberFunctor <
    Return,
    QExtSignal6,
    typename QExtTypeTrait< T_arg1 >::Take,
    typename QExtTypeTrait< T_arg2 >::Take,
    typename QExtTypeTrait< T_arg3 >::Take,
    typename QExtTypeTrait< T_arg4 >::Take,
    typename QExtTypeTrait< T_arg5 >::Take,
    typename QExtTypeTrait< T_arg6 >::Take >
    makeSlot() const
    {
        return QExtBoundConstMemberFunctor <
                Return,
                QExtSignal6,
                typename QExtTypeTrait< T_arg1 >::Take,
                typename QExtTypeTrait< T_arg2 >::Take,
                typename QExtTypeTrait< T_arg3 >::Take,
                typename QExtTypeTrait< T_arg4 >::Take,
                typename QExtTypeTrait< T_arg5 >::Take,
                typename QExtTypeTrait< T_arg6 >::Take > (this, &QExtSignal6::send);
    }

    /** Creates an STL-style interface for the signal's list of slots.
         * This interface supports iteration, insertion and removal of slots.
         * \return An STL-style interface for the signal's list of slots.
         */
    SlotList slotList()
    {
        return SlotList(this->data());
    }

    /** Creates an STL-style interface for the signal's list of slots.
         * This interface supports iteration, insertion and removal of slots.
         * \return An STL-style interface for the signal's list of slots.
         */
    const SlotList slotList() const
    {
        return SlotList(const_cast< QExtSignal6 * >(this)->data());
    }

    QExtSignal6() {}

    QExtSignal6(const QExtSignal6 &other) : QExtSignalBase(other) {}
};

/** Signal declaration.
     * QExtSignal7 can be used to connect() slots that are invoked
     * during subsequent calls to send(). Any functor or slot
     * can be passed into connect(). It is converted into a slot
      *implicitly.
     *
     * If you want to connect one signal to another, use make_slot()
     * to retrieve a functor that emits the signal when invoked.
     *
     * Be careful if you directly pass one signal into the connect()
     * method of another: a shallow copy of the signal is made and
     * the signal's slots are not disconnected until both the signal
     * and its clone are destroyed, which is probably not what you want!
     *
     * An STL-style list interface for the signal's list of slots
     * can be retrieved with slots(). This interface supports
     * iteration, insertion and removal of slots.
     *
     * The following template arguments are used:
     * - @e T_return The desired return type for the send() function (may be overridden by the accumulator).
     * - @e T_arg1 Argument type used in the definition of send().
     * - @e T_arg2 Argument type used in the definition of send().
     * - @e T_arg3 Argument type used in the definition of send().
     * - @e T_arg4 Argument type used in the definition of send().
     * - @e T_arg5 Argument type used in the definition of send().
     * - @e T_arg6 Argument type used in the definition of send().
     * - @e T_arg7 Argument type used in the definition of send().
     * - @e T_accumulator The accumulator type used for sender. The default
     * @p QExtNil means that no accumulator should be used, for example if signal
     * sender returns the return value of the last slot invoked.
     *
     * You should use the more convenient unnumbered QExtSignal template.
     *
     * \ingroup signal
     */
template <
        typename T_return,
        typename T_arg1,
        typename T_arg2,
        typename T_arg3,
        typename T_arg4,
        typename T_arg5,
        typename T_arg6,
        typename T_arg7,
        typename T_accumulator = QExtNil >
class QExtSignal7 : public QExtSignalBase
{
public:
    typedef detail::QExtSignalSend7< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_accumulator > Sender;
    typedef typename Sender::Return                                                                                     Return;
    typedef QExtFunction< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >                                  Slot;
    typedef QExtFunctionList< Slot >                                                                                          SlotList;
    typedef typename SlotList::Iterator                                                                                 Iterator;
    typedef typename SlotList::ConstIterator                                                                            ConstIterator;
    typedef typename SlotList::ReverseIterator                                                                          ReverseIterator;
    typedef typename SlotList::ConstReverseIterator                                                                     ConstReverseIterator;

    QExtSignal7() {}
    QExtSignal7(const QExtSignal7 &other) : QExtSignalBase(other) {}

    /** Add a slot to the list of slots.
         * Any functor or slot may be passed into connect().
         * It will be converted into a slot implicitly.
         * The returned iterator may be stored for disconnection
         * of the slot at some later point. It stays valid until
         * the slot is removed from the list of slots. The iterator
         * can also be implicitly converted into a QExtConnection object
         * that may be used safely beyond the life time of the slot.
         *
         * std::function<> and C++11 lambda expressions are functors.
         * These are examples of functors that can be connected to a signal.
         *
         * %std::bind() creates a functor, but this functor typically has an
         * %operator()() which is a variadic template.
         * #QEXT_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE can't deduce the result type
         * of such a functor. If you first assign the return value of %std::bind()
         * to a std::function, you can connect the std::function to a signal.
         *
         * \param slot_ The slot to add to the list of slots.
         * \return An iterator pointing to the new slot in the list.
         */
    Iterator connect(const Slot &slot)
    {
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7))
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7))
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj *obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }
    template < typename T_obj >
    Iterator connect(T_obj &obj, T_return (T_obj::*func)(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const volatile)
    {
        QExtFunction<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7> slot = QExtBoundMemberFunctor< T_return, T_obj, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 >(obj, func);
        return Iterator(QExtSignalBase::connect(static_cast< const QExtFunctionBase & >(slot)));
    }

    /** Triggers the sender of the signal.
         * During signal sender all slots that have been connected
         * to the signal are invoked unless they are manually set into
         * a blocking state. The parameters are passed on to the slots.
         * If @e T_accumulated is not @p QExtNil, an accumulator of this type
         * is used to process the return values of the slot invocations.
         * Otherwise, the return value of the last slot invoked is returned.
         * \param arg1 Argument to be passed on to the slots.
         * \param arg2 Argument to be passed on to the slots.
         * \param arg3 Argument to be passed on to the slots.
         * \param arg4 Argument to be passed on to the slots.
         * \param arg5 Argument to be passed on to the slots.
         * \param arg6 Argument to be passed on to the slots.
         * \param arg7 Argument to be passed on to the slots.
         * \return The accumulated return values of the slot invocations.
         */
    Return send(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6,
            typename QExtTypeTrait< T_arg7 >::Take arg7) const
    {
        return Sender::send(m_data, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    /** Triggers the sender of the signal in reverse order (see send()). */
    Return sendReverse(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6,
            typename QExtTypeTrait< T_arg7 >::Take arg7) const
    {
        return Sender::sendReverse(m_data, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    /** Triggers the sender of the signal (see send()). */
    Return operator()(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6,
            typename QExtTypeTrait< T_arg7 >::Take arg7) const
    {
        return send(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    /** Creates a functor that calls send() on this signal.
         * @code
         * qextMemberFunctor(mysignal, &QExtSignal7::send)
         * @endcode
         * yields the same result.
         * \return A functor that calls send() on this signal.
         */
    QExtBoundConstMemberFunctor <
    Return,
    QExtSignal7,
    typename QExtTypeTrait< T_arg1 >::Take,
    typename QExtTypeTrait< T_arg2 >::Take,
    typename QExtTypeTrait< T_arg3 >::Take,
    typename QExtTypeTrait< T_arg4 >::Take,
    typename QExtTypeTrait< T_arg5 >::Take,
    typename QExtTypeTrait< T_arg6 >::Take,
    typename QExtTypeTrait< T_arg7 >::Take >
    makeSlot() const
    {
        return QExtBoundConstMemberFunctor <
                Return,
                QExtSignal7,
                typename QExtTypeTrait< T_arg1 >::Take,
                typename QExtTypeTrait< T_arg2 >::Take,
                typename QExtTypeTrait< T_arg3 >::Take,
                typename QExtTypeTrait< T_arg4 >::Take,
                typename QExtTypeTrait< T_arg5 >::Take,
                typename QExtTypeTrait< T_arg6 >::Take,
                typename QExtTypeTrait< T_arg7 >::Take > (this, &QExtSignal7::send);
    }

    /** Creates an STL-style interface for the signal's list of slots.
         * This interface supports iteration, insertion and removal of slots.
         * \return An STL-style interface for the signal's list of slots.
         */
    SlotList slotList()
    {
        return SlotList(this->data());
    }

    /** Creates an STL-style interface for the signal's list of slots.
         * This interface supports iteration, insertion and removal of slots.
         * \return An STL-style interface for the signal's list of slots.
         */
    const SlotList slotList() const
    {
        return SlotList(const_cast< QExtSignal7 * >(this)->data());
    }
};

}


/** Convenience wrapper for the numbered QExtSignal# templates.
 * signal can be used to connect() slots that are invoked
 * during subsequent calls to send(). Any functor or slot
 * can be passed into connect(). It is converted into a slot
  *implicitly.
 *
 * If you want to connect one signal to another, use make_slot()
 * to retrieve a functor that emits the signal when invoked.
 *
 * Be careful if you directly pass one signal into the connect()
 * method of another: a shallow copy of the signal is made and
 * the signal's slots are not disconnected until both the signal
 * and its clone are destroyed, which is probably not what you want!
 *
 * An STL-style list interface for the signal's list of slots
 * can be retrieved with slots(). This interface supports
 * iteration, insertion and removal of slots.
 *
 * The template arguments determine the function signature of
 * the send() function:
 * - @e T_return The desired return type of the send() function.
 * - @e T_arg1 Argument type used in the definition of send(). The default @p QExtNil means no argument.
 * - @e T_arg2 Argument type used in the definition of send(). The default @p QExtNil means no argument.
 * - @e T_arg3 Argument type used in the definition of send(). The default @p QExtNil means no argument.
 * - @e T_arg4 Argument type used in the definition of send(). The default @p QExtNil means no argument.
 * - @e T_arg5 Argument type used in the definition of send(). The default @p QExtNil means no argument.
 * - @e T_arg6 Argument type used in the definition of send(). The default @p QExtNil means no argument.
 * - @e T_arg7 Argument type used in the definition of send(). The default @p QExtNil means no argument.
 *
 * To specify an accumulator type the nested class signal::accumulated can be used.
 *
 * @par Example:
 * @code
 * void foo(int) {}
 * QExtSignal<void, long> sig;
 * sig.connect(ptr_fun(&foo));
 * sig.send(19);
 * @endcode
 *
 * \ingroup signal
 */
template <
        typename T_return,
        typename T_arg1 = QExtNil,
        typename T_arg2 = QExtNil,
        typename T_arg3 = QExtNil,
        typename T_arg4 = QExtNil,
        typename T_arg5 = QExtNil,
        typename T_arg6 = QExtNil,
        typename T_arg7 = QExtNil >
class QExtSignal : public detail::QExtSignal7< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, QExtNil >
{
public:
    typedef detail::QExtSignal7< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, QExtNil > Base;
    typedef typename Base::Return                                                                           Return;

    /** Convenience wrapper for the numbered QExtSignal# templates.
       * Like QExtSignal but the additional template parameter @e T_accumulator
       * defines the accumulator type that should be used.
       *
       * An accumulator is a functor that uses a pair of special iterators
       * to step through a list of slots and calculate a return value
       * from the results of the slot invokations. The iterators' operator*()
       * executes the slot. The return value is buffered, so that in an expression
       * like @code a = (*i) * (*i); @endcode the slot is executed only once.
       * The accumulator must define its return value as @p result_type.
       *
       * @par Example 1:
       * This accumulator calculates the arithmetic mean value:
       * @code
       * struct arithmetic_mean_accumulator
       * {
       *   typedef double result_type;
       *   template<typename T_iterator>
       *   result_type operator()(T_iterator first, T_iterator last) const
       *   {
       *     result_type value_ = 0;
       *     int n_ = 0;
       *     for (; first != last; ++first, ++n_)
       *       value_ += *first;
       *     return value_ / n_;
       *   }
       * };
       * @endcode
       *
       * @par Example 2:
       * This accumulator stops signal sender when a slot returns zero:
       * @code
       * struct interruptable_accumulator
       * {
       *   typedef bool result_type;
       *   template<typename T_iterator>
       *   result_type operator()(T_iterator first, T_iterator last) const
       *   {
       *     for (; first != last; ++first, ++n_)
       *       if (!*first) return false;
       *     return true;
       *   }
       * };
       * @endcode
       *
       * \ingroup signal
       */
    template < typename T_accumulator >
    class Accumulated : public detail::QExtSignal7< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_accumulator >
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &other) : detail::QExtSignal7< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_accumulator >(other) {}
    };

    QExtSignal() {}
    QExtSignal(const QExtSignal &other) : Base(other) {}

    Return send(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6,
            typename QExtTypeTrait< T_arg7 >::Take arg7) const
    {
        return Base::send(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    Return sendReverse(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6,
            typename QExtTypeTrait< T_arg7 >::Take arg7) const
    {
        return Base::sendReverse(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    Return operator()(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6,
            typename QExtTypeTrait< T_arg7 >::Take arg7) const
    {
        return Base::send(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

/** Convenience wrapper for the numbered QExtSignal6 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtSignal
 * template for 6 argument(s).
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6 >
class QExtSignal< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil >
        : public detail::QExtSignal6< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil >
{
public:
    typedef detail::QExtSignal6< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QExtNil > Base;
    typedef typename Base::Return                                                                   Return;

    /** Convenience wrapper for the numbered QExtSignal6 template.
     * Like QExtSignal but the additional template parameter @e T_accumulator
     * defines the accumulator type that should be used.
     */
    template < typename T_accumulator >
    class Accumulated : public detail::QExtSignal6< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_accumulator >
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &other) : detail::QExtSignal6< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_accumulator >(other) {}
    };

    QExtSignal() {}
    QExtSignal(const QExtSignal &other) : Base(other) {}

    Return send(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6) const
    {
        return Base::send(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    Return sendReverse(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6) const
    {
        return Base::sendReverse(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    Return operator()(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5,
            typename QExtTypeTrait< T_arg6 >::Take arg6) const
    {
        return Base::send(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

/** Convenience wrapper for the numbered QExtSignal5 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtSignal
 * template for 5 argument(s).
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5 >
class QExtSignal< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil, QExtNil > : public detail::QExtSignal5< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil >
{
public:
    typedef detail::QExtSignal5< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QExtNil > Base;
    typedef typename Base::Return                                                           Return;

    /** Convenience wrapper for the numbered QExtSignal5 template.
     * Like QExtSignal but the additional template parameter @e T_accumulator
     * defines the accumulator type that should be used.
     */
    template < typename T_accumulator >
    class Accumulated : public detail::QExtSignal5< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_accumulator >
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &other) : detail::QExtSignal5< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_accumulator >(other) {}
    };

    QExtSignal() {}
    QExtSignal(const QExtSignal &other) : Base(other) {}

    Return send(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5) const
    {
        return Base::send(arg1, arg2, arg3, arg4, arg5);
    }

    Return sendReverse(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5) const
    {
        return Base::sendReverse(arg1, arg2, arg3, arg4, arg5);
    }

    Return operator()(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4,
            typename QExtTypeTrait< T_arg5 >::Take arg5) const
    {
        return Base::send(arg1, arg2, arg3, arg4, arg5);
    }
};

/** Convenience wrapper for the numbered QExtSignal4 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtSignal
 * template for 4 argument(s).
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4 >
class QExtSignal< T_return, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil, QExtNil, QExtNil > : public detail::QExtSignal4< T_return, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil >
{
public:
    typedef detail::QExtSignal4< T_return, T_arg1, T_arg2, T_arg3, T_arg4, QExtNil > Base;
    typedef typename Base::Return                                                   Return;

    /** Convenience wrapper for the numbered QExtSignal4 template.
     * Like QExtSignal but the additional template parameter @e T_accumulator
     * defines the accumulator type that should be used.
     */
    template < typename T_accumulator >
    class Accumulated : public detail::QExtSignal4< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_accumulator >
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &other) : detail::QExtSignal4< T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_accumulator >(other) {}
    };

    QExtSignal() {}
    QExtSignal(const QExtSignal &other) : Base(other) {}

    Return send(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4) const
    {
        return Base::send(arg1, arg2, arg3, arg4);
    }

    Return sendReverse(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4) const
    {
        return Base::sendReverse(arg1, arg2, arg3, arg4);
    }

    Return operator()(
            typename QExtTypeTrait< T_arg1 >::Take arg1,
            typename QExtTypeTrait< T_arg2 >::Take arg2,
            typename QExtTypeTrait< T_arg3 >::Take arg3,
            typename QExtTypeTrait< T_arg4 >::Take arg4) const
    {
        return Base::send(arg1, arg2, arg3, arg4);
    }
};

/** Convenience wrapper for the numbered QExtSignal3 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtSignal
 * template for 3 argument(s).
 */
template < typename T_return, typename T_arg1, typename T_arg2, typename T_arg3 >
class QExtSignal< T_return, T_arg1, T_arg2, T_arg3, QExtNil, QExtNil, QExtNil, QExtNil > : public detail::QExtSignal3< T_return, T_arg1, T_arg2, T_arg3, QExtNil >
{
public:
    typedef detail::QExtSignal3< T_return, T_arg1, T_arg2, T_arg3, QExtNil > Base;
    typedef typename Base::Return                                           Return;

    /** Convenience wrapper for the numbered QExtSignal3 template.
     * Like QExtSignal but the additional template parameter @e T_accumulator
     * defines the accumulator type that should be used.
     */
    template < typename T_accumulator >
    class Accumulated : public detail::QExtSignal3< T_return, T_arg1, T_arg2, T_arg3, T_accumulator >
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &other) : detail::QExtSignal3< T_return, T_arg1, T_arg2, T_arg3, T_accumulator >(other) {}
    };

    QExtSignal() {}
    QExtSignal(const QExtSignal &other) : Base(other) {}

    Return send(typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2, typename QExtTypeTrait< T_arg3 >::Take arg3) const
    {
        return Base::send(arg1, arg2, arg3);
    }

    Return sendReverse(typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2, typename QExtTypeTrait< T_arg3 >::Take arg3) const
    {
        return Base::sendReverse(arg1, arg2, arg3);
    }

    Return operator()(typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2, typename QExtTypeTrait< T_arg3 >::Take arg3) const
    {
        return Base::send(arg1, arg2, arg3);
    }
};

/** Convenience wrapper for the numbered QExtSignal2 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtSignal
 * template for 2 argument(s).
 */
template < typename T_return, typename T_arg1, typename T_arg2 >
class QExtSignal< T_return, T_arg1, T_arg2, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > : public detail::QExtSignal2< T_return, T_arg1, T_arg2, QExtNil >
{
public:
    typedef detail::QExtSignal2< T_return, T_arg1, T_arg2, QExtNil > Base;
    typedef typename Base::Return                                   Return;

    /** Convenience wrapper for the numbered QExtSignal2 template.
     * Like QExtSignal but the additional template parameter @e T_accumulator
     * defines the accumulator type that should be used.
     */
    template < typename T_accumulator >
    class Accumulated : public detail::QExtSignal2< T_return, T_arg1, T_arg2, T_accumulator >
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &other) : detail::QExtSignal2< T_return, T_arg1, T_arg2, T_accumulator >(other) {}
    };

    QExtSignal() {}
    QExtSignal(const QExtSignal &other) : Base(other) {}

    Return send(typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2) const
    {
        return Base::send(arg1, arg2);
    }

    Return sendReverse(typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2) const
    {
        return Base::sendReverse(arg1, arg2);
    }

    Return operator()(typename QExtTypeTrait< T_arg1 >::Take arg1, typename QExtTypeTrait< T_arg2 >::Take arg2) const
    {
        return Base::send(arg1, arg2);
    }
};

/** Convenience wrapper for the numbered QExtSignal1 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtSignal
 * template for 1 argument(s).
 */
template < typename T_return, typename T_arg1 >
class QExtSignal< T_return, T_arg1, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > : public detail::QExtSignal1< T_return, T_arg1, QExtNil >
{
public:
    typedef detail::QExtSignal1< T_return, T_arg1, QExtNil > Base;
    typedef typename Base::Return                           Return;

    /** Convenience wrapper for the numbered QExtSignal1 template.
     * Like QExtSignal but the additional template parameter @e T_accumulator
     * defines the accumulator type that should be used.
     */
    template < typename T_accumulator >
    class Accumulated : public detail::QExtSignal1< T_return, T_arg1, T_accumulator >
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &other) : detail::QExtSignal1< T_return, T_arg1, T_accumulator >(other) {}
    };

    QExtSignal() {}
    QExtSignal(const QExtSignal &other) : Base(other) {}

    Return send(typename QExtTypeTrait< T_arg1 >::Take arg1) const
    {
        return Base::send(arg1);
    }

    Return sendReverse(typename QExtTypeTrait< T_arg1 >::Take arg1) const
    {
        return Base::sendReverse(arg1);
    }

    Return operator()(typename QExtTypeTrait< T_arg1 >::Take arg1) const
    {
        return Base::send(arg1);
    }
};

/** Convenience wrapper for the numbered QExtSignal0 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QExtSignal
 * template for 0 argument(s).
 */
template < typename T_return >
class QExtSignal< T_return, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil, QExtNil > : public detail::QExtSignal0< T_return, QExtNil >
{
public:
    typedef detail::QExtSignal0< T_return, QExtNil >   Base;
    typedef typename Base::Return                           Return;

    /** Convenience wrapper for the numbered QExtSignal0 template.
     * Like QExtSignal but the additional template parameter @e T_accumulator
     * defines the accumulator type that should be used.
     */
    template < typename T_accumulator >
    class Accumulated : public detail::QExtSignal0< T_return, T_accumulator >
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &other) : detail::QExtSignal0< T_return, T_accumulator >(other) {}
    };

    QExtSignal() {}
    QExtSignal(const QExtSignal &other) : Base(other) {}

    Return send() const
    {
        return Base::send();
    }

    Return sendReverse() const
    {
        return Base::sendReverse();
    }

    Return operator()() const
    {
        return Base::send();
    }
};


#endif // _QEXTSIGNAL_H
