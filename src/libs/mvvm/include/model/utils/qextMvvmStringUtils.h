#ifndef _QEXTMVVMUTILSSTRINGUTILS_H
#define _QEXTMVVMUTILSSTRINGUTILS_H

#include <qextMvvmGlobal.h>

#include <optional>
#include <string>
#include <vector>

namespace ModelView ::QEXTMvvmUtils
{

//! Returns string representation of double with given precision.
//! Provides additional formatting on top of iomanip, so "double x{0}" becomes "0.0".
QEXT_MVVM_API std::string DoubleToString(double input, int precision = 12);

//! Returns string representation of scientific double.
//! Provides additional formatting on top of iomanip, so "double x{1}" becomes "1.0e+00".
QEXT_MVVM_API std::string ScientificDoubleToString(double input, int precision = 6);

//! Returns string after trimming whitespace surrounding, including tabs and carriage returns.
QEXT_MVVM_API std::string TrimWhitespace(const std::string& str);

//! Removes repeating spaces for a string.
QEXT_MVVM_API std::string RemoveRepeatedSpaces(std::string str);

//! Split string on substring using given delimeter. Reproduces Python's str.split() behavior.
QEXT_MVVM_API std::vector<std::string> SplitString(const std::string& str,
                                                       const std::string& delimeter);

//! Parses string for double values and returns result as a vector.
//! All non-numeric symbols are ingored.
QEXT_MVVM_API std::vector<double> ParseSpaceSeparatedDoubles(const std::string& str);

//! Parses string for double values and stores result in a vector.
//! All non-numeric symbols are ingored.
QEXT_MVVM_API void ParseSpaceSeparatedDoubles(const std::string& str,
                                                  std::vector<double>& result);

} // namespace ModelView::Utils

#endif // _QEXTMVVMUTILSSTRINGUTILS_H
