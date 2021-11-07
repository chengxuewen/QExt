#include <algorithm>
#include <qextMvvmUtils.h>
#include <qextMvvmItemData.h>
#include <sstream>
#include <stdexcept>



QVector<int> QEXTMvvmItemData::roles() const
{
    QVector<int> result;
    for (const auto& value : m_values)
        result.push_back(value.m_role);
    return result;
}

QVariant QEXTMvvmItemData::data(int role) const
{
    for (const auto& value : m_values) {
        if (value.m_role == role)
            return value.m_data;
    }
    return QVariant();
}

//! Sets the data for given role. Returns true if data was changed.
//! If variant is invalid, corresponding role will be removed.

bool QEXTMvvmItemData::setData(const QVariant& value, int role)
{
    for (auto it = m_values.begin(); it != m_values.end(); ++it) {
        if (it->m_role == role) {
            if (value.isValid()) {
                if (QEXTMvvmUtils::IsTheSame(it->m_data, value))
                    return false;
                it->m_data = value;
            } else {
                m_values.erase(it);
            }
            return true;
        }
    }
    m_values.push_back(QEXTMvvmDataRole(value, role));
    return true;
}

QEXTMvvmItemData::const_iterator QEXTMvvmItemData::begin() const
{
    return m_values.begin();
}

QEXTMvvmItemData::const_iterator QEXTMvvmItemData::end() const
{
    return m_values.end();
}

//! Returns true if item has data with given role.

bool QEXTMvvmItemData::hasData(int role) const
{
    auto has_role = [role](const auto& x) { return x.m_role == role; };
    return std::find_if(m_values.begin(), m_values.end(), has_role) != m_values.end();
}
