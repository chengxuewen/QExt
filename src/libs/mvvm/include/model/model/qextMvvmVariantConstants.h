#ifndef _QEXTMVVMVARIANTCONSTANTS_H
#define _QEXTMVVMVARIANTCONSTANTS_H

#include <string>

//! @file variant-constants.h
//! Collection of constants with supported variant names.

namespace ModelView
{
    namespace Constants
    {

        const std::string invalid_type_name = "invalid";
        const std::string bool_type_name = "bool";
        const std::string int_type_name = "int";
        const std::string string_type_name = "std::string";
        const std::string double_type_name = "double";
        const std::string vector_double_type_name = "std::vector<double>";
        const std::string comboproperty_type_name = "ModelView::QEXTMvvmComboProperty";
        const std::string qcolor_type_name = "QColor";
        const std::string extproperty_type_name = "ModelView::QEXTMvvmExternalProperty";
        const std::string reallimits_type_name = "ModelView::QEXTMvvmRealLimits";

    } // namespace Constants

} // namespace ModelView

#endif // _QEXTMVVMVARIANTCONSTANTS_H
