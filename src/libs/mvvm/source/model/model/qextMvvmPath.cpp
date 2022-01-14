// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <algorithm>
#include <iterator>
#include <qextMvvmPath.h>
#include <numeric>
#include <sstream>

using namespace ModelView;

//! Constructs Path object from string containing sequence of integers ("0,0,1,3").

QEXTMvvmPath QEXTMvvmPath::fromString(const std::string& str)
{
    QEXTMvvmPath result;

    std::string str_spaces(str);
    std::replace(str_spaces.begin(), str_spaces.end(), ',', ' ');

    std::istringstream iss(str_spaces);
    std::for_each(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),
                  [&result](std::string x) { result.append(std::stoi(x)); });
    return result;
}

//! Constructs Path object from vector of integers..

QEXTMvvmPath QEXTMvvmPath::fromVector(const std::vector<int>& data)
{
    QEXTMvvmPath result;
    std::for_each(data.begin(), data.end(), [&result](int x) { result.append(x); });
    return result;
}

//! Returns string representing path ("0,0,1,3").

std::string QEXTMvvmPath::str() const
{
    auto comma_fold = [](std::string a, int b) { return std::move(a) + ',' + std::to_string(b); };
    return m_data.empty() ? std::string()
                          : std::accumulate(std::next(m_data.begin()), m_data.end(),
                                            std::to_string(m_data[0]), comma_fold);
}

void QEXTMvvmPath::append(QEXTMvvmPath::PathElement element)
{
    m_data.push_back(element);
}

void QEXTMvvmPath::prepend(QEXTMvvmPath::PathElement element)
{
    m_data.insert(m_data.begin(), element);
}

QEXTMvvmPath::iterator QEXTMvvmPath::begin()
{
    return m_data.begin();
}

QEXTMvvmPath::const_iterator QEXTMvvmPath::begin() const
{
    return m_data.begin();
}

QEXTMvvmPath::iterator QEXTMvvmPath::end()
{
    return m_data.end();
}

QEXTMvvmPath::const_iterator QEXTMvvmPath::end() const
{
    return m_data.end();
}
