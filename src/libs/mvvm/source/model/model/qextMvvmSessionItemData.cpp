#include <algorithm>
#include <qextMvvmCustomVariants.h>
#include <qextMvvmSessionItemData.h>
#include <sstream>
#include <stdexcept>

using namespace ModelView;

std::vector<int> QEXTMvvmSessionItemData::roles() const
{
    std::vector<int> result;
    for (const auto& value : m_values)
        result.push_back(value.m_role);
    return result;
}

QEXTMvvmVariant QEXTMvvmSessionItemData::data(int role) const
{
    for (const auto& value : m_values) {
        if (value.m_role == role)
            return value.m_data;
    }
    return QEXTMvvmVariant();
}

//! Sets the data for given role. Returns true if data was changed.
//! If variant is invalid, corresponding role will be removed.

bool QEXTMvvmSessionItemData::setData(const QEXTMvvmVariant& value, int role)
{
    assure_validity(value, role);

    for (auto it = m_values.begin(); it != m_values.end(); ++it) {
        if (it->m_role == role) {
            if (value.isValid()) {
                if (Utils::IsTheSame(it->m_data, value))
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

QEXTMvvmSessionItemData::const_iterator QEXTMvvmSessionItemData::begin() const
{
    return m_values.begin();
}

QEXTMvvmSessionItemData::const_iterator QEXTMvvmSessionItemData::end() const
{
    return m_values.end();
}

//! Returns true if item has data with given role.

bool QEXTMvvmSessionItemData::hasData(int role) const
{
    auto has_role = [role](const auto& x) { return x.m_role == role; };
    return std::find_if(m_values.begin(), m_values.end(), has_role) != m_values.end();
}

//! Check if variant is compatible

void QEXTMvvmSessionItemData::assure_validity(const QEXTMvvmVariant& variant, int role)
{
    if (variant.typeName() == QStringLiteral("QString"))
        throw std::runtime_error("Attempt to set QString based variant");

    if (!Utils::CompatibleVariantTypes(data(role), variant)) {
        std::ostringstream ostr;
        ostr << "QEXTMvvmSessionItemData::assure_validity() -> Error. QEXTMvvmVariant types mismatch. "
             << "Old variant type '" << data(role).typeName() << "' "
             << "new variant type '" << variant.typeName() << "\n";
        throw std::runtime_error(ostr.str());
    }
}
