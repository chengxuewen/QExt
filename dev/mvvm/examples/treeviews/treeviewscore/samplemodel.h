// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef TREEVIEWSCORE_SAMPLEMODEL_H
#define TREEVIEWSCORE_SAMPLEMODEL_H

#include <qextMvvmSessionModel.h>

namespace TreeViews {

//! Main application model.

class SampleModel : public ModelView::QExtMvvmSessionModel {
public:
    SampleModel();

private:
    void populateModel();
};

} // namespace TreeViews

#endif // TREEVIEWSCORE_SAMPLEMODEL_H
