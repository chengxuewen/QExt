#include <qextFunction.h>

namespace detail
{

    QExtFunctionData::QExtFunctionData() : m_trackable(QEXT_ATOMIC_INT_FALSE) {}

    QExtFunctionData::QExtFunctionData(const QExtFunctionData &other) : m_trackable(other.m_trackable), m_objectList(other.m_objectList) {}

    QExtFunctionData &QExtFunctionData::operator=(const QExtFunctionData &other)
    {
        if (this != &other)
        {
            m_trackable = other.m_trackable;
            m_objectList = other.m_objectList;
        }
        return *this;
    }

    bool QExtFunctionData::operator==(const QExtFunctionData &other) const
    {
        if (m_trackable == other.m_trackable)
        {
            return m_objectList == other.m_objectList;
        }
        return false;
    }

    bool QExtFunctionData::operator!=(const QExtFunctionData &other) const
    {
        return !(*this == other);
    }

    QExtFunctionBase::QExtFunctionBase()
        : m_blocked(QEXT_ATOMIC_INT_FALSE), m_parent(QEXT_NULLPTR), m_cleanupFunc(QEXT_NULLPTR), m_callFunc(QEXT_NULLPTR)
    {
    }

    QExtFunctionBase::QExtFunctionBase(const QSharedPointer< QExtFunctionData > &data)
        : m_blocked(QEXT_ATOMIC_INT_FALSE), m_parent(QEXT_NULLPTR), m_cleanupFunc(QEXT_NULLPTR), m_callFunc(QEXT_NULLPTR), m_data(data)
    {
    }

    QExtFunctionBase::QExtFunctionBase(const QExtFunctionBase &other)
        : m_blocked(other.m_blocked), m_parent(other.m_parent), m_cleanupFunc(other.m_cleanupFunc), m_callFunc(other.m_callFunc), m_data(other.m_data)
    {
    }

    QExtFunctionBase &QExtFunctionBase::operator=(const QExtFunctionBase &other)
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

    bool QExtFunctionBase::operator==(const QExtFunctionBase &other) const
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

    bool QExtFunctionBase::operator!=(const QExtFunctionBase &other) const
    {
        return !(*this == other);
    }

    bool QExtFunctionBase::isNull() const
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

    bool QExtFunctionBase::isTrackable() const
    {
        if (!m_data.isNull())
        {
            return m_data->m_trackable == QEXT_ATOMIC_INT_TRUE;
        }
        return false;
    }

    bool QExtFunctionBase::isBlocked() const
    {
        return m_blocked == QEXT_ATOMIC_INT_TRUE;
    }

    bool QExtFunctionBase::setBlock(bool block)
    {
        m_blocked = block ? QEXT_ATOMIC_INT_TRUE : QEXT_ATOMIC_INT_FALSE;
        return true;
    }

    bool QExtFunctionBase::unblock()
    {
        m_blocked = QEXT_ATOMIC_INT_FALSE;
        return true;
    }

    bool QExtFunctionBase::isValid() const
    {
        return QEXT_NULLPTR != m_callFunc && !m_data.isNull() && !this->isNull();
    }

    void QExtFunctionBase::setParent(void *parent, HookFunction cleanup)
    {
        m_parent = parent;
        m_cleanupFunc = cleanup;
    }

    bool QExtFunctionBase::isConnected() const
    {
        return m_parent && m_cleanupFunc;
    }

    void QExtFunctionBase::disconnect()
    {
        if (m_parent)
        {
            // Invalidate the slot.
            // Must be done here because m_parent might defer the actual
            (m_cleanupFunc)(m_parent);  // Notify the parent (might lead to destruction of this!).
            m_parent = QEXT_NULLPTR; // Just a precaution.
        }
    }

} // namespace QExtPrivate


