#include <qextMvvmCommandResult.h>

QEXTMvvmCommandResult::QEXTMvvmCommandResult()
    : m_resultValue(false)
{

}

QEXTMvvmCommandResult::QEXTMvvmCommandResult(bool value)
    : m_resultValue(value)
{

}

QEXTMvvmCommandResult::QEXTMvvmCommandResult(QEXTMvvmItem *item)
    : m_resultValue(false)
    , m_resultItem(item)
{

}

QEXTMvvmCommandResult::QEXTMvvmCommandResult(const QEXTMvvmCommandResult &other)
    : m_resultValue(other.m_resultValue)
    , m_resultItem(other.m_resultItem)
{

}

QEXTMvvmCommandResult::~QEXTMvvmCommandResult()
{

}

QEXTMvvmCommandResult &QEXTMvvmCommandResult::operator =(const QEXTMvvmCommandResult &other)
{
    if (this != &other)
    {
        m_resultItem = other.m_resultItem;
        m_resultValue = other.m_resultValue;
    }
    return *this;
}

bool QEXTMvvmCommandResult::operator ==(const QEXTMvvmCommandResult &other) const
{
    if (m_resultValue == other.m_resultValue)
    {
        return m_resultItem == other.m_resultItem;
    }
    return false;
}

bool QEXTMvvmCommandResult::operator !=(const QEXTMvvmCommandResult &other) const
{
    return !(*this == other);
}

QEXTMvvmItem *QEXTMvvmCommandResult::resultItem() const
{
    return m_resultItem.data();
}

void QEXTMvvmCommandResult::setResultItem(QEXTMvvmItem *item)
{
    m_resultItem.reset(item);
}

bool QEXTMvvmCommandResult::resultValue() const
{
    return m_resultValue;
}

void QEXTMvvmCommandResult::setResultValue(bool value)
{
    m_resultValue = value;
}
