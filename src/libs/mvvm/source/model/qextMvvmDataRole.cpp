#include <qextMvvmUtils.h>
#include <qextMvvmDataRole.h>



QEXTMvvmDataRole::QEXTMvvmDataRole(QVariant data, int role) : m_data(data), m_role(role) {}

bool QEXTMvvmDataRole::operator==(const QEXTMvvmDataRole& other) const
{
    return m_role == other.m_role && QEXTMvvmUtils::IsTheSame(m_data, other.m_data);
}
