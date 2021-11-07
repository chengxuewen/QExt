#ifndef _QEXTMVVMCONSTANTS_H
#define _QEXTMVVMCONSTANTS_H

#include <qextMvvmGlobal.h>
#include <qextMvvmTypes.h>

#include <string>

class QEXTMvvmItem;
class QEXTMvvmModel;

enum Appearance
{
    NOFLAGS = 0x000,
    ENABLED = 0x001, // enabled in Qt widgets; when disabled, will be shown in gray
    EDITABLE = 0x002 // editable in Qt widgets; readonly otherwise
};

namespace QEXTMvvmConstants
{
    static const char *BaseType = "QEXTMvvmItem";
    static const char *ColorMapItemType = "ColorMap";
    static const char *ColorMapViewportItemType = "ColorMapViewport";
    static const char *CompoundItemType = "Compound";
    static const char *ContainerItemType = "Container";
    static const char *Data1DItemType = "Data1D";
    static const char *Data2DItemType = "Data2D";
    static const char *FixedBinAxisItemType = "FixedBinAxis";
    static const char *GraphItemType = "Graph";
    static const char *GraphViewportItemType = "GraphViewport";
    static const char *GroupItemType = "Group";
    static const char *LinkedItemType = "Linked";
    static const char *PenItemType = "Pen";
    static const char *PointwiseAxisItemType = "PointwiseAxis";
    static const char *PropertyType = "Property";
    static const char *TextItemType = "Text";
    static const char *VectorItemType = "Vector";
    static const char *ViewportAxisItemType = "ViewportAxis";

    static const char *BoolEditorType = "BoolEditor";
    static const char *ColorEditorType = "ColorEditor";
    static const char *ComboPropertyEditorType = "ComboPropertyEditor";
    static const char *DoubleEditorType = "DoubleEditor";
    static const char *ExternalPropertyEditorType = "ExternalPropertyEditor";
    static const char *IntegerEditorType = "IntegerEditor";
    static const char *ScientficDoubleEditorType = "ScientficDoubleEditor";
    static const char *ScientficSpinBoxEditorType = "ScientficSpinBoxEditor";
    static const char *SelectableComboPropertyEditorType = "SelectableComboPropertyEditor";

    static const char *invalid_type_name = "invalid";
    static const char *bool_type_name = "bool";
    static const char *int_type_name = "int";
    static const char *double_type_name = "double";
    static const char *string_type_name = "std::string";
    static const char *color_type_name = "QColor";
    static const char *vector_double_type_name = "std::vector<double>";
    static const char *comboproperty_type_name = "CFMvvmComboProperty";
    static const char *extproperty_type_name = "CFMvvmExternalProperty";
    static const char *reallimits_type_name = "CFMvvmRealLimits";

    static const int default_double_decimals = 4; //! number of digits after decimal points
}

#endif // _QEXTMVVMCONSTANTS_H
