#ifndef _QEXTMVVMMODELMVVMTYPES_H
#define _QEXTMVVMMODELMVVMTYPES_H

#include <qextMvvmTypes.h>

#include <string>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmSessionModel;

//! Defines constants to be used as QEXTMvvmSessionItem data role.

namespace ItemDataRole
{
const int IDENTIFIER = 0; //!< unique identifier
const int DATA = 1;       //!< main data role
const int DISPLAY = 2;    //!< display name
const int APPEARANCE = 3; //!< appearance flag
const int LIMITS = 4;     //!< possibly limits on item's data
const int TOOLTIP = 5;    //!< tooltip for item's data
const int EDITORTYPE = 6; //!< type of custom editor for the data role
};                        // namespace ItemDataRole

enum Appearance {
    NOFLAGS = 0x000,
    ENABLED = 0x001, // enabled in Qt widgets; when disabled, will be shown in gray
    EDITABLE = 0x002 // editable in Qt widgets; readonly otherwise
};

namespace QEXTMvvmConstants
{
const model_type BaseType = "QEXTMvvmSessionItem";
const model_type ColorMapItemType = "ColorMap";
const model_type ColorMapViewportItemType = "ColorMapViewport";
const model_type CompoundItemType = "Compound";
const model_type ContainerItemType = "Container";
const model_type Data1DItemType = "Data1D";
const model_type Data2DItemType = "Data2D";
const model_type FixedBinAxisItemType = "FixedBinAxis";
const model_type GraphItemType = "Graph";
const model_type GraphViewportItemType = "GraphViewport";
const model_type GroupItemType = "Group";
const model_type LinkedItemType = "Linked";
const model_type PenItemType = "Pen";
const model_type PointwiseAxisItemType = "PointwiseAxis";
const model_type PropertyType = "Property";
const model_type TextItemType = "Text";
const model_type VectorItemType = "Vector";
const model_type ViewportAxisItemType = "ViewportAxis";
} // namespace Constants

} // namespace ModelView

#endif // _QEXTMVVMMODELMVVMTYPES_H
