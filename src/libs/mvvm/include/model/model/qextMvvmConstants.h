#ifndef _QEXTMVVMCONSTANTS_H
#define _QEXTMVVMCONSTANTS_H

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

namespace Constants
{
const QEXTMvvmModelType BaseType = "QEXTMvvmSessionItem";
const QEXTMvvmModelType ColorMapItemType = "ColorMap";
const QEXTMvvmModelType ColorMapViewportItemType = "ColorMapViewport";
const QEXTMvvmModelType CompoundItemType = "Compound";
const QEXTMvvmModelType ContainerItemType = "Container";
const QEXTMvvmModelType Data1DItemType = "Data1D";
const QEXTMvvmModelType Data2DItemType = "Data2D";
const QEXTMvvmModelType FixedBinAxisItemType = "FixedBinAxis";
const QEXTMvvmModelType GraphItemType = "Graph";
const QEXTMvvmModelType GraphViewportItemType = "GraphViewport";
const QEXTMvvmModelType GroupItemType = "Group";
const QEXTMvvmModelType LinkedItemType = "Linked";
const QEXTMvvmModelType PenItemType = "Pen";
const QEXTMvvmModelType PointwiseAxisItemType = "PointwiseAxis";
const QEXTMvvmModelType PropertyType = "Property";
const QEXTMvvmModelType TextItemType = "Text";
const QEXTMvvmModelType VectorItemType = "Vector";
const QEXTMvvmModelType ViewportAxisItemType = "ViewportAxis";
} // namespace Constants

} // namespace ModelView

#endif // _QEXTMVVMCONSTANTS_H
