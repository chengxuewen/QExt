#include <qextSignal.h>



namespace qextPrivate
{

    QEXTSignalData::QEXTSignalData()
        : m_referenceCount(0)
        , m_executionCount(0)
        , m_deferred(0)
    {

    }

    QEXTSignalData::~QEXTSignalData()
    {
        m_slotList.clear();
        m_selfIteratorList.clear();
    }

    QEXTSignalData &QEXTSignalData::operator=(const QEXTSignalData &other)
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

    bool QEXTSignalData::operator==(const QEXTSignalData &other) const
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

    bool QEXTSignalData::operator!=(const QEXTSignalData &other) const
    {
        return !(*this == other);
    }

    void QEXTSignalData::clear()
    {
        // Don't let QEXTSignalImpl::notify() erase the slots. It would invalidate the
        // iterator in the following loop.
        const bool savedDeferred = m_deferred;
        QEXTSignalExecution execution(this);

        // Disconnect all connected slots before they are deleted.
        // QEXTSignalImpl::notify() will be called and delete the QEXTSelfIterator structs.
        for (Iterator iter = m_slotList.begin(); iter != m_slotList.end(); ++iter)
        {
            iter->disconnect();
        }
        m_deferred = savedDeferred;
        m_slotList.clear();
    }

    QEXTSignalData::Size QEXTSignalData::size() const
    {
        return m_slotList.size();
    }

    bool QEXTSignalData::isBlocked() const
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

    void QEXTSignalData::setBlock(bool block)
    {
        for (Iterator iter = m_slotList.begin(); iter != m_slotList.end(); ++iter)
        {
            iter->setBlock(block);
        }
    }

    QEXTSignalData::Iterator QEXTSignalData::connect(const QEXTSlotBase &slot)
    {
        return this->insert(m_slotList.end(), slot);
    }

    QEXTSignalData::Iterator QEXTSignalData::insert(Iterator iter, const QEXTSlotBase &slot)
    {
        Iterator temp = m_slotList.insert(iter, slot);
        m_selfIteratorList.push_back(SelfIterator(this, temp));
        SelfIterator *selfIter = &(m_selfIteratorList.back());
        temp->setParent(selfIter, &notify);
        return temp;
    }

    QEXTSignalData::Iterator QEXTSignalData::erase(Iterator iter)
    {
        // Don't let QEXTSignalImpl::notify() erase the slot. It would be more
        // difficult to get the correct return value from QEXTSignalImpl::erase().
        const bool savedDeferred = m_deferred;
        QEXTSignalExecution execution(this);

        // Disconnect the slot before it is deleted.
        // QEXTSignalImpl::notify() will be called and delete the QEXTSelfIterator struct.
        iter->disconnect();

        m_deferred = savedDeferred;
        return m_slotList.erase(iter);
    }

    void QEXTSignalData::sweep()
    {
        // The deletion of a slot may cause the deletion of a QEXTSignalBase,
        // a decrementation of m_refCount, and the deletion of this.
        // In that case, the deletion of this is deferred to ~QEXTSignalExecution().
        QEXTSignalExecution execution(this);

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

    void *QEXTSignalData::notify(void *data)
    {
        SelfIterator *selfIter = static_cast<SelfIterator *>(data);

        if (0 == selfIter->first->m_executionCount)
        {
            // The deletion of a slot may cause the deletion of a QEXTSignalBase,
            // a decrementation of selfIter->m_self->m_referenceCount, and the deletion of selfIter->m_self.
            // In that case, the deletion of selfIter->m_self is deferred to ~QEXTSignalExecution().
            QEXTSignalExecution execution(selfIter->first);
            selfIter->first->m_slotList.erase(selfIter->second);
        }
        else        // This is occuring during signal send or slot erasure.
        {
            selfIter->first->m_deferred = QEXT_ATOMIC_INT_TRUE; // => sweep() will be called from ~QEXTSignalExecution() after signal send.
        }
        // This is safer because we don't have to care about our iterators in send(), clear(), and erase().
        return QEXT_DECL_NULLPTR;
    }



    QEXTSignalBase::QEXTSignalBase()
        : m_data(QEXT_DECL_NULLPTR)
    {

    }

    QEXTSignalBase::QEXTSignalBase(const QEXTSignalBase &other)
        : m_data(other.data())
    {
        m_data->reference();
    }

    QEXTSignalBase::~QEXTSignalBase()
    {
        if (m_data)
        {
            // Disconnect all slots before m_impl is deleted.
            // TODO: Move the QEXTSignalImpl::clear() call to ~QEXTSignalImpl() when ABI can be broken.
            if (m_data->m_referenceCount == 1)
            {
                m_data->clear();
            }
            m_data->unreference();
        }
    }

    QEXTSignalBase &QEXTSignalBase::operator=(const QEXTSignalBase &other)
    {
        if (this != &other)
        {
            if (this->data())
            {
                // Disconnect all slots before m_impl is deleted.
                // TODO: Move the QEXTSignalImpl::clear() call to ~QEXTSignalImpl() when ABI can be broken.
                if (m_data->m_referenceCount == 1)
                {
                    m_data->clear();
                }
                m_data->unreference();
                m_data = QEXT_DECL_NULLPTR;
                this->data();
            }
            *m_data = *(other.data());
        }
        return *this;
    }

    bool QEXTSignalBase::operator==(const QEXTSignalBase &other) const
    {
        if (QEXT_DECL_NULLPTR != m_data && QEXT_DECL_NULLPTR != other.m_data)
        {
            return *m_data == *other.m_data;
        }
        else if (QEXT_DECL_NULLPTR == m_data && QEXT_DECL_NULLPTR == other.m_data)
        {
            return true;
        }
        return false;
    }

    bool QEXTSignalBase::operator!=(const QEXTSignalBase &other) const
    {
        return !(*this == other);
    }

    void QEXTSignalBase::clear()
    {
        if (m_data)
        {
            m_data->clear();
        }
    }

    QEXTSignalBase::Size QEXTSignalBase::size() const
    {
        return (m_data ? m_data->size() : 0);
    }

    bool QEXTSignalBase::isBlocked() const
    {
        return (m_data ? m_data->isBlocked() : true);
    }

    void QEXTSignalBase::setBlock(bool block)
    {
        if (m_data)
        {
            m_data->setBlock(block);
        }
    }

    void QEXTSignalBase::unblock()
    {
        if (m_data)
        {
            m_data->setBlock(false);
        }
    }

    QEXTSignalBase::Iterator QEXTSignalBase::connect(const QEXTSlotBase &slot)
    {
        return this->data()->connect(slot);
    }

    QEXTSignalBase::Iterator QEXTSignalBase::insert(Iterator iter, const QEXTSlotBase &slot)
    {
        return this->data()->insert(iter, slot);
    }

    QEXTSignalBase::Iterator QEXTSignalBase::erase(Iterator iter)
    {
        return this->data()->erase(iter);
    }

    QEXTSignalData *QEXTSignalBase::data() const
    {
        if (!m_data)
        {
            m_data = new QEXTSignalData;
            m_data->reference();  // start with a reference count of 1
        }
        return m_data;
    }



    QEXTSignalExecution::QEXTSignalExecution(const QEXTSignalData *signalData)
        : m_data(const_cast<QEXTSignalData *>(signalData))
    {
        m_data->referenceExecution();
    }

    QEXTSignalExecution::~QEXTSignalExecution()
    {
        m_data->unreferenceExecution();
    }

} // namespace qextPrivate



