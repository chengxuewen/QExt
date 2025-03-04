// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_MVVM_TYPES_H
#define MVVM_MODEL_MVVM_TYPES_H

#include "model/core/types.h"
#include <string>

namespace ModelView {

class QExtMvvmSessionItem;
class QExtMvvmSessionModel;

//! Defines constants to be used as QExtMvvmSessionItem data role.

namespace ItemDataRole {
const int IDENTIFIER = 0; //!< unique identifier
const int DATA = 1;       //!< main data role
const int DISPLAY = 2;    //!< display name
const int APPEARANCE = 3; //!< appearance flag
const int LIMITS = 4;     //!< possibly limits on item's data
const int TOOLTIP = 5;    //!< tooltip for item's data
const int EDITORTYPE = 6; //!< type of custom editor for the data role
} // namespace ItemDataRole

enum Appearance {
    ENABLED = 1,  // enabled in Qt widgets; when disabled, will be shown in gray
    EDITABLE = 2, // editable in Qt widgets; readonly otherwise
    VISIBLE = 4   // visible in Qt widgets; doesn't appear in trees and tables otherwise
};

namespace Constants {
const QExtMvvmModelType BaseType = "QExtMvvmSessionItem";
const QExtMvvmModelType ColorMapItemType = "ColorMap";
const QExtMvvmModelType ColorMapViewportItemType = "ColorMapViewport";
const QExtMvvmModelType CompoundItemType = "Compound";
const QExtMvvmModelType ContainerItemType = "Container";
const QExtMvvmModelType Data1DItemType = "Data1D";
const QExtMvvmModelType Data2DItemType = "Data2D";
const QExtMvvmModelType FixedBinAxisItemType = "FixedBinAxis";
const QExtMvvmModelType GraphItemType = "Graph";
const QExtMvvmModelType GraphViewportItemType = "GraphViewport";
const QExtMvvmModelType GroupItemType = "Group";
const QExtMvvmModelType LinkedItemType = "Linked";
const QExtMvvmModelType PenItemType = "Pen";
const QExtMvvmModelType PointwiseAxisItemType = "PointwiseAxis";
const QExtMvvmModelType PropertyType = "Property";
const QExtMvvmModelType TextItemType = "Text";
const QExtMvvmModelType VectorItemType = "Vector";
const QExtMvvmModelType ViewportAxisItemType = "ViewportAxis";
} // namespace Constants

} // namespace ModelView

#endif // MVVM_MODEL_MVVM_TYPES_H
