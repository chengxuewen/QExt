// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iterator>
#include <qextMvvmStringUtils.h>
#include <sstream>
#include <string_view>

#include <QString>

using namespace ModelView;

std::string QEXTMvvmUtils::DoubleToString(double input, int precision)
{
    std::ostringstream inter;
    inter << std::setprecision(precision);
    if (std::abs(input) < std::numeric_limits<double>::epsilon()) {
        inter << "0.0";
        return inter.str();
    }
    inter << input;
    if (inter.str().find('e') == std::string::npos && inter.str().find('.') == std::string::npos)
        inter << ".0";
    return inter.str();
}

std::string QEXTMvvmUtils::ScientificDoubleToString(double input, int precision)
{
    std::ostringstream inter;
    inter << std::scientific;
    inter << std::setprecision(precision);
    inter << input;

    std::string::size_type pos = inter.str().find('e');
    if (pos == std::string::npos)
        return inter.str();

    std::string part1 = inter.str().substr(0, pos);
    std::string part2 = inter.str().substr(pos, std::string::npos);

    part1.erase(part1.find_last_not_of('0') + 1, std::string::npos);
    if (part1.back() == '.')
        part1 += "0";

    return part1 + part2;
}

std::string QEXTMvvmUtils::TrimWhitespace(const std::string& str)
{
    const char whitespace[]{" \t\n"};
    const size_t first = str.find_first_not_of(whitespace);
    if (std::string::npos == first)
        return {};
    const size_t last = str.find_last_not_of(whitespace);
    return str.substr(first, (last - first + 1));
}

std::string QEXTMvvmUtils::RemoveRepeatedSpaces(std::string str)
{
    if (str.empty())
        return {};
    auto it = std::unique(str.begin(), str.end(),
                          [](std::string::value_type x, std::string::value_type y) { return x == y && std::isspace(x); });
    str.erase(it, str.end());
    return str;
}


std::vector<std::string> QEXTMvvmUtils::SplitString(const std::string& str, const std::string& delimeter)
{
    // splitting string following Python's str.split()
    if (delimeter.empty())
        throw std::runtime_error("Empty delimeter");
    if (str.empty())
        return {};

    std::vector<std::string> result;
//    std::string_view view(str);
//    size_t pos{0};
    //    while ((pos = view.find(delimeter)) != std::string::npos) {
    //        result.emplace_back(std::string(view.substr(0, pos)));
    //        view.remove_prefix(pos + delimeter.length());
    //    }
    //    result.emplace_back(std::string(view));

    QString view = QString::fromStdString(str);
    QString qdelimeter = QString::fromStdString(delimeter);
    int pos = -1;
    while ((pos = view.indexOf(qdelimeter)) != -1) {
        result.emplace_back(view.left(pos).toStdString());
        view = view.mid(pos + delimeter.length());
    }
    result.emplace_back(view.toStdString());

    return result;
}

std::vector<double> QEXTMvvmUtils::ParseSpaceSeparatedDoubles(const std::string& str)
{
    std::vector<double> result;
    ParseSpaceSeparatedDoubles(str, result);
    return result;
}

void QEXTMvvmUtils::ParseSpaceSeparatedDoubles(const std::string& str, std::vector<double>& result)
{
    std::istringstream iss(str);
    iss.imbue(std::locale::classic());
    std::copy(std::istream_iterator<double>(iss), std::istream_iterator<double>(),
              back_inserter(result));
}
