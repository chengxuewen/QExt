#ifndef _QEXTMVVMCONSTANTS_H
#define _QEXTMVVMCONSTANTS_H

#include <qextMvvmGlobal.h>

#include <string>

class QEXT_MVVM_API QEXTMvvmConstants
{
public:
    QEXTMvvmConstants();

    static const char *BoolEditorType;
    static const char *ColorEditorType;
    static const char *ComboPropertyEditorType;
    static const char *DoubleEditorType;
    static const char *ExternalPropertyEditorType;
    static const char *IntegerEditorType;
    static const char *ScientficDoubleEditorType;
    static const char *ScientficSpinBoxEditorType;
    static const char *SelectableComboPropertyEditorType;

    static const char *invalid_type_name;
    static const char *bool_type_name;
    static const char *int_type_name;
    static const char *string_type_name;
    static const char *double_type_name;
    static const char *vector_double_type_name;
    static const char *comboproperty_type_name;
    static const char *qcolor_type_name;
    static const char *extproperty_type_name;
    static const char *reallimits_type_name;

    static const int default_double_decimals;
};

#endif // _QEXTMVVMCONSTANTS_H
