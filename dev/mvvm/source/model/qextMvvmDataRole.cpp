// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmDataRole.h>
#include <qextMvvmCustomVariants.h>

using namespace ModelView;

QExtMvvmDataRole::QExtMvvmDataRole(QVariant data, int role) : m_data(std::move(data)), m_role(role) {}

bool QExtMvvmDataRole::operator==(const QExtMvvmDataRole& other) const
{
    return m_role == other.m_role && Utils::IsTheSame(m_data, other.m_data);
}
