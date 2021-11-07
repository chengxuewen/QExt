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

#include <qextMvvmModel.h>


class QEXTMvvmItem;


namespace DragAndView
{

//! Main application model.

class SampleModel : public QEXTMvvmModel
{
public:
    SampleModel();

    void append_random_item(QEXTMvvmItem* container);

private:
    void init_model_content();
};

} // namespace DragAndView

#endif
