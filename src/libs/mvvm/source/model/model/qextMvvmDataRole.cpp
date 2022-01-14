// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmCustomVariants.h>
#include <qextMvvmDataRole.h>

using namespace ModelView;

QEXTMvvmDataRole::QEXTMvvmDataRole(QVariant data, int role) : m_data(std::move(data)), m_role(role) {}

bool QEXTMvvmDataRole::operator==(const QEXTMvvmDataRole& other) const
{
    return m_role == other.m_role && QEXTMvvmUtils::IsTheSame(m_data, other.m_data);
}
