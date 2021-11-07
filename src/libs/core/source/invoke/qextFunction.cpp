#include <qextFunction.h>

namespace qextPrivate
{

    QEXTFunctionData::QEXTFunctionData() : m_trackable(QEXT_ATOMIC_INT_FALSE) {}

    QEXTFunctionData::QEXTFunctionData(const QEXTFunctionData &other) : m_trackable(other.m_trackable), m_objectList(other.m_objectList) {}

    QEXTFunctionData &QEXTFunctionData::operator=(const QEXTFunctionData &other)
    {
        if (this != &other)
        {
            m_trackable = other.m_trackable;
            m_objectList = other.m_objectList;
        }
        return *this;
    }

    bool QEXTFunctionData::operator==(const QEXTFunctionData &other) const
    {
        if (m_trackable == other.m_trackable)
        {
            return m_objectList == other.m_objectList;
        }
        return false;
    }

    bool QEXTFunctionData::operator!=(const QEXTFunctionData &other) const
    {
        return !(*this == other);
    }

    QEXTFunctionBase::QEXTFunctionBase()
        : m_blocked(QEXT_ATOMIC_INT_FALSE), m_parent(QEXT_DECL_NULLPTR), m_cleanupFunc(QEXT_DECL_NULLPTR), m_callFunc(QEXT_DECL_NULLPTR)
    {
    }

    QEXTFunctionBase::QEXTFunctionBase(const QSharedPointer< QEXTFunctionData > &data)
        : m_blocked(QEXT_ATOMIC_INT_FALSE), m_parent(QEXT_DECL_NULLPTR), m_cleanupFunc(QEXT_DECL_NULLPTR), m_callFunc(QEXT_DECL_NULLPTR), m_data(data)
    {
    }

    QEXTFunctionBase::QEXTFunctionBase(const QEXTFunctionBase &other)
        : m_blocked(other.m_blocked), m_parent(other.m_parent), m_cleanupFunc(other.m_cleanupFunc), m_callFunc(other.m_callFunc), m_data(other.m_data)
    {
    }

    QEXTFunctionBase &QEXTFunctionBase::operator=(const QEXTFunctionBase &other)
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

    bool QEXTFunctionBase::operator==(const QEXTFunctionBase &other) const
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

    bool QEXTFunctionBase::operator!=(const QEXTFunctionBase &other) const
    {
        return !(*this == other);
    }

    bool QEXTFunctionBase::isNull() const
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

    bool QEXTFunctionBase::isTrackable() const
    {
        if (!m_data.isNull())
        {
            return m_data->m_trackable == QEXT_ATOMIC_INT_TRUE;
        }
        return false;
    }

    bool QEXTFunctionBase::isBlocked() const
    {
        return m_blocked == QEXT_ATOMIC_INT_TRUE;
    }

    bool QEXTFunctionBase::setBlock(bool block)
    {
        m_blocked = block ? QEXT_ATOMIC_INT_TRUE : QEXT_ATOMIC_INT_FALSE;
        return true;
    }

    bool QEXTFunctionBase::unblock()
    {
        m_blocked = QEXT_ATOMIC_INT_FALSE;
        return true;
    }

    bool QEXTFunctionBase::isValid() const
    {
        return QEXT_DECL_NULLPTR != m_callFunc && !m_data.isNull() && !this->isNull();
    }

    void QEXTFunctionBase::setParent(void *parent, HookFunction cleanup)
    {
        m_parent = parent;
        m_cleanupFunc = cleanup;
    }

    bool QEXTFunctionBase::isConnected() const
    {
        return m_parent && m_cleanupFunc;
    }

    void QEXTFunctionBase::disconnect()
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


