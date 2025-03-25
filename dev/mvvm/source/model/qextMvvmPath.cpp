// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmPath.h>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <sstream>

using namespace ModelView;

//! Constructs QExtMvvmPath object from string containing sequence of integers ("0,0,1,3").

QExtMvvmPath QExtMvvmPath::fromString(const std::string& str)
{
    QExtMvvmPath result;

    std::string str_spaces(str);
    std::replace(str_spaces.begin(), str_spaces.end(), ',', ' ');

    std::istringstream iss(str_spaces);
    std::for_each(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),
                  [&result](std::string x) { result.append(std::stoi(x)); });
    return result;
}

//! Constructs QExtMvvmPath object from vector of integers..

QExtMvvmPath QExtMvvmPath::fromVector(const std::vector<int>& data)
{
    QExtMvvmPath result;
    std::for_each(data.begin(), data.end(), [&result](int x) { result.append(x); });
    return result;
}

//! Returns string representing path ("0,0,1,3").

std::string QExtMvvmPath::str() const
{
    auto comma_fold = [](std::string a, int b) { return std::move(a) + ',' + std::to_string(b); };
    return m_data.empty() ? std::string()
                          : std::accumulate(std::next(m_data.begin()), m_data.end(),
                                            std::to_string(m_data[0]), comma_fold);
}

void QExtMvvmPath::append(QExtMvvmPath::PathElement element)
{
    m_data.push_back(element);
}

void QExtMvvmPath::prepend(QExtMvvmPath::PathElement element)
{
    m_data.insert(m_data.begin(), element);
}

QExtMvvmPath::iterator QExtMvvmPath::begin()
{
    return m_data.begin();
}

QExtMvvmPath::const_iterator QExtMvvmPath::begin() const
{
    return m_data.begin();
}

QExtMvvmPath::iterator QExtMvvmPath::end()
{
    return m_data.end();
}

QExtMvvmPath::const_iterator QExtMvvmPath::end() const
{
    return m_data.end();
}
