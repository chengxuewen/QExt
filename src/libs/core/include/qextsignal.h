#ifndef QEXTSIGNAL_H
#define QEXTSIGNAL_H

#include <qextglobal.h>
#include <qextsignalbase.h>

#include <list>

template <typename T_slot>
struct QEXTSlotIterator
{
    typedef std::size_t                         SizeType;
    typedef T_slot                              SlotType;
    typedef T_slot                              ValueType;
    typedef T_slot*                             PointerType;
    typedef T_slot&                             ReferenceType;

    typedef typename qextinternal::QEXTSignalImpl::IteratorType IteratorType;

    QEXTSlotIterator() {}
    explicit QEXTSlotIterator(const IteratorType &iter) : m_iter(iter) {}

    ReferenceType operator*() const {
        return static_cast<ReferenceType>(*m_iter);
    }

    PointerType operator->() const {
        return &(operator*());
    }

    QEXTSlotIterator& operator++() {
        ++m_iter;
        return *this;
    }

    QEXTSlotIterator operator++(int) {
        QEXTSlotIterator tmpIter(*this);
        ++m_iter;
        return tmpIter;
    }

    QEXTSlotIterator& operator--() {
        --m_iter;
        return *this;
    }

    QEXTSlotIterator operator--(int) {
        QEXTSlotIterator tmpIter(*this);
        --m_iter;
        return tmpIter;
    }

    bool operator == (const QEXTSlotIterator &other) const {
        return m_iter == other.m_iter;
    }

    bool operator != (const QEXTSlotIterator &other) const {
        return m_iter != other.m_iter;
    }

    IteratorType m_iter;
};


template <typename T_slot>
struct QEXTSlotConstIterator
{
    typedef std::size_t                         SizeType;
    typedef T_slot                              SlotType;
    typedef T_slot                              ValueType;
    typedef const T_slot*                       PointerType;
    typedef const T_slot&                       ReferenceType;

    typedef typename qextinternal::QEXTSignalImpl::ConstIteratorType IteratorType;

    QEXTSlotConstIterator() {}

    explicit QEXTSlotConstIterator(const IteratorType &iter) : m_iter(iter) {}

    ReferenceType operator*() const {
        return static_cast<ReferenceType>(*m_iter);
    }

    PointerType operator->() const {
        return &(operator*());
    }

    QEXTSlotConstIterator& operator++() {
        ++m_iter;
        return *this;
    }

    QEXTSlotConstIterator operator++(int) {
        QEXTSlotConstIterator tmpIter(*this);
        ++m_iter;
        return tmpIter;
    }

    QEXTSlotConstIterator& operator--() {
        --m_iter;
        return *this;
    }

    QEXTSlotConstIterator operator--(int) {
        QEXTSlotConstIterator tmpIter(*this);
        --m_iter;
        return tmpIter;
    }

    bool operator == (const QEXTSlotConstIterator &other) const {
        return m_iter == other.m_iter;
    }

    bool operator != (const QEXTSlotConstIterator &other) const {
        return m_iter != other.m_iter;
    }

    IteratorType m_iter;
};

/** list interface for QEXTSignal#.
 * QEXTSlotList can be used to iterate over the list of slots that
 * is managed by a signal. Slots can be added or removed from
 * the list while existing iterators stay valid. A slot_list
 * object can be retrieved from the signal's slotList() function.
 *
 * @ingroup signal
 */
template <typename T_slot>
struct QEXTSlotList
{
    typedef T_slot                                  SlotType;

    typedef SlotType&                               ReferenceType;
    typedef const SlotType&                         ConstReferenceType;

    typedef QEXTSlotIterator<SlotType>              Iterator;
    typedef QEXTSlotConstIterator<SlotType>         ConstIterator;

    typedef std::reverse_iterator<Iterator>         ReverseIterator;
    typedef std::reverse_iterator<ConstIterator>    ConstReverseIterator;

    QEXTSlotList() : m_list(QEXT_NULLPTR) {}

    explicit QEXTSlotList(qextinternal::QEXTSignalImpl *list) : m_list(list) {}

    Iterator begin() {
        return Iterator(m_list->m_slotList.begin());
    }

    ConstIterator begin() const {
        return ConstIterator(m_list->m_slotList.begin());
    }

    Iterator end() {
        return Iterator(m_list->m_slotList.end());
    }

    ConstIterator end() const {
        return ConstIterator(m_list->m_slotList.end());
    }

    ReverseIterator rbegin() {
        return ReverseIterator(this->end());
    }

    ConstReverseIterator rbegin() const {
        return ConstReverseIterator(this->end());
    }

    ReverseIterator rend() {
        return ReverseIterator(this->begin());
    }

    ConstReverseIterator rend() const {
        return ConstReverseIterator(this->begin());
    }

    ReferenceType front() {
        return *this->begin();
    }

    ConstReferenceType front() const {
        return *this->begin();
    }

    ReferenceType back() {
        return *(--this->end());
    }

    ConstReferenceType back() const {
        return *(--this->end());
    }

    Iterator insert(Iterator i, const SlotType &slot) {
        return Iterator(m_list->insert(i.m_iter, static_cast<const QEXTSlotBase&>(slot)));
    }

    void push_front(const SlotType &c) {
        this->insert(this->begin(), c);
    }

    void push_back(const SlotType &c) {
        this->insert(this->end(), c);
    }

    Iterator erase(Iterator i) {
        return Iterator(m_list->erase(i.m_iter));
    }

    Iterator erase(Iterator first, Iterator last) {
        while (first != last) {
            first = this->erase(first);
        }
        return last;
    }

    void pop_front() {
        this->erase(this->begin());
    }

    void pop_back() {
        Iterator tmp = this->end();
        this->erase(--tmp);
    }

protected:
    qextinternal::QEXTSignalImpl *m_list;
};


namespace qextinternal {

/** Special iterator over QEXTSignalImpl's slot list that holds extra data.
 * This iterators is for use in accumulators. operator*() executes
 * the slot. The return value is buffered, so that in an expression
 * like @code a = (*i) * (*i); @endcode the slot is executed only once.
 */
template <typename T_emitter, typename T_result = typename T_emitter::ResultType>
struct QEXTSlotIteratorBuffer
{
    typedef std::size_t                         SizeType;

    //These are needed just to make this a proper C++ Iterator,
    //that can be used with standard C++ algorithms.
    typedef T_result                            ValueType;
    typedef T_result&                           ReferenceType;
    typedef T_result*                           PointerType;

    typedef T_emitter                           SenderType;
    typedef T_result                            ResultType;
    typedef typename T_emitter::SlotType        SlotType;

    typedef QEXTSignalImpl::ConstIteratorType   IteratorType;

    QEXTSlotIteratorBuffer() : m_sender(QEXT_NULLPTR), m_invoked(false) {}

    QEXTSlotIteratorBuffer(const IteratorType &iter, const SenderType *sender)
        : m_iter(iter), m_sender(sender), m_invoked(false) {}

    ResultType operator*() const {
        if (!m_iter->isEmpty() && !m_iter->isBlocked() && !m_invoked) {
            m_result = (*m_sender)(static_cast<const SlotType&>(*m_iter));
            m_invoked = true;
        }
        return m_result;
    }

    QEXTSlotIteratorBuffer& operator++() {
        ++m_iter;
        m_invoked = false;
        return *this;
    }

    QEXTSlotIteratorBuffer operator++(int) {
        QEXTSlotIteratorBuffer tmp(*this);
        ++m_iter;
        m_invoked = false;
        return tmp;
    }

    QEXTSlotIteratorBuffer& operator--() {
        --m_iter;
        m_invoked = false;
        return *this;
    }

    QEXTSlotIteratorBuffer operator--(int) {
        QEXTSlotIteratorBuffer tmp(*this);
        --m_iter;
        m_invoked = false;
        return tmp;
    }

    bool operator == (const QEXTSlotIteratorBuffer &other) const {
        /* If '!m_sender' the iterators are empty.
         * Unfortunately, empty stl iterators are not equal.
         * We are forcing equality so that 'first==last'
         * in the accumulator's send function yields true. */
        return (!m_sender || (m_iter == other.m_iter));
    }

    bool operator != (const QEXTSlotIteratorBuffer &other) const {
        return (m_sender && (m_iter != other.m_iter));
    }

private:
    IteratorType m_iter;
    const SenderType *m_sender;
    mutable ResultType m_result;
    mutable bool m_invoked;
};

/** Template specialization of QEXTSlotIteratorBuffer for void return signals.
 */
template <typename T_emitter>
struct QEXTSlotIteratorBuffer<T_emitter, void>
{
    typedef std::size_t                         SizeType;

    typedef T_emitter                           SenderType;
    typedef void                                ResultType;
    typedef typename T_emitter::SlotType        SlotType;

    typedef QEXTSignalImpl::ConstIteratorType   IteratorType;

    QEXTSlotIteratorBuffer() : m_sender(QEXT_NULLPTR), m_invoked(false) {}

    QEXTSlotIteratorBuffer(const IteratorType &iter, const SenderType *sender)
        : m_iter(iter), m_sender(sender), m_invoked(false) {}

    void operator*() const {
        if (!m_iter->isEmpty() && !m_iter->isBlocked() && !m_invoked) {
            (*m_sender)(static_cast<const SlotType&>(*m_iter));
            m_invoked = true;
        }
    }

    QEXTSlotIteratorBuffer& operator++() {
        ++m_iter;
        m_invoked = false;
        return *this;
    }

    QEXTSlotIteratorBuffer operator++(int) {
        QEXTSlotIteratorBuffer tmp(*this);
        ++m_iter;
        m_invoked = false;
        return tmp;
    }

    QEXTSlotIteratorBuffer& operator--() {
        --m_iter;
        m_invoked = false;
        return *this;
    }

    QEXTSlotIteratorBuffer operator--(int) {
        QEXTSlotIteratorBuffer tmp(*this);
        --m_iter;
        m_invoked = false;
        return tmp;
    }

    bool operator == (const QEXTSlotIteratorBuffer &other) const {
        return m_iter == other.m_iter;
    }

    bool operator != (const QEXTSlotIteratorBuffer &other) const {
        return m_iter != other.m_iter;
    }

private:
    IteratorType m_iter;
    const SenderType *m_sender;
    mutable bool m_invoked;
};

/** Reverse version of QEXTSlotIteratorBuffer. */
template <typename T_emitter, typename T_result = typename T_emitter::ResultType>
struct QEXTSlotReverseIteratorBuffer
{
    typedef std::size_t                         SizeType;

    //These are needed just to make this a proper C++ Iterator,
    //that can be used with standard C++ algorithms.
    typedef T_result                            ValueType;
    typedef T_result&                           ReferenceType;
    typedef T_result*                           PointerType;

    typedef T_emitter                           SenderType;
    typedef T_result                            ResultType;
    typedef typename T_emitter::SlotType        SlotType;

    typedef QEXTSignalImpl::ConstIteratorType   IteratorType;

    QEXTSlotReverseIteratorBuffer() : m_sender(QEXT_NULLPTR), m_invoked(false) {}

    QEXTSlotReverseIteratorBuffer(const IteratorType &iter, const SenderType *sender)
        : m_iter(iter), m_sender(sender), m_invoked(false) {}

    ResultType operator*() const {
        IteratorType tmp(m_iter);
        --tmp;
        if (!tmp->isEmpty() && !tmp->isBlocked() && !m_invoked) {
            m_result = (*m_sender)(static_cast<const SlotType&>(*tmp));
            m_invoked = true;
        }
        return m_result;
    }

    QEXTSlotReverseIteratorBuffer& operator++() {
        --m_iter;
        m_invoked = false;
        return *this;
    }

    QEXTSlotReverseIteratorBuffer operator++(int) {
        QEXTSlotReverseIteratorBuffer tmp(*this);
        --m_iter;
        m_invoked = false;
        return tmp;
    }

    QEXTSlotReverseIteratorBuffer& operator--() {
        ++m_iter;
        m_invoked = false;
        return *this;
    }

    QEXTSlotReverseIteratorBuffer operator--(int) {
        QEXTSlotReverseIteratorBuffer tmp(*this);
        ++m_iter;
        m_invoked = false;
        return tmp;
    }

    bool operator == (const QEXTSlotReverseIteratorBuffer &other) const {
        /* If '!m_sender' the iterators are empty.
         * Unfortunately, empty stl iterators are not equal.
         * We are forcing equality so that 'first==last'
         * in the accumulator's send function yields true. */
        return (!m_sender || (m_iter == other.m_iter));
    }

    bool operator != (const QEXTSlotReverseIteratorBuffer &other) const {
        return (m_sender && (m_iter != other.m_iter));
    }

private:
    IteratorType m_iter;
    const SenderType *m_sender;
    mutable ResultType m_result;
    mutable bool m_invoked;
};

/** Template specialization of QEXTSlotReverseIteratorBuffer for void return signals.
 */
template <typename T_emitter>
struct QEXTSlotReverseIteratorBuffer<T_emitter, void>
{
    typedef std::size_t                         SizeType;

    typedef T_emitter                           SenderType;
    typedef void                                ResultType;
    typedef typename T_emitter::SlotType        SlotType;

    typedef QEXTSignalImpl::ConstIteratorType   IteratorType;

    QEXTSlotReverseIteratorBuffer() : m_sender(QEXT_NULLPTR), m_invoked(false) {}

    QEXTSlotReverseIteratorBuffer(const IteratorType &iter, const SenderType *sender)
        : m_iter(iter), m_sender(sender), m_invoked(false) {}

    void operator*() const {
        IteratorType tmp(m_iter);
        --tmp;
        if (!tmp->isEmpty() && !tmp->isBlocked() && !m_invoked) {
            (*m_sender)(static_cast<const SlotType&>(*tmp));
            m_invoked = true;
        }
    }

    QEXTSlotReverseIteratorBuffer& operator++() {
        --m_iter;
        m_invoked = false;
        return *this;
    }

    QEXTSlotReverseIteratorBuffer operator++(int) {
        QEXTSlotReverseIteratorBuffer tmp(*this);
        --m_iter;
        m_invoked = false;
        return tmp;
    }

    QEXTSlotReverseIteratorBuffer& operator--() {
        ++m_iter;
        m_invoked = false;
        return *this;
    }

    QEXTSlotReverseIteratorBuffer operator--(int) {
        QEXTSlotReverseIteratorBuffer tmp(*this);
        ++m_iter;
        m_invoked = false;
        return tmp;
    }

    bool operator == (const QEXTSlotReverseIteratorBuffer &other) const {
        return m_iter == other.m_iter;
    }

    bool operator != (const QEXTSlotReverseIteratorBuffer &other) const {
        return m_iter != other.m_iter;
    }

private:
    IteratorType m_iter;
    const SenderType *m_sender;
    mutable bool m_invoked;
};

/** Abstracts signal sender.
 * This template implements the send() function of QEXTSignal0.
 * Template specializations are available to optimize signal
 * sender when no accumulator is used, for example when the template
 * argument @e T_accumulator is @p QEXTNil.
 */
template <typename T_return, typename T_accumulator>
struct QEXTSignalSend0
{
    typedef QEXTSignalSend0<T_return, T_accumulator>                        SelfType;
    typedef typename T_accumulator::ResultType                              ResultType;
    typedef QEXTSlot<T_return>                                              SlotType;
    typedef qextinternal::QEXTSlotIteratorBuffer<SelfType, T_return>        SlotIteratorBufferType;
    typedef qextinternal::QEXTSlotReverseIteratorBuffer<SelfType, T_return> SlotReverseIteratorBufferType;
    typedef QEXTSignalImpl::ConstIteratorType                               IteratorType;

    QEXTSignalSend0()  {}

    /** Invokes a slot.
     * @param slot Some slot to invoke.
     * @return The slot's return value.
     */
    T_return operator()(const SlotType &slot) const {
        return (reinterpret_cast<typename SlotType::CallType>(slot.m_slotRep->m_call))(slot.m_slotRep.data());
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * @return The accumulated return values of the slot invocations as processed by the accumulator.
     */
    static ResultType send(QEXTSignalImpl *impl) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self;
        return accumulator(SlotIteratorBufferType(slotList.begin(), &self),
                           SlotIteratorBufferType(slotList.end(), &self));
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * @return The accumulated return values of the slot invocations as processed by the accumulator.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self ;
        return accumulator(SlotReverseIteratorBufferType(slotList.end(), &self),
                           SlotReverseIteratorBufferType(slotList.begin(), &self));
    }

};

/** Abstracts signal sender.
 * This template specialization implements an optimized send()
 * function for the case that no accumulator is used.
 */
template <typename T_return>
struct QEXTSignalSend0<T_return, QEXTNil>
{
    typedef QEXTSignalSend0<T_return, QEXTNil>  SelfType;
    typedef T_return                            ResultType;
    typedef QEXTSlot<T_return>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType   IteratorType;
    typedef typename SlotType::CallType         CallType;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The return value of the last slot invoked is returned.
     * @return The return value of the last slot invoked.
     */
    static ResultType send(QEXTSignalImpl *impl) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExecution execution(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QEXTTempSlotList slotList(impl->m_slotList);
            IteratorType iter = slotList.begin();
            for (; iter != slotList.end(); ++iter) {
                if (!iter->isEmpty() && !iter->isBlocked()) {
                    break;
                }
            }

            if (iter == slotList.end()) {
                // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
                return T_return();
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data());
            for (++iter; iter != slotList.end(); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data());
            }
        }

        return m_result;
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The return value of the last slot invoked is returned.
     * @param first An iterator pointing to the first slot in the list.
     * @param last An iterator pointing to the last slot in the list.
     * @return The return value of the last slot invoked.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExecution execution(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;

            QEXTTempSlotList slotList(impl->m_slotList);
            ReverseIteratorType iter(slotList.end());
            for (; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (!iter->isEmpty() && !iter->isBlocked()) {
                    break;
                }
            }

            if (iter == ReverseIteratorType(slotList.begin())) {
                // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
                return T_return();
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data());
            for (++iter; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data());
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
struct QEXTSignalSend0<void, QEXTNil>
{
    typedef QEXTSignalSend0<void, QEXTNil> SelfType;
    typedef void ResultType;
    typedef QEXTSlot<void> SlotType;
    typedef QEXTSignalImpl::ConstIteratorType IteratorType;
    typedef void (*CallType)(QEXTSlotRep *);

    static ResultType send(QEXTSignalImpl *impl) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        for (IteratorType iter = slotList.begin(); iter != slotList.end(); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data());
        }
    }

    static ResultType sendReverse(QEXTSignalImpl *impl) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;

        for (ReverseIteratorType iter = ReverseIteratorType(slotList.end()); iter != ReverseIteratorType(slotList.begin()); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data());
        }
    }
};


/** Abstracts signal sender.
 * This template implements the send() function of QEXTSignal1.
 * Template specializations are available to optimize signal
 * sender when no accumulator is used, for example when the template
 * argument @e T_accumulator is @p QEXTNil.
 */
template <typename T_return, typename T_arg1, typename T_accumulator>
struct QEXTSignalSend1
{
    typedef QEXTSignalSend1<T_return, T_arg1, T_accumulator>                SelfType;
    typedef typename T_accumulator::ResultType                              ResultType;
    typedef QEXTSlot<T_return, T_arg1>                                      SlotType;
    typedef qextinternal::QEXTSlotIteratorBuffer<SelfType, T_return>        SlotIteratorBufferType;
    typedef qextinternal::QEXTSlotReverseIteratorBuffer<SelfType, T_return> SlotReverseIteratorBufferType;
    typedef QEXTSignalImpl::ConstIteratorType                               IteratorType;

    /** Instantiates the class.
     * The parameters are stored in member variables. operator()() passes
     * the values on to some slot.
     */
    QEXTSignalSend1(typename QEXTTypeTrait<T_arg1>::Take arg1) : m_arg1(arg1) {}

    /** Invokes a slot using the buffered parameter values.
     * @param slot Some slot to invoke.
     * @return The slot's return value.
     */
    T_return operator()(const SlotType &slot) const {
        return (reinterpret_cast<typename SlotType::CallType>(slot.m_slotRep->m_call))(slot.m_slotRep.data(), m_arg1);
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are buffered in a temporary instance of QEXTSignalSend1.

     * @param arg1 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations as processed by the accumulator.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self(arg1);
        return accumulator(SlotIteratorBufferType(slotList.begin(), &self),
                           SlotIteratorBufferType(slotList.end(), &self));
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are buffered in a temporary instance of QEXTSignalSend1.

     * @param arg1 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations as processed by the accumulator.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self (arg1);
        return accumulator(SlotReverseIteratorBufferType(slotList.end(), &self),
                           SlotReverseIteratorBufferType(slotList.begin(), &self));
    }

    typename QEXTTypeTrait<T_arg1>::Take m_arg1;
};

/** Abstracts signal sender.
 * This template specialization implements an optimized send()
 * function for the case that no accumulator is used.
 */
template <typename T_return, typename T_arg1>
struct QEXTSignalSend1<T_return, T_arg1, QEXTNil>
{
    typedef QEXTSignalSend1<T_return, T_arg1, QEXTNil >     SelfType;
    typedef T_return                                        ResultType;
    typedef QEXTSlot<T_return, T_arg1>                      SlotType;
    typedef QEXTSignalImpl::ConstIteratorType               IteratorType;
    typedef typename SlotType::CallType                     CallType;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are passed directly on to the slots.
     * The return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @return The return value of the last slot invoked.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExecution execution(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QEXTTempSlotList slotList(impl->m_slotList);
            IteratorType iter = slotList.begin();
            for (; iter != slotList.end(); ++iter) {
                if (!iter->isEmpty() && !iter->isBlocked()) break;
            }

            if (iter == slotList.end()) {
                // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
                return T_return();
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1);
            for (++iter; iter != slotList.end(); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1);
            }
        }

        return m_result;
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are passed directly on to the slots.
     * The return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @return The return value of the last slot invoked.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExecution execution(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;

            QEXTTempSlotList slotList(impl->m_slotList);
            ReverseIteratorType iter(slotList.end());
            for (; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (!iter->isEmpty() && !iter->isBlocked()) {
                    break;
                }
            }

            if (iter == ReverseIteratorType(slotList.begin())) {
                // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
                return T_return();
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1);
            for (++iter; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1);
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
template <typename T_arg1>
struct QEXTSignalSend1<void, T_arg1, QEXTNil>
{
    typedef QEXTSignalSend1<void, T_arg1, QEXTNil>  SelfType;
    typedef void                                    ResultType;
    typedef QEXTSlot<void, T_arg1>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType       IteratorType;
    typedef typename SlotType::CallType             CallType;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are passed directly on to the slots.
     * @param arg1 Argument to be passed on to the slots.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        for (IteratorType iter = slotList.begin(); iter != slotList.end(); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1);
        }
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are passed directly on to the slots.
     * @param arg1 Argument to be passed on to the slots.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;
        for (ReverseIteratorType iter = ReverseIteratorType(slotList.end()); iter != ReverseIteratorType(slotList.begin()); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1);
        }
    }
};

/** Abstracts signal sender.
 * This template implements the send() function of QEXTSignal2.
 * Template specializations are available to optimize signal
 * sender when no accumulator is used, for example when the template
 * argument @e T_accumulator is @p QEXTNil.
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_accumulator>
struct QEXTSignalSend2
{
    typedef QEXTSignalSend2<T_return, T_arg1, T_arg2, T_accumulator>            SelfType;
    typedef typename T_accumulator::ResultType                                  ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2>                                  SlotType;
    typedef qextinternal::QEXTSlotIteratorBuffer<SelfType, T_return>            SlotIteratorBufferType;
    typedef qextinternal::QEXTSlotReverseIteratorBuffer<SelfType, T_return>     SlotReverseIteratorBufferType;
    typedef QEXTSignalImpl::ConstIteratorType                                   IteratorType;

    /** Instantiates the class.
     * The parameters are stored in member variables. operator()() passes
     * the values on to some slot.
     */
    QEXTSignalSend2(typename QEXTTypeTrait<T_arg1>::Take arg1, typename QEXTTypeTrait<T_arg2>::Take arg2)
        : m_arg1(arg1), m_arg2(arg2) {}

    /** Invokes a slot using the buffered parameter values.
     * @param slot Some slot to invoke.
     * @return The slot's return value.
     */
    T_return operator()(const SlotType &slot) const {
        return (reinterpret_cast<typename SlotType::CallType>(slot.m_slotRep->m_call))(slot.m_slotRep.data(), m_arg1, m_arg2);
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are buffered in a temporary instance of QEXTSignalSend2.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations as processed by the accumulator.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self (arg1, arg2);
        return accumulator(SlotIteratorBufferType(slotList.begin(), &self),
                           SlotIteratorBufferType(slotList.end(), &self));
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are buffered in a temporary instance of QEXTSignalSend2.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations as processed by the accumulator.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self (arg1, arg2);
        return accumulator(SlotReverseIteratorBufferType(slotList.end(), &self),
                           SlotReverseIteratorBufferType(slotList.begin(), &self));
    }

    typename QEXTTypeTrait<T_arg1>::Take m_arg1;
    typename QEXTTypeTrait<T_arg2>::Take m_arg2;
};

/** Abstracts signal sender.
 * This template specialization implements an optimized send()
 * function for the case that no accumulator is used.
 */
template <typename T_return, typename T_arg1, typename T_arg2>
struct QEXTSignalSend2<T_return, T_arg1, T_arg2, QEXTNil>
{
    typedef QEXTSignalSend2<T_return, T_arg1, T_arg2, QEXTNil >     SelfType;
    typedef T_return                                                ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2>                      SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                       IteratorType;
    typedef typename SlotType::CallType                             CallType;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are passed directly on to the slots.
     * The return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @return The return value of the last slot invoked.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExecution execution(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QEXTTempSlotList slotList(impl->m_slotList);
            IteratorType iter = slotList.begin();
            for (; iter != slotList.end(); ++iter) {
                if (!iter->isEmpty() && !iter->isBlocked()) {
                    break;
                }
            }

            if (iter == slotList.end()) {
                return T_return(); // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2);
            for (++iter; iter != slotList.end(); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2);
            }
        }

        return m_result;
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are passed directly on to the slots.
     * The return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @return The return value of the last slot invoked.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExecution execution(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;

            QEXTTempSlotList slotList(impl->m_slotList);
            ReverseIteratorType iter(slotList.end());
            for (; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (!iter->isEmpty() && !iter->isBlocked()) {
                    break;
                }
            }

            if (iter == ReverseIteratorType(slotList.begin())) {
                // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
                return T_return();
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2);
            for (++iter; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2);
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
template <typename T_arg1, typename T_arg2>
struct QEXTSignalSend2<void, T_arg1, T_arg2, QEXTNil>
{
    typedef QEXTSignalSend2<void, T_arg1, T_arg2, QEXTNil>  SelfType;
    typedef void                                            ResultType;
    typedef QEXTSlot<void, T_arg1, T_arg2>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType               IteratorType;
    typedef typename SlotType::CallType                     CallType;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are passed directly on to the slots.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        for (IteratorType iter = slotList.begin(); iter != slotList.end(); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2);
        }
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are passed directly on to the slots.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;

        for (ReverseIteratorType iter = ReverseIteratorType(slotList.end()); iter != ReverseIteratorType(slotList.begin()); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2);
        }
    }
};

/** Abstracts signal sender.
 * This template implements the send() function of QEXTSignal3.
 * Template specializations are available to optimize signal
 * sender when no accumulator is used, for example when the template
 * argument @e T_accumulator is @p QEXTNil.
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_accumulator>
struct QEXTSignalSend3
{
    typedef QEXTSignalSend3<T_return, T_arg1, T_arg2, T_arg3, T_accumulator>    SelfType;
    typedef typename T_accumulator::ResultType                                  ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3>                          SlotType;
    typedef qextinternal::QEXTSlotIteratorBuffer<SelfType, T_return>            SlotIteratorBufferType;
    typedef qextinternal::QEXTSlotReverseIteratorBuffer<SelfType, T_return>     SlotReverseIteratorBufferType;
    typedef QEXTSignalImpl::ConstIteratorType                                   IteratorType;

    /** Instantiates the class.
     * The parameters are stored in member variables. operator()() passes
     * the values on to some slot.
     */
    QEXTSignalSend3(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3)
        : m_arg1(arg1), m_arg2(arg2), m_arg3(arg3) {}

    /** Invokes a slot using the buffered parameter values.
     * @param slot Some slot to invoke.
     * @return The slot's return value.
     */
    T_return operator()(const SlotType &slot) const {
        return (reinterpret_cast<typename SlotType::CallType>(slot.m_slotRep->m_call))(slot.m_slotRep.data(), m_arg1, m_arg2, m_arg3);
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are buffered in a temporary instance of QEXTSignalSend3.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations as processed by the accumulator.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self (arg1, arg2, arg3);
        return accumulator(SlotIteratorBufferType(slotList.begin(), &self),
                           SlotIteratorBufferType(slotList.end(), &self));
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are buffered in a temporary instance of QEXTSignalSend3.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations as processed by the accumulator.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self(arg1, arg2, arg3);
        return accumulator(SlotReverseIteratorBufferType(slotList.end(), &self),
                           SlotReverseIteratorBufferType(slotList.begin(), &self));
    }

    typename QEXTTypeTrait<T_arg1>::Take m_arg1;
    typename QEXTTypeTrait<T_arg2>::Take m_arg2;
    typename QEXTTypeTrait<T_arg3>::Take m_arg3;
};

/** Abstracts signal sender.
 * This template specialization implements an optimized send()
 * function for the case that no accumulator is used.
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTSignalSend3<T_return, T_arg1, T_arg2, T_arg3, QEXTNil>
{
    typedef QEXTSignalSend3<T_return, T_arg1, T_arg2, T_arg3, QEXTNil > SelfType;
    typedef T_return                                                    ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                           IteratorType;
    typedef typename SlotType::CallType                                 CallType;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are passed directly on to the slots.
     * The return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @return The return value of the last slot invoked.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExecution execution(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QEXTTempSlotList slotList(impl->m_slotList);
            IteratorType iter = slotList.begin();
            for (; iter != slotList.end(); ++iter) {
                if (!iter->isEmpty() && !iter->isBlocked()) {
                    break;
                }
            }

            if (iter == slotList.end()) {
                // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
                return T_return();
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3);
            for (++iter; iter != slotList.end(); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3);
            }
        }

        return m_result;
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are passed directly on to the slots.
     * The return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @return The return value of the last slot invoked.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExecution execution(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;

            QEXTTempSlotList slotList(impl->m_slotList);
            ReverseIteratorType iter(slotList.end());
            for (; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (!iter->isEmpty() && !iter->isBlocked()) {
                    break;
                }
            }

            if (iter == ReverseIteratorType(slotList.begin())) {
                // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
                return T_return();
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3);
            for (++iter; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3);
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
template <typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTSignalSend3<void, T_arg1, T_arg2, T_arg3, QEXTNil>
{
    typedef QEXTSignalSend3<void, T_arg1, T_arg2, T_arg3, QEXTNil>  SelfType;
    typedef void                                                    ResultType;
    typedef QEXTSlot<void, T_arg1, T_arg2, T_arg3>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                       IteratorType;
    typedef typename SlotType::CallType                             CallType;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are passed directly on to the slots.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }

        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        for (IteratorType iter = slotList.begin(); iter != slotList.end(); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3);
        }
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are passed directly on to the slots.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;

        for (ReverseIteratorType iter = ReverseIteratorType(slotList.end()); iter != ReverseIteratorType(slotList.begin()); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3);
        }
    }
};

/** Abstracts signal sender.
 * This template implements the send() function of QEXTSignal4.
 * Template specializations are available to optimize signal
 * sender when no accumulator is used, for example when the template
 * argument @e T_accumulator is @p QEXTNil.
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_accumulator>
struct QEXTSignalSend4
{
    typedef QEXTSignalSend4<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_accumulator>    SelfType;
    typedef typename T_accumulator::ResultType                                          ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4>                          SlotType;
    typedef qextinternal::QEXTSlotIteratorBuffer<SelfType, T_return>                    SlotIteratorBufferType;
    typedef qextinternal::QEXTSlotReverseIteratorBuffer<SelfType, T_return>             SlotReverseIteratorBufferType;
    typedef QEXTSignalImpl::ConstIteratorType                                           IteratorType;

    /** Instantiates the class.
     * The parameters are stored in member variables. operator()() passes
     * the values on to some slot.
     */
    QEXTSignalSend4(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4)
        : m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4) {}

    /** Invokes a slot using the buffered parameter values.
     * @param slot Some slot to invoke.
     * @return The slot's return value.
     */
    T_return operator()(const SlotType &slot) const {
        return (reinterpret_cast<typename SlotType::CallType>(slot.m_slotRep->m_call))(slot.m_slotRep.data(), m_arg1, m_arg2, m_arg3, m_arg4);
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are buffered in a temporary instance of QEXTSignalSend4.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations as processed by the accumulator.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self(arg1, arg2, arg3, arg4);
        return accumulator(SlotIteratorBufferType(slotList.begin(), &self),
                           SlotIteratorBufferType(slotList.end(), &self));
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are buffered in a temporary instance of QEXTSignalSend4.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations as processed by the accumulator.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3,
                                  typename QEXTTypeTrait<T_arg4>::Take arg4) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self(arg1, arg2, arg3, arg4);
        return accumulator(SlotReverseIteratorBufferType(slotList.end(), &self),
                           SlotReverseIteratorBufferType(slotList.begin(), &self));
    }

    typename QEXTTypeTrait<T_arg1>::Take m_arg1;
    typename QEXTTypeTrait<T_arg2>::Take m_arg2;
    typename QEXTTypeTrait<T_arg3>::Take m_arg3;
    typename QEXTTypeTrait<T_arg4>::Take m_arg4;
};

/** Abstracts signal sender.
 * This template specialization implements an optimized send()
 * function for the case that no accumulator is used.
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTSignalSend4<T_return, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil>
{
    typedef QEXTSignalSend4<T_return, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil > SelfType;
    typedef T_return                                                            ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                                   IteratorType;
    typedef typename SlotType::CallType                                         CallType;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are passed directly on to the slots.
     * The return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @return The return value of the last slot invoked.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExecution execution(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QEXTTempSlotList slotList(impl->m_slotList);
            IteratorType iter = slotList.begin();
            for (; iter != slotList.end(); ++iter) {
                if (!iter->isEmpty() && !iter->isBlocked()) {
                    break;
                }
            }

            if (iter == slotList.end()) {
                // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
                return T_return();
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4);
            for (++iter; iter != slotList.end(); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4);
            }
        }

        return m_result;
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are passed directly on to the slots.
     * The return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @return The return value of the last slot invoked.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3,
                                  typename QEXTTypeTrait<T_arg4>::Take arg4) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExecution execution(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;

            QEXTTempSlotList slotList(impl->m_slotList);
            ReverseIteratorType iter(slotList.end());
            for (; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (!iter->isEmpty() && !iter->isBlocked()) {
                    break;
                }
            }

            if (iter == ReverseIteratorType(slotList.begin())) {
                // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
                return T_return();
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4);
            for (++iter; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4);
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
template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTSignalSend4<void, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil>
{
    typedef QEXTSignalSend4<void, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil>  SelfType;
    typedef void                                                            ResultType;
    typedef QEXTSlot<void, T_arg1, T_arg2, T_arg3, T_arg4>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                               IteratorType;
    typedef typename SlotType::CallType                                     CallType;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are passed directly on to the slots.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        for (IteratorType iter = slotList.begin(); iter != slotList.end(); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4);
        }
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are passed directly on to the slots.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3,
                                  typename QEXTTypeTrait<T_arg4>::Take arg4) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;

        for (ReverseIteratorType iter = ReverseIteratorType(slotList.end()); iter != ReverseIteratorType(slotList.begin()); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4);
        }
    }
};

/** Abstracts signal sender.
 * This template implements the send() function of QEXTSignal5.
 * Template specializations are available to optimize signal
 * sender when no accumulator is used, for example when the template
 * argument @e T_accumulator is @p QEXTNil.
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_accumulator>
struct QEXTSignalSend5
{
    typedef QEXTSignalSend5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_accumulator>    SelfType;
    typedef typename T_accumulator::ResultType                                                  ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>                          SlotType;
    typedef qextinternal::QEXTSlotIteratorBuffer<SelfType, T_return>                            SlotIteratorBufferType;
    typedef qextinternal::QEXTSlotReverseIteratorBuffer<SelfType, T_return>                     SlotReverseIteratorBufferType;
    typedef QEXTSignalImpl::ConstIteratorType                                                   IteratorType;

    /** Instantiates the class.
     * The parameters are stored in member variables. operator()() passes
     * the values on to some slot.
     */
    QEXTSignalSend5(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4,
                    typename QEXTTypeTrait<T_arg5>::Take arg5)
        : m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5) {}

    /** Invokes a slot using the buffered parameter values.
     * @param slot Some slot to invoke.
     * @return The slot's return value.
     */
    T_return operator()(const SlotType &slot) const {
        return (reinterpret_cast<typename SlotType::CallType>(slot.m_slotRep->m_call))(slot.m_slotRep.data(), m_arg1, m_arg2, m_arg3, m_arg4, m_arg5);
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are buffered in a temporary instance of QEXTSignalSend5.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations as processed by the accumulator.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self(arg1, arg2, arg3, arg4, arg5);
        return accumulator(SlotIteratorBufferType(slotList.begin(), &self),
                           SlotIteratorBufferType(slotList.end(), &self));
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are buffered in a temporary instance of QEXTSignalSend5.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations as processed by the accumulator.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3,
                                  typename QEXTTypeTrait<T_arg4>::Take arg4,
                                  typename QEXTTypeTrait<T_arg5>::Take arg5) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self(arg1, arg2, arg3, arg4, arg5);
        return accumulator(SlotReverseIteratorBufferType(slotList.end(), &self),
                           SlotReverseIteratorBufferType(slotList.begin(), &self));
    }

    typename QEXTTypeTrait<T_arg1>::Take m_arg1;
    typename QEXTTypeTrait<T_arg2>::Take m_arg2;
    typename QEXTTypeTrait<T_arg3>::Take m_arg3;
    typename QEXTTypeTrait<T_arg4>::Take m_arg4;
    typename QEXTTypeTrait<T_arg5>::Take m_arg5;
};

/** Abstracts signal sender.
 * This template specialization implements an optimized send()
 * function for the case that no accumulator is used.
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTSignalSend5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil>
{
    typedef QEXTSignalSend5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil > SelfType;
    typedef T_return                                                                    ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                                           IteratorType;
    typedef typename SlotType::CallType                                                 CallType;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are passed directly on to the slots.
     * The return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @return The return value of the last slot invoked.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExecution execution(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QEXTTempSlotList slotList(impl->m_slotList);
            IteratorType iter = slotList.begin();
            for (; iter != slotList.end(); ++iter) {
                if (!iter->isEmpty() && !iter->isBlocked()) {
                    break;
                }
            }

            if (iter == slotList.end()) {
                // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
                return T_return();
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4, arg5);
            for (++iter; iter != slotList.end(); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4, arg5);
            }
        }

        return m_result;
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are passed directly on to the slots.
     * The return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @return The return value of the last slot invoked.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3,
                                  typename QEXTTypeTrait<T_arg4>::Take arg4,
                                  typename QEXTTypeTrait<T_arg5>::Take arg5) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExecution execution(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;

            QEXTTempSlotList slotList(impl->m_slotList);
            ReverseIteratorType iter(slotList.end());
            for (; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (!iter->isEmpty() && !iter->isBlocked()) {
                    break;
                }
            }

            if (iter == ReverseIteratorType(slotList.begin())) {
                // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
                return T_return();
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4, arg5);
            for (++iter; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4, arg5);
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
template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTSignalSend5<void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil>
{
    typedef QEXTSignalSend5<void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil>  SelfType;
    typedef void                                                                    ResultType;
    typedef QEXTSlot<void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                                       IteratorType;
    typedef typename SlotType::CallType                                             CallType;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are passed directly on to the slots.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        for (IteratorType iter = slotList.begin(); iter != slotList.end(); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4, arg5);
        }
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are passed directly on to the slots.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3,
                                  typename QEXTTypeTrait<T_arg4>::Take arg4,
                                  typename QEXTTypeTrait<T_arg5>::Take arg5) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;
        for (ReverseIteratorType iter = ReverseIteratorType(slotList.end()); iter != ReverseIteratorType(slotList.begin()); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4, arg5);
        }
    }
};

/** Abstracts signal sender.
 * This template implements the send() function of QEXTSignal6.
 * Template specializations are available to optimize signal
 * sender when no accumulator is used, for example when the template
 * argument @e T_accumulator is @p QEXTNil.
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_accumulator>
struct QEXTSignalSend6
{
    typedef QEXTSignalSend6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_accumulator>    SelfType;
    typedef typename T_accumulator::ResultType                                                          ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>                          SlotType;
    typedef qextinternal::QEXTSlotIteratorBuffer<SelfType, T_return>                                    SlotIteratorBufferType;
    typedef qextinternal::QEXTSlotReverseIteratorBuffer<SelfType, T_return>                             SlotReverseIteratorBufferType;
    typedef QEXTSignalImpl::ConstIteratorType                                                           IteratorType;

    /** Instantiates the class.
     * The parameters are stored in member variables. operator()() passes
     * the values on to some slot.
     */
    QEXTSignalSend6(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4,
                    typename QEXTTypeTrait<T_arg5>::Take arg5,
                    typename QEXTTypeTrait<T_arg6>::Take arg6)
        : m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5), m_arg6(arg6) {}

    /** Invokes a slot using the buffered parameter values.
     * @param slot Some slot to invoke.
     * @return The slot's return value.
     */
    T_return operator()(const SlotType &slot) const {
        return (reinterpret_cast<typename SlotType::CallType>(slot.m_slotRep->m_call))(slot.m_slotRep.data(), m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6);
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are buffered in a temporary instance of QEXTSignalSend6.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @param arg6 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations as processed by the accumulator.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5,
                           typename QEXTTypeTrait<T_arg6>::Take arg6) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self (arg1, arg2, arg3, arg4, arg5, arg6);
        return accumulator(SlotIteratorBufferType(slotList.begin(), &self),
                           SlotIteratorBufferType(slotList.end(), &self));
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are buffered in a temporary instance of QEXTSignalSend6.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @param arg6 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations as processed by the accumulator.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3,
                                  typename QEXTTypeTrait<T_arg4>::Take arg4,
                                  typename QEXTTypeTrait<T_arg5>::Take arg5,
                                  typename QEXTTypeTrait<T_arg6>::Take arg6) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self(arg1, arg2, arg3, arg4, arg5, arg6);
        return accumulator(SlotReverseIteratorBufferType(slotList.end(), &self),
                           SlotReverseIteratorBufferType(slotList.begin(), &self));
    }

    typename QEXTTypeTrait<T_arg1>::Take m_arg1;
    typename QEXTTypeTrait<T_arg2>::Take m_arg2;
    typename QEXTTypeTrait<T_arg3>::Take m_arg3;
    typename QEXTTypeTrait<T_arg4>::Take m_arg4;
    typename QEXTTypeTrait<T_arg5>::Take m_arg5;
    typename QEXTTypeTrait<T_arg6>::Take m_arg6;
};

/** Abstracts signal sender.
 * This template specialization implements an optimized send()
 * function for the case that no accumulator is used.
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTSignalSend6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
{
    typedef QEXTSignalSend6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil > SelfType;
    typedef T_return                                                                            ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                                                   IteratorType;
    typedef typename SlotType::CallType                                                         CallType;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are passed directly on to the slots.
     * The return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @param arg6 Argument to be passed on to the slots.
     * @return The return value of the last slot invoked.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5,
                           typename QEXTTypeTrait<T_arg6>::Take arg6) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExecution execution(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QEXTTempSlotList slotList(impl->m_slotList);
            IteratorType iter = slotList.begin();
            for (; iter != slotList.end(); ++iter) {
                if (!iter->isEmpty() && !iter->isBlocked()) {
                    break;
                }
            }

            if (iter == slotList.end()) {
                // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
                return T_return();
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4, arg5, arg6);
            for (++iter; iter != slotList.end(); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4, arg5, arg6);
            }
        }

        return m_result;
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are passed directly on to the slots.
     * The return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @param arg6 Argument to be passed on to the slots.
     * @return The return value of the last slot invoked.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3,
                                  typename QEXTTypeTrait<T_arg4>::Take arg4,
                                  typename QEXTTypeTrait<T_arg5>::Take arg5,
                                  typename QEXTTypeTrait<T_arg6>::Take arg6) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExecution execution(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;

            QEXTTempSlotList slotList(impl->m_slotList);
            ReverseIteratorType iter(slotList.end());
            for (; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (!iter->isEmpty() && !iter->isBlocked()) {
                    break;
                }
            }

            if (iter == ReverseIteratorType(slotList.begin())) {
                // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
                return T_return();
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4, arg5, arg6);
            for (++iter; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4, arg5, arg6);
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
template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTSignalSend6<void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
{
    typedef QEXTSignalSend6<void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>  SelfType;
    typedef void                                                                            ResultType;
    typedef QEXTSlot<void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                                               IteratorType;
    typedef typename SlotType::CallType                                                     CallType;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are passed directly on to the slots.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @param arg6 Argument to be passed on to the slots.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5,
                           typename QEXTTypeTrait<T_arg6>::Take arg6) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        for (IteratorType iter = slotList.begin(); iter != slotList.end(); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4, arg5, arg6);
        }
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are passed directly on to the slots.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @param arg6 Argument to be passed on to the slots.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3,
                                  typename QEXTTypeTrait<T_arg4>::Take arg4,
                                  typename QEXTTypeTrait<T_arg5>::Take arg5,
                                  typename QEXTTypeTrait<T_arg6>::Take arg6) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;
        for (ReverseIteratorType iter = ReverseIteratorType(slotList.end()); iter != ReverseIteratorType(slotList.begin()); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4, arg5, arg6);
        }
    }
};

/** Abstracts signal sender.
 * This template implements the send() function of QEXTSignal7.
 * Template specializations are available to optimize signal
 * sender when no accumulator is used, for example when the template
 * argument @e T_accumulator is @p QEXTNil.
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_accumulator>
struct QEXTSignalSend7
{
    typedef QEXTSignalSend7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_accumulator>    SelfType;
    typedef typename T_accumulator::ResultType                                                                  ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>                          SlotType;
    typedef qextinternal::QEXTSlotIteratorBuffer<SelfType, T_return>                                            SlotIteratorBufferType;
    typedef qextinternal::QEXTSlotReverseIteratorBuffer<SelfType, T_return>                                     SlotReverseIteratorBufferType;
    typedef QEXTSignalImpl::ConstIteratorType                                                                   IteratorType;

    /** Instantiates the class.
     * The parameters are stored in member variables. operator()() passes
     * the values on to some slot.
     */
    QEXTSignalSend7(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4,
                    typename QEXTTypeTrait<T_arg5>::Take arg5,
                    typename QEXTTypeTrait<T_arg6>::Take arg6,
                    typename QEXTTypeTrait<T_arg7>::Take arg7)
        : m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5), m_arg6(arg6), m_arg7(arg7) {}

    /** Invokes a slot using the buffered parameter values.
     * @param slot Some slot to invoke.
     * @return The slot's return value.
     */
    T_return operator()(const SlotType &slot) const {
        return (reinterpret_cast<typename SlotType::CallType>(slot.m_slotRep->m_call))(slot.m_slotRep.data(), m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7);
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are buffered in a temporary instance of QEXTSignalSend7.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @param arg6 Argument to be passed on to the slots.
     * @param arg7 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations as processed by the accumulator.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5,
                           typename QEXTTypeTrait<T_arg6>::Take arg6,
                           typename QEXTTypeTrait<T_arg7>::Take arg7) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        return accumulator(SlotIteratorBufferType(slotList.begin(), &self),
                           SlotIteratorBufferType(slotList.end(), &self));
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are buffered in a temporary instance of QEXTSignalSend7.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @param arg6 Argument to be passed on to the slots.
     * @param arg7 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations as processed by the accumulator.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3,
                                  typename QEXTTypeTrait<T_arg4>::Take arg4,
                                  typename QEXTTypeTrait<T_arg5>::Take arg5,
                                  typename QEXTTypeTrait<T_arg6>::Take arg6,
                                  typename QEXTTypeTrait<T_arg7>::Take arg7) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        return accumulator(SlotReverseIteratorBufferType(slotList.end(), &self),
                           SlotReverseIteratorBufferType(slotList.begin(), &self));
    }

    typename QEXTTypeTrait<T_arg1>::Take m_arg1;
    typename QEXTTypeTrait<T_arg2>::Take m_arg2;
    typename QEXTTypeTrait<T_arg3>::Take m_arg3;
    typename QEXTTypeTrait<T_arg4>::Take m_arg4;
    typename QEXTTypeTrait<T_arg5>::Take m_arg5;
    typename QEXTTypeTrait<T_arg6>::Take m_arg6;
    typename QEXTTypeTrait<T_arg7>::Take m_arg7;
};

/** Abstracts signal sender.
 * This template specialization implements an optimized send()
 * function for the case that no accumulator is used.
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTSignalSend7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, QEXTNil>
{
    typedef QEXTSignalSend7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, QEXTNil > SelfType;
    typedef T_return                                                                                    ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                                                           IteratorType;
    typedef typename SlotType::CallType                                                                 CallType;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are passed directly on to the slots.
     * The return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @param arg6 Argument to be passed on to the slots.
     * @param arg7 Argument to be passed on to the slots.
     * @return The return value of the last slot invoked.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5,
                           typename QEXTTypeTrait<T_arg6>::Take arg6,
                           typename QEXTTypeTrait<T_arg7>::Take arg7) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExecution execution(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            QEXTTempSlotList slotList(impl->m_slotList);
            IteratorType iter = slotList.begin();
            for (; iter != slotList.end(); ++iter) {
                if (!iter->isEmpty() && !iter->isBlocked()) {
                    break;
                }
            }

            if (iter == slotList.end()) {
                // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
                return T_return();
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4, arg5, arg6, arg7);
            for (++iter; iter != slotList.end(); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4, arg5, arg6, arg7);
            }
        }

        return m_result;
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are passed directly on to the slots.
     * The return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @param arg6 Argument to be passed on to the slots.
     * @param arg7 Argument to be passed on to the slots.
     * @return The return value of the last slot invoked.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3,
                                  typename QEXTTypeTrait<T_arg4>::Take arg4,
                                  typename QEXTTypeTrait<T_arg5>::Take arg5,
                                  typename QEXTTypeTrait<T_arg6>::Take arg6,
                                  typename QEXTTypeTrait<T_arg7>::Take arg7) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExecution execution(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "execution" is destroyed.
        {
            typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;

            QEXTTempSlotList slotList(impl->m_slotList);
            ReverseIteratorType iter(slotList.end());
            for (; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (!iter->isEmpty() && !iter->isBlocked()) {
                    break;
                }
            }

            if (iter == ReverseIteratorType(slotList.begin())) {
                // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
                return T_return();
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4, arg5, arg6, arg7);
            for (++iter; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4, arg5, arg6, arg7);
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
template <typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTSignalSend7<void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, QEXTNil>
{
    typedef QEXTSignalSend7<void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, QEXTNil>  SelfType;
    typedef void                                                                                    ResultType;
    typedef QEXTSlot<void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                                                       IteratorType;
    typedef typename SlotType::CallType                                                             CallType;

    /** Executes a list of slots using an accumulator of type @e T_accumulator.
     * The arguments are passed directly on to the slots.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @param arg6 Argument to be passed on to the slots.
     * @param arg7 Argument to be passed on to the slots.
     */
    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5,
                           typename QEXTTypeTrait<T_arg6>::Take arg6,
                           typename QEXTTypeTrait<T_arg7>::Take arg7) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        for (IteratorType iter = slotList.begin(); iter != slotList.end(); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }
    }

    /** Executes a list of slots using an accumulator of type @e T_accumulator in reverse order.
     * The arguments are passed directly on to the slots.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @param arg6 Argument to be passed on to the slots.
     * @param arg7 Argument to be passed on to the slots.
     */
    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3,
                                  typename QEXTTypeTrait<T_arg4>::Take arg4,
                                  typename QEXTTypeTrait<T_arg5>::Take arg5,
                                  typename QEXTTypeTrait<T_arg6>::Take arg6,
                                  typename QEXTTypeTrait<T_arg7>::Take arg7) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExecution execution(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;

        for (ReverseIteratorType iter = ReverseIteratorType(slotList.end()); iter != ReverseIteratorType(slotList.begin()); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep.data(), arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }
    }
};


} /* namespace qextinternal */



/** Signal declaration.
 * QEXTSignal0 can be used to connect() slots that are invoked
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
 * @p QEXTNil means that no accumulator should be used, for example if signal
 * sender returns the return value of the last slot invoked.
 *
 * You should use the more convenient unnumbered QEXTSignal template.
 *
 * @ingroup signal
 */
template <typename T_return, typename T_accumulator = QEXTNil>
class QEXTSignal0 : public QEXTSignalBase
{
public:
    typedef qextinternal::QEXTSignalSend0<T_return, T_accumulator>  SenderType;
    typedef typename SenderType::ResultType                         ResultType;
    typedef QEXTSlot<T_return>                                      SlotType;
    typedef QEXTSlotList<SlotType>                                  SlotListType;
    typedef typename SlotListType::Iterator                         Iterator;
    typedef typename SlotListType::ConstIterator                    ConstIterator;

    typedef typename SlotListType::ReverseIterator                  ReverseIterator;
    typedef typename SlotListType::ConstReverseIterator             ConstReverseIterator;

    /** Add a slot to the list of slots.
     * Any functor or slot may be passed into connect().
     * It will be converted into a slot implicitly.
     * The returned iterator may be stored for disconnection
     * of the slot at some later point. It stays valid until
     * the slot is removed from the list of slots. The iterator
     * can also be implicitly converted into a QEXTConnection object
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
     * @param slot_ The slot to add to the list of slots.
     * @return An iterator pointing to the new slot in the list.
     */
    Iterator connect(const SlotType &slot) {
        return Iterator(QEXTSignalBase::connect(static_cast<const QEXTSlotBase&>(slot)));
    }

    /** Triggers the sender of the signal.
     * During signal sender all slots that have been connected
     * to the signal are invoked unless they are manually set into
     * a blocking state. The parameters are passed on to the slots.
     * If @e T_accumulated is not @p QEXTNil, an accumulator of this type
     * is used to process the return values of the slot invocations.
     * Otherwise, the return value of the last slot invoked is returned.
     * @return The accumulated return values of the slot invocations.
     */
    ResultType send() const {
        return SenderType::send(m_impl);
    }

    /** Triggers the sender of the signal in reverse order (see send()). */
    ResultType sendReverse() const {
        return SenderType::sendReverse(m_impl);
    }

    /** Triggers the sender of the signal (see send()). */
    ResultType operator()() const {
        return send();
    }

    /** Creates a functor that calls send() on this signal.
     * @code
     * qextMemberFunctor(mysignal, &QEXTSignal0::send)
     * @endcode
     * yields the same result.
     * @return A functor that calls send() on this signal.
     */
    QEXTBoundConstMemberFunctor0<ResultType, QEXTSignal0> makeSlot() const {
        return QEXTBoundConstMemberFunctor0<ResultType, QEXTSignal0>(this, &QEXTSignal0::send);
    }

    /** Creates an STL-style interface for the signal's list of slots.
     * This interface supports iteration, insertion and removal of slots.
     * @return An STL-style interface for the signal's list of slots.
     */
    SlotListType slotList() {
        return SlotListType(impl());
    }

    /** Creates an STL-style interface for the signal's list of slots.
     * This interface supports iteration, insertion and removal of slots.
     * @return An STL-style interface for the signal's list of slots.
     */
    const SlotListType slotList() const {
        return SlotListType(const_cast<QEXTSignal0*>(this)->impl());
    }

    QEXTSignal0() {}

    QEXTSignal0(const QEXTSignal0 &src) : QEXTSignalBase(src) {}
};

/** Signal declaration.
 * QEXTSignal1 can be used to connect() slots that are invoked
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
 * @p QEXTNil means that no accumulator should be used, for example if signal
 * sender returns the return value of the last slot invoked.
 *
 * You should use the more convenient unnumbered QEXTSignal template.
 *
 * @ingroup signal
 */
template <typename T_return, typename T_arg1, typename T_accumulator = QEXTNil>
class QEXTSignal1 : public QEXTSignalBase
{
public:
    typedef qextinternal::QEXTSignalSend1<T_return, T_arg1, T_accumulator>  SenderType;
    typedef typename SenderType::ResultType                                 ResultType;
    typedef QEXTSlot<T_return, T_arg1>                                      SlotType;
    typedef QEXTSlotList<SlotType>                                          SlotListType;
    typedef typename SlotListType::Iterator                                 Iterator;
    typedef typename SlotListType::ConstIterator                            ConstIterator;
    typedef typename SlotListType::ReverseIterator                          ReverseIterator;
    typedef typename SlotListType::ConstReverseIterator                     ConstReverseIterator;

    /** Add a slot to the list of slots.
     * Any functor or slot may be passed into connect().
     * It will be converted into a slot implicitly.
     * The returned iterator may be stored for disconnection
     * of the slot at some later point. It stays valid until
     * the slot is removed from the list of slots. The iterator
     * can also be implicitly converted into a QEXTConnection object
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
     * @param slot_ The slot to add to the list of slots.
     * @return An iterator pointing to the new slot in the list.
     */
    Iterator connect(const SlotType &slot) {
        return Iterator(QEXTSignalBase::connect(static_cast<const QEXTSlotBase&>(slot)));
    }

    /** Triggers the sender of the signal.
     * During signal sender all slots that have been connected
     * to the signal are invoked unless they are manually set into
     * a blocking state. The parameters are passed on to the slots.
     * If @e T_accumulated is not @p QEXTNil, an accumulator of this type
     * is used to process the return values of the slot invocations.
     * Otherwise, the return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations.
     */
    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return SenderType::send(m_impl, arg1);
    }

    /** Triggers the sender of the signal in reverse order (see send()). */
    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return SenderType::sendReverse(m_impl, arg1);
    }

    /** Triggers the sender of the signal (see send()). */
    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return this->send(arg1);
    }

    /** Creates a functor that calls send() on this signal.
     * @code
     * qextMemberFunctor(mysignal, &QEXTSignal1::send)
     * @endcode
     * yields the same result.
     * @return A functor that calls send() on this signal.
     */
    QEXTBoundConstMemberFunctor1<
    ResultType, QEXTSignal1,
    typename QEXTTypeTrait<T_arg1>::Take>
    makeSlot() const {
        return QEXTBoundConstMemberFunctor1<
                ResultType, QEXTSignal1,
                typename QEXTTypeTrait<T_arg1>::Take>(this, &QEXTSignal1::send);
    }

    /** Creates an STL-style interface for the signal's list of slots.
     * This interface supports iteration, insertion and removal of slots.
     * @return An STL-style interface for the signal's list of slots.
     */
    SlotListType slotList() {
        return SlotListType(impl());
    }

    /** Creates an STL-style interface for the signal's list of slots.
     * This interface supports iteration, insertion and removal of slots.
     * @return An STL-style interface for the signal's list of slots.
     */
    const SlotListType slotList() const {
        return SlotListType(const_cast<QEXTSignal1*>(this)->impl());
    }

    QEXTSignal1() {}

    QEXTSignal1(const QEXTSignal1 &src) : QEXTSignalBase(src) {}
};

/** Signal declaration.
 * QEXTSignal2 can be used to connect() slots that are invoked
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
 * @p QEXTNil means that no accumulator should be used, for example if signal
 * sender returns the return value of the last slot invoked.
 *
 * You should use the more convenient unnumbered QEXTSignal template.
 *
 * @ingroup signal
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_accumulator = QEXTNil>
class QEXTSignal2 : public QEXTSignalBase
{
public:
    typedef qextinternal::QEXTSignalSend2<T_return, T_arg1, T_arg2, T_accumulator>  SenderType;
    typedef typename SenderType::ResultType                                         ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2>                                      SlotType;
    typedef QEXTSlotList<SlotType>                                                  SlotListType;
    typedef typename SlotListType::Iterator                                         Iterator;
    typedef typename SlotListType::ConstIterator                                    ConstIterator;
    typedef typename SlotListType::ReverseIterator                                  ReverseIterator;
    typedef typename SlotListType::ConstReverseIterator                             ConstReverseIterator;

    /** Add a slot to the list of slots.
     * Any functor or slot may be passed into connect().
     * It will be converted into a slot implicitly.
     * The returned iterator may be stored for disconnection
     * of the slot at some later point. It stays valid until
     * the slot is removed from the list of slots. The iterator
     * can also be implicitly converted into a QEXTConnection object
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
     * @param slot_ The slot to add to the list of slots.
     * @return An iterator pointing to the new slot in the list.
     */
    Iterator connect(const SlotType &slot) {
        return Iterator(QEXTSignalBase::connect(static_cast<const QEXTSlotBase&>(slot)));
    }

    /** Triggers the sender of the signal.
     * During signal sender all slots that have been connected
     * to the signal are invoked unless they are manually set into
     * a blocking state. The parameters are passed on to the slots.
     * If @e T_accumulated is not @p QEXTNil, an accumulator of this type
     * is used to process the return values of the slot invocations.
     * Otherwise, the return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations.
     */
    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return SenderType::send(m_impl, arg1, arg2);
    }

    /** Triggers the sender of the signal in reverse order (see send()). */
    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return SenderType::sendReverse(m_impl, arg1, arg2);
    }

    /** Triggers the sender of the signal (see send()). */
    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                          typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return send(arg1, arg2);
    }

    /** Creates a functor that calls send() on this signal.
     * @code
     * qextMemberFunctor(mysignal, &QEXTSignal2::send)
     * @endcode
     * yields the same result.
     * @return A functor that calls send() on this signal.
     */
    QEXTBoundConstMemberFunctor2<
    ResultType, QEXTSignal2,
    typename QEXTTypeTrait<T_arg1>::Take,
    typename QEXTTypeTrait<T_arg2>::Take>
    makeSlot() const {
        return QEXTBoundConstMemberFunctor2<
                ResultType, QEXTSignal2,
                typename QEXTTypeTrait<T_arg1>::Take,
                typename QEXTTypeTrait<T_arg2>::Take>(this, &QEXTSignal2::send);
    }

    /** Creates an STL-style interface for the signal's list of slots.
     * This interface supports iteration, insertion and removal of slots.
     * @return An STL-style interface for the signal's list of slots.
     */
    SlotListType slotList() {
        return SlotListType(impl());
    }

    /** Creates an STL-style interface for the signal's list of slots.
     * This interface supports iteration, insertion and removal of slots.
     * @return An STL-style interface for the signal's list of slots.
     */
    const SlotListType slotList() const {
        return SlotListType(const_cast<QEXTSignal2*>(this)->impl());
    }

    QEXTSignal2() {}

    QEXTSignal2(const QEXTSignal2 &src) : QEXTSignalBase(src) {}
};

/** Signal declaration.
 * QEXTSignal3 can be used to connect() slots that are invoked
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
 * @p QEXTNil means that no accumulator should be used, for example if signal
 * sender returns the return value of the last slot invoked.
 *
 * You should use the more convenient unnumbered QEXTSignal template.
 *
 * @ingroup signal
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_accumulator = QEXTNil>
class QEXTSignal3 : public QEXTSignalBase
{
public:
    typedef qextinternal::QEXTSignalSend3<T_return, T_arg1, T_arg2, T_arg3, T_accumulator>  SenderType;
    typedef typename SenderType::ResultType                                                 ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3>                                      SlotType;
    typedef QEXTSlotList<SlotType>                                                          SlotListType;
    typedef typename SlotListType::Iterator                                                 Iterator;
    typedef typename SlotListType::ConstIterator                                            ConstIterator;
    typedef typename SlotListType::ReverseIterator                                          ReverseIterator;
    typedef typename SlotListType::ConstReverseIterator                                     ConstReverseIterator;

    /** Add a slot to the list of slots.
     * Any functor or slot may be passed into connect().
     * It will be converted into a slot implicitly.
     * The returned iterator may be stored for disconnection
     * of the slot at some later point. It stays valid until
     * the slot is removed from the list of slots. The iterator
     * can also be implicitly converted into a QEXTConnection object
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
     * @param slot_ The slot to add to the list of slots.
     * @return An iterator pointing to the new slot in the list.
     */
    Iterator connect(const SlotType &slot) {
        return Iterator(QEXTSignalBase::connect(static_cast<const QEXTSlotBase&>(slot)));
    }

    /** Triggers the sender of the signal.
     * During signal sender all slots that have been connected
     * to the signal are invoked unless they are manually set into
     * a blocking state. The parameters are passed on to the slots.
     * If @e T_accumulated is not @p QEXTNil, an accumulator of this type
     * is used to process the return values of the slot invocations.
     * Otherwise, the return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations.
     */
    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return SenderType::send(m_impl, arg1, arg2, arg3);
    }

    /** Triggers the sender of the signal in reverse order (see send()). */
    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return SenderType::sendReverse(m_impl, arg1, arg2, arg3);
    }

    /** Triggers the sender of the signal (see send()). */
    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                          typename QEXTTypeTrait<T_arg2>::Take arg2,
                          typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return send(arg1, arg2, arg3);
    }

    /** Creates a functor that calls send() on this signal.
     * @code
     * qextMemberFunctor(mysignal, &QEXTSignal3::send)
     * @endcode
     * yields the same result.
     * @return A functor that calls send() on this signal.
     */
    QEXTBoundConstMemberFunctor3<
    ResultType, QEXTSignal3,
    typename QEXTTypeTrait<T_arg1>::Take,
    typename QEXTTypeTrait<T_arg2>::Take,
    typename QEXTTypeTrait<T_arg3>::Take>
    makeSlot() const {
        return QEXTBoundConstMemberFunctor3<
                ResultType, QEXTSignal3,
                typename QEXTTypeTrait<T_arg1>::Take,
                typename QEXTTypeTrait<T_arg2>::Take,
                typename QEXTTypeTrait<T_arg3>::Take>(this, &QEXTSignal3::send);
    }

    /** Creates an STL-style interface for the signal's list of slots.
     * This interface supports iteration, insertion and removal of slots.
     * @return An STL-style interface for the signal's list of slots.
     */
    SlotListType slotList() {
        return SlotListType(impl());
    }

    /** Creates an STL-style interface for the signal's list of slots.
     * This interface supports iteration, insertion and removal of slots.
     * @return An STL-style interface for the signal's list of slots.
     */
    const SlotListType slotList() const {
        return SlotListType(const_cast<QEXTSignal3*>(this)->impl());
    }

    QEXTSignal3() {}

    QEXTSignal3(const QEXTSignal3 &src) : QEXTSignalBase(src) {}
};

/** Signal declaration.
 * QEXTSignal4 can be used to connect() slots that are invoked
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
 * @p QEXTNil means that no accumulator should be used, for example if signal
 * sender returns the return value of the last slot invoked.
 *
 * You should use the more convenient unnumbered QEXTSignal template.
 *
 * @ingroup signal
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_accumulator = QEXTNil>
class QEXTSignal4 : public QEXTSignalBase
{
public:
    typedef qextinternal::QEXTSignalSend4<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_accumulator>  SenderType;
    typedef typename SenderType::ResultType                                                         ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4>                                      SlotType;
    typedef QEXTSlotList<SlotType>                                                                  SlotListType;
    typedef typename SlotListType::Iterator                                                         Iterator;
    typedef typename SlotListType::ConstIterator                                                    ConstIterator;
    typedef typename SlotListType::ReverseIterator                                                  ReverseIterator;
    typedef typename SlotListType::ConstReverseIterator                                             ConstReverseIterator;

    /** Add a slot to the list of slots.
     * Any functor or slot may be passed into connect().
     * It will be converted into a slot implicitly.
     * The returned iterator may be stored for disconnection
     * of the slot at some later point. It stays valid until
     * the slot is removed from the list of slots. The iterator
     * can also be implicitly converted into a QEXTConnection object
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
     * @param slot_ The slot to add to the list of slots.
     * @return An iterator pointing to the new slot in the list.
     */
    Iterator connect(const SlotType &slot) {
        return Iterator(QEXTSignalBase::connect(static_cast<const QEXTSlotBase&>(slot)));
    }

    /** Triggers the sender of the signal.
     * During signal sender all slots that have been connected
     * to the signal are invoked unless they are manually set into
     * a blocking state. The parameters are passed on to the slots.
     * If @e T_accumulated is not @p QEXTNil, an accumulator of this type
     * is used to process the return values of the slot invocations.
     * Otherwise, the return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations.
     */
    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return SenderType::send(m_impl, arg1, arg2, arg3, arg4);
    }

    /** Triggers the sender of the signal in reverse order (see send()). */
    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return SenderType::sendReverse(m_impl, arg1, arg2, arg3, arg4);
    }

    /** Triggers the sender of the signal (see send()). */
    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                          typename QEXTTypeTrait<T_arg2>::Take arg2,
                          typename QEXTTypeTrait<T_arg3>::Take arg3,
                          typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return send(arg1, arg2, arg3, arg4);
    }

    /** Creates a functor that calls send() on this signal.
     * @code
     * qextMemberFunctor(mysignal, &QEXTSignal4::send)
     * @endcode
     * yields the same result.
     * @return A functor that calls send() on this signal.
     */
    QEXTBoundConstMemberFunctor4<
    ResultType, QEXTSignal4,
    typename QEXTTypeTrait<T_arg1>::Take,
    typename QEXTTypeTrait<T_arg2>::Take,
    typename QEXTTypeTrait<T_arg3>::Take,
    typename QEXTTypeTrait<T_arg4>::Take>
    makeSlot() const {
        return QEXTBoundConstMemberFunctor4<
                ResultType, QEXTSignal4,
                typename QEXTTypeTrait<T_arg1>::Take,
                typename QEXTTypeTrait<T_arg2>::Take,
                typename QEXTTypeTrait<T_arg3>::Take,
                typename QEXTTypeTrait<T_arg4>::Take>(this, &QEXTSignal4::send);
    }

    /** Creates an STL-style interface for the signal's list of slots.
     * This interface supports iteration, insertion and removal of slots.
     * @return An STL-style interface for the signal's list of slots.
     */
    SlotListType slotList() {
        return SlotListType(impl());
    }

    /** Creates an STL-style interface for the signal's list of slots.
     * This interface supports iteration, insertion and removal of slots.
     * @return An STL-style interface for the signal's list of slots.
     */
    const SlotListType slotList() const {
        return SlotListType(const_cast<QEXTSignal4*>(this)->impl());
    }

    QEXTSignal4() {}

    QEXTSignal4(const QEXTSignal4 &src) : QEXTSignalBase(src) {}
};

/** Signal declaration.
 * QEXTSignal5 can be used to connect() slots that are invoked
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
 * @p QEXTNil means that no accumulator should be used, for example if signal
 * sender returns the return value of the last slot invoked.
 *
 * You should use the more convenient unnumbered QEXTSignal template.
 *
 * @ingroup signal
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_accumulator = QEXTNil>
class QEXTSignal5 : public QEXTSignalBase
{
public:
    typedef qextinternal::QEXTSignalSend5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_accumulator>  SenderType;
    typedef typename SenderType::ResultType                                                                 ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>                                      SlotType;
    typedef QEXTSlotList<SlotType>                                                                          SlotListType;
    typedef typename SlotListType::Iterator                                                                 Iterator;
    typedef typename SlotListType::ConstIterator                                                            ConstIterator;
    typedef typename SlotListType::ReverseIterator                                                          ReverseIterator;
    typedef typename SlotListType::ConstReverseIterator                                                     ConstReverseIterator;

    /** Add a slot to the list of slots.
     * Any functor or slot may be passed into connect().
     * It will be converted into a slot implicitly.
     * The returned iterator may be stored for disconnection
     * of the slot at some later point. It stays valid until
     * the slot is removed from the list of slots. The iterator
     * can also be implicitly converted into a QEXTConnection object
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
     * @param slot_ The slot to add to the list of slots.
     * @return An iterator pointing to the new slot in the list.
     */
    Iterator connect(const SlotType &slot) {
        return Iterator(QEXTSignalBase::connect(static_cast<const QEXTSlotBase&>(slot)));
    }

    /** Triggers the sender of the signal.
     * During signal sender all slots that have been connected
     * to the signal are invoked unless they are manually set into
     * a blocking state. The parameters are passed on to the slots.
     * If @e T_accumulated is not @p QEXTNil, an accumulator of this type
     * is used to process the return values of the slot invocations.
     * Otherwise, the return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations.
     */
    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4,
                    typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return SenderType::send(m_impl, arg1, arg2, arg3, arg4, arg5);
    }

    /** Triggers the sender of the signal in reverse order (see send()). */
    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return SenderType::sendReverse(m_impl, arg1, arg2, arg3, arg4, arg5);
    }

    /** Triggers the sender of the signal (see send()). */
    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                          typename QEXTTypeTrait<T_arg2>::Take arg2,
                          typename QEXTTypeTrait<T_arg3>::Take arg3,
                          typename QEXTTypeTrait<T_arg4>::Take arg4,
                          typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return send(arg1, arg2, arg3, arg4, arg5);
    }

    /** Creates a functor that calls send() on this signal.
     * @code
     * qextMemberFunctor(mysignal, &QEXTSignal5::send)
     * @endcode
     * yields the same result.
     * @return A functor that calls send() on this signal.
     */
    QEXTBoundConstMemberFunctor5<
    ResultType, QEXTSignal5,
    typename QEXTTypeTrait<T_arg1>::Take,
    typename QEXTTypeTrait<T_arg2>::Take,
    typename QEXTTypeTrait<T_arg3>::Take,
    typename QEXTTypeTrait<T_arg4>::Take,
    typename QEXTTypeTrait<T_arg5>::Take>
    makeSlot() const {
        return QEXTBoundConstMemberFunctor5<
                ResultType, QEXTSignal5,
                typename QEXTTypeTrait<T_arg1>::Take,
                typename QEXTTypeTrait<T_arg2>::Take,
                typename QEXTTypeTrait<T_arg3>::Take,
                typename QEXTTypeTrait<T_arg4>::Take,
                typename QEXTTypeTrait<T_arg5>::Take>(this, &QEXTSignal5::send);
    }

    /** Creates an STL-style interface for the signal's list of slots.
     * This interface supports iteration, insertion and removal of slots.
     * @return An STL-style interface for the signal's list of slots.
     */
    SlotListType slotList() {
        return SlotListType(impl());
    }

    /** Creates an STL-style interface for the signal's list of slots.
     * This interface supports iteration, insertion and removal of slots.
     * @return An STL-style interface for the signal's list of slots.
     */
    const SlotListType slotList() const {
        return SlotListType(const_cast<QEXTSignal5*>(this)->impl());
    }

    QEXTSignal5() {}

    QEXTSignal5(const QEXTSignal5 &src) : QEXTSignalBase(src) {}
};

/** Signal declaration.
 * QEXTSignal6 can be used to connect() slots that are invoked
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
 * @p QEXTNil means that no accumulator should be used, for example if signal
 * sender returns the return value of the last slot invoked.
 *
 * You should use the more convenient unnumbered QEXTSignal template.
 *
 * @ingroup signal
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_accumulator = QEXTNil>
class QEXTSignal6 : public QEXTSignalBase
{
public:
    typedef qextinternal::QEXTSignalSend6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_accumulator>  SenderType;
    typedef typename SenderType::ResultType                                                                         ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>                                      SlotType;
    typedef QEXTSlotList<SlotType>                                                                                  SlotListType;
    typedef typename SlotListType::Iterator                                                                         Iterator;
    typedef typename SlotListType::ConstIterator                                                                    ConstIterator;
    typedef typename SlotListType::ReverseIterator                                                                  ReverseIterator;
    typedef typename SlotListType::ConstReverseIterator                                                             ConstReverseIterator;

    /** Add a slot to the list of slots.
     * Any functor or slot may be passed into connect().
     * It will be converted into a slot implicitly.
     * The returned iterator may be stored for disconnection
     * of the slot at some later point. It stays valid until
     * the slot is removed from the list of slots. The iterator
     * can also be implicitly converted into a QEXTConnection object
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
     * @param slot_ The slot to add to the list of slots.
     * @return An iterator pointing to the new slot in the list.
     */
    Iterator connect(const SlotType &slot) {
        return Iterator(QEXTSignalBase::connect(static_cast<const QEXTSlotBase&>(slot)));
    }

    /** Triggers the sender of the signal.
     * During signal sender all slots that have been connected
     * to the signal are invoked unless they are manually set into
     * a blocking state. The parameters are passed on to the slots.
     * If @e T_accumulated is not @p QEXTNil, an accumulator of this type
     * is used to process the return values of the slot invocations.
     * Otherwise, the return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @param arg6 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations.
     */
    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4,
                    typename QEXTTypeTrait<T_arg5>::Take arg5,
                    typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return SenderType::send(m_impl, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /** Triggers the sender of the signal in reverse order (see send()). */
    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5,
                           typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return SenderType::sendReverse(m_impl, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /** Triggers the sender of the signal (see send()). */
    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                          typename QEXTTypeTrait<T_arg2>::Take arg2,
                          typename QEXTTypeTrait<T_arg3>::Take arg3,
                          typename QEXTTypeTrait<T_arg4>::Take arg4,
                          typename QEXTTypeTrait<T_arg5>::Take arg5,
                          typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return send(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /** Creates a functor that calls send() on this signal.
     * @code
     * qextMemberFunctor(mysignal, &QEXTSignal6::send)
     * @endcode
     * yields the same result.
     * @return A functor that calls send() on this signal.
     */
    QEXTBoundConstMemberFunctor6<
    ResultType, QEXTSignal6,
    typename QEXTTypeTrait<T_arg1>::Take,
    typename QEXTTypeTrait<T_arg2>::Take,
    typename QEXTTypeTrait<T_arg3>::Take,
    typename QEXTTypeTrait<T_arg4>::Take,
    typename QEXTTypeTrait<T_arg5>::Take,
    typename QEXTTypeTrait<T_arg6>::Take>
    makeSlot() const {
        return QEXTBoundConstMemberFunctor6<
                ResultType, QEXTSignal6,
                typename QEXTTypeTrait<T_arg1>::Take,
                typename QEXTTypeTrait<T_arg2>::Take,
                typename QEXTTypeTrait<T_arg3>::Take,
                typename QEXTTypeTrait<T_arg4>::Take,
                typename QEXTTypeTrait<T_arg5>::Take,
                typename QEXTTypeTrait<T_arg6>::Take>(this, &QEXTSignal6::send);
    }

    /** Creates an STL-style interface for the signal's list of slots.
     * This interface supports iteration, insertion and removal of slots.
     * @return An STL-style interface for the signal's list of slots.
     */
    SlotListType slotList() {
        return SlotListType(impl());
    }

    /** Creates an STL-style interface for the signal's list of slots.
     * This interface supports iteration, insertion and removal of slots.
     * @return An STL-style interface for the signal's list of slots.
     */
    const SlotListType slotList() const {
        return SlotListType(const_cast<QEXTSignal6*>(this)->impl());
    }

    QEXTSignal6() {}

    QEXTSignal6(const QEXTSignal6 &src) : QEXTSignalBase(src) {}
};

/** Signal declaration.
 * QEXTSignal7 can be used to connect() slots that are invoked
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
 * @p QEXTNil means that no accumulator should be used, for example if signal
 * sender returns the return value of the last slot invoked.
 *
 * You should use the more convenient unnumbered QEXTSignal template.
 *
 * @ingroup signal
 */
template <typename T_return,
          typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7, typename T_accumulator = QEXTNil>
class QEXTSignal7 : public QEXTSignalBase
{
public:
    typedef qextinternal::QEXTSignalSend7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_accumulator>  SenderType;
    typedef typename SenderType::ResultType                                                                                 ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>                                      SlotType;
    typedef QEXTSlotList<SlotType>                                                                                          SlotListType;
    typedef typename SlotListType::Iterator                                                                                 Iterator;
    typedef typename SlotListType::ConstIterator                                                                            ConstIterator;
    typedef typename SlotListType::ReverseIterator                                                                          ReverseIterator;
    typedef typename SlotListType::ConstReverseIterator                                                                     ConstReverseIterator;

    /** Add a slot to the list of slots.
     * Any functor or slot may be passed into connect().
     * It will be converted into a slot implicitly.
     * The returned iterator may be stored for disconnection
     * of the slot at some later point. It stays valid until
     * the slot is removed from the list of slots. The iterator
     * can also be implicitly converted into a QEXTConnection object
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
     * @param slot_ The slot to add to the list of slots.
     * @return An iterator pointing to the new slot in the list.
     */
    Iterator connect(const SlotType &slot) {
        return Iterator(QEXTSignalBase::connect(static_cast<const QEXTSlotBase&>(slot)));
    }

    /** Triggers the sender of the signal.
     * During signal sender all slots that have been connected
     * to the signal are invoked unless they are manually set into
     * a blocking state. The parameters are passed on to the slots.
     * If @e T_accumulated is not @p QEXTNil, an accumulator of this type
     * is used to process the return values of the slot invocations.
     * Otherwise, the return value of the last slot invoked is returned.
     * @param arg1 Argument to be passed on to the slots.
     * @param arg2 Argument to be passed on to the slots.
     * @param arg3 Argument to be passed on to the slots.
     * @param arg4 Argument to be passed on to the slots.
     * @param arg5 Argument to be passed on to the slots.
     * @param arg6 Argument to be passed on to the slots.
     * @param arg7 Argument to be passed on to the slots.
     * @return The accumulated return values of the slot invocations.
     */
    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4,
                    typename QEXTTypeTrait<T_arg5>::Take arg5,
                    typename QEXTTypeTrait<T_arg6>::Take arg6,
                    typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return SenderType::send(m_impl, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    /** Triggers the sender of the signal in reverse order (see send()). */
    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5,
                           typename QEXTTypeTrait<T_arg6>::Take arg6,
                           typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return SenderType::sendReverse(m_impl, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    /** Triggers the sender of the signal (see send()). */
    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                          typename QEXTTypeTrait<T_arg2>::Take arg2,
                          typename QEXTTypeTrait<T_arg3>::Take arg3,
                          typename QEXTTypeTrait<T_arg4>::Take arg4,
                          typename QEXTTypeTrait<T_arg5>::Take arg5,
                          typename QEXTTypeTrait<T_arg6>::Take arg6,
                          typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return send(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    /** Creates a functor that calls send() on this signal.
     * @code
     * qextMemberFunctor(mysignal, &QEXTSignal7::send)
     * @endcode
     * yields the same result.
     * @return A functor that calls send() on this signal.
     */
    QEXTBoundConstMemberFunctor7<
    ResultType, QEXTSignal7,
    typename QEXTTypeTrait<T_arg1>::Take,
    typename QEXTTypeTrait<T_arg2>::Take,
    typename QEXTTypeTrait<T_arg3>::Take,
    typename QEXTTypeTrait<T_arg4>::Take,
    typename QEXTTypeTrait<T_arg5>::Take,
    typename QEXTTypeTrait<T_arg6>::Take,
    typename QEXTTypeTrait<T_arg7>::Take> makeSlot() const {
        return QEXTBoundConstMemberFunctor7<
                ResultType, QEXTSignal7,
                typename QEXTTypeTrait<T_arg1>::Take,
                typename QEXTTypeTrait<T_arg2>::Take,
                typename QEXTTypeTrait<T_arg3>::Take,
                typename QEXTTypeTrait<T_arg4>::Take,
                typename QEXTTypeTrait<T_arg5>::Take,
                typename QEXTTypeTrait<T_arg6>::Take,
                typename QEXTTypeTrait<T_arg7>::Take>(this, &QEXTSignal7::send);
    }

    /** Creates an STL-style interface for the signal's list of slots.
     * This interface supports iteration, insertion and removal of slots.
     * @return An STL-style interface for the signal's list of slots.
     */
    SlotListType slotList() {
        return SlotListType(impl());
    }

    /** Creates an STL-style interface for the signal's list of slots.
     * This interface supports iteration, insertion and removal of slots.
     * @return An STL-style interface for the signal's list of slots.
     */
    const SlotListType slotList() const {
        return SlotListType(const_cast<QEXTSignal7*>(this)->impl());
    }

    QEXTSignal7() {}

    QEXTSignal7(const QEXTSignal7 &src) : QEXTSignalBase(src) {}
};



/** Convenience wrapper for the numbered QEXTSignal# templates.
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
 * - @e T_arg1 Argument type used in the definition of send(). The default @p QEXTNil means no argument.
 * - @e T_arg2 Argument type used in the definition of send(). The default @p QEXTNil means no argument.
 * - @e T_arg3 Argument type used in the definition of send(). The default @p QEXTNil means no argument.
 * - @e T_arg4 Argument type used in the definition of send(). The default @p QEXTNil means no argument.
 * - @e T_arg5 Argument type used in the definition of send(). The default @p QEXTNil means no argument.
 * - @e T_arg6 Argument type used in the definition of send(). The default @p QEXTNil means no argument.
 * - @e T_arg7 Argument type used in the definition of send(). The default @p QEXTNil means no argument.
 *
 * To specify an accumulator type the nested class signal::accumulated can be used.
 *
 * @par Example:
 * @code
 * void foo(int) {}
 * QEXTSignal<void, long> sig;
 * sig.connect(ptr_fun(&foo));
 * sig.send(19);
 * @endcode
 *
 * @ingroup signal
 */
template <typename T_return,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTSignal : public QEXTSignal7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, QEXTNil>
{
public:
    typedef QEXTSignal7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, QEXTNil>  BaseType;
    typedef typename BaseType::ResultType                                                           ResultType;

    /** Convenience wrapper for the numbered QEXTSignal# templates.
       * Like QEXTSignal but the additional template parameter @e T_accumulator
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
       * @ingroup signal
       */
    template <typename T_accumulator>
    class Accumulated : public QEXTSignal7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_accumulator>
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &src) : QEXTSignal7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_accumulator>(src) {}
    };

    QEXTSignal() {}
    QEXTSignal(const QEXTSignal &src) : BaseType(src) {}

    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4,
                    typename QEXTTypeTrait<T_arg5>::Take arg5,
                    typename QEXTTypeTrait<T_arg6>::Take arg6,
                    typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::send(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5,
                           typename QEXTTypeTrait<T_arg6>::Take arg6,
                           typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::sendReverse(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                          typename QEXTTypeTrait<T_arg2>::Take arg2,
                          typename QEXTTypeTrait<T_arg3>::Take arg3,
                          typename QEXTTypeTrait<T_arg4>::Take arg4,
                          typename QEXTTypeTrait<T_arg5>::Take arg5,
                          typename QEXTTypeTrait<T_arg6>::Take arg6,
                          typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return BaseType::send(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }
};

/** Convenience wrapper for the numbered QEXTSignal6 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTSignal
 * template for 6 argument(s).
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTSignal <T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTSignal6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
{
public:
    typedef QEXTSignal6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>  BaseType;
    typedef typename BaseType::ResultType                                                   ResultType;

    /** Convenience wrapper for the numbered QEXTSignal6 template.
     * Like QEXTSignal but the additional template parameter @e T_accumulator
     * defines the accumulator type that should be used.
     */
    template <typename T_accumulator>
    class Accumulated : public QEXTSignal6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_accumulator>
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &src) : QEXTSignal6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_accumulator>(src) {}
    };

    QEXTSignal() {}
    QEXTSignal(const QEXTSignal &src) : BaseType(src) {}

    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4,
                    typename QEXTTypeTrait<T_arg5>::Take arg5,
                    typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::send(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5,
                           typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::sendReverse(arg1, arg2, arg3, arg4, arg5, arg6);
    }

    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                          typename QEXTTypeTrait<T_arg2>::Take arg2,
                          typename QEXTTypeTrait<T_arg3>::Take arg3,
                          typename QEXTTypeTrait<T_arg4>::Take arg4,
                          typename QEXTTypeTrait<T_arg5>::Take arg5,
                          typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return BaseType::send(arg1, arg2, arg3, arg4, arg5, arg6);
    }
};

/** Convenience wrapper for the numbered QEXTSignal5 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTSignal
 * template for 5 argument(s).
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTSignal<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTSignal5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil>
{
public:
    typedef QEXTSignal5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil>  BaseType;
    typedef typename BaseType::ResultType                                           ResultType;

    /** Convenience wrapper for the numbered QEXTSignal5 template.
     * Like QEXTSignal but the additional template parameter @e T_accumulator
     * defines the accumulator type that should be used.
     */
    template <typename T_accumulator>
    class Accumulated : public QEXTSignal5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_accumulator>
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &src) : QEXTSignal5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_accumulator>(src) {}
    };

    QEXTSignal() {}
    QEXTSignal(const QEXTSignal &src) : BaseType(src) {}

    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4,
                    typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::send(arg1, arg2, arg3, arg4, arg5);
    }

    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::sendReverse(arg1, arg2, arg3, arg4, arg5);
    }

    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                          typename QEXTTypeTrait<T_arg2>::Take arg2,
                          typename QEXTTypeTrait<T_arg3>::Take arg3,
                          typename QEXTTypeTrait<T_arg4>::Take arg4,
                          typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return BaseType::send(arg1, arg2, arg3, arg4, arg5);
    }
};

/** Convenience wrapper for the numbered QEXTSignal4 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTSignal
 * template for 4 argument(s).
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTSignal <T_return, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSignal4<T_return, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil>
{
public:
    typedef QEXTSignal4<T_return, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil>  BaseType;
    typedef typename BaseType::ResultType                                   ResultType;

    /** Convenience wrapper for the numbered QEXTSignal4 template.
     * Like QEXTSignal but the additional template parameter @e T_accumulator
     * defines the accumulator type that should be used.
     */
    template <typename T_accumulator>
    class Accumulated : public QEXTSignal4<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_accumulator>
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &src) : QEXTSignal4<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_accumulator>(src) {}
    };

    QEXTSignal() {}
    QEXTSignal(const QEXTSignal &src) : BaseType(src) {}

    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::send(arg1, arg2, arg3, arg4);
    }

    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::sendReverse(arg1, arg2, arg3, arg4);
    }

    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                          typename QEXTTypeTrait<T_arg2>::Take arg2,
                          typename QEXTTypeTrait<T_arg3>::Take arg3,
                          typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return BaseType::send(arg1, arg2, arg3, arg4);
    }
};

/** Convenience wrapper for the numbered QEXTSignal3 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTSignal
 * template for 3 argument(s).
 */
template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTSignal <T_return, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSignal3<T_return, T_arg1, T_arg2, T_arg3, QEXTNil>
{
public:
    typedef QEXTSignal3<T_return, T_arg1, T_arg2, T_arg3, QEXTNil>  BaseType;
    typedef typename BaseType::ResultType                           ResultType;

    /** Convenience wrapper for the numbered QEXTSignal3 template.
     * Like QEXTSignal but the additional template parameter @e T_accumulator
     * defines the accumulator type that should be used.
     */
    template <typename T_accumulator>
    class Accumulated : public QEXTSignal3<T_return, T_arg1, T_arg2, T_arg3, T_accumulator>
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &src) : QEXTSignal3<T_return, T_arg1, T_arg2, T_arg3, T_accumulator>(src) {}
    };

    QEXTSignal() {}
    QEXTSignal(const QEXTSignal &src) : BaseType(src) {}

    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::send(arg1, arg2, arg3);
    }

    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::sendReverse(arg1, arg2, arg3);
    }

    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                          typename QEXTTypeTrait<T_arg2>::Take arg2,
                          typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return BaseType::send(arg1, arg2, arg3);
    }
};

/** Convenience wrapper for the numbered QEXTSignal2 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTSignal
 * template for 2 argument(s).
 */
template <typename T_return, typename T_arg1, typename T_arg2>
class QEXTSignal <T_return, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSignal2<T_return, T_arg1, T_arg2, QEXTNil>
{
public:
    typedef QEXTSignal2<T_return, T_arg1, T_arg2, QEXTNil>  BaseType;
    typedef typename BaseType::ResultType                   ResultType;

    /** Convenience wrapper for the numbered QEXTSignal2 template.
     * Like QEXTSignal but the additional template parameter @e T_accumulator
     * defines the accumulator type that should be used.
     */
    template <typename T_accumulator>
    class Accumulated : public QEXTSignal2<T_return, T_arg1, T_arg2, T_accumulator>
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &src) : QEXTSignal2<T_return, T_arg1, T_arg2, T_accumulator>(src) {}
    };

    QEXTSignal() {}
    QEXTSignal(const QEXTSignal &src) : BaseType(src) {}

    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::send(arg1, arg2);
    }

    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::sendReverse(arg1, arg2);
    }

    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                          typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return BaseType::send(arg1, arg2);
    }
};

/** Convenience wrapper for the numbered QEXTSignal1 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTSignal
 * template for 1 argument(s).
 */
template <typename T_return, typename T_arg1>
class QEXTSignal <T_return, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSignal1<T_return, T_arg1, QEXTNil>
{
public:
    typedef QEXTSignal1<T_return, T_arg1, QEXTNil>  BaseType;
    typedef typename BaseType::ResultType           ResultType;

    /** Convenience wrapper for the numbered QEXTSignal1 template.
     * Like QEXTSignal but the additional template parameter @e T_accumulator
     * defines the accumulator type that should be used.
     */
    template <typename T_accumulator>
    class Accumulated : public QEXTSignal1<T_return, T_arg1, T_accumulator>
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &src) : QEXTSignal1<T_return, T_arg1, T_accumulator>(src) {}
    };

    QEXTSignal() {}
    QEXTSignal(const QEXTSignal &src) : BaseType(src) {}

    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::send(arg1);
    }

    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::sendReverse(arg1);
    }

    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return BaseType::send(arg1);
    }
};

/** Convenience wrapper for the numbered QEXTSignal0 template.
 * See the base class for useful methods.
 * This is the template specialization of the unnumbered QEXTSignal
 * template for 0 argument(s).
 */
template <typename T_return>
class QEXTSignal <T_return, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSignal0<T_return, QEXTNil>
{
public:
    typedef QEXTSignal0<T_return, QEXTNil> BaseType;
    typedef typename BaseType::ResultType  ResultType;

    /** Convenience wrapper for the numbered QEXTSignal0 template.
     * Like QEXTSignal but the additional template parameter @e T_accumulator
     * defines the accumulator type that should be used.
     */
    template <typename T_accumulator>
    class Accumulated : public QEXTSignal0<T_return, T_accumulator>
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &src) : QEXTSignal0<T_return, T_accumulator>(src) {}
    };

    QEXTSignal() {}
    QEXTSignal(const QEXTSignal &src) : BaseType(src) {}

    ResultType send() const {
        return BaseType::send();
    }

    ResultType sendReverse() const {
        return BaseType::sendReverse();
    }

    ResultType operator()() const {
        return BaseType::send();
    }
};


#endif // QEXTSIGNAL_H
