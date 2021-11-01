#include <qextMvvmCustomVariants.h>
#include <qextMvvmDataRole.h>

using namespace ModelView;

QEXTMvvmDataRole::QEXTMvvmDataRole(QEXTMvvmVariant data, int role) : m_data(std::move(data)), m_role(role) {}

bool QEXTMvvmDataRole::operator==(const QEXTMvvmDataRole& other) const
{
    return m_role == other.m_role && Utils::IsTheSame(m_data, other.m_data);
}
