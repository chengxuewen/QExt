// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/model/taginfo.h"
#include "model/utils/containerutils.h"
#include <sstream>
#include <stdexcept>

ModelView::QExtMvvmTagInfo::QExtMvvmTagInfo() : m_min(0), m_max(-1) {}

ModelView::QExtMvvmTagInfo::QExtMvvmTagInfo(std::string name, int min, int max, std::vector<std::string> modelTypes)
    : m_name(std::move(name)), m_min(min), m_max(max), m_modelTypes(std::move(modelTypes))
{
    if (m_min < 0 || (m_min > m_max && m_max >= 0) || m_name.empty()) {
        std::ostringstream ostr;
        ostr << "Invalid constructor parameters"
             << " " << m_name << " " << m_min << " " << m_max;
        throw std::runtime_error(ostr.str());
    }
}

ModelView::QExtMvvmTagInfo ModelView::QExtMvvmTagInfo::universalTag(std::string name,
                                                    std::vector<std::string> modelTypes)
{
    return QExtMvvmTagInfo(std::move(name), 0, -1, std::move(modelTypes));
}

ModelView::QExtMvvmTagInfo ModelView::QExtMvvmTagInfo::propertyTag(std::string name, std::string QExtMvvmModelType)
{
    return QExtMvvmTagInfo(std::move(name), 1, 1, {std::move(QExtMvvmModelType)});
}

std::string ModelView::QExtMvvmTagInfo::name() const
{
    return m_name;
}

int ModelView::QExtMvvmTagInfo::min() const
{
    return m_min;
}

int ModelView::QExtMvvmTagInfo::max() const
{
    return m_max;
}

std::vector<std::string> ModelView::QExtMvvmTagInfo::modelTypes() const
{
    return m_modelTypes;
}

//! Returns true if given modelType matches the list of possible model types.

bool ModelView::QExtMvvmTagInfo::isValidChild(const std::string& modelType) const
{
    return m_modelTypes.empty() ? true : Utils::Contains(m_modelTypes, modelType);
}

//! Returns true if this tag is used to store single properties.
//! Properties are children that are created in QExtMvvmSessionItem constructor using ::addProperty method.

bool ModelView::QExtMvvmTagInfo::isSinglePropertyTag() const
{
    return m_min == 1 && m_max == 1;
}

bool ModelView::QExtMvvmTagInfo::operator==(const ModelView::QExtMvvmTagInfo& other) const
{
    return m_name == other.m_name && m_min == other.m_min && m_max == other.m_max
           && m_modelTypes == other.m_modelTypes;
}

bool ModelView::QExtMvvmTagInfo::operator!=(const ModelView::QExtMvvmTagInfo& other) const
{
    return !(*this == other);
}
