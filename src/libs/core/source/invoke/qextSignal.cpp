#include <qextSignal.h>


namespace detail
{

    QExtSignalData::QExtSignalData()
            : m_referenceCount(0)
              , m_executionCount(0)
              , m_deferred(0)
    {

    }

    QExtSignalData::~QExtSignalData()
    {
        m_slotList.clear();
        m_selfIteratorList.clear();
    }

    QExtSignalData &QExtSignalData::operator=(const QExtSignalData &other)
    {
        if (this != &other)
        {
            m_referenceCount = other.m_referenceCount;
            m_executionCount = other.m_executionCount;
            m_deferred = other.m_deferred;
            m_slotList = other.m_slotList;
        }
        return *this;
    }

    bool QExtSignalData::operator==(const QExtSignalData &other) const
    {
        if (m_referenceCount == other.m_referenceCount)
        {
            if (m_executionCount == other.m_executionCount)
            {
                if (m_deferred == other.m_deferred)
                {
                    return m_slotList == other.m_slotList;
                }
            }
        }
        return false;
    }

    bool QExtSignalData::operator!=(const QExtSignalData &other) const
    {
        return !(*this == other);
    }

    void QExtSignalData::clear()
    {
        // Don't let QExtSignalImpl::notify() erase the slots. It would invalidate the
        // iterator in the following loop.
        const bool savedDeferred = m_deferred;
        QExtSignalExecution execution(this);

        // Disconnect all connected slots before they are deleted.
        // QExtSignalImpl::notify() will be called and delete the QEXTSelfIterator structs.
        for (Iterator iter = m_slotList.begin(); iter != m_slotList.end(); ++iter)
        {
            iter->disconnect();
        }
        m_deferred = savedDeferred;
        m_slotList.clear();
    }

    QExtSignalData::Size QExtSignalData::size() const
    {
        return m_slotList.size();
    }

    bool QExtSignalData::isBlocked() const
    {
        for (ConstIterator iter = m_slotList.begin(); iter != m_slotList.end(); ++iter)
        {
            if (!iter->isBlocked())
            {
                return false;
            }
        }
        return true;
    }

    void QExtSignalData::setBlock(bool block)
    {
        for (Iterator iter = m_slotList.begin(); iter != m_slotList.end(); ++iter)
        {
            iter->setBlock(block);
        }
    }

    QExtSignalData::Iterator QExtSignalData::connect(const QExtFunctionBase &slot)
    {
        return this->insert(m_slotList.end(), slot);
    }

    QExtSignalData::Iterator QExtSignalData::insert(Iterator iter, const QExtFunctionBase &slot)
    {
        Iterator temp = m_slotList.insert(iter, slot);
        m_selfIteratorList.push_back(SelfIterator(this, temp));
        SelfIterator *selfIter = &(m_selfIteratorList.back());
        temp->setParent(selfIter, &notify);
        return temp;
    }

    QExtSignalData::Iterator QExtSignalData::erase(Iterator iter)
    {
        // Don't let QExtSignalImpl::notify() erase the slot. It would be more
        // difficult to get the correct return value from QExtSignalImpl::erase().
        const bool savedDeferred = m_deferred;
        QExtSignalExecution execution(this);

        // Disconnect the slot before it is deleted.
        // QExtSignalImpl::notify() will be called and delete the QEXTSelfIterator struct.
        iter->disconnect();

        m_deferred = savedDeferred;
        return m_slotList.erase(iter);
    }

    void QExtSignalData::sweep()
    {
        // The deletion of a slot may cause the deletion of a QExtSignalBase,
        // a decrementation of m_refCount, and the deletion of this.
        // In that case, the deletion of this is deferred to ~QExtSignalExecution().
        QExtSignalExecution execution(this);

        m_deferred = QEXT_ATOMIC_INT_FALSE;
        Iterator iter = m_slotList.begin();
        while (iter != m_slotList.end())
        {
            if (!(*iter).isValid())
            {
                iter = m_slotList.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }

    void *QExtSignalData::notify(void *data)
    {
        SelfIterator *selfIter = static_cast<SelfIterator *>(data);

        if (0 == selfIter->first->m_executionCount)
        {
            // The deletion of a slot may cause the deletion of a QExtSignalBase,
            // a decrementation of selfIter->m_self->m_referenceCount, and the deletion of selfIter->m_self.
            // In that case, the deletion of selfIter->m_self is deferred to ~QExtSignalExecution().
            QExtSignalExecution execution(selfIter->first);
            selfIter->first->m_slotList.erase(selfIter->second);
        }
        else        // This is occuring during signal send or slot erasure.
        {
            selfIter->first->m_deferred = QEXT_ATOMIC_INT_TRUE; // => sweep() will be called from ~QExtSignalExecution() after signal send.
        }
        // This is safer because we don't have to care about our iterators in send(), clear(), and erase().
        return QEXT_NULLPTR;
    }

    QExtSignalBase::QExtSignalBase()
            : m_data(QEXT_NULLPTR)
    {

    }

    QExtSignalBase::QExtSignalBase(const QExtSignalBase &other)
            : m_data(other.data())
    {
        m_data->reference();
    }

    QExtSignalBase::~QExtSignalBase()
    {
        if (m_data)
        {
            // Disconnect all slots before m_impl is deleted.
            // TODO: Move the QExtSignalImpl::clear() call to ~QExtSignalImpl() when ABI can be broken.
            if (m_data->m_referenceCount == 1)
            {
                m_data->clear();
            }
            m_data->unreference();
        }
    }

    QExtSignalBase &QExtSignalBase::operator=(const QExtSignalBase &other)
    {
        if (this != &other)
        {
            if (this->data())
            {
                // Disconnect all slots before m_impl is deleted.
                // TODO: Move the QExtSignalImpl::clear() call to ~QExtSignalImpl() when ABI can be broken.
                if (m_data->m_referenceCount == 1)
                {
                    m_data->clear();
                }
                m_data->unreference();
                m_data = QEXT_NULLPTR;
                this->data();
            }
            *m_data = *(other.data());
        }
        return *this;
    }

    bool QExtSignalBase::operator==(const QExtSignalBase &other) const
    {
        if (QEXT_NULLPTR != m_data && QEXT_NULLPTR != other.m_data)
        {
            return *m_data == *other.m_data;
        }
        else if (QEXT_NULLPTR == m_data && QEXT_NULLPTR == other.m_data)
        {
            return true;
        }
        return false;
    }

    bool QExtSignalBase::operator!=(const QExtSignalBase &other) const
    {
        return !(*this == other);
    }

    void QExtSignalBase::clear()
    {
        if (m_data)
        {
            m_data->clear();
        }
    }

    QExtSignalBase::Size QExtSignalBase::size() const
    {
        return (m_data ? m_data->size() : 0);
    }

    bool QExtSignalBase::isBlocked() const
    {
        return (m_data ? m_data->isBlocked() : true);
    }

    void QExtSignalBase::setBlock(bool block)
    {
        if (m_data)
        {
            m_data->setBlock(block);
        }
    }

    void QExtSignalBase::unblock()
    {
        if (m_data)
        {
            m_data->setBlock(false);
        }
    }

    QExtSignalBase::Iterator QExtSignalBase::connect(const QExtFunctionBase &slot)
    {
        return this->data()->connect(slot);
    }

    QExtSignalBase::Iterator QExtSignalBase::insert(Iterator iter, const QExtFunctionBase &slot)
    {
        return this->data()->insert(iter, slot);
    }

    QExtSignalBase::Iterator QExtSignalBase::erase(Iterator iter)
    {
        return this->data()->erase(iter);
    }

    QExtSignalData *QExtSignalBase::data() const
    {
        if (!m_data)
        {
            m_data = new QExtSignalData;
            m_data->reference();  // start with a reference count of 1
        }
        return m_data;
    }

    QExtSignalExecution::QExtSignalExecution(const QExtSignalData *signalData)
            : m_data(const_cast<QExtSignalData *>(signalData))
    {
        m_data->referenceExecution();
    }

    QExtSignalExecution::~QExtSignalExecution()
    {
        m_data->unreferenceExecution();
    }

} // namespace QExtPrivate



