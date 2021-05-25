#ifndef QEXTSIGNAL_H
#define QEXTSIGNAL_H

#include <qextglobal.h>
#include <qextsignalbase.h>

#include <list>

template <typename T_slot>
struct QEXTSlotIterator
{
    typedef std::size_t                     SizeType;
    typedef std::ptrdiff_t                  DifferenceType;
    typedef std::bidirectional_iterator_tag IteratorCategory;

    typedef T_slot  SlotType;
    typedef T_slot  ValueType;
    typedef T_slot* PointerType;
    typedef T_slot& ReferenceType;

    typedef typename qextinternal::QEXTSignalImpl::IteratorType IteratorType;

    QEXTSlotIterator() {}
    explicit QEXTSlotIterator(const IteratorType& i) : m_iter(i) {}

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

    bool operator == (const QEXTSlotIterator& other) const {
        return m_iter == other.m_iter;
    }

    bool operator != (const QEXTSlotIterator& other) const {
        return m_iter != other.m_iter;
    }

    IteratorType m_iter;
};


template <typename T_slot>
struct QEXTSlotConstIterator
{
    typedef std::size_t                     SizeType;
    typedef std::ptrdiff_t                  DifferenceType;
    typedef std::bidirectional_iterator_tag IteratorCategory;

    typedef T_slot        SlotType;
    typedef T_slot        ValueType;
    typedef const T_slot* PointerType;
    typedef const T_slot& ReferenceType;

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


template <typename T_slot>
struct QEXTSlotList
{
    typedef T_slot SlotType;

    typedef SlotType&       ReferenceType;
    typedef const SlotType& ConstReferenceType;

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
        return ReverseIterator(end());
    }

    ConstReverseIterator rbegin() const {
        return ConstReverseIterator(end());
    }

    ReverseIterator rend() {
        return ReverseIterator(begin());
    }

    ConstReverseIterator rend() const {
        return ConstReverseIterator(begin());
    }

    ReferenceType front() {
        return *begin();
    }

    ConstReferenceType front() const {
        return *begin();
    }

    ReferenceType back() {
        return *(--end());
    }

    ConstReferenceType back() const {
        return *(--end());
    }

    Iterator insert(Iterator i, const SlotType &slot) {
        return Iterator(m_list->insert(i.m_iter, static_cast<const QEXTSlotBase&>(slot)));
    }

    void push_front(const SlotType &c) {
        insert(begin(), c);
    }

    void push_back(const SlotType &c) {
        insert(end(), c);
    }

    Iterator erase(Iterator i) {
        return Iterator(m_list->erase(i.m_iter));
    }

    Iterator erase(Iterator first, Iterator last) {
        while (first != last) {
            first = erase(first);
        }
        return last;
    }

    void pop_front() {
        erase(begin());
    }

    void pop_back() {
        Iterator tmp = end();
        erase(--tmp);
    }

protected:
    qextinternal::QEXTSignalImpl *m_list;
};


namespace qextinternal {


template <typename T_emitter, typename T_result = typename T_emitter::ResultType>
struct QEXTSlotIteratorBuffer
{
    typedef std::size_t                         SizeType;
    typedef std::ptrdiff_t                      DifferenceType;
    typedef std::bidirectional_iterator_tag     IteratorCategory;

    //These are needed just to make this a proper C++ Iterator,
    //that can be used with standard C++ algorithms.
    typedef T_result                            ValueType;
    typedef T_result&                           ReferenceType;
    typedef T_result*                           PointerType;

    typedef T_emitter                           SenderType;
    typedef T_result                            ResultType;
    typedef typename T_emitter::SlotType        SlotType;

    typedef QEXTSignalImpl::ConstIteratorType IteratorType;

    QEXTSlotIteratorBuffer() : m_emitter(QEXT_NULLPTR), m_invoked(false) {}

    QEXTSlotIteratorBuffer(const IteratorType &i, const SenderType *emitter)
        : m_iter(i), m_emitter(emitter), m_invoked(false) {}

    ResultType operator*() const {
        if (!m_iter->isEmpty() && !m_iter->isBlocked() && !m_invoked) {
            m_result = (*m_emitter)(static_cast<const SlotType&>(*m_iter));
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
        /* If '!m_emitter' the iterators are empty.
         * Unfortunately, empty stl iterators are not equal.
         * We are forcing equality so that 'first==last'
         * in the accumulator's send function yields true. */
        return (!m_emitter || (m_iter == other.m_iter));
    }

    bool operator != (const QEXTSlotIteratorBuffer &other) const {
        return (m_emitter && (m_iter != other.m_iter));
    }

private:
    IteratorType m_iter;
    const SenderType *m_emitter;
    mutable ResultType m_result;
    mutable bool m_invoked;
};

template <typename T_emitter>
struct QEXTSlotIteratorBuffer<T_emitter, void>
{
    typedef std::size_t                         SizeType;
    typedef std::ptrdiff_t                      DifferenceType;
    typedef std::bidirectional_iterator_tag     IteratorCategory;

    typedef T_emitter                           SenderType;
    typedef void                                ResultType;
    typedef typename T_emitter::SlotType        SlotType;

    typedef QEXTSignalImpl::ConstIteratorType   IteratorType;

    QEXTSlotIteratorBuffer() : m_emitter(QEXT_NULLPTR), m_invoked(false) {}

    QEXTSlotIteratorBuffer(const IteratorType &i, const SenderType *emitter)
        : m_iter(i), m_emitter(emitter), m_invoked(false) {}

    void operator*() const {
        if (!m_iter->isEmpty() && !m_iter->isBlocked() && !m_invoked) {
            (*m_emitter)(static_cast<const SlotType&>(*m_iter));
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
    const SenderType *m_emitter;
    mutable bool m_invoked;
};

/** Reverse version of sigc::qextinternal::QEXTSlotIteratorBuffer. */
template <typename T_emitter, typename T_result = typename T_emitter::ResultType>
struct QEXTSlotReverseIteratorBuffer
{
    typedef std::size_t                         SizeType;
    typedef std::ptrdiff_t                      DifferenceType;
    typedef std::bidirectional_iterator_tag     IteratorCategory;

    //These are needed just to make this a proper C++ Iterator,
    //that can be used with standard C++ algorithms.
    typedef T_result                            ValueType;
    typedef T_result&                           ReferenceType;
    typedef T_result*                           PointerType;

    typedef T_emitter                           SenderType;
    typedef T_result                            ResultType;
    typedef typename T_emitter::SlotType        SlotType;

    typedef QEXTSignalImpl::ConstIteratorType   IteratorType;

    QEXTSlotReverseIteratorBuffer() : m_emitter(QEXT_NULLPTR), m_invoked(false) {}

    QEXTSlotReverseIteratorBuffer(const IteratorType &iter, const SenderType *emitter)
        : m_iter(iter), m_emitter(emitter), m_invoked(false) {}

    ResultType operator*() const {
        IteratorType tmp(m_iter);
        --tmp;
        if (!tmp->isEmpty() && !tmp->isBlocked() && !m_invoked) {
            m_result = (*m_emitter)(static_cast<const SlotType&>(*tmp));
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
        /* If '!m_emitter' the iterators are empty.
         * Unfortunately, empty stl iterators are not equal.
         * We are forcing equality so that 'first==last'
         * in the accumulator's send function yields true. */
        return (!m_emitter || (m_iter == other.m_iter));
    }

    bool operator != (const QEXTSlotReverseIteratorBuffer &other) const {
        return (m_emitter && (m_iter != other.m_iter));
    }

private:
    IteratorType m_iter;
    const SenderType *m_emitter;
    mutable ResultType m_result;
    mutable bool m_invoked;
};

template <typename T_emitter>
struct QEXTSlotReverseIteratorBuffer<T_emitter, void>
{
    typedef std::size_t                         SizeType;
    typedef std::ptrdiff_t                      DifferenceType;
    typedef std::bidirectional_iterator_tag     IteratorCategory;

    typedef T_emitter                           SenderType;
    typedef void                                ResultType;
    typedef typename T_emitter::SlotType        SlotType;

    typedef QEXTSignalImpl::ConstIteratorType   IteratorType;

    QEXTSlotReverseIteratorBuffer() : m_emitter(QEXT_NULLPTR), m_invoked(false) {}

    QEXTSlotReverseIteratorBuffer(const IteratorType &iter, const SenderType *emitter)
        : m_iter(iter), m_emitter(emitter), m_invoked(false) {}

    void operator*() const {
        IteratorType tmp(m_iter);
        --tmp;
        if (!tmp->isEmpty() && !tmp->isBlocked() && !m_invoked) {
            (*m_emitter)(static_cast<const SlotType&>(*tmp));
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
    const SenderType *m_emitter;
    mutable bool m_invoked;
};


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

    T_return operator()(const SlotType &slot) const {
        return (reinterpret_cast<typename SlotType::CallType>(slot.m_slotRep->m_call))(slot.m_slotRep);
    }

    static ResultType send(QEXTSignalImpl *impl) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self;
        return accumulator(SlotIteratorBufferType(slotList.begin(), &self),
                           SlotIteratorBufferType(slotList.end(), &self));
    }

    static ResultType sendReverse(QEXTSignalImpl *impl) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self ;
        return accumulator(SlotReverseIteratorBufferType(slotList.end(), &self),
                           SlotReverseIteratorBufferType(slotList.begin(), &self));
    }

};

template <typename T_return>
struct QEXTSignalSend0<T_return, QEXTNil>
{
    typedef QEXTSignalSend0<T_return, QEXTNil>  SelfType;
    typedef T_return                            ResultType;
    typedef QEXTSlot<T_return>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType   IteratorType;
    typedef typename SlotType::CallType         CallType;

    static ResultType send(QEXTSignalImpl *impl) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExec exec(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "exec" is destroyed.
        //This avoids a leak on MSVC++ - see http://bugzilla.gnome.org/show_bug.cgi?id=306249
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

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep);
            for (++iter; iter != slotList.end(); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep);
            }
        }

        return m_result;
    }


    static ResultType sendReverse(QEXTSignalImpl *impl) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExec exec(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "exec" is destroyed.
        //This avoids a leak on MSVC++ - see http://bugzilla.gnome.org/show_bug.cgi?id=306249
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
                return T_return(); // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep);
            for (++iter; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep);
            }
        }

        return m_result;
    }
};


template <>
struct QEXTSignalSend0<void, QEXTNil>
{
    typedef QEXTSignalSend0<void, QEXTNil> SelfType;
    typedef void ResultType;
    typedef QEXTSlot<void> SlotType;
    typedef QEXTSignalImpl::ConstIteratorType IteratorType;
    typedef void (*CallType)(QEXTSlotRepresentation *);


    static ResultType send(QEXTSignalImpl *impl) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        for (IteratorType iter = slotList.begin(); iter != slotList.end(); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep);
        }
    }


    static ResultType sendReverse(QEXTSignalImpl *impl) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;

        for (ReverseIteratorType iter = ReverseIteratorType(slotList.end()); iter != ReverseIteratorType(slotList.begin()); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep);
        }
    }
};


template <typename T_return, typename T_arg1, typename T_accumulator>
struct QEXTSignalSend1
{
    typedef QEXTSignalSend1<T_return, T_arg1, T_accumulator>                SelfType;
    typedef typename T_accumulator::ResultType                              ResultType;
    typedef QEXTSlot<T_return, T_arg1>                                      SlotType;
    typedef qextinternal::QEXTSlotIteratorBuffer<SelfType, T_return>        SlotIteratorBufferType;
    typedef qextinternal::QEXTSlotReverseIteratorBuffer<SelfType, T_return> SlotReverseIteratorBufferType;
    typedef QEXTSignalImpl::ConstIteratorType                               IteratorType;

    QEXTSignalSend1(typename QEXTTypeTrait<T_arg1>::Take arg1) : m_arg1(arg1) {}

    T_return operator()(const SlotType& slot) const {
        return (reinterpret_cast<typename SlotType::CallType>(slot.m_slotRep->m_call))(slot.m_slotRep, m_arg1);
    }

    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self(arg1);
        return accumulator(SlotIteratorBufferType(slotList.begin(), &self),
                           SlotIteratorBufferType(slotList.end(), &self));
    }


    static ResultType sendReverse(QEXTSignalImpl* impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self (arg1);
        return accumulator(SlotReverseIteratorBufferType(slotList.end(), &self),
                           SlotReverseIteratorBufferType(slotList.begin(), &self));
    }

    typename QEXTTypeTrait<T_arg1>::Take m_arg1;
};


template <typename T_return, typename T_arg1>
struct QEXTSignalSend1<T_return, T_arg1, QEXTNil>
{
    typedef QEXTSignalSend1<T_return, T_arg1, QEXTNil >     SelfType;
    typedef T_return                                        ResultType;
    typedef QEXTSlot<T_return, T_arg1>                      SlotType;
    typedef QEXTSignalImpl::ConstIteratorType               IteratorType;
    typedef typename SlotType::CallType                     CallType;

    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExec exec(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "exec" is destroyed.
        //This avoids a leak on MSVC++ - see http://bugzilla.gnome.org/show_bug.cgi?id=306249
        {
            QEXTTempSlotList slotList(impl->m_slotList);
            IteratorType iter = slotList.begin();
            for (; iter != slotList.end(); ++iter) {
                if (!iter->isEmpty() && !iter->isBlocked()) break;
            }

            if (iter == slotList.end()) {
                return T_return(); // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1);
            for (++iter; iter != slotList.end(); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1);
            }
        }

        return m_result;
    }


    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExec exec(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "exec" is destroyed.
        //This avoids a leak on MSVC++ - see http://bugzilla.gnome.org/show_bug.cgi?id=306249
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
                return T_return(); // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1);
            for (++iter; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1);
            }
        }

        return m_result;
    }
};


template <typename T_arg1>
struct QEXTSignalSend1<void, T_arg1, QEXTNil>
{
    typedef QEXTSignalSend1<void, T_arg1, QEXTNil>  SelfType;
    typedef void                                    ResultType;
    typedef QEXTSlot<void, T_arg1>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType       IteratorType;
    typedef typename SlotType::CallType             CallType;


    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        for (IteratorType iter = slotList.begin(); iter != slotList.end(); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1);
        }
    }


    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;
        for (ReverseIteratorType iter = ReverseIteratorType(slotList.end()); iter != ReverseIteratorType(slotList.begin()); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1);
        }
    }
};

template <typename T_return, typename T_arg1, typename T_arg2, typename T_accumulator>
struct QEXTSignalSend2
{
    typedef QEXTSignalSend2<T_return, T_arg1, T_arg2, T_accumulator>            SelfType;
    typedef typename T_accumulator::ResultType                                  ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2>                                  SlotType;
    typedef qextinternal::QEXTSlotIteratorBuffer<SelfType, T_return>            SlotIteratorBufferType;
    typedef qextinternal::QEXTSlotReverseIteratorBuffer<SelfType, T_return>     SlotReverseIteratorBufferType;
    typedef QEXTSignalImpl::ConstIteratorType                                   IteratorType;

    QEXTSignalSend2(typename QEXTTypeTrait<T_arg1>::Take arg1, typename QEXTTypeTrait<T_arg2>::Take arg2)
        : m_arg1(arg1), m_arg2(arg2) {}


    T_return operator()(const SlotType &slot) const {
        return (reinterpret_cast<typename SlotType::CallType>(slot.m_slotRep->m_call))(slot.m_slotRep, m_arg1, m_arg2);
    }


    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self (arg1, arg2);
        return accumulator(SlotIteratorBufferType(slotList.begin(), &self),
                           SlotIteratorBufferType(slotList.end(), &self));
    }

    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self (arg1, arg2);
        return accumulator(SlotReverseIteratorBufferType(slotList.end(), &self),
                           SlotReverseIteratorBufferType(slotList.begin(), &self));
    }

    typename QEXTTypeTrait<T_arg1>::Take m_arg1;
    typename QEXTTypeTrait<T_arg2>::Take m_arg2;
};


template <typename T_return, typename T_arg1, typename T_arg2>
struct QEXTSignalSend2<T_return, T_arg1, T_arg2, QEXTNil>
{
    typedef QEXTSignalSend2<T_return, T_arg1, T_arg2, QEXTNil >     SelfType;
    typedef T_return                                                ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2>                      SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                       IteratorType;
    typedef typename SlotType::CallType                             CallType;


    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExec exec(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "exec" is destroyed.
        //This avoids a leak on MSVC++ - see http://bugzilla.gnome.org/show_bug.cgi?id=306249
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

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2);
            for (++iter; iter != slotList.end(); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2);
            }
        }

        return m_result;
    }


    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExec exec(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "exec" is destroyed.
        //This avoids a leak on MSVC++ - see http://bugzilla.gnome.org/show_bug.cgi?id=306249
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
                return T_return(); // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2);
            for (++iter; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2);
            }
        }

        return m_result;
    }
};


template <typename T_arg1, typename T_arg2>
struct QEXTSignalSend2<void, T_arg1, T_arg2, QEXTNil>
{
    typedef QEXTSignalSend2<void, T_arg1, T_arg2, QEXTNil>  SelfType;
    typedef void                                            ResultType;
    typedef QEXTSlot<void, T_arg1, T_arg2>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType               IteratorType;
    typedef typename SlotType::CallType                     CallType;

    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        for (IteratorType iter = slotList.begin(); iter != slotList.end(); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2);
        }
    }


    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;

        for (ReverseIteratorType iter = ReverseIteratorType(slotList.end()); iter != ReverseIteratorType(slotList.begin()); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2);
        }
    }
};


template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_accumulator>
struct QEXTSignalSend3
{
    typedef QEXTSignalSend3<T_return, T_arg1, T_arg2, T_arg3, T_accumulator>    SelfType;
    typedef typename T_accumulator::ResultType                                  ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3>                          SlotType;
    typedef qextinternal::QEXTSlotIteratorBuffer<SelfType, T_return>            SlotIteratorBufferType;
    typedef qextinternal::QEXTSlotReverseIteratorBuffer<SelfType, T_return>     SlotReverseIteratorBufferType;
    typedef QEXTSignalImpl::ConstIteratorType                                   IteratorType;


    QEXTSignalSend3(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3)
        : m_arg1(arg1), m_arg2(arg2), m_arg3(arg3) {}

    T_return operator()(const SlotType &slot) const {
        return (reinterpret_cast<typename SlotType::CallType>(slot.m_slotRep->m_call))(slot.m_slotRep, m_arg1, m_arg2, m_arg3);
    }

    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self (arg1, arg2, arg3);
        return accumulator(SlotIteratorBufferType(slotList.begin(), &self),
                           SlotIteratorBufferType(slotList.end(), &self));
    }

    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self(arg1, arg2, arg3);
        return accumulator(SlotReverseIteratorBufferType(slotList.end(), &self),
                           SlotReverseIteratorBufferType(slotList.begin(), &self));
    }

    typename QEXTTypeTrait<T_arg1>::Take m_arg1;
    typename QEXTTypeTrait<T_arg2>::Take m_arg2;
    typename QEXTTypeTrait<T_arg3>::Take m_arg3;
};


template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTSignalSend3<T_return, T_arg1, T_arg2, T_arg3, QEXTNil>
{
    typedef QEXTSignalSend3<T_return, T_arg1, T_arg2, T_arg3, QEXTNil > SelfType;
    typedef T_return                                                    ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                           IteratorType;
    typedef typename SlotType::CallType                                 CallType;


    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExec exec(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "exec" is destroyed.
        //This avoids a leak on MSVC++ - see http://bugzilla.gnome.org/show_bug.cgi?id=306249
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

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3);
            for (++iter; iter != slotList.end(); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3);
            }
        }

        return m_result;
    }


    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExec exec(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "exec" is destroyed.
        //This avoids a leak on MSVC++ - see http://bugzilla.gnome.org/show_bug.cgi?id=306249
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
                return T_return(); // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3);
            for (++iter; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3);
            }
        }

        return m_result;
    }
};


template <typename T_arg1, typename T_arg2, typename T_arg3>
struct QEXTSignalSend3<void, T_arg1, T_arg2, T_arg3, QEXTNil>
{
    typedef QEXTSignalSend3<void, T_arg1, T_arg2, T_arg3, QEXTNil>  SelfType;
    typedef void                                                    ResultType;
    typedef QEXTSlot<void, T_arg1, T_arg2, T_arg3>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                       IteratorType;
    typedef typename SlotType::CallType                             CallType;


    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }

        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        for (IteratorType iter = slotList.begin(); iter != slotList.end(); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3);
        }
    }


    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;

        for (ReverseIteratorType iter = ReverseIteratorType(slotList.end()); iter != ReverseIteratorType(slotList.begin()); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3);
        }
    }
};


template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_accumulator>
struct QEXTSignalSend4
{
    typedef QEXTSignalSend4<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_accumulator>    SelfType;
    typedef typename T_accumulator::ResultType                                          ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4>                          SlotType;
    typedef qextinternal::QEXTSlotIteratorBuffer<SelfType, T_return>                    SlotIteratorBufferType;
    typedef qextinternal::QEXTSlotReverseIteratorBuffer<SelfType, T_return>             SlotReverseIteratorBufferType;
    typedef QEXTSignalImpl::ConstIteratorType                                           IteratorType;


    QEXTSignalSend4(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4)
        : m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4) {}

    T_return operator()(const SlotType &slot) const {
        return (reinterpret_cast<typename SlotType::CallType>(slot.m_slotRep->m_call))(slot.m_slotRep, m_arg1, m_arg2, m_arg3, m_arg4);
    }


    static ResultType send(QEXTSignalImpl* impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self(arg1, arg2, arg3, arg4);
        return accumulator(SlotIteratorBufferType(slotList.begin(), &self),
                           SlotIteratorBufferType(slotList.end(), &self));
    }

    static ResultType sendReverse(QEXTSignalImpl* impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3,
                                  typename QEXTTypeTrait<T_arg4>::Take arg4) {
        T_accumulator accumulator;

        if (!impl) {
            return accumulator(SlotIteratorBufferType(), SlotIteratorBufferType());
        }

        QEXTSignalExec exec(impl);
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

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTSignalSend4<T_return, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil>
{
    typedef QEXTSignalSend4<T_return, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil > SelfType;
    typedef T_return                                                            ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                                   IteratorType;
    typedef typename SlotType::CallType                                         CallType;


    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExec exec(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "exec" is destroyed.
        //This avoids a leak on MSVC++ - see http://bugzilla.gnome.org/show_bug.cgi?id=306249
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

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4);
            for (++iter; iter != slotList.end(); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4);
            }
        }

        return m_result;
    }

    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3,
                                  typename QEXTTypeTrait<T_arg4>::Take arg4) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExec exec(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "exec" is destroyed.
        //This avoids a leak on MSVC++ - see http://bugzilla.gnome.org/show_bug.cgi?id=306249
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
                return T_return(); // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4);
            for (++iter; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4);
            }
        }

        return m_result;
    }
};


template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
struct QEXTSignalSend4<void, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil>
{
    typedef QEXTSignalSend4<void, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil>  SelfType;
    typedef void                                                            ResultType;
    typedef QEXTSlot<void, T_arg1, T_arg2, T_arg3, T_arg4>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                               IteratorType;
    typedef typename SlotType::CallType                                     CallType;

    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        for (IteratorType iter = slotList.begin(); iter != slotList.end(); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4);
        }
    }

    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3,
                                  typename QEXTTypeTrait<T_arg4>::Take arg4) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;

        for (ReverseIteratorType iter = ReverseIteratorType(slotList.end()); iter != ReverseIteratorType(slotList.begin()); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4);
        }
    }
};


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


    QEXTSignalSend5(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4,
                    typename QEXTTypeTrait<T_arg5>::Take arg5)
        : m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5) {}

    T_return operator()(const SlotType &slot) const {
        return (reinterpret_cast<typename SlotType::CallType>(slot.m_slotRep->m_call))(slot.m_slotRep, m_arg1, m_arg2, m_arg3, m_arg4, m_arg5);
    }

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

        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self(arg1, arg2, arg3, arg4, arg5);
        return accumulator(SlotIteratorBufferType(slotList.begin(), &self),
                           SlotIteratorBufferType(slotList.end(), &self));
    }

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

        QEXTSignalExec exec(impl);
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


template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTSignalSend5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil>
{
    typedef QEXTSignalSend5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil > SelfType;
    typedef T_return                                                                    ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                                           IteratorType;
    typedef typename SlotType::CallType                                                 CallType;

    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExec exec(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "exec" is destroyed.
        //This avoids a leak on MSVC++ - see http://bugzilla.gnome.org/show_bug.cgi?id=306249
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

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4, arg5);
            for (++iter; iter != slotList.end(); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4, arg5);
            }
        }

        return m_result;
    }


    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3,
                                  typename QEXTTypeTrait<T_arg4>::Take arg4,
                                  typename QEXTTypeTrait<T_arg5>::Take arg5) {
        if (!impl || impl->m_slotList.empty()) {
            return T_return();
        }

        QEXTSignalExec exec(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "exec" is destroyed.
        //This avoids a leak on MSVC++ - see http://bugzilla.gnome.org/show_bug.cgi?id=306249
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
                return T_return(); // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4, arg5);
            for (++iter; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4, arg5);
            }
        }

        return m_result;
    }
};


template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
struct QEXTSignalSend5<void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil>
{
    typedef QEXTSignalSend5<void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil>  SelfType;
    typedef void                                                                    ResultType;
    typedef QEXTSlot<void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                                       IteratorType;
    typedef typename SlotType::CallType                                             CallType;

    static ResultType send(QEXTSignalImpl *impl,
                           typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        for (IteratorType iter = slotList.begin(); iter != slotList.end(); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4, arg5);
        }
    }


    static ResultType sendReverse(QEXTSignalImpl *impl,
                                  typename QEXTTypeTrait<T_arg1>::Take arg1,
                                  typename QEXTTypeTrait<T_arg2>::Take arg2,
                                  typename QEXTTypeTrait<T_arg3>::Take arg3,
                                  typename QEXTTypeTrait<T_arg4>::Take arg4,
                                  typename QEXTTypeTrait<T_arg5>::Take arg5) {
        if (!impl || impl->m_slotList.empty()) {
            return;
        }
        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;
        for (ReverseIteratorType iter = ReverseIteratorType(slotList.end()); iter != ReverseIteratorType(slotList.begin()); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4, arg5);
        }
    }
};


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

    QEXTSignalSend6(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4,
                    typename QEXTTypeTrait<T_arg5>::Take arg5,
                    typename QEXTTypeTrait<T_arg6>::Take arg6)
        : m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5), m_arg6(arg6) {}

    T_return operator()(const SlotType &slot) const {
        return (reinterpret_cast<typename SlotType::CallType>(slot.m_slotRep->m_call))(slot.m_slotRep, m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6);
    }

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

        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self (arg1, arg2, arg3, arg4, arg5, arg6);
        return accumulator(SlotIteratorBufferType(slotList.begin(), &self),
                           SlotIteratorBufferType(slotList.end(), &self));
    }

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

        QEXTSignalExec exec(impl);
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


template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTSignalSend6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
{
    typedef QEXTSignalSend6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil > SelfType;
    typedef T_return                                                                            ResultType;
    typedef QEXTSlot<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                                                   IteratorType;
    typedef typename SlotType::CallType                                                         CallType;


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

        QEXTSignalExec exec(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "exec" is destroyed.
        //This avoids a leak on MSVC++ - see http://bugzilla.gnome.org/show_bug.cgi?id=306249
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

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4, arg5, arg6);
            for (++iter; iter != slotList.end(); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4, arg5, arg6);
            }
        }

        return m_result;
    }


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

        QEXTSignalExec exec(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "exec" is destroyed.
        //This avoids a leak on MSVC++ - see http://bugzilla.gnome.org/show_bug.cgi?id=306249
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
                return T_return(); // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4, arg5, arg6);
            for (++iter; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4, arg5, arg6);
            }
        }

        return m_result;
    }
};


template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
struct QEXTSignalSend6<void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
{
    typedef QEXTSignalSend6<void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>  SelfType;
    typedef void                                                                            ResultType;
    typedef QEXTSlot<void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                                               IteratorType;
    typedef typename SlotType::CallType                                                     CallType;


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
        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        for (IteratorType iter = slotList.begin(); iter != slotList.end(); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4, arg5, arg6);
        }
    }


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
        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;
        for (ReverseIteratorType iter = ReverseIteratorType(slotList.end()); iter != ReverseIteratorType(slotList.begin()); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4, arg5, arg6);
        }
    }
};


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

    QEXTSignalSend7(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4,
                    typename QEXTTypeTrait<T_arg5>::Take arg5,
                    typename QEXTTypeTrait<T_arg6>::Take arg6,
                    typename QEXTTypeTrait<T_arg7>::Take arg7)
        : m_arg1(arg1), m_arg2(arg2), m_arg3(arg3), m_arg4(arg4), m_arg5(arg5), m_arg6(arg6), m_arg7(arg7) {}

    T_return operator()(const SlotType &slot) const {
        return (reinterpret_cast<typename SlotType::CallType>(slot.m_slotRep->m_call))(slot.m_slotRep, m_arg1, m_arg2, m_arg3, m_arg4, m_arg5, m_arg6, m_arg7);
    }

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

        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        SelfType self(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        return accumulator(SlotIteratorBufferType(slotList.begin(), &self),
                           SlotIteratorBufferType(slotList.end(), &self));
    }


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

        QEXTSignalExec exec(impl);
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

        QEXTSignalExec exec(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "exec" is destroyed.
        //This avoids a leak on MSVC++ - see http://bugzilla.gnome.org/show_bug.cgi?id=306249
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

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
            for (++iter; iter != slotList.end(); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
            }
        }

        return m_result;
    }


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

        QEXTSignalExec exec(impl);
        T_return m_result = T_return();

        //Use this scope to make sure that "slotList" is destroyed before "exec" is destroyed.
        //This avoids a leak on MSVC++ - see http://bugzilla.gnome.org/show_bug.cgi?id=306249
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
                return T_return(); // note that 'T_return m_result();' doesn't work => define 'm_result' after this line and initialize as follows:
            }

            m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
            for (++iter; iter != ReverseIteratorType(slotList.begin()); ++iter) {
                if (iter->isEmpty() || iter->isBlocked()) {
                    continue;
                }
                m_result = (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
            }
        }

        return m_result;
    }
};


template <typename T_arg1, typename T_arg2, typename T_arg3,
          typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
struct QEXTSignalSend7<void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, QEXTNil>
{
    typedef QEXTSignalSend7<void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, QEXTNil>  SelfType;
    typedef void                                                                                    ResultType;
    typedef QEXTSlot<void, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7>                  SlotType;
    typedef QEXTSignalImpl::ConstIteratorType                                                       IteratorType;
    typedef typename SlotType::CallType                                                             CallType;

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
        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        for (IteratorType iter = slotList.begin(); iter != slotList.end(); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }
    }


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
        QEXTSignalExec exec(impl);
        QEXTTempSlotList slotList(impl->m_slotList);

        typedef std::reverse_iterator<QEXTSignalImpl::IteratorType> ReverseIteratorType;

        for (ReverseIteratorType iter = ReverseIteratorType(slotList.end()); iter != ReverseIteratorType(slotList.begin()); ++iter) {
            if (iter->isEmpty() || iter->isBlocked()) {
                continue;
            }
            (reinterpret_cast<CallType>(iter->m_slotRep->m_call))(iter->m_slotRep, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }
    }
};


} /* namespace qextinternal */


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


    Iterator connect(const SlotType &slot) {
        return Iterator(QEXTSignalBase::connect(static_cast<const QEXTSlotBase&>(slot)));
    }

    ResultType send() const {
        return SenderType::send(m_impl);
    }

    ResultType sendReverse() const {
        return SenderType::sendReverse(m_impl);
    }

    ResultType operator()() const {
        return send();
    }

    QEXTBoundConstMemberFunctor0<ResultType, QEXTSignal0> makeSlot() const {
        return QEXTBoundConstMemberFunctor0<ResultType, QEXTSignal0>(this, &QEXTSignal0::send);
    }

    SlotListType slotList() {
        return SlotListType(impl());
    }

    const SlotListType slotList() const {
        return SlotListType(const_cast<QEXTSignal0*>(this)->impl());
    }

    QEXTSignal0() {}

    QEXTSignal0(const QEXTSignal0 &src) : QEXTSignalBase(src) {}
};

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

    Iterator connect(const SlotType &slot) {
        return Iterator(QEXTSignalBase::connect(static_cast<const QEXTSlotBase&>(slot)));
    }

    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return SenderType::send(m_impl, arg1);
    }

    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return SenderType::sendReverse(m_impl, arg1);
    }

    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1) const {
        return this->send(arg1);
    }

    QEXTBoundConstMemberFunctor1<
    ResultType, QEXTSignal1,
    typename QEXTTypeTrait<T_arg1>::Take>
    makeSlot() const {
        return QEXTBoundConstMemberFunctor1<
                ResultType, QEXTSignal1,
                typename QEXTTypeTrait<T_arg1>::Take>(this, &QEXTSignal1::send);
    }

    SlotListType slotList() {
        return SlotListType(impl());
    }


    const SlotListType slotList() const {
        return SlotListType(const_cast<QEXTSignal1*>(this)->impl());
    }

    QEXTSignal1() {}

    QEXTSignal1(const QEXTSignal1 &src) : QEXTSignalBase(src) {}
};


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


    Iterator connect(const SlotType &slot) {
        return Iterator(QEXTSignalBase::connect(static_cast<const QEXTSlotBase&>(slot)));
    }


    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return SenderType::send(m_impl, arg1, arg2);
    }

    /** Triggers the emission of the QEXTSignal in reverse order (see send()). */
    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return SenderType::sendReverse(m_impl, arg1, arg2);
    }

    /** Triggers the emission of the QEXTSignal (see send()). */
    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                          typename QEXTTypeTrait<T_arg2>::Take arg2) const {
        return send(arg1, arg2);
    }

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

    SlotListType slotList() {
        return SlotListType(impl());
    }

    const SlotListType slotList() const {
        return SlotListType(const_cast<QEXTSignal2*>(this)->impl());
    }

    QEXTSignal2() {}

    QEXTSignal2(const QEXTSignal2 &src) : QEXTSignalBase(src) {}
};


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


    Iterator connect(const SlotType &slot) {
        return Iterator(QEXTSignalBase::connect(static_cast<const QEXTSlotBase&>(slot)));
    }


    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return SenderType::send(m_impl, arg1, arg2, arg3);
    }

    /** Triggers the emission of the QEXTSignal in reverse order (see send()). */
    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return SenderType::sendReverse(m_impl, arg1, arg2, arg3);
    }

    /** Triggers the emission of the QEXTSignal (see send()). */
    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                          typename QEXTTypeTrait<T_arg2>::Take arg2,
                          typename QEXTTypeTrait<T_arg3>::Take arg3) const {
        return send(arg1, arg2, arg3);
    }


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


    SlotListType slotList() {
        return SlotListType(impl());
    }

    const SlotListType slotList() const {
        return SlotListType(const_cast<QEXTSignal3*>(this)->impl());
    }

    QEXTSignal3() {}

    QEXTSignal3(const QEXTSignal3 &src) : QEXTSignalBase(src) {}
};


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


    Iterator connect(const SlotType &slot) {
        return Iterator(QEXTSignalBase::connect(static_cast<const QEXTSlotBase&>(slot)));
    }


    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return SenderType::send(m_impl, arg1, arg2, arg3, arg4);
    }

    /** Triggers the emission of the QEXTSignal in reverse order (see send()). */
    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return SenderType::sendReverse(m_impl, arg1, arg2, arg3, arg4);
    }

    /** Triggers the emission of the QEXTSignal (see send()). */
    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                          typename QEXTTypeTrait<T_arg2>::Take arg2,
                          typename QEXTTypeTrait<T_arg3>::Take arg3,
                          typename QEXTTypeTrait<T_arg4>::Take arg4) const {
        return send(arg1, arg2, arg3, arg4);
    }

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

    SlotListType slotList() {
        return SlotListType(impl());
    }

    const SlotListType slotList() const {
        return SlotListType(const_cast<QEXTSignal4*>(this)->impl());
    }

    QEXTSignal4() {}

    QEXTSignal4(const QEXTSignal4 &src) : QEXTSignalBase(src) {}
};


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


    Iterator connect(const SlotType &slot) {
        return Iterator(QEXTSignalBase::connect(static_cast<const QEXTSlotBase&>(slot)));
    }

    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4,
                    typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return SenderType::send(m_impl, arg1, arg2, arg3, arg4, arg5);
    }

    /** Triggers the emission of the QEXTSignal in reverse order (see send()). */
    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return SenderType::sendReverse(m_impl, arg1, arg2, arg3, arg4, arg5);
    }

    /** Triggers the emission of the QEXTSignal (see send()). */
    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                          typename QEXTTypeTrait<T_arg2>::Take arg2,
                          typename QEXTTypeTrait<T_arg3>::Take arg3,
                          typename QEXTTypeTrait<T_arg4>::Take arg4,
                          typename QEXTTypeTrait<T_arg5>::Take arg5) const {
        return send(arg1, arg2, arg3, arg4, arg5);
    }


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

    SlotListType slotList() {
        return SlotListType(impl());
    }

    const SlotListType slotList() const {
        return SlotListType(const_cast<QEXTSignal5*>(this)->impl());
    }

    QEXTSignal5() {}

    QEXTSignal5(const QEXTSignal5 &src) : QEXTSignalBase(src) {}
};


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

    Iterator connect(const SlotType &slot) {
        return Iterator(QEXTSignalBase::connect(static_cast<const QEXTSlotBase&>(slot)));
    }

    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4,
                    typename QEXTTypeTrait<T_arg5>::Take arg5,
                    typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return SenderType::send(m_impl, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /** Triggers the emission of the QEXTSignal in reverse order (see send()). */
    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5,
                           typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return SenderType::sendReverse(m_impl, arg1, arg2, arg3, arg4, arg5, arg6);
    }

    /** Triggers the emission of the QEXTSignal (see send()). */
    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                          typename QEXTTypeTrait<T_arg2>::Take arg2,
                          typename QEXTTypeTrait<T_arg3>::Take arg3,
                          typename QEXTTypeTrait<T_arg4>::Take arg4,
                          typename QEXTTypeTrait<T_arg5>::Take arg5,
                          typename QEXTTypeTrait<T_arg6>::Take arg6) const {
        return send(arg1, arg2, arg3, arg4, arg5, arg6);
    }

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

    SlotListType slotList() {
        return SlotListType(impl());
    }

    const SlotListType slotList() const {
        return SlotListType(const_cast<QEXTSignal6*>(this)->impl());
    }

    QEXTSignal6() {}

    QEXTSignal6(const QEXTSignal6 &src) : QEXTSignalBase(src) {}
};

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

    Iterator connect(const SlotType &slot) {
        return Iterator(QEXTSignalBase::connect(static_cast<const QEXTSlotBase&>(slot)));
    }

    ResultType send(typename QEXTTypeTrait<T_arg1>::Take arg1,
                    typename QEXTTypeTrait<T_arg2>::Take arg2,
                    typename QEXTTypeTrait<T_arg3>::Take arg3,
                    typename QEXTTypeTrait<T_arg4>::Take arg4,
                    typename QEXTTypeTrait<T_arg5>::Take arg5,
                    typename QEXTTypeTrait<T_arg6>::Take arg6,
                    typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return SenderType::send(m_impl, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    /** Triggers the emission of the QEXTSignal in reverse order (see send()). */
    ResultType sendReverse(typename QEXTTypeTrait<T_arg1>::Take arg1,
                           typename QEXTTypeTrait<T_arg2>::Take arg2,
                           typename QEXTTypeTrait<T_arg3>::Take arg3,
                           typename QEXTTypeTrait<T_arg4>::Take arg4,
                           typename QEXTTypeTrait<T_arg5>::Take arg5,
                           typename QEXTTypeTrait<T_arg6>::Take arg6,
                           typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return SenderType::sendReverse(m_impl, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    /** Triggers the emission of the QEXTSignal (see send()). */
    ResultType operator()(typename QEXTTypeTrait<T_arg1>::Take arg1,
                          typename QEXTTypeTrait<T_arg2>::Take arg2,
                          typename QEXTTypeTrait<T_arg3>::Take arg3,
                          typename QEXTTypeTrait<T_arg4>::Take arg4,
                          typename QEXTTypeTrait<T_arg5>::Take arg5,
                          typename QEXTTypeTrait<T_arg6>::Take arg6,
                          typename QEXTTypeTrait<T_arg7>::Take arg7) const {
        return send(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

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

    SlotListType slotList() {
        return SlotListType(impl());
    }

    const SlotListType slotList() const {
        return SlotListType(const_cast<QEXTSignal7*>(this)->impl());
    }

    QEXTSignal7() {}

    QEXTSignal7(const QEXTSignal7 &src) : QEXTSignalBase(src) {}
};


template <typename T_return,
          typename T_arg1 = QEXTNil, typename T_arg2 = QEXTNil, typename T_arg3 = QEXTNil,
          typename T_arg4 = QEXTNil, typename T_arg5 = QEXTNil, typename T_arg6 = QEXTNil, typename T_arg7 = QEXTNil>
class QEXTSignal : public QEXTSignal7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, QEXTNil>
{
public:
    typedef QEXTSignal7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, QEXTNil> BaseType;

    template <typename T_accumulator>
    class Accumulated : public QEXTSignal7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_accumulator>
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &src) : QEXTSignal7<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7, T_accumulator>(src) {}
    };

    QEXTSignal() {}
    QEXTSignal(const QEXTSignal &src) : BaseType(src) {}
};

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
class QEXTSignal <T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
        : public QEXTSignal6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil>
{
public:
    typedef QEXTSignal6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, QEXTNil> BaseType;

    template <typename T_accumulator>
    class Accumulated : public QEXTSignal6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_accumulator>
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &src) : QEXTSignal6<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_accumulator>(src) {}
    };

    QEXTSignal() {}
    QEXTSignal(const QEXTSignal &src) : BaseType(src) {}
};

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
class QEXTSignal<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil, QEXTNil>
        : public QEXTSignal5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil>
{
public:
    typedef QEXTSignal5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, QEXTNil> BaseType;

    template <typename T_accumulator>
    class Accumulated : public QEXTSignal5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_accumulator>
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &src) : QEXTSignal5<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_accumulator>(src) {}
    };

    QEXTSignal() {}
    QEXTSignal(const QEXTSignal &src) : BaseType(src) {}
};

template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
class QEXTSignal <T_return, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSignal4<T_return, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil>
{
public:
    typedef QEXTSignal4<T_return, T_arg1, T_arg2, T_arg3, T_arg4, QEXTNil> BaseType;

    template <typename T_accumulator>
    class Accumulated : public QEXTSignal4<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_accumulator>
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &src) : QEXTSignal4<T_return, T_arg1, T_arg2, T_arg3, T_arg4, T_accumulator>(src) {}
    };

    QEXTSignal() {}
    QEXTSignal(const QEXTSignal &src) : BaseType(src) {}
};


template <typename T_return, typename T_arg1, typename T_arg2, typename T_arg3>
class QEXTSignal <T_return, T_arg1, T_arg2, T_arg3, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSignal3<T_return, T_arg1, T_arg2, T_arg3, QEXTNil>
{
public:
    typedef QEXTSignal3<T_return, T_arg1, T_arg2, T_arg3, QEXTNil> BaseType;

    template <typename T_accumulator>
    class Accumulated : public QEXTSignal3<T_return, T_arg1, T_arg2, T_arg3, T_accumulator>
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &src) : QEXTSignal3<T_return, T_arg1, T_arg2, T_arg3, T_accumulator>(src) {}
    };

    QEXTSignal() {}
    QEXTSignal(const QEXTSignal &src) : BaseType(src) {}
};

template <typename T_return, typename T_arg1, typename T_arg2>
class QEXTSignal <T_return, T_arg1, T_arg2, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSignal2<T_return, T_arg1, T_arg2, QEXTNil>
{
public:
    typedef QEXTSignal2<T_return, T_arg1, T_arg2, QEXTNil> BaseType;

    template <typename T_accumulator>
    class Accumulated : public QEXTSignal2<T_return, T_arg1, T_arg2, T_accumulator>
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &src) : QEXTSignal2<T_return, T_arg1, T_arg2, T_accumulator>(src) {}
    };

    QEXTSignal() {}
    QEXTSignal(const QEXTSignal &src) : BaseType(src) {}
};


template <typename T_return, typename T_arg1>
class QEXTSignal <T_return, T_arg1, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSignal1<T_return, T_arg1, QEXTNil>
{
public:
    typedef QEXTSignal1<T_return, T_arg1, QEXTNil> BaseType;

    template <typename T_accumulator>
    class Accumulated : public QEXTSignal1<T_return, T_arg1, T_accumulator>
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &src) : QEXTSignal1<T_return, T_arg1, T_accumulator>(src) {}
    };

    QEXTSignal() {}
    QEXTSignal(const QEXTSignal &src) : BaseType(src) {}
};

template <typename T_return>
class QEXTSignal <T_return, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil, QEXTNil>
        : public QEXTSignal0<T_return, QEXTNil>
{
public:
    typedef QEXTSignal0<T_return, QEXTNil> BaseType;

    template <typename T_accumulator>
    class Accumulated : public QEXTSignal0<T_return, T_accumulator>
    {
    public:
        Accumulated() {}
        Accumulated(const Accumulated &src) : QEXTSignal0<T_return, T_accumulator>(src) {}
    };

    QEXTSignal() {}
    QEXTSignal(const QEXTSignal &src) : BaseType(src) {}
};


#endif // QEXTSIGNAL_H
