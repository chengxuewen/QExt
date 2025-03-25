// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DRAGANDMOVECORE_SAMPLEMODEL_H
#define DRAGANDMOVECORE_SAMPLEMODEL_H

#include <qextMvvmSessionModel.h>

namespace ModelView {
class QExtMvvmSessionItem;
}

namespace DragAndMove {

//! Main application model.

class SampleModel : public ModelView::QExtMvvmSessionModel {
public:
    SampleModel();

    void appendRandomItem(ModelView::QExtMvvmSessionItem* container);

private:
    void populateModel();
};

} // namespace DragAndMove

#endif // DRAGANDMOVECORE_SAMPLEMODEL_H
