#include <qextSlot.h>

namespace qextPrivate
{

    QEXTSlotData::QEXTSlotData() : m_trackable(QEXT_ATOMIC_INT_FALSE) {}

    QEXTSlotData::QEXTSlotData(const QEXTSlotData &other) : m_trackable(other.m_trackable), m_objectList(other.m_objectList) {}

    QEXTSlotData &QEXTSlotData::operator=(const QEXTSlotData &other)
    {
        if (this != &other)
        {
            m_trackable = other.m_trackable;
            m_objectList = other.m_objectList;
        }
        return *this;
    }

    bool QEXTSlotData::operator==(const QEXTSlotData &other) const
    {
        if (m_trackable == other.m_trackable)
        {
            return m_objectList == other.m_objectList;
        }
        return false;
    }

    bool QEXTSlotData::operator!=(const QEXTSlotData &other) const
    {
        return !(*this == other);
    }

    QEXTSlotBase::QEXTSlotBase()
        : m_blocked(QEXT_ATOMIC_INT_FALSE), m_parent(QEXT_DECL_NULLPTR), m_cleanupFunc(QEXT_DECL_NULLPTR), m_callFunc(QEXT_DECL_NULLPTR)
    {
    }

    QEXTSlotBase::QEXTSlotBase(const QSharedPointer< QEXTSlotData > &data)
        : m_blocked(QEXT_ATOMIC_INT_FALSE), m_parent(QEXT_DECL_NULLPTR), m_cleanupFunc(QEXT_DECL_NULLPTR), m_callFunc(QEXT_DECL_NULLPTR), m_data(data)
    {
    }

    QEXTSlotBase::QEXTSlotBase(const QEXTSlotBase &other)
        : m_blocked(other.m_blocked), m_parent(other.m_parent), m_cleanupFunc(other.m_cleanupFunc), m_callFunc(other.m_callFunc), m_data(other.m_data)
    {
    }

    QEXTSlotBase &QEXTSlotBase::operator=(const QEXTSlotBase &other)
    {
        if (this != &other)
        {
            m_blocked = other.m_blocked;
            m_parent = other.m_parent;
            m_cleanupFunc = other.m_cleanupFunc;
            m_callFunc = other.m_callFunc;
            m_data = other.m_data;
        }
        return *this;
    }

    bool QEXTSlotBase::operator==(const QEXTSlotBase &other) const
    {
        if (m_blocked == other.m_blocked && m_parent == other.m_parent)
        {
            if (m_cleanupFunc == other.m_cleanupFunc && m_callFunc == other.m_callFunc)
            {
                return m_data == other.m_data;
            }
        }
        return false;
    }

    bool QEXTSlotBase::operator!=(const QEXTSlotBase &other) const
    {
        return !(*this == other);
    }

    bool QEXTSlotBase::isNull() const
    {
        if (this->isTrackable() && !m_data->m_objectList.empty())
        {
            QList<QPointer< QObject > >::iterator iter;
            for (iter = m_data->m_objectList.begin(); iter != m_data->m_objectList.end(); ++iter)
            {
                if ((*iter).isNull())
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool QEXTSlotBase::isTrackable() const
    {
        if (!m_data.isNull())
        {
            return m_data->m_trackable == QEXT_ATOMIC_INT_TRUE;
        }
        return false;
    }

    bool QEXTSlotBase::isBlocked() const
    {
        return m_blocked == QEXT_ATOMIC_INT_TRUE;
    }

    bool QEXTSlotBase::setBlock(bool block)
    {
        m_blocked = block ? QEXT_ATOMIC_INT_TRUE : QEXT_ATOMIC_INT_FALSE;
        return true;
    }

    bool QEXTSlotBase::unblock()
    {
        m_blocked = QEXT_ATOMIC_INT_FALSE;
        return true;
    }

    bool QEXTSlotBase::isValid() const
    {
        return QEXT_DECL_NULLPTR != m_callFunc && !m_data.isNull() && !this->isNull();
    }

    void QEXTSlotBase::setParent(void *parent, HookFunction cleanup)
    {
        m_parent = parent;
        m_cleanupFunc = cleanup;
    }

    bool QEXTSlotBase::isConnected() const
    {
        return m_parent && m_cleanupFunc;
    }

    void QEXTSlotBase::disconnect()
    {
        if (m_parent)
        {
            // Invalidate the slot.
            // Must be done here because m_parent might defer the actual
            (m_cleanupFunc)(m_parent);  // Notify the parent (might lead to destruction of this!).
            m_parent = QEXT_DECL_NULLPTR; // Just a precaution.
        }
    }

} // namespace qextPrivate


