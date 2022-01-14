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
#include <limits>
#include <qextMvvmNumericUtils.h>
#include <random>

using namespace ModelView;

bool QEXTMvvmUtils::AreAlmostEqual(double a, double b, double tolerance)
{
    constexpr double eps = std::numeric_limits<double>::epsilon();
    return std::abs(a - b)
           <= eps * std::max(tolerance * eps, std::max(1., tolerance) * std::abs(b));
}

int QEXTMvvmUtils::RandInt(int low, int high)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> uniform_int(low, high);
    return uniform_int(gen);
}

double QEXTMvvmUtils::RandDouble(double low, double high)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> uniform_real(low, high);
    return uniform_real(gen);
}
