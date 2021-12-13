// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SAMPLEMODEL_H
#define SAMPLEMODEL_H

#include <qextMvvmSessionModel.h>

namespace ModelView
{
class QEXTMvvmSessionItem;
}

namespace DragAndView
{

//! Main application model.

class SampleModel : public ModelView::SessionModel
{
public:
    SampleModel();

    void append_random_item(ModelView::QEXTMvvmSessionItem* container);

private:
    void init_model_content();
};

} // namespace DragAndView

#endif
