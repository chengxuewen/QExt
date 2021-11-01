#include <algorithm>
#include <qextMvvmTagInfo.h>
#include <utils/qextMvvmContainerUtils.h>
#include <sstream>
#include <stdexcept>

ModelView::QEXTMvvmTagInfo::QEXTMvvmTagInfo() : m_min(0), m_max(-1) {}

ModelView::QEXTMvvmTagInfo::QEXTMvvmTagInfo(std::string name, int min, int max, std::vector<std::string> modelTypes)
    : m_name(std::move(name)), m_min(min), m_max(max), m_modelTypes(std::move(modelTypes))
{
    if (m_min < 0 || (m_min > m_max && m_max >= 0) || m_name.empty()) {
        std::ostringstream ostr;
        ostr << "Invalid constructor parameters"
             << " " << m_name << " " << m_min << " " << m_max;
        throw std::runtime_error(ostr.str());
    }
}

ModelView::QEXTMvvmTagInfo ModelView::QEXTMvvmTagInfo::universalTag(std::string name,
                                                    std::vector<std::string> modelTypes)
{
    return QEXTMvvmTagInfo(std::move(name), 0, -1, std::move(modelTypes));
}

ModelView::QEXTMvvmTagInfo ModelView::QEXTMvvmTagInfo::propertyTag(std::string name, std::string QEXTMvvmModelType)
{
    return QEXTMvvmTagInfo(std::move(name), 1, 1, {std::move(QEXTMvvmModelType)});
}

std::string ModelView::QEXTMvvmTagInfo::name() const
{
    return m_name;
}

int ModelView::QEXTMvvmTagInfo::min() const
{
    return m_min;
}

int ModelView::QEXTMvvmTagInfo::max() const
{
    return m_max;
}

std::vector<std::string> ModelView::QEXTMvvmTagInfo::modelTypes() const
{
    return m_modelTypes;
}

bool ModelView::QEXTMvvmTagInfo::isValidChild(const std::string& child) const
{
    return m_modelTypes.empty() ? true : Utils::Contains(m_modelTypes, child);
}

bool ModelView::QEXTMvvmTagInfo::isSinglePropertyTag() const
{
    return m_min == 1 && m_max == 1;
}

bool ModelView::QEXTMvvmTagInfo::operator==(const ModelView::QEXTMvvmTagInfo& other) const
{
    return m_name == other.m_name && m_min == other.m_min && m_max == other.m_max
           && m_modelTypes == other.m_modelTypes;
}

bool ModelView::QEXTMvvmTagInfo::operator!=(const ModelView::QEXTMvvmTagInfo& other) const
{
    return !(*this == other);
}
