#include <algorithm>
#include <qextMvvmTagInfo.h>
#include <qextMvvmUtils.h>
#include <sstream>
#include <stdexcept>

QEXTMvvmTagInfo::QEXTMvvmTagInfo()
    : m_min(0)
    , m_max(-1)
{

}

QEXTMvvmTagInfo::QEXTMvvmTagInfo(const QString &name, int min, int max, const QVector<QString> &modelTypes)
    : m_name(name)
    , m_min(min)
    , m_max(max)
    , m_modelTypes(modelTypes)
{
    if (m_min < 0 || (m_min > m_max && m_max >= 0) || m_name.isEmpty())
    {
        std::ostringstream ostr;
        ostr << "Invalid constructor parameters"
             << " " << m_name.toStdString() << " " << m_min << " " << m_max;
        throw std::runtime_error(ostr.str());
    }
}

QEXTMvvmTagInfo QEXTMvvmTagInfo::universalTag(const QString &name, const QVector<QString> &modelTypes)
{
    return QEXTMvvmTagInfo(name, 0, -1, modelTypes);
}

QEXTMvvmTagInfo QEXTMvvmTagInfo::propertyTag(const QString &name, const QString &modelType)
{
    return QEXTMvvmTagInfo(name, 1, 1, QVector<QString>(1, modelType));
}

QString QEXTMvvmTagInfo::name() const
{
    return m_name;
}

int QEXTMvvmTagInfo::min() const
{
    return m_min;
}

int QEXTMvvmTagInfo::max() const
{
    return m_max;
}

QVector<QString> QEXTMvvmTagInfo::modelTypes() const
{
    return m_modelTypes;
}

bool QEXTMvvmTagInfo::isValidChild(const QString &child) const
{
    return m_modelTypes.isEmpty() ? true : m_modelTypes.contains(child);
}

bool QEXTMvvmTagInfo::isSinglePropertyTag() const
{
    return m_min == 1 && m_max == 1;
}

bool QEXTMvvmTagInfo::operator==(const QEXTMvvmTagInfo &other) const
{
    return m_name == other.m_name
           && m_min == other.m_min
           && m_max == other.m_max
           && m_modelTypes == other.m_modelTypes;
}

bool QEXTMvvmTagInfo::operator!=(const QEXTMvvmTagInfo &other) const
{
    return !(*this == other);
}
